/************************************************************************************************************************
NOTICE:
This document contains information that is proprietary to RADVision LTD..
No part of this publication may be reproduced in any form whatsoever without
written prior approval by RADVision LTD..

RADVision LTD. reserves the right to revise this publication and make changes
without obligation to notify any person of such revisions or changes.

************************************************************************************************************************/



/*********************************************************************************
 *                              <RvSipMidTypes.h>
 *
 *  This file provides headers for the mid layer of the sip stack. this layer is the 
 *  applicaion way to interact wth core. build application timers, register on file 
 *  descriptor event, etc.
 *
 *
 *    Author                         Date
 *    ------                        ------
 *    Udi Tir0sh                   March 2004
 *********************************************************************************/


#ifndef RV_SIP_MID_TYPES_H
#define RV_SIP_MID_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif


/*-----------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                           */
/*-----------------------------------------------------------------------*/
#include "RV_SIP_DEF.h"
    

/*-----------------------------------------------------------------------*/
/*                          TYPE DEFINITIONS                             */
/*-----------------------------------------------------------------------*/
/* Declares a handle to the mid layer manager object. */
RV_DECLARE_HANDLE(RvSipMidMgrHandle);

/* Declares a handle to the appliaction timer object. */
RV_DECLARE_HANDLE(RvSipMidTimerHandle);


/*  RvSipMidCfg
 * -------------------
 *  Structure needed to construct the MidLayer manager.
 *  maxUserFd       -- Maximal number of user file descriptor
 *  maxUserTimers   -- Maximal number of user timers
 *  hLog            - Handle to log manager.
 */
typedef struct{
    RvInt32         maxUserFd;
    RvInt32         maxUserTimers;
    RV_LOG_Handle   hLog;
}RvSipMidCfg;

/*
 * RvSipMidSelectEvent
 * ---------------------------------------------------------------------------
 * Defined select events that can be registered on an application file descriptor
 * RVSIP_MID_SELECT_READ  - notify on read events
 * RVSIP_MID_SELECT_WRITE - notify on write events
 *
 */
typedef enum
{
    RVSIP_MID_SELECT_READ  = 0x01,
    RVSIP_MID_SELECT_WRITE = 0x02
} RvSipMidSelectEvent;


/************************************************************************
 * RvSipMidSelectEv
 * purpose: Callback function returned on events
 * input  : fd      - Handle/file descriptor this event occured on
 *          sEvent  - Event that occured
 *          error   - RV_TRUE if there was an error in the event
 *          ctx     - a context that the application may provide
 * output : none
 * return : none
 ************************************************************************/
typedef void (RVCALLCONV *RvSipMidSelectEv) (
    IN RvInt                       fd,
    IN RvSipMidSelectEvent         event,
    IN RvBool                      error,
    IN void*                       ctx);

/************************************************************************
 * RvSipMidTimerExpEv
 * purpose: Callback function returned on events
 * input  : context - a context that the application may provide
 * output : none
 * return : none
 ************************************************************************/
typedef void (RVCALLCONV *RvSipMidTimerExpEv)(IN void* context);

#ifdef __cplusplus
}
#endif

#endif /*RV_SIP_MID_TYPES_H*/
