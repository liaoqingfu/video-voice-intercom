/******************************************************************************
Filename    :rvsdpmedia.h
Description :Definitions and structures for SDP media descriptor

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

#ifndef RV_SDPMEDIA_H
#define RV_SDPMEDIA_H


#define RV_SDPPORT_ANY     -1
#define RV_SDPPORT_NOTSET  -2
#define RV_SDPPORT_IGNORE  -3
#define RV_SDPPORT_ATM     -4
#define RV_SDPPORT_OTHER   -5

#include "rvsdpobjs.h"

#if !defined(RV_SDP_DECLSPEC)
#define RV_SDP_DECLSPEC
#endif

#if defined(__cplusplus)
extern "C" {
#endif

#define rvSdpMemEqual(d,s,T) memcmp((void*)d,(void*)s,sizeof(T))

/******************* Media descriptor methods ********************************/
typedef struct RvSdpMedia_{
    RvSdpMediaType          media_type;
#if defined(RV_SDP_CHECK_BAD_SYNTAX)
    RvString                badSyntaxField;
    RvBool                  badSyntaxFieldSet;
#endif
#ifdef RV_SDPSYMB_USESTRING
    RvString                media_type_str;
#endif
    RvString                control_method; /* Used for NAS */
    int             port;
    int                     num_of_ports;
    RvSdpProtocol           protocol;
#ifdef RV_SDPSYMB_USESTRING
    RvString                protocol_str;
#endif
    RvSdpList(RvString)        fmt_list;

    /* VcId */
    int                     vcid_type[4];
    RvSdpList(RvString)        vcid_value;

} RvSdpMedia;

typedef struct RvSdpMediaDescr_{
    RvSdpMedia              media;
    RvSdpCommonFields       fields;
    struct RvSdpMsg_ *      sdp;
    RvAlloc *               alloc;
} RvSdpMediaDescr;

rvSdpDeclareList(RvSdpMediaDescr)
typedef RvSdpList(RvSdpMediaDescr) RvSdpMediaDescrList;
RV_SDP_DECLSPEC RvSdpMediaDescrList* rvSdpMediaDescrListConstruct(RvSdpMediaDescrList *x);
#define rvSdpMediaDescrListConstructA rvListConstruct(RvSdpMediaDescr)
#define rvSdpMediaDescrListConstructCopy rvListConstructCopy(RvSdpMediaDescr)
#define rvSdpMediaDescrListDestruct rvListDestruct(RvSdpMediaDescr)
#define rvSdpMediaDescrListCopy rvListCopy(RvSdpMediaDescr)
#define rvSdpMediaDescrListEqual rvListEqual(RvSdpMediaDescr)
#define rvSdpMediaDescrListAdd rvListPushBack(RvSdpMediaDescr)
#define rvSdpMediaDescrListClear rvListClear(RvSdpMediaDescr)
#define rvSdpMediaDescrListGetSize rvListSize
#define rvSdpMediaDescrListGetElem rvListAt(RvSdpMediaDescr)

/****************************************************/
/*      MEDIA DESCRIPTION LEVEL METHODS             */
/****************************************************/

/* Set default values for other fields, set only one fmt */
#if defined(RV_SDP_CHECK_BAD_SYNTAX)
RV_SDP_DECLSPEC RvSdpMedia* rvSdpMediaBadSyntaxConstruct(RvSdpMedia* m,char  *badSyntaxField,RvAlloc * a);
RV_SDP_DECLSPEC RvSdpMedia* rvSdpMediaBadSyntaxConstructN(RvSdpMedia* m,char  *badSyntaxField,int len,RvAlloc * a) ;
RV_SDP_DECLSPEC RvSdpMediaDescr* rvSdpMediaDescrBadSyntaxConstructA(RvSdpMediaDescr* descr,char *badSyntaxField,RvAlloc * a) ;
RV_SDP_DECLSPEC RvSdpMediaDescr* rvSdpMediaDescrBadSyntaxConstruct(RvSdpMediaDescr* descr,char *badSyntaxField);
#endif
RV_SDP_DECLSPEC RvSdpMediaDescr* rvSdpMediaDescrConstructA(RvSdpMediaDescr* descr,RvSdpMediaType media_type,int port,RvSdpProtocol protocol,RvAlloc * a);
RV_SDP_DECLSPEC RvSdpMediaDescr* rvSdpMediaDescrConstruct(RvSdpMediaDescr* descr,RvSdpMediaType media_type,int port,RvSdpProtocol protocol);
RV_SDP_DECLSPEC RvSdpMediaDescr* rvSdpMediaDescrConstructCopyA(RvSdpMediaDescr *d,const RvSdpMediaDescr *s,RvAlloc * alloc) ;
RV_SDP_DECLSPEC RvSdpMediaDescr* rvSdpMediaDescrConstructCopy(RvSdpMediaDescr *d,const RvSdpMediaDescr *s) ;
RV_SDP_DECLSPEC void rvSdpMediaDescrDestruct(RvSdpMediaDescr* descr);
RV_SDP_DECLSPEC RvSdpMediaDescr* rvSdpMediaDescrCopy(RvSdpMediaDescr* d,const RvSdpMediaDescr* s);

