/******************************************************************************
Filename    :rvsdpmsg.h
Description :Definitions and structures for SDP messages

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

#ifndef RV_SDPMSG_H
#define RV_SDPMSG_H

#include "rvsdpmedia.h"

#if !defined(RV_SDP_DECLSPEC)
#define RV_SDP_DECLSPEC
#endif

#if defined(__cplusplus)
extern "C" {
#endif

#define RV_SDPMAX_VERSION_SIZE      4

#define RV_SDPDEPRECATED_MGCP1_0

/* Default */
#ifndef RV_SDPTIME_FULL
#define RV_SDPTIME_FULL
#endif
#ifndef RV_SDPSYMB_USESTRING
#define RV_SDPSYMB_USESTRING
#endif


typedef struct {
    short       type; /* prompt,clear,base64,uri */
    char *      key_data; /* including uri */
    int         key_len;
} RvSdpKey_;

typedef enum {
    RV_SDPPARSER_PREFIX_BAD_SYNTAX = 0,
    RV_SDPPARSER_PREFIX_CONT,
    RV_SDPPARSER_PREFIX_BAD_SYNTAX_M ,
    RV_SDPPARSER_PREFIX_CONT_M,
    RV_SDPPARSER_PREFIX_REPARSE

} SdpParseMarkPrefix;

typedef enum
{
    SDP_FIELDTYPE_ORIGIN,
    SDP_FIELDTYPE_INFORMATION,
    SDP_FIELDTYPE_SESSION,
    SDP_FIELDTYPE_URI,
    SDP_FIELDTYPE_EMAIL,
    SDP_FIELDTYPE_PHONE,
    SDP_FIELDTYPE_BANDWIDTH,
    SDP_FIELDTYPE_VERSION,
    SDP_FIELDTYPE_TIME,
    SDP_FIELDTYPE_KEY,
    SDP_FIELDTYPE_ATTRIBUTE,
    SDP_FIELDTYPE_CONNECTION,
    SDP_FIELDTYPE_REPEAT,
    SDP_FIELDTYPE_MEDIA,
    SDP_FIELDTYPE_RTP_MAP,
    SDP_FIELDTYPE_UNKNOWN_TAG,
    SDP_FIELDTYPE_BAD_FIELD

} RvSdpFieldTypes;

typedef struct RvSdpMsg_ {

    char                    sdp_version[RV_SDPMAX_VERSION_SIZE+1];
    RvAlloc *               alloc;

    /* Origin fields */
    RvSdpOrigin*            origin;

    /* Session fields */
    RvString                session_id;

    /* Uri */
    RvString                uri;
    RvBool                  uri_bad_syntax_set;
    RvSdpEmailList          email_list;
    RvSdpPhoneList          phone_list;

    /* Fields common to session level and media level */
    /* Information,Connection,Bandwidth, encryption key */
    /* and attributes and other field*/
    RvSdpCommonFields       fields;

    /* Time fields */
    RvSdpSessionTimeList     session_time;
    RvSdpTimeZoneAdjustList  zone_adjustment_list;

    /* Media descriptor */
    RvSdpMediaDescrList      media_descriptors;

    /* Encoded sdp message */
    char *                   sdp_msg;
    int                      msg_len;
    RvSdpFieldTypes          cur_field;

} RvSdpMsg;


/*--------------------------------------------------*/
/*Access functions for sdp description parameters   */
/* fields not set return RV_SDPFIELD_NOTSET         */
/* or NULL                                          */
/*--------------------------------------------------*/

/****************************************************/
/*      CONSTRUCTORS AND DESTRUCTORS                */
/****************************************************/

/* Construct and destruct and sdp structure */
RV_SDP_DECLSPEC RvSdpMsg* rvSdpMsgConstruct(RvSdpMsg * sdp);
RV_SDP_DECLSPEC void rvSdpMsgDestruct(RvSdpMsg * sdp);

/* Use for the parser, accepts an allocator  */
RV_SDP_DECLSPEC RvSdpMsg* rvSdpMsgConstructA(RvSdpMsg * sdp, RvAlloc *a);

