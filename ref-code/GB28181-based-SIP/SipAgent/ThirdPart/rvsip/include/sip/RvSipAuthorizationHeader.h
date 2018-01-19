/*

NOTICE:
This document contains information that is proprietary to RADVision LTD..
No part of this publication may be reproduced in any form whatsoever without
written prior approval by RADVision LTD..

RADVision LTD. reserves the right to revise this publication and make changes
without obligation to notify any person of such revisions or changes.

*/

/******************************************************************************
 *                     RvSipAuthorizationHeader.h                             *
 *                                                                            *
 * The file defines the methods of the Authorization header object:           *
 * construct, destruct, copy, encode, parse and the ability to access and     *
 * change it's parameters.                                                    *
 *                                                                            *
 *                                                                            *
 *                                                                            *
 *      Author           Date                                                 *
 *     ------           ------------                                          *
 *    Oren Libis         Jan. 2001                                            *
 ******************************************************************************/

#ifndef RVSIPAUTHORIZATIONHEADER_H
#define RVSIPAUTHORIZATIONHEADER_H

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
 * RvSipAuthorizationHeaderStringName
 * ----------------------
 * This enum defines all the header's strings (for getting it's size)
 * Defines all Authorization header object fields that are kept in the 
 * object in a string format.
 */
typedef enum
{
    RVSIP_AUTHORIZATION_AUTHSCHEME,
    RVSIP_AUTHORIZATION_USERNAME,
    RVSIP_AUTHORIZATION_REALM,
    RVSIP_AUTHORIZATION_NONCE,
    RVSIP_AUTHORIZATION_CNONCE,
    RVSIP_AUTHORIZATION_URI,
    RVSIP_AUTHORIZATION_OPAQUE,
    RVSIP_AUTHORIZATION_QOP,
    RVSIP_AUTHORIZATION_RESPONSE,
    RVSIP_AUTHORIZATION_ALGORITHM,
    RVSIP_AUTHORIZATION_OTHER_PARAMS,
    RVSIP_AUTHORIZATION_BAD_SYNTAX
}RvSipAuthorizationHeaderStringName;



/*
 * RvSipAuthorizationHeaderType
 * ----------------------
 * This enum defines the types of authorization headers
 */
typedef enum
{
    RVSIP_AUTH_UNDEFINED_AUTHORIZATION_HEADER = -1,
    RVSIP_AUTH_AUTHORIZATION_HEADER,
    RVSIP_AUTH_PROXY_AUTHORIZATION_HEADER
}RvSipAuthorizationHeaderType;


/*-----------------------------------------------------------------------*/
/*                   CONSTRUCTORS AND DESTRUCTORS                        */
/*-----------------------------------------------------------------------*/

