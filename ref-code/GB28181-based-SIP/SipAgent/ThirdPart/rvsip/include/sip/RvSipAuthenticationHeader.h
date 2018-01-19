/*

NOTICE:
This document contains information that is proprietary to RADVision LTD..
No part of this publication may be reproduced in any form whatsoever without
written prior approval by RADVision LTD..

RADVision LTD. reserves the right to revise this publication and make changes
without obligation to notify any person of such revisions or changes.

*/

/******************************************************************************
 *                      RvSipAuthenticationHeader.h                           *
 *                                                                            *
 * The file defines the methods of the Authentication header object:          *
 * construct, destruct, copy, encode, parse and the ability to access and     *
 * change it's parameters.                                                    *
 *                                                                            *
 *                                                                            *
 *                                                                            *
 *      Author           Date                                                 *
 *     ------           ------------                                          *
 *    Oren Libis         Jan. 2001                                             *
 ******************************************************************************/

#ifndef RVSIPAUTHENTICATIONHEADER_H
#define RVSIPAUTHENTICATIONHEADER_H

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
 * RvSipAuthenticationHeaderStrings
 * ----------------------
 * This enum defines all the header's strings (for getting it's size).
 * Defines all Authentication header object fields that are kept in the
 * object in a string format.
 */
typedef enum
{
    RVSIP_AUTHENTICATION_AUTHSCHEME,
    RVSIP_AUTHENTICATION_REALM,
    RVSIP_AUTHENTICATION_DOMAIN,
    RVSIP_AUTHENTICATION_NONCE,
    RVSIP_AUTHENTICATION_OPAQUE,
    RVSIP_AUTHENTICATION_ALGORITHM,
    RVSIP_AUTHENTICATION_QOP,
    RVSIP_AUTHENTICATION_OTHER_PARAMS,
    RVSIP_AUTHENTICATION_BAD_SYNTAX
}RvSipAuthenticationHeaderStringName;


/*
 * RvSipAuthenticationHeaderType
 * ----------------------
 * This enum defines the types of authentication headers
 */
typedef enum
{
    RVSIP_AUTH_UNDEFINED_AUTHENTICATION_HEADER = -1,
    RVSIP_AUTH_WWW_AUTHENTICATION_HEADER,
    RVSIP_AUTH_PROXY_AUTHENTICATION_HEADER
}RvSipAuthenticationHeaderType ;


/*-----------------------------------------------------------------------*/
/*                   CONSTRUCTORS AND DESTRUCTORS                        */
/*-----------------------------------------------------------------------*/

