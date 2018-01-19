#if (0)
******************************************************************************
Filename    : rvsdpvector.h
Description :
The following pseudo C++ prototypes describe the RvSdpVector<T> interface:
RvSdpVector<T>* rvSdpVectorConstruct<T>(RvSdpVector<T>* v, RvAlloc* a);
RvSdpVector<T>* rvSdpVectorConstructN<T>(RvSdpVector<T>* v, RvSize_t n, const T* x, RvAlloc* a);
RvSdpVector<T>* rvSdpVectorConstructCopy<T>(RvSdpVector<T>* v, const _RvSdpVector<T>* src, RvAlloc *a);
void rvSdpVectorDestruct<T>(RvSdpVector<T>* v);
RvSdpVector<T>* rvSdpVectorCopy<T>(RvSdpVector<T>* v, const RvSdpVector<T>* src);
void rvSdpVectorClear<T>(RvSdpVector<T>* v);
RvBool rvSdpVectorFill<T>(RvSdpVector<T>* v);
RvBool rvSdpVectorReserve<T>(_RvSdpVector<T>* v, RvSize_t n);
RvSdpVectorIter<T> rvSdpVectorPushBack<T>(RvSdpVector<T>* v, const T* x);
RvSdpVectorIter<T> rvSdpVectorInsert<T>(RvSdpVector<T>* v, RvSdpVectorIter<T> it, const T* x);
void rvSdpVectorPopBack(RvSdpVector<T>* v);
RvSdpVectorIter<T> rvSdpVectorErase(RvSdpVector<T>* v, _RvSdpVectorIter<T> it);
RvBool rvSdpVectorEqual<T>(const RvSdpVectorT* a, const RvSdpVector<T>* b);
void rvSdpVectorSwap(RvSdpVector<T>* a, RvSdpVector<T>* b);
RvSize_t rvSdpVectorSize(RvSdpVector<T>* v);
RvSize_t rvSdpVectorCapacity(RvSdpVector<T>* v);
T* rvSdpVectorFront(RvSdpVector<T>* v);
T* rvSdpVectorBack(RvSdpVector<T>* v);
RvSdpVectorIter<T> rvSdpVectorBegin(RvSdpVector<T>* v);
RvSdpVectorIter<T> rvSdpVectorEnd(RvSdpVector<T>* v);
RvSdpVectorRevIter<T> rvSdpVectorRevBegin(RvSdpVector<T>* v);
RvSdpVectorRevIter<T> rvSdpVectorRevEnd(RvSdpVector<T>* v);
T* rvSdpVectorAt(RvSdpVector<T>* v, RvSize_t i);

The following C++ prototypes describe the RvSdpVectorIter interface:
RvSdpVectorIter<T> rvSdpVectorIterPrev(RvSdpVectorIter<T> i);
RvSdpVectorIter<T> rvSdpVectorIterNext(RvSdpVectorIter<T> i);
T* rvSdpVectorIterData(RvSdpVectorIter<T> i);

The following C++ prototypes describe the RvSdpVectorRevIter interface:
RvSdpVectorRevIter<T> rvSdpVectorRevIterPrev(RvSdpVectorRevIter<T> i);
RvSdpVectorRevIter<T> rvSdpVectorRevIterNext(RvSdpVectorRevIter<T> i);
T* rvSdpVectorRevIterData(RvSdpVectorIter<T> i);

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
$Revision:$
$Date:$
$Author: S. Cipolli$
******************************************************************************
#endif

#ifndef RV_SDPVECTOR_H
#define RV_SDPVECTOR_H

#include "rvalloc.h"

#define rvSdpDeclareForwardVector(T) \
	typedef struct _RvSdpVector##T; \
	typedef T* _RvSdpVectorIter##T; \
	typedef T* _RvSdpVectorRevIter##T;

