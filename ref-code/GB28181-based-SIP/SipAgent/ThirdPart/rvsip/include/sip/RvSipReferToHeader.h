
/*

NOTICE:
This document contains information that is proprietary to RADVision LTD..
No part of this publication may be reproduced in any form whatsoever without
written prior approval by RADVision LTD..

RADVision LTD. reserves the right to revise this publication and make changes
without obligation to notify any person of such revisions or changes.

*/

/******************************************************************************
 *                     RvSipReferToHeader.h                                   *
 *                                                                            *
 * The file defines the methods of the Refer-To header object:                *
 * construct, destruct, copy, encode, parse and the ability to access and     *
 * change it's parameters.                                                    *
 *                                                                            *
 *                                                                            *
 *      Author           Date                                                 *
 *     ------           ------------                                          *
 *     Tamar Barzuza    Apr.2001                                             *
 ******************************************************************************/

#ifndef RVSIPREFERTOHEADER_H
#define RVSIPREFERTOHEADER_H

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                           */
/*-----------------------------------------------------------------------*/
#include "RV_SIP_DEF.h"
#ifndef RV_SIP_PRIMITIVES

#include "RvSipReplacesHeader.h"
#include "RvSipMsgTypes.h"
#include "rpool_API.h"


/*-----------------------------------------------------------------------*/
/*                   DECLERATIONS                                        */
/*-----------------------------------------------------------------------*/
/*
 * RvSipReferToHeaderStringName
 * ----------------------
 * This enum defines all the header's strings (for getting it's size)
 * Defines all Refer-To header object fields that are kept in the 
 * object in string format.
 */
typedef enum
{
    RVSIP_REFER_TO_DISPLAY_NAME,
    RVSIP_REFER_TO_OTHER_PARAMS,
    RVSIP_REFER_TO_BAD_SYNTAX

}RvSipReferToHeaderStringName;

/****************************************************/
/*        CONSTRUCTORS AND DESTRUCTORS                */
/****************************************************/

