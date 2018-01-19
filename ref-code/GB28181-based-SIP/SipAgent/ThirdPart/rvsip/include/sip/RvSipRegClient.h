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
 *                              <RvSipRegClient.h>
 *
 * This file defines the RegClient API functions.
 * The API contains two major parts:
 * 1. The register-client manager API: The register-client manager is incharged
 *                                     of all the register-clients. It is used
 *                                     to set the event handlers of the
 *                                     register-client module and to create new
 *                                     register-client.
 * 2. The register-client API: Using the register-client API the user can
 *                             request to Register at a chosen registrar. It
 *                             can redirect a register request and authenticate
 *                             a register request when needed.
 *                             A RegClient is a stateful object and has a set
 *                             of states associated with it.
 *
 *    Author                         Date
 *    ------                        ------
 *    Tamar Barzuza                 Jan 2001
 *********************************************************************************/


#ifndef RV_SIP_REG_CLIENT_H
#define RV_SIP_REG_CLIENT_H

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                           */
/*-----------------------------------------------------------------------*/
#include "RV_SIP_DEF.h"
#ifndef RV_SIP_PRIMITIVES
#include "RvSipRegClientTypes.h"
#include "RvSipPartyHeader.h"
#include "RvSipContactHeader.h"
#include "RvSipExpiresHeader.h"
#include "RvSipTransportTypes.h"
#include "RvSipCompartmentTypes.h"
#include "RvSipTransportDNSTypes.h"

/*-----------------------------------------------------------------------*/
/*                REG_CLIENT MANAGER  API                                  */
/*-----------------------------------------------------------------------*/



/***************************************************************************
 * RvSipRegClientMgrSetEvHandlers
 * ------------------------------------------------------------------------
 * General: Sets event handlers for all register-client events.
 * Return Value:RV_ERROR_INVALID_HANDLE - The handle to the manager is invalid.
 *              RV_ERROR_NULLPTR    - Bad pointer to the event handler structure.
 *              RV_OK       - Success.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hMgr - Handle to the register-client manager.
 *            pEvHandlers - Pointer to the application event handler structure
 *            structSize - The size of the event handler structure.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientMgrSetEvHandlers(
                                   IN  RvSipRegClientMgrHandle   hMgr,
                                   IN  RvSipRegClientEvHandlers *pEvHandlers,
                                   IN  RvInt32                  structSize);


/***************************************************************************
 * RvSipRegClientMgrSetCallId
 * ------------------------------------------------------------------------
 * General: Sets the Call-Id to the register-client manager. The string is be
 *          copied. Note: the Call-Id is a null terminated string.
 * Return Value:RV_ERROR_INVALID_HANDLE - The handle to the manager is invalid.
 *              RV_ERROR_NULLPTR    - Bad pointer to the Call-Id string.
 *              RV_ERROR_OUTOFRESOURCES - Not enough resources to copy the Call-Id.
 *              RV_OK       - Success.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hMgr - Handle to the register-client manager.
 *            strCallId - The Call-Id string.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientMgrSetCallId(
                                   IN  RvSipRegClientMgrHandle   hMgr,
                                   IN  RvChar                  *strCallId);


/***************************************************************************
 * RvSipRegClientMgrGetCallId
 * ------------------------------------------------------------------------
 * General: Gets the Call-Id of the register-client manager. The Call-Id
 *          string will be copied to strCallId. If strCallId is not
 *          adequate the function returns RV_InsuffitientBuffer.
 * Return Value:RV_ERROR_INVALID_HANDLE - The handle to the manager is invalid.
 *              RV_ERROR_NULLPTR    - Bad pointer to the Call-Id string.
 *              RV_ERROR_INSUFFICIENT_BUFFER - The given buffer is not large enough.
 *              RV_OK       - Success.
 *              RV_ERROR_UNKNOWN       - There is no Call-Id for this manager.
 *                                 This is an exception.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hMgr - Handle to the register-client manager.
 *            strCallId - The application buffer. The Call-Id string is
 *                      copied to this buffer.
 *            bufferSize - The size of the strCallId buffer.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientMgrGetCallId(
                                   IN  RvSipRegClientMgrHandle   hMgr,
                                   IN  RvChar                  *strCallId,
                                   IN  RvUint32                 bufferSize);


/***************************************************************************
 * RvSipRegClientMgrCreateRegClient
 * ------------------------------------------------------------------------
 * General: Creates a new register-client and replace handles with the
 *          application.  The new register-client assumes the idle state.
 *          In order to register to a registrar you should:
 *          1. Create a new RegClient with this function.
 *          2. Set at least the To and From headers.
 *          3. Call the Register() function.
 *
 * Return Value: RV_ERROR_INVALID_HANDLE -  The handle to the manager is invalid.
 *               RV_ERROR_NULLPTR -     The pointer to the register-client
 *                                   handle is invalid.
 *               RV_ERROR_OUTOFRESOURCES - Not enough resources to create a new
 *                                   RegClient object.
 *               RV_OK -        Success.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClientMgr - Handle to the register-client manager
 *            hAppRegClient - Application handle to the newly created register-
 *                          client.
 * Output:     hRegClient -    sip stack handle to the register-client
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientMgrCreateRegClient(
                                   IN  RvSipRegClientMgrHandle hRegClientMgr,
                                   IN  RvSipAppRegClientHandle hAppRegClient,
                                   OUT RvSipRegClientHandle   *phRegClient);


/***************************************************************************
 * RvSipRegClientMgrGetStackInstance
 * ------------------------------------------------------------------------
 * General: Returns the handle to the stack instance to which this reg-client
 *          manager belongs to.
 *
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClientMgr   - Handle to the register-client manager.
 * Output:     phStackInstance - A valid pointer which will be updated with a
 *                            handle to the stack instance.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientMgrGetStackInstance(
                                   IN   RvSipRegClientMgrHandle   hRegClientMgr,
                                   OUT  void*         *phStackInstance);


/*-----------------------------------------------------------------------*/
/*                 REG_CLIENT API                                          */
/*-----------------------------------------------------------------------*/

