/******************************************************************************
Filename    :rvsdpobjs.h
Description :Definitions and structures for SDP message objects

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

#ifndef RV_SDPOBJS_H
#define RV_SDPOBJS_H

#include <stdlib.h>

#include "rvsdptypes.h"
#include "rvsdplist.h"
#include "rvstring.h"
#include "rvsdpsymb.h"
#include "rvdefalloc.h"

#if !defined(RV_SDP_DECLSPEC)
#define RV_SDP_DECLSPEC
#endif

#if defined(__cplusplus)
extern "C" {
#endif

/* Version */
#define RV_SDP_SOFTWAREVERSION               0x02000000
#define rvSdpGetSoftwareVersion()            (RV_SDP_SOFTWAREVERSION)

#define rvSdpMemEqual(d,s,T) memcmp((void*)d,(void*)s,sizeof(T))

/* typedef int RvInetPort; */

#define RV_SDPFIELD_NOTSET          0
#define RV_SDPTTL_NOTSET           -1


/* Default */
#ifndef RV_SDPTIME_FULL
#define RV_SDPTIME_FULL
#endif
#ifndef RV_SDPSYMB_USESTRING
#define RV_SDPSYMB_USESTRING
#endif




/* Possible errors returned as RvSdpStatus
   from 'set' or 'add' functions */
#define rvSdpStringAssignCheckN(x,s,n) if(rvStringAssignN(x,s,n)==NULL) return RV_SDPSTATUS_ALLOCFAIL;
#define rvSdpStringAssignCheck(x,s) if(rvStringAssign(x,s)==NULL) return RV_SDPSTATUS_ALLOCFAIL;
#define rvSdpAllocCheck(var,type,a) if((var=(type*)rvAllocAllocate(a,sizeof(type)))==NULL) return RV_SDPSTATUS_ALLOCFAIL;

#if defined(RV_SDP_CHECK_BAD_SYNTAX)
#define rvSdpBadSyntaxCheckStatus(x) if (x->badSyntaxFieldSet) return RV_SDPSTATUS_PARSEFAIL;
#define rvSdpBadSyntaxCheckPtr(x) if (x->badSyntaxFieldSet) return NULL;
#define rvSdpBadSyntaxCheckInt(x) if (x->badSyntaxFieldSet) return 0;
#endif
rvSdpDeclareList(RvString)


/* Internal functions */
void rvSdpSetAllocator(RvAlloc* alloc);
RvAlloc* rvSdpGetAllocator(void);

/************* Private helper functions ****************************************/

RV_SDP_DECLSPEC RvSdpStatus rvSdpStringAssign(RvString* s, const char* v);
RV_SDP_DECLSPEC const char* rvSdpStringGetData(const RvString* s);

/************* Origin object and methods ***************************************/

typedef struct RvSdpOrigin_
{
#if defined(RV_SDP_CHECK_BAD_SYNTAX)
    int             badSyntaxFieldSet;
    char            *badSyntaxField;
#endif
    RvString        username;
    RvString        session_id;
    RvString        version;
    RvSdpNetType    nettype;    /* "IN" ,ATM                                        */
#ifdef RV_SDPSYMB_USESTRING
    RvString        nettype_str;
#endif
    RvSdpAddrType   addrtype;   /* IP4,IP6,LOCAL                                    */
#ifdef RV_SDPSYMB_USESTRING
    RvString        addrtype_str;
#endif
    RvString        address;    /* Connection address: multicast,or FQDN            */
} RvSdpOrigin;

RV_SDP_DECLSPEC RvSdpOrigin * rvSdpOriginConstructN(RvSdpOrigin *x,
                                const char* username,RvSize_t ulen,
                                const char* session_id,RvSize_t slen,
                                const char* version,RvSize_t vlen,
                                RvSdpNetType nettype,RvSdpAddrType addrtype,
                                const char* address,RvSize_t alen,RvAlloc* alloc);


#if defined(RV_SDP_CHECK_BAD_SYNTAX)

RV_SDP_DECLSPEC RvSdpOrigin * rvSdpBadSyntaxOriginConstructN(RvSdpOrigin *x,
                                                    const char* bad_syntax,RvSize_t alen,RvAlloc* alloc);

#define rvSdpBadSyntaxOriginConstructA(x,bs,alloc) rvSdpBadSyntaxOriginConstructN(x,bs,strlen(bs),alloc)

RV_SDP_DECLSPEC RvSdpOrigin * rvSdpBadSyntaxOriginConstruct(RvSdpOrigin *x,
                                                   const char* bad_syntax);
#endif

#define rvSdpOriginConstructA(x,u,s,v,n,at,a,alloc) rvSdpOriginConstructN(x,u,strlen(u),s,strlen(s),v,strlen(v),n,at,a,strlen(a),alloc)


RV_SDP_DECLSPEC RvSdpOrigin * rvSdpOriginConstruct(RvSdpOrigin *x,
                                const char* username,
                                const char* session_id,
                                const char* version,
                                RvSdpNetType nettype,RvSdpAddrType addrtype,
                                const char* address);
RV_SDP_DECLSPEC RvSdpOrigin * rvSdpOriginConstructCopyA(RvSdpOrigin *d,const RvSdpOrigin *s, RvAlloc *a);
RV_SDP_DECLSPEC RvSdpOrigin * rvSdpOriginConstructCopy(RvSdpOrigin *d,const RvSdpOrigin *s);
RV_SDP_DECLSPEC void rvSdpOriginDestruct(RvSdpOrigin *x);
RV_SDP_DECLSPEC RvSdpOrigin * rvSdpOriginCopy(RvSdpOrigin *d,const RvSdpOrigin *s, RvAlloc *a);
RV_SDP_DECLSPEC RvSdpStatus rvSdpOriginSetUsername(RvSdpOrigin* x,const char* username);
/*#define   rvSdpOriginSetUsername(x,u)  rvSdpStringAssign(&(x)->username,u)*/
RV_SDP_DECLSPEC const char* rvSdpOriginGetUsername(const RvSdpOrigin* x);
/*#define   rvSdpOriginGetUsername(x)   rvSdpStringGetData(&(x)->username)*/


RV_SDP_DECLSPEC RvSdpStatus rvSdpOriginSetVersion(RvSdpOrigin* x,const char* version);
/*#define   rvSdpOriginSetVersion(x,v)  rvSdpStringAssign(&(x)->version,v)*/
RV_SDP_DECLSPEC const char* rvSdpOriginGetVersion(const RvSdpOrigin* x);
/*#define   rvSdpOriginGetVersion(x)  rvSdpStringGetData(&(x)->version)*/

RV_SDP_DECLSPEC RvSdpStatus rvSdpOriginSetSessionId(RvSdpOrigin* x,const char* id);
/*#define   rvSdpOriginSetSessionId(x,id) rvSdpStringAssign(&(x)->session_id,id)*/
RV_SDP_DECLSPEC const char* rvSdpOriginGetSessionId(const RvSdpOrigin* x);
/*#define   rvSdpOriginGetSessionId(x) rvSdpStringGetData(&(x)->session_id)*/

/*void rvSdpOriginSetNetType(RvSdpOrigin* x,RvSdpNetType type);*/
#define rvSdpOriginSetNetType(x,t)  ((x)->nettype=t)
RV_SDP_DECLSPEC RvSdpNetType rvSdpOriginGetNetType(const RvSdpOrigin* x);
/*#define   rvSdpOriginGetNetType(x) ((x)->nettype)*/

RV_SDP_DECLSPEC RvSdpStatus rvSdpOriginSetNetTypeStr(RvSdpOrigin* x,const char* type);
RV_SDP_DECLSPEC RvSdpStatus rvSdpOriginSetNetTypeStrN(RvSdpOrigin* x,const char* type,RvSize_t n);
RV_SDP_DECLSPEC const char* rvSdpOriginGetNetTypeStr(const RvSdpOrigin* x);

/*void rvSdpOriginSetAddressType(RvSdpOrigin* x,RvSdpAddrType type);*/
#define rvSdpOriginSetAddressType(x,type) ((x)->addrtype=type)
RV_SDP_DECLSPEC RvSdpAddrType   rvSdpOriginGetAddressType(const RvSdpOrigin* x);
/*#define   rvSdpOriginGetAddressType(x) ((x)->addrtype)*/

RV_SDP_DECLSPEC RvSdpStatus rvSdpOriginSetAddressTypeStr(RvSdpOrigin* x,const char* t);
RV_SDP_DECLSPEC RvSdpStatus rvSdpOriginSetAddressTypeStrN(RvSdpOrigin* x,const char* t,RvSize_t n);
RV_SDP_DECLSPEC const char* rvSdpOriginGetAddressTypeStr(const RvSdpOrigin* x);

RV_SDP_DECLSPEC RvSdpStatus rvSdpOriginSetAddress(RvSdpOrigin* x,const char* addr);
/*#define   rvSdpOriginSetAddress(x,a) rvSdpStringAssign(&(x)->address,a)*/
RV_SDP_DECLSPEC const char* rvSdpOriginGetAddress(const RvSdpOrigin* x);
/*#define   rvSdpOriginGetAddress(x) rvSdpStringGetData(&(x)->address)*/

