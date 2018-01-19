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
 *                              <RvSipResourcesTypes.h>
 *
 *
 *
 *    Author                         Date
 *    ------                        ------
 *    Sarit Mekler                  Nov 2000
 *********************************************************************************/


#ifndef RV_SIP_RESOURCES_TYPES_H
#define RV_SIP_RESOURCES_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                           */
/*-----------------------------------------------------------------------*/
#include "RV_SIP_DEF.h"
#include "RV_ADS_DEF.h"


/*-----------------------------------------------------------------------*/
/*                          TYPE DEFINITIONS                             */
/*-----------------------------------------------------------------------*/


/*
 * RvSipResource
 * --------------------
 * A general resource struct, used by all modules
 */
typedef struct
{
    RvUint32       numOfAllocatedElements;
    RvUint32       currNumOfUsedElements;
    RvUint32       maxUsageOfElements;
} RvSipResource;

#ifndef RV_SIP_PRIMITIVES
/*
 * RvSipCallLegResources
 * --------------------
 * The resources of the call module.
 */

typedef struct
{
    RvSipResource   calls;
    RvSipResource   transcLists;
    RvSipResource   transcHandles;
} RvSipCallLegResources;

/*
 * RvSipRegClientResources
 * --------------------
 * The resources of the reg-client module..
 */
typedef struct
{
    RvSipResource   regClients;
} RvSipRegClientResources;

#endif /* RV_SIP_PRIMITIVES */
/*
 * RvSipTransportResources
 * --------------------
 * Defines the resources of the Transport module.
 */
typedef struct
{
    RvSipResource   connections;
    RvSipResource   pQueueElements;
    RvSipResource   pQueueEvents;
    RvSipResource   readBuffers;
    RvSipResource   connHash;
    RvSipResource   ownersHash;
    RvSipResource   tlsSessions;
    RvSipResource   tlsEngines;
    RvSipResource   oorEvents;
} RvSipTransportResources;


/*
 * RvSipTranscResources
 * --------------------
 * The resources of the transaction module..
 */
typedef struct
{
    RvSipResource   transactions;
} RvSipTranscResources;


/*
 * RvSipStackResources
 * --------------------
 * The resources of the stack module.
 */
typedef struct
{
    RvSipResource   msgPoolElements;
    RvSipResource   generalPoolElements;
    RvSipResource   headerPoolElements;
    RvSipResource   timerPool;
} RvSipStackResources;

#ifndef RV_SIP_PRIMITIVES
/*
 * RvSipSubsResources
 * --------------------
 * Defines the resource structure of the Subscription module
 */

typedef struct
{
    RvSipResource   subscriptions;
    RvSipResource   notifications;
    RvSipResource   notifyLists;
} RvSipSubsResources;
#endif
/*
 * RvSipCompartmentResources
 * --------------------
 * Defines the resource structure of the Compartment module
 */
typedef struct {
    RvSipResource compartments;
} RvSipCompartmentResources;

/*
 * RvSipTransmitterResources
 * --------------------
 * Defines the resource structure of the Tranmistter module
 */
typedef struct {
    RvSipResource transmitters;
}RvSipTransmitterResources;



#ifdef __cplusplus
}
#endif


#endif /* END OF: #ifndef RV_SIP_RESOURCES_TYPES_H */
