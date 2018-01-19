/*

NOTICE:
This document contains information that is proprietary to RADVision LTD..
No part of this publication may be reproduced in any form whatsoever without
written prior approval by RADVision LTD..

RADVision LTD. reserves the right to revise this publication and make changes
without obligation to notify any person of such revisions or changes.

*/

/******************************************************************************
 *                     RvSipRouteHopHeader.h                                  *
 *                                                                            *
 * The file defines the functions of the RouteHop  object                     *
 * construct, destruct, copy, encode, parse and the ability to access and     *
 * change parameters.                                                         *
 * The RouteHop header object represents both Route and Record-Route SIP      *
 * headers                                                                    *
 *                                                                            *
 *                                                                            *
 *      Author           Date                                                 *
 *     ------           ------------                                          *
 *     Sarit Mekler     April.2001                                            *
 ******************************************************************************/


#ifndef RvSipRouteHopHOPHEADER_H
#define RvSipRouteHopHOPHEADER_H

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
 * RvSipRouteHopHeaderStringName
 * ----------------------
 * This enum defines all the header's strings (for getting it's size)
 * Defines all the Route Hop header fields that are kept in the object 
 * in string format.
 */
typedef enum
{
    RVSIP_ROUTE_HOP_DISPLAY_NAME,
    RVSIP_ROUTE_HOP_OTHER_PARAMS,
    RVSIP_ROUTE_HOP_BAD_SYNTAX
}RvSipRouteHopHeaderStringName;

/*
 * RvSipRouteHopHeaderType
 * ----------------------
 * This enum defines whether the RouteHop header represents a Route
 * or a Record-Route header.
 */
typedef enum
{
    RVSIP_ROUTE_HOP_UNDEFINED_HEADER = -1,
    RVSIP_ROUTE_HOP_ROUTE_HEADER,
    RVSIP_ROUTE_HOP_RECORD_ROUTE_HEADER
}RvSipRouteHopHeaderType;



/*-----------------------------------------------------------------------*/
/*                   CONSTRUCTORS AND DESTRUCTORS                        */
/*-----------------------------------------------------------------------*/


