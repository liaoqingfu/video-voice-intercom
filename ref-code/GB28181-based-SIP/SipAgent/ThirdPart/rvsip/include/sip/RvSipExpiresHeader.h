/*

NOTICE:
This document contains information that is proprietary to RADVision LTD..
No part of this publication may be reproduced in any form whatsoever without
written prior approval by RADVision LTD..

RADVision LTD. reserves the right to revise this publication and make changes
without obligation to notify any person of such revisions or changes.

*/

/******************************************************************************
 *                             RvSipExpiresHeader.h                           *
 *                                                                            *
 * The file defines the methods of the Expires header object.                 *
 * The Expires header functions enable you to construct, copy, encode, parse, *
 * access and change Expires Header parameters.                               *                                                *
 *                                                                            *
 *      Author           Date                                                 *
 *     ------           ------------                                          *
 *     Tamar Barzuza    Jan 2001                                              *
 ******************************************************************************/
#ifndef RVSIPEXPIRESHEADER_H
#define RVSIPEXPIRESHEADER_H

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                           */
/*-----------------------------------------------------------------------*/
#include "RV_SIP_DEF.h"

#include "RvSipMsgTypes.h"
#include "rpool_API.h"

/*-----------------------------------------------------------------------*/
/*                   DECLERATIONS                                        */
/*-----------------------------------------------------------------------*/
/*
 * RvSipExpiresHeaderStringName
 * ----------------------------
 * This enum defines all the header's strings (for getting it's size)
 * Defines all Expires header object fields that are kept in the object 
 * in string format.
 */
typedef enum
{
    RVSIP_EXPIRES_BAD_SYNTAX
}RvSipExpiresHeaderStringName;

/*-----------------------------------------------------------------------*/
/*                   CONSTRUCTORS AND DESTRUCTORS                        */
/*-----------------------------------------------------------------------*/

