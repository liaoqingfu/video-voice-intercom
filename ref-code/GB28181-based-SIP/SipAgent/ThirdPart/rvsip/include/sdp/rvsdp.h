/******************************************************************************
Filename    :rvsdp.h
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
$Date:2/19/04$
$Author:Effi Goldstein$
******************************************************************************/

#ifndef RV_SDP_H
#define RV_SDP_H

#if defined(__cplusplus)
extern "C" {
#endif

#include "rvsdptypes.h"
#include "rverror.h"
#include "rvalloc.h"


/* Defines the log filters to be used by the SDP Stack module. */

typedef enum {
        RVSDP_LOG_DEBUG_FILTER = 0x01,
        RVSDP_LOG_INFO_FILTER  = 0x02,
        RVSDP_LOG_WARN_FILTER  = 0x04,
        RVSDP_LOG_ERROR_FILTER = 0x08,
        RVSDP_LOG_EXCEP_FILTER = 0x10,
        RVSDP_LOG_SYNC_FILTER  = 0x20,
        RVSDP_LOG_ENTER_FILTER = 0x40,
        RVSDP_LOG_LEAVE_FILTER = 0x80
} RvSdpLogFilters;


/***************************************************************************
 * RvSdpStackPrintLogEntryEv
 * ------------------------------------------------------------------------
 * General: Notifies the application each time a line should be printed to
 *          the log. The application can decide wether to print the line
 *          to the screen, file or other output device.
 * Return Value: (-)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   filter -    The filter that this message is using (info, error..)
 *          formattedText - The text to be printed to the log. The text
 *                          is formatted as follows:
 *                          <filer> - <module> - <message>
 *                          for example:
 *                          "INFO  - STACK - Stack was constructed successfully"
 ***************************************************************************/
typedef void
        (RVCALLCONV * RvSdpStackPrintLogEntryEv)(
                                         IN void*           context,
                                         IN RvSdpLogFilters filter,
                                         IN const RvChar   *formattedText);


typedef struct
{
    RvSdpStackPrintLogEntryEv   pfnPrintLogEntryEvHandler;
	void*						logManagerPtr;				
    void*                       logContext;

}RvSdpStackCfg;


/***************************************************************************
 * RvSdpConstruct
 * ------------------------------------------------------------------------
 * General: Construct sdp library
 * Return Value: RV_ERROR_UNKNOWN     - When other problem occured
 *               RV_Success           - On success
 * ------------------------------------------------------------------------
 * Arguments: pStackCfg - Structure containing SDP Stack configuration parameters. 
 *                        NULL will result in creating a new log manager with default parameters.
 ***************************************************************************/
RVAPI RvStatus RvSdpConstruct(IN RvSdpStackCfg *pStackConfig);

/***************************************************************************
 * RvSdpDestruct
 * ------------------------------------------------------------------------
 * General: Destruct the sdp library
 * Return Value: void
 ***************************************************************************/
RVAPI void RvSdpDestruct(void);

#if defined(__cplusplus)
}
#endif

#endif /* RV_SDP_H */
