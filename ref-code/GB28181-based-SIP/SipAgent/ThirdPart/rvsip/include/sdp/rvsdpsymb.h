/************************************************************************
Filename    : rvsdpsymb.h
Description : Sdp Symbols Table
The constant are defined in such a way that identical literal symbols
will have the same numerical constant
************************************************************************
                Copyright (c) 1999 RADVision Inc.
************************************************************************
NOTICE:
This document contains information that is proprietary to RADVision LTD.
No part of this publication may be reproduced in any form whatsoever
without written prior approval by RADVision LTD..

RADVision LTD. reserves the right to revise this publication and make
changes without obligation to notify any person of such revisions or
changes.
************************************************************************
************************************************************************
$Revision: 1.0$
$Date:3/29/00$
$Author:Dan E.$
************************************************************************/
#ifndef RVSDPSYMB_H
#define RVSDPSYMB_H

#include "rvsdptypes.h"
#include "rverror.h"

#if defined(__cplusplus)
extern "C" {
#endif

/* Return codes */
typedef enum
{
    RV_SDPSTATUS_OK = RV_OK,
    RV_SDPSTATUS_ENCODEFAILBUF = -1,
    RV_SDPSTATUS_ALLOCFAIL = -2,
    RV_SDPSTATUS_PARSEFAIL = -3
} RvSdpStatus;

/* Undef to disable "bad syntax" reparsing */
/*#define RV_SDP_CHECK_BAD_SYNTAX*/

/* Undef to disable the string fields used to hold unknown constant values */
#define RV_SDPSYMB_USESTRING

#define RV_SDPSYMB_BASE_            100

#define RV_SDPSYMB_IN               RV_SDPSYMB_BASE_+1
#define RV_SDPSYMB_ATM              RV_SDPSYMB_IN+1
#define RV_SDPSYMB_LOCAL            RV_SDPSYMB_ATM+1
#define RV_SDPSYMB_OTHER            RV_SDPSYMB_LOCAL+1
#define RV_SDPSYMB_TN               RV_SDPSYMB_OTHER+1
#define RV_SDPSYMB_ANY              RV_SDPSYMB_TN+1
#define RV_SDPSYMB_IGNORE           RV_SDPSYMB_ANY+1

#define RV_SDPSYMB_IP4              RV_SDPSYMB_IGNORE+1
#define RV_SDPSYMB_IP6              RV_SDPSYMB_IP4+1
#define RV_SDPSYMB_EPN              RV_SDPSYMB_IP6+1		/* = 110 */
#define RV_SDPSYMB_NSAP             RV_SDPSYMB_EPN+1
#define RV_SDPSYMB_E164             RV_SDPSYMB_NSAP+1
#define RV_SDPSYMB_GWID             RV_SDPSYMB_E164+1
#define RV_SDPSYMB_ALIAS            RV_SDPSYMB_GWID+1
#define RV_SDPSYMB_RFC2543          RV_SDPSYMB_ALIAS+1

#define RV_SDPSYMB_AUDIO            RV_SDPSYMB_RFC2543 +1
#define RV_SDPSYMB_NAS              RV_SDPSYMB_AUDIO+1
#define RV_SDPSYMB_VIDEO            RV_SDPSYMB_NAS+1
#define RV_SDPSYMB_APP              RV_SDPSYMB_VIDEO+1
#define RV_SDPSYMB_DATA             RV_SDPSYMB_APP+1		/* = 120 */
#define RV_SDPSYMB_IMAGE            RV_SDPSYMB_DATA+1
#define RV_SDPSYMB_CONTROL          RV_SDPSYMB_IMAGE+1

#define RV_SDPSYMB_RTPAVP           RV_SDPSYMB_CONTROL+1
#define RV_SDPSYMB_ATMAVP           RV_SDPSYMB_RTPAVP+1
#define RV_SDPSYMB_UDP              RV_SDPSYMB_ATMAVP+1
#define RV_SDPSYMB_TCP              RV_SDPSYMB_UDP+1
#define RV_SDPSYMB_AAL1ATMF         RV_SDPSYMB_TCP+1
#define RV_SDPSYMB_AAL1ITU          RV_SDPSYMB_AAL1ATMF+1
#define RV_SDPSYMB_AAL1CUSTOM       RV_SDPSYMB_AAL1ITU+1
#define RV_SDPSYMB_AAL2ATMF         RV_SDPSYMB_AAL1CUSTOM+1	/* = 130 */
#define RV_SDPSYMB_AAL2ITU          RV_SDPSYMB_AAL2ATMF+1
#define RV_SDPSYMB_AAL2CUSTOM       RV_SDPSYMB_AAL2ITU+1
#define RV_SDPSYMB_AAL5ATMF         RV_SDPSYMB_AAL2CUSTOM+1
#define RV_SDPSYMB_AAL5ITU          RV_SDPSYMB_AAL5ATMF+1
#define RV_SDPSYMB_AAL5CUSTOM       RV_SDPSYMB_AAL5ITU+1
#define RV_SDPSYMB_H323C            RV_SDPSYMB_AAL5CUSTOM+1

#define RV_SDPSYMB_CLEAR            RV_SDPSYMB_H323C+1
#define RV_SDPSYMB_BASE64           RV_SDPSYMB_CLEAR+1
#define RV_SDPSYMB_URI              RV_SDPSYMB_BASE64+1
#define RV_SDPSYMB_PROMPT           RV_SDPSYMB_URI+1		/* = 140 */

#define RV_SDPSYMB_DAY              RV_SDPSYMB_PROMPT+1
#define RV_SDPSYMB_HOUR             RV_SDPSYMB_DAY+1
#define RV_SDPSYMB_MONTH            RV_SDPSYMB_HOUR+1
#define RV_SDPSYMB_SECOND           RV_SDPSYMB_MONTH+1

#define RV_SDPSYMB_SENDONLY         RV_SDPSYMB_SECOND+1
#define RV_SDPSYMB_RECVONLY         RV_SDPSYMB_SENDONLY+1
#define RV_SDPSYMB_SENDRECV         RV_SDPSYMB_RECVONLY+1

#define RV_SDPSYMB_VCCI             RV_SDPSYMB_SENDRECV+1
#define RV_SDPSYMB_CID              RV_SDPSYMB_VCCI+1
#define RV_SDPSYMB_BCG              RV_SDPSYMB_CID+1		/* = 150 */
#define RV_SDPSYMB_PORT             RV_SDPSYMB_BCG+1
#define RV_SDPSYMB_VPI              RV_SDPSYMB_PORT+1
#define RV_SDPSYMB_VCI              RV_SDPSYMB_VPI+1
#define RV_SDPSYMB_VPCI             RV_SDPSYMB_VCI+1

#define RV_SDPSYMB_MAX_             RV_SDPSYMB_VPCI+1

/**************** SDP network type ************/
typedef enum {
    RV_SDPNETTYPE_NOTSET    = 0,
    RV_SDPNETTYPE_IN        = RV_SDPSYMB_IN,                    /*  IN     */
    RV_SDPNETTYPE_ATM       = RV_SDPSYMB_ATM,                   /*  ATM    */
    RV_SDPNETTYPE_LOCAL     = RV_SDPSYMB_LOCAL,                 /*  LOCAL  */
    RV_SDPNETTYPE_OTHER     = RV_SDPSYMB_OTHER,                 /*  Other  */
    RV_SDPNETTYPE_TN        = RV_SDPSYMB_TN,                    /*  TN     */
    RV_SDPNETTYPE_ANY       = RV_SDPSYMB_ANY,                   /*  ANY    */
    RV_SDPNETTYPE_IGNORE    = RV_SDPSYMB_IGNORE,                /*  IGNORE */
    RV_SDPNETTYPE_UNKNOWN   = RV_SDPSYMB_MAX_ + 1
} RvSdpNetType;

/**************** SDP addresses ************/
typedef enum {
    RV_SDPADDRTYPE_NOTSET    = 0,
    RV_SDPADDRTYPE_IP4       = RV_SDPSYMB_IP4,                  /*  IP4    */
    RV_SDPADDRTYPE_IP6       = RV_SDPSYMB_IP6,                  /*  IP6    */
    RV_SDPADDRTYPE_ENDPOINT  = RV_SDPSYMB_EPN,                  /*  epn    */
    RV_SDPADDRTYPE_NSAP      = RV_SDPSYMB_NSAP,                 /*  nsap   */
    RV_SDPADDRTYPE_E164      = RV_SDPSYMB_E164,                 /*  e164   */
    RV_SDPADDRTYPE_GWID      = RV_SDPSYMB_GWID,                 /*  GWID   */
    RV_SDPADDRTYPE_ALIAS     = RV_SDPSYMB_ALIAS,                /*  ALIAS  */
    RV_SDPADDRTYPE_RFC2543   = RV_SDPSYMB_RFC2543,              /*  RFC2543*/
    RV_SDPADDRTYPE_ANY       = RV_SDPSYMB_ANY,                  /*  ANY    */
    RV_SDPADDRTYPE_IGNORE    = RV_SDPSYMB_IGNORE,               /*  IGNORE */
    RV_SDPADDRTYPE_UNKNOWN   = RV_SDPSYMB_MAX_ + 2
} RvSdpAddrType;

/**************** SDP media types ************/
typedef enum {
    RV_SDPMEDIATYPE_NOTSET   = 0,
    RV_SDPMEDIATYPE_AUDIO    = RV_SDPSYMB_AUDIO,                /*  audio  */
    RV_SDPMEDIATYPE_NAS      = RV_SDPSYMB_NAS,                  /*  nas    */
    RV_SDPMEDIATYPE_VIDEO    = RV_SDPSYMB_VIDEO,                /*  video    */
    RV_SDPMEDIATYPE_APP      = RV_SDPSYMB_APP,                  /*  application */
    RV_SDPMEDIATYPE_DATA     = RV_SDPSYMB_DATA,                 /*  data    */
    RV_SDPMEDIATYPE_IMAGE    = RV_SDPSYMB_IMAGE,                /*  image   */
    RV_SDPMEDIATYPE_CONTROL  = RV_SDPSYMB_CONTROL,              /*  control */
    RV_SDPMEDIATYPE_UNKNOWN  = RV_SDPSYMB_MAX_ + 3
} RvSdpMediaType;

/**************** SDP media protocols ********/

typedef enum {
    RV_SDPPROTOCOL_NOTSET       = 0,
    RV_SDPPROTOCOL_RTP          = RV_SDPSYMB_RTPAVP ,           /*  RTP/AVP  */
    RV_SDPPROTOCOL_LOCAL        = RV_SDPSYMB_LOCAL  ,           /*  LOCAL  */
    RV_SDPPROTOCOL_ATM          = RV_SDPSYMB_ATMAVP ,           /*  atm/avp  */
    RV_SDPPROTOCOL_UDP          = RV_SDPSYMB_UDP,
    RV_SDPPROTOCOL_TCP          = RV_SDPSYMB_TCP,
    RV_SDPPROTOCOL_AAL1ATMF     = RV_SDPSYMB_AAL1ATMF,
    RV_SDPPROTOCOL_AAL1ITU      = RV_SDPSYMB_AAL1ITU,
    RV_SDPPROTOCOL_AAL1CUSTOM   = RV_SDPSYMB_AAL1CUSTOM,
    RV_SDPPROTOCOL_AAL2ATMF     = RV_SDPSYMB_AAL2ATMF,
    RV_SDPPROTOCOL_AAL2ITU      = RV_SDPSYMB_AAL2ITU,
    RV_SDPPROTOCOL_AAL2CUSTOM   = RV_SDPSYMB_AAL2CUSTOM,
    RV_SDPPROTOCOL_AAL5ATMF     = RV_SDPSYMB_AAL5ATMF,
    RV_SDPPROTOCOL_AAL5ITU      = RV_SDPSYMB_AAL5ITU,
    RV_SDPPROTOCOL_AAL5CUSTOM   = RV_SDPSYMB_AAL5CUSTOM,
    RV_SDPPROTOCOL_H323C        = RV_SDPSYMB_H323C,
    RV_SDPPROTOCOL_UNKNOWN      = RV_SDPSYMB_MAX_ + 4
} RvSdpProtocol;

/**************** SDP encryption methods ********/
typedef enum
{
    RV_SDPENCRMTHD_NOTSET = 0,
    RV_SDPENCRMTHD_CLEAR  = RV_SDPSYMB_CLEAR,    /* clear  */
    RV_SDPENCRMTHD_BASE64 = RV_SDPSYMB_BASE64,  /* base64 */
    RV_SDPENCRMTHD_URI    = RV_SDPSYMB_URI,     /* uri    */
    RV_SDPENCRMTHD_PROMPT = RV_SDPSYMB_PROMPT,  /* prompt */
    RV_SDPENCRMTHD_UNKNOWN  = RV_SDPSYMB_MAX_ + 5
} RvSdpEncrMethod;

/**************** Typed-time units ********/
typedef enum
{
    RV_SDPTIMETYPE_DAY      = RV_SDPSYMB_DAY,       /* "d" */
    RV_SDPTIMETYPE_HOUR     = RV_SDPSYMB_HOUR,      /* "h" */
    RV_SDPTIMETYPE_MONTH    = RV_SDPSYMB_MONTH,     /* "m" */
    RV_SDPTIMETYPE_SECOND   = RV_SDPSYMB_SECOND     /* "s" */
} RvSdpTimeUnit;

/**************** Send mode  ********/
typedef enum
{
    RV_SDPCONNECTMODE_NOTSET    = 0,
    RV_SDPCONNECTMODE_SENDONLY = RV_SDPSYMB_SENDONLY,       /* "sendonly" */
    RV_SDPCONNECTMODE_RECVONLY = RV_SDPSYMB_RECVONLY,       /* "recvonly" */
    RV_SDPCONNECTMODE_SENDRECV = RV_SDPSYMB_SENDRECV        /* "sendrecv" */
} RvSdpConnectionMode;

/**************** VcId Type  ********/
typedef enum
{
    RV_SDPVCID_NOTSET       = 0,
    RV_SDPVCID_VCCI         = RV_SDPSYMB_VCCI,
    RV_SDPVCID_CID          = RV_SDPSYMB_CID,
    RV_SDPVCID_BCG          = RV_SDPSYMB_BCG,
    RV_SDPVCID_PORT         = RV_SDPSYMB_PORT,
    RV_SDPVCID_VPI          = RV_SDPSYMB_VPI,
    RV_SDPVCID_VCI          = RV_SDPSYMB_VCI,
    RV_SDPVCID_VPCI         = RV_SDPSYMB_VPCI,
    RV_SDPVCID_NSAP         = RV_SDPSYMB_NSAP,
    RV_SDPVCID_E164         = RV_SDPSYMB_E164,
    RV_SDPVCID_GWID         = RV_SDPSYMB_GWID,
    RV_SDPVCID_ALIAS        = RV_SDPSYMB_ALIAS,
    RV_SDPVCID_UNKNOWN      = RV_SDPSYMB_MAX_ + 6
} RvSdpVcId;

const char * rvSdpSymbolGetString(int value,RvSdpStatus* stat);

#if defined(__cplusplus)
}
#endif

#endif /* RVSDPSYMB_H */