#if defined(RV_SDP_CHECK_BAD_SYNTAX)
#define rvSdpOriginGetBadSyntax(x) rvSdpStringGetData(&(x)->badSyntaxField)
#define rvSdpOriginIsBadSyntax(x) (x)->badSyntaxFieldSet
#endif

/************* Email object and methods ***************************************/

typedef struct  RvSdpEmail_
{
#if defined(RV_SDP_CHECK_BAD_SYNTAX)
    RvString    badSyntaxField;
    RvBool      badSyntaxFieldSet;
#endif
    RvString address;
    RvString text;
} RvSdpEmail;

rvSdpDeclareList(RvSdpEmail)
typedef RvSdpList(RvSdpEmail) RvSdpEmailList;
/* RvSdpEmailList* rvSdpEmailListConstruct(RvSdpEmailList *x); */
#define rvSdpEmailListConstructA rvListConstruct(RvSdpEmail)
#define rvSdpEmailListConstructCopy rvListConstructCopy(RvSdpEmail)
#define rvSdpEmailListDestruct rvListDestruct(RvSdpEmail)
#define rvSdpEmailListCopy rvListCopy(RvSdpEmail)
#define rvSdpEmailListEqual rvListEqual(RvSdpEmail)
#define rvSdpEmailListAdd rvListPushBack(RvSdpEmail)
#define rvSdpEmailListClear rvListClear(RvSdpEmail)
#define rvSdpEmailListGetSize rvListSize
#define rvSdpEmailListGetElem rvListAt(RvSdpEmail)

RV_SDP_DECLSPEC RvSdpEmail* rvSdpEmailConstructN(RvSdpEmail* x,
                                const char* address,RvSize_t alen,
                                const char* text,RvSize_t tlen,
                                RvAlloc* alloc);

#if defined(RV_SDP_CHECK_BAD_SYNTAX)
RV_SDP_DECLSPEC RvSdpEmail* rvSdpBadSyntaxEmailConstructN(RvSdpEmail* x,
                                                 const char* bad_syntax,RvSize_t len,
                                                 RvAlloc* alloc);

#define rvSdpBadSyntaxEmailConstructA(x,bs,alloc) rvSdpBadSyntaxEmailConstructN(x,bs,strlen(bs),alloc)

RV_SDP_DECLSPEC RvSdpEmail* rvSdpBadSyntaxEmailConstruct(RvSdpEmail* x,
                                                const char* badsyntax);

#define rvSdpEmailGetBadSyntax(x) rvSdpStringGetData(&(x)->badSyntaxField)
#define rvSdpEmailIsBadSyntax(x) (x)->badSyntaxFieldSet

#endif

#define rvSdpEmailConstructA(x,a,t,alloc) rvSdpEmailConstructN(x,a,strlen(a),t,strlen(t),alloc)

RV_SDP_DECLSPEC RvSdpEmail* rvSdpEmailConstruct(RvSdpEmail* x,
                                                const char* address,
                                                const char* text);
RV_SDP_DECLSPEC RvSdpEmail* rvSdpEmailConstructCopyA(RvSdpEmail *d,const RvSdpEmail *s,RvAlloc* alloc);

RV_SDP_DECLSPEC RvSdpEmail* rvSdpEmailConstructCopy(RvSdpEmail *d,const RvSdpEmail *s);
RV_SDP_DECLSPEC void rvSdpEmailDestruct(RvSdpEmail *x);
RV_SDP_DECLSPEC RvSdpEmail* rvSdpEmailCopy(RvSdpEmail *d,const RvSdpEmail *s);

/*void rvSdpEmailSetAddress*/
RV_SDP_DECLSPEC RvSdpStatus rvSdpEmailSetAddress(RvSdpEmail* x,const char* addr);
RV_SDP_DECLSPEC const char* rvSdpEmailGetAddress(const RvSdpEmail* x);
/*void rvSdpEmailSetText(RvSdpEmail* x,const char* text);*/
RV_SDP_DECLSPEC RvSdpStatus rvSdpEmailSetText(RvSdpEmail* x,const char* text);
RV_SDP_DECLSPEC const char* rvSdpEmailGetText(const RvSdpEmail* x);

#define RvSdpEmailConstructCopy rvSdpEmailConstructCopyA
#define RvSdpEmailCopy          rvSdpEmailCopy
#define RvSdpEmailDestruct      rvSdpEmailDestruct
#define RvSdpEmailEqual(d,s)    rvSdpMemEqual(d,s,RvSdpEmail)

/************** Phone fields ******************************/

typedef struct RvSdpPhone_
{
#if defined(RV_SDP_CHECK_BAD_SYNTAX)
    RvString    badSyntaxField;
    RvBool   badSyntaxFieldSet;
#endif
    RvString phone_number;
    RvString text;
} RvSdpPhone;

rvSdpDeclareList(RvSdpPhone)
typedef RvSdpList(RvSdpPhone) RvSdpPhoneList;
/* RvSdpPhoneList* rvSdpPhoneListConstruct(RvSdpPhoneList *x); */
#define rvSdpPhoneListConstructA rvListConstruct(RvSdpPhone)
#define rvSdpPhoneListConstructCopy rvListConstructCopy(RvSdpPhone)
#define rvSdpPhoneListDestruct rvListDestruct(RvSdpPhone)
#define rvSdpPhoneListCopy rvListCopy(RvSdpPhone)
#define rvSdpPhoneListEqual rvListEqual(RvSdpPhone)
#define rvSdpPhoneListAdd rvListPushBack(RvSdpPhone)
#define rvSdpPhoneListClear rvListClear(RvSdpPhone)
#define rvSdpPhoneListGetSize rvListSize
#define rvSdpPhoneListGetElem rvListAt(RvSdpPhone)

RV_SDP_DECLSPEC RvSdpPhone* rvSdpPhoneConstructN(RvSdpPhone* x,
                                const char* number,RvSize_t nlen,
                                const char* text,RvSize_t tlen,
                                RvAlloc* alloc);

#if defined(RV_SDP_CHECK_BAD_SYNTAX)

RV_SDP_DECLSPEC RvSdpPhone* rvSdpBadSyntaxPhoneConstructN(RvSdpPhone* x,
                                                 const char* badSyntax,RvSize_t len,
                                                 RvAlloc* alloc);

#define rvSdpBadSyntaxPhoneConstructA(x,bs,alloc) rvSdpBadSyntaxPhoneConstructN(x,bs,strlen(bs),alloc)

RV_SDP_DECLSPEC RvSdpPhone* rvSdpBadSyntaxPhoneConstruct(RvSdpPhone* x,
                                                const char* badSyntax);

#define rvSdpPhoneGetBadSyntax(x) rvSdpStringGetData(&(x)->badSyntaxField)
#define rvSdpPhoneIsBadSyntax(x) x->badSyntaxFieldSet

#endif

#define rvSdpPhoneConstructA(x,n,t,alloc) rvSdpPhoneConstructN(x,n,strlen(n),t,strlen(t),alloc)
RV_SDP_DECLSPEC RvSdpPhone* rvSdpPhoneConstruct(RvSdpPhone* x,
                                                const char* number,const char* text);

RV_SDP_DECLSPEC RvSdpPhone* rvSdpPhoneConstructCopyA(RvSdpPhone *d,const RvSdpPhone *s,RvAlloc* alloc);
RV_SDP_DECLSPEC RvSdpPhone* rvSdpPhoneConstructCopy(RvSdpPhone *d,const RvSdpPhone *s);
RV_SDP_DECLSPEC void rvSdpPhoneDestruct(RvSdpPhone *x);
RV_SDP_DECLSPEC RvSdpPhone* rvSdpPhoneCopy(RvSdpPhone *d,const RvSdpPhone *s);

RV_SDP_DECLSPEC RvSdpStatus rvSdpPhoneSetNumber(RvSdpPhone* x,const char* number);
RV_SDP_DECLSPEC const char* rvSdpPhoneGetNumber(const RvSdpPhone* x);
RV_SDP_DECLSPEC RvSdpStatus   rvSdpPhoneSetText(RvSdpPhone* x,const char* text);

RV_SDP_DECLSPEC const char* rvSdpPhoneGetText(const RvSdpPhone* x);

#define RvSdpPhoneConstructCopy rvSdpPhoneConstructCopyA
#define RvSdpPhoneDestruct  rvSdpPhoneDestruct
#define RvSdpPhoneCopy  rvSdpPhoneCopy
#define RvSdpPhoneEqual(d,s)  rvSdpMemEqual(d,s,RvSdpPhone)

/************** Typed time fields ******************************/

typedef struct {
    RvSdpTimeUnit type;
    RvUint32  time;
} RvSdpTypedTime;

