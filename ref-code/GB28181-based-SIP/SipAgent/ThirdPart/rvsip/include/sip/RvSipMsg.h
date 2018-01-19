/*

NOTICE:
This document contains information that is proprietary to RADVision LTD..
No part of this publication may be reproduced in any form whatsoever without
written prior approval by RADVision LTD..

RADVision LTD. reserves the right to revise this publication and make changes
without obligation to notify any person of such revisions or changes.

*/

/******************************************************************************
 *                        RvSipMsg.h                                          *
 *                                                                            *
 * The file defines the methods of the Message object.                        *
 * The message object represents a SIP message and holds all SIP message      *
 * information including start-line, headers and SDP body.                    *
 * Message object functions enable you to construct, destruct, copy, encode,  *
 * parse, access and change Message object parameters and manage the list     *
 * of headers in message objects.                                             *
 * list of headers.                                                           *
 *                                                                            *
 *      Author           Date                                                 *
 *     ------           ------------                                          *
 *      Ofra             Nov.2000                                             *
 ******************************************************************************/



#ifndef RVSIPMSG_H
#define RVSIPMSG_H

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
 * RvSipMessageStringName
 * ----------------------------
 * This enum defines all the message's strings (for getting it's size)
 * Defines all Message object fields that are kept in the object 
 * in a string format.
 */
typedef enum
{
    RVSIP_MSG_REQUEST_METHOD,
    RVSIP_MSG_RESPONSE_PHRASE,
    RVSIP_MSG_CALL_ID,
    RVSIP_MSG_CONTENT_TYPE,
    RVSIP_MSG_BODY,
    RVSIP_MSG_BAD_SYNTAX_START_LINE
}RvSipMessageStringName;

/*-----------------------------------------------------------------------*/
/*                   CONSTRUCTORS AND DESTRUCTORS                        */
/*-----------------------------------------------------------------------*/

/***************************************************************************
 * RvSipMsgConstruct
 * ------------------------------------------------------------------------
 * General: Constructs SIP message object. The object is constructed on a
 *          page taken from a given memory pool.
 * Return Value: RV_OK or RV_ERROR_OUTOFRESOURCES.
 * ------------------------------------------------------------------------
 * Arguments:
 *  input:
 *      hMsgMgr - Handle to the message manager.
 *      hPool   - Handle to the memory pool. The Construct() function uses a page
 *                from this pool for the newly created message object.
 *  output:
 *        hSipMsg - Handle to the new message object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMsgConstruct(IN  RvSipMsgMgrHandle hMsgMgr,
                                             IN  HRPOOL          hPool,
                                             OUT RvSipMsgHandle* hSipMsg);

/***************************************************************************
 * RvSipMsgDestruct
 * ------------------------------------------------------------------------
 * General: Destructor. Destroys the message object and frees all the object
 *          resources.
 * Return Value: none.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hSipMsg - Handle to the message object to destruct.
 ***************************************************************************/
RVAPI void RVCALLCONV RvSipMsgDestruct(IN  RvSipMsgHandle  hSipMsg);


/***************************************************************************
 * RvSipMsgCopy
 * ------------------------------------------------------------------------
 * General: Copies all fields from a source message object to a destination
 *          message object.You should construct the destination message object
 *          before using this function.
 * Return Value: RV_OK, RV_ERROR_OUTOFRESOURCES, RV_ERROR_INVALID_HANDLE.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hDestination - Handle to the destination message to which values
 *                         are copied.
 *          hSource      - Handle of the source msg.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMsgCopy(INOUT RvSipMsgHandle hDestination,
                                        IN    RvSipMsgHandle hSource);

/***************************************************************************
 * RvSipMsgEncode
 * ------------------------------------------------------------------------
 * General: Encodes a message object to a textual SIP message.
 *          The textual SIP message is placed on a page taken from a given
 *          memory pool. In order to copy the message from the page to a
 *          consecutive buffer, use RPOOL_CopyToExternal().
 *          The application must free the allocated page, using RPOOL_FreePage().
 *          The allocated page must be freed only if this function
 *          returns RV_OK.
 * Return Value: RV_OK, RV_ERROR_UNKNOWN, RV_ERROR_BADPARAM, RV_ERROR_OUTOFRESOURCES.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hSipMsg - Handle to the message to encode.
 *          hPool   - Handle to a pool.
 * Output:     hPage   - The memory page allocated to hold the encoded message.
 *          length  - The length of the encoded message.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMsgEncode(IN  RvSipMsgHandle hSipMsg,
                                          IN  HRPOOL         hPool,
                                          OUT HPAGE*         hPage,
                                          OUT RvUint32*     length);

/***************************************************************************
 * RvSipMsgParse
 * ------------------------------------------------------------------------
 * General: Parses a SIP textual message into a message object.
 *          All the textual fields are placed inside the object.
 *          Note that the given message buffer must be ended with two CRLF.
 *          one CRLF must separate between headers in the message.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hMsg      - A handle to the message object.
 *    buffer    - Buffer containing a textual msg ending with two CRLFs.
 *  bufferLen - Length of buffer.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMsgParse(IN RvSipMsgHandle hMsg,
                                         IN RvChar*       buffer,
                                         IN RvInt32       bufferLen);
/*-----------------------------------------------------------------------
                         G E T  A N D  S E T  M E T H O D S
 ------------------------------------------------------------------------*/
/***************************************************************************
 * RvSipMsgGetStringLength
 * ------------------------------------------------------------------------
 * General: Some of the Message fields are kept in a string format—for
 *          example, the reason phrase of a response message. In order to get
 *          such a field from the Message object, your application should
 *          supply an adequate buffer to where the string will be copied.
 *          This function provides you with the length of the string to enable
 *          you to allocate an appropriate buffer size before calling the
 *          Get function.
 *          NOTE: 
 *                If the message body is of type multipart it might be
 *                represented as a list of body parts, and not as a string. In
 *                order to retrieve the body string length the body object must
 *                be encoded if it is presented as a list of body
 *                parts. This function will encode the message body on a
 *                temporary memory page when ever the massage body object
 *                contains a list of body parts (in order to calculate the
 *                message body string length). If this function did not
 *                succeed to encode the message body (Error occured while
 *                encoding), 0 is returned and an appropriate ERROR can be
 *                found in the log.
 * Return Value: The length.
 * ------------------------------------------------------------------------
 * Arguments:
 *  Input:
 *       hHeader    - Handle to the message object.
 *     stringName - Enumeration of the string name for which you require the length.
 ***************************************************************************/
