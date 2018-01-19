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
 *                              <RV_SIP_DEF.h>
 *
 * Type definitions that are specific for the sip stack.
 *
 *
 *    Author                         Date
 *    ------                        ------
 *    Sarit Galanos                Jan-2004
 *********************************************************************************/

#ifndef _RV_SIP_DEF
#define _RV_SIP_DEF

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#include "rvtypes.h"
#include "rverror.h"

#if !defined(RV_NOUSRCONFIG)
/* Pull in user (override) definitions */
#include "RvSipUserConfig.h"
#endif

/*****************************************************************************
 *                 Status codes                          *
 *****************************************************************************/

/*sip stack additional status codes
  more status codes can be found in the rverror.h file  */
#define RV_ERROR_ILLEGAL_SYNTAX                -3000
#define RV_ERROR_OBJECT_ALREADY_EXISTS         -3001
#define RV_ERROR_COMPRESSION_FAILURE           -3002
#define RV_ERROR_NUM_OF_THREADS_DECREASED      -3003 


#ifndef RV_LOG_TYPES
#define RV_LOG_TYPES
RV_DECLARE_HANDLE(RV_LOG_Handle);
#endif

#if defined(RV_DEPRECATED_CORE)

/* Definition select and timer pool handles*/
#ifndef RV_SELI_HANDLE
#define RV_SELI_HANDLE
RV_DECLARE_HANDLE(RV_SELI_Handle);
#endif /*RV_SELI_HANDLE*/


#ifndef RV_TIMER_POOL_HANDLE
#define RV_TIMER_POOL_HANDLE
RV_DECLARE_HANDLE(RV_TIMER_PoolHandle);
#endif /*RV_TIMER_POOL_HANDLE*/
#endif

#include "RvSipDeprecatedDefs.h"



/*****************************************************************************
 *                 Compilation Flags Definitions                             *
 *****************************************************************************/

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