/***************************************************************************
 * RvSipAuthorizationHeaderConstructInMsg
 * ------------------------------------------------------------------------
 * General: Constructs an Authorization header object inside a given message object. The
 *          header is kept in the header list of the message. You can choose to insert the
 *          header either at the head or tail of the list.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hSipMsg          - Handle to the message object.
 *         pushHeaderAtHead - Boolean value indicating whether the header should be pushed to the head of the
 *                            list—RV_TRUE—or to the tail—RV_FALSE.
 * output: hHeader          - Handle to the newly constructed Authorization header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthorizationHeaderConstructInMsg(
                                   IN  RvSipMsgHandle                  hSipMsg,
                                   IN  RvBool                         pushHeaderAtHead,
                                   OUT RvSipAuthorizationHeaderHandle *hHeader);


/***************************************************************************
 * RvSipAuthorizationHeaderConstruct
 * ------------------------------------------------------------------------
 * General: Constructs and initializes a stand-alone Authorization Header object. The header
 *          is constructed on a given page taken from a specified pool. The handle to the
 *          new header object is returned.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hMsgMgr - Handle to the message manager.
 *         hPool   - Handle to the memory pool that the object will use.
 *         hPage   - Handle to the memory page that the object will use.
 * output: hHeader - Handle to the newly constructed Authorization header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthorizationHeaderConstruct(
                                           IN  RvSipMsgMgrHandle                hMsgMgr,
                                           IN  HRPOOL                           hPool,
                                           IN  HPAGE                            hPage,
                                           OUT RvSipAuthorizationHeaderHandle   *hHeader);


/***************************************************************************
 * RvSipAuthorizationHeaderCopy
 * ------------------------------------------------------------------------
 * General: Copies all fields from a source Authorization header object to a destination
 *          Authorization header object.
 *          You must construct the destination object before using this function.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hDestination - Handle to the destination Authorization header object.
 *    hSource      - Handle to the source Authorization header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthorizationHeaderCopy
                                    (IN    RvSipAuthorizationHeaderHandle hDestination,
                                     IN    RvSipAuthorizationHeaderHandle hSource);


/***************************************************************************
 * RvSipAuthorizationHeaderEncode
 * ------------------------------------------------------------------------
 * General: Encodes an Authorization header object to a textual Authorization header. The
 *          textual header is placed on a page taken from a specified pool. In order to copy
 *          the textual header from the page to a consecutive buffer, use
 *          RPOOL_CopyToExternal().
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader           - Handle to the Authorization header object.
 *        hPool             - Handle to the specified memory pool.
 * output: hPage            - The memory page allocated to contain the encoded header.
 *         length           - The length of the encoded information.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthorizationHeaderEncode(
                                          IN    RvSipAuthorizationHeaderHandle  hHeader,
                                          IN    HRPOOL                          hPool,
                                          OUT   HPAGE*                          hPage,
                                          OUT   RvUint32*                      length);


/***************************************************************************
 * RvSipAuthorizationHeaderParse
 * ------------------------------------------------------------------------
 * General: Parses a SIP textual Authorization header into an Authorization header object.
 *          All the textual fields are placed inside the object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader   - Handle to the Authorization header object.
 *    buffer    - Buffer containing a textual Authorization header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthorizationHeaderParse(
                                     IN    RvSipAuthorizationHeaderHandle  hHeader,
                                     IN    RvChar*                        buffer);

/***************************************************************************
 * RvSipAuthorizationHeaderParseValue
 * ------------------------------------------------------------------------
 * General: Parses a SIP textual Authorization header value into an Authorization header object.
 *          A SIP header has the following grammer:
 *          header-name:header-value. This function takes the header-value part as
 *          a parameter and parses it into the supplied object.
 *          All the textual fields are placed inside the object.
 *          Note: Use the RvSipAuthorizationHeaderParse() function to parse strings that also
 *          include the header-name.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader   - The handle to the Authorization header object.
 *    buffer    - The buffer containing a textual Authorization header value.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthorizationHeaderParseValue(
                                     IN RvSipAuthorizationHeaderHandle  hHeader,
                                     IN RvChar*                        buffer);

/***************************************************************************
 * RvSipAuthorizationHeaderFix
 * ------------------------------------------------------------------------
 * General: Fixes an Authorization header with bad-syntax information.
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
RVAPI RvStatus RVCALLCONV RvSipAuthorizationHeaderFix(
                                     IN RvSipAuthorizationHeaderHandle hHeader,
                                     IN RvChar*                       pFixedBuffer);

/*-----------------------------------------------------------------------
                         G E T  A N D  S E T  M E T H O D S
 ------------------------------------------------------------------------*/
/***************************************************************************
 * RvSipAuthorizationHeaderGetStringLength
 * ------------------------------------------------------------------------
 * General: Some of the Authorization header fields are kept in a string format—for
 *          example, the Authorization header user name string. In order to get such a field
 *          from the Authorization header object, your application should supply an
 *          adequate buffer to where the string will be copied.
 *          This function provides you with the length of the string to enable you to allocate
 *          an appropriate buffer size before calling the Get function.
 * Return Value: Returns the length of the specified string.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader     - Handle to the Authorization header object.
 *  eStringName - Enumeration of the string name for which you require the length.
 ***************************************************************************/
