/***********************************************************************
Filename   : rvlinux.h
Description: config file for Linux
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
#ifndef RV_LINUX_H
#define RV_LINUX_H

#include <string.h>

#define RVAPI
#define RVINTAPI
#define RVCOREAPI
#define RVCALLCONV

/* rvtime: Select timestamp interface to use */
#define RV_TIMESTAMP_TYPE RV_TIMESTAMP_LINUX

/* rvtime: Select clock interface to use */
#define RV_CLOCK_TYPE RV_CLOCK_LINUX

/* rvtm: Select tm (calendar time) interface to use */
#define RV_TM_TYPE RV_TM_POSIX

/* TODO: kongqx */
/* rv64ascii: Select 64 bit conversions to use */
#define RV_64TOASCII_TYPE RV_64TOASCII_STANDARD

/* rvsemaphore: Select semaphore interface to use */
#define RV_SEMAPHORE_TYPE RV_SEMAPHORE_POSIX
//#define RV_SEMAPHORE_ATTRIBUTE_DEFAULT SEM_Q_PRIORITY /* options */
#define RV_SEMAPHORE_ATTRIBUTE_DEFAULT 0/* options */

/* rvmutex: Select mutex interface to use */
#define RV_MUTEX_TYPE RV_MUTEX_LINUX
//#define RV_MUTEX_ATTRIBUTE_DEFAULT (SEM_Q_PRIORITY | SEM_INVERSION_SAFE) /* options */
#define RV_MUTEX_ATTRIBUTE_DEFAULT 0 /* options */

/* rvthread: Select thread interface to use and set parameters */
#define RV_THREAD_TYPE RV_THREAD_POSIX
#define RV_THREAD_PRIORITY_DEFAULT 126
#define RV_THREAD_STACKSIZE_DEFAULT 20000
#define RV_THREAD_STACKSIZE_USEDEFAULT 0 /* No minimum stack size */
#define RV_THREAD_ATTRIBUTE_DEFAULT 0  /* options parameter to taskInit */

/* rvlock: Select lock interface to use */
#define RV_LOCK_TYPE RV_LOCK_LINUX
//#define RV_LOCK_ATTRIBUTE_DEFAULT SEM_Q_PRIORITY /* options */
#define RV_LOCK_ATTRIBUTE_DEFAULT 0/* options */

/* rvmemory: Select memory interface to use */
#define RV_MEMORY_TYPE RV_MEMORY_STANDARD

/* rvosmem: Select OS dynamic memory driver to use */
#define RV_OSMEM_TYPE RV_OSMEM_MALLOC

/* rvhost: Select network host interface to use */
#define RV_HOST_TYPE RV_HOST_POSIX

/* rvfdevent: File-descriptor events interface to use */
#define RV_SELECT_TYPE RV_SELECT_SELECT

/* rvsockets: Type of Sockets used in the system */
#define RV_SOCKET_TYPE RV_SOCKET_BSD

/* rvportrange: Type of Port-range used in the system */
#define RV_PORTRANGE_TYPE RV_PORTRANGE_FAST

/* rvloglistener: Type of log listeners used in the system */
#define RV_LOGLISTENER_TYPE RV_LOGLISTENER_TERMINAL

/* rvstdio: Select stdio interface to use */
#define RV_STDIO_TYPE RV_STDIO_ANSI

/* rvassert: Select stdio interface to use */
#define RV_ASSERT_TYPE RV_ASSERT_ANSI


#endif /* RV_RVWORKS_H */