#define RvSdpMediaDescrConstructCopy    rvSdpMediaDescrConstructCopyA
#define RvSdpMediaDescrDestruct rvSdpMediaDescrDestruct
#define RvSdpMediaDescrCopy rvSdpMediaDescrCopy
#define RvSdpMediaDescrEqual(d,s) rvSdpMemEqual(d,s,RvSdpMediaDescr)

/* Internal function */

/*------ Media  Field ------------------------------*/
/* return values :
RV_SDPMEDIA_AUDIO
RV_SDPMEDIA_DATA */
/*RvSdpMediaType    rvSdpMediaDescrGetMediaType(const RvSdpMediaDescr* descr); */
#define rvSdpMediaDescrGetMediaType(descr) ((descr)->media.media_type)
RV_SDP_DECLSPEC void rvSdpMediaDescrSetMediaType(RvSdpMediaDescr* descr,RvSdpMediaType type);
#define rvSdpMediaDescrSetMediaType(descr,type) ((descr)->media.media_type=type);

#if defined(RV_SDP_CHECK_BAD_SYNTAX)
RV_SDP_DECLSPEC RvSdpStatus rvSdpMediaDescrSetBadSyntax(RvSdpMediaDescr* descr, const char* bs);
#endif
RV_SDP_DECLSPEC const char *rvSdpMediaDescrGetMediaTypeStr(const RvSdpMediaDescr* descr);
RV_SDP_DECLSPEC RvSdpStatus rvSdpMediaDescrSetMediaTypeStrN(RvSdpMediaDescr* descr,const char * type,RvSize_t n);
RV_SDP_DECLSPEC RvSdpStatus rvSdpMediaDescrSetMediaTypeStr(RvSdpMediaDescr* descr,const char * type);
#if defined(RV_SDP_CHECK_BAD_SYNTAX)
RV_SDP_DECLSPEC RvSdpStatus rvSdpMediaDescrSetbadSyntaxN(RvSdpMediaDescr* descr, const char * ctrl_method, int len) ;
#endif
/* Used for NAS */
/* const char *rvSdpMediaDescrGetNASCtrlMethod(const RvSdpMediaDescr* descr);   */
#define rvSdpMediaDescrGetNASCtrlMethod(descr) (rvStringGetData(&(descr)->media.control_method))

RV_SDP_DECLSPEC RvSdpStatus rvSdpMediaDescrSetNASCtrlMethod(RvSdpMediaDescr* descr, const char* cm);

/* RvInet rvSdpMediaDescrGetPort(const RvSdpMediaDescr* descr);    */
#define rvSdpMediaDescrGetPort(descr) ((descr)->media.port)

/*void rvSdpMediaDescrSetPort(RvSdpMediaDescr* descr,int port);*/
#define rvSdpMediaDescrSetPort(descr,port_) ((descr)->media.port = (port_))

/* int rvSdpMediaDescrGetNumOfPorts(const RvSdpMediaDescr* descr); */
#define rvSdpMediaDescrGetNumOfPorts(descr) ((descr)->media.num_of_ports)

