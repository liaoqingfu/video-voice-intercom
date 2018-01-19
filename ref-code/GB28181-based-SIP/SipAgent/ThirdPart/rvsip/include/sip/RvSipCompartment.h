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
 *                              <RvSipCompartment.h>
 *
 * The  Compartment functions of the RADVISION SIP stack enable you to
 * create and manage  Compartment objects, attach/detach to/from
 * compartments and control the compartment parameters.
 *
 *
 *  Compartment API functions are grouped as follows:
 * The  Compartment Manager API
 * ------------------------------------
 * The  Compartment manager is in charge of all the compartments. It is used
 * to create new compartments.
 *
 * The  Compartment API
 * ----------------------------
 * A compartment represents a SIP  Compartment as defined in RFC3320.
 * This compartment unifies a group of SIP Stack objects such as CallLegs or
 * Transacions that is identify by a compartment ID when sending request
 * through a compressor entity. Using the API, the user can initiate compartments,
 * or destruct it. Functions to set and access the compartment fields are also
 * available in the API.
 *
 *    Author                         Date
 *    ------                        ------
 *    Dikla Dror                  Nov 2003
 *********************************************************************************/

#ifndef RV_SIP_COMPARTMENT_H
#define RV_SIP_COMPARTMENT_H

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                           */
/*-----------------------------------------------------------------------*/
#include "RV_SIP_DEF.h"
#include "rpool_API.h"
#include "RvSipCompartmentTypes.h"
    
/*-----------------------------------------------------------------------*/
/*                      COMPARTMENT MANAGER  API                         */
/*-----------------------------------------------------------------------*/

/***************************************************************************
 * RvSipCompartmentMgrCreateCompartment
 * ------------------------------------------------------------------------
 * General: Creates a new  Compartment. The creation triggers an automatic
 *          attachment to the newly created compartment.
 *
 * Return Value: RV_ERROR_INVALID_HANDLE -  The handle to the manager is invalid.
 *               RV_ERROR_NULLPTR -     The pointer to the compartment handle
 *                                   is invalid.
 *               RV_ERROR_OUTOFRESOURCES - Compartment list is full,compartment
 *                                   was not created.
 *               RV_OK -        Success.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:  hCompartmentMgr - Handle to the  compartment manager
 *         hAppCompartment - Application handle to the compartment.
 * Output: phCompartment   - RADVISION SIP stack handle to the 
 *                           compartment.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipCompartmentMgrCreateCompartment(
                IN  RvSipCompartmentMgrHandle hCompartmentMgr,
                IN  RvSipAppCompartmentHandle hAppCompartment,
                OUT RvSipCompartmentHandle   *phCompartment);


/***************************************************************************
 * RvSipCompartmentMgrGetStackInstance
 * ------------------------------------------------------------------------
 * General: Returns the handle to the stack instance to which this
 *          compartment manager belongs to.
 *
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hCompartmentMgr - Handle to the stack compartment manager.
 * Output:    phStackInstance - A valid pointer which will be updated with a
 *                              handle to the stack instance.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipCompartmentMgrGetStackInstance(
                      IN   RvSipCompartmentMgrHandle hCompartmentMgr,
                      OUT  void                    **phStackInstance);


/*-----------------------------------------------------------------------*/
/*                             COMPARTMENT API                           */
/*-----------------------------------------------------------------------*/

/***************************************************************************
 * RvSipCompartmentDetach
 * ------------------------------------------------------------------------
 * General: Detaches from a  Compartment. If the compartment is not
 *          used by any of the stack objects (Call-Leg/Transaction etc.)
 *          or even by the application it's physically deleted. Otherwise 
 *          the termination will be only logically.
 * Return Value:RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hCompartment - Handle to the  compartment the application
 *                          wishes to detach from.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipCompartmentDetach(
                        IN RvSipCompartmentHandle hCompartment);

/***************************************************************************
 * RvSipCompartmentAttach
 * ------------------------------------------------------------------------
 * General: Attaches to a  Compartment. This function enables the
 *          application to attach a compartment that WASN'T created by it
 *          (An automatic attachment takes place while creating manually
 *          new compartment). This attachment keeps the compartment "alive"
 *          until the compartment is detached by all the objects that are
 *          part of it and by the application.
 * Return Value:RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hCompartment - Handle to the  compartment the application
 *                          wishes to attach to.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipCompartmentAttach(
                        IN RvSipCompartmentHandle hCompartment);

/***************************************************************************
 * RvSipCompartmentSetAppHandle
 * ------------------------------------------------------------------------
 * General: Sets the  Compartment application handle. Usually the
 *          application replaces handles with the stack in the
 *          RvSipCompartmentMgrCreateCompartment() API function.
 *          This function is used if the application wishes to set a new
 *          application handle.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hCompartment    - Handle to the Compartment.
 *            hAppCompartment - A new application handle to the Compartment.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipCompartmentSetAppHandle(
                   IN  RvSipCompartmentHandle     hCompartment,
                   IN  RvSipAppCompartmentHandle  hAppCompartment);

/***************************************************************************
 * RvSipCompartmentGetAppHandle
 * ------------------------------------------------------------------------
 * General: Returns the application handle of this Compartment.
 * Return Value: RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hCompartment     - Handle to the Compartment.
 * Output:     phAppCompartment - A pointer to application handle of the Compartment
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipCompartmentGetAppHandle(
                   IN  RvSipCompartmentHandle     hCompartment,
                   OUT RvSipAppCompartmentHandle *phAppCompartment);

#ifdef __cplusplus
}
#endif

#endif /* END OF: #ifndef RV_SIP_COMPARTMENT_H*/