RVAPI RvUint RVCALLCONV RvSipMsgGetStringLength(
                                      IN  RvSipMsgHandle            hSipMsg,
                                      IN  RvSipMessageStringName    stringName);

/***************************************************************************
 * RvSipMsgGetMsgType
 * ------------------------------------------------------------------------
 * General: Gets the message type—request, response or undefined.
 * Return Value: Returns the enumeration of the message type.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:    hSipMsg - Handle to the message object.
 ***************************************************************************/
RVAPI RvSipMsgType RVCALLCONV RvSipMsgGetMsgType(IN const RvSipMsgHandle hSipMsg);


/*        START LINE FUNCTIONS */

/***************************************************************************
 * RvSipMsgGetRequestMethod
 * ------------------------------------------------------------------------
 * General: Gets the method type enumeration from the message object request
 *          line. If this function returns RVSIP_METHOD_OTHER, call
 *          RvSipMsgGetStrRequestMethod() to get the method in a string format.
 * Return Value: Returns the request method type.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hSipMsg    - Handle to the message object.
 ***************************************************************************/
RVAPI RvSipMethodType RVCALLCONV RvSipMsgGetRequestMethod(
                                                 IN  RvSipMsgHandle   hSipMsg);

/***************************************************************************
 * RvSipMsgGetStrRequestMethod
 * ------------------------------------------------------------------------
 * General: Copies the method type string from the message object request
 *          line into a given buffer. Use this function if RvSipMsgGetRequestMethod()
 *          returns RVSIP_METHOD_OTHER. If the bufferLen is adequate, the
 *          function copies the parameter into the strBuffer.
 *          Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and the actualLen
 *          parameter contains the required buffer length.
 * Return Value: RV_OK or RV_ERROR_INSUFFICIENT_BUFFER.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hSipMsg   - Handle to the message object.
 *        strBuffer - buffer to fill with the requested parameter.
 *        bufferLen - the length of the buffer.
 * output:actualLen - The length of the requested parameter, + 1 to
 *                     include a NULL value at the end of the parameter.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMsgGetStrRequestMethod(
                                               IN  RvSipMsgHandle   hSipMsg,
                                               IN  RvChar*         strBuffer,
                                               IN  RvUint          bufferLen,
                                               OUT RvUint*         actualLen);

/***************************************************************************
 * RvSipMsgSetMethodInRequestLine
 * ------------------------------------------------------------------------
 * General: Sets the method type in the request line of the message object.
 *          The function gets an enumeration and string as input. The string
 *          is set as method only if the enumeration is RVSIP_METHOD_OTHER.
 *          Otherwise, the string is ignored.
 * Return Value: RV_OK,
 *               RV_ERROR_UNKNOWN - If the startLine of the message is not requestLine.
 *               RV_ERROR_OUTOFRESOURCES - If didn't manage to allocate space for
 *                            setting strMethod.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hSipMsg - Handle of a message object.
 *            eRequsetMethod -Request method type to set in the message.
 *           strMethod - A textual string which indicates the method type
 *                      when eRequsetMethod is RVSIP_METHOD_OTHER.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMsgSetMethodInRequestLine(
                                             IN    RvSipMsgHandle  hSipMsg,
                                             IN    RvSipMethodType eRequsetMethod,
                                             IN    RvChar*        strMethod);


/***************************************************************************
 * RvSipMsgGetRequestUri
 * ------------------------------------------------------------------------
 * General: Gets the request URI address object handle.
 * Return Value: Returns a handle to the URI address object or NULL if no
 *               URI address exists.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hSipMsg - Handle to a message object.
 ***************************************************************************/
RVAPI RvSipAddressHandle RVCALLCONV RvSipMsgGetRequestUri(IN RvSipMsgHandle hSipMsg);


/***************************************************************************
 * RvSipMsgSetRequestUri
 * ------------------------------------------------------------------------
 * General: Sets the request URI address in the message object request line.
 * Return Value: RV_OK, RV_ERROR_OUTOFRESOURCES, RV_ERROR_INVALID_HANDLE.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hSipMsg - Handle to a message object.
 *         hSipUrl - Handle to an address object with the request URI.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMsgSetRequestUri(IN    RvSipMsgHandle     hSipMsg,
                                                 IN    RvSipAddressHandle hSipUrl);

/***************************************************************************
 * RvSipMsgGetStatusCode
 * ------------------------------------------------------------------------
 * General: Gets the response code from the message object start-line.
 * Return Value: Returns a response code or UNDEFINED if there is no response
 *               code or the message object represents a request message.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hSipMsg - Handle of a message object.
 ***************************************************************************/
RVAPI RvInt16 RVCALLCONV RvSipMsgGetStatusCode(IN RvSipMsgHandle hSipMsg);