/***************************************************************************
 * RvSipAuthenticationHeaderConstructInMsg
 * ------------------------------------------------------------------------
 * General: Constructs an Authentication header object inside a given message object. The
 *          header is kept in the header list of the message. You can choose to insert the
 *          header either at the head or tail of the list.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hSipMsg          - Handle to the message object.
 *         pushHeaderAtHead - Boolean value indicating whether the header should be pushed to the head of the
 *                            list—RV_TRUE—or to the tail—RV_FALSE.
 * output: hHeader          - Handle to the newly constructed Authentication header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthenticationHeaderConstructInMsg(
                                   IN  RvSipMsgHandle                  hSipMsg,
                                   IN  RvBool                         pushHeaderAtHead,
                                   OUT RvSipAuthenticationHeaderHandle *hHeader);


/***************************************************************************
 * RvSipAuthenticationHeaderConstruct
 * ------------------------------------------------------------------------
 * General: Constructs and initializes a stand-alone Authentication Header object. The
 *          header is constructed on a given page taken from a specified pool. The handle to
 *          the new header object is returned.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hMsgMgr - Handle of the message manager.
 *         hPool   - Handle to the memory pool that the object will use.
 *         hPage   - Handle to the memory page that the object will use.
 * output: hHeader - Handle to the newly constructed Authentication header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthenticationHeaderConstruct(
                                           IN  RvSipMsgMgrHandle                hMsgMgr,
                                           IN  HRPOOL                           hPool,
                                           IN  HPAGE                            hPage,
                                           OUT RvSipAuthenticationHeaderHandle* hHeader);


/***************************************************************************
 * RvSipAuthenticationHeaderCopy
 * ------------------------------------------------------------------------
 * General: Copies all fields from a source Authentication header object to a destination
 *          Authentication header object.
 *          You must construct the destination object before using this function.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hDestination - Handle to the destination Authentication header object.
 *    hSource      - Handle to the source Authentication header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthenticationHeaderCopy
                                    (IN    RvSipAuthenticationHeaderHandle hDestination,
                                     IN    RvSipAuthenticationHeaderHandle hSource);


/***************************************************************************
 * RvSipAuthenticationHeaderEncode
 * ------------------------------------------------------------------------
 * General: Encodes a Authentication header object to a textual Authentication header. The
 *          textual header is placed on a page taken from a specified pool. In order to copy
 *          the textual header from the page to a consecutive buffer, use
 *          RPOOL_CopyToExternal().
 *          The application must free the allocated page, using RPOOL_FreePage(). The
 *          allocated page must be freed only if this function returns RV_OK.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader           - Handle to the Authentication header object.
 *        hPool             - Handle to the specified memory pool.
 * output: hPage            - The memory page allocated to contain the encoded header.
 *         length           - The length of the encoded information.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthenticationHeaderEncode(
                                          IN    RvSipAuthenticationHeaderHandle hHeader,
                                          IN    HRPOOL                          hPool,
                                          OUT   HPAGE*                          hPage,
                                          OUT   RvUint32*                      length);


/***************************************************************************
 * RvSipAuthenticationHeaderParse
 * ------------------------------------------------------------------------
 * General:Parses a SIP textual Authentication header into an Authentication header object.
 *         All the textual fields are placed inside the object.
 *         You must construct an Authentication header before using this function.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader   - A handle to the Authentication header object.
 *    buffer    - Buffer containing a textual Authentication header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthenticationHeaderParse(
                                     IN RvSipAuthenticationHeaderHandle hHeader,
                                     IN RvChar*                        buffer);

/***************************************************************************
 * RvSipAuthenticationHeaderParseValue
 * ------------------------------------------------------------------------
 * General: Parses a SIP textual Authentication header value into an
 *          Authentication header object.
 *          A SIP header has the following grammer:
 *          header-name:header-value. This function takes the header-value part as
 *          a parameter and parses it into the supplied object.
 *          All the textual fields are placed inside the object.
 *          Note: Use the RvSipAuthenticationHeaderParse() function to parse
 *          strings that also include the header-name.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader   - The handle to the Authentication header object.
 *    buffer    - The buffer containing a textual Authentication header value.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthenticationHeaderParseValue(
                                     IN RvSipAuthenticationHeaderHandle hHeader,
                                     IN RvChar*                        buffer);

/***************************************************************************
 * RvSipAuthenticationHeaderFix
 * ------------------------------------------------------------------------
 * General: Fixes an Authentication header with bad-syntax information.
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
RVAPI RvStatus RVCALLCONV RvSipAuthenticationHeaderFix(
                                     IN RvSipAuthenticationHeaderHandle hHeader,
                                     IN RvChar*                     pFixedBuffer);

/*-----------------------------------------------------------------------
                         G E T  A N D  S E T  M E T H O D S
 ------------------------------------------------------------------------*/
/***************************************************************************
 * RvSipAuthenticationHeaderGetStringLength
 * ------------------------------------------------------------------------
 * General: Some of the Authentication header fields are kept in a string format—for
 *          example, the nonce parameter. In order to get such a field from the
 *          Authentication header object, your application should supply an adequate buffer
 *          to where the string will be copied.
 *          This function provides you with the length of the string to enable you to allocate
 *          an appropriate buffer size before calling the Get function.
 * Return Value: Returns the length of specified string.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader     - Handle to the Authentication header object.
 *  eStringName - Enumeration of the string name for which you require the length.
 ***************************************************************************/