/*void rvSdpMediaDescrSetNumOfPorts(RvSdpMediaDescr* descr,int subport);*/
#define rvSdpMediaDescrSetNumOfPorts(descr,subport_) ((descr)->media.num_of_ports = subport_)

/* return values :
RV_SDPPROTOCOL_RTP
RV_SDPPROTOCOL_LOCAL
RV_SDPPROTOCOL_ATM */
/*RvSdpProtocol rvSdpMediaDescrGetProtocol(const RvSdpMediaDescr* descr); */
#define rvSdpMediaDescrGetProtocol(descr) ((descr)->media.protocol)
/*void rvSdpMediaDescrSetProtocol(RvSdpMediaDescr* descr,RvSdpProtocol protocol);*/
#define rvSdpMediaDescrSetProtocol(descr,p) ((descr)->media.protocol=p)
/*     #define rvSdpMediaDescrIsBadSyntax(x)    x->media.badSyntaxFieldSet*/
/*#define rvSdpMediaDescrGetBadSyntax(x)    rvSdpStringGetData(&x->media.badSyntaxField)*/
RV_SDP_DECLSPEC const char *rvSdpMediaDescrGetProtocolStr(const RvSdpMediaDescr* descr);
RV_SDP_DECLSPEC RvSdpStatus rvSdpMediaDescrSetProtocolStr(RvSdpMediaDescr* descr,const char * protocol);
RV_SDP_DECLSPEC RvSdpStatus rvSdpMediaDescrSetProtocolStrN(RvSdpMediaDescr* descr,const char * protocol,RvSize_t n);

RV_SDP_DECLSPEC RvSize_t rvSdpMediaDescrGetNumOfFormats(const RvSdpMediaDescr* descr);
RV_SDP_DECLSPEC const char *rvSdpMediaDescrGetFormat(RvSdpMediaDescr* descr, RvSize_t index);
RV_SDP_DECLSPEC void rvSdpMediaDescrRemoveFormat(RvSdpMediaDescr* descr, RvSize_t index);
RV_SDP_DECLSPEC RvSdpStatus rvSdpMediaDescrAddFormat(RvSdpMediaDescr* descr,const char* fmt);
RV_SDP_DECLSPEC void rvSdpMediaDescrClearFormat(RvSdpMediaDescr* descr);

RV_SDP_DECLSPEC RvSize_t rvSdpMediaDescrGetNumOfPayloads(const RvSdpMediaDescr* descr);
RV_SDP_DECLSPEC int rvSdpMediaDescrGetPayloadNumber(RvSdpMediaDescr* descr, RvSize_t index);

RV_SDP_DECLSPEC RvSdpStatus rvSdpMediaDescrAddPayloadNumber(RvSdpMediaDescr* descr,int payload);
/*void rvSdpMediaDescrRemovePayloadNumber(RvSdpMediaDescr* descr, RvSize_t index);*/
#define rvSdpMediaDescrRemovePayloadNumber   rvSdpMediaDescrRemoveFormat

/*void rvSdpMediaDescrClearPayloads(RvSdpMediaDescr* descr);*/
#define rvSdpMediaDescrClearPayloads rvSdpMediaDescrClearFormat

/*------ Information Field ---------------------------*/
/*RvSdpStatus rvSdpMediaDescrSetInformation(RvSdpMediaDescr* descr,const char * info);*/
#define rvSdpMediaDescrSetInformation(descr,info) rvSdpCommonFieldsSetInformationN(&(descr)->fields,info,strlen(info))
/*const char * rvSdpMediaDescrGetInformation(const RvSdpMediaDescr* descr);*/
#define rvSdpMediaDescrGetInformation(descr) rvStringGetData(&(descr)->fields.information)

/*------ Connection Field ---------------------------*/
/*RvSdpStatus rvSdpMediaDescrSetConnection(RvSdpMediaDescr* descr,RvSdpNetType type,RvSdpAddrType addr_type,const char* addr);*/
#define rvSdpMediaDescrSetConnection(d,nt,at,a) rvSdpCommonFieldsSetConnectionN(&(d)->fields,(nt),(at),(a),strlen((a)),(d)->alloc)

/*RvSdpConnection* rvSdpMediaDescrGetConnection(const RvSdpMediaDescr* descr);*/
#define rvSdpMediaDescrGetConnection(descr) ((descr)->fields.connection)

