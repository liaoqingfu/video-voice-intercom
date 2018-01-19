/*

NOTICE:
This document contains information that is proprietary to RADVision LTD..
No part of this publication may be reproduced in any form whatsoever without
written prior approval by RADVision LTD..

RADVision LTD. reserves the right to revise this publication and make changes
without obligation to notify any person of such revisions or changes.

*/

/******************************************************************************
 *                       RvSipMsgTypes.h                                      *
 *                                                                            *
 * This file defines all the handles, and the enumuration types, for using    *
 * the message APIs.                                                          *                                                                                                  *
 *                                                                            *
 *                                                                            *
 *      Author           Date                                                 *
 *     ------           ------------                                          *
 *      Ofra             Nov.2000                                             *
 ******************************************************************************/


#ifndef RVSIPTYPES_H
#define RVSIPTYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                           */
/*-----------------------------------------------------------------------*/
#include "RV_SIP_DEF.h"

#define UNDEFINED -1

/*-----------------------------------------------------------------------*/
/*                          TYPE DEFINITIONS                             */
/*-----------------------------------------------------------------------*/

                            /* address definitions */
/*
 * RvSipAddressHandle
 * ----------------------
 * Handle of the sip address object
 */
RV_DECLARE_HANDLE(RvSipAddressHandle);


                            /* headers definitions */

/*
 * RvSipContactHeaderHandle
 * ----------------------
 * Handle of the contact header object
 */
RV_DECLARE_HANDLE(RvSipContactHeaderHandle);



/*
 * RvSipCSeqHeaderHandle
 * ----------------------
 * Handle of the CSeq header object
 */
RV_DECLARE_HANDLE(RvSipCSeqHeaderHandle);

/*
 * RvSipOtherHeaderHandle
 * ----------------------
 * Handle of the other header object
 */
RV_DECLARE_HANDLE(RvSipOtherHeaderHandle);

/*
 * RvSipPartyHeaderHandle
 * ----------------------
 * Handle of the party header object
 */
RV_DECLARE_HANDLE(RvSipPartyHeaderHandle);

/*
 * RvSipViaHeaderHandle
 * ----------------------
 * Handle of the allow header object
 */
RV_DECLARE_HANDLE(RvSipViaHeaderHandle);


/*
 * RvSipAuthenticationHeaderHandle
 * ----------------------
 * Handle of the authentication header object
 */
RV_DECLARE_HANDLE(RvSipAuthenticationHeaderHandle);

/*
* RvSipAuthorizationHeaderHandle
* ----------------------
* Handle of the authorization header object
*/
RV_DECLARE_HANDLE(RvSipAuthorizationHeaderHandle);

#ifndef RV_SIP_PRIMITIVES
/*
 * RvSipAllowHeaderHandle
 * ----------------------
 * Handle of the allow header object
 */
RV_DECLARE_HANDLE(RvSipAllowHeaderHandle);

/*
 * RvSipReferToHeaderHandle
 * ----------------------
 * Handle of the Refer-To header object
 */
RV_DECLARE_HANDLE(RvSipReferToHeaderHandle);

/*
 * RvSipReferredByHeaderHandle
 * ----------------------
 * Handle of the Referred-By header object
 */
RV_DECLARE_HANDLE(RvSipReferredByHeaderHandle);

/*
 * RvSipReplacesHeaderHandle
 * -------------------------
 * Handle of the Replaces header object
 */
RV_DECLARE_HANDLE(RvSipReplacesHeaderHandle);

/*
 * RvSipRSeqHeaderHandle
 * ----------------------
 * Handle of the RSeq header object
 */
RV_DECLARE_HANDLE(RvSipRSeqHeaderHandle);


/*
 * RvSipRAckHeaderHandle
 * ----------------------
 * Handle of the RAck header object
 */
RV_DECLARE_HANDLE(RvSipRAckHeaderHandle);

/*
 * RvSipBodyHandle
 * ----------------------
 * Handle of the Message Body object
 */
RV_DECLARE_HANDLE(RvSipBodyHandle);

/*
 * RvSipBodyPartHandle
 * ----------------------
 * Handle of the Message Body-Part object
 */
RV_DECLARE_HANDLE(RvSipBodyPartHandle);


