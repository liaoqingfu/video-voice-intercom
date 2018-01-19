/*

NOTICE:
This document contains information that is proprietary to RADVision LTD..
No part of this publication may be reproduced in any form whatsoever without
written prior approval by RADVision LTD..

RADVision LTD. reserves the right to revise this publication and make changes
without obligation to notify any person of such revisions or changes.

*/

/******************************************************************************
*                          RvSipBody.h                                       *
*                                                                            *
* The file defines the methods of the Body object:                           *
* construct, destruct, copy, encode, parse and the ability to access, add    *
* and change it's body parts and Content-Type.                               *
*                                                                            *
*      Author           Date                                                 *
*     ------           -----------                                         *
*     Tamar Barzuza    Aug 2001                                              *
******************************************************************************/

#ifndef RVSIPBODY_H
#define RVSIPBODY_H

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
#include "RvSipCommonTypes.h"


	/*-----------------------------------------------------------------------*/
	/*                   CONSTRUCTORS AND DESTRUCTORS                        */
	/*-----------------------------------------------------------------------*/

	/***************************************************************************
	* RvSipBodyConstructInMsg
	* ------------------------------------------------------------------------
	* General: Constructs a Body object inside a given message object.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* input:  hSipMsg - Handle to the message related to the new Body object.
	* output: hBody   - Handle to the Body object.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipBodyConstructInMsg(
		IN  RvSipMsgHandle        hSipMsg,
		OUT RvSipBodyHandle      *hBody);

	/***************************************************************************
	* RvSipBodyConstructInBodyPart
	* ------------------------------------------------------------------------
	* General: Constructs a Body object inside a given body-part object.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* input:  hBodyPart - Handle to the body-part related to the new Body object.
	* output: hBody - Handle to the Body object.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipBodyConstructInBodyPart(
		IN  RvSipBodyPartHandle  hBodyPart,
		OUT RvSipBodyHandle      *hBody);

	/***************************************************************************
	* RvSipBodyConstruct
	* ------------------------------------------------------------------------
	* General: Constructs and initializes a stand-alone Body object.
	*          The Body object is constructed on a given page taken
	*          from a specified pool. The handle to the new Body object is
	*          returned.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* input:  hMsgMgr   - Handle to the messge manager.
	*         hPool   - Handle to the memory pool that the object will use.
	*         hPage   - Handle to the memory page that the object will use.
	* output: hBody - Handle to the newly constructed Body object.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipBodyConstruct(
		IN  RvSipMsgMgrHandle     hMsgMgr,
		IN  HRPOOL                hPool,
		IN  HPAGE                 hPage,
		OUT RvSipBodyHandle      *hBody);

	/***************************************************************************
	* RvSipBodyCopy
	* ------------------------------------------------------------------------
	* General: Copies all fields from a source Body object to a destination
	*          Body object.
	*          You must construct the destination object before using this
	*          function.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    hDestination - Handle to the destination Body object.
	*    hSource      - Handle to the source Body object.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipBodyCopy(
		INOUT  RvSipBodyHandle hDestination,
		IN     RvSipBodyHandle hSource);

	/***************************************************************************
	* RvSipBodyEncode
	* ------------------------------------------------------------------------
	* General: Encodes a Body object to a textual body.
	*              1. If the body is of type multipart (held as a list
	*              of body parts), each body part is encoded and concatinated to
	*              the textual body. The body parts are separated by a boundary
	*              delimiter line. The boundary delimiter line is created using
	*              the boundary parameter found in the Content-Type of the Body object.
	*              If no boundary is defined for this Body object, a unique
	*              boundary is generated and the boundary delimiter line is
	*              created accordingly.
	*              2. If the body type is other than multipart it is copied, as
	*              is.
	*          The encoded body is placed on a page taken from a
	*          specified pool. In order to copy the encoded body from
	*          the page to a consecutive buffer, use RPOOL_CopyToExternal().
	*          The application must free the allocated page, using
	*          RPOOL_FreePage(). The Allocated page must be freed if and only
	*          if this function returns RV_OK.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:
	*         hBody    - Handle to the Body object.
	*         hPool    - Handle to the specified memory pool.
	* Output:
	*         hPage    - The memory page allocated to contain the encoded object.
	*         length   - The length of the encoded information.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipBodyEncode(
		IN    RvSipBodyHandle      hBody,
		IN    HRPOOL               hPool,
		OUT   HPAGE*               hPage,
		OUT   RvUint32*           length);

	/***************************************************************************
	* RvSipBodyMultipartParse
	* ------------------------------------------------------------------------
	* General:Parses a SIP textual body of type multipart into a Body object.
	*         The given Body object must have a valid Content-Type header
	*         on it headers list. the  Content-Type header must contain
	*         the boundary that was used to create the boundary
	*         delimiter lines that separated the different parts of the body.
	*         The parsing will be made according to this boundary.
	*
	*         ?for example, to parse the following multipart body correctly,
	*         "boundary=unique-boundary-1" must be a parameter of the
	*         Content-Type of the given Body object.
	*         ?-unique-boundary-1
	*          Content-Type: application/SDP; charset=ISO-10646
	*
	*          v=0
	*          o=audet 2890844526 2890842807 5 IN IP4 134.177.64.4
	*          s=SDP seminar
	*          c=IN IP4 MG141.nortelnetworks.com
	*          t= 2873397496 2873404696
	*          m=audio 9092 RTP/AVP 0 3 4
	*
	*          --unique-boundary-1
	*          Content-type:application/QSIG; version=iso
	*
	*          08 02 55 55 05 04 02 90 90 18 03 a1 83 01
	*          70 0a 89 31 34 30 38 34 39 35 35 30 37 32
	*          --unique-boundary-1--?
	*         The body parts are seperated into a list of body parts within the
	*         Body object. The headers list of each body part is parsed within
	*         the appropriate body part object.
	*
	*         To Parse a Body object you can either supply a string of your own,
	*         or you can use the body string within the Body object, if exists.
	*         The second option can be used when the body was received via the
	*         network. The Body object will contain the body string. You can
	*         receive this string using RvSipBodyGetBodyStr. To receive the
	*         length of this string in advance, use RvSipBodyGetBodyStrLength().
	*         After you retrieve the body string you can use
	*         RvSipBodyMultipartParse() to parse it.
	*
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*  Input:
	*      hBody        - A handle to the Body object.
	*      strBody      - The string of the body.
	*      bufLength    - The buffer length.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipBodyMultipartParse(
		IN    RvSipBodyHandle         hBody,
		IN    RvChar                *strBody,
		IN    RvUint                 bufLength);

	/*-----------------------------------------------------------------------
	G E T  A N D  S E T  M E T H O D S
	------------------------------------------------------------------------*/

	/***************************************************************************
	* RvSipBodyGetContentType
	* ------------------------------------------------------------------------
	* General: Gets the Content-Type header from the Body object.
	* Return Value: Returns the Content-Type header handle, or NULL if there
	*               is no Content-Type for this Body object.
	* ------------------------------------------------------------------------
	* Arguments:
	*  Input:
	*        hBody - Handle to the Body object.
	***************************************************************************/
	RVAPI RvSipContentTypeHeaderHandle RVCALLCONV RvSipBodyGetContentType(
		IN RvSipBodyHandle hBody);

	/***************************************************************************
	* RvSipBodySetContentType
	* ------------------------------------------------------------------------
	* General:Sets the Content-Type header in the Body object.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*  Input:
	*        hBody         - Handle to the Body object.
	*        hContentType  - Content-Type header to be set in the Body object.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipBodySetContentType(
		IN  RvSipBodyHandle              hBody,
		IN  RvSipContentTypeHeaderHandle hContentType);

	/***************************************************************************
	* RvSipBodyGetBodyStrLength
	* ------------------------------------------------------------------------
	* General: Get the length of the body string.
	*          NOTE: If the body is of type multipart, it might contain a list
	*                of body parts. The body string and the list of body parts
	*                may not represent the same body, since each of the body
	*                parts can be independently manipulated. You can use this
	*                function only when the Body object does not contain a list
	*                of body parts. If the Body object contains a list of body
	*                parts this function will return 0. In that case you can use
	*                RvSipBodyEncode(). RvSipBodyEncode() will encode the
	*                list of body parts and will return the length of the encoded
	*                string, which represents the length of the body string.
	* Return Value: The length of the body string.
	* ------------------------------------------------------------------------
	* Arguments:
	*  Input:
	*        hBody      - Handle to the Body object.
	***************************************************************************/
	RVAPI RvUint32 RVCALLCONV RvSipBodyGetBodyStrLength(
		IN     RvSipBodyHandle    hBody);

	/***************************************************************************
	* RvSipBodyGetBodyStr
	* ------------------------------------------------------------------------
	* General: Get the string of the body.
	*          NOTE: If the body is of type multipart, it might contain a list
	*                of body parts. The body string and the list of body parts
	*                may not represent the same body, since each of the body
	*                parts can be independently manipulated. If the body object
	*                contains a list of body parts this function will return
	*                RV_ERROR_UNKNOWN. You can only use this function when the body
	*                does not contain a list of body parts. If you would like
	*                to get the body string of a body object in the format of
	*                body parts list, use RvSipBodyEncode() and than
	*                RPOOL_CopyToExternal() method.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:
	*       hBody         - Handle to the body object.
	*       rawBuffer     - The body string of the body object. Note that the
	*                       body string does not necessarily end with '\0'. The
	*                       body string might contain '\0' as part of the body
	*                       string.
	*       bufferLen     - The length of the given buffer.
	* Output:
	*       actualLen     - The actual length of the body string.
	*                       This is also relevant when the buffer was insufficient.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipBodyGetBodyStr(
		IN     RvSipBodyHandle     hBody,
		IN     RvChar            *rawBuffer,
		IN     RvUint32           bufferLen,
		OUT    RvUint32          *actualLen);

	/***************************************************************************
	* RvSipBodySetBodyStr
	* ------------------------------------------------------------------------
	* General: Sets a textual body to the Body object. The textual body is
	*          copied and saved in the Body object.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:
	*       hBody         - Handle to the Body object.
	*       rawBuffer     - The buffer to set to the Body object.
	*     length        - The buffer's length.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipBodySetBodyStr(
		IN  RvSipBodyHandle        hBody,
		IN  RvChar               *rawBuffer,
		IN  RvUint32              length);

	/***************************************************************************
	* RvSipBodyGetBodyPart
	* ------------------------------------------------------------------------
	* General: Gets a body part from the body parts list. The Body object
	*          holds the Body Part objects in a sequential list.
	*          Use the location parameter to specify the location of the body
	*          part you wish to get. When Using the next or prev locatopns
	*          you must supply a relative body part.
	*          For example in order to get the second body part from the list
	*          you must first get the first body part. You should then ask
	*          for the next body part when the first body part serves
	*          as a relative header.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*  Input:
	*        hBody     - Handle of the Body object.
	*        location  - The location in list ?next, previous, first or last.
	*        hRelative - Handle to the current position in the list (a relative
	*                    body part from the list). Supply this value if you choose
	*                    next or previous in the location parameter.
	*  Output:
	*        hBodyPart - Handle to the requested body part.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipBodyGetBodyPart(
		IN  RvSipBodyHandle         hBody,
		IN  RvSipListLocation       location,
		IN  RvSipBodyPartHandle     hRelative,
		OUT RvSipBodyPartHandle    *hBodyPart);

	/***************************************************************************
	* RvSipBodyPushBodyPart
	* ------------------------------------------------------------------------
	* General: Inserts a given body part into the body parts list based on a
	*          given location - first, last, before or after a given relative
	*          element. The body part you supply is copied before it
	*          is inserted into the list. The function returnes the handle to
	*          the body part object that was actually inserted to the list,
	*          which can be used in a following call to this function as the
	*          relative body part.
	* Return Value: Returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:   hBody        - Handle of the Body object.
	*          location     - The location in list ?next, previous, first or
	*                         last.
	*          hBodyPart    - Handle to the body part to be pushed into the
	*                         list.
	*          hRelative    - Handle to the current position in the list (a
	*                         relative body part from the list). Supply this
	*                         value if you chose next or previous in the
	*                         location parameter.
	*  Output:
	*          hNewBodyPart - Handle to a copy of hBodyPart that was inserted
	*                         to the body parts list. Can be used in further
	*                         calls for this function as hRelative.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipBodyPushBodyPart(
		IN   RvSipBodyHandle            hBody,
		IN   RvSipListLocation          location,
		IN   RvSipBodyPartHandle        hBodyPart,
		IN   RvSipBodyPartHandle        hRelative,
		OUT  RvSipBodyPartHandle       *hNewBodyPart);

	/***************************************************************************
	* RvSipBodyRemoveBodyPart
	* ------------------------------------------------------------------------
	* General: Removes a body part from the body parts list.
	*          You should supply this function the handle to the body part you
	*          wish to remove.
	* Return Value: returns RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* input:  hBody     - Handle to the Body object.
	*         hBodyPart - Handle to the body part to be removed.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipBodyRemoveBodyPart(
		IN    RvSipBodyHandle     hBody,
		IN    RvSipBodyPartHandle hBodyPart);


	/***************************************************************************
	* RvSipBodyGetRpoolString
	* ------------------------------------------------------------------------
	* General: Copy the body string from the body object into a given page
	*          from a specified pool. The copied string is not consecutive.
	* Return Value: RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*  Input: hBody     - Handle to the body object.
	*  Input/Output:
	*         pRpoolPtr -  Pointer to a location inside a RPOOL memory object.
	*                      You need to supply only the pool and page. The offset
	*                      where the returned string was located will be returned
	*                      as an output parameter. If the function set the returned 
	*                      offset to UNDEFINED is means that the parameter was 
	*                      not set in the RPOOL memory.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipBodyGetRpoolString(
		IN    RvSipBodyHandle     hBody,
		INOUT RPOOL_Ptr          *pRpoolPtr);


	/***************************************************************************
	* RvSipBodySetRpoolString
	* ------------------------------------------------------------------------
	* General: Sets a  body string into a body
	*          object. The given string is located on an RPOOL memory and is
	*          not consecutive.
	* Return Value: RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	*    Input: hBody     - Handle to the body object.
	*           pRpoolPtr - Pointer to a location inside an rpool where the
	*                       new string is located.
	*           length    - The body length +1 for the terminating '\0' char. 
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipBodySetRpoolString(
		IN    RvSipBodyHandle     hBody,
		IN    RPOOL_Ptr          *pRpoolPtr,
		IN    RvUint32            length);


#endif /*RV_SIP_PRIMITIVES*/

#ifdef __cplusplus
}
#endif
#endif /* RVSIPBODY_H */