#define rvSdpDeclareVector(T) \
	typedef struct { \
		T* data; \
		RvSize_t size; \
		RvSize_t capacity; \
		RvAlloc* allocator; \
	} _RvSdpVector##T; \
	typedef T* _RvSdpVectorIter##T; \
	typedef T* _RvSdpVectorRevIter##T; \
	RvSdpVector(T)* _RvSdpVector##T##Construct(RvSdpVector(T)* v, RvAlloc* a); \
	RvSdpVector(T)* _RvSdpVector##T##ConstructN(RvSdpVector(T)* v, RvSize_t n, \
	  const T* x, RvAlloc* a); \
	RvSdpVector(T)* _RvSdpVector##T##ConstructCopy(RvSdpVector(T)* d, \
	  const RvSdpVector(T)* s, RvAlloc *a); \
	void _RvSdpVector##T##Destruct(RvSdpVector(T)* v); \
	RvSdpVector(T)* _RvSdpVector##T##Copy(RvSdpVector(T)* d, const RvSdpVector(T)* s); \
	void _RvSdpVector##T##Clear(RvSdpVector(T)* v); \
	RvBool _RvSdpVector##T##Fill(RvSdpVector(T)* v, RvSize_t n, const T* x); \
	RvBool _RvSdpVector##T##Reserve(RvSdpVector(T)* v, RvSize_t n); \
	_RvSdpVectorIter##T _RvSdpVector##T##PushBack(RvSdpVector(T)* v, const T* x); \
	_RvSdpVectorIter##T _RvSdpVector##T##Insert(RvSdpVector(T)* v, \
	  _RvSdpVectorIter##T it, const T* x); \
	T* _RvSdpVector##T##AllocBack(RvSdpVector(T)* v); \
	void _RvSdpVector##T##PopBack(RvSdpVector(T)* v); \
	_RvSdpVectorIter##T _RvSdpVector##T##Erase(RvSdpVector(T)* v, \
	  _RvSdpVectorIter##T it); \
	RvBool _RvSdpVector##T##Equal(const RvSdpVector(T)* a, const RvSdpVector(T)* b); \
	void _RvSdpVector##T##Swap(_RvSdpVector##T* a, _RvSdpVector##T* b);

