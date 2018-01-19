/***********************************************************************
Filename   : rvccoreconfig.h
Description: ccore configuration
************************************************************************
        Copyright (c) 2001 RADVISION Inc. and RADVISION Ltd.
************************************************************************
NOTICE:
This document contains information that is confidential and proprietary
to RADVISION Inc. and RADVISION Ltd.. No part of this document may be
reproduced in any form whatsoever without written prior approval by
RADVISION Inc. or RADVISION Ltd..

RADVISION Inc. and RADVISION Ltd. reserve the right to revise this
publication and make changes without obligation to notify any person of
such revisions or changes.
***********************************************************************/
#ifndef RV_CCORECONFIG_H
#define RV_CCORECONFIG_H

/* Include configuration definitions. Look at this file for possible settings */
#include "rvccoredefs.h"

/* For OS specific configuration, please look at config/os/rv<os>.h */

/* Configuration settings that effect all OS's */

#define RV_CHECK_MASK RV_CHECK_ALL      /* Validation checking options */

#define RV_LOGMASK RV_LOGLEVEL_ALL      /* Compile time mask for logging */

#define RV_THREADNESS_TYPE RV_THREADNESS_MULTI  /* Threadness type: Single / Multi */

#define RV_THREAD_MAX_NAMESIZE 32       /* Maximum size of thread name to store (minimum 1) */
#define RV_THREAD_MAX_VARS 32           /* Maximum number of thread specific variables (minimum 1) */
#define RV_THREAD_MAX_VARNAMESIZE 32    /* Maximum size of variable name to store (minimum 1) */
#define RV_MEMORY_MAX_NAMESIZE 32       /* Maximum size of region name to store (minimum 1) */

#if defined(RV_DEBUG)
#define RV_MEMORY_KEEPSTATS RV_YES      /* Should memory regions maintain stats */
#define RV_MEMORY_DEBUGCHECK RV_YES     /* Do boundry and other memory checks */
#define RV_MEMORY_DEBUGINFO RV_YES      /* Include addition debug info with each alloc */
#define RV_ASSERT_ENABLE RV_YES         /* Enable assertions */
#else
#define RV_MEMORY_KEEPSTATS RV_YES      /* Should memory regions maintain stats */
#define RV_MEMORY_DEBUGCHECK RV_NO      /* Do boundry and other memory checks */
#define RV_MEMORY_DEBUGINFO RV_NO       /* Include addition debug info with each alloc */
#define RV_ASSERT_ENABLE RV_NO          /* Enable assertions */
#endif

#define RV_HOST_MAX_NAMESIZE 255        /* Maximum size of host name to store (minimum 1) */
#define RV_HOST_MAX_ADDRS 10            /* Maximum number of host network addresses (minimum 1) */
#define RV_HOST_HAS_STATIC_ADDR RV_NO   /* Does local host have a static list of addresses */

#define RV_NET_TYPE RV_NET_IPV4         /* Type of IP networking: None, IPv4, IPv6 */

#define RV_SOCKET_USE_SHARER RV_NO      /* Does the sockets go through a sharer */
                                        /* The socket sharer should be used for pSOS in
                                           multi-threaded applications */
#define RV_DNS_TYPE RV_DNS_NONE         /* DNS support */

#define RV_TLS_TYPE RV_TLS_NONE         /* TLS support */

#define RV_NTPTIME_TYPE RV_YES          /* NTP time support */

#define RV_64BITS_TYPE RV_64BITS_STANDARD /* 64-bit arithmetic: Manual or standard */

#define RV_SECURITY RV_NO                /* Security feature (used by SCTP and RTP) */

/* Select engine preemption is usually used in multithreading scenarios
 *  to interrupt RvSelectWaitAndBlock call. As a side effect user defined
 *  callback is called. In single-threaded scenarios the main effect (interrupt
 *  of RvSelectWaitAndBlock) is meaningless, so this mechanism is disabled by default.
 *  On the other hand, some application may find usefull the above mentioned 
 *  side effect. To enable preemption in single-threaded scenarios also - set
 *  'RV_SINGLE_THREADED_PREEMPTION' to RV_YES
 */
#define RV_SINGLE_THREADED_PREEMPTION  RV_NO 

#endif /* RV_CCORECONFIG_H */