/*
 * RvSipContentTypeHeaderHandle
 * ----------------------
 * Handle of the Content-Type header object
 */
RV_DECLARE_HANDLE(RvSipContentTypeHeaderHandle);

/*
 * RvSipContentDispositionHeaderHandle
 * ----------------------
 * Handle of the Content-Disposition header object
 */
RV_DECLARE_HANDLE(RvSipContentDispositionHeaderHandle);

/*
 * RvSipRetryAfterHeaderHandle
 * ----------------------
 * Handle of the retry-after header object
 */
RV_DECLARE_HANDLE(RvSipRetryAfterHeaderHandle);

/*
 * RvSipSubscriptionStateHeaderHandle
 * ----------------------
 * Handle of the Subscription-State header object
 */
RV_DECLARE_HANDLE(RvSipSubscriptionStateHeaderHandle);

/*
 * RvSipEventHeaderHandle
 * ----------------------
 * Handle of the Event header object
 */
RV_DECLARE_HANDLE(RvSipEventHeaderHandle);

/*
 * RvSipAllowEventsHeaderHandle
 * ----------------------
 * Handle of the Allow-Events header object
 */
RV_DECLARE_HANDLE(RvSipAllowEventsHeaderHandle);

/*
 * RvSipSessionExpiresHeaderHandle
 * ----------------------
 * Handle of the Session-Expires header object
 */
RV_DECLARE_HANDLE(RvSipSessionExpiresHeaderHandle);
/*
 * RvSipMinSEHeaderHandle
 * ----------------------
 * Handle of the Min-SE header object
 */
RV_DECLARE_HANDLE(RvSipMinSEHeaderHandle);

#endif /* RV_SIP_PRIMITIVES */

/*
 * RvSipDateHeaderHandle
 * ----------------------
 * Handle of the expires header object
 */
RV_DECLARE_HANDLE(RvSipDateHeaderHandle);

/*
 * RvSipExpiresHeaderHandle
 * ----------------------
 * Handle of the expires header object
 */
RV_DECLARE_HANDLE(RvSipExpiresHeaderHandle);

/*
 * RvSipRouteHopHeaderHandle
 * -----------------------------
 * Handle of the Route header object
 */

RV_DECLARE_HANDLE(RvSipRouteHopHeaderHandle);

        /* message definitions */
/*
 * RvSipMsgHandle
 * --------------
 * Handle of the message object
 */
RV_DECLARE_HANDLE(RvSipMsgHandle);

/*
 * RvSipHeadersListElemHandle
 * -----------------------------
 * Handle of the position of one element in the list of headers.
 * will be used only for the getting and setting of headers from the headers list.
 */

RV_DECLARE_HANDLE(RvSipHeaderListElemHandle);


        /* message manager definitions */
/*
 * RvSipMsgMgrHandle
 * --------------
 * Handle of the message manager object
 */
RV_DECLARE_HANDLE(RvSipMsgMgrHandle);

                /* enumurations definitions */

/*
 * RvSipMethodType
 * ---------------
 * defines the methods that are support in the SIP stack.
 */

typedef enum
{
    RVSIP_METHOD_UNDEFINED = -1, /* undefined method type. */
    RVSIP_METHOD_INVITE,         /* user or service is being invited to participate
                                    in a session. */
    RVSIP_METHOD_ACK,            /* confirmation that the client has received a final
                                    response to INVITE requset. */
    RVSIP_METHOD_BYE,            /* The user agent uses BYE to indicate to the server that
                                    it wishes to release the call. */
    RVSIP_METHOD_REGISTER,       /* The user agent client requests to register
                                    to a registerar server by the addresses sent
                                    in the Contact header of the REGISTER request*/
    RVSIP_METHOD_REFER,          /* Triggers the server to initiate a call with a
                                    third party. */
    RVSIP_METHOD_NOTIFY,         /* Notifies of an event occuring. */
    RVSIP_METHOD_OTHER,          /* not one of the above */
    RVSIP_METHOD_PRACK,
    RVSIP_METHOD_CANCEL,         /* cancel a request */
    RVSIP_METHOD_SUBSCRIBE       /* The user requests current state and state updates
                                    from a remote node */

} RvSipMethodType;



