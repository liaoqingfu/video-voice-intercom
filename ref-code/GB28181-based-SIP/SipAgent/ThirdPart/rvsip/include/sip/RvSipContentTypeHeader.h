/*

NOTICE:
This document contains information that is proprietary to RADVision LTD..
No part of this publication may be reproduced in any form whatsoever without
written prior approval by RADVision LTD..

RADVision LTD. reserves the right to revise this publication and make changes
without obligation to notify any person of such revisions or changes.

*/

/******************************************************************************
 *                     RvSipContentTypeHeader.h                               *
 *                                                                            *
 * The file defines the methods of the Content-Type header object             *
 * construct, destruct, copy, encode, parse and the ability to access and     *
 * change it's parameters.                                                    *
 *                                                                            *
 *                                                                            *
 *      Author           Date                                                 *
 *     ------           ------------                                          *
 *     Tamar Barzuza    Aug 2001                                              *
 ******************************************************************************/


#ifndef RVSIPCONTENTTYPEHEADER_H
#define RVSIPCONTENTTYPEHEADER_H

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
 * RvSipContentTypeHeaderStringName
 * ----------------------
 * Defines all Content Type header object fields that are kept in
 * the object in a string format.
 */
typedef enum
{
    RVSIP_CONTENT_TYPE_MEDIATYPE,
    RVSIP_CONTENT_TYPE_MEDIASUBTYPE,
    RVSIP_CONTENT_TYPE_BOUNDARY,
    RVSIP_CONTENT_TYPE_VERSION,
    RVSIP_CONTENT_TYPE_BASE,
    RVSIP_CONTENT_TYPE_OTHER_PARAMS,
    RVSIP_CONTENT_TYPE_BAD_SYNTAX
} RvSipContentTypeHeaderStringName;

/*-----------------------------------------------------------------------*/
/*                   CONSTRUCTORS AND DESTRUCTORS                        */
/*-----------------------------------------------------------------------*/


/***************************************************************************
 * RvSipContentTypeHeaderConstructInBody
 * ------------------------------------------------------------------------
 * General: Constructs a Content-type header object inside a given message
 *          body object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hBody - Handle to the message body object.
 * output: hHeader - Handle to the newly constructed Content-Type header
 *                   object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipContentTypeHeaderConstructInBody(
                               IN  RvSipBodyHandle               hBody,
                               OUT RvSipContentTypeHeaderHandle* hHeader);

/***************************************************************************
 * RvSipContentTypeHeaderConstruct
 * ------------------------------------------------------------------------
 * General: Constructs and initializes a stand-alone Content-Type Header
 *          object. The header is constructed on a given page taken from a
 *          specified pool. The handle to the new header object is returned.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hMsgMgr - Handle to the message manager.
 *         hPool   - Handle to the memory pool that the object will use.
 *         hPage   - Handle to the memory page that the object will use.
 * output: hHeader - Handle to the newly constructed Content-Type header
 *                   object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipContentTypeHeaderConstruct(
                                    IN  RvSipMsgMgrHandle             hMsgMgr,
                                    IN  HRPOOL                        hPool,
                                    IN  HPAGE                         hPage,
                                    OUT RvSipContentTypeHeaderHandle* hHeader);

/***************************************************************************
 * RvSipContentTypeHeaderCopy
 * ------------------------------------------------------------------------
 * General: Copies all fields from a source Content-Type header object to
 *          a destination Content-Type header object.
 *          You must construct the destination object before using this
 *          function.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hDestination - Handle to the destination Content-Type header object.
 *    hSource      - Handle to the source Content-Type header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipContentTypeHeaderCopy(
                             INOUT RvSipContentTypeHeaderHandle hDestination,
                             IN    RvSipContentTypeHeaderHandle hSource);

/***************************************************************************
 * RvSipContentTypeHeaderEncode
 * ------------------------------------------------------------------------
 * General: Encodes a Content-Type header object to a textual Content-Type
 *          header. The textual header is placed on a page taken from a
 *          specified pool. In order to copy the textual header from the
 *          page to a consecutive buffer, use RPOOL_CopyToExternal().
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader  - Handle to the Content-Type header object.
 *        hPool    - Handle to the specified memory pool.
 * output: hPage   - The memory page allocated to contain the encoded header.
 *         length  - The length of the encoded information.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipContentTypeHeaderEncode(
                                IN    RvSipContentTypeHeaderHandle hHeader,
                                IN    HRPOOL                       hPool,
                                OUT   HPAGE*                       hPage,
                                OUT   RvUint32*                   length);
/***************************************************************************
 * RvSipContentTypeHeaderSetCompactForm
 * ------------------------------------------------------------------------
 * General: Instructs the header to use the compact header name when the
 *          header is encoded.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader  - Handle to the Allow header object.
 *        bIsCompact - specify whether or not to use a compact form
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipContentTypeHeaderSetCompactForm(
                                   IN    RvSipContentTypeHeaderHandle hHeader,
                                   IN    RvBool                bIsCompact);

/***************************************************************************
 * RvSipContentTypeHeaderParse
 * ------------------------------------------------------------------------
 * General:Parses a SIP textual ContentType header — for example:
 *         "Content-Type: multipart/mixed; boundart=unique"
 *         — into a Content-Type header object. All the textual fields are
 *         placed inside the object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader   - A handle to the Content-Type header object.
 *    buffer    - Buffer containing a textual Content-Type header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipContentTypeHeaderParse(
                                 IN    RvSipContentTypeHeaderHandle  hHeader,
                                 IN    RvChar*                      buffer);

/***************************************************************************
 * RvSipContentTypeHeaderParseValue
 * ------------------------------------------------------------------------
 * General: Parses a SIP textual ContentType header value into an ContentType
 *          header object.
 *          A SIP header has the following grammer:
 *          header-name:header-value. This function takes the header-value part as
 *          a parameter and parses it into the supplied object.
 *          All the textual fields are placed inside the object.
 *          Note: Use the RvSipContentTypeHeaderParse() function to parse
 *          strings that also include the header-name.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader   - The handle to the ContentType header object.
 *    buffer    - The buffer containing a textual ContentType header value.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipContentTypeHeaderParseValue(
                                 IN    RvSipContentTypeHeaderHandle  hHeader,
                                 IN    RvChar*                      buffer);

/***************************************************************************
 * RvSipContentTypeHeaderFix
 * ------------------------------------------------------------------------
 * General: Fixes an ContentType header with bad-syntax information.
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
RVAPI RvStatus RVCALLCONV RvSipContentTypeHeaderFix(
                                     IN RvSipContentTypeHeaderHandle hHeader,
                                     IN RvChar*                     pFixedBuffer);

/*-----------------------------------------------------------------------
                         G E T  A N D  S E T  M E T H O D S
 ------------------------------------------------------------------------*/

