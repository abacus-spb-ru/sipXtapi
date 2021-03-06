//
// Copyright (C) 2004-2010 SIPfoundry Inc. All rights reserved.
// Licensed by SIPfoundry under the LGPL license.
//
// Copyright (C) 2004-2006 Pingtel Corp.  All rights reserved.
// Licensed to SIPfoundry under a Contributor Agreement.
//
// $$
///////////////////////////////////////////////////////////////////////////////

#include <sipxunittests.h>
#include "sipXtapiTest.h"
#include "EventValidator.h"
#include "EventRecorder.h"

extern SIPX_INST g_hInst;
extern EventRecorder g_recorder ;
extern EventRecorder g_lineRecorder; 
extern EventRecorder g_lineRecorder2; 

extern SIPX_INST g_hInst2;
extern EventRecorder g_recorder2 ;

extern SIPX_INST g_hInst3;
extern EventRecorder g_recorder3 ;

extern bool g_bCallbackCalled;

extern SIPX_CALL ghCallHangup;

SIPX_CALL g_hAutoAnswerCallbackCall ;
SIPX_CALL g_hAutoAnswerCallbackCallOther ;
SIPX_LINE g_hAutoAnswerCallbackLine ;
SIPX_CALL g_hAutoAnswerCallbackCall2 ;
SIPX_CALL g_hAutoAnswerCallbackCall2Other ;
SIPX_LINE g_hAutoAnswerCallbackLine2 ;
SIPX_CALL g_hAutoAnswerHangupCallbackCall ;
SIPX_LINE g_hAutoAnswerHangupCallbackLine ;
SIPX_CALL g_hAutoRejectCallbackCall ;
SIPX_LINE g_hAutoRejectCallbackLine ;
SIPX_CALL g_hAutoRedirectCallbackCall ;
SIPX_LINE g_hAutoRedirectCallbackLine ;

SIPX_CALL g_hAutoAnswerCallbackCallHolder ;
SIPX_CALL g_hAutoAnswerCallbackCallOtherHolder ;
SIPX_LINE g_hAutoAnswerCallbackLineHolder ;

SIPX_CALL g_hNewCallDetectorCall1 ;
SIPX_CALL g_hNewCallDetectorSourceCall1 ;
SIPX_CALL g_hNewCallDetectorCall2 ;
SIPX_CALL g_hNewCallDetectorSourceCall2 ;

bool SIPX_CALLING_CONVENTION FlibbleTransportCallback(SIPX_TRANSPORT hTransport,
                                      const char* szDestinationIp,
                                      const int   iDestPort,
                                      const char* szLocalIp,
                                      const int   iLocalPort,
                                      const void* pData,
                                      const size_t nData,
                                      const void* pUserData)
{
    bool bRet = true;
    return bRet;
}

bool SIPX_CALLING_CONVENTION UniversalEventValidatorCallback(SIPX_EVENT_CATEGORY category,
                                     void* pInfo,
                                     void* pUserData)
{
    EventValidator* pValidator = (EventValidator*) pUserData ;
    assert(pValidator) ;
    pValidator->addEvent(category, pInfo) ;
    

    // Uncomment for debugging purposes...
/*
    char cBuffer[1000]; 
    if (category == EVENT_CATEGORY_CALLSTATE) 
    {
        SIPX_CALLSTATE_INFO* pCallInfo = (SIPX_CALLSTATE_INFO*) pInfo ;

        printf("%s: [hCall=%2d, hAssocCall=%2d] %s\n", pValidator->getTitle(), pCallInfo->hCall, pCallInfo->hAssociatedCall,
            sipxEventToString(category, pInfo, cBuffer, 1000)) ;
    }
    else
    {        
        printf("%s: %s\n", pValidator->getTitle(), sipxEventToString(category, pInfo, cBuffer, 1000)) ;
    }
*/

    return true ;
}

void resetAutoAnswerCallback() 
{
    g_hAutoAnswerCallbackCall = 0 ;
    g_hAutoAnswerCallbackCallOther = 0 ;
}


