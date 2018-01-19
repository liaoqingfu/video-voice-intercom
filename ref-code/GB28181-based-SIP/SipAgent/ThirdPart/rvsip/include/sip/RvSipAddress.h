/*

NOTICE:
This document contains information that is proprietary to RADVision LTD..
No part of this publication may be reproduced in any form whatsoever without
written prior approval by RADVision LTD..

RADVision LTD. reserves the right to revise this publication and make changes
without obligation to notify any person of such revisions or changes.

*/

/******************************************************************************
 *                           RvSipAddress.h                                   *
 *                                                                            *
 * The file defines the methods of the address object: construct, destruct,   *
 * copy, encode, parse and the ability to access and change it's parameters.  *
 *                                                                            *
 *                                                                            *
 *      Author           Date                                                 *
 *     ------           ------------                                          *
 *      Ofra             Nov.2000                                             *
 ******************************************************************************/



#ifndef RVSIPADDRESS_H
#define RVSIPADDRESS_H

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                           */
/*-----------------------------------------------------------------------*/
#include "RV_SIP_DEF.h"
#include "RvSipMsgTypes.h"
#include "rpool_API.h"
#include "RvSipCommonList.h"

/*-----------------------------------------------------------------------*/
/*                   DECLERATIONS                                        */
/*-----------------------------------------------------------------------*/
/*
 * RvSipAddressStringName
 * ----------------------
 * Defines all Address object fields that are kept in the object in a string format.
 */
typedef enum
{
    RVSIP_ADDRESS_ABS_URI_SCHEAM,
    RVSIP_ADDRESS_ABS_URI_IDENTIFIER,
    RVSIP_ADDRESS_USER,
    RVSIP_ADDRESS_HOST,
    RVSIP_ADDRESS_TRANSPORT,
    RVSIP_ADDRESS_MADDR_PARAM,
    RVSIP_ADDRESS_USER_PARAM,
    RVSIP_ADDRESS_COMP_PARAM,
    RVSIP_ADDRESS_URL_OTHER_PARAMS,
    RVSIP_ADDRESS_HEADERS,
    RVSIP_ADDRESS_METHOD
}RvSipAddressStringName;

/*-----------------------------------------------------------------------*/
/*                   CONSTRUCTORS AND DESTRUCTORS                        */
/*-----------------------------------------------------------------------*/

/*
 * There are several functions for constructing url:
 * 1. stand alone url (RvSipAddrConstruct) -
 *                          will be copied on the page that is given as argument.
 *
 * 2. url that is part of the requestLine of the msg (RvSipAddrConstructInStartLine) -
 *                          url will be construct on the given msg's page.
 *
 * 3. url that is part of XXX header ( RvSipAddrConstructInXXXHeader ) -
 *                          url will be construct on the given header's page.
 *
 */