rvSdpDeclareList(RvSdpTypedTime)
typedef RvSdpList(RvSdpTypedTime) RvSdpTypedTimeList;
RV_SDP_DECLSPEC RvSdpTypedTimeList* rvSdpTypedTimeListConstruct(RvSdpTypedTimeList *x);
#define rvSdpTypedTimeListConstructA rvListConstruct(RvSdpTypedTime)
#define rvSdpTypedTimeListConstructCopy rvListConstructCopy(RvSdpTypedTime)
#define rvSdpTypedTimeListDestruct rvListDestruct(RvSdpTypedTime)
#define rvSdpTypedTimeListCopy rvListCopy(RvSdpTypedTime)
#define rvSdpTypedTimeListEqual rvListEqual(RvSdpTypedTime)
#define rvSdpTypedTimeListAdd rvListPushBack(RvSdpTypedTime)
#define rvSdpTypedTimeListClear rvListClear(RvSdpTypedTime)
#define rvSdpTypedTimeListGetSize rvListSize
#define rvSdpTypedTimeListGetElem rvListAt(RvSdpTypedTime)

RV_SDP_DECLSPEC RvSdpTypedTime* rvSdpTypedTimeConstruct(RvSdpTypedTime* x,RvSdpTimeUnit units,RvUint32 time);
RV_SDP_DECLSPEC RvSdpTypedTime* rvSdpTypedTimeConstructA(RvSdpTypedTime* x,RvSdpTimeUnit units,RvUint32 time,RvAlloc* a);
RV_SDP_DECLSPEC RvSdpTypedTime* rvSdpTypedTimeConstructCopy(RvSdpTypedTime *d,const RvSdpTypedTime *s,RvAlloc* alloc);
RV_SDP_DECLSPEC void rvSdpTypedTimeDestruct(RvSdpTypedTime* x);
RV_SDP_DECLSPEC RvSdpTypedTime* rvSdpTypedTimeCopy(RvSdpTypedTime *d,const RvSdpTypedTime *s,RvAlloc* alloc);

RV_SDP_DECLSPEC RvSdpTimeUnit rvSdpTypedTimeGetUnits(const RvSdpTypedTime* x);
#define rvSdpTypedTimeSetUnits(x,t) ((x)->type = t)

RvUint32 rvSdpTypedTimeGetTime(const RvSdpTypedTime* x);
#define rvSdpTypedTimeSetTime(x,t) ((x)->time = t)
/* #define RvSdpTypedTimeConstruct  rvSdpTypedTimeConstruct */
#define RvSdpTypedTimeConstructCopy rvSdpTypedTimeConstructCopy
#define RvSdpTypedTimeDestruct  rvSdpTypedTimeDestruct
#define RvSdpTypedTimeEqual(d,s)  rvSdpMemEqual(d,s,RvSdpTypedTime)

/****** Repeat time object and methods **************************/

typedef struct RvSdpRepeatInterval_{
    RvSdpTypedTime interval;
    RvSdpTypedTime duration;
    RvSdpTypedTimeList offset;
#if defined(RV_SDP_CHECK_BAD_SYNTAX)
    int             badSyntaxFieldSet;
    char            *badSyntaxField;
#endif
} RvSdpRepeatInterval;

rvSdpDeclareList(RvSdpRepeatInterval)
typedef RvSdpList(RvSdpRepeatInterval) RvSdpRepeatIntervalList;
/* RvSdpRepeatIntervalList* rvSdpRepeatIntervalListConstruct(RvSdpRepeatIntervalList *x); */
#define rvSdpRepeatIntervalListConstructA rvListConstruct(RvSdpRepeatInterval)
#define rvSdpRepeatIntervalListConstructCopy rvListConstructCopy(RvSdpRepeatInterval)
#define rvSdpRepeatIntervalListDestruct rvListDestruct(RvSdpRepeatInterval)
#define rvSdpRepeatIntervalListCopy rvListCopy(RvSdpRepeatInterval)
#define rvSdpRepeatIntervalListEqual rvListEqual(RvSdpRepeatInterval)
#define rvSdpRepeatIntervalListAdd rvListPushBack(RvSdpRepeatInterval)
#define rvSdpRepeatIntervalListClear rvListClear(RvSdpRepeatInterval)
#define rvSdpRepeatIntervalListGetSize rvListSize
#define rvSdpRepeatIntervalListGetElem rvListAt(RvSdpRepeatInterval)

#if defined(RV_SDP_CHECK_BAD_SYNTAX)
RV_SDP_DECLSPEC RvSdpRepeatInterval* rvSdpBadSyntaxRepeatIntervalConstructA(RvSdpRepeatInterval* x,char *badSytax,int len,RvAlloc* a) ;

RV_SDP_DECLSPEC RvSdpRepeatInterval* rvSdpBadSyntaxRepeatIntervalConstruct(RvSdpRepeatInterval* x,
                                                                  char *badSyntax,int len);

#define rvSdpRepeatIntervalIsBadSyntax(x)   x->badSyntaxFieldSet
#define rvSdpRepeatIntervalGetBadSyntax(x)  rvSdpStringGetData(&(x)->badSyntaxField)

#endif

RV_SDP_DECLSPEC RvSdpRepeatInterval* rvSdpRepeatIntervalConstructA(RvSdpRepeatInterval* x,
                               RvUint32 time,RvSdpTimeUnit t_units,
                               RvUint32 duration ,RvSdpTimeUnit d_units,RvAlloc* a) ;
RV_SDP_DECLSPEC RvSdpRepeatInterval* rvSdpRepeatIntervalConstruct(RvSdpRepeatInterval* x,
                               RvUint32 time,RvSdpTimeUnit t_units,
                               RvUint32 duration ,RvSdpTimeUnit d_units);
RV_SDP_DECLSPEC RvSdpRepeatInterval* rvSdpRepeatIntervalConstructCopy(RvSdpRepeatInterval *d,const RvSdpRepeatInterval *s,RvAlloc* alloc);
RV_SDP_DECLSPEC void rvSdpRepeatIntervalDestruct(RvSdpRepeatInterval* x);
RV_SDP_DECLSPEC RvSdpRepeatInterval* rvSdpRepeatIntervalCopy(RvSdpRepeatInterval *d,const RvSdpRepeatInterval *s);

RV_SDP_DECLSPEC RvSdpTimeUnit   rvSdpRepeatIntervalGetDurationUnits(const RvSdpRepeatInterval* x);
/*#define   rvSdpRepeatIntervalGetDurationUnits(x) rvSdpTypedTimeGetUnits(&(x)->duration)*/
#define rvSdpRepeatIntervalSetDurationUnits(x, unit) rvSdpTypedTimeSetUnits(&(x)->duration, unit)

RV_SDP_DECLSPEC RvUint32 rvSdpRepeatIntervalGetDurationTime(const RvSdpRepeatInterval* x);
/*#define   rvSdpRepeatIntervalGetDurationTime(x) rvSdpTypedTimeGetTime(&(x)->duration)*/
#define rvSdpRepeatIntervalSetDurationTime(x, time) rvSdpTypedTimeSetTime(&(x)->duration,time)

RV_SDP_DECLSPEC RvSdpTimeUnit   rvSdpRepeatIntervalGetIntervalUnits(const RvSdpRepeatInterval* x);
/*#define   rvSdpRepeatIntervalGetIntervalUnits(x) rvSdpTypedTimeGetUnits(&(x)->interval)*/
#define rvSdpRepeatIntervalSetIntervalUnits(x, unit) rvSdpTypedTimeSetUnits(&(x)->interval, unit)

RV_SDP_DECLSPEC RvUint32 rvSdpRepeatIntervalGetIntervalTime(const RvSdpRepeatInterval* x);
/*#define   rvSdpRepeatIntervalGetIntervalTime(x) rvSdpTypedTimeGetTime(&x->interval)*/
#define rvSdpRepeatIntervalSetIntervalTime(x,time) rvSdpTypedTimeSetTime(&x->interval, time)
RV_SDP_DECLSPEC RvSdpStatus rvSdpRepeatIntervalAddOffset(RvSdpRepeatInterval* repeat,RvUint32 time,RvSdpTimeUnit units);
RV_SDP_DECLSPEC void rvSdpRepeatIntervalClearOffset(RvSdpRepeatInterval* repeat);
RV_SDP_DECLSPEC RvSize_t rvSdpRepeatIntervalGetNumOfOffset(RvSdpRepeatInterval* repeat);

#ifdef RV_SDPTIME_FULL
RV_SDP_DECLSPEC RvUint32 rvSdpRepeatIntervalGetOffsetTime(RvSdpRepeatInterval* repeat,RvSize_t i);
RV_SDP_DECLSPEC RvSdpTimeUnit rvSdpRepeatIntervalGetOffsetUnits(RvSdpRepeatInterval* repeat,RvSize_t i);
#endif

#define RvSdpRepeatIntervalConstructCopy    rvSdpRepeatIntervalConstructCopy
#define RvSdpRepeatIntervalDestruct         rvSdpRepeatIntervalDestruct
#define RvSdpRepeatIntervalCopy             rvSdpRepeatIntervalCopy
#define RvSdpRepeatIntervalEqual(d,s)       rvSdpMemEqual(d,s,RvSdpRepeatInterval)
/******** Session time object and methods **********************/

typedef struct RvSdpSessionTime_
{
#if defined(RV_SDP_CHECK_BAD_SYNTAX)
    int             badSyntaxFieldSet;
    char            *badSyntaxField;
#endif
    RvUint32                start;
    RvUint32                end;
#ifdef RV_SDPTIME_FULL
    RvSdpRepeatIntervalList repeat_list;
#endif
} RvSdpSessionTime;

