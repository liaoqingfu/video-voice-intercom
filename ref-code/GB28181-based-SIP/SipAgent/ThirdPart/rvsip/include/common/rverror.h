/***********************************************************************
Filename   : rverror.h
Description: error code definitions for all RADVISION modules
             - This module provides macros and constants for handling error codes.
************************************************************************
      Copyright (c) 2001,2002 RADVISION Inc. and RADVISION Ltd.
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

#ifndef RV_ERROR_H
#define RV_ERROR_H

#include "rvtypes.h"


/********************************************************************************************
 * RvStatus
 * A status value (also know as an error code value).
 * Each status code can be checked for three basic conditions:
 *  RvStatus = RV_OK indicates no error.
 *  RvStatus < RV_OK indicates an error.
 *  RvStatus > RV_OK indicates a warning.
 *
 * When a warning or an error is indicated, more information can
 * be extracted from the value. Each warning or error contains
 * three pieces of information which can be retrieved using the
 * corresponding functions:
 * Library code: This value indicates which library the error code
 *  was generated in. The library codes are defined in rverror.h.
 * Module code: This value indicates which module within the indicated
 * 	library that the error code was generate in. These module codes
 * 	are defined by each library and are listed in the main definitions
 * 	file for each library.
 * Error/Warning code: This value indicates the actual error or warning
 *	code that was generated. Error codes will be negative numbers and
 *	warning codes will be positive numbers. There are two types of
 *	error/warning codes, global ones defined in rverror.h and module
 *	specific ones which can be found in the header file of each module.
 ********************************************************************************************/
typedef RvInt32 RvStatus;


/* Error code layout (32 bits, 0 = low order bit, 31 = high order/sign bit): */
/* Bits 0-9, 31: Error code (range includes sign bit: -1 to -1023, 1 to 1023)*/
/* Bits 10-19: Module code (range: 1 to 1023) */
/* Bits 20-30: Library code (range: 1 to 2047) */
#define RV_ERROR_MODULE_STARTBIT  10 /* skip this many bits for the error code */
#define RV_ERROR_LIB_STARTBIT 20 /* skip this many bits for error and module codes */
#define RV_ERROR_ERROR_MASK  0x800003FF /* include sign bit */
#define RV_ERROR_MODULE_MASK 0x000FFC00
#define RV_ERROR_LIB_MASK    0x7FF00000

/* Error Macros: See documentation blocks below for details. */

/********************************************************************************************
 * RvErrorCode
 * Create a status code.
 * PARAMS: _p - Library code.
 *         _m - Module code.
 *         _e - Error or warning code.
 * RETURN: Status code.
 ********************************************************************************************/
#define RvErrorCode(_p, _m, _e) ((RvStatus)(((RvUint32)(_e) & RV_ERROR_ERROR_MASK) | ((_p) << RV_ERROR_LIB_STARTBIT) | ((_m) << RV_ERROR_MODULE_STARTBIT)))

/********************************************************************************************
 * RvErrorGetCode
 * Get the error or warning code from a status code.
 * PARAMS: _e - Status code to get error/warning code from.
 * RETURN: Error or warning code.
 ********************************************************************************************/
#define RvErrorGetCode(_e) ((RvStatus)(((_e) < 0) ? ((RvUint32)(_e) | (~RV_ERROR_ERROR_MASK)) : ((RvUint32)(_e) & RV_ERROR_ERROR_MASK)))

/********************************************************************************************
 * RvErrorGetModule
 * Get the module code from a status code.
 * PARAMS: _e - Status code to get module code from.
 * RETURN: Module code.
 ********************************************************************************************/
#define RvErrorGetModule(_e) (((_e) & RV_ERROR_MODULE_MASK) >> RV_ERROR_MODULE_STARTBIT)

/********************************************************************************************
 * RvErrorGetLib
 * Get the library code from a status code.
 * PARAMS: _e - Status code to get library code from.
 * RETURN: Library code.
 ********************************************************************************************/
#define RvErrorGetLib(_e) (((_e) & RV_ERROR_LIB_MASK) >> RV_ERROR_LIB_STARTBIT)

/* OK value. If RvStatus < RV_OK then its an error. If RvStatus > RV_OK */
/* then its a warning. */
#define RV_OK RvInt32Const(0)

/* Library Codes 1..2047 */
#define RV_ERROR_LIBCODE_CUTILS 1
#define RV_ERROR_LIBCODE_CCORE 2
#define RV_ERROR_LIBCODE_CBASE 3
#define RV_ERROR_LIBCODE_MGCP 4
#define RV_ERROR_LIBCODE_MEGACO 5
#define RV_ERROR_LIBCODE_SIP 6
#define RV_ERROR_LIBCODE_H323 7
#define RV_ERROR_LIBCODE_RTP 8
#define RV_ERROR_LIBCODE_SDP 9
#define RV_ERROR_LIBCODE_OLDRTP 10
#define RV_ERROR_LIBCODE_EPP 11
#define RV_ERROR_LIBCODE_H223 12

/* Module Codes 1..1023 */
/* These codes are specific to each library and should be defined */
/* in the main header file for each library. */

/* Error Codes */
/* Negative error codes are real error while positive codes are used */
/* to indicate a warning. Codes in the range -1 to -511 and 1 to 511 */
/* are defined here and are common errors that may be used by any module. */
/* Codes in the range -512 to -1023 and 512 to 1023 may be defined on a */
/* module by module basis and should be defined in that module's header */
/* file. */

/* Common Error Codes -1..-511 */
#define RV_ERROR_UNKNOWN -1                 /* There was an error, but we don't know specifics */
#define RV_ERROR_OUTOFRESOURCES -2          /* no resource left for this operation */
#define RV_ERROR_BADPARAM -3                /* parameter value invalid */
#define RV_ERROR_NULLPTR -4                 /* required pointer parameter was a NULL pointer */
#define RV_ERROR_OUTOFRANGE -5              /* parameter out of range */
#define RV_ERROR_DESTRUCTED -6              /* operation attempted on a destructed object */
#define RV_ERROR_NOTSUPPORTED -7            /* request not supported under current configuration */
#define RV_ERROR_UNINITIALIZED -8           /* object uninitialized */
#define RV_ERROR_TRY_AGAIN -9	            /* incomplete operation, used by semaphore's try lock */
#define RV_ERROR_ILLEGAL_ACTION -10         /* the requested action is illegal */
#define RV_ERROR_NETWORK_PROBLEM -11        /* action failed due to network problems */
#define RV_ERROR_INVALID_HANDLE -12         /* a handle passed to a function is illegal */
#define RV_ERROR_NOT_FOUND -13              /* the requested item cannot be found */
#define RV_ERROR_INSUFFICIENT_BUFFER -14    /* the buffer is too small */




/* Common Warning Codes 1..511 */
/* None yet.*/

#endif /* RV_ERROR_H */
