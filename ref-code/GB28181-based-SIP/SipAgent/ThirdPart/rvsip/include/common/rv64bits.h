/***********************************************************************
Filename   : rv64bits.h
Description: 64 bit module header
************************************************************************
      Copyright (c) 2001,2002 RADVISION Inc. and RADVISION Ltd.
************************************************************************
NOTICE:
This document contains information that is confidential and proprietary
to RADVISION Inc. and RADVISION Ltd.. No part of this document may be
reproduced in any form whatsoever without written prior approval by
RADVISION Inc. or RADVISION Ltd..

RADVISION Inc. and RADVISION Ltd. reserve the right to revise this
publication and make changes without obligation to notify any person of
such revisions or changes.
***********************************************************************/
#ifndef RV_64BITS_H
#define RV_64BITS_H

#if !defined(RV_64BITS_TYPE) || \
    ((RV_64BITS_TYPE != RV_64BITS_STANDARD) && (RV_64BITS_TYPE != RV_64BITS_MANUAL))
#error RV_64BITS_TYPE not set properly
#endif

#if defined(__cplusplus)
extern "C" {
#endif 

/* Prototypes and macros */

#if (RV_64BITS_TYPE == RV_64BITS_STANDARD)
/* Compiler supports 64 bit math so just macro out everything */

/* Basic Assignments */
/* Not used in STANDARD mode */

/* Mathematical Operations */
#define RvUint64ShiftLeft(_val, _numbits) ((_val) << (_numbits))
#define RvInt64ShiftLeft(_val, _numbits) ((_val) << (_numbits))
#define RvUint64ShiftRight(_val, _numbits) ((_val) >> (_numbits))
#define RvInt64ShiftRight(_val, _numbits) ((_val) >> (_numbits))
#define RvUint64Not(_val) (~(_val))
#define RvInt64Not(_val) (~(_val))
#define RvUint64And(_val1, _val2) ((_val1) & (_val2))
#define RvInt64And(_val1, _val2) ((_val1) & (_val2))
#define RvUint64Or(_val1, _val2) ((_val1) | (_val2))
#define RvInt64Or(_val1, _val2) ((_val1) | (_val2))
#define RvUint64Xor(_val1, _val2) ((_val1) ^ (_val2))
#define RvInt64Xor(_val1, _val2) ((_val1) ^ (_val2))
#define RvUint64Add(_val1, _val2) ((_val1) + (_val2))
#define RvInt64Add(_val1, _val2) ((_val1) + (_val2))
#define RvUint64Sub(_val1, _val2) ((_val1) - (_val2))
#define RvInt64Sub(_val1, _val2) ((_val1) - (_val2))
#define RvUint64Mul(_val1, _val2) ((_val1) * (_val2))
#define RvInt64Mul(_val1, _val2) ((_val1) * (_val2))
#define RvUint64Div(_val1, _val2) ((_val1) / (_val2))
#define RvInt64Div(_val1, _val2) ((_val1) / (_val2))
#define RvUint64Mod(_val1, _val2) ((_val1) % (_val2))
#define RvInt64Mod(_val1, _val2) ((_val1) % (_val2))

/* Cast from RvInt64 to RvUint64 and back */
#define RvUint64FromRvInt64(_val) ((RvUint64)(_val))
#define RvInt64FromRvUint64(_val) ((RvInt64)(_val))

/* Cast from base types to RvInt64 and RvUint64 */
#define RvUint64FromRvUint32(_val) ((RvUint64)(_val))
#define RvUint64FromRvInt32(_val) ((RvUint64)(_val))
#define RvInt64FromRvUint32(_val) ((RvInt64)(_val))
#define RvInt64FromRvInt32(_val) ((RvInt64)(_val))
#define RvUint64FromRvUint16(_val) ((RvUint64)(_val))
#define RvUint64FromRvInt16(_val) ((RvUint64)(_val))
#define RvInt64FromRvUint16(_val) ((RvInt64)(_val))
#define RvInt64FromRvInt16(_val) ((RvInt64)(_val))
#define RvUint64FromRvUint8(_val) ((RvUint64)(_val))
#define RvUint64FromRvInt8(_val) ((RvUint64)(_val))
#define RvInt64FromRvUint8(_val) ((RvInt64)(_val))
#define RvInt64FromRvInt8(_val) ((RvInt64)(_val))
#define RvUint64FromRvUint(_val) ((RvUint64)(_val))
#define RvUint64FromRvInt(_val) ((RvUint64)(_val))
#define RvInt64FromRvUint(_val) ((RvInt64)(_val))
#define RvInt64FromRvInt(_val) ((RvInt64)(_val))
#define RvUint64FromRvSize_t(_val) ((RvUint64)(_val))
#define RvInt64FromRvSize_t(_val) ((RvInt64)(_val))
#define RvUint64FromRvChar(_val) ((RvUint64)(_val))
#define RvInt64FromRvChar(_val) ((RvInt64)(_val))

/* Cast to base types from RvInt64 and RvUint64 */
#define RvUint64ToRvUint32(_val) ((RvUint32)(_val))
#define RvUint64ToRvInt32(_val) ((RvInt32)(_val))
#define RvInt64ToRvUint32(_val) ((RvUint32)(_val))
#define RvInt64ToRvInt32(_val) ((RvInt32)(_val))
#define RvUint64ToRvUint16(_val) ((RvUint16)(_val))
#define RvUint64ToRvInt16(_val) ((RvInt16)(_val))
#define RvInt64ToRvUint16(_val) ((RvUint16)(_val))
#define RvInt64ToRvInt16(_val) ((RvInt16)(_val))
#define RvUint64ToRvUint8(_val) ((RvUint8)(_val))
#define RvUint64ToRvInt8(_val) ((RvInt8)(_val))
#define RvInt64ToRvUint8(_val) ((RvUint8)(_val))
#define RvInt64ToRvInt8(_val) ((RvInt8)(_val))
#define RvUint64ToRvUint(_val) ((RvUint)(_val))
#define RvUint64ToRvInt(_val) ((RvInt)(_val))
#define RvInt64ToRvUint(_val) ((RvUint)(_val))
#define RvInt64ToRvInt(_val) ((RvInt)(_val))
#define RvUint64ToRvSize_t(_val) ((RvSize_t)(_val))
#define RvInt64ToRvSize_t(_val) ((RvSize_t)(_val))
#define RvUint64ToRvChar(_val) ((RvChar)(_val))
#define RvInt64ToRvChar(_val) ((RvChar)(_val))

/* Logical Operations */
#define RvUint64IsEqual(_val1, _val2) ((_val1) == (_val2))
#define RvInt64IsEqual(_val1, _val2) ((_val1) == (_val2))
#define RvUint64IsNotEqual(_val1, _val2) ((_val1) != (_val2))
#define RvInt64IsNotEqual(_val1, _val2) ((_val1) != (_val2))
#define RvUint64IsLessThan(_val1, _val2) ((_val1) < (_val2))
#define RvInt64IsLessThan(_val1, _val2) ((_val1) < (_val2))
#define RvUint64IsGreaterThan(_val1, _val2) ((_val1) > (_val2))
#define RvInt64IsGreaterThan(_val1, _val2) ((_val1) > (_val2))
#define RvUint64IsLessThanOrEqual(_val1, _val2) ((_val1) <= (_val2))
#define RvInt64IsLessThanOrEqual(_val1, _val2) ((_val1) <= (_val2))
#define RvUint64IsGreaterThanOrEqual(_val1, _val2) ((_val1) >= (_val2))
#define RvInt64IsGreaterThanOrEqual(_val1, _val2) ((_val1) >= (_val2))

/* Min/Max Operations */
#define RvUint64Min(val1, val2) RvMin((val1), (val2))
#define RvInt64Min(val1, val2)  RvMin((val1), (val2))
#define RvUint64Max(val1, val2) RvMax((val1), (val2))
#define RvInt64Max(val1, val2)  RvMax((val1), (val2))

#else
/* Use this module to do 64 bit math */

/* Basic Assignments */
RVCOREAPI RvUint64 RVCALLCONV RvUint64Assign(RvUint32 ms32, RvUint32 ls32);
RVCOREAPI RvInt64  RVCALLCONV RvInt64Assign(RvInt sign, RvUint32 ms32, RvUint32 ls32);
RVCOREAPI RvInt64 RVCALLCONV RvInt64ShortAssign(RvInt32 ls32);

/* Mathematical Operations */
RVCOREAPI RvUint64 RVCALLCONV RvUint64ShiftLeft(RvUint64 val, RvInt numbits);
RVCOREAPI RvInt64  RVCALLCONV RvInt64ShiftLeft(RvInt64 val, RvInt numbits);
RVCOREAPI RvUint64 RVCALLCONV RvUint64ShiftRight(RvUint64 val, RvInt numbits);
RVCOREAPI RvInt64  RVCALLCONV RvInt64ShiftRight(RvInt64 val, RvInt numbits);
RVCOREAPI RvUint64 RVCALLCONV RvUint64Not(RvUint64 val);
RVCOREAPI RvInt64  RVCALLCONV RvInt64Not(RvInt64 val);
RVCOREAPI RvUint64 RVCALLCONV RvUint64And(RvUint64 val1, RvUint64 val2);
RVCOREAPI RvInt64  RVCALLCONV RvInt64And(RvInt64 val1, RvInt64 val2);
RVCOREAPI RvUint64 RVCALLCONV RvUint64Or(RvUint64 val1, RvUint64 val2);
RVCOREAPI RvInt64  RVCALLCONV RvInt64Or(RvInt64 val1, RvInt64 val2);
RVCOREAPI RvUint64 RVCALLCONV RvUint64Xor(RvUint64 val1, RvUint64 val2);
RVCOREAPI RvInt64  RVCALLCONV RvInt64Xor(RvInt64 val1, RvInt64 val2);
RVCOREAPI RvUint64 RVCALLCONV RvUint64Add(RvUint64 val1, RvUint64 val2);
RVCOREAPI RvInt64  RVCALLCONV RvInt64Add(RvInt64 val1, RvInt64 val2);
RVCOREAPI RvUint64 RVCALLCONV RvUint64Sub(RvUint64 val1, RvUint64 val2);
RVCOREAPI RvInt64  RVCALLCONV RvInt64Sub(RvInt64 val1, RvInt64 val2);
RVCOREAPI RvUint64 RVCALLCONV RvUint64Mul(RvUint64 val1, RvUint64 val2);
RVCOREAPI RvInt64  RVCALLCONV RvInt64Mul(RvInt64 val1, RvInt64 val2);
RVCOREAPI RvUint64 RVCALLCONV RvUint64Div(RvUint64 val1, RvUint64 val2);
RVCOREAPI RvInt64  RVCALLCONV RvInt64Div(RvInt64 val1, RvInt64 val2);
RVCOREAPI RvUint64 RVCALLCONV RvUint64Mod(RvUint64 val1, RvUint64 val2);
RVCOREAPI RvInt64  RVCALLCONV RvInt64Mod(RvInt64 val1, RvInt64 val2);

/* Cast from RvInt64 to RvUint64 and back */
RVCOREAPI RvUint64 RVCALLCONV RvUint64FromRvInt64(RvInt64 val);
RVCOREAPI RvInt64  RVCALLCONV RvInt64FromRvUint64(RvUint64 val);

/* Cast from base types to RvInt64 and RvUint64 */
RVCOREAPI RvUint64 RVCALLCONV RvUint64FromRvUint32(RvUint32 val);
RVCOREAPI RvUint64 RVCALLCONV RvUint64FromRvInt32(RvInt32 val);
RVCOREAPI RvInt64  RVCALLCONV RvInt64FromRvUint32(RvUint32 val);
RVCOREAPI RvInt64  RVCALLCONV RvInt64FromRvInt32(RvInt32 val);
RVCOREAPI RvUint64 RVCALLCONV RvUint64FromRvUint16(RvUint16 val);
RVCOREAPI RvUint64 RVCALLCONV RvUint64FromRvInt16(RvInt16 val);
RVCOREAPI RvInt64  RVCALLCONV RvInt64FromRvUint16(RvUint16 val);
RVCOREAPI RvInt64  RVCALLCONV RvInt64FromRvInt16(RvInt16 val);
RVCOREAPI RvUint64 RVCALLCONV RvUint64FromRvUint8(RvUint8 val);
RVCOREAPI RvUint64 RVCALLCONV RvUint64FromRvInt8(RvInt8 val);
RVCOREAPI RvInt64  RVCALLCONV RvInt64FromRvUint8(RvUint8 val);
RVCOREAPI RvInt64  RVCALLCONV RvInt64FromRvInt8(RvInt8 val);
RVCOREAPI RvUint64 RVCALLCONV RvUint64FromRvUint(RvUint val);
RVCOREAPI RvUint64 RVCALLCONV RvUint64FromRvInt(RvInt val);
RVCOREAPI RvInt64  RVCALLCONV RvInt64FromRvUint(RvUint val);
RVCOREAPI RvInt64  RVCALLCONV RvInt64FromRvInt(RvInt val);
RVCOREAPI RvUint64 RVCALLCONV RvUint64FromRvSize_t(RvSize_t val);
RVCOREAPI RvInt64  RVCALLCONV RvInt64FromRvSize_t(RvSize_t val);
RVCOREAPI RvUint64 RVCALLCONV RvUint64FromRvChar(RvChar val);
RVCOREAPI RvInt64  RVCALLCONV RvInt64FromRvChar(RvChar val);

/* Cast to base types from RvInt64 and RvUint64 */
RVCOREAPI RvUint32 RVCALLCONV RvUint64ToRvUint32(RvUint64 val);
RVCOREAPI RvInt32  RVCALLCONV RvUint64ToRvInt32(RvUint64 val);
RVCOREAPI RvUint32 RVCALLCONV RvInt64ToRvUint32(RvInt64 val);
RVCOREAPI RvInt32  RVCALLCONV RvInt64ToRvInt32(RvInt64 val);
RVCOREAPI RvUint16 RVCALLCONV RvUint64ToRvUint16(RvUint64 val);
RVCOREAPI RvInt16  RVCALLCONV RvUint64ToRvInt16(RvUint64 val);
RVCOREAPI RvUint16 RVCALLCONV RvInt64ToRvUint16(RvInt64 val);
RVCOREAPI RvInt16  RVCALLCONV RvInt64ToRvInt16(RvInt64 val);
RVCOREAPI RvUint8  RVCALLCONV RvUint64ToRvUint8(RvUint64 val);
RVCOREAPI RvInt8   RVCALLCONV RvUint64ToRvInt8(RvUint64 val);
RVCOREAPI RvUint8  RVCALLCONV RvInt64ToRvUint8(RvInt64 val);
RVCOREAPI RvInt8   RVCALLCONV RvInt64ToRvInt8(RvInt64 val);
RVCOREAPI RvUint   RVCALLCONV RvUint64ToRvUint(RvUint64 val);
RVCOREAPI RvInt    RVCALLCONV RvUint64ToRvInt(RvUint64 val);
RVCOREAPI RvUint   RVCALLCONV RvInt64ToRvUint(RvInt64 val);
RVCOREAPI RvInt    RVCALLCONV RvInt64ToRvInt(RvInt64 val);
RVCOREAPI RvSize_t RVCALLCONV RvUint64ToRvSize_t(RvUint64 val);
RVCOREAPI RvSize_t RVCALLCONV RvInt64ToRvSize_t(RvInt64 val);
RVCOREAPI RvChar   RVCALLCONV RvUint64ToRvChar(RvUint64 val);
RVCOREAPI RvChar   RVCALLCONV RvInt64ToRvChar(RvInt64 val);

/* Logical Operations */
RVCOREAPI RvBool RVCALLCONV RvUint64IsEqual(RvUint64 val1, RvUint64 val2);
RVCOREAPI RvBool RVCALLCONV RvInt64IsEqual(RvInt64 val1, RvInt64 val2);
#define                     RvUint64IsNotEqual(val1, val2) (!RvUint64IsEqual(val1, val2))
#define                     RvInt64IsNotEqual(val1, val2) (!RvInt64IsEqual(val1, val2))
RVCOREAPI RvBool RVCALLCONV RvUint64IsLessThan(RvUint64 val1, RvUint64 val2);
RVCOREAPI RvBool RVCALLCONV RvInt64IsLessThan(RvInt64 val1, RvInt64 val2);
RVCOREAPI RvBool RVCALLCONV RvUint64IsGreaterThan(RvUint64 val1, RvUint64 val2);
RVCOREAPI RvBool RVCALLCONV RvInt64IsGreaterThan(RvInt64 val1, RvInt64 val2);
RVCOREAPI RvBool RVCALLCONV RvUint64IsLessThanOrEqual(RvUint64 val1, RvUint64 val2);
RVCOREAPI RvBool RVCALLCONV RvInt64IsLessThanOrEqual(RvInt64 val1, RvInt64 val2);
RVCOREAPI RvBool RVCALLCONV RvUint64IsGreaterThanOrEqual(RvUint64 val1, RvUint64 val2);
RVCOREAPI RvBool RVCALLCONV RvInt64IsGreaterThanOrEqual(RvInt64 val1, RvInt64 val2);

/* Min/Max Operations */
#define RvUint64Min(val1, val2) ((RvUint64IsLessThan   ((val1), (val2))) ? (val1) : (val2))
#define RvInt64Min(val1, val2)  ((RvInt64IsLessThan    ((val1), (val2))) ? (val1) : (val2))
#define RvUint64Max(val1, val2) ((RvUint64IsGreaterThan((val1), (val2))) ? (val1) : (val2))
#define RvInt64Max(val1, val2)  ((RvInt64IsGreaterThan ((val1), (val2))) ? (val1) : (val2))

#endif /* RV_64BITS_TYPE == RV_64BITS_STANDARD */

#if defined(__cplusplus)
}
#endif 

#endif /* RV_64BITS_H */
