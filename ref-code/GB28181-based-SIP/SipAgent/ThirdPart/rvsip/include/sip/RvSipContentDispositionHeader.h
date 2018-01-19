/*

NOTICE:
This document contains information that is proprietary to RADVision LTD..
No part of this publication may be reproduced in any form whatsoever without
written prior approval by RADVision LTD..

RADVision LTD. reserves the right to revise this publication and make changes
without obligation to notify any person of such revisions or changes.

*/

/******************************************************************************
 *                     RvSipContentDispositionHeader.h                        *
 *                                                                            *
 * The file defines the methods of the Content-Diposition header object       *
 * construct, destruct, copy, encode, parse and the ability to access and     *
 * change it's parameters.                                                    *
 *                                                                            *
 *                                                                            *
 *      Author           Date                                                 *
 *     ------           ------------                                          *
 *     Tamar Barzuza    Aug 2001                                              *
 ******************************************************************************/


#ifndef RVSIPCONTENTDISPOSITIONHEADER_H
#define RVSIPCONTENTDISPOSITIONHEADER_H

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
 * RvSipContentDispositionHeaderStringName
 * ----------------------
 * Defines all Content Disposition header object fields that are kept in
 * the object in a string format.
 */
typedef enum
{
    RVSIP_CONTENT_DISPOSITION_TYPE,
    RVSIP_CONTENT_DISPOSITION_HANDLING,
    RVSIP_CONTENT_DISPOSITION_OTHER_PARAMS,
    RVSIP_CONTENT_DISPOSITION_BAD_SYNTAX
} RvSipContentDispositionHeaderStringName;

/*-----------------------------------------------------------------------*/
/*                   CONSTRUCTORS AND DESTRUCTORS                        */
/*-----------------------------------------------------------------------*/