/***************************************************************************
 * RvSipRegClientDetachFromMgr
 * ------------------------------------------------------------------------
 * General: Detaches a Register-Client object from the Register-Client
 *          manager object.
 *          By default, all the register clients created in a single stack
 *          instance represent a single User agent and therefore use the same
 *          call-id and an increased CSeq step.
 *          The Call-ID and the CSeq step are managed by the RegClient manager.
 *          When implementing a muilti-lined user agent each register-client
 *          object should have a different Call-Id (representing a different
 *          user) and should manage its owner CSeq step counting.
 *          calling RvSipRegClientDetachFromMgr()
 *          on a register client object will cause the Register-Client to
 *          generate its own call-id and to manage its own CSeq-Step counter.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient - The Sip Stack handle to the Reg-Client
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientDetachFromMgr(
                                      IN  RvSipRegClientHandle   hRegClient);

/***************************************************************************
 * RvSipRegClientRegister
 * ------------------------------------------------------------------------
 * General: Sends a Register request to the registrar. The Request-Url,To,
 *          From , Expires and Contact headers that were set to the register
 *          client are inserted to the outgoing REGISTER request.
 *          The register-client will asume the Registering state and wait for
 *          a response from the server.
 * Return Value: RV_ERROR_INVALID_HANDLE -  The handle to the register-client is
 *                                   invalid.
 *                 RV_ERROR_ILLEGAL_ACTION - Invalid register-client state for this
 *                                  action, or the To and From header have
 *                                  yet been set to the register-client object,
 *                                  or the registrar Request-Url haas not
 *                                  yet been set to the register-client object.
 *               RV_ERROR_OUTOFRESOURCES - register-client failed to create a new
 *                                   transaction, or message object.
 *               RV_ERROR_UNKNOWN - An error occurred while trying to send the
 *                              message (Couldn't send a message to the given
 *                            Request-Uri).
 *               RV_OK - Invite message was sent successfully.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient - The register-client handle.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientRegister (
                                         IN RvSipRegClientHandle hRegClient);


/***************************************************************************
 * RvSipRegClientMake
 * ------------------------------------------------------------------------
 * General: Set the register client from,to,registrar,contact parameters that
 *          are given as strings to the regClient and sends a Register
 *          request to the registrar. If a null value is supplied as one of
 *          the arguments this parameter will not be set.
 *          The register-client will asume the Registering state and wait for
 *          a response from the server.
 * Return Value: RV_ERROR_INVALID_HANDLE -  The handle to the register-client is
 *                                   invalid.
 *                 RV_ERROR_ILLEGAL_ACTION - Invalid register-client state for this
 *                                  action or there is a missing parameter that
 *                                  is needed for the registration process such as
 *                                  the request URI.
 *               RV_ERROR_OUTOFRESOURCES - register-client failed to create a new
 *                                   transaction, or message object.
 *               RV_ERROR_UNKNOWN - An error occurred while trying to send the
 *                              message (Couldn't send a message to the given
 *                            Request-Uri).
 *               RV_OK - Invite message was sent successfully.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient - The register-client handle.
 *          strFrom    - the initiator of the registration request.
 *                       for example: "From: sip:user@home.com"
 *          strTo      - The registaring user.
 *                       "To: sip:bob@proxy.com"
 *          strRegistrar - The request URI of the registration request.This
 *                         is the proxy address.
 *                         for example: "sip:proxy.com"
 *          strContact - The location of the registaring user.
 *                       for example: "Contact: sip:bob@work.com"
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientMake (
                                         IN RvSipRegClientHandle hRegClient,
                                         IN RvChar*             strFrom,
                                         IN RvChar*             strTo,
                                         IN RvChar*             strRegistrar,
                                         IN RvChar*             strContact);


/***************************************************************************
 * RvSipRegClientAuthenticate
 * ------------------------------------------------------------------------
 * General: Re-sends the Register request with authentication information.
 *          This method should be called in the Unauthenticated state
 *          after receiving a 401 or 407 response from the server.
 *          The authorization header will be added to the outgoing request.
 *          The register-client then assumes the Registering state and
 *          waits for a response from the server.
 * Return Value: RV_ERROR_INVALID_HANDLE -  The handle to the register-client or
 *                                   the Request-Uri is invalid.
 *               RV_ERROR_BADPARAM - The Request-Uri must be a SIP-Url and
 *                                     must not contain a User name. In case
 *                                     these rules are violated Invalid-
 *                                     Parameter is returned.
 *                 RV_ERROR_ILLEGAL_ACTION - Invalid register-client state for this
 *                                  action.
 *               RV_ERROR_OUTOFRESOURCES - register-client failed to create a new
 *                                   transaction, or message object.
 *               RV_ERROR_UNKNOWN - An error occurred while trying to send the
 *                              message (Couldn't send a message to the given
 *                            Request-Uri).
 *               RV_OK - Invite message was sent successfully.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient - The register-client handle.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientAuthenticate (
                                         IN RvSipRegClientHandle hRegClient);


/***************************************************************************
 * RvSipRegClientTerminate
 * ------------------------------------------------------------------------
 * General: Terminates a register-client object. This function destructs the
 *          register-client object. You cannot reference the object after
 *          calling this function.
 * Return Value: RV_ERROR_INVALID_HANDLE -  The handle to the register-client is
 *                                   invalid.
 *                 RV_OK - The register-client was successfully terminated
 *                            and distructed.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient - The register-client handle.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientTerminate (
                                         IN RvSipRegClientHandle hRegClient);

/***************************************************************************
 * RvSipRegClientDetachOwner
 * ------------------------------------------------------------------------
 * General: Detach the Register-Client owner. After calling this function the user will
 *          stop receiving events for this Register-Client. This function can be called
 *          only when the object is in terminated state.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient - The register-client handle.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientDetachOwner (
                                         IN RvSipRegClientHandle hRegClient);





/*-----------------------------------------------------------------------
       R E G  - C L I E N T:  D N S   A P I
 ------------------------------------------------------------------------*/
