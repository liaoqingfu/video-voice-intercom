/******************************************************************************
Filename    :rvsdpprsaux.h
Description :SDP parser auxiliary (reduction) functions

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
$Date:7/18/99$
$Author:Dan Elbert$
******************************************************************************/

#ifndef RV_SDPENC_H
#define RV_SDPENC_H

#include "rvsdpmsg.h"
#include "rvstrstream.h"

#if !defined(RV_SDP_DECLSPEC)
#define RV_SDP_DECLSPEC
#endif

#if defined(__cplusplus)
extern "C" {
#endif

RV_SDP_DECLSPEC RvBool rvSdpMsgEncode(RvSdpMsg * sdp,RvStrStream * o_str);
RV_SDP_DECLSPEC char * rvSdpMsgEncodeToBuf(RvSdpMsg * sdp,char * buf,int len,RvSdpStatus * stat);

#if defined(__cplusplus)
}
#endif

#endif /* RV_SDPENC_H */
