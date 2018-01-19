
/*

NOTICE:
This document contains information that is proprietary to RADVision LTD..
No part of this publication may be reproduced in any form whatsoever without
written prior approval by RADVision LTD..

RADVision LTD. reserves the right to revise this publication and make changes
without obligation to notify any person of such revisions or changes.

*/

/******************************************************************************
*                     RvSipSubscriptionStateHeader.h                         *
*                                                                            *
* The file defines the methods of the Subscription-State header object:      *
* construct, destruct, copy, encode, parse and the ability to access and     *
* change it's parameters.                                                    *
*                                                                            *
*                                                                            *
*      Author           Date                                                 *
*     ------           ------------                                          *
*     Ofra Wachsman    May 2002                                              *
******************************************************************************/

#ifndef RVSIPSUBSSTATEHEADER_H
#define RVSIPSUBSSTATEHEADER_H

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
	* RvSipSubscriptionStateHeaderStringName
	* ----------------------
	* This enum defines all the header's strings (for getting it's size)
	* Defines all Subscription-State header object fields that are kept 
	* in the object in string format.
	*/
	typedef enum
	{
		RVSIP_SUBSCRIPTION_STATE_SUBSTATE_VAL,
		RVSIP_SUBSCRIPTION_STATE_REASON,
		RVSIP_SUBSCRIPTION_STATE_OTHER_PARAMS,
		RVSIP_SUBSCRIPTION_STATE_BAD_SYNTAX

	}RvSipSubscriptionStateHeaderStringName;

	/****************************************************/
	/*        CONSTRUCTORS AND DESTRUCTORS                */
	/****************************************************/

	/***************************************************************************
	* RvSipSubscriptionStateHeaderConstructInMsg
	* ------------------------------------------------------------------------
	* General: Constructs a Subscription-State header object inside a given message
	*          object. The header is kept in the header list of the message.
	*          You can choose to insert the header either at the head or tail of
	*          the list.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* input:  hSipMsg          - Handle to the message object.
	*         pushHeaderAtHead - Boolean value indicating whether the header should
	*                            be pushed to the head of the list—RV_TRUE—or to the
	*                            tail—RV_FALSE.
	* output: hHeader          - Handle to the newly constructed Subscription-State header object.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipSubscriptionStateHeaderConstructInMsg(
		IN  RvSipMsgHandle                      hSipMsg,
		IN  RvBool                             pushHeaderAtHead,
		OUT RvSipSubscriptionStateHeaderHandle* hHeader);

	/***************************************************************************
	* RvSipSubscriptionStateHeaderConstruct
	* ------------------------------------------------------------------------
	* General: Constructs and initializes a stand-alone Subscription-State Header object.
	*          The header is constructed on a given page taken from a specified
	*          pool. The handle to the new header object is returned.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* input:  hMsgMgr - Handle to the Message manager.
	*         hPool   - Handle to the memory pool that the object will use.
	*         hPage   - Handle to the memory page that the object will use.
	* output: hHeader - Handle to the newly constructed Subscription-State header object.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipSubscriptionStateHeaderConstruct(
		IN  RvSipMsgMgrHandle                   hMsgMgr,
		IN  HRPOOL                              hPool,
		IN  HPAGE                               hPage,
		OUT RvSipSubscriptionStateHeaderHandle* hHeader);

	/***************************************************************************
	* RvSipSubscriptionStateHeaderCopy
	* ------------------------------------------------------------------------
	* General: Copies all fields from a source Subscription-State header object to a
	*          destination Subscription-State header object.
	*          You must construct the destination object before using this function.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hDestination - Handle to the destination Subscription-State header object.
	*    hSource      - Handle to the source Subscription-State header object.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipSubscriptionStateHeaderCopy(
		INOUT  RvSipSubscriptionStateHeaderHandle hDestination,
		IN     RvSipSubscriptionStateHeaderHandle hSource);

	/***************************************************************************
	* RvSipSubscriptionStateHeaderEncode
	* ------------------------------------------------------------------------
	* General: Encodes a Subscription-State header object to a textual Subscription-State
	*          header. The textual header is placed on a page taken from a specified pool.
	*          In order to copy the textual header
	*          from the page to a consecutive buffer, use RPOOL_CopyToExternal().
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* input: hHeader  - Handle to the Subscription-State header object.
	*        hPool    - Handle to the specified memory pool.
	* output: hPage   - The memory page allocated to contain the encoded header.
	*         length  - The length of the encoded information.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipSubscriptionStateHeaderEncode(
		IN    RvSipSubscriptionStateHeaderHandle hHeader,
		IN    HRPOOL                             hPool,
		OUT   HPAGE*                             hPage,
		OUT   RvUint32*                         length);

	/***************************************************************************
	* RvSipSubscriptionStateHeaderParse
	* ------------------------------------------------------------------------
	* General:Parses a SIP textual Subscription-State header—for example,
	*         "Subscription-State: "active";expires=100??
	*          into a Subscription-State header object.
	*         All the textual fields are placed inside the object.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader   - A handle to the Subscription-State header object.
	*    buffer    - Buffer containing a textual Subscription-State header.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipSubscriptionStateHeaderParse(
		IN  RvSipSubscriptionStateHeaderHandle  hHeader,
		IN  RvChar*                            buffer);

	/***************************************************************************
	* RvSipSubscriptionStateHeaderParseValue
	* ------------------------------------------------------------------------
	* General: Parses a SIP textual SubscriptionState header value into an
	*          SubscriptionState header object.
	*          A SIP header has the following grammer:
	*          header-name:header-value. This function takes the header-value part as
	*          a parameter and parses it into the supplied object.
	*          All the textual fields are placed inside the object.
	*          Note: Use the RvSipSubscriptionStateHeaderParse() function to parse
	*          strings that also include the header-name.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader   - The handle to the SubscriptionState header object.
	*    buffer    - The buffer containing a textual SubscriptionState header value.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipSubscriptionStateHeaderParseValue(
		IN RvSipSubscriptionStateHeaderHandle hHeader,
		IN RvChar*               buffer);

	/***************************************************************************
	* RvSipSubscriptionStateHeaderFix
	* ------------------------------------------------------------------------
	* General: Fixes an SubscriptionState header with bad-syntax information.
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
	RVAPI RvStatus RVCALLCONV RvSipSubscriptionStateHeaderFix(
		IN RvSipSubscriptionStateHeaderHandle hHeader,
		IN RvChar*                           pFixedBuffer);

	/*-----------------------------------------------------------------------
	G E T  A N D  S E T  M E T H O D S
	------------------------------------------------------------------------*/

	/***************************************************************************
	* RvSipSubscriptionStateHeaderGetStringLength
	* ------------------------------------------------------------------------
	* General: Some of the Subscription-State header fields are kept in a string format?
	*          for example, the Subscription-State header other params. In order to get
	*          such a field from the Subscription-State header object, your application
	*          should supply an adequate buffer to where the string
	*          will be copied.
	*          This function provides you with the length of the string to
	*          enable you to allocate an appropriate buffer size before calling
	*          the Get function.
	* Return Value: Returns the length of the specified string.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader    - Handle to the Subscription-State header object.
	*  stringName - Enumeration of the string name for which you require the
	*               length.
	***************************************************************************/
	RVAPI RvUint RVCALLCONV RvSipSubscriptionStateHeaderGetStringLength(
		IN  RvSipSubscriptionStateHeaderHandle     hHeader,
		IN  RvSipSubscriptionStateHeaderStringName stringName);


	/***************************************************************************
	* RvSipSubscriptionStateHeaderGetSubstate
	* ------------------------------------------------------------------------
	* General: This function gets the substate eunmuration value of the
	*          subscription-state object. If RVSIP_SUBSCRIPTION_SUBSTATE_OTHER
	*          is returned, you can receive the substate string using
	*          RvSipSubscriptionStateHeaderGetStrSubstate().
	* Return Value: Returns an enumuration value of substate.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader - Handle to the Subscription-State header object.
	***************************************************************************/
	RVAPI RvSipSubscriptionSubstate RVCALLCONV RvSipSubscriptionStateHeaderGetSubstate(
		IN RvSipSubscriptionStateHeaderHandle hHeader);

	/***************************************************************************
	* RvSipSubscriptionStateHeaderGetStrSubstate
	* ------------------------------------------------------------------------
	* General: Copies the substate string from the Subscription-State header into
	*          a given buffer. Use this function when the substate enumeration
	*          returned by RvSipSubscriptionStateHeaderGetSubstate() is
	*          RVSIP_SUBSCRIPTION_SUBSTATE_OTHER.
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
	RVAPI RvStatus RVCALLCONV RvSipSubscriptionStateHeaderGetStrSubstate(
		IN RvSipSubscriptionStateHeaderHandle   hHeader,
		IN RvChar*                       strBuffer,
		IN RvUint                        bufferLen,
		OUT RvUint*                      actualLen);

	/***************************************************************************
	* RvSipSubscriptionStateHeaderSetSubstate
	* ------------------------------------------------------------------------
	* General: Sets the substate field in the Subscription-State header object.
	*          If the enumeration given by eSubstate is RVSIP_SUBSCRIPTION_SUBSTATE_OTHER,
	*          sets the substate string given by strSubstate in the
	*          Subscription-State header object.
	*          Use RVSIP_SUBSCRIPTION_SUBSTATE_OTHER when the substate you wish
	*          to set to the Subscription-State does not have a
	*          matching enumeration value in the RvSipSubscriptionSubstate enumeration.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader    - Handle to the Subscription-State header object.
	*    eSubstate  - The substate enumeration to be set in the Subscription-State
	*               header object. If RVSIP_SUBSCRIPTION_SUBSTATE_UNDEFINED is supplied,
	*               the existing substate is removed from the header.
	*    strSubstate - The substate string to be set in the Subscription-State header.
	*                (relevant when eSubstate is RVSIP_SUBSCRIPTION_SUBSTATE_OTHER).
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipSubscriptionStateHeaderSetSubstate(
		IN  RvSipSubscriptionStateHeaderHandle hHeader,
		IN  RvSipSubscriptionSubstate          eSubstate,
		IN  RvChar                            *strSubstate);

	/***************************************************************************
	* RvSipSubscriptionStateHeaderGetReason
	* ------------------------------------------------------------------------
	* General: This function gets the reason eunmuration value of the
	*          subscription-state object. If RVSIP_SUBSCRIPTION_REASON_OTHER
	*          is returned, you can receive the reason string using
	*          RvSipSubscriptionStateHeaderGetStrReason().
	* Return Value: Returns an enumuration value of substate.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader - Handle to the Subscription-State header object.
	***************************************************************************/
	RVAPI RvSipSubscriptionReason RVCALLCONV RvSipSubscriptionStateHeaderGetReason(
		IN RvSipSubscriptionStateHeaderHandle hHeader);

	/***************************************************************************
	* RvSipSubscriptionStateHeaderGetStrReason
	* ------------------------------------------------------------------------
	* General: Copies the reason string from the Subscription-State header into
	*          a given buffer. Use this function when the reason enumeration
	*          returned by RvSipSubscriptionStateHeaderGetReason() is
	*          RVSIP_SUBSCRIPTION_REASON_OTHER.
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
	RVAPI RvStatus RVCALLCONV RvSipSubscriptionStateHeaderGetStrReason(
		IN RvSipSubscriptionStateHeaderHandle   hHeader,
		IN RvChar*                             strBuffer,
		IN RvUint                              bufferLen,
		OUT RvUint*                            actualLen);

	/***************************************************************************
	* RvSipSubscriptionStateHeaderSetReason
	* ------------------------------------------------------------------------
	* General: Sets the reason field in the Subscription-State header object.
	*          If the enumeration given by eReason is RVSIP_SUBSCRIPTION_REASON_OTHER,
	*          sets the reason string given by strReason in the
	*          Subscription-State header object.
	*          Use RVSIP_SUBSCRIPTION_REASON_OTHER when the substate you wish
	*          to set to the Subscription-State does not have a
	*          matching enumeration value in the RvSipSubscriptionReason enumeration.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader   - Handle to the Subscription-State header object.
	*    eReason   - The reason enumeration to be set in the Subscription-State
	*               header object. If RVSIP_SUBSCRIPTION_REASON_UNDEFINED is supplied,
	*               the existing reason is removed from the header.
	*    strReason - The reason string to be set in the Subscription-State header.
	*                (relevant when eReason is RVSIP_SUBSCRIPTION_REASON_OTHER).
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipSubscriptionStateHeaderSetReason(
		IN  RvSipSubscriptionStateHeaderHandle hHeader,
		IN  RvSipSubscriptionReason            eReason,
		IN  RvChar                            *strReason);

	/***************************************************************************
	* RvSipSubscriptionStateHeaderGetOtherParams
	* ------------------------------------------------------------------------
	* General: Copies the Subscription-State header other params field of the
	*          Subscription-State header object into a given buffer.
	*          Not all the Subscription-State header parameters have separated
	*          fields in the Subscribe-State header object. Parameters with no
	*          specific fields are refered to as other params.
	*          They are kept in the object in one concatenated string in the form?
	*          ”name=value;name=value...?
	*          If the bufferLen is adequate, the function copies the requested parameter into
	*          strBuffer. Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and actualLen
	*          contains the required buffer length.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* input: hHeader    - Handle to the Subscription-State header object.
	*        strBuffer  - Buffer to fill with the requested parameter.
	*        bufferLen  - The length of the buffer.
	* output:actualLen - The length of the requested parameter, + 1 to include a
	*                     NULL value at the end of the parameter.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipSubscriptionStateHeaderGetOtherParams(
		IN RvSipSubscriptionStateHeaderHandle hHeader,
		IN RvChar*                 strBuffer,
		IN RvUint                  bufferLen,
		OUT RvUint*                actualLen);

	/***************************************************************************
	* RvSipSubscriptionStateHeaderSetOtherParams
	* ------------------------------------------------------------------------
	* General:Sets the other params field in the Subscription-State header object.
	*         Not all the Subscription-State header parameters have separated
	*         fields in the Subscription-State header object.
	*         Parameters with no specific fields are refered to as other params.
	*         They are kept in the object in one concatenated string in the form?
	*         ”name=value;name=value...?
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader       - Handle to the Subscription-State header object.
	*    strOtherParam - The extended parameters field to be set in the Subscription-State
	*                  header. If NULL is supplied, the existing extended parameters field
	*                  is removed from the header.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipSubscriptionStateHeaderSetOtherParams(
		IN    RvSipSubscriptionStateHeaderHandle hHeader,
		IN    RvChar *                strOtherParam);

	/***************************************************************************
	* RvSipSubscriptionStateHeaderGetExpiresParam
	* ------------------------------------------------------------------------
	* General: The Subscription-State header may contain an expires parameter.
	*          This function returns the expires parameter value.
	* Return Value: Returns the expires parameter value, UNDEFINED if not exists.
	* ------------------------------------------------------------------------
	* Arguments:
	* input: hHeader   - Handle to the Subscription-State  header object.
	***************************************************************************/
	RVAPI RvInt32 RVCALLCONV RvSipSubscriptionStateHeaderGetExpiresParam(
		IN RvSipSubscriptionStateHeaderHandle hHeader);

	/***************************************************************************
	* RvSipSubscriptionStateHeaderSetExpiresParam
	* ------------------------------------------------------------------------
	* General: Sets an expires parameter in the Subscription-State header object.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader  - Handle to the Subscription-State  header object.
	*    hExpires - Expires value to be set in the Subscription-State header object.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipSubscriptionStateHeaderSetExpiresParam(
		IN    RvSipSubscriptionStateHeaderHandle hHeader,
		IN    RvInt32                           expiresVal);

	/***************************************************************************
	* RvSipSubscriptionStateHeaderGetRetryAfter
	* ------------------------------------------------------------------------
	* General: The Subscription-State header may contain a retry-after parameter.
	*          This function returns this parameter value.
	* Return Value: Returns the retry-after parameter value, UNDEFINED if not exists.
	* ------------------------------------------------------------------------
	* Arguments:
	* input: hHeader   - Handle to the Subscription-State  header object.
	***************************************************************************/
	RVAPI RvInt32 RVCALLCONV RvSipSubscriptionStateHeaderGetRetryAfter(
		IN RvSipSubscriptionStateHeaderHandle hHeader);

	/***************************************************************************
	* RvSipSubscriptionStateHeaderSetRetryAfter
	* ------------------------------------------------------------------------
	* General: Sets a retry-after parameter in the Subscription-State header object.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader  - Handle to the Subscription-State  header object.
	*    hExpires - Retry-after value to be set in the Subscription-State header object.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipSubscriptionStateHeaderSetRetryAfter(
		IN    RvSipSubscriptionStateHeaderHandle hHeader,
		IN    RvInt32                           retryAfterVal);

	/***************************************************************************
	* RvSipSubscriptionStateHeaderGetStrBadSyntax
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
	*          implementation if the message contains a bad SubscriptionState header,
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
	RVAPI RvStatus RVCALLCONV RvSipSubscriptionStateHeaderGetStrBadSyntax(
		IN RvSipSubscriptionStateHeaderHandle hHeader,
		IN RvChar*                 strBuffer,
		IN RvUint                  bufferLen,
		OUT RvUint*                actualLen);
	/***************************************************************************
	* RvSipSubscriptionStateHeaderSetStrBadSyntax
	* ------------------------------------------------------------------------
	* General: Sets a bad-syntax string in the object.
	*          A SIP header has the following grammer:
	*          header-name:header-value. When a header contains a syntax error,
	*          the header-value is kept as a separate "bad-syntax" string.
	*          By using this function you can create a header with "bad-syntax".
	*          Setting a bad syntax string to the header will mark the header as
	*          an invalid syntax header.
	*          You can use his function when you want to send an illegal SubscriptionState header.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader      - The handle to the header object.
	*  strBadSyntax - The bad-syntax string.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipSubscriptionStateHeaderSetStrBadSyntax(
		IN RvSipSubscriptionStateHeaderHandle hHeader,
		IN RvChar*                     strBadSyntax);


#endif /*#ifndef RV_SIP_PRIMITIVES*/

#ifdef __cplusplus
}
#endif

#endif /* RVSIPSUBSSTATEHEADER_H */