RVAPI RvUint RVCALLCONV RvSipAuthenticationHeaderGetStringLength(
                                      IN  RvSipAuthenticationHeaderHandle     hHeader,
                                      IN  RvSipAuthenticationHeaderStringName eStringName);


/***************************************************************************
 * RvSipAuthenticationHeaderGetAuthScheme
 * ------------------------------------------------------------------------
 * General: Gets the Authentication scheme enumeration from the Authentication header
 *          object.
 *          If this function returns RVSIP_AUTH_SCHEME_OTHER, call
 *          RvSipAuthenticationHeaderGetStrAuthScheme() to get the actual
 *          Authentication scheme in a string format.
 * Return Value: Returns the Authentication scheme enumeration from the header object.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader - Handle to the Authentication header object.
 ***************************************************************************/
RVAPI RvSipAuthScheme RVCALLCONV RvSipAuthenticationHeaderGetAuthScheme(
                                      IN  RvSipAuthenticationHeaderHandle hHeader);


/***************************************************************************
 * RvSipAuthenticationHeaderGetStrAuthScheme
 * ------------------------------------------------------------------------
 * General: Copies the authentication scheme string value from the Authentication object
 *          into a given buffer.
 *          Use this function if RvSipAuthenticationHeaderGetAuthScheme() returns
 *          RVSIP_AUTH_SCHEME_OTHER.
 *          If the bufferLen is adequate, the function copies the requested parameter into
 *          strBuffer. Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and actualLen
 *          contains the required buffer length.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader    - Handle to the Authentication header object.
 *        strBuffer  - Buffer to fill with the requested parameter.
 *        bufferLen  - The length of the buffer.
 * output:actualLen - The length of the requested parameter, + 1 to include a NULL value at the end of
 *                     the parameter.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthenticationHeaderGetStrAuthScheme(
                                       IN  RvSipAuthenticationHeaderHandle hHeader,
                                       IN  RvChar*                        strBuffer,
                                       IN  RvUint                         bufferLen,
                                       OUT RvUint*                        actualLen);


/***************************************************************************
 * RvSipAuthenticationHeaderSetAuthScheme
 * ------------------------------------------------------------------------
 * General: Sets the authentication scheme in the Authentication header object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader       - Handle to the Authentication header object.
 *  eAuthScheme   - The authentication scheme to be set in the object.
 *    strAuthScheme - Text string giving the authentication scheme to be set in the object. This
 *                  parameter is required when eAuthScheme is
 *                  RVSIP_AUTH_SCHEME_OTHER. Otherwise, the parameter is set to NULL.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthenticationHeaderSetAuthScheme(
                                      IN RvSipAuthenticationHeaderHandle hHeader,
                                      IN RvSipAuthScheme                 eAuthScheme,
                                      IN RvChar*                        strAuthScheme);


/***************************************************************************
 * RvSipAuthenticationHeaderGetRealm
 * ------------------------------------------------------------------------
 * General: Copies the realm value of the Authentication object into a given buffer.
 *          If the bufferLen is adequate, the function copies the requested parameter into
 *          strBuffer. Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and actualLen
 *          contains the required buffer length.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader    - Handle to the header object.
 *        strBuffer  - Buffer to fill with the requested parameter.
 *        bufferLen  - The length of the buffer.
 * output:actualLen - The length of the requested parameter, + 1 to include a NULL value at the end of
 *                     the parameter.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthenticationHeaderGetRealm(
                                           IN RvSipAuthenticationHeaderHandle hHeader,
                                           IN RvChar*                        strBuffer,
                                           IN RvUint                         bufferLen,
                                           OUT RvUint*                       actualLen);

/***************************************************************************
 * RvSipAuthenticationHeaderSetRealm
 * ------------------------------------------------------------------------
 * General:Sets the realm string in the Authentication header object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader  - Handle to the Authentication header object.
 *    pRealm   - The realm to be set in the Authentication header. If a NULL value is supplied,
 *             the existing realm string in the header is removed.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthenticationHeaderSetRealm(
                                     IN RvSipAuthenticationHeaderHandle hHeader,
                                     IN RvChar *                       pRealm);


/***************************************************************************
 * RvSipAuthenticationHeaderGetDomain
 * ------------------------------------------------------------------------
 * General: Copies the domain value of the Authentication object into a given buffer.
 *          If the bufferLen is adequate, the function copies the requested parameter into
 *          strBuffer. Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and actualLen
 *          contains the required buffer length.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader    - Handle to the Authentication header object.
 *        strBuffer  - Buffer to fill with the requested parameter.
 *        bufferLen  - The length of the buffer.
 * output:actualLen - The length of the requested parameter, + 1 to include a NULL value at the end of
 *                     the parameter.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthenticationHeaderGetDomain(
                                           IN RvSipAuthenticationHeaderHandle hHeader,
                                           IN RvChar*                        strBuffer,
                                           IN RvUint                         bufferLen,
                                           OUT RvUint*                       actualLen);

/***************************************************************************
 * RvSipAuthenticationHeaderSetDomain
 * ------------------------------------------------------------------------
 * General: Sets the domain string in the Authentication header object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader  - Handle to the Authentication header object.
 *    pDomain  - The domain to be set in the Authentication header. If a NULL value is supplied,
 *             the existing domain string in the header is removed.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthenticationHeaderSetDomain(
                                     IN RvSipAuthenticationHeaderHandle hHeader,
                                     IN RvChar *                       pDomain);


/***************************************************************************
 * RvSipAuthenticationHeaderGetNonce
 * ------------------------------------------------------------------------
 * General: Copies the nonce value of the Authentication object into a given buffer.
 *          If the bufferLen is adequate, the function copies the requested parameter into
 *          strBuffer. Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and actualLen
 *          contains the required buffer length.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader    - Handle to the Authentication header object.
 *        strBuffer  - Buffer to fill with the requested parameter.
 *        bufferLen  - The length of the buffer.
 * output:actualLen - The length of the requested parameter, + 1 to include a NULL value at the end of
 *                     the parameter.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthenticationHeaderGetNonce(
                                           IN RvSipAuthenticationHeaderHandle hHeader,
                                           IN RvChar*                        strBuffer,
                                           IN RvUint                         bufferLen,
                                           OUT RvUint*                       actualLen);

/***************************************************************************
 * RvSipAuthenticationHeaderSetNonce
 * ------------------------------------------------------------------------
 * General: Sets the nonce string in the Authentication header object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader  - Handle to the Authentication header object.
 *    pNonce   - The nonce to be set in the Authentication header. If a NULL value is supplied,
 *             the existing nonce string in the header is removed.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthenticationHeaderSetNonce(
                                     IN RvSipAuthenticationHeaderHandle hHeader,
                                     IN RvChar *                       pNonce);


/***************************************************************************
 * RvSipAuthenticationHeaderGetOpaque
 * ------------------------------------------------------------------------
 * General: Copies the opaque value of the Authentication object into a given buffer.
 *          If the bufferLen is adequate, the function copies the requested parameter into
 *          strBuffer. Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and actualLen
 *          contains the required buffer length.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader    - Handle to the Authentication header object.
 *        strBuffer  - Buffer to fill with the requested parameter.
 *        bufferLen  - The length of the buffer.
 * output:actualLen - The length of the requested parameter, + 1 to include a NULL value at the end of
 *                     the parameter.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthenticationHeaderGetOpaque(
                                           IN RvSipAuthenticationHeaderHandle hHeader,
                                           IN RvChar*                        strBuffer,
                                           IN RvUint                         bufferLen,
                                           OUT RvUint*                       actualLen);

/***************************************************************************
 * RvSipAuthenticationHeaderSetOpaque
 * ------------------------------------------------------------------------
 * General:Sets the opaque string in the Authentication header object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader   - Handle to the Authentication header object.
 *    pOpaque   - The opaque string to be set in the Authentication header. If a NULL value is
 *              supplied, the existing opaque string in the header is removed.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthenticationHeaderSetOpaque(
                                     IN RvSipAuthenticationHeaderHandle hHeader,
                                     IN RvChar *                       pOpaque);


/***************************************************************************
 * RvSipAuthenticationHeaderGetStrQop
 * ------------------------------------------------------------------------
 * General: Copies the Qop string value of the Authentication object into a given buffer.
 *          If the bufferLen is adequate, the function copies the requested parameter into
 *          strBuffer. Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and actualLen
 *          contains the required buffer length.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader    - Handle to the Authentication header object.
 *        strBuffer  - Buffer to fill with the requested parameter.
 *        bufferLen  - The length of the buffer.
 * output:actualLen - The length of the requested parameter, + 1 to include a NULL value at the end of
 *                     the parameter.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthenticationHeaderGetStrQop(
                                           IN RvSipAuthenticationHeaderHandle hHeader,
                                           IN RvChar*                        strBuffer,
                                           IN RvUint                         bufferLen,
                                           OUT RvUint*                       actualLen);

/***************************************************************************
 * RvSipAuthenticationHeaderSetStrQop
 * ------------------------------------------------------------------------
 * General:Sets the Qop string in the Authentication header object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader  - Handle to the Authentication header object.
 *    pQop     - The Qop string to be set in the Authentication header. If a NULL value is supplied, the
 *             existing Qop string in the header is removed.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthenticationHeaderSetStrQop(
                                     IN RvSipAuthenticationHeaderHandle hHeader,
                                     IN RvChar *                       pQop);


/***************************************************************************
 * RvSipAuthenticationHeaderGetOtherParams
 * ------------------------------------------------------------------------
 * General: Copies the Authentication header other params field of the Authentication
 *          header object into a given buffer.
 *          Not all the Authentication header parameters have separated fields in the
 *          Authentication header object. Parameters with no specific fields are refered to as
 *          other params. They are kept in the object in one concatenated string in the
 *          form—”name=value;name=value...”
 *          If the bufferLen is adequate, the function copies the requested parameter into
 *          strBuffer. Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and actualLen
 *          contains the required buffer length.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader    - Handle to the Authentication header object.
 *        strBuffer  - Buffer to fill with the requested parameter.
 *        bufferLen  - The length of the buffer.
 * output:actualLen - The length of the requested parameter, + 1 to include a NULL value at the end of
 *                     the parameter.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthenticationHeaderGetOtherParams(
                                           IN RvSipAuthenticationHeaderHandle hHeader,
                                           IN RvChar*                        strBuffer,
                                           IN RvUint                         bufferLen,
                                           OUT RvUint*                       actualLen);

/***************************************************************************
 * RvSipAuthenticationHeaderSetOtherParams
 * ------------------------------------------------------------------------
 * General: Sets the other params field in the Authentication header object.
 *          Not all the Party header parameters have separated fields in the Party header
 *          object. Parameters with no specific fields are refered to as other params. They
 *          are kept in the object in one concatenated string in the form—
 *          ”name=value;name=value...”.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader      - Handle to the Authentication header object.
 *    pOtherParams - The other params field to be set in the Authentication header. If NULL is
 *                 supplied, the existing other params field is removed from the header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthenticationHeaderSetOtherParams(
                                     IN RvSipAuthenticationHeaderHandle hHeader,
                                     IN RvChar *                       pOtherParams);


/***************************************************************************
 * RvSipAuthenticationHeaderGetStale
 * ------------------------------------------------------------------------
 * General: Gets the stale enumeration from the Authentication Header object.
 * Return Value: Returns the stale enumeration from the header object
 * ------------------------------------------------------------------------
 * Arguments:
 *    hSipAuthHeader - Handle to the Authentication header object.
 ***************************************************************************/