RV_SDP_DECLSPEC RvSdpMsg* rvSdpMsgCopy(RvSdpMsg* d,const RvSdpMsg* s);
RV_SDP_DECLSPEC RvSdpMsg* rvSdpMsgConstructCopyA(RvSdpMsg *d, const RvSdpMsg *s, RvAlloc *a);
RV_SDP_DECLSPEC RvSdpMsg* rvSdpMsgConstructCopy(RvSdpMsg *d, const RvSdpMsg *s);


/****************************************************/
/*      Method to get the SIP text                  */
/****************************************************/
RV_SDP_DECLSPEC const char * rvSdpMsgGetText(RvSdpMsg *d,int * len);

/****************************************************/
/*      SESSION LEVEL METHODS                       */
/****************************************************/

/*const char* rvSdpMsgGetVersion(const RvSdpMsg* x);*/
#define rvSdpMsgGetVersion(sdp) ((const char*)(&(sdp)->sdp_version[0]))
RV_SDP_DECLSPEC RvSdpStatus rvSdpMsgSetVersionN(RvSdpMsg* x,const char * version,RvSize_t len);

/*------ Origin Field ---------------------------------*/

RV_SDP_DECLSPEC RvSdpStatus rvSdpMsgSetOriginN(RvSdpMsg *x,
                            const char * username,RvSize_t ulen,
                            const char * session_id,RvSize_t slen,
                            const char * version,RvSize_t vlen,
                            RvSdpNetType nettype,RvSdpAddrType addrtype,
                            const char * address,RvSize_t alen);

#define rvSdpMsgSetOrigin(x,u,s,v,n,at,a) rvSdpMsgSetOriginN(x,u,strlen(u),s,strlen(s),v,strlen(v),n,at,a,strlen(a))
/* RvSdpOrigin rvSdpMsgGetOrigin(cons RvSdpMsg * x) */
#define rvSdpMsgGetOrigin(x) (x->origin)

/*------ Session Id Field -----------------------------*/

/*const char * rvSdpMsgGetSessionName(RvSdpMsg* x);*/
#define rvSdpMsgGetSessionName(x) rvStringGetData(&x->session_id)

RV_SDP_DECLSPEC RvSdpStatus rvSdpMsgSetSessionNameN(RvSdpMsg* x,const char * sess_id,RvSize_t len);
/*RvSdpStatus rvSdpMsgSetSessionName(RvSdpMsg* x,const char * session_name)*/
#define rvSdpMsgSetSessionName(x,i) rvSdpMsgSetSessionNameN(x,i,strlen(i))

/*------ Session Information Field --------------------*/
#define rvSdpMsgSetSessionInformation(x,info) rvSdpCommonFieldsSetInformationN(&(x)->fields,info,strlen(info))
#define rvSdpMsgGetSessionInformation(x)      ((const char*)(rvStringGetData(&(x)->fields.information)))

/*------ Uri Field ------------------------------------*/
RV_SDP_DECLSPEC RvSdpStatus rvSdpMsgSetURIN(RvSdpMsg* x,const char * uri,RvSize_t len);
/*RvSdpStatus rvSdpMsgSetURI(RvSdpMsg* x,const char * uri) */
#define rvSdpMsgSetURI(x,uri) rvSdpMsgSetURIN(x,uri,strlen(uri))
#if defined(RV_SDP_CHECK_BAD_SYNTAX)
#define rvSdpMsgUriIsBadSyntax(x)   x->uri_bad_syntax_set
#define rvSdpMsgGetBadSyntaxUri(x)  x->uri
#define rvSdpMsgSetBadSyntaxURI(x,uri) rvSdpMsgSetBadSyntaxURIN(x,uri,strlen(uri))
#define rvSdpMsgGetURIBadSyntax(x) ((const char*)(rvStringGetData(&(x)->uri)))
#endif
/*const char* rvSdpMsgGetURI(RvSdpMsg* x);*/
#define rvSdpMsgGetURI(x) ((const char*)(rvStringGetData(&(x)->uri)))
/*------ Email Field ---------------------------------*/
#if defined(RV_SDP_CHECK_BAD_SYNTAX)
RV_SDP_DECLSPEC RvSdpStatus rvSdpMsgSetBadSyntaxURIN(RvSdpMsg* x,const char * uri,RvSize_t len) ;
RV_SDP_DECLSPEC RvSdpEmail* rvSdpMsgAddBadSyntaxEmailN(RvSdpMsg* descr,const char * bad_syntax,RvSize_t len);
#define rvSdpMsgAddBadSyntaxEmail(x,bs) rvSdpMsgAddBadSyntaxEmailN(x,e,strlen(bs))
#endif