rvSdpDeclareList(RvSdpSessionTime)

typedef RvSdpList(RvSdpSessionTime) RvSdpSessionTimeList;
/* RvSdpSessionTimeList* rvSdpSessionTimeListConstruct(RvSdpSessionTimeList *x); */
#define rvSdpSessionTimeListConstructA rvListConstruct(RvSdpSessionTime)
#define rvSdpSessionTimeListConstructCopy rvListConstructCopy(RvSdpSessionTime)
#define rvSdpSessionTimeListDestruct rvListDestruct(RvSdpSessionTime)
#define rvSdpSessionTimeListCopy rvListCopy(RvSdpSessionTime)
#define rvSdpSessionTimeListEqual rvListEqual(RvSdpSessionTime)
#define rvSdpSessionTimeListAdd rvListPushBack(RvSdpSessionTime)
#define rvSdpSessionTimeListClear rvListClear(RvSdpSessionTime)
#define rvSdpSessionTimeListGetSize rvListSize
#define rvSdpSessionTimeListGetElem rvListAt(RvSdpSessionTime)

RV_SDP_DECLSPEC RvSdpSessionTime* rvSdpSessionTimeConstructN(RvSdpSessionTime* x,
                         RvUint32 start,RvUint32 end,
                         RvAlloc* alloc) ;

#if defined(RV_SDP_CHECK_BAD_SYNTAX)
RV_SDP_DECLSPEC RvSdpSessionTime* rvSdpBadSyntaxSessionTimeConstructN(RvSdpSessionTime* x,
                                                             char *bad_syntax,int len,
                                                             RvAlloc* alloc) ;

#define rvSdpBadSyntaxSessionTimeConstructA(x,bs,alloc) rvSdpBadSyntaxSessionTimeConstructN(x,bs,strlen(bs),alloc)

RV_SDP_DECLSPEC RvSdpSessionTime* rvSdpBadSyntaxSessionTimeConstruct(RvSdpSessionTime* x,
                                                            char *bad_syntax);

#define rvSdpSessionTimeGetBadSyntax(x)  rvSdpStringGetData(&(x)->badSyntaxField)
#define rvSdpSessionTimeIsBadSyntax(x)  ((x)->badSyntaxFieldSet)

#endif

#define rvSdpSessionTimeConstructA(x,s,e,alloc) rvSdpSessionTimeConstructN(x,s,e,alloc)


RV_SDP_DECLSPEC RvSdpSessionTime* rvSdpSessionTimeConstruct(RvSdpSessionTime* x,
                                                            RvUint32 start,RvUint32 end);

RV_SDP_DECLSPEC RvSdpSessionTime* rvSdpSessionTimeConstructCopyA(RvSdpSessionTime *d,const RvSdpSessionTime *s,RvAlloc* alloc) ;
RV_SDP_DECLSPEC RvSdpSessionTime* rvSdpSessionTimeConstructCopy(RvSdpSessionTime *d,const RvSdpSessionTime *s) ;
RV_SDP_DECLSPEC void rvSdpSessionTimeDestruct(RvSdpSessionTime *x) ;
RV_SDP_DECLSPEC RvSdpSessionTime* rvSdpSessionTimeCopy(RvSdpSessionTime *d,const RvSdpSessionTime *s) ;
RV_SDP_DECLSPEC RvSdpRepeatInterval* rvSdpSessionTimeAddRepeatInterval(RvSdpSessionTime* session,
                                                  RvUint32 time,RvSdpTimeUnit t_units,
                                                  RvUint32 duration ,RvSdpTimeUnit d_units);

RV_SDP_DECLSPEC RvUint32 rvSdpSessionTimeGetStart(const RvSdpSessionTime* x);
/*#define rvSdpSessionTimeGetStart(x) ((x)->start)*/

/*void  rvSdpSessionTimeSetStart(const RvSdpSessionTime* x,RvUint32 start);*/
#define rvSdpSessionTimeSetStart(x,s) ((x)->start=s)

RV_SDP_DECLSPEC RvUint32 rvSdpSessionTimeGetEnd(const RvSdpSessionTime* x);
/*#define rvSdpSessionTimeGetEnd(x)  ((x)->end)*/
/*void rvSdpSessionTimeSetEnd(const RvSdpSessionTime* x,RvUint32 end);*/
#define rvSdpSessionTimeSetEnd(x,e)  ((x)->end=e)

RV_SDP_DECLSPEC RvSize_t rvSdpSessionTimeGetNumOfRepeatInterval(const RvSdpSessionTime* x);

RV_SDP_DECLSPEC RvSdpRepeatInterval* rvSdpSessionTimeGetRepeatInterval(const RvSdpSessionTime* x,RvSize_t i);
/*#define rvSdpSessionTimeGetRepeatInterval(x,i) rvSdpRepeatIntervalListGetElem(&(x)->repeat_list,i)*/

#define RvSdpSessionTimeConstructCopy   rvSdpSessionTimeConstructCopyA
#define RvSdpSessionTimeDestruct        rvSdpSessionTimeDestruct
#define RvSdpSessionTimeCopy            rvSdpSessionTimeCopy
#define RvSdpSessionTimeEqual(d,s)      rvSdpMemEqual(d,s,RvSdpSessionTime)

/**** Zone adjust object and methods ****************************/

typedef struct RvSdpTimeZoneAdjust_{
    RvUint32        adjustment_time;
    RvInt32         offset_time;
    RvSdpTimeUnit   offset_units;
} RvSdpTimeZoneAdjust;

rvSdpDeclareList(RvSdpTimeZoneAdjust)
typedef RvSdpList(RvSdpTimeZoneAdjust) RvSdpTimeZoneAdjustList;
#define rvSdpTimeZoneAdjustListConstructA rvListConstruct(RvSdpTimeZoneAdjust)
#define rvSdpTimeZoneAdjustListConstructCopy rvListConstructCopy(RvSdpTimeZoneAdjust)
#define rvSdpTimeZoneAdjustListDestruct rvListDestruct(RvSdpTimeZoneAdjust)
#define rvSdpTimeZoneAdjustListCopy rvListCopy(RvSdpTimeZoneAdjust)
#define rvSdpTimeZoneAdjustListEqual rvListEqual(RvSdpTimeZoneAdjust)
#define rvSdpTimeZoneAdjustListAdd rvListPushBack(RvSdpTimeZoneAdjust)
#define rvSdpTimeZoneAdjustListClear rvListClear(RvSdpTimeZoneAdjust)
#define rvSdpTimeZoneAdjustListGetSize rvListSize
#define rvSdpTimeZoneAdjustListGetElem rvListAt(RvSdpTimeZoneAdjust)

/*
typedef struct {
    RvSdpSessionTimeList        session_time;
    RvSdpTimeZoneAdjustList     zone_adjustment_list;
} RvSdpTime;
*/

RV_SDP_DECLSPEC RvSdpTimeZoneAdjust* rvSdpTimeZoneAdjustConstructN(RvSdpTimeZoneAdjust* x,RvUint32 time,RvInt32 offset_time,RvSdpTimeUnit offset_units) ;
#define rvSdpTimeZoneAdjustConstructA(x,t,o,u,alloc) rvSdpTimeZoneAdjustConstructN(x,t,o,u)
RV_SDP_DECLSPEC RvSdpTimeZoneAdjust* rvSdpTimeZoneAdjustConstruct(RvSdpTimeZoneAdjust* x,RvUint32 time,RvInt32 offset_time,RvSdpTimeUnit offset_units) ;

RV_SDP_DECLSPEC RvSdpTimeZoneAdjust* rvSdpTimeZoneAdjustConstructCopy(RvSdpTimeZoneAdjust *d,const RvSdpTimeZoneAdjust *s,RvAlloc* alloc) ;
RV_SDP_DECLSPEC void rvSdpTimeZoneAdjustDestruct(RvSdpTimeZoneAdjust *x) ;
RV_SDP_DECLSPEC RvSdpTimeZoneAdjust* rvSdpTimeZoneAdjustCopy(RvSdpTimeZoneAdjust *d,const RvSdpTimeZoneAdjust *s) ;

/*RvUint32 rvSdpTimeZoneAdjustGetTime(const RvSdpTimeZoneAdjust* x);*/
#define rvSdpTimeZoneAdjustSetTime(x,t) ((x)->adjustment_time =t)
#define rvSdpTimeZoneAdjustGetTime(x) ((x)->adjustment_time)

/*RvInt32 rvSdpTimeZoneAdjustGetOffsetTime(const RvSdpTimeZoneAdjust* x);*/
#define  rvSdpTimeZoneAdjustSetOffsetTime(x,t) ((x)->offset_time=t)
#define  rvSdpTimeZoneAdjustGetOffsetTime(x) ((x)->offset_time)

/*RvSdpTimeUnit rvSdpTimeZoneAdjustGetOffsetUnits(const RvSdpTimeZoneAdjust* x);*/
#define  rvSdpTimeZoneAdjustSetOffsetUnits(x,tu) ((x)->offset_units=tu)
#define  rvSdpTimeZoneAdjustGetOffsetUnits(x) ((x)->offset_units)

