
/*

NOTICE:
This document contains information that is proprietary to RADVision LTD..
No part of this publication may be reproduced in any form whatsoever without
written prior approval by RADVision LTD..

RADVision LTD. reserves the right to revise this publication and make changes
without obligation to notify any person of such revisions or changes.

*/

/******************************************************************************
 *                             RvSipRetryAfterHeader.c                        *
 *                                                                            *
 * The file defines the methods of the Retry-After header object.             *
 * The Retry-After header functions enable you to construct, copy, encode,    *
 * parse, access and change Retry-After Header parameters.                    *
 *                                                                            *
 *      Author           Date                                                 *
 *     ------           ------------                                          *
 *     Ofra Wachsamn    December 2001                                         *
 ******************************************************************************/

#ifndef RVSIP_RETRYAFTER_HEADER_H
#define RVSIP_RETRYAFTER_HEADER_H

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                           */
/*-----------------------------------------------------------------------*/
#include "RV_SIP_DEF.h"
#ifndef RV_SIP_PRIMITIVES
#include "RvSipMsgTypes.h"
#include "rpool_API.h"

/*-----------------------------------------------------------------------*/
/*                   DECLERATIONS                                        */
/*-----------------------------------------------------------------------*/
/*
 * RvSipRetryAfterHeaderStringName
 * ----------------------
 * This enum defines all the header's strings (for getting it's size)
 * Defines all Retry-After header object fields that are kept in the 
 * object in string format.
 */
typedef enum
{
    RVSIP_RETRY_AFTER_COMMENT,
    RVSIP_RETRY_AFTER_PARAMS,
    RVSIP_RETRY_AFTER_BAD_SYNTAX

}RvSipRetryAfterHeaderStringName;