RV_SDP_DECLSPEC RvSdpEmail* rvSdpMsgAddEmailN(RvSdpMsg* descr,const char * email_addr,RvSize_t len,const char* string,RvSize_t slen);
#define rvSdpMsgAddEmail(x,e,s) rvSdpMsgAddEmailN(x,e,strlen(e),s,strlen(s))
RV_SDP_DECLSPEC RvSize_t         rvSdpMsgGetNumOfEmail(const RvSdpMsg* descr);
RV_SDP_DECLSPEC RvSdpEmail* rvSdpMsgGetEmail(const RvSdpMsg* descr,RvSize_t i);
RV_SDP_DECLSPEC void rvSdpMsgRemoveEmail(RvSdpMsg* descr,RvSize_t i);
RV_SDP_DECLSPEC void rvSdpMsgClearEmail(RvSdpMsg* descr);

/*------ Phone Field ---------------------------------*/

RV_SDP_DECLSPEC RvSdpPhone * rvSdpMsgAddPhoneN(RvSdpMsg* x,const char * phone,RvSize_t plen,const char* string,RvSize_t slen);
#define rvSdpMsgAddPhone(x,p,s) rvSdpMsgAddPhoneN(x,p,strlen(p),s,strlen(s))

#if defined(RV_SDP_CHECK_BAD_SYNTAX)
RV_SDP_DECLSPEC RvSdpPhone * rvSdpMsgAddBadSyntaxPhoneN(RvSdpMsg* x,const char * badSyntax,RvSize_t len);
#define rvSdpMsgAddBadSyntaxPhone(x,bs) rvSdpMsgAddBadSyntaxPhoneN(x,bs,strlen(bs))
#endif

RV_SDP_DECLSPEC RvSize_t rvSdpMsgGetNumOfPhones(const RvSdpMsg* descr);
RV_SDP_DECLSPEC RvSdpPhone* rvSdpMsgGetPhone(const RvSdpMsg* descr,RvSize_t i);
RV_SDP_DECLSPEC void rvSdpMsgRemovePhone(RvSdpMsg* descr,RvSize_t i);
RV_SDP_DECLSPEC void rvSdpMsgClearPhones(RvSdpMsg* descr);

/*------ Connection Field ---------------------------*/
RV_SDP_DECLSPEC RvSdpStatus rvSdpMsgSetConnection(RvSdpMsg* descr,RvSdpNetType type,RvSdpAddrType addr_type,const char* addr);
#if defined(RV_SDP_CHECK_BAD_SYNTAX)
RV_SDP_DECLSPEC RvSdpStatus rvSdpMsgSetBadSyntaxConnection(RvSdpMsg* descr,const char* badsyntax);
#endif
RV_SDP_DECLSPEC RvSdpConnection* rvSdpMsgGetConnection(const RvSdpMsg* descr);
#define rvSdpMsgGetConnection_(x) ((x)->fields.connection)

/*------ Bandwidth Field ---------------------------*/
RV_SDP_DECLSPEC RvSdpStatus rvSdpMsgSetBandwidth(RvSdpMsg* x,const char *bwtype,int b);
#if defined(RV_SDP_CHECK_BAD_SYNTAX)
RV_SDP_DECLSPEC RvSdpStatus rvSdpMsgSetBadSyntaxBandwidth(RvSdpMsg* x,const char *bad_syntax);
#endif
#define rvSdpMsgGetBandwidth(x) ((x)->fields.bandwidth)