#define RvSdpTimeZoneAdjustConstructCopy rvSdpTimeZoneAdjustConstructCopy
#define RvSdpTimeZoneAdjustDestruct rvSdpTimeZoneAdjustDestruct
#define RvSdpTimeZoneAdjustCopy rvSdpTimeZoneAdjustCopy
#define RvSdpTimeZoneAdjustEqual(d,s) rvSdpMemEqual(d,s,RvSdpTimeZoneAdjust)

/******************* Bandwidth methods ********************************/

#define RV_SDPBANDWIDTH_MAXLEN 10

typedef struct RvSdpBandwidth_
{
#if defined(RV_SDP_CHECK_BAD_SYNTAX)
    RvString    badSyntaxField;
    RvBool      badSyntaxFieldSet;
#endif
    RvString    type;
    RvUint32    value;
} RvSdpBandwidth;

RV_SDP_DECLSPEC RvSdpBandwidth* rvSdpBandwidthConstructN(RvSdpBandwidth* x,const char* type,int tlen,int value,RvAlloc* alloc);

#if defined(RV_SDP_CHECK_BAD_SYNTAX)

RV_SDP_DECLSPEC RvSdpBandwidth* rvSdpBadSyntaxBandwidthConstructN(RvSdpBandwidth* x,const char* bad_syntax,int len,RvAlloc* alloc);

#define rvSdpBadSyntaxBandwidthConstructA(x,bs,a)  rvSdpBadSyntaxBandwidthConstructN(x,bs,strlen(bs),a)

RV_SDP_DECLSPEC RvSdpBandwidth* rvSdpBadSyntaxBandwidthConstruct(RvSdpBandwidth* x,const char* bad_syntax,RvAlloc* alloc);

#define rvSdpBandwidthIsBadSyntax(x)    x->badSyntaxFieldSet
#define rvSdpBandwidthGetBadSyntax(x)   rvSdpStringGetData(&(x)->badSyntaxField)

#endif

#define rvSdpBandwidthConstructA(x,t,v,a)  rvSdpBandwidthConstructN(x,t,strlen(t),v,a)

RV_SDP_DECLSPEC RvSdpBandwidth* rvSdpBandwidthConstruct(RvSdpBandwidth* x,const char* type,int value,RvAlloc* alloc);

RV_SDP_DECLSPEC RvSdpBandwidth* rvSdpBandwidthConstructCopyA(RvSdpBandwidth *d,const RvSdpBandwidth *s,RvAlloc* alloc) ;
RV_SDP_DECLSPEC RvSdpBandwidth* rvSdpBandwidthConstructCopy(RvSdpBandwidth *d,const RvSdpBandwidth *s) ;
RV_SDP_DECLSPEC void rvSdpBandwidthDestruct(RvSdpBandwidth *x) ;
RV_SDP_DECLSPEC RvSdpBandwidth* rvSdpBandwidthCopy(RvSdpBandwidth *d,const RvSdpBandwidth *s) ;

RV_SDP_DECLSPEC const char* rvSdpBandwidthGetType(const RvSdpBandwidth* x);
/*#define rvSdpBandwidthGetType(x)   rvStringGetData(&(x)->type)*/

RV_SDP_DECLSPEC RvUint32 rvSdpBandwidthGetValue(const RvSdpBandwidth* x);
/*#define rvSdpBandwidthGetValue(x) ((x)->value)*/
RV_SDP_DECLSPEC RvSdpStatus rvSdpBandwidthSetType(RvSdpBandwidth* x,const char* type);

/*RV_SDP_DECLSPEC RvSdpStatus  rvSdpBandwidthSetValue(const RvSdpBandwidth* x,RvUint32 value);*/
#define rvSdpBandwidthSetValue(x,v) ((x)->value=v)

/******************* Connection methods ********************************/
typedef struct RvSdpConnection_
{
#if defined(RV_SDP_CHECK_BAD_SYNTAX)
    RvString    badSyntaxField;
    RvBool      badSyntaxFieldSet;
#endif
    /* Connection fields */
    RvSdpNetType    nettype;    /* "IN" ,ATM                                        */
#ifdef RV_SDPSYMB_USESTRING
    RvString        nettype_str;
#endif
    RvSdpAddrType   addrtype;   /* IP4,IP6,LOCAL                                    */
#ifdef RV_SDPSYMB_USESTRING
    RvString        addrtype_str;
#endif
    RvString        address;    /* Connection address: multicast,FQDN or Unicast    */
    int             ttl,num_addr;
} RvSdpConnection;

RV_SDP_DECLSPEC RvSdpConnection* rvSdpConnectionConstructN(RvSdpConnection *connection,
                                           RvSdpNetType nettype,
                                           RvSdpAddrType addrtype,
                                           const char* address,RvSize_t len,RvAlloc* alloc);

#if defined(RV_SDP_CHECK_BAD_SYNTAX)

RV_SDP_DECLSPEC RvSdpConnection* rvSdpBadSyntaxConnectionConstructN(RvSdpConnection *connection,
                                                           const char* bad_syntax,RvSize_t len,RvAlloc* alloc);
#define rvSdpBadSyntaxConnectionConstructA(c,bs,al) rvSdpBadSyntaxConnectionConstructN(c,bs,strlen(bs),al);

RV_SDP_DECLSPEC RvSdpConnection* rvSdpBadSyntaxConnectionConstruct(RvSdpConnection *connection,
                                                          const char* bad_syntax);
#define rvSdpConnectionSetBadSyntax(c,a)   rvSdpStringAssign(&(c)->badSyntaxField,a)

#define rvSdpConnectionGetBadSyntax(c)  rvSdpStringGetData(&(c)->badSyntaxField)
#define rvSdpConnectionIsBadSyntax(c)   c->badSyntaxFieldSet
#endif

#define rvSdpConnectionConstructA(c,n,at,a,al) rvSdpConnectionConstructN(c,n,at,a,strlen(a),al);

RV_SDP_DECLSPEC RvSdpConnection* rvSdpConnectionConstruct(RvSdpConnection *connection,
                                                          RvSdpNetType nettype,
                                                          RvSdpAddrType addrtype,
                                                          const char* address);

RV_SDP_DECLSPEC RvSdpConnection* rvSdpConnectionCopy(RvSdpConnection *d,const RvSdpConnection* s);
RV_SDP_DECLSPEC RvSdpConnection* rvSdpConnectionConstructCopyA(RvSdpConnection *d,const RvSdpConnection* s,RvAlloc* alloc);
RV_SDP_DECLSPEC RvSdpConnection* rvSdpConnectionConstructCopy(RvSdpConnection *d,const RvSdpConnection* s);
RV_SDP_DECLSPEC void rvSdpConnectionDestruct(RvSdpConnection *connection);

/*RV_SDP_DECLSPEC RvSdpStatus rvSdpConnectionSetNetType(RvSdpConnection *connection,RvSdpNetType type);*/
#define rvSdpConnectionSetNetType(c,t) ((c)->nettype=t)
RV_SDP_DECLSPEC RvSdpNetType    rvSdpConnectionGetNetType(const RvSdpConnection *connection);
/*#define rvSdpConnectionGetNetType(c) ((c)->nettype)*/

RV_SDP_DECLSPEC RvSdpStatus rvSdpConnectionSetNetTypeStr(RvSdpConnection *connection,const char* type);
RV_SDP_DECLSPEC RvSdpStatus rvSdpConnectionSetNetTypeStrN(RvSdpConnection *connection,const char* type,RvSize_t n);
RV_SDP_DECLSPEC const char* rvSdpConnectionGetNetTypeStr(const RvSdpConnection *connection);

/*void rvSdpConnectionSetAddrType(RvSdpConnection *connection,RvSdpAddrType type);*/
#define rvSdpConnectionSetAddrType(c,t) ((c)->addrtype=t)
RV_SDP_DECLSPEC RvSdpAddrType   rvSdpConnectionGetAddrType(const RvSdpConnection *connection);
/*#define rvSdpConnectionGetAddrType(c) ((c)->addrtype)*/

RV_SDP_DECLSPEC RvSdpStatus rvSdpConnectionSetAddrTypeStr(RvSdpConnection *c,const char* t);
RV_SDP_DECLSPEC RvSdpStatus rvSdpConnectionSetAddrTypeStrN(RvSdpConnection *c,const char* t,RvSize_t n);
RV_SDP_DECLSPEC const char* rvSdpConnectionGetAddrTypeStr(const RvSdpConnection* c);

RV_SDP_DECLSPEC RvSdpStatus rvSdpConnectionSetAddress(RvSdpConnection *connection,const char* addr);
/*#define rvSdpConnectionSetAddress(c,a)    rvSdpStringAssign(&(c)->address,a)*/
RV_SDP_DECLSPEC const char* rvSdpConnectionGetAddress(const RvSdpConnection *connection);
/*#define rvSdpConnectionGetAddress(c)  rvSdpStringGetData(&(c)->address) */
RV_SDP_DECLSPEC void rvSdpConnectionSetAddressTTL(RvSdpConnection *connection,int ttl);
RV_SDP_DECLSPEC int rvSdpConnectionGetAddressTTL(const RvSdpConnection *connection);
/*#define rvSdpConnectionSetAddressTTL(c,ttl) ((c)->ttl=ttl)*/
/*#define rvSdpConnectionGetAddressTTL(c)       ((c)->ttl)*/

