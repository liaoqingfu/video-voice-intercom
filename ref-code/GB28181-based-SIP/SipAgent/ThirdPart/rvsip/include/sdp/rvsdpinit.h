/******************************************************************************
Filename    :rvsdpinit.h
Description :init the sdp library.

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
$Revision:1.0$
$Date:08/01/00$
$Author:Michal Mashiach$
******************************************************************************/

#ifndef RV_SDPINIT_H
#define RV_SDPINIT_H

#if defined(__cplusplus)
extern "C" {
#endif

#include "rpool_API.h"
#include "rvsdp.h"


/***************************************************************************
 * RvSdpRPoolAlloc
 * ------------------------------------------------------------------------
 * General: This function is used from the sdp library to allocated.
 *          It is been stored in the allocator of every sdp object.
 *          The function "rvAllocAllocate" will operate it when we will need
 *          new space.
 * Return Value: NULL - if there is not enough space.
 *               Pointer to the allocated space.
 * ------------------------------------------------------------------------
 * Arguments:
 *  rpoolPtr    - RPOOL_Ptr structure which holds the pool, page and offset.
 *  SizeToAlloc - The size that need to be allocate.
 ***************************************************************************/
void *RvSdpRPoolAlloc(IN void   *rpoolPtr,IN RvSize_t SizeToAlloc);

/***************************************************************************
 * RvSdpRPoolDealloc
 * ------------------------------------------------------------------------
 * General: This function is used from the sdp library to deallocated.
 *          It is been stored in the allocator of every sdp object.
 *          The function "rvAllocDeallocate" will operate it when we will need
 *          to free space.
 *          The function acturally doesn't do anythings because rpool frees
 *          the memory just when a page is freed.
 * Return Value: void
 * ------------------------------------------------------------------------
 * Arguments:
 *  rpoolPtr      - RPOOL_Ptr structure which holds the pool, page and offset.
 *  SizeToDealloc - The size that need to be deallocate.
 *  NullPtr       - null pointer.
 ***************************************************************************/
void RvSdpRPoolDealloc (void * rpoolPtr, RvSize_t SizeToDealloc, void* NullPtr);


/***************************************************************************
 * RvSdpAllocConstruct
 * ------------------------------------------------------------------------
 * General: Construct sdp allocator.
 *          Sdp allocator is used when ever we will need space using RPOOL.
 * Return Value: RV_ERROR_UNKNOWN     - When other problem accoured
 *               RV_Success     - On success
 * ------------------------------------------------------------------------
 * Arguments:
 *  Input:  hPool    - The Pool which the sdp library will use.
 *  Output: sdpAlloc - Pointer to the allocator which was initialized.
 ***************************************************************************/
RVAPI RvStatus RvSdpAllocConstruct(IN HRPOOL hPool, OUT RvAlloc * sdpAlloc);

 /***************************************************************************
 * RvSdpAllocDestruct
 * ------------------------------------------------------------------------
 * General: Destruct the sdp allocator.
 *          This function is called after the sdp message was destructed.
 * Return Value: void
 * ------------------------------------------------------------------------
 * Arguments:
 *  sdpAlloc - Sdp allocator of the message.
 *
 ***************************************************************************/
RVAPI void RvSdpAllocDestruct(INOUT RvAlloc * sdpAlloc);

/***************************************************************************
 * RvSdpMgrConstructWithConfig
 * ------------------------------------------------------------------------
 * General: Construct sdp library
 * Return Value: RV_ERROR_UNKNOWN     - When other problem accoured
 *               RV_Success     - On success
 * ------------------------------------------------------------------------
 * Arguments:pStackCfg - Structure containing SDP Stack configuration parameters.
 *           sizeOfCfg - The size of the configuration structure.
 ***************************************************************************/
RVAPI RvStatus RvSdpMgrConstructWithConfig(IN RvSdpStackCfg *pStackConfig,
                                            IN RvUint32     sizeOfCfg);
/***************************************************************************
 * RvSdpMgrConstruct
 * ------------------------------------------------------------------------
 * General: Construct sdp library
 * Return Value: RV_ERROR_UNKNOWN     - When other problem accoured
 *               RV_Success     - On success
 * ------------------------------------------------------------------------
 * Arguments:none
 ***************************************************************************/
RVAPI RvStatus RvSdpMgrConstruct(void);

/***************************************************************************
 * SdpMgrDestruct
 * ------------------------------------------------------------------------
 * General: Destruct the sdp library
 * Return Value: void
 ***************************************************************************/
RVAPI void RvSdpMgrDestruct(void);

#if defined(__cplusplus)
}
#endif

#endif /* RV_SDPINIT_H */