/*------ Key Field ----------------------------------*/
RV_SDP_DECLSPEC RvSdpStatus rvSdpMsgSetKey(RvSdpMsg* x,RvSdpEncrMethod em,const char* key);
#if defined(RV_SDP_CHECK_BAD_SYNTAX)
RV_SDP_DECLSPEC RvSdpStatus rvSdpMsgSetBadSyntaxKey(RvSdpMsg* x,const char* badSyntax);
RvSdpStatus rvSdpMsgSetBadSyntaxOriginN(RvSdpMsg *x,
                               const char * bad_syntax);
#endif
RV_SDP_DECLSPEC RvSdpKey* rvSdpMsgGetKey(const RvSdpMsg* x);
#define rvSdpMsgGetKey_(x) ((x)->fields.key)
/*------ Time Fields  ---------------------------------*/

/* Session and repeat fields */
RV_SDP_DECLSPEC RvSdpSessionTime* rvSdpMsgAddSessionTime(RvSdpMsg* descr,RvUint32 start,RvUint32 stop);
#if defined(RV_SDP_CHECK_BAD_SYNTAX)
RV_SDP_DECLSPEC RvSdpSessionTime* rvSdpMsgAddBadSyntaxSessionTime(RvSdpMsg* descr,char *bad_syntax);
RV_SDP_DECLSPEC RvSdpRepeatInterval * rvSdpSessionTimeAddBadSyntaxRepeatInterval(RvSdpMsg* descr,RvSdpSessionTime * session,char *badSyntax);
#endif

RV_SDP_DECLSPEC void rvSdpMsgClearSessionTime(RvSdpMsg* descr);
RV_SDP_DECLSPEC RvSize_t rvSdpMsgGetNumOfSessionTime(RvSdpMsg* descr);
RV_SDP_DECLSPEC RvSdpSessionTime* rvSdpMsgGetSessionTime(RvSdpMsg* descr,RvSize_t i);
RV_SDP_DECLSPEC void rvSdpMsgRemoveSessionTime(RvSdpMsg* descr,RvSize_t i);
/* Zone adjustment field */
RV_SDP_DECLSPEC RvSdpTimeZoneAdjust * rvSdpMsgTimeAddZoneAdjustment(RvSdpMsg* descr,RvUint32 time,RvInt32 adjust_time,RvSdpTimeUnit units);
RV_SDP_DECLSPEC void rvSdpMsgClearZoneAdjustment(RvSdpMsg* descr);
RV_SDP_DECLSPEC RvSize_t rvSdpMsgGetNumOfZoneAdjustments(RvSdpMsg* descr);
#ifdef RV_SDPTIME_FULL
RV_SDP_DECLSPEC RvSdpTimeZoneAdjust* rvSdpMsgGetZoneAdjustment(RvSdpMsg* descr,RvSize_t i);
RV_SDP_DECLSPEC void rvSdpMsgRemoveTimeZoneAdjust(RvSdpMsg* descr,RvSize_t i);
#endif

#if defined(RV_SDP_CHECK_BAD_SYNTAX)
/*------ BadSyntax Field ----------------------------------*/
RV_SDP_DECLSPEC RvSize_t rvSdpMsgGetNumOfBadSyntax(const RvSdpMsg* descr);
RV_SDP_DECLSPEC RvSdpBadSyntax* rvSdpMsgGetBadSyntax(const RvSdpMsg* descr,RvSize_t i);
RV_SDP_DECLSPEC RvSdpBadSyntax* rvSdpMsgAddBadSyntax(RvSdpMsg* descr, RvSdpGenericFieldPtr field,RvSdpBadSyntaxType field_type);
RV_SDP_DECLSPEC void rvSdpMsgRemoveBadSyntax(RvSdpMsg* descr,RvSize_t i);
RV_SDP_DECLSPEC void rvSdpMsgRemoveBadSyntaxP(RvSdpMsg* x,RvSdpGenericFieldPtr *p) ;
RV_SDP_DECLSPEC void rvSdpMsgClearBadSyntax(RvSdpMsg* x);
#endif