/***************************************************************************
 * RvSipExpiresHeaderConstructInMsg
 * ------------------------------------------------------------------------
 * General: Constructs a Expires header object inside a given message object.
 *          The header is kept in the header list of the message. You can
 *          choose to insert the header either at the head or tail of the list.
 * Return Value: RV_OK, RV_ERROR_INVALID_HANDLE, RV_ERROR_NULLPTR, RV_ERROR_OUTOFRESOURCES
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hSipMsg - Handle to the message object.
 *         pushHeaderAtHead - Boolean value indicating whether the header
 *                            should be pushed to the head of the
 *                            list—RV_TRUE—or to the tail—RV_FALSE.
 * output: phHeader - Handle to the newly constructed Expires header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipExpiresHeaderConstructInMsg(
                                IN  RvSipMsgHandle            hSipMsg,
                                IN  RvBool                   pushHeaderAtHead,
                                OUT RvSipExpiresHeaderHandle* phHeader);

/***************************************************************************
 * RvSipExpiresConstructInContactHeader
 * ------------------------------------------------------------------------
 * General: Constructs an Expires object inside a given Contact header.
 *          The header handle is returned.
 * Return Value: RV_OK, RV_ERROR_INVALID_HANDLE, RV_ERROR_NULLPTR, RV_ERROR_OUTOFRESOURCES
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hHeader - Handle to the Contact header that relates to this Expires object.
 * output: phExpires - Handle to the newly constructed expires object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipExpiresConstructInContactHeader(
                                       IN  RvSipContactHeaderHandle  hHeader,
                                       OUT RvSipExpiresHeaderHandle *phExpires);

/***************************************************************************
 * RvSipExpiresHeaderConstruct
 * ------------------------------------------------------------------------
 * General: Constructs and initializes a stand-alone Expires Header object.
 *          The header is constructed on a given page taken from a specified
 *          pool. The handle to the new header object is returned.
 * Return Value: RV_OK, RV_ERROR_INVALID_HANDLE, RV_ERROR_NULLPTR, RV_ERROR_OUTOFRESOURCES.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hMsgMgr  - Handle to the message manager.
 *         hPool -   Handle to the memory pool that the object will use.
 *         hPage   - Handle to the memory page that the object will use.
 * output: phHeader - Handle to the newly constructed Expires header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipExpiresHeaderConstruct(
                                        IN  RvSipMsgMgrHandle         hMsgMgr,
                                        IN  HRPOOL                    hPool,
                                        IN  HPAGE                     hPage,
                                        OUT RvSipExpiresHeaderHandle* phHeader);


/***************************************************************************
 * RvSipExpiresHeaderCopy
 * ------------------------------------------------------------------------
 * General:Copies all fields from a source Expires header object to a
 *         destination Expires header object.
 *         You must construct the destination object before using this function.
 * Return Value: RV_OK, RV_ERROR_OUTOFRESOURCES, RV_ERROR_INVALID_HANDLE.
 * ------------------------------------------------------------------------
 * Arguments:
 *    pDestination - Handle to the destination Expires header object.
 *    pSource      - Handle to the source Expires header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipExpiresHeaderCopy(
                                     INOUT RvSipExpiresHeaderHandle hDestination,
                                     IN    RvSipExpiresHeaderHandle hSource);


/***************************************************************************
 * RvSipExpiresHeaderEncode
 * ------------------------------------------------------------------------
 * General: Encodes a Expires header object to a textual Expires header.
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
 * input: hHeader  - Handle to the Expires header object.
 *        hPool    - Handle to the specified memory pool.
 * output: phPage   - The memory page allocated to contain the encoded header.
 *         pLength  - The length of the encoded information.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipExpiresHeaderEncode(
                                      IN    RvSipExpiresHeaderHandle hHeader,
                                      IN    HRPOOL                   hPool,
                                      OUT   HPAGE*                   phPage,
                                      OUT   RvUint32*               pLength);


/***************************************************************************
 * RvSipExpiresHeaderParse
 * ------------------------------------------------------------------------
 * General:Parses a SIP textual expires header—for example,
 *         “Expires: Thu, 01 Dec 2040 16:00:00 GMT”—into a Expires header
 *          object. All the textual fields are placed inside the object.
 * Return Value: RV_OK, RV_ERROR_OUTOFRESOURCES,RV_ERROR_INVALID_HANDLE,
 *                 RV_ERROR_ILLEGAL_SYNTAX,RV_ERROR_ILLEGAL_SYNTAX.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader   -    A handle to the Expires header object.
 *    strBuffer    - Buffer containing a textual Expires header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipExpiresHeaderParse(
                                     IN    RvSipExpiresHeaderHandle hHeader,
                                     IN    RvChar*                 strBuffer);

/***************************************************************************
 * RvSipExpiresHeaderParseValue
 * ------------------------------------------------------------------------
 * General: Parses a SIP textual Expires header value into an Expires header object.
 *          A SIP header has the following grammer:
 *          header-name:header-value. This function takes the header-value part as
 *          a parameter and parses it into the supplied object.
 *          All the textual fields are placed inside the object.
 *          Note: Use the RvSipExpiresHeaderParse() function to parse strings that also
 *          include the header-name.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader   - The handle to the Expires header object.
 *    buffer    - The buffer containing a textual Expires header value.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipExpiresHeaderParseValue(
                                     IN    RvSipExpiresHeaderHandle hHeader,
                                     IN    RvChar*                 strBuffer);

/***************************************************************************
 * RvSipExpiresHeaderFix
 * ------------------------------------------------------------------------
 * General: Fixes an Expires header with bad-syntax information.
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
RVAPI RvStatus RVCALLCONV RvSipExpiresHeaderFix(
                                     IN RvSipExpiresHeaderHandle hHeader,
                                     IN RvChar*                 pFixedBuffer);

/*-----------------------------------------------------------------------
                         G E T  A N D  S E T  M E T H O D S
 ------------------------------------------------------------------------*/
/***************************************************************************
 * RvSipExpiresHeaderGetStringLength
 * ------------------------------------------------------------------------
 * General: Some of the Expires header fields are kept in a string format.
 *          In order to get such a field from the Expires header object,
 *          your application should supply an adequate buffer to where the
 *          string will be copied.
 *          This function provides you with the length of the string to enable
 *          you to allocate an appropriate buffer size before calling the Get function.
 * Return Value: Returns the length of the specified string.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader    - Handle to the Expires header object.
 *  stringName - Enumeration of the string name for which you require the length.
 ***************************************************************************/
RVAPI RvUint RVCALLCONV RvSipExpiresHeaderGetStringLength(
                                      IN  RvSipExpiresHeaderHandle     hHeader,
                                      IN  RvSipExpiresHeaderStringName stringName);

/***************************************************************************
 * RvSipExpiresHeaderGetFormat
 * ------------------------------------------------------------------------
 * General: Gets the format of the Expires header: Undefined, Date or
 *          Delta-seconds.
 * Return Value: The format enumeration.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input: hHeader - Handle to the Expires header object.
 ***************************************************************************/