/***************************************************************************
 * RvSipAddrConstructInStartLine
 * ------------------------------------------------------------------------
 * General: Constructs an address object inside the Request line of a given message. The
 *          new address is set as the request URI of the Request line. The handle of the
 *          address object is returned.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hSipMsg   - Handle to the SIP message.
 *         eAddrType - The type of address to construct—In this version, only URL.
 * output: hSipAddr  - Handle to the newly created address object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAddrConstructInStartLine(
                                            IN  RvSipMsgHandle      hSipMsg,
                                            IN  RvSipAddressType    eAddrType,
                                            OUT RvSipAddressHandle* hSipAddr);

/***************************************************************************
 * RvSipAddrConstructInPartyHeader
 * ------------------------------------------------------------------------
 * General: Constructs the address-spec address object inside a given To or From party
 *          header. The address handle is returned.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hHeader   - Handle to the party header.
 *         eAddrType - The type of address to construct—In this version, only URL.
 * output: hSipAddr  - Handle to the newly constructed address object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAddrConstructInPartyHeader(
                                          IN  RvSipPartyHeaderHandle hHeader,
                                          IN  RvSipAddressType       eAddrType,
                                          OUT RvSipAddressHandle*    hSipAddr);

/***************************************************************************
 * RvSipAddrConstructInRouteHopHeader
 * ------------------------------------------------------------------------
 * General: Constructs the address-spec address object inside a given RouteHop
 *          header. The address handle is returned.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hHeader   - Handle to the Route Hop header.
 *         eAddrType - The type of address to construct—In this version, only URL.
 * output: hSipAddr  - Handle to the newly constructed address object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAddrConstructInRouteHopHeader(
                                          IN  RvSipRouteHopHeaderHandle hHeader,
                                          IN  RvSipAddressType       eAddrType,
                                          OUT RvSipAddressHandle*    hSipAddr);
#ifndef RV_SIP_PRIMITIVES
/***************************************************************************
 * RvSipAddrConstructInReferToHeader
 * ------------------------------------------------------------------------
 * General: Constructs the address-spec address object inside a given Refer-To
 *          header. The address handle is returned.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hHeader   - Handle to the Refer-To header.
 *         eAddrType - The type of address to construct—In this version, only URL.
 * output: hSipAddr  - Handle to the newly constructed address object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAddrConstructInReferToHeader(
                                          IN  RvSipReferToHeaderHandle hHeader,
                                          IN  RvSipAddressType         eAddrType,
                                          OUT RvSipAddressHandle*      hSipAddr);

/***************************************************************************
 * RvSipAddrConstructInReferredByHeader
 * ------------------------------------------------------------------------
 * General: Constructs the address-spec address object inside a given Referred-By
 *          header. The address handle is returned.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hHeader   - Handle to the Referred-By header.
 *         eAddrType - The type of address to construct—In this version, only URL.
 * output: hSipAddr  - Handle to the newly constructed address object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAddrConstructInReferredByHeader(
                                        IN  RvSipReferredByHeaderHandle hHeader,
                                        IN  RvSipAddressType            eAddrType,
                                        OUT RvSipAddressHandle*         hSipAddr);

#endif /* #ifndef RV_SIP_PRIMITIVES*/
/***************************************************************************
 * RvSipAddrConstructInAuthorizationHeader
 * ------------------------------------------------------------------------
 * General: Constructs the digest URI address object inside a given Authorization header.
 *          The address handle is returned.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hHeader   - Handle to the Authorization header.
 *         eAddrType - The type of address to construct—In this version, only URL.
 * output: hSipAddr  - Handle to the newly constructed address object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAddrConstructInAuthorizationHeader(
                                          IN  RvSipAuthorizationHeaderHandle hHeader,
                                          IN  RvSipAddressType               eAddrType,
                                          OUT  RvSipAddressHandle*           hSipAddr);



/***************************************************************************
 * RvSipAddrConstructInContactHeader
 * ------------------------------------------------------------------------
 * General: Constructs the address-spec address object inside a given contact header. The
 *          address handle is returned.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hHeader   - Handle to the contact header.
 *         eAddrType - The type of address to construct—In this version, only URL.
 * output: hSipAddr  - Handle to the newly constructed address object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAddrConstructInContactHeader(
                                          IN  RvSipContactHeaderHandle hHeader,
                                          IN  RvSipAddressType         eAddrType,
                                          OUT  RvSipAddressHandle*     hSipAddr);



/***************************************************************************
 * RvSipAddrConstruct
 * ------------------------------------------------------------------------
 * General: Constructs and initializes a stand-alone Address object. The object is
 *          constructed on a given page taken from a specified pool. The handle to the new
 *          header object is returned.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hMsgMgr   - Handle to the message manager.
 *         hPool     - Handle to the memory pool. that the object uses.
 *         hPage     - Handle to the memory page that the object uses.
 *         eAddrType - The type of address URL to construct.
 * output: hSipAddr  - Handle to the newly constructed address object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAddrConstruct(IN  RvSipMsgMgrHandle   hMsgMgr,
                                              IN  HRPOOL              hPool,
                                              IN  HPAGE               hPage,
                                              IN  RvSipAddressType    eAddrType,
                                              OUT RvSipAddressHandle* hSipAddr);

/***************************************************************************
 * RvSipAddrCopy
 * ------------------------------------------------------------------------
 * General:Copies all fields from a source Address object to a destination Address object.
 *         You must construct the destination object before using this function.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hDestination - Handle to the destination Address object.
 *    hSource      - Handle to the source Address object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAddrCopy(INOUT    RvSipAddressHandle hDestination,
                                        IN       RvSipAddressHandle hSource);

/***************************************************************************
 * RvSipAddrEncode
 * ------------------------------------------------------------------------
 * General: Encodes an Address object to a textual address object. The textual header is
 *          placed on a page taken from a specified pool. In order to copy the textual header
 *          from the page to a consecutive buffer, use RPOOL_CopyToExternal().
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hSipAddr - Handle to the Address object.
 *        hPool    - Handle to the specified memory pool.
 * output: hPage   - The memory page allocated to contain the encoded object.
 *         length  - The length of the encoded information.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAddrEncode(IN  RvSipAddressHandle hSipAddr,
                                           IN  HRPOOL             hPool,
                                           OUT HPAGE*             hPage,
                                           OUT RvUint32*         length);

/***************************************************************************
 * RvSipAddrParse
 * ------------------------------------------------------------------------
 * General:Parses a SIP textual Address object, such as, “sip:bob@radvision.com? 
 *         into an Address object . 
 *         All the textual fields are placed inside the object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hSipAddr  - A handle to the Address object.
 *    buffer    - Buffer containing a textual Address.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAddrParse(
                                     IN    RvSipAddressHandle hSipAddr,
                                     IN    RvChar*           buffer);

/*-----------------------------------------------------------------------
                         G E T  A N D  S E T  F U N C T I O N S
 ------------------------------------------------------------------------*/
