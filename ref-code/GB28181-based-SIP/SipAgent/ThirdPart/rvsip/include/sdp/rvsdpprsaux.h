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

#ifndef RV_SDP_PRSAUX_H
#define RV_SDP_PRSAUX_H

#include "rvsdpmsg.h"
#include "rvstr.h"

#if defined(__cplusplus)
extern "C" {
#endif

#if !defined(RV_SDP_DECLSPEC)
#define RV_SDP_DECLSPEC
#endif

typedef enum {
    RV_SDPPARSER_STOP_ZERO,
    RV_SDPPARSER_STOP_BLANKLINE,
    RV_SDPPARSER_STOP_DOTLINE,
    RV_SDPPARSER_STOP_CLOSEBRACE,
    RV_SDPPARSER_PARSING,
    RV_SDPPARSER_PARSING_MEDIA,
    RV_SDPPARSER_STOP_ALLOCFAIL = RV_SDPSTATUS_ALLOCFAIL,
    RV_SDPPARSER_STOP_ERROR = RV_SDPSTATUS_PARSEFAIL
} RvSdpParseStatus;

typedef struct {
    RvSdpParseStatus stat;

    char * cur_token;
    char * cur_line;
//#if defined(RV_SDP_CHECK_BAD_SYNTAX)
    RvSdpGenericFieldPtr cur_reparse_field;
//#endif
    RvpStrPtrN          cur_nettype;
    RvpStrPtrN          cur_addrtype;
    RvpStrPtrN          cur_addr;
    RvSdpMsg *          cur_sdp;
    RvSdpMediaDescr *   cur_media_descr;
    RvSdpCommonFields * cur_sdp_fields;
    RvSdpSessionTime *  cur_session_time;
    RvSdpTypedTime      cur_typed_time;
    RvSdpRepeatInterval * cur_repeat;
    int                 ttl,num_addr;

    int                 vcid_type[4];
    int                 vcid_len[4];
    RvStringList        vcid_value;
    RvAlloc             *alloc;

} RvSdpParserState_;

struct rvSdpParser_pcb_struct;

#if defined(RV_SDP_CHECK_BAD_SYNTAX)
RV_SDP_DECLSPEC void rvSdpParseAuxAddBadSyntaxSessionTime(struct rvSdpParser_pcb_struct* pcb,char *bad_syntax);
RV_SDP_DECLSPEC void rvSdpMsgSetBadSyntxField(struct rvSdpParser_pcb_struct* pcb,  char *s,int sLen);

#endif

RV_SDP_DECLSPEC void rvSdpParseAuxAddSessionTime(struct rvSdpParser_pcb_struct* pcb,RvUint32 start,RvUint32 stop);
RV_SDP_DECLSPEC void rvSdpParseAuxAddSessionRepeatField(struct rvSdpParser_pcb_struct* pcb,RvSdpTypedTime time);
RV_SDP_DECLSPEC void rvSdpParseAuxSetRepeatActiveDuration(struct rvSdpParser_pcb_struct* pcb,RvSdpTypedTime time);
RV_SDP_DECLSPEC void rvSdpParseAuxAddRepeatOffset(struct rvSdpParser_pcb_struct* pcb,RvSdpTypedTime time);
RV_SDP_DECLSPEC void rvSdpParseAuxAddZoneAdjustment(struct rvSdpParser_pcb_struct* pcb,RvUint32 time,RvInt32 offset_time,RvSdpTimeUnit offset_units);
RV_SDP_DECLSPEC void rvSdpParseAuxAddPhone(struct rvSdpParser_pcb_struct* pcb,const char * phone_number,RvSize_t plen,const char* text,RvSize_t tlen);
RV_SDP_DECLSPEC void  rvSdpParseAuxSetURI(struct rvSdpParser_pcb_struct* pcb,char *uri,RvSize_t uri_len);
RV_SDP_DECLSPEC void rvSdpParserAuxAddEmail(struct rvSdpParser_pcb_struct* pcb,char *e,int e_len,char *s, int s_len);
RV_SDP_DECLSPEC void rvSdpParseAuxSetType(struct rvSdpParser_pcb_struct *pcb,int type);
RV_SDP_DECLSPEC void rvSdpParseAuxResetType(struct rvSdpParser_pcb_struct *pcb);
RV_SDP_DECLSPEC void rvSdpParseAuxAddSdpMedia(struct rvSdpParser_pcb_struct* pcb,RvpStrPtrN media,int port,int subport,RvpStrPtrN proto_);
RV_SDP_DECLSPEC void rvSdpParseAuxAddSdpMediaNAS(struct rvSdpParser_pcb_struct* pcb,int port,int subport,char * access_method,RvSize_t len);
RV_SDP_DECLSPEC void rvSdpParserAuxSetDescrCtrlMethodN(struct rvSdpParser_pcb_struct* pcb,const char* cm,RvSize_t);
RV_SDP_DECLSPEC void rvSdpParseAuxAddMediaDescrFormatN(struct rvSdpParser_pcb_struct* pcb,const char* fmt,RvSize_t len);
RV_SDP_DECLSPEC RvSdpRtpMap *  rvSdpParseAuxAddRtpMap(struct rvSdpParser_pcb_struct* pcb,int payload,const char * encoding_name,RvSize_t len,int rate);

RV_SDP_DECLSPEC void rvSdpParserAuxSaveAddr(struct rvSdpParser_pcb_struct* pcb,const char * nettype,RvSize_t nlen,
                            const char * addrtype,RvSize_t alen,const char * connaddr,RvSize_t calen);

RV_SDP_DECLSPEC void rvSdpParserAuxSetConnectionN(struct rvSdpParser_pcb_struct* pcb);


RV_SDP_DECLSPEC void rvSdpParserAuxSetOriginN(struct rvSdpParser_pcb_struct* pcb,RvSdpMsg * sdp,const char * username,RvSize_t ulen,
                                  const char * sess_id,RvSize_t slen,const char * version,RvSize_t vlen);

#if defined(RV_SDP_CHECK_BAD_SYNTAX)
RV_SDP_DECLSPEC void rvSdpParserAuxSetBadSyntaxOrigin(struct rvSdpParser_pcb_struct* pcb,RvSdpMsg * sdp,const char * bad_syntax);
RV_SDP_DECLSPEC void rvSdpParserAuxSetBadSyntaxBandwidth(struct rvSdpParser_pcb_struct*,RvSdpCommonFields *fields,const char * bad_syntax);
RV_SDP_DECLSPEC void rvSdpParserAuxSetBadSyntaxKeyN(struct rvSdpParser_pcb_struct * pcb,const char * badSyntax) ;
RV_SDP_DECLSPEC void rvSdpParserAuxSetBadSyntaxConnection(struct rvSdpParser_pcb_struct* pcb,char *bad_syntax) ;
RV_SDP_DECLSPEC void rvSdpMsgSetBadSyntxFieldM(struct rvSdpParser_pcb_struct * pcb ,char *s,int sLen);

#endif

RV_SDP_DECLSPEC void rvSdpParserAuxSetKeyN(struct rvSdpParser_pcb_struct* pcb,RvpStrPtrN key_type,const char * data,int data_len);

void rvSdpParseAuxClearCurMediaDescr(struct rvSdpParser_pcb_struct * pcb);
void  rvSdpParseAuxClearRepeat(struct rvSdpParser_pcb_struct * pcb);
void rvSdpParseAuxSetBandwidth(struct rvSdpParser_pcb_struct * pcb,char *t,RvSize_t len,int b);
/* Parsing functions */
RV_SDP_DECLSPEC RvSdpMsg * rvSdpMsgConstructParseA(RvSdpMsg * sdp,char * msg,int * len,RvSdpParseStatus * stat,RvAlloc * a);
RV_SDP_DECLSPEC RvSdpMsg * rvSdpMsgConstructParse(RvSdpMsg * sdp,char * msg,int * len,RvSdpParseStatus * stat);
/*reparse functions */
RV_SDP_DECLSPEC RvSdpConnection * rvSdpConnectionReparse(RvSdpMsg *msg, RvSdpConnection* c,int * len,RvSdpParseStatus * stat,RvAlloc * a) ;
RV_SDP_DECLSPEC RvSdpMediaDescr  *rvSdpMediaDescrReparse( RvSdpMsg *msg,RvSdpMediaDescr *m,int * len,RvSdpParseStatus * stat,RvAlloc * a) ;
RV_SDP_DECLSPEC RvSdpRtpMap * rvSdpRtpMapReparse( RvSdpMsg *msg,RvSdpRtpMap * m,int * len,RvSdpParseStatus * stat,RvAlloc * a) ;
RV_SDP_DECLSPEC RvSdpRepeatInterval * rvSdpRepeatIntReparse(RvSdpMsg *msg, RvSdpRepeatInterval* r,int * len,RvSdpParseStatus * stat,RvAlloc * a) ;
RV_SDP_DECLSPEC RvSdpBandwidth * rvSdpBandwidthReparse( RvSdpMsg *msg,RvSdpBandwidth* b,int * len,RvSdpParseStatus * stat,RvAlloc * a) ;
RV_SDP_DECLSPEC RvSdpKey * rvSdpKeyReparse( RvSdpMsg *msg,RvSdpKey *k,int * len,RvSdpParseStatus * stat,RvAlloc * a) ;
RV_SDP_DECLSPEC RvSdpPhone * rvSdpPhoneReparse( RvSdpMsg *msg,RvSdpPhone* p,int * len,RvSdpParseStatus * stat,RvAlloc * a) ;
RV_SDP_DECLSPEC RvSdpEmail * rvSdpEmailReparse( RvSdpMsg *msg,RvSdpEmail* e,int * len,RvSdpParseStatus * stat,RvAlloc * a) ;
RV_SDP_DECLSPEC RvSdpSessionTime * rvSdpSessionTimeReparse(RvSdpMsg *msg, RvSdpSessionTime* t,int * len,RvSdpParseStatus * stat,RvAlloc * a) ;
RV_SDP_DECLSPEC char * rvSdpUriReparse( RvSdpMsg *msg,char * uri,int * len,RvSdpParseStatus * stat,RvAlloc * a);
RV_SDP_DECLSPEC RvSdpMedia * rvSdpMediaReparse(RvSdpMsg *msg, RvSdpMedia* c,int * len,RvSdpParseStatus * stat,RvAlloc * a);

RV_SDP_DECLSPEC RvSdpOrigin * rvSdpOriginReparse(RvSdpMsg *msg, RvSdpOrigin* o,int * len,RvSdpParseStatus * stat,RvAlloc * a);
/* Error functions used by the parser */
RV_SDP_DECLSPEC void rvSdpParseSetSyntaxErr(void * pcb_);
RV_SDP_DECLSPEC void rvSdpParseSetSemErr(void * pcb_,const char * msg);
RV_SDP_DECLSPEC void rvSdpParseSetMemoryErr(void * pcb_);
void ParserAttachPcbToMsgBuffer(IN void * pcb_,
                                IN SdpParseMarkPrefix ePrefix);


void* rvSdpAuxAssertMem_(void* x,void* pcb);
RvStatus rvSdpAuxAssertMem2_(RvStatus s,void* pcb);

/* VcId and Transport */
void rvSdpParserAuxSetVcIdN(struct rvSdpParser_pcb_struct* pcb);
void rvSdpParserAuxSaveVcId(struct rvSdpParser_pcb_struct* pcb,int type, const char *value, int len);

#if defined(__cplusplus)
}
#endif

#endif /* RV_SDP_PRSAUX_H */