RVAPI RvSipExpiresFormat RVCALLCONV RvSipExpiresHeaderGetFormat(
                                    IN  RvSipExpiresHeaderHandle     hHeader);


/***************************************************************************
 * RvSipExpiresHeaderGetDeltaSeconds
 * ------------------------------------------------------------------------
 * General: Gets the delta-seconds integer of the Expires header.
 *          If the delta-seconds integer is not set, UNDEFINED is returned.
 * Return Value: RV_OK - success.
 *               RV_ERROR_INVALID_HANDLE - hHeader is NULL.
 *               RV_ERROR_NULLPTR - pDeltaSeconds is NULL.
 *               RV_ERROR_NOT_FOUND - delta-seconds were not defined for this
 *                             expires object.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input:  hHeader - Handle to the Expires header object.
 *  Output: pDeltaSeconds - The delta-seconds integer.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipExpiresHeaderGetDeltaSeconds(
                                  IN  RvSipExpiresHeaderHandle hHeader,
                                  OUT RvUint32               *pDeltaSeconds);


/***************************************************************************
 * RvSipExpiresHeaderSetDeltaSeconds
 * ------------------------------------------------------------------------
 * General: Sets the delta seconds integer of the Expires header. Changes
 *          the Expires format to delta-seconds. If the given delta-seconds
 *          is UNDEFINED, the delta-seconds of the Expires header is removed
 *          and the format is changed to UNDEFINED.
 * Return Value: RV_OK - success.
 *               RV_ERROR_INVALID_HANDLE - The Expires header handle is invalid.
 *               RV_Invalid parameter - The delta-seconds integer is negative
 *                                      other than UNDEFINED.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input: hHeader - Handle to the Expires header object.
 *         deltaSeconds - The delta-seconds to be set to the Expires header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipExpiresHeaderSetDeltaSeconds(
                                   IN  RvSipExpiresHeaderHandle hHeader,
                                   IN  RvInt32                deltaSeconds);


/***************************************************************************
 * RvSipExpiresHeaderGetDateHandle
 * ------------------------------------------------------------------------
 * General: Gets the date Handle to the Expires header.
 * Return Value: Returns the handle to the date header object, or NULL
 *               if the date header object does not exist.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input: hHeader - Handle to the Expires header object.
 ***************************************************************************/
RVAPI RvSipDateHeaderHandle RVCALLCONV RvSipExpiresHeaderGetDateHandle(
                                        IN  RvSipExpiresHeaderHandle hHeader);


/***************************************************************************
 * RvSipExpiresHeaderSetDateHandle
 * ------------------------------------------------------------------------
 * General: Sets a new Date header in the Expires header object and changes
 *          the Expires format to date.
 * Return Value: RV_OK - success.
 *               RV_ERROR_INVALID_HANDLE - The Expires header handle is invalid.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input: hHeader - Handle to the Expires header object.
 *         hDate - The date handle to be set to the Expires header.
 *                 If the date handle is NULL, the existing date header
 *                 is removed from the expires header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipExpiresHeaderSetDateHandle(
                                       IN  RvSipExpiresHeaderHandle hHeader,
                                       IN  RvSipDateHeaderHandle    hDate);

/***************************************************************************
 * RvSipExpiresHeaderGetStrBadSyntax
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
 *          implementation if the message contains a bad Expires header,
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
RVAPI RvStatus RVCALLCONV RvSipExpiresHeaderGetStrBadSyntax(
                                               IN RvSipExpiresHeaderHandle hHeader,
                                               IN RvChar*                 strBuffer,
                                               IN RvUint                  bufferLen,
                                               OUT RvUint*                actualLen);
/***************************************************************************
 * RvSipExpiresHeaderSetStrBadSyntax
 * ------------------------------------------------------------------------
 * General: Sets a bad-syntax string in the object.
 *          A SIP header has the following grammer:
 *          header-name:header-value. When a header contains a syntax error,
 *          the header-value is kept as a separate "bad-syntax" string.
 *          By using this function you can create a header with "bad-syntax".
 *          Setting a bad syntax string to the header will mark the header as
 *          an invalid syntax header.
 *          You can use his function when you want to send an illegal Expires header.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader      - The handle to the header object.
 *  strBadSyntax - The bad-syntax string.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipExpiresHeaderSetStrBadSyntax(
                                  IN RvSipExpiresHeaderHandle hHeader,
                                  IN RvChar*                     strBadSyntax);

#ifdef __cplusplus
}
#endif

#endif /* END OF: #ifndef RVSIPEXPIRESHEADER_H */