/***************************************************************************
 * RvSipAddrGetStringLength
 * ------------------------------------------------------------------------
 * General: Some of the address fields are kept in a string format, such as the address host
 *          name. In order to get such a field from the address object, your application
 *          should supply an adequate buffer to where the string will be copied.
 *          This function provides you with the length of the string to enable you to allocate
 *          an appropriate buffer size before calling the Get function.
 * Return Value: Returns the length of the specified string.
 * ------------------------------------------------------------------------
 * Arguments:
 *  hSipAddr   - Handle to the Address object.
 *  stringName - Enumeration of the string name for which you require the length.
 ***************************************************************************/
RVAPI RvUint RVCALLCONV RvSipAddrGetStringLength(
                                      IN  RvSipAddressHandle     hSipAddr,
                                      IN  RvSipAddressStringName stringName);

/***************************************************************************
 * RvSipAddrGetAddrType
 * ------------------------------------------------------------------------
 * General: Gets the address type of an address object.
 * Return Value: Returns RvSipAddressType—for more information see RvSipAddressType
 *               in the Enumerations.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input: hSipAddr - Handle to the address object.
 ***************************************************************************/
RVAPI RvSipAddressType RVCALLCONV RvSipAddrGetAddrType(IN RvSipAddressHandle hSipAddr);


/***************************************************************************
 * RvSipAddrGetRpoolString
 * ------------------------------------------------------------------------
 * General: Copy a string parameter from the address into a given page
 *          from a specified pool. The copied string is not consecutive.
 * Return Value: RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input: hAddr - Handle to the address object.
 *           eStringName   - The string the user wish to get
 *  Input/Output:
 *         pRpoolPtr     - pointer to a location inside an rpool. You need to
 *                         supply only the pool and page. The offset where the
 *                         returned string was located will be returned as an
 *                         output parameter.
 *                         If the function set the returned offset to
 *                         UNDEFINED is means that the parameter was not
 *                         set to the Via header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAddrGetRpoolString(
                             IN    RvSipAddressHandle      hAddr,
                             IN    RvSipAddressStringName  eStringName,
                             INOUT RPOOL_Ptr                 *pRpoolPtr);

/***************************************************************************
 * RvSipAddrSetRpoolString
 * ------------------------------------------------------------------------
 * General: Sets a string into a specified parameter in the address
 *          object. The given string is located on an RPOOL memory and is
 *          not consecutive.
 * Return Value: RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input: hAddr         - Handle to the address object.
 *           eStringName   - The string the user wish to set
 *           pRpoolPtr     - pointer to a location inside an rpool where the
 *                         new string is located.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAddrSetRpoolString(
                             IN    RvSipAddressHandle      hAddr,
                             IN    RvSipAddressStringName  eStringName,
                             IN    RPOOL_Ptr               *pRpoolPtr);


/*-----------------------------------------------------------------------*/
/*                  ADDRESS COMPARSION FUNCTIONS                         */
/*-----------------------------------------------------------------------*/

/***************************************************************************
 * RvSipAddrIsEqual
 * ------------------------------------------------------------------------
 * General: Compares two SIP addresses, as specified in RFC 2543.
 * Return Value: Returns RV_TRUE if the addresses are equal.
 *               Otherwise, the function returns RV_FALSE.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hAddress      - Handle to the first address object.
 *    hOtherAddress - Handle to the second address object with which a
 *                    comparison is being made.
 ***************************************************************************/
RVAPI RvBool RVCALLCONV RvSipAddrIsEqual(IN RvSipAddressHandle hAddress,
                                          IN RvSipAddressHandle hOtherAddress);

/***************************************************************************
 * RvSipAddrUrlIsEqual
 * ------------------------------------------------------------------------
 * General: OBSOLETE function. use RvSipAddrIsEqual().
 * Return Value: Returns RV_TRUE if the URLs are equal. 
 *               Otherwise, the function returns RV_FALSE.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader      - Handle to the URL object.
 *    hOtherHeader - Handle to the URL object with which a comparison is being made.
 ***************************************************************************/
RVAPI RvBool RVCALLCONV RvSipAddrUrlIsEqual(IN RvSipAddressHandle hHeader,
                                             IN RvSipAddressHandle hOtherHeader);

/*-----------------------------------------------------------------------
                   SIP URL - GET AND SET FUNCTIONS                      
  -----------------------------------------------------------------------*/