/***************************************************************************
 * RvSipRouteHopHeaderConstructInMsg
 * ------------------------------------------------------------------------
 * General: Constructs a RouteHop header object inside a given message object.
 *          The header is kept in the header list of the message. You can
 *          choose to insert the header either at the head or tail of the list.
 *          Use RvSipRouteHopHeaderSetHeaderType to determine whether the
 *          object represents a Route or a Record-Route header.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hSipMsg - Handle to the message object.
 *         pushHeaderAtHead - Boolean value indicating whether the header should be pushed to the head of the
 *                            list—RV_TRUE—or to the tail—RV_FALSE.
 * output: hHeader - Handle to the newly constructed Route header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRouteHopHeaderConstructInMsg(
                                      IN  RvSipMsgHandle             hSipMsg,
                                      IN  RvBool                    pushHeaderAtHead,
                                      OUT RvSipRouteHopHeaderHandle* hHeader);



/***************************************************************************
 * RvSipRouteHopHeaderConstruct
 * ------------------------------------------------------------------------
 * General: Constructs and initializes a stand-alone RouteHop Header object.
 *          The header is constructed on a given page taken from a specified
 *          pool. The handle to the new header object is returned.
 *          Use RvSipRouteHopHeaderSetHeaderType to determine whether the
 *          object represents a Route or a Record-Route header.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hMsgMgr - Handle to the Message manager.
 *         hPool   - Handle to the memory pool that the object will use.
 *         hPage   - Handle to the memory page that the object will use.
 * output: hHeader - Handle to the newly constructed RouteHop header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRouteHopHeaderConstruct(
                                      IN  RvSipMsgMgrHandle          hMsgMgr,
                                      IN  HRPOOL                     hPool,
                                      IN  HPAGE                      hPage,
                                      OUT RvSipRouteHopHeaderHandle* hHeader);

/***************************************************************************
 * RvSipRouteHopHeaderCopy
 * ------------------------------------------------------------------------
 * General: Copies all fields from a source RouteHop header object to a destination
 *          RouteHop header object.
 *          You must construct the destination object before using this function.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hDestination - Handle to the destination RouteHop header object.
 *    hSource      - Handle to the source RouteHop header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRouteHopHeaderCopy
                                        (INOUT RvSipRouteHopHeaderHandle hDestination,
                                         IN    RvSipRouteHopHeaderHandle hSource);


/***************************************************************************
 * RvSipRouteHopHeaderEncode
 * ------------------------------------------------------------------------
 * General: Encodes a RouteHop header object to a textual Route/Record-Route header.
 *          The textual header is placed on a page taken from a specified pool.
 *          In order to copy the textual header from the page to a consecutive
 *          buffer, use RPOOL_CopyToExternal().
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader  - Handle to the RouteHop header object.
 *        hPool    - Handle to the specified memory pool.
 * output: hPage   - The memory page allocated to contain the encoded header.
 *         length  - The length of the encoded information.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRouteHopHeaderEncode(
                                          IN    RvSipRouteHopHeaderHandle hHeader,
                                          IN    HRPOOL                 hPool,
                                          OUT   HPAGE*                 hPage,
                                          OUT   RvUint32*             length);

/***************************************************************************
 * RvSipRouteHopHeaderParse
 * ------------------------------------------------------------------------
 * General:Parses a SIP textual Route or Record-Route header—for example,
 *        "Record-Route: <sip:UserB@there.com;maddr=ss1.wcom.com>"—into a
 *         RouteHop header object. All the textual fields are placed inside
 *         the object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader   - A handle to the RouteHop header object.
 *    buffer    - Buffer containing a textual RouteHop header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRouteHopHeaderParse(
                                     IN    RvSipRouteHopHeaderHandle   hHeader,
                                     IN    RvChar*                 buffer);

/***************************************************************************
 * RvSipRouteHopHeaderParseValue
 * ------------------------------------------------------------------------
 * General: Parses a SIP textual RouteHop header value into an RouteHop header object.
 *          A SIP header has the following grammer:
 *          header-name:header-value. This function takes the header-value part as
 *          a parameter and parses it into the supplied object.
 *          All the textual fields are placed inside the object.
 *          Note: Use the RvSipRouteHopHeaderParse() function to parse strings that also
 *          include the header-name.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader   - The handle to the RouteHop header object.
 *    buffer    - The buffer containing a textual RouteHop header value.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRouteHopHeaderParseValue(
                                     IN    RvSipRouteHopHeaderHandle   hHeader,
                                     IN    RvChar*                    buffer);

/***************************************************************************
 * RvSipRouteHopHeaderFix
 * ------------------------------------------------------------------------
 * General: Fixes an RouteHop header with bad-syntax information.
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
RVAPI RvStatus RVCALLCONV RvSipRouteHopHeaderFix(
                                     IN RvSipRouteHopHeaderHandle hHeader,
                                     IN RvChar*                  pFixedBuffer);

/*-----------------------------------------------------------------------
                         G E T  A N D  S E T  M E T H O D S
 ------------------------------------------------------------------------*/
/***************************************************************************
 * RvSipRouteHopHeaderGetStringLength
 * ------------------------------------------------------------------------
 * General: Some of the RouteHop header fields are kept in a string format—for example, the
 *          Route header display name. In order to get such a field from the Route header
 *          object, your application should supply an adequate buffer to where the string
 *          will be copied.
 *          This function provides you with the length of the string to enable you to allocate
 *          an appropriate buffer size before calling the Get function.
 * Return Value: Returns the length of the specified string.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader    - Handle to the RouteHop header object.
 *  stringName - Enumeration of the string name for which you require the length.
 ***************************************************************************/
RVAPI RvUint RVCALLCONV RvSipRouteHopHeaderGetStringLength(
                                      IN  RvSipRouteHopHeaderHandle     hHeader,
                                      IN  RvSipRouteHopHeaderStringName stringName);


