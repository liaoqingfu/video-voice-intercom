/*

NOTICE:
This document contains information that is proprietary to RADVision LTD..
No part of this publication may be reproduced in any form whatsoever without
written prior approval by RADVision LTD..

RADVision LTD. reserves the right to revise this publication and make changes
without obligation to notify any person of such revisions or changes.

*/

/******************************************************************************
*                             RvSipSessionExpiresHeader.c                    *
*                                                                            *
* The file defines the methods of the Session Expires header object.         *
* The Session Expires header functions enable you to construct, copy, encode *
* parse, access and change Session Expires Header parameters.                *
*                                                                            *
*      Author           Date                                                 *
*     ------           ------------                                          *
*     Michal Mashiach    June 2001                                           *
******************************************************************************/


#ifndef RVSIPSESSIONEXPIRESHEADER_H
#define RVSIPSESSIONEXPIRESHEADER_H

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
	* RvSipSessionExpiresHeaderStringName
	* ----------------------
	* Defines all Session Expires header object fields that are kept in
	* the object in a string format.
	*/
	typedef enum
	{
		RVSIP_SESSION_EXPIRES_OTHER_PARAMS,
		RVSIP_SESSION_EXPIRES_BAD_SYNTAX
	} RvSipSessionExpiresHeaderStringName;
	/*-----------------------------------------------------------------------*/
	/*                   CONSTRUCTORS AND DESTRUCTORS                        */
	/*-----------------------------------------------------------------------*/

	/***************************************************************************
	* RvSipSessionExpiresHeaderConstructInMsg
	* ------------------------------------------------------------------------
	* General: Constructs a Session Expires header object inside a given message object.
	*          The header is kept in the header list of the message. You can
	*          choose to insert the header either at the head or tail of the list.
	* Return Value: RV_OK, RV_ERROR_INVALID_HANDLE, RV_ERROR_NULLPTR, RV_ERROR_OUTOFRESOURCES
	* ------------------------------------------------------------------------
	* Arguments:
	* input:  hSipMsg - Handle to the message object.
	*         pushHeaderAtHead - Boolean value indicating whether the header
	*                            should be pushed to the head of the
	*                            list(RV_TRUE) or to the tail(RV_FALSE).
	* output: phHeader - Handle to the newly constructed Session Expires header object.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipSessionExpiresHeaderConstructInMsg(
		IN  RvSipMsgHandle                   hSipMsg,
		IN  RvBool                          pushHeaderAtHead,
		OUT RvSipSessionExpiresHeaderHandle* phHeader);


	/***************************************************************************
	* RvSipSessionExpiresHeaderConstruct
	* ------------------------------------------------------------------------
	* General: Constructs and initializes a stand-alone Session Expires Header object.
	*          The header is constructed on a given page taken from a specified
	*          pool. The handle to the new header object is returned.
	* Return Value: RV_OK, RV_ERROR_INVALID_HANDLE, RV_ERROR_NULLPTR, RV_ERROR_OUTOFRESOURCES.
	* ------------------------------------------------------------------------
	* Arguments:
	* input:  hMsgMgr  - Handle to the message manager.
	*         hPool    - Handle to the memory pool that the object will use.
	*         hPage    - Handle to the memory page that the object will use.
	* output: phHeader - Handle to the newly constructed Session Expires header object.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipSessionExpiresHeaderConstruct(
		IN  RvSipMsgMgrHandle                hMsgMgr,
		IN  HRPOOL                           hPool,
		IN  HPAGE                            hPage,
		OUT RvSipSessionExpiresHeaderHandle* phHeader);


	/***************************************************************************
	* RvSipSessionExpiresHeaderCopy
	* ------------------------------------------------------------------------
	* General:Copies all fields from a source Session Expires header object to a
	*         destination Session Expires header object.
	*         You must construct the destination object before using this function.
	* Return Value: RV_OK, RV_ERROR_OUTOFRESOURCES, RV_ERROR_INVALID_HANDLE.
	* ------------------------------------------------------------------------
	* Arguments:
	*    pDestination - Handle to the destination Session Expires header object.
	*    pSource      - Handle to the source Session Expires header object.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipSessionExpiresHeaderCopy(
		INOUT RvSipSessionExpiresHeaderHandle hDestination,
		IN    RvSipSessionExpiresHeaderHandle hSource);


	/***************************************************************************
	* RvSipSessionExpiresHeaderSetCompactForm
	* ------------------------------------------------------------------------
	* General: Instructs the header to use the compact header name when the
	*          header is encoded.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* input: hHeader  - Handle to the Session-Expires header object.
	*        bIsCompact - specify whether or not to use a compact form
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipSessionExpiresHeaderSetCompactForm(
		IN RvSipSessionExpiresHeaderHandle hHeader,
		IN RvBool                      bIsCompact);

	/***************************************************************************
	* RvSipSessionExpiresHeaderEncode
	* ------------------------------------------------------------------------
	* General: Encodes a Session Expires header object to a textual Session Expires header.
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
	* input: hHeader  - Handle to the Session Expires header object.
	*        hPool    - Handle to the specified memory pool.
	* output: phPage   - The memory page allocated to contain the encoded header.
	*         pLength  - The length of the encoded information.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipSessionExpiresHeaderEncode(
		IN    RvSipSessionExpiresHeaderHandle hHeader,
		IN    HRPOOL                          hPool,
		OUT   HPAGE*                          phPage,
		OUT   RvUint32*                      pLength);


	/***************************************************************************
	* RvSipSessionExpiresHeaderParse
	* ------------------------------------------------------------------------
	* General:Parses a SIP textual Session Expires header—for example,
	*         “Session Expires: 3600;refresher=uac??into a Session Expires header
	*          object. All the textual fields are placed inside the object.
	* Return Value: RV_OK, RV_ERROR_OUTOFRESOURCES,RV_ERROR_INVALID_HANDLE,
	*                 RV_ERROR_ILLEGAL_SYNTAX,RV_ERROR_ILLEGAL_SYNTAX.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader      - A handle to the Session Expires header object.
	*    strBuffer    - Buffer containing a textual Session Expires header.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipSessionExpiresHeaderParse(
		IN    RvSipSessionExpiresHeaderHandle hHeader,
		IN    RvChar*                        strBuffer);

	/***************************************************************************
	* RvSipSessionExpiresHeaderParseValue
	* ------------------------------------------------------------------------
	* General: Parses a SIP textual SessionExpires header value into an
	*          SessionExpires header object.
	*          A SIP header has the following grammer:
	*          header-name:header-value. This function takes the header-value
	*          part as a parameter and parses it into the supplied object.
	*          All the textual fields are placed inside the object.
	*          Note: Use the RvSipSessionExpiresHeaderParse() function to parse
	*          strings that also include the header-name.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader   - The handle to the SessionExpires header object.
	*    buffer    - The buffer containing a textual SessionExpires header value.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipSessionExpiresHeaderParseValue(
		IN RvSipSessionExpiresHeaderHandle hHeader,
		IN RvChar*                        buffer);

	/***************************************************************************
	* RvSipSessionExpiresHeaderFix
	* ------------------------------------------------------------------------
	* General: Fixes an SessionExpires header with bad-syntax information.
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
	RVAPI RvStatus RVCALLCONV RvSipSessionExpiresHeaderFix(
		IN RvSipSessionExpiresHeaderHandle hHeader,
		IN RvChar*                        pFixedBuffer);

	/*-----------------------------------------------------------------------
	G E T  A N D  S E T  M E T H O D S
	------------------------------------------------------------------------*/


	/***************************************************************************
	* RvSipSessionExpiresHeaderGetDeltaSeconds
	* ------------------------------------------------------------------------
	* General: Gets the delta-seconds integer of the Session Expires header.
	*          If the delta-seconds integer is not set, UNDEFINED is returned.
	* Return Value: RV_OK - success.
	*               RV_ERROR_INVALID_HANDLE - hHeader is NULL.
	*               RV_ERROR_NULLPTR - pDeltaSeconds is NULL.
	* ------------------------------------------------------------------------
	* Arguments:
	*  Input:  hHeader       - Handle to the Session Expires header object.
	*  Output: pDeltaSeconds - The delta-seconds integer.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipSessionExpiresHeaderGetDeltaSeconds(
		IN  RvSipSessionExpiresHeaderHandle hHeader,
		OUT RvInt32                       *pDeltaSeconds);


	/***************************************************************************
	* RvSipSessionExpiresHeaderSetDeltaSeconds
	* ------------------------------------------------------------------------
	* General: Sets the delta seconds integer of the Session Expires header.
	*          If the given delta-seconds is UNDEFINED, the delta-seconds of
	*          the Session Expires header is removed
	* Return Value: RV_OK - success.
	*               RV_ERROR_INVALID_HANDLE - The Session Expires header handle is invalid.
	* ------------------------------------------------------------------------
	* Arguments:
	*    Input: hHeader - Handle to the Session Expires header object.
	*         deltaSeconds - The delta-seconds to be set to the Session Expires header.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipSessionExpiresHeaderSetDeltaSeconds(
		IN  RvSipSessionExpiresHeaderHandle hHeader,
		IN  RvInt32                        deltaSeconds);


	/***************************************************************************
	* RvSipSessionExpiresHeaderGetRefresherType
	* ------------------------------------------------------------------------
	* General: Gets the refresher type of the Session Expires header.
	*          If the refresher type is not set,
	*          RVSIP_SESSION_EXPIRES_REFRESHER_NONE is returned.
	* Return Value: RV_OK - success.
	*               RV_ERROR_INVALID_HANDLE - hHeader is NULL.
	*               RV_ERROR_NULLPTR - peRefresherType is NULL.
	* ------------------------------------------------------------------------
	* Arguments:
	*    Input:  hHeader - Handle to the Session Expires header object.
	*  Output: peRefresherType - The refresher type.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipSessionExpiresHeaderGetRefresherType(
		IN  RvSipSessionExpiresHeaderHandle  hHeader,
		OUT RvSipSessionExpiresRefresherType *peRefresherType);
	/***************************************************************************
	* RvSipSessionExpiresHeaderSetRefresherType
	* ------------------------------------------------------------------------
	* General: Sets the refresher type of the Session Expires header.
	* Return Value: RV_OK - success.
	*               RV_ERROR_INVALID_HANDLE - The Session Expires header handle is invalid.
	* ------------------------------------------------------------------------
	* Arguments:
	*    Input: hHeader - Handle to the Session Expires header object.
	*         deltaSeconds - The refreher type to be set to the Session Expires header.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipSessionExpiresHeaderSetRefresherType(
		IN  RvSipSessionExpiresHeaderHandle  hHeader,
		IN  RvSipSessionExpiresRefresherType eRefresherType);


	/***************************************************************************
	* RvSipSessionExpiresHeaderGetOtherParams
	* ------------------------------------------------------------------------
	* General: Copies the other parameters string from the Session-Expires header
	*          into a given buffer.
	*          Not all the Session-Expires header parameters have separated fields
	*          in the Session-Expires header object. Parameters with no specific
	*          fields are refered to as other params. They are kept in the object
	*          in one concatenated string in the form?”name=value;name=value...?
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
	RVAPI RvStatus RVCALLCONV RvSipSessionExpiresHeaderGetOtherParams(
		IN RvSipSessionExpiresHeaderHandle hHeader,
		IN RvChar*                        strBuffer,
		IN RvUint                         bufferLen,
		OUT RvUint*                       actualLen);
	/***************************************************************************
	* RvSipSessionExpiresHeaderSetOtherParams
	* ------------------------------------------------------------------------
	* General: Sets the other parameters string in the Session-Expires header object.
	*          The given string is copied to the Session-Expires header.
	*          Not all the Session-Expires header parameters have separated fields
	*          in the Session-Expires header object. Parameters with no specific
	*          fields are refered to as other params. They are kept in the object
	*          in one concatenated string in the form?”name=value;name=value...?
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader     - Handle to the header object.
	*    otherParams - The other parameters string to be set in the Session-Expires
	*                header. If NULL is supplied, the existing parametes string
	*                is removed from the header.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipSessionExpiresHeaderSetOtherParams(
		IN   RvSipSessionExpiresHeaderHandle  hHeader,
		IN   RvChar                      *otherParams);

	/***************************************************************************
	* RvSipSessionExpiresHeaderGetStrBadSyntax
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
	*          implementation if the message contains a bad SessionExpires header,
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
	RVAPI RvStatus RVCALLCONV RvSipSessionExpiresHeaderGetStrBadSyntax(
		IN RvSipSessionExpiresHeaderHandle hHeader,
		IN RvChar*                 strBuffer,
		IN RvUint                  bufferLen,
		OUT RvUint*                actualLen);

	/***************************************************************************
	* RvSipSessionExpiresHeaderSetStrBadSyntax
	* ------------------------------------------------------------------------
	* General: Sets the bad-syntax string in object.
	* A SIP header has the following grammar: header-name:header-value. When a
	* header contains a syntax error, the header-value is kept as a separate 
	* bad-syntax string. By using this function you can create a header with a
	* bad-syntax string. Setting a bad-syntax string to the header will mark 
	* the header as an invalid syntax header. 
	* You can use his function when you want to send an illegal SessionExpires
	* header.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*  hHeader      - Handle to the header object.
	*  strBadSyntax - The bad-syntax string.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipSessionExpiresHeaderSetStrBadSyntax(
		IN RvSipSessionExpiresHeaderHandle hHeader,
		IN RvChar*                     strBadSyntax);

	/***************************************************************************
	* RvSipSessionExpiresHeaderGetStringLength
	* ------------------------------------------------------------------------
	* General: The other params of Session-Expires header fields are kept in a string
	*          format.
	*          In order to get such a field from the Session-Expires header
	*          object, your application should supply an adequate buffer to where
	*          the string will be copied.
	*          This function provides you with the length of the string to enable
	*          you to allocate an appropriate buffer size before calling the Get
	*          function.
	* Return Value: Returns the length of the specified string.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader    - Handle to the Session-Expires header object.
	*  stringName - Enumeration of the string name for which you require the
	*               length.
	***************************************************************************/
	RVAPI RvUint RVCALLCONV RvSipSessionExpiresHeaderGetStringLength(
		IN  RvSipSessionExpiresHeaderHandle     hHeader,
		IN  RvSipSessionExpiresHeaderStringName stringName);
#endif /* RV_SIP_PRIMITIVES*/

#ifdef __cplusplus
}
#endif

#endif /* END OF: #ifndef RVSIPSESSIONEXPIRESHEADER_H */

