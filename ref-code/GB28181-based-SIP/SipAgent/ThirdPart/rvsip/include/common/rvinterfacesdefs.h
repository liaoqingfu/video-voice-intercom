/***********************************************************************
Filename   : rvinterfacesdefs.h
Description: ccore interfaces definitions
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
#ifndef RV_INTERFACESDEFS_H
#define RV_INTERFACESDEFS_H

/* General definitions */
#define RV_NO 0
#define RV_YES 1

/* Validation checking options */
#define RV_CHECK_NULL  0x01
#define RV_CHECK_RANGE 0x02
#define RV_CHECK_OTHER 0x04
#define RV_CHECK_ALL   0xff
#define RV_CHECK_NONE  0x00

/* RV_THREADNESS_TYPE - Select threadness type: Single Multi */
#define RV_THREADNESS_SINGLE 0
#define RV_THREADNESS_MULTI 1

/* rvtimestamp: RV_TIMESTAMP_TYPE - Select time interface to use */
#define RV_TIMESTAMP_USER_DEFINED 0 /* Call external user functions */
#define RV_TIMESTAMP_LINUX 1
#define RV_TIMESTAMP_VXWORKS_NORMAL 2
#define RV_TIMESTAMP_VXWORKS_TIMESTAMP 3 /* Use VxWorks Timestamp driver */
#define RV_TIMESTAMP_PSOS 4
#define RV_TIMESTAMP_OSE 5
#define RV_TIMESTAMP_NUCLEUS 6
#define RV_TIMESTAMP_SOLARIS 7
#define RV_TIMESTAMP_WIN32 8
#define RV_TIMESTAMP_POSIX 9
#define RV_TIMESTAMP_UNIXWARE 10
#define RV_TIMESTAMP_EMBLINUX 11
#define RV_TIMESTAMP_SYMBIAN 12
#define RV_TIMESTAMP_MOPI 13

/* rvtime: RV_CLOCK_TYPE - Select clock interface to use */
#define RV_CLOCK_LINUX 0
#define RV_CLOCK_VXWORKS 1
#define RV_CLOCK_PSOS 2
#define RV_CLOCK_OSE 3
#define RV_CLOCK_NUCLEUS 4
#define RV_CLOCK_SOLARIS 5
#define RV_CLOCK_WIN32 6
#define RV_CLOCK_TRU64 7
#define RV_CLOCK_UNIXWARE 8
#define RV_CLOCK_SYMBIAN 9
#define RV_CLOCK_MOPI 10

/* rvtm: RV_TM_TYPE - Select tm (calendar time) interface to use */
#define RV_TM_POSIX 0
#define RV_TM_VXWORKS 1
#define RV_TM_PSOS 2
#define RV_TM_OSE 3
#define RV_TM_NUCLEUS 4
#define RV_TM_WIN32 5
#define RV_TM_WINCE 6
#define RV_TM_MOPI 7

/* rv64bits: RV_64BITS_TYPE - Select 64-bit arithmetic to use */
#define RV_64BITS_STANDARD 0
#define RV_64BITS_MANUAL 1

/* rv64ascii: RV_64TOASCII_TYPE - Select 64 bit conversions to use */
#define RV_64TOASCII_STANDARD 0 /* Standard GNU style 64 bit sprintf formatting */
#define RV_64TOASCII_WIN32 1
#define RV_64TOASCII_MANUAL 2   /* For systems where 64 bit sprintf doesn't work */

/* rvsemaphore: RV_SEMAPHORE_TYPE - Select semaphore interface to use */
#define RV_SEMAPHORE_POSIX 0
#define RV_SEMAPHORE_VXWORKS 1
#define RV_SEMAPHORE_PSOS 2
#define RV_SEMAPHORE_OSE 3
#define RV_SEMAPHORE_NUCLEUS 4
#define RV_SEMAPHORE_WIN32 5
#define RV_SEMAPHORE_SYMBIAN 6
#define RV_SEMAPHORE_NONE 7 /* No effect, single threaded environment only */

/* rvmutex: RV_MUTEX_TYPE - Select MUTEX interface to use */
#define RV_MUTEX_SOLARIS 0
#define RV_MUTEX_LINUX 1
#define RV_MUTEX_POSIX 1
#define RV_MUTEX_VXWORKS 2
#define RV_MUTEX_PSOS 3
#define RV_MUTEX_WIN32_MUTEX 4
#define RV_MUTEX_WIN32_CRITICAL 5 /* Use critical sections instead */
#define RV_MUTEX_MOPI 6
#define RV_MUTEX_MANUAL 7
#define RV_MUTEX_NONE 8 /* No locking, single threaded environment only */

/* rvthread: RV_THREAD_TYPE - Select thread interface to use */
#define RV_THREAD_SOLARIS 0
#define RV_THREAD_POSIX 1
#define RV_THREAD_VXWORKS 2
#define RV_THREAD_PSOS 3
#define RV_THREAD_OSE 4
#define RV_THREAD_NUCLEUS 5
#define RV_THREAD_WIN32 6
#define RV_THREAD_WINCE 7
#define RV_THREAD_UNIXWARE 8
#define RV_THREAD_SYMBIAN 9
#define RV_THREAD_MOPI 10
#define RV_THREAD_NONE 11 /* Work as single threaded only */

/* rvmutex: RV_LOCK_TYPE - Select Lock interface to use */
#define RV_LOCK_SOLARIS 0
#define RV_LOCK_LINUX 1
#define RV_LOCK_VXWORKS 2
#define RV_LOCK_PSOS 3
#define RV_LOCK_WIN32_MUTEX 4 /* use mutex even though they are recusive */
#define RV_LOCK_WIN32_CRITICAL 5 /* Use critical sections instead (recursive too) */
#define RV_LOCK_SYMBIAN 6
#define RV_LOCK_MOPI 7
#define RV_LOCK_MANUAL 8 /* Just use a semaphore */
#define RV_LOCK_NONE 9 /* No locking, single threaded environment only */

