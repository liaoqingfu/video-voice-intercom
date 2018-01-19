
/*

NOTICE:
This document contains information that is proprietary to RADVision LTD..
No part of this publication may be reproduced in any form whatsoever without
written prior approval by RADVision LTD..

RADVision LTD. reserves the right to revise this publication and make changes
without obligation to notify any person of such revisions or changes.

*/

/******************************************************************************
 *                           RvSipAllowHeader.h                               *
 *                                                                            *
 * The file defines the methods of the Allow header object:                   *
 * construct, destruct, copy, encode, parse and the ability to access and     *
 * change it's parameters.                                                    *
 *                                                                            *
 *                                                                            *
 *                                                                            *
 *      Author           Date                                                 *
 *     ------           ------------                                          *
 *      Ofra             Nov.2000                                             *
 ******************************************************************************/

#ifndef RVSIPALLOWHEADER_H
#define RVSIPALLOWHEADER_H

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
 * RvSipAllowHeaderStrings
 * ----------------------
 * Defines all Allow header object fields that are kept in the object 
 * in a string format.
 */
typedef enum
{
    RVSIP_ALLOW_METHOD,
    RVSIP_ALLOW_BAD_SYNTAX
}RvSipAllowHeaderStringName;

/*-----------------------------------------------------------------------*/
/*                   CONSTRUCTORS AND DESTRUCTORS                        */
/*-----------------------------------------------------------------------*/

/***************************************************************************
 * RvSipAllowHeaderConstructInMsg
 * ------------------------------------------------------------------------
 * General: Constructs an Allow Header object inside a given message object.
 *          The header is kept in the header list of the message.
 *          You can choose to insert the header either at the head or tail of the header list.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hSipMsg          - Handle to the message object.
 *         pushHeaderAtHead - Boolean value indicating whether the header should be
 *                            pushed to the head of the list—RV_TRUE—or to the tail—RV_FALSE.
 * output: hHeader          - Handle to the newly constructed Allow header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAllowHeaderConstructInMsg(
                                           IN  RvSipMsgHandle          hSipMsg,
                                           IN  RvBool                 pushHeaderAtHead,
                                           OUT RvSipAllowHeaderHandle* hHeader);

/***************************************************************************
 * RvSipAllowHeaderConstruct
 * ------------------------------------------------------------------------
 * General: Constructs and initializes a stand-alone Allow Header object. The header is
 *          constructed on a given page taken from a specified pool. The handle to the new
 *          header object is returned.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hMsgMgr - Handle of the message manager.
 *         hPool   - Handle to the memory pool that the object will use.
 *         hPage   - Handle to the memory page that the object will use.
 * output: hHeader - Handle to the newly constructed Allow header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAllowHeaderConstruct(
                                           IN  RvSipMsgMgrHandle       hMsgMgr,
                                           IN  HRPOOL                  hPool,
                                           IN  HPAGE                   hPage,
                                           OUT RvSipAllowHeaderHandle* hHeader);

/***************************************************************************
 * RvSipAllowHeaderCopy
 * ------------------------------------------------------------------------
 * General: Copies all fields from a source Allow header object to a destination Allow
 *          header object.
 *          You must construct the destination object before using this function.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hDestination - Handle to the destination Allow header object.
 *    hSource      - Handle to the source Allow header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAllowHeaderCopy
                                        (INOUT RvSipAllowHeaderHandle hDestination,
                                         IN    RvSipAllowHeaderHandle hSource);


/***************************************************************************
 * RvSipAllowHeaderEncode
 * ------------------------------------------------------------------------
 * General: Encodes an Allow header object to a textual Allow header.
 *          The textual header is placed on a page taken from a specified pool.
 *          In order to copy the textual header from the page to a
 *          consecutive buffer, use RPOOL_CopyToExternal().
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader  - Handle to the Allow header object.
 *        hPool    - Handle to the specified memory pool.
 * output: hPage   - The memory page allocated to contain the encoded header.
 *         length  - The length of the encoded information.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAllowHeaderEncode(
                                          IN    RvSipAllowHeaderHandle hHeader,
                                          IN    HRPOOL                 hPool,
                                          OUT   HPAGE*                 hPage,
                                          OUT   RvUint32*             length);


/***************************************************************************
 * RvSipAllowHeaderParse
 * ------------------------------------------------------------------------
 * General: Parses a SIP textual Allow header into an Allow header object.
 *          All the textual fields are placed inside the object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader   - A handle to the Allow header object.
 *    buffer    - Buffer containing a textual Allow header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAllowHeaderParse(
                                     IN RvSipAllowHeaderHandle hHeader,
                                     IN RvChar*               buffer);

/***************************************************************************
 * RvSipAllowHeaderParseValue
 * ------------------------------------------------------------------------
 * General: Parses a SIP textual Allow header value into an Allow header object.
 *          A SIP header has the following grammer:
 *          header-name:header-value. This function takes the header-value part as
 *          a parameter and parses it into the supplied object.
 *          All the textual fields are placed inside the object.
 *          Note: Use the RvSipAllowHeaderParse() function to parse strings that also
 *          include the header-name.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader   - The handle to the Allow header object.
 *    buffer    - The buffer containing a textual Allow header value.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAllowHeaderParseValue(
                                     IN RvSipAllowHeaderHandle hHeader,
                                     IN RvChar*               buffer);

/***************************************************************************
 * RvSipAllowHeaderFix
 * ------------------------------------------------------------------------
 * General: Fixes an Allow header with bad-syntax information.
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
RVAPI RvStatus RVCALLCONV RvSipAllowHeaderFix(
                                     IN RvSipAllowHeaderHandle hHeader,
                                     IN RvChar*               pFixedBuffer);

/*-----------------------------------------------------------------------
                         G E T  A N D  S E T  M E T H O D S
 ------------------------------------------------------------------------*/
