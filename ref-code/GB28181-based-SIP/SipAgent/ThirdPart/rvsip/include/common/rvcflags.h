/***********************************************************************
Filename   : rvcflags.h
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
#ifndef RV_CFLAGS_H
#define RV_CFLAGS_H


/* Logging options */
#if defined(RV_CFLAG_NOLOG)
#undef  RV_LOGMASK
#define RV_LOGMASK RV_LOGLEVEL_NONE
#endif

/* Single threaded */
#if defined(RV_CFLAG_NOTHREADS)
#undef  RV_THREADNESS_TYPE
#define RV_THREADNESS_TYPE RV_THREADNESS_SINGLE
#endif

/* IPv6 support */
#if defined(RV_CFLAG_IPV6)
#undef  RV_NET_TYPE
#define RV_NET_TYPE RV_NET_IPV6
#endif

/* DNS support */
#if defined(RV_CFLAG_DNS)
#undef  RV_DNS_TYPE
#define RV_DNS_TYPE RV_DNS_ARES
#endif

/* TLS support */
#if defined(RV_CFLAG_TLS)
#undef  RV_TLS_TYPE
#define RV_TLS_TYPE RV_TLS_OPENSSL
#endif

/* Use of poll() */
#if defined(RV_CFLAG_POLL)
#undef  RV_SELECT_TYPE
#define RV_SELECT_TYPE RV_SELECT_POLL
#endif

/* Use of /dev/poll */
#if defined(RV_CFLAG_DEVPOLL)
#undef  RV_SELECT_TYPE
#define RV_SELECT_TYPE RV_SELECT_DEVPOLL
#endif


#endif /* RV_CFLAGS_H */
