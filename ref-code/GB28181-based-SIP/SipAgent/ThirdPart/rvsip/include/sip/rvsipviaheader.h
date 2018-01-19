/*

NOTICE:
This document contains information that is proprietary to RADVision LTD..
No part of this publication may be reproduced in any form whatsoever without
written prior approval by RADVision LTD..

RADVision LTD. reserves the right to revise this publication and make changes
without obligation to notify any person of such revisions or changes.

*/

/******************************************************************************
*                   RvSipViaHeader.h                                         *
*                                                                            *
* The file defines the methods of the Via header object.                     *
* The Via header functions enable you to construct, copy, encode, parse,     *
* Via header objects and access Via header object parameters.                *                                                                            *
*      Author           Date                                                 *
*     ------           ------------                                          *
*      Ofra             Nov.2000                                             *
******************************************************************************/

#ifndef RVSIPVIAHEADER_H
#define RVSIPVIAHEADER_H

#ifdef __cplusplus
extern "C" {
#endif

	/*-----------------------------------------------------------------------*/
	/*                        INCLUDE HEADER FILES                           */
	/*-----------------------------------------------------------------------*/
#include "RV_SIP_DEF.h"
#include "RvSipMsgTypes.h"
#include "rpool_API.h"

	/*
	* RvSipViaHeaderStringName
	* ----------------------
	* This enum defines all the header's strings (for getting it's size)
	* Defines all Via header object fields that are kept in the object
	* in a string format.
	*/
	typedef enum
	{
		RVSIP_VIA_TRANSPORT,
		RVSIP_VIA_HOST,
		RVSIP_VIA_MADDR_PARAM,
		RVSIP_VIA_RECEIVED_PARAM,
		RVSIP_VIA_BRANCH_PARAM,
		RVSIP_VIA_COMP_PARAM,
		RVSIP_VIA_OTHER_PARAMS,
		RVSIP_VIA_BAD_SYNTAX
	}RvSipViaHeaderStringName;

	/*-----------------------------------------------------------------------*/
	/*                   CONSTRUCTORS AND DESTRUCTORS                        */
	/*-----------------------------------------------------------------------*/

	/***************************************************************************
	* RvSipViaHeaderConstructInMsg
	* ------------------------------------------------------------------------
	* General: Constructs a Via Header header object inside a given message
	*          object. The header is kept in the header list of the message.
	*          You can choose to insert the header either at the head or tail
	*          of the list.
	* Return Value: RV_OK, RV_ERROR_INVALID_HANDLE, RV_ERROR_OUTOFRESOURCES.
	* ------------------------------------------------------------------------
	* Arguments:
	* input:  hSipMsg - Handle to the message object.
	*         pushHeaderAtHead - Boolean value indicating whether the header
	*                            should be pushed to the head of the list—RV_TRUE
	*                            —or to the tail—RV_FALSE.
	* output: hHeader - Handle to the newly constructed Via header object.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipViaHeaderConstructInMsg(
		IN  RvSipMsgHandle        hSipMsg,
		IN  RvBool               pushHeaderAtHead,
		OUT RvSipViaHeaderHandle* hHeader);

	/***************************************************************************
	* RvSipViaHeaderConstruct
	* ------------------------------------------------------------------------
	* General: Constructs and initializes a stand-alone Via header object.
	*          The header is constructed on a given page taken from a specified
	*          pool. The handle to the new header object is returned.
	* Return Value: RV_OK, RV_ERROR_INVALID_HANDLE, RV_ERROR_OUTOFRESOURCES.
	* ------------------------------------------------------------------------
	* Arguments:
	* input:  hMsgMgr - Handle to the Message manager.
	*         hPool   - Handle to the memory pool that the object will use.
	*         hPage   - Handle to the memory page that the object will use.
	* output: hHeader - Handle to the newly constructed Via header object.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipViaHeaderConstruct(
		IN  RvSipMsgMgrHandle     hMsgMgr,
		IN  HRPOOL                hPool,
		IN  HPAGE                 hPage,
		OUT RvSipViaHeaderHandle* hHeader);

	/***************************************************************************
	* RvSipViaHeaderCopy
	* ------------------------------------------------------------------------
	* General: Copies all fields from a source Via header object to a
	*          destination Via header object.
	*          You must construct the destination object before using this
	*          function.
	* Return Value: RV_OK, RV_ERROR_OUTOFRESOURCES, RV_ERROR_INVALID_HANDLE.
	* ------------------------------------------------------------------------
	* Arguments:
	*    pDestination - Handle to the destination Via header object.
	*    pSource      - Handle to the source Via header object.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipViaHeaderCopy(
		INOUT    RvSipViaHeaderHandle hDestination,
		IN       RvSipViaHeaderHandle hSource);

	/***************************************************************************
	* RvSipViaHeaderSetCompactForm
	* ------------------------------------------------------------------------
	* General: Instructs the header to use the compact header name when the
	*          header is encoded.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* input: hHeader  - Handle to the Via header object.
	*        bIsCompact - specify whether or not to use a compact form
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipViaHeaderSetCompactForm(
		IN    RvSipViaHeaderHandle hHeader,
		IN    RvBool                bIsCompact);

	/***************************************************************************
	* RvSipViaHeaderEncode
	* ------------------------------------------------------------------------
	* General: Encodes a Via header object to a textual Via header.
	*          The textual header is placed on a page taken from a specified pool.
	*          In order to copy the textual header from the page to a consecutive
	*          buffer, use RPOOL_CopyToExternal().
	* Return Value: RV_OK          - If succeeded.
	*               RV_ERROR_OUTOFRESOURCES   - If allocation failed (no resources)
	*               RV_ERROR_UNKNOWN          - In case of a failure.
	*               RV_ERROR_BADPARAM - If hHeader or hPage are NULL or no method was given.
	* ------------------------------------------------------------------------
	* Arguments:
	* input:  hHeader  - Handle to the Via header object.
	*         hPool    - Handle to the specified memory pool.
	* output: hPage   - The memory page allocated to contain the encoded header.
	*         length  - The length of the encoded information.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipViaHeaderEncode(
		IN    RvSipViaHeaderHandle   hHeader,
		IN    HRPOOL                 hPool,
		OUT   HPAGE*                 hPage,
		OUT   RvUint32*             length);

	/***************************************************************************
	* RvSipViaHeaderParse
	* ------------------------------------------------------------------------
	* General:Parses a SIP textual Via header—for example,
	*         “Via: SIP/2.0/UDP h.caller.com”—into a Via header object.
	*         All the textual fields are placed inside the object.
	*         You must construct a Via header before using this function.
	* Return Value: RV_OK, RV_ERROR_OUTOFRESOURCES, RV_ERROR_INVALID_HANDLE, RV_ERROR_NULLPTR,
	*                 RV_ERROR_ILLEGAL_SYNTAX,RV_ERROR_ILLEGAL_SYNTAX.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader   - A handle to the Via header object.
	*    buffer    - Buffer containing a textual Via header.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipViaHeaderParse(
		IN    RvSipViaHeaderHandle     hHeader,
		IN    RvChar*                 buffer);

	/***************************************************************************
	* RvSipViaHeaderParseValue
	* ------------------------------------------------------------------------
	* General: Parses a SIP textual Via header value into an Via header object.
	*          A SIP header has the following grammer:
	*          header-name:header-value. This function takes the header-value part as
	*          a parameter and parses it into the supplied object.
	*          All the textual fields are placed inside the object.
	*          Note: Use the RvSipViaHeaderParse() function to parse strings that also
	*          include the header-name.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader   - The handle to the Via header object.
	*    buffer    - The buffer containing a textual Via header value.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipViaHeaderParseValue(
		IN    RvSipViaHeaderHandle     hHeader,
		IN    RvChar*                 buffer);

	/***************************************************************************
	* RvSipViaHeaderFix
	* ------------------------------------------------------------------------
	* General: Fixes an Via header with bad-syntax information.
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
	RVAPI RvStatus RVCALLCONV RvSipViaHeaderFix(
		IN RvSipViaHeaderHandle hHeader,
		IN RvChar*             pFixedBuffer);

	/*-----------------------------------------------------------------------
	G E T  A N D  S E T  M E T H O D S
	------------------------------------------------------------------------*/
	/***************************************************************************
	* RvSipViaHeaderGetStringLength
	* ------------------------------------------------------------------------
	* General: Some of the Via header fields are kept in a string format—for
	*          example, the host parameter. In order to get such a field from
	*          the Via header object, your application should supply an adequate
	*          buffer to where the string will be copied. This function provides
	*          you with the length of the string to enable you to allocate
	*          an appropriate buffer size before calling the Get function.
	* Return Value: Returns the length of the specified string.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader    - Handle to the Via header object.
	*  stringName - Enumeration of the string name for which you require the length.
	***************************************************************************/
	RVAPI RvUint RVCALLCONV RvSipViaHeaderGetStringLength(
		IN  RvSipViaHeaderHandle     hHeader,
		IN  RvSipViaHeaderStringName stringName);

	/***************************************************************************
	* RvSipViaHeaderGetTransport
	* ------------------------------------------------------------------------
	* General: Gets the transport protocol enumeration from the Via header object.
	*          If this function returns RVSIP_TRANSPORT_OTHER, call
	*          RvSipViaHeaderGetStrTransport() to get the transport protocol
	*          in a string format.
	*
	* Return Value: Returns the transport protocol enumeration of the Via
	*        header object.
	* ------------------------------------------------------------------------
	* Arguments:
	*    input: hViaHeader - Handle to the Via header object.
	***************************************************************************/
	RVAPI RvSipTransport RVCALLCONV RvSipViaHeaderGetTransport(
		IN  RvSipViaHeaderHandle hViaHeader);

	/***************************************************************************
	* RvSipViaHeaderGetStrTransport
	* ------------------------------------------------------------------------
	* General: Copies the transport protocol string from the Via header object
	*          into a given buffer. Use this function if
	*          RvSipViaHeaderGetTransport() returns RVSIP_TRANSPORT_OTHER.
	*          If the bufferLen size is adequate, the function copies the
	*          parameter into the strBuffer. Otherwise, the function
	*          returns RV_ERROR_INSUFFICIENT_BUFFER and the actualLen paramater contains
	*          the required buffer length.
	* Return Value: RV_OK, RV_ERROR_INVALID_HANDLE, RV_ERROR_NULLPTR or RV_ERROR_INSUFFICIENT_BUFFER.
	* ------------------------------------------------------------------------
	* Arguments:
	*    input: hHeader - Handle to the Via header object.
	*         strBuffer - Buffer to fill with the requested parameter.
	*         bufferLen - The length of the buffer.
	*  output:actualLen - The length of the requested parameter + 1, to
	*         include a NULL value at the end of the parameter.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipViaHeaderGetStrTransport(
		IN  RvSipViaHeaderHandle hHeader,
		IN  RvChar*            strBuffer,
		IN  RvUint             bufferLen,
		OUT RvUint*            actualLen);

	/***************************************************************************
	* RvSipViaHeaderSetTransport
	* ------------------------------------------------------------------------
	* General:  Sets the transport type the Via header object.
	*           You can use this parametere only if the eTransport parameter is
	*           set to RVSIP_TRANSPORT_OTHER. In this case you can supply the
	*           transport protocol as a string.
	*           If eTransport is set to RVSIP_TRANSPORT_OTHER strTransport is
	*           copied to the header. Otherwise, strTransport is ignored.
	* Return Value: RV_OK, RV_ERROR_INVALID_HANDLE, RV_ERROR_BADPARAM.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hSipViaHeader - Handle to the Via header object.
	*    eTransport    - The enumeration transport protocol to set in the object.
	*  strTransport  - You can use this parametere only if the eTransport
	*                  parameter is set to RVSIP_TRANSPORT_OTHER. In this case
	*                  you can supply the transport protocol as a string.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipViaHeaderSetTransport(
		IN    RvSipViaHeaderHandle hSipViaHeader,
		IN    RvSipTransport       eTransport,
		IN    RvChar*             strTransport);

	/***************************************************************************
	* RvSipViaHeaderGetHost
	* ------------------------------------------------------------------------
	* General:  Copies the host name—send-by parameter—from the Via header
	*           object into a given buffer. If the bufferLen size is adequate,
	*           the function copies the parameter into the strBuffer.
	*           Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and the
	*           actualLen parameter contains the required buffer length.
	* Return Value: RV_OK, RV_ERROR_INVALID_HANDLE, RV_ERROR_NULLPTR or RV_ERROR_INSUFFICIENT_BUFFER.
	* ------------------------------------------------------------------------
	* Arguments:
	* input: hHeader   - Handle to the header object.
	*        strBuffer - Buffer to fill with the requested parameter.
	*        bufferLen - The length of the buffer.
	*  output:actualLen - The length of the requested parameter + 1, to
	*         include a NULL value at the end of the parameter.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipViaHeaderGetHost(
		IN RvSipViaHeaderHandle hHeader,
		IN RvChar*             strBuffer,
		IN RvUint              bufferLen,
		OUT RvUint*            actualLen);


	/***************************************************************************
	* RvSipViaHeaderSetHost
	* ------------------------------------------------------------------------
	* General: Sets the host field in the Via header object.
	* Return Value: RV_OK, RV_ERROR_OUTOFRESOURCES, RV_ERROR_INVALID_HANDLE.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hSipViaHeader - Handle to the Via header object.
	*    strHost       - The host to be set in the object. If Null is supplied,
	*                  the existing host string is removed from the object.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipViaHeaderSetHost(
		IN    RvSipViaHeaderHandle hViaHeader,
		IN    RvChar*             strHost);

	/***************************************************************************
	* RvSipViaHeaderGetPortNum
	* ------------------------------------------------------------------------
	* General: Gets the host port from the Via header object.
	* Return Value: Returns the port number, or UNDEFINED if the port number
	*               does not exist.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hViaHeader - Handle to the Via header object.
	***************************************************************************/
	RVAPI RvInt32 RVCALLCONV RvSipViaHeaderGetPortNum(
		IN RvSipViaHeaderHandle hViaHeader);


	/***************************************************************************
	* RvSipViaHeaderSetPortNum
	* ------------------------------------------------------------------------
	* General:  Sets the host port number of the Via header object.
	* Return Value: RV_OK,  RV_ERROR_INVALID_HANDLE.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hViaHeader - Handle to the Via header object.
	*    portNum       - The port number value to be set in the object.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipViaHeaderSetPortNum(
		IN    RvSipViaHeaderHandle hViaHeader,
		IN    RvInt32             portNum);

	/***************************************************************************
	* RvSipViaHeaderGetTtlNum
	* ------------------------------------------------------------------------
	* General: Gets the ttl from the Via header object.
	* Return Value: Returns the ttl number, or UNDEFINED if the ttl
	*               does not exist.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hViaHeader - Handle to the Via header object.
	***************************************************************************/
	RVAPI RvInt16 RVCALLCONV RvSipViaHeaderGetTtlNum(
		IN RvSipViaHeaderHandle hViaHeader);

	/***************************************************************************
	* RvSipViaHeaderSetTtlNum
	* ------------------------------------------------------------------------
	* General: Sets the ttl field in the Via header object.
	* Return Value: RV_OK,  RV_ERROR_INVALID_HANDLE.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hViaHeader - Handle to the Via header object.
	*    ttlNum        - The ttl value to be set in the object.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipViaHeaderSetTtlNum(
		IN    RvSipViaHeaderHandle hViaHeader,
		IN    RvInt16             ttlNum);

	/***************************************************************************
	* RvSipViaHeaderGetMaddrParam
	* ------------------------------------------------------------------------
	* General: Copies the maddr parameter of the Via header object into a
	*          given buffer. If the bufferLen size is adequate, the function
	*          copies the parameter into the strBuffer. Otherwise, the function
	*          returns RV_ERROR_INSUFFICIENT_BUFFER and the actualLen parameter contains
	*          the required buffer length.
	* Return Value: RV_OK, RV_ERROR_INVALID_HANDLE, RV_ERROR_NULLPTR or RV_ERROR_INSUFFICIENT_BUFFER.
	* ------------------------------------------------------------------------
	* Arguments:
	* input: hHeader   - Handle to the header object.
	*        strBuffer - Buffer to fill with the requested parameter.
	*        bufferLen - The length of the buffer.
	*  output:actualLen - The length of the requested parameter + 1, to
	*         include a NULL value at the end of the parameter.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipViaHeaderGetMaddrParam(
		IN RvSipViaHeaderHandle hHeader,
		IN RvChar*             strBuffer,
		IN RvUint              bufferLen,
		OUT RvUint*            actualLen);


	/***************************************************************************
	* RvSipViaHeaderSetMaddrParam
	* ------------------------------------------------------------------------
	* General: Sets the maddr string parameter in the Via header object.
	* Return Value: RV_OK, RV_ERROR_OUTOFRESOURCES, RV_ERROR_INVALID_HANDLE.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hViaHeader - Handle to the Via header object.
	*    strMaddrParam - The Maddr parameter to be set in the object. If Null is
	*                  supplied, the existing Maddr parameter string is removed
	*                  from the object.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipViaHeaderSetMaddrParam(
		IN    RvSipViaHeaderHandle hViaHeader,
		IN    RvChar              *strMaddrParam);

	/***************************************************************************
	* RvSipViaHeaderGetReceivedParam
	* ------------------------------------------------------------------------
	* General: Copies the received parameter of the Via header object into a
	*          given buffer. If the bufferLen size is adequate, the function
	*          copies the parameter into the strBuffer. Otherwise, the function
	*          returns RV_ERROR_INSUFFICIENT_BUFFER and the actualLen parameter
	*          contains the required buffer length.
	* Return Value: RV_OK, RV_ERROR_INVALID_HANDLE, RV_ERROR_NULLPTR or RV_ERROR_INSUFFICIENT_BUFFER.
	* ------------------------------------------------------------------------
	* Arguments:
	* input: hHeader   - Handle to the header object.
	*        strBuffer - Buffer to fill with the requested parameter.
	*        bufferLen - The length of the buffer.
	*  output:actualLen - The length of the requested parameter + 1, to
	*         include a NULL value at the end of the parameter.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipViaHeaderGetReceivedParam(
		IN RvSipViaHeaderHandle hHeader,
		IN RvChar*             strBuffer,
		IN RvUint              bufferLen,
		OUT RvUint*            actualLen);


	/***************************************************************************
	* RvSipViaHeaderSetReceivedParam
	* ------------------------------------------------------------------------
	* General: Sets the value of the received string parameter in the Via
	*          header object.
	* Return Value: RV_OK, RV_ERROR_OUTOFRESOURCES, RV_ERROR_INVALID_HANDLE.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hViaHeader    - Handle to the Via header object.
	*    strReceivedParam - The Received parameter to be set in the object.
	*                     If Null is supplied, the existing received parameter
	*                     string is removed from the object.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipViaHeaderSetReceivedParam(
		IN    RvSipViaHeaderHandle hViaHeader,
		IN    RvChar*             strReceivedParam);

	/***************************************************************************
	* RvSipViaHeaderGetRportParam
	* ------------------------------------------------------------------------
	* General: Gets the rport parameter from the Via header object.
	* Return Value: Returns RV_OK when rport parameter appears in Via header,
	*                 or RV_ERROR_UNKNOWN in case of nonexisting rport parameter,
	*               RV_ERROR_INVALID_HANDLE, or RV_ERROR_BADPARAM.
	* ------------------------------------------------------------------------
	* Arguments:
	* input:  hSipViaHeader - Handle to the Via header object.
	* output: rportParam    - The rport (number) value , or UNDEFINED if the rport
	*               parameter is empty.
	*         bUseRport     - Indication if 'rport' parameter exists in header
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipViaHeaderGetRportParam(
		IN  RvSipViaHeaderHandle hSipViaHeader,
		OUT RvInt32*            rportParam,
		OUT RvBool*              bUseRport);


	/***************************************************************************
	* RvSipViaHeaderSetRportParam
	* ------------------------------------------------------------------------
	* General:  Sets the rport parameter value in Via header object.
	* Return Value: RV_OK,RV_ERROR_INVALID_HANDLE.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hSipViaHeader - Handle to the Via header object.
	*    rportParam    - The rport number to be set in the Via header object
	*                  (UNDEFINED is possible for empty 'rport' paramter)
	*  useRport      - Indication if the 'rport' should be added to Via Header
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipViaHeaderSetRportParam(
		IN    RvSipViaHeaderHandle hSipViaHeader,
		IN    RvInt32             rportParam,
		IN    RvBool              useRport);

	/***************************************************************************
	* RvSipViaHeaderGetBranchParam
	* ------------------------------------------------------------------------
	* General: Copies the Branch parameter from the Via header object into a
	*          given buffer. If the bufferLen size is adequate, the function
	*          copies the parameter into the strBuffer. Otherwise, the function
	*          returns RV_ERROR_INSUFFICIENT_BUFFER and the actualLen parameter contains
	*          the required buffer length.
	* Return Value: RV_OK, RV_ERROR_INVALID_HANDLE, RV_ERROR_NULLPTR or RV_ERROR_INSUFFICIENT_BUFFER.
	* ------------------------------------------------------------------------
	* Arguments:
	* input: hHeader   - Handle to the header object.
	*        strBuffer - Buffer to fill with the requested parameter.
	*        bufferLen - The length of the buffer.
	*  output:actualLen - The length of the requested parameter + 1, to
	*         include a NULL value at the end of the parameter.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipViaHeaderGetBranchParam(
		IN RvSipViaHeaderHandle hHeader,
		IN RvChar*             strBuffer,
		IN RvUint              bufferLen,
		OUT RvUint*            actualLen);


	/***************************************************************************
	* RvSipViaHeaderSetBranchParam
	* ------------------------------------------------------------------------
	* General: Sets the branch parameter in the Via header object.
	* Return Value: RV_OK, RV_ERROR_OUTOFRESOURCES, RV_ERROR_INVALID_HANDLE.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hViaHeader       - Handle to the Via header object.
	*    strBranchParam   - The Branch parameter to be set in the object.
	*                     If NULL is supplied, the existing Branch string is
	*                     removed from the Via header object.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipViaHeaderSetBranchParam(
		IN    RvSipViaHeaderHandle hViaHeader,
		IN    RvChar*             strBranchParam);

	/***************************************************************************
	* RvSipViaHeaderGetCompParam
	* ------------------------------------------------------------------------
	* General: Gets the 'comp' enumeration from the Via header object.
	*          If this function returns RVSIP_SIGCOMP_OTHER, call
	*          RvSipViaHeaderGetStrCompParam() to get the 'comp' parameter
	*          in a string format.
	*
	* Return Value: Returns the 'comp' enumeration of the Via
	*        header object.
	* ------------------------------------------------------------------------
	* Arguments:
	*    input: hViaHeader - Handle to the Via header object.
	***************************************************************************/
	RVAPI RvSipCompType RVCALLCONV RvSipViaHeaderGetCompParam(
		IN  RvSipViaHeaderHandle hSipViaHeader);


	/***************************************************************************
	* RvSipViaHeaderGetStrCompParam
	* ------------------------------------------------------------------------
	* General: Copies the Comp parameter from the Via header object into a
	*          given buffer. If the bufferLen size is adequate, the function
	*          copies the parameter into the strBuffer. Otherwise, the function
	*          returns RV_ERROR_INSUFFICIENT_BUFFER and the actualLen parameter contains
	*          the required buffer length.
	* Return Value: RV_OK, RV_ERROR_INVALID_HANDLE, RV_ERROR_NULLPTR or RV_ERROR_INSUFFICIENT_BUFFER.
	* ------------------------------------------------------------------------
	* Arguments:
	* input: hHeader   - Handle to the header object.
	*        strBuffer - Buffer to fill with the requested parameter.
	*        bufferLen - The length of the buffer.
	*  output:actualLen - The length of the requested parameter + 1, to
	*         include a NULL value at the end of the parameter.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipViaHeaderGetStrCompParam(
		IN  RvSipViaHeaderHandle hHeader,
		IN  RvChar*             strBuffer,
		IN  RvUint              bufferLen,
		OUT RvUint*             actualLen);

	/***************************************************************************
	* RvSipViaHeaderSetCompParam
	* ------------------------------------------------------------------------
	* General:  Sets the compression type in the Via header object.
	*           You can use strTransport parameter only if the eComp parameter
	*           is set to RVSIP_COMP_OTHER. In this case you can supply the
	*           compression type as a string.
	*           If eComp is set to RVSIP_COMP_OTHER strComp is
	*           copied to the header. Otherwise, strComp is ignored.
	* Return Value: RV_OK, RV_ERROR_INVALID_HANDLE, RV_ERROR_BADPARAM.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hSipViaHeader - Handle to the Via header object.
	*    eComp         - The enumeration transport protocol to set in the object.
	*  strComp       - You can use this parameter only if the eComp
	*                  parameter is set to RVSIP_COMP_OTHER. In this case
	*                  you can supply the compression type as a string.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipViaHeaderSetCompParam(
		IN    RvSipViaHeaderHandle hSipViaHeader,
		IN    RvSipCompType        eComp,
		IN    RvChar*             strComp);

	/***************************************************************************
	* RvSipViaHeaderGetHiddenParam
	* ------------------------------------------------------------------------
	* General: This method gets the hidden parameter from the Via Header object.
	* Return Value: The hidden parameter value. If the hidden parameter exists
	*               in the Via Header then RV_TRUE will be returned, otherwise - RV_FALSE.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hSipViaHeader - Handle of the Via header object.
	***************************************************************************/
	RVAPI RvBool RVCALLCONV RvSipViaHeaderGetHiddenParam(IN RvSipViaHeaderHandle hSipViaHeader);

	/***************************************************************************
	* RvSipViaHeaderSetHiddenParam
	* ------------------------------------------------------------------------
	* General: This method sets the hidden parameter in the Via Header object.
	*          If the hidden parameter exists in the Via Header RV_TRUE will be
	*          set, otherwise - RV_FALSE.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    Input:   hSipViaHeader - Handle of the Via header object.
	*           hiddenValue   - The hidden parameter value to set.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipViaHeaderSetHiddenParam(IN  RvSipViaHeaderHandle hSipViaHeader,
		IN RvBool              hiddenValue);

	/***************************************************************************
	* RvSipViaHeaderGetOtherParams
	* ------------------------------------------------------------------------
	* General: Copies the Via header other params field of the Via header
	*          object into a given buffer.
	*          Not all the Via header parameters have separated fields in the
	*          Via header object.
	*          Parameters with no specific fields are refered to as other params.
	*          They are kept in the object in one concatenated string in the form?
	*          ”name=value;name=value...?
	*          If the bufferLen is adequate, the function copies the requested
	*          parameter into strBuffer. Otherwise, the function returns
	*          RV_ERROR_INSUFFICIENT_BUFFER and actualLen contains the required buffer length.
	* Return Value: RV_OK, RV_ERROR_INVALID_HANDLE, RV_ERROR_NULLPTR or RV_ERROR_INSUFFICIENT_BUFFER.
	* ------------------------------------------------------------------------
	* Arguments:
	* input: hHeader   - Handle to the header object.
	*        strBuffer - Buffer to fill with the requested parameter.
	*        bufferLen - The length of the buffer.
	*  output:actualLen - The length of the requested parameter + 1, to
	*         include a NULL value at the end of the parameter.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipViaHeaderGetOtherParams(
		IN RvSipViaHeaderHandle hHeader,
		IN RvChar*             strBuffer,
		IN RvUint              bufferLen,
		OUT RvUint*            actualLen);


	/***************************************************************************
	* RvSipViaHeaderSetOtherParams
	* ------------------------------------------------------------------------
	* General: Sets the other params field in the Via header object.
	*          Not all the Via header parameters have separated fields in the
	*          Via header object. Parameters with no specific fields are refered
	*          to as other params. They are kept in the object in one concatenated
	*          string in the form?”name=value;name=value...?
	* Return Value: RV_OK, RV_ERROR_OUTOFRESOURCES, RV_ERROR_INVALID_HANDLE.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hSipViaHeader    - Handle to the Via header object.
	*    strViaParams     - The Via Params string to be set in the Via header.
	*                     If NULL is supplied, the existing Other Params field
	*                     is removed from the header.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipViaHeaderSetOtherParams(
		IN    RvSipViaHeaderHandle hSipViaHeader,
		IN    RvChar*             strViaParams);

	/***************************************************************************
	* RvSipViaHeaderGetStrBadSyntax
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
	*          implementation if the message contains a bad Via header,
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
	RVAPI RvStatus RVCALLCONV RvSipViaHeaderGetStrBadSyntax(
		IN RvSipViaHeaderHandle hHeader,
		IN RvChar*                 strBuffer,
		IN RvUint                  bufferLen,
		OUT RvUint*                actualLen);

	/***************************************************************************
	* RvSipViaHeaderSetStrBadSyntax
	* ------------------------------------------------------------------------
	* General: Sets a bad-syntax string in the object.
	*          A SIP header has the following grammer:
	*          header-name:header-value. When a header contains a syntax error,
	*          the header-value is kept as a separate "bad-syntax" string.
	*          By using this function you can create a header with "bad-syntax".
	*          Setting a bad syntax string to the header will mark the header as
	*          an invalid syntax header.
	*          You can use his function when you want to send an illegal Via header.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader      - The handle to the header object.
	*  strBadSyntax - The bad-syntax string.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipViaHeaderSetStrBadSyntax(
		IN RvSipViaHeaderHandle hHeader,
		IN RvChar*             strBadSyntax);

#ifndef RV_SIP_PRIMITIVES
	/***************************************************************************
	* RvSipViaHeaderGetRpoolString
	* ------------------------------------------------------------------------
	* General: Copy a string parameter from the via header into a given page
	*          from a specified pool. The copied string is not consecutive.
	* Return Value: RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    Input: hSipViaHeader - Handle to the Via header object.
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
	RVAPI RvStatus RVCALLCONV RvSipViaHeaderGetRpoolString(
		IN    RvSipViaHeaderHandle      hSipViaHeader,
		IN    RvSipViaHeaderStringName  eStringName,
		INOUT RPOOL_Ptr                 *pRpoolPtr);

#endif /* #ifndef RV_SIP_PRIMITIVES*/

	/***************************************************************************
	* RvSipViaHeaderSetRpoolString
	* ------------------------------------------------------------------------
	* General: Sets a string into a specified parameter in the Via header
	*          object. The given string is located on an RPOOL memory and is
	*          not consecutive.
	* Return Value: RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    Input: hSipViaHeader - Handle to the Via header object.
	*           eStringName   - The string the user wish to set
	*         pRpoolPtr     - pointer to a location inside an rpool where the
	*                         new string is located.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipViaHeaderSetRpoolString(
		IN    RvSipViaHeaderHandle      hSipViaHeader,
		IN    RvSipViaHeaderStringName  eStringName,
		IN    RPOOL_Ptr                 *pRpoolPtr);


#ifdef __cplusplus
}
#endif

#endif /* RVSIPVIAHEADER_H */
