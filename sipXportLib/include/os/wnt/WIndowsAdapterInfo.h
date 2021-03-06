//
// Copyright (C) 2004-2006 SIPfoundry Inc.
// Licensed by SIPfoundry under the LGPL license.
//
// Copyright (C) 2004-2006 Pingtel Corp.  All rights reserved.
// Licensed to SIPfoundry under a Contributor Agreement.
//
// $$
///////////////////////////////////////////////////////////////////////////////


#ifndef _WINDOWSADAPTERINFO_H
#define _WINDOWSADAPTERINFO_H

#define MAX_ADAPTERS 20  //if you have more than 20 adapters, something is wrong with you. :)

#ifndef MAX_ADAPTER_NAME_LENGTH
   #define MAX_ADAPTER_NAME_LENGTH 256
#endif

typedef struct _AdapterInfo
{
        char AdapterName[MAX_ADAPTER_NAME_LENGTH + 4];  //long adapter name
        char IpAddress[40];                                                             //ip address of adapter
        BYTE MacAddress[MAX_ADAPTER_NAME_LENGTH];               //mac address of adapter
} AdapterInfoRec, *pAdapterInfoRec;

#ifdef WIN32


//FUNCTIONS

        //pass in amac address and get out the current ip address assigned to it
        extern int lookupIpAddressByMacAddress(char *mac_address, char *ipaddress);

        //initializes internal adapter structure
        extern int getAdaptersInfo();

        extern int getWindowsDomainName(char *domain_name);


#endif  //WIN32

#endif //_WINDOWSADAPTERINFO_H