/*
 * RvSipTransport
 * -------------
 * determines the transport protocol to be use for sending
 * SIP requests and responses.
 */
typedef enum
{
    RVSIP_TRANSPORT_UNDEFINED = -1,  /* undefined transport. */
    RVSIP_TRANSPORT_UDP,             /* UDP  */
    RVSIP_TRANSPORT_TCP,             /* TCP  */
    RVSIP_TRANSPORT_SCTP,             /* SCTP */
    RVSIP_TRANSPORT_TLS,             /* TLS  */
    RVSIP_TRANSPORT_OTHER             /* not one of the above */
}RvSipTransport;

/*
 * RvSipAddressType
 * ----------------
 * Enumuration of the sip sddress types. will be use in the address object.
 */

typedef enum
{
    RVSIP_ADDRTYPE_UNDEFINED = -1,
    RVSIP_ADDRTYPE_ABS_URI,
    RVSIP_ADDRTYPE_URL
}RvSipAddressType;

/*
 * RvSipUrlScheme
 * --------------
 * Enumuration of the sip-url scheme.
 */

typedef enum
{
    RVSIP_URL_SCHEME_UNDEFINED = -1,
    RVSIP_URL_SCHEME_SIP,  /* "sip:".  a SIP URI  */
    RVSIP_URL_SCHEME_SIPS  /* "sips:". a secure URI*/
} RvSipUrlScheme;

/*
 * RvSipUrlLrParamType
 * --------------
 * Enumuration defines how is the lr parameter is kept in the sip address:
 * lr; lr=1; lr=true;
 */

typedef enum
{
    RVSIP_URL_LR_TYPE_UNDEFINED = -1,
    RVSIP_URL_LR_TYPE_EMPTY,   /* "lr;" */
    RVSIP_URL_LR_TYPE_1,       /* "lr=1;" */
    RVSIP_URL_LR_TYPE_TRUE     /* "lr=true;" */
} RvSipUrlLrType;


/*
 * RvSipUserParam determines the user info part in the SIP-URL.
 */
typedef enum
{
    RVSIP_USERPARAM_UNDEFINED = -1, /* no user parameter. */
    RVSIP_USERPARAM_PHONE,          /* indicates that the SIP URL contains a phone
                                       number */
    RVSIP_USERPARAM_IP,                /* indicates that the SIP URL contains either
                                       a host name or an IP address */
    RVSIP_USERPARAM_OTHER            /* not one of the above */
} RvSipUserParam;

/*
 * RvSipHeaderType
 * ---------------
 * defines the header type that stored in the
 * headers list in a SIP message.
 * The headers: To/From/CallId/Cseq/ContentLength/ContentType are stored in the
 * sip message by value and they are not part of the headers list.
 */
typedef enum
{
    RVSIP_HEADERTYPE_UNDEFINED = -1,
    RVSIP_HEADERTYPE_ALLOW,
    RVSIP_HEADERTYPE_CONTACT,
    RVSIP_HEADERTYPE_VIA,
    RVSIP_HEADERTYPE_EXPIRES,
    RVSIP_HEADERTYPE_DATE,
    RVSIP_HEADERTYPE_ROUTE_HOP, /* 5*/
    RVSIP_HEADERTYPE_AUTHENTICATION,
    RVSIP_HEADERTYPE_AUTHORIZATION,
    RVSIP_HEADERTYPE_REFER_TO,
    RVSIP_HEADERTYPE_REFERRED_BY,
    RVSIP_HEADERTYPE_CONTENT_DISPOSITION, /*10 */
    RVSIP_HEADERTYPE_RETRY_AFTER,
    RVSIP_HEADERTYPE_OTHER,
    RVSIP_HEADERTYPE_RSEQ,
    RVSIP_HEADERTYPE_RACK,
    RVSIP_HEADERTYPE_TO, /* 15 */
    RVSIP_HEADERTYPE_FROM,
    RVSIP_HEADERTYPE_CSEQ,
    RVSIP_HEADERTYPE_SUBSCRIPTION_STATE,
    RVSIP_HEADERTYPE_EVENT,
    RVSIP_HEADERTYPE_ALLOW_EVENTS, /* 20 */
    RVSIP_HEADERTYPE_SESSION_EXPIRES,
    RVSIP_HEADERTYPE_MINSE,
    RVSIP_HEADERTYPE_REPLACES,
    RVSIP_HEADERTYPE_CONTENT_TYPE /* 24 */
} RvSipHeaderType;

