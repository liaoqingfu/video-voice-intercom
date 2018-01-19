/*

NOTICE:
This document contains information that is proprietary to RADVision LTD..
No part of this publication may be reproduced in any form whatsoever without
written prior approval by RADVision LTD..

RADVision LTD. reserves the right to revise this publication and make changes
without obligation to notify any person of such revisions or changes.

*/

/******************************************************************************
*                             RvSipContactHeader.h                           *
*                                                                            *
* The file defines the methods of the Contact header object:                 *
* construct, destruct, copy, encode, parse and the ability to access and     *
* change it's parameters.                                                    *
*                                                                            *
*      Author           Date                                                 *
*     ------           ------------                                          *
*      Ofra             Nov.2000                                             *
******************************************************************************/
#ifndef RVSIPCONTACTHEADER_H
#define RVSIPCONTACTHEADER_H

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
	* RvSipContactHeaderStringName
	* ----------------------------
	* This enum defines all the header's strings (for getting it's size)
	* Defines all Contact header object fields that are kept in the 
	* object in a string format.
	*/
	typedef enum
	{
		RVSIP_CONTACT_DISPLAYNAME,
		RVSIP_CONTACT_OTHER_PARAMS,
		RVSIP_CONTACT_QVAL,
		RVSIP_CONTACT_BAD_SYNTAX
	}RvSipContactHeaderStringName;

	/*-----------------------------------------------------------------------*/
	/*                   CONSTRUCTORS AND DESTRUCTORS                        */
	/*-----------------------------------------------------------------------*/

	/***************************************************************************
	* RvSipContactHeaderConstructInMsg
	* ------------------------------------------------------------------------
	* General: Constructs a Contact header object inside a given message object. The header is
	*          kept in the header list of the message. You can choose to insert the header either
	*          at the head or tail of the list.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* input:  hSipMsg          - Handle to the message object.
	*         pushHeaderAtHead - Boolean value indicating whether the header should be pushed to the head of the
	*                            list—RV_TRUE—or to the tail—RV_FALSE.
	* output: hHeader          - Handle to the newly constructed Contact header object.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipContactHeaderConstructInMsg(
		IN  RvSipMsgHandle            hSipMsg,
		IN  RvBool                   pushHeaderAtHead,
		OUT RvSipContactHeaderHandle* hHeader);

	/***************************************************************************
	* RvSipContactHeaderConstruct
	* ------------------------------------------------------------------------
	* General: Constructs and initializes a stand-alone Contact Header object. The header is
	*          constructed on a given page taken from a specified pool. The handle to the new
	*          header object is returned.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* input:  hMsgMgr - Handle to the Message manager.
	*         hPool   - Handle to the memory pool that the object will use.
	*         hPage   - Handle to the memory page that the object will use.
	* output: hHeader - Handle to the newly constructed contact header object.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipContactHeaderConstruct(
		IN  RvSipMsgMgrHandle         hMsgMgr,
		IN  HRPOOL                    hPool,
		IN  HPAGE                     hPage,
		OUT RvSipContactHeaderHandle* hHeader);

	/***************************************************************************
	* RvSipContactHeaderCopy
	* ------------------------------------------------------------------------
	* General: Copies all fields from a source Contact header object to a destination Contact
	*          header object.
	*          You must construct the destination object before using this function.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hDestination - Handle to the destination Contact header object.
	*    hSource      - Handle to the destination Contact header object.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipContactHeaderCopy(
		INOUT RvSipContactHeaderHandle hDestination,
		IN    RvSipContactHeaderHandle hSource);
	/***************************************************************************
	* RvSipContactHeaderSetCompactForm
	* ------------------------------------------------------------------------
	* General: Instructs the header to use the compact header name when the
	*          header is encoded.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* input: hHeader  - Handle to the Allow header object.
	*        bIsCompact - specify whether or not to use a compact form
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipContactHeaderSetCompactForm(
		IN    RvSipContactHeaderHandle hHeader,
		IN    RvBool                bIsCompact);

	/***************************************************************************
	* RvSipContactHeaderEncode
	* ------------------------------------------------------------------------
	* General: Encodes a contact header object to a textual Contact header. The textual header
	*          is placed on a page taken from a specified pool. In order to copy the textual
	*          header from the page to a consecutive buffer, use RPOOL_CopyToExternal().
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* input: hHeader  - Handle to the contact header object.
	*        hPool    - Handle to the specified memory pool.
	* output: hPage   - The memory page allocated to contain the encoded header.
	*         length  - The length of the encoded information.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipContactHeaderEncode(
		IN    RvSipContactHeaderHandle hHeader,
		IN    HRPOOL                   hPool,
		OUT   HPAGE*                   hPage,
		OUT   RvUint32*               length);

	/***************************************************************************
	* RvSipContactHeaderParse
	* ------------------------------------------------------------------------
	* General: Parses a SIP textual Contact header—for example,
	*          “Contact:sip:172.20.5.3:5060”—into a contact header object. All the textual
	*          fields are placed inside the object.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader   - A handle to the Contact header object.
	*    buffer    - Buffer containing a textual Contact header.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipContactHeaderParse(
		IN    RvSipContactHeaderHandle hHeader,
		IN    RvChar*                 buffer);

	/***************************************************************************
	* RvSipContactHeaderParseValue
	* ------------------------------------------------------------------------
	* General: Parses a SIP textual Contact header value into an Contact header object.
	*          A SIP header has the following grammer:
	*          header-name:header-value. This function takes the header-value part as
	*          a parameter and parses it into the supplied object.
	*          All the textual fields are placed inside the object.
	*          Note: Use the RvSipContactHeaderParse() function to parse strings that also
	*          include the header-name.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader   - The handle to the Contact header object.
	*    buffer    - The buffer containing a textual Contact header value.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipContactHeaderParseValue(
		IN    RvSipContactHeaderHandle hHeader,
		IN    RvChar*                 buffer);

	/***************************************************************************
	* RvSipContactHeaderFix
	* ------------------------------------------------------------------------
	* General: Fixes an Contact header with bad-syntax information.
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
	RVAPI RvStatus RVCALLCONV RvSipContactHeaderFix(
		IN RvSipContactHeaderHandle hHeader,
		IN RvChar*                 pFixedBuffer);

	/*-----------------------------------------------------------------------
	G E T  A N D  S E T  M E T H O D S
	------------------------------------------------------------------------*/
	/***************************************************************************
	* RvSipContactHeaderGetStringLength
	* ------------------------------------------------------------------------
	* General: Some of the Contact header fields are kept in a string format—for example, the
	*          contact header display name. In order to get such a field from the Contact header
	*          object, your application should supply an adequate buffer to where the string
	*          will be copied.
	*          This function provides you with the length of the string to enable you to allocate
	*          an appropriate buffer size before calling the Get function.
	* Return Value: Returns the length of the specified string.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader    - Handle to the Contact header object.
	*  stringName - Enumeration of the string name for which you require the length.
	***************************************************************************/
	RVAPI RvUint RVCALLCONV RvSipContactHeaderGetStringLength(
		IN  RvSipContactHeaderHandle     hHeader,
		IN  RvSipContactHeaderStringName stringName);

	/***************************************************************************
	* RvSipContactHeaderGetDisplayName
	* ------------------------------------------------------------------------
	* General: Copies the display name from the Contact header into a given buffer.
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
	RVAPI RvStatus RVCALLCONV RvSipContactHeaderGetDisplayName(
		IN RvSipContactHeaderHandle hHeader,
		IN RvChar*                 strBuffer,
		IN RvUint                  bufferLen,
		OUT RvUint*                actualLen);

	/***************************************************************************
	* RvSipContactHeaderSetDisplayName
	* ------------------------------------------------------------------------
	* General:Sets the display name in the Contact header object.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader      - Handle to the header object.
	*    strDisplayName - The display name to be set in the Contact header. If NULL is supplied, the
	*                 existing display name is removed from the header.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipContactHeaderSetDisplayName(
		IN    RvSipContactHeaderHandle hHeader,
		IN    RvChar*                 strDisplayName);

	/***************************************************************************
	* RvSipContactHeaderGetAddrSpec
	* ------------------------------------------------------------------------
	* General: The Address Spec field is held in the contact header object as an Address object.
	*          This function returns the handle to the address object.
	* Return Value: Returns a handle to the Address Spec object, or NULL if the Address Spec
	*               object does not exist.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader - Handle to the Contact header object.
	***************************************************************************/
	RVAPI RvSipAddressHandle RVCALLCONV RvSipContactHeaderGetAddrSpec(
		IN RvSipContactHeaderHandle hHeader);

	/***************************************************************************
	* RvSipContactHeaderSetAddrSpec
	* ------------------------------------------------------------------------
	* General: Sets the Address Spec parameter in the Contact header object.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader   - Handle to the Contact header object.
	*    hAddrSpec - Handle to the Address Spec Address object. If NULL is supplied, the existing
	*              Address Spec is removed from the Contact header.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipContactHeaderSetAddrSpec(
		IN    RvSipContactHeaderHandle hHeader,
		IN    RvSipAddressHandle       pAddrSpec);


	/***************************************************************************
	* RvSipContactHeaderGetExpires
	* ------------------------------------------------------------------------
	* General: The Contact header contains an Expires header object. This function returns the
	*          handle to the Expires header object.
	* Return Value: Returns the handle to the Expires header object, or NULL if the Expires header
	*               object does not exist.
	* ------------------------------------------------------------------------
	* Arguments:
	* input: hHeader   - Handle to the Contact header object.
	***************************************************************************/
	RVAPI RvSipExpiresHeaderHandle RVCALLCONV RvSipContactHeaderGetExpires(
		IN RvSipContactHeaderHandle hHeader);

	/***************************************************************************
	* RvSipContactHeaderSetExpires
	* ------------------------------------------------------------------------
	* General: Sets the Expires header object in the Contact header object.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader  - Handle to the Contact header object.
	*    hExpires - Handle to the Expires header object to be set in the Contact header object.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipContactHeaderSetExpires(
		IN    RvSipContactHeaderHandle hHeader,
		IN    RvSipExpiresHeaderHandle hExpires);

	/***************************************************************************
	* RvSipContactHeaderGetQVal
	* ------------------------------------------------------------------------
	* General: Copies the 'q' parameter from the Contact header into a given buffer.
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
	RVAPI RvStatus RVCALLCONV RvSipContactHeaderGetQVal(
		IN RvSipContactHeaderHandle hHeader,
		IN RvChar*                 strBuffer,
		IN RvUint                  bufferLen,
		OUT RvUint*                actualLen);

	/***************************************************************************
	* RvSipContactHeaderSetQVal
	* ------------------------------------------------------------------------
	* General: Sets the 'q' parameter value in the Contact header object.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader  - Handle to the Contact header object.
	*    strQVal  - The value of the offset of the 'q' parameter to be set.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipContactHeaderSetQVal(
		IN    RvSipContactHeaderHandle hHeader,
		IN    RvChar                 *strQVal);

	/***************************************************************************
	* RvSipContactHeaderGetAction
	* ------------------------------------------------------------------------
	* General: The Contact header contains the Action type. This function
	*          returns this type.
	* Return Value: Returns the type of the action in the Contact header.
	* ------------------------------------------------------------------------
	* Arguments:
	* input: hHeader   - Handle to the Contact header object.
	***************************************************************************/
	RVAPI RvSipContactAction RVCALLCONV RvSipContactHeaderGetAction(
		IN RvSipContactHeaderHandle hHeader);

	/***************************************************************************
	* RvSipContactHeaderSetAction
	* ------------------------------------------------------------------------
	* General: Sets the action type in the Contact header object.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader  - Handle to the Contact header object.
	*    action   - The action type to be set.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipContactHeaderSetAction(
		IN    RvSipContactHeaderHandle hHeader,
		IN    RvSipContactAction       action);

	/***************************************************************************
	* RvSipContactHeaderGetOtherParams
	* ------------------------------------------------------------------------
	* General: Copies the Contact header other params field of the Contact header object into a
	*          given buffer.
	*          Not all the Contact header parameters have separated fields in the Contact
	*          header object. Parameters with no specific fields are refered to as other params.
	*          They are kept in the object in one concatenated string in the form?
	*          ”name=value;name=value...?
	*          If the bufferLen is adequate, the function copies the requested parameter into
	*          strBuffer. Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and actualLen
	*          contains the required buffer length.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* input: hHeader    - Handle to the Contact header object.
	*        strBuffer  - Buffer to fill with the requested parameter.
	*        bufferLen  - The length of the buffer.
	* output:actualLen - The length of the requested parameter, + 1 to include a NULL value at the end of
	*                     the parameter.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipContactHeaderGetOtherParams(
		IN RvSipContactHeaderHandle hHeader,
		IN RvChar*                 strBuffer,
		IN RvUint                  bufferLen,
		OUT RvUint*                actualLen);

	/***************************************************************************
	* RvSipContactHeaderSetOtherParams
	* ------------------------------------------------------------------------
	* General:Sets the other params field in the Contact header object.
	*         Not all the Contact header parameters have separated fields in the Contact
	*         header object. Parameters with no specific fields are refered to as other params.
	*         They are kept in the object in one concatenated string in the form?
	*         ”name=value;name=value...?
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader         - Handle to the Contact header object.
	*    strContactParam - The extended parameters field to be set in the Contact header. If NULL is
	*                    supplied, the existing extended parameters field is removed from the header.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipContactHeaderSetOtherParams(
		IN    RvSipContactHeaderHandle hHeader,
		IN    RvChar *                strContactParam);


	/***************************************************************************
	* RvSipContactHeaderSetStar
	* ------------------------------------------------------------------------
	* General: A Contact header can be in the form of "Contact: * ". This function defines the
	*          Contact header as an Asterisk Contact header.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader      - Handle of the Contact header object.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipContactHeaderSetStar(
		IN    RvSipContactHeaderHandle hHeader);


	/***************************************************************************
	* RvSipContactHeaderIsStar
	* ------------------------------------------------------------------------
	* General:Determines whether or not the contact header object contains an Asterisk (*).
	*         This means that the header is of the form "Contact: * ".
	* Return Value: Returns RV_TRUE if the Contact header is of the form "Contact: * ". Otherwise,
	*               the function returns RV_FALSE.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader      - Handle of the Contact header object.
	***************************************************************************/
	RVAPI RvBool RVCALLCONV RvSipContactHeaderIsStar(
		IN RvSipContactHeaderHandle hHeader);


	/***************************************************************************
	* RvSipContactHeaderGetStrBadSyntax
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
	*          implementation if the message contains a bad Contact header,
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
	RVAPI RvStatus RVCALLCONV RvSipContactHeaderGetStrBadSyntax(
		IN RvSipContactHeaderHandle hHeader,
		IN RvChar*                 strBuffer,
		IN RvUint                  bufferLen,
		OUT RvUint*                actualLen);

	/***************************************************************************
	* RvSipContactHeaderSetStrBadSyntax
	* ------------------------------------------------------------------------
	* General: Sets a bad-syntax string in the object.
	*          A SIP header has the following grammer:
	*          header-name:header-value. When a header contains a syntax error,
	*          the header-value is kept as a separate "bad-syntax" string.
	*          By using this function you can create a header with "bad-syntax".
	*          Setting a bad syntax string to the header will mark the header as
	*          an invalid syntax header.
	*          You can use his function when you want to send an illegal Contact header.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hHeader      - The handle to the header object.
	*  strBadSyntax - The bad-syntax string.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipContactHeaderSetStrBadSyntax(
		IN RvSipContactHeaderHandle hHeader,
		IN RvChar*                 strBadSyntax);


	/***************************************************************************
	* RvSipContactHeaderGetRpoolString
	* ------------------------------------------------------------------------
	* General: Copy a string parameter from the Contact header into a given page
	*          from a specified pool. The copied string is not consecutive.
	* Return Value: RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    Input: hSipContactHeader - Handle to the Contact header object.
	*           eStringName   - The string the user wish to get
	*  Input/Output:
	*         pRpoolPtr     - pointer to a location inside an rpool. You need to
	*                         supply only the pool and page. The offset where the
	*                         returned string was located will be returned as an
	*                         output patameter.
	*                         If the function set the returned offset to
	*                         UNDEFINED is means that the parameter was not
	*                         set to the Contact header object.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipContactHeaderGetRpoolString(
		IN    RvSipContactHeaderHandle      hSipContactHeader,
		IN    RvSipContactHeaderStringName  eStringName,
		INOUT RPOOL_Ptr                     *pRpoolPtr);


	/***************************************************************************
	* RvSipContactHeaderSetRpoolString
	* ------------------------------------------------------------------------
	* General: Sets a string into a specified parameter in the Contact header
	*          object. The given string is located on an RPOOL memory and is
	*          not consecutive.
	* Return Value: RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    Input: hSipContactHeader - Handle to the Contact header object.
	*           eStringName   - The string the user wish to set
	*         pRpoolPtr     - pointer to a location inside an rpool where the
	*                         new string is located.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipContactHeaderSetRpoolString(
		IN    RvSipContactHeaderHandle      hSipContactHeader,
		IN    RvSipContactHeaderStringName  eStringName,
		IN    RPOOL_Ptr                 *pRpoolPtr);



#ifdef __cplusplus
}
#endif

#endif /* RVSIPCONTACTHEADER_H */