/***************************************************************************
 * RvSipContentTypeHeaderGetStringLength
 * ------------------------------------------------------------------------
 * General: Some of the Content-Type header fields are kept in a string format
 *          — for example, the Content-Type header parameter boundary. In order
 *          to get such a field from the Content-Type header object, your
 *          application should supply an adequate buffer to where the string
 *          will be copied.
 *          This function provides you with the length of the string to enable
 *          you to allocate an appropriate buffer size before calling the Get
 *          function.
 * Return Value: Returns the length of the specified string.
 * ------------------------------------------------------------------------
 * Arguments:
 *  hHeader    - Handle to the Content-Type header object.
 *  stringName - Enumeration of the string name for which you require the
 *               length.
 ***************************************************************************/
RVAPI RvUint RVCALLCONV RvSipContentTypeHeaderGetStringLength(
                             IN  RvSipContentTypeHeaderHandle     hHeader,
                             IN  RvSipContentTypeHeaderStringName stringName);

/***************************************************************************
 * RvSipContentTypeHeaderGetMediaType
 * ------------------------------------------------------------------------
 * General: Gets the media type enumeration value. If RVSIP_MEDIATYPE_OTHER
 *          is returned, you can receive the media type string using
 *          RvSipContentTypeHeaderGetMediaTypeStr().
 * Return Value: Returns enum value if SIP media type.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader    - Handle to the header object.
 ***************************************************************************/
RVAPI RvSipMediaType RVCALLCONV RvSipContentTypeHeaderGetMediaType(
                                   IN RvSipContentTypeHeaderHandle   hHeader);