/***************************************************************************
 * RvSipAddrUrlGetUser
 * ------------------------------------------------------------------------
 * General:  Copies the user field from the address object into a given buffer.
 *           If the bufferLen is adequate, the function copies the parameter 
 *           into the strBuffer.
 *           Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and
 *           actualLen contains the required buffer length.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hSipAddr  - Handle to the URL address object.
 *        strBuffer - Buffer to fill with the requested parameter.
 *        bufferLen - The length of the given buffer.
 * output:actualLen - The length of the requested parameter + 1, to include NULL 
 *                    character at the end of the string.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAddrUrlGetUser(IN RvSipAddressHandle hSipAddr,
                                               IN RvChar*           strBuffer,
                                               IN RvUint            bufferLen,
                                               OUT RvUint*          actualLen);


/***************************************************************************
 * RvSipAddrUrlSetUser
 * ------------------------------------------------------------------------
 * General: Sets the user string value in the Address URL object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hSipAddr - Handle to the Address object.
 *    strUser  - The user value to be set in the object. If NULL is supplied, 
 *               the existing strUser is removed from the Address object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAddrUrlSetUser(IN RvSipAddressHandle hSipAddr,
                                               IN RvChar*           strUser);

/***************************************************************************
 * RvSipAddrUrlGetHost
 * ------------------------------------------------------------------------
 * General:  Copies the host field from the address object into a given buffer.
 *           If the bufferLen is adequate, the function copies the parameter 
 *           into the strBuffer.
 *           Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and
 *           actualLen contains the required buffer length.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hSipAddr   - Handle to the URL address object.
 *        strBuffer  - Buffer to fill with the requested parameter.
 *        bufferLen  - The length of the given buffer.
 * output:actualLen -  The length of the requested parameter + 1, to include NULL 
 *                     character at the end of the string.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAddrUrlGetHost(
                                               IN RvSipAddressHandle hSipAddr,
                                               IN RvChar*           strBuffer,
                                               IN RvUint            bufferLen,
                                               OUT RvUint*          actualLen);


/***************************************************************************
 * RvSipAddrUrlSetHost
 * ------------------------------------------------------------------------
 * General: Sets the host in the URL object or removes the existing host from the URL
 *          object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hSipAddr - Handle to the URL address object.
 *    strHost  - The host value to be set in the object. 
 *               If NULL is supplied, the existing host is removed.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAddrUrlSetHost(
                                           IN    RvSipAddressHandle hSipAddr,
                                           IN    RvChar*           strHost);

/***************************************************************************
 * RvSipAddrUrlGetPortNum
 * ------------------------------------------------------------------------
 * General:Gets the port number from the URL object.
 * Return Value: Returns the port number, or UNDEFINED if the port is not set.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hSipUrl - Handle to the URL address object.
 ***************************************************************************/
RVAPI RvInt32 RVCALLCONV RvSipAddrUrlGetPortNum(IN RvSipAddressHandle hSipUrl);


/***************************************************************************
 * RvSipAddrUrlSetPortNum
 * ------------------------------------------------------------------------
 * General:  Sets the port number in the URL object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hSipUrl - Handle to the URL address object.
 *    portNum - The port number value to be set in the object. In order to remove the port
 *            number from the address object, you can set this parameter to UNDEFINED.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAddrUrlSetPortNum(IN RvSipAddressHandle hSipUrl,
                                                  IN RvInt32           portNum);

/***************************************************************************
 * RvSipAddrUrlGetTtlNum
 * ------------------------------------------------------------------------
 * General: Gets the ttl number from the URL object.
 * Return Value: Returns the ttl number, or UNDEFINED if ttl is not set.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hSipAddr - Handle to the URL address object.
 ***************************************************************************/
RVAPI RvInt16 RVCALLCONV RvSipAddrUrlGetTtlNum(IN RvSipAddressHandle hSipAddr);


/***************************************************************************
 * RvSipAddrUrlSetTtlNum
 * ------------------------------------------------------------------------
 * General:  Sets the ttl number in the address URL object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hSipAddr - Handle to the URL address object.
 *    ttlNum   - The ttl number value to be set in the object. 
 *               In order to remove the ttl number from the address object, 
 *               you can set this parameter to UNDEFINED.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAddrUrlSetTtlNum(
                                          IN RvSipAddressHandle hSipAddr,
                                          IN RvInt16           ttlNum);

/***************************************************************************
 * RvSipAddrUrlGetLrParam
 * ------------------------------------------------------------------------
 * General: Returns RV_TRUE if the lr param exists in the address.
 * Return Value: Returns RV_TRUE if the lr param exists in the address.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hSipAddr - Handle to the URL address object.
 ***************************************************************************/

RVAPI RvBool RVCALLCONV RvSipAddrUrlGetLrParam(IN RvSipAddressHandle hSipAddr);

/***************************************************************************
 * RvSipAddrUrlGetLrParamType
 * ------------------------------------------------------------------------
 * General: Returns the type of the lr param exists in the address.
 *          (lr; lr-true; lr=1;)
 * Return Value: RvSipUrlLrType.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hSipAddr - Handle to the URL address object.
 ***************************************************************************/
RVAPI RvSipUrlLrType RVCALLCONV RvSipAddrUrlGetLrParamType(
                                              IN RvSipAddressHandle hSipAddr);