/***************************************************************************
 * RvSipMsgSetStatusCode
 * ------------------------------------------------------------------------
 * General: Sets a status code in the message object status line.
 *          This will set the message object to represent a response message.
 * Return Value: RV_OK,
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hSipMsg - Handle to a message object.
 *         code    - status code to be set in the message object.
 *         insertDefaultReasonPhrase - Determines whether or not to insert
 *                     a default reason phrase into the status line.
 *                     the reason phrase is set according to the code number.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMsgSetStatusCode(IN    RvSipMsgHandle hSipMsg,
                                                 IN    RvInt16       code,
                                                 IN    RvBool        insertDefaultReasonPhrase);

/***************************************************************************
 * RvSipMsgGetReasonPhrase
 * ------------------------------------------------------------------------
 * General: Copies the reason phrase from the message object status line
 *          into a given buffer. If the bufferLen size adequate, the
 *          function copies the parameter into the strBuffer. Otherwise,
 *          it returns RV_ERROR_INSUFFICIENT_BUFFER and the actualLen param contains
 *          the required buffer length.
 * Return Value: RV_OK or RV_ERROR_INSUFFICIENT_BUFFER.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hSipMsg   - Handle of the message object.
 *        strBuffer - buffer to fill with the requested parameter.
 *        bufferLen - the length of the buffer.
 * output:actualLen - The length of the requested parameter, + 1 to include
 *                     a NULL value at the end of the parameter.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMsgGetReasonPhrase(
                                               IN  RvSipMsgHandle hSipMsg,
                                               IN  RvChar*       strBuffer,
                                               IN  RvUint        bufferLen,
                                               OUT RvUint*       actualLen);

/***************************************************************************
 * RvSipMsgSetReasonPhrase
 * ------------------------------------------------------------------------
 * General: Sets the reason phrase in the message object status line.
 * Return Value:  RV_OK, RV_ERROR_OUTOFRESOURCES, RV_ERROR_INVALID_HANDLE.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hSipMsg - Handle of a message object.
 *         strReasonPhrase - Reason phrase to be set in the message object.
 *                           If NULL is supplied, the existing
 *                           reason phrase of the message is removed
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMsgSetReasonPhrase(IN RvSipMsgHandle hSipMsg,
                                                  IN RvChar*        strReasonPhrase);

/***************************************************************************
 * RvSipMsgGetHeader
 * ------------------------------------------------------------------------
 * General: Gets a header from the header list. The message object holds most
 *          headers in a sequential list except, To, From, CallId, Cseq,
 *          ContentLength and ContentType headers.
 *          The function returns the handle to the requested header as a void
 *          pointer. You should check the pHeaderType parameter and cast the
 *          return value to the appropriate header handle.
 *          Note - The RvSipMsgGetHeaderExt() function is an extension of this
 *                 function
 * Return Value: Returns the header handle as void*, or NULL if there is no header
 *               to retrieve.
 * ------------------------------------------------------------------------
 * Arguments:
 *  input:
 *      hSipMsg   - Handle of the message object.
 *      location  - The location on list—next, previous, first or last.
 *      hListElem - Handle to the current position in the list. Supply this
 *                  value if you chose next or previous in the location parameter.
 *                  This is also an output parameter and will be set with a link
 *                  to requested header in the list.
 *  output:
 *      hListElem - Handle to the current position in the list. Supply this
 *                  value if you chose next or previous in the location parameter.
 *                  This is also an output parameter and will be set with a link
 *                  to requested header in the list.
 *      pHeaderType - The type of the retrieved header.
 ***************************************************************************/
RVAPI void* RVCALLCONV RvSipMsgGetHeader(
                                     IN    RvSipMsgHandle             hSipMsg,
                                     IN    RvSipHeadersLocation       location,
                                     INOUT RvSipHeaderListElemHandle* hListElem,
                                     OUT   RvSipHeaderType*           pHeaderType);

/***************************************************************************
 * RvSipMsgGetHeaderByType
 * ------------------------------------------------------------------------
 * General: Gets a header by type from the header list. The message object
 *          holds most headers in a sequential list except, To, From, CallId,
 *          Cseq, ContentLength and ContentType headers.
 *          The function returns the handle to the requested header as a void
 *          pointer. You should cast the return value to the header type you
 *          requested.
 *          Note - The RvSipMsgGetHeaderByTypeExt() function is an extension of 
 *                 this function
 * Return Value:Returns the header handle as void*, or NULL if there is no
 *               header to retrieve.
 * ------------------------------------------------------------------------
 * Arguments:
 *  input:
 *      hSipMsg     - Handle of the message object.
 *      eHeaderType - The header type to be retrieved.
 *      location    - The location on list—next, previous, first or last.
 *      hListElem - Handle to the current position in the list. Supply this
 *                  value if you chose next or previous in the location parameter.
 *                  This is also an output parameter and will be set with a link
 *                  to requested header in the list.
 *  output:
 *      hListElem - Handle to the current position in the list. Supply this
 *                  value if you chose next or previous in the location parameter.
 *                  This is also an output parameter and will be set with a link
 *                  to requested header in the list.
 ***************************************************************************/
RVAPI void* RVCALLCONV RvSipMsgGetHeaderByType(
                                 IN    RvSipMsgHandle               hSipMsg,
                                 IN    RvSipHeaderType              eHeaderType,
                                 IN    RvSipHeadersLocation         location,
                                 INOUT RvSipHeaderListElemHandle*   hListElem);

/***************************************************************************
 * RvSipMsgGetHeaderByName
 * ------------------------------------------------------------------------
 * General: Gets a header by name from the header list.
 *          The message object holds most headers in a sequential list except,
 *          To, From, CallId, Cseq, ContentLength and ContentType headers.
 *          This function should be used only for headers of type
 *          RVSIP_HEADERTYPE_OTHER.
 *          Note - The RvSipMsgGetHeaderByNameExt() function is an extension of
 *                 this function 
 * Return Value: Returns the Other header handle, or NULL if no Other header
 *                handle with the same name exists.
 * ------------------------------------------------------------------------
 * Arguments:
 *  input:
 *      hSipMsg   - Handle of the message object.
 *      strName   - The header name to be retrieved.
 *      location    - The location on list—next, previous, first or last.
 *      hListElem - Handle to the current position in the list. Supply this
 *                  value if you chose next or previous in the location parameter.
 *                  This is also an output parameter and will be set with a link
 *                  to requested header in the list.
 *  output:
 *      hListElem - Handle to the current position in the list. Supply this
 *                  value if you chose next or previous in the location parameter.
 *                  This is also an output parameter and will be set with a link
 *                  to requested header in the list.
 ***************************************************************************/