/***************************************************************************
 * RvSipReferToHeaderConstructInMsg
 * ------------------------------------------------------------------------
 * General: Constructs a Refer-To header object inside a given message object.
 *          The header is kept in the header list of the message.
 *          You can choose to insert the header either at the head or tail of
 *          the list.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hSipMsg          - Handle to the message object.
 *         pushHeaderAtHead - Boolean value indicating whether the header should be pushed to the head of the
 *                            list—RV_TRUE—or to the tail—RV_FALSE.
 * output: hHeader          - Handle to the newly constructed Refer-To header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipReferToHeaderConstructInMsg(
                                       IN  RvSipMsgHandle            hSipMsg,
                                       IN  RvBool                   pushHeaderAtHead,
                                       OUT RvSipReferToHeaderHandle* hHeader);

/***************************************************************************
 * RvSipReferToHeaderConstruct
 * ------------------------------------------------------------------------
 * General: Constructs and initializes a stand-alone Refer-To Header object.
 *          The header is constructed on a given page taken from a specified
 *          pool. The handle to the new header object is returned.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hMsgMgr - Handle to the Message manager.
 *         hPool   - Handle to the memory pool that the object will use.
 *         hPage   - Handle to the memory page that the object will use.
 * output: hHeader - Handle to the newly constructed Refer-To header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipReferToHeaderConstruct(
                                        IN  RvSipMsgMgrHandle         hMsgMgr,
                                        IN  HRPOOL                    hPool,
                                        IN  HPAGE                     hPage,
                                        OUT RvSipReferToHeaderHandle* hHeader);

/***************************************************************************
 * RvSipReferToHeaderCopy
 * ------------------------------------------------------------------------
 * General: Copies all fields from a source Refer-To header object to a
 *          destination Refer-To header object.
 *          You must construct the destination object before using this function.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hDestination - Handle to the destination Refer-To header object.
 *    hSource      - Handle to the source Refer-To header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipReferToHeaderCopy(
                                    INOUT  RvSipReferToHeaderHandle hDestination,
                                    IN     RvSipReferToHeaderHandle hSource);
/***************************************************************************
 * RvSipReferToHeaderSetCompactForm
 * ------------------------------------------------------------------------
 * General: Instructs the header to use the compact header name when the
 *          header is encoded.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader  - Handle to the ReferTo header object.
 *        bIsCompact - specify whether or not to use a compact form
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipReferToHeaderSetCompactForm(
                                   IN    RvSipReferToHeaderHandle hHeader,
                                   IN    RvBool                bIsCompact);

/***************************************************************************
 * RvSipReferToHeaderEncode
 * ------------------------------------------------------------------------
 * General: Encodes a Refer-To header object to a textual Refer-To header.
 *          The textual header is placed on a page taken from a specified pool.
 *          In order to copy the textual header
 *          from the page to a consecutive buffer, use RPOOL_CopyToExternal().
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader  - Handle to the Refer-To header object.
 *        hPool    - Handle to the specified memory pool.
 * output: hPage   - The memory page allocated to contain the encoded header.
 *         length  - The length of the encoded information.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipReferToHeaderEncode(
                                        IN    RvSipReferToHeaderHandle hHeader,
                                        IN    HRPOOL                   hPool,
                                        OUT   HPAGE*                   hPage,
                                        OUT   RvUint32*               length);

/***************************************************************************
 * RvSipReferToHeaderParse
 * ------------------------------------------------------------------------
 * General:Parses a SIP textual Refer-To header—for example,
 *         "Refer-To: <sip:charlie@caller.com>”—into a Refer-To header object.
 *         All the textual fields are placed inside the object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader   - A handle to the Refer-To header object.
 *    buffer    - Buffer containing a textual Refer-To header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipReferToHeaderParse(
                                     IN  RvSipReferToHeaderHandle  hHeader,
                                     IN  RvChar*                  buffer);

/***************************************************************************
 * RvSipReferToHeaderParseValue
 * ------------------------------------------------------------------------
 * General: Parses a SIP textual ReferTo header value into an ReferTo header object.
 *          A SIP header has the following grammer:
 *          header-name:header-value. This function takes the header-value part as
 *          a parameter and parses it into the supplied object.
 *          All the textual fields are placed inside the object.
 *          Note: Use the RvSipReferToHeaderParse() function to parse strings that also
 *          include the header-name.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader   - The handle to the ReferTo header object.
 *    buffer    - The buffer containing a textual ReferTo header value.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipReferToHeaderParseValue(
                                     IN  RvSipReferToHeaderHandle  hHeader,
                                     IN  RvChar*                  buffer);

/***************************************************************************
 * RvSipReferToHeaderFix
 * ------------------------------------------------------------------------
 * General: Fixes an ReferTo header with bad-syntax information.
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
RVAPI RvStatus RVCALLCONV RvSipReferToHeaderFix(
                                     IN RvSipReferToHeaderHandle hHeader,
                                     IN RvChar*                 pFixedBuffer);

/***************************************************************************
 * RvSipReferToHeaderGetStringLength
 * ------------------------------------------------------------------------
 * General: Some of the Refer-To header fields are kept in a string format—
 *          for example, the Refer-To header display name. In order to get
 *          such a field from the Refer-To header object, your application
 *          should supply an adequate buffer to where the string
 *          will be copied.
 *          This function provides you with the length of the string to
 *          enable you to allocate an appropriate buffer size before calling
 *          the Get function.
 * Return Value: Returns the length of the specified string.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader    - Handle to the Refer-To header object.
 *  stringName - Enumeration of the string name for which you require the
 *               length.
 ***************************************************************************/
RVAPI RvUint RVCALLCONV RvSipReferToHeaderGetStringLength(
                                IN  RvSipReferToHeaderHandle     hHeader,
                                IN  RvSipReferToHeaderStringName stringName);

/***************************************************************************
 * RvSipReferToHeaderGetAddrSpec
 * ------------------------------------------------------------------------
 * General: The Address Spec field is held in the Refer-To header object as
 *          an Address object.
 *          This function returns the handle to the Address object.
 * Return Value: Returns a handle to the Address Spec object, or NULL if the Address Spec
 *               object does not exist.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader - Handle to the Refer-To header object.
 ***************************************************************************/
RVAPI RvSipAddressHandle RVCALLCONV RvSipReferToHeaderGetAddrSpec(
                                            IN RvSipReferToHeaderHandle hHeader);

