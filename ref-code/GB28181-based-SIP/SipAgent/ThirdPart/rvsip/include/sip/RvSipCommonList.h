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
* Copyright RADVision 1996.                                                     *
* Last Revision: Jan. 2000                                                      *
*********************************************************************************
*/


/*********************************************************************************
 *                              <RvSipCommonList.h>
 *
 * This file contain an API implementation of the Sip common list.
 *
 *
 *    Author                         Date
 *    ------                        ------
 *    Ofra Wachsman                 Nov-2003
 *********************************************************************************/
#ifndef _RV_SIP_COMMON_LIST_H
#define _RV_SIP_COMMON_LIST_H


#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILED                           */
/*-----------------------------------------------------------------------*/
#include "RV_SIP_DEF.h"
#include "RvSipCommonTypes.h"
#include "rpool_API.h"
#include "RV_ADS_DEF.h"



/*-----------------------------------------------------------------------*/
/*                            TYPE DEFINITIONS                           */
/*-----------------------------------------------------------------------*/
/*
 * RvSipCommonListHandle
 * ---------------------
 * Handle to a sip-common-list object.
 */
RV_DECLARE_HANDLE(RvSipCommonListHandle);

/*
 * RvSipCommonListElemHandle
 * ---------------------
 * Handle to a sip-common-list element object.
 */
RV_DECLARE_HANDLE(RvSipCommonListElemHandle);
/*-----------------------------------------------------------------------*/
/*                           MODULE FUNCTIONS                            */
/*-----------------------------------------------------------------------*/

/***************************************************************************
 * RvSipCommonListConstruct
 * ------------------------------------------------------------------------
 * General: Construct Sip Common list.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input :    hPool    - A handle to the List Pool.
 *            hLog     - A handle to the stack log module.
 * Output:    phList   - A handle to the created list.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipCommonListConstruct(
                                    IN  HRPOOL                     hPool,
                                    IN  RV_LOG_Handle              hLog,
                                    OUT RvSipCommonListHandle*     phList);

/***************************************************************************
 * RvSipCommonListDestruct
 * ------------------------------------------------------------------------
 * General: Destruct a Sip Common list. When the list is destructed its free
 *          all stored data (header and messages).
 * Return Value: RV_OK - on success.
 *               RV_ERROR_NULLPTR - hList is NULL.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input: hHeaderList - handle to list to destruct.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipCommonListDestruct(
                                       IN RvSipCommonListHandle hList);

/***************************************************************************
 * RvSipCommonListPushElem
 * ------------------------------------------------------------------------
 * General: Add given element to the Sip Common list.
 *          Application must allocate the new element on the list page
 *          and then call this function to add the allocated element to the list.
 *
 * Return Value: RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input : hList       - handle to list.
 *         eElemType   - element type to be set in the list element.
 *                       (e.g RVSIP_HEADERTYPE_CONTACT when adding a contact
 *                       header to the list)
 *           pData       - pointer to allocated element data (e.g this is the contact
 *                       header handle that application got when calling
 *                       RvSipContactHeaderConstruct).
 *           eLocation   - inserted element location (first, last, etc).
 *         hPos        - current list position, relevant in case that
 *                       location is next or prev.
 * Output: pNewPos     - returned the location of the object that was pushed.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipCommonListPushElem(
                              IN     RvSipCommonListHandle       hList,
                              IN     RvInt                      eElemType,
                              IN     void*                       pData,
                              IN     RvSipListLocation           eLocation,
                              IN     RvSipCommonListElemHandle   hPos,
                              INOUT  RvSipCommonListElemHandle*  phNewPos);

/***************************************************************************
 * RvSipCommonListRemoveElem
 * ------------------------------------------------------------------------
 * General: Remove an element from the list.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input : hList       - List.
 *         hListElem   - handle to the list element to be removed.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipCommonListRemoveElem(
                                    IN RvSipCommonListHandle     hList,
                                    IN RvSipCommonListElemHandle hListElem);

/***************************************************************************
 * RvSipCommonListGetElem
 * ------------------------------------------------------------------------
 * General: Return element from the Sip Common list.
 *          The function returns the first/last elements, or the
 *          previous/following elements relatively to another element.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input :    hList - List.
 *          eLocation  - Location of the wanted element in the list.
 *                       (first, last, next, prev).
 *          hPos       - current list position, relevant in case that
 *                       location is next or prev.
 * Output:    peElemType - the type of the list element that was got from list.
 *          pElemData  - the data of the list element that was got from list.
 *          phNewPos   - the location of the object that was got.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipCommonListGetElem(
                               IN     RvSipCommonListHandle      hList,
                               IN     RvSipListLocation          eLocation,
                               IN     RvSipCommonListElemHandle  hPos,
                               OUT    RvInt                     *peElemType,
                               OUT    void*                      *pElemData,
                               OUT    RvSipCommonListElemHandle  *phNewPos);


/***************************************************************************
 * RvSipCommonListIsEmpty
 * ------------------------------------------------------------------------
 * General: Return indication whether the Sip Common list is empty.
 * Return Value: RV_OK    - on success.
 *                 RV_ERROR_NULLPTR - either hList or pbIsEmpty are NULL.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input:  hList - Handle to the list.
 *    Output: *pbIsEmpty  - RV_TRUE if Sip Common list is empty. otherwise RV_FALSE.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipCommonListIsEmpty(
                                         IN  RvSipCommonListHandle hList,
                                         OUT RvBool*           pbIsEmpty);

/***************************************************************************
 * RvSipCommonListGetPool
 * ------------------------------------------------------------------------
 * General: Return the Sip Common list memory pool.
 * Return Value: the memory pool handle.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input:  hList - Handle to the list.
 ***************************************************************************/
RVAPI HRPOOL RVCALLCONV RvSipCommonListGetPool(
                                         IN  RvSipCommonListHandle hList);
/***************************************************************************
 * RvSipCommonListGetPage
 * ------------------------------------------------------------------------
 * General: Return the Sip Common list memory page.
 * Return Value: the memory page handle.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input:  hList - Handle to the list.
 ***************************************************************************/
RVAPI HPAGE RVCALLCONV RvSipCommonListGetPage(
                                         IN  RvSipCommonListHandle hList);

#ifdef __cplusplus
}
#endif

#endif  /*END OF: define _RV_SIP_COMMON_LIST_H*/
/* new line :)*/

