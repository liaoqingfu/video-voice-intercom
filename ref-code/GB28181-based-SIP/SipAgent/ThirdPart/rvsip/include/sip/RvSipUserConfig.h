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
 *                              <RvSipUserConfig.h>
 *
 * The file enables the user to configure the stack compilation flags.
 * The configuration flags defined here will override any compilation flag
 * supplied in the compilation process.
 *    Author                         Date
 *    ------                        ------
 *    Sarit Galanos                Jan-2004
 *********************************************************************************/

#ifndef _RV_SIP_USER_CONFIG
#define _RV_SIP_USER_CONFIG

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



/*Enabling   the SigComp module*/
/*
#define RV_SIGCOMP_ON
*/


/*Enabling the enhanced DNS feature*/
/*
#define RV_DNS_ENHANCED_FEATURES_SUPPORT
*/

/*Enabling usage of the deprecated core API. This is for backwards
  compatability only. For os services use the mid layer.*/
/*

#define RV_DEPRECATED_CORE

*/



/*
#define RV_SIP_PRIMITIVES
*/

/*
#define RV_SIP_OTHER_HEADER_ENCODE_SEPARATELY
*/

/*
#define RV_SIP_HIGH_AVAL_3_0
*/

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*#define _RV_SIP_USER_CONFIG*/