/*------ Attribute Field ----------------------------------*/
RV_SDP_DECLSPEC RvSize_t rvSdpMsgGetNumOfAttr(const RvSdpMsg* descr);
RV_SDP_DECLSPEC RvSdpAttribute* rvSdpMsgGetAttribute(const RvSdpMsg* descr,RvSize_t i);
RV_SDP_DECLSPEC RvSdpAttribute* rvSdpMsgAddAttr(RvSdpMsg* descr, const char* name, const char* value);
RV_SDP_DECLSPEC void rvSdpMsgRemoveAttr(RvSdpMsg* descr,RvSize_t i);
RV_SDP_DECLSPEC void rvSdpMsgClearAttr(RvSdpMsg* x);

#if defined(RV_SDP_CHECK_BAD_SYNTAX)
/*------ Other Field ----------------------------------*/
RV_SDP_DECLSPEC RvSize_t rvSdpMsgGetNumOfOther(const RvSdpMsg* descr);
RV_SDP_DECLSPEC RvSdpOther* rvSdpMsgGetOther(const RvSdpMsg* descr,RvSize_t i);
RV_SDP_DECLSPEC RvSdpOther* rvSdpMsgAddOther(RvSdpMsg* descr, const char tag, const char* value);
RV_SDP_DECLSPEC void rvSdpMsgRemoveOther(RvSdpMsg* descr,RvSize_t i);
RV_SDP_DECLSPEC void rvSdpMsgClearOther(RvSdpMsg* x);
#endif

/*------ RtpMap Field ----------------------------------*/
RV_SDP_DECLSPEC RvSize_t rvSdpMsgGetNumOfRtpMap(const RvSdpMsg* descr);
RV_SDP_DECLSPEC RvSdpRtpMap* rvSdpMsgGetRtpMap(const RvSdpMsg* descr,RvSize_t i);
RV_SDP_DECLSPEC RvSdpRtpMap* rvSdpMsgAddRtpMap(RvSdpMsg* x,int payload,const char * encoding_name,int rate);
#if defined(RV_SDP_CHECK_BAD_SYNTAX)
RV_SDP_DECLSPEC RvSdpRtpMap* rvSdpMsgAddBadSyntaxRtpMap(RvSdpMsg* x,const char * badSyntax);
#endif
RV_SDP_DECLSPEC void rvSdpMsgRemoveRtpMap(RvSdpMsg* descr,RvSize_t i);
RV_SDP_DECLSPEC void rvSdpMsgClearRtpMap(RvSdpMsg* x);

/*------ Send mode Field ----------------------------------*/
/* Used to encode attributes sendonly, recvonly, sendrecv  */
/*void rvSdpMsgSetConnectionMode(RvSdpMsg * x,RvSdpConnectionMode mode);*/
#define rvSdpMsgSetConnectionMode(x,mode) rvSdpCommonFieldsSetConnectionMode(&(x)->fields,mode)
/*RvSdpConnectionMode rvSdpMsgGetConnectionMode(const RvSdpMsg * x);*/
#define rvSdpMsgGetConnectionMode(x) rvSdpCommonFieldsGetConnectionMode(&(x)->fields)

/*------ Media Description Field ----------------------*/

RV_SDP_DECLSPEC RvSize_t rvSdpMsgGetNumOfMediaDescr(const RvSdpMsg * sdp);
RV_SDP_DECLSPEC RvSdpMediaDescr* rvSdpMsgGetMediaDescr(const RvSdpMsg * sdp, RvSize_t index);
#if defined(RV_SDP_CHECK_BAD_SYNTAX)
RV_SDP_DECLSPEC RvSdpMediaDescr* rvSdpMsgAddBadSyntaxMediaDescr(RvSdpMsg * sdp,char *bs) ;
#endif
/* Currently,only one media descr can be added or inserted */
RV_SDP_DECLSPEC RvSdpMediaDescr* rvSdpMsgAddMediaDescr(RvSdpMsg * sdp,RvSdpMediaType media_type,int port,RvSdpProtocol protocol);
/* ATM */
RV_SDP_DECLSPEC RvSdpMediaDescr* rvSdpMsgAddMediaDescrAtm(RvSdpMsg * sdp,RvSdpMediaType media_type,RvSdpProtocol protocol);

