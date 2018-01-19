
/*

NOTICE:
This document contains information that is proprietary to RADVision LTD..
No part of this publication may be reproduced in any form whatsoever without
written prior approval by RADVision LTD..

RADVision LTD. reserves the right to revise this publication and make changes
without obligation to notify any person of such revisions or changes.

*/

/******************************************************************************
 *                      RvSipAllowEventsHeader.h                               *
 *                                                                            *
 * The file defines the methods of the Allow-events header object:             *
 * construct, destruct, copy, encode, parse and the ability to access and     *
 * change it's parameters.                                                    *
 *                                                                            *
 *                                                                            *
 *                                                                            *
 *      Author           Date                                                 *
 *     ------           ------------                                          *
 *      Ofra             May 2002                                             *
 ******************************************************************************/

#ifndef RVSIPALLOW_EVENTS_HEADER_H
#define RVSIPALLOW_EVENTS_HEADER_H

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
 * RvSipAllowEventsHeaderStrings
 * ----------------------
 * Defines all Allow-events header object fields that are kept in the 
 * object in string format.
 */
typedef enum
{
    RVSIP_ALLOW_EVENTS_EVENT_PACKAGE,
    RVSIP_ALLOW_EVENTS_EVENT_TEMPLATE,
    RVSIP_ALLOW_EVENTS_BAD_SYNTAX
}RvSipAllowEventsHeaderStringName;

/*-----------------------------------------------------------------------*/
/*                   CONSTRUCTORS AND DESTRUCTORS                        */
/*-----------------------------------------------------------------------*/

/***************************************************************************
 * RvSipAllowEventsHeaderConstructInMsg
 * ------------------------------------------------------------------------
 * General: Constructs an Allow-events header object inside a given message object.
 *          The header is kept in the header list of the message.
 *          You can choose to insert the header either at the head or tail
 *          of the header list.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hSipMsg          - Handle to the message object.
 *         pushHeaderAtHead - Boolean value indicating whether the header should be
 *                            pushed to the head of the list—RV_TRUE—or to the tail—RV_FALSE.
 * output: hHeader          - Handle to the newly constructed Allow-events header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAllowEventsHeaderConstructInMsg(
                                           IN  RvSipMsgHandle          hSipMsg,
                                           IN  RvBool                 pushHeaderAtHead,
                                           OUT RvSipAllowEventsHeaderHandle* hHeader);

/***************************************************************************
 * RvSipAllowEventsHeaderConstruct
 * ------------------------------------------------------------------------
 * General: Constructs and initializes a stand-alone Allow-events header object.
 *          The header is constructed on a given page taken from a specified pool.
 *          The handle to the new header object is returned.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hMsgMgr - Handle of the message manager.
 *         hPool   - Handle to the memory pool that the object will use.
 *         hPage   - Handle to the memory page that the object will use.
 * output: hHeader - Handle to the newly constructed Allow-events header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAllowEventsHeaderConstruct(
                                           IN  RvSipMsgMgrHandle       hMsgMgr,
                                           IN  HRPOOL                  hPool,
                                           IN  HPAGE                   hPage,
                                           OUT RvSipAllowEventsHeaderHandle* hHeader);

/***************************************************************************
 * RvSipAllowEventsHeaderCopy
 * ------------------------------------------------------------------------
 * General: Copies all fields from a source Allow-events header object to a
 *          destination Allow-events header object.
 *          You must construct the destination object before using this function.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hDestination - Handle to the destination Allow-events header object.
 *    hSource      - Handle to the source Allow-events header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAllowEventsHeaderCopy(
                                         INOUT RvSipAllowEventsHeaderHandle hDestination,
                                         IN    RvSipAllowEventsHeaderHandle hSource);

/***************************************************************************
 * RvSipAllowEventsHeaderSetCompactForm
 * ------------------------------------------------------------------------
 * General: Instructs the header to use the compact header name when the
 *          header is encoded.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader  - Handle to the Allow-Events header object.
 *        bIsCompact - specify whether or not to use a compact form
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAllowEventsHeaderSetCompactForm(
                                   IN    RvSipAllowEventsHeaderHandle hHeader,
                                   IN    RvBool                      bIsCompact);

/***************************************************************************
 * RvSipAllowEventsHeaderEncode
 * ------------------------------------------------------------------------
 * General: Encodes an Allow-events header object to a textual Allow-events header.
 *          The textual header is placed on a page taken from a specified pool.
 *          In order to copy the textual header from the page to a consecutive
 *          buffer, use RPOOL_CopyToExternal().
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader  - Handle to the Allow-events header object.
 *        hPool    - Handle to the specified memory pool.
 * output: hPage   - The memory page allocated to contain the encoded header.
 *         length  - The length of the encoded information.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAllowEventsHeaderEncode(
                                          IN    RvSipAllowEventsHeaderHandle hHeader,
                                          IN    HRPOOL                 hPool,
                                          OUT   HPAGE*                 hPage,
                                          OUT   RvUint32*             length);


/***************************************************************************
 * RvSipAllowEventsHeaderParse
 * ------------------------------------------------------------------------
 * General: Parses a SIP textual Allow-events header into an Allow-events header
 *          object. All the textual fields are placed inside the object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader   - A handle to the Allow-events header object.
 *    buffer    - Buffer containing a textual Allow-events header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAllowEventsHeaderParse(
                                     IN RvSipAllowEventsHeaderHandle hHeader,
                                     IN RvChar*               buffer);

/***************************************************************************
 * RvSipAllowEventsHeaderParseValue
 * ------------------------------------------------------------------------
 * General: Parses a SIP textual AllowEvents header value into an AllowEvents
 *          header object.
 *          A SIP header has the following grammer:
 *          header-name:header-value. This function takes the header-value part as
 *          a parameter and parses it into the supplied object.
 *          All the textual fields are placed inside the object.
 *          Note: Use the RvSipAllowEventsHeaderParse() function to parse strings
 *          that also include the header-name.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader   - The handle to the AllowEvents header object.
 *    buffer    - The buffer containing a textual AllowEvents header value.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAllowEventsHeaderParseValue(
                                     IN RvSipAllowEventsHeaderHandle hHeader,
                                     IN RvChar*                     buffer);

/***************************************************************************
 * RvSipAllowEventsHeaderFix
 * ------------------------------------------------------------------------
 * General: Fixes an AllowEvents header with bad-syntax information.
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
RVAPI RvStatus RVCALLCONV RvSipAllowEventsHeaderFix(
                                     IN RvSipAllowEventsHeaderHandle hHeader,
                                     IN RvChar*                     pFixedBuffer);

/*-----------------------------------------------------------------------
                         G E T  A N D  S E T  M E T H O D S
 ------------------------------------------------------------------------*/