/***************************************************************************
 * RvSipContentDispositionHeaderConstructInMsg
 * ------------------------------------------------------------------------
 * General: Constructs a Content-Disposition header object inside a given
 *          message object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hSipMsg - Handle to the message object.
 *         pushHeaderAtHead - Boolean value indicating whether the header
 *                            should be pushed to the head of the list(RV_TRUE)
 *                            or to the tail (RV_FALSE).
 * output: hHeader - Handle to the newly constructed Content-Disposition header
 *                   object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipContentDispositionHeaderConstructInMsg(
                        IN  RvSipMsgHandle                       hSipMsg,
                        IN  RvBool                               pushHeaderAtHead,
                        OUT RvSipContentDispositionHeaderHandle* hHeader);

/***************************************************************************
 * RvSipContentDispositionHeaderConstructInBodyPart
 * ------------------------------------------------------------------------
 * General: Constructs a Content-Disposition header object inside a given
 *          message body part object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hBodyPart - Handle to the message body part object.
 * output: hHeader   - Handle to the newly constructed Content-Disposition header
 *                     object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipContentDispositionHeaderConstructInBodyPart(
                        IN  RvSipBodyPartHandle                  hBodyPart,
                        OUT RvSipContentDispositionHeaderHandle* hHeader);

/***************************************************************************
 * RvSipContentDispositionHeaderConstruct
 * ------------------------------------------------------------------------
 * General: Constructs and initializes a stand-alone Content-Disposition Header
 *          object. The header is constructed on a given page taken from a
 *          specified pool. The handle to the new header object is returned.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hMsgMgr - Handle to the message manager.
 *         hPool   - Handle to the memory pool that the object will use.
 *         hPage   - Handle to the memory page that the object will use.
 * output: hHeader - Handle to the newly constructed Content-Disposition header
 *                   object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipContentDispositionHeaderConstruct(
                              IN  RvSipMsgMgrHandle                    hMsgMgr,
                              IN  HRPOOL                               hPool,
                              IN  HPAGE                                hPage,
                              OUT RvSipContentDispositionHeaderHandle* hHeader);

/***************************************************************************
 * RvSipContentDispositionHeaderCopy
 * ------------------------------------------------------------------------
 * General: Copies all fields from a source Content-Disposition header object
 *          to a destination Content-Disposition header object.
 *          You must construct the destination object before using this
 *          function.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hDestination - Handle to the destination Content-Disposition header object.
 *    hSource      - Handle to the source Content-Disposition header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipContentDispositionHeaderCopy(
                        INOUT RvSipContentDispositionHeaderHandle hDestination,
                        IN    RvSipContentDispositionHeaderHandle hSource);

/***************************************************************************
 * RvSipContentDispositionHeaderEncode
 * ------------------------------------------------------------------------
 * General: Encodes a Content-Disposition header object to a textual
 *          Content-Disposition header. The textual header is placed on a page
 *          taken from a specified pool. In order to copy the textual header
 *          from the page to a consecutive buffer, use RPOOL_CopyToExternal().
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader  - Handle to the Content-Disposition header object.
 *        hPool    - Handle to the specified memory pool.
 * output: hPage   - The memory page allocated to contain the encoded header.
 *         length  - The length of the encoded information.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipContentDispositionHeaderEncode(
                             IN    RvSipContentDispositionHeaderHandle hHeader,
                             IN    HRPOOL                              hPool,
                             OUT   HPAGE*                              hPage,
                             OUT   RvUint32*                          length);

/***************************************************************************
 * RvSipContentDispositionHeaderParse
 * ------------------------------------------------------------------------
 * General:Parses a SIP textual Content-Disposition header — for example:
 *         "Content-Disposition: signal; handling=optional"
 *         — into a Content-Disposition header object. All the textual
 *         fields are placed inside the object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader   - A handle to the Content-Disposition header object.
 *    buffer    - Buffer containing a textual Content-Disposition header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipContentDispositionHeaderParse(
                           IN    RvSipContentDispositionHeaderHandle  hHeader,
                           IN    RvChar*                             buffer);

/***************************************************************************
 * RvSipContentDispositionHeaderParseValue
 * ------------------------------------------------------------------------
 * General: Parses a SIP textual ContentDisposition header value into an
 *          ContentDisposition header object.
 *          A SIP header has the following grammer:
 *          header-name:header-value. This function takes the header-value
 *          part as a parameter and parses it into the supplied object.
 *          All the textual fields are placed inside the object.
 *          Note: Use the RvSipContentDispositionHeaderParse() function to
 *          parse strings that also include the header-name.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader   - The handle to the ContentDisposition header object.
 *    buffer    - The buffer containing a textual ContentDisposition header value.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipContentDispositionHeaderParseValue(
                           IN    RvSipContentDispositionHeaderHandle  hHeader,
                           IN    RvChar*                             buffer);

/***************************************************************************
 * RvSipContentDispositionHeaderFix
 * ------------------------------------------------------------------------
 * General: Fixes an ContentDisposition header with bad-syntax information.
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
RVAPI RvStatus RVCALLCONV RvSipContentDispositionHeaderFix(
                                     IN RvSipContentDispositionHeaderHandle hHeader,
                                     IN RvChar*                            pFixedBuffer);

/*-----------------------------------------------------------------------
                         G E T  A N D  S E T  M E T H O D S
 ------------------------------------------------------------------------*/

/***************************************************************************
 * RvSipContentDispositionHeaderGetStringLength
 * ------------------------------------------------------------------------
 * General: Some of the Content-Disposition header fields are kept in a string
 *          format — for example, the Content-Disposition header parameter
 *          handling may be in a string format in case it's value is not
 *          enumerated by RvSipDispositionHandling.
 *          In order to get such a field from the Content-Disposition header
 *          object, your application should supply an adequate buffer to where
 *          the string will be copied.
 *          This function provides you with the length of the string to enable
 *          you to allocate an appropriate buffer size before calling the Get
 *          function.
 * Return Value: Returns the length of the specified string.
 * ------------------------------------------------------------------------
 * Arguments:
 *  hHeader    - Handle to the Content-Disposition header object.
 *  stringName - Enumeration of the string name for which you require the
 *               length.
 ***************************************************************************/
RVAPI RvUint RVCALLCONV RvSipContentDispositionHeaderGetStringLength(
                        IN  RvSipContentDispositionHeaderHandle     hHeader,
                        IN  RvSipContentDispositionHeaderStringName stringName);