/***************************************************************************
 * RvSipContentTypeHeaderGetStrMediaType
 * ------------------------------------------------------------------------
 * General: Copies the media type string from the Content-Type header into
 *          a given buffer. Use this function when the media type enumeration
 *          returned by RvSipContentTypeGetMediaType() is RVSIP_MEDIATYPE_OTHER.
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
RVAPI RvStatus RVCALLCONV RvSipContentTypeHeaderGetStrMediaType(
                                    IN RvSipContentTypeHeaderHandle   hHeader,
                                    IN RvChar*                       strBuffer,
                                    IN RvUint                        bufferLen,
                                    OUT RvUint*                      actualLen);

/***************************************************************************
 * RvSipContentTypeHeaderSetMediaType
 * ------------------------------------------------------------------------
 * General: Sets the media type field in the Content-Type header object.
 *          If the enumeration given by eMediaType is RVSIP_MEDIATYPE_OTHER,
 *          sets the media type string given by strMediaType in the
 *          Content-Type header object. Use RVSIP_MEDIATYPE_OTHER when the
 *          media type you wish to set to the Content-Type does not have a
 *          matching enumeration value in the RvSipMediaType enumeration.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader    - Handle to the Content-Type header object.
 *    eMediaType - The media type enumeration to be set in the Content-Type
 *               header object. If RVSIP_MEDIATYPE_UNDEFINED is supplied, the
 *               existing media type is removed from the header.
 *    strMediaType - The media type string to be set in the Content-Type header.
 *                (relevant when eMediaType is RVSIP_MEDIATYPE_OTHER).
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipContentTypeHeaderSetMediaType(
                                 IN  RvSipContentTypeHeaderHandle hHeader,
                                 IN  RvSipMediaType               eMediaType,
                                 IN  RvChar                     *strMediaType);

/***************************************************************************
 * RvSipContentTypeHeaderGetMediaSubType
 * ------------------------------------------------------------------------
 * General: Gets the media sub type enumeration value. If
 *          RVSIP_MEDIASUBTYPE_OTHER is returned, you can receive the media
 *          sub type string using RvSipContentTypeHeaderGetMediaSubTypeStr().
 * Return Value: Returns enum value if SIP media sub type.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader    - Handle to the header object.
 ***************************************************************************/
RVAPI RvSipMediaSubType RVCALLCONV RvSipContentTypeHeaderGetMediaSubType(
                                   IN RvSipContentTypeHeaderHandle   hHeader);