/*void rvSdpConnectionSetAddressNum(RvSdpConnection *connection,int num);*/
#define rvSdpConnectionSetAddressNum(c,n)   ((c)->num_addr=n)
RV_SDP_DECLSPEC int rvSdpConnectionGetAddressNum(const RvSdpConnection *connection);
/*#define rvSdpConnectionGetAddressNum(c)       ((c)->num_addr)*/

/******************* Key methods ********************************/
typedef struct RvSdpKey
{
    /* Key fields */
#if defined(RV_SDP_CHECK_BAD_SYNTAX)
    int             badSyntaxFieldSet;
    char            *badSyntaxField;
#endif
    RvSdpEncrMethod type;   /* prompt,clear,base64,uri */
#ifdef RV_SDPSYMB_USESTRING
    RvString        type_str;
#endif
    RvString        data;   /* including uri */
} RvSdpKey;

RV_SDP_DECLSPEC RvSdpKey* rvSdpKeyConstructN(RvSdpKey *key,RvSdpEncrMethod type,
                              const char* data,RvSize_t len,RvAlloc* alloc);

#if defined(RV_SDP_CHECK_BAD_SYNTAX)

RV_SDP_DECLSPEC RvSdpKey* rvSdpBadSyntaxKeyConstructN(RvSdpKey *key,
                                             const char* badSyntax,RvSize_t len,RvAlloc* alloc);

#define rvSdpBadSyntaxKeyConstructA(k,bs,a) rvSdpBadSyntaxKeyConstructN(k,bs,strlen(bs),a)

RV_SDP_DECLSPEC RvSdpKey* rvSdpBadSyntaxKeyConstruct(RvSdpKey *key,
                                            const char* badSyntax);
RV_SDP_DECLSPEC RvSdpKey* rvSdpBadSyntaxKeyConstruct(RvSdpKey *key,
                                            const char* badSyntax);
#define rvSdpKeyGetBadSyntax(x) rvSdpStringGetData(&(x)->badSyntaxField)
#define rvSdpKeyIsBadSyntax(x)  x->badSyntaxFieldSet

#endif

#define rvSdpKeyConstructA(k,t,d,a) rvSdpKeyConstructN(k,t,d,strlen(d),a)
RV_SDP_DECLSPEC RvSdpKey* rvSdpKeyConstruct(RvSdpKey *key,RvSdpEncrMethod type,
                                            const char* data);
RV_SDP_DECLSPEC RvSdpKey* rvSdpKeyCopy(RvSdpKey *d,const RvSdpKey* s);
RV_SDP_DECLSPEC RvSdpKey* rvSdpKeyConstructCopyA(RvSdpKey *d,const RvSdpKey* s,RvAlloc* a);
RV_SDP_DECLSPEC RvSdpKey* rvSdpKeyConstructCopy(RvSdpKey *d,const RvSdpKey* s);
RV_SDP_DECLSPEC void rvSdpKeyDestruct(RvSdpKey *key);

/*void rvSdpKeySetType(RvSdpKey *key,RvSdpEncrMethod method);*/
#define rvSdpKeySetType(key,m) ((key)->type=m)
/*RvSdpEncrMethod rvSdpKeyGetType(const RvSdpKey *key);*/
#define rvSdpKeyGetType(key) ((key)->type)

RV_SDP_DECLSPEC RvSdpStatus rvSdpKeySetTypeStr(RvSdpKey *key,const char* method);
RV_SDP_DECLSPEC RvSdpStatus rvSdpKeySetTypeStrN(RvSdpKey *key,const char* method,RvSize_t n);
RV_SDP_DECLSPEC const char* rvSdpKeyGetTypeStr(const RvSdpKey *key);

RvSdpStatus rvSdpKeySetData(RvSdpKey *key,const char* data);
/*#define rvSdpKeySetData(key,data) rvSdpStringAssign(&(key)->data,data)*/
RV_SDP_DECLSPEC const char* rvSdpKeyGetData(const RvSdpKey *key);
/*#define rvSdpKeyGetData(key) rvSdpStringGetData(&(key)->data)*/
/******************* Attribute methods ********************************/
typedef int RvSdpAttrType;

typedef struct RvSdpAttribute_{
    RvString name;
    RvString value;
} RvSdpAttribute;

rvSdpDeclareList(RvSdpAttribute)
typedef RvSdpList(RvSdpAttribute) RvSdpAttributeList;

#define rvSdpAttributeListConstructA rvListConstruct(RvSdpAttribute)
#define rvSdpAttributeListConstructCopy rvListConstructCopy(RvSdpAttribute)
#define rvSdpAttributeListDestruct rvListDestruct(RvSdpAttribute)
#define rvSdpAttributeListCopy rvListCopy(RvSdpAttribute)
#define rvSdpAttributeListEqual rvListEqual(RvSdpAttribute)
#define rvSdpAttributeListAdd rvListPushBack(RvSdpAttribute)
#define rvSdpAttributeListClear rvListClear(RvSdpAttribute)
#define rvSdpAttributeListGetSize rvListSize
#define rvSdpAttributeListGetElem rvListAt(RvSdpAttribute)

#define RvSdpAttributeConstructCopy rvSdpAttributeConstructCopyA
#define RvSdpAttributeDestruct  rvSdpAttributeDestruct
#define RvSdpAttributeCopy  rvSdpAttributeCopy
#define RvSdpAttributeEqual(d,s) rvSdpMemEqual(d,s,RvSdpAttribute)

RV_SDP_DECLSPEC RvSdpAttribute* rvSdpAttributeConstructN(RvSdpAttribute* x,const char* name,RvSize_t nlen,const char* value,RvSize_t vlen,RvAlloc* a) ;
#define rvSdpAttributeConstructA(x,n,v,a) rvSdpAttributeConstructN(x,n,strlen(n),v,strlen(v),a)
RV_SDP_DECLSPEC RvSdpAttribute* rvSdpAttributeConstruct(RvSdpAttribute* x,const char* name,const char* value) ;

RV_SDP_DECLSPEC RvSdpAttribute* rvSdpAttributeConstructCopyA(RvSdpAttribute* d,const RvSdpAttribute* s,RvAlloc* alloc);
RV_SDP_DECLSPEC RvSdpAttribute* rvSdpAttributeConstructCopy(RvSdpAttribute* d,const RvSdpAttribute* s);
RV_SDP_DECLSPEC void rvSdpAttributeDestruct(RvSdpAttribute* x);
RV_SDP_DECLSPEC RvSdpAttribute* rvSdpAttributeCopy(RvSdpAttribute* d,const RvSdpAttribute* s);

/*RvSdpStatus rvSdpAttributeSetName(RvSdpAttribute*  a,const char* name);*/
#define rvSdpAttributeSetName(a,new_name)  rvSdpStringAssign(&(a)->name,new_name)
/*const char*   rvSdpAttributeGetName(const RvSdpAttribute*  a);*/
#define rvSdpAttributeGetName(a) rvSdpStringGetData(&(a)->name)

/*RvSdpStatus rvSdpAttributeSetValue(RvSdpAttribute*  a,const char* value);*/
#define rvSdpAttributeSetValue(a,new_value)   rvSdpStringAssign(&(a)->value,new_value)
/*const char*   rvSdpAttributeGetValue(const RvSdpAttribute*  a);*/
#define rvSdpAttributeGetValue(a)  rvSdpStringGetData(&(a)->value)


typedef void *RvSdpGenericFieldPtr;

#if defined(RV_SDP_CHECK_BAD_SYNTAX)

/******************* BadSyntax list methods ********************************/
typedef int RvSdpBadSyntaxType;
typedef struct RvSdpBadSyntax_{
    RvSdpGenericFieldPtr field;
    RvSdpBadSyntaxType field_type;
} RvSdpBadSyntax;

rvSdpDeclareList(RvSdpBadSyntax)
typedef RvSdpList(RvSdpBadSyntax) RvSdpBadSyntaxList;

#define rvSdpBadSyntaxListConstructA rvListConstruct(RvSdpBadSyntax)
#define rvSdpBadSyntaxListConstructCopy rvListConstructCopy(RvSdpBadSyntax)
#define rvSdpBadSyntaxListDestruct rvListDestruct(RvSdpBadSyntax)
#define rvSdpBadSyntaxListCopy rvListCopy(RvSdpBadSyntax)
#define rvSdpBadSyntaxListEqual rvListEqual(RvSdpBadSyntax)
#define rvSdpBadSyntaxListAdd rvListPushBack(RvSdpBadSyntax)
#define rvSdpBadSyntaxListClear rvListClear(RvSdpBadSyntax)
#define rvSdpBadSyntaxListGetSize rvListSize
#define rvSdpBadSyntaxListGetElem rvListAt(RvSdpBadSyntax)