/***************************************************************************
 * RvSipRegClientDNSGiveUp
 * ------------------------------------------------------------------------
 * General: Stops retries to send a Register request after send failure.
 *          When a Register request fails due to timeout, network error or
 *          503 response the Reg-Client Object moves to the MSG_SEND_FAILURE state.
 *          At this state the application can do one of the following:
 *          1. Send the request to the next DNS resolved IP.
 *          2. Give up on this request.
 *          Calling RvSipRegClientDNSGiveUp() indicates that the application
 *          wishes to give up on this request. Retries to send the request
 *          will stop and the Register client will change its state back to
 *          the previous state.
 *          If this is the initial Register request of the Reg-Client, calling
 *          DNSGiveUp() will terminate the Reg-Client object. If this is a
 *          refresh, the Reg-Client will move back to the REGISTERED state.
 * Return Value: RvStatus;
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient - Handle to the Reg-Client that sent the request.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientDNSGiveUp (
                                   IN  RvSipRegClientHandle   hRegClient);
/***************************************************************************
 * RvSipRegClientDNSContinue
 * ------------------------------------------------------------------------
 * General: Prepares the Reg-Client object to a retry to send a request after
 *          the previous attempt failed.
 *          When a Register request fails due to timeout, network error or
 *          503 response the Reg-Client Object moves to the MSG_SEND_FAILURE state.
 *          At this state the application can do one of the following:
 *          1. Send the request to the next DNS resolved IP.
 *          2. Give up on this request.
 *          In order to retry to send the message the application must first
 *          call the RvSipRegClientDNSContinue() function.
 *          Calling this function, clones the failure transaction and
 *          updates the DNS list. (In order to actually re-send the request
 *          to the next IP address use the function RvSipRegClientDNSReSendRequest()).
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient - Handle to the Reg-Client that sent the request.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientDNSContinue (
                                      IN  RvSipRegClientHandle   hRegClient);

/***************************************************************************
 * RvSipRegClientDNSReSendRequest
 * ------------------------------------------------------------------------
 * General: Re-sends a register request after the previous attempt failed.
 *          When a Register request fails due to timeout, network error or
 *          503 response the Reg-Client Object moves to the MSG_SEND_FAILURE state.
 *          At this state the application can do one of the following:
 *          1. Send the request to the next DNS resolved IP.
 *          2. Give up on this request.
 *          In order to re-send the request first call RvSipRegClientDNSContinue().
 *          You should then call RvSipRegClientDNSReSendRequest().
 *          The request will automatically be sent to the next resoulved IP address
 *          in the DNS list.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient - Handle to the reg client that sent the request.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientDNSReSendRequest (
                                            IN  RvSipRegClientHandle   hRegClient);

/***************************************************************************
 * RvSipRegClientDNSGetList
 * ------------------------------------------------------------------------
 * General: Retrieves DNS list object from the Reg-Client current active
 *          transaction.
 *          When a Register request fails due to timeout, network error or
 *          503 response the Reg-Client Object moves to the MSG_SEND_FAILURE state.
 *          At this state you can use RvSipRegClientDNSGetList() to get the
 *          DNS list if you wish to view or change it.
 * Return Value: RV_OK or RV_ERROR_BADPARAM
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient - Handle to the reg client that sent the request.
 * Output   phDnsList - The DNS list handle
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientDNSGetList(
                              IN  RvSipRegClientHandle         hRegClient,
                              OUT RvSipTransportDNSListHandle *phDnsList);

/*-----------------------------------------------------------------------
       R E G - C L I E N T:  G E T   A N D   S E T    A P I
 ------------------------------------------------------------------------*/

/***************************************************************************
 * RvSipRegClientGetNewPartyHeaderHandle
 * ------------------------------------------------------------------------
 * General: Allocates a new Party header and returns its handle.
 *          In order to set the To or From headers of a register client ,
 *          the application should:
 *         1. Get a new party header handle using this function.
 *         2. Fill the party header information and set it back using the
 *            RvSipRegClientSetToHeader or   RvSipRegClientSetFromHeader.
 *
 * Return Value: RV_ERROR_INVALID_HANDLE  - The register-client handle is invalid.
 *               RV_ERROR_NULLPTR     - Bad pointer to party handle was given.
 *               RV_ERROR_OUTOFRESOURCES - Not enough resources to allocate.
 *               RV_OK        - New party header was allocated successfully
 *                                   and its handle was returned.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient - Handle to the register-client object.
 * Output:     phParty - Handle to the newly created party header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientGetNewPartyHeaderHandle (
                                      IN   RvSipRegClientHandle     hRegClient,
                                      OUT  RvSipPartyHeaderHandle  *phParty);


/***************************************************************************
 * RvSipRegClientGetNewContactHeaderHandle
 * ------------------------------------------------------------------------
 * General: Allocates a new Contact header and returns its handle.
 *          The application should use this function to construct new Contact
 *          header when it is necessary to set a new register-client Contact
 *          header.
 *          After setting the relevant information in the header, the header
 *          should be set back in the register-client using the
 *          RvSipRegClientSetContactHeader function.
 * Return Value: RV_ERROR_INVALID_HANDLE  - The register-client handle is invalid.
 *               RV_ERROR_NULLPTR     - Bad pointer to Contact handle was given.
 *               RV_ERROR_OUTOFRESOURCES - Not enough resources to allocate.
 *               RV_OK        - New Contact header was allocated
 *                                   successfully and its handle was returned.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient   - Handle to the register-client.
 * Output:     phContact    - Handle to the newly created Contact header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientGetNewContactHeaderHandle (
                                    IN   RvSipRegClientHandle      hRegClient,
                                    OUT  RvSipContactHeaderHandle *phContact);


/***************************************************************************
 * RvSipRegClientGetNewAddressHandle
 * ------------------------------------------------------------------------
 * General: Allocates a new Address object and returns its handle.
 *          Your application should use this function to construct a new
 *          address object when setting the register-client's registrar field.
 *          After setting the relevant information in the header, it should
 *          be set back in the register-client using
 *          RvSipRegClientSetRegistrar().
 * Return Value: RV_ERROR_INVALID_HANDLE  - The register-client handle is invalid.
 *               RV_ERROR_NULLPTR     - Bad pointer to address handle was given.
 *               RV_ERROR_OUTOFRESOURCES - Not enough resources to allocate.
 *               RV_OK        - New address object was allocated
 *                                   successfully and its handle was returned.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient   - Handle to the register-client.
 *          eAddrType    - The type of address the application wishes to create.
 * Output:     phRequestUri - Handle to the newly created address object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientGetNewAddressHandle (
                                    IN   RvSipRegClientHandle  hRegClient,
                                    IN   RvSipAddressType      eAddrType,
                                    OUT  RvSipAddressHandle    *phRequestUri);


/***************************************************************************
 * RvSipRegClientGetNewExpiresHeaderHandle
 * ------------------------------------------------------------------------
 * General: Allocates a new Expires header and returns its handle.
 *          The application should use this function to construct new Expires
 *          header when it is necessary to set the register-client expires
 *          field.
 *          After setting the relevant information in the header, the header
 *          should be set back in the register-client using the
 *          RvSipRegClientSetExpiresHeader function.
 * Return Value: RV_ERROR_INVALID_HANDLE  - The register-client handle is invalid.
 *               RV_ERROR_NULLPTR     - Bad pointer to Expires handle was given.
 *               RV_ERROR_OUTOFRESOURCES - Not enough resources to allocate.
 *               RV_OK        - New Expires header was allocated
 *                                   successfully and its handle was returned.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient   - Handle to the register-client.
 * Output:     phExpires    - Handle to the newly created Expires header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientGetNewExpiresHeaderHandle (
                                    IN   RvSipRegClientHandle      hRegClient,
                                    OUT  RvSipExpiresHeaderHandle *phExpires);


/***************************************************************************
 * RvSipRegClientGetReceivedMsg
 * ------------------------------------------------------------------------
 * General: Gets the message that was received by the register client. You can
 *          call this function from the RvSipRegClientStateChangedEv call back function
 *          when the new state indicates that a message was received.
 *          If there is no valid received message, NULL will be returned.
 *
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient      - Handle to the register-client.
 * Output:     phMsg           - pointer to the received message.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientGetReceivedMsg(
                                            IN  RvSipRegClientHandle  hRegClient,
                                             OUT RvSipMsgHandle          *phMsg);


/***************************************************************************
 * RvSipRegClientGetOutboundMsg
 * ------------------------------------------------------------------------
 * General: Gets the message that is going to be sent by the register-client.
 *          You can call this function before you call API functions such as
 *          Register(), Make() and Authenticate().
 *          Note: The message you receive from this function is not complete.
 *          In some cases it might even be empty.
 *          You should use this function to add headers to the message before
 *          it is sent. To view the complete message use event message to
 *          send.
 *
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient      - Handle to the register-client.
 * Output:     phMsg           -  pointer to the message.
 ***************************************************************************/