/***************************************************************************
 * RvSipAllowHeaderGetStringLength
 * ------------------------------------------------------------------------
 * General: Some of the Allow header fields are kept in a string format—for example, the
 *          method string. In order to get such a field from the Allow header object, your
 *          application should supply an adequate buffer to where the string will be copied.
 *          This function provides you with the length of the string to enable you to
 *          allocator an appropriate buffer size before calling the Get function.
 * Return Value: Returns the length of the specified string.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader    - Handle to the Allow header object.
 *  stringName - Enumeration of the string name for which you require the length.
 ***************************************************************************/
RVAPI RvUint RVCALLCONV RvSipAllowHeaderGetStringLength(
                                      IN  RvSipAllowHeaderHandle     hHeader,
                                      IN  RvSipAllowHeaderStringName stringName);

/***************************************************************************
 * RvSipAllowHeaderGetMethodType
 * ------------------------------------------------------------------------
 * General: Gets the method type enumeration from the Allow header object.
 * Return Value: Returns the method type enumeration from the header object.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader - Handle to the Allow header object.
 ***************************************************************************/
RVAPI RvSipMethodType RVCALLCONV RvSipAllowHeaderGetMethodType(
                                      IN  RvSipAllowHeaderHandle hHeader);

/***************************************************************************
 * RvSipAllowHeaderGetStrMethodType
 * ------------------------------------------------------------------------
 * General:Copies the method type string from the Allow header object into a given buffer.
 *         Use this function if RvSipAllowHeaderGetMethodType() returns
 *         RVSIP_METHOD_OTHER.
 *         If the bufferLen is adequate, the function copies the requested parameter into
 *         strBuffer. Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and actualLen
 *         contains the required buffer length.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader    - Handle to the Allow header object.
 *        strBuffer  - Buffer to fill with the requested parameter.
 *        bufferLen  - The length of the buffer.
 * output:actualLen - The length of the requested parameter, + 1 to include a NULL value at the end of
 *                     the parameter.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAllowHeaderGetStrMethodType(
                                               IN  RvSipAllowHeaderHandle hHeader,
                                               IN  RvChar*               strBuffer,
                                               IN  RvUint                bufferLen,
                                               OUT RvUint*               actualLen);

/***************************************************************************
 * RvSipAllowHeaderSetMethodType
 * ------------------------------------------------------------------------
 * General: Sets the method type in the Allow header object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader       - Handle to the Allow header object.
 *  eMethodType   - The method type to be set in the object.
 *    strMethodType - You can use this parameter only if the eMethodType parameter is set to
 *                  RVSIP_METHOD_OTHER. In this case, you can supply the method as a string.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAllowHeaderSetMethodType(
                                          IN    RvSipAllowHeaderHandle hHeader,
                                          IN    RvSipMethodType        eMethodType,
                                          IN    RvChar*               strMethodType);


/***************************************************************************
 * RvSipAllowHeaderGetStrBadSyntax
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
 *          implementation if the message contains a bad Allow header,
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
RVAPI RvStatus RVCALLCONV RvSipAllowHeaderGetStrBadSyntax(
                                               IN  RvSipAllowHeaderHandle hHeader,
                                               IN  RvChar*               strBuffer,
                                               IN  RvUint                bufferLen,
                                               OUT RvUint*               actualLen);


/***************************************************************************
 * RvSipAllowHeaderSetStrBadSyntax
 * ------------------------------------------------------------------------
 * General: Sets a bad-syntax string in the object.
 *          A SIP header has the following grammer:
 *          header-name:header-value. When a header contains a syntax error,
 *          the header-value is kept as a separate "bad-syntax" string.
 *          By using this function you can create a header with "bad-syntax".
 *          Setting a bad syntax string to the header will mark the header as
 *          an invalid syntax header.
 *          You can use his function when you want to send an illegal Allow header.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader      - The handle to the header object.
 *  strBadSyntax - The bad-syntax string.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAllowHeaderSetStrBadSyntax(
                                  IN RvSipAllowHeaderHandle hHeader,
                                  IN RvChar*               strBadSyntax);

#endif /*RV_SIP_PRIMITIVES */

#ifdef __cplusplus
}
#endif

#endif /*RVSIPALLOWHEADER_H*/