/* RvSipMsgType
 * ------------
 * determines the type of the message it could be requset or response.
 */
typedef enum
{
    RVSIP_MSG_UNDEFINED = -1,   /* Undefined Message Type  */
    RVSIP_MSG_REQUEST,          /* REQUSET Message Type  */
    RVSIP_MSG_RESPONSE          /* RESPONSE Message Type */

} RvSipMsgType;

/* RvSipHeadersLocation
 * --------------------
 * This enumuration is for the Header List member of message or
 * body part objects.
 * It indicates which header the user wishes to get.
 */

typedef enum
{
    RVSIP_FIRST_HEADER = 0,
    RVSIP_LAST_HEADER,
    RVSIP_NEXT_HEADER,
    RVSIP_PREV_HEADER

} RvSipHeadersLocation;


/* RvSipMsgHeadersOption
 * --------------------
 * This enumuration is for RvSipMsgGetHeaderExt,RvSipMsgGetHeaderByTypeExt,
 * RvSipMsgGetHeaderByNameExt API functions.
 * It defineses which type of headers the user wishes to get.
 * RVSIP_MSG_HEADERS_OPTION_LEGAL_SYNTAX - Only legal headers, with no syntax errors.
 * RVSIP_MSG_HEADERS_OPTION_ALL          - All headers, bad-syntax or not.
 */
typedef enum
{
    RVSIP_MSG_HEADERS_OPTION_UNDEFINED = -1,
    RVSIP_MSG_HEADERS_OPTION_LEGAL_SYNTAX,
    RVSIP_MSG_HEADERS_OPTION_ALL
} RvSipMsgHeadersOption;


/* RvSipAuthAlgorithm
 * --------------------
 * This enumuration is for the authentication algorithm type
 */
typedef enum {
    RVSIP_AUTH_ALGORITHM_UNDEFINED = -1,
    RVSIP_AUTH_ALGORITHM_MD5,
    RVSIP_AUTH_ALGORITHM_OTHER
}RvSipAuthAlgorithm;

/* RvSipAuthScheme
 * --------------------
 * This enumuration is for the authentication scheme
 */
typedef enum {
    RVSIP_AUTH_SCHEME_UNDEFINED = -1,
    RVSIP_AUTH_SCHEME_DIGEST,
    RVSIP_AUTH_SCHEME_OTHER
}RvSipAuthScheme;


/* RvSipAuthQopOption
 * --------------------
 * This enumuration is for the authentication scheme
 */
typedef enum {
    RVSIP_AUTH_QOP_UNDEFINED = -1,
    RVSIP_AUTH_QOP_OTHER,
    RVSIP_AUTH_QOP_AUTH_ONLY,
    RVSIP_AUTH_QOP_AUTHINT_ONLY,
    RVSIP_AUTH_QOP_AUTH_AND_AUTHINT
}RvSipAuthQopOption ;

/* RvSipAuthStale
 * --------------------
 * This enumuration is for the authentication stale parameter
 */
typedef enum {
    RVSIP_AUTH_STALE_UNDEFINED = -1,
    RVSIP_AUTH_STALE_FALSE,
    RVSIP_AUTH_STALE_TRUE
}RvSipAuthStale;

#ifndef RV_SIP_PRIMITIVES

/* RvSipMediaType
 * --------------------
 * This enumuration is used to indicate the media type of the message body.
 * The media type enumeration is found in the Content-Type header (The
 * Content-Type has the format of Content-Type: media type/media sub type).
 * When the media type is not set it has the value of RVSIP_MEDIATYPE_UNDEFINED
 */
typedef enum {
    RVSIP_MEDIATYPE_UNDEFINED = -1,
    RVSIP_MEDIATYPE_TEXT,
    RVSIP_MEDIATYPE_IMAGE,
    RVSIP_MEDIATYPE_AUDIO,
    RVSIP_MEDIATYPE_VIDEO,
    RVSIP_MEDIATYPE_APPLICATION,
    RVSIP_MEDIATYPE_MULTIPART,
    RVSIP_MEDIATYPE_MESSAGE,
    RVSIP_MEDIATYPE_OTHER

} RvSipMediaType;