/***************************************************************************
 * RvSipAddrUrlSetLrParam
 * ------------------------------------------------------------------------
 * General:  Sets the lr parameter in the address URL object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hSipAddr - Handle to the URL address object.
 *    bLrParam   - RV_TRUE specifies that the lr exists in the address.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAddrUrlSetLrParam(
                                          IN    RvSipAddressHandle hSipAddr,
                                          IN    RvBool            bLrParam);

/***************************************************************************
 * RvSipAddrUrlSetLrParamType
 * ------------------------------------------------------------------------
 * General:  Sets the lr parameter type in the address URL object.
 *          (lr; lr-true; lr=1;)
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hSipAddr     - Handle to the URL address object.
 *    eLrParamType - Type of the lr parameter.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAddrUrlSetLrParamType(
                                          IN    RvSipAddressHandle hSipAddr,
                                          IN    RvSipUrlLrType     eLrParamType);

/***************************************************************************
 * RvSipAddrUrlIsSecure
 * ------------------------------------------------------------------------
 * General: Defines if the url address scheme is secure or not.
 *          (does the url is secures - with "sips:" prefix,
 *          or not secured - with "sip:" prefix)
 * Return Value: is secure.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hSipAddr - Handle to the URL address object.
 ***************************************************************************/
RVAPI RvBool RVCALLCONV RvSipAddrUrlIsSecure(IN RvSipAddressHandle hSipAddr);

/***************************************************************************
 * RvSipAddrUrlSetIsSecure
 * ------------------------------------------------------------------------
 * General:  Sets the address URL object to be secured or not.
 *          (sets the url to be secured - with "sips:" prefix,
 *          or not - with "sip:" prefix)
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hSipAddr    - Handle to the URL address object.
 *    bIsSecure   - indicates the secure / not secured
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAddrUrlSetIsSecure(
                                          IN    RvSipAddressHandle hSipAddr,
                                          IN    RvBool             bIsSecure);

/***************************************************************************
 * RvSipAddrUrlGetMethod
 * ------------------------------------------------------------------------
 * General: Gets the method type enumeration from the URL address object.
 *          If this function returns RVSIP_METHOD_OTHER, call
 *          RvSipAddrUrlGetStrMethod() to get the actual method in a string
 *          format.
 * Return Value: Returns the method type enumeration from the URL address object.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hSipAddr   - Handle to the URL address object.
 ***************************************************************************/
RVAPI RvSipMethodType RVCALLCONV RvSipAddrUrlGetMethod(
                                          IN  RvSipAddressHandle hSipAddr);

/***************************************************************************
 * RvSipAddrUrlGetStrMethod
 * ------------------------------------------------------------------------
 * General: This method retrieves the method type string value from the
 *          URL address object.
 *          If the bufferLen is big enough, the function will copy the parameter,
 *          into the strBuffer. Else, it will return RV_ERROR_INSUFFICIENT_BUFFER, and
 *          the actualLen param will contain the needed buffer length.
 * Return Value: RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader   - Handle to the URL address object.
 *        strBuffer - buffer to fill with the requested parameter.
 *        bufferLen - the length of the buffer.
 * output:actualLen - The length of the requested parameter + 1 for null in the end.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAddrUrlGetStrMethod(
                                          IN  RvSipAddressHandle hSipAddr,
                                          IN  RvChar*           strBuffer,
                                          IN  RvUint            bufferLen,
                                          OUT RvUint*           actualLen);

/***************************************************************************
 * RvSipAddrUrlSetMethod
 * ------------------------------------------------------------------------
 * General:Sets the method type in the URL address object.
 *         If eMethodType is RVSIP_METHOD_OTHER, strMethodType is copied to the
 *         header. Otherwise strMethodType is ignored.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader       - Handle to the URL address object.
 *  eMethodType   - The method type to be set in the object.
 *    strMethodType - You can use this parameter only if the eMethodType parameter is set to
 *                  RVSIP_METHOD_OTHER. In this case, you can supply the method as a string.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAddrUrlSetMethod(
                                             IN    RvSipAddressHandle hSipAddr,
                                             IN    RvSipMethodType    eMethodType,
                                             IN    RvChar*           pMethodTypeStr);

/***************************************************************************
 * RvSipAddrUrlGetTransport
 * ------------------------------------------------------------------------
 * General: Gets the transport protocol enumeration value from the URL object. If the
 *          returned Transport enumeration is RVSIP_TRANSPORT_OTHER, you can get
 *          the transport protocol string by calling RvSipAddrUrlGetStrTransport().
 *          If this function returns RVSIP_METHOD_OTHER, call
 *          RvSipAddrUrlGetStrTransport().
 * Return Value: Returns the transportType enumeration value.
 * ------------------------------------------------------------------------
 * Arguments:
 *    input:  hSipAddr - Handle to the URL address object.
 ***************************************************************************/
RVAPI RvSipTransport RVCALLCONV RvSipAddrUrlGetTransport(
                                           IN RvSipAddressHandle hSipAddr);

