//
// Copyright (C) 2004-2006 SIPfoundry Inc.
// Licensed by SIPfoundry under the LGPL license.
//
// Copyright (C) 2004-2006 Pingtel Corp.  All rights reserved.
// Licensed to SIPfoundry under a Contributor Agreement.
//
// $$
///////////////////////////////////////////////////////////////////////////////


#ifndef _OsEvent_h_
#define _OsEvent_h_

// SYSTEM INCLUDES

// APPLICATION INCLUDES
#include "os/OsDefs.h"
#include "os/OsBSem.h"
#include "os/OsNotification.h"
#include "os/OsTime.h"
#include "os/OsMutex.h"

// DEFINES
// MACROS
// EXTERNAL FUNCTIONS
// EXTERNAL VARIABLES
// CONSTANTS
// STRUCTS
// TYPEDEFS
// FORWARD DECLARATIONS

/**
*  @brief Events are used to synchronize a task with an ISR or between two tasks.
*
*  Events consist of event data (an integer) that is set when the event is
*  signaled and a state variable that indicates whether the event has been
*  signaled. When first initialized, an OsEvent is ready to be signaled.
*  However, once signaled, the OsEvent must be explicitly reset before it
*  may be signaled again. An OsEvent is intended for use in synchronizing
*  one notifier (task or ISR) with one listener task. If an OsEvent object
*  is intended for use with more than one notifier or listener, then an
*  external mutex must be used to serialize access and avoid race 
*  conditions. 
*
*     <h3>Background</h3>
*  First, a little bit of terminology.  The task that wishes to be notified
*  when an event occurs is the "Listener" task. The task that signals when
*  a given event occurs is the "Notifier" task.  A Notifier informs the
*  Listener that a given event has occurred by sending an "Event
*  Notification". 
*
*     <h3>Expected Usage</h3>
*  The Listener passes an event object to the Notifier.  When the
*  corresponding event occurs, the Notifier uses the event object
*  to signal the occurrence of the event. The Listener may receive
*  event notifications by: polling, blocking until the event is
*  signaled, or blocking until either the event is signaled or a
*  timeout expires.  When the Listener receives the event
*  notification, it can then invoke the appropriate event handler.
*  This handler will run in the Listener's task context. 
*
*  @note Using a busy loop to poll for event status is considered
*  anti-social behavior.  However, when using the event object
*  approach, a task can perform a blocking wait for only one event
*  at a time.  A solution that allows a task to receive signals
*  for multiple events is a message queue (see OsQueuedEvent for more
*  information).
*/
class OsEvent : public OsNotification
{

/* //////////////////////////// PUBLIC //////////////////////////////////// */
public:

/* ============================ CREATORS ================================== */

     /// Constructor
   OsEvent(const intptr_t userData=0);

     /// Destructor
   virtual ~OsEvent();

/* ============================ MANIPULATORS ============================== */

     /// Set the event data and signal the occurrence of the event
   virtual OsStatus signal(const intptr_t eventData);
     /**<
     *  Return OS_ALREADY_SIGNALED if the event has already been signaled
     *  (and has not yet been cleared), otherwise return OS_SUCCESS.
     */

     /// Reset the event so that it may be signaled again
   virtual OsStatus reset(void);
     /**<
     *  Return OS_NOT_SIGNALED if the event has not been signaled (or has
     *  already been cleared), otherwise return OS_SUCCESS.
     */

     /// Wait for the event to be signaled
   virtual OsStatus wait(const OsTime& rTimeout=OsTime::OS_INFINITY);
     /**<
     *  Return OS_BUSY if the timeout expired, otherwise return OS_SUCCESS.
     */

     /// Sets the user data specified.  There are situations (such as the OsProtedtedEvent)
   virtual OsStatus setUserData(intptr_t userData);
     /**<
     *  when the user data can not be specified when this object was constructed
     *  so that this method is necessary to set the user data.
     *  Always returns OS_SUCCESS.
     */

/* ============================ ACCESSORS ================================= */

     /// Return the event data that was signaled by the notifier task.
   virtual OsStatus getEventData(intptr_t& rEventData);
     /**<
     *  Return OS_NOT_SIGNALED if the event has not been signaled (or has
     *  already been cleared), otherwise return OS_SUCCESS.
     */

     /// Return the user data specified when this object was constructed.
   virtual OsStatus getUserData(intptr_t& rUserData) const;
     /**<
     *  Always returns OS_SUCCESS.
     */

/* ============================ INQUIRY =================================== */

     /// Return TRUE if the event has been signaled, otherwise FALSE
   virtual UtlBoolean isSignaled(void);

/* //////////////////////////// PROTECTED ///////////////////////////////// */
protected:

/* //////////////////////////// PRIVATE /////////////////////////////////// */
private:

   intptr_t  mEventData;   ///< Data set when the event was signaled.
   UtlBoolean mIsSignaled; ///< Indicates whether the event has been signaled.
   OsBSem    mSignalSem;   ///< Semaphore used to queue up tasks waiting for
                           ///<  the event to be signaled.
   OsMutex   mMutex;       ///< Mutex to synchronize access to member variables,
                           ///< especially to mIsSignaled, which may cause
                           ///< deadlock when changed without synchronization.
   intptr_t  mUserData;    ///< Data specified on behalf of the user and
                           ///<  not otherwise used by this class -- the user
                           ///<  data is specified as an argument to the class
                           ///<  constructor.

     /// Copy constructor (not implemented for this class)
   OsEvent(const OsEvent& rOsEvent);

     /// Assignment operator (not implemented for this class)
   OsEvent& operator=(const OsEvent& rhs);

};

/* ============================ INLINE METHODS ============================ */

#endif  // _OsEvent_h_