RVAPI RvUint RVCALLCONV RvSipAuthorizationHeaderGetStringLength(
                                      IN  RvSipAuthorizationHeaderHandle     hHeader,
                                      IN  RvSipAuthorizationHeaderStringName eStringName);

/***************************************************************************
 * RvSipAuthorizationHeaderGetCredentialIdentifier
 * ------------------------------------------------------------------------
 * General: Gets the Identifiers of the crededtials Authentication header.
 *          This function will return the realm and username strings,
 *          without quotation marks!!
 *          If you want this parameters in quotation marks, use the specific
 *          get functions, and not this function.
 *          If the realmLen or usernameLen is adequate, the function copies the
 *          strings into strRealm and strUsername buffers,
 *          Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and realmActualLen
 *          and usernameActualLen contain the required buffer length.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
  * input: hHeader          - Handle to the header object.
 *        strRealmBuff     - Buffer to fill with the realm parameter.
 *        realmBuffLen     - The length of the given realm buffer.
 *        strUsernameBuff  - Buffer to fill with the username parameter.
 *        usernameBuffLen  - The length of the username given buffer.
 *        strNonceBuff     - Buffer to fill with the nonce parameter.
 *        nonceBuffLen     - The length of the nonce given buffer.
 * output:realmActualLen   - The length of the realm parameter, + 1 to include
 *                           a NULL value at the end.
 *        usernameActualLen- The length of the username parameter, + 1 to include
 *                           a NULL value at the end.
 *        nonceActualLen   - The length of the nonce parameter, + 1 to include
 *                           a NULL value at the end.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthorizationHeaderGetCredentialIdentifier(
                               IN  RvSipAuthorizationHeaderHandle hHeader,
                               IN  RvChar*                       strRealmBuff,
                               IN  RvUint                        realmBuffLen,
                               IN  RvChar*                       strUsernameBuff,
                               IN  RvUint                        usernameBuffLen,
                               IN  RvChar*                       strNonceBuff,
                               IN  RvUint                        nonceBuffLen,
                               OUT RvUint*                       realmActualLen,
                               OUT RvUint*                       usernameActualLen,
                               OUT RvUint*                       nonceActualLen);

/***************************************************************************
 * RvSipAuthorizationHeaderGetAuthScheme
 * ------------------------------------------------------------------------
 * General: Gets the Authentication scheme enumeration value from the Authorization
 *          header object.
 * Return Value: The Unauthentication scheme enumeration from the object.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader - Handle to the Authorization header object.
 ***************************************************************************/
RVAPI RvSipAuthScheme RVCALLCONV RvSipAuthorizationHeaderGetAuthScheme(
                                      IN  RvSipAuthorizationHeaderHandle hHeader);