bool SIPX_CALLING_CONVENTION AutoAnswerCallback(SIPX_EVENT_CATEGORY category, 
                                                void* pInfo, 
                                                void* pUserData)
{
    if (category == EVENT_CATEGORY_CALLSTATE)
    {
        SIPX_CALLSTATE_INFO* pCallInfo = (SIPX_CALLSTATE_INFO*) pInfo;

        if (g_hAutoAnswerCallbackCall == 0)
        {
            g_hAutoAnswerCallbackCall = pCallInfo->hCall;
        }
        else if (g_hAutoAnswerCallbackCall != pCallInfo->hCall)
        {
            g_hAutoAnswerCallbackCallOther = pCallInfo->hCall ;
        }
        g_hAutoAnswerCallbackLine = pCallInfo->hLine;
        
        
        // If we have user data verify the line url against it
        if (pUserData)
        {
            char szBuffer[500] ; 
            size_t nBuffer ;

            if (strlen((const char*) pUserData))
            {
                if (pCallInfo->hLine)  // hLine can be 0, and therefore, sipxLineGetURI should fail)
                {
                    CPPUNIT_ASSERT_EQUAL(sipxLineGetURI(pCallInfo->hLine, szBuffer, sizeof(szBuffer), nBuffer), SIPX_RESULT_SUCCESS) ;
                }
            }
        }

        switch(pCallInfo->event)
        {
            case CALLSTATE_OFFERING:
                sipxCallAccept(pCallInfo->hCall) ;
                break ;
            case CALLSTATE_ALERTING:
                {
                    int delay = rand() % 500 ;
                    OsTask::delay(delay) ;
                    sipxCallAnswer(pCallInfo->hCall) ;
                }
                break ;
            case CALLSTATE_DISCONNECTED:
                {
                    SIPX_CALL hDestroy = pCallInfo->hCall ;
                    sipxCallDestroy(hDestroy) ; 
                }
                break ;
            default:
                break ;
        }
    }     
    
    return true;
}

void resetAutoAnswerCallbackHolder() 
{
    g_hAutoAnswerCallbackCallHolder = 0 ;
    g_hAutoAnswerCallbackCallOtherHolder = 0 ;
}


bool SIPX_CALLING_CONVENTION AutoAnswerCallbackHolder(SIPX_EVENT_CATEGORY category, 
                                                        void* pInfo, 
                                                        void* pUserData)
{
    if (category == EVENT_CATEGORY_CALLSTATE)
    {
        SIPX_CALLSTATE_INFO* pCallInfo = (SIPX_CALLSTATE_INFO*) pInfo;

        if (g_hAutoAnswerCallbackCallHolder == 0)
        {
            g_hAutoAnswerCallbackCallHolder = pCallInfo->hCall;
        }
        else if (g_hAutoAnswerCallbackCallHolder != pCallInfo->hCall)
        {
            g_hAutoAnswerCallbackCallOtherHolder = pCallInfo->hCall ;
        }
        g_hAutoAnswerCallbackLineHolder = pCallInfo->hLine;
        
        
        // If we have user data verify the line url against it
        if (pUserData)
        {
            char szBuffer[500] ; 
            size_t nBuffer ;

            if (strlen((const char*) pUserData))
            {
                if (pCallInfo->hLine)  // hLine can be 0, and therefore, sipxLineGetURI should fail)
                {
                    CPPUNIT_ASSERT_EQUAL(sipxLineGetURI(pCallInfo->hLine, szBuffer, sizeof(szBuffer), nBuffer), SIPX_RESULT_SUCCESS) ;
                }
            }
        }

        switch(pCallInfo->event)
        {
            case CALLSTATE_OFFERING:
                sipxCallAccept(pCallInfo->hCall) ;
                break ;
            case CALLSTATE_ALERTING:
                {
                    // printf("%d Alerting\n", GetTickCount()) ;
                    int delay = rand() % 500 ;
                    OsTask::delay(delay) ;
                    // printf("%d Answering\n", GetTickCount()) ;
                    sipxCallAnswer(pCallInfo->hCall) ;                    
                    delay = rand() % 500 ;
                    OsTask::delay(delay) ;
                    // printf("%d Holding\n", GetTickCount()) ;
                    sipxCallHold(pCallInfo->hCall, true) ;                   
                }
                break ;
            case CALLSTATE_DISCONNECTED:
                {
                    // printf("%d Dropping\n", GetTickCount()) ;
                    SIPX_CALL hDestroy = pCallInfo->hCall ;
                    sipxCallDestroy(hDestroy) ; 
                }
                break ;
            default:
                break ;
        }
    }     
    
    return true;
}