/***************************************************************************
 * RvSipAddrUrlGetStrTransport
 * ------------------------------------------------------------------------
 * General: Copies the transport protocol string from the URL address object into a given
 *          buffer. Use this function if RvSipAddrUrlGetTransport() returns
 *          RVSIP_TRANSPORT_OTHER.
 *          If the bufferLen is adequate, the function copies the parameter 
 *           into the strBuffer.
 *           Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and
 *           actualLen contains the required buffer length.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    input:  hSipAddr     - Handle to the URL address object.
 *          strBuffer    - Buffer to include the requested parameter.
 *          bufferLen    - The length of the given buffer.
 *  output: actualLen   - The length of the requested parameter + 1, to include NULL character at the end
 *                         of the string.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAddrUrlGetStrTransport(
                                           IN RvSipAddressHandle hSipAddr,
                                           IN RvChar*           strBuffer,
                                           IN RvUint            bufferLen,
                                           OUT RvUint*          actualLen);

/***************************************************************************
 * RvSipAddrUrlSetTransport
 * ------------------------------------------------------------------------
 * General:  Sets the transport protocol value in the URL object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hSipAddr     - Handle to the URL address object.
 *    eTransport   - The transport protocol enumeration value to be set in the object.
 *  strTransport - You can use this parameter only if the eTransport parameter is set to
 *                 RVSIP_TRANSPORT_OTHER. In this case you can supply the transport
 *                 protocol as a string.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAddrUrlSetTransport(
                                            IN    RvSipAddressHandle hSipAddr,
                                            IN    RvSipTransport     eTransport,
                                            IN    RvChar*           strTransport);

/***************************************************************************
 * RvSipAddrUrlGetMaddrParam
 * ------------------------------------------------------------------------
 * General: Copies the maddr parameter from the address object into a given buffer. If the
 *          bufferLen is adequate, the function copies the parameter into the strBuffer.
 *          Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and the actualLen
 *          parameter contains the required buffer length.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hSipAddr   - Handle to the URL address object.
 *        strBuffer  - Buffer to fill with the requested parameter.
 *        bufferLen  - The length of the buffer.
 * output:actualLen - The length of the requested parameter + 1, to include a NULL value at the end
 *                     of the parameter.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAddrUrlGetMaddrParam(
                                               IN RvSipAddressHandle hSipAddr,
                                               IN RvChar*           strBuffer,
                                               IN RvUint            bufferLen,
                                               OUT RvUint*          actualLen);

/***************************************************************************
 * RvSipAddrUrlSetMaddrParam
 * ------------------------------------------------------------------------
 * General: Sets the value of the maddr parameter in the URL object or removes the the
 *          maddr parameter from the object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hSipUrl       - Handle to the URL address object.
 *    strMaddrParam - The maddr parameter to be set in the object. If NULL is supplied, the maddr
 *                  parameter is removed from the URL object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAddrUrlSetMaddrParam(IN RvSipAddressHandle hSipUrl,
                                                     IN RvChar*       strMaddrParam);


/***************************************************************************
 * RvSipAddrUrlGetUserParam
 * ------------------------------------------------------------------------
 * General:Gets the user parameter enumeration value from the URL object. If eUserParam
 *         is RVSIP_USERPARAM_OTHER, then you can get the user parameter string
 *         value using RvSipAddrUrlGetStrUserParam().
 * Return Value: The enumeration value of the requested userParam.
 * ------------------------------------------------------------------------
 * Arguments:
 *    input:  hSipAddr     - Handle to the URL address object.
 ***************************************************************************/
RVAPI RvSipUserParam RVCALLCONV RvSipAddrUrlGetUserParam(
                                            IN  RvSipAddressHandle hSipAddr);