/*------ Bandwidth Field ---------------------------*/
/*RvSdpStatus rvSdpMediaDescrSetBandwidth(RvSdpMediaDescr* descr,const char *bwtype,int b);*/
#define rvSdpMediaDescrSetBandwidth(descr,bwtype,b) rvSdpCommonFieldsSetBandwidthN(&(descr)->fields,bwtype,strlen(bwtype),b,(descr)->alloc)
#if defined(RV_SDP_CHECK_BAD_SYNTAX)
#define rvSdpMediaDescrSetBadSyntaxBandwidth(descr,bs) rvSdpCommonFieldsSetBadSyntaxBandwidthN(&(descr)->fields,bs,strlen(bs),(descr)->alloc)
#endif
#define rvSdpMediaDescrGetBandwidth(descr) ((descr)->fields.bandwidth)

/*------ Key Field ----------------------------------*/
/*RvSdpStatus rvSdpMediaDescrSetKey(RvSdpMediaDescr* descr,RvSdpEncrMethod em,const char* key);*/
#define rvSdpMediaDescrSetKey(descr,em,key) rvSdpCommonFieldsSetKeyN(&(descr)->fields,(em),(key),strlen(key),(descr)->alloc)
#if defined(RV_SDP_CHECK_BAD_SYNTAX)
#define rvSdpMediaDescrSetBadSyntaxKey(descr,badSyntax) rvSdpCommonFieldsSetBadSyntaxKeyN(&(descr)->fields,badSyntax,strlen(badSyntax),(descr)->alloc)
#endif
/*RvSdpKey* rvSdpMediaDescrGetKey(const RvSdpMediaDescr* descr);*/
#define rvSdpMediaDescrGetKey(descr) ((descr)->fields.key)

#if defined(RV_SDP_CHECK_BAD_SYNTAX)
/*------ BadSyntax Field ------------------------------*/
RV_SDP_DECLSPEC RvSize_t rvSdpMediaDescrGetNumOfBadSyntax(const RvSdpMediaDescr* descr);
RV_SDP_DECLSPEC RvSdpBadSyntax* rvSdpMediaDescrGetBadSyntax(const RvSdpMediaDescr* descr,RvSize_t i);

/*RvSdpStatus rvSdpMediaDescrAddAttr(RvSdpMediaDescr* descr, const char* name, const char* value);*/
#define rvSdpMediaDescrAddBadSyntax(d,n,v) rvSdpCommonFieldsAddBadSyntaxN(&(d)->fields,n,v,(d)->alloc)

RV_SDP_DECLSPEC void rvSdpMediaDescrRemoveBadSyntax(RvSdpMediaDescr* descr,RvSize_t i);
RV_SDP_DECLSPEC void rvSdpMediaDescrClearBadSyntax(RvSdpMediaDescr* descr);
#endif

/*------ Attribute Field ------------------------------*/
RV_SDP_DECLSPEC RvSize_t rvSdpMediaDescrGetNumOfAttr(const RvSdpMediaDescr* descr);
RV_SDP_DECLSPEC RvSdpAttribute* rvSdpMediaDescrGetAttribute(const RvSdpMediaDescr* descr,RvSize_t i);

/*RvSdpStatus rvSdpMediaDescrAddAttr(RvSdpMediaDescr* descr, const char* name, const char* value);*/
#define rvSdpMediaDescrAddAttr(d,n,v) rvSdpCommonFieldsAddAttrN(&(d)->fields,n,strlen(n),v,strlen(v),(d)->alloc)

RV_SDP_DECLSPEC void rvSdpMediaDescrRemoveAttr(RvSdpMediaDescr* descr,RvSize_t i);
RV_SDP_DECLSPEC void rvSdpMediaDescrClearAttr(RvSdpMediaDescr* descr);
/*------ Other Field ------------------------------*/
RV_SDP_DECLSPEC RvSize_t rvSdpMediaDescrGetNumOfOther(const RvSdpMediaDescr* descr);
#if defined(RV_SDP_CHECK_BAD_SYNTAX)
RV_SDP_DECLSPEC RvSdpOther* rvSdpMediaDescrGetOther(const RvSdpMediaDescr* descr,RvSize_t i);