/* RvSipMediaSubType
 * --------------------
 * This enumuration is used to indicate the media sub type of the message body.
 * The media sub type enumeration is found in the Content-Type header (The
 * Content-Type has the format of Content-Type: media type/media sub type).
 * When the media sub type is not set it has the value of
 * RVSIP_MEDIASUBTYPE_UNDEFINED
 */
typedef enum {
    RVSIP_MEDIASUBTYPE_UNDEFINED = -1,
    RVSIP_MEDIASUBTYPE_PLAIN,
    RVSIP_MEDIASUBTYPE_SDP,
    RVSIP_MEDIASUBTYPE_ISUP,
    RVSIP_MEDIASUBTYPE_QSIG,
    RVSIP_MEDIASUBTYPE_MIXED,
    RVSIP_MEDIASUBTYPE_ALTERNATIVE,
    RVSIP_MEDIASUBTYPE_DIGEST,
    RVSIP_MEDIASUBTYPE_RFC822,
    RVSIP_MEDIASUBTYPE_OTHER

} RvSipMediaSubType;

/* RvSipDispositionType
 * --------------------
 * This enumuration is used to indicate the disposition type of a Content-Disposition
 * header.
 */
typedef enum {
    RVSIP_DISPOSITIONTYPE_UNDEFINED = -1,
    RVSIP_DISPOSITIONTYPE_RENDER,
    RVSIP_DISPOSITIONTYPE_SESSION,
    RVSIP_DISPOSITIONTYPE_ICON,
    RVSIP_DISPOSITIONTYPE_ALERT,
    RVSIP_DISPOSITIONTYPE_SIGNAL,    /* see: draft-ietf-sip-isup-mime */
    RVSIP_DISPOSITIONTYPE_OTHER

} RvSipDispositionType;

/* RvSipDispositionHandling
 * --------------------
 * This enumuration is used to indicate the hadling type of a Content-Disposition
 * header.
 */
typedef enum {
    RVSIP_DISPOSITIONHANDLING_UNDEFINED = -1,
    RVSIP_DISPOSITIONHANDLING_OPTIONAL,
    RVSIP_DISPOSITIONHANDLING_REQUIRED,
    RVSIP_DISPOSITIONHANDLING_OTHER

} RvSipDispositionHandling;

#endif /* RV_SIP_PRIMITIVES */


/* RvSipDateWeekDay
 * --------------------
 * This enumuration is used to indicate the week day within a given date.
 */
typedef enum {
    RVSIP_WEEKDAY_UNDEFINED = -1,
    RVSIP_WEEKDAY_SUN,
    RVSIP_WEEKDAY_MON,
    RVSIP_WEEKDAY_TUE,
    RVSIP_WEEKDAY_WED,
    RVSIP_WEEKDAY_THU,
    RVSIP_WEEKDAY_FRI,
    RVSIP_WEEKDAY_SAT

}RvSipDateWeekDay;

/* RvSipDateMonth
 * --------------------
 * This enumuration is used to indicate the month within a given date.
 */
typedef enum {
    RVSIP_MONTH_UNDEFINED = -1,
    RVSIP_MONTH_JAN,
    RVSIP_MONTH_FEB,
    RVSIP_MONTH_MAR,
    RVSIP_MONTH_APR,
    RVSIP_MONTH_MAY,
    RVSIP_MONTH_JUN,
    RVSIP_MONTH_JUL,
    RVSIP_MONTH_AUG,
    RVSIP_MONTH_SEP,
    RVSIP_MONTH_OCT,
    RVSIP_MONTH_NOV,
    RVSIP_MONTH_DEC

}RvSipDateMonth;

/* RvSipExpiresFormat
 * --------------------
 * This enumuration is used to indicate the format of a given Expires header.
 * If the header is not initialized the format is undefined. An initialized
 * Expires header can either contain a date structure or an integer inidicating
 * deflta-seconds time.
 */