/***************************************************************************
 * RvSipAuthorizationHeaderGetStrAuthScheme
 * ------------------------------------------------------------------------
 * General: Gets the Authentication scheme string value from the Authorization header
 *          object.
 *          Use this function if RvSipAuthorizationHeaderGetAuthScheme() returns
 *          RVSIP_AUTH_SCHEME_OTHER.
 *          If the bufferLen is adequate, the function copies the requested parameter into
 *          strBuffer. Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and actualLen
 *          contains the required buffer length.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader    - Handle to the header object.
 *        strBuffer  - Buffer to fill with the requested parameter.
 *        bufferLen  - The length of the buffer.
 * output:actualLen - The length of the requested parameter, + 1 to include a NULL value at the end.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthorizationHeaderGetStrAuthScheme(
                                       IN  RvSipAuthorizationHeaderHandle hHeader,
                                       IN  RvChar*                       strBuffer,
                                       IN  RvUint                        bufferLen,
                                       OUT RvUint*                       actualLen);

/***************************************************************************
 * RvSipAuthorizationHeaderSetAuthScheme
 * ------------------------------------------------------------------------
 * General: Sets the Authentication scheme in the Authorization header object.
 *          If eAuthScheme is RVSIP_AUTH_SCHEME_OTHER, strAuthScheme is
 *          copied to the header. Otherwise, strAuthScheme is ignored.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader       - Handle to the Authorization header object.
 *  eAuthScheme   - The Authentication scheme to be set in the object.
 *    strAuthScheme - Text string giving the Authentication scheme to be set in the object. Use this
 *                  parameter only if eAuthScheme is RVSIP_AUTH_SCHEME_OTHER.
 *                  Otherwise, the parameter is set to NULL.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthorizationHeaderSetAuthScheme(
                                      IN    RvSipAuthorizationHeaderHandle  hHeader,
                                      IN    RvSipAuthScheme                 eAuthScheme,
                                      IN    RvChar*                        strAuthScheme);



/***************************************************************************
 * RvSipAuthorizationHeaderGetRealm
 * ------------------------------------------------------------------------
 * General: Copies the realm string from the Authorization header into a given buffer.
 *          If the bufferLen is adequate, the function copies the requested parameter into
 *          strBuffer. Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and actualLen
 *          contains the required buffer length.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader    - Handle to the Authorization header object.
 *        strBuffer  - Buffer to fill with the requested parameter.
 *        bufferLen  - The length of the buffer.
 * output:actualLen - The length of the requested parameter, + 1 to include a NULL value at the end of
 *                     the parameter.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthorizationHeaderGetRealm(
                                           IN RvSipAuthorizationHeaderHandle  hHeader,
                                           IN RvChar*                        strBuffer,
                                           IN RvUint                         bufferLen,
                                           OUT RvUint*                       actualLen);


/***************************************************************************
 * RvSipAuthorizationHeaderSetRealm
 * ------------------------------------------------------------------------
 * General:Sets the realm string in the Authorization header object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader  - Handle to the Authorization header object.
 *    pRealm   - The realm string to be set in the Authorization header. If NULL is supplied, the
 *             existing realm is removed from the header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthorizationHeaderSetRealm(
                                     IN    RvSipAuthorizationHeaderHandle hHeader,
                                     IN    RvChar *                       pRealm);




/***************************************************************************
 * RvSipAuthorizationHeaderGetNonce
 * ------------------------------------------------------------------------
 * General: Copies the Nonce string from the Authorization header into a given buffer.
 *          If the bufferLen is adequate, the function copies the requested parameter into
 *          strBuffer. Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and actualLen
 *          contains the required buffer length.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader    - Handle to the Authorization header object.
 *        strBuffer  - Buffer to fill with the requested parameter.
 *        bufferLen  - The length of the buffer.
 * output:actualLen - The length of the requested parameter, + 1 to include a NULL value at the end of
 *                     the parameter.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthorizationHeaderGetNonce(
                                           IN RvSipAuthorizationHeaderHandle  hHeader,
                                           IN RvChar*                        strBuffer,
                                           IN RvUint                         bufferLen,
                                           OUT RvUint*                       actualLen);


/***************************************************************************
 * RvSipAuthorizationHeaderSetNonce
 * ------------------------------------------------------------------------
 * General:Sets the nonce string in the Authorization header object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader  - Handle to the Authorization header object.
 *    pNonce   - The nonce string to be set in the Authorization header. If a NULL value is
 *             supplied, the existing nonce string in the header object is removed.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthorizationHeaderSetNonce(
                                     IN    RvSipAuthorizationHeaderHandle hHeader,
                                     IN    RvChar *                       pNonce);


/***************************************************************************
 * RvSipAuthorizationHeaderGetOpaque
 * ------------------------------------------------------------------------
 * General: Copies the opaque string from the Authorization header into a given buffer.
 *          If the bufferLen is adequate, the function copies the requested parameter into
 *          strBuffer. Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and actualLen
 *          contains the required buffer length.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader    - Handle to the Authorization header object.
 *        strBuffer  - Buffer to fill with the requested parameter.
 *        bufferLen  - The length of the buffer.
 * output:actualLen - The length of the requested parameter, + 1 to include a NULL value at the end of
 *                     the parameter.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthorizationHeaderGetOpaque(
                                           IN RvSipAuthorizationHeaderHandle hHeader,
                                           IN RvChar*                        strBuffer,
                                           IN RvUint                         bufferLen,
                                           OUT RvUint*                       actualLen);

/***************************************************************************
 * RvSipAuthorizationHeaderSetOpaque
 * ------------------------------------------------------------------------
 * General:Sets the opaque string in the Authorization header object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader  - Handle to the Authorization header object.
 *    pOpaque  - The opaque string to be set in the Authorization header. If a NULL value is
 *             supplied, the existing opaque string in the header is removed.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthorizationHeaderSetOpaque(
                                     IN    RvSipAuthorizationHeaderHandle hHeader,
                                     IN    RvChar *                      pOpaque);

/***************************************************************************
 * RvSipAuthorizationHeaderGetUserName
 * ------------------------------------------------------------------------
 * General: Copies the user name string from the Authorization header into a given buffer.
 *          If the bufferLen is adequate, the function copies the requested parameter into
 *          strBuffer. Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and actualLen
 *          contains the required buffer length.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader    - Handle to the Authorization header object.
 *        strBuffer  - Buffer to fill with the requested parameter.
 *        bufferLen  - The length of the buffer.
 * output:actualLen - The length of the requested parameter, + 1 to include a NULL value at the end of
 *                     the parameter.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthorizationHeaderGetUserName(
                                           IN RvSipAuthorizationHeaderHandle  hHeader,
                                           IN RvChar*                        strBuffer,
                                           IN RvUint                         bufferLen,
                                           OUT RvUint*                       actualLen);

/***************************************************************************
 * RvSipAuthorizationHeaderSetUserName
 * ------------------------------------------------------------------------
 * General:Sets the user name string in the Authorization header object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader   - Handle to the Authorization header object.
 *    pUserName - The user name string to be set in the Authorization header. If a NULL value is
 *              supplied, the existing user name string in the header is removed.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthorizationHeaderSetUserName(
                                     IN    RvSipAuthorizationHeaderHandle  hHeader,
                                     IN    RvChar *                       pUserName);




/***************************************************************************
 * RvSipAuthorizationHeaderGetOtherParams
 * ------------------------------------------------------------------------
 * General: Copies the other params field of the Authorization
 *          header object into a given buffer.
 *          Not all the Authorization header parameters have separated fields in the
 *          Authorization header object. Parameters with no specific fields are refered to as
 *          other params. They are kept in the object in one concatenated string in the
 *          form—”name=value;name=value...?
 *          If the bufferLen is adequate, the function copies the requested parameter into
 *          strBuffer. Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and actualLen
 *          contains the required buffer length.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader    - Handle to the Authorization header object.
 *        strBuffer  - Buffer to fill with the requested parameter.
 *        bufferLen  - The length of the buffer.
 * output:actualLen - The length of the requested parameter, + 1 to include a NULL value at the end of
 *                     the parameter.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthorizationHeaderGetOtherParams(
                                           IN RvSipAuthorizationHeaderHandle  hHeader,
                                           IN RvChar*                        strBuffer,
                                           IN RvUint                         bufferLen,
                                           OUT RvUint*                       actualLen);


/***************************************************************************
 * RvSipAuthorizationHeaderSetOtherParams
 * ------------------------------------------------------------------------
 * General:Sets the other params field in the Authorization header object.
 *         Not all the Party header parameters have separated fields in the Party header
 *         object. Parameters with no specific fields are refered to as other params. They
 *         are kept in the object in one concatenated string in the form?
 *         ”name=value;name=value...?
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader       - Handle to the Authorization header object.
 *    pOtherParams  - The other params field to be set in the Authorization header. If NULL is
 *                  supplied, the existing other params field is removed from the header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthorizationHeaderSetOtherParams(
                                     IN    RvSipAuthorizationHeaderHandle  hHeader,
                                     IN    RvChar *                       strOtherParams);



/***************************************************************************
 * RvSipAuthorizationHeaderGetNonceCount
 * ------------------------------------------------------------------------
 * General: Gets the nonce count value from the Authorization Header object.
 * Return Value: Returns the nonce count value.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hSipAuthHeader - Handle to the Authorization header object.
 ***************************************************************************/
