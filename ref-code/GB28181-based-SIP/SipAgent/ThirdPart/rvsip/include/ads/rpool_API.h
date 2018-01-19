/************************************************************************************************************************

Notice:
This document contains information that is proprietary to RADVision LTD..
No part of this publication may be reproduced in any form whatsoever without
written prior approval by RADVision LTD..

RADVision LTD. reserves the right to revise this publication and make changes
without obligation to notify any person of such revisions or changes.

*************************************************************************************************************************/


/********************************************************************************************
 *                                rpool_API.h
 *
 * The RADVISION SIP stack does not allocate memory dynamically. All memory is
 * allocated during the initialization process.
 * The memory is divided to blocks called pages. The page size and the number of
 * pages are configurable. The collection of all pages is called a memory pool.
 * The memory pool manages the pages, supplying a simple API that allows the
 * user to receive and recycle memory bytes when needed.
 * The Rpool API allows you to construct and destruct pool of pages, allocate
 * pages and read and write from them.
 *
 *
 *      Written by                        Version & Date                        Change
 *     ------------                       ---------------                      --------
 *     Tsahi Levent-Levi                  26-Jul-2000
 *     Ayelet Back                        Nov 2000                       Divide header file
 *                                                                       for rpool.h and rpool_extern,h
 *                                                                       for the purpose of exporting
 *                                                                       the extern file as part
 *                                                                       of the SipExpress API.
 *
 ***********************************************************************************************/
#ifndef RPOOL_API_H
#define RPOOL_API_H