SIPX_SECURITY_ATTRIBUTES* gpAcceptSecurity = NULL;
void setAutoAnswerSecurity(SIPX_SECURITY_ATTRIBUTES* pSecurity)
{
    gpAcceptSecurity = pSecurity;
}

bool AutoAnswerCallback_Secure(SIPX_EVENT_CATEGORY category, 
                        void* pInfo, 
                        void* pUserData)
{
    if (category == EVENT_CATEGORY_CALLSTATE)
    {
        SIPX_CALLSTATE_INFO* pCallInfo = (SIPX_CALLSTATE_INFO*) pInfo;

        if (g_hAutoAnswerCallbackCall == 0)
        {
            g_hAutoAnswerCallbackCall = pCallInfo->hCall;
        }
        else if (g_hAutoAnswerCallbackCall != pCallInfo->hCall)
        {
            g_hAutoAnswerCallbackCallOther = pCallInfo->hCall ;
        }
        g_hAutoAnswerCallbackLine = pCallInfo->hLine;
        
        
        // If we have user data verify the line url against it
        if (pUserData)
        {
            char szBuffer[500] ; 
            size_t nBuffer ;

            if (strlen((const char*) pUserData))
            {
                if (pCallInfo->hLine)  // hLine can be 0, and therefore, sipxLineGetURI should fail)
                {
                    CPPUNIT_ASSERT_EQUAL(sipxLineGetURI(pCallInfo->hLine, szBuffer, sizeof(szBuffer), nBuffer), SIPX_RESULT_SUCCESS) ;
                }
            }
        }

        switch(pCallInfo->event)
        {
            case CALLSTATE_OFFERING:
                sipxCallAccept(pCallInfo->hCall, NULL, gpAcceptSecurity) ;
                break ;
            case CALLSTATE_ALERTING:
                {
                    int delay = rand() % 40 ;
                    OsTask::delay(delay) ;
                    sipxCallAnswer(pCallInfo->hCall) ;
                }
                break ;
            case CALLSTATE_DISCONNECTED:
                {
                    SIPX_CALL hDestroy = pCallInfo->hCall ;
                    sipxCallDestroy(hDestroy) ; 
                }
                break ;
            default:
                break ;
        }
    }     
    
    return true;
}


void resetAutoAnswerCallback2() 
{
    g_hAutoAnswerCallbackCall2 = 0 ;
    g_hAutoAnswerCallbackCall2Other = 0 ;
}

