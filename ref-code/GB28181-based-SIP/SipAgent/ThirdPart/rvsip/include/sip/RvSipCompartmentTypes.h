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
 *                              <RvSipCompartmentTypes.h>
 *
 * The RvSipCompartmentTypes.h file contains all type definitions for the  module.
 *
 * includes:
 * 1.Handle Type definitions
 * 2.Compartment Type definitions
 *
 *
 *    Author                         Date
 *    ------                        ------
 *    Dikla Dror                  Nov 2003
 *********************************************************************************/

#ifndef RV_SIP_COMPARTMENT_TYPES_H
#define RV_SIP_COMPARTMENT_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                           */
/*-----------------------------------------------------------------------*/
#include "RV_SIP_DEF.h"

/*-----------------------------------------------------------------------*/
/*                     COMMON TYPE DEFINITIONS                           */
/*-----------------------------------------------------------------------*/

/*
 * RvSipCompartmentMgrHandle
 * ---------------------------------------------------------------------------
 * Declaration of handle to a  compartment Manager instance. The manager
 * object manages all the module compartments and its handle is needed in all
 * manager related API such as creation of new  comapartments.
 */
RV_DECLARE_HANDLE(RvSipCompartmentMgrHandle);


/*
 * RvSipCompartmentHandle
 * ---------------------------------------------------------------------------
 * Declaration of a  Compartment handle.  Compartment is needed
 * in all  compartments API function and is used to reference the
 * correct compartment object.
 */
RV_DECLARE_HANDLE(RvSipCompartmentHandle);

/*
 * RvSipAppCompartmentHandle
 * ---------------------------------------------------------------------------
 * Declaration  of application handle to a  Compartment. This handle
 * is used by the application in order to associate sip stack
 * Compartment objects with application  Compartment object. The
 * application gives the application handle when a new  Compartment is
 * created.
 */

RV_DECLARE_HANDLE(RvSipAppCompartmentHandle);

#ifdef __cplusplus
}
#endif

#endif /* END OF: #ifndef RV_SIP_COMPARTMENT_TYPES_H*/