#ifdef __cplusplus
extern "C" {
#endif

#include "RV_ADS_DEF.h"

#ifndef RPOOL_TYPES
#define RPOOL_TYPES
/* Define the the handle to the memory pool */
RV_DECLARE_HANDLE (HRPOOL);

/* Define the handle to a page inside a memory pool */
typedef void * HPAGE;

/* Definition for an invalid page */
#define NULL_PAGE ( NULL )

/* structure that holds parameters that give the actual pointer in the memory.
   To get the actual data from the memory, you should use RPOOL_CopyToExternal
   with the parameters that RPOOL_ptr supplies */
typedef struct {
    HRPOOL    hPool;
    HPAGE     hPage;
    RvInt32  offset;
}RPOOL_Ptr;

#endif

/********************************************************************************************
 * RPOOL_Construct
 * purpose : Allocates memory for a new pool. A pool contains a set of memory pages.
 *           The function receives parameters that indicate the number of pages and
 *           the size of each page inside the pool.
 * input   : pageSize           - The size of each page in the requested pool.
 *           maxNumOfPages      - The number of pages that should be allocated.
 *           logHandle          - LOG handle to use for log messages. You can use
 *                                the Stack Manager functions to get
 *                                the log handle. If logHandle is NULL, no
 *                                messages are printed to the log.
 *           allocEmptyPages    - Indicates whether or not the content of new
 *                                allocated pages is initialized to zero.
 *           name               - Name of the RPOOL instance (used for log messages)
 * output  : none
 * return  : Returns a handle to the RPOOL instance when the function
 *           is successful. Otherwise, the function returns NULL.
 ********************************************************************************************/
HRPOOL RVAPI RVCALLCONV RPOOL_Construct(IN RvInt32         pageSize,
                                        IN RvInt32         maxNumOfPages,
                                        IN RV_LOG_Handle    logHandle,
                                        IN RvBool          allocEmptyPagess,
                                        IN const char*      name);


/********************************************************************************************
 * RPOOL_Destruct
 * purpose : Destructs a memory pool and frees allocated memory.
 * input   : hPool   - Handle for the pool that should be freed
 * output  : none
 * return  : none
 ********************************************************************************************/
void RVAPI RVCALLCONV RPOOL_Destruct(IN HRPOOL hPool);



/********************************************************************************************
 * RPOOL_GetPage
 * purpose : Allocates a page in the memory pool.
 * input   : hPool          - Handle to the RPOOL used
 *           size           - For internal use only. Use only zero.
 * output  : newRpoolElem   - The handle to the allocated page
 * return  : RV_OK if allocation succedded.
 *           RV_ERROR_OUTOFRESOURCES - if allocation failed (no resources)
 ********************************************************************************************/
RvStatus RVAPI RVCALLCONV RPOOL_GetPage(IN  HRPOOL           hPool,
                                         IN  RvInt32         size,
                                         OUT HPAGE*           newRpoolElem);

/********************************************************************************************
 * RPOOL_FreePage
 * purpose : Frees a given page allocation of the memory pool.
 * input   : hPool       - Handle to the RPOOL used
 *           hPage       - Handle to the page to be deallocated
 * output  : none
 * return  : none
 ********************************************************************************************/
void RVAPI RVCALLCONV RPOOL_FreePage(IN HRPOOL    hPool,
                                     IN HPAGE     hPage);




/********************************************************************************************
 * RPOOL_CopyToExternal
 * purpose : Copies a given number of bytes from a specific location inside a
 *           given page to a specified destination buffer.
 *           This function copies non-consecutive memory into a consecutive buffer.
 * input   : hPool   - Handle to the pool.
 *           hPage   - Handle to the source page from which the copy is made.
 *           offset  - Offset from the beginning of the page indicating from
 *                     where the copy is to be made.
 *           dest    - Pointer to the destination buffer to which the copy is made.
 *           size    - The number of bytes to be copied.
 * output  : none
 * return  : RV_OK  - If succeeded.
 *           RV_ERROR_UNKNOWN     - In case of a failure
 ********************************************************************************************/
RvStatus RVAPI RVCALLCONV RPOOL_CopyToExternal(IN HRPOOL     hPool,
                                                IN HPAGE      hPage,
                                                IN RvInt32   offset,
                                                IN void*      dest,
                                                IN RvInt32   size);


/********************************************************************************************
 * RPOOL_AppendFromExternalToPage
 * purpose : The function is used to copy a given number of bytes from an external buffer to
 *           the first available offset inside a given RPOOL page
 * input   : hPool               - Handle to the destination rpool.
 *           hPage               - Handle to the destination page
 *           src                 - Pointer to the source buffer from which the copy
 *                                 is made.
 *           size                - The number of bytes to be copied to the page.
 * output  : allocationOffset    - This is the position in the page from where the append
 *                                 is made. If the append fails, the output offset
 *                                 is UNDEFINED.
 * return  : RV_OK          - If succeeded.
 *           RV_ERROR_OUTOFRESOURCES   - If allocation failed (no resources)
 *           RV_ERROR_UNKNOWN          - In case of a failure
 ********************************************************************************************/
RvStatus RVAPI RVCALLCONV RPOOL_AppendFromExternalToPage(IN  HRPOOL              hPool,
                                                          IN  HPAGE               hPage,
                                                          IN  const void*         src,
                                                          IN  int                 size,
                                                          OUT RvInt32           *allocationOffset);

/***********************************************************************************************
 * RPOOL_Strlen
 * purpose : Return the length of a NULL terminated string that is located in an RPOOL.
 *           The size of the string this function returns does NOT include
 *           the Null termination character.
 *           This string may reside on more the one page element.
 * input   : hPool   : Handle to the pool.
 *           hPage   : Handle to the page.
 *           offset :  The start location of the string in the page..
 * return  : The string length. ( -1 is returned if the string is a not NULL terminated).
 *********************************************************************************************/
RvInt32 RVAPI RVCALLCONV RPOOL_Strlen ( IN HRPOOL     hPool,
                                        IN HPAGE      hPage,
                                        IN RvInt32  offset );

/**********************************************************************************************
 * RPOOL_GetResources
 * purpose : Returns the resources used by a given pool
 * input   : hPool             - Handle to the pool.
 * output  : pNumOfAlloc       - Number of allocated blocks in the pool.
 *           pCurrNumOfUsed    - The currently number of used blocks in the pool.
 *           pMaxUsageMaxUsage - The maximum number of concurrent used blocks in the pool
 *                               until the time this function was called.
 **********************************************************************************************/
void RVAPI RVCALLCONV RPOOL_GetResources ( IN  HRPOOL    hPool,
                                           OUT RvUint32 *pNumOfAlloc,
                                           OUT RvUint32 *pCurrNumOfUsed,
                                           OUT RvUint32 *pMaxUsage);



#ifdef __cplusplus
}
#endif


#endif