bool SIPX_CALLING_CONVENTION AutoAnswerCallback2(SIPX_EVENT_CATEGORY category, 
                         void* pInfo, 
                         void* pUserData)
{

    if (category == EVENT_CATEGORY_CALLSTATE)
    {
        SIPX_CALLSTATE_INFO* pCallInfo = (SIPX_CALLSTATE_INFO*) pInfo;

        if (g_hAutoAnswerCallbackCall2 == 0)
        {
            g_hAutoAnswerCallbackCall2 = pCallInfo->hCall;
        }
        else if (g_hAutoAnswerCallbackCall2 != pCallInfo->hCall)
        {
            g_hAutoAnswerCallbackCall2Other = pCallInfo->hCall;
        }
        g_hAutoAnswerCallbackLine2 = pCallInfo->hLine;

                
        // If we have user data verify the line url against it
        if (pUserData)
        {
            char szBuffer[500] ; 
            size_t nBuffer ;

            if (strlen((const char*) pUserData))
            {
                if (pCallInfo->hLine)  // hLine can be 0, and therefore, sipxLineGetURI should fail)
                {
                    CPPUNIT_ASSERT_EQUAL(sipxLineGetURI(pCallInfo->hLine, szBuffer, sizeof(szBuffer), nBuffer), SIPX_RESULT_SUCCESS) ;
                }
            }
        }

        switch(pCallInfo->event)
        {
            case CALLSTATE_OFFERING:
                sipxCallAccept(pCallInfo->hCall) ;
                break ;
            case CALLSTATE_ALERTING:
                sipxCallAnswer(pCallInfo->hCall) ;
                break ;
            case CALLSTATE_DISCONNECTED:
                {
                    SIPX_CALL hDestroy = pCallInfo->hCall ;
                    sipxCallDestroy(hDestroy) ; 
                }
                break ;
            case CALLSTATE_DESTROYED:
                {
                    int i ;
                    i = 2; 
                }
                break ;
            default:
                break ;
        }
    }     
    
    return true;
}


bool SIPX_CALLING_CONVENTION AutoAnswerHangupCallback(SIPX_EVENT_CATEGORY category, 
                              void* pInfo, 
                              void* pUserData)
{
    if (category == EVENT_CATEGORY_CALLSTATE)
    {
        SIPX_CALLSTATE_INFO* pCallInfo = (SIPX_CALLSTATE_INFO*) pInfo;
        g_hAutoAnswerHangupCallbackCall = pCallInfo->hCall;
        g_hAutoAnswerHangupCallbackLine = pCallInfo->hLine;
        
        
        // If we have user data verify the line url against it
        if (pUserData)
        {
            char szBuffer[500] ; 
            size_t nBuffer ;

            if (strlen((const char*) pUserData))
            {
                if (g_hAutoAnswerHangupCallbackLine)  // hLine can be 0, and therefore, sipxLineGetURI should fail)
                {
                    CPPUNIT_ASSERT_EQUAL(sipxLineGetURI(g_hAutoAnswerHangupCallbackLine, szBuffer, sizeof(szBuffer), nBuffer), SIPX_RESULT_SUCCESS) ;
                }
            }
        }

        switch(pCallInfo->event)
        {
            case CALLSTATE_OFFERING:
                sipxCallAccept(g_hAutoAnswerHangupCallbackCall) ;
                break ;
            case CALLSTATE_ALERTING:
                {
                    sipxCallAnswer(g_hAutoAnswerHangupCallbackCall) ;
                    OsTask::delay(CALL_DELAY);
                    SIPX_CALL hDestroy = g_hAutoAnswerHangupCallbackCall ;
                    sipxCallDestroy(hDestroy) ;
                }
                break ;
            default:
                break ;
        }
    }     
    
    return true;
}


bool SIPX_CALLING_CONVENTION AutoAnswerHangupRingingCallback(SIPX_EVENT_CATEGORY category, 
                              void* pInfo, 
                              void* pUserData)
{
    if (category == EVENT_CATEGORY_CALLSTATE)
    {
        SIPX_CALLSTATE_INFO* pCallInfo = (SIPX_CALLSTATE_INFO*) pInfo;
        g_hAutoAnswerCallbackCall = pCallInfo->hCall;
        g_hAutoAnswerCallbackLine = pCallInfo->hLine;
        
        
        // If we have user data verify the line url against it
        if (pUserData)
        {
            char szBuffer[500] ; 
            size_t nBuffer ;

            if (strlen((const char*) pUserData))
            {
                if (g_hAutoAnswerCallbackLine)  // hLine can be 0, and therefore, sipxLineGetURI should fail)
                {
                    CPPUNIT_ASSERT_EQUAL(sipxLineGetURI(g_hAutoAnswerCallbackLine, szBuffer, sizeof(szBuffer), nBuffer), SIPX_RESULT_SUCCESS) ;
                }
            }
        }

        switch(pCallInfo->event)
        {
            case CALLSTATE_OFFERING:
                sipxCallAccept(g_hAutoAnswerCallbackCall) ;
                break ;
            case CALLSTATE_ALERTING:
                {
                    SIPX_CALL hDestroy = g_hAutoAnswerCallbackCall ;
                    sipxCallDestroy(hDestroy) ;
                }
                break ;
            default:
               break ;
        }
    }     
    
    return true;
}


