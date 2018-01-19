/*

NOTICE:
This document contains information that is proprietary to RADVision LTD..
No part of this publication may be reproduced in any form whatsoever without
written prior approval by RADVision LTD..

RADVision LTD. reserves the right to revise this publication and make changes
without obligation to notify any person of such revisions or changes.

*/

/******************************************************************************
 *                             RvSipMinSEHeader.c                             *
 *                                                                            *
 * The file defines the methods of the Min SE header object.                  *
 * The Min SE header functions enable you to construct, copy, encode, parse,  *
 * access and change Min-SE Header parameters.                                *
 *                                                                            *
 *      Author           Date                                                 *
 *     ------           ------------                                          *
 *     Michal Mashiach    June 2001                                           *
 ******************************************************************************/
#ifndef RVSIPMINSEHEADER_H
#define RVSIPMINSEHEADER_H

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

/*
 * RvSipMinSEHeaderStringName
 * ----------------------
 * Defines all MinSE header object fields that are kept in
 * the object in a string format.
 */
typedef enum
{
    RVSIP_MINSE_OTHER_PARAMS,
    RVSIP_MINSE_BAD_SYNTAX
} RvSipMinSEHeaderStringName;
/*-----------------------------------------------------------------------*/
/*                   CONSTRUCTORS AND DESTRUCTORS                        */
/*-----------------------------------------------------------------------*/

/***************************************************************************
 * RvSipMinSEHeaderConstructInMsg
 * ------------------------------------------------------------------------
 * General: Constructs a Min SE header object inside a given message object.
 *          The header is kept in the header list of the message. You can
 *          choose to insert the header either at the head or tail of the list.
 * Return Value: RV_OK, RV_ERROR_INVALID_HANDLE, RV_ERROR_NULLPTR, RV_ERROR_OUTOFRESOURCES
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hSipMsg - Handle to the message object.
 *         pushHeaderAtHead - Boolean value indicating whether the header
 *                            should be pushed to the head of the
 *                            list—RV_TRUE—or to the tail—RV_FALSE.
 * output: phHeader - Handle to the newly constructed Min SE header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMinSEHeaderConstructInMsg(
                        IN  RvSipMsgHandle          hSipMsg,
                        IN  RvBool                 pushHeaderAtHead,
                        OUT RvSipMinSEHeaderHandle* phHeader);


/***************************************************************************
 * RvSipMinSEHeaderConstruct
 * ------------------------------------------------------------------------
 * General: Constructs and initializes a stand-alone Min SE Header object.
 *          The header is constructed on a given page taken from a specified
 *          pool. The handle to the new header object is returned.
 * Return Value: RV_OK, RV_ERROR_INVALID_HANDLE, RV_ERROR_NULLPTR, RV_ERROR_OUTOFRESOURCES.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hMsgMgr  - Handle to the message manager.
 *         hPool    - Handle to the memory pool that the object will use.
 *         hPage    - Handle to the memory page that the object will use.
 * output: phHeader - Handle to the newly constructed Min SE  header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMinSEHeaderConstruct(
                               IN  RvSipMsgMgrHandle                hMsgMgr,
                               IN  HRPOOL                           hPool,
                               IN  HPAGE                            hPage,
                               OUT RvSipMinSEHeaderHandle* phHeader);


/***************************************************************************
 * RvSipMinSEHeaderCopy
 * ------------------------------------------------------------------------
 * General:Copies all fields from a source Min SE header object to a
 *         destination Min SE header object.
 *         You must construct the destination object before using this function.
 * Return Value: RV_OK, RV_ERROR_OUTOFRESOURCES, RV_ERROR_INVALID_HANDLE.
 * ------------------------------------------------------------------------
 * Arguments:
 *    pDestination - Handle to the destination Min SE header object.
 *    pSource      - Handle to the source Min SE header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMinSEHeaderCopy(
                                     INOUT RvSipMinSEHeaderHandle hDestination,
                                     IN    RvSipMinSEHeaderHandle hSource);


/***************************************************************************
 * RvSipMinSEHeaderEncode
 * ------------------------------------------------------------------------
 * General: Encodes a Min SE header object to a textual Min SE header.
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
 * input: hHeader  - Handle to the Min SE header object.
 *        hPool    - Handle to the specified memory pool.
 * output: phPage   - The memory page allocated to contain the encoded header.
 *         pLength  - The length of the encoded information.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMinSEHeaderEncode(
                              IN    RvSipMinSEHeaderHandle hHeader,
                              IN    HRPOOL                 hPool,
                              OUT   HPAGE*                 phPage,
                              OUT   RvUint32*             pLength);


/***************************************************************************
 * RvSipMinSEHeaderParse
 * ------------------------------------------------------------------------
 * General:Parses a SIP textual Min SE header—for example,
 *         “Min-SE: 3600 ” — into a Min SE header
 *          object. All the textual fields are placed inside the object.
 * Return Value: RV_OK, RV_ERROR_OUTOFRESOURCES,RV_ERROR_INVALID_HANDLE,
 *                 RV_ERROR_ILLEGAL_SYNTAX,RV_ERROR_ILLEGAL_SYNTAX.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader   -    A handle to the Min SE header object.
 *    strBuffer    - Buffer containing a textual Min SE header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMinSEHeaderParse(
                                     IN    RvSipMinSEHeaderHandle hHeader,
                                     IN    RvChar*               strBuffer);

/***************************************************************************
 * RvSipMinSEHeaderParseValue
 * ------------------------------------------------------------------------
 * General: Parses a SIP textual MinSE header value into an MinSE header object.
 *          A SIP header has the following grammer:
 *          header-name:header-value. This function takes the header-value part as
 *          a parameter and parses it into the supplied object.
 *          All the textual fields are placed inside the object.
 *          Note: Use the RvSipMinSEHeaderParse() function to parse strings that also
 *          include the header-name.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader   - The handle to the MinSE header object.
 *    buffer    - The buffer containing a textual MinSE header value.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMinSEHeaderParseValue(
                                     IN    RvSipMinSEHeaderHandle hHeader,
                                     IN    RvChar*               strBuffer);

/***************************************************************************
 * RvSipMinSEHeaderFix
 * ------------------------------------------------------------------------
 * General: Fixes an MinSE header with bad-syntax information.
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
RVAPI RvStatus RVCALLCONV RvSipMinSEHeaderFix(
                                     IN RvSipMinSEHeaderHandle hHeader,
                                     IN RvChar*               pFixedBuffer);

/*-----------------------------------------------------------------------
                         G E T  A N D  S E T  M E T H O D S
 ------------------------------------------------------------------------*/


