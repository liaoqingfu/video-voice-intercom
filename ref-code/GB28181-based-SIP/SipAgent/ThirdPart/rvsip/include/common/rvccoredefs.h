/***********************************************************************
Filename   : rvccoredefs.h
Description: ccore configuration definitions
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
#ifndef RV_CCOREDEFS_H
#define RV_CCOREDEFS_H

#include "rvinterfacesdefs.h"

/* Module codes (1..1023). One for each module in ccore. See rverror.h for details */
#define RV_CCORE_MODULE_CCORE 1
#define RV_CCORE_MODULE_TM 2
#define RV_CCORE_MODULE_CLOCK 3
#define RV_CCORE_MODULE_TIMESTAMP 4
#define RV_CCORE_MODULE_64ASCII 5
#define RV_CCORE_MODULE_SEMAPHORE 6
#define RV_CCORE_MODULE_MUTEX 7
#define RV_CCORE_MODULE_THREAD 8
#define RV_CCORE_MODULE_LOCK 9
#define RV_CCORE_MODULE_MEMORY 10
#define RV_CCORE_MODULE_OSMEM 11 /* MEMORY driver */
#define RV_CCORE_MODULE_POOLMEM 12 /* MEMORY driver */
#define RV_CCORE_MODULE_SELECT 13
#define RV_CCORE_MODULE_SOCKET 14
#define RV_CCORE_MODULE_PORTRANGE 15
#define RV_CCORE_MODULE_LOGLISTENER 16
#define RV_CCORE_MODULE_ADDRESS 17
#define RV_CCORE_MODULE_HOST 18
#define RV_CCORE_MODULE_STDIO 19
#define RV_CCORE_MODULE_LOG 20
#define RV_CCORE_MODULE_TLS 21
#define RV_CCORE_MODULE_DNS 22
#define RV_CCORE_MODULE_SYMNET 23


#endif /* RV_CCOREDEFS_H */