RVAPI  RvStatus RVCALLCONV RvSipRegClientGetOutboundMsg(
                                     IN  RvSipRegClientHandle  hRegClient,
                                     OUT RvSipMsgHandle           *phMsg);


/***************************************************************************
 * RvSipRegClientResetOutboundMsg
 * ------------------------------------------------------------------------
 * General: Sets the outbound message of the register-client to NULL. If the
 *          register-client is about to send a message it will create its own
 *          message to send.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient      - Handle to the register-client.
 ***************************************************************************/
RVAPI  RvStatus RVCALLCONV RvSipRegClientResetOutboundMsg(
                                     IN  RvSipRegClientHandle  hRegClient);

/***************************************************************************
 * RvSipRegClientSetCallId
 * ------------------------------------------------------------------------
 * General: Sets the Reg-Client Call-Id. Calling this function is
 *          optional. If the Call-Id is not set
 *          the Reg-Client will take the Call-Id from the Reg-Client
 *          Manager. Detached Reg-Client will generate it's own Call-Id.
 *
 *          For more information on detached Reg-Clients see
 *          RvSipRegClientDetachFromMgr() function.
 *
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient - The Sip Stack handle to the Reg-Client
 *            strCallId - Null terminating string with the new call Id.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientSetCallId (
                                      IN  RvSipRegClientHandle   hRegClient,
                                      IN  RvChar              *strCallId);

/***************************************************************************
 * RvSipRegClientGetCallId
 * ------------------------------------------------------------------------
 * General:Returns the Call-Id used by the Reg-Client.
 *         If the buffer allocated by the application is insufficient
 *         an RV_ERROR_INSUFFICIENT_BUFFER status is returned and actualSize
 *         contains the size of the Call-ID string in the Reg-Client.
 *
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient   - The Sip Stack handle to the reg-client.
 *          bufSize    - The size of the application buffer for the call-id.
 * Output:     strCallId  - An application allocated buffer.
 *          actualSize - The Call-Id actual size.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientGetCallId (
                            IN  RvSipRegClientHandle   hRegClient,
                            IN  RvInt32             bufSize,
                            OUT RvChar              *pstrCallId,
                            OUT RvInt32             *actualSize);

/***************************************************************************
 * RvSipRegClientSetFromHeader
 * ------------------------------------------------------------------------
 * General: Sets the from header associated with the register-client. If the
 *          From header was constructed by the
 *          RvSipRegClientGetNewPartyHeaderHandle function, the From header
 *          is attached to the register-client object.
 *          Otherwise it will be copied by this function. Note
 *          that attempting to alter the from address after Registeration has
 *          been requested might cause unexpected results.
 * Return Value: RV_ERROR_INVALID_HANDLE  - The register-client handle is invalid
 *                                   or the From header handle is invalid.
 *               RV_ERROR_OUTOFRESOURCES - Not enough memory to allocate.
 *               RV_OK - From header was set successfully.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient - Handle to the register-client.
 *            hFrom      - Handle to an application constructed an initialized
 *                       from header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientSetFromHeader (
                                      IN  RvSipRegClientHandle   hRegClient,
                                      IN  RvSipPartyHeaderHandle hFrom);


/***************************************************************************
 * RvSipRegClientGetFromHeader
 * ------------------------------------------------------------------------
 * General: Returns the from header associated with the register-client.
 *          Attempting to alter the from address after Regitration has
 *          been requested might cause unexpected results.
 * Return Value: RV_ERROR_INVALID_HANDLE  - The register-client handle is invalid.
 *               RV_ERROR_NULLPTR     - Bad pointer was given by the application.
 *               RV_OK        - From header was returned successfully.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient - Handle to the register-client.
 * Output:     phFrom     - Pointer to the register-client From header handle.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientGetFromHeader (
                                      IN  RvSipRegClientHandle    hRegClient,
                                      OUT RvSipPartyHeaderHandle *phFrom);


/***************************************************************************
 * RvSipRegClientSetToHeader
 * ------------------------------------------------------------------------
 * General: Sets the To header associated with the register-client. If the To
 *          header was constructed by the RvSipRegClientGetNewPartyHeaderHandle
 *          function, the To header will be attached to the register-client
 *          object.
 *          Otherwise the To header is copied by this function. Note
 *          that attempting to alter the To header after Registration has
 *          been requested might cause unexpected results.
 * Return Value: RV_ERROR_INVALID_HANDLE  - The register-client handle or the To
 *                                   header handle is invalid.
 *               RV_ERROR_OUTOFRESOURCES - Not enough memory to allocate.
 *               RV_OK        - To header was set successfully.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient - Handle to the register-client.
 *            hTo        - Handle to an application constructed and initialized
 *                       To header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientSetToHeader (
                                      IN  RvSipRegClientHandle   hRegClient,
                                      IN  RvSipPartyHeaderHandle hTo);



/***************************************************************************
 * RvSipRegClientGetToHeader
 * ------------------------------------------------------------------------
 * General: Returns the To header associated with the register-client.
 *          Attempting to alter the To header after Registration has
 *          been requested might cause unexpected results.
 * Return Value: RV_ERROR_INVALID_HANDLE  - The register-client handle is invalid.
 *               RV_ERROR_NULLPTR     - Bad pointer was given by the application.
 *               RV_OK        - To header was returned successfully.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient - Handle to the register-client.
 * Output:     phTo       - Pointer to the register-client To header handle.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientGetToHeader (
                                      IN    RvSipRegClientHandle    hRegClient,
                                      OUT   RvSipPartyHeaderHandle *phTo);


/***************************************************************************
 * RvSipRegClientSetContactHeader
 * ------------------------------------------------------------------------
 * General: Set a contact header to the register-client object. Before calling
 *          Register() the application should use this function to
 *          supply all the Contact headers the application requires in order
 *          to register.
 *          These Contact headers are inserted to the Register request
 *          message before it is sent to the registrar.
 * Return Value: RV_ERROR_INVALID_HANDLE  -   The register-client handle is invalid.
 *                 RV_ERROR_BADPARAM - The supplied Contact header is not
 *                                     supported or illegal.
 *               RV_ERROR_OUTOFRESOURCES - Not enough memory to allocate.
 *               RV_OK        - New contact header was set successfully.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient - Handle to the register-client.
 *            hContactHeader - Handle to a Contact header to be set to the
 *                           register-client.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientSetContactHeader (
                                 IN  RvSipRegClientHandle     hRegClient,
                                 IN  RvSipContactHeaderHandle hContactHeader);


/***************************************************************************
 * RvSipRegClientGetFirstContactHeader
 * ------------------------------------------------------------------------
 * General: Get the first Contact header of the Contact headers list.
 * Return Value: A pointer to the first Contact header of the list. NULL
 *               there are no Contact headers in the list.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient  - Handle to the register-client.
 ***************************************************************************/