RV_SDP_DECLSPEC RvSdpStatus rvSdpMsgInsertMediaDescr(RvSdpMsg * sdp,RvSdpMediaDescr* descr);
RV_SDP_DECLSPEC void rvSdpMsgClearMediaDescr(RvSdpMsg * sdp);
RV_SDP_DECLSPEC void rvSdpMsgRemoveMediaDescr(RvSdpMsg * sdp,RvSize_t index);

#ifdef RV_SDPDEPRECATED_MGCP1_0
RV_SDP_DECLSPEC RvSdpStatus rvSdpMsgSetOriginAddress(RvSdpMsg* x,const char * origin_addr);
RV_SDP_DECLSPEC RvSdpNetType rvSdpMsgGetNetworkType(const RvSdpMsg * sdp);
RV_SDP_DECLSPEC RvSdpAddrType rvSdpMsgGetAddrType(const RvSdpMsg* x);
RV_SDP_DECLSPEC const char* rvSdpMsgGetAddress(const RvSdpMsg* x);
RV_SDP_DECLSPEC RvSdpNetType rvSdpMediaDescrGetNetworkType(const RvSdpMediaDescr* descr);
RV_SDP_DECLSPEC RvSdpAddrType rvSdpMediaDescrGetAddrType(const RvSdpMediaDescr* descr);
RV_SDP_DECLSPEC const char* rvSdpMediaDescrGetAddress(const RvSdpMediaDescr* descr);
RV_SDP_DECLSPEC RvSdpEncrMethod rvSdpMsgGetKeyType(const RvSdpMsg* x);
RV_SDP_DECLSPEC const char* rvSdpMsgGetKeyData(const RvSdpMsg * sdp);
RV_SDP_DECLSPEC RvSdpEncrMethod rvSdpMediaDescrGetKeyType(const RvSdpMediaDescr* descr);
RV_SDP_DECLSPEC const char* rvSdpMediaDescrGetKeyData(const RvSdpMediaDescr* descr);
#endif

/* Data structure to support a list of Sdp messages */
rvSdpDeclareList(RvSdpMsg)
typedef RvSdpList(RvSdpMsg)            RvSdpMsgList;

RV_SDP_DECLSPEC RvSdpMsgList* rvSdpMsgListConstructA(RvSdpMsgList* msgList, RvAlloc* a);
RV_SDP_DECLSPEC RvSdpMsgList* rvSdpMsgListConstructCopy(RvSdpMsgList* d, const RvSdpMsgList* s, RvAlloc* a);
RV_SDP_DECLSPEC void rvSdpMsgListDestruct(RvSdpMsgList* msgList);
RV_SDP_DECLSPEC RvSdpMsgList* rvSdpMsgListCopy(RvSdpMsgList* d, const RvSdpMsgList* s);
RV_SDP_DECLSPEC RvBool rvSdpMsgListEqual(RvSdpMsgList* a, RvSdpMsgList* b);
RV_SDP_DECLSPEC RvSize_t rvSdpMsgListGetSize(const RvSdpMsgList* msgList);
RV_SDP_DECLSPEC RvSdpMsg* rvSdpMsgListGetElement(RvSdpMsgList * msgList, RvSize_t i);
RV_SDP_DECLSPEC void rvSdpMsgListRemoveElement(RvSdpMsgList * msgList, RvSize_t i);
RV_SDP_DECLSPEC void rvSdpMsgListClear(RvSdpMsgList * msgList);
RV_SDP_DECLSPEC RvSdpMsg * rvSdpMsgListAddMsg(RvSdpMsgList * msgList);
RV_SDP_DECLSPEC RvSdpStatus rvSdpMsgListInsertMsg(RvSdpMsgList * msgList,const RvSdpMsg * msg);

#if defined(__cplusplus)
}
#endif

#endif /* RV_SDPMSG_H */