/***************************************************************************
 * RvSipContentDispositionHeaderGetType
 * ------------------------------------------------------------------------
 * General: Gets the disposition type enumeration value.
 *          If RVSIP_DISPOSITIONTYPE_OTHER is returned, you can receive the
 *          disposition type string using
 *          RvSipContentDispositionHeaderGetTypeStr().
 * Return Value: The disposition type enumeration value.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader    - Handle to the header object.
 ***************************************************************************/
RVAPI RvSipDispositionType RVCALLCONV RvSipContentDispositionHeaderGetType(
                            IN RvSipContentDispositionHeaderHandle   hHeader);

/***************************************************************************
 * RvSipContentDispositionHeaderGetStrType
 * ------------------------------------------------------------------------
 * General: Copies the disposition type string from the Content-Disposition
 *          header into a given buffer. Use this function when the disposition
 *          type enumeration returned by RvSipContentDispositionGetType()
 *          is RVSIP_DISPOSITIONTYPE_OTHER.
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
RVAPI RvStatus RVCALLCONV RvSipContentDispositionHeaderGetStrType(
                              IN RvSipContentDispositionHeaderHandle hHeader,
                              IN RvChar*                            strBuffer,
                              IN RvUint                             bufferLen,
                              OUT RvUint*                           actualLen);

/***************************************************************************
 * RvSipContentDispositionHeaderSetType
 * ------------------------------------------------------------------------
 * General: Sets the disposition type field in the Content-Disposition header
 *          object. If the enumeration given by eDispType is
 *          RVSIP_DISPOSITIONTYPE_OTHER, sets the disposition type string
 *          given by strDispType in the Content-Type header object. Use
 *          RVSIP_DISPOSITIONTYPE_OTHER when the disposition type you wish to
 *          set to the Content-Type does not have a matching enumeration value
 *          in the RvSipDispositionType enumeration.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader    - Handle to the Content-Disposition header object.
 *    eDispType  - The disposition type enumeration to be set in the
 *               Content-Type header object. If RVSIP_DISPOSITIONTYPE_UNDEFINED
 *               is supplied, the existing disposition type is removed from the
 *               header.
 *    strDispType - The disposition type string to be set in the Content-Type
 *                header. (relevant when eDispType is RVSIP_DISPOSITIONTYPE_OTHER).
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipContentDispositionHeaderSetType(
                    IN  RvSipContentDispositionHeaderHandle hHeader,
                    IN  RvSipDispositionType                eDispType,
                    IN  RvChar                            *strDispType);

/***************************************************************************
 * RvSipContentDispositionHeaderGetHandling
 * ------------------------------------------------------------------------
 * General: Gets the handling enumeration value. If
 *          RVSIP_DISPOSITIONHANDLING_OTHER is returned, you can receive the
 *          handling string using RvSipContentDispositionHeaderGetHandlingStr().
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader    - Handle to the header object.
 ***************************************************************************/
RVAPI RvSipDispositionHandling RVCALLCONV
                            RvSipContentDispositionHeaderGetHandling(
                               IN RvSipContentDispositionHeaderHandle   hHeader);