/***************************************************************************
 * RvSipRouteHopHeaderGetDisplayName
 * ------------------------------------------------------------------------
 * General: Copies the display name from the RouteHop header into a given buffer.
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
RVAPI RvStatus RVCALLCONV RvSipRouteHopHeaderGetDisplayName(
                                               IN RvSipRouteHopHeaderHandle   hHeader,
                                               IN RvChar*                 strBuffer,
                                               IN RvUint                  bufferLen,
                                               OUT RvUint*                actualLen);

/***************************************************************************
 * RvSipRouteHopHeaderSetDisplayName
 * ------------------------------------------------------------------------
 * General: Sets the display name in the RouteHop header object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader        - Handle to the header object.
 *    strDisplayName - The display name to be set in the RouteHop header.
 *                   If NULL is supplied, the existing
 *                   display name is removed from the header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRouteHopHeaderSetDisplayName(
                                             IN    RvSipRouteHopHeaderHandle hHeader,
                                             IN    RvChar *              strDisplayName);

/***************************************************************************
 * RvSipRouteHopHeaderGetAddrSpec
 * ------------------------------------------------------------------------
 * General: The Address Spec field is held in the RouteHop header object as an Address object.
 *          This function returns the handle to the Address object.
 * Return Value: Returns a handle to the Address Spec object, or NULL if the Address Spec
 *               object does not exist.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader - Handle to the RouteHop header object.
 ***************************************************************************/
RVAPI RvSipAddressHandle RVCALLCONV RvSipRouteHopHeaderGetAddrSpec
                                            (IN RvSipRouteHopHeaderHandle hHeader);

/***************************************************************************
 * RvSipRouteHopHeaderSetAddrSpec
 * ------------------------------------------------------------------------
 * General: Sets the Address Spec address object in the RouteHop header object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader   - Handle to the RouteHop header object.
 *  hAddrSpec - Handle to the Address Spec address object to be set in
 *              the RouteHop header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRouteHopHeaderSetAddrSpec
                                            (IN    RvSipRouteHopHeaderHandle hHeader,
                                             IN    RvSipAddressHandle     hAddrSpec);

/***************************************************************************
 * RvSipRouteHopHeaderGetOtherParams
 * ------------------------------------------------------------------------
 * General: Copies the RouteHop header other params field of the RouteHop header object into a
 *          given buffer.
 *          Not all the RouteHop header parameters have separated fields in the RouteHop header
 *          object. Parameters with no specific fields are refered to as other params. They
 *          are kept in the object in one concatenated string in the form?
 *          ”name=value;name=value...?
 *          If the bufferLen is adequate, the function copies the requested parameter into
 *          strBuffer. Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and actualLen
 *          contains the required buffer length.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader    - Handle to the RouteHop header object.
 *        strBuffer  - Buffer to fill with the requested parameter.
 *        bufferLen  - The length of the buffer.
 * output:actualLen - The length of the requested parameter, + 1 to include a NULL value at the end of
 *                     the parameter.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRouteHopHeaderGetOtherParams(
                                               IN RvSipRouteHopHeaderHandle   hHeader,
                                               IN RvChar*                 strBuffer,
                                               IN RvUint                  bufferLen,
                                               OUT RvUint*                actualLen);

/***************************************************************************
 * RvSipRouteHopHeaderSetOtherParams
 * ------------------------------------------------------------------------
 * General: Sets the other params field in the RouteHop header object.
 *          Not all the RouteHop header parameters have separated fields in the RouteHop header
 *          object. Parameters with no specific fields are refered to as other params. They
 *          are kept in the object in one concatenated string in the form?
 *          ”name=value;name=value...?
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader        - Handle to the RouteHop header object.
 *    strOtherParams - The Other Params string to be set in the RouteHop header.
 *                   If NULL is supplied, the existing Other Params field is
 *                   removed from the header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRouteHopHeaderSetOtherParams(
                                             IN    RvSipRouteHopHeaderHandle hHeader,
                                             IN    RvChar *              strOtherParams);

/***************************************************************************
 * RvSipRouteHopHeaderGetHeaderType
 * ------------------------------------------------------------------------
 * General: Gets the header type enumeration from the RouteHop Header object.
 * Return Value: Returns the RouteHop header type enumeration from the RouteHop
 *               header object.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hSipAuthHeader - Handle to the RouteHop header object.
 ***************************************************************************/
