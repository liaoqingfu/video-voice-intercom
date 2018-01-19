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

#ifndef __RTCP_H
#define __RTCP_H

#include "rvtypes.h"


#ifdef __cplusplus
extern "C" {
#endif


#ifndef __RTP_H
RV_DECLARE_HANDLE(HRTCPSESSION);
#define RVVXDAPI RVAPI
#define VXDCALLCONV RVCALLCONV
#define CALLCONVC
#endif


#define ERR_RTCP_GENERALERROR     -350   /* general error */
#define ERR_RTCP_SSRCCOLLISION    -351   /* ssrc collision */
#define ERR_RTCP_ILLEGALSSRC      -352   /* an illegal ssrc was specified */
#define ERR_RTCP_ILLEGALSDES      -353   /* an illegal sdes was specified */
#define ERR_RTCP_ILLEGALPACKET    -354   /* illegal RTCP pkt encountered */


/*h.e 30.04.01*/
typedef void (RVCALLCONV *LPRTCPEVENTHANDLER)(
        IN HRTCPSESSION,
        IN void * context,
        IN RvUint32 ssrc);
/*===*/

typedef RvBool (RVCALLCONV *LPSSRCENUM)(
        IN  HRTCPSESSION  hRTCP,
        IN  RvUint32      ssrc);


typedef struct {
    RvBool      valid; /* RV_TRUE if this struct contains valid information. */
    RvUint32    mNTPtimestamp; /* Most significant 32bit of NTP timestamp */
    RvUint32    lNTPtimestamp; /* Least significant 32bit of NTP timestamp */
    RvUint32    timestamp; /* RTP timestamp */
    RvUint32    packets; /* Total number of RTP data packets transmitted by the sender
                            since transmission started and up until the time this SR packet
                            was generated. */
    RvUint32    octets; /* The total number of payload octets (not including header or padding */
} RTCPSRINFO;

typedef struct {
    RvBool      valid; /* RV_TRUE if this struct contains valid information. */
    RvUint32    fractionLost; /* The fraction of RTP data packets from source specified by
                                 SSRC that were lost since previous SR/RR packet was sent. */
    RvUint32    cumulativeLost; /* Total number of RTP data packets from source specified bu
                                   SSRC that have been lost since the beginning of reception. */
    RvUint32    sequenceNumber; /* Sequence number that was received from the source specified
                                   by SSRC. */
    RvUint32    jitter; /* Estimate of the statistical variance of the RTP data packet inter
                           arrival time. */
    RvUint32    lSR; /* The middle 32 bits of the NTP timestamp received. */
    RvUint32    dlSR; /* Delay since the last SR. */
} RTCPRRINFO;

typedef struct {
    RvBool      selfNode; /* RV_TRUE if this tructure contains information about a source
                             created by this session. In this case, only sr and cname fields
                             are relevant in the structure. */
    RTCPSRINFO  sr; /* Sender report information. For selfNode==RV_TRUE, this field contains
                       the report that will be sent to other sources. Otherwise, this is the
                       last report received from remote sources. */
    RTCPRRINFO  rrFrom; /* Receiver report informatino. The last, if any, receiver report
                           received from the source identified by the ssrc parameter about the
                           source that created this session. */
    RTCPRRINFO  rrTo; /* Local receiver report information. Information about the source
                         identifier by the ssrc parameter about the source that created this
                         session. */
    char        cname[255]; /* cname of the source that is identified by the ssrc parameter */
} RTCPINFO;



                      /* == Basic RTCP Functions == */


RVAPI
RvInt32 RVCALLCONV rtcpInit(void);


RVAPI
RvInt32 RVCALLCONV rtcpInitEx(RvUint32);

RVAPI
RvInt32 RVCALLCONV rtcpEnd(void);


/************************************************************************************
 * rtcpSetLocalAddress
 * description: Set the local address to use for calls to rtcpOpenXXX functions.
 *              This parameter overrides the value given in rtcpInitEx() for all
 *              subsequent calls.
 * input: ip    - Local IP address to use
 * output: none.
 * return value: Non-negative value on success
 *               Negative value on failure
 ***********************************************************************************/
RVAPI
int RVCALLCONV rtcpSetLocalAddress(IN RvUint32 ip);


RVAPI
RvInt32 RVCALLCONV rtcpSetRTCPRecvEventHandler(
    IN HRTCPSESSION         hRTCP,
    IN LPRTCPEVENTHANDLER   rtcpCallback,
    IN void *               context);


RVAPI
int RVCALLCONV rtcpGetAllocationSize(
    IN  int sessionMembers);

/************************************************************************************
 * rtcpOpenFrom
 * description: Opens an RTCP session in the memory that the application allocated.
 * input: ssrc        - Synchronization source value for the RTCP session.
 *        port        - The UDP port number to be used for the RTCP session.
 *        cname       - CNAME to use
 *        maxSessionMembers - Maximum number of different SSRC that can be handled
 *        buffer      - Application allocated buffer with a value no less than the
 *                      value returned by the function rtpGetAllocationSize().
 *        bufferSize  - size of the buffer.
 * output: none.
 * return value: If no error occurs, the function returns the handle for the opened RTP
 *               session. Otherwise, it returns NULL.
 ***********************************************************************************/
RVAPI
HRTCPSESSION RVCALLCONV rtcpOpenFrom(
    IN  RvUint32    ssrc,
    IN  RvUint16    port,
    IN  char *      cname,
    IN  int         maxSessionMembers,
    IN  void *      buffer,
    IN  int         bufferSize);

RVAPI
HRTCPSESSION RVCALLCONV rtcpOpen(
        IN  RvUint32    ssrc,
        IN  RvUint16    port,
        IN  char *      cname);

RVAPI
RvInt32 RVCALLCONV rtcpClose(
        IN  HRTCPSESSION  hRCTP);

RVAPI
void RVCALLCONV rtcpSetRemoteAddress(
        IN  HRTCPSESSION  hRTCP,
        IN  RvUint32      ip,
        IN  RvUint16      port);

RVAPI
RvInt32 RVCALLCONV rtcpStop(
        IN  HRTCPSESSION  hRTCP);


RVAPI
RvInt32 RVCALLCONV rtcpRTPPacketRecv(
        IN  HRTCPSESSION  hRTCP,
        IN  RvUint32      ssrc,
        IN  RvUint32      localTimestamp,
        IN  RvUint32      myTimestamp,
        IN  RvUint16      sequence);

RVAPI
RvInt32 RVCALLCONV rtcpRTPPacketSent(
        IN  HRTCPSESSION  hRTCP,
        IN  RvInt32       bytes,
        IN  RvUint32      timestamp);

RVAPI
RvUint16 RVCALLCONV rtcpGetPort(
        IN  HRTCPSESSION  hRCTP);


                   /* == ENDS: Basic RTCP Functions == */



                    /* == Accessory RTCP Functions == */


RVAPI
RvBool RVCALLCONV rtcpCheckSSRCCollision(
        IN  HRTCPSESSION  hRTCP);

/* ouch! */
#define rtcpEnumParticipients  rtcpEnumParticipants

RVAPI
RvBool RVCALLCONV rtcpEnumParticipants(
        IN  HRTCPSESSION  hRTCP,
        IN  LPSSRCENUM    enumerator);

RVAPI
RvInt32 RVCALLCONV rtcpGetSourceInfo(
        IN   HRTCPSESSION hRTCP,
        IN   RvUint32     ssrc,
        OUT  RTCPINFO*    info);

RVAPI
RvInt32 RVCALLCONV rtcpSetGroupAddress(
        IN  HRTCPSESSION  hRTCP,
        IN  RvUint32      ip);

RVAPI
RvInt32 RVCALLCONV rtcpGetSSRC(
        IN  HRTCPSESSION  hRTCP);

RVAPI
RvInt32 RVCALLCONV rtcpSetSSRC(
        IN  HRTCPSESSION  hRTCP,
        IN  RvUint32      ssrc);

                 /* == ENDS: Accessory RTCP Functions == */

RVAPI
RvInt32 RVCALLCONV rtcpGetEnumNext(
                IN  HRTCPSESSION  hRTCP,
                IN  RvInt32       prev,
                IN  RvInt32 *     ssrc);


RVAPI
RvInt32 RVCALLCONV rtcpGetEnumFirst(
                IN  HRTCPSESSION  hRTCP,
                IN  RvInt32 *     ssrc);


#ifdef __cplusplus
}
#endif

#endif  /* __RTCP_H */