RVAPI RvSipOtherHeaderHandle RVCALLCONV RvSipMsgGetHeaderByName(
                                 IN    RvSipMsgHandle             hSipMsg,
                                 IN    RvChar*                   strName,
                                 IN    RvSipHeadersLocation       location,
                                 INOUT RvSipHeaderListElemHandle* hListElem);

/***************************************************************************
  * RvSipMsgGetHeaderExt
  * ------------------------------------------------------------------------
  * General: Gets a header from the header list. The message object holds most
  *          headers in a sequential list except, To, From, CallId, Cseq,
  *          ContentLength and ContentType headers.
  *          The function returns the handle to the requested header as a void
  *          pointer. You should check the pHeaderType parameter and cast the
  *          return value to the appropriate header handle.
  *          The header list can hold both valid syntax and bad syntax headers.
  *          Using the eOption parameter you should specify whether you wish to get
  *          any type of header or only headers with valid syntax.
  *          Note: this function extends the functionality of
  *                RvSipMsgGetHeader function.
  * Return Value: Returns the header handle as void*, or NULL if there is no header
  *               to retrieve.
  * ------------------------------------------------------------------------
  * Arguments:
  *  input:
  *      hSipMsg   - Handle of the message object.
  *      location  - The location on list: next, previous, first or last.
  *      eOption   - Specifies whether the application wish to get Only legal syntax headers,
  *                  or any header (legal and illegal headers)
  *      hListElem - Handle to the current position in the list. Supply this
  *                  value if you chose next or previous in the location parameter.
  *                  This is also an output parameter and will be set with a link
  *                  to requested header in the list.
  *  output:
  *      hListElem - Handle to the current position in the list. Supply this
  *                  value if you chose next or previous in the location parameter.
  *                  This is also an output parameter and will be set with a link
  *                  to requested header in the list.
  *      pHeaderType  - The type of the retrieved header.
  ***************************************************************************/
RVAPI void* RVCALLCONV RvSipMsgGetHeaderExt(
                                IN    RvSipMsgHandle                hSipMsg,
                                IN    RvSipHeadersLocation          location,
                                IN    RvSipMsgHeadersOption         eOption,
                                INOUT RvSipHeaderListElemHandle*    hListElem,
                                OUT   RvSipHeaderType*              pHeaderType);

/***************************************************************************
  * RvSipMsgGetHeaderByTypeExt
  * ------------------------------------------------------------------------
  * General: Gets a header by type from the header list. The message object
  *          holds most headers in a sequential list except, To, From, CallId,
  *          Cseq, ContentLength and ContentType headers.
  *          The function returns the handle to the requested header as a void
  *          pointer. You should cast the return value to the header type you
  *          requested.
  *          The header list can hold both valid syntax and bad syntax headers.
  *          Using the eOption parameter you should specify whether you wish to get
  *          any type of header or only headers with valid syntax.
  *          Note: this function extends the functionality of
  *                RvSipMsgGetHeaderByType function.
  * Return Value:Returns the header handle as void*, or NULL if there is no
  *               header to retrieve.
  * ------------------------------------------------------------------------
  * Arguments:
  *  input:
  *      hSipMsg   - Handle of the message object.
  *      eHeaderType - The header type to be retrieved.
  *      location  - The location on list-next, previous, first or last.
  *      eOption   - Specifies whether the application wish to get only legal syntax headers,
  *                  or any header (legal and illegal headers)
  *      hListElem - Handle to the current position in the list. Supply this
  *                  value if you chose next or previous in the location parameter.
  *                  This is also an output parameter and will be set with a link
  *                  to requested header in the list.
  *  output:
  *      hListElem - Handle to the current position in the list. Supply this
  *                  value if you chose next or previous in the location parameter.
  *                  This is also an output parameter and will be set with a link
  *                  to requested header in the list.
  ***************************************************************************/
RVAPI void* RVCALLCONV RvSipMsgGetHeaderByTypeExt(
                                IN    RvSipMsgHandle             hSipMsg,
                                IN    RvSipHeaderType            eHeaderType,
                                IN    RvSipHeadersLocation       location,
                                IN    RvSipMsgHeadersOption      eOption,
                                INOUT RvSipHeaderListElemHandle* hListElem);

/***************************************************************************
  * RvSipMsgGetHeaderByNameExt
  * ------------------------------------------------------------------------
  * General:
  *          Gets a header by name from the header list.
  *          The message object holds most headers in a sequential list except,
  *          To, From, CallId, Cseq, ContentLength and ContentType headers.
  *          This function should be used only for headers of type
  *          RVSIP_HEADERTYPE_OTHER.
  *          The header list can hold both valid syntax and bad syntax headers.
  *          Using the eOption parameter you should specify whether you wish to get
  *          any type of header or only headers with valid syntax.
  *          Note: this function extends the functionality of
  *                RvSipMsgGetHeaderByName function.
  * Return Value: Returns the Other header handle, or NULL if no Other header
  *                handle with the same name exists.
  * ------------------------------------------------------------------------
  * Arguments:
  *  input:
  *      hSipMsg   - Handle of the message object.
  *      strName   - The header name to be retrieved.
  *      location  - The location on list-next, previous, first or last.
  *      eOption   - Specifies whether the application wish to get only legal syntax headers,
  *                  or any header (legal and illegal headers)
  *      hListElem - Handle to the current position in the list. Supply this
  *                  value if you chose next or previous in the location parameter.
  *                  This is also an output parameter and will be set with a link
  *                  to requested header in the list.
  *  output:
  *      hListElem - Handle to the current position in the list. Supply this
  *                  value if you chose next or previous in the location parameter.
  *                  This is also an output parameter and will be set with a link
  *                  to requested header in the list.
  ***************************************************************************/