#define rvSdpDefineVector(T) \
	void _RvSdpVector##T##Copy_(T* d, const T* s, RvSize_t n, RvAlloc *a) { \
		RvSize_t i; \
		for (i = 0; i < n; ++i) \
			T##ConstructCopy(&(d[i]), &(s[i]), a); \
	} \
	void _RvSdpVector##T##Clear_(RvSdpVector(T)* v) { \
		RvSize_t i; \
		for (i = v->size; i > 0; --i) \
			T##Destruct(&v->data[i - 1]); \
	} \
	RvSdpVector(T)* _RvSdpVector##T##Construct(RvSdpVector(T)* v, RvAlloc* a) { \
		v->allocator = a; \
		v->size = 0; \
		v->capacity = 0; \
		return v; \
	} \
	RvSdpVector(T)* _RvSdpVector##T##ConstructN(RvSdpVector(T)* v, RvSize_t n, \
	  const T* x, RvAlloc* a) { \
		v->allocator = a; \
		v->size = 0; \
		v->capacity = 0; \
		if (!rvSdpVectorFill(T)(v, n, x)) return NULL; \
		return v; \
	} \
	RvSdpVector(T)* _RvSdpVector##T##ConstructCopy(RvSdpVector(T)* d, \
	  const RvSdpVector(T)* s, RvAlloc *a) { \
		d->allocator = a; \
		d->size = 0; \
		d->capacity = 0; \
		if (!rvSdpVectorReserve(T)(d, s->size)) return NULL; \
		_RvSdpVector##T##Copy_(d->data, s->data, s->size, d->allocator); \
		d->size = s->size; \
		return d; \
	} \
	void _RvSdpVector##T##Destruct(RvSdpVector(T)* v) { \
		if (v->capacity) { \
			_RvSdpVector##T##Clear_(v); \
			rvAllocDeallocate(v->allocator, \
			  v->capacity * sizeof(T), v->data); \
		} \
	} \
	RvSdpVector(T)* _RvSdpVector##T##Copy(RvSdpVector(T)* d, \
	  const RvSdpVector(T)* s) { \
		_RvSdpVector##T##Clear_(d); \
		d->size = 0; \
		if (!rvSdpVectorReserve(T)(d, s->size)) return NULL; \
		_RvSdpVector##T##Copy_(d->data, s->data, s->size, d->allocator); \
		d->size = s->size; \
		return d; \
	} \
	void _RvSdpVector##T##Clear(RvSdpVector(T)* v) { \
		_RvSdpVector##T##Clear_(v); \
		v->size = 0; \
	} \
	RvBool _RvSdpVector##T##Fill(RvSdpVector(T)* v, RvSize_t n, const T* x) { \
		if (rvSdpVectorReserve(T)(v, n)) { \
			RvSize_t i; \
			for (i = 0; i < n; ++i) { \
				T##Destruct(rvSdpVectorAt(v, i)); \
				T##ConstructCopy(rvSdpVectorAt(v, i), x, v->allocator); \
			} \
			v->size = RvMax(v->size, n); \
		} else \
			return RV_FALSE; \
		return RV_TRUE; \
	} \
	RvBool _RvSdpVector##T##Reserve(RvSdpVector(T)* v, RvSize_t n) { \
		RvSize_t capacity; \
		T* data = NULL; \
		if (n > v->capacity) { \
			if (v->capacity == 0) { \
				capacity = ((n < 4) ? 4 : n); \
				data = (T*)rvAllocAllocate(v->allocator, capacity * sizeof(T)); \
				if (!data) return RV_FALSE; \
			} else { \
				capacity = v->size + ((n < v->size) ? v->size : n); \
				data = (T*)rvAllocAllocate(v->allocator, capacity * sizeof(T)); \
				if (!data) return RV_FALSE; \
				_RvSdpVector##T##Copy_(data, v->data, v->size, v->allocator); \
				_RvSdpVector##T##Clear_(v); \
				rvAllocDeallocate(v->allocator, v->capacity * sizeof(T), \
				  v->data); \
			} \
			v->capacity = capacity; \
			v->data = data; \
		} \
		return RV_TRUE; \
	} \
	_RvSdpVectorIter##T _RvSdpVector##T##PushBack(RvSdpVector(T)* v, const T* x) { \
		if (rvSdpVectorReserve(T)(v, v->size + 1)) { \
			T##ConstructCopy(&(v->data[v->size]), x, v->allocator); \
			++(v->size); \
			return &(v->data[v->size - 1]); \
		} \
		return rvSdpVectorEnd(v); \
	} \
	T* _RvSdpVector##T##AllocBack(RvSdpVector(T)* v) { \
		if (rvSdpVectorReserve(T)(v, v->size + 1)) { \
			++(v->size); \
			return &(v->data[v->size - 1]); \
		} \
		return NULL; \
	} \
	_RvSdpVectorIter##T _RvSdpVector##T##Insert(RvSdpVector(T)* v, \
	  _RvSdpVectorIter##T it, const T* x) { \
		ptrdiff_t i = it - rvSdpVectorBegin(v); \
		RvSize_t j; \
		rvAssert(it >= rvSdpVectorBegin(v) && it <= rvSdpVectorEnd(v)); \
		if (rvSdpVectorReserve(T)(v, v->size + 1)) { \
			for (j = v->size; j > (RvSize_t)i; --j) { \
				T##ConstructCopy(&(v->data[j]), &(v->data[j - 1]), v->allocator); \
				T##Destruct(&v->data[j - 1]); \
			} \
			T##ConstructCopy(&(v->data[i]), x, v->allocator); \
			++(v->size); \
			return it; \
		} \
		return rvSdpVectorEnd(v); \
	} \
	void _RvSdpVector##T##PopBack(RvSdpVector(T)* v) { \
		if (v->size != 0) { \
			--(v->size); \
			T##Destruct(&v->data[v->size]); \
		} \
	} \
	_RvSdpVectorIter##T _RvSdpVector##T##Erase(RvSdpVector(T)* v, \
	  _RvSdpVectorIter##T it) { \
		_RvSdpVectorIter##T i = it; \
	  	rvAssert(i >= rvSdpVectorBegin(v) && i < rvSdpVectorEnd(v)); \
		if (i < rvSdpVectorEnd(v)) { \
			T##Destruct(rvSdpVectorIterData(i)); \
			i = rvSdpVectorIterNext(i); \
			for (; i != rvSdpVectorEnd(v); i = rvSdpVectorIterNext(i)) { \
				T##ConstructCopy(rvSdpVectorIterData(i - 1), \
				rvSdpVectorIterData(i), v->allocator); \
				T##Destruct(rvSdpVectorIterData(i)); \
			} \
			--(v->size); \
		} \
		return it; \
	} \
	RvBool _RvSdpVector##T##Equal(const RvSdpVector(T)* a, const RvSdpVector(T)* b) { \
		if (a->size == b->size) { \
			RvSize_t i; \
			for (i = 0; i < a->size; ++i) \
				if (!(T##Equal(&(a->data[i]), &(b->data[i])))) \
					return RV_FALSE; \
			return RV_TRUE; \
		} \
		return RV_FALSE; \
	} \
	void _RvSdpVector##T##Swap(RvSdpVector(T)* a, RvSdpVector(T)* b) { \
		RvSdpVector(T) t = *a; *a = *b; *b = t; \
	}