/***************************************************************************
 * RvSipAllowEventsHeaderGetStringLength
 * ------------------------------------------------------------------------
 * General: Some of the Allow-Events header fields are kept in a string format.
 *          In order to get such a field from the Allow-events header object, your
 *          application should supply an adequate buffer to where the string will be copied.
 *          This function provides you with the length of the string to enable you to
 *          allocator an appropriate buffer size before calling the Get function.
 * Return Value: Returns the length of the specified string.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader    - Handle to the Allow-Events header object.
 *  stringName - Enumeration of the string name for which you require the length.
 ***************************************************************************/
RVAPI RvUint RVCALLCONV RvSipAllowEventsHeaderGetStringLength(
                                      IN  RvSipAllowEventsHeaderHandle     hHeader,
                                      IN  RvSipAllowEventsHeaderStringName stringName);

/***************************************************************************
 * RvSipAllowEventsHeaderGetRpoolString
 * ------------------------------------------------------------------------
 * General: Copy a string parameter from the Allow-Events header into
 *          a given page from a specified pool. The copied string is not
 *          consecutive.
 * Return Value: RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input: hSipAllowEventsHeader - Handle to the Allow-Events header object.
 *           eStringName   - The string the user wish to get
 *  Input/Output:
 *         pRpoolPtr     - pointer to a location inside an rpool. You need to
 *                         supply only the pool and page. The offset where the
 *                         returned string was located will be returned as an
 *                         output patameter.
 *                         If the function set the returned offset to
 *                         UNDEFINED is means that the parameter was not
 *                         set to the Allow-Events header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAllowEventsHeaderGetRpoolString(
                             IN    RvSipAllowEventsHeaderHandle      hSipAllowEventsHeader,
                             IN    RvSipAllowEventsHeaderStringName  eStringName,
                             INOUT RPOOL_Ptr                         *pRpoolPtr);

/***************************************************************************
 * RvSipAllowEventsHeaderSetRpoolString
 * ------------------------------------------------------------------------
 * General: Sets a string into a specified parameter in the Allow-Events
 *          header object. The given string is located on an RPOOL memory and is
 *          not consecutive.
 * Return Value: RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input: hSipAllowEventsHeader - Handle to the Allow-Events header object.
 *           eStringName   - The string the user wish to set
 *         pRpoolPtr     - pointer to a location inside an rpool where the
 *                         new string is located.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAllowEventsHeaderSetRpoolString(
                             IN    RvSipAllowEventsHeaderHandle      hSipAllowEventsHeader,
                             IN    RvSipAllowEventsHeaderStringName  eStringName,
                             IN    RPOOL_Ptr                         *pRpoolPtr);

/***************************************************************************
 * RvSipAllowEventsHeaderGetEventPackage
 * ------------------------------------------------------------------------
 * General:Copies the event package string from the Allow-Events header object
 *         into a given buffer. If the bufferLen is adequate, the function copies
 *         the requested parameter into strBuffer. Otherwise, the function
 *         returns RV_ERROR_INSUFFICIENT_BUFFER and actualLen contains the required
 *         buffer length.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader    - Handle to the Allow-Events header object.
 *        strBuffer  - Buffer to fill with the requested parameter.
 *        bufferLen  - The length of the buffer.
 * output:actualLen  - The length of the requested parameter, + 1 to include
 *                     a NULL value at the end of the parameter.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAllowEventsHeaderGetEventPackage(
                                               IN  RvSipAllowEventsHeaderHandle hHeader,
                                               IN  RvChar*               strBuffer,
                                               IN  RvUint                bufferLen,
                                               OUT RvUint*               actualLen);

/***************************************************************************
 * RvSipAllowEventsHeaderSetEventPackage
 * ------------------------------------------------------------------------
 * General: Sets the Event package in the Allow-Events header object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader  - Handle to the Allow-Events header object.
 *  strEvent - The event string.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAllowEventsHeaderSetEventPackage(
                                  IN RvSipAllowEventsHeaderHandle hHeader,
                                  IN RvChar*                     strEventPackage);

/***************************************************************************
 * RvSipAllowEventsHeaderGetEventTemplate
 * ------------------------------------------------------------------------
 * General:Copies the event template string from the Allow-Events header object
 *         into a given buffer. If the bufferLen is adequate, the function copies
 *         the requested parameter into strBuffer. Otherwise, the function
 *         returns RV_ERROR_INSUFFICIENT_BUFFER and actualLen contains the required
 *         buffer length.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader    - Handle to the Allow-Events header object.
 *        strBuffer  - Buffer to fill with the requested parameter.
 *        bufferLen  - The length of the buffer.
 * output:actualLen  - The length of the requested parameter, + 1 to include
 *                     a NULL value at the end of the parameter.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAllowEventsHeaderGetEventTemplate(
                                               IN  RvSipAllowEventsHeaderHandle hHeader,
                                               IN  RvChar*               strBuffer,
                                               IN  RvUint                bufferLen,
                                               OUT RvUint*               actualLen);

/***************************************************************************
 * RvSipAllowEventsHeaderSetEventTemplate
 * ------------------------------------------------------------------------
 * General: Sets the Event template in the Allow-Events header object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader  - Handle to the Allow-Events header object.
 *  strEvent - The event string.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAllowEventsHeaderSetEventTemplate(
                                  IN RvSipAllowEventsHeaderHandle hHeader,
                                  IN RvChar*                     strEvent);

/***************************************************************************
 * RvSipAllowEventsHeaderGetStrBadSyntax
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
 *          implementation if the message contains a bad AllowEvents header,
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
RVAPI RvStatus RVCALLCONV RvSipAllowEventsHeaderGetStrBadSyntax(
                                               IN  RvSipAllowEventsHeaderHandle hHeader,
                                               IN  RvChar*               strBuffer,
                                               IN  RvUint                bufferLen,
                                               OUT RvUint*               actualLen);
/***************************************************************************
 * RvSipAllowEventsHeaderSetStrBadSyntax
 * ------------------------------------------------------------------------
 * General: Sets a bad-syntax string in the object.
 *          A SIP header has the following grammer:
 *          header-name:header-value. When a header contains a syntax error,
 *          the header-value is kept as a separate "bad-syntax" string.
 *          By using this function you can create a header with "bad-syntax".
 *          Setting a bad syntax string to the header will mark the header as
 *          an invalid syntax header.
 *          You can use his function when you want to send an illegal AllowEvents header.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader      - The handle to the header object.
 *  strBadSyntax - The bad-syntax string.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAllowEventsHeaderSetStrBadSyntax(
                                  IN RvSipAllowEventsHeaderHandle hHeader,
                                  IN RvChar*                     strBadSyntax);

#endif /*RV_SIP_PRIMITIVES */

#ifdef __cplusplus
}
#endif

#endif /*RVSIPALLOW_EVENTS_HEADER_H*/