bool SIPX_CALLING_CONVENTION AutoRejectCallback(SIPX_EVENT_CATEGORY category, 
                        void* pInfo, 
                        void* pUserData) 
{
    if (category == EVENT_CATEGORY_CALLSTATE)
    {
        SIPX_CALLSTATE_INFO* pCallInfo = (SIPX_CALLSTATE_INFO*) pInfo;
        g_hAutoRejectCallbackCall = pCallInfo->hCall;
        g_hAutoRejectCallbackLine = pCallInfo->hLine;
        
        
        // If we have user data verify the line url against it
        if (pUserData)
        {
            char szBuffer[500] ; 
            size_t nBuffer ;

            if (strlen((const char*) pUserData))
            {
                if (g_hAutoRejectCallbackLine)  // hLine can be 0, and therefore, sipxLineGetURI should fail)
                {
                    CPPUNIT_ASSERT_EQUAL(sipxLineGetURI(g_hAutoRejectCallbackLine, szBuffer, sizeof(szBuffer), nBuffer), SIPX_RESULT_SUCCESS) ;
                }
            }
        }

        switch(pCallInfo->event)
        {
            case CALLSTATE_OFFERING:
                sipxCallReject(g_hAutoRejectCallbackCall) ;
                break ;            
            case CALLSTATE_DISCONNECTED:
                {
                    SIPX_CALL hDestroy = g_hAutoRejectCallbackCall ;
                    sipxCallDestroy(hDestroy) ;
                }
                break ;
            default:
                break ;
        }
    }     
    
    return true;
}


bool SIPX_CALLING_CONVENTION AutoRedirectCallback(SIPX_EVENT_CATEGORY category, 
                          void* pInfo, 
                          void* pUserData) 
{
    if (category == EVENT_CATEGORY_CALLSTATE)
    {
        SIPX_CALLSTATE_INFO* pCallInfo = (SIPX_CALLSTATE_INFO*) pInfo;
        g_hAutoRedirectCallbackCall = pCallInfo->hCall;
        g_hAutoRedirectCallbackLine = pCallInfo->hLine;
        
        
        // If we have user data verify the line url against it
        if (pUserData)
        {
            char szBuffer[500] ; 
            size_t nBuffer ;

            if (strlen((const char*) pUserData))
            {
                if (g_hAutoRedirectCallbackLine)  // hLine can be 0, and therefore, sipxLineGetURI should fail)
                {
                    CPPUNIT_ASSERT_EQUAL(sipxLineGetURI(g_hAutoRedirectCallbackLine, szBuffer, sizeof(szBuffer), nBuffer), SIPX_RESULT_SUCCESS) ;
                }
            }
        }

        switch(pCallInfo->event)
        {
            case CALLSTATE_OFFERING:
                sipxCallRedirect(g_hAutoRedirectCallbackCall, "sip:foo@127.0.0.1:10000");				                
                break ;            
            case CALLSTATE_DISCONNECTED:
                {
                    SIPX_CALL hDestroy = g_hAutoRedirectCallbackCall ;
                    sipxCallDestroy(hDestroy) ;
                }
                break ;
            default:
                break ;
        }
    }     
    
    return true;
}