/***************************************************************************
 * RvSipContentDispositionHeaderGetStrHandling
 * ------------------------------------------------------------------------
 * General: Copies the handling string from the Content-Disposition header
 *          into a given buffer. Use this function when the handling
 *          enumeration returned by RvSipContentDispositionGetHandling() is
 *          RVSIP_DISPOSITIONHANDLING_OTHER.
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
RVAPI RvStatus RVCALLCONV RvSipContentDispositionHeaderGetStrHandling(
                            IN RvSipContentDispositionHeaderHandle   hHeader,
                            IN RvChar*                              strBuffer,
                            IN RvUint                               bufferLen,
                            OUT RvUint*                             actualLen);

/***************************************************************************
 * RvSipContentDispositionHeaderSetHandling
 * ------------------------------------------------------------------------
 * General: Sets the handling field in the Content-Disposition header
 *          object. If the enumeration given by eHandling is
 *          RVSIP_DISPOSITIONHANDLING_OTHER, sets the handling string
 *          given by strHandling in the Content-Type header object. Use
 *          RVSIP_DISPOSITIONHANDLING_OTHER when the disposition type you wish
 *          to set to the Content-Type does not have a matching enumeration
 *          value in the RvSipDispositionHandling enumeration.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader    - Handle to the Content-Disposition header object.
 *    eHandling  - The handling enumeration to be set in the Content-Type header
 *               object. If RVSIP_DISPOSITIONHANDLING_UNDEFINED is supplied,
 *               the existing handling is removed from the header.
 *    strHandling - The handling string to be set in the Content-Type header.
 *                (relevant when eHandling is RVSIP_DISPOSITIONHANDLING_OTHER).
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipContentDispositionHeaderSetHandling(
                        IN  RvSipContentDispositionHeaderHandle hHeader,
                        IN  RvSipDispositionHandling            eHandling,
                        IN  RvChar                            *strHandling);

/***************************************************************************
 * RvSipContentDispositionHeaderGetOtherParams
 * ------------------------------------------------------------------------
 * General: Copies the other parameters string from the Content-Disposition
 *          header into a given buffer.
 *          Not all the Content-Disposition header parameters have separated
 *          fields in the Content-Disposition header object. Parameters with no
 *          specific fields are refered to as other params. They are kept in
 *          the object in one concatenated string in the form—
 *          ”name=value;name=value...”
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
RVAPI RvStatus RVCALLCONV RvSipContentDispositionHeaderGetOtherParams(
                            IN RvSipContentDispositionHeaderHandle   hHeader,
                            IN RvChar*                              strBuffer,
                            IN RvUint                               bufferLen,
                            OUT RvUint*                             actualLen);

/***************************************************************************
 * RvSipContentDispositionHeaderSetOtherParams
 * ------------------------------------------------------------------------
 * General: Sets the other parameters string in the Content-Disposition header
 *          object.
 *          Not all the Content-Disposition header parameters have separated
 *          fields in the Content-Disposition header object. Parameters with no
 *          specific fields are refered to as other params. They are kept in
 *          the object in one concatenated string in the form—
 *          ”name=value;name=value...”
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader     - Handle to the header object.
 *    otherParams - The other parameters string to be set in the
 *                Content-Disposition header. If NULL is supplied, the existing
 *                other parameters string is removed from the header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipContentDispositionHeaderSetOtherParams(
                          IN   RvSipContentDispositionHeaderHandle  hHeader,
                          IN   RvChar                             *otherParams);

/***************************************************************************
 * RvSipContentDispositionHeaderGetStrBadSyntax
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
 *          implementation if the message contains a bad ContentDisposition header,
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
RVAPI RvStatus RVCALLCONV RvSipContentDispositionHeaderGetStrBadSyntax(
                            IN RvSipContentDispositionHeaderHandle   hHeader,
                            IN RvChar*                              strBuffer,
                            IN RvUint                               bufferLen,
                            OUT RvUint*                             actualLen);

/***************************************************************************
 * RvSipContentDispositionHeaderSetStrBadSyntax
 * ------------------------------------------------------------------------
 * General: Sets a bad-syntax string in the object.
 *          A SIP header has the following grammer:
 *          header-name:header-value. When a header contains a syntax error,
 *          the header-value is kept as a separate "bad-syntax" string.
 *          By using this function you can create a header with "bad-syntax".
 *          Setting a bad syntax string to the header will mark the header as
 *          an invalid syntax header.
 *          You can use his function when you want to send an illegal ContentDisposition header.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *  hHeader      - The handle to the header object.
 *  strBadSyntax - The bad-syntax string.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipContentDispositionHeaderSetStrBadSyntax(
                                  IN RvSipContentDispositionHeaderHandle hHeader,
                                  IN RvChar*                     strBadSyntax);

#endif /*RV_SIP_PRIMITIVES*/

#ifdef __cplusplus
}
#endif

#endif /* RVSIPCONTENTDISPOSITIONHEADER_H */