/***************************************************************************
 * RvSipMinSEHeaderGetDeltaSeconds
 * ------------------------------------------------------------------------
 * General: Gets the delta-seconds integer of the Min SE header.
 *          If the delta-seconds integer is not set, UNDEFINED is returned.
 * Return Value: RV_OK - success.
 *               RV_ERROR_INVALID_HANDLE - hHeader is NULL.
 *               RV_ERROR_NULLPTR - pDeltaSeconds is NULL.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input:  hHeader - Handle to the Min SE header object.
 *  Output: pDeltaSeconds - The delta-seconds integer.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMinSEHeaderGetDeltaSeconds(
                    IN  RvSipMinSEHeaderHandle hHeader,
                    OUT RvInt32              *pDeltaSeconds);

/***************************************************************************
 * RvSipMinSEHeaderSetDeltaSeconds
 * ------------------------------------------------------------------------
 * General: Sets the delta seconds integer of the Min SE header.
 *          If the given delta-seconds is UNDEFINED, the delta-seconds of
 *          the Min SE header is removed
 * Return Value: RV_OK - success.
 *               RV_ERROR_INVALID_HANDLE - The Min SE header handle is invalid.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input: hHeader - Handle to the Min SE header object.
 *         deltaSeconds - The delta-seconds to be set to the Min SE header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMinSEHeaderSetDeltaSeconds(
                        IN  RvSipMinSEHeaderHandle hHeader,
                        IN  RvInt32              deltaSeconds);

/***************************************************************************
 * RvSipMinSEHeaderGetOtherParams
 * ------------------------------------------------------------------------
 * General: Copies the other parameters string from the MinSE header
 *          into a given buffer.
 *          Not all the Content-Type header parameters have separated fields
 *          in the Content-Type header object. Parameters with no specific
 *          fields are refered to as other params. They are kept in the object
 *          in one concatenated string in the form— ”name=value;name=value...”
 *          If the bufferLen is adequate, the function copies the requested
 *          parameter into strBuffer. Otherwise, the function returns
 *          RV_ERROR_INSUFFICIENT_BUFFER and actualLen contains the required buffer
 *          length.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader    - Handle to the header object.
 *        strBuffer  - Buffer to fill with the requested parameter.
 *        bufferLen  - The length of the buffer.
 * output:actualLen  - The length of the requested parameter, + 1 to include
 *                     a NULL value at the end of the parameter.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMinSEHeaderGetOtherParams(
                                    IN RvSipMinSEHeaderHandle hHeader,
                                    IN RvChar*                        strBuffer,
                                    IN RvUint                         bufferLen,
                                    OUT RvUint*                       actualLen);
/***************************************************************************
 * RvSipMinSEHeaderSetOtherParams
 * ------------------------------------------------------------------------
 * General: Sets the other parameters string in the MinSE header object.
 *          The given string is copied to the MinSE header.
 *          Not all the MinSE header parameters have separated fields
 *          in the MinSE header object. Parameters with no specific
 *          fields are refered to as other params. They are kept in the object
 *          in one concatenated string in the form— ”name=value;name=value...”
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader     - Handle to the header object.
 *    otherParams - The other parameters string to be set in the MinSE
 *                header. If NULL is supplied, the existing parametes string
 *                is removed from the header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMinSEHeaderSetOtherParams(
                                 IN   RvSipMinSEHeaderHandle  hHeader,
                                 IN   RvChar                      *otherParams);
/***************************************************************************
 * RvSipMinSEHeaderGetStringLength
 * ------------------------------------------------------------------------
 * General: The other params of MinSE header fields are kept in a string
 *          format.
 *          In order to get such a field from the MinSE header
 *          object, your application should supply an adequate buffer to where
 *          the string will be copied.
 *          This function provides you with the length of the string to enable
 *          you to allocate an appropriate buffer size before calling the Get
 *          function.
 * Return Value: Returns the length of the specified string.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader    - Handle to the MinSE header object.
 *  stringName - Enumeration of the string name for which you require the
 *               length.
 ***************************************************************************/
