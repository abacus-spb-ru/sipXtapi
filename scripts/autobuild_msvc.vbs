option explicit

'determine if we're running in cscript mode, and bitch if not.
if UCase(Right(WScript.FullName, 11)) <> "CSCRIPT.EXE" then
   WScript.echo("Running autobuild in wscript mode unsupported." & vbCrLf _
         & "Please re-run using cscript")
   WScript.Quit(1)
end if

WScript.echo "Copyright (C) 2005-2008 SIPfoundry Inc."
WScript.echo "Licensed by SIPfoundry under the LGPL license."
WScript.echo ""
WScript.echo "Copyright (C) 2005-2008 SIPez LLC."
WScript.echo "Licensed to SIPfoundry under a Contributor Agreement."
WScript.echo ""
WScript.echo "Building sipX using MS Visual Studio"


' Put this class and it's primitive singleton-like initializer
' at the top of your script.
' This class makes sure that wsh/vbscript runtime errors are caught
' and returned as ERRORLEVEL when the script exits.  If you don't
' do this, runtime errors will still result in the caller of this
' script receiving 0 (success) error code.
Class QuitErrorlevelOnRuntimeError
   Private Sub Class_Terminate()
      ' When 'WScript.Quit' is called, it seems to set err.Number 
      ' to -2147155971.  Since we want the quit to return it's 
      ' error code, don't return err.number if this err.number is 
      ' seen
      dim quitErrNum : quitErrNum = -2147155971
      if Err.Number <> 0 and Err.Number <> quitErrNum then
        WScript.Quit Err.Number
      end if 
   End Sub
End Class
Dim qeloreObj : Set qeloreObj = New QuitErrorlevelOnRuntimeError



dim objShell, objFS, env, args, doClean, releaseType, libPrefix
dim cDir, vcVer

set objShell = CreateObject("WScript.Shell")
set objFS = CreateObject("Scripting.FileSystemObject")
set env = objShell.environment("process")
set args = WScript.Arguments
cDir = objShell.CurrentDirectory

doClean = ""
if args.Count > 0 then
   select case args.Item(0)
   case "clean"
      doClean="/CLEAN"
   case "check"
      dim unittest_errcode
      unittest_errcode = runUnittests()
      WScript.Quit(unittest_errcode)
   case else
      WScript.echo "Invalid arguments!"
      WScript.Quit(1)
   end select
end if

releaseType="Debug"
libPrefix="d"
WScript.echo "releaseType=" & releaseType
WScript.echo "libPrefix=" & libPrefix

Dim vc6vcvarspath, vc8vcvarspath

vc6vcvarspath = "C:\Program Files\Microsoft Visual Studio\VC98\Bin\vcvars32.bat"
vc8vcvarspath = "C:\Program Files\Microsoft Visual Studio 8\Common7\Tools\vsvars32.bat"

dim msdevpath
msdevpath = getFullExePath("msdev")
' Determine if msdev is in the path
if msdevpath = "" then
   WScript.echo "couldn't find msdev in default path"
   ' Check to see if the msvc6 compiler setup batch file exists (thus msvc6 is installed)
   if objFS.FileExists(vc6vcvarspath) then
      vcVer="6.0"
      WScript.echo "Found vc6 vcvars, calling it and pulling in it's env vars"
      ' Try to call vcvars.
      callBatchfile(vc6vcvarspath)


   ' Check to see if the msvc8/vs2005 compiler setup batch file exists (thus msvc8/vs2005 is installed)
   elseif objFS.FileExists(vc8vcvarspath) then
      vcVer="8.0"
      WScript.echo "Found vc8 vcvars, calling it and pulling in it's env vars"
      ' Try to call vcvars.
      callBatchfile(vc8vcvarspath)

   else
      ' Otherwise, exit without going any further -- we don't have 
      ' any known compiler to do compiling with.
      WScript.echo("Couldn't find a way to access the compiler!")
      WScript.Quit(2)
   end if
else
   WScript.echo "msdevpath = " & msdevpath
   vcVer="6.0"
end if


' For compile steps, if we're compiling using vc6, then 'msdev' is used for
' compiling, else if compiling with vc8, 'devenv' is used.

' For now we say vc8 isn't supported, since priority is on getting vc6 working.
' Only vc6 is currently supported.
if vcVer = "8.0" then
   WScript.stderr.writeline("Visual Studio 2005 is not currently supported")
   WScript.Quit(3)
elseif vcVer <> "6.0" then
   WScript.stderr.writeline("Only Visual Studio 6.0 is currently supported")
   WScript.Quit(3)
end if 

