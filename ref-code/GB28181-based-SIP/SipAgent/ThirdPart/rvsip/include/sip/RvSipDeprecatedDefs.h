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
 *                              <RvSipDepracatedDefs.h>
 *
 * The file includes type definitions that where replaced and are no longer in use.
 * The old type definitions are converted to the new type definitions.
 *
 *
 *    Author                         Date
 *    ------                        ------
 *    Sarit Galanos                 Dec-2004
 *********************************************************************************/
#ifndef _RV_SIP_DEPRECATED_DEFS
#define _RV_SIP_DEPRECATED_DEFS

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "rvtypes.h"
#include "rverror.h"



#ifndef RV_Success
#define RV_Success                RV_OK
#endif


#ifndef RV_Failure
#define RV_Failure                RV_ERROR_UNKNOWN
#endif

#ifndef RV_InvalidHandle
#define RV_InvalidHandle          RV_ERROR_INVALID_HANDLE
#endif

#ifndef RV_InvalidParameter
#define RV_InvalidParameter       RV_ERROR_BADPARAM
#endif

#ifndef RV_OutOfResources
#define RV_OutOfResources         RV_ERROR_OUTOFRESOURCES
#endif

#ifndef RV_TryAgain
#define RV_TryAgain               RV_ERROR_TRY_AGAIN
#endif

#ifndef RV_IllegalAction
#define RV_IllegalAction           RV_ERROR_ILLEGAL_ACTION
#endif


#ifndef RV_NumOfThreadsDecrease
#define RV_NumOfThreadsDecrease    RV_ERROR_NUM_OF_THREADS_DECREASED
#endif

#ifndef RV_Uninitialized
#define RV_Uninitialized           RV_ERROR_UNINITIALIZED
#endif

#ifndef RV_OutOfMemory
#define RV_OutOfMemory             RV_ERROR_OUTOFRESOURCES
#endif

#ifndef RV_BadPointer
#define RV_BadPointer              RV_ERROR_NULLPTR
#endif

#ifndef RV_NotFound
#define RV_NotFound                RV_ERROR_NOT_FOUND
#endif

#ifndef RV_ObjectTerminated
#define RV_ObjectTerminated        RV_ERROR_DESTRUCTED
#endif

#ifndef RV_InsufficientBuffer
#define RV_InsufficientBuffer      RV_ERROR_INSUFFICIENT_BUFFER
#endif

#ifndef RV_ApplicationError
#define RV_ApplicationError        RV_ERROR_UNKNOWN
#endif

#ifndef RV_UnsupportedOperation
#define RV_UnsupportedOperation    RV_ERROR_NOTSUPPORTED
#endif

#ifndef RV_PartialMessage
#define RV_PartialMessage          RV_ERROR_ILLEGAL_SYNTAX
#endif

#ifndef RV_IllegalSyntax
#define RV_IllegalSyntax           RV_ERROR_ILLEGAL_SYNTAX
#endif

#ifndef RV_ParserError
#define RV_ParserError             RV_ERROR_ILLEGAL_SYNTAX
#endif

#ifndef RV_ObjectAlreadyExists
#define RV_ObjectAlreadyExists     RV_ERROR_OBJECT_ALREADY_EXISTS
#endif

#ifndef RV_UnParsedMultiPart
#define RV_UnParsedMultiPart       RV_ERROR_ILLEGAL_SYNTAX
#endif

#ifndef RV_MandatoryParamMissing
#define RV_MandatoryParamMissing   RV_ERROR_NOT_FOUND
#endif

#ifndef RV_NetworkProblem
#define RV_NetworkProblem          RV_ERROR_NETWORK_PROBLEM
#endif

/*****************************************************************************
 *                          MACROS Definition                                *
 *****************************************************************************/

#ifndef DECLARE_VOID_POINTER
#define DECLARE_VOID_POINTER RV_DECLARE_HANDLE
#endif 


/*****************************************************************************
 *                         Primitive Type Definitions                        *
 *****************************************************************************/

#ifndef RV_BASIC_TYPES
#define RV_BASIC_TYPES

typedef RvStatus        RV_Status;
typedef RvUint64        RV_UINT64;
typedef RvUint32        RV_UINT32;
typedef RvUint16        RV_UINT16;
typedef RvUint8         RV_UINT8;
typedef RvInt32         RV_INT32;
typedef RvInt16         RV_INT16;
typedef RvInt8          RV_INT8;
typedef RvUint          RV_UINT;
typedef RvInt           RV_INT;
typedef RvUint8         RV_BYTE;
typedef RvUint8         RV_UCHAR;
typedef RvChar          RV_CHAR;
typedef RvBool          RV_BOOL;
#endif



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*_RV_SIP_DEPRECATED_DEFS*/