bool SIPX_CALLING_CONVENTION basicCall_CallBack_Place(SIPX_EVENT_CATEGORY category,
                              void* pInfo,
                              void* pUserData)
{
    if (category == EVENT_CATEGORY_CALLSTATE)
    {
        SIPX_CALLSTATE_INFO* pCallInfo = (SIPX_CALLSTATE_INFO*)pInfo;
        g_recorder.addEvent(pCallInfo->hLine, pCallInfo->event, pCallInfo->cause) ;
    }
    return true;
}


bool SIPX_CALLING_CONVENTION basicCall_CallBack_Receive(SIPX_EVENT_CATEGORY category, 
                                         void* pInfo, 
                                         void* pUserData)
{
     
    if (category == EVENT_CATEGORY_CALLSTATE)
    {
        SIPX_CALLSTATE_INFO* pCallInfo = (SIPX_CALLSTATE_INFO*)pInfo;
        SIPX_LINE hLine = pCallInfo->hLine;
        SIPX_CALL hCall = pCallInfo->hCall;
        
        g_recorder2.addEvent(hLine, pCallInfo->event, pCallInfo->cause) ;

        // If we have user data verify the line url against it
        if (pUserData)
        {
            char szBuffer[500] ; 
            size_t nBuffer ;

            if (strlen((const char*) pUserData))
            {
                if (hLine)  // hLine can be 0, and therefore, sipxLineGetURI should fail)
                {
                    CPPUNIT_ASSERT_EQUAL(sipxLineGetURI(hLine, szBuffer, sizeof(szBuffer), nBuffer), SIPX_RESULT_SUCCESS) ;

                    // an event can come in with what appears to be the "wrong" user data.
                    // for instance, if a listener is removed and a new listener is added immediately with new user data.
                    // printf("comparing %s to %s\n", pUserData, szBuffer) ;
                    //CPPUNIT_ASSERT(strcmp((char*) pUserData, szBuffer) == 0) ;
                }
            }
            //else
            //{
                //CPPUNIT_ASSERT_EQUAL(sipxLineGetURI(hLine, szBuffer, sizeof(szBuffer), nBuffer), SIPX_RESULT_FAILURE) ;
            //}
        }

        switch(pCallInfo->event)
        {
            case CALLSTATE_OFFERING:
                sipxCallAccept(hCall) ;
                break ;
            case CALLSTATE_ALERTING:
                sipxCallAnswer(hCall) ;
                break ;
            case CALLSTATE_DISCONNECTED:
                sipxCallDestroy(hCall) ; 
                break ;
            default:
                break ;
        }
    }     
    
    return true;
}


bool SIPX_CALLING_CONVENTION basicCall_CallBack_Receive3(SIPX_EVENT_CATEGORY category,
                              void* pInfo,
                              void* pUserData)
{ 
    if (category == EVENT_CATEGORY_CALLSTATE)
    {
        SIPX_CALLSTATE_INFO* pCallInfo = (SIPX_CALLSTATE_INFO*) pInfo;
        SIPX_LINE hLine = pCallInfo->hLine;
        SIPX_CALL hCall = pCallInfo->hCall;
        g_recorder3.addEvent(hLine, pCallInfo->event, pCallInfo->cause) ;

        // If we have user data verify the line url against it
        if (pUserData)
        {
            char szBuffer[500] ; 
            size_t nBuffer ;

            if (strlen((const char*) pUserData))
            {
                CPPUNIT_ASSERT_EQUAL(sipxLineGetURI(hLine, szBuffer, sizeof(szBuffer), nBuffer), SIPX_RESULT_SUCCESS) ;

                // printf("comparing %s to %s\n", pUserData, szBuffer) ;
                CPPUNIT_ASSERT(strcmp((char*) pUserData, szBuffer) == 0) ;
            }
            else
            {
                CPPUNIT_ASSERT_EQUAL(sipxLineGetURI(hLine, szBuffer, sizeof(szBuffer), nBuffer), SIPX_RESULT_FAILURE) ;
            }
        }

        switch(pCallInfo->event)
        {
            case CALLSTATE_OFFERING:
                sipxCallAccept(hCall) ;
                break ;
            case CALLSTATE_ALERTING:
                sipxCallAnswer(hCall) ;
                break ;
            case CALLSTATE_DISCONNECTED:
                sipxCallDestroy(hCall) ; 
                break ;
            default:
                break ;
        }
    }
    return true;
}