RVAPI RvInt32 RVCALLCONV RvSipAuthorizationHeaderGetNonceCount(
                                    IN RvSipAuthorizationHeaderHandle hSipAuthHeader);

/***************************************************************************
 * RvSipAuthorizationHeaderSetNonceCount
 * ------------------------------------------------------------------------
 * General: Sets the nonce count value in the Authorization Header object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hSipAuthHeader          - Handle to the Authorization header object.
 *    nonceCount              - The nonce count value to be set in the object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthorizationHeaderSetNonceCount(
                                 IN    RvSipAuthorizationHeaderHandle hSipAuthHeader,
                                 IN    RvInt32                       nonceCount);


/***************************************************************************
 * RvSipAuthorizationHeaderGetAuthAlgorithm
 * ------------------------------------------------------------------------
 * General: Gets the authentication algorithm enumeration from the Authorization header
 *          object.
 *          if this function returns RVSIP_AUTH_ALGORITHM_OTHER, call
 *          RvSipAuthorizationHeaderGetStrAuthAlgorithm() to get the algorithm in a
 *          string format.
 * Return Value: Returns the authentication algorithm enumeration from the header object.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader - Handle to the Authorization header object.
 ***************************************************************************/
RVAPI RvSipAuthAlgorithm RVCALLCONV RvSipAuthorizationHeaderGetAuthAlgorithm(
                                      IN  RvSipAuthorizationHeaderHandle hHeader);