/* rvmemory: RV_MEMORY_TYPE - Select Memory interface to use */
#define RV_MEMORY_STANDARD 0 /* OS mem driver */
#define RV_MEMORY_POOL 1     /* Pool mem driver */

/* rvosmem: RV_OSMEM_TYPE - Select OS dynamic Memory interface to use */
#define RV_OSMEM_MALLOC 0
#define RV_OSMEM_OSE 1
#define RV_OSMEM_NUCLEUS 2
#define RV_OSMEM_PSOS 3
#define RV_OSMEM_VXWORKS 4
#define RV_OSMEM_SYMBIAN 5

/* networking: RV_NET_TYPE - Select type of IP networking (combination of the following) */
#define RV_NET_NONE 0x00
#define RV_NET_IPV4 0x01
#define RV_NET_IPV6 0x02
#define RV_NET_SCTP 0x04

/* rvhost: RV_HOST_TYPE - Select network host interface to use */
#define RV_HOST_BSD 0
#define RV_HOST_POSIX 1
#define RV_HOST_VXWORKS 2
#define RV_HOST_PSOS 3
#define RV_HOST_OSE 4
#define RV_HOST_NUCLEUS 5
#define RV_HOST_WIN32 6

/* rvdns: RV_DNS_TYPE - Select DNS interface to use */
#define RV_DNS_NONE 0
#define RV_DNS_WIN32 1
#define RV_DNS_BIND 2
#define RV_DNS_ARES 3

/* rvtls: RV_TLS_TYPE - Select TLS interface to use */
#define RV_TLS_NONE 0
#define RV_TLS_OPENSSL 1

/* rvfdevents: RV_SELECT_TYPE - Select file-descriptor events interface to use */
#define RV_SELECT_SELECT 0
#define RV_SELECT_POLL 1
#define RV_SELECT_DEVPOLL 2
#define RV_SELECT_WIN32_WSA 3
#define RV_SELECT_WIN32_COMPLETION 4 /* Don't use - This doesn't work */
#define RV_SELECT_SYMBIAN 5
#define RV_SELECT_DEFAULT -1

/* rvsockets: Type of Sockets used in the system */
#define RV_SOCKET_BSD           0
#define RV_SOCKET_WIN32_WSA     1
#define RV_SOCKET_PSOS          2
#define RV_SOCKET_NUCLEUS       3
#define RV_SOCKET_SYMBIAN       4

/* rvportrange: Type of Port-range used in the system */
#define RV_PORTRANGE_SLIM 0 /* "Quick and Dirty" port-range. Uses a single index */
#define RV_PORTRANGE_FAST 1 /* "Fast" port-range implementation, with a linked list on the range. */
                            /* This one takes 2 bytes per port in the range. */

#define RV_PORTRANGE_DEFAULT_START  5000	/* set a default range for nucleus portrange used */
#define RV_PORTRANGE_DEFAULT_FINISH 65535   /* in rvsocket.c */

/* rvlog: Severity of a LOG message
 * EXCEP    - Possible bug in the code
 * ERROR    - Cannot continue with current operation
 * WARNING  - Warning about a possible problem
 * INFO     - Debug information
 * DEBUG    - Detailed debug information
 * ENTER    - Entry to a function
 * LEAVE    - Exit from a function 
 * SYNC     - Synchronization objects log, 
 *            Synchronization objects are: mutexes, 
 *            semaphores and locks
 * ALL      - Enables all log severities
 * NONE     - Disables log
*/
#define RV_LOGLEVEL_EXCEP       0x01
#define RV_LOGLEVEL_ERROR       0x02
#define RV_LOGLEVEL_WARNING     0x04
#define RV_LOGLEVEL_INFO        0x08
#define RV_LOGLEVEL_DEBUG       0x10
#define RV_LOGLEVEL_ENTER       0x20
#define RV_LOGLEVEL_LEAVE       0x40
#define RV_LOGLEVEL_SYNC        0x80
#define RV_LOGLEVEL_ALL         0xff
#define RV_LOGLEVEL_NONE        0x00

/* rvloglistener: Type of Log listeners used in the system */
#define RV_LOGLISTENER_WIN32 0             /* Support for all internal listeners (file, terminal and debug) */
#define RV_LOGLISTENER_FILE_AND_TERMINAL 1 /* Support File and Terminal listeners */
#define RV_LOGLISTENER_TERMINAL 2          /* Support only terminal listener */
#define RV_LOGLISTENER_UDP 3               /* Support UDP listener */
#define RV_LOGLISTENER_NONE 4              /* Support none of the sample listeners */

/* rvstdio: RV_STDIO_TYPE - Select stdio interface to use */
#define RV_STDIO_ANSI 0        /* Use ANSI libraries */
#define RV_STDIO_STUB 1        /* Use stubbed out versions of functions */
#define RV_STDIO_OSE_DEBUG 2   /* Use ANSI libraries but use OSE dbgprintf instead of printf */
#define RV_STDIO_WINCE_DEBUG 3 /* Use ANSI libraries but use WINCE OutputDebugString instead of printf */

/* rvassert: RV_ASSERT_TYPE - Select assert interface to use */
#define RV_ASSERT_ANSI 0       /* Use ANSI libraries */
#define RV_ASSERT_WINCE 1      /* WINCE calls it's assert-macro differently */


#endif /* RV_INTERFACESDEFS_H */
