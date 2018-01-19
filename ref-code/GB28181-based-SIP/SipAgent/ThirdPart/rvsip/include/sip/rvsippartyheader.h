/*

NOTICE:
This document contains information that is proprietary to RADVision LTD..
No part of this publication may be reproduced in any form whatsoever without
written prior approval by RADVision LTD..

RADVision LTD. reserves the right to revise this publication and make changes
without obligation to notify any person of such revisions or changes.

*/

/******************************************************************************
*                     RvSipPartyHeader.h                                     *
*                                                                            *
* The file defines the methods of the Party header object                    *
* (for To/From headers):                                                     *
* construct, destruct, copy, encode, parse and the ability to access and     *
* change it's parameters.                                                    *
*                                                                            *
*                                                                            *
*      Author           Date                                                 *
*     ------           ------------                                          *
*      Ofra             Nov.2000                                             *
******************************************************************************/


#ifndef RVSIPPARTYHEADER_H
#define RVSIPPARTYHEADER_H

#ifdef __cplusplus
extern "C" {
#endif

	/*-----------------------------------------------------------------------*/
	/*                        INCLUDE HEADER FILES                           */
	/*-----------------------------------------------------------------------*/
#include "RV_SIP_DEF.h"
#include "RvSipMsgTypes.h"
#include "rpool_API.h"

	/*-----------------------------------------------------------------------*/
	/*                   DECLERATIONS                                        */
	/*-----------------------------------------------------------------------*/
	/*
	* RvSipPartyHeaderStringName
	* ----------------------
	* This enum defines all the header's strings (for getting it's size)
	* Defines all Party header object fields that are kept in the object
	* in a string format.
	*/
	typedef enum
	{
		RVSIP_PARTY_DISPLAY_NAME,
		RVSIP_PARTY_TAG,
		RVSIP_PARTY_OTHER_PARAMS,
		RVSIP_PARTY_BAD_SYNTAX
	}RvSipPartyHeaderStringName;

	/*-----------------------------------------------------------------------*/
	/*                   CONSTRUCTORS AND DESTRUCTORS                        */
	/*-----------------------------------------------------------------------*/


	/***************************************************************************
	* RvSipToHeaderConstructInMsg
	* ------------------------------------------------------------------------
	* General: Constructs a To Party header object inside a given message object.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* input:  hSipMsg - Handle to the message object.
	* output: hHeader - Handle to the newly constructed To Party header object.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipToHeaderConstructInMsg(
		IN  RvSipMsgHandle          hSipMsg,
		OUT RvSipPartyHeaderHandle* hHeader);


	/***************************************************************************
	* RvSipFromHeaderConstructInMsg
	* ------------------------------------------------------------------------
	* General: Constructs a From Party header object inside a given message object.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* input:  hSipMsg - Handle to the message object.
	* output: hHeader - Handle to the newly constructed From Party header object.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipFromHeaderConstructInMsg(
		IN  RvSipMsgHandle          hSipMsg,
		OUT RvSipPartyHeaderHandle* hHeader);

	/***************************************************************************
	* RvSipPartyHeaderConstruct
	* ------------------------------------------------------------------------
	* General: Constructs and initializes a stand-alone Party Header object. The header is
	*          constructed on a given page taken from a specified pool. The handle to the new
	*          header object is returned.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* input:  hMsgMgr - Handle to the Message manager.
	*         hPool   - Handle to the memory pool that the object will use.
	*         hPage   - Handle to the memory page that the object will use.
	* output: hHeader - Handle to the newly constructed Party header object.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipPartyHeaderConstruct(
		IN  RvSipMsgMgrHandle       hMsgMgr,
		IN  HRPOOL                  hPool,
		IN  HPAGE                   hPage,
		OUT RvSipPartyHeaderHandle* hHeader);

	/***************************************************************************
	* RvSipPartyHeaderCopy
	* ------------------------------------------------------------------------
	* General: Copies all fields from a source Party header object to a destination Party header
	*          object.
	*          You must construct the destination object before using this function.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hDestination - Handle to the destination Party header object.
	*    hSource      - Handle to the source Party header object.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipPartyHeaderCopy
		(INOUT RvSipPartyHeaderHandle hDestination,
		IN    RvSipPartyHeaderHandle hSource);


	/***************************************************************************
	* RvSipPartyHeaderSetCompactForm
	* ------------------------------------------------------------------------
	* General: Instructs the header to use the compact header name when the
	*          header is encoded.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* input: hHeader  - Handle to the Party header object.
	*        bIsCompact - specify whether or not to use a compact form
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipPartyHeaderSetCompactForm(
		IN    RvSipPartyHeaderHandle hHeader,
		IN    RvBool                bIsCompact);

	/***************************************************************************
	* RvSipPartyHeaderEncode
	* ------------------------------------------------------------------------
	* General: Encodes a Party header object to a textual Party header. The textual header is
	*          placed on a page taken from a specified pool. In order to copy the textual header
	*          from the page to a consecutive buffer, use RPOOL_CopyToExternal().
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* input: hHeader  - Handle to the contact header object.
	*        hPool    - Handle to the specified memory pool.
	*        isTo     - Indicates whether a Header is a To header—RV_TRUE?or From header?
	*                   RV_FALSE.
	* output: hPage   - The memory page allocated to contain the encoded header.
	*         length  - The length of the encoded information.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipPartyHeaderEncode(
		IN    RvSipPartyHeaderHandle hHeader,
		IN    HRPOOL                 hPool,
		IN    RvBool                isTo,
		OUT   HPAGE*                 hPage,
		OUT   RvUint32*             length);

	/***************************************************************************
	* RvSipPartyHeaderParse
	* ------------------------------------------------------------------------
	* General:Parses a SIP textual Party header—for example, “From:
	*         <sip:charlie@caller.com>;tag=5”—into a Party header object. All the textual
	*         fields are placed inside the object.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader   - A handle to the Party header object.
	*  isTo      - Indicates whether a Header is a To header—RV_TRUE?or From header?
	*              RV_FALSE.
	*    buffer    - Buffer containing a textual Party header.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipPartyHeaderParse(
		IN    RvSipPartyHeaderHandle   hHeader,
		IN    RvBool                  isTo,
		IN    RvChar*                 buffer);
	/***************************************************************************
	* RvSipPartyHeaderParseValue
	* ------------------------------------------------------------------------
	* General: Parses a SIP textual Party header value into an Party header object.
	*          A SIP header has the following grammer:
	*          header-name:header-value. This function takes the header-value part as
	*          a parameter and parses it into the supplied object.
	*          All the textual fields are placed inside the object.
	*          Note: Use the RvSipPartyHeaderParse() function to parse strings
	*          that also include the header-name.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader   - The handle to the Party header object.
	*    buffer    - The buffer containing a textual Party header value.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipPartyHeaderParseValue(
		IN    RvSipPartyHeaderHandle   hHeader,
		IN    RvBool                  isTo,
		IN    RvChar*                 buffer);

	/***************************************************************************
	* RvSipPartyHeaderFix
	* ------------------------------------------------------------------------
	* General: Fixes an Party header with bad-syntax information.
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
	RVAPI RvStatus RVCALLCONV RvSipPartyHeaderFix(
		IN RvSipPartyHeaderHandle hHeader,
		IN RvBool                bIsTo,
		IN RvChar*               pFixedBuffer);

	/***************************************************************************
	* RvSipPartyIsEqual
	* ------------------------------------------------------------------------
	* General:Compares two party header objects. Party header fields are considered equal if
	*         their URIs match and their header parameters match in name and value.
	*         Parameters names and token parameter values are compared ignoring case while
	*         quoted-string parameter values are case-sensitive.
	*         The tag comparison is performed if both header fields have a tag value.
	* Return Value: Returns RV_TRUE if the party header objects being compared are equal.
	*               Otherwise, the function returns RV_FALSE.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader      - Handle to the party header object.
	*    hOtherHeader - Handle to the party header object with which a comparison is being made.
	***************************************************************************/
	RVAPI RvBool RVCALLCONV RvSipPartyIsEqual(const RvSipPartyHeaderHandle hHeader,
		const RvSipPartyHeaderHandle hOtherHeader);


	/*-----------------------------------------------------------------------
	G E T  A N D  S E T  M E T H O D S
	------------------------------------------------------------------------*/
	/***************************************************************************
	* RvSipPartyHeaderGetStringLength
	* ------------------------------------------------------------------------
	* General: Some of the Party header fields are kept in a string format—for example, the
	*          Party header display name. In order to get such a field from the Party header
	*          object, your application should supply an adequate buffer to where the string
	*          will be copied.
	*          This function provides you with the length of the string to enable you to allocate
	*          an appropriate buffer size before calling the Get function.
	* Return Value: Returns the length of the specified string.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader    - Handle to the Party header object.
	*  stringName - Enumeration of the string name for which you require the length.
	***************************************************************************/
	RVAPI RvUint RVCALLCONV RvSipPartyHeaderGetStringLength(
		IN  RvSipPartyHeaderHandle     hHeader,
		IN  RvSipPartyHeaderStringName stringName);

	/***************************************************************************
	* RvSipPartyHeaderGetTag
	* ------------------------------------------------------------------------
	* General: Copies the Tag parameter of the Party header object into a given buffer.
	*          If the bufferLen is adequate, the function copies the requested parameter into
	*          strBuffer. Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and actualLen
	*          contains the required buffer length.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* input: hHeader    - Handle to the header object.
	*        strBuffer  - Buffer to include the requested parameter.
	*        bufferLen  - The length of the buffer.
	* output:actualLen - The length of the requested parameter, + 1 to include a NULL value at the end
	*                     of the parameter.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipPartyHeaderGetTag(
		IN RvSipPartyHeaderHandle   hHeader,
		IN RvChar*                 strBuffer,
		IN RvUint                  bufferLen,
		OUT RvUint*                actualLen);

	/***************************************************************************
	* RvSipPartyHeaderSetTag
	* ------------------------------------------------------------------------
	* General: Sets the tag field in the Party header object
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader - Handle to the party header object.
	*    strTag  - The Tag field to be set in the Party header object. If NULL is supplied, the
	*            existing display name is removed from the header.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipPartyHeaderSetTag(
		IN    RvSipPartyHeaderHandle hHeader,
		IN    RvChar *              strTag);


	/***************************************************************************
	* RvSipPartyHeaderGetDisplayName
	* ------------------------------------------------------------------------
	* General: Copies the display name from the Party header into a given buffer.
	*          If the bufferLen is adequate, the function copies the requested parameter into
	*          strBuffer. Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and actualLen
	*          contains the required buffer length.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* input: hHeader    - Handle to the header object.
	*        strBuffer  - Buffer to fill with the requested parameter.
	*        bufferLen  - The length of the buffer.
	* output:actualLen - The length of the requested parameter, + 1 to include a NULL value at the end
	*                     of the parameter.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipPartyHeaderGetDisplayName(
		IN RvSipPartyHeaderHandle   hHeader,
		IN RvChar*                 strBuffer,
		IN RvUint                  bufferLen,
		OUT RvUint*                actualLen);

	/***************************************************************************
	* RvSipPartyHeaderSetDisplayName
	* ------------------------------------------------------------------------
	* General: Sets the display name in the Party header object.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader        - Handle to the header object.
	*    strDisplayName - The display name to be set in the Party header. If NULL is supplied, the existing
	*                   display name is removed from the header.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipPartyHeaderSetDisplayName(
		IN    RvSipPartyHeaderHandle hHeader,
		IN    RvChar *              strDisplayName);

	/***************************************************************************
	* RvSipPartyHeaderGetAddrSpec
	* ------------------------------------------------------------------------
	* General: The Address Spec field is held in the Party header object as an Address object.
	*          This function returns the handle to the Address object.
	* Return Value: Returns a handle to the Address Spec object, or NULL if the Address Spec
	*               object does not exist.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader - Handle to the Party header object.
	***************************************************************************/
	RVAPI RvSipAddressHandle RVCALLCONV RvSipPartyHeaderGetAddrSpec
		(IN RvSipPartyHeaderHandle hHeader);

	/***************************************************************************
	* RvSipPartyHeaderSetAddrSpec
	* ------------------------------------------------------------------------
	* General: Sets the Address Spec address object in the Contact header object.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader   - Handle to the Contact header object.
	*  hAddrSpec - Handle to the Address Spec address object to be set in the Party header object.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipPartyHeaderSetAddrSpec
		(IN    RvSipPartyHeaderHandle hHeader,
		IN    RvSipAddressHandle     hAddrSpec);

	/***************************************************************************
	* RvSipPartyHeaderGetOtherParams
	* ------------------------------------------------------------------------
	* General: Copies the Party header other params field of the Party header object into a
	*          given buffer.
	*          Not all the Party header parameters have separated fields in the Party header
	*          object. Parameters with no specific fields are refered to as other params. They
	*          are kept in the object in one concatenated string in the form?
	*          ”name=value;name=value...?
	*          If the bufferLen is adequate, the function copies the requested parameter into
	*          strBuffer. Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and actualLen
	*          contains the required buffer length.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* input: hHeader    - Handle to the Party header object.
	*        strBuffer  - Buffer to fill with the requested parameter.
	*        bufferLen  - The length of the buffer.
	* output:actualLen - The length of the requested parameter, + 1 to include a NULL value at the end of
	*                     the parameter.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipPartyHeaderGetOtherParams(
		IN RvSipPartyHeaderHandle   hHeader,
		IN RvChar*                 strBuffer,
		IN RvUint                  bufferLen,
		OUT RvUint*                actualLen);

	/***************************************************************************
	* RvSipPartyHeaderSetOtherParams
	* ------------------------------------------------------------------------
	* General: Sets the other params field in the Party header object.
	*          Not all the Party header parameters have separated fields in the Party header
	*          object. Parameters with no specific fields are refered to as other params. They
	*          are kept in the object in one concatenated string in the form?
	*          ”name=value;name=value...?
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader        - Handle to the party header object.
	*    strOtherParams - The Other Params string to be set in the Party header. If NULL is supplied, the
	*                   existing Other Params field is removed from the header.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipPartyHeaderSetOtherParams(
		IN    RvSipPartyHeaderHandle hHeader,
		IN    RvChar *              strOtherParams);

	/***************************************************************************
	* RvSipPartyHeaderGetType
	* ------------------------------------------------------------------------
	* General: returns the tpye of a party header:
	*          RVSIP_HEADERTYPE_TO or RVSIP_HEADERTYPE_FROM
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader        - the handle to the party header object.
	*  peType         - The type of the header object (to / from)
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipPartyHeaderGetType(IN RvSipPartyHeaderHandle hHeader,
		OUT RvSipHeaderType*      peType);

	/***************************************************************************
	* RvSipPartyHeaderSetType
	* ------------------------------------------------------------------------
	* General: Sets the type of a party header:
	*          RVSIP_HEADERTYPE_TO or RVSIP_HEADERTYPE_FROM
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader        - the handle to the party header object.
	*  eType          - The type of the header object (to / from)
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipPartyHeaderSetType(IN RvSipPartyHeaderHandle hHeader,
		IN RvSipHeaderType        eType);

	/***************************************************************************
	* RvSipPartyHeaderGetStrBadSyntax
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
	*          implementation if the message contains a bad Party header,
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
	RVAPI RvStatus RVCALLCONV RvSipPartyHeaderGetStrBadSyntax(
		IN RvSipPartyHeaderHandle hHeader,
		IN RvChar*                 strBuffer,
		IN RvUint                  bufferLen,
		OUT RvUint*                actualLen);

	/***************************************************************************
	* RvSipPartyHeaderSetStrBadSyntax
	* ------------------------------------------------------------------------
	* General: Sets a bad-syntax string in the object.
	*          A SIP header has the following grammer:
	*          header-name:header-value. When a header contains a syntax error,
	*          the header-value is kept as a separate "bad-syntax" string.
	*          By using this function you can create a header with "bad-syntax".
	*          Setting a bad syntax string to the header will mark the header as
	*          an invalid syntax header.
	*          You can use his function when you want to send an illegal Party header.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader      - The handle to the header object.
	*  strBadSyntax - The bad-syntax string.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipPartyHeaderSetStrBadSyntax(
		IN RvSipPartyHeaderHandle hHeader,
		IN RvChar*                     strBadSyntax);


#ifndef RV_SIP_PRIMITIVES
	/***************************************************************************
	* RvSipPartyHeaderGetRpoolString
	* ------------------------------------------------------------------------
	* General: Copy a string parameter from the Party header into a given page
	*          from a specified pool. The copied string is not consecutive.
	* Return Value: RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    Input: hSipPartyHeader - Handle to the Party header object.
	*           eStringName   - The string the user wish to get
	*  Input/Output:
	*         pRpoolPtr     - pointer to a location inside an rpool. You need to
	*                         supply only the pool and page. The offset where the
	*                         returned string was located will be returned as an
	*                         output patameter.
	*                         If the function set the returned offset to
	*                         UNDEFINED is means that the parameter was not
	*                         set to the Party header object.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipPartyHeaderGetRpoolString(
		IN    RvSipPartyHeaderHandle      hSipPartyHeader,
		IN    RvSipPartyHeaderStringName  eStringName,
		INOUT RPOOL_Ptr                     *pRpoolPtr);

	/***************************************************************************
	* RvSipPartyHeaderSetRpoolString
	* ------------------------------------------------------------------------
	* General: Sets a string into a specified parameter in the Party header
	*          object. The given string is located on an RPOOL memory and is
	*          not consecutive.
	* Return Value: RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    Input: hSipPartyHeader - Handle to the Party header object.
	*           eStringName   - The string the user wish to set
	*         pRpoolPtr     - pointer to a location inside an rpool where the
	*                         new string is located.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipPartyHeaderSetRpoolString(
		IN    RvSipPartyHeaderHandle      hSipPartyHeader,
		IN    RvSipPartyHeaderStringName  eStringName,
		IN    RPOOL_Ptr                 *pRpoolPtr);

#endif /*#ifndef RV_SIP_PRIMITIVES*/

#ifdef __cplusplus
}
#endif

#endif /* RVSIPPARTYHEADER_H */
