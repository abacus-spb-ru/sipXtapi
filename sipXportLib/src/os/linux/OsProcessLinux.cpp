//
// Copyright (C) 2004-2006 SIPfoundry Inc.
// Licensed by SIPfoundry under the LGPL license.
//
// Copyright (C) 2004-2006 Pingtel Corp.  All rights reserved.
// Licensed to SIPfoundry under a Contributor Agreement.
//
// $$
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

// APPLICATION INCLUDES
#include "os/OsProcess.h"
#include "os/OsTask.h"
#include "os/linux/OsProcessLinux.h"
#include "os/linux/OsUtilLinux.h"

// EXTERNAL FUNCTIONS
// EXTERNAL VARIABLES
// CONSTANTS
// STATIC VARIABLE INITIALIZATIONS

/* //////////////////////////// PUBLIC //////////////////////////////////// */

/* ============================ CREATORS ================================== */

OsProcessLinux::OsProcessLinux()
{
}

// Destructor
OsProcessLinux::~OsProcessLinux()
{
}


/* ============================ MANIPULATORS ============================== */

OsStatus OsProcessLinux::setIORedirect(OsPath &rStdInputFilename, OsPath &rStdOutputFilename, OsPath &rStdErrorFilename)
{
    OsStatus retval = OS_FAILED;

    if (rStdInputFilename.length())
        mStdInputFilename = rStdInputFilename;
    else
        mStdInputFilename = "";
        
    
    if (rStdOutputFilename.length())
        mStdOutputFilename = rStdOutputFilename;
    else
        mStdInputFilename = "";
    
    if (rStdErrorFilename.length())
        mStdErrorFilename = rStdErrorFilename;
    else
        mStdInputFilename = "";
    
    return retval;
}

OsStatus OsProcessLinux::setPriority(int prio)
{
    OsStatus retval = OS_FAILED;
    
    if (setpriority(PRIO_PROCESS,mPID,prio) == 0)
    {
        retval = OS_SUCCESS;
    }

    return retval;
}

//waits for a process to complete before returning 
//or exits when WaitInSecs has completed
int OsProcessLinux::wait(int WaitInSecs)
{
    UtlBoolean bStillRunning = TRUE;
    int secs_waited = 0;
    int status = 1;
    int ExitCode = -1;

    if (WaitInSecs < 0)
        WaitInSecs = 0;

    if (mPID > 0)
    {
        while (bStillRunning && secs_waited <= WaitInSecs)
        {
            if (waitpid(mPID,&status,WNOHANG|WUNTRACED) != mPID)
            {
                bStillRunning = TRUE;

                OsTask::delay(1000);

                if (WaitInSecs >  0)
                    secs_waited++;
            }
            else
            {
                bStillRunning = FALSE;
                ExitCode = WEXITSTATUS(status);
            }

        }
    }
    else
        ExitCode = -1;

    return ExitCode;
}

OsStatus OsProcessLinux::kill()
{
    OsStatus retval = OS_FAILED;
    
    if (::kill(mPID, SIGTERM) == 0)
    {
        int trycount = 0;

        OsSysLog::add(FAC_PROCESS, PRI_INFO,"Attempting kill on  %s\n",mProcessName.data());

        while (isRunning() && trycount++ < 3)
        {
            OsTask::delay(1000);    
            ::kill(mPID, SIGTERM);
        }
        
        //bust a cap in it's....
        trycount = 0;
        while (isRunning() && trycount++ < 30)
        {
            ::kill(mPID, SIGKILL);
            OsTask::delay(1000);    
        }


        if (isRunning())
        {
            OsSysLog::add(FAC_PROCESS, PRI_INFO,"KILL FAILED on  %s\n",mProcessName.data());
            retval = OS_FAILED;  //not good.  the thing just won't go away
        }
        else
        {
            retval = OS_SUCCESS; //hurray! it's gone
            OsSysLog::add(FAC_PROCESS, PRI_INFO,"SUCCESSFUL KILL on  %s\n",mProcessName.data());
        }
    }

    //this is the only way "so far" that I have found for killing the parent and
    //all the children
    /* if (isRunning())
    {
    
        char killString[80];
        sprintf(killString,"ps -ef | grep \"%d\" | awk '{ print $2}' | xargs kill 2>&1>/dev/null",mPID);
        system(killString);
               
        if (!isRunning()) 
            retval = OS_SUCCESS;
    }*/

    return retval;
}