RVAPI RvSipOtherHeaderHandle RVCALLCONV RvSipMsgGetHeaderByNameExt(
                                    IN    RvSipMsgHandle             hSipMsg,
                                    IN    RvChar*                   strName,
                                    IN    RvSipHeadersLocation       location,
                                    IN    RvSipMsgHeadersOption      eOption,
                                    INOUT RvSipHeaderListElemHandle* hListElem);

/***************************************************************************
* RvSipMsgGetBadSyntaxHeader
* ------------------------------------------------------------------------
* General: Gets a header with a syntax error from the message.
*          The message object holds most headers in a sequential list.
*          To, From, CallId, Cseq, ContentLength and ContentType headers are held separately.
*          This function scans all headers in message object, (The ones that are in the header
*          list and the ones that are not) and retrieves only headers with syntax errors.
*          This function treats all headers as if they were located in one virtual list.
*          The virtual list includes the headers that are in the header list and the headers
*          that are not.
*          The function returns the handle to the requested header as a void
*          pointer. You should check the pHeaderType parameter and cast the
*          return value to the appropriate header handle.
*
* Return Value: Returns the header handle as void*, or NULL if there is no header
*               to retrieve.
* ------------------------------------------------------------------------
* Arguments:
*  input:
*      hSipMsg   - Handle of the message object.
*      location  - The location on the list: next, previous, first or last.
*      hListElem - Handle to the current position in the list. Supply this
*                  value if you chose next or previous in the location parameter.
*                  This is also an output parameter and will be set with a link
*                  to requested header in the list.
*  output:
*      hListElem - Handle to the current position in the list. Supply this
*                  value if you chose next or previous in the location parameter.
*                  This is also an output parameter and will be set with a link
*                  to requested header in the list.
*      pHeaderType - The type of the retrieved header.
***************************************************************************/
RVAPI void* RVCALLCONV RvSipMsgGetBadSyntaxHeader(
                                     IN    RvSipMsgHandle                hSipMsg,
                                     IN    RvSipHeadersLocation          location,
                                     INOUT RvSipHeaderListElemHandle*    hListElem,
                                     OUT   RvSipHeaderType*              pHeaderType);

/***************************************************************************
 * RvSipMsgPushHeader
 * ------------------------------------------------------------------------
 * General: Inserts a given header into the header list based on a given
 *          location. For example, first, last, before or after a given
 *          element. The message object holds most headers in a sequential
 *          list except, To, From, CallId, Cseq, ContentLength and
 *          ContentType headers. The header you supply is copied before it
 *          is inserted into the list. The pNewHeader output parameter
 *          contains the handle to the actual header pushed into the list.
 *          You should use this handle to refer to the header pushed into
 *          the list.
 * Return Value: RV_OK, RV_ERROR_OUTOFRESOURCES, RV_ERROR_INVALID_HANDLE, RV_ERROR_BADPARAM.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:      hSipMsg     - Handle of the message object.
 *             location    - The location on list—next, previous, first or last.
 *             pHeader     - Handle to the header pushed into the list.
 *             eHeaderType - Type of the header to be pushed.
 *      hListElem - Handle to the current position in the list. Supply this
 *                  value if you chose next or previous in the location parameter.
 *                  This is also an output parameter and will be set with a link
 *                  to requested header in the list.
 *  output:
 *      hListElem - Handle to the current position in the list. Supply this
 *                  value if you chose next or previous in the location parameter.
 *                  This is also an output parameter and will be set with a link
 *                  to requested header in the list.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMsgPushHeader(
                                    IN      RvSipMsgHandle                hSipMsg,
                                    IN      RvSipHeadersLocation          location,
                                    IN      void*                         pHeader,
                                    IN      RvSipHeaderType               eHeaderType,
                                    INOUT   RvSipHeaderListElemHandle*    hListElem,
                                    OUT     void**                        pNewHeader);


/***************************************************************************
 * RvSipMsgRemoveHeaderAt
 * ------------------------------------------------------------------------
 * General: Removes an header from the header list. The message object holds
 *          most headers in a sequential list except, To, From, CallId, Cseq,
 *          ContentLength and ContentType headers.
 *          You should supply this function with the list element of the
 *          header you wish to remove.
 * Return Value: RV_OK,RV_ERROR_INVALID_HANDLE.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hSipMsg - Handle to the message object.
 *           hListElem - Handle to the list element to be removed.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMsgRemoveHeaderAt(
                                      IN    RvSipMsgHandle            hSipMsg,
                                      IN    RvSipHeaderListElemHandle hListElem);

/***************************************************************************
 * RvSipMsgConstructHeaderInMsgByType
 * ------------------------------------------------------------------------
 * General: The function constructs a header in message, according to it's type.
 *
 * Return Value: RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hMsg -    Handle to the message.
 *          eType -   Type of the header to construct.
 *          pushHeaderAtHead - Boolean value indicating whether the header should
 *                            be pushed to the head of the list (RV_TRUE),
 *                            or to the tail (RV_FALSE).
 * output:  phHeader   - Handle to the header structure.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMsgConstructHeaderInMsgByType(
                                          IN    RvSipMsgHandle  hMsg,
                                          IN    RvSipHeaderType eType,
                                          IN    RvBool          bPushHeaderAtHead,
                                          OUT   void**          phHeader);

/***************************************************************************
 * RvSipMsgEncodeHeaderByType
 * ------------------------------------------------------------------------
 * General: Obsolete function - calls to RvSipHeaderEncode.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMsgEncodeHeaderByType(IN    RvSipHeaderType eType,
                                                    IN    void*          pHeader,
                                                    IN    RvSipMsgMgrHandle hMsgMgr,
                                                    IN    HRPOOL         hPool,
                                                    OUT   HPAGE*         hPage,
                                                    OUT   RvUint32*     length);

/***************************************************************************
 * RvSipMsgParseHeaderByType
 * ------------------------------------------------------------------------
 * General: Obsolete function - calls to RvSipHeaderParse.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMsgParseHeaderByType(
                                          IN    RvSipMsgMgrHandle hMsgMgr,
                                          IN    RvSipHeaderType eType,
                                          IN    void*           hHeader,
                                          IN    RvChar*        buffer);

/*        "To" HEADERS FUNCTIONS      */

