
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
 *                              RvSipStack.h
 *
 *  This file provides headers for the stack manager module of the RADVISION SIP stack.
 *  It contains headers for the functions that initialize, construct and
 *  destructs the entire sip stack.
 *
 *    Author                         Date
 *    ------                        ------
 *  Oren Libis                    20-Nov-2000
 *********************************************************************************/


#ifndef _RV_SIP_STACK_H
#define _RV_SIP_STACK_H


#ifdef __cplusplus
extern "C" {
#endif


/*-----------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                           */
/*-----------------------------------------------------------------------*/
#include "RV_SIP_DEF.h"
#include "RvSipStackTypes.h"
#ifndef RV_SIP_PRIMITIVES
#include "RvSipCallLegTypes.h"
#include "RvSipRegClientTypes.h"
#include "RvSipSubscriptionTypes.h"
#endif /* RV_SIP_PRIMITIVES */
#include "RvSipAuthenticator.h"
#include "RvSipTransaction.h"
#include "RvSipTransport.h"
#include "RvSipCompartmentTypes.h"
#include "RvSipResourcesTypes.h"
#ifdef RV_SIGCOMP_ON
#include "RvSigComp.h"
#endif /* RV_SIGCOMP_ON */
/*-----------------------------------------------------------------------*/
/*                          TYPE DEFINITIONS                             */
/*-----------------------------------------------------------------------*/

#if !defined(RV_SIGCOMP_ON)
/* Declares a DUMMY handle to the SigComp Manager object in case of disabled feature*/
RV_DECLARE_HANDLE(RvSigCompMgrHandle);
#endif /* !defined(RV_SIGCOMP_ON) */


/*-----------------------------------------------------------------------*/
/*                          FUNCTIONS HEADERS                            */
/*-----------------------------------------------------------------------*/

/************************************************************************************
 * RvSipStackConstruct
 * ----------------------------------------------------------------------------------
 * General: Constructs and initializes the RADVISION SIP stack. This function allocates the
 *          required memory and constructs RADVISION SIP stack objects according to
 *          configuration parameters specified in the RvSipStackCfg structure. The function
 *          returns a handle to the Stack Manager. You need this handle in order to use the
 *          Stack Manager API functions.
 * Return Value: Returns RvStatus.
 * ----------------------------------------------------------------------------------
 * Arguments:
 * Input:   sizeOfCfg - The size of the configuration structure.
 *          pStackCfg     - Structure containing RADVISION SIP stack configuration parameters.
 *                          Values that were set to -1 will be replaced with a value calculated
 *                          by the stack. Invalid values will be replaced with the stack default
 *                          values.
 * Output:  hStack        - Handle to the Stack Manager.
 ***********************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipStackConstruct(
                                         IN    RvInt32               sizeOfCfg,
                                         INOUT RvSipStackCfg          *pStackCfg,
                                         OUT   RvSipStackHandle       *hStack);


/************************************************************************************
 * RvSipStackDestruct
 * ----------------------------------------------------------------------------------
 * General: Destructor. The function destructs all RADVISION SIP stack objects and frees all
 *          allocated memory.
 * Return Value: Returns RvStatus.
 * ----------------------------------------------------------------------------------
 * Arguments:
 * Input:   hStack         - Handle to the RADVISION SIP stack.
 * Output:  none
 ***********************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipStackDestruct(IN RvSipStackHandle hStack);

/***************************************************************************
 * RvSipStackSetAppHandle
 * ------------------------------------------------------------------------
 * General: Set an application handle to the Sip Stack instance. Setting a
 *          stack application handle can be useful
 *          when implementing a multiInstance applications
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hStack    - Handle to the stack.
 *            hAppStack - A new application handle to the stack
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipStackSetAppHandle (
                                      IN  RvSipStackHandle       hStack,
                                      IN  RvSipAppStackHandle    hAppStack);


/***************************************************************************
 * RvSipStackGetAppHandle
 * ------------------------------------------------------------------------
 * General: Returns the application handle of this stack instance
 * Return Value: RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hStack - Handle to the stack.
 * Output:     phAppStack     - The application handle of the stack instance.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipStackGetAppHandle (
                                      IN    RvSipStackHandle        hStack,
                                      OUT   RvSipAppStackHandle     *phAppStack);


#ifndef RV_SIP_PRIMITIVES
/************************************************************************************
 * RvSipStackGetCallLegMgrHandle
 * ----------------------------------------------------------------------------------
 * General: Gets the Call-Leg Manager handle. You need this handle in order to use the
 *          Call-leg API functions.
 * Return Value: Returns RvStatus.
 * ----------------------------------------------------------------------------------
 * Arguments:
 * Input:   hStack          - Handle to the RADVISION SIP stack.
 * Output:  phCallLegMgr     - Handle to the Call-Leg Manager.
 ***********************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipStackGetCallLegMgrHandle(
                                         IN    RvSipStackHandle       hStack,
                                         OUT   RvSipCallLegMgrHandle  *phCallLegMgr);
#endif /*#ifndef RV_SIP_PRIMITIVES */
/************************************************************************************
 * RvSipStackGetTransactionMgrHandle
 * ----------------------------------------------------------------------------------
 * General: Gets the Transaction Manager handle. You need this handle in order to use the
 *          Transaction API functions.
 * Return Value: Returns RvStatus.
 * ----------------------------------------------------------------------------------
 * Arguments:
 * Input:   hStack          - Handle to the RADVISION SIP stack.
 * Output:  phTranscMgr      - Handle to the Transaction Manager.
 ***********************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipStackGetTransactionMgrHandle(
                                         IN    RvSipStackHandle       hStack,
                                         OUT   RvSipTranscMgrHandle  *phTranscMgr);

/************************************************************************************
 * RvSipStackGetTransportMgrHandle
 * ----------------------------------------------------------------------------------
 * General: Gets the Transport Manager handle. You need this handle in order to use the
 *          Transport API functions and callbacks.
 * Return Value:RvStatus
 * ----------------------------------------------------------------------------------
 * Arguments:
 * Input:   hStack          - handle to the SIP Stack.
 * Output:  phTransportMgr   - handle to the Transport Manager.
 ***********************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipStackGetTransportMgrHandle(
                                       IN    RvSipStackHandle          hStack,
                                       OUT   RvSipTransportMgrHandle  *phTransportMgr);

/************************************************************************************
 * RvSipStackGetTransmitterMgrHandle
 * ----------------------------------------------------------------------------------
 * General: get the transmitter manager handle.You need this handle in order to use the
 *          Transmitter API functions.
 * Return Value:RvStatus
 * ----------------------------------------------------------------------------------
 * Arguments:
 * Input:   hStack          - handle to the sip stack.
 * Output:  phTrxMgr        - handle to the Transmitter Manager.
 ***********************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipStackGetTransmitterMgrHandle(
                                         IN    RvSipStackHandle           hStack,
                                         OUT   RvSipTransmitterMgrHandle *phTrxMgr);

/************************************************************************************
 * RvSipStackGetMsgMgrHandle
 * ----------------------------------------------------------------------------------
 * General: Gets the Message Manager handle. You need this handle in order to use
 *          the Message API functions.
 * Return Value: Returns RvStatus.
 * ----------------------------------------------------------------------------------
 * Arguments:
 * Input:   hStack         - Handle to the SIP stack.
 * Output:  phMsgMgr        - Handle to the Message Manager.
 ***********************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipStackGetMsgMgrHandle(
                                  IN    RvSipStackHandle  hStack,
                                  OUT   RvSipMsgMgrHandle *phMsgMgr);
#ifndef RV_SIP_PRIMITIVES
/************************************************************************************
 * RvSipStackGetRegClientMgrHandle
 * ----------------------------------------------------------------------------------
 * General: Gets the Register-client Manager handle. You need this handle in order to use
 *          the Register-client API functions.
 * Return Value: Returns RvStatus.
 * ----------------------------------------------------------------------------------
 * Arguments:
 * Input:   hStack          - Handle to the RADVISION SIP stack.
 * Output:  phRegClientMgr   - Handle to the Register-client Manager.
 ***********************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipStackGetRegClientMgrHandle(
                                  IN    RvSipStackHandle         hStack,
                                  OUT   RvSipRegClientMgrHandle *phRegClientMgr);
#endif /* #ifndef RV_SIP_PRIMITIVES */
/************************************************************************************
 * RvSipStackGetLogHandle
 * ----------------------------------------------------------------------------------
 * General: Gets the Log handle of the RADVISION SIP stack object.
 * Return Value: Returns RvStatus.
 * ----------------------------------------------------------------------------------
 * Arguments:
 * Input:   hStack          - Handle to the RADVISION SIP stack.
 * Output:  phLog            - Handle to the Log.
 ***********************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipStackGetLogHandle(
                                         IN    RvSipStackHandle       hStack,
                                         OUT   RV_LOG_Handle          *phLog);

#if defined(RV_DEPRECATED_CORE)
/************************************************************************************
 * RvSipStackGetSeliHandle
 * ----------------------------------------------------------------------------------
 * General: This function can be used only if the stack is compiled with
 *          RV_DEPRECATED_CORE compilation flag which means that the application
 *          is using the stack deprecated core implementation. 
 *          This function returns the seli handle. The seli handle is used by 
 *          some of the deprecated core functions, specifically select related functions.
 *          Using the deprecated core is not recommended.
 *          For low level functionality please use the mid layer API.
 *          
 * Return Value:RvStatus
 * ----------------------------------------------------------------------------------
 * Arguments:
 * Input:   hStack          - handle to the stack manager.
 * Output:  phSeli          - handle to the seli.
 ***********************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipStackGetSeliHandle(
                                         IN    RvSipStackHandle           hStack,
                                         OUT   RV_SELI_Handle             *phSeli);


/************************************************************************************
 * RvSipStackGetTimerPoolHandle
 * ----------------------------------------------------------------------------------
 * General: This function can be used only if the sip stack is compiled with
 *          RV_DEPRECATED_CORE compilation flag which means that the application
 *          is using the deprecated core implementation. 
 *          However, this function is deprecated and will always return NULL.
 *          If you are using the deprecated core to set timers you must first
 *          call the TIMER pool initialization functions to allocate the timer pool.
 *          only then you will be able to set timers.
 *          Using the deprecated core is not recommended.
 *          For low level functionality please use the mid layer API.
 * Return Value:
 *          RvStatus
 * ----------------------------------------------------------------------------------
 * Arguments:
 * Input:   hStack          - Handle to the stack manager.
 * Output:  phTimerPool      - Will always return NULL.
 ***********************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipStackGetTimerPoolHandle(
                                         IN    RvSipStackHandle           hStack,
                                         OUT   RV_TIMER_PoolHandle        *phTimerPool);

#endif /*defined(RV_DEPRECATED_CORE)*/


/************************************************************************************
 * RvSipStackGetAuthenticatorHandle
 * ----------------------------------------------------------------------------------
 * General: Gets the Authenticator object handle. You need this handle in order to use the
 *          Authenticator API.
 * Return Value: Returns RvStatus.
 * ----------------------------------------------------------------------------------
 * Arguments:
 * Input:   hStack          - Handle to the RADVISION SIP stack.
 * Output:  phAuth           - Handle to the Authenticator object handle.
 ***********************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipStackGetAuthenticatorHandle(
                                         IN    RvSipStackHandle           hStack,
                                         OUT   RvSipAuthenticatorHandle  *phAuth);
#ifndef RV_SIP_PRIMITIVES
/************************************************************************************
 * RvSipStackGetSubsMgrHandle
 * ----------------------------------------------------------------------------------
 * General: Gets the Subscription manager object handle. You need this handle in
 *          order to use the Subscription API.
 * Return Value:RvStatus
 * ----------------------------------------------------------------------------------
 * Arguments:
 * Input:   hStack          - Handle to the SIP stack.
 * Output:  phSubsMgr        - Handle to the Subscription manager object.
 ***********************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipStackGetSubsMgrHandle(
                                  IN    RvSipStackHandle    hStack,
                                  OUT   RvSipSubsMgrHandle *phSubsMgr);
#endif /* #ifndef RV_SIP_PRIMITIVES */
/************************************************************************************
 * RvSipStackGetCompartmentMgrHandle
 * ----------------------------------------------------------------------------------
 * General: Gets the Compartment manager object handle. You need this handle
 *          in order to use the Compartment API.
 * Return Value:RvStatus
 * ----------------------------------------------------------------------------------
 * Arguments:
 * Input:   hStack          - Handle to the SIP stack.
 * Output:  phCompartmentMgr - Handle to the Compartment manager object.
 ***********************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipStackGetCompartmentMgrHandle(
                   IN    RvSipStackHandle           hStack,
                   OUT   RvSipCompartmentMgrHandle *phCompartmentMgr);

/************************************************************************************
 * RvSipStackSetNewLogFilters
 * ----------------------------------------------------------------------------------
 * General: set the new log filters for the specified module in run time.
 *          note that the new filters are not only the ones that we want to change,
 *          but they are a new set of filters that the module is going to use.
 * Return Value:
 *          RV_OK          - log filters were set successfully
 *          RV_ERROR_INVALID_HANDLE    - the handle to the stack was NULL
 *          RV_ERROR_BADPARAM - the register id of this module is not used
 * ----------------------------------------------------------------------------------
 * Arguments:
 * Input:   hStack         - Handle to stack instance
 *          eModule        - the module whose filters are going to be changed
 *                           If the module name is RVSIP_CORE the function will change
 *                           the logging level for all the core modules.
 *          filters        - the new set of filters
 * Output:  none
 ***********************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipStackSetNewLogFilters(
                                                IN RvSipStackHandle  hStack,
                                                IN RvSipStackModule  eModule,
                                                IN RvInt32          filters);



/************************************************************************************
 * RvSipStackIsLogFilterExist
 * ----------------------------------------------------------------------------------
 * General: Checks the existence of a filter for a specified module.
 * Return Value: Returns RV_TRUE if a filter exists for the specified module. Otherwise, the
 *               function returns RV_FALSE.
 * ----------------------------------------------------------------------------------
 * Arguments:
 * Input:   hStack         - Handle to the RADVISION SIP stack object
 *          module         - The module for which the existence of a filter is being checked.
 *          filter         - The filter being checked.
 * Output:  none
 ***********************************************************************************/
RVAPI RvBool RVCALLCONV RvSipStackIsLogFilterExist(
                                              IN RvSipStackHandle  hStack,
                                              IN RvSipStackModule  module,
                                              IN RvSipLogFilters   filter);


/************************************************************************************
 * RvSipStackGetResources
 * ----------------------------------------------------------------------------------
 * General: Gets the status of resources used by the RADVISION SIP stack. The function is used
 *          only for the Call-Leg, Message, Transaction, Register-client and Stack Manager
 *          modules. You should specify the module name and give an appropriate
 *          structure. For example, if you wish to get the Register-client resources, the
 *          module parameter should be set to RVSIP_REGCLIENT and the pResources
 *          parameter should be of type RvSipRegClientResources.
 * Return Value: Returns RvStatus.
 * ----------------------------------------------------------------------------------
 * Arguments:
 * Input:   hStack         - Handle to the RADVISION SIP stack object.
 *          module         - The module for which resource status is being checked.
 *          pResources     - The resources in use by the specified module.
 * Output:  none
 ***********************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipStackGetResources(
                                              IN RvSipStackHandle      hStack,
                                              IN RvSipStackModule      module,
                                              OUT void                 *pResources);

#ifdef SIP_DEBUG
/************************************************************************************
 * RvSipStackGetStatistics
 * ----------------------------------------------------------------------------------
 * General: Gets the statistics about number of messages sent and received by the stack.
 *          You must supply here a pointer to a valid RvSipStackStatistics structure.
 *          The stack will fill this structure with the current statistics.
 * Return Value: Returns RvStatus.
 * ----------------------------------------------------------------------------------
 * Arguments:
 * Input:   hStack         - Handle to the RADVISION SIP stack object.
 * Output:  pStatistics    - The structure to be filled with the current statistics.
 ***********************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipStackGetStatistics(
                                           IN    RvSipStackHandle       hStack,
                                           OUT   RvSipStackStatistics  *pStatistics);

#endif /*SIP_DEBUG*/

/************************************************************************************
 * RvSipStackMgrIsEnhancedDnsFeatureEnabled
 * ----------------------------------------------------------------------------------
 * General: Returns RV_TRUE if SIP stack was compiled with RV_DNS_ENHANCED_FEATURES_SUPPORT
 * flag.
 * Return Value: returns RV_TRUE if SIP stack was compiled with RV_DNS_ENHANCED_FEATURES_SUPPORT
 * flag and RV_FALSE otherwise.
 * ----------------------------------------------------------------------------------
 * Arguments:
 * Input:   none
 * Output:  none
 ***********************************************************************************/
RVAPI RvBool RvSipStackMgrIsEnhancedDnsFeatureEnabled(void);

/************************************************************************************
 * RvSipStackMgrIsTlsFeatureEnabled
 * ----------------------------------------------------------------------------------
 * General: Returns RV_TRUE if SIP stack was compiled with RV_CFLAG_TLS
 * flag.
 * Return Value: returns RV_TRUE if SIP stack was compiled with RV_CFLAG_TLS
 * flag and RV_FALSE otherwise.
 * ----------------------------------------------------------------------------------
 * Arguments:
 * Input:   none
 * Output:  none
 ***********************************************************************************/
RVAPI RvBool RvSipStackMgrIsTlsFeatureEnabled(void);

/************************************************************************************
 * RvSipStackGetVersion
 * ----------------------------------------------------------------------------------
 * General: Gets the current version of the RADVISION SIP stack.
 * Return Value: Returns the version number.
 * ----------------------------------------------------------------------------------
 * Arguments:
 * Input:   none
 * Output:  none
 ***********************************************************************************/
RVAPI RvChar * RVCALLCONV RvSipStackGetVersion(void);



/************************************************************************************
 * RvSipStackProcessEvents
 * ----------------------------------------------------------------------------------
 * General:  Checks for events and processes them as they occur. The function is usually
 *           used for console applications.
 * Return Value: (-)
 * ----------------------------------------------------------------------------------
 * Arguments:
 * Input:   (-)
 * Output:  (-)
 ***********************************************************************************/
RVAPI void RVCALLCONV RvSipStackProcessEvents(void);

/************************************************************************
 * RvSipStackSelect
 * purpose: Block on the select() interface on some operating systems.
 *          Use parallel interfaces on other operating systems.
 *          An application should write a "while (1) RvSipStackSelect();"
 *          as its main loop.
 * input  : none
 * output : none
 * return : RV_OK on success, negative value on failure
 ************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipStackSelect(void);

/******************************************************************************
 * RvSipStackSelectUntil
 * ----------------------------------------------------------------------------
 * General: Block on the select() interface on some operating systems.
 *          Use parallel interfaces on other operating systems.
 *          This function also gives the application the ability to give a
 *          maximum delay to block for.
 *
 * Return Value: RV_OK on success, negative value on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  delay    - Maximum time to block on milliseconds.
 * Output: None.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipStackSelectUntil(IN RvUint32 delay);


/************************************************************************************
 * RvSipStackInitCfg
 * ----------------------------------------------------------------------------------
 * General: Initializes the RvSipStackCfg  structure. This structure is given to the
 *          RvSipStackConstruct function and it is used to initialize the stack.
 *          The RvSipStackInitCfg function relates to two types of parameters found in
 *          the RvSipStackCfg structure:
 *          (A) Parameters that influence the value of other parameters
 *          (B) Parameters that are influenced by the value of other parameters.
 *          The RvSipStackInitCfg will set all parameters of type A to default values
 *          and parameters of type B to -1.
 *          For example the maxCallLegs is of type A and will be set to 10.
 *          The maxTransaction is of type B and is set to -1.
 *          When calling the RvSipStackConstruct function all the B type parameters
 *          will be calculated using the values found in the A type paraemeters.
 *          if you change the A type values the B type values will be changed
 *          accordingly.
 *
 * Return Value: (-)
 * ----------------------------------------------------------------------------------
 * Arguments:
 * Input:  sizeOfCfg - The size of the configuration structure.
 * output: pStackCfg - The configuration structure containing the RADVISION SIP stack default values.
 *                     values.
 ***********************************************************************************/
RVAPI void RvSipStackInitCfg(IN  RvInt32      sizeOfCfg,
                             OUT RvSipStackCfg *pStackCfg);


#ifndef RV_SIP_PRIMITIVES
/************************************************************************************
 * RvSipStackIsSessionTimerSupported
 * ----------------------------------------------------------------------------------
 * General: Returns weather the stack supports the session timer feature.
 *          bIsSupported output parameter will be set to RV_TRUE if the
 *          stack supported list includs the "timer" option tag. Otherwise it will be
 *          set to RV_FALSE.
 * Return Value: Returns RvStatus.
 * ----------------------------------------------------------------------------------
 * Arguments:
 * Input:    hStack         - Handle to the RADVISION SIP stack.
 * Output:   bIsSupported   - RV_TRUE if session timer is supported, RV_FALSE otherwise.
 ***********************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipStackIsSessionTimerSupported(
                                           IN    RvSipStackHandle      hStack,
                                           OUT   RvBool               *bIsSupported);

/***************************************************************************
 * RvSipStackIsReplacesSupported
 * ------------------------------------------------------------------------
 * General: Returns weather the stack supports the replaces feature.
 *          bIsSupported output parameter will be set to RV_TRUE if the
 *          stack supported list includs the "replaces" option tag. Otherwise it will be
 *          set to RV_FALSE.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hStack         - The stack handle.
 * Output:  pbIsSupported  - RV_TRUE if replaces is supported, RV_FALSE otherwise.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipStackIsReplacesSupported(
                                    IN  RvSipStackHandle            hStack,
                                    OUT RvBool                    *pbIsSupported);

#endif /*#ifndef RV_SIP_PRIMITIVES */

/***************************************************************************
 * RvSipStackSetSigCompMgrHandle
 * ------------------------------------------------------------------------
 * General: Stores the SigComp manager handle in the stack manager.
 *          This function must be called only after the stack was constructed
 *          successfully. You get the SigComp manager when the SigComp module
 *          is constructed. The sip stack will use the SigComp manager to compress
 *          and decompress SIP messages. 
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hStack      - The stack handle.
 *            hSigCompMgr - Handle of the SigComp manager.
 * Output:    -
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipStackSetSigCompMgrHandle(
                      IN  RvSipStackHandle        hStack,
                      IN  RvSigCompMgrHandle      hSigCompMgr);

#ifdef __cplusplus
}
#endif

#endif  /*END OF: define _RV_SIP_STACK_H*/