/*RvSdpStatus rvSdpMediaDescrAddAttr(RvSdpMediaDescr* descr, const char* name, const char* value);*/
#define rvSdpMediaDescrAddOther(d,t,v) rvSdpCommonFieldsAddOtherN(&(d)->fields,t,v,strlen(v),(d)->alloc)
#endif

RV_SDP_DECLSPEC void rvSdpMediaDescrRemoveOther(RvSdpMediaDescr* descr,RvSize_t i);
RV_SDP_DECLSPEC void rvSdpMediaDescrClearOther(RvSdpMediaDescr* descr);

/*------ Send mode Field ----------------------------------*/
/* Used to encode attributes sendonly, recvonly, sendrecv  */
/*RvSdpStatus rvSdpMediaDescrSetConnectionMode(RvSdpMediaDescr * x,RvSdpConnectionMode mode);*/
#define rvSdpMediaDescrSetConnectionMode(x,mode) rvSdpCommonFieldsSetConnectionMode(&(x)->fields,mode)
/*RvSdpConnectionMode rvSdpMediaDescrGetConnectionMode(const RvSdpMediaDescr * x);*/
#define rvSdpMediaDescrGetConnectionMode(x) rvSdpCommonFieldsGetConnectionMode(&(x)->fields)


/*------ RtpMap Field ----------------------------------*/
RV_SDP_DECLSPEC RvSize_t rvSdpMediaDescrGetNumOfRtpMap(const RvSdpMediaDescr* descr);
RV_SDP_DECLSPEC RvSdpRtpMap* rvSdpMediaDescrGetRtpMap(const RvSdpMediaDescr* descr,RvSize_t index);

/*RvSdpRtpMap* rvSdpMediaDescrAddRtpMap(RvSdpMediaDescr* x,int payload,const char * encoding_name,int rate);*/
#define rvSdpMediaDescrAddRtpMap(x,p,e,r) rvSdpCommonFieldsAddRtpMapN(&(x)->fields,p,e,strlen(e),r,(x)->alloc)
#if defined(RV_SDP_CHECK_BAD_SYNTAX)
#define rvSdpMediaDescrAddBadSyntaxRtpMap(x,bs) rvSdpCommonFieldsAddBadSyntaxRtpMapN(&(x)->fields,bs,strlen(bs),(x)->alloc)
#endif
RV_SDP_DECLSPEC void rvSdpMediaDescrRemoveRtpMap(RvSdpMediaDescr* descr, RvSize_t index);
RV_SDP_DECLSPEC void rvSdpMediaDescrClearRtpMap(RvSdpMediaDescr* x);

/* Optimized functions used for the parser */
RV_SDP_DECLSPEC RvSdpStatus rvSdpMediaDescrAddFormatN(RvSdpMediaDescr* descr,const char* fmt,int len);
RV_SDP_DECLSPEC RvSdpStatus rvSdpMediaDescrSetCtrlMethodN(RvSdpMediaDescr* descr, const char* cm,int len);

/*------ RtpMap Field ----------------------------------*/

/*------ VcId Field ------------------------------------*/
RV_SDP_DECLSPEC RvSdpStatus rvSdpMediaDescrAddVcIdN(RvSdpMediaDescr* descr,int type,const char* value,int len);
/*RV_SDP_DECLSPEC void rvSdpMediaDescrAddVcId(RvSdpMediaDescr* descr,int type,const char* value);*/
#define rvSdpMediaDescrAddVcId(descr,type,value) rvSdpMediaDescrAddVcIdN(descr,type,value,strlen(value))

RV_SDP_DECLSPEC RvSize_t rvSdpMediaDescrGetVcIdNum(const RvSdpMediaDescr* descr);
RV_SDP_DECLSPEC RvSdpVcId rvSdpMediaDescrGetVcIdType(const RvSdpMediaDescr* descr, RvSize_t idx);
RV_SDP_DECLSPEC const char *rvSdpMediaDescrGetVcIdValue(RvSdpMediaDescr* descr, RvSize_t idx);

#if defined(__cplusplus)
}
#endif

#endif /* RV_SDPMEDIA_H */