/***************************************************************************
 * RvSipMsgGetToHeader
 * ------------------------------------------------------------------------
 * General: Gets the Handle to the To header object from the message object.
 * Return Value: Returns RvSipPartyHeaderHandle, or NULL if the message does
 *               not contain a To header.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hSipMsg - Handle to a message object.
 ***************************************************************************/
RVAPI RvSipPartyHeaderHandle RVCALLCONV RvSipMsgGetToHeader(IN RvSipMsgHandle hSipMsg) ;

/***************************************************************************
 * RvSipMsgSetToHeader
 * ------------------------------------------------------------------------
 * General: Sets a To header in the message object. If there is no To header
 *          in the message, the function constructs a To header.
 * Return Value: RV_OK,RV_ERROR_OUTOFRESOURCES, RV_ERROR_INVALID_HANDLE.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hSipMsg   - Handle to the message object.
 *    hToHeader - Handle to the To header to be set. If a NULL is supplied,
 *              the existing To header is removed from the message.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMsgSetToHeader(IN    RvSipMsgHandle         hSipMsg,
                                               IN    RvSipPartyHeaderHandle hToHeader);

/*        "FROM" HEADERS FUNCTIONS        */

/***************************************************************************
 * RvSipMsgGetFromHeader
 * ------------------------------------------------------------------------
 * General: Gets a handle to the From header object from the message object.
 * Return Value: MsgPartyHeader handle, or NULL if the message does not
 *               contain a From header.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hSipMsg - Handle to a message object.
 ***************************************************************************/
RVAPI RvSipPartyHeaderHandle RVCALLCONV RvSipMsgGetFromHeader(IN RvSipMsgHandle hSipMsg);

/***************************************************************************
 * RvSipMsgSetFromHeader
 * ------------------------------------------------------------------------
 * General: Sets a From header in the message object. If no From header exists
 *          in the message, the function constructs a From header.
 * Return Value: RV_OK,RV_ERROR_OUTOFRESOURCES, RV_ERROR_INVALID_HANDLE.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hSipMsg     - Handle to a message object.
 *    hFromHeader - Handle to the From header to be set. If a NULL value is
 *                 supplied, the existing From header is removed from the
 *                 message.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMsgSetFromHeader(IN    RvSipMsgHandle         hSipMsg,
                                                IN    RvSipPartyHeaderHandle hFromHeader);

/*        CONTENT LENGTH HEADERS FUNCTIONS    */

/***************************************************************************
 * RvSipMsgGetContentLengthHeader
 * ------------------------------------------------------------------------
 * General:Gets the Content Length of the message object. The content
 *         length indicates the size of the body string.
 *         NOTE:  If the body is of type multipart and holds a list
 *                of Body Parts this function will return UNDEFINED.
 *                To receive the Content-Length of a multipart body
 *                use RvSipMsgGetStringLength() with body enumeration.
 * Return Value: Returns content length or UNDEFINED if no body is set in
 *               the message object.
 * ------------------------------------------------------------------------
 * Arguments:
 *  Input:
 *        hSipMsg - Handle to the message object.
 ***************************************************************************/
RVAPI RvInt32 RVCALLCONV RvSipMsgGetContentLengthHeader(
                                               IN RvSipMsgHandle hSipMsg);

/***************************************************************************
 * RvSipMsgSetContentLengthHeader
 * ------------------------------------------------------------------------
 * General: Sets a Content Length value in the message object. The content
 *          length indicates the size of the message body.
 *          NOTE: If the body is of type multipart and holds a list
 *                of Body Parts objects this function will return RV_ERROR_UNKNOWN.
 *                In this case the content length is determine by the size of
 *                the encoded Body-Part list.
 * Return Value: RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *  Input:
 *        hSipMsg - Handle to the message object.
 *        contentLen - The Content Length value to be set.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMsgSetContentLengthHeader(
                                              IN    RvSipMsgHandle  hSipMsg,
                                              IN    RvInt32        contentLen);

/*        "CSEQ" HEADERS FUNCTIONS      */

/***************************************************************************
 * RvSipMsgGetCSeqHeader
 * ------------------------------------------------------------------------
 * General: Gets the Handle to the Cseq header object from the message object.
 * Return Value: Returns the CSeq header handle, or NULL if no CSeq Header
 *               handle exists.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hSipMsg - Handle to a message object.
 ***************************************************************************/
RVAPI RvSipCSeqHeaderHandle RVCALLCONV RvSipMsgGetCSeqHeader(
                                               IN RvSipMsgHandle hSipMsg);

/***************************************************************************
 * RvSipMsgSetCSeqHeader
 * ------------------------------------------------------------------------
 * General: Sets a CSeq header in the message object.
 *          If there is no CSeq header in the message, the function
 *          constructs one.
 * Return Value: RV_OK, RV_ERROR_OUTOFRESOURCES, RV_ERROR_INVALID_HANDLE.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hSipMsg - Handle of a message object.
 *    hCSeqHeader - Handle of the CSEQ header to beset. if NULL value is
 *                supplied, the existing CSeq header will be removed from the
 *                message.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMsgSetCSeqHeader(
                                         IN    RvSipMsgHandle        hSipMsg,
                                         IN    RvSipCSeqHeaderHandle hCSeqHeader);

/*        "CALL-ID" HEADERS FUNCTIONS      */

