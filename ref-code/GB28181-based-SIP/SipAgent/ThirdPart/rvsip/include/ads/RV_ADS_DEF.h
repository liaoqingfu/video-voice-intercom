#ifndef _RV_ADS_DEF
#define _RV_ADS_DEF

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/*****************************************************************************
 *  RV_Status SIP specific codes -- status codes that may be returned by SIP
 *  API functions as RV_Status (in addition to the general RV_Status values
 *  defined in RV_DEF.h).
 *****************************************************************************/

#include "rvtypes.h"
#include "rverror.h"


/*****************************************************************************
 *  RV_Status -- status codes returned from API functions.
 *  Note: only general status codes are defined here,
 *****************************************************************************/


#ifndef RV_Success
#define RV_Success              RV_OK    
#endif

#ifndef RV_Failure
#define RV_Failure              RV_ERROR_UNKNOWN   
#endif

#ifndef RV_InvalidHandle
#define RV_InvalidHandle        RV_ERROR_BADPARAM    
#endif

#ifndef RV_InvalidParameter
#define RV_InvalidParameter     RV_ERROR_BADPARAM    
#endif

#ifndef RV_OutOfResources
#define RV_OutOfResources       RV_ERROR_OUTOFRESOURCES   
#endif
                                      


#if defined(RV_NOLOG)
#undef RV_CFLAG_NOLOG
#define RV_CFLAG_NOLOG
#endif  /* defined(RV_NOLOG) */

#if defined(RV_NOTHREADS)
#undef  RV_CFLAG_NOTHREADS
#define RV_CFLAG_NOTHREADS
#endif

#if defined(SIP_DEBUG)
#undef  RV_ADS_DEBUG
#define RV_ADS_DEBUG
#endif

#if defined(RV_DEBUG)
#undef  RV_ADS_DEBUG
#define RV_ADS_DEBUG
#endif

/*****************************************************************************
 *                          MACROS Definition                                *
 *****************************************************************************/

#ifndef RV_LOG_TYPES
#define RV_LOG_TYPES
RV_DECLARE_HANDLE(RV_LOG_Handle);
#endif
/*****************************************************************************
 *                         Primitive Type Definitions                        *
 *****************************************************************************/
#ifndef RV_BASIC_TYPES
#define RV_BASIC_TYPES


typedef RvStatus RV_Status;
typedef RvUint64        RV_UINT64;
typedef RvUint32        RV_UINT32;
typedef RvUint16        RV_UINT16;
typedef RvUint8         RV_UINT8;
typedef RvInt32         RV_INT32;
typedef RvInt16         RV_INT16;
typedef RvInt8          RV_INT8;
typedef RvUint          RV_UINT;
typedef RvInt           RV_INT;
typedef RvUint8         RV_BYTE;
typedef RvUint8         RV_UCHAR;
typedef RvChar          RV_CHAR;
typedef RvBool          RV_BOOL;

#endif

typedef struct
{
    RvUint32      numOfUsed;
    RvUint32      maxUsage;
    RvUint32      maxNumOfElements;
} RV_Resource;

#define ADS_HASH   "HASH"
#define ADS_RA     "RA"
#define ADS_RPOOL  "RPOOL"
#define ADS_RLIST  "RLIST"
#define ADS_PQUEUE "PQUEUE"
#define NAMEWRAP(_n) (NULL==(_n)) ? "" : _n

#define ADS_ALIGN_NUMBER 8 /* The number of alignment BYTES */

#ifdef __cplusplus
}
#endif


#endif