RVAPI RvSipAuthStale RVCALLCONV RvSipAuthenticationHeaderGetStale(
                                    IN RvSipAuthenticationHeaderHandle hSipAuthHeader);


/***************************************************************************
 * RvSipAuthenticationHeaderSetStale
 * ------------------------------------------------------------------------
 * General: Sets the stale field in the Authentication Header object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hSipAuthHeader - Handle to the Authentication header object.
 *    eStale         - The stale value to be set in the object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthenticationHeaderSetStale(
                                 IN RvSipAuthenticationHeaderHandle hSipAuthHeader,
                                 IN RvSipAuthStale                  eStale);


/***************************************************************************
 * RvSipAuthenticationHeaderGetAuthAlgorithm
 * ------------------------------------------------------------------------
 * General: Gets the algorithm type enumeration from the Authentication header object.
 *          If this function returns RVSIP_AUTH_ALGORITHM_OTHER, call
 *          RvSipAuthenticationHeaderGetStrAuthAlgorithm(), to get the actual algorithm
 *          type in a string format.
 * Return Value: Returns the algorithm type enumeration of the header object.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader - Handle to the Authentication header object.
 ***************************************************************************/
RVAPI RvSipAuthAlgorithm RVCALLCONV RvSipAuthenticationHeaderGetAuthAlgorithm(
                                      IN  RvSipAuthenticationHeaderHandle hHeader);