/***************************************************************************
 * RvSipMsgGetCallIdHeader
 * ------------------------------------------------------------------------
 * General: Copies the message object Call-ID into a given buffer.
 *          If the bufferLen size is adequate, the function copies the Call-ID
 *          into the strBuffer. Otherwise, the function returns
 *          RV_ERROR_INSUFFICIENT_BUFFER and the actualLen parameter contains the
 *          required buffer length.
 * Return Value: RV_OK or RV_ERROR_INSUFFICIENT_BUFFER.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hSipMsg   - Handle to the message object.
 *        strBuffer - Buffer to fill with the requested parameter.
 *        bufferLen - The length of the buffer.
 * output:actualLen - The length of the requested parameter, + 1 to include
 *                     a NULL value at the end of the parameter.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMsgGetCallIdHeader(
                                           IN RvSipMsgHandle     hSipMsg,
                                           IN RvChar*           strBuffer,
                                           IN RvUint            bufferLen,
                                           OUT RvUint*          actualLen);

/***************************************************************************
 * RvSipMsgSetCallIdHeader
 * ------------------------------------------------------------------------
 * General: Sets a Call-ID in the message object.
 * Return Value: RV_OK, RV_ERROR_OUTOFRESOURCES, RV_ERROR_INVALID_HANDLE.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hSipMsg   - Handle to the message object.
 *    strCallId - The new Call-ID string to be set in the message object.
 *              If a NULL value is supplied, the existing Call-ID is removed
 *              from the message.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMsgSetCallIdHeader(IN    RvSipMsgHandle hSipMsg,
                                                   IN    RvChar*       strCallId);

/*        "CONTENT-TYPE" HEADERS FUNCTIONS               */

/***************************************************************************
 * RvSipMsgGetContentTypeHeader
 * ------------------------------------------------------------------------
 * General:  Copies the Content-Type of the message object into a given buffer.
 *           If the bufferLen size is adequate, the function copies the
 *           Content-Type, into the strBuffer. Otherwise, the function returns
 *           RV_ERROR_INSUFFICIENT_BUFFER and the actualLen param contains the
 *           required buffer length.
 * Return Value: RV_OK or RV_ERROR_INSUFFICIENT_BUFFER.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hSipMsg   - Handle to the message object.
 *        strBuffer - Buffer to fill with the requested parameter.
 *        bufferLen - The length of the buffer.
 * output:actualLen - The length of the requested parameter, + 1 to include
 *                     a NULL value at the end of the parameter.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMsgGetContentTypeHeader(
                                                IN RvSipMsgHandle     hSipMsg,
                                                IN RvChar*           strBuffer,
                                                IN RvUint            bufferLen,
                                                OUT RvUint*          actualLen);

/***************************************************************************
 * RvSipMsgSetContentTypeHeader
 * ------------------------------------------------------------------------
 * General: Sets a Content-Type string in the message object.
 * Return Value: RV_OK,RV_ERROR_OUTOFRESOURCES, RV_ERROR_INVALID_HANDLE.
 * ------------------------------------------------------------------------
 * Arguments:RvStatus
 *    hSipMsg      - Handle to a message object.
 *    pContentType - The ContentType string to be set in the message object.
 *                 If a NULL value is supplied, the existing ContentType
 *                 header is removed from the message.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMsgSetContentTypeHeader(
                                                IN    RvSipMsgHandle hSipMsg,
                                                IN    RvChar*       pContentType);

/* BODY FUNCTIONS */

/***************************************************************************
 * RvSipMsgGetBody
 * ------------------------------------------------------------------------
 * General: Copies the body from the message object into a given buffer.
 *          If the bufferLen is adequate, the function copies the message
 *          body into strBuffer. Otherwise, the function returns
 *          RV_ERROR_INSUFFICIENT_BUFFER and actualLen contains the required
 *          buffer length.
 *          NOTE: 
 *                If the message body is of type multipart it might be
 *                represented as a list of body parts, and not as a string. If
 *                the body contains a list of body parts, in order
 *                to retrieve the body string, the body object must be encoded.
 *                This function will encode the message body on a
 *                temporary memory page when ever the body object contains a
 *                list of body parts. The encoded body string will be copied
 *                to the supplied buffer, and the temporary page will be
 *                freed.
 * Return Value: RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hSipMsg   - Handle to the message object.
 *        strBuffer - buffer to fill with the requested parameter.
 *        bufferLen - the length of the buffer.
 * output:actualLen - The length of the requested parameter, + 1 to include
 *                     a NULL value at the end of the parameter.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMsgGetBody(IN RvSipMsgHandle hSipMsg,
                                           IN RvChar*       strBuffer,
                                           IN RvUint        bufferLen,
                                           OUT RvUint*      actualLen);

/***************************************************************************
 * RvSipMsgSetBody
 * ------------------------------------------------------------------------
 * General: Sets a body in the message object and updates the content-length
 *          field with the body length.
 *          Remember to update the Content-Type value according to the new
 *          body.
 *          NOTE: You can use RvSipMsgSetBody() ONLY when the body
 *                string does not contain NULL characters. To set body string
 *                that contains NULL characters you must first get the Body
 *                object from the message using RvSipMsgGetBodyObject().
 *                Then you can use the RvSipBodySetBodyStr() to set the
 *                body string. You can also use RvSipbodyConstructInMsg()
 *                to construct a new Body object in the message object.
 * Return Value: RV_OK, RV_ERROR_OUTOFRESOURCES, RV_ERROR_INVALID_HANDLE.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hSipMsg - Handle to the message object.
 *            strBody - SIP message body to be set in the message object.
 *                    If NULL is supplied, the existing body is removed and
 *                    the message object contentLength is set to zero.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMsgSetBody(IN   RvSipMsgHandle hSipMsg,
                                           IN   RvChar*       strBody);

#ifndef RV_SIP_PRIMITIVES
/***************************************************************************
 * RvSipMsgGetBodyObject
 * ------------------------------------------------------------------------
 * General: Gets the Body object from the given Message object. The
 *          handle of the Body object is returned. Any changes that will be 
 *          made to this body object will be reflected in the message.
 *          
 * Return Value: The handle to the Body object.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:
 *      hSipMsg   - Handle to the Message object.
 ***************************************************************************/
RVAPI RvSipBodyHandle RVCALLCONV RvSipMsgGetBodyObject(
                                            IN RvSipMsgHandle       hSipMsg);