#define RvSdpBadSyntaxConstructCopy rvSdpBadSyntaxConstructCopyA
#define RvSdpBadSyntaxDestruct  rvSdpBadSyntaxDestruct
#define RvSdpBadSyntaxCopy  rvSdpBadSyntaxCopy
#define RvSdpBadSyntaxEqual(d,s) rvSdpMemEqual(d,s,RvSdpBadSyntax)

RV_SDP_DECLSPEC RvSdpBadSyntax* rvSdpBadSyntaxConstructN(RvSdpBadSyntax* x,RvSdpGenericFieldPtr field,RvSdpBadSyntaxType field_type,RvAlloc * alloc) ;
#define rvSdpBadSyntaxConstructA rvSdpBadSyntaxConstructN
RV_SDP_DECLSPEC RvSdpBadSyntax* rvSdpBadSyntaxConstruct(RvSdpBadSyntax* x,RvSdpGenericFieldPtr field,RvSdpBadSyntaxType field_type) ;

RV_SDP_DECLSPEC RvSdpBadSyntax* rvSdpBadSyntaxConstructCopyA(RvSdpBadSyntax* d,const RvSdpBadSyntax* s,RvAlloc * alloc);
RV_SDP_DECLSPEC RvSdpBadSyntax* rvSdpBadSyntaxConstructCopy(RvSdpBadSyntax* d,const RvSdpBadSyntax* s);
RV_SDP_DECLSPEC void rvSdpBadSyntaxDestruct(RvSdpBadSyntax* x);
RV_SDP_DECLSPEC RvSdpBadSyntax* rvSdpBadSyntaxCopy(RvSdpBadSyntax* d,const RvSdpBadSyntax* s);

RvSdpStatus rvSdpBadSyntaxSetField(RvSdpBadSyntax*  a,RvSdpGenericFieldPtr field);

/*const char*   rvSdpAttributeGetName(const RvSdpAttribute*  a);*/
#define rvSdpBadSyntaxGetField(b) b->field

RvSdpStatus rvSdpBadSyntaxSetFieldType(RvSdpBadSyntax*  a,RvSdpBadSyntaxType field_type);

/*const char*   rvSdpAttributeGetName(const RvSdpAttribute*  a);*/
#define rvSdpBadSyntaxGetFieldType(b) b->field_type

/******************* Other field methods ********************************/
typedef int RvSdpOtherType;

typedef struct RvSdpOther_{
    char tag;
    RvString value;
} RvSdpOther;

rvSdpDeclareList(RvSdpOther)
typedef RvSdpList(RvSdpOther) RvSdpOtherList;

#define rvSdpOtherListConstructA rvListConstruct(RvSdpOther)
#define RvSdpOtherListConstructCopy rvListConstructCopy(RvSdpOther)
#define rvSdpOtherListDestruct rvListDestruct(RvSdpOther)
#define RvSdpOtherListCopy rvListCopy(RvSdpOther)
#define RvSdpOtherListEqual rvListEqual(RvSdpOther)
#define rvSdpOtherListAdd rvListPushBack(RvSdpOther)
#define rvSdpOtherListClear rvListClear(RvSdpOther)
#define rvSdpOtherListGetSize rvListSize
#define rvSdpOtherListGetElem rvListAt(RvSdpOther)

#define RvSdpOtherConstructCopy rvSdpOtherConstructCopyA
#define RvSdpOtherDestruct  rvSdpOtherDestruct
#define RvSdpOtherCopy  rvSdpOtherCopy
#define RvSdpOtherEqual(d,s) rvSdpMemEqual(d,s,RvSdpOther)

RV_SDP_DECLSPEC RvSdpOther* RvSdpOtherConstructN(RvSdpOther* x,const char tag,const char* value,RvSize_t vlen,RvAlloc* a) ;
#define rvSdpOtherConstructA(x,t,v,a) rvSdpOtherConstructN(x,t,v,strlen(v),a)
RV_SDP_DECLSPEC RvSdpOther* RvSdpOtherConstruct(RvSdpOther* x,const char tag,const char* value) ;
RV_SDP_DECLSPEC RvSdpOther * rvSdpOtherConstructCopyA(RvSdpOther * d,const RvSdpOther * s,RvAlloc * alloc);
RV_SDP_DECLSPEC RvSdpOther* RvSdpOtherConstructCopyA(RvSdpOther* d,const RvSdpOther* s,RvAlloc* alloc);
RV_SDP_DECLSPEC void RvSdpOtherDestruct(RvSdpOther* x);
RV_SDP_DECLSPEC RvSdpOther* RvSdpOtherCopy(RvSdpOther* d,const RvSdpOther* s);

/*RvSdpStatus RvSdpOtherSetName(RvSdpOther*  a,const char* name);*/
#define rvSdpOtherSetTag(a,new_tag)  a->tag= new_tag
/*const char*   RvSdpOtherGetName(const RvSdpOther*  a);*/
#define rvSdpOtherGetTag(a) (const char)a->tag

/*RvSdpStatus RvSdpOtherSetValue(RvSdpOther*  a,const char* value);*/
#define rvSdpOtherSetValue(a,new_value)   rvSdpStringAssign(&(a)->value,new_value)
/*const char*   RvSdpOtherGetValue(const RvSdpOther*  a);*/
#define rvSdpOtherGetValue(a)  rvSdpStringGetData(&(a)->value)

#endif

/***************** Rtp map *****************************************/
/*
     a=rtpmap:<payload type> <encoding name>/<clock rate>[/<encoding
     parameters>]
*/

typedef struct RvSdpRtpMap_
{
#if defined(RV_SDP_CHECK_BAD_SYNTAX)
    int         badSyntaxFieldSet;
    char        *badSyntaxField;
#endif
    int         payload;
    RvString    enc_name;
    RvUint32    clock_rate;
/*  int         channels; */
    RvString    enc_parameters;
} RvSdpRtpMap;

rvSdpDeclareList(RvSdpRtpMap)
typedef RvSdpList(RvSdpRtpMap) RvSdpRtpMapList;
#define rvSdpRtpMapListConstructA rvListConstruct(RvSdpRtpMap)
#define rvSdpRtpMapListConstructCopy rvListConstructCopy(RvSdpRtpMap)
#define rvSdpRtpMapListDestruct rvListDestruct(RvSdpRtpMap)
#define rvSdpRtpMapListCopy rvListCopy(RvSdpRtpMap)
#define rvSdpRtpMapListEqual rvListEqual(RvSdpRtpMap)
#define rvSdpRtpMapListAdd rvListPushBack(RvSdpRtpMap)
#define rvSdpRtpMapListClear rvListClear(RvSdpRtpMap)
#define rvSdpRtpMapListGetSize rvListSize
#define rvSdpRtpMapListGetElem rvListAt(RvSdpRtpMap)

#define RvSdpRtpMapConstructCopy    rvSdpRtpMapConstructCopyA
#define RvSdpRtpMapDestruct rvSdpRtpMapDestruct
#define RvSdpRtpMapCopy rvSdpRtpMapCopy
#define RvSdpRtpMapEqual(d,s) rvSdpMemEqual(d,s,RvSdpRtpMap)

RV_SDP_DECLSPEC RvSdpRtpMap* rvSdpRtpMapConstructN(RvSdpRtpMap* x,int payload,const char* encoding_name,RvSize_t len,int rate,RvAlloc* a) ;

#if defined(RV_SDP_CHECK_BAD_SYNTAX)

RV_SDP_DECLSPEC RvSdpRtpMap* rvSdpBadSyntaxRtpMapConstructN(RvSdpRtpMap* x,const char* badSyntax,RvSize_t len,RvAlloc* a) ;

#define rvSdpBadSyntaxRtpMapConstructA(x,bs,a) rvSdpBadSyntaxRtpMapConstructN(x,bs,strlen(bs),a)

RV_SDP_DECLSPEC RvSdpRtpMap* rvSdpBadSyntaxRtpMapConstruct(RvSdpRtpMap* x,const char* badSyntax) ;

#define rvSdpRtpMapIsBadSyntax(x)   x->badSyntaxFieldSet
#define rvSdpRtpMapGetBadSyntax(x)  rvSdpStringGetData(&(x)->badSyntaxField)

#endif

#define rvSdpRtpMapConstructA(x,p,e,r,a) rvSdpRtpMapConstructN(x,p,e,strlen(e),r,a)

RV_SDP_DECLSPEC RvSdpRtpMap* rvSdpRtpMapConstruct(RvSdpRtpMap* x,int payload,const char* encoding_name,int rate) ;

RV_SDP_DECLSPEC RvSdpRtpMap* rvSdpRtpMapConstructCopyA(RvSdpRtpMap* d,const RvSdpRtpMap* s,RvAlloc* alloc);
RV_SDP_DECLSPEC RvSdpRtpMap* rvSdpRtpMapConstructCopy(RvSdpRtpMap* d,const RvSdpRtpMap* s);
RV_SDP_DECLSPEC void rvSdpRtpMapDestruct(RvSdpRtpMap* x);
RV_SDP_DECLSPEC RvSdpRtpMap* rvSdpRtpMapCopy(RvSdpRtpMap* d,const RvSdpRtpMap* s);