/***************************************************************************
 * RvSipAddrUrlGetStrUserParam
 * ------------------------------------------------------------------------
 * General: Copies the user param string from the URL address object into a given buffer.
 *          Use this function if RvSipAddrUrlGetUserParam() returns
 *          RVSIP_USERPARAM_OTHER.
 *          If the bufferLen is adequate, the function copies the parameter into the strBuffer.
 *          Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and the actualLen
 *          parameter contains the required buffer length.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    input:  hSipAddr   - Handle to the URL address object.
 *          strBuffer  - Buffer to fill with the requested parameter.
 *          bufferLen  - The length of the buffer.
 *  output: actualLen - The length of the requested parameter + 1, to include a NULL
 *                       value at the end of the parameter.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAddrUrlGetStrUserParam(
                                           IN RvSipAddressHandle hSipAddr,
                                           IN RvChar*           strBuffer,
                                           IN RvUint            bufferLen,
                                           OUT RvUint*          actualLen);

/***************************************************************************
 * RvSipAddrUrlSetUserParam
 * ------------------------------------------------------------------------
 * General: Sets the user param value within the URL object. If eUserParam is set to
 *          RVSIP_USERPARAM_OTHER, then the string in strUserParam is set to the
 *          URL user parameter. Otherwise, strUserParam is ignored.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    input:  hSipAddr     - Handle to the URL address object.
 *          eUserParam   - Enumeration value of the userParam.
 *          strUserParam - String containing the user param when eUserParam value is
 *                         RVSIP_USERPARAM_OTHER.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAddrUrlSetUserParam(IN RvSipAddressHandle hSipAddr,
                                                    IN RvSipUserParam     eUserParam,
                                                    IN RvChar*           strUserParam);


/***************************************************************************
 * RvSipAddrUrlGetOtherParams
 * ------------------------------------------------------------------------
 * General: Copies the URL other params field of the Address object into a given buffer.
 *          Not all the address parameters have separated fields in the address object.
 *          Parameters with no specific fields are refered to as other params. 
 *          They are kept in the object in one concatenated string in the form:
 *          ”name=value;name=value...?
 *          If the bufferLen is adequate, the function copies the requested 
 *          parameter into strBuffer. 
 *          Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and actualLen
 *          contains the required buffer length.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hSipAddr   - Handle to the URL address object.
 *        strBuffer  - Buffer to include the requested parameter.
 *        bufferLen  - The length of the given buffer.
 * output:actualLen  - The length of the requested parameter + 1, to include a 
 *                     NULL value at the end of the parameter.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAddrUrlGetOtherParams(
                                               IN RvSipAddressHandle hSipAddr,
                                               IN RvChar*           strBuffer,
                                               IN RvUint            bufferLen,
                                               OUT RvUint*          actualLen);


/***************************************************************************
 * RvSipAddrUrlSetOtherParams
 * ------------------------------------------------------------------------
 * General: Sets the other params field in the address object.
 *          Not all the address parameters have separated fields in the address object.
 *          Parameters with no specific fields are referred to as other params.
 *          They are kept in the object in one concatenated string in the form:
 *          ”name=value;name=value...?
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hSipUrl       - Handle to the URL address object.
 *    strUrlParams  - The extended parameters field to be set in the Address object. 
 *                    If NULL is supplied, the existing extended parameters field 
 *                    is removed from the header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAddrUrlSetOtherParams(
                                            IN RvSipAddressHandle hSipUrl,
                                            IN RvChar*           strUrlParams);

/***************************************************************************
 * RvSipAddrUrlGetHeaders
 * ------------------------------------------------------------------------
 * General: Copies the headers field of the Address object into a given buffer.
 *          If the bufferLen is adequate, the function copies the parameter 
 *           into the strBuffer.
 *           Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and
 *           actualLen contains the required buffer length.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hSipAddr   - Handle to the URL address object.
 *        strBuffer  - Buffer to include the requested parameter.
 *        bufferLen  - The length of the given buffer.
 * output:actualLen - The length of the requested parameter + 1, to include a 
 *                     NULL value at the end of the string.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAddrUrlGetHeaders(
                                               IN RvSipAddressHandle hSipAddr,
                                               IN RvChar*           strBuffer,
                                               IN RvUint            bufferLen,
                                               OUT RvUint*          actualLen);


/***************************************************************************
 * RvSipAddrUrlSetHeaders
 * ------------------------------------------------------------------------
 * General: Used to set the headers parameter in the URL address object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hSipUrl    - Handle to the URL address object.
 *    strHeaders - The headers parameter to be set in the object. If NULL is 
 *                 supplied, the existing headers parameter is removed.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAddrUrlSetHeaders(
                                              IN RvSipAddressHandle hSipUrl,
                                              IN RvChar*           strHeaders);

#ifndef RV_SIP_PRIMITIVES
/***************************************************************************
 * RvSipAddrUrlGetHeadersList
 * ------------------------------------------------------------------------
 * General: The function takes the url headers parameter as string, and parse
 *          it into a list of headers.
 *          Application must supply a list structure, and a consecutive buffer
 *          with url headers parameter string.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hSipAddr        - Handle to the address object.
 *    hHeadersList    - A handle to the Address object.
 *    pHeadersBuffer  - Buffer containing a textual url headers parameter string.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAddrUrlGetHeadersList(
                                     IN    RvSipAddressHandle    hSipAddr,
                                     IN    RvSipCommonListHandle hHeadersList,
                                     IN    RvChar*               pHeadersBuffer);

/***************************************************************************
 * RvSipAddrUrlSetHeadersList
 * ------------------------------------------------------------------------
 * General: This function is used to set the Headers param from headers list.
 *          The function encode all headers. during encoding each header
 *          coverts reserved characters to it's escaped form. each header
 *          also set '=' instead of ':' after header name.
 *          This function also sets '&' between headers.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hSipAddr        - Handle to the address object.
 *    hHeadersList    - A handle to the headers list object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAddrUrlSetHeadersList(
                                     IN    RvSipAddressHandle    hSipAddr,
                                     IN    RvSipCommonListHandle hHeadersList);
#endif /*#ifndef RV_SIP_PRIMITIVES*/