typedef enum {
    RVSIP_EXPIRES_FORMAT_UNDEFINED = -1,
    RVSIP_EXPIRES_FORMAT_DELTA_SECONDS,
    RVSIP_EXPIRES_FORMAT_DATE

}RvSipExpiresFormat;


/* RvSipContactAction
 * --------------------
 * This enumuration is used to indicate the contact action.
 */
typedef enum {
    RVSIP_CONTACT_ACTION_UNDEFINED = -1,
    RVSIP_CONTACT_ACTION_PROXY,
    RVSIP_CONTACT_ACTION_REDIRECT
} RvSipContactAction;

#ifndef RV_SIP_PRIMITIVES
/* RvSipSubscriptionSubstate
 * --------------------
 * This enumuration is used to indicate the substate in Subscription-State header.
 */
typedef enum {
    RVSIP_SUBSCRIPTION_SUBSTATE_UNDEFINED = -1,
    RVSIP_SUBSCRIPTION_SUBSTATE_ACTIVE,
    RVSIP_SUBSCRIPTION_SUBSTATE_PENDING,
    RVSIP_SUBSCRIPTION_SUBSTATE_TERMINATED,
    RVSIP_SUBSCRIPTION_SUBSTATE_OTHER
}RvSipSubscriptionSubstate;

/* RvSipSubscriptionReason
 * --------------------
 * This enumuration is used to indicate the reason in Subscription-State header.
 */
typedef enum {
    RVSIP_SUBSCRIPTION_REASON_UNDEFINED = -1,
    RVSIP_SUBSCRIPTION_REASON_DEACTIVATED,
    RVSIP_SUBSCRIPTION_REASON_PROBATION,
    RVSIP_SUBSCRIPTION_REASON_REJECTED,
    RVSIP_SUBSCRIPTION_REASON_TIMEOUT,
    RVSIP_SUBSCRIPTION_REASON_GIVEUP,
    RVSIP_SUBSCRIPTION_REASON_NORESOURCE,
    RVSIP_SUBSCRIPTION_REASON_OTHER
}RvSipSubscriptionReason;

/* RvSipSessionExpiresRefresherType
 * --------------------
 * This enumuration is used when session timer feature is enable.
 * RVSIP_SESSION_EXPIRES_REFRESHER_NONE - the refresher side of the call has not been set.
 * RVSIP_SESSION_EXPIRES_REFRESHER_UAC  - the refresher of the call is the uac
 * RVSIP_SESSION_EXPIRES_REFRESHER_UAS  - the refresher of the call is the uas
 */
typedef enum
{
    RVSIP_SESSION_EXPIRES_REFRESHER_NONE = -1,
    RVSIP_SESSION_EXPIRES_REFRESHER_UAC,
    RVSIP_SESSION_EXPIRES_REFRESHER_UAS
}RvSipSessionExpiresRefresherType;


/*
 * RvSipReplacesEarlyFlagType
 * --------------
 * Enumuration defines how the early-only parameter was received:
 * (early-only; early-only=true; early-only=1)
 */

typedef enum
{
    RVSIP_REPLACES_EARLY_FLAG_TYPE_UNDEFINED = -1,
    RVSIP_REPLACES_EARLY_FLAG_TYPE_EARLY_ONLY_EMPTY,   /* "early-only;" */
    RVSIP_REPLACES_EARLY_FLAG_TYPE_EARLY_ONLY_1,       /* "early-only=1;" */
    RVSIP_REPLACES_EARLY_FLAG_TYPE_EARLY_ONLY_TRUE     /* "early-only=true;" */
} RvSipReplacesEarlyFlagType;
#endif /* RV_SIP_PRIMITIVES */

/*
 * RvSipCompType
 * --------------
 * This enumuration is used to indicate the compression type of SIP messages
 * RVSIP_COMP_UNDEFINED - Undefined compression type.
 * RVSIP_COMP_SIGCOMP   - SigComp compression. 
 * RVSIP_COMP_OTHER     - not one of the above.
 */
typedef enum
{
    RVSIP_COMP_UNDEFINED = -1,  
    RVSIP_COMP_SIGCOMP,         
    RVSIP_COMP_OTHER            
}RvSipCompType;

#ifdef __cplusplus
}
#endif
#endif /* RVSIPTYPES_H */
