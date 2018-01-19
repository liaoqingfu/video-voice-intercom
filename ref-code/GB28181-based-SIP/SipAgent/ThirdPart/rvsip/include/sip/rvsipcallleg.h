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
*                              <RvSipCallLeg.h>
*
* The Call-Leg functions of the RADVISION SIP stack enable you to create and
* manage call-leg objects, connect and disconnect calls and control call-leg
* parameters.
* Call-Leg API functions are grouped as follows:
* The Call-Leg Manager API
* ------------------------
* The call-leg manager is in charge of all the call-legs. It is used
* to set the event handlers of the call-leg module and to create
* new call-legs.
*
* The Call-Leg API
* -----------------
* A call-leg represents a SIP call leg as defined in RFC 2543. This
* means that a call-leg is defined using the Call-ID, From and To
* headers. Using the call-leg API, the user can initiate calls, react
* to incoming calls and disconnect calls. Functions to set and
* access the call-leg fields are also available in the API. A call-leg
* is a stateful object and has a set of states associated with it.
*    Author                         Date
*    ------                        ------
*    Sarit Mekler                  Nov 2000
*********************************************************************************/


#ifndef RV_SIP_CALL_LEG_H
#define RV_SIP_CALL_LEG_H

#ifdef __cplusplus
extern "C" {
#endif

	/*-----------------------------------------------------------------------*/
	/*                        INCLUDE HEADER FILES                           */
	/*-----------------------------------------------------------------------*/
#include "RV_SIP_DEF.h"
#ifndef RV_SIP_PRIMITIVES
#include "RvSipCallLegTypes.h"
#include "RvSipMsg.h"
#include "RvSipPartyHeader.h"
#include "RvSipAddress.h"
#include "RvSipTransaction.h"
#include "RvSipSubscriptionTypes.h"
#include "RvSipSessionExpiresHeader.h"
#ifdef RV_SIGCOMP_ON
#include "RvSipCompartmentTypes.h"
#endif

	/*-----------------------------------------------------------------------*/
	/*                CALL_LEG MANAGER  API                                  */
	/*-----------------------------------------------------------------------*/



	/***************************************************************************
	* RvSipCallLegMgrSetEvHandlers
	* ------------------------------------------------------------------------
	* General: Set event handlers for all call-leg events.
	* Return Value:RV_ERROR_INVALID_HANDLE - The handle to the manager is invalid.
	*              RV_ERROR_NULLPTR    - Bad pointer to the event handler structure.
	*              RV_OK       - Success.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hMgr - Handle to the call-leg manager.
	*            pEvHandlers - Pointer to structure containing application event
	*                        handler pointers.
	*            structSize - The size of the event handler structure.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegMgrSetEvHandlers(
		IN  RvSipCallLegMgrHandle  hMgr,
		IN  RvSipCallLegEvHandlers *pEvHandlers,
		IN  RvInt32               structSize);



	/***************************************************************************
	* RvSipCallLegMgrCreateCallLeg
	* ------------------------------------------------------------------------
	* General: Creates a new Outgoing call-leg and exchange handles with the
	*          application.  The new call-leg assumes the Idle state.
	*          To establish a new session
	*          1. Create a new call-leg with this function.
	*          2. Set, at least, the To and From header.
	*          3. Call the Connect() function.
	*
	* Return Value: RV_ERROR_INVALID_HANDLE -  The handle to the manager is invalid.
	*               RV_ERROR_NULLPTR -     The pointer to the call-leg handle is
	*                                   invalid.
	*               RV_ERROR_OUTOFRESOURCES - Call list is full,call-leg was not
	*                                   created.
	*               RV_OK -        Success.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLegMgr - Handle to the call-leg manager
	*            hAppCallLeg - Application handle to the newly created call-leg.
	* Output:     RvSipCallLegHandle -   RADVISION SIP stack handle to the call-leg
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegMgrCreateCallLeg(
		IN  RvSipCallLegMgrHandle hCallLegMgr,
		IN  RvSipAppCallLegHandle hAppCallLeg,
		OUT RvSipCallLegHandle    *hCallLeg);


	/***************************************************************************
	* RvSipCallLegMgrSetAppMgrHandle
	* ------------------------------------------------------------------------
	* General: The application can have its own call-leg manager handle.
	*          You can use the RvSipCallLegMgrSetAppMgrHandle function to
	*          save this handle in the stack call-leg manager object.
	*
	* Return Value: RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLegMgr - Handle to the stack call-leg manager.
	*           pAppCallLegMgr - The application call-leg manager handle.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegMgrSetAppMgrHandle(
		IN RvSipCallLegMgrHandle hCallLegMgr,
		IN void*               pAppCallLegMgr);


	/***************************************************************************
	* RvSipCallLegMgrGetAppMgrHandle
	* ------------------------------------------------------------------------
	* General: Returns the handle to the application call-leg manger object.
	*          You set this handle in the stack using the
	*          RvSipCallLegMgrSetAppMgrHandle() function.
	*
	* Return Value: RvStatus
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLegMgr - Handle to the stack call-leg manager.
	* Output:     pAppCallLegMgr - The application call-leg manager handle.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegMgrGetAppMgrHandle(
		IN RvSipCallLegMgrHandle hCallLegMgr,
		OUT void**               pAppCallLegMgr);

	/***************************************************************************
	* RvSipCallLegMgrGetStackInstance
	* ------------------------------------------------------------------------
	* General: Returns the handle to the stack instance to which this call-leg
	*          manager belongs to.
	*
	* Return Value: RvStatus
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLegMgr     - Handle to the stack call-leg manager.
	* Output:     phStackInstance - A valid pointer which will be updated with a
	*                            handle to the stack instance.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegMgrGetStackInstance(
		IN   RvSipCallLegMgrHandle   hCallLegMgr,
		OUT  void*       *phStackInstance);

	/*-----------------------------------------------------------------------*/
	/*                 CALL_LEG API                                          */
	/*-----------------------------------------------------------------------*/


	/*-----------------------------------------------------------------------
	C A L L  - L E G:  S E S S I O N   A P I
	------------------------------------------------------------------------*/
	/***************************************************************************
	* RvSipCallLegMake
	* ------------------------------------------------------------------------
	* General: Set the To and From header in the call-leg and
	*          initiate an outgoing call. This function will cause
	*          an INVITE to be sent out and the call-leg state machine
	*          will progress to the Inviting state.
	* Return Value: RV_ERROR_INVALID_HANDLE -  The handle to the call-leg is invalid.
	*
	*                 RV_ERROR_ILLEGAL_ACTION - Invalid call-leg state for this action.
	*               RV_ERROR_OUTOFRESOURCES - Call-leg failed to create a new
	*                                   transaction.
	*               RV_ERROR_BADPARAM - Bad parameter was given by the application.
	*               RV_ERROR_NULLPTR - Bad pointer was given by the application.
	*               RV_ERROR_UNKNOWN - An error occurred while trying to send the
	*                              message (Couldn't send a message to the given
	*                            Request-Uri).
	*               RV_OK - Invite message was sent successfully.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call leg the user wishes to connect
	*          strFrom  - A string with the from party header for example:
	*                     "From:sip:172.20.1.1:5060"
	*          strTo -   A string with the to party header for example:
	*                     "To:sip:172.20.5.5:5060"
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegMake (
		IN  RvSipCallLegHandle   hCallLeg,
		IN  RvChar*             strFrom,
		IN  RvChar*             strTo);

	/***************************************************************************
	* RvSipCallLegConnect
	* ------------------------------------------------------------------------
	* General: Initiate an outgoing call. This method may be called
	*          only after the To, From fields have been set. Calling
	*          Connect causes an INVITE to be sent out and the
	*          call-leg state machine to progress to the Inviting state.
	* Return Value: RV_ERROR_INVALID_HANDLE -  The handle to the call-leg is invalid.
	*                 RV_ERROR_ILLEGAL_ACTION - Invalid call-leg state for this action.
	*               RV_ERROR_OUTOFRESOURCES - Call-leg failed to create a new
	*                                   transaction.
	*               RV_ERROR_UNKNOWN - An error occurred while trying to send the
	*                              message (Couldn't send a message to the given
	*                            Request-Uri).
	*               RV_OK - Invite message was sent successfully.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call leg the user wishes to connect
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegConnect (
		IN  RvSipCallLegHandle   hCallLeg);

	/***************************************************************************
	* RvSipCallLegAccept
	* ------------------------------------------------------------------------
	* General: Called by the application to indicate that it is willing to accept
	*          an incoming call or an incoming re-Invite.
	* Return Value: RV_ERROR_INVALID_HANDLE -  The handle to the call-leg is invalid.
	*                 RV_ERROR_ILLEGAL_ACTION -  Invalid call-leg state for this action.
	*               RV_ERROR_UNKNOWN       -  Failed to accept the call. (failed
	*                                   while trying to send the 200 response).
	*               RV_OK       -  Accept final response was sent successfully.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call leg the user wishes to accept
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegAccept (
		IN  RvSipCallLegHandle   hCallLeg);


	/***************************************************************************
	* RvSipCallLegByeAccept
	* ------------------------------------------------------------------------
	* General: Called by the application to indicate that it is willing to accept
	*          an incoming BYE.
	* Return Value: RV_ERROR_INVALID_HANDLE -  The handle to the call-leg is invalid.
	*                 RV_ERROR_ILLEGAL_ACTION -  Invalid call-leg state for this action.
	*               RV_ERROR_UNKNOWN       -  Failed to accept the call. (failed
	*                                   while trying to send the 200 response).
	*               RV_OK       -  Accept final response was sent successfully.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call leg the user wishes to accept its BYE.
	*          hTransc  - handle to the BYE transaction
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegByeAccept (IN  RvSipCallLegHandle   hCallLeg,
		IN  RvSipTranscHandle    hTransc);


	/***************************************************************************
	* RvSipCallLegReject
	* ------------------------------------------------------------------------
	* General: Can be used in the Offering state to reject an incoming call.
	*          This function can also be used to reject a modify (re-Invite)
	*          request received by a connected call-leg.
	* Return Value: RV_ERROR_INVALID_HANDLE    -  The handle to the call-leg is invalid.
	*               RV_ERROR_BADPARAM - The status code is invalid.
	*                 RV_ERROR_ILLEGAL_ACTION    - Invalid call-leg state for this action.
	*               RV_ERROR_UNKNOWN          - Failed to reject the call. (failed
	*                                     while trying to send the reject response).
	*               RV_OK -          Reject final response was sent successfully.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call leg the user wishes to reject
	*            status   - The rejection response code.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegReject (
		IN  RvSipCallLegHandle   hCallLeg,
		IN  RvUint16 status);

	/***************************************************************************
	* RvSipCallLegByeReject
	* ------------------------------------------------------------------------
	* General: Can be used in the Offering state to reject an incoming call.
	*          This function can also be used to reject a modify (re-Invite)
	*          request received by a connected call-leg.
	* Return Value: RV_ERROR_INVALID_HANDLE    -  The handle to the call-leg is invalid.
	*               RV_ERROR_BADPARAM - The status code is invalid.
	*                 RV_ERROR_ILLEGAL_ACTION    - Invalid call-leg state for this action.
	*               RV_ERROR_UNKNOWN          - Failed to reject the call. (failed
	*                                     while trying to send the reject response).
	*               RV_OK -          Reject final response was sent successfully.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call leg the user wishes to reject
	*          hTransc  - Handle to the BYE transaction
	*            status   - The rejection response code.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegByeReject (
		IN  RvSipCallLegHandle   hCallLeg,
		IN  RvSipTranscHandle    hTransc,
		IN  RvUint16            status);


	/***************************************************************************
	* RvSipCallLegProvisionalResponse
	* ------------------------------------------------------------------------
	* General: Sends a provisional response (1xx class) to the remote party.
	*          This function can be called when ever a request is received for
	*          example in the offering state.
	* Return Value: RV_ERROR_UNKNOWN - Failed to send provisional response.
	*               RV_OK - Provisional response was sent successfully.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call leg.
	*            status -   The provisional response status code.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegProvisionalResponse (
		IN  RvSipCallLegHandle   hCallLeg,
		IN  RvUint16 status);

	/***************************************************************************
	* RvSipCallLegAck
	* ------------------------------------------------------------------------
	* General: Sends an ACK request from the call-leg to the remote party.
	*          When the stack is configured to work in a manual ACK mode the
	*          call-leg will not send the ACK message after receive a 2xx
	*          response by itself. The application should use the RvSipCallLegAck()
	*          function to trigger the call-leg to send the ACK.
	*          This function can be called only in the Remote-Accepted state
	*          or in the Modify Re-Invite Remote Accepted state.
	* Return Value: RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call leg.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegAck (
		IN  RvSipCallLegHandle   hCallLeg);

	/***************************************************************************
	* RvSipCallLegProvisionalResponseReliable
	* ------------------------------------------------------------------------
	* General: Sends a reliable provisional response (1xx class other then 100)
	*          to the remote party.
	*          This function can be called when an Invite request is received for
	*          example in the Offering state.
	* Return Value: RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call leg.
	*            status -   The provisional response status code.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegProvisionalResponseReliable (
		IN  RvSipCallLegHandle   hCallLeg,
		IN  RvUint16            status);

	/***************************************************************************
	* RvSipCallLegSendPrack
	* ------------------------------------------------------------------------
	* General: Sends a manual PRACK message to a reliable provisional response. 
	*          This function can be called if the configuration flag 'manualPrack' 
	*          is set to RV_TRUE and the call-leg PRACK state is
	*          RVSIP_CALL_LEG_PRACK_STATE_REL_PROV_RESPONSE_RCVD.
	* Return Value: RvStatus
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg  - The transaction handle.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegSendPrack(
		IN RvSipCallLegHandle            hCallLeg);

	/***************************************************************************
	* RvSipCallLegSendPrackResponse
	* ------------------------------------------------------------------------
	* General: Sends a manual response to a PRACK message. 
	*          This function can be called if the configuration flag 'manualPrack' 
	*          is set to RV_TRUE and the call-leg PRACK state is
	*          RVSIP_CALL_LEG_PRACK_STATE_PRACK_RCVD.
	* Return Value: RvStatus
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg     - The transaction handle.
	*            responseCode - The response code to send.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegSendPrackResponse(
		IN RvSipCallLegHandle            hCallLeg,
		IN RvUint16                     responseCode);


	/***************************************************************************
	* RvSipCallLegDisconnect
	* ------------------------------------------------------------------------
	* General: Causes the call to disconnect.
	*          Disconnect() may be called in any state. The
	*          behavior of the function depends on the following call-leg states:
	*
	*          Connected, Accepted, Inviting
	*          -----------------------------
	*          Bye is sent and the call moves to the Disconnecting state.
	*
	*          Offering
	*          --------
	*          The incoming Invite is rejected with status code 603.
	*
	*          Idle, Disconnecting, Disconnected , Redirected ,Unauthenticated
	*          ---------------------------------------------------------------
	*          The call is terminated.
	*
	*          If the functions fail to send the BYE request, the call-leg will
	*          be terminated.
	*
	* Return Value: RV_ERROR_INVALID_HANDLE  -  The handle to the call-leg is invalid.
	*               RV_ERROR_UNKNOWN        - Failed to send message (BYE or final
	*                                   rejection response).
	*               RV_ERROR_OUTOFRESOURCES - Request failed due to resource problem.
	*               RV_OK        - BYE message was sent successfully.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call leg the user wishes to disconnect.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegDisconnect (
		IN  RvSipCallLegHandle   hCallLeg);

	/***************************************************************************
	* RvSipCallLegTerminate
	* ------------------------------------------------------------------------
	* General: Terminates a call-leg without sending any messages (CANCEL or
	*          BYE). The call-leg will assume the Terminated state.
	*          Calling this function will cause an abnormal
	*          termination. All transactions related to the call-leg will be
	*          terminated as well.
	* Return Value:RvStatus
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call leg the user wishes to terminate.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegTerminate (
		IN  RvSipCallLegHandle   hCallLeg);

	/***************************************************************************
	* RvSipCallLegDetachOwner
	* ------------------------------------------------------------------------
	* General: Detach the Call-Leg owner. After calling this function the user
	*          will stop receiving events for this call-leg.
	*          This function can be called only when the object is in terminated
	*          state.
	* Return Value:RvStatus
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call leg the user wishes to detach its owner.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegDetachOwner(IN RvSipCallLegHandle  hCallLeg);

	/***************************************************************************
	* RvSipCallLegCancel
	* ------------------------------------------------------------------------
	* General: Cancels an Invite request (or re-Invite request).
	*          You can call this function only at the Inviting state and at the
	*          Modify Re-Invite Sent state.
	*
	* Return Value: RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call leg the user wishes to cancel.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegCancel (
		IN  RvSipCallLegHandle   hCallLeg);

	/***************************************************************************
	* RvSipCallLegModify
	* ------------------------------------------------------------------------
	* General: Causes a re-INVITE to be sent. Can be called only in the connected
	*          state when there is no other pending re-Invite transaction.
	*          The remote-party's response to the re-INVITE will be given
	*          in the EvModifyResultRecvd callback.
	* Return Value: RV_ERROR_INVALID_HANDLE -  The handle to the call-leg is invalid.
	*                 RV_ERROR_ILLEGAL_ACTION - Invalid call-leg state for this action.
	*               RV_ERROR_OUTOFRESOURCES - Request failed due to resource problem.
	*               RV_ERROR_UNKNOWN - Failed to send re-Invite.
	*               RV_OK - Invite message was sent successfully.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call leg the user wishes to modify.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegModify (
		IN  RvSipCallLegHandle   hCallLeg);



	/***************************************************************************
	* RvSipCallLegTranscCreate
	* ------------------------------------------------------------------------
	* General:Creates a new general transaction that is related to the supplied
	*         call-leg.
	*         The transaction will have the call-leg characteristics such as:
	*         To Header, From header, Call-ID and local and outbound addresses.
	*         The application can define an application handle to the transaction
	*         and supply it to the stack when calling this function.
	*         The application handle will be supplied back to the application
	*         when the  RvSipCallLegTranscStateChangedEv callback will be called.
	* Return Value: RvStatus
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg   - Handle to the call leg.
	*          hAppTransc - Application handle to the new transaction
	* Output:  hTransc    - The handle to the newly created transaction
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegTranscCreate(
		IN  RvSipCallLegHandle   hCallLeg,
		IN  RvSipAppTranscHandle hAppTransc,
		OUT RvSipTranscHandle    *hTransc);


	/***************************************************************************
	* RvSipCallLegTranscRequest
	* ------------------------------------------------------------------------
	* General: This function gets a Transaction related to the call-leg and
	*          sends a Request message with a given method. It can be used at
	*          any call-leg state. You can use this function for sending requests,
	*          such as INFO. The request will have the To, From and Call-ID of
	*          the call-leg and will be sent with a correct CSeq step. The request
	*          will be recordrouted if needed.
	*          Note:
	*          1. If you supply the function a NULL transaction, the stack
	*             will create a new call-leg transaction for you but you will not be
	*             able to replace handles with this transaction.
	*          2. A transaction that was supplied by the application will
	*             not be terminated on failure. It is the application
	*             responsibility to terminate the transaction using the
	*             RvSipCallLegTranscTerminated() function.
	* Return Value: RvStatus
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call leg that will send the new Request.
	*          strMethod - A String with the request method.
	* Input Output:  hTransc - The handle to the newly created transaction
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegTranscRequest(
		IN  RvSipCallLegHandle   hCallLeg,
		IN  RvChar*             strMethod,
		INOUT RvSipTranscHandle    *hTransc);


	/***************************************************************************
	* RvSipCallLegTranscResponse
	* ------------------------------------------------------------------------
	* General: This function sends a response to a call-leg related transaction.
	*          When a call-leg receives a general request such as INFO
	*          (and other then BYE or PRACK) the call-leg first notifies the
	*          application that a new call-leg transaction was created using
	*          the RvSipCallLegTranscCreatedEv() callback. At this stage the
	*          application can specify whether or not it wishes to handle the
	*          transaction and can also replace handles with the stack.
	*          The call-leg will then notify the application about the new
	*          transaction state: "General Request Rcvd" using the callback
	*          RvSipCallLegTranscStateChangedEv().
	*          At this state the application should use the
	*          RvSipCallLegTranscResponse() function to send a response to the
	*          request.
	* Return Value: RvStatus
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call leg that will send the new Request.
	*          hTransc - Handle to the transaction the request belongs to.
	*          status - The response code to the request.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegTranscResponse(
		IN  RvSipCallLegHandle   hCallLeg,
		IN  RvSipTranscHandle    hTransc,
		IN  RvUint16            status);

	/***************************************************************************
	* RvSipCallLegTranscTerminate
	* ------------------------------------------------------------------------
	* General: 1. Terminate a General transaction inside a call-leg.
	*          2. Terminate a BYE transaction. Used by applications that work with
	*             the BYE stateChangedEv.
	* Return Value: RvStatus
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call leg that the transaction terminated relates to.
	*          hTransc  - Handle to the transaction that is terminated.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegTranscTerminate(
		IN  RvSipCallLegHandle   hCallLeg,
		IN  RvSipTranscHandle    hTransc);

	/***************************************************************************
	* RvSipCallLegNoActiveTransc
	* ------------------------------------------------------------------------
	* General: The function is for B2B usage.
	*          The function verify that there is no transaction in active state
	*          in the call-leg.
	*          For every transaction in the call-leg, that is not in active state,
	*          the function sets the AppTranscHandle to be NULL.
	*
	* Return Value: RV_OK - If there is no active transaction.
	*               RV_ERROR_UNKNOWN - If there is an active transaction.
	*               RV_ERROR_INVALID_HANDLE
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call leg.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegNoActiveTransc(
		IN  RvSipCallLegHandle           hCallLeg);
	/***************************************************************************
	* RvSipCallLegAuthenticate - client authentication.
	* ------------------------------------------------------------------------
	* General: Call this function to send a request with authentication information.
	*          If a call-leg receives a 401 or 407 response indicating that a
	*          request was not authenticated by the server or proxy, the
	*          call-leg assumes the Unauthenticated state.
	*          You may use RvSipCallLegAuthenticate() in the Unauthenticated
	*          state to re-send the request with authentication information.
	*          You can use this function to authenticate both the INVITE
	*          and BYE requests.
	* Return Value: RV_ERROR_INVALID_HANDLE -  The handle to the call-leg is invalid.
	*                 RV_ERROR_ILLEGAL_ACTION - Invalid call-leg state for this action.
	*               RV_ERROR_OUTOFRESOURCES - Cannot send request due to a resource problem.
	*               RV_ERROR_UNKNOWN - An error occurred. request was not sent.
	*               RV_OK - request was sent successfully.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call leg the user wishes to authenticate.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegAuthenticate(
		IN  RvSipCallLegHandle   hCallLeg);

	/***************************************************************************
	* RvSipCallLegAuthBegin - Server authentication
	* ------------------------------------------------------------------------
	* General: Begin the server authentication process. challenge an incoming
	*          request.
	*          If the request is an active transaction (Invite, Bye),
	*          hCallLeg handle should be given, and hTransaction should be NULL.
	*          For general request, hTransaction should be given, and
	*          hCallLeg should be NULL.
	* Return Value: RvStatus
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call leg the user wishes to challenge
	*          hTransaction - Handle to the transaction user wishes to challenge
	*                         (in case of general request).
	***************************************************************************/
	RVAPI  RvStatus RVCALLCONV RvSipCallLegAuthBegin(
		IN  RvSipCallLegHandle hCallLeg,
		IN  RvSipTranscHandle  hTransaction);

	/***************************************************************************
	* RvSipCallLegAuthProceed - Server authentication
	* ------------------------------------------------------------------------
	* General: The function order the stack to proceed in authentication procedure.
	*          actions options are:
	*          RVSIP_TRANSC_AUTH_ACTION_USING_PASSWORD
	*          - Check the given authorization header, with the given password.
	*
	*          RVSIP_TRANSC_AUTH_ACTION_SUCCESS
	*          - user had checked the authorization header by himself, and it is
	*            correct. (will cause AuthCompletedEv to be called, with status success)..
	*
	*          RVSIP_TRANSC_AUTH_ACTION_FAILURE
	*          - user wants to stop the loop that searchs for authorization headers.
	*            (will cause AuthCompletedEv to be called, with status failure).
	*
	*          RVSIP_TRANSC_AUTH_ACTION_SKIP
	*          - order to skip the given header, and continue the authentication
	*            procedure with next header (if exists).
	*            (will cause AuthCredentialsFoundEv to be called, or
	*            AuthCompletedEv(failure) if there are no more authorization headers.
	*
	* Return Value: RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg -       The callLeg handle.
	*          hTransaction -   The transaction handle.
	*          action -         With which action to proceed. (see above)
	*          hAuthorization - Handle of the authorization header that the function
	*                           will check authentication for. (needed if action is
	*                           RVSIP_TRANSC_AUTH_ACTION_USING_PASSWORD, else NULL.)
	*          password -       The password for the realm+userName in the header.
	*                           (needed if action is
	*                           RVSIP_TRANSC_AUTH_ACTION_USING_PASSWORD, else NULL.)
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegAuthProceed(
		IN  RvSipCallLegHandle             hCallLeg,
		IN  RvSipTranscHandle              hTransaction,
		IN  RvSipTransactionAuthAction     action,
		IN  RvSipAuthorizationHeaderHandle hAuthorization,
		IN  RvChar                        *password);

	/***************************************************************************
	* RvSipCallLegRespondUnauthenticated - Server authentication
	* ------------------------------------------------------------------------
	* General: Sends 401/407 response.
	*          Add a copy of the given header to the response message.
	* Return Value: RvStatus
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg -       The callLeg handle.
	*          hTransaction -   The transaction handle.
	*          responseCode -   401 or 407.
	*          strReasonPhrase - May be NULL, for default reason phrase.
	*          headerType -     The type of the given header
	*          hHeader -        Pointer to the header to be set in the msg.
	***************************************************************************/
	RVAPI  RvStatus RVCALLCONV RvSipCallLegRespondUnauthenticated(
		IN  RvSipCallLegHandle   hCallLeg,
		IN  RvSipTranscHandle    hTransaction,
		IN  RvUint16            responseCode,
		IN  RvChar*             strReasonPhrase,
		IN  RvSipHeaderType      headerType,
		IN  void*                hHeader);

	/***************************************************************************
	* RvSipCallLegRespondUnauthenticatedDigest - Server authentication
	* ------------------------------------------------------------------------
	* General: Sends 401/407 response.
	*          Build an authentication header containing all given parameters,
	*          and add it to the response message.
	* Return Value: RvStatus
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg -       The callLeg handle.
	*          hTransaction -   The transaction handle.
	*          responseCode -   401 or 407
	*          strReasonPhrase - The reason phrase for this response code.
	*          strRealm -       mandatory.
	*          strDomain -      Optional string. may be NULL.
	*          strNonce -       Optional string. may be NULL.
	*          strOpaque -      Optional string. may be NULL.
	*          bStale -         TRUE or FALSE
	*          eAlgorithm -     Enumeration of algorithm. if RVSIP_AUTH_ALGORITHM_OTHER
	*                           the algorithm value is taken from the the next argument.
	*          strAlgorithm -   String of algorithm. this parameters will be set only if
	*                           eAlgorithm parameter is set to be RVSIP_AUTH_ALGORITHM_OTHER.
	*          eQop -           Enumeration of qop. if RVSIP_AUTH_QOP_OTHER, the qop value
	*                           will be taken from the next argument.
	*          strQop -         String of qop. this parameter will be set only if eQop
	*                           argument is set to be RVSIP_AUTH_QOP_OTHER.
	***************************************************************************/
	RVAPI  RvStatus RVCALLCONV RvSipCallLegRespondUnauthenticatedDigest(
		IN  RvSipCallLegHandle hCallLeg,
		IN  RvSipTranscHandle  hTransaction,
		IN  RvUint16          responseCode,
		IN  RvChar           *strReasonPhrase,
		IN  RvChar           *strRealm,
		IN  RvChar           *strDomain,
		IN  RvChar           *strNonce,
		IN  RvChar           *strOpaque,
		IN  RvBool            bStale,
		IN  RvSipAuthAlgorithm eAlgorithm,
		IN  RvChar            *strAlgorithm,
		IN  RvSipAuthQopOption eQop,
		IN  RvChar            *strQop);


	/*-----------------------------------------------------------------------
	C A L L  - L E G   R E F E R   F U N C T I O N S
	------------------------------------------------------------------------*/

	/***************************************************************************
	* RvSipCallLegRefer
	* ------------------------------------------------------------------------
	* General: This function is DEPRECATED!!! you should use the subscription refer API.
	*          In order to use it for code that written for earlier stack version,
	*          you must set the configuration parameter 'disableRefer3515Behavior' to true.
	*          Sends a REFER associated with the call-leg. This function may be
	*          called only after the To and From header fields were set.
	*          Calling Refer causes a REFER request to be sent out and the
	*          call-leg refer state machine to progress to the Refer Sent
	*          state.
	*          This function is also used to send an authenticated refer
	*          request in the RVSIP_CALL_LEG_REFER_STATE_REFER_UNAUTHENTICATED.
	* Return Value: RV_ERROR_INVALID_HANDLE -  The handle to the call-leg is invalid.
	*                 RV_ERROR_ILLEGAL_ACTION - Invalid call-leg state for this action.
	*               RV_ERROR_OUTOFRESOURCES - Call-leg failed to create a new
	*                                   transaction.
	*               RV_ERROR_UNKNOWN - An error occurred while trying to send the
	*                              message (Couldn't send a message to the given
	*                            Request-Uri).
	*               RV_OK - REFER message was sent successfully.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:   hCallLeg     - Handle to the call leg the user wishes to send REFER.
	*          hReferTo     - The Refer-To header to be sent in the REFER request.
	*                         The Refer-To header will be kept in the call-leg object, and can
	*                         contain Replaces header.
	*                         When using this function for authenticating or
	*                           redirecting a previously sent refer request you can
	*                           set this parameter to NULL. The Refer-To header will
	*                            be taken from the call-leg object.
	*          hReferredBy  - The Referred-By header to be sent in the REFER request.
	*                         The Referred-By header will be kept in the call-leg object.
	*                         This parameter is optional. If not specified the call-leg
	*                         will use a default Referred-By header.
	*                         When using this function for authenticating or
	*                           redirecting a previously sent refer request you can
	*                           set this parameter to NULL. The Referred-By header will
	*                            be taken from the call-leg object.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegRefer (
		IN  RvSipCallLegHandle          hCallLeg,
		IN  RvSipReferToHeaderHandle    hReferTo,
		IN  RvSipReferredByHeaderHandle hReferredBy);

	/***************************************************************************
	* RvSipCallLegReferAccept
	* ------------------------------------------------------------------------
	* General: This function is DEPRECATED!!! you should use the subscription refer API.
	*          In order to use it for code that written for earlier stack version,
	*          you must set the configuration parameter 'disableRefer3515Behavior' to true.
	*          Call this function in the "Refer Received" state to accept the
	*          REFER request.
	*          This function will do the following:
	*          1. send a  202-Accepted response to the REFER request.
	*          2. create a new call-leg object.
	*          3. Set the following parameter to the new call-leg:
	*              * Call-Id: the Call-Id of the REFER request.
	*              * To header: The Refer-To header of the REFER request.
	*              * From header: The local contact
	*              * Referred-By: The Referred-By header of the RFEER request.
	*          After calling this function you should connect the new call-leg to
	*          the referenced user agent by calling RvSipCallLegConnect().
	* Return Value: RV_ERROR_INVALID_HANDLE -  The handle to the call-leg is invalid.
	*               RV_ERROR_NULLPTR    - The pointer to the new call-leg handle is
	*                                  invalid.
	*                 RV_ERROR_ILLEGAL_ACTION -  Invalid call-leg state for this action.
	*               RV_ERROR_UNKNOWN       -  Failed to accept the call. (failed
	*                                   while trying to send the 202 response, or
	*                                   to create and initialize the new call-leg).
	*               RV_OK       -  Accepted final response was sent successfully,
	*                                   and a new call-leg was created and initialized
	*                                   successfully.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call leg the user wishes to accept its refer.
	*          hAppCallLeg - Application handle to the newly created call-leg.
	* Output:  phNewCallLeg - The new call-leg that is created and initialized by
	*                        this function.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegReferAccept (
		IN  RvSipCallLegHandle    hCallLeg,
		IN  RvSipAppCallLegHandle hAppCallLeg,
		OUT RvSipCallLegHandle   *phNewCallLeg);

	/***************************************************************************
	* RvSipCallLegReferReject
	* ------------------------------------------------------------------------
	* General: This function is DEPRECATED!!! you should use the subscription refer API.
	*          In order to use it for code that written for earlier stack version,
	*          you must set the configuration parameter 'disableRefer3515Behavior' to true.
	*          Can be used in the "Refer Received" refer state to reject an
	*          incoming REFER request.
	* Return Value: RV_ERROR_INVALID_HANDLE    -  The handle to the call-leg is invalid.
	*               RV_ERROR_BADPARAM - The status code is invalid.
	*                 RV_ERROR_ILLEGAL_ACTION    - Invalid call-leg state for this action.
	*               RV_ERROR_UNKNOWN          - Failed to reject the call. (failed
	*                                     while trying to send the reject response).
	*               RV_OK -          Reject final response was sent successfully.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call leg the user wishes to reject the refer
	*            status   - The rejection response code.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegReferReject (
		IN  RvSipCallLegHandle   hCallLeg,
		IN  RvUint16            status);


	/***************************************************************************
	* RvSipCallLegReferStr
	* ------------------------------------------------------------------------
	* General: This function is DEPRECATED!!! you should use the subscription refer API.
	*          In order to use it for code that written for earlier stack version,
	*          you must set the configuration parameter 'disableRefer3515Behavior' to true.
	*          Sends a REFER associated with the call-leg. This function may be
	*          called only after the To and From header fields were set.
	*          Calling Refer causes a REFER request to be sent out and the
	*          call-leg refer state machine to progress to the Refer Sent
	*          state.
	*          This function is also used to send an authenticated refer
	*          request in the RVSIP_CALL_LEG_REFER_STATE_REFER_UNAUTHENTICATED.
	*          Note: this function is equivalent to RvSipCallLegRefer.The difference
	*          is that in this function the Refer-To and Referred-By parameters
	*          are given as strings.
	*          The strings may be addresses (for example: "sip:bob@172.20.1.20:5060"),
	*          for backward compatability, or headers strings ( for example:
	*          "Refer-To: A<sip:172.20.1.20:5060>")
	* Return Value: RV_ERROR_INVALID_HANDLE -  The handle to the call-leg is invalid.
	*                 RV_ERROR_ILLEGAL_ACTION - Invalid call-leg state for this action.
	*               RV_ERROR_OUTOFRESOURCES - Call-leg failed to create a new
	*                                   transaction.
	*               RV_ERROR_UNKNOWN - An error occurred while trying to send the
	*                              message (Couldn't send a message to the given
	*                            Request-Uri).
	*               RV_OK - REFER message was sent successfully.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg     - Handle to the call leg the user wishes to send REFER.
	*          strReferTo   - The Refer-To address to be sent in the Refer-To
	*                         header of the REFER request. or the Refer-To header itself.
	*                         The Refer-To header will be kept in the call-leg object.
	*                         When using this function for authenticating or
	*                           redirecting a previously sent refer request you can
	*                           set this parameter to NULL. The Refer-To header will
	*                            be taken from the call-leg object.
	*          strReferredBy - The Referred-By address to be sent in the
	*                         Referred-By header of the REFER request, or the
	*                         Referred-By header itself.
	*                         The Referred-By header will be kept in the call-leg object.
	*                         This parameter is optional. If not specified the call-leg
	*                         will use a default Referred-By header.
	*                         When using this function for authenticating or
	*                           redirecting a previously sent refer request you can
	*                           set this parameter to NULL. The Refer-To header will
	*                            be taken from the call-leg object.
	*          strReplaces  - The Replaces header to be sent in the Refer-To
	*                         header of the REFER request. The Replaces header string doesn't
	*                           contain the 'Replaces:'.
	*                         The Replaces header will be kept in the Refer-To header in
	*                           the call-leg object.
	*                         When using this function for authenticating or
	*                           redirecting a previously sent refer request you can
	*                           set this parameter to NULL. The Replaces header will
	*                            be taken from Refer-To header in the call-leg object.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegReferStr (
		IN  RvSipCallLegHandle   hCallLeg,
		IN  RvChar             *strReferTo,
		IN  RvChar             *strReferredBy,
		IN  RvChar              *strReplaces);

	/***************************************************************************
	* RvSipCallLegReferCancel
	* ------------------------------------------------------------------------
	* General: This function is obsolete. Cancel on REFER is illegal.
	*
	* Return Value: RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call leg.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegReferCancel (
		IN  RvSipCallLegHandle   hCallLeg);

	/***************************************************************************
	* RvSipCallLegReferNotify
	* ------------------------------------------------------------------------
	* General: This function is DEPRECATED!!! you should use the subscription refer API.
	*          In order to use it for code that written for earlier stack version,
	*          you must set the configuration parameter 'disableRefer3515Behavior' to true.
	*          Four call-legs are involved in a complete Refer operation:
	*          call-leg A  - the call-leg that sends the REFER request.
	*          call-leg B1 - the call-leg that receives the REFER request.
	*          call-leg B2 - a new call-leg created to contact the third party
	*          call-leg C  - The Refer-To call-leg.
	*
	*             A                       B1 B2               C
	*           |                        | |                |
	*           |   REFER                | |                |
	*           |----------------------->| |                |
	*           |        202 Accepted    | |                |
	*           |<-----------------------| | INVITE         |
	*           |                        | |--------------->|
	*           |                        | |  (whatever)    |
	*           |                        | |<---------------|
	*           |            NOTIFY      | |                |
	*           |<-----------------------| |                |
	*           |   200 OK               | |                |
	*           |----------------------->| |                |
	*           |                        |
	*           |                        |
	*          Once it is known whether B2 succeeded or failed contacting C,
	*          B1 will get a "Notify Ready" notification.
	*          By calling the RvSipCallLegReferNotify() B1 can send a NOTIFY
	*          message to A letting it know the REFER result.
	*          The NOTIFY message will include the "Event=refer" header.
	*          The body of the NOTIFY message will contain a SIP Response Status-Line
	*          with a status code given as a parameter to this function.
	*          If the application wishes to avoid sending the NOTIFY request is
	*          should call RvSipCallLegReferEnd() function instead.
	*          The RvSipCallLegReferNotify() function is also used to
	*          authenticate a previously sent NOTIFY request.
	* Return Value: RV_ERROR_INVALID_HANDLE -  The handle to the call-leg is invalid.
	*               RV_ERROR_OUTOFRESOURCES - Call-leg failed to create a new
	*                                   transaction.
	*               RV_ERROR_UNKNOWN - An error occurred while trying to send the
	*                              message (Couldn't send a message to the given
	*                            Request-Uri).
	*               RV_OK - NOTIFY message was sent successfully(if needed).
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call leg the user wishes to send REFER.
	*          status   - The status code that will be used to create a status
	*                     line for the NOTIFY request message body.
	*          cSeqStep - The Cseq step of the REFER transaction that this
	*                     NOTIFY relate to. This value will be set to the cseq
	*                     parameter of the Event header of the NOTIFY request.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegReferNotify (
		IN  RvSipCallLegHandle   hCallLeg,
		IN  RvInt16             status,
		IN  RvInt32             cSeqStep);

	/***************************************************************************
	* RvSipCallLegReferEnd
	* ------------------------------------------------------------------------
	* General: This function is DEPRECATED!!! you should use the subscription refer API.
	*          In order to use it for code that written for earlier stack version,
	*          you must set the configuration parameter 'disableRefer3515Behavior' to true.
	*          Four call-legs are involved in a complete Refer operation:
	*          call-leg A  - the call-leg that sends the REFER request.
	*          call-leg B1 - the call-leg that receives the REFER request.
	*          call-leg B2 - a new call-leg created to contact the third party
	*          call-leg C  - The Refer-To call-leg.
	*
	*             A                       B1 B2               C
	*           |                        | |                |
	*           |   REFER                | |                |
	*           |----------------------->| |                |
	*           |        202 Accepted    | |                |
	*           |<-----------------------| | INVITE         |
	*           |                        | |--------------->|
	*           |                        | |  (whatever)    |
	*           |                        | |<---------------|
	*           |                        |
	*          Once it is known whether B2 succeeded or failed contacting C,
	*          B1 will get a "Notify Ready" notification.
	*          At this point B1 can notify A about the result of the refer by
	*          sending NOTIFY request.
	*          1. Call the RvSipCallLegReferEnd() function to indicate that you
	*          do NOT wish to send the NOTIFY request.
	*          Note: If you call this function with a call-leg in the Idle state,
	*          the call-leg will be terminated.
	*          2. You can also use RvSipCallLegReferEnd() in the
	*          Unauthenticated and Redirected refer states of the call-leg in order
	*          to complete the refer process without re-sending a refer request.
	*          Calling ReferEnd() from states Unauthenticated or Redirected
	*          will return the call-leg to
	*          Idle refer state.
	* Return Value: RV_ERROR_INVALID_HANDLE -  The handle to the call-leg is invalid.
	*               RV_OK - REFER process was completed.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call leg the user wishes to send REFER.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegReferEnd (
		IN  RvSipCallLegHandle   hCallLeg);


	/***************************************************************************
	* RvSipCallLegReferGetCurrentState
	* ------------------------------------------------------------------------
	* General: This function is DEPRECATED!!! you should use the subscription refer API.
	*          In order to use it for code that written for earlier stack version,
	*          you must set the configuration parameter 'disableRefer3515Behavior' to true.
	*          Returns the Refer sub-state inside the call leg.
	* Return Value: RvStatus
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg     - Handle to the call leg the user wishes to get its Refer state.
	* Output:  peReferState - The Refer state.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegReferGetCurrentState(
		IN  RvSipCallLegHandle      hCallLeg,
		OUT RvSipCallLegReferState *peReferState);

	/***************************************************************************
	* RvSipCallLegReplacesDisconnect
	* ------------------------------------------------------------------------
	* General: This function is obsolete. In order to disconnect a replaces call
	*          use RvSipCallLegDisconnect.
	*
	* Return Value: RV_ERROR_INVALID_HANDLE  -  The handle to the call-leg is invalid.
	*               RV_ERROR_UNKNOWN        - Failed to send message (BYE or final
	*                                   rejection response).
	*               RV_ERROR_OUTOFRESOURCES - Request failed due to resource problem.
	*               RV_OK        - BYE message was sent successfully.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call leg the user wishes to disconnect.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegReplacesDisconnect(IN RvSipCallLegHandle hCallLeg);


	/***************************************************************************
	* RvSipCallLegReplacesGetMatchedCall
	* ------------------------------------------------------------------------
	* General: This function is obsolete. use RvSipCallLegReplacesGetMatchedCallExt
	*
	* Return Value: RvStatus
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg               - Handle to the call leg that received the INVITE with
	*                                   the Replaces header.
	* Output:  pbFoundNonInviteDialog - RV_TRUE if we found matched dialog which was not established
	*                                   with INVITE. For example, Subscription. In this case
	*                                   hMatchedCallLeg will be NULL and the application should
	*                                   return 401/481/501 to the INVITE with the Replaces.
	*          hMatchedCallLeg        - Handle to the call leg matched to the Replaces header.
	*                                   If there is no such call leg, this handle will be NULL,
	*                                   and 481 response will be sent to the original call leg
	*                                   (hCallLeg)
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegReplacesGetMatchedCall(
		IN  RvSipCallLegHandle         hCallLeg,
		OUT RvBool                   *pbFoundNonInviteDialog,
		OUT RvSipCallLegHandle        *hMatchedCallLeg);

	/***************************************************************************
	* RvSipCallLegReplacesGetMatchedCallExt
	* ------------------------------------------------------------------------
	* General: This function is called when the call leg is in the OFFERING state.
	*          This function searches for the call leg that has the same Call-ID,
	*          to tag and from tag as the Replaces header in the original call leg.
	*          If a matched call leg is found then this call leg is returned as
	*          the function output, otherwise this pointer will be NULL.
	*
	* Return Value: RvStatus
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call leg that received the INVITE with
	*                                   the Replaces header.
	* Output:  peReason - If we found a dialog with same dialog identifiers,
	*                     but still does not match the replaces header, this
	*                     parameter indicates why the dialog doesn't fit.
	*                     application should use this parameter to decide how to
	*                     respond (401/481/486/501) to the INVITE with the Replaces.
	*          hMatchedCallLeg - Handle to the call leg matched to the Replaces header.
	*                     If there is no such call leg, this handle will be NULL.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegReplacesGetMatchedCallExt(
		IN  RvSipCallLegHandle         hCallLeg,
		OUT RvSipCallLegReplacesReason *peReason,
		OUT RvSipCallLegHandle        *hMatchedCallLeg);
	/***************************************************************************
	* RvSipCallLegReplacesPrepareHeaderFromCallLeg
	* ------------------------------------------------------------------------
	* General: This function prepares a Replaces header from the Call-ID, from-tag and
	*          to-tag of a Call-Leg
	*
	* Return Value: RvStatus
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg        - Handle to the call leg to make the Replaces header from.
	*          hReplacesHeader - Handle to a Constructed Replaces header.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegReplacesPrepareHeaderFromCallLeg(
		IN    RvSipCallLegHandle         hCallLeg,
		IN    RvSipReplacesHeaderHandle  hReplacesHeader);

	/***************************************************************************
	* RvSipCallLegReplacesCompareReplacesToCallLeg
	* ------------------------------------------------------------------------
	* General: This function compares a Call leg to a Replaces header. The Call leg and Replaces
	*          header are equal if the Call-ID, from-tag and to-tag are equal.
	*
	* Return Value: RvStatus
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg        - Handle to the call leg to compare with the Replaces header.
	*          hReplacesHeader - Handle to a Replaces header.
	* Output:  pbIsEqual       - The result of the comparison. RV_TRUE if the Call-leg and
	*                            Replaces header are equal, RV_FALSE - otherwise.
	***************************************************************************/
	RVAPI RvStatus    RVCALLCONV RvSipCallLegReplacesCompareReplacesToCallLeg(IN  RvSipCallLegHandle        hCallLeg,
		IN  RvSipReplacesHeaderHandle hReplacesHeader,
		OUT RvBool                  *pbIsEqual);


	/*-----------------------------------------------------------------------
	C A L L  - L E G:  G E T   A N D   S E T    A P I
	------------------------------------------------------------------------*/

	/***************************************************************************
	* RvSipCallLegGetNewPartyHeaderHandle
	* ------------------------------------------------------------------------
	* General:Allocates a new Party header and returns the new Party header
	*         handle.
	*         In order to set the To or From headers of a call-leg ,the application
	*         should:
	*         1. Get a new party header handle using this function.
	*         2. Fill the party header information and set it back using
	*            RvSipCallLegSetToHeader() or RvSipCallLegSetFromHeader().
	* Return Value: RV_ERROR_INVALID_HANDLE  - The call-leg handle is invalid.
	*               RV_ERROR_NULLPTR     - Bad pointer to party handle was given.
	*               RV_ERROR_OUTOFRESOURCES - Not enough resources to allocate.
	*               RV_OK        - New party header was allocated successfully
	*                                   and its handle was returned.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call-leg.
	* Output:     phParty - Handle to the newly created party header.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegGetNewPartyHeaderHandle (
		IN   RvSipCallLegHandle      hCallLeg,
		OUT  RvSipPartyHeaderHandle  *phParty);


	/***************************************************************************
	* RvSipCallLegGetNewReferToHeaderHandle
	* ------------------------------------------------------------------------
	* General:This function is DEPRECATED!!! you should use the subscription refer API.
	*         In order to use it for code that written for earlier stack version,
	*         you must set the configuration parameter 'disableRefer3515Behavior' to true.
	*         Allocates a new Refer-To header and returns the new Refer-To header
	*         handle.
	*         In order to set the Refer-To header of a call-leg ,the application
	*         should:
	*         1. Get a new Refer-To header handle using this function.
	*         2. Fill the Refer-To header information and set it back using
	*            RvSipCallLegRefer().
	* Return Value: RV_ERROR_INVALID_HANDLE  - The call-leg handle is invalid.
	*               RV_ERROR_NULLPTR     - Bad pointer to party handle was given.
	*               RV_ERROR_OUTOFRESOURCES - Not enough resources to allocate.
	*               RV_OK        - New party header was allocated successfully
	*                                   and its handle was returned.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg  - Handle to the call-leg.
	* Output:     phReferTo - Handle to the newly created Refer-To header.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegGetNewReferToHeaderHandle (
		IN   RvSipCallLegHandle         hCallLeg,
		OUT  RvSipReferToHeaderHandle  *phReferTo);


	/***************************************************************************
	* RvSipCallLegGetNewReplacesHeaderHandle
	* ------------------------------------------------------------------------
	* General:Allocates a new Replaces header and returns the new Replaces header
	*         handle.
	*         In order to set the Replaces header of a call-leg ,the application
	*         should:
	*         1. Get a new Replaces header handle using this function.
	*         2. Fill the Replaces header information and set it back using
	*            RvSipCallLegSetReplaces().
	* Return Value: RV_ERROR_INVALID_HANDLE  - The call-leg handle is invalid.
	*               RV_ERROR_NULLPTR     - Bad pointer to party handle was given.
	*               RV_ERROR_OUTOFRESOURCES - Not enough resources to allocate.
	*               RV_OK        - New party header was allocated successfully
	*                                   and its handle was returned.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg  - Handle to the call-leg.
	* Output:     phReplaces - Handle to the newly created Replaces header.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegGetNewReplacesHeaderHandle (
		IN   RvSipCallLegHandle         hCallLeg,
		OUT  RvSipReplacesHeaderHandle  *phReplaces);


	/***************************************************************************
	* RvSipCallLegGetNewReferredByHeaderHandle
	* ------------------------------------------------------------------------
	* General:This function is DEPRECATED!!! you should use the subscription refer API.
	*         In order to use it for code that written for earlier stack version,
	*         you must set the configuration parameter 'disableRefer3515Behavior' to true.
	*         Allocates a new Referred-By header and returns the new Referred-By header
	*         handle.
	*         In order to set the Referred-By header of a call-leg ,the application
	*         should:
	*         1. Get a new Referred-By header handle using this function.
	*         2. Fill the Referred-By header information and set it back using
	*            RvSipCallLegRefer().
	* Return Value: RV_ERROR_INVALID_HANDLE  - The call-leg handle is invalid.
	*               RV_ERROR_NULLPTR     - Bad pointer to party handle was given.
	*               RV_ERROR_OUTOFRESOURCES - Not enough resources to allocate.
	*               RV_OK        - New party header was allocated successfully
	*                                   and its handle was returned.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg     - Handle to the call-leg.
	* Output:     phReferredBy - Handle to the newly created Referred-By header.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegGetNewReferredByHeaderHandle (
		IN   RvSipCallLegHandle            hCallLeg,
		OUT  RvSipReferredByHeaderHandle  *phReferredBy);



	/***************************************************************************
	* RvSipCallLegGetNewAddressHandle
	* ------------------------------------------------------------------------
	* General: Allocates a new Address header and returns its handle.
	*          When the application wishes to set one of the call leg address
	*          fields (for example the remote contact) it should use this function
	*          to get new address header. After setting the relevant
	*          information in the header it should be set back in the call-leg
	*          using the correct API function.
	* Return Value: RV_ERROR_INVALID_HANDLE  - The call-leg handle is invalid.
	*               RV_ERROR_NULLPTR     - Bad pointer to address handle was given.
	*               RV_ERROR_OUTOFRESOURCES - Not enough resources to allocate.
	*               RV_OK        - New address header was allocated successfully
	*                                   and its handle was returned.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg  - Handle to the call-leg.
	*            eAddrType - Type of address the application wishes to create.
	* Output:     phAddr    - Handle to the newly created address header.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegGetNewAddressHandle (
		IN   RvSipCallLegHandle      hCallLeg,
		IN  RvSipAddressType         eAddrType,
		OUT  RvSipAddressHandle      *phAddr);

	/***************************************************************************
	* RvSipCallLegSetCallId
	* ------------------------------------------------------------------------
	* General: Sets the call-leg call-id.
	* Return Value: RV_ERROR_INVALID_HANDLE  - The call-leg handle is invalid.
	*               RV_ERROR_NULLPTR     - Bad pointer was given by the application.
	*               RV_ERROR_OUTOFRESOURCES - Not enough memory to allocate.
	*               RV_OK        - Call-id was set successfully.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - The Sip Stack handle to the call-leg
	*            strCallId - Null terminating string with the new call Id.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegSetCallId (
		IN  RvSipCallLegHandle   hCallLeg,
		IN  RvChar              *strCallId);



	/***************************************************************************
	* RvSipCallLegGetCallId
	* ------------------------------------------------------------------------
	* General:Copies the call-leg Call-Id into a given buffer.
	*         If the buffer allocated by the application is insufficient
	*         an RV_ERROR_INSUFFICIENT_BUFFER status is returned and actualSize
	*         contains the size of the Call-ID string in the call-leg.
	*
	* Return Value: RV_ERROR_INSUFFICIENT_BUFFER - The buffer given by the application
	*                                       was insufficient.
	*               RV_ERROR_NOT_FOUND           - The call-leg does not contain a call-id
	*                                       yet.
	*               RV_OK            - Call-id was copied into the
	*                                       application buffer. The size is
	*                                       returned in the actualSize param.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg   - The Sip Stack handle to the call-leg.
	*          bufSize    - The size of the application buffer for the call-id.
	* Output:     strCallId  - An application allocated buffer.
	*          actualSize - The call-id actual size.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegGetCallId (
		IN  RvSipCallLegHandle   hCallLeg,
		IN  RvInt32              bufSize,
		OUT RvChar              *strCallId,
		OUT RvInt32             *actualSize);
	/***************************************************************************
	* RvSipCallLegSetCSeq
	* ------------------------------------------------------------------------
	* General: Sets the call-leg outgoing CSeq step counter.
	* Return Value: RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - The Sip Stack handle to the call-leg
	*            cseq - The cseq step.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegSetCSeq (
		IN  RvSipCallLegHandle  hCallLeg,
		IN  RvInt32            cseq);

	/***************************************************************************
	* RvSipCallLegGetCSeq
	* ------------------------------------------------------------------------
	* General: Gets the call-leg outgoing CSeq step counter.
	*
	* Return Value: RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg   - The Sip Stack handle to the call-leg.
	* Output:     cseq       - The cseq step.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegGetCSeq (
		IN  RvSipCallLegHandle   hCallLeg,
		OUT RvInt32             *cseq);

	/***************************************************************************
	* RvSipCallLegGetRemoteCSeq
	* ------------------------------------------------------------------------
	* General: Gets the call-leg incoming CSeq step counter.
	*
	* Return Value: RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg   - The Sip Stack handle to the call-leg.
	* Output:     cseq       - The remote cseq step.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegGetRemoteCSeq (
		IN  RvSipCallLegHandle   hCallLeg,
		OUT RvInt32             *cseq);

	/***************************************************************************
	* RvSipCallLegSetFromHeader
	* ------------------------------------------------------------------------
	* General: Sets the from header associated with the call-leg. Note
	*          that attempting to alter the from header after call has
	*          been initiated might cause unexpected results.
	* Return Value: RV_ERROR_INVALID_HANDLE  - The call-leg handle is invalid.
	*               RV_ERROR_NULLPTR     - Bad pointer was given by the application.
	*               RV_ERROR_OUTOFRESOURCES - Not enough memory to allocate.
	*               RV_OK - From header was set successfully.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call-leg.
	*            hFrom    - Handle to an application constructed from header.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegSetFromHeader (
		IN  RvSipCallLegHandle      hCallLeg,
		IN  RvSipPartyHeaderHandle  hFrom);


	/***************************************************************************
	* RvSipCallLegGetFromHeader
	* ------------------------------------------------------------------------
	* General: Returns the from header associated with the call.
	*         Attempting to alter the from header after
	*         call left the Idle state might cause unexpected results.
	* Return Value: RV_ERROR_INVALID_HANDLE  - The call-leg handle is invalid.
	*               RV_ERROR_NULLPTR     - Bad pointer was given by the application.
	*               RV_OK        - From header was returned successfully.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call-leg.
	* Output:     phFrom -   Pointer to the call-leg From header handle.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegGetFromHeader (
		IN    RvSipCallLegHandle      hCallLeg,
		OUT RvSipPartyHeaderHandle    *phFrom);


	/***************************************************************************
	* RvSipCallLegSetToHeader
	* ------------------------------------------------------------------------
	* General: Sets the To header associated with the call-leg. Note
	*          that attempting to alter the To header after call left the Idle state
	*          might cause unexpected results.
	* Return Value: RV_ERROR_INVALID_HANDLE  - The call-leg handle is invalid.
	*               RV_ERROR_NULLPTR     - Bad pointer was given by the application.
	*               RV_ERROR_OUTOFRESOURCES - Not enough memory to allocate.
	*               RV_OK - To header was set successfully.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call-leg.
	*            hTo      - Handle to an application constructed To header.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegSetToHeader (
		IN  RvSipCallLegHandle       hCallLeg,
		IN  RvSipPartyHeaderHandle   hTo);



	/***************************************************************************
	* RvSipCallLegGetToHeader
	* ------------------------------------------------------------------------
	* General: Returns the To address associated with the call.
	*          Attempting to alter the To address after
	*          call has been initiated might cause unexpected results.
	* Return Value: RV_ERROR_INVALID_HANDLE  - The call-leg handle is invalid.
	*               RV_ERROR_NULLPTR     - Bad pointer was given by the application.
	*               RV_OK        - To header was returned successfully.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call-leg.
	* Output:     phTo     - Pointer to the call-leg To header handle.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegGetToHeader (
		IN    RvSipCallLegHandle        hCallLeg,
		OUT   RvSipPartyHeaderHandle    *phTo);



	/***************************************************************************
	* RvSipCallLegSetRemoteContactAddress
	* ------------------------------------------------------------------------
	* General: Set the contact address of the remote party. This is the address
	*          with which the remote party may be contacted with. This method
	*          may be used for outgoing calls when the user wishes to use a
	*          Request-URI that is different from the call-leg's To header.
	* Return Value: RV_ERROR_INVALID_HANDLE  - The call-leg handle is invalid.
	*               RV_ERROR_NULLPTR     - Bad pointer was given by the application.
	*                 RV_ERROR_BADPARAM - The supplied address type is not supported.
	*               RV_ERROR_OUTOFRESOURCES - Not enough memory to allocate.
	*               RV_OK        - New remote contact was set successfully.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call-leg.
	*            hContactAddress - Handle to an Address header.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegSetRemoteContactAddress (
		IN  RvSipCallLegHandle   hCallLeg,
		IN  RvSipAddressHandle   hContactAddress);




	/***************************************************************************
	* RvSipCallLegGetRemoteContactAddress
	* ------------------------------------------------------------------------
	* General: Get the remote party's contact address. This is the
	*          address supplied by the remote party by which it can be
	*          directly contacted in future requests.
	* Return Value: RV_ERROR_INVALID_HANDLE  - The call-leg handle is invalid.
	*               RV_ERROR_NULLPTR     - Bad pointer was given by the application.
	*               RV_OK.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg         - Handle to the call-leg.
	* Output:     phContactAddress - Pointer to the call-leg Remote Contact Address.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegGetRemoteContactAddress (
		IN  RvSipCallLegHandle   hCallLeg,
		OUT RvSipAddressHandle   *phContactAddress);


	/***************************************************************************
	* RvSipCallLegSetLocalContactAddress
	* ------------------------------------------------------------------------
	* General: Sets the local contact address which the SIP stack uses
	*          to identify itself to the remote party. The
	*          local contact address is used by the remote party to
	*          directly contact the local party.
	* Return Value: RV_ERROR_INVALID_HANDLE  - The call-leg handle is invalid.
	*               RV_ERROR_NULLPTR     - Bad pointer was given by the application.
	*                 RV_ERROR_BADPARAM - The supplied address type is not supported.
	*               RV_ERROR_OUTOFRESOURCES - Not enough memory to allocate.
	*               RV_OK        - New local contact was set successfully.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call-leg
	*            hContactAddress - Handle to the local contact address header.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegSetLocalContactAddress (
		IN  RvSipCallLegHandle   hCallLeg,
		IN  RvSipAddressHandle   hContactAddress);


	/***************************************************************************
	* RvSipCallLegGetLocalContactAddress
	* ------------------------------------------------------------------------
	* General: Gets the local contact address which the SIP stack uses
	*          to identify itself to the remote party. If no value is
	*          supplied the From header's address part is taken. The
	*          local contact address is used by the remote party to
	*          directly contact the local party.
	* Return Value: RV_ERROR_INVALID_HANDLE  - The call-leg handle is invalid.
	*               RV_ERROR_NULLPTR     - Bad pointer was given by the application.
	*               RV_OK.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg        - Handle to the call-leg.
	* Output:     phContactAddress - Handle to the local contact address header.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegGetLocalContactAddress (
		IN  RvSipCallLegHandle   hCallLeg,
		OUT RvSipAddressHandle   *phContactAddress);



	/***************************************************************************
	* RvSipCallLegSetPersistency
	* ------------------------------------------------------------------------
	* General: Changes the call-leg persistency definition at runtime.
	* This function receives a Boolean value that indicates whether or not the
	* application wishes this call-leg to be persistent. A persistent call-leg
	* object will apply its persistency to the transactions it creates. A persistent
	* transaction will try to locate a suitable connection in the connection hash before
	* opening a new connection. A persistent call-leg will also try to use the
	* same connection for all outgoing requests by applying the last-used connection
	* object to the next-created transaction.
	* Return Value: RvStatus
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:    hCallLeg - The call-leg handle
	*          bIsPersistent - Determines the call-leg persistency definition.
	*                          RV_TRUE indicates that the call-leg is persistent.
	*                          Otherwise, RV_FALSE.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegSetPersistency(
		IN RvSipCallLegHandle       hCallLeg,
		IN RvBool                  bIsPersistent);

	/***************************************************************************
	* RvSipCallLegGetPersistency
	* ------------------------------------------------------------------------
	* General: Returns the call-leg persistency definition.
	* Return Value: RvStatus
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:    hCallLeg - The call-leg handle
	* Output:  pbIsPersistent - The call-leg persistency definition.
	*                           RV_TRUE indicates that the call-leg is persistent. Otherwise,
	*                           RV_FALSE.
	***************************************************************************/
	RVAPI  RvStatus RVCALLCONV RvSipCallLegGetPersistency(
		IN  RvSipCallLegHandle                   hCallLeg,
		OUT RvBool                             *pbIsPersistent);


	/***************************************************************************
	* RvSipCallLegSetConnection
	* ------------------------------------------------------------------------
	* General: Sets a connection object to be used by the call-leg transactions.
	* The call-leg object will hold this connection in its internal database.
	* Whenever the call-leg creates a new transaction, it supplies the
	* transaction with the given connection. The transaction will use the connection
	* only if it fits the local and remote addresses of the transaction. Otherwise, the
	* transaction will either locate a suitable connection in the connection hash or
	* create a new connection. The call-leg object will be informed that the
	* supplied connection did not fit, and that a different connection was used and will
	* update its database.
	* Note: this function can be used only if the call-leg is persistent.
	* Return Value: RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call-leg
	*          hConn - Handle to the connection.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegSetConnection(
		IN  RvSipCallLegHandle                hCallLeg,
		IN  RvSipTransportConnectionHandle   hConn);

	/***************************************************************************
	* RvSipCallLegGetConnection
	* ------------------------------------------------------------------------
	* General: Returns the connection that the call-leg transactions are currently using.
	* Note: Only persistent call-legs keep the currently-used connection. NULL
	* will be returned if the call-leg is not persistent.
	* Return Value: RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call-leg.
	* Output:    phConn - Handle to the currently used connection
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegGetConnection(
		IN  RvSipCallLegHandle             hCallLeg,
		OUT  RvSipTransportConnectionHandle *phConn);

	/***************************************************************************
	* RvSipCallLegGetReferToAddress
	* ------------------------------------------------------------------------
	* General: This function is DEPRECATED!!! you should use the subscription refer API.
	*          In order to use it for code that written for earlier stack version,
	*          you must set the configuration parameter 'disableRefer3515Behavior' to true.
	*          Gets the Refer-To address associated with the call-leg.
	* Return Value: RV_ERROR_INVALID_HANDLE  - The call-leg handle is invalid.
	*               RV_ERROR_NULLPTR     - Bad pointer was given by the application.
	*               RV_OK.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg        - Handle to the call-leg.
	* Output:     phReferToAddress - Handle to the Refer-To address header.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegGetReferToAddress (
		IN  RvSipCallLegHandle   hCallLeg,
		OUT RvSipAddressHandle  *phReferToAddress);


	/***************************************************************************
	* RvSipCallLegGetReferredByAddress
	* ------------------------------------------------------------------------
	* General: This function is DEPRECATED!!! you should use the subscription refer API.
	*          In order to use it for code that written for earlier stack version,
	*          you must set the configuration parameter 'disableRefer3515Behavior' to true.
	*          Gets the Referred-By address associated with the call-leg.
	* Return Value: RV_ERROR_INVALID_HANDLE  - The call-leg handle is invalid.
	*               RV_ERROR_NULLPTR     - Bad pointer was given by the application.
	*               RV_OK.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg        - Handle to the call-leg.
	* Output:     phReferredByAddress - Handle to the Referred-By address header.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegGetReferredByAddress (
		IN  RvSipCallLegHandle   hCallLeg,
		OUT RvSipAddressHandle  *phReferredByAddress);

	/***************************************************************************
	* RvSipCallLegGetReplacesStatus
	* ------------------------------------------------------------------------
	* General: Return the replaces option tag status of a received Invite/Refer request.
	*
	* Return Value: RvStatus
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg       - The call-leg handle.
	* Output:  replacesStatus - The replaces status received in the INVITE/REFER request.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegGetReplacesStatus(
		IN  RvSipCallLegHandle             hCallLeg,
		OUT RvSipCallLegReplacesStatus    *replacesStatus);

	/***************************************************************************
	* RvSipCallLegGetReplacesHeader
	* ------------------------------------------------------------------------
	* General: Get the Replaces header from the Call-Leg. This function should be called
	*          before sending an INVITE - to get the replaces header set by the REFER message,
	*          if it exists, or when receiving an INVITE - from the evStateChanged, in order
	*          to know if the INVITE contained Replaces header.
	* Return Value: RV_ERROR_INVALID_HANDLE  - The call-leg handle is invalid.
	*               RV_ERROR_NULLPTR     - Bad pointer was given by the application.
	*                 RV_ERROR_BADPARAM - The supplied address type is not supported.
	*               RV_ERROR_OUTOFRESOURCES - Not enough memory to allocate.
	*               RV_OK        - New remote contact was set successfully.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call-leg.
	* Output:    hReplacesHeader - pointer to an handle to a Replaces header.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegGetReplacesHeader(IN  RvSipCallLegHandle        hCallLeg,
		OUT RvSipReplacesHeaderHandle *phReplacesHeader);

	/***************************************************************************
	* RvSipCallLegSetReplacesHeader
	* ------------------------------------------------------------------------
	* General: Set the Replaces header in the Call-Leg. This function should be called
	*          before sending the INVITE request, when the call is in the idle state
	*          The application should call this function when it wants to add a Replaces
	*          header to the INVITE. If the application wants not to add a Replaces header
	*          that was received in the REFER message, and should be added to the INVITE
	*          triggered by the REFER, it should call this function with NULL as the
	*          replaces header
	* Return Value: RV_ERROR_INVALID_HANDLE  - The call-leg handle is invalid.
	*               RV_ERROR_NULLPTR     - Bad pointer was given by the application.
	*                 RV_ERROR_BADPARAM - The supplied address type is not supported.
	*               RV_ERROR_OUTOFRESOURCES - Not enough memory to allocate.
	*               RV_OK        - New remote contact was set successfully.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call-leg.
	*            hReplacesHeader - Handle to a Replaces header.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegSetReplacesHeader(IN  RvSipCallLegHandle        hCallLeg,
		IN  RvSipReplacesHeaderHandle hReplacesHeader);


	/***************************************************************************
	* RvSipCallLegGetCurrentState
	* ------------------------------------------------------------------------
	* General: Gets the call-leg current state
	* Return Value: RV_ERROR_INVALID_HANDLE - if the given call leg handle is invalid
	*               RV_ERROR_NULLPTR    - Bad pointer was given by the application.
	*               RV_OK.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - The call-leg handle.
	* Output:     peState -  The call-leg current state.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegGetCurrentState (
		IN  RvSipCallLegHandle   hCallLeg,
		OUT RvSipCallLegState    *peState);


	/***************************************************************************
	* RvSipCallLegGetCurrentModifyState
	* ------------------------------------------------------------------------
	* General: Gets the call-leg current modify state
	* Return Value: RV_ERROR_INVALID_HANDLE - if the given call leg handle is invalid
	*               RV_ERROR_NULLPTR    - Bad pointer was given by the application.
	*               RV_OK.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - The call-leg handle.
	* Output:     peState -  The call-leg current modify state.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegGetCurrentModifyState (
		IN  RvSipCallLegHandle       hCallLeg,
		OUT RvSipCallLegModifyState  *peModifyState);


	/***************************************************************************
	* RvSipCallLegSetAppHandle
	* ------------------------------------------------------------------------
	* General: Sets the call-leg application handle. Usually the application
	*          replaces handles with the stack in the RvSipCallLegCreatedEv()
	*          callback or the RvSipCallLegMgrCreateCallLeg() API function.
	*          This function is used if the application wishes to set a new
	*          application handle.
	* Return Value: RvStatus
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg    - Handle to the call-leg.
	*            hAppCallLeg - A new application handle to the call-leg
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegSetAppHandle (
		IN  RvSipCallLegHandle     hCallLeg,
		IN  RvSipAppCallLegHandle  hAppCallLeg);

	/***************************************************************************
	* RvSipCallLegGetAppHandle
	* ------------------------------------------------------------------------
	* General: Returns the application handle of this call-leg.
	* Return Value: RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call-leg.
	* Output:     phAppCallLeg     - The application handle of the call-leg.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegGetAppHandle (
		IN    RvSipCallLegHandle    hCallLeg,
		OUT   RvSipAppCallLegHandle *phAppCallLeg);

	/***************************************************************************
	* RvSipCallLegGetDirection
	* ------------------------------------------------------------------------
	* General: Queries the call-leg direction. A call-leg can be either an
	*          Incoming call or an Outgoing call. When you create a call,
	*          it is always an Outgoing call. If the call is created because
	*          an Invite has arrived, the call is an Incoming call.
	* Return Value: RV_ERROR_INVALID_HANDLE - if the given call leg handle is invalid
	*               RV_ERROR_NULLPTR    - Bad pointer was given by the application.
	*               RV_OK.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg -     The call-leg handle.
	* Output:     *peDirection - The call-leg direction.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegGetDirection (
		IN  RvSipCallLegHandle     hCallLeg,
		OUT RvSipCallLegDirection  *peDirection);

	/***************************************************************************
	* RvSipCallLegGetTranscByMsg
	* ------------------------------------------------------------------------
	* General: Gets the transaction of a given message
	*          Use this function to know the transaction handle of a specific
	*          message.
	* Return Value: RV_ERROR_INVALID_HANDLE - if the given call leg handle is invalid
	*               RV_ERROR_NULLPTR    - Bad pointer was given by the application.
	*               RV_OK.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - The call-leg handle.
	*          hMsg     - The message handle
	*          bIsMsgRcvd - RV_TRUE if this is a received message. RV_FALSE otherwise.
	* Output:     phTransc -  The handle of the transaction this message belongs to.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegGetTranscByMsg (
		IN  RvSipCallLegHandle     hCallLeg,
		IN  RvSipMsgHandle         hMsg,
		IN  RvBool                bIsMsgRcvd,
		OUT RvSipTranscHandle      *phTransc);

	/***************************************************************************
	* RvSipCallLegGet100RelStatus
	* ------------------------------------------------------------------------
	* General: Return the 100rel option tag status of a received Invite request.
	*          The 100rel option tag indicates whether the remote party
	*          Support/Require the PRACK extension. In case of a Require status
	*          the application should use the RvSipCallLegProvisionalResponseReliable
	*          and send a reliable provisional response.
	* Return Value: RvStatus
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg  - The transaction handle.
	* Output:  relStatus - the reliable status received in the INVITE request.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegGet100RelStatus(
		IN RvSipCallLegHandle            hCallLeg,
		OUT RvSipTransaction100RelStatus *relStatus);
	/***************************************************************************
	* RvSipCallLegGetCallLegMgr
	* ------------------------------------------------------------------------
	* General: Return the call leg manager handle
	* Return Value: RvStatus
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg     - The call leg handle.
	* Output:  phCallLegMgr - The call leg manager handle
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegGetCallLegMgr(
		IN  RvSipCallLegHandle            hCallLeg,
		OUT RvSipCallLegMgrHandle         *phCallLegMgr);


	/***************************************************************************
	* RvSipCallLegGetReceivedMsg
	* ------------------------------------------------------------------------
	* General: Gets the message that was received by the call-leg. You can
	*          call this function from the state changed call back function
	*          when the new state indicates that a message was received.
	*          If there is no valid received message, NULL will be returned.
	*
	* Return Value: RvStatus
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - The call-leg handle.
	* Output:     phMsg    -  pointer to the received message.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegGetReceivedMsg(
		IN  RvSipCallLegHandle  hCallLeg,
		OUT RvSipMsgHandle       *phMsg);

	/***************************************************************************
	* RvSipCallLegGetOutboundMsg
	* ------------------------------------------------------------------------
	* General: Gets the message that is going to be sent by the call-leg.
	*          You can call this function before you call API functions such as
	*          Connect(), Accept() Reject() etc, or from the state changed
	*          callback function when the new state indicates that a message
	*          is going to be sent.
	*          Note: The message you receive from this function is not complete.
	*          In some cases it might even be empty.
	*          You should use this function to add headers to the message before
	*          it is sent. To view the complete message use event message to
	*          send.
	*          Note: The section of using RvSipCallLegGetOutboundMsg and sending
	*          the message is critical. For example, if you call
	*          RvSipCallLegGetOutboundMsg and Connect, your object must be locked.
	* Return Value: RvStatus
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - The call-leg handle.
	* Output:     phMsg   -  pointer to the message.
	***************************************************************************/
	RVAPI  RvStatus RVCALLCONV RvSipCallLegGetOutboundMsg(
		IN  RvSipCallLegHandle     hCallLeg,
		OUT RvSipMsgHandle            *phMsg);

	/***************************************************************************
	* RvSipCallLegGetOutboundAckMsg
	* ------------------------------------------------------------------------
	* General: Gets the ACK message that is going to be sent by the call-leg.
	*          You can call this function only at the REMOTE_ACCEPTED state 
	*          before calling the RvSipCallLegAck() API function.
	*          Note: If the call-leg is an original call-leg created by the
	*          application you can use RvSipCallLegGetOutboundMsg() function.
	*          for a forked call-leg you must use the 
	*          RvSipCallLegGetOutboundMsgForAck() function.
	*          Note: You must not use this function to add headers that the stack
	*          is responsible for adding such as To, From, Call-ID Via and Route.
	*          doing so will cause unexpected behavior of the call-leg.
	*          Note If your application is multithreaded you must lock your 
	*          application object before calling the RvSipCallLegGetOutboundMsgForAck() 
	*          function and unlock it only after calling the RvSipCallLegAck() function.
	*          
	* Return Value: RvStatus
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - The call-leg handle.
	* Output:    phMsg   -  A pointer to the message.
	***************************************************************************/
	RVAPI  RvStatus RVCALLCONV RvSipCallLegGetOutboundAckMsg(
		IN  RvSipCallLegHandle     hCallLeg,
		OUT RvSipMsgHandle            *phMsg);


	/***************************************************************************
	* RvSipCallLegResetOutboundMsg
	* ------------------------------------------------------------------------
	* General: Sets the outbound message of the call-leg to NULL. If the
	*          call-leg is about to send a message it will create its own
	*          message to send.
	* Return Value: RvStatus
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - The call-leg handle.
	***************************************************************************/
	RVAPI  RvStatus RVCALLCONV RvSipCallLegResetOutboundMsg(
		IN  RvSipCallLegHandle     hCallLeg);

	/***************************************************************************
	* RvSipCallLegGetSubscription
	* ------------------------------------------------------------------------
	* General: Gets a subscription handle from call-leg subscriptions list.
	*          User may use the location and hItem parameters, to go over the list.
	* Return Value: RV_ERROR_INVALID_HANDLE - if the given call leg handle is invalid
	*               RV_ERROR_NULLPTR    - Bad pointer was given by the application.
	*               RV_OK.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - The call-leg handle.
	*          location - The location in list ?next, previous, first or last.
	*          hRelative - Handle to the current position in the list (a relative
	*                      subscription from the list). Supply this value if you choose
	*                      next or previous in the location parameter.
	* Output:     phSubs   -  The handle of the returned subscription.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegGetSubscription (
		IN  RvSipCallLegHandle     hCallLeg,
		IN  RvSipListLocation      location,
		IN  RvSipSubsHandle        hRelative,
		OUT RvSipSubsHandle        *phSubs);
	/***************************************************************************
	* RvSipCallLegGetStackInstance
	* ------------------------------------------------------------------------
	* General: Returns the handle to the stack instance to which this call-leg
	*          belongs to.
	*
	* Return Value: RvStatus
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg        - Handle to the call-leg object.
	* Output:     phStackInstance - A valid pointer which will be updated with a
	*                            handle to the stack instance.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegGetStackInstance(
		IN   RvSipCallLegHandle   hCallLeg,
		OUT  void*       *phStackInstance);

	/*-----------------------------------------------------------------------
	C A L L  - L E G   HIGH AVAILABILITY   F U N C T I O N S
	------------------------------------------------------------------------*/

	/***************************************************************************
	* RvSipCallLegGetConnectedCallStorageSize
	* ------------------------------------------------------------------------
	* General: Gets the size of buffer needed to store all parameters of a connected call.
	*          (The size of buffer, that should be supplied in RvSipCallLegStoreConnectedCall()).
	* Return Value:RvStatus
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call-leg .
	* Output:  len - the size of buffer. will be -1 in case of failure.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegGetConnectedCallStorageSize(
		IN  RvSipCallLegHandle hCallLeg,
		OUT RvInt32*           len);

	/***************************************************************************
	* RvSipCallLegStoreConnectedCall
	* ------------------------------------------------------------------------
	* General: Copies all call-leg parameters from a given call-leg to a given buffer.
	*          This buffer should be supplied when restoring the call leg.
	*          In order to store call-leg information the call leg must be in the
	*          connected state.
	* Return Value:RvStatus
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call-leg .
	*            memBuff  - The buffer that will be filled with the callLeg information.
	*          buffLen  - The length of the given buffer.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegStoreConnectedCall(
		IN RvSipCallLegHandle hCallLeg,
		IN void*              memBuff,
		IN RvUint32          buffLen);

	/***************************************************************************
	* RvSipCallLegRestoreConnectedCall
	* ------------------------------------------------------------------------
	* General: Restore all call-leg information into a given call-leg. The call-leg
	*          will assume the connected state and all call-leg parameters will be
	*          initialized from the given buffer.
	* Return Value:RvStatus
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:   hCallLeg   - Handle to the call-leg.
	*          memBuff    - The buffer that stores all the call-leg information
	*          buffLen    - The buffer size
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegRestoreConnectedCall(
		IN RvSipCallLegHandle   hCallLeg,
		IN void                *memBuff,
		IN RvUint32             buffLen);

	/*-----------------------------------------------------------------------
	C A L L  - L E G   SESSION TIMER   F U N C T I O N S
	------------------------------------------------------------------------*/

	/***************************************************************************
	* RvSipCallLegSessionTimerRefresh
	* ------------------------------------------------------------------------
	* General: Causes a re-INVITE to be sent in order to refresh the session time.
	*          Can be called only in the connected
	*          state when there is no other pending re-Invite transaction.
	*          The remote-party's response to the re-INVITE will be given
	*          in the EvModifyResultRecvd callback.
	* Return Value: RV_ERROR_INVALID_HANDLE -  The handle to the call-leg is invalid.
	*                 RV_ERROR_ILLEGAL_ACTION - Invalid call-leg state for this action.
	*               RV_ERROR_OUTOFRESOURCES - Request failed due to resource problem.
	*               RV_ERROR_UNKNOWN - Failed to send re-Invite.
	*               RV_OK - Invite message was sent successfully.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call leg the user wishes to refresh the call.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegSessionTimerRefresh(
		IN  RvSipCallLegHandle   hCallLeg);
	/***************************************************************************
	* RvSipCallLegTranscSessionTimerGeneralRefresh
	* ------------------------------------------------------------------------
	* General: Creates a transaction related to the call-leg and sends a
	*          Request message with the given method in order to refresh the call.
	*          The only general transaction which allowed is "UPDATE".
	*          The request will have the To, From and Call-ID of the call-leg and
	*          will be sent with a correct CSeq step. It will be record routed if needed.
	* Return Value: RV_ERROR_OUTOFRESOURCES - Request failed due to resource problem.
	*               RV_ERROR_UNKNOWN - Failed to send.
	*               RV_OK - Message was sent successfully.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:   pCallLeg - Pointer to the call leg the user wishes to modify.
	*          strMethod - A String with the request method.
	*          sessionExpires - session time that will attach to this call.
	*          minSE - minimum session expires time of this call
	*          eRefresher - the refresher preference for this call
	* Output:  hTransc - The handle to the newly created transaction
	*                    if a transaction was supplied, this transaction will be used,
	*                    and a new transaction will not be created
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegTranscSessionTimerGeneralRefresh (
		IN  RvSipCallLegHandle                             hCallLeg,
		IN  RvChar                                        *strMethod,
		IN  RvInt32                                       sessionExpires,
		IN  RvInt32                                       minSE,
		IN  RvSipCallLegSessionTimerRefresherPreference    eRefresher,
		INOUT RvSipTranscHandle                              *hTransc);

	/***************************************************************************
	* RvSipCallLegSessionTimerSetPreferenceParams
	* ------------------------------------------------------------------------
	* General:Sets the preference Session Timer parameters associated with this call.
	*         These parameters may not be equal to the Session timer parameters
	*         of the call in the end of the negotiation.(after OK has been sent or
	*         received).
	*
	* Return Value: RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg   - handle to the call-leg.
	*          sessionExpires - session time that will attach to this call.
	*          minSE - minimum session expires time of this call
	*          eRefresher - the refresher preference for this call
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegSessionTimerSetPreferenceParams(
		IN  RvSipCallLegHandle                             hCallLeg,
		IN  RvInt32                                       sessionExpires,
		IN  RvInt32                                       minSE,
		IN  RvSipCallLegSessionTimerRefresherPreference    eRefresher);
	/***************************************************************************
	* RvSipCallLegTranscSessionTimerSetPreferenceParams
	* ------------------------------------------------------------------------
	* General:Sets the preference Session Timer parameters associated with this
	*         transaction.These parameters may not be equal to the Session timer
	*         parameters of the call in the end of the negotiation.
	*         (after OK has been sent or received).
	*
	* Return Value: RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg   - handle to the call-leg.
	*          hTransc  - Handle to the transaction the request belongs to.
	*          sessionExpires - session time that will attach to this call.
	*          minSE - minimum session expires time of this call
	*          eRefresher - the refresher preference for this call
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegTranscSessionTimerSetPreferenceParams (
		IN  RvSipCallLegHandle                             hCallLeg,
		IN  RvSipTranscHandle                              hTransc,
		IN  RvInt32                                       sessionExpires,
		IN  RvInt32                                       minSE,
		IN  RvSipCallLegSessionTimerRefresherPreference    eRefresher);
	/***************************************************************************
	* RvSipCallLegSessionTimerGetNegotiationParams
	* ------------------------------------------------------------------------
	* General:Gets the negotiation Session Timer parameters associated with this call.
	*         These parameters may not be equal to the Session timer parameters
	*         of the call in the end of the negotiation.(after OK has been sent or
	*         received).
	*
	* Return Value: RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg   - handle to the call-leg.
	* OutPut:  sessionExpires - session time that will attach to this call.
	*          minSE - minimum session expires time of this call
	*          eRefresherType - the refresher type for this call
	*          eRefresherPref  - the refresher request for this call
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegSessionTimerGetNegotiationParams(
		IN  RvSipCallLegHandle                             hCallLeg,
		OUT  RvInt32                                      *sessionExpires,
		OUT  RvInt32                                      *minSE,
		OUT  RvSipSessionExpiresRefresherType              *eRefresherType,
		OUT RvSipCallLegSessionTimerRefresherPreference    *eRefresherPref);
	/***************************************************************************
	* RvSipCallLegTranscSessionTimerGetNegotiationParams
	* ------------------------------------------------------------------------
	* General:Gets the negotiation Session Timer parameters associated with this
	*         transaction.These parameters may not be equal to the Session timer
	*         parameters of the call in the end of the negotiation.
	*         (after OK has been sent or received).
	*
	* Return Value: RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg   - handle to the call-leg.
	*          hTransc  - Handle to the transaction the request belongs to.
	* OutPut:  sessionExpires - session time that will attach to this call.
	*          minSE - minimum session expires time of this call
	*          eRefresherType - the refresher type for this call
	*          eRefresherPref  - the refresher request for this call
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegTranscSessionTimerGetNegotiationParams(
		IN  RvSipCallLegHandle                             hCallLeg,
		IN  RvSipTranscHandle                              hTransc,
		OUT  RvInt32                                      *sessionExpires,
		OUT  RvInt32                                      *minSE,
		OUT  RvSipSessionExpiresRefresherType              *eRefresherType,
		OUT RvSipCallLegSessionTimerRefresherPreference    *eRefresherPref);

	/***************************************************************************
	* RvSipCallLegSessionTimerGetAlertTime
	* ------------------------------------------------------------------------
	* General: Return the alert time (the time in which refresh will be send
	*          before the session ends).
	*
	* Return Value: RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg   - handle to the call-leg.
	* Output:  alertTime  - the time in which refresh will be send
	*                       before the session ends.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegSessionTimerGetAlertTime (
		IN  RvSipCallLegHandle   hCallLeg,
		OUT RvInt32             *alertTime);

	/***************************************************************************
	* RvSipCallLegSessionTimerSetAlertTime
	* ------------------------------------------------------------------------
	* General: This function enables the application to modify the time in
	*          in which refresh will be send before the session ends.
	*
	* Return Value: RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg   - handle to the call-leg.
	* Output:  alertTime  - the time in which refresh will be send
	*                       before the session ends.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegSessionTimerSetAlertTime (
		IN  RvSipCallLegHandle   hCallLeg,
		IN  RvInt32             alertTime);

	/***************************************************************************
	* RvSipCallLegSessionTimerGetRefresherType
	* ------------------------------------------------------------------------
	* General: Returns the refresher type of this call.
	*          The value of refresher type can be different from refresher
	*          preference (which is the application request).
	*
	* Return Value: RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg   - handle to the call-leg.
	* Output:  eRefresher  - the refresher request for this call
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegSessionTimerGetRefresherType (
		IN  RvSipCallLegHandle               hCallLeg,
		OUT RvSipSessionExpiresRefresherType *eRefresher);
	/***************************************************************************
	* RvSipCallLegSessionTimerGetMinSEValue
	* ------------------------------------------------------------------------
	* General:Returns the Min-SE value associated with this call.
	*
	* Return Value: RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg   - handle to the call-leg.
	* Output:  minSE - minimum session expires time of this call
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegSessionTimerGetMinSEValue (
		IN  RvSipCallLegHandle   hCallLeg,
		OUT RvInt32             *minSE);

	/***************************************************************************
	* RvSipCallLegSessionTimerGetSessionExpiresValue
	* ------------------------------------------------------------------------
	* General:Returns the Session-Expires value associated with this call
	*
	* Return Value: RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg   - handle to the call-leg.
	* Output:  sessionExpires - session expires time of this call
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegSessionTimerGetSessionExpiresValue (
		IN  RvSipCallLegHandle   hCallLeg,
		OUT RvInt32             *sessionExpires);




	/***************************************************************************
	* RvSipCallLegSetOutboundMsg
	* ------------------------------------------------------------------------
	* General: Copies an application constructed message into the outbound message
	*          of the call-leg. It is the application responsibility to free this
	*          message after calling the set function.
	*          It is not recommended to use this function and it is not documented.
	* Return Value: RvStatus
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - The call-leg handle.
	*             hMsg     - Handle to the message.
	***************************************************************************/
	RVAPI  RvStatus RVCALLCONV RvSipCallLegSetOutboundMsg(
		IN  RvSipCallLegHandle     hCallLeg,
		IN  RvSipMsgHandle            hMsg);



	/***************************************************************************
	* RvSipCallLegSetCompartment
	* ------------------------------------------------------------------------
	* General: Associates the Call-Leg to a SigComp Compartment.
	* Return Value: RvStatus
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg     - The call-leg handle.
	*             hCompartment - Handle to the SigComp Compartment.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegSetCompartment(
		IN RvSipCallLegHandle     hCallLeg,
		IN RvSipCompartmentHandle hCompartment);

	/***************************************************************************
	* RvSipCallLegGetCompartment
	* ------------------------------------------------------------------------
	* General: Retrieves the associated the SigComp Compartment of a Call-Leg
	* Return Value: RvStatus
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:  hCallLeg      - The call-leg handle.
	*            phCompartment - Pointer of the handle to the SigComp Compartment.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegGetCompartment(
		IN  RvSipCallLegHandle      hCallLeg,
		OUT RvSipCompartmentHandle *phCompartment);

	/***************************************************************************
	* RvSipCallLegDisableCompression
	* ------------------------------------------------------------------------
	* General: Disables the compression mechanism in a Call-Leg for outgoing
	*          requests.
	* Return Value: RvStatus
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:  hCallLeg      - The call-leg handle.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegDisableCompression(
		IN RvSipCallLegHandle hCallLeg);

	/***************************************************************************
	* RvSipCallLegIsCompartmentRequired
	* ------------------------------------------------------------------------
	* General: Checks if the call-leg has to be related to a compartment.
	*          The function is particularly useful for applications that would
	*          like to manage the stack Compartments manually. For instance,
	*          if you wish to relate an incoming CallLeg object, which handles
	*          SigComp messages to a specific Compartment, you can use this 
	*          function in your implementation of a callback that notifies 
	*          about newly created CallLeg object, before the stack attaches
	*          automatically this object to any Compartment.
	* Return Value: RvStatus
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg      - The call-leg handle.
	* Output:    pbRequired    - Indication if a compartment is required.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegIsCompartmentRequired(
		IN  RvSipCallLegHandle  hCallLeg,
		OUT RvBool             *pbRequired);


#endif /*#ifndef RV_SIP_PRIMITIVES*/
	/*-----------------------------------------------------------------------
	C A L L  - L E G:  D N S   A P I
	------------------------------------------------------------------------*/
	/***************************************************************************
	* RvSipCallLegDNSGiveUp
	* ------------------------------------------------------------------------
	* General: This function is for use at MSG_SEND_FAILURE state.
	*          Calling to this function, delete the sending of the message, and
	*          change state of the state machine back to previous state.
	*          You can use this function for a call-leg request or for a general
	*          request:
	*          Use this function for INVITE, BYE, RE-INVITE messages,
	*          if state was changed to MSG_SEND_FAILURE state. For those transaction,
	*          you should set the transaction handle parameter to be NULL.
	*          Use this function for a general request, if you got MSG_SEND_FAILURE
	*          status in RvSipCallLegTranscResolvedEv event. For a general request,
	*          you should supply the general transaction handle.
	* Return Value: RV_ERROR_INVALID_HANDLE -  The handle to the call-leg is invalid.
	*                 RV_ERROR_ILLEGAL_ACTION - Invalid call-leg state for this action.
	*               RV_ERROR_OUTOFRESOURCES - Request failed due to resource problem.
	*               RV_ERROR_UNKNOWN - Failed to send re-Invite.
	*               RV_OK - Invite message was sent successfully.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call leg that sent the request.
	*          hTransc  - Handle to the transaction, in case of general request.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegDNSGiveUp (
		IN  RvSipCallLegHandle   hCallLeg,
		IN  RvSipTranscHandle    hTransc);

	/***************************************************************************
	* RvSipCallLegDNSContinue
	* ------------------------------------------------------------------------
	* General: This function is for use at MSG_SEND_FAILURE state.
	*          Calling to this function, clone the failure transaction, with an updated
	*          dns list. (next step for user is to re-send the new transaction message
	*          to the next ip address, by using RvSipCallLegDNSReSendRequest API)
	*          You can use this function for a call-leg request or for a general
	*          request:
	*          Use this function for INVITE, BYE, RE-INVITE messages,
	*          if state was changed to MSG_SEND_FAILURE state. For those transaction,
	*          you should set the transaction handle parameter to be NULL.
	*          Use this function for a general request, if you got MSG_SEND_FAILURE
	*          status in RvSipCallLegTranscResolvedEv event. For a general request,
	*          you should supply the general transaction handle.
	* Return Value: RV_ERROR_INVALID_HANDLE -  The handle to the call-leg is invalid.
	*                 RV_ERROR_ILLEGAL_ACTION - Invalid call-leg state for this action.
	*               RV_ERROR_OUTOFRESOURCES - Request failed due to resource problem.
	*               RV_ERROR_UNKNOWN - Failed to send re-Invite.
	*               RV_OK - Invite message was sent successfully.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call leg that sent the request.
	*          hTransc  - Handle to the transaction, in case of general request.
	* Output:  phClonedTransc - Handle to the cloned transAction - in case of general
	*                      transaction only.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegDNSContinue (
		IN  RvSipCallLegHandle   hCallLeg,
		IN  RvSipTranscHandle    hTransc,
		OUT RvSipTranscHandle*   phClonedTransc);

	/***************************************************************************
	* RvSipCallLegDNSReSendRequest
	* ------------------------------------------------------------------------
	* General: This function is for use at MSG_SEND_FAILURE state.
	*          This function re-send the failure request.
	*          You should call this function after you have created the new
	*          transaction with RvSipCallLegDNSContinue, and after you set all
	*          needed parameters in the message.
	*          You can use this function for a call-leg request or for a general
	*          request:
	*          Use this function for INVITE, BYE, RE-INVITE messages,
	*          if state was changed to MSG_SEND_FAILURE state. For those transaction,
	*          you should set the transaction handle parameter to be NULL.
	*          Use this function for a general request, if you got MSG_SEND_FAILURE
	*          status in RvSipCallLegTranscResolvedEv event. For a general request,
	*          you should supply the general transaction handle.
	* Return Value: RV_ERROR_INVALID_HANDLE -  The handle to the call-leg is invalid.
	*                 RV_ERROR_ILLEGAL_ACTION - Invalid call-leg state for this action.
	*               RV_ERROR_OUTOFRESOURCES - Request failed due to resource problem.
	*               RV_ERROR_UNKNOWN - Failed to send re-Invite.
	*               RV_OK - Invite message was sent successfully.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call leg that sent the request.
	*          hTransc  - Handle to the transaction, in case of general request.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegDNSReSendRequest (
		IN  RvSipCallLegHandle   hCallLeg,
		IN  RvSipTranscHandle    hTransc);

	/***************************************************************************
	* RvSipCallLegDNSGetList
	* ------------------------------------------------------------------------
	* General: retrieves DNS list object from the transaction object.
	*          You can use this function for a call-leg request or for a general
	*          request:
	*          Use this function for INVITE, BYE, RE-INVITE messages,
	*          if state was changed to MSG_SEND_FAILURE state. For those transaction,
	*          you should set the transaction handle parameter to be NULL.
	*          Use this function for a general request, if you got MSG_SEND_FAILURE
	*          status in RvSipCallLegTranscResolvedEv event. For a general request,
	*          you should supply the general transaction handle.
	* Return Value: RV_OK or RV_ERROR_BADPARAM
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call leg that sent the request.
	*          hTransc  - Handle to the transaction, in case of general request.
	* Output   phDnsList - DNS list handle
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegDNSGetList(
		IN  RvSipCallLegHandle           hCallLeg,
		IN  RvSipTranscHandle            hTransc,
		OUT RvSipTransportDNSListHandle *phDnsList);

	/*--------------------------------------------------------------------------------
	C A L L  - L E G:  L O C A L   A N D   R E M O T E   A D D R E S S   A P I
	---------------------------------------------------------------------------------*/

	/***************************************************************************
	* RvSipCallLegSetLocalAddress
	* ------------------------------------------------------------------------
	* General: Set the local address from which the call-leg will use to send outgoing
	*          requests. 
	*          The SIP stack can be configured to listen to many local addresses.
	*          each local address has a transport type (TCP/UDP/TLS) and address type
	*          (IPv4/IPv6).
	*          When the SIP Stack sends an outgoing request, the local address (from where
	*          the request is sent) is chosen  according to the charecteristics of the 
	*          remote address. Both the local and the remote addresses must have the
	*          same characteristics (transport type and address type).
	*          If several configured local addresses match the remote address chracteristics
	*          the first configured address is taken.
	*          You can use this function to force the call-leg to choose a specific local
	*          address for a specific transport and address type.
	*
	*          If the given ip address is 0.0.0.0 a default host is chosen
	*          according to the given port. To choose default ip and port use
	*          port 0.
	*          If localAddress is NULL or localAddress is empty, or eTransportType is
	*          RVSIP_TRANSPORT_UNDEFINED or eAddressType is RVSIP_TRANSPORT_ADDRESS_TYPE_UNDEFINED
	*          then the local addresses of the CallLeg will be the first address from
	*          each type from the configuration.
	*          You can use this function when the stack is listening to more then
	*          one IP address.
	*          strings that are used for the local address must match exactly to one of the
	*          strings that was inserted in the configuration struct in the initialization of the
	*          sip stack.
	* Return Value: RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call-leg
	*            eTransportType - The transport type(UDP, TCP, SCTP, TLS).
	*            eAddressType - The address type(ip or ip6).
	*            localAddress - The local address to be set to this call-leg.
	*            localPort - The local port to be set to this call-leg.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegSetLocalAddress(
		IN  RvSipCallLegHandle        hCallLeg,
		IN  RvSipTransport            eTransportType,
		IN  RvSipTransportAddressType eAddressType,
		IN  RvChar                   *localAddress,
		IN  RvUint16                 localPort);

	/***************************************************************************
	* RvSipCallLegGetLocalAddress
	* ------------------------------------------------------------------------
	* General: Get the local address the call-leg will use to send outgoing
	*          requests. This is the address the user set using the
	*          RvSipCallLegSetLocalAddress function. If no address was set the
	*          function will return the default UDP address.
	*          The user can use the transport type and the address type to indicate
	*          which kind of local address he wishes to get.
	* Return Value: RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call-leg
	*          eTransportType - The transport type (UDP, TCP, SCTP, TLS).
	*          eAddressType - The address type (ip4 or ip6).
	* Output:    localAddress - The local address this call-leg is using.
	*          localPort - The local port this call-leg is using.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegGetLocalAddress(
		IN  RvSipCallLegHandle        hCallLeg,
		IN  RvSipTransport            eTransportType,
		IN  RvSipTransportAddressType eAddressType,
		OUT  RvChar                  *localAddress,
		OUT  RvUint16                *localPort);

	/***************************************************************************
	* RvSipCallLegGetTranscCurrentLocalAddress
	* ------------------------------------------------------------------------
	* General: Gets the local address that is used by a specific call-leg
	*          transaction. You can supply a specific transaction handle or use
	*          NULL in order to get the address of the active transaction (INVITE
	*          transaction). In this version this function can be called
	*          only in the offering state to get the local address of an incoming INVITE
	*          transaction.
	* Return Value: RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg - Handle to the call-leg.
	*          hTransc - Handle to a specific call-leg transaction or NULL to
	*                    indicate active transaction.
	* Output:    eTransporType - The transport type(UDP, TCP, SCTP, TLS).
	*          eAddressType  - The address type(IP4 or IP6).
	*          localAddress - The local address this transaction is using(must be longer than 48 bytes).
	*          localPort - The local port this transaction is using.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegGetTranscCurrentLocalAddress(
		IN  RvSipCallLegHandle        hCallLeg,
		IN  RvSipTranscHandle         hTransc,
		OUT RvSipTransport            *eTransportType,
		OUT RvSipTransportAddressType *eAddressType,
		OUT RvChar                   *localAddress,
		OUT RvUint16                 *localPort);

	/***************************************************************************
	* RvSipCallLegSetOutboundDetails
	* ------------------------------------------------------------------------
	* General: Sets all outbound proxy details to the Call-Leg object. 
	*          All detailes are supplied in the RvSipTransportOutboundProxyCfg
	*          structure that includes parameter such as IP address or host name
	*          transport, port and compression type.
	*          Request sent by this object will use the outbound detail specifications
	*          as a remote address. The Request-URI will be ignored.
	*          If the object has a Route Set, the outbound details will be ignored.
	*
	*          NOTE: If you specify both IP address and a host name in the
	*                Configuration structure, either of them will be set BUT
	*                the IP address is preferably used.
	*                If you do not specify port or transport, both will be determined
	*                according to the DNS procedures specified in RFC 3263
	* Return Value: RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg       - Handle to the call-leg.
	*            pOutboundCfg   - Pointer to the outbound proxy configuration
	*                             structure with all relevant details.
	*            sizeOfCfg      - The size of the outbound proxy configuration structure.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegSetOutboundDetails(
		IN  RvSipCallLegHandle              hCallLeg,
		IN  RvSipTransportOutboundProxyCfg *pOutboundCfg,
		IN  RvInt32                         sizeOfCfg);

	/***************************************************************************
	* RvSipCallLegGetOutboundDetails
	* ------------------------------------------------------------------------
	* General: Gets all outbound proxy details that the Call-Leg object uses. 
	*          The details are placed in the RvSipTransportOutboundProxyCfg
	*          structure that includes parameter such as IP address or host name
	*          transport, port and compression type.
	*          If the outbound details were not set to the specific 
	*          Call-Leg object but outbound proxy was defined to the stack 
	*          on initialization, these parameters will be returned.
	*          If the Call-Leg is not using an outbound address NULL/UNDEFINED
	*          values are returned.
	*          NOTE: You must supply a valid consecutive buffer in the 
	*                RvSipTransportOutboundProxyCfg structure to get the
	*                outbound strings (host name and ip address).
	* Return Value: RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:   hCallLeg       - Handle to the call-leg.
	*          sizeOfCfg      - The size of the configuration structure.
	* Output:  pOutboundCfg   - Pointer to outbound proxy configuration
	*                           structure.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegGetOutboundDetails(
		IN  RvSipCallLegHandle              hCallLeg,
		IN  RvInt32                         sizeOfCfg,
		OUT RvSipTransportOutboundProxyCfg *pOutboundCfg);

	/***************************************************************************
	* RvSipCallLegSetOutboundAddress
	* ------------------------------------------------------------------------
	* General: Sets the outbound address of the call-leg. All the requests sent
	*          by this call-leg will be sent directly to the call-leg
	*          outbound address (unless the call-leg is using a
	*          Record-Route path).
	* Return Value: RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg          - Handle to the call-leg
	*            strOutboundAddrIp   - The outbound ip to be set to this
	*                              call-leg.
	*          outboundAddressPort - The outbound port to be set to this
	*                              call-leg.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegSetOutboundAddress(
		IN  RvSipCallLegHandle     hCallLeg,
		IN  RvChar               *strOutboundAddrIp,
		IN  RvUint16              outboundAddressPort);

	/***************************************************************************
	* RvSipCallLegGetOutboundHostName
	* ------------------------------------------------------------------------
	* General: Gets the host name of the outbound proxy that the call-leg is using.
	* If an outbound host was set to the call-leg this host will be returned. If no
	* outbound host was set to the call-leg but an outbound host was configured
	* for the SIP Stack, the configured host is returned. If the call-leg is not
	* using an outbound host, '\0' is returned.
	* Note: You must supply a valid consecutive buffer to get the strOutboundHost host
	*       name.
	* Return Value: RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:
	*          hCallLeg      - Handle to the call-leg
	* Output:
	*            strOutboundHost   -  A buffer with the outbound host name
	*          pOutboundPort - The outbound host port.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegGetOutboundHostName(
		IN   RvSipCallLegHandle    hCallLeg,
		OUT  RvChar              *strOutboundHost,
		OUT  RvUint16            *pOutboundPort);


	/***************************************************************************
	* RvSipCallLegSetOutboundHostName
	* ------------------------------------------------------------------------
	* General: Sets the outbound proxy host name of the call-leg object.
	* The outbound host name will be resolved each time a request is sent to this host.
	* the request will be sent to the resolved IP address.
	* Note: To set a specific IP address, use RvSipCallLegSetOutboundAddress().
	* If you configure a call-leg with both an outbound IP address and an
	* outbound host name, the call-leg will ignore the outbound host name and
	* will use the outbound IP address.
	* When using an outbound host all outgoing requests be sent directly to the call-leg
	* outbound proxy host (unless the call-leg is using a Record-Route path).
	* Return Value: RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg           - Handle to the call-leg
	*            strOutboundHostName    - The outbound proxy host to be set to this
	*                               call-leg.
	*          outboundPort  - The outbound proxy port to be set to this
	*                               call-leg. If you set the port to zero it
	*                               will be determined using the DNS procedure.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegSetOutboundHostName(
		IN  RvSipCallLegHandle     hCallLeg,
		IN  RvChar                *strOutboundHostName,
		IN  RvUint16              outboundPort);

	/***************************************************************************
	* RvSipCallLegSetOutboundTransport
	* ------------------------------------------------------------------------
	* General: Sets the outbound transport of the call-leg outbound proxy.
	* This transport will be used for the outbound proxy that you set using the
	* RvSipCallLegSetOutboundAddress() function or the
	* RvSipCallLegSetOutboundHostName() function. If you do not set an
	* outbound transport, the transport will be determined using the DNS procedures.
	* Return Value: RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hCallLeg           - Handle to the call-leg
	*          eOutboundTransport - The outbound transport to be set
	*                               to this call-leg.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegSetOutboundTransport(
		IN  RvSipCallLegHandle     hCallLeg,
		IN  RvSipTransport         eOutboundTransport);

	/***************************************************************************
	* RvSipCallLegGetOutboundAddress
	* ------------------------------------------------------------------------
	* General: Gets the address of outbound proxy the call-leg is using. If an
	*          outbound address was set to the call-leg this address will be
	*          returned. If no outbound address was set to the call-leg
	*          but an outbound proxy was configured for the stack, the configured
	*          address is returned. '\0' is returned if the call-leg is not using
	*          an outbound proxy.
	*          NOTE: you must supply a valid consecutive buffer of size 48 to
	*          get the outboundProxyIp.
	* Return Value: RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:
	*          hCallLeg      - Handle to the call-leg
	* Output:
	*            outboundProxyIp   -  A buffer with the outbound proxy IP the call-leg.
	*                               is using(must be longer than 48).
	*          pOutboundProxyPort - The outbound proxy port the call-leg is using.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegGetOutboundAddress(
		IN   RvSipCallLegHandle    hCallLeg,
		OUT  RvChar              *outboundProxyIp,
		OUT  RvUint16            *pOutboundProxyPort);

	/***************************************************************************
	* RvSipCallLegGetOutboundTransport
	* ------------------------------------------------------------------------
	* General: Gets the transport of the outbound proxy that the call-leg is using.
	* If an outbound transport was set to the call-leg, this transport will be
	* returned. If no outbound transport was set to the call-leg but an outbound
	* proxy was configured for the SIP Stack, the configured transport is returned.
	* RVSIP_TRANSPORT_UNDEFINED is returned if the call-leg is not
	* using an outbound proxy.
	* Return Value: RvStatus.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:  hCallLeg           - Handle to the call-leg
	* Output: eOutboundTransport - The outbound proxy transport the call-leg is using.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegGetOutboundTransport(
		IN   RvSipCallLegHandle    hCallLeg,
		OUT  RvSipTransport       *eOutboundProxyTransport);

	/*-----------------------------------------------------------------------
	C A L L  - L E G:  F O R K I N G   A P I
	------------------------------------------------------------------------*/
	/***************************************************************************
	* RvSipCallLegGetOriginalCallLeg 
	* ------------------------------------------------------------------------
	* General: An initial INVITE request, might be forked by a proxy. as a result,
	*          several 1xx and 2xx responses may be received from several UASs.
	*          The first incoming response will be mapped to the original call-leg,
	*          that sent the INVITE request. every other incoming response (with a 
	*          different to-tag parameter), creates a new 'forked call-leg'.
	*
	*          This function returns the original call-leg of a given call-leg:
	*          If the given call-leg is a 'forked call-leg' the function will  
	*          return the original call-leg handle.
	*          If the given call-leg is an 'original call-leg' the function will 
	*          return the same call-leg handle.
	* Return Value: RvStatus
	* ------------------------------------------------------------------------
	* Arguments:
	* Input: 	hCallLeg      - Handle to a call-leg.
	* Output: 	phOrigCallLeg - Handle to the original call-leg. 
	***************************************************************************/
	RVAPI  RvStatus RVCALLCONV RvSipCallLegGetOriginalCallLeg(
		IN RvSipCallLegHandle   hCallLeg,
		OUT RvSipCallLegHandle  *phOrigCallLeg);

	/***************************************************************************
	* RvSipCallLegSetForkingEnabledFlag 
	* ------------------------------------------------------------------------
	* General: This function sets the 'forking-enabled' flag of the call-leg.
	*          This flag defines the call-leg behavior on receiving a 'forked'
	*          1xx/2xx response. 
	*          If this flag is set to TRUE, then a new call-leg is created for 
	*          every 1xx/2xx response with new to-tag.
	*          If this flag is set to FALSE, then the response will be mapped
	*          to the original call-leg. every 1xx response will update the
	*          call-leg to-tag parameter.
	*          
	* Return Value: RvStatus
	* ------------------------------------------------------------------------
	* Arguments:
	* Input: 	hCallLeg - Handle to the call-leg.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegSetForkingEnabledFlag (
		IN RvSipCallLegHandle   hCallLeg,
		IN RvBool               bForkingEnabled);

	/***************************************************************************
	* RvSipCallLegGetForkingEnabledFlag 
	* ------------------------------------------------------------------------
	* General: This function returns the 'forking-enabled' flag of the call-leg.
	*          This flag defines the call-leg behavior on receiving a 'forked'
	*          1xx/2xx response. 
	*          If this flag is set to TRUE, then a new call-leg is created for 
	*          every 1xx/2xx response with new to-tag.
	*          If this flag is set to FALSE, then the response will be mapped
	*          to the original call-leg. every 1xx response will update the
	*          call-leg to-tag parameter.
	*          
	* Return Value: RvStatus
	* ------------------------------------------------------------------------
	* Arguments:
	* Input: 	hCallLeg - Handle to the call-leg.
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegGetForkingEnabledFlag(
		IN RvSipCallLegHandle   hCallLeg,
		IN RvBool               *pbForkingEnabled);


	/***************************************************************************
	* RvSipCallLegSetForkedAckTimerTimeout 
	* ------------------------------------------------------------------------
	* General: An initial INVITE request, might be forked by a proxy. as a result,
	*          several 1xx and 2xx responses may be received from several UASs.
	*          The first incoming response will be mapped to the original call-leg,
	*          that sent the INVITE request. every other incoming response (with a 
	*          different to-tag parameter), creates a new 'forked call-leg'.
	*
	*          A forked call-leg, that received a 2xx response, sends ACK request.
	*          The forked call-leg holds a special transmitter, for sending this
	*          ACK request, and a timer ('forked-ack-timer') that defines when this
	*          transmitter object will be destructed.
	*          This function enables application to define the timeout value for  
	*          this timer, per a specific call-leg.
	*          (usually the timer timeout value is taken from stack configuration). 
	*          
	* Return Value: RvStatus
	* ------------------------------------------------------------------------
	* Arguments:
	* Input: 	hCallLeg - Handle to the call-leg.
	*          timeout  - The timeout value for the Ack timer. (if 0, the timer will
	*                     not be set).
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegSetForkedAckTimerTimeout (
		IN RvSipCallLegHandle   hCallLeg,
		IN RvInt32              timeout);

	/***************************************************************************
	* RvSipCallLegSetForked1xxTimerTimeout 
	* ------------------------------------------------------------------------
	* General: An initial INVITE request, might be forked by a proxy. as a result,
	*          several 1xx and 2xx responses may be received from several UASs.
	*          The first incoming response will be mapped to the original call-leg,
	*          that sent the INVITE request. every other incoming response (with a 
	*          different to-tag parameter), creates a new 'forked call-leg'.
	*
	*          A forked call-leg, that received a 1xx response, sets a timer 
	*          ('forked-1xx-timer'). This timer will be released when this 
	*          call-leg receive a 2xx response.
	*          If it expires before 2xx was received, the call-leg is terminated.
	*          (usually the timer timeout value is taken from stack configuration). 
	*          
	* Return Value: RvStatus
	* ------------------------------------------------------------------------
	* Arguments:
	* Input: 	hCallLeg - Handle to the call-leg.
	*          timeout  - The timeout value for the 1xx timer. (if 0, the timer will
	*                     not be set).
	***************************************************************************/
	RVAPI RvStatus RVCALLCONV RvSipCallLegSetForked1xxTimerTimeout (
		IN RvSipCallLegHandle   hCallLeg,
		IN RvInt32              timeout);

#ifdef __cplusplus
}
#endif


#endif /* END OF: #ifndef RV_SIP_CALL_LEG_H */