/***************************************************************************
 * RvSipAuthenticationHeaderGetStrAuthAlgorithm
 * ------------------------------------------------------------------------
 * General: Copies the authentication algorithm string from the Authentication header
 *          object into a given buffer.
 *          If the bufferLen is adequate, the function copies the requested parameter into
 *          strBuffer. Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and actualLen
 *          contains the required buffer length.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader    - Handle to the Authentication header object.
 *        strBuffer  - Buffer to fill with the requested parameter.
 *        bufferLen  - The length of the buffer.
 * output:actualLen - The length of the requested parameter, + 1 to include a NULL value at the end of
 *        the parameter.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthenticationHeaderGetStrAuthAlgorithm(
                                           IN  RvSipAuthenticationHeaderHandle hHeader,
                                           IN  RvChar*                        strBuffer,
                                           IN  RvUint                         bufferLen,
                                           OUT RvUint*                        actualLen);

/***************************************************************************
 * RvSipAuthenticationHeaderSetAuthAlgorithm
 * ------------------------------------------------------------------------
 * General: Sets the authentication algorithm in Authentication object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader           - Handle to the Authentication header object.
 *  eAuthAlgorithm    - The authentication scheme to be set in the object.
 *    strAuthAlgorithm  - Text string giving the authentication algorithm to be set in the object. Use this
 *                      parameter only if eAuthAlgorithm is set to
 *                      RVSIP_AUTH_ALGORITHM_OTHER. Otherwise, the parameter is NULL.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthenticationHeaderSetAuthAlgorithm(
                                      IN    RvSipAuthenticationHeaderHandle    hHeader,
                                      IN    RvSipAuthAlgorithm                 eAuthAlgorithm,
                                      IN    RvChar                            *strAuthAlgorithm);



/***************************************************************************
 * RvSipAuthenticationHeaderGetQopOption
 * ------------------------------------------------------------------------
 * General: Gets the Qop option from the Authentication header object.
 * Return Value: The Qop option from the header object.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader - Handle to the Authentication header object.
 ***************************************************************************/