OsStatus OsProcessLinux::launch(UtlString &rAppName, UtlString parameters[], OsPath &startupDir,
                    OsProcessPriorityClass prioClass, UtlBoolean bExeclusive)
{
    OsStatus retval = OS_FAILED;

    OsUtilLinux::signal(SIGCHLD, cleanZombieProcess);

    //build one string out of the array passed in
    int parameterCount = -1;
    while (!parameters[++parameterCount].isNull());

    const char ** parms = new const char * [parameterCount + 2];
    parms[0] = rAppName.data();
    for(int i = 0; i < parameterCount; i++)
        parms[i + 1] = parameters[i].data();
    parms[parameterCount + 1] = NULL;
    
    //now fork into two processes
    int forkReturnVal = fork();
    switch (forkReturnVal) 
    {
        case -1 :   retval = OS_FAILED;
                    break;
        
        case 0 :    // this is the child process so we need to exec the new
                    // process now it's time to redirect the output, input, and
                    // error streams

                    // Note: we must use _exit() rather than exit() here.
                    // This has to do with the interactions between C++, the OS
                    // abstraction layer, and the way threads are implemented on
                    // Linux.

                        if (mStdInputFilename.length())
                        {
                            if (!freopen(mStdInputFilename.data(),"r",stdin)) 
                            {
                                osPrintf("Could not redirect stdInput in OsProcess!");
                                _exit(1);
                            }
                        }

                        if (mStdOutputFilename.length())
                        {
                            if (!freopen(mStdOutputFilename.data(),"w",stdout)) 
                            {
                                osPrintf("Could not redirect stdOutput in OsProcess!");
                                _exit(1);
                            }
                        }               

                        if (mStdErrorFilename.length())
                        {
                            if (!freopen(mStdErrorFilename.data(),"w",stderr)) 
                            {
                                osPrintf("Could not redirect stdError in OsProcess!");
                                _exit(1);
                            }
                        }

                    //now apply the env variables the user may have set
                    ApplyEnv();

                    //osPrintf("About to launch: %s %s\n", rAppName.data(), cmdLine.data());

                    //set the current dir for this process
                    OsFileSystem::change(startupDir);

                    //3...2...1...  Blastoff!
                    execvp(rAppName.data(), (char **) parms);
                    
                    //and it never reaches here hopefully
                    osPrintf("Failed to execute '%s'!\n", rAppName.data());
                    _exit(1);
    default :   // this is the parent process
                    mPID = forkReturnVal;
                    mParentPID = getpid();

                    retval = OS_SUCCESS;
                    break;
    }

    delete[] parms;

    return retval;
}

/* ============================ ACCESSORS ================================= */
OsStatus OsProcessLinux::getByPID(PID pid, OsProcess &rProcess)
{
    OsStatus retval = OS_FAILED;
    OsProcess process;
    OsProcessIterator pi;
    
    char buf[20];
    sprintf(buf,"%d",pid);
    OsPath pidStr = buf;
    OsStatus findRetVal = pi.readProcFile(pidStr,process);
    
    if (findRetVal == OS_SUCCESS)
    {
            rProcess.mParentPID     = process.mParentPID;
            rProcess.mPID           = process.mPID;
            rProcess.mProcessName   = process.mProcessName;
            retval = OS_SUCCESS;
    }


    return retval;
}


OsStatus OsProcessLinux::getInfo(OsProcessInfo &rProcessInfo)
{
    OsStatus retval = OS_FAILED;
    
    OsProcess process;
    OsProcessIterator pi;
    
    OsStatus findRetVal = getByPID(mPID,process);
    
    if(findRetVal == OS_SUCCESS)
    {
        rProcessInfo.parentProcessID = process.mParentPID;
        rProcessInfo.name = process.mProcessName;
        rProcessInfo.commandline = ""; //TODO
        rProcessInfo.prioClass = 0; //TODO
            
        retval = OS_SUCCESS;
    }

    return retval;
}


OsStatus OsProcessLinux::getUpTime(OsTime &rUpTime)
{
    OsStatus retval = OS_FAILED;


    return retval;
}

OsStatus OsProcessLinux::getPriorityClass(OsProcessPriorityClass &rPrioClass)
{
    OsStatus retval = OS_FAILED;

    return retval;
}

OsStatus OsProcessLinux::getMinPriority(int &rMinPrio)
{
    OsStatus retval = OS_FAILED;
    
    return retval;
}

OsStatus OsProcessLinux::getMaxPriority(int &rMaxPrio)
{
    OsStatus retval = OS_FAILED;

    return retval;
}

OsStatus OsProcessLinux::getPriority(int &rPrio)
{
    OsStatus retval = OS_FAILED;
    errno = 0;
    rPrio = getpriority(PRIO_PROCESS,mPID);
    if (errno == 0) 
    {
        retval = OS_SUCCESS;
    }
    return retval;
}

int OsProcessLinux::getCurrentPID()
{
    return getpid();
}

/* ============================ INQUIRY =================================== */
UtlBoolean OsProcessLinux::isRunning() const
{
    UtlBoolean retval = FALSE;

    OsProcess rProcess;        
    if ( getByPID(mPID,rProcess) == OS_SUCCESS)
        retval = TRUE;

    return retval;   
}

/* //////////////////////////// PROTECTED ///////////////////////////////// */

/* //////////////////////////// PRIVATE /////////////////////////////////// */

void OsProcessLinux::cleanZombieProcess(int signal)
{
   while(waitpid(-1, NULL, WNOHANG) > 0);
}

/* ============================ FUNCTIONS ================================= */