/***************************************************************************
 * RvSipAuthorizationHeaderGetStrAuthAlgorithm
 * ------------------------------------------------------------------------
 * General: Copies the authentication algorithm string from the Authorization header object
 *          into a given buffer. Use this function if
 *          RvSipAuthorizationHeaderGetAuthAlgorithm() returns
 *          RVSIP_AUTH_ALGORITHM_OTHER.
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
RVAPI RvStatus RVCALLCONV RvSipAuthorizationHeaderGetStrAuthAlgorithm(
                                           IN  RvSipAuthorizationHeaderHandle  hHeader,
                                           IN  RvChar*                        strBuffer,
                                           IN  RvUint                         bufferLen,
                                           OUT RvUint*                        actualLen);


/***************************************************************************
 * RvSipAuthorizationHeaderSetAuthAlgorithm
 * ------------------------------------------------------------------------
 * General: Sets the authentication algorithm in Authorization header object.
 *          If eAuthAlgorithm is RVSIP_AUTH_SCHEME_OTHER, strAuthAlgorithm is
 *          copied to the header. Otherwise, strAuthAlgorithm is ignored.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader           - Handle to the Authorization header object.
 *  eAuthAlgorithm    - The Authentication algorithm to be set in the object.
 *    strAuthAlgorithm  - Text string giving the Authorization algorithm to be set in the object. You can
 *                      use this parameter if eAuthAlgorithm is set to
 *                      RVSIP_AUTH_ALGORITHM_OTHER. Otherwise, the parameter is set to
 *                      NULL.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthorizationHeaderSetAuthAlgorithm(
                                  IN    RvSipAuthorizationHeaderHandle     hHeader,
                                  IN    RvSipAuthAlgorithm                 eAuthAlgorithm,
                                  IN    RvChar                            *strAuthAlgorithm);



/***************************************************************************
 * RvSipAuthorizationHeaderGetQopOption
 * ------------------------------------------------------------------------
 * General: Gets the Qop option enumeration from the Authorization object.
 * Return Value: The qop type from the object.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader - Returns the Qop option enumeration from the object.
 ***************************************************************************/
RVAPI RvSipAuthQopOption  RVCALLCONV RvSipAuthorizationHeaderGetQopOption(
                                      IN  RvSipAuthorizationHeaderHandle hHeader);


/***************************************************************************
 * RvSipAuthorizationHeaderSetQopOption
 * ------------------------------------------------------------------------
 * General: Sets the Qop option enumeration in the Authorization Header object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hSipAuthHeader - Handle to the Authorization header object.
 *    eQop           - The Qop option to be set in the object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthorizationHeaderSetQopOption(
                                 IN    RvSipAuthorizationHeaderHandle hSipAuthHeader,
                                 IN    RvSipAuthQopOption             eQop);



/***************************************************************************
 * RvSipAuthorizationHeaderGetResponse
 * ------------------------------------------------------------------------
 * General: Copies the Response string from the Authorization header into a given buffer.
 *          If the bufferLen is adequate, the function copies the requested parameter into
 *          strBuffer. Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and actualLen
 *          contains the required buffer length.
 * Return Value: RV_OK or RV_ERROR_INSUFFICIENT_BUFFER.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader    - Handle to the header object.
 *        strBuffer  - Buffer to fill with the requested parameter.
 *        bufferLen  - The length of the buffer.
 * output:actualLen - The length of the requested parameter, + 1 to include a NULL value at the end
 *                     of the parameter.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthorizationHeaderGetResponse(
                                           IN RvSipAuthorizationHeaderHandle  hHeader,
                                           IN RvChar*                        strBuffer,
                                           IN RvUint                         bufferLen,
                                           OUT RvUint*                       actualLen);


/***************************************************************************
 * RvSipAuthorizationHeaderSetResponse
 * ------------------------------------------------------------------------
 * General: Sets the Response string in the Authentication header object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader    - Handle to the Authorization header object.
 *    pResponse  - The Response string to be set in the Authorization header. If a NULL value is
 *               supplied, the existing Response string in the header is removed.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthorizationHeaderSetResponse(
                                     IN    RvSipAuthorizationHeaderHandle  hHeader,
                                     IN    RvChar *                       pResponse);





/***************************************************************************
 * RvSipAuthorizationHeaderGetCNonce
 * ------------------------------------------------------------------------
 * General: Copies the CNonce string from the Authorization header into a given buffer.
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
RVAPI RvStatus RVCALLCONV RvSipAuthorizationHeaderGetCNonce(
                                           IN RvSipAuthorizationHeaderHandle  hHeader,
                                           IN RvChar*                        strBuffer,
                                           IN RvUint                         bufferLen,
                                           OUT RvUint*                       actualLen);



/***************************************************************************
 * RvSipAuthorizationHeaderSetCNonce
 * ------------------------------------------------------------------------
 * General: Sets the CNonce string in the Authorization object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader  - Handle to the Authorization header object.
 *    pCNonce  - The CNonce string to be set in the Authorization header. If a NULL value is
 *             supplied, the existing CNonce string in the header is removed.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthorizationHeaderSetCNonce(
                                     IN    RvSipAuthorizationHeaderHandle hHeader,
                                     IN    RvChar *                      pCNonce);


/***************************************************************************
 * RvSipAuthorizationHeaderGetDigestUri
 * ------------------------------------------------------------------------
 * General: Gets the handle to the address object digest Uri field from the
 *          Authorization header object.
 * Return Value: Returns a handle to the Address object, or NULL if the Address object does not
 *               exist.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader - Handle to the Authorization header object.
 ***************************************************************************/
RVAPI RvSipAddressHandle RVCALLCONV RvSipAuthorizationHeaderGetDigestUri
                                            (IN RvSipAuthorizationHeaderHandle hHeader);


/***************************************************************************
 * RvSipAuthorizationHeaderSetDigestUri
 * ------------------------------------------------------------------------
 * General: Sets the digest uri parameter in the Authorization header object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader    - Handle to the Authorization header object
 *  hDigestUri - Handle to the Address object. If a NULL is supplied, the existing addressSpec in
 *               the Authorization header is removed.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthorizationHeaderSetDigestUri
                                    (IN    RvSipAuthorizationHeaderHandle hHeader,
                                     IN    RvSipAddressHandle             hDigestUri);


/***************************************************************************
 * RvSipAuthorizationHeaderGetHeaderType
 * ------------------------------------------------------------------------
 * General: Gets the header type enumeration from the Authorization Header object.
 * Return Value: Returns the Authorization header type enumeration from the authorization
 *               header object.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hSipAuthHeader - Handle to the Authorization header object.
 ***************************************************************************/
RVAPI RvSipAuthorizationHeaderType  RVCALLCONV RvSipAuthorizationHeaderGetHeaderType(
                                                    IN RvSipAuthorizationHeaderHandle hSipAuthHeader);

/***************************************************************************
 * RvSipAuthorizationHeaderSetHeaderType
 * ------------------------------------------------------------------------
 * General: Sets the header type in the Authorization Header object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hSipAuthHeader    - Handle to the Authorization header object.
 *    eHeaderType       - The header type to be set in the object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthorizationHeaderSetHeaderType(
                                 IN    RvSipAuthorizationHeaderHandle hSipAuthHeader,
                                 IN    RvSipAuthorizationHeaderType   eHeaderType);

/***************************************************************************
 * RvSipAuthorizationHeaderGetStrBadSyntax
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
 *          implementation if the message contains a bad Authorization header,
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
RVAPI RvStatus RVCALLCONV RvSipAuthorizationHeaderGetStrBadSyntax(
                                           IN  RvSipAuthorizationHeaderHandle  hHeader,
                                           IN  RvChar*                        strBuffer,
                                           IN  RvUint                         bufferLen,
                                           OUT RvUint*                        actualLen);

/***************************************************************************
 * RvSipAuthorizationHeaderSetStrBadSyntax
 * ------------------------------------------------------------------------
 * General: Sets a bad-syntax string in the object.
 *          A SIP header has the following grammer:
 *          header-name:header-value. When a header contains a syntax error,
 *          the header-value is kept as a separate "bad-syntax" string.
 *          By using this function you can create a header with "bad-syntax".
 *          Setting a bad syntax string to the header will mark the header as
 *          an invalid syntax header.
 *          You can use his function when you want to send an illegal
 *          Authorization header.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader      - The handle to the header object.
 *  strBadSyntax - The bad-syntax string.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthorizationHeaderSetStrBadSyntax(
                                  IN RvSipAuthorizationHeaderHandle hHeader,
                                  IN RvChar*                     strBadSyntax);


/***************************************************************************
 * RvSipAuthorizationHeaderSetRpoolString
 * ------------------------------------------------------------------------
 * General: Sets a string into a specified parameter in the Authorization header
 *          object. The given string is located on an RPOOL memory and is
 *          not consecutive.
 * Return Value: RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input: hSipAuthHeader - Handle to the Authorization header object.
 *           eStringName   - The string the user wish to set
 *         pRpoolPtr     - pointer to a location inside an rpool where the
 *                         new string is located.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthorizationHeaderSetRpoolString(
                             IN    RvSipAuthorizationHeaderHandle      hSipAuthHeader,
                             IN    RvSipAuthorizationHeaderStringName  eStringName,
                             IN    RPOOL_Ptr                 *pRpoolPtr);

/***************************************************************************
 * RvSipAuthorizationHeaderGetRpoolString
 * ------------------------------------------------------------------------
 * General: Copy a string parameter from the Authorization header into a given page
 *          from a specified pool. The copied string is not consecutive.
 * Return Value: RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input: hSipAuthHeader - Handle to the Authorization header object.
 *           eStringName   - The string the user wish to get
 *  Input/Output:
 *         pRpoolPtr     - pointer to a location inside an rpool. You need to
 *                         supply only the pool and page. The offset where the
 *                         returned string was located will be returned as an
 *                         output patameter.
 *                         If the function set the returned offset to
 *                         UNDEFINED is means that the parameter was not
 *                         set to the Authorization header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthorizationHeaderGetRpoolString(
                             IN    RvSipAuthorizationHeaderHandle      hSipAuthHeader,
                             IN    RvSipAuthorizationHeaderStringName  eStringName,
                             INOUT RPOOL_Ptr                 *pRpoolPtr);



#ifdef __cplusplus
}
#endif

#endif /*RVSIPAUTHENTICATIONHEADER_H*/