/* Defaults number of channels is 1 for audio, NA for video */

/*void rvSdpRtpMapSetPayload(RvSdpRtpMap*  x,int payload);*/
#define rvSdpRtpMapSetPayload(x,p)  ((x)->payload=p)
RV_SDP_DECLSPEC int rvSdpRtpMapGetPayload(const RvSdpRtpMap*  x);
/*#define   rvSdpRtpMapGetPayload(x)    ((x)->payload) */

RV_SDP_DECLSPEC RvSdpStatus rvSdpRtpMapSetEncodingName(RvSdpRtpMap*  x,const char* name);
/*#define   rvSdpRtpMapSetEncodingName(x,n) rvSdpStringAssign(&(x)->enc_name,n)*/

/*#define   rvSdpRtpMapGetEncodingName(x)   rvSdpStringGetData(&(x)->enc_name)*/
RV_SDP_DECLSPEC const char *    rvSdpRtpMapGetEncodingName(const RvSdpRtpMap *  x);
/*void rvSdpRtpMapSetClockRate(RvSdpRtpMap*  x,int rate);*/
#define rvSdpRtpMapSetClockRate(x,rate) ((x)->clock_rate=rate)
RV_SDP_DECLSPEC int rvSdpRtpMapGetClockRate(const RvSdpRtpMap*  x);
/*#define   rvSdpRtpMapGetClockRate(x)      ((x)->clock_rate)*/
RV_SDP_DECLSPEC RvSdpStatus rvSdpRtpMapSetEncodingParameters(RvSdpRtpMap*  x,const char* parameters);
RV_SDP_DECLSPEC RvSdpStatus rvSdpRtpMapSetEncodingParametersN(RvSdpRtpMap*  x,const char* parameters,int len);
RV_SDP_DECLSPEC const char* rvSdpRtpMapGetEncodingParameters(const RvSdpRtpMap*  x);
/*#define   rvSdpRtpMapGetEncodingParameters(x) rvStringGetData(&(x)->enc_parameters)*/

RV_SDP_DECLSPEC RvSdpStatus rvSdpRtpMapSetChannels(RvSdpRtpMap*  x,int channels);
RV_SDP_DECLSPEC int rvSdpRtpMapGetChannels(const RvSdpRtpMap*  x);

/***************** Common fields *****************************************/

typedef struct {
    RvString            information;
    RvSdpBandwidth*     bandwidth;
    RvSdpConnection*    connection;

    RvSdpKey*           key;
    RvSdpConnectionMode send_mode;
    /* List of attributes */
    /* List of attributes */
    RvSdpAttributeList  attr_list;

#if defined(RV_SDP_CHECK_BAD_SYNTAX)
    RvSdpBadSyntaxList  bad_syntax_list;

    /* List of unknown fields */
    RvSdpOtherList  other_list;
#endif

    /* List of rtp maps */
    RvSdpRtpMapList     rtp_map_list;

    RvAlloc*            a;
} RvSdpCommonFields;        /* Fields common to session level and and media description level */

RV_SDP_DECLSPEC RvSdpCommonFields* rvSdpCommonFieldsConstruct(RvSdpCommonFields* c,RvAlloc* a);
RV_SDP_DECLSPEC void rvSdpCommonFieldsDestruct(RvSdpCommonFields* c);
void rvSdpCommonFieldsDestructWrap(void* c);
RV_SDP_DECLSPEC RvSdpStatus rvSdpCommonFieldsSetConnectionN(RvSdpCommonFields* fields,RvSdpNetType type,RvSdpAddrType addr_type,const char* addr,int addr_len,RvAlloc* alloc);

#if defined(RV_SDP_CHECK_BAD_SYNTAX)
RV_SDP_DECLSPEC RvSdpBadSyntax *rvSdpCommonFieldsGetBadSyntax(RvSdpCommonFields* fields,RvSize_t i);

RV_SDP_DECLSPEC RvSize_t rvSdpCommonFieldsGetNumOfBadSyntax(RvSdpCommonFields* fields) ;
RV_SDP_DECLSPEC RvSdpBadSyntax* rvSdpCommonFieldsAddBadSyntax(RvSdpCommonFields* fields, RvSdpGenericFieldPtr field,RvSdpBadSyntaxType field_type,RvAlloc* a) ;
RV_SDP_DECLSPEC void rvSdpCommonFieldsRemoveBadSyntax(RvSdpCommonFields* fields, RvSize_t index);
RV_SDP_DECLSPEC void rvSdpCommonFieldsClearBadSyntax(RvSdpCommonFields* fields) ;
RV_SDP_DECLSPEC void rvSdpCommonFieldsRemoveBadSyntaxP(RvSdpCommonFields* fields,RvSdpGenericFieldPtr *p);

RV_SDP_DECLSPEC RvSdpStatus rvSdpCommonFieldsSetBadSyntaxConnectionN(RvSdpCommonFields* fields,const char* bad_syntax,int bad_syntax_len,RvAlloc* alloc);
RV_SDP_DECLSPEC RvSdpStatus rvSdpCommonFieldsSetBadSyntaxKeyN(RvSdpCommonFields* fields,const char* badSyntax,int len,RvAlloc* alloc);

RV_SDP_DECLSPEC RvSdpBadSyntax * rvSdpCommonFieldsAddBadSyntaxN(RvSdpCommonFields* fields,RvSdpGenericFieldPtr field,RvSdpBadSyntaxType field_type,RvAlloc * alloc) ;
RV_SDP_DECLSPEC RvSdpOther * rvSdpCommonFieldsAddOtherN(RvSdpCommonFields* fields, const char tag, const char* value, RvSize_t vlen,RvAlloc* alloc);

RV_SDP_DECLSPEC RvSdpRtpMap* rvSdpCommonFieldsAddBadSyntaxRtpMapN(RvSdpCommonFields* fields,const char* badSyntax,RvSize_t len,RvAlloc* a);
RV_SDP_DECLSPEC RvSdpStatus rvSdpCommonFieldsSetBadSyntaxBandwidthN(RvSdpCommonFields*fields, const char *bad_syntax,int len,RvAlloc * alloc);

#endif

RV_SDP_DECLSPEC RvSdpStatus rvSdpCommonFieldsSetKeyN(RvSdpCommonFields* fields,RvSdpEncrMethod em,const char* key,int key_len,RvAlloc* alloc);
RV_SDP_DECLSPEC RvSdpStatus rvSdpCommonFieldsSetKeyCopy(RvSdpCommonFields* fields,RvSdpKey* s,RvAlloc* alloc);
RV_SDP_DECLSPEC RvSdpAttribute * rvSdpCommonFieldsAddAttrN(RvSdpCommonFields* fields, const char *name, RvSize_t nlen, const char* value, RvSize_t vlen,RvAlloc* alloc);
RV_SDP_DECLSPEC RvSdpRtpMap* rvSdpCommonFieldsAddRtpMapN(RvSdpCommonFields* fields,int payload,const char* encoding_name,RvSize_t len,int rate,RvAlloc* a);
RV_SDP_DECLSPEC RvSdpStatus rvSdpCommonFieldsSetInformationN(RvSdpCommonFields* fields, const char *info, RvSize_t len);
RV_SDP_DECLSPEC RvSdpStatus rvSdpCommonFieldsSetBandwidthN(RvSdpCommonFields* fields, const char *bwtype, RvSize_t len,int b,RvAlloc* alloc);
/*void rvSdpCommonFieldsSetConnectionMode(RvSdpCommonFields* fields,RvSdpConnectionMode mode);*/
#define rvSdpCommonFieldsSetConnectionMode(fields,mode) ((fields)->send_mode = mode)
/*RvSdpConnectionMode rvSdpCommonFieldsGetConnectionMode(RvSdpCommonFields* fields);*/
#define rvSdpCommonFieldsGetConnectionMode(fields) ((fields)->send_mode)

/************* Auxiliary functions ****************************************/
typedef RvSdpList(RvString) RvSdpStringList;
RvSdpStatus rvSdpPushString(RvSdpStringList* list,const char* value,int len);

/* Used to keep track of a series of constructs */
typedef void (*RvSdpGenericDestructor)(void* x);

/* Keep a 'stack' of called constructors for cleanup */
/* 32 should be enough... */
typedef struct RvSdpCtrStack_ {
    RvSdpStatus stat;
    int idx;
    RvSdpGenericDestructor destruct[32];
    void*                  objs[32];
} RvSdpCtrStack;
void rvSdpCtrStackConstruct(RvSdpCtrStack* x);

/* verify the return value of the construct, and add the object and the
   destructor to the stack for cleanup if needed */
void  rvSdpAssertConstruct(void* c,RvSdpCtrStack* s,RvSdpGenericDestructor d,void* obj);
/* Check the overall status, if some construct failed call the
   destructor for the succesfull ones */
RvSdpStatus rvSdpVerifyConstructs(RvSdpCtrStack* s);
void rvSdpRepeatIntervalListDestructWrap(void *I);
void rvSdpStringDestructWrap(void* s);
void rvSdpStringListDestructWrap(void* l);


#if defined(__cplusplus)
}
#endif

#endif /* RV_SDPOBJS_H */
