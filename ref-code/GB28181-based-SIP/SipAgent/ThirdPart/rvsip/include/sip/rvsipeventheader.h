
/*

NOTICE:
This document contains information that is proprietary to RADVision LTD..
No part of this publication may be reproduced in any form whatsoever without
written prior approval by RADVision LTD..

RADVision LTD. reserves the right to revise this publication and make changes
without obligation to notify any person of such revisions or changes.

*/

/******************************************************************************
*                     RvSipEventHeader.h                                     *
*                                                                            *
* The file defines the methods of the Event header object:                   *
* construct, destruct, copy, encode, parse and the ability to access and     *
* change it's parameters.                                                    *
*                                                                            *
*                                                                            *
*      Author           Date                                                 *
*     ------           ------------                                          *
*     Ofra Wachsman    May 2002                                              *
******************************************************************************/

#ifndef RVSIPEVENTHEADER_H
#define RVSIPEVENTHEADER_H

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
	* RvSipEventHeaderStringName
	* ----------------------
	* This enum defines all the header's strings (for getting it's size)
	* Defines all Event header object fields that are kept in the object
	* in a string format.
	*/
	typedef enum
	{
		RVSIP_EVENT_PACKAGE,
		RVSIP_EVENT_TEMPLATE,
		RVSIP_EVENT_ID,
		RVSIP_EVENT_PARAM,
		RVSIP_EVENT_BAD_SYNTAX
	}RvSipEventHeaderStringName;

	/****************************************************/
	/*        CONSTRUCTORS AND DESTRUCTORS                */
	/****************************************************/

	/***************************************************************************
	* RvSipEventHeaderConstructInMsg
	* ------------------------------------------------------------------------
	* General: Constructs an Event Header object inside a given message
	*          object. The header is kept in the header list of the message.
	*          You can choose to insert the header either at the head or tail of
	*          the list.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* input:  hSipMsg          - Handle to the message object.
	*         pushHeaderAtHead - Boolean value indicating whether the header should
	*                            be pushed to the head of the list (RV_TRUE),
	*                            or to the tail (RV_FALSE).
	* output: hHeader          - Handle to the newly constructed Event Header object.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipEventHeaderConstructInMsg(
		IN  RvSipMsgHandle          hSipMsg,
		IN  RvBool                 pushHeaderAtHead,
		OUT RvSipEventHeaderHandle* hHeader);

	/***************************************************************************
	* RvSipEventHeaderConstruct
	* ------------------------------------------------------------------------
	* General: Constructs and initializes a stand-alone Event Header object.
	*          The header is constructed on a given page taken from a specified
	*          pool. The handle to the new header object is returned.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* input:  hMsgMgr - Handle to the Message manager.
	*         hPool   - Handle to the memory pool that the object will use.
	*         hPage   - Handle to the memory page that the object will use.
	* output: hHeader - Handle to the newly constructed Event Header object.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipEventHeaderConstruct(
		IN  RvSipMsgMgrHandle       hMsgMgr,
		IN  HRPOOL                  hPool,
		IN  HPAGE                   hPage,
		OUT RvSipEventHeaderHandle* hHeader);

	/***************************************************************************
	* RvSipEventHeaderCopy
	* ------------------------------------------------------------------------
	* General: Copies all fields from a source Event Header object to a
	*          destination Event Header object.
	*          You must construct the destination object before using this function.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hDestination - Handle to the destination Event Header object.
	*    hSource      - Handle to the source Event Header object.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipEventHeaderCopy(
		INOUT  RvSipEventHeaderHandle hDestination,
		IN     RvSipEventHeaderHandle hSource);

	/***************************************************************************
	* RvSipEventHeaderSetCompactForm
	* ------------------------------------------------------------------------
	* General: Instructs the header to use the compact header name when the
	*          header is encoded.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* input: hHeader    - Handle to the Event header object.
	*        bIsCompact - specify whether or not to use a compact form
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipEventHeaderSetCompactForm(
		IN    RvSipEventHeaderHandle hHeader,
		IN    RvBool                bIsCompact);

	/***************************************************************************
	* RvSipEventHeaderEncode
	* ------------------------------------------------------------------------
	* General: Encodes an Event Header object to a textual Event header.
	*          The textual header is placed on a page taken from a specified pool.
	*          In order to copy the textual header from the page to a consecutive
	*          buffer, use RPOOL_CopyToExternal().
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* input: hHeader  - Handle to the Event Header object.
	*        hPool    - Handle to the specified memory pool.
	* output: hPage   - The memory page allocated to contain the encoded header.
	*         length  - The length of the encoded information.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipEventHeaderEncode(
		IN    RvSipEventHeaderHandle hHeader,
		IN    HRPOOL                 hPool,
		OUT   HPAGE*                 hPage,
		OUT   RvUint32*             length);

	/***************************************************************************
	* RvSipEventHeaderParse
	* ------------------------------------------------------------------------
	* General:Parses a SIP textual Event Header—for example,
	*         "Event : event-package.event-template;id=5;event-param=param-val??
	*          into an Event Header object.
	*         All the textual fields are placed inside the object.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader   - A handle to the Event Header object.
	*    buffer    - Buffer containing a textual Event Header.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipEventHeaderParse(
		IN  RvSipEventHeaderHandle  hHeader,
		IN  RvChar*                buffer);

	/***************************************************************************
	* RvSipEventHeaderParseValue
	* ------------------------------------------------------------------------
	* General: Parses a SIP textual Event header value into an Event header object.
	*          A SIP header has the following grammer:
	*          header-name:header-value. This function takes the header-value part as
	*          a parameter and parses it into the supplied object.
	*          All the textual fields are placed inside the object.
	*          Note: Use the RvSipEventHeaderParse() function to parse strings that also
	*          include the header-name.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader   - The handle to the Event header object.
	*    buffer    - The buffer containing a textual Event header value.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipEventHeaderParseValue(
		IN  RvSipEventHeaderHandle  hHeader,
		IN  RvChar*                buffer);

	/***************************************************************************
	* RvSipEventHeaderFix
	* ------------------------------------------------------------------------
	* General: Fixes an Event header with bad-syntax information.
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
	RVAPI RvStatus RVCALLCONV RvSipEventHeaderFix(
		IN RvSipEventHeaderHandle hHeader,
		IN RvChar*               pFixedBuffer);

	/***************************************************************************
	* RvSipEventHeaderIsEqual
	* ------------------------------------------------------------------------
	* General:Compares two event header objects.
	*         event headers considered equal if the event-type and event id parameter,
	*         are equal.
	*         The event-type portion of the "Event" header is compared byte-by-byte,
	*         and the "id" parameter token (if present) is compared byte-by-byte.
	*         An "Event" header containing an "id" parameter never matches an "Event"
	*         header without an "id" parameter.
	*         No other parameters are considered when performing a comparison.
	* Return Value: Returns RV_TRUE if the party header objects being compared are equal.
	*               Otherwise, the function returns RV_FALSE.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader      - A handle to the Event Header object.
	*    hOtherHeader - Handle to the Event header object with which a comparison is being made.
	***************************************************************************/
	RVAPI RvBool RVCALLCONV RvSipEventHeaderIsEqual(
		IN  const RvSipEventHeaderHandle  hHeader,
		IN  const RvSipEventHeaderHandle  hOtherHeader);

	/*-----------------------------------------------------------------------
	G E T  A N D  S E T  M E T H O D S
	------------------------------------------------------------------------*/

	/***************************************************************************
	* RvSipEventHeaderGetStringLength
	* ------------------------------------------------------------------------
	* General: Some of the Event Header fields are kept in a string format,
	*          for example, the Event Header other params. In order to get
	*          such a field from the Event Header object, your application
	*          should supply an adequate buffer to where the string
	*          will be copied.
	*          This function provides you with the length of the string to
	*          enable you to allocate an appropriate buffer size before calling
	*          the Get function.
	* Return Value: Returns the length of the specified string.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader    - Handle to the Event Header object.
	*  stringName - Enumeration of the string name for which you require the
	*               length.
	***************************************************************************/
	RVAPI RvUint RVCALLCONV RvSipEventHeaderGetStringLength(
		IN  RvSipEventHeaderHandle     hHeader,
		IN  RvSipEventHeaderStringName stringName);

	/***************************************************************************
	* RvSipEventHeaderGetRpoolString
	* ------------------------------------------------------------------------
	* General: Copy a string parameter from the Event header into a given page
	*          from a specified pool. The copied string is not consecutive.
	* Return Value: RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    Input: hSipEventHeader - Handle to the Event header object.
	*           eStringName   - The string the user wish to get
	*  Input/Output:
	*         pRpoolPtr     - pointer to a location inside an rpool. You need to
	*                         supply only the pool and page. The offset where the
	*                         returned string was located will be returned as an
	*                         output patameter.
	*                         If the function set the returned offset to
	*                         UNDEFINED is means that the parameter was not
	*                         set to the Via header object.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipEventHeaderGetRpoolString(
		IN    RvSipEventHeaderHandle      hSipEventHeader,
		IN    RvSipEventHeaderStringName  eStringName,
		INOUT RPOOL_Ptr                   *pRpoolPtr);

	/***************************************************************************
	* RvSipEventHeaderSetRpoolString
	* ------------------------------------------------------------------------
	* General: Sets a string into a specified parameter in the Event header
	*          object. The given string is located on an RPOOL memory and is
	*          not consecutive.
	* Return Value: RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    Input: hSipEventHeader - Handle to the Event header object.
	*           eStringName   - The string the user wish to set
	*         pRpoolPtr     - pointer to a location inside an rpool where the
	*                         new string is located.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipEventHeaderSetRpoolString(
		IN    RvSipEventHeaderHandle      hSipEventHeader,
		IN    RvSipEventHeaderStringName  eStringName,
		IN    RPOOL_Ptr                   *pRpoolPtr);

	/***************************************************************************
	* RvSipEventHeaderGetEventPackage
	* ------------------------------------------------------------------------
	* General: Copies the event-package string from the Event Header into
	*          a given buffer.
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
	RVAPI RvStatus RVCALLCONV RvSipEventHeaderGetEventPackage(
		IN RvSipEventHeaderHandle   hHeader,
		IN RvChar*                 strBuffer,
		IN RvUint                  bufferLen,
		OUT RvUint*                actualLen);

	/***************************************************************************
	* RvSipEventHeaderSetEventPackage
	* ------------------------------------------------------------------------
	* General: Sets the event-package field in the Event Header object.
	*
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader    - Handle to the Event Header object.
	*    strPackage - The event-package string to be set in the Event Header.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipEventHeaderSetEventPackage(
		IN  RvSipEventHeaderHandle hHeader,
		IN  RvChar                *strPackage);

	/***************************************************************************
	* RvSipEventHeaderGetEventTemplate
	* ------------------------------------------------------------------------
	* General: Copies the event-template string from the Event Header into
	*          a given buffer.
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
	RVAPI RvStatus RVCALLCONV RvSipEventHeaderGetEventTemplate(
		IN RvSipEventHeaderHandle   hHeader,
		IN RvChar*                 strBuffer,
		IN RvUint                  bufferLen,
		OUT RvUint*                actualLen);

	/***************************************************************************
	* RvSipEventHeaderSetEventTemplate
	* ------------------------------------------------------------------------
	* General: Sets the event-template field in the Event Header object.
	*
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader    - Handle to the Event Header object.
	*    strPackage - The event-template string to be set in the Event Header.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipEventHeaderSetEventTemplate(
		IN  RvSipEventHeaderHandle hHeader,
		IN  RvChar                *strTemplate);

	/***************************************************************************
	* RvSipEventHeaderGetEventParam
	* ------------------------------------------------------------------------
	* General: Copies the event-param string from the Event Header into
	*          a given buffer.
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
	RVAPI RvStatus RVCALLCONV RvSipEventHeaderGetEventParam(
		IN RvSipEventHeaderHandle   hHeader,
		IN RvChar*                 strBuffer,
		IN RvUint                  bufferLen,
		OUT RvUint*                actualLen);

	/***************************************************************************
	* RvSipEventHeaderSetEventParam
	* ------------------------------------------------------------------------
	* General: Sets the event-param field in the Event Header object.
	*
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader    - Handle to the Event Header object.
	*    strEventParam - The event-param string to be set in the Event Header.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipEventHeaderSetEventParam(
		IN  RvSipEventHeaderHandle hHeader,
		IN  RvChar                *strEventParam);

	/***************************************************************************
	* RvSipEventHeaderGetEventId
	* ------------------------------------------------------------------------
	* General: Copies the event-id string from the Event Header into
	*          a given buffer.
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
	RVAPI RvStatus RVCALLCONV RvSipEventHeaderGetEventId(
		IN RvSipEventHeaderHandle   hHeader,
		IN RvChar*                 strBuffer,
		IN RvUint                  bufferLen,
		OUT RvUint*                actualLen);

	/***************************************************************************
	* RvSipEventHeaderSetEventId
	* ------------------------------------------------------------------------
	* General: Sets the event-id field in the Event Header object.
	*
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader    - Handle to the Event Header object.
	*    strId      - The event-id string to be set in the Event Header.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipEventHeaderSetEventId(
		IN  RvSipEventHeaderHandle hHeader,
		IN  RvChar                *strId);

	/***************************************************************************
	* RvSipEventHeaderGetStrBadSyntax
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
	*          implementation if the message contains a bad Event header,
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
	RVAPI RvStatus RVCALLCONV RvSipEventHeaderGetStrBadSyntax(
		IN RvSipEventHeaderHandle   hHeader,
		IN RvChar*                 strBuffer,
		IN RvUint                  bufferLen,
		OUT RvUint*                actualLen);

	/***************************************************************************
	* RvSipEventHeaderSetStrBadSyntax
	* ------------------------------------------------------------------------
	* General: Sets a bad-syntax string in the object.
	*          A SIP header has the following grammer:
	*          header-name:header-value. When a header contains a syntax error,
	*          the header-value is kept as a separate "bad-syntax" string.
	*          By using this function you can create a header with "bad-syntax".
	*          Setting a bad syntax string to the header will mark the header as
	*          an invalid syntax header.
	*          You can use his function when you want to send an illegal Event header.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader      - The handle to the header object.
	*  strBadSyntax - The bad-syntax string.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipEventHeaderSetStrBadSyntax(
		IN RvSipEventHeaderHandle hHeader,
		IN RvChar*                     strBadSyntax);

#endif /*#ifndef RV_SIP_PRIMITIVES*/

#ifdef __cplusplus
}
#endif

#endif /* RVSIPEVENTHEADER_H */