/***************************************************************************
 * RvSipReferToHeaderSetAddrSpec
 * ------------------------------------------------------------------------
 * General: Sets the Address Spec address object in the Refer-To header object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader   - Handle to the Refer-To header object.
 *  hAddrSpec - Handle to the Address Spec address object to be set in the
 *              Refer-To header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipReferToHeaderSetAddrSpec(
                                         IN  RvSipReferToHeaderHandle hHeader,
                                         IN  RvSipAddressHandle       hAddrSpec);

/***************************************************************************
 * RvSipReferToHeaderGetDisplayName
 * ------------------------------------------------------------------------
 * General: Copies the display name from the Refer-To header into a given buffer.
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
 * output:actualLen - The length of the requested parameter, + 1 to include a
 *                    NULL value at the end of the parameter.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipReferToHeaderGetDisplayName(
                                              IN RvSipReferToHeaderHandle hHeader,
                                              IN RvChar*                 strBuffer,
                                              IN RvUint                  bufferLen,
                                              OUT RvUint*                actualLen);

/***************************************************************************
 * RvSipReferToHeaderSetDisplayName
 * ------------------------------------------------------------------------
 * General: Sets the display name in the ReferTo header object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader        - Handle to the header object.
 *    strDisplayName - The display name to be set in the Refer-To header. If NULL
 *                   is supplied, the existing display name is removed from the
 *                   header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipReferToHeaderSetDisplayName(
                                         IN    RvSipReferToHeaderHandle hHeader,
                                         IN    RvChar *                strDisplayName);

/***************************************************************************
 * RvSipReferToHeaderGetReplacesHeader
 * ------------------------------------------------------------------------
 * General: Gets the replaces header from the Refer-To header object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input:  hHeader            - Handle to the Refer-To header object.
 *  Output: hReplacesHeader - Pointer to the handle of the returned Replaces header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipReferToHeaderGetReplacesHeader(
                                          IN  RvSipReferToHeaderHandle   hHeader,
                                          OUT RvSipReplacesHeaderHandle *hReplacesHeader);

/***************************************************************************
 * RvSipReferToHeaderSetReplacesHeader
 * ------------------------------------------------------------------------
 * General: Sets the replaces header in the Refer-To header object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader            - Handle to the Refer-To header object.
 *  hReplacesHeader - Handle to the Replaces header to be set in the
 *                      Refer-To header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipReferToHeaderSetReplacesHeader(
                                         IN  RvSipReferToHeaderHandle  hHeader,
                                         IN  RvSipReplacesHeaderHandle hReplacesHeader);

/***************************************************************************
 * RvSipReferToHeaderGetOtherParams
 * ------------------------------------------------------------------------
 * General: Copies the other params field of the ReferTo header
 *          object into a given buffer.
 *          generic-parameters of refer-to header are refered to as other params.
 *          It is kept in the object in one concatenated string in the form —
 *          ”name=value;name=value...”
 *          If the bufferLen is adequate, the function copies the requested
 *          parameter into strBuffer.
 *          Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and actualLen
 *          contains the required buffer length.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader    - Handle to the ReferTo header object.
 *        strBuffer  - Buffer to fill with the requested parameter.
 *        bufferLen  - The length of the buffer.
 * output:actualLen  - The length of the requested parameter, + 1 to include a
 *                     NULL value at the end of the parameter.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipReferToHeaderGetOtherParams(
                                               IN RvSipReferToHeaderHandle   hHeader,
                                               IN RvChar*                 strBuffer,
                                               IN RvUint                  bufferLen,
                                               OUT RvUint*                actualLen);

/***************************************************************************
 * RvSipReferToHeaderSetOtherParams
 * ------------------------------------------------------------------------
 * General: Sets the other params field in the ReferTo header object.
 *          generic-parameters of refer-to header are refered to as other params.
 *          It is kept in the object in one concatenated string in the form —
 *          ”name=value;name=value...”
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader        - Handle to the ReferTo header object.
 *    strOtherParams - The Other Params string to be set in the ReferTo header.
 *                   If NULL is supplied, the existing Other Params field is
 *                   removed from the header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipReferToHeaderSetOtherParams(
                                     IN    RvSipReferToHeaderHandle hHeader,
                                     IN    RvChar *              strOtherParams);
/***************************************************************************
 * RvSipReferToHeaderGetStrBadSyntax
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
 *          implementation if the message contains a bad ReferTo header,
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
RVAPI RvStatus RVCALLCONV RvSipReferToHeaderGetStrBadSyntax(
                                               IN RvSipReferToHeaderHandle hHeader,
                                               IN RvChar*                 strBuffer,
                                               IN RvUint                  bufferLen,
                                               OUT RvUint*                actualLen);

/***************************************************************************
 * RvSipReferToHeaderSetStrBadSyntax
 * ------------------------------------------------------------------------
 * General: Sets a bad-syntax string in the object.
 *          A SIP header has the following grammer:
 *          header-name:header-value. When a header contains a syntax error,
 *          the header-value is kept as a separate "bad-syntax" string.
 *          By using this function you can create a header with "bad-syntax".
 *          Setting a bad syntax string to the header will mark the header as
 *          an invalid syntax header.
 *          You can use his function when you want to send an illegal ReferTo header.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader      - The handle to the header object.
 *  strBadSyntax - The bad-syntax string.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipReferToHeaderSetStrBadSyntax(
                                  IN RvSipReferToHeaderHandle hHeader,
                                  IN RvChar*                     strBadSyntax);


#endif /*#ifndef RV_SIP_PRIMITIVES*/

#ifdef __cplusplus
}
#endif

#endif /* RVSIPREFERTOHEADER_H */