/****************************************************/
/*        CONSTRUCTORS AND DESTRUCTORS                */
/****************************************************/
/***************************************************************************
 * RvSipRetryAfterHeaderConstructInMsg
 * ------------------------------------------------------------------------
 * General: Constructs a Retry-After header object inside a given message object.
 *          The header is kept in the header list of the message. You can
 *          choose to insert the header either at the head or tail of the list.
 * Return Value: RV_OK, RV_ERROR_INVALID_HANDLE, RV_ERROR_NULLPTR, RV_ERROR_OUTOFRESOURCES
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hSipMsg - Handle to the message object.
 *         pushHeaderAtHead - Boolean value indicating whether the header
 *                            should be pushed to the head of the
 *                            list—RV_TRUE—or to the tail—RV_FALSE.
 * output: phHeader - Handle to the newly constructed retry-after header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRetryAfterHeaderConstructInMsg(
                                IN  RvSipMsgHandle            hSipMsg,
                                IN  RvBool                   pushHeaderAtHead,
                                OUT RvSipRetryAfterHeaderHandle* phHeader);

/***************************************************************************
 * RvSipRetryAfterHeaderConstruct
 * ------------------------------------------------------------------------
 * General: Constructs and initializes a stand-alone Retry-After Header object.
 *          The header is constructed on a given page taken from a specified
 *          pool. The handle to the new header object is returned.
 * Return Value: RV_OK, RV_ERROR_INVALID_HANDLE, RV_ERROR_NULLPTR, RV_ERROR_OUTOFRESOURCES.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hMsgMgr - Handle to the Message manager.
 *         hPool -   Handle to the memory pool that the object will use.
 *         hPage   - Handle to the memory page that the object will use.
 * output: phHeader - Handle to the newly constructed Retry-After header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRetryAfterHeaderConstruct(
                                        IN  RvSipMsgMgrHandle         hMsgMgr,
                                        IN  HRPOOL                    hPool,
                                        IN  HPAGE                     hPage,
                                        OUT RvSipRetryAfterHeaderHandle* phHeader);
/***************************************************************************
 * RvSipRetryAfterHeaderCopy
 * ------------------------------------------------------------------------
 * General:Copies all fields from a source retry-after header object to a
 *         destination retry-after header object.
 *         You must construct the destination object before using this function.
 * Return Value: RV_OK, RV_ERROR_OUTOFRESOURCES, RV_ERROR_INVALID_HANDLE.
 * ------------------------------------------------------------------------
 * Arguments:
 *    pDestination - Handle to the destination Retry-After header object.
 *    pSource      - Handle to the source Retry-After header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRetryAfterHeaderCopy(
                                     INOUT RvSipRetryAfterHeaderHandle hDestination,
                                     IN    RvSipRetryAfterHeaderHandle hSource);

/***************************************************************************
 * RvSipRetryAfterHeaderEncode
 * ------------------------------------------------------------------------
 * General: Encodes a Retry-After header object to a textual Retry-After header.
 *          The textual header is placed on a page taken from a specified pool.
 *          In order to copy the textual header from the page to a consecutive
 *          buffer, use RPOOL_CopyToExternal().
 *          The application must free the allocated page, using RPOOL_FreePage().
 *          The allocated page must be freed only if this function returns
 *          RV_OK.
 * Return Value: RV_OK          - If succeeded.
 *               RV_ERROR_OUTOFRESOURCES   - If allocation failed (no resources)
 *               RV_ERROR_UNKNOWN          - In case of a failure.
 *               RV_ERROR_BADPARAM - If hHeader or hPool are NULL or the
 *                                     header is not initialized.
 *               RV_ERROR_NULLPTR       - pLength or phPage are NULL.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader  - Handle to the Retry-After header object.
 *        hPool    - Handle to the specified memory pool.
 * output: phPage   - The memory page allocated to contain the encoded header.
 *         pLength  - The length of the encoded information.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRetryAfterHeaderEncode(
                                      IN    RvSipRetryAfterHeaderHandle hHeader,
                                      IN    HRPOOL                   hPool,
                                      OUT   HPAGE*                   phPage,
                                      OUT   RvUint32*               pLength);

/***************************************************************************
 * RvSipRetryAfterHeaderParse
 * ------------------------------------------------------------------------
 * General:Parses a SIP textual Retry-After header—for example,
 *         “RetryAfter: Thu, 01 Dec 2040 16:00:00 GMT”—into a RetryAfter header
 *          object. All the textual fields are placed inside the object.
 * Return Value: RV_OK, RV_ERROR_OUTOFRESOURCES,RV_ERROR_INVALID_HANDLE,
 *                 RV_ERROR_ILLEGAL_SYNTAX,RV_ERROR_ILLEGAL_SYNTAX.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader   -    A handle to the Retry-After header object.
 *    strBuffer    - Buffer containing a textual Retry-After header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRetryAfterHeaderParse(
                                     IN    RvSipRetryAfterHeaderHandle hHeader,
                                     IN    RvChar*                 strBuffer);

/***************************************************************************
 * RvSipRetryAfterHeaderParseValue
 * ------------------------------------------------------------------------
 * General: Parses a SIP textual RetryAfter header value into an RetryAfter
 *          header object.
 *          A SIP header has the following grammer:
 *          header-name:header-value. This function takes the header-value
 *          part as a parameter and parses it into the supplied object.
 *          All the textual fields are placed inside the object.
 *          Note: Use the RvSipRetryAfterHeaderParse() function to parse
 *          strings that also include the header-name.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader   - The handle to the RetryAfter header object.
 *    buffer    - The buffer containing a textual RetryAfter header value.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRetryAfterHeaderParseValue(
                                     IN    RvSipRetryAfterHeaderHandle hHeader,
                                     IN    RvChar*                 strBuffer);

/***************************************************************************
 * RvSipRetryAfterHeaderFix
 * ------------------------------------------------------------------------
 * General: Fixes an RetryAfter header with bad-syntax information.
 *          A SIP header has the following grammer:
 *          header-name:header-value. When a header contains a syntax error,
 *          the header-value is kept as a separate "bad-syntax" string.
 *          Use this function to fix the header. This function parses a given
 *          correct header-value string to the supplied header object.
 *          If parsing succeeds, this function places all fields inside the
 *          object and removes the bad syntax string.
 *          If parsing fails, the bad-syntax string in the header remains as it was.
 * Return Value: RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input: hHeader      - The handle to the header object.
 *        pFixedBuffer - The buffer containing a legal header value.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRetryAfterHeaderFix(
                                     IN RvSipRetryAfterHeaderHandle hHeader,
                                     IN RvChar*                    pFixedBuffer);

/***************************************************************************
 * RvSipRetryAfterHeaderGetStringLength
 * ------------------------------------------------------------------------
 * General: Some of the Retry-After header fields are kept in a string
 *          format — for example, the comment. In order to get
 *          such a field from the Retry-After header object, your application
 *          should supply an adequate buffer to where the string
 *          will be copied.
 *          This function provides you with the length of the string to enable
 *          you to allocate an appropriate buffer size before calling the Get
 *          function.
 * Return Value: Returns the length of the specified string.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader    - Handle to the Retry-After header object.
 *  stringName - Enumeration of the string name for which you require the length.
 ***************************************************************************/