bool SIPX_CALLING_CONVENTION basicCall_CallBack_Receive3_hangup(SIPX_EVENT_CATEGORY category,
                              void* pInfo,
                              void* pUserData)
{ 
    if (category == EVENT_CATEGORY_CALLSTATE)
    {
        SIPX_CALLSTATE_INFO* pCallInfo = (SIPX_CALLSTATE_INFO*) pInfo;
        SIPX_LINE hLine = pCallInfo->hLine;
        SIPX_CALL hCall = pCallInfo->hCall;
        g_recorder3.addEvent(hLine, pCallInfo->event, pCallInfo->cause) ;

        // If we have user data verify the line url against it
        if (pUserData)
        {
            char szBuffer[500] ; 
            size_t nBuffer ;

            if (strlen((const char*) pUserData))
            {
                CPPUNIT_ASSERT_EQUAL(sipxLineGetURI(hLine, szBuffer, sizeof(szBuffer), nBuffer), SIPX_RESULT_SUCCESS) ;

                // printf("comparing %s to %s\n", pUserData, szBuffer) ;
                CPPUNIT_ASSERT(strcmp((char*) pUserData, szBuffer) == 0) ;
            }
            else
            {
                CPPUNIT_ASSERT_EQUAL(sipxLineGetURI(hLine, szBuffer, sizeof(szBuffer), nBuffer), SIPX_RESULT_FAILURE) ;
            }
        }

        switch(pCallInfo->event)
        {
            case CALLSTATE_OFFERING:
                sipxCallAccept(hCall) ;
                break ;
            case CALLSTATE_ALERTING:
                sipxCallAnswer(hCall) ;
                break ;
            case CALLSTATE_CONNECTED:
                ghCallHangup = hCall;
                break ;
            case CALLSTATE_DISCONNECTED:            
                break ;
            default:
                break ;
        }
    }
    return true;
}


bool SIPX_CALLING_CONVENTION basicCall_CallBack_Receive3_busy(SIPX_EVENT_CATEGORY category,
                              void* pInfo,
                              void* pUserData)
{ 
    if (category == EVENT_CATEGORY_CALLSTATE)
    {
        SIPX_CALLSTATE_INFO* pCallInfo = (SIPX_CALLSTATE_INFO*) pInfo;
        SIPX_LINE hLine = pCallInfo->hLine;
        SIPX_CALL hCall = pCallInfo->hCall;
        g_recorder3.addEvent(hLine, pCallInfo->event, pCallInfo->cause) ;

        // If we have user data verify the line url against it
        if (pUserData)
        {
            char szBuffer[500] ; 
            size_t nBuffer ;

            if (strlen((const char*) pUserData))
            {
                CPPUNIT_ASSERT_EQUAL(sipxLineGetURI(hLine, szBuffer, sizeof(szBuffer), nBuffer), SIPX_RESULT_SUCCESS) ;

                // printf("comparing %s to %s\n", pUserData, szBuffer) ;
                CPPUNIT_ASSERT(strcmp((char*) pUserData, szBuffer) == 0) ;
            }
            else
            {
                CPPUNIT_ASSERT_EQUAL(sipxLineGetURI(hLine, szBuffer, sizeof(szBuffer), nBuffer), SIPX_RESULT_FAILURE) ;
            }
        }

        switch(pCallInfo->event)
        {
            case CALLSTATE_OFFERING:
                sipxCallReject(hCall) ;
                sipxCallDestroy(hCall) ;
                break ;
            default:
                break ;
        }
    }
    return true;
}