RVAPI RvSipAuthQopOption  RVCALLCONV RvSipAuthenticationHeaderGetQopOption(
                                      IN  RvSipAuthenticationHeaderHandle hHeader);


/***************************************************************************
 * RvSipAuthenticationHeaderSetQopOption
 * ------------------------------------------------------------------------
 * General: Sets the Qop option enumeration in the Authentication Header object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hSipAuthHeader           - Handle to the Authentication header object.
 *    eQop                     - The Qop option enumeration to be set in the object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthenticationHeaderSetQopOption(
                                 IN RvSipAuthenticationHeaderHandle hSipAuthHeader,
                                 IN RvSipAuthQopOption              eQop);



/***************************************************************************
 * RvSipAuthenticationHeaderGetHeaderType
 * ------------------------------------------------------------------------
 * General: Gets the header type enumeration from the Authentication Header object.
 * Return Value: Returns the Authentication header type enumeration from the header object.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hSipAuthHeader - Handle to the Authentication header object.
 ***************************************************************************/
RVAPI RvSipAuthenticationHeaderType  RVCALLCONV RvSipAuthenticationHeaderGetHeaderType(
                                                    IN RvSipAuthenticationHeaderHandle hSipAuthHeader);

/***************************************************************************
 * RvSipAuthenticationHeaderSetHeaderType
 * ------------------------------------------------------------------------
 * General: Sets the header type in the Authentication Header object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hSipAuthnHeader - Handle to the Authentication header object.
 *    eHeaderType     - The header type to be set in the object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthenticationHeaderSetHeaderType(
                                 IN RvSipAuthenticationHeaderHandle hSipAuthHeader,
                                 IN RvSipAuthenticationHeaderType   eHeaderType);

/***************************************************************************
 * RvSipAuthenticationHeaderGetStrBadSyntax
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
 *          implementation if the message contains a bad Authentication header,
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
RVAPI RvStatus RVCALLCONV RvSipAuthenticationHeaderGetStrBadSyntax(
                                           IN RvSipAuthenticationHeaderHandle hHeader,
                                           IN RvChar*                        strBuffer,
                                           IN RvUint                         bufferLen,
                                           OUT RvUint*                       actualLen);

/***************************************************************************
 * RvSipAuthenticationHeaderSetStrBadSyntax
 * ------------------------------------------------------------------------
 * General: Sets a bad-syntax string in the object.
 *          A SIP header has the following grammer:
 *          header-name:header-value. When a header contains a syntax error,
 *          the header-value is kept as a separate "bad-syntax" string.
 *          By using this function you can create a header with "bad-syntax".
 *          Setting a bad syntax string to the header will mark the header as
 *          an invalid syntax header.
 *          You can use his function when you want to send an illegal Authentication header.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader      - The handle to the header object.
 *  strBadSyntax - The bad-syntax string.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthenticationHeaderSetStrBadSyntax(
                                  IN RvSipAuthenticationHeaderHandle hHeader,
                                  IN RvChar*                     strBadSyntax);

/***************************************************************************
 * RvSipAuthenticationHeaderGetRpoolString
 * ------------------------------------------------------------------------
 * General: Copy a string parameter from the Authentication header into a given page
 *          from a specified pool. The copied string is not consecutive.
 * Return Value: RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input: hSipAuthHeader - Handle to the Authentication header object.
 *           eStringName   - The string the user wish to get
 *  Input/Output:
 *         pRpoolPtr     - pointer to a location inside an rpool. You need to
 *                         supply only the pool and page. The offset where the
 *                         returned string was located will be returned as an
 *                         output patameter.
 *                         If the function set the returned offset to
 *                         UNDEFINED is means that the parameter was not
 *                         set to the Authentication header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthenticationHeaderGetRpoolString(
                             IN    RvSipAuthenticationHeaderHandle      hSipAuthHeader,
                             IN    RvSipAuthenticationHeaderStringName  eStringName,
                             INOUT RPOOL_Ptr                 *pRpoolPtr);
/***************************************************************************
 * RvSipAuthenticationHeaderSetRpoolString
 * ------------------------------------------------------------------------
 * General: Sets a string into a specified parameter in the Authentication header
 *          object. The given string is located on an RPOOL memory and is
 *          not consecutive.
 * Return Value: RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input: hSipAuthHeader - Handle to the Authentication header object.
 *           eStringName   - The string the user wish to set
 *         pRpoolPtr     - pointer to a location inside an rpool where the
 *                         new string is located.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthenticationHeaderSetRpoolString(
                             IN    RvSipAuthenticationHeaderHandle      hSipAuthHeader,
                             IN    RvSipAuthenticationHeaderStringName  eStringName,
                             IN    RPOOL_Ptr                 *pRpoolPtr);



#ifdef __cplusplus
}
#endif

#endif /*RVSIPAUTHENTICATIONHEADER_H*/