RVAPI RvUint RVCALLCONV RvSipMinSEHeaderGetStringLength(
                      IN  RvSipMinSEHeaderHandle     hHeader,
                      IN  RvSipMinSEHeaderStringName stringName);


/***************************************************************************
 * RvSipMinSEHeaderGetStrBadSyntax
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
 *          implementation if the message contains a bad MinSE header,
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
RVAPI RvStatus RVCALLCONV RvSipMinSEHeaderGetStrBadSyntax(
                                               IN RvSipMinSEHeaderHandle hHeader,
                                               IN RvChar*                 strBuffer,
                                               IN RvUint                  bufferLen,
                                               OUT RvUint*                actualLen);
/***************************************************************************
 * RvSipMinSEHeaderSetStrBadSyntax
 * ------------------------------------------------------------------------
 * General: Sets a bad-syntax string in the object.
 *          A SIP header has the following grammer:
 *          header-name:header-value. When a header contains a syntax error,
 *          the header-value is kept as a separate "bad-syntax" string.
 *          By using this function you can create a header with "bad-syntax".
 *          Setting a bad syntax string to the header will mark the header as
 *          an invalid syntax header.
 *          You can use his function when you want to send an illegal MinSE header.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader      - The handle to the header object.
 *  strBadSyntax - The bad-syntax string.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMinSEHeaderSetStrBadSyntax(
                                  IN RvSipMinSEHeaderHandle hHeader,
                                  IN RvChar*                     strBadSyntax);

#endif /* RV_SIP_PRIMITIVES*/

#ifdef __cplusplus
}
#endif

#endif /* END OF: #ifndef RVSIPMINSEHEADER_H */