RVAPI RvUint RVCALLCONV RvSipRetryAfterHeaderGetStringLength(
                                 IN  RvSipRetryAfterHeaderHandle     hHeader,
                                 IN  RvSipRetryAfterHeaderStringName stringName);

/***************************************************************************
 * RvSipRetryAfterHeaderGetFormat
 * ------------------------------------------------------------------------
 * General: Gets the format of the Retry-After header: Undefined, Date or
 *          Delta-seconds.
 * Return Value: The format enumeration.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input: hHeader - Handle to the Retry-After header object.
 ***************************************************************************/
RVAPI RvSipExpiresFormat RVCALLCONV RvSipRetryAfterHeaderGetFormat(
                                    IN  RvSipRetryAfterHeaderHandle hHeader);

/***************************************************************************
 * RvSipRetryAfterHeaderGetDeltaSeconds
 * ------------------------------------------------------------------------
 * General: Gets the delta-seconds integer of the Retry-After header.
 *          If the delta-seconds integer is not set, UNDEFINED is returned.
 * Return Value: RV_OK - success.
 *               RV_ERROR_INVALID_HANDLE - hHeader is NULL.
 *               RV_ERROR_NULLPTR - pDeltaSeconds is NULL.
 *               RV_ERROR_NOT_FOUND - delta-seconds were not defined for this
 *                             expires object.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input:  hHeader - Handle to the Retry-After header object.
 *  Output: pDeltaSeconds - The delta-seconds integer.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRetryAfterHeaderGetDeltaSeconds(
                                  IN  RvSipRetryAfterHeaderHandle hHeader,
                                  OUT RvUint32                   *pDeltaSeconds);

/***************************************************************************
 * RvSipRetryAfterHeaderSetDeltaSeconds
 * ------------------------------------------------------------------------
 * General: Sets the delta seconds integer of the Retry-After header. Changes
 *          the Retry-After format to delta-seconds. If the given delta-seconds
 *          is UNDEFINED, the delta-seconds of the Retry-After header is removed
 *          and the format is changed to UNDEFINED.
 * Return Value: RV_OK - success.
 *               RV_ERROR_INVALID_HANDLE - The Retry-After header handle is invalid.
 *               RV_Invalid parameter - The delta-seconds integer is negative
 *                                      other than UNDEFINED.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input: hHeader - Handle to the Retry-After header object.
 *         deltaSeconds - The delta-seconds to be set to the Retry-After header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRetryAfterHeaderSetDeltaSeconds(
                                   IN  RvSipRetryAfterHeaderHandle hHeader,
                                   IN  RvInt32                deltaSeconds);

/***************************************************************************
 * RvSipRetryAfterHeaderGetDateHandle
 * ------------------------------------------------------------------------
 * General: Gets the date Handle to the Retry-After header.
 * Return Value: Returns the handle to the date header object, or NULL
 *               if the date header object does not exist.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input: hHeader - Handle to the Retry-After header object.
 ***************************************************************************/