RVAPI RvSipContactHeaderHandle *RVCALLCONV RvSipRegClientGetFirstContactHeader(
                          IN  RvSipRegClientHandle                 hRegClient);


/***************************************************************************
 * RvSipRegClientGetNextContactHeader
 * ------------------------------------------------------------------------
 * General: Get a Contact header from the Contact headers list. The returned
 *          Contact header follows the Contact header indicated by
 *          phPrevContact in the list of Contact headers. For this purpose,
 *          the phPrevContact must be valid- a part of the list of Contact
 *          headers.
 * Return Value: A pointer to the requested Contact header. NULL if doesn't
 *               exist.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient  - Handle to the register-client.
 *          phPrevContact   - A handle to the previos Contact header.
 ***************************************************************************/
RVAPI RvSipContactHeaderHandle *RVCALLCONV RvSipRegClientGetNextContactHeader(
                        IN  RvSipRegClientHandle                 hRegClient,
                        IN  RvSipContactHeaderHandle            *phPrevContact);


/***************************************************************************
 * RvSipRegClientRemoveContactHeader
 * ------------------------------------------------------------------------
 * General: Removes a Contact header from the Contact headers list.
 * Return Value: RV_ERROR_INVALID_HANDLE  - The register-client handle is invalid.
 *                 RV_ERROR_NULLPTR     - The supplied Contact header handle is
 *                                   invalid.
 *               RV_OK        - success.
 *               RV_ERROR_NOT_FOUND       - The received Contact header is not in
 *                                   the list.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient  - Handle to the register-client.
 *          hContact   - A handle to the Contact header to be removed.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientRemoveContactHeader (
                        IN  RvSipRegClientHandle                 hRegClient,
                        IN  RvSipContactHeaderHandle             hContact);

/***************************************************************************
 * RvSipRegClientSetRegistrar
 * ------------------------------------------------------------------------
 * General: Set the SIP-Url of the registrar in the register-client object.
 *          Before calling Register(), your application should use
 *          this function to supply the SIP-Url of the registrar.
 *          The register request will be sent to this SIP-Url.
 *          You can change the registrar's SIP-Url each time you call
 *          Register().
 *          This ability can be used for updating the registrar's SIP-Url
 *          in case of redirections and refreshes.
 *          The registrar address must be a SIP-Url with no user name.
 * Return Value: RV_ERROR_INVALID_HANDLE  - The register-client handle is invalid.
 *                 RV_ERROR_BADPARAM - The supplied address handle is not
 *                                     supported or illegal.
 *               RV_ERROR_OUTOFRESOURCES - Not enough memory to allocate.
 *               RV_OK        - New address was set successfully.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient - Handle to the register-client.
 *            hRequestUri - Handle to the registrar SIP-Url to be set to the
 *                        register-client.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientSetRegistrar (
                                 IN  RvSipRegClientHandle  hRegClient,
                                 IN  RvSipAddressHandle    hRequestUri);


/***************************************************************************
 * RvSipRegClientGetRegistrar
 * ------------------------------------------------------------------------
 * General: Gets the SIP-Url of the registrar assosiated with the
 *          register-client.
 * Return Value: RV_ERROR_INVALID_HANDLE  - The register-client handle is invalid.
 *               RV_ERROR_NULLPTR     - Bad pointer was given by the application.
 *               RV_OK        - The address object was successfully
 *                                   returned.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient      - Handle to the register-client.
 * Output:     phRequestUri    - Handle to the registrar SIP-Url.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientGetRegistrar (
                               IN  RvSipRegClientHandle      hRegClient,
                               OUT RvSipAddressHandle       *phRequestUri);


/***************************************************************************
 * RvSipRegClientSetExpiresHeader
 * ------------------------------------------------------------------------
 * General: Set an Expires header in the register-client object. Before
 *          calling Register(), the application can use this function to
 *          supply the required Expires header to use in the Register
 *          request. This Expires header is inserted to the Register
 *          request message before it is sent to the registrar.
 * Return Value: RV_ERROR_INVALID_HANDLE  - The register-client handle is invalid.
 *                 RV_ERROR_BADPARAM - The supplied Expires header is not
 *                                     supported or illegal.
 *               RV_ERROR_OUTOFRESOURCES - Not enough memory to allocate.
 *               RV_OK        - New Expires header was set successfully.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient - Handle to the register-client.
 *            hExpiresHeader - Handle to an Expires header to be set to the
 *                           register-client.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientSetExpiresHeader (
                                 IN  RvSipRegClientHandle     hRegClient,
                                 IN  RvSipExpiresHeaderHandle hExpiresHeader);


/***************************************************************************
 * RvSipRegClientGetExpiresHeader
 * ------------------------------------------------------------------------
 * General: Gets the Expires header assosiated with the register-client.
 * Return Value: RV_ERROR_INVALID_HANDLE  - The register-client handle is invalid.
 *               RV_ERROR_NULLPTR     - Bad pointer was given by the application.
 *               RV_OK        - The Expires header was successfully
 *                                   returned.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient      - Handle to the register-client.
 * Output:     phExpiresHeader - Handle to the register-client's Expires header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientGetExpiresHeader (
                               IN  RvSipRegClientHandle      hRegClient,
                               OUT RvSipExpiresHeaderHandle *phExpiresHeader);


/***************************************************************************
 * RvSipRegClientGetCurrentState
 * ------------------------------------------------------------------------
 * General: Returns the current state of the register-client.
 * Return Value: RV_ERROR_INVALID_HANDLE - The given register-client handle is invalid
 *               RV_ERROR_NULLPTR    - Bad pointer was given by the application.
 *               RV_OK - The state was successfully returned.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient - The register-client handle.
 * Output:     peState -  The register-client's current state.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientGetCurrentState (
                                      IN  RvSipRegClientHandle hRegClient,
                                      OUT RvSipRegClientState *peState);


/***************************************************************************
 * RvSipRegClientSetCSeqStep
 * ------------------------------------------------------------------------
 * General: Sets the CSeq-Step associated with the register-client.
 *          The supplied CSeq must be bigger then zero.
 *          If you don't set the CSeq step the register client will send the
 *          first register request with CSeq=1 and will increase the CSeq for
 *          subsequent requests.
 *          Note1: Most applications do not need to use this function.
 *          The register client manages the CSeq step automatically.
 *          Note2: The CSeq supplied using this function will be used only if
 *          the register client detached from its manager.
 *
 *
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient -  The register-client handle.
 *            cSeqStep   -  The CSeq-Step.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientSetCSeqStep (
                                      IN  RvSipRegClientHandle hRegClient,
                                      IN  RvUint32            cSeqStep);

/***************************************************************************
 * RvSipRegClientGetCSeqStep
 * ------------------------------------------------------------------------
 * General: Returns the CSeq-Step assosiated with the register-client.
 *          Note: The CSeq-Step is valid only after a registeration request
 *                was successfully executed. Otherwise the CSeq-Step is 0.
 * Return Value: RV_ERROR_INVALID_HANDLE - The given register-client handle is invalid
 *               RV_ERROR_NULLPTR    - Bad pointer was given by the application.
 *               RV_OK - The state was successfully returned.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient - The register-client handle.
 * Output:     pCSeqStep -  The register-client's CSeq-Step.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientGetCSeqStep (
                                      IN  RvSipRegClientHandle hRegClient,
                                      OUT RvUint32           *pCSeqStep);


/***************************************************************************
 * RvSipRegClientGetStackInstance
 * ------------------------------------------------------------------------
 * General: Returns the handle to the stack instance to which this reg-client
 *          belongs to.
 *
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient      - Handle to the register-client object.
 * Output:     phStackInstance - A valid pointer which will be updated with a
 *                            handle to the stack instance.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientGetStackInstance(
                                   IN   RvSipRegClientHandle   hRegClient,
                                   OUT  void*       *phStackInstance);

/***************************************************************************
 * RvSipRegClientSetLocalAddress
 * ------------------------------------------------------------------------
 * General: Sets the local address from which the Reg-Client will send outgoing
 *          requests.
 *          The stack can be configured to listen to many local addresses.
 *          Each local address has a transport type (UDP/TCP/TLS) and an address type
 *          (IPv4/IPv6). When the stack sends an outgoing request, the local address
 *          (from where the request is sent) is chosen according to the characteristics
 *          of the remote address. Both the local and remote addresses must have
 *          the same characteristics i.e. the same transport type and address type.
 *          If several configured local addresses
 *          match the remote address characteristics, the first configured address is taken.
 *          You can use RvSipRegClientSetLocalAddress() to force the Reg-Client to choose
 *          a specific local address for a specific transport and address type.
 *          For example, you can force the Reg-Client to use the second configured UDP/IPv4
 *          local address. If the Reg-Client will send a request to an
 *          UDP/IPv4 remote address it will use the local address that you set instead
 *          of the default first local address.
 *
 *          Note: The localAddress string you provide this function must match exactly
 *          to the local address that was inserted in the configuration structure in the
 *          initialization of the sip stack.
 *          If you configured the stack to listen to a 0.0.0.0 local address you must use
 *          the same notation here.
 * Return Value: RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient     - The register-client handle.
 *          eTransportType - The transport type(UDP, TCP, SCTP, TLS).
 *          eAddressType   - The address type(IPv4 or IPv6).
 *            strLocalIPAddress   - A string with the local address to be set to this reg-client.
 *          localPort      - The local port to be set to this reg-client. If you set
 *                           the local port to 0, you will get a default value of 5060.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientSetLocalAddress(
                            IN  RvSipRegClientHandle      hRegClient,
                            IN  RvSipTransport            eTransportType,
                            IN  RvSipTransportAddressType eAddressType,
                            IN  RvChar                   *strLocalIPAddress,
                            IN  RvUint16                 localPort);

/***************************************************************************
 * RvSipRegClientGetLocalAddress
 * ------------------------------------------------------------------------
 * General: Gets the local address the Reg-Client will use to send outgoing
 *          requests to a destination with the supplied
 *          transport type and address type.
 *          This is the address the user set using the
 *          RvSipRegClientSetLocalAddress() function. If no address was set the
 *          function will return the default first configured local address
 *          of the requested transport and address type.
 * Return Value: RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient      - The register-client handle
 *          eTransportType  - The transport type (UDP, TCP, SCTP, TLS).
 *          eAddressType    - The address type (ip4 or ip6).
 * Output:    strLocalIPAddress    - The local address the Reg-Client will use
 *                            for the supplied transport and address types.
 *                            (The buffer must be longer than 48 bytes).
 *          pLocalPort       - The local port the Reg-Client will use.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientGetLocalAddress(
                            IN  RvSipRegClientHandle      hRegClient,
                            IN  RvSipTransport            eTransportType,
                            IN  RvSipTransportAddressType eAddressType,
                            OUT  RvChar                  *strLocalIPAddress,
                            OUT  RvUint16                *pLocalPort);

/***************************************************************************
 * RvSipRegClientSetOutboundDetails
 * ------------------------------------------------------------------------
 * General: Sets all outbound proxy details to the register-client object.
 *          All details are supplied in the RvSipTransportOutboundProxyCfg 
 *          structure that includes parameters such as the IP address or host name, 
 *          transport, port and compression type. 
 *          Requests sent by this object will use the outbound details
 *          specifications as a remote address. 
 *          Note: If you specify both the IP address and a host name in the 
 *          configuration structure, either of them will be set but the IP 
 *          address will be used. If you do not specify port or transport, 
 *          both will be determined according to the DNS
 *          procedures specified in RFC 3263.
 * Return Value: RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient     - Handle to the register-client.
 *            pOutboundCfg   - A pointer to the outbound proxy configuration 
 *                             structure with all relevant details.
 *            sizeOfCfg      - The size of the outbound proxy configuration structure.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientSetOutboundDetails(
                            IN  RvSipRegClientHandle            hRegClient,
                            IN  RvSipTransportOutboundProxyCfg *pOutboundCfg,
                            IN  RvInt32                         sizeOfCfg);

/***************************************************************************
 * RvSipRegClientGetOutboundDetails
 * ------------------------------------------------------------------------
 * General: Gets all the outbound proxy details that the register-client object uses.
 *          The details are placed in the RvSipTransportOutboundProxyCfg structure that
 *          includes parameters such as the IP address or host name, transport, port and
 *          compression type. If the outbound details were not set to the specific 
 *          register-client object, but the outbound proxy was defined to the SIP 
 *          Stack on initialization, the SIP Stack parameters will be returned. 
 *          If the register-client is not using an outbound address, NULL/UNDEFINED 
 *          values are returned.
 *          Note: You must supply a valid consecutive buffer in the
 *                RvSipTransportOutboundProxyCfg structure to get the outbound strings 
 *               (host name and IP address).
 * Return Value: RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient     - Handle to the register-client.
 *            sizeOfCfg      - The size of the configuration structure.
 * Output:  pOutboundCfg   - A pointer to outbound proxy configuration structure.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientGetOutboundDetails(
                            IN  RvSipRegClientHandle            hRegClient,
                            IN  RvInt32                         sizeOfCfg,
                            OUT RvSipTransportOutboundProxyCfg *pOutboundCfg);

/***************************************************************************
 * RvSipRegClientSetOutboundAddress
 * ------------------------------------------------------------------------
 * General: Sets the outbound proxy IP address of the Reg-Client object. All Regsiter
 *          requests sent by this Reg-Client will be sent directly to the Reg-Client
 *          outbound IP address.
 * Return Value: RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient        - The register-client handle
 *            strOutboundAddrIp   - The outbound IP to be set to this
 *                              reg-client.
 *          outboundProxyPort - The outbound port to be set to this
 *                              Reg-client.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientSetOutboundAddress(
                            IN  RvSipRegClientHandle   hRegClient,
                            IN  RvChar               *strOutboundAddrIp,
                            IN  RvUint16              outboundProxyPort);


/***************************************************************************
 * RvSipRegClientGetOutboundAddress
 * ------------------------------------------------------------------------
 * General: Gets the address of outbound proxy the Reg-Client is using. If an
 *          outbound address was set to the Reg-Client this address will be
 *          returned. If no outbound address was set to the reg-client
 *          but an outbound proxy was configured for the stack, the configured
 *          address is returned. '\0' is returned if the reg-client is not using
 *          an outbound proxy.
 *          NOTE: you must supply a valid consecutive buffer of size 48 to
 *          get the outboundProxyIp.
 * Return Value: RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient        - The register-client handle
 * Output:  outboundProxyIp   - A buffer with the outbound proxy IP the reg-client.
 *                              is using(must be longer than 48).
 *          pOutboundProxyPort - The outbound proxy port the reg-client is using.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientGetOutboundAddress(
                            IN   RvSipRegClientHandle  hRegClient,
                            OUT  RvChar              *outboundProxyIp,
                            OUT  RvUint16            *pOutboundProxyPort);

/***************************************************************************
 * RvSipRegClientSetOutboundHostName
 * ------------------------------------------------------------------------
 * General:  Sets the outbound proxy host name of the Reg-Client object.
 *           The outbound host name will be resolved each time a Register
 *           request is sent and the Register requests will be sent to the
 *           resolved IP address.
 *           Note: To set a specific IP address use RvSipRegClientSetOutboundAddress().
 *           If you configure a Reg-Client with both an outbound IP address and an
 *           outbound host name, the Reg-Client will ignore the outbound host name
 *           and will use the outbound IP address.
 *
 * Return Value: RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient           - Handle to the RegClient
 *            strOutboundHost    - The outbound proxy host to be set to this
 *                               RegClient.
 *          outboundPort  - The outbound proxy port to be set to this
 *                               RegClient. If you set the port to zero it
 *                               will be determined using the DNS procedures.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientSetOutboundHostName(
                            IN  RvSipRegClientHandle     hRegClient,
                            IN  RvChar                *strOutboundHost,
                            IN  RvUint16              outboundPort);


/***************************************************************************
 * RvSipRegClientGetOutboundHostName
 * ------------------------------------------------------------------------
 * General: Gets the host name of the outbound proxy the RegClient is using. If an
 *          outbound host was set to the RegClient this host will be
 *          returned. If no outbound host was set to the RegClient
 *          but an outbound host was configured for the stack, the configured
 *          address is returned. '\0' is returned if the RegClient is not using
 *          an outbound host.
 *          NOTE: you must supply a valid consecutive buffer to
 *          get the outboundProxy host name
 * Return Value: RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:
 *          hRegClient      - Handle to the RegClient
 * Output:
 *            srtOutboundHostName   -  A buffer with the outbound proxy host name
 *          pOutboundPort - The outbound proxy port.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientGetOutboundHostName(
                            IN   RvSipRegClientHandle    hRegClient,
                            OUT  RvChar              *strOutboundHostName,
                            OUT  RvUint16            *pOutboundPort);


/***************************************************************************
 * RvSipRegClientSetOutboundTransport
 * ------------------------------------------------------------------------
 * General: Sets the outbound transport of the Reg-Client outbound proxy.
 *          This transport will be used for the outbound proxy that you set
 *          using the RvSipRegClientSetOutboundAddress() function or the
 *          RvSipRegClientSetOutboundHostName() function.
 *          If you do not set an outbound transport, the transport will be
 *          determined using the DNS procedures.
 * Return Value: RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient        - The Reg-Client handle
 *            eTransportType    - The outbound proxy transport to be set to this
 *                              Reg-Client
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientSetOutboundTransport(
                            IN  RvSipRegClientHandle   hRegClient,
                            IN  RvSipTransport         eTransportType);


/***************************************************************************
 * RvSipRegClientGetOutboundTransport
 * ------------------------------------------------------------------------
 * General: Gets the transport of outbound proxy the Reg-Client is using. If an
 *          outbound transport was set to the reg-client this transport will be
 *          returned. If no outbound transport was set to the reg-client
 *          but an outbound proxy was configured for the stack, the configured
 *          transport is returned. RVSIP_TRANSPORT_UNDEFINED is returned if the
 *          reg-client is not using an outbound proxy.
 * Return Value: RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient        - The register-client handle
 * Output:  eOutboundProxyTransport    - The outbound proxy transport type
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientGetOutboundTransport(
                            IN   RvSipRegClientHandle  hRegClient,
                            OUT  RvSipTransport       *eOutboundProxyTransport);



/***************************************************************************
 * RvSipRegClientSetPersistency
 * ------------------------------------------------------------------------
 * General: Changes the Reg-Client persistency definition on run time.
 *          The function receives a boolean value that indicates whether the
 *          application wishes this Reg-Client to be persistent or not.
 *          A persistent Reg-Client object will apply its persistency to the
 *          transactions it creates. A persistent transaction will try
 *          to locate a suitable connection in the connection hash before opening
 *          a new connection.A persistent Reg-Client will also try to use the same connection
 *          for all outgoing requests by appling the last used connection object
 *          to the next created transaction.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:    hRegClient - The Reg-Client handle
 *          bIsPersistent - Determines the Reg-Client persistency definition.
 *                          RV_TRUE = persistent, RV_FALSE otherwise.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientSetPersistency(
                           IN RvSipRegClientHandle       hRegClient,
                           IN RvBool                  bIsPersistent);

/***************************************************************************
 * RvSipRegClientGetPersistency
 * ------------------------------------------------------------------------
 * General: Returns the Reg-Client persistency definition.
 *          RV_TRUE indicates that the Reg-Client is persistent, RV_FALSE
 *          otherwise.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:    hRegClient - The Reg-Client handle
 * Output:  pbIsPersistent - The Reg-Client persistency definition.
 *                           RV_TRUE indicates that the Reg-Client is persistent,
 *                           RV_FALSE otherwise.
 ***************************************************************************/
