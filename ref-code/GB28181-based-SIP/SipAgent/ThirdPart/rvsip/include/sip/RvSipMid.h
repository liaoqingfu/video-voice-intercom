/************************************************************************************************************************
NOTICE:
This document contains information that is proprietary to RADVision LTD..
No part of this publication may be reproduced in any form whatsoever without
written prior approval by RADVision LTD..

RADVision LTD. reserves the right to revise this publication and make changes
without obligation to notify any person of such revisions or changes.

************************************************************************************************************************/



/*********************************************************************************
 *                              <RvSipMid.h>
 *
 * This file contains all API functions relevant to intrer acting with core lever 
 * functionality, including select poll and timers.
 *
 * select/poll 
 * ------------------------
 * Enables an application to register event for select loop or poll queries.
 * Enables an application to perform a select loop or a poll loop
 *
 * timers
 * -----------------
 * Enables an application to set and release timers.
 * Timer can be set on threads that ran one of RADVISION toolkits only, as only those 
 * threads use the RADVISION select() loop.
 *
 *    Author                         Date
 *    ------                        ------
 *    Udi Tir0sh                   March 2004
 *********************************************************************************/


#ifndef RV_SIP_MID_H
#define RV_SIP_MID_H

#ifdef __cplusplus
extern "C" {
#endif


/*-----------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                           */
/*-----------------------------------------------------------------------*/
#include "RV_SIP_DEF.h"
#include "RvSipMidTypes.h"
    
/*-------------------------------------------------------------------------*/
/*                           MODULE FUNCTIONS                              */
/*-------------------------------------------------------------------------*/

/************************************************************************************
 * RvSipMidInit
 * ----------------------------------------------------------------------------------
 * General: Starts the Mid layer services. before calling to any of the function 
 *          of this module, the application must call this function
 * Return Value: Returns RvStatus.
 * ----------------------------------------------------------------------------------
 * Arguments:
 * Input:   -
 * Output:  -
 ***********************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMidInit(void);

/************************************************************************************
 * RvSipMidEnd
 * ----------------------------------------------------------------------------------
 * General: Ends the Mid layer services. 
 * Return Value: Returns RvStatus.
 * ----------------------------------------------------------------------------------
 * Arguments:
 * Input:   -
 * Output:  -
 ***********************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMidEnd(void);

/************************************************************************************
 * RvSipMidConstruct
 * ----------------------------------------------------------------------------------
 * General: Constructs and initializes the middle layer. This function allocates the
 *          required memory and constructs middle layer objects acording to the given 
 *          configuration. The function returns a handle to the middle layer manager. 
 *          You need this handle in order to use the middle layer APIs.
 *          when finishig using the middle layer call RvSipMidPrepareDestruct() if 
 *          needed and RvSipMidDesstruct() to free all resources.
 *          allocated resources
 * Return Value: Returns RvStatus.
 * ----------------------------------------------------------------------------------
 * Arguments:
 * Input:   pMidCfg     - Structure containing middle layer configuration parameters.
 *          sizeOfCfg   - The size of the configuration structure.
 * Output:  phMidMgr     - Handle to the middle layer manager.
 ***********************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMidConstruct(
                                         IN    RvInt32               sizeOfCfg,
                                         IN    RvSipMidCfg*          pMidCfg,
                                         OUT   RvSipMidMgrHandle*    phMidMgr);

/************************************************************************************
 * RvSipMidPrepareDestruct
 * ----------------------------------------------------------------------------------
 * General: This function will free all application resources. after calling this 
 *          function, allow enough time for other threads (if there are any) to finish 
 *          any calls to middle functions and call RvSipMidDestruct().
 *          If the application is sure that no other threads wait tp preform actions 
 *          on the mid layer, it can call RvSipMidDestruct() directly.
 *          After calling this function the application is not allowed to set timers 
 *          or register on select events
 *          All Application timers will be released.
 *          All select registrations will be removed.
 *
 * Return Value: RvStatus
 * ----------------------------------------------------------------------------------
 * Arguments:
 * Input:   hMidMgr     - Handle to the middle layer manager
 * Output:
 ***********************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMidPrepareDestruct(IN RvSipMidMgrHandle    hMidMgr);

/************************************************************************************
 * RvSipMidDestruct
 * ----------------------------------------------------------------------------------
 * General: This function will free all manager resources. after calling this 
 *          function the application is not allowed to call on file descriptors 
 *          or set timers.
 * Return Value: RvStatus
 * ----------------------------------------------------------------------------------
 * Arguments:
 * Input:   hMidMgr     - Handle to the middle layer manager
 * Output:
 ***********************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMidDestruct(IN RvSipMidMgrHandle    hMidMgr);
    
/************************************************************************************
 * RvSipMidSetLog
 * ----------------------------------------------------------------------------------
 * General: Sets a log handle to the mid layer. Use this function if mid layed was 
 *          initiated before the stack.
 *          Use RvSipStackGetLogHandle() to get the log handle from the SIP Toolkit.
 * Return Value: Returns RvStatus.
 * ----------------------------------------------------------------------------------
 * Arguments:
 * Input:   hMidMgr   -- handle to the middle layer manager.
 *          hLog      -- log handle
 * Output:  -
 ***********************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMidSetLog(IN RvSipMidMgrHandle     hMidMgr,
                                         IN RV_LOG_Handle         hLog);

/***************************************************************************
 * RvSipMidMemAlloc
 * ------------------------------------------------------------------------
 * General: Allocates memory for application use.
 *          This function can be called only after core services were initialized.
 * Return Value: Pointer to newly allocated memory if successful.
 *               NULL o/w.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     size   - Allocation size in bytes.
 ***************************************************************************/
RVAPI void* RVCALLCONV RvSipMidMemAlloc(IN RvInt32 size);


/***************************************************************************
 * RvSipMidMemFree
 * ------------------------------------------------------------------------
 * General: Frees memory allocated by RvSipMemAlloc().
 *          Only memory allocation that were done using RvSipMemAlloc() should
 *          be freed with this function.
 * Return Value: (-).
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     memptr     - memory to free.
 ***************************************************************************/
RVAPI void RVCALLCONV RvSipMidMemFree(IN void* memptr);


/***************************************************************************
 * RvSipMidTimeInMilliGet
 * ------------------------------------------------------------------------
 * General: Gets a timestamp value in milliseconds.
 * Return Value: The timestamp value in milliseconds.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     
 ***************************************************************************/
RVAPI RvUint32 RVCALLCONV RvSipMidTimeInMilliGet(void);

/***************************************************************************
 * RvSipMidTimeInSecondsGet
 * ------------------------------------------------------------------------
 * General: Gets a timestamp value in seconds.
 * Return Value: The timestamp value in seconds.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     
 ***************************************************************************/
RVAPI RvUint32 RVCALLCONV RvSipMidTimeInSecondsGet(void);

/************************************************************************************
 * RvSipMidTimerSet
 * ----------------------------------------------------------------------------------
 * General: Sets a new timer.
 *          when a timer expires, the resources it consumes will be released automaticlly.
 *          it is forbidden to call RvSipMidTimerReset() in the timer callback.
 * Return Value: Returns RvStatus.
 * ----------------------------------------------------------------------------------
 * Arguments:
 * Input:   hMidMgr     -- handle to the middle layer manager.
 *          miliTimeOut -- experation specified in miliseconds
 *          cb          -- application callback
 *          ctx         -- context to be called when timer expires
 * Output:  phTimer     -- a newly allocated timer
 ***********************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMidTimerSet(IN RvSipMidMgrHandle       hMidMgr,
                                    IN RvUint32                 miliTimeOut,
                                    IN RvSipMidTimerExpEv       cb,
                                    IN void*                    ctx,
                                    OUT RvSipMidTimerHandle*    phTimer);

/************************************************************************************
 * RvSipMidTimerReset
 * ----------------------------------------------------------------------------------
 * General: releases a timer
 * Return Value: Returns RvStatus.
 * ----------------------------------------------------------------------------------
 * Arguments:
 * Input:   pMidMgr   -- pointer to the middle layer manager.
 * Output:  phTimer   -- handle of timer to delete
 ***********************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMidTimerReset(IN RvSipMidMgrHandle       hMidMgr,
                                             IN RvSipMidTimerHandle    hTimer);

/************************************************************************************
 * RvSipMidSelectCallOn
 * ----------------------------------------------------------------------------------
 * General: registers a file descriptor to the select loop. You can register to 
 *          listen on read or write events, and provide a callback that will be called 
 *          when the select exits due to activity on that file descriptor
 * Return Value: Returns RvStatus.
 * ----------------------------------------------------------------------------------
 * Arguments:
 * Input:   hMidMgr   -- handle to the middle layer manager.
 *          fd        -- OS file descriptor
 *          events    -- read/write
 *          pCallBack -- user callback
 *          ctx       -- usr context
 * Output:  
 ***********************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMidSelectCallOn(IN RvSipMidMgrHandle    hMidMgr,
                                               IN RvInt32              fd,
                                               IN RvSipMidSelectEvent  events,
                                               IN RvSipMidSelectEv     pCallBack,
                                               IN void*                ctx);

/******************************************************************************
 * RvSipMidSelectSetMaxDescs
 * ------------------------------------------------------------------------
 * General: Set the amount of file descriptors that the Select module can handle in a single
 *          select engine. This is also the value of the highest file descriptor possible.
 *          This function MUST be called before stack/middle layer initialization
 * Return Value: RV_OK on success, error code otherwise
 *               (see RV_SIP_DEF.h, rverror.h)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:  maxDescs - Maximum value of file descriptor possible
 * Output: - 
 *****************************************************************************/
RVAPI RvStatus RvSipMidSelectSetMaxDescs(IN RvUint32 maxDescs);

/******************************************************************************
 * RvSipMidSelectGetMaxDesc
 * ------------------------------------------------------------------------
 * General: Get the current value used as the maximum value for a file descriptor 
 *          by the select procedures.
 * Return Value: RV_OK on success, error code otherwise
 *               (see RV_SIP_DEF.h, rverror.h)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:  -
 * Output: pMaxFds - place to store maximun number of file descriptors
 *****************************************************************************/
RVAPI RvStatus RvSipMidSelectGetMaxDesc(OUT RvUint32 *pMaxFds);

#if defined(FD_SETSIZE)
#if (RV_SELECT_TYPE == RV_SELECT_SELECT)
/******************************************************************************
 * RvSipMidSelectGetEventsRegistration
 * ------------------------------------------------------------------------
 * General: Get Select file descriptors for select operation
 *          NOTE: 1. This function cann be called only in the thread that 
 *                   initiated the stack.
 *                2. This function resets the fd sets that was given to it.
 *                   if you intent to add file descriptors to the fd sets do 
 *                   so AFTER calling this function
 *
 * Return Value: RV_OK on success, error code otherwise
 *               (see RV_SIP_DEF.h, rverror.h)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:  hMidMgr         - handle to the middle layer manager
 *         fdSetLen        - the length of the file descriptors set
 * Output: pMaxfd          - maximum number of file descriptors
 *         rdSet           - pointer to read file descriptor set
 *         wrSet           - pointer to write file descriptor set
 *         exSet           - pointer to exeption file descriptor set (reserved for future use)
 *         pTimeOut        - time out the stack want to give to select. (-1 means ingfinite)      
 *****************************************************************************/
RVAPI RvStatus RvSipMidSelectGetEventsRegistration(IN  RvSipMidMgrHandle               hMidMgr,
                                                    IN  RvInt                           fdSetLen,
                                                    OUT RvInt*                          pMaxfd,
                                                    OUT fd_set*                         rdSet,
                                                    OUT fd_set*                         wrSet,
                                                    OUT fd_set*                         exSet,
                                                    OUT RvUint32*                       pTimeOut);

/******************************************************************************
 * RvSipMidSelectEventsHandling
 * ------------------------------------------------------------------------
 * General: Handle events gotten from select procedure
 *          NOTE: this function can be called only in the thread that 
 *          initiated the stack
 * Return Value: RV_OK on success, error code otherwise
 *               (see RV_SIP_DEF.h, rverror.h)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:  hMidMgr         - handle to the middle layer manager
 *         rdSet           - pointer to read file descriptor set
 *         wrSet           - pointer to write file descriptor set
 *         exSet           - pointer to exeption file descriptor set (reserved for futur use)
 *         numFds         - maximum number of file descriptors
 *         numEvents      - number of occured events
 *****************************************************************************/
RVAPI RvStatus RvSipMidSelectEventsHandling(IN RvSipMidMgrHandle               hMidMgr,
                                            IN fd_set*   rdSet,
                                            IN fd_set*   wrSet,
                                            IN fd_set*   exSet,
                                            IN RvInt     numFds,
                                            IN RvInt     numEvents);
#endif /*(RV_SELECT_TYPE == RV_SELECT_SELECT)*/
#endif  /* #if defined(FD_SETSIZE)*/

#if (RV_SELECT_TYPE == RV_SELECT_POLL)
/******************************************************************************
 * RvSipMidPollGetEventsRegistration
 * ------------------------------------------------------------------------
 * General: Get Select file descriptors for select operation
 *          NOTE: 1. This function cann be called only in the thread that 
 *                   initiated the stack.
 *                2. This function resets the fd sets that was given to it.
 *                   if you intent to add file descriptors to the fd sets do 
 *                   so AFTER calling this function
 *
 * Return Value: RV_OK on success, error code otherwise
 *               (see RV_SIP_DEF.h, rverror.h)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:  hMidMgr         - handle to the middle layer manager
 *         len             - the length of the poll fd set
 * Output: pollFdSet       - pointer poll fd set to poll 
 *         pNum            - the number of file descriptors on the poll set      
 *         pTimeOut        - time out the stack want to give to poll. (-1 means ingfinite)      
 *****************************************************************************/
RVAPI RvStatus RvSipMidPollGetEventsRegistration(IN RvSipMidMgrHandle               hMidMgr,
                                                IN  RvInt           len,
                                                OUT struct pollfd*  pollFdSet,
                                                OUT RvInt*          pNum,
                                                OUT RvUint32*       pTimeOut);

/******************************************************************************
 * RvSipMidPollEventsHandling
 * ------------------------------------------------------------------------
 * General: Handle events gotten from poll procedure
 *          NOTE: this function can be called only in the thread that 
 *          initiated the stack
 *
 * Return Value: RV_OK on success, error code otherwise
 *               (see RV_SIP_DEF.h, rverror.h)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:  hMidMgr         - handle to the middle layer manager
 *         num             - number of file descriptors
 *         pollFdSet       - pointer poll fd set from poll 
 * Output: 
 *           
 *****************************************************************************/
RVAPI RvStatus RvSipMidPollEventsHandling(IN RvSipMidMgrHandle  hMidMgr,
                                            IN struct pollfd*     pollFdSet,
                                            IN RvInt              num,
                                            IN RvInt              numEvents);
#endif  /* (RV_SELECT_TYPE == RV_SELECT_POLL) */


/************************************************************************************
 * RvSipMidMainThreadClean
 * ----------------------------------------------------------------------------------
 * General: releases all resources taken by the main thread.
 *          if an application wishes to clean all the resources taken by SIP Stack 
 *          main thread, it should call this function. This function should be called 
 *          only after ALL RADVISION's toolkits have been destructed
 * Return Value: RvStatus.
 * ----------------------------------------------------------------------------------
 * Arguments:
 * Input:   -
 * Output:  -
 ***********************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMidMainThreadClean();

#ifdef __cplusplus
}
#endif

#endif /*RV_SIP_MID_H*/