RVAPI RvSipDateHeaderHandle RVCALLCONV RvSipRetryAfterHeaderGetDateHandle(
                                        IN  RvSipRetryAfterHeaderHandle hHeader);

/***************************************************************************
 * RvSipRetryAfterHeaderSetDate
 * ------------------------------------------------------------------------
 * General: Sets a new Date header in the Retry-After header object and changes
 *          the Retry-After format to date. (The function allocates a date header,
 *          and copy the given hDate object to it).
 * Return Value: RV_OK - success.
 *               RV_ERROR_INVALID_HANDLE - The Retry-After header handle is invalid.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input: hHeader - Handle to the Retry-After header object.
 *         hDate - The date handle to be set to the Retry-After header.
 *                 If the date handle is NULL, the existing date header
 *                 is removed from the expires header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRetryAfterHeaderSetDate(
                                       IN  RvSipRetryAfterHeaderHandle hHeader,
                                       IN  RvSipDateHeaderHandle    hDate);

/***************************************************************************
 * RvSipRetryAfterHeaderGetDuration
 * ------------------------------------------------------------------------
 * General: Gets the duration integer of the Retry-After header.
 *          If the duration integer is not set, UNDEFINED is returned.
 * Return Value: RV_OK - success.
 *               RV_ERROR_INVALID_HANDLE - hHeader is NULL.
 *               RV_ERROR_NULLPTR - pDuration is NULL.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input:  hHeader - Handle to the Retry-After header object.
 *  Output: pDuration - The duration integer.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRetryAfterHeaderGetDuration(
                                  IN  RvSipRetryAfterHeaderHandle hHeader,
                                  OUT RvInt32                   *pDuration);

/***************************************************************************
 * RvSipRetryAfterHeaderSetDuration
 * ------------------------------------------------------------------------
 * General: Sets the duration integer of the Retry-After header. If the given duration
 *          is UNDEFINED, the duration of the Retry-After header is removed.
 * Return Value: RV_OK - success.
 *               RV_ERROR_INVALID_HANDLE - The Retry-After header handle is invalid.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input: hHeader - Handle to the Retry-After header object.
 *         duration - The duration to be set to the Retry-After header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRetryAfterHeaderSetDuration(
                                   IN  RvSipRetryAfterHeaderHandle hHeader,
                                   IN  RvInt32                   duration);
/***************************************************************************
 * RvSipRetryAfterHeaderGetstrComment
 * ------------------------------------------------------------------------
 * General: Copies the strComment field of the RetryAfter header object into a
 *          given buffer.
 *          If the bufferLen is adequate, the function copies the requested parameter into
 *          strBuffer. Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and actualLen
 *          contains the required buffer length.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader    - Handle to the RetryAfter header object.
 *        strBuffer  - Buffer to fill with the requested parameter.
 *        bufferLen  - The length of the buffer.
 * output:actualLen  - The length of the requested parameter, + 1 to include a NULL value
 *                     at the end of the parameter.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRetryAfterHeaderGetStrComment(
                                               IN RvSipRetryAfterHeaderHandle   hHeader,
                                               IN RvChar*                      strBuffer,
                                               IN RvUint                       bufferLen,
                                               OUT RvUint*                     actualLen);

/***************************************************************************
 * RvSipRetryAfterHeaderSetStrComment
 * ------------------------------------------------------------------------
 * General: Sets the strComment field in the RetryAfter header object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader    - Handle to the RetryAfter header object.
 *    strComment - The strComment string to be set in the RetryAfter header.
 *               If NULL is supplied, the existing strComment field
 *               is removed from the header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRetryAfterHeaderSetStrComment(
                                    IN    RvSipRetryAfterHeaderHandle hHeader,
                                    IN    RvChar *                   strComment);
/***************************************************************************
 * RvSipRetryAfterHeaderGetRetryAfterParams
 * ------------------------------------------------------------------------
 * General: Copies the RetryAfterParams field of the RetryAfter header object into a
 *          given buffer.
 *          Not all the RetryAfter header parameters have separated fields in the RetryAfter
 *          header object. Parameters with no specific fields are refered to as RetryAfterParams.
 *          They are kept in the object in one concatenated string in the form—
 *          ”name=value;name=value...”
 *          If the bufferLen is adequate, the function copies the requested parameter into
 *          strBuffer. Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and actualLen
 *          contains the required buffer length.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader    - Handle to the RetryAfter header object.
 *        strBuffer  - Buffer to fill with the requested parameter.
 *        bufferLen  - The length of the buffer.
 * output:actualLen - The length of the requested parameter, + 1 to include a NULL value at the end of
 *                     the parameter.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRetryAfterHeaderGetRetryAfterParams(
                                               IN RvSipRetryAfterHeaderHandle   hHeader,
                                               IN RvChar*                      strBuffer,
                                               IN RvUint                       bufferLen,
                                               OUT RvUint*                     actualLen);
/***************************************************************************
 * RvSipRetryAfterHeaderSetRetryAfterParams
 * ------------------------------------------------------------------------
 * General: Sets the RetryAfterParams field in the RetryAfter header object.
 *          Not all the RetryAfter header parameters have separated fields in the
 *          RetryAfter header object. Parameters with no specific fields are
 *          refered to as RetryAfterParams. They are kept in the object in one
 *          concatenated string in the form— ”name=value;name=value...”
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader             - Handle to the RetryAfter header object.
 *    strRetryAfterParams - The RetryAfter Params string to be set in the RetryAfter header.
 *                        If NULL is supplied, the existing RetryAfter Params field
 *                        is removed from the header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRetryAfterHeaderSetRetryAfterParams(
                                    IN    RvSipRetryAfterHeaderHandle hHeader,
                                    IN    RvChar *                   strRetryAfterParams);

/***************************************************************************
 * RvSipRetryAfterHeaderGetStrBadSyntax
 * ------------------------------------------------------------------------
 * General: Copies the bad-syntax string from the header object into a
 *          given buffer.
 *          A SIP header has the following grammer:
 *          header-name:header-value. When a header contains a syntax error,
 *          the header-value is kept as a separate "bad-syntax" string.
 *          You use this function to retrieve the bad-syntax string.
 *          If the value of bufferLen is adequate, this function copies
 *          the requested parameter into strBuffer. Otherwise, the function
 *          returns RV_ERROR_INSUFFICIENT_BUFFER and actualLen contains the required
 *          buffer length.
 *          Use this function in the RvSipTransportBadSyntaxMsgEv() callback
 *          implementation if the message contains a bad RetryAfter header,
 *          and you wish to see the header-value.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader    - The handle to the header object.
 *        strBuffer  - The buffer with which to fill the bad syntax string.
 *        bufferLen  - The length of the buffer.
 * output:actualLen  - The length of the bad syntax + 1, to include
 *                     a NULL value at the end of the parameter.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRetryAfterHeaderGetStrBadSyntax(
                                               IN RvSipRetryAfterHeaderHandle hHeader,
                                               IN RvChar*                 strBuffer,
                                               IN RvUint                  bufferLen,
                                               OUT RvUint*                actualLen);

/***************************************************************************
 * RvSipRetryAfterHeaderSetStrBadSyntax
 * ------------------------------------------------------------------------
 * General: Sets a bad-syntax string in the object.
 *          A SIP header has the following grammer:
 *          header-name:header-value. When a header contains a syntax error,
 *          the header-value is kept as a separate "bad-syntax" string.
 *          By using this function you can create a header with "bad-syntax".
 *          Setting a bad syntax string to the header will mark the header as
 *          an invalid syntax header.
 *          You can use his function when you want to send an illegal RetryAfter header.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader      - The handle to the header object.
 *  strBadSyntax - The bad-syntax string.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRetryAfterHeaderSetStrBadSyntax(
                                  IN RvSipRetryAfterHeaderHandle hHeader,
                                  IN RvChar*                     strBadSyntax);

#endif /*#ifndef RV_SIP_PRIMITIVES*/

#ifdef __cplusplus
}
#endif

#endif /* RVSIP_RETRYAFTER_HEADER_H */

