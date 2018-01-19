/***********************************************************************
Filename   : rvusrconfig.h
Description: let the user to put his own choices
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
#ifndef RV_USRCONFIG_H
#define RV_USRCONFIG_H


/* Validation checking options */
#undef  RV_CHECK_MASK
#define RV_CHECK_MASK RV_CHECK_ALL

/* Logging options */
#undef  RV_LOGMASK
#define RV_LOGMASK RV_LOGLEVEL_ALL

/* Log listener */
#undef  RV_LOGLISTENER_TYPE
#define RV_LOGLISTENER_TYPE RV_LOGLISTENER_FILE_AND_TERMINAL

/* Threadness mode: Single / Multi */
#undef  RV_THREADNESS_TYPE
#define RV_THREADNESS_TYPE RV_THREADNESS_MULTI

/* Networking support: None, IPv4, IPv6 */
#undef  RV_NET_TYPE
#define RV_NET_TYPE RV_NET_IPV4

/* Select method: Select, Poll, Devpoll, Win32 WSA */
#undef  RV_SELECT_TYPE
#define RV_SELECT_TYPE RV_SELECT_DEFAULT

/* DNS support: None, Ares */
#undef  RV_DNS_TYPE
#define RV_DNS_TYPE RV_DNS_ARES

/* TLS support: None, OpenSSL */
#undef  RV_TLS_TYPE
#define RV_TLS_TYPE RV_TLS_NONE

/* Does local host have a static list of addresses */
#undef RV_HOST_HAS_STATIC_ADDR 
#define RV_HOST_HAS_STATIC_ADDR RV_YES

/* Set the priority of the blocked commands for Nucleus (connect, close) 
   RV_THREAD_SOCKET_PRIORITY_DEFAULT by default is 3 */
/*
#undef RV_THREAD_SOCKET_PRIORITY_DEFAULT
#define RV_THREAD_SOCKET_PRIORITY_DEFAULT  (2) 
*/
/* Set the range of Nucleus default portRange (otherwise, default range is 5000-65535) */
/*#undef RV_PORTRANGE_DEFAULT_START
#define RV_PORTRANGE_DEFAULT_START 1000
#undef RV_PORTRANGE_DEFAULT_FINISH
#define RV_PORTRANGE_DEFAULT_FINISH 12275*/


/* To enable single threaded select preemption */
#undef RV_SINGLE_THREADED_PREEMPTION 
#define RV_SINGLE_THREADED_PREEMPTION RV_YES


/*-----------------------------------------------------*/
/*      SIP Stack deprecated definitions               */
/*-----------------------------------------------------*/
/*Do not delete the following type definitions. They are defined
  for backwards compatabilities and enable sip applications
  to use deprecated type definitions.*/

#if defined(RV_IPV6)
#undef  RV_CFLAG_IPV6
#define RV_CFLAG_IPV6
#endif  /* defined(RV_IPV6) */

#if defined(RV_TLS_ON)
#undef  RV_CFLAG_TLS
#define RV_CFLAG_TLS
#endif  /* defined(RV_TLS_ON) */

#if defined(RV_NOLOG)
#undef RV_CFLAG_NOLOG
#define RV_CFLAG_NOLOG
#endif  /* defined(RV_NOLOG) */

#if defined(RV_NOTHREADS)
#undef  RV_CFLAG_NOTHREADS
#define RV_CFLAG_NOTHREADS
#endif /* defined(RV_NOTHREADS) */


#endif /* RV_USRCONFIG_H */