/***************************************************************************
 * RvSipAddrUrlGetCompParam
 * ------------------------------------------------------------------------
 * General: Gets the compression type enumeration value from the URL object. If the
 *          returned compression enumeration is RVSIP_COMP_OTHER, you can get
 *          the compression type string by calling RvSipAddrUrlGetStrCompParam().
 * Return Value: Returns the compression Type enumeration value.
 * ------------------------------------------------------------------------
 * Arguments:
 *    input:  hSipAddr - Handle to the URL address object.
 ***************************************************************************/
RVAPI RvSipCompType RVCALLCONV RvSipAddrUrlGetCompParam(
                                           IN RvSipAddressHandle hSipAddr);

/***************************************************************************
 * RvSipAddrUrlGetStrCompParam
 * ------------------------------------------------------------------------
 * General: Copies the compression type string from the URL address object into a given
 *          buffer. Use this function if RvSipAddrUrlGetCompParam() returns
 *          RVSIP_COMP_OTHER.
 *          If the bufferLen is adequate, the function copies the parameter 
 *           into the strBuffer.
 *           Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and
 *           actualLen contains the required buffer length.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    input:  hSipAddr     - Handle to the URL address object.
 *          strBuffer    - Buffer to include the requested parameter.
 *          bufferLen    - The length of the given buffer.
 *  output: actualLen   - The length of the requested parameter + 1, to include NULL character at the end
 *                         of the string.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAddrUrlGetStrCompParam(
                                           IN RvSipAddressHandle hSipAddr,
                                           IN RvChar*           strBuffer,
                                           IN RvUint            bufferLen,
                                           OUT RvUint*          actualLen);

/***************************************************************************
 * RvSipAddrUrlSetCompParam
 * ------------------------------------------------------------------------
 * General:  Sets the compression type value in the URL object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hSipAddr     - Handle to the URL address object.
 *    eComp        - The compression type enumeration value to be set in the object.
 *  strCompParam - You can use this parameter only if the eComp parameter is set to
 *                 RVSIP_COMP_OTHER. In this case you can supply the compression
 *                 type as a string.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAddrUrlSetCompParam(
                                            IN    RvSipAddressHandle hSipAddr,
                                            IN    RvSipCompType     eComp,
                                            IN    RvChar*           strCompParam);


/*-----------------------------------------------------------------------
                  ABS URI - GET AND SET FUNCTIONS                      
   -----------------------------------------------------------------------*/

/***************************************************************************
 * RvSipAddrAbsUriGetScheme
 * ------------------------------------------------------------------------
 * General:  Copies the scheme field from the address object into a given buffer.
 *           If the bufferLen is adequate, the function copies the parameter 
 *           into the strBuffer.
 *           Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and
 *           actualLen contains the required buffer length.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hSipAddr  - Handle to the URL address object.
 *        strBuffer - Buffer to fill with the requested parameter.
 *        bufferLen - The length of the given buffer.
 * output:actualLen - The length of the requested parameter + 1, to include 
 *                    NULL character at the end of the string.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAddrAbsUriGetScheme(IN RvSipAddressHandle hSipAddr,
                                                    IN RvChar*           strBuffer,
                                                    IN RvUint            bufferLen,
                                                    OUT RvUint*          actualLen);

/***************************************************************************
 * RvSipAddrAbsUriSetScheme
 * ------------------------------------------------------------------------
 * General: Sets the scheme string in the absolute URI Address object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hSipAddr - Handle to the absolute URI Address object.
 *    strScheme  - The scheme to be set in the object. If NULL is supplied,
 *             the existing scheme is removed from the Address object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAddrAbsUriSetScheme(IN    RvSipAddressHandle hSipAddr,
                                                    IN    RvChar*           strScheme);


/***************************************************************************
 * RvSipAddrAbsUriGetIdentifier
 * ------------------------------------------------------------------------
 * General:  Copies the Identifier field from the absolute URI address object
 *           into a given buffer.
 *           If the bufferLen is adequate, the function copies the parameter 
 *           into the strBuffer.
 *           Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and
 *           actualLen contains the required buffer length.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hSipAddr  - Handle to the  absolute URI address object.
 *        strBuffer - Buffer to fill with the requested parameter.
 *        bufferLen - The length of the given buffer.
 * output:actualLen - The length of the requested parameter + 1, to include NULL character at the end
 *                    of the string.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAddrAbsUriGetIdentifier(IN RvSipAddressHandle hSipAddr,
                                                        IN RvChar*           strBuffer,
                                                        IN RvUint            bufferLen,
                                                        OUT RvUint*          actualLen);

/***************************************************************************
 * RvSipAddrAbsUriSetIdentifier
 * ------------------------------------------------------------------------
 * General: Sets the Identifier string in the absolute URI Address object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hSipAddr - Handle to the absolute URI Address object.
 *    strIdentifier  - The identifier string to be set in the object. If NULL is supplied,
 *             the existing identifier
 *             is removed from the Address object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAddrAbsUriSetIdentifier(IN    RvSipAddressHandle hSipAddr,
                                                        IN    RvChar*           strIdentifier);


#ifdef __cplusplus
}
#endif


#endif /* RVSIPADDRESS_H */


