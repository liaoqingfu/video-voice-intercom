/******************************************************************************
Filename:    rvstring.h
Description: copy-on-write string class declarations
*******************************************************************************
                Copyright (c) 2000 RADVision Inc.
*******************************************************************************
NOTICE:
This document contains information that is proprietary to RADVision LTD.
No part of this publication may be reproduced in any form whatsoever
without written prior approval by RADVision LTD..

RADVision LTD. reserves the right to revise this publication and make
changes without obligation to notify any person of such revisions or
changes.
******************************************************************************/

#ifndef RV_STRING_H
#define RV_STRING_H

#include "rvalloc.h"
#include "rvsdpvector.h"

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct
{
    RvSize_t length, maxlen, refs;
    RvAlloc *alloc;
} RvStringHeader;

typedef char *RvString;

/* Private */
#define rvStringGetHeader(x) ( (RvStringHeader *)(*(x) - sizeof(RvStringHeader)) )

/*RvString* rvStringConstruct(RvString *x, const char *str, RvAlloc *a);*/
#define rvStringConstruct(x,s,a) rvStringConstructN(x,s,strlen(s),a)

#define rvStringConstructA rvStringConstruct
RvString* rvStringConstructN(RvString *x, const char *str, RvSize_t n, RvAlloc *a);
RvString* rvStringConstructAndReserve(RvString *x, RvSize_t n, RvAlloc *sdpAllocator);
RvString* rvStringConstructCopy(RvString *d, const RvString *s, RvAlloc *a);
void rvStringDestruct(RvString *x);
RvString* rvStringCopy(RvString *d, const RvString *s);

/*RvSize_t rvStringGetSize(const RvString *x);*/
#define rvStringGetSize(x) ( rvStringGetHeader(x)->length )

/*RvSize_t rvStringGetCapacity(const RvString *x);*/
#define rvStringGetCapacity(x) ( rvStringGetHeader(x)->maxlen )

RvString* rvStringResize(RvString *x, RvSize_t n);
RvString* rvStringReserve(RvString *x, RvSize_t n);
RvString* rvStringAssign(RvString *x, const char* str);
RvString* rvStringAssignN(RvString *x, const char* str, RvSize_t n);
RvString* rvStringMakeUppercase(RvString *x);
RvString* rvStringMakeLowercase(RvString *x);
RvString* rvStringConcatenateN(RvString *x, const char* str, RvSize_t n);
/*RvString* rvStringConcatenate(RvString *x, const char *str);*/
#define rvStringConcatenate(x,s) rvStringConcatenateN(x,s,strlen(s))
/*RvString* rvStringConcatenateString(RvString *x, const RvString *s);*/
#define rvStringConcatenateString(x,s)  rvStringConcatenateN(x, rvStringGetData(s), rvStringGetSize(s))
RvString* rvStringPushBack(RvString *x, char c);
/*const char* rvStringGetData(const RvString *x);*/
#define rvStringGetData(x) ( (const char*)*(x) )
RvBool rvStringEqual(const RvString *a, const RvString *b);
RvBool rvStringEqualIgnoreCase(const RvString *a, const RvString *b);
RvBool rvStringLess(const RvString *a, const RvString *b);
RvBool rvStringLessIgnoreCase(const RvString *a, const RvString *b);
RvAlloc *rvStringGetAllocator(const RvString *x);
#define rvStringIsValid(x) (*(x) != NULL)
RvSize_t  rvStringHash(const RvString *x);
RvSize_t  rvStringHashIgnoreCase(const RvString *x);


#define RvStringConstructCopy rvStringConstructCopy
#define RvStringDestruct rvStringDestruct
#define RvStringCopy rvStringCopy
#define RvStringEqual rvStringEqual
#define RvStringLess rvStringLess
#define RvStringGetAllocator rvStringGetAllocator

rvSdpDeclareVector(RvString)
typedef RvSdpVector(RvString) RvStringList;
#define rvStringListConstructA rvSdpVectorConstruct(RvString)
#define rvStringListConstructCopy rvSdpVectorConstructCopy(RvString)
#define rvStringListDestruct rvSdpVectorDestruct(RvString)
#define rvStringListCopy rvSdpVectorCopy(RvString)
#define rvStringListEqual rvSdpVectorEqual(RvString)
void rvStringListAdd(RvStringList *x, const char *str);
void rvStringListAddN(RvStringList *x, const char *str, RvSize_t n);
#define rvStringListAddString rvSdpVectorPushBack(RvString)
#define rvStringListAddRvString rvStringListAddString
#define rvStringListClear rvSdpVectorClear(RvString)
#define rvStringListGetSize rvSdpVectorSize
const char* rvStringListGetElem(const RvStringList *x, RvSize_t idx);
RvString* rvStringListGetString(const RvStringList *x, RvSize_t idx);

/* Use to build a vector,map,list,etc when case insensitive comparison is desired*/
typedef RvString RvIString;
#define RvIStringConstructCopy  rvStringConstructCopy
#define RvIStringDestruct       rvStringDestruct
#define RvIStringLess           rvStringLessIgnoreCase
#define RvIStringEqual          rvStringEqualIgnoreCase

#if defined(__cplusplus)
}
#endif

#endif