RVAPI RvSipRouteHopHeaderType  RVCALLCONV RvSipRouteHopHeaderGetHeaderType(
                                   IN RvSipRouteHopHeaderHandle hHeader);

/***************************************************************************
 * RvSipRouteHopHeaderSetHeaderType
 * ------------------------------------------------------------------------
 * General: Sets the header type in the RouteHop Header object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hSipAuthHeader    - Handle to the RouteHop header object.
 *    eHeaderType       - The header type to be set in the object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRouteHopHeaderSetHeaderType(
                                 IN    RvSipRouteHopHeaderHandle hHeader,
                                 IN    RvSipRouteHopHeaderType   eHeaderType);

/***************************************************************************
 * RvSipRouteHopHeaderGetStrBadSyntax
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
 *          implementation if the message contains a bad RouteHop header,
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
RVAPI RvStatus RVCALLCONV RvSipRouteHopHeaderGetStrBadSyntax(
                                               IN RvSipRouteHopHeaderHandle hHeader,
                                               IN RvChar*                 strBuffer,
                                               IN RvUint                  bufferLen,
                                               OUT RvUint*                actualLen);

/***************************************************************************
 * RvSipRouteHopHeaderSetStrBadSyntax
 * ------------------------------------------------------------------------
 * General: Sets a bad-syntax string in the object.
 *          A SIP header has the following grammer:
 *          header-name:header-value. When a header contains a syntax error,
 *          the header-value is kept as a separate "bad-syntax" string.
 *          By using this function you can create a header with "bad-syntax".
 *          Setting a bad syntax string to the header will mark the header as
 *          an invalid syntax header.
 *          You can use his function when you want to send an illegal RouteHop header.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader      - The handle to the header object.
 *  strBadSyntax - The bad-syntax string.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRouteHopHeaderSetStrBadSyntax(
                                  IN RvSipRouteHopHeaderHandle hHeader,
                                  IN RvChar*                     strBadSyntax);


#ifndef RV_SIP_PRIMITIVES
/***************************************************************************
 * RvSipRouteHopHeaderGetRpoolString
 * ------------------------------------------------------------------------
 * General: Copy a string parameter from the RouteHop header into a given page
 *          from a specified pool. The copied string is not consecutive.
 * Return Value: RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input: hSipRouteHopHeader - Handle to the RouteHop header object.
 *           eStringName   - The string the user wish to get
 *  Input/Output:
 *         pRpoolPtr     - pointer to a location inside an rpool. You need to
 *                         supply only the pool and page. The offset where the
 *                         returned string was located will be returned as an
 *                         output patameter.
 *                         If the function set the returned offset to
 *                         UNDEFINED is means that the parameter was not
 *                         set to the RouteHop header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRouteHopHeaderGetRpoolString(
                             IN    RvSipRouteHopHeaderHandle      hSipRouteHopHeader,
                             IN    RvSipRouteHopHeaderStringName  eStringName,
                             INOUT RPOOL_Ptr                     *pRpoolPtr);

/***************************************************************************
 * RvSipRouteHopHeaderSetRpoolString
 * ------------------------------------------------------------------------
 * General: Sets a string into a specified parameter in the RouteHop header
 *          object. The given string is located on an RPOOL memory and is
 *          not consecutive.
 * Return Value: RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input: hSipRouteHopHeader - Handle to the RouteHop header object.
 *           eStringName   - The string the user wish to set
 *         pRpoolPtr     - pointer to a location inside an rpool where the
 *                         new string is located.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRouteHopHeaderSetRpoolString(
                             IN    RvSipRouteHopHeaderHandle      hSipRouteHopHeader,
                             IN    RvSipRouteHopHeaderStringName  eStringName,
                             IN    RPOOL_Ptr                 *pRpoolPtr);

#endif /* #ifndef RV_SIP_PRIMITIVES*/



#ifdef __cplusplus
}
#endif

#endif /* RvSipRouteHopHOPHEADER_H */
