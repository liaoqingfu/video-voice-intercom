/*
*********************************************************************************
*                                                                               *
* NOTICE:                                                                       *
* This document contains information that is confidential and proprietary to    *
* RADVision LTD.. No part of this publication may be reproduced in any form     *
* whatsoever without written prior approval by RADVision LTD..                  *
*                                                                               *
* RADVision LTD. reserves the right to revise this publication and make changes *
* without obligation to notify any person of such revisions or changes.         *
*********************************************************************************
*/


/*********************************************************************************
 *                              <RvSipTranportDNSTypes.h>
 *
 * The transport layer of the RADVISION SIP toolkit allows you to control sending
 * and receiving of messages over the network.
 * This file defines the DNS list handle and structures.
 *
 *    Author                         Date
 *    ------                        ------
 *    Shiri Margel                 May 2002
 *********************************************************************************/


#ifndef RVSIP_DNS_TRANSPORTTYPES_H
#define RVSIP_DNS_TRANSPORTTYPES_H

#ifdef __cplusplus
extern "C" {
#endif


/*-----------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                           */
/*-----------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RV_SIP_DEF.h"
#include "RvSipMsg.h"
#include "RvSipMsgTypes.h"
#include "RvSipCommonTypes.h"
#include "RvSipTransportTypes.h"

/*-----------------------------------------------------------------------*/
/*                          TYPE DEFINITIONS                             */
/*-----------------------------------------------------------------------*/

/* RvSipTransportDNSListHandle
 * ---------------------------
 * Deceleration of handle to a DNS list handle. The DNS list is used as an
 * interface between the sip stack toolkit DNS lists and the application. In
 * this list the stack holds SRV host and IP records.
 */
RV_DECLARE_HANDLE(RvSipTransportDNSListHandle);


/* RvSipTransportDNSSRVElement
 * --------------------------------------------------------------------------
 * RvSipTransportDNSSRVElement defines external API SRV name element, produced
 * by the NAPTR DNS query and used for SRV DNS query.
 *
 *    srvName         - SRV name for DNS SRV query
 *    protocol         - transport protocol that may be discovered by the NAPTR query
 *    order             - NAPTR order discovered by the NAPTR query
 *    preference         - NAPTR preference discovered by the NAPTR query
 */
typedef struct
{
    /* According to RFC1035 (DNS) DNS can return up to 255 characters string */
    RvChar          srvName[256];
    RvSipTransport  protocol;
    RvUint16        order;
    RvUint16        preference;
} RvSipTransportDNSSRVElement;


/* RvSipTransportDNSHostNameElement
 * --------------------------------------------------------------------------
 * RvSipTransportDNSHostNameElement defines the DNS host name list element, which keeps information
 * according to single host name that may be retrived by the SRV DNS query.
 *
 *    hostName    - the host name for DNS 'A/AAAA' query
 *    protocol    - transport protocol, discovered by the SRV query, defined explicitly or undefined
 *    port        - port , discovered by the SRV query, defined explicitly or undefined
 *    priority    - priority discovered by the SRV query
 *    weight        - weight discovered by the SRV query
 */
typedef struct
{
    /* According to RFC1035 (DNS) DNS can return up to 255 characters string */
    RvChar          hostName[256];
    RvSipTransport  protocol;
    RvUint16        port;
    RvUint16        priority;
    RvUint16        weight;
} RvSipTransportDNSHostNameElement;


/* RvSipTransportDNSIPElement
 * --------------------------------------------------------------------------
 * RvSipTransportDNSIPElement defines the DNS IP address list element, which keeps information
 * according to single IP address.
 *
 *    ip             - binary IP address - for internal use only
 *  ipAddress   - IP address as a string. (x.x.x.x for ipv4, a:a:a:a:a:a:a:a for ipv6)
 *    bIsIpV6        - true if IP address is IPv6 address
 *    protocol     - transport protocol, discovered by the NAPTR query or undefined
 *    port         - destination port that should be connected
 */
typedef struct
{
    RvUint8         ip[RVSIP_TRANSPORT_LEN_BYTES_IPV6];
    RvBool          bIsIpV6;
    RvSipTransport  protocol;
    RvUint16        port;
} RvSipTransportDNSIPElement;


#ifdef __cplusplus
}
#endif


#endif /* END OF: #ifndef RVSIP_DNS_TRANSPORTTYPES_H */