/***************************************************************************
 * RvSipMsgSetBodyObject
 * ------------------------------------------------------------------------
 * General: Sets a Body object in a given Message object.
 *          The given body is copied to the message. 
 *          If the body object contains a Content-Type header it
 *          will be copied to the message object as well.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hSipMsg - Handle to the message object.
 *            hBody   - The body object to be set to the message object.
 *                    If NULL is supplied, the existing body is removed from
 *                    the message object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMsgSetBodyObject(
                                           IN   RvSipMsgHandle  hSipMsg,
                                           IN   RvSipBodyHandle hBody);
#endif /* ifndef RV_SIP_PRIMITIVES */

#ifndef RV_SIP_PRIMITIVES
/***************************************************************************
 * RvSipMsgGetRpoolString
 * ------------------------------------------------------------------------
 * General: Copy a string parameter from the message into a given page
 *          from a specified pool. The copied string is not consecutive.
 * Return Value: RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input: hSipMsg - Handle to the message object.
 *           eStringName - The string the user wish to get. In this version RVSIP_MSG_CALL_ID
 *                         is the only string supported.
 *  Input/Output:
 *         pRpoolPtr     - pointer to a location inside an rpool. You need to
 *                         supply only the pool and page. The offset where the
 *                         returned string was located will be returned as an
 *                         output parameter.
 *                         If the function set the returned offset to
 *                         UNDEFINED is means that the parameter was not
 *                         set to the Other header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMsgGetRpoolString(
                             IN    RvSipMsgHandle                 hSipMsg,
                             IN    RvSipMessageStringName         eStringName,
                             INOUT RPOOL_Ptr                     *pRpoolPtr);


/***************************************************************************
 * RvSipMsgSetRpoolString
 * ------------------------------------------------------------------------
 * General: Sets a string into a specified parameter in the message object.
 *          The given string is located on an RPOOL memory and is not consecutive.
 * Return Value: RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input: hSipMsg       - Handle to the message object.
 *           eStringName   - The string the user wish to set. In this version 
 *                           RVSIP_MSG_CALL_ID is the only string supported.
 *           pRpoolPtr     - pointer to a location inside an rpool where the
 *                           new string is located.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMsgSetRpoolString(
                             IN    RvSipMsgHandle          hSipMsg,
                             IN    RvSipMessageStringName  eStringName,
                             IN    RPOOL_Ptr               *pRpoolPtr);
#endif /* #ifndef RV_SIP_PRIMITIVES */

/***************************************************************************
 * RvSipMsgSetCallIdCompactForm
 * ------------------------------------------------------------------------
 * General: Instructs the Call-ID header to use the compact header 
 *          name when the it's encoded.
 * Return Value: Returns RV_Status.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hSipMsg    - Handle to the message object.
 *  	  bIsCompact - specify whether or not to use a compact form
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMsgSetCallIdCompactForm(
                                   IN RvSipMsgHandle    hSipMsg,
                                   IN RvBool            bIsCompact);
 
/***************************************************************************
 * RvSipMsgSetContentLengthCompactForm
 * ------------------------------------------------------------------------
 * General: Instructs the Content-Length header to use the compact header 
 *          name when the it's encoded.
 * Return Value: Returns RV_Status.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hSipMsg    - Handle to the message object.
 *  	  bIsCompact - specify whether or not to use a compact form
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMsgSetContentLengthCompactForm(
                                   IN  RvSipMsgHandle  hSipMsg,
                                   IN  RvBool          bIsCompact);

/***************************************************************************
 * RvSipMsgGetStrBadSyntaxStartLine
 * ------------------------------------------------------------------------
 * General: Copies the bad-syntax start line from the message object
 *          into a given buffer.
 *          When a message is received and the start line contains
 *          a syntax error, the start line is kept as a separate bad syntax
 *          string. This function retrieves this string.
 *          If the bufferLen size adequate, the function copies the parameter
 *          into the strBuffer. Otherwise, it returns RV_ERROR_INSUFFICIENT_BUFFER
 *          and the actualLen parameter contains the required buffer length.
 *          Use this function in RvSipTransportBadSyntaxStartLineMsgEv event
 *          implementation, in order to check and fix the defected start-line.
 *          Note: If the start line is valid the function will return RV_ERROR_NOT_FOUND
 *          and the actualLen parameter will be set to 0.
 * Return Value: RV_OK or RV_ERROR_INSUFFICIENT_BUFFER.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hSipMsg   - Handle of the message object.
 *        strBuffer - buffer to fill with the bad syntax start line
 *        bufferLen - the length of the buffer.
 * output:actualLen - The length of the bad syntax start line + 1 to include
 *                    a NULL value at the end of the parameter.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMsgGetStrBadSyntaxStartLine(
                                    IN  RvSipMsgHandle hSipMsg,
                                    IN  RvChar*       strBuffer,
                                    IN  RvUint        bufferLen,
                                    OUT RvUint*       actualLen);
/***************************************************************************
 * RvSipMsgStartLineFix
 * ------------------------------------------------------------------------
 * General: Fixes a start-line with bad-syntax information. When a message
 *          is received with a syntax error in the start line, the start line
 *          string is kept as a separate "bad-syntax" string.
 *          Use this function in order to fix the start line.
 *          The function parses a given correct start line string to the supplied message object.
 *          If parsing succeeds the function places all fields inside the message start
 *          line and removes the bad syntax string.
 *          If parsing fails, the bad-syntax string is remained untouched.
 *          Use this function in RvSipTransportBadSyntaxStartLineMsgEv event
 *          implementation, in order to fix a defected start-line.
 * Return Value: RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input: hSipMsg      - Handle to the message object.
 *        pFixedBuffer - Buffer containing a legal start-line value.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipMsgStartLineFix(
                                    IN RvSipMsgHandle hSipMsg,
                                    IN RvChar*       pFixedBuffer);

#ifdef __cplusplus
}
#endif


#endif /* RVSIPMSG_H */
