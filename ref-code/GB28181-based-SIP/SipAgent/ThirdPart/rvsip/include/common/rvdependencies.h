/***********************************************************************
Filename   : rvdependencies.h
Description: calculates dependencies between macro definition
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
#ifndef RV_DEPENDENCIES_H
#define RV_DEPENDENCIES_H


/* Log & Log listener */
#if (RV_LOGMASK == RV_LOGLEVEL_NONE)
#undef  RV_LOGLISTENER_TYPE
#define RV_LOGLISTENER_TYPE RV_LOGLISTENER_NONE
#endif


/* Handle Solaris 2.6 deficiencies */
#if (RV_OS_TYPE == RV_OS_TYPE_SOLARIS) && (RV_OS_VERSION == RV_OS_SOLARIS_2_6)
/* Lock interface */
#undef  RV_LOCK_TYPE
#define RV_LOCK_TYPE RV_LOCK_MANUAL
#undef  RV_LOCK_ATTRIBUTE_DEFAULT
#define RV_LOCK_ATTRIBUTE_DEFAULT 0 /* not used */
/* Mutex interface */
#undef  RV_MUTEX_TYPE
#define RV_MUTEX_TYPE RV_MUTEX_MANUAL
#undef  RV_MUTEX_ATTRIBUTE_DEFAULT
#define RV_MUTEX_ATTRIBUTE_DEFAULT 0 /* not used */
#endif


/* Threadness: Single / Multi */
#if (RV_THREADNESS_TYPE == RV_THREADNESS_SINGLE)
/* Seems like we don't want any thread support at all */

#if (RV_OS_TYPE == RV_OS_TYPE_NUCLEUS)
#error RV_THREADNESS_TYPE: illegal value
#endif

#undef  RV_LOCK_TYPE
#define RV_LOCK_TYPE RV_LOCK_NONE

#undef  RV_LOCK_ATTRIBUTE_DEFAULT
#define RV_LOCK_ATTRIBUTE_DEFAULT 0 /* not used */

#undef  RV_MUTEX_TYPE
#define RV_MUTEX_TYPE RV_MUTEX_NONE

#undef  RV_MUTEX_ATTRIBUTE_DEFAULT
#define RV_MUTEX_ATTRIBUTE_DEFAULT 0 /* not used */

#undef  RV_SEMAPHORE_TYPE
#define RV_SEMAPHORE_TYPE RV_SEMAPHORE_NONE

#undef  RV_SEMAPHORE_ATTRIBUTE_DEFAULT
#define RV_SEMAPHORE_ATTRIBUTE_DEFAULT 0 /* not used */

#undef  RV_THREAD_TYPE
#define RV_THREAD_TYPE RV_THREAD_NONE

#undef  RV_THREAD_PRIORITY_DEFAULT
#define RV_THREAD_PRIORITY_DEFAULT 0

#undef  RV_THREAD_STACKSIZE_DEFAULT
#define RV_THREAD_STACKSIZE_DEFAULT 0

#undef  RV_THREAD_STACKSIZE_USEDEFAULT
#define RV_THREAD_STACKSIZE_USEDEFAULT 0

#undef  RV_THREAD_ATTRIBUTE_DEFAULT
#define RV_THREAD_ATTRIBUTE_DEFAULT {0}

#else

/* Threadness = Multi */
#if (RV_OS_TYPE == RV_OS_TYPE_TRU64) || (RV_OS_TYPE == RV_OS_TYPE_UNIXWARE)
#error RV_THREADNESS_TYPE: illegal value
#endif

#if (RV_SOCKET_TYPE == RV_SOCKET_PSOS)
#undef  RV_SOCKET_USE_SHARER
#define RV_SOCKET_USE_SHARER RV_YES
#endif

#endif /* RV_THREADNESS_TYPE */


/* Networking: DNS, TLS, SCTP etc. */
#if (RV_NET_TYPE == RV_NET_NONE)
#undef  RV_DNS_TYPE
#define RV_DNS_TYPE RV_DNS_NONE
#undef  RV_TLS_TYPE
#define RV_TLS_TYPE RV_TLS_NONE

#elif (RV_NET_TYPE & RV_NET_SCTP)
#undef  RV_MEMORY_TYPE
#define RV_MEMORY_TYPE RV_MEMORY_POOL
#undef  RV_SECURITY
#define RV_SECURITY RV_YES
#endif /* (RV_NET_TYPE == RV_NET_NONE) */


/* Select */
#if (RV_SELECT_TYPE == RV_SELECT_DEFAULT)
#undef RV_SELECT_TYPE
#if (RV_OS_TYPE == RV_OS_TYPE_WIN32)
#define RV_SELECT_TYPE RV_SELECT_WIN32_WSA
#elif (RV_OS_TYPE == RV_OS_TYPE_SYMBIAN)
#define RV_SELECT_TYPE RV_SELECT_SYMBIAN
#else
#define RV_SELECT_TYPE RV_SELECT_SELECT
#endif
#endif

#if (RV_OS_TYPE == RV_OS_TYPE_SOLARIS) || (RV_OS_TYPE == RV_OS_TYPE_HPUX)
#if (RV_SELECT_TYPE != RV_SELECT_SELECT) && (RV_SELECT_TYPE != RV_SELECT_POLL) && \
    (RV_SELECT_TYPE != RV_SELECT_DEVPOLL)
#error RV_SELECT_TYPE: illegal value
#endif

#elif (RV_OS_TYPE == RV_OS_TYPE_LINUX) || (RV_OS_TYPE == RV_OS_TYPE_TRU64) || \
      (RV_OS_TYPE == RV_OS_TYPE_UNIXWARE)
#if (RV_SELECT_TYPE != RV_SELECT_SELECT) && (RV_SELECT_TYPE != RV_SELECT_POLL)
#error RV_SELECT_TYPE: illegal value
#endif

#elif (RV_OS_TYPE == RV_OS_TYPE_WIN32)
#if (RV_SELECT_TYPE != RV_SELECT_WIN32_WSA)
#error RV_SELECT_TYPE: illegal value
#endif

#elif (RV_OS_TYPE == RV_OS_TYPE_SYMBIAN)
#if (RV_SELECT_TYPE != RV_SELECT_SYMBIAN)
#error RV_SELECT_TYPE: illegal value
#endif

#else /* VxWorks, pSOS, OSE, Nucleus */
#if (RV_SELECT_TYPE != RV_SELECT_SELECT)
#error RV_SELECT_TYPE: illegal value
#endif

#endif /* RV_OS_TYPE == ... */

#if defined(RV_DEBUG) && defined(RV_RELEASE)
#error RV_DEBUG and RV_RELEASE cannot be both defined
#endif
#if !defined(RV_DEBUG) && !defined(RV_RELEASE)
#error RV_DEBUG or RV_RELEASE must be defined
#endif

#endif /* RV_DEPENDENCIES_H */
