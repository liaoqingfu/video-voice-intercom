/***********************************************************************
        Copyright (c) 2002 RADVISION Ltd.
************************************************************************
NOTICE:
This document contains information that is confidential and proprietary
to RADVISION Ltd.. No part of this document may be reproduced in any
form whatsoever without written prior approval by RADVISION Ltd..

RADVISION Ltd. reserve the right to revise this publication and make
changes without obligation to notify any person of such revisions or
changes.
***********************************************************************/

#ifndef __PAYLOAD_H
#define __PAYLOAD_H


#include "rverror.h"
#include "rtp.h"


#ifdef __cplusplus
extern "C" {
#endif


typedef enum
{
    PCMU  =  0,
    G7231 =  4,
    PCMA  =  8,
    G722  =  9,
    G728  = 15,
    G729  = 18,
    H261  = 31,
    H263  = 34

} payload_e;



/* == G.711 U-Law == */

RVAPI
RvInt32 RVCALLCONV rtpPCMUPack(
        IN  void *      buf,
        IN  RvInt32     len,
        IN  rtpParam *  p,
        IN  void     *  param);

RVAPI
RvInt32 RVCALLCONV rtpPCMUUnpack(
        OUT  void *      buf,
        IN   RvInt32     len,
        OUT  rtpParam *  p,
        OUT  void *      param);

RVAPI
RvInt32 RVCALLCONV rtpPCMUGetHeaderLength(void);


/* == G.711 A-Law == */

RVAPI
RvInt32 RVCALLCONV rtpPCMAPack(
        IN  void *      buf,
        IN  RvInt32     len,
        IN  rtpParam *  p,
        IN  void     *  param);

RVAPI
RvInt32 RVCALLCONV rtpPCMAUnpack(
        OUT  void *      buf,
        IN   RvInt32     len,
        OUT  rtpParam *  p,
        OUT  void *      param);

RVAPI
RvInt32 RVCALLCONV rtpPCMAGetHeaderLength(void);


/* == G.722 == */

RVAPI
RvInt32 RVCALLCONV rtpG722Pack(
        IN  void *      buf,
        IN  RvInt32     len,
        IN  rtpParam *  p,
        IN  void     *  param);


RVAPI
RvInt32 RVCALLCONV rtpG722Unpack(
        OUT  void *      buf,
        IN   RvInt32     len,
        OUT  rtpParam *  p,
        OUT  void *      param);

RVAPI
RvInt32 RVCALLCONV rtpG722GetHeaderLength(void);

/* == G.728 == */

RVAPI
RvInt32 RVCALLCONV rtpG728Pack(
        IN  void *      buf,
        IN  RvInt32     len,
        IN  rtpParam *  p,
        IN  void     *  param);


RVAPI
RvInt32 RVCALLCONV rtpG728Unpack(
        OUT  void *      buf,
        IN   RvInt32     len,
        OUT  rtpParam *  p,
        OUT  void *      param);

RVAPI
RvInt32 RVCALLCONV rtpG728GetHeaderLength(void);

/* == G.729 == */

RVAPI
RvInt32 RVCALLCONV rtpG729Pack(
        IN  void *      buf,
        IN  RvInt32     len,
        IN  rtpParam *  p,
        IN  void     *  param);


RVAPI
RvInt32 RVCALLCONV rtpG729Unpack(
        OUT  void *      buf,
        IN   RvInt32     len,
        OUT  rtpParam *  p,
        OUT  void *      param);

RVAPI
RvInt32 RVCALLCONV rtpG729GetHeaderLength(void);


/* == G.723.1 == */
RVAPI
RvInt32 RVCALLCONV rtpG7231Pack(
        IN  void *      buf,
        IN  RvInt32     len,
        IN  rtpParam *  p,
        IN  void     *  param);

RVAPI
RvInt32 RVCALLCONV rtpG7231Unpack(
        OUT  void *      buf,
        IN   RvInt32     len,
        OUT  rtpParam *  p,
        OUT  void *      param);

RVAPI
RvInt32 RVCALLCONV rtpG7231GetHeaderLength(void);


/* == H.261 == */

typedef struct
{
    int sBit;
    int eBit;
    int i;
    int v;
    int gobN;
    int mbaP;
    int quant;
    int hMvd;
    int vMvd;
} H261param;

RVAPI
RvInt32 RVCALLCONV rtpH261Pack(
        IN  void *      buf,
        IN  RvInt32     len,
        IN  rtpParam *  p,
        IN  void     *  param);

RVAPI
RvInt32 RVCALLCONV rtpH261Unpack(
        OUT  void*buf,
        IN   RvInt32     len,
        OUT  rtpParam*p,
        OUT  void *      param);

RVAPI
RvInt32 RVCALLCONV rtpH261GetHeaderLength(void);


/* == H.263 == */

typedef struct
{
    int f;
    int p;
    int sBit;
    int eBit;
    int src;
    int i;
    int a;
    int s;
    int dbq;
    int trb;
    int tr;
    int gobN;
    int mbaP;
    int quant;
    int hMv1;
    int vMv1;
    int hMv2;
    int vMv2;
} H263param;

RVAPI
RvInt32 RVCALLCONV rtpH263Pack(
        IN  void *      buf,
        IN  RvInt32     len,
        IN  rtpParam *  p,
        IN  void     *  param);

RVAPI
RvInt32 RVCALLCONV rtpH263Unpack(
        OUT  void *      buf,
        IN   RvInt32     len,
        OUT  rtpParam *  p,
        OUT  void *      param);


RVAPI
RvInt32 RVCALLCONV rtpH263GetHeaderLength(void);



/* == H.263a == */

typedef struct
{
    int f;
    int p;
    int sBit;
    int eBit;
    int src;
    int i;
    int u;
    int a;
    int s;
    int dbq;
    int trb;
    int tr;
    int gobN;
    int mbaP;
    int quant;
    int hMv1;
    int vMv1;
    int hMv2;
    int vMv2;
} H263aparam;

RVAPI
RvInt32 RVCALLCONV rtpH263aPack(
        IN  void *      buf,
        IN  RvInt32     len,
        IN  rtpParam *  p,
        IN  void     *  param);

RVAPI
RvInt32 RVCALLCONV rtpH263aUnpack(
        OUT  void *      buf,
        IN   RvInt32     len,
        OUT  rtpParam *  p,
        OUT  void *      param);


RVAPI
RvInt32 RVCALLCONV rtpH263aGetHeaderLength(void);



/* ================================================== */
/* ==== DTMF inBand (via RTP payload) - RFC 2833 ==== */
/* ================================================== */

  /*
  There are two types/options of transmitting DTMF in RTP payload:

   1) identify the frequency component of the voice-band signals, and
      than transmit them 'as is' to their destination.
   2) identify the tones and translate them into an event-name. the
      event-name is a logical description of DTMF tones, fax-related tones etc.
      the receiver, on this case, produces the signals appropriate to
      the event name that was received.

  each of these options has a different method for transmiting the information inside
  an RTP payload. since they are not both mandatory, an endpoint may indicate
  support for receiving these tones/events by including the following flags in the
  terminal capability set (TCS):

  (*) 'receiveRTPAudioTelephoneEventCapability' - for event-name method.
  (*) 'receiveRTPAudioToneCapability' - for tones-frequency method.

  at this phase, as noted in the MRD (and as recommended in RFC2833) the mandatory
  telephone events are the following DTMF's:

                0,1,2,3,4,5,6,7,8,9,#,*,A,B,C,D.

  the events will be identified by an enumeration.
  */

/* DTMF event name. according to RFC2833
   - the order is very important! do not change the order! */
typedef enum
{
    rtpDtmfEvent_0,
    rtpDtmfEvent_1,
    rtpDtmfEvent_2,
    rtpDtmfEvent_3,
    rtpDtmfEvent_4,
    rtpDtmfEvent_5,
    rtpDtmfEvent_6,
    rtpDtmfEvent_7,
    rtpDtmfEvent_8,
    rtpDtmfEvent_9,
    rtpDtmfEvent_asterisk,
    rtpDtmfEvent_pound,
    rtpDtmfEvent_A,
    rtpDtmfEvent_B,
    rtpDtmfEvent_C,
    rtpDtmfEvent_D,
    rtpDtmfEvent_NoEvent

} rtpDtmfEvent;


/************************************************************************
 * rtpDtmfEventParams
 * This struct holds all the information needed/received for RFC2833
 * packet with event mode
 ***********************************************************************/
typedef struct
{
    rtpDtmfEvent event;         /* type of current event received or to-send */
    RvBool       end;           /* the E (end bit) - indicating the last packet of this event */
    RvUint8      volume;        /* volume of current event received or to-send */
    RvUint32     duration;      /* duration of current event received or to-send */

} rtpDtmfEventParams;



/************************************************************************
 * rtpDtmfEventPack
 *
 * purpose: set the payload format, for sending DTMF events inband,
 *          as described in RFC2833, section 3.5.
 *
 * input  : buf - buffer pointer that will be sent
 *          len - length of the buffer.
 *          p - RTP header default parameters.
 *          param - a structure containing the required parameters for DTMF events.
 * output : none
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
RVAPI
RvInt32 RVCALLCONV rtpDtmfEventPack(
        IN  void *      buf,
        IN  RvInt32     len,
        IN  rtpParam *  p,
        IN  void     *  param);


/************************************************************************
 * rtpDtmfEventUnpack
 *
 * purpose: evaluates the DTMF events from the received packed.
 *
 * input  : len - length of the buffer.
 * output : buf - the received buffer.
 *          p - RTP header parameters that were received.
 *          param - the received parameters for DTMF events.
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
RVAPI
RvInt32 RVCALLCONV rtpDtmfEventUnpack(
        OUT  void *      buf,
        IN   RvInt32     len,
        OUT  rtpParam *  p,
        OUT  void *      param);


/******************************************************************************
 * rtpDtmfEventGetHeaderLength
 * ----------------------------------------------------------------------------
 * General: Returns the length of a DTMF event payload.
 *          This length should be placed as the len parameter to rtpWrite().
 *
 * Return Value: Length of a DTMF event payload.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  none.
 * Output: none.
 *****************************************************************************/
RVAPI
RvInt32 RVCALLCONV rtpDtmfEventGetHeaderLength(void);


/* == Telephony Tones according to RFC2833 == */

/************************************************************************
 * rtpDtmfTonesParams
 * This struct holds all the information needed/received for RFC2833
 * packet with tone mode
 ***********************************************************************/
typedef struct
{
    RvUint16     modulation;        /* The modulation frequency, in Hz */
    RvBool       T;                 /* the 'T' bit. True means divide by 3 */
    RvUint8      volume;            /* volume of current tone received or to-send */
    RvUint32     duration;          /* duration of current tone received or to-send */
    RvUint16     *freqList;         /* the list of frequencies to send/received */
    RvUint32     freqListLength;    /* length of the frequencies list */

} rtpDtmfTonesParams;


/************************************************************************
 * rtpDtmfTonesPack
 *
 * purpose: set the payload format, for sending telephony tones inband,
 *          as described in RFC2833, section 4.4.
 *
 * input  : buf - buffer pointer that will be sent
 *          len - length of the buffer.
 *          p - RTP header default parameters.
 *          param - a structure containing the required parameters for telephony tones.
 * output : none
 * return : Non-negative value on success
 *          Negative value on failure
 *
 * Important: one of the members of the 'rtpDtmfTonesParams' struct(param) is a pointer
 * notes      to an integer array, that symbolizes the frequencies that form the tone.
 *            the array is not limited in size, since a single tone can contain any
 *            number of frequencies. this is the reason there is a member 'freqListLength'
 *            in the struct as well.
 ************************************************************************/
RVAPI
RvInt32 RVCALLCONV rtpDtmfTonesPack(
        IN  void *      buf,
        IN  RvInt32     len,
        IN  rtpParam *  p,
        IN  void     *  param);


/************************************************************************
 * rtpDtmfTonesUnpack
 *
 * purpose: evaluates the telephony tones from the received packed.
 *
 * input  : len - length of the buffer.
 * output : buf - the received buffer.
 *          p - RTP header parameters that were received.
 *          param - the received parameters for telephony tones.
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
RVAPI
RvInt32 RVCALLCONV rtpDtmfTonesUnpack(
        OUT  void *      buf,
        IN   RvInt32     len,
        OUT  rtpParam *  p,
        OUT  void *      param);


/************************************************************************
 * rtpDtmfTonesGetByIndex
 *
 * purpose: find the requested frequency in the received message.
 *
 * input  : buf - the received buffer.
 *          index - index of the frequency inside the frequency list.
 *          p - RTP header parameters that were received.
 *          param - the received parameters for telephony tones.
 * output : frequency - The requested frequency
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
RVAPI
RvStatus RVCALLCONV rtpDtmfTonesGetByIndex(
        IN   void *      buf,
        IN   RvUint32    index,
        IN   rtpParam *  p,
        IN   void *      param,
        OUT  RvUint16 *  frequency);



/* ========================================================= */
/* ==== Annex Q & H.281 - Far End Camera Control (FECC) ==== */
/* ========================================================= */
/*
    The FECC protocol is designed to function along with H.224, in order to
    allow a multi-point video conferencing to be individually controlled from
    any video terminal.
*/

typedef enum
{
    rtpAnnexQProceduresStartAction = 1,
    rtpAnnexQProceduresContinueAction = 2,
    rtpAnnexQProceduresStopAction = 3,
    rtpAnnexQProceduresSelectVideoSource = 4,
    rtpAnnexQProceduresVideoSourceSwitched = 5,
    rtpAnnexQProceduresStoreAsPreset = 6,
    rtpAnnexQProceduresActivatePreset = 7

} rtpAnnexQProcedures;


typedef enum
{
    rtpAnnexQMoveDisable = 0,  /* = 00(binary) */
    rtpAnnexQMoveLeftDownOut = 2, /* = 10(binary) */
    rtpAnnexQMoveRightUpIn = 3  /* = 11(binary) */

} rtpAnnexQMoveCamera;


/************************************************************************
 * rtpAnnexQActions
 * This struct holds the various possible positions for a camera. the user
 * can request to move the camera in several positions concurrently.
 ***********************************************************************/
typedef struct
{
    rtpAnnexQMoveCamera pan;
    rtpAnnexQMoveCamera tilt;
    rtpAnnexQMoveCamera zoom;
    rtpAnnexQMoveCamera focus;

} rtpAnnexQActions;


/************************************************************************
 * AnnexQCameraMode
 * This struct holds the user request for camera method of imaging.
 ***********************************************************************/
typedef struct
{
    RvBool stillImage;
    RvBool doubleResolutionStillImage;

} AnnexQCameraMode;


/************************************************************************
 * rtpAnnexQParam
 * This struct holds all the information needed/received for H.281
 * packet with FECC capability request.
 ***********************************************************************/
typedef struct
{
    rtpAnnexQProcedures procedure;
    rtpAnnexQActions    action;
    RvUint8             timeOut;
    RvUint8             videoSource;
    AnnexQCameraMode    mode;
    RvUint8             preset;

} rtpAnnexQParam;


/************************************************************************
 * rtpAnnexQMessagePack
 *
 * purpose: set the payload format, for sending Far end camera commands inband,
 *          as described in H.281.
 *          Several AnnexQ commands can be sent in the same packet. Using
 *          rtpAnnexQMessagePack on the same buffer for several such messages
 *          places them in reverse order.
 *
 * input  : buf - buffer pointer that will be sent
 *          len - length of the buffer.
 *          p - RTP header default parameters.
 *          param - a structure containing the required parameters for FECC.
 * output : none
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
RVAPI
RvInt32 RVCALLCONV rtpAnnexQMessagePack(
        IN  void *      buf,
        IN  RvInt32     len,
        IN  rtpParam *  p,
        IN  void     *  params);


/************************************************************************
 * rtpAnnexQMessageUnpack
 *
 * purpose: evaluates the FECC commands from the received packed.
 *
 * input  : len - length of the buffer.
 * output : buf - the received buffer.
 *          p - RTP header parameters that were received.
 *          param - the received parameters for FECC.
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
RVAPI
RvInt32 RVCALLCONV rtpAnnexQMessageUnpack(
        OUT  void *      buf,
        IN   RvInt32     len,
        OUT  rtpParam *  p,
        OUT  void *      params);



#ifdef __cplusplus
}
#endif

#endif  /* __PAYLOAD_H */
