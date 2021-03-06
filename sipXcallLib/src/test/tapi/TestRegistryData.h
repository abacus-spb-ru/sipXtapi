//
// Copyright (C) 2004-2006 SIPfoundry Inc.
// Licensed by SIPfoundry under the LGPL license.
//
// Copyright (C) 2004-2006 Pingtel Corp.  All rights reserved.
// Licensed to SIPfoundry under a Contributor Agreement.
//
// $$
///////////////////////////////////////////////////////////////////////////////


#ifndef _TestRegistryData_h_
#define _TestRegistryData_h_

// SYSTEM INCLUDES
// APPLICATION INCLUDES
#include "utl/UtlString.h"
// DEFINES
// MACROS
// EXTERNAL FUNCTIONS
// EXTERNAL VARIABLES
// CONSTANTS
// STRUCTS
// TYPEDEFS
// FORWARD DECLARATIONS

/**
 */
class TestRegistryData
{
/* //////////////////////////// PUBLIC //////////////////////////////////// */
  public:

/* ============================ CREATORS ================================== */

    /**
    * Default constructor
    */
    TestRegistryData();
        
    /**
    * Copy constructor
    */
    TestRegistryData(const TestRegistryData& rTestRegistryData);     

    /**
    * Destructor
    */
    virtual ~TestRegistryData();


    /* ============================ MANIPULATORS ============================== */

    /**
    * Assignment operator
    *
    * @param rhs right hand side of the equals operator
    */
    TestRegistryData& operator=(const TestRegistryData& rhs);  

    /* ============================ ACCESSORS ================================= */
    const UtlString getIdentity() const;
    const UtlString getRealm() const;
    const UtlString getContact() const;
    const UtlString getCallId() const;
    const int getExpires() const;
    const int getBornOnDate() const;

    void setIdentity(const UtlString identity);
    void setRealm(const UtlString realm);
    void setContact(const UtlString contact);
    void setCallId(const UtlString callId);
    void setExpires(const int expires);
    void setBornOnDate(const int bornOnDate);
    
/* ============================ INQUIRY =================================== */

/* //////////////////////////// PROTECTED ///////////////////////////////// */
  protected:
/* //////////////////////////// PRIVATE /////////////////////////////////// */
  private:
    UtlString mIdentity;
    UtlString mRealm;
    UtlString mContact;
    UtlString mCallId;
    int mExpires;
    int mBornOnDate;    
};

/* ============================ INLINE METHODS ============================ */

#endif  // _TestRegistryData_h_
