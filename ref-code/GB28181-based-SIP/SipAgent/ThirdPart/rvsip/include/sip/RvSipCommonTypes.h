
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
*********************************************************************************
*/


/*********************************************************************************
 *                              RvSipCommonTypes.h
 *
 *	Common definitions of RADVISION SIP stack.
 *
 *    Author                         Date
 *    ------                        ------
 *  
 *********************************************************************************/


#ifndef _RV_SIP_COMMON_TYPES_H
#define _RV_SIP_COMMON_TYPES_H


#ifdef __cplusplus
extern "C" {
#endif


    
typedef enum
{
    RVSIP_COMMON_STACK_OBJECT_TYPE_UNDEFINED = -1,
    RVSIP_COMMON_STACK_OBJECT_TYPE_CALL_LEG,
    RVSIP_COMMON_STACK_OBJECT_TYPE_TRANSACTION,
    RVSIP_COMMON_STACK_OBJECT_TYPE_CALL_TRANSACTION,
    RVSIP_COMMON_STACK_OBJECT_TYPE_SUBSCRIPTION,
    RVSIP_COMMON_STACK_OBJECT_TYPE_NOTIFICATION,
    RVSIP_COMMON_STACK_OBJECT_TYPE_REG_CLIENT,
    RVSIP_COMMON_STACK_OBJECT_TYPE_CONNECTION
}RvSipCommonStackObjectType;



/* RvSipListLocation
 * --------------------
 * This enumeration represents the location of an element on a list.
 * 
 */

typedef enum
{
    RVSIP_FIRST_ELEMENT = 0,
	RVSIP_LAST_ELEMENT,
	RVSIP_NEXT_ELEMENT,
	RVSIP_PREV_ELEMENT
} RvSipListLocation;



/* Defines the log filters to be used by the RADVISION SIP stack modules. */ 
 typedef enum {
    RVSIP_LOG_DEBUG_FILTER    = 0x01,
    RVSIP_LOG_INFO_FILTER     = 0x02,
    RVSIP_LOG_WARN_FILTER     = 0x04,
    RVSIP_LOG_ERROR_FILTER    = 0x08,
    RVSIP_LOG_EXCEP_FILTER    = 0x10,
    RVSIP_LOG_LOCKDBG_FILTER  = 0x20,
	RVSIP_LOG_ENTER_FILTER    = 0x40,   /*only for common core loging*/
	RVSIP_LOG_LEAVE_FILTER    = 0x80
} RvSipLogFilters;


#ifdef __cplusplus
}
#endif

#endif  /*END OF: define _RV_SIP_COMMON_TYPES_H*/