/* Vector */
#define RvSdpVector(T)					_RvSdpVector##T
#define rvSdpVectorGetAllocator(v)		((v)->allocator)
#define rvSdpVectorSize(v)				((v)->size)
#define rvSdpVectorCapacity(v)			((v)->capacity - (v)->size)
#define rvSdpVectorFront(v)			(&((v)->data[0]))
#define rvSdpVectorBack(v)				((v)->size ? &((v)->data[(v)->size - 1]) : &((v)->data[-1]))
#define rvSdpVectorBegin(v)			(&((v)->data[0]))
#define rvSdpVectorEnd(v)				(&((v)->data[(v)->size]))
#define rvSdpVectorRevBegin(v)			(rvSdpVectorBack(v))
#define rvSdpVectorRevEnd(v)			(&((v)->data[-1]))
#define rvSdpVectorAt(v, i)			(&((v)->data[i]))
#define rvSdpVectorConstruct(T)		_RvSdpVector##T##Construct
#define rvSdpVectorConstructN(T)		_RvSdpVector##T##ConstructN
#define rvSdpVectorConstructCopy(T)	_RvSdpVector##T##ConstructCopy
#define rvSdpVectorDestruct(T)			_RvSdpVector##T##Destruct
#define rvSdpVectorCopy(T)				_RvSdpVector##T##Copy
#define rvSdpVectorClear(T)			_RvSdpVector##T##Clear
#define rvSdpVectorFill(T)				_RvSdpVector##T##Fill
#define rvSdpVectorReserve(T)			_RvSdpVector##T##Reserve
#define rvSdpVectorAllocBack(T)		_RvSdpVector##T##AllocBack
#define rvSdpVectorPushBack(T)			_RvSdpVector##T##PushBack
#define rvSdpVectorInsert(T)			_RvSdpVector##T##Insert
#define rvSdpVectorPopBack(T)			_RvSdpVector##T##PopBack
#define rvSdpVectorErase(T)			_RvSdpVector##T##Erase
#define rvSdpVectorEqual(T)			_RvSdpVector##T##Equal
#define rvSdpVectorSwap(T)				_RvSdpVector##T##Swap

/* Aliases for naming problem */
#define RvSdpVectorConstructCopy(T)	rvSdpVectorConstructCopy(T)
#define RvSdpVectorCopy(T)				rvSdpVectorCopy(T)
#define RvSdpVectorDestruct(T)			rvSdpVectorDestruct(T)
#define RvSdpVectorGetAllocator(T)		rvSdpVectorGetAllocator(T)
#define RvSdpVectorSwap(T)				rvSdpVectorSwap(T)
#define RvSdpVectorEqual(T)			rvSdpVectorEqual(T)

/* Iterator */
#define RvSdpVectorIter(T)				_RvSdpVectorIter##T
#define rvSdpVectorIterNext(i)			((i) + 1)
#define rvSdpVectorIterPrev(i)			((i) - 1)
#define rvSdpVectorIterData(i)			(i)
#define rvSdpVectorIterEqual(a,b)		((a) == (b))

/* Aliases for naming problem */
#define RvSdpVectorIterData(i)			rvSdpVectorIterData(i)
#define RvSdpVectorIterPrev(i)			rvSdpVectorIterPrev(i)
#define RvSdpVectorIterNext(i)			rvSdpVectorIterNext(i)
#define RvSdpVectorIterEqual(a,b)		rvSdpVectorIterEqual(a,b)

/* Reverse Iterator */
#define RvSdpVectorRevIter(T)			_RvSdpVectorRevIter##T
#define rvSdpVectorRevIterNext(i)		((i) - 1)
#define rvSdpVectorRevIterPrev(i)		((i) + 1)
#define rvSdpVectorRevIterData(i)		(i)
#define rvSdpVectorRevIterEqual(a,b)	((a) == (b))

/* Aliases for naming problem */
#define RvSdpVectorRevIterData(i)		rvSdpVectorRevIterData(i)
#define RvSdpVectorRevIterPrev(i)		rvSdpVectorRevIterPrev(i)
#define RvSdpVectorRevIterNext(i)		rvSdpVectorRevIterNext(i)
#define RvSdpVectorRevIterEqual(a,b)	rvSdpVectorRevIterEqual(a,b)

#endif