RVAPI  RvStatus RVCALLCONV RvSipRegClientGetPersistency(
        IN  RvSipRegClientHandle                   hRegClient,
        OUT RvBool                                *pbIsPersistent);

/***************************************************************************
 * RvSipRegClientSetConnection
 * ------------------------------------------------------------------------
 * General: Sets a connection object to be used by the Reg-Client transactions.
 *          The Reg-Client object holds this connection in its internal database.
 *          Whenever the Reg-Client creates a new transaction it supplies
 *          the transaction with given connection.
 *          The transaction will use the connection only if it fits the transaction's
 *          local and remote addresses.
 *          Otherwise the transaction will either locate a suitable connection in the hash
 *          or create a new connection. The Reg-Client object will be informed that
 *          the supplied connection did not fit and that a different connection was used and
 *          will update its database.
 *          Note: You can set a connection only to a persistent Reg-Client.
 * Return Value: RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient - Handle to the reg-client
 *          hConn - Handle to the connection.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientSetConnection(
                   IN  RvSipRegClientHandle                hRegClient,
                   IN  RvSipTransportConnectionHandle   hConn);

/***************************************************************************
 * RvSipRegClientGetConnection
 * ------------------------------------------------------------------------
 * General: Returns the connection that is currently beeing used by the
 *          Reg-Client.
 *          Note: only persistent Reg-Clients keep the currently used connection.
 *                NULL will be returned if the Reg-Client is not persistent.
 * Return Value: RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient - Handle to the Reg-Client.
 * Output:    phConn - Handle to the currently used connection
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientGetConnection(
                            IN  RvSipRegClientHandle             hRegClient,
                           OUT  RvSipTransportConnectionHandle  *phConn);



/***************************************************************************
 * RvSipRegClientSetAppHandle
 * ------------------------------------------------------------------------
 * General: Sets the Reg-Client application handle. Usually the application
 *          replaces handles with the stack in the
 *          RvSipRegClientMgrCreateRegClient() API function.
 *          This function is used if the application wishes to set a new
 *          application handle to the Reg-Client object
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient    - Handle to the Reg-Client.
 *            hAppRegClient - A new application handle to set in the Reg-Client.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientSetAppHandle (
                                      IN  RvSipRegClientHandle     hRegClient,
                                      IN  RvSipAppRegClientHandle  hAppRegClient);

/***************************************************************************
 * RvSipRegClientGetAppHandle
 * ------------------------------------------------------------------------
 * General: Gets the Reg-Client application handle.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient    - Handle to the Reg-Client.
 *            hAppRegClient - The Reg-Client application handle
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientGetAppHandle (
                                      IN  RvSipRegClientHandle     hRegClient,
                                      IN  RvSipAppRegClientHandle *phAppRegClient);

/***************************************************************************
 * RvSipRegClientSetCompartment
 * ------------------------------------------------------------------------
 * General: Associates the register-client to a SigComp compartment.
 *          The register-client will use this compartment in the message 
 *          compression process.
 *          Note The message will be compressed only if the remote URI includes the
 *          comp=sigcomp parameter.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient   - The handle to the register client.
 *            hCompartment - Handle to the SigComp Compartment.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientSetCompartment(
                            IN RvSipRegClientHandle   hRegClient,
                            IN RvSipCompartmentHandle hCompartment);

/***************************************************************************
 * RvSipRegClientGetCompartment
 * ------------------------------------------------------------------------
 * General: Retrieves the SigComp compartment associated with the register-client.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:  hRegClient    - The handle to the register client.
 * Output: phCompartment - The handle to the SigComp compartment.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientGetCompartment(
                            IN  RvSipRegClientHandle    hRegClient,
                            OUT RvSipCompartmentHandle *phCompartment);

/***************************************************************************
 * RvSipRegClientDisableCompression
 * ------------------------------------------------------------------------
 * General:Disables the compression mechanism in a register-client. 
 *         This means that even if the message indicates compression, 
 *         it will not be compressed.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:  hRegClient    - The handle to the register client.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRegClientDisableCompression(
                                      IN  RvSipRegClientHandle hRegClient);

#ifdef __cplusplus
}
#endif

#endif /*RV_SIP_PRIMITIVES*/
#endif /* END OF: #ifndef RV_SIP_REG_CLIENT_H */