'WScript.echo("PATH = " & objShell.environment("process")("PATH")) ' Debug
'WScript.Quit(0) ' Debug

dim errCode, staticlibfile, exe
' Compile sipXportLib
if vcVer = "6.0" then
   staticlibfile = releaseType & "\sipXportLib" & libPrefix & ".lib"
   objShell.CurrentDirectory = cDir & "\sipXportLib"
   if objFS.FileExists(staticlibfile) then
      objFS.deleteFile(staticlibfile)
   end if
   errCode = runWithOutput("msdev sipXportLib.dsp /MAKE ""sipXportLib - Win32 " & releaseType & """" & doClean)

elseif vcVer = "8.0" then
'   dim compileMode
'   compileMode = "/build"
'   if doClean <> "" then
'      compileMode = "/rebuild"
'   end if 
'   ' Devenv.com needs to be specified specifically, so that output will
'   ' go to the console
'   errCode = runWithOutput("devenv.com sipX-msvc8.sln /Project ""sipXportLib-msvc8"" /ProjectConfig """ & releaseType & "|Win32"" " & compileMode)
end if
quitIfError(errCode)


' Compile sipXportLibTest
if vcVer = "6.0" then
   exe = releaseType & "\sipXportLibTest.exe"
   objShell.CurrentDirectory = cDir & "\sipXportLib"
   if objFS.FileExists(exe) then
      objFS.deleteFile(exe)
   end if
   errCode = runWithOutput("msdev sipXportLibTest.dsp /MAKE ""sipXportLibTest - Win32 " & releaseType & """" & doClean)
end if
quitIfError(errCode)


' Compile sipXsdpLib
if vcVer = "6.0" then
   staticlibfile = releaseType & "\sipXsdpLib" & libPrefix & ".lib"
   objShell.CurrentDirectory = cDir & "\sipXsdpLib"
   if objFS.FileExists(staticlibfile) then
      objFS.deleteFile(staticlibfile)
   end if
   errCode = runWithOutput("msdev sipXsdpLib.dsp /MAKE ""sipXsdpLib - Win32 " & releaseType & """" & doClean)
end if
quitIfError(errCode)


' Compile sipXtackLib
if vcVer = "6.0" then
   staticlibfile = releaseType & "\sipXtackLib" & libPrefix & ".lib"
   objShell.CurrentDirectory = cDir & "\sipXtackLib"
   if objFS.FileExists(staticlibfile) then
      objFS.deleteFile(staticlibfile)
   end if
   errCode = runWithOutput("msdev sipXtackLib.dsp /MAKE ""sipXtackLib - Win32 " & releaseType & """" & doClean)
end if
quitIfError(errCode)


' Compile sipXsdpLibTest
if vcVer = "6.0" then
   exe = releaseType & "\sipXsdpLibTest.exe"
   objShell.CurrentDirectory = cDir & "\sipXsdpLib"
   if objFS.FileExists(exe) then
      objFS.deleteFile(exe)
   end if
   errCode = runWithOutput("msdev sipXsdpLibTest.dsp /MAKE ""sipXsdpLibTest - Win32 " & releaseType & """" & doClean)
end if
quitIfError(errCode)


' Compile sipXtackLibTest
if vcVer = "6.0" then
   exe = releaseType & "\sipXtackLibTest.exe"
   objShell.CurrentDirectory = cDir & "\sipXtackLib"
   if objFS.FileExists(exe) then
      objFS.deleteFile(exe)
   end if
   errCode = runWithOutput("msdev sipXtackLibTest.dsp /MAKE ""sipXtackLibTest - Win32 " & releaseType & """" & doClean)
end if
quitIfError(errCode)


' Compile libspeex (for medialib)
if vcVer = "6.0" then 
   staticlibfile = "..\..\lib\libspeex.lib"
   objShell.CurrentDirectory = cDir & "\sipXmediaLib\contrib\libspeex\win32\libspeex"
   if objFS.FileExists(staticlibfile) then
      objFS.deleteFile(staticlibfile)
   end if
   errCode = runWithOutput("msdev libspeex.dsp /MAKE ""libspeex - Win32 " & releaseType & """" & doClean)
end if
quitIfError(errCode)


' Compile libgsm (for medialib)
if vcVer = "6.0" then
   staticlibfile = releaseType & "\gsm" & libPrefix & ".lib"
   objShell.CurrentDirectory = cDir & "\sipXmediaLib\contrib\libgsm"
   if objFS.FileExists(staticlibfile) then
      objFS.deleteFile(staticlibfile)
   end if
   errCode = runWithOutput("msdev libgsm.dsp /MAKE ""libgsm - Win32 " & releaseType & """" & doClean)
end if
quitIfError(errCode)


' Compile sipXmediaLib
if vcVer = "6.0" then
   staticlibfile = releaseType & "\sipXmediaLib" & libPrefix & ".lib"
   objShell.CurrentDirectory = cDir & "\sipXmediaLib"
   if objFS.FileExists(staticlibfile) then
      objFS.deleteFile(staticlibfile)
   end if
   errCode = runWithOutput("msdev sipXmediaLib.dsp /MAKE ""sipXmediaLib - Win32 " & releaseType & """" & doClean)
end if
quitIfError(errCode)


' Compile sipXmediaLibTest
if vcVer = "6.0" then
   exe = releaseType & "\sipXmediaLibTest.exe"
   objShell.CurrentDirectory = cDir & "\sipXmediaLib"
   if objFS.FileExists(exe) then
      objFS.deleteFile(exe)
   end if
   errCode = runWithOutput("msdev sipXmediaLibTest.dsp /MAKE ""sipXmediaLibTest - Win32 " & releaseType & """" & doClean)
end if
quitIfError(errCode)


' Compile sipXmediaAdapterLib
if vcVer = "6.0" then
   staticlibfile = releaseType & "\sipXmediaAdapterLib" & libPrefix & ".lib"
   objShell.CurrentDirectory = cDir & "\sipXmediaAdapterLib"
   if objFS.FileExists(staticlibfile) then
      objFS.deleteFile(staticlibfile)
   end if
   errCode = runWithOutput("msdev sipXmediaAdapterLib.dsp /MAKE ""sipXmediaAdapterLib - Win32 " & releaseType & """" & doClean)
end if
quitIfError(errCode)


' Compile sipXmediaAdapterLibTest
if vcVer = "6.0" then
   exe = releaseType & "\sipXmediaAdapterLibTest.exe"
   objShell.CurrentDirectory = cDir & "\sipXmediaAdapterLib"
   if objFS.FileExists(exe) then
      objFS.deleteFile(exe)
   end if
   errCode = runWithOutput("msdev sipXmediaAdapterLibTest.dsp /MAKE ""sipXmediaAdapterLibTest - Win32 " & releaseType & """" & doClean)
end if
quitIfError(errCode)


' Compile sipXcallLib
if vcVer = "6.0" then
   staticlibfile = releaseType & "\sipXcallLib" & libPrefix & ".lib"
   objShell.CurrentDirectory = cDir & "\sipXcallLib"
   if objFS.FileExists(staticlibfile) then
      objFS.deleteFile(staticlibfile)
   end if
   errCode = runWithOutput("msdev sipXcallLib.dsp /MAKE ""sipXcallLib - Win32 " & releaseType & """" & doClean)
end if
quitIfError(errCode)


' Compile sipXcallLibTest
if vcVer = "6.0" then
   exe = releaseType & "\sipXcallLibTest.exe"
   objShell.CurrentDirectory = cDir & "\sipXcallLib"
   if objFS.FileExists(exe) then
      objFS.deleteFile(exe)
   end if
   errCode = runWithOutput("msdev sipXcallLibTest.dsp /MAKE ""sipXcallLibTest - Win32 " & releaseType & """" & doClean)
end if
quitIfError(errCode)


' Compile sipXtapi
if vcVer = "6.0" then
   staticlibfile = releaseType & "\sipXtapi" & libPrefix & ".lib"
   objShell.CurrentDirectory = cDir & "\sipXcallLib\sipXtapi"
   if objFS.FileExists(staticlibfile) then
      objFS.deleteFile(staticlibfile)
   end if
   errCode = runWithOutput("msdev sipXtapi.dsp /MAKE ""sipXtapi - Win32 " & releaseType & """" & doClean)
end if
quitIfError(errCode)


' Compile sipXtapiTest
if vcVer = "6.0" then
   exe = releaseType & "\sipXtapiTest.exe"
   objShell.CurrentDirectory = cDir & "\sipXcallLib"
   if objFS.FileExists(exe) then
      objFS.deleteFile(exe)
   end if
   errCode = runWithOutput("msdev sipXtapiTest.dsp /MAKE ""sipXtapiTest - Win32 " & releaseType & """" & doClean)
end if
quitIfError(errCode)

'goto end
'
'cd sipXcallLib\examples\sipXezPhone 
'del Debug\sipXezPhone.exe
'msdev sipXezPhone.dsp /USEENV /MAKE "sipXezPhone - Win32 Debug" %doClean%
'@if %ERRORLEVEL% GTR 0 goto end
'cd ..\..\..
'
'cd sipXcommserverLib 
'del Debug\sipXcommserverLibd.lib
'msdev sipXcommserverLib.dsp /USEENV /MAKE "sipXcommserverLib - Win32 Debug" %doClean%
'@if %ERRORLEVEL% GTR 0 goto end
'cd ..
'
'cd sipXregistry 
'del Debug\sipXregistry.exe
'msdev sipXregistry.dsp /USEENV /MAKE "sipXregistry - Win32 Debug" %doClean%
'@if %ERRORLEVEL% GTR 0 goto end
'cd ..
'
'cd sipXproxy
'del Debug\sipXforkingProxy.exe
'msdev sipXforkingProxy.dsp /USEENV /MAKE "sipXforkingProxy - Win32 Debug" %doClean%
'@if %ERRORLEVEL% GTR 0 goto end
'cd ..
'
'cd sipXproxy
'del Debug\sipXauthproxy.exe
'msdev sipXauthproxy.dsp /USEENV /MAKE "sipXauthproxy - Win32 Debug" %doClean%
'@if %ERRORLEVEL% GTR 0 goto end
'cd ..
'
'goto end
'
':run_unittests
'REM Here we run the unit tests
'@echo off
'
'set NAME_PREFIX=test-test-
'if not "%1" == "" set NAME_PREFIX=%1
'echo logging in %NAME_PREFIX% files
'svn info | grep Revision
'
'sipXportLib\Debug\sipXportLibTest.exe 2> %NAME_PREFIX%port.err.txt > %NAME_PREFIX%port.txt
'set EL_STORE=%ERRORLEVEL%
'sed -e "/^\(OK (\|Run:\)/!d;s/^/sipXportLib - /" %NAME_PREFIX%port.txt
'set ERRORLEVEL=%EL_STORE%
'@if %ERRORLEVEL% GTR 0 goto end
'
'sipXtackLib\Debug\sipXtackLibTest.exe 2> %NAME_PREFIX%stack.err.txt > %NAME_PREFIX%stack.txt
'set EL_STORE=%ERRORLEVEL%
'sed -e "/^\(OK (\|Run:\)/!d;s/^/sipXtackLib - /" %NAME_PREFIX%stack.txt
'set ERRORLEVEL=%EL_STORE%
'@if %ERRORLEVEL% GTR 0 goto end
'
'sipXmediaLib\Debug\sipXmediaLibTest.exe 2> %NAME_PREFIX%media.err.txt > %NAME_PREFIX%media.txt
'set EL_STORE=%ERRORLEVEL%
'sed -e "/^\(OK (\|Run:\)/!d;s/^/sipXmediaLib - /" %NAME_PREFIX%media.txt
'set ERRORLEVEL=%EL_STORE%
'@if %ERRORLEVEL% GTR 0 goto end
'
'sipXmediaAdapterLib\Debug\sipXmediaAdapterLibTest.exe 2> %NAME_PREFIX%adapter.err.txt > %NAME_PREFIX%adapter.txt
'set EL_STORE=%ERRORLEVEL%
'sed -e "/^\(OK (\|Run:\)/!d;s/^/sipXmediaAdapterLib - /" %NAME_PREFIX%adapter.txt
'set ERRORLEVEL=%EL_STORE%
'@if %ERRORLEVEL% GTR 0 goto end
'
'sipXcallLib\Debug\sipXcallLibTest.exe 2> %NAME_PREFIX%call.err.txt > %NAME_PREFIX%call.txt
'set EL_STORE=%ERRORLEVEL%
'sed -e "/^\(OK (\|Run:\)/!d;s/^/sipXcallLib - /" %NAME_PREFIX%call.txt
'set ERRORLEVEL=%EL_STORE%
'@if %ERRORLEVEL% GTR 0 goto end
'
'sipXcallLib\Debug\sipXtapiTest.exe 2> %NAME_PREFIX%tapi.err.txt > %NAME_PREFIX%tapi.txt
'set EL_STORE=%ERRORLEVEL%
'sed -e "/^\(OK (\|Run:\)/!d;s/^/sipXtapi - /" %NAME_PREFIX%tapi.txt
'sed -e "/^\(OK (\|Run:\)/!d;s/^/sipXtapi - /" %NAME_PREFIX%tapi.err.txt
'set ERRORLEVEL=%EL_STORE%
'@if %ERRORLEVEL% GTR 0 goto end
'
':end

Function runUnittests()
   WScript.echo("Function runUnittests running")
   WScript.echo("Running unit tests is not implemented yet.")
End Function

Function callBatchfile(batchFile)
   ' Script pulled as a powershell script from:
   ' http://www.tavaresstudios.com/Blog/post/The-last-vsvars32ps1-Ill-ever-need.aspx
   ' Which got it from the book "Windows Powershell in Action" by Bruce Payette

   ' Ported code to wsh vbscript by Keith Kyzivat
   ' TODO: Still needs to be converted from powershell script to 
   ' WScript/vbscript.
   dim batchExec
   ' below doesn't work by itself, despite what the above referenced page
   ' says.  Try it yourself -- open shell window and type 
   '    cmd /c <path to batch> & set
   ' and see that it *doesn't* print the env vars set in the batch file :(
   ' set batchExec = objShell.Exec("%COMSPEC% /c " & batchFile & " & set")
   
   ' Create a new batch file to call the referenced batch file and then
   ' print out the env vars
   dim f, fStream
   f = "tmp" & int(rnd * 1000) & ".bat"
   set fStream = objFS.CreateTextFile(f, TRUE)
   fStream.writeline("call """ & batchFile & """ >nul")
   fStream.writeline("set")
   fStream.close()
   set fStream = Nothing
   

   set batchExec = objShell.Exec(f)
   ' Wait till the exec is finished
   do while batchExec.status = 0
      wscript.sleep 100
   loop

   ' Can delete the temporary batch file now.
   objFS.deleteFile(f)
   f=""

   dim line
   do while not batchExec.stdout.AtEndOfStream
      line = batchExec.stdout.readline
      if InStr(line, "=") > 0 then
         dim splitline
         splitline=Split(line, "=", 2)
         'WScript.echo("setting " & splitline(0) & "=" & splitline(1))
         env(splitline(0)) = splitline(1)
      end if 
   loop
   set batchExec = Nothing
End Function

Function getFullExePath(exe)
   dim f, fStream
   f = "which" & int(rnd * 1000) & ".bat"
   set fStream = objFS.CreateTextFile(f, FALSE)
   fStream.writeline("@set argonefullpath=%~$PATH:1")
   fStream.writeline("@if ""%argonefullpath%"" == """" goto end")
   fStream.writeline("@echo %argonefullpath%")
   fStream.writeline(":end")
   fStream.close()
   set fStream = Nothing

   dim batchExec
   set batchExec = objShell.exec(f & " " & exe)
   do while batchExec.status = 0
      wscript.sleep 100
   loop

   ' Can delete the temporary batch file now.
   objFS.deleteFile(f)
   f=""

   if not batchExec.stdout.AtEndOfStream then
      getFullExePath = batchExec.stdout.readline 
   end if 
   set batchExec = Nothing
End Function

Function runWithOutput(cmdline)
   dim cmdExec
   'WScript.echo("runWithOutput(" & cmdLine & ")") ' Debug
   ' Run the command and wait for it to finish
   set cmdExec = objShell.exec(cmdline)
   do while cmdExec.status = 0
      ' For each loop, empty out the stdout and stderr
      ' and print them out to the screen.

      ' Copy over it's stdout to this processes stdout
      do while not cmdExec.stdout.AtEndOfStream
         WScript.stdout.writeline(cmdExec.stdout.readline)
      loop
      ' Now copy over it's stderr to this processes stderr
      do while not cmdExec.stderr.AtEndOfStream
         WScript.stderr.writeline(cmdExec.stderr.readline)
      loop

      ' Sleep for 100ms
      wscript.sleep 100
   loop

   ' Now that it's done, do one last look at stderr and stdout
   ' and copy the data over to this processes stderr and stdout
   do while not cmdExec.stdout.AtEndOfStream
      WScript.stdout.writeline(cmdExec.stdout.readline)
   loop
   do while not cmdExec.stderr.AtEndOfStream
      WScript.stderr.writeline(cmdExec.stderr.readline)
   loop

   ' Return the error code/return code from the executed command.
   runWithOutput = cmdExec.ExitCode
   set cmdExec = Nothing
End Function

Function quitIfError(errCode)
   if errCode <> 0 then
      WScript.Quit(errCode)
   end if
End Function


' Reference material:
' http://www.robvanderwoude.com/vbstech.html
' http://www.microsoft.com/technet/scriptcenter/resources/tales/sg1002.mspx
' http://www.microsoft.com/technet/scriptcenter/guide/sas_wsh_ywsa.mspx?mfr=true
' http://www.microsoft.com/library/media/1033/technet/images/scriptcenter/guide/sas_wsh_60c_big.gif
' http://www.microsoft.com/technet/scriptcenter/resources/qanda/jun05/hey0620.mspx
' http://www.tavaresstudios.com/Blog/post/The-last-vsvars32ps1-Ill-ever-need.aspx

' vim:ts=3:sts=3:sw=3:expandtab:cindent:
