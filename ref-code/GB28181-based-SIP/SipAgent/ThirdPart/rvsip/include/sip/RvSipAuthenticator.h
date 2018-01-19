/*
*********************************************************************************
*                                                                               *
* NOTICE:                                                                       *
* This document contains information that is confidential and proprietary to    *
* RADVision LTD.. No part of this publication may be reproduced in any form     *
* whatsoever without written prior approval by RADVision LTD..                  *
*                                                                               *
* RADVision LTD. reserves the right to revise this publication and make changes *
* without obligation to notify any person of such revisions or changes.         *
*********************************************************************************
*/


/*********************************************************************************
 *                              RvSipAuthenticator.h
 *
 *  This file provides headers for the functions that handle the digest response creating,
 *  the authorization header building.
 *
 *
 *    Author                         Date
 *    ------                        ------
 *  Oren Libis                      Jan. 2001
 *********************************************************************************/

#ifndef _RV_SIP_AUTHENTICATOR_H
#define _RV_SIP_AUTHENTICATOR_H


#ifdef __cplusplus
extern "C" {
#endif



/*-----------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                           */
/*-----------------------------------------------------------------------*/

#include "RV_SIP_DEF.h"
#include "RvSipCommonTypes.h"
#include "RvSipMsgTypes.h"
#include "rpool_API.h"


/*-----------------------------------------------------------------------*/
/*                          TYPE DEFINITIONS                             */
/*-----------------------------------------------------------------------*/

/* declaring the handle to the Authenticator object */
RV_DECLARE_HANDLE(RvSipAuthenticatorHandle);

/* declaring the application handle to the Authenticator object */
RV_DECLARE_HANDLE(RvSipAppAuthenticatorHandle);


/***************************************************************************
 * RvSipAuthenticatorMD5Ev (DEPRECATED - use RvSipAuthenticatorMD5ExEv)
 * ------------------------------------------------------------------------
 * General:  Notifies that there is a need to use the MD5 algorithm.
 * Return Value: (-)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     pRpoolMD5Input - Rpool pointer to the MD5 input
 *          length         - length of the string inside the page
 * Output:     strMd5Output   - The output of the hash algorithm
 ***************************************************************************/
typedef void
        (RVCALLCONV * RvSipAuthenticatorMD5Ev)(
                                   IN  RPOOL_Ptr                     *pRpoolMD5Input,
                                   IN  RvUint32                     length,
                                   OUT RPOOL_Ptr                     *pRpoolMD5Output);

/***************************************************************************
 * RvSipAuthenticatorMD5ExEv
 * ------------------------------------------------------------------------
 * General:  Notifies that there is a need to use the MD5 algorithm.
 * Return Value: (-)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hAuthenticator    - Handle to the authenticator object.
 *          hAppAuthenticator - Handle to the application authenticator handle.
 *          pRpoolMD5Input - Rpool pointer to the MD5 input
 *          length         - length of the string inside the page
 * Output:     strMd5Output   - The output of the hash algorithm
 ***************************************************************************/
typedef void
        (RVCALLCONV * RvSipAuthenticatorMD5ExEv)(
                                   IN  RvSipAuthenticatorHandle       hAuthenticator,
                                   IN  RvSipAppAuthenticatorHandle    hAppAuthenticator,
                                   IN  RPOOL_Ptr                     *pRpoolMD5Input,
                                   IN  RvUint32                     length,
                                   OUT RPOOL_Ptr                     *pRpoolMD5Output);


/***************************************************************************
 * RvSipAuthenticatorSharedSecretEv
 * ------------------------------------------------------------------------
 * General:  Notifies that there is a need for the username and password.
 *           This callback function is for client side authentication.
 *           Note: This function is obsolete and was deprecated in
 *           RvSipAuthenticatorGetSharedSecretEv().
 * Return Value: (-)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRequestUri      - handle to the request uri
 *          pRpoolRealm      - the realm string in RPool_ptr format
 * Output:     pRpoolUserName   - the username string in RPool_ptr format
 *          pRpoolPassword   - the password string in RPool_ptr format
 ***************************************************************************/
typedef void
        (RVCALLCONV * RvSipAuthenticatorSharedSecretEv)(
                                   IN  RvSipAddressHandle            hRequestUri,
                                   IN  RPOOL_Ptr                     *pRpoolRealm,
                                   OUT RPOOL_Ptr                     *pRpoolUserName,
                                   OUT RPOOL_Ptr                     *pRpoolPassword);


/***************************************************************************
 * RvSipAuthenticatorGetSharedSecretEv
 * ------------------------------------------------------------------------
 * General:  Notifies that there is a need for the username and password.
 *           This callback function is for client side authentication.
 * Return Value: (-)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hAuthenticator    - Handle to the authenticator object.
 *          hAppAuthenticator - Handle to the application authenticator.
 *          hObject           - Handle to the Object, that is served
 *                              by the Authenticator (e.g. CallLeg, RegClient)
 *          peObjectType      - pointer to the variable, that stores the
 *                              type of the hObject. 
 *                              Use following code to get the type:
 *                              RvSipCommonStackObjectType eObjType = *peObjectType;
 *          pRpoolRealm       - the realm string in RPool_ptr format
 * Output:  pRpoolUserName    - the username string in RPool_ptr format
 *          pRpoolPassword    - the password string in RPool_ptr format
 ***************************************************************************/
typedef void
        (RVCALLCONV * RvSipAuthenticatorGetSharedSecretEv)(
                                   IN  RvSipAuthenticatorHandle       hAuthenticator,
                                   IN  RvSipAppAuthenticatorHandle    hAppAuthenticator,
                                   IN  void*                          hObject,
                                   IN  void*                          peObjectType,
                                   IN  RPOOL_Ptr                     *pRpoolRealm,
                                   OUT RPOOL_Ptr                     *pRpoolUserName,
                                   OUT RPOOL_Ptr                     *pRpoolPassword);

/***************************************************************************
 * RvSipAuthenticatorMD5EntityBodyEv
 * ------------------------------------------------------------------------
 * General:  This callback function notifies the application that 
 *           it should supply the hash result made on the message body
 *           MD5(entity-body). Message body hash value is needed when
 *           the required quality of protection (qop) is 'auth-int'.
 *           Note: This callback supplies the message object as a parameter.
 *           However, it is called before the msgToSend callback
 *           of stack objects. If your code adds the message body 
 *           in the msgToSend callback, The body will not be available when
 *           this callback is called. If you wish the message object to 
 *           include the body at this stage you must use the
 *           outbound message mechanism to add the body.
 * Return Value: (-)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hAuthenticator    - handle to the Authenticator object
 *          hAppAuthenticator - Handle to the application authenticator.
 *          hObject           - Handle to the Object, that is served
 *                              by the Authenticator (e.g. CallLeg, RegClient)
 *          peObjectType      - Pointer to the variable, that stores the
 *                              type of the hObject. 
 *                              Use following code to get the type:
 *                              RvSipCommonStackObjectType eObjType = *peObjectType;
 *          hMsg              - Handle to the message that it is now beeing sent
 *                              and that will include the user credentials.
 * Output:  pRpoolMD5Output   - The MD5 of the message body in RPOOL_Ptr format.
 *          pLength           - length of the string after MD5 result 
 *                              concatenation.
 ***************************************************************************/
typedef void
        (RVCALLCONV * RvSipAuthenticatorMD5EntityBodyEv)(
                       IN     RvSipAuthenticatorHandle      hAuthenticator,
                       IN     RvSipAppAuthenticatorHandle   hAppAuthenticator,
                       IN     void*                         hObject,
                       IN     void*                         peObjectType,
                       IN     RvSipMsgHandle                hMsg,
                       OUT    RPOOL_Ptr                     *pRpoolMD5Output,
                       OUT    RvUint32                      *pLength);

/* RvSipAuthenticatorEvHandlers
 * ------------------------------------------------------------------------
 * Structure with function pointers to the hash algorithm call-backs.
 * This structure is used to set the application call-backs in the function
 * RvSipAuthenticationSetEventHandlers();
 * pfnMD5AuthenticationHandler          - Deprecated
 * pfnSharedSecretAuthenticationHandler - Deprecated
 * pfnGetSharedSecretAuthenticationHandler - notify the application that there is a need for
 *                      the username and password
 * pfnMD5AuthenticationExHandler        - notify that MD5 algorithm should be used.
 * pfnMD5EntityBodyAuthenticationHandler - asks an application for H(entity-body)
 *                      string, necessary for A2 token calculation in case
 *                      "auth-int" Quality-of-Protection authentication.
 */
typedef struct
{
    RvSipAuthenticatorMD5Ev             pfnMD5AuthenticationHandler;
    RvSipAuthenticatorSharedSecretEv    pfnSharedSecretAuthenticationHandler;
    RvSipAuthenticatorGetSharedSecretEv pfnGetSharedSecretAuthenticationHandler;
    RvSipAuthenticatorMD5ExEv           pfnMD5AuthenticationExHandler;
    RvSipAuthenticatorMD5EntityBodyEv   pfnMD5EntityBodyAuthenticationHandler;
} RvSipAuthenticatorEvHandlers;


/*-----------------------------------------------------------------------*/
/*                          FUNCTIONS HEADERS                            */
/*-----------------------------------------------------------------------*/





/***************************************************************************************
 *
 * General functions
 *
 ***************************************************************************************/



/************************************************************************************
 * RvSipAuthenticatorSetEvHandlers
 * ----------------------------------------------------------------------------------
 * General: Sets event handlers for the authenticator events.
 * Return Value: RvStatus - RV_OK       - the event handlers were set successfully
 *                           RV_ERROR_INVALID_HANDLE - the authentication handle was invalid
 * ----------------------------------------------------------------------------------
 * Arguments:
 * Input:   hAuth             - handle to the authenticator module.
 *          evHandlers        - pointer to event handlers structure.
 *          evHandlersSize    - the size of the event handlers structure.
 * Output:  none
 ***********************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthenticatorSetEvHandlers(
                                   IN RvSipAuthenticatorHandle      hAuth,
                                   IN RvSipAuthenticatorEvHandlers  *evHandlers,
                                   IN RvUint32                      evHandlersSize);


/******************************************************************************
 * RvSipAuthenticatorSetProxyAuthInfo
 * ----------------------------------------------------------------------------
 * General: Sets a Proxy-Authenticate header to the authenticator object.
 *          This header will be used to authenticate requests in advance.
 *          The authenticator object will use this header to build a 
 *          Proxy-Authorization header that will be placed automatically
 *          in all requests sent by Call-Legs, Register-Clients and Subscriptions.
 *          An application should use this function if it knows the challenge
 *          requested by its proxy. By setting the Proxy-Authorization header
 *          in initial requests the application might avoid the first message exchange
 *          of a request and its 407 response.
 *          Note1: If a stack object received 407 response despite of the
 *          existence of the Proxy-Authorization header in the request,
 *          the object will use the new received challenge to create correct
 *          credentials.
 *          Note2: This function can be used only for setting Proxy-Authenticate
 *          header. You cannot set a WWW-Authenticate header here.
 *
 *          
 * Return Value: RvStatus
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hAuth             - handle to the authenticator object.
 *          hAuthHeader       - handle to the authentication header.
 *          strUserName       - the user name string.
 *          strPassword       - the password string.
 * Output:  none
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthenticatorSetProxyAuthInfo(
                              IN RvSipAuthenticatorHandle        hAuth,
                              IN RvSipAuthenticationHeaderHandle hAuthHeader,
                              IN RvChar                          *strUserName,
                              IN RvChar                          *strPassword);

/************************************************************************************
 * RvSipAuthenticatorSetAppHandle
 * ----------------------------------------------------------------------------------
 * General: Set the application authenticator handle to the SIP stack authenticator
 *          object. This handle is returned in some of the authenticator callback
 *          functions.
 * Return Value: RvStatus.
 * ----------------------------------------------------------------------------------
 * Arguments:
 * Input:   hAuth             - Handle to the authenticator object.
 *          hAppAuth          - Handle to the application authenticator object.
 * Output:  none
 ***********************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthenticatorSetAppHandle(
                                   IN RvSipAuthenticatorHandle    hAuth,
                                   IN RvSipAppAuthenticatorHandle hAppAuth);

/***************************************************************************
 * RvSipAuthenticatorCredentialsSupported
 * ------------------------------------------------------------------------
 * General: The function checks parameters in the authorization header like
 *          qop, algorithm and scheme and determins if the header can be
 *          authenticated by SIP Stack or not.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input: hAuth - handle to the authenticator manager.
 *        hAuthorization    - handle to the authorization header.
 * Output:  bIsSupported - RV_TRUE if supported.
 ***************************************************************************/
RVAPI RvStatus RvSipAuthenticatorCredentialsSupported(
                                        IN  RvSipAuthenticatorHandle         hAuth,
                                        IN  RvSipAuthorizationHeaderHandle   hAuthorization,
                                        OUT RvBool*                         bIsSupported);

/************************************************************************************
 * RvSipAuthenticatorVerifyCredentials
 * ----------------------------------------------------------------------------------
 * General: This function is for a server side authentication.
 *          Using this function the application can verify the credentials received
 *          in an incoming request message. The application
 *          supplies the password that belong to the user name and realm found
 *          in the authorization header, and wishes to know if the authorization
 *          header is correct for this username.          
 *          This function creates the digest string as specified in RFC 2617, and compare
 *          it to the digest string inside the given authorization header.
 *          If it is equal, the header is correct.
 * Return Value: RvStatus.
 * ----------------------------------------------------------------------------------
 * Arguments:
 * Input:   hAuth           - handle to the authentication module.
 *          hAuthorization  - handle to the authorization header.
 *          password        - password of the user indicated in the Authorization header.
 *          strMethod       - the method type of the request.
 * Output:  isCorrect       - boolean, TRUE if correct, False if not.
 ***********************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthenticatorVerifyCredentials(
                                   IN RvSipAuthenticatorHandle         hAuth,
                                   IN RvSipAuthorizationHeaderHandle   hAuthorization,
                                   IN RvChar                          *password,
                                   IN RvChar                          *strMethod,
                                   OUT RvBool                         *isCorrect);

/***************************************************************************
 * RvSipAuthenticatorGetStackInstance
 * ------------------------------------------------------------------------
 * General: Returns the handle to the Stack instance to which this 
 *          authenticator belongs.
 *
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hAuth     - Handle to the Authenticator.
 * Output:     phStackInstance - A valid pointer which will be updated with a
 *                            handle to the stack instance.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthenticatorGetStackInstance(
                                   IN   RvSipAuthenticatorHandle  hAuth,
                                   OUT  void*       *phStackInstance);

/******************************************************************************
 * RvSipAuthenticatorSetNonceCount
 * ----------------------------------------------------------------------------
 * General: Sets the initial value of the nonce-count parameter, that will be used
 *          when creating the Proxy-Authorization header placed in outgoing
 *          requests.
 *          This nonce count is used with the challenge supplied by calling
 *          the RvSipAuthenticatorSetProxyAuthInfo() for authenticating
 *          messages in advance.
 *          The nonce-count value is incremented by the authenticator after each
 *          header calculation according to RFC 2617.
 *          Note1: Range of legal values for the nonce-count is [0,MAX_INT32].
 *          Note2: The value of the nonce count is reset each time the application
 *          calls the RvSipAuthenticatorSetProxyAuthInfo() with a new nonce field.
 *
 * Return Value: RvStatus.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hAuth      - Handle to the authenticator object.
 *          nonceCount - The nonce count value to use.
 * Output: none.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthenticatorSetNonceCount(
                                   IN RvSipAuthenticatorHandle  hAuth,
                                   IN RvInt32                   nonceCount);

/******************************************************************************
 * RvSipAuthenticatorAddProxyAuthorizationToMsg
 * ----------------------------------------------------------------------------
 * General: Adds a Proxy-Authorization header to the supplied message object.
 *          You can use this function only if you set a Proxy-Authenticate
 *          header to the authenticator using the RvSipAuthenticatorSetProxyAuthInfo()
 *          API function. The authenticator uses the challenge found in the
 *          Proxy-Authenticate header to build the correct Proxy-Authorization()
 *          header.
 *          You should use this function if you want to add credentials to
 *          outgoing requests sent by stand alone transactions. The function
 *          should be called from the message to send callback of the transaction.
 *          For other stack objects, the process of adding the authorization
 *          header is automatic.
 *
 * Return Value: RvStatus.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hAuth      - Handle to the Authenticator object.
 *          hMsg       - Handle to the message, to which the Proxy-Authorization
 *                       header should be added.
 *          nonceCount - 'nonce-count' value, that should be used for the MD5 signature
 *                       generation. If set to UNDEFINED, internal nonce-count,
 *                       managed by the Authenticator, will be used. If no 
 *                       internal 'nonce-value' was set (with the  
 *                       RvSipAuthenticatorSetNonceCount() function), '1' will be used.
 *          hObject    - Handle to the object this message belongs to.
 *                       The handle will be supplied back to the application in
 *                       some of the authenticator callback functions.
 *                       You can supply NULL value.
 *          eObjectType- The type of the object this message belongs to.
 *                       The type will be supplied back to the application in
 *                       some of the authenticator callback functions.
 *                       You can set this value to RVSIP_COMMON_STACK_OBJECT_TYPE_UNDEFINED.
 * Output: none.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipAuthenticatorAddProxyAuthorizationToMsg(
                            IN RvSipAuthenticatorHandle        hAuth,
                            IN RvSipMsgHandle                  hMsg,
                            IN RvInt32                         nonceCount, 
                            IN void*                           hObject,
                            IN RvSipCommonStackObjectType      eObjectType);


#ifdef __cplusplus
}
#endif

#endif  /*END OF: define _RV_SIP_AUTHENTICATOR_H*/