bool basicCall_CallBack_Receive_Hangup(SIPX_EVENT_CATEGORY category,
                              void* pInfo,
                              void* pUserData)
{ 
    if (category == EVENT_CATEGORY_CALLSTATE)
    {
        SIPX_CALLSTATE_INFO* pCallInfo = (SIPX_CALLSTATE_INFO*) pInfo;
        SIPX_LINE hLine = pCallInfo->hLine;
        SIPX_CALL hCall = pCallInfo->hCall;
        g_recorder2.addEvent(hLine, pCallInfo->event, pCallInfo->cause) ;
        
        switch(pCallInfo->event)
        {
            case CALLSTATE_OFFERING:
                sipxCallAccept(hCall) ;
                break ;
            case CALLSTATE_ALERTING:
                sipxCallAnswer(hCall) ;
                OsTask::delay(CALL_DELAY);
                sipxCallDestroy(hCall) ;
                break ;
            case CALLSTATE_DISCONNECTED:
                break ;
            default:
                break ;
        }
    }
    return true;
}

bool basicCall_CallBack_Receive_Reject(SIPX_EVENT_CATEGORY category,
                              void* pInfo,
                              void* pUserData)
{ 
    if (category == EVENT_CATEGORY_CALLSTATE)
    {
        SIPX_CALLSTATE_INFO* pCallInfo = (SIPX_CALLSTATE_INFO*) pInfo;
        SIPX_LINE hLine = pCallInfo->hLine;
        SIPX_CALL hCall = pCallInfo->hCall;
        g_recorder2.addEvent(hLine, pCallInfo->event, pCallInfo->cause) ;
        

        switch(pCallInfo->event)
        {
            case CALLSTATE_OFFERING:
                sipxCallReject(hCall) ;
                sipxCallDestroy(hCall) ;
                break ;
            case CALLSTATE_ALERTING:
                break ;
            case CALLSTATE_DISCONNECTED:            
                break ;
            default:
                break ;
        }
    }
    return true;
}


bool basicCall_CallBack_Redirect(SIPX_EVENT_CATEGORY category,
                              void* pInfo,
                              void* pUserData)
{ 
    if (category == EVENT_CATEGORY_CALLSTATE)
    {
        SIPX_CALLSTATE_INFO* pCallInfo = (SIPX_CALLSTATE_INFO*) pInfo;
        SIPX_CALL hCall = pCallInfo->hCall;

        switch(pCallInfo->event)
        {
            case CALLSTATE_OFFERING:
                sipxCallRedirect(hCall, "sip:foo@127.0.0.1:10000");
				sipxCallDestroy(hCall);
                break ;
            case CALLSTATE_ALERTING:
                break ;
            case CALLSTATE_DISCONNECTED:            
                break ;
            default:
                break ;
        }
    }
    return true;
}


bool SIPX_CALLING_CONVENTION NewCallDetector1(SIPX_EVENT_CATEGORY category, 
                                              void* pInfo, 
                                              void* pUserData)
{
    if (category == EVENT_CATEGORY_CALLSTATE)
    {
        SIPX_CALLSTATE_INFO* pCallInfo = (SIPX_CALLSTATE_INFO*) pInfo;

        if (pCallInfo->event == CALLSTATE_NEWCALL)
        {
            g_hNewCallDetectorCall1 = pCallInfo->hCall ;
            g_hNewCallDetectorSourceCall1 = pCallInfo->hAssociatedCall ;
        }
    }
    
    return true;
}


bool SIPX_CALLING_CONVENTION NewCallDetector2(SIPX_EVENT_CATEGORY category, 
                                              void* pInfo, 
                                              void* pUserData)
{
    if (category == EVENT_CATEGORY_CALLSTATE)
    {
        SIPX_CALLSTATE_INFO* pCallInfo = (SIPX_CALLSTATE_INFO*) pInfo;

        if (pCallInfo->event == CALLSTATE_NEWCALL)
        {
            g_hNewCallDetectorCall2 = pCallInfo->hCall ;
            g_hNewCallDetectorSourceCall2 = pCallInfo->hAssociatedCall ;
        }
    }
    
    return true;
}
