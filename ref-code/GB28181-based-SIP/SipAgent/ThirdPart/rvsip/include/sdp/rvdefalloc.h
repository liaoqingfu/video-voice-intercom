#if (0)
******************************************************************************
Filename:
Description: C/Macro-based allocator
******************************************************************************
                Copyright (c) 1999 RADVision Inc.
************************************************************************
NOTICE:
This document contains information that is proprietary to RADVision LTD.
No part of this publication may be reproduced in any form whatsoever
without written prior approval by RADVision LTD..

RADVision LTD. reserves the right to revise this publication and make
changes without obligation to notify any person of such revisions or
changes.
******************************************************************************
$Revision:$
$Date:$
$Author: S. Cipolli$
******************************************************************************
#endif

#ifndef RV_DEFALLOC_H
#define RV_DEFALLOC_H


#include "rvalloc.h"

#if defined(__cplusplus)
extern "C" {
#endif

/* Default allocator */
void* _alloc(void* p, RvSize_t s);
void _dealloc(void* p, RvSize_t s, void* x);
extern RvAlloc rvDefaultAlloc;

#if defined(__cplusplus)
}
#endif

#endif