/***************************************************************************
 * RvSipContentTypeHeaderGetStrMediaSubType
 * ------------------------------------------------------------------------
 * General: Copies the media sub type string from the Content-Type header
 *          into a given buffer. Use this function when the media sub type
 *          enumeration returned by RvSipContentTypeGetMediaSubType() is
 *          RVSIP_MEDIASUBTYPE_OTHER.
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
RVAPI RvStatus RVCALLCONV RvSipContentTypeHeaderGetStrMediaSubType(
                                    IN RvSipContentTypeHeaderHandle   hHeader,
                                    IN RvChar*                       strBuffer,
                                    IN RvUint                        bufferLen,
                                    OUT RvUint*                      actualLen);

/***************************************************************************
 * RvSipContentTypeHeaderSetMediaSubType
 * ------------------------------------------------------------------------
 * General: Sets the media sub type field in the Content-Type header object.
 *          If the enumeration given by eMediaSubType is RVSIP_MEDIASUBTYPE_OTHER,
 *          sets the media sub type string given by strMediaSubType in the
 *          Content-Type header object. Use RVSIP_MEDIASUBTYPE_OTHER when the
 *          media type you wish to set to the Content-Type does not have a
 *          matching enumeration value in the RvSipMediaSubType enumeration.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader    - Handle to the Content-Type header object.
 *    eMediaSubType - The media sub type enumeration to be set in the Content-Type
 *               header object. If RVSIP_MEDIASUBTYPE_UNDEFINED is supplied, the
 *               existing media sub type is removed from the header.
 *    strMediaSubType - The media sub type string to be set in the Content-Type
 *               header. (relevant when eMediaSubType is RVSIP_MEDIASUBTYPE_OTHER).
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipContentTypeHeaderSetMediaSubType(
                            IN  RvSipContentTypeHeaderHandle hHeader,
                            IN  RvSipMediaSubType            eMediaSubType,
                            IN  RvChar                     *strMediaSubType);

/***************************************************************************
 * RvSipContentTypeHeaderGetBoundary
 * ------------------------------------------------------------------------
 * General: Copies the boundary string from the Content-Type header
 *          into a given buffer.
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
RVAPI RvStatus RVCALLCONV RvSipContentTypeHeaderGetBoundary(
                                    IN RvSipContentTypeHeaderHandle   hHeader,
                                    IN RvChar*                       strBuffer,
                                    IN RvUint                        bufferLen,
                                    OUT RvUint*                      actualLen);

/***************************************************************************
 * RvSipContentTypeHeaderSetBoundary
 * ------------------------------------------------------------------------
 * General: Sets the boundary string in the Content-Type header object.
 *          The given string is copied to the Content-Type header.
 *          Note that the given boundary may be quoted as defined in RFC 2046.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader     - Handle to the header object.
 *    boundary    - The boundary string to be set in the Content-Type header.
 *                If NULL is supplied, the existing boudary is removed from
 *                the header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipContentTypeHeaderSetBoundary(
                                 IN   RvSipContentTypeHeaderHandle  hHeader,
                                 IN   RvChar                      *boundary);

/***************************************************************************
 * RvSipContentTypeHeaderGetVersion
 * ------------------------------------------------------------------------
 * General: Copies the vesion string from the Content-Type header
 *          into a given buffer.
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
RVAPI RvStatus RVCALLCONV RvSipContentTypeHeaderGetVersion(
                                    IN RvSipContentTypeHeaderHandle   hHeader,
                                    IN RvChar*                       strBuffer,
                                    IN RvUint                        bufferLen,
                                    OUT RvUint*                      actualLen);

/***************************************************************************
 * RvSipContentTypeHeaderSetVersion
 * ------------------------------------------------------------------------
 * General: Sets the version string in the Content-Type header object.
 *          The given string is copied to the Content-Type header.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader     - Handle to the header object.
 *    version     - The version string to be set in the Content-Type header.
 *                If NULL is supplied, the existing version is removed from
 *                the header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipContentTypeHeaderSetVersion(
                                 IN   RvSipContentTypeHeaderHandle  hHeader,
                                 IN   RvChar                      *version);

/***************************************************************************
 * RvSipContentTypeHeaderGetBase
 * ------------------------------------------------------------------------
 * General: Copies the base string from the Content-Type header
 *          into a given buffer.
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
RVAPI RvStatus RVCALLCONV RvSipContentTypeHeaderGetBase(
                                    IN RvSipContentTypeHeaderHandle   hHeader,
                                    IN RvChar*                       strBuffer,
                                    IN RvUint                        bufferLen,
                                    OUT RvUint*                      actualLen);

/***************************************************************************
 * RvSipContentTypeHeaderSetBase
 * ------------------------------------------------------------------------
 * General: Sets the base string in the Content-Type header object.
 *          The given string is copied to the Content-Type header.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader     - Handle to the header object.
 *    base        - The base string to be set in the Content-Type header.
 *                If NULL is supplied, the existing base is removed from
 *                the header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipContentTypeHeaderSetBase(
                                 IN   RvSipContentTypeHeaderHandle  hHeader,
                                 IN   RvChar                      *base);

/***************************************************************************
 * RvSipContentTypeHeaderGetOtherParams
 * ------------------------------------------------------------------------
 * General: Copies the other parameters string from the Content-Type header
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
RVAPI RvStatus RVCALLCONV RvSipContentTypeHeaderGetOtherParams(
                                    IN RvSipContentTypeHeaderHandle   hHeader,
                                    IN RvChar*                       strBuffer,
                                    IN RvUint                        bufferLen,
                                    OUT RvUint*                      actualLen);

/***************************************************************************
 * RvSipContentTypeHeaderSetOtherParams
 * ------------------------------------------------------------------------
 * General: Sets the other parameters string in the Content-Type header object.
 *          The given string is copied to the Content-Type header.
 *          Not all the Content-Type header parameters have separated fields
 *          in the Content-Type header object. Parameters with no specific
 *          fields are refered to as other params. They are kept in the object
 *          in one concatenated string in the form— ”name=value;name=value...”
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader     - Handle to the header object.
 *    otherParams - The other parameters string to be set in the Content-Type
 *                header. If NULL is supplied, the existing parametes string
 *                is removed from the header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipContentTypeHeaderSetOtherParams(
                                 IN   RvSipContentTypeHeaderHandle  hHeader,
                                 IN   RvChar                      *otherParams);

/***************************************************************************
 * RvSipContentTypeHeaderGetStrBadSyntax
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
 *          implementation if the message contains a bad ContentType header,
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
RVAPI RvStatus RVCALLCONV RvSipContentTypeHeaderGetStrBadSyntax(
                                    IN RvSipContentTypeHeaderHandle   hHeader,
                                    IN RvChar*                       strBuffer,
                                    IN RvUint                        bufferLen,
                                    OUT RvUint*                      actualLen);

/***************************************************************************
 * RvSipContentTypeHeaderSetStrBadSyntax
 * ------------------------------------------------------------------------
 * General: Sets a bad-syntax string in the object.
 *          A SIP header has the following grammer:
 *          header-name:header-value. When a header contains a syntax error,
 *          the header-value is kept as a separate "bad-syntax" string.
 *          By using this function you can create a header with "bad-syntax".
 *          Setting a bad syntax string to the header will mark the header as
 *          an invalid syntax header.
 *          You can use his function when you want to send an illegal ContentType header.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *  hHeader      - The handle to the header object.
 *  strBadSyntax - The bad-syntax string.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipContentTypeHeaderSetStrBadSyntax(
                                  IN RvSipContentTypeHeaderHandle hHeader,
                                  IN RvChar*                     strBadSyntax);

#endif /*RV_SIP_PRIMITIVES*/

#ifdef __cplusplus
}
#endif

#endif /* RVSIPCONTENTTYPEHEADER_H */
