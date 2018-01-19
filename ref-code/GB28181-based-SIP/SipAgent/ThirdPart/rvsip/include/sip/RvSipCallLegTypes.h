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
 *                              <RvSipCallLegTypes.h>
 *
 * The RvSipCallLegTypes.h file contains all type definitions and call-back functions
 * type definitions for the Call-leg module.
 *
 * includes:
 * 1.Handle Type definitions
 * 2.Call-Leg Type definitions
 * 3.Call-Leg callback functions
 *
 *
 *    Author                         Date
 *    ------                        ------
 *    Sarit Mekler                  Nov 2000
 *********************************************************************************/


#ifndef RV_SIP_CALL_LEG_TYPES_H
#define RV_SIP_CALL_LEG_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                           */
/*-----------------------------------------------------------------------*/
#include "RV_SIP_DEF.h"
#ifndef RV_SIP_PRIMITIVES
#include "RvSipMsg.h"
#include "RvSipTransactionTypes.h"

/*-----------------------------------------------------------------------*/
/*                         MACRO DEFINITIONS                             */
/*-----------------------------------------------------------------------*/
#define RVSIP_CALL_LEG_MIN_MINSE 90

/*-----------------------------------------------------------------------*/
/*                     COMMON TYPE DEFINITIONS                           */
/*-----------------------------------------------------------------------*/

/*
 * RvSipCallLegMgrHandle
 * ---------------------------------------------------------------------------
 * Declaration of handle to a Call Leg Manager instance. The manager object
 * manages all the module call-legs and its handle is needed in all manager
 * related API such as creation of new call-legs.
 */
RV_DECLARE_HANDLE(RvSipCallLegMgrHandle);


/*
 * RvSipCallLegHandle
 * ---------------------------------------------------------------------------
 * Declaration of a Call-Leg handle. Call-leg is needed in all Call-leg API
 * function and is used to reference the correct call-leg object.
 */
RV_DECLARE_HANDLE(RvSipCallLegHandle);


/*
 * RvSipAppCallLegHandle
 * ---------------------------------------------------------------------------
 * Declaration  of application handle to a Call Leg. This handle is used by the
 * application in order to associate sip stack call-leg objects with application
 * call-leg object. The application gives the application handle when
 * a new call-leg is created. The sip stack will give this handle back to the
 * application in every callback function.
 */

RV_DECLARE_HANDLE(RvSipAppCallLegHandle);




/*-----------------------------------------------------------------------*/
/*                    CALL_LEG TYPE DEFINITIONS                           */
/*-----------------------------------------------------------------------*/


/* RvSipCallLegState
 * ----------------------------------------------------------------------
 * RvSipCallLegState represents a state in a session. The state changes
 * are reported using the RvSipCallLegStateChangedEv call back function
 * together with a state change reason that may indicate to the application
 * how the new state was reached
 *
 * RVSIP_CALL_LEG_STATE_UNDEFINED: No state for this call leg.
 * RVSIP_CALL_LEG_STATE_IDLE:      Initial state for a newly created call.
 *                                 The call will stay in this state until
 *                                 the connect() method will be called.
 * RVSIP_CALL_LEG_STATE_INVITING:  Invite message was sent to the destination.
 * RVSIP_CALL_LEG_STATE_PROCEEDING:A 1xx class response was received in the
 *                                 inviting state.
 * RVSIP_CALL_LEG_STATE_REDIRECTED:A 3xx class response was received in the
 *                                 inviting state. The application may confirm
 *                                 the redirection by calling connect().
 * RVSIP_CALL_LEG_STATE_OFFERING:  An initial INVITE was received. The
 *                                 application can decide to accept or reject
 *                                 the call.
 * RVSIP_CALL_LEG_STATE_ACCEPTED:  The call (in Offering state) was accepted.
 *                                 It will move to connected state after
 *                                 receiving the ACK.
 * RVSIP_CALL_LEG_STATE_UNAUTHENTICATED: A call-leg sending a request to a server
 *                                 or proxy may receive a 401 or 407
 *                                 response. In this case, the call-leg assumes
 *                                 the Unauthenticated state. At this
 *                                 point, you may re-send your request with
 *                                 authentication information by calling
 *                                 the Authenticate() function. You can also
 *                                 disconnect the call using the
 *                                 Disconnect() function.
 * RVSIP_CALL_LEG_STATE_CONNECTED: The call-leg is connected. The session has
 *                                 been successfully set-up.The state is
 *                                 reached either when a 200 response is
 *                                 received on an initial INVITE or when an
 *                                 ACK is received on a 200 response.
 * RVSIP_CALL_LEG_STATE_DISCONNECTING: A BYE request was sent. When receiving
 *                                     final response the call-leg will change
 *                                     state to disconnected.
 * RVSIP_CALL_LEG_STATE_DISCONNECTED: A Bye request or a final response to a previously
 *                                    sent BYE was received from the remote party.
 *                                    This is also the state indicating the rejection of
 *                                    an Invite request or the disconnection of a call
 *                                    before it reached the connected state.                                    This state notifies the application that the
 *                                    This is the final state where the application can
 *                                    still reference the call-leg using the call-leg
 *                                      API functions.
 * RVSIP_CALL_LEG_STATE_TERMINATED:   The final call-leg state. The call-leg resources
 *                                    where freed and the application must no longer
 *                                    reference this call-leg object.
 * RVSIP_CALL_LEG_STATE_REMOTE_ACCEPTED: The call-leg received 2xx response.
 *                                    This state will be reached only if the
 *                                    stack is configured to work in a
 *                                    manualAckOn2xx mode. The application must
 *                                    manually call the RvSipCallLegAck() function
 *                                    is order to send the ACK request to the remote
 *                                    party.
 * RVSIP_CALL_LEG_STATE_CANCELLED: When a call-leg has been canceled, it will assume this state. if manual
 *                                 response flag is off 487 will be sent automaticly, else call call
 *                                 reject with 487 to complete the transaction
 * RVSIP_CALL_LEG_STATE_CANCELLING: A CANCEL request was sent. The call-leg is
 *                                  waiting for an 487 response.
 * RVSIP_CALL_LEG_STATE_PROCEEDING_TIMEOUT: This state is relevant only if the configuration flag of
 * enableInviteProceedingTimeoutState==true. If so, upon proceeding timeout the call-leg will assume this
 * state and the application will have to decide whether to terminate the call or cancel the sent invite.
 */

typedef enum
{
    RVSIP_CALL_LEG_STATE_UNDEFINED = -1,
    RVSIP_CALL_LEG_STATE_IDLE,
    RVSIP_CALL_LEG_STATE_INVITING,
    RVSIP_CALL_LEG_STATE_REDIRECTED,
    RVSIP_CALL_LEG_STATE_UNAUTHENTICATED,
    RVSIP_CALL_LEG_STATE_OFFERING,
    RVSIP_CALL_LEG_STATE_ACCEPTED,
    RVSIP_CALL_LEG_STATE_CONNECTED,
    RVSIP_CALL_LEG_STATE_DISCONNECTED,
    RVSIP_CALL_LEG_STATE_DISCONNECTING,
    RVSIP_CALL_LEG_STATE_TERMINATED,
    RVSIP_CALL_LEG_STATE_REMOTE_ACCEPTED,
    RVSIP_CALL_LEG_STATE_CANCELLED,
    RVSIP_CALL_LEG_STATE_CANCELLING,
    RVSIP_CALL_LEG_STATE_PROCEEDING,
    RVSIP_CALL_LEG_STATE_PROCEEDING_TIMEOUT,
    RVSIP_CALL_LEG_STATE_MSG_SEND_FAILURE

} RvSipCallLegState;

/* RvSipCallLegModifyState
 *-------------------------------------------------------------------------
 * RvSipCallLegModifyState represents a state of a re-Invite process in
 * a connected session. The state changes
 * are reported using the RvSipCallLegModifyStateChangedEv call back function
 * together with a state change reason that may indicate to the application
 * how the new state was reached *
 * RVSIP_CALL_LEG_MODIFY_STATE_UNDEFINED - The call cannot send or receive a
 *                                         re-Invite. Usually this state indicates
 *                                         that the call is not in the connected state.
 * RVSIP_CALL_LEG_MODIFY_STATE_IDLE      - The call is connected, and there is no active
 *                                         Re-Invite. This is also the state when a response
 *                                         is received on a previously sent re-Invite. Now the
 *                                         call leg is ready to initiate a second re-Invite if
 *                                         the user wishes to. (The ACK is sent automatically).
 * RVSIP_CALL_LEG_MODIFY_STATE_REINVITE_RCVD  - Re-invite request was received.
 * RVSIP_CALL_LEG_MODIFY_STATE_REINVITE_RESPONSE_SENT - a response was sent for Re-invite.
 * RVSIP_CALL_LEG_MODIFY_STATE_REINVITE_SENT - Re-invite was sent.
 * RVSIP_CALL_LEG_MODIFY_STATE_REINVITE_REMOTE_ACCEPTED - The remote party accepted the re-Invite.
 *                                         This state will be reported only if the autoAckOn2xx
 *                                         configuration parameter is set to RV_TRUE. In this case
 *                                         the ACK will not be sent automatically on 2xx to re-Invite
 *                                         and the application must initiate the ACK by itself.
 * RVSIP_CALL_LEG_MODIFY_STATE_REINVITE_RESPONSE_RCVD - A final response was received on an outgoing
 *                                          re-Invite.
 * RVSIP_CALL_LEG_MODIFY_STATE_REINVITE_CANCELLING - cancel was sent on the re-Invite
 * RVSIP_CALL_LEG_MODIFY_STATE_REINVITE_PROCEEDING - 1xx response was received for a previously sent
 *                                                   re-Invite.
 * RVSIP_CALL_LEG_MODIFY_STATE_REINVITE_CANCELLED - a re-invite request has been cancelled by the remote side.
 * RVSIP_CALL_LEG_MODIFY_STATE_REINVITE_PROCEEDING_TIMEOUT - This state is relevant only if the configuration flag of
 * enableInviteProceedingTimeoutState==true. If so, upon proceeding timeout the call-leg will assume this
 * modify state and the application will have to decide whether to terminate the call or cancel the sent invite.
 *
 */
typedef enum
{
    RVSIP_CALL_LEG_MODIFY_STATE_UNDEFINED = -1,
    RVSIP_CALL_LEG_MODIFY_STATE_IDLE,
    RVSIP_CALL_LEG_MODIFY_STATE_REINVITE_RCVD,
    RVSIP_CALL_LEG_MODIFY_STATE_REINVITE_RESPONSE_SENT,
    RVSIP_CALL_LEG_MODIFY_STATE_REINVITE_SENT,
    RVSIP_CALL_LEG_MODIFY_STATE_REINVITE_RESPONSE_RCVD,
    RVSIP_CALL_LEG_MODIFY_STATE_REINVITE_REMOTE_ACCEPTED,
    RVSIP_CALL_LEG_MODIFY_STATE_REINVITE_CANCELLING,
    RVSIP_CALL_LEG_MODIFY_STATE_REINVITE_PROCEEDING,
    RVSIP_CALL_LEG_MODIFY_STATE_REINVITE_CANCELLED,
    RVSIP_CALL_LEG_MODIFY_STATE_REINVITE_PROCEEDING_TIMEOUT,
    RVSIP_CALL_LEG_MODIFY_STATE_MSG_SEND_FAILURE

}RvSipCallLegModifyState;

/* RvSipCallLegStateChangeReason
 * ------------------------------------------------------------------
 * A call-leg object has an inner state. The state changes according
 * to the state machine defined for the call-leg. Each state change
 * is explained by one of the reasons enumerated bellow.
 *
 * RVSIP_CALL_LEG_REASON_UNDEFINED           - The reason is undefined.
 * RVSIP_CALL_LEG_REASON_LOCAL_INVITING      - The local party invited the remote party.
 * RVSIP_CALL_LEG_REASON_REMOTE_INVITING     - The remote party invited the local party.
 * RVSIP_CALL_LEG_REASON_LOCAL_REFER         - The local party sent a REFER request to the remote party.
 * RVSIP_CALL_LEG_REASON_REMOTE_REFER        - The remote party sent a REFER request to the local party.
 * RVSIP_CALL_LEG_REASON_LOCAL_REFER_NOTIFY        - The local party sent a refer-NOTIFY request to the remote party.
 * RVSIP_CALL_LEG_REASON_REMOTE_REFER_NOTIFY       - The remote party sent a refer-NOTIFY request to the local party.
 * RVSIP_CALL_LEG_REASON_REMOTE_ACCEPTED     - Remote party accepted the call
 * RVSIP_CALL_LEG_REASON_LOCAL_ACCEPTED      - Local party accepted the call
 * RVSIP_CALL_LEG_REASON_REMOTE_ACK          - The remote party sent Ack.
 * RVSIP_CALL_LEG_REASON_REDIRECTED          - 3XX was received
 * RVSIP_CALL_LEG_REASON_LOCAL_REJECT        - The local party rejected the call
 * RVSIP_CALL_LEG_REASON_REQUEST_FAILURE     - 4XX was received
 * RVSIP_CALL_LEG_REASON_SERVER_FAILURE      - 5XX was received
 * RVSIP_CALL_LEG_REASON_GLOBAL_FAILURE      - 6XX was received
 * RVSIP_CALL_LEG_REASON_LOCAL_DISCONNECTING - Local party sent BYE and is waiting for
 *                                             response.
 * RVSIP_CALL_LEG_REASON_DISCONNECTED        - The local party received a final response
 *                                             to a previously sent Bye request.
 * RVSIP_CALL_LEG_REASON_REMOTE_DISCONNECTED - The remote party sent BYE
 * RVSIP_CALL_LEG_REASON_LOCAL_FAILURE       - The local party failed. For example
 *                                             it failed to send a request.
 * RVSIP_CALL_LEG_REASON_LOCAL_TIME_OUT      - There was a time out. For example an
 *                                             expected response has not arrived.
 * RVSIP_CALL_LEG_REASON_CALL_TERMINATED     - The call-leg was terminated.
 * RVSIP_CALL_LEG_REASON_AUTH_NEEDED         - 401 or 407 response was received.
 * RVSIP_CALL_LEG_REASON_UNSUPPORTED_AUTH_PARAMS - 401 or 407 response was received
 *                                              but the authentication parameters
 *                                              are not supported.
 * RVSIP_CALL_LEG_REASON_REMOTE_PROVISIONAL_RESP -
 * The remote party sent provisional response to the INVITE or reINVITE request
 * RVSIP_CALL_LEG_REASON_REMOTE_REFER_REPLACES -
 * The remote party sent REFER request with Replaces header inside the Refer-To header.
 * RVSIP_CALL_LEG_REASON_REMOTE_INVITING_REPLACES -
 * The remote party sent INVITE request with Replaces header.
 * RVSIP_CALL_LEG_REASON_REMOTE_DISCONNECT_REQUESTED -
 * The remote party sent BYE request.
 * RVSIP_CALL_LEG_REASON_DISCONNECT_LOCAL_REJECT -
 * The local party rejected the BYE request it received.
 * RVSIP_CALL_LEG_REASON_DISCONNECT_REMOTE_REJECT -
 * The remote party rejected the BYE request it received.
 * RVSIP_CALL_LEG_REASON_DISCONNECT_LOCAL_ACCEPT -
 * The local party accepted the BYE request it received.
 * RVSIP_CALL_LEG_REASON_NETWORK_ERROR -
 * One of the reasons for moving to the msg_send_failure state. The message failed to
 * be sent due to network error.
 * RVSIP_CALL_LEG_REASON_503_RECEIVED -
 * One of the reasons for moving to the msg_send_failure state. The message received 503
 * response.
 * RVSIP_CALL_LEG_REASON_GIVE_UP_DNS -
 * The local party decided to give up sending a message, after its previous send failed
 * (DNS feature).
 * RVSIP_CALL_LEG_REASON_CONTINUE_DNS -
 * The local party decided to send a message to the next address in its transaction DNS list,
 * after its previous send failed (DNS feature).
 * RVSIP_CALL_LEG_REASON_OUT_OF_RESOURCES -
 * Out of resource problem.
 * RVSIP_CALL_LEG_REASON_FORKED_CALL_NO_FINAL_RESPONSE -
 * call-leg that was created by 1xx response on a forked request, did not get a final response.
 */
typedef enum
{
    RVSIP_CALL_LEG_REASON_UNDEFINED = -1,
    RVSIP_CALL_LEG_REASON_LOCAL_INVITING,
    RVSIP_CALL_LEG_REASON_REMOTE_INVITING,
    RVSIP_CALL_LEG_REASON_LOCAL_REFER,
    RVSIP_CALL_LEG_REASON_REMOTE_REFER,
    RVSIP_CALL_LEG_REASON_LOCAL_REFER_NOTIFY,
    RVSIP_CALL_LEG_REASON_REMOTE_REFER_NOTIFY,
    RVSIP_CALL_LEG_REASON_LOCAL_ACCEPTED,
    RVSIP_CALL_LEG_REASON_REMOTE_ACCEPTED,
    RVSIP_CALL_LEG_REASON_REMOTE_ACK,
    RVSIP_CALL_LEG_REASON_REDIRECTED,
    RVSIP_CALL_LEG_REASON_LOCAL_REJECT,
    RVSIP_CALL_LEG_REASON_REQUEST_FAILURE,
    RVSIP_CALL_LEG_REASON_SERVER_FAILURE,
    RVSIP_CALL_LEG_REASON_GLOBAL_FAILURE,
    RVSIP_CALL_LEG_REASON_LOCAL_DISCONNECTING,
    RVSIP_CALL_LEG_REASON_DISCONNECTED,
    RVSIP_CALL_LEG_REASON_REMOTE_DISCONNECTED,
    RVSIP_CALL_LEG_REASON_LOCAL_FAILURE,
    RVSIP_CALL_LEG_REASON_LOCAL_TIME_OUT,
    RVSIP_CALL_LEG_REASON_CALL_TERMINATED,
    RVSIP_CALL_LEG_REASON_AUTH_NEEDED,
    RVSIP_CALL_LEG_REASON_UNSUPPORTED_AUTH_PARAMS,
    RVSIP_CALL_LEG_REASON_LOCAL_CANCELLING,
    RVSIP_CALL_LEG_REASON_REMOTE_CANCELED,
    RVSIP_CALL_LEG_REASON_ACK_SENT,
    RVSIP_CALL_LEG_REASON_CALL_CONNECTED,
    RVSIP_CALL_LEG_REASON_REMOTE_PROVISIONAL_RESP,
    RVSIP_CALL_LEG_REASON_REMOTE_REFER_REPLACES,
    RVSIP_CALL_LEG_REASON_REMOTE_INVITING_REPLACES,
    RVSIP_CALL_LEG_REASON_REMOTE_DISCONNECT_REQUESTED,
    RVSIP_CALL_LEG_REASON_DISCONNECT_LOCAL_REJECT,
    RVSIP_CALL_LEG_REASON_DISCONNECT_REMOTE_REJECT,
    RVSIP_CALL_LEG_REASON_DISCONNECT_LOCAL_ACCEPT,
    RVSIP_CALL_LEG_REASON_NETWORK_ERROR,
    RVSIP_CALL_LEG_REASON_503_RECEIVED,
    RVSIP_CALL_LEG_REASON_GIVE_UP_DNS,
    RVSIP_CALL_LEG_REASON_CONTINUE_DNS,
    RVSIP_CALL_LEG_REASON_OUT_OF_RESOURCES,
    RVSIP_CALL_LEG_REASON_FORKED_CALL_NO_FINAL_RESPONSE
} RvSipCallLegStateChangeReason;


/* RvSipCallLegReferState
 * ----------------------------------------------------------------------
 * RvSipCallLegReferState represents a state in a refer process between two
 * SIP user agents.
 * The state changes are reported using the RvSipCallLegReferStateChangedEv
 * call back function
 *
 * RVSIP_CALL_LEG_REFER_STATE_UNDEFINED: No refer-state for this call leg.
 * RVSIP_CALL_LEG_REFER_STATE_REFER_IDLE: The initial refer-state of the call-leg.
 *                                  Indicates that the call-leg is ready to
 *                                  process an incoming or an outgoing REFER
 *                                  message (as long as the call-leg state is
 *                                  idle or connected). Calling Refer() function
 *                                  in this state will send a REFER message and
 *                                  move the call-leg to state refer-sent. The
 *                                  call-leg will return to the Idle refer state
 *                                  when a final response for the REFER request
 *                                  is received, or in case of transaction timeout.
 *                                  Receipt of REFER request in the Idle refer state will
 *                                  move the call-leg to state refer-received. Responding
 *                                  to the REFER request with a final response will
 *                                  move the call-leg state back to Idle refer state.
 * RVSIP_CALL_LEG_REFER_STATE_REFER_SENT:  REFER message was sent to the destination.
 * RVSIP_CALL_LEG_REFER_STATE_REFER_CANCELLING: REFER client transaction was canceled.
 *                                              The transaction is waiting for the servers
 *                                              final response.
 * RVSIP_CALL_LEG_REFER_STATE_REFER_UNAUTHENTICATED: A 401/407 response was received by the
 *                                             REFER transaction of the call-leg.
 *                                             To re-send the REFER request with
 *                                             authentication information
 *                                             call the Refer() function.
 * RVSIP_CALL_LEG_REFER_STATE_REFER_REDIRECTED:      A 3xx response was received by the
 *                                             REFER transaction of the call-leg. To
 *                                             redirect the REFER request call the
 *                                             Refer() function.
 * RVSIP_CALL_LEG_REFER_STATE_REFER_RCVD: REFER request was received by the call-leg.
 *                                         The application can decide whether to accept
 *                                         or reject the REFER request using ReferAccept()
 *                                         and ReferReject() functions respectively.
 *
 */

typedef enum
{
    RVSIP_CALL_LEG_REFER_STATE_REFER_UNDEFINED = -1,
    RVSIP_CALL_LEG_REFER_STATE_REFER_IDLE,

    /*Outgoing REFER*/
    RVSIP_CALL_LEG_REFER_STATE_REFER_SENT,
    RVSIP_CALL_LEG_REFER_STATE_REFER_CANCELLING,
    RVSIP_CALL_LEG_REFER_STATE_REFER_UNAUTHENTICATED,
    RVSIP_CALL_LEG_REFER_STATE_REFER_REDIRECTED,

    /*Incoming REFER*/
    RVSIP_CALL_LEG_REFER_STATE_REFER_RCVD,

    RVSIP_CALL_LEG_REFER_STATE_MSG_SEND_FAILURE

} RvSipCallLegReferState;


/* RvSipCallLegReferNotifyEvents
 * ----------------------------------------------------------------------
 * The refer-notify events indicate the events occurring in a refer-notify
 * process between two SIP user agents. The RvSipCallLegReferNotifyEv()
 * callback reports call-leg refer-notify events, specifying the reason for
 * the event occurrence and the final status of the connect attempt when relevant.
 *
 * RVSIP_CALL_LEG_REFER_NOTIFY_UNDEFINED: No refer-notify event for this call leg.
 * RVSIP_CALL_LEG_REFER_NOTIFY_READY: The connect attempt that was triggered by the
 *                                    refer message has reached a final status. The
 *                                    application can decide whether to send a NOTIFY
 *                                    request to the remote party notifying the connect
 *                                    final status, or to complete the refer process
 *                                    without sending a NOTIFY request.
 * RVSIP_CALL_LEG_REFER_NOTIFY_SENT:  NOTIFY message was sent to the destination.
 * RVSIP_CALL_LEG_REFER_NOTIFY_UNAUTHENTICATED: A 401/407 response was received by the
 *                                             NOTIFY transaction of the call-leg. To
 *                                             re-send the NOTIFY request with
 *                                             authentication information
 *                                             use the ReferNotify() function.
 * RVSIP_CALL_LEG_REFER_NOTIFY_REDIRECTED:     A 3xx response was received by the
 *                                             NOTIFY transaction of the call-leg.
 *                                             To redirect the NOTIFY request
 *                                             call ReferNotify().
 * RVSIP_CALL_LEG_REFER_NOTIFY_RESPONSE_RECVD: A final response to a NOTIFY request was
 *                                             received by the call-leg.
 * RVSIP_CALL_LEG_REFER_NOTIFY_RECVD: NOTIFY message was received by the call-leg.
 *
 */

typedef enum
{
    RVSIP_CALL_LEG_REFER_NOTIFY_UNDEFINED = -1,

    /*Outgoing REFER*/
    RVSIP_CALL_LEG_REFER_NOTIFY_READY,
    RVSIP_CALL_LEG_REFER_NOTIFY_SENT,
    RVSIP_CALL_LEG_REFER_NOTIFY_UNAUTHENTICATED,
    RVSIP_CALL_LEG_REFER_NOTIFY_REDIRECTED,
    RVSIP_CALL_LEG_REFER_NOTIFY_RESPONSE_RCVD,

    /*Incoming REFER*/
    RVSIP_CALL_LEG_REFER_NOTIFY_RCVD

} RvSipCallLegReferNotifyEvents;


/* RvSipCallLegDirection
 * ------------------------------------------------------------------
 * Indicates whether the call-leg represents an incoming or an
 * outgoing call.
 */
typedef enum
{
    RVSIP_CALL_LEG_DIRECTION_UNDEFINED = -1,
    RVSIP_CALL_LEG_DIRECTION_INCOMING,       /*incoming call-leg*/
    RVSIP_CALL_LEG_DIRECTION_OUTGOING        /*outgoing call-leg*/
}RvSipCallLegDirection;


/* RvSipCallLegTranscState
 * ------------------------------------------------------------------
 * Indicates a state of a general transaction such as INFO that
 * belongs to a call-leg.
 */
typedef enum
{
    RVSIP_CALL_LEG_TRANSC_STATE_UNDEFINED = -1,
    RVSIP_CALL_LEG_TRANSC_STATE_IDLE,
    RVSIP_CALL_LEG_TRANSC_STATE_SERVER_GEN_REQUEST_RCVD,
    RVSIP_CALL_LEG_TRANSC_STATE_SERVER_GEN_FINAL_RESPONSE_SENT,
    RVSIP_CALL_LEG_TRANSC_STATE_CLIENT_GEN_REQUEST_SENT,
    RVSIP_CALL_LEG_TRANSC_STATE_CLIENT_GEN_PROCEEDING,
    RVSIP_CALL_LEG_TRANSC_STATE_TERMINATED,
    RVSIP_CALL_LEG_TRANSC_STATE_CLIENT_GEN_FINAL_RESPONSE_RCVD,
    RVSIP_CALL_LEG_TRANSC_STATE_CLIENT_MSG_SEND_FAILURE
} RvSipCallLegTranscState;

/* RvSipCallLegByeState
 * ------------------------------------------------------------------
 * Indicates a state of a received BYE request
 */

typedef enum
{
    RVSIP_CALL_LEG_BYE_STATE_UNDEFINED = -1,
    RVSIP_CALL_LEG_BYE_STATE_IDLE,
    RVSIP_CALL_LEG_BYE_STATE_REQUEST_RCVD,
    RVSIP_CALL_LEG_BYE_STATE_RESPONSE_SENT,
    RVSIP_CALL_LEG_BYE_STATE_TERMINATED,
    RVSIP_CALL_LEG_BYE_STATE_DETACHED  /*the call-leg is about to detach from the transaction,
                                          no more states will be available for this transaction*/
} RvSipCallLegByeState;


/* RvSipCallLegTranscStatus
 * ------------------------------------------------------------------
 * Indicates the status of a transaction. This status is received with
 * the RvSipCallLegTranscResolvedEv callback.
 */
typedef enum
{
    RVSIP_CALL_LEG_TRANSC_STATUS_UNDEFINED = -1,
    RVSIP_CALL_LEG_TRANSC_STATUS_RESPONSE_RCVD,
    RVSIP_CALL_LEG_TRANSC_STATUS_TIME_OUT,
    RVSIP_CALL_LEG_TRANSC_STATUS_MSG_SEND_FAILURE
} RvSipCallLegTranscStatus;



/* RvSipCallLegPrackState
 * ------------------------------------------------------------------
 * Indicates the status of a prack process. This call back is only a
 * notification to the application and no response is expected for the
 * different states.
 * RVSIP_CALL_LEG_PRACK_STATE_UNDEFINED - No defined state.
 * RVSIP_CALL_LEG_PRACK_STATE_REL_PROV_RESPONSE_RCVD - a reliable provisional
 *                                        response was received on the call-leg
 * RVSIP_CALL_LEG_PRACK_STATE_PRACK_SENT - A prack was sent on the call-leg
 * RVSIP_CALL_LEG_PRACK_STATE_PRACK_FINAL_RESPONSE_RCVD - final response was
 *                                         received for a previously sent prack
 * RVSIP_CALL_LEG_PRACK_STATE_PRACK_PRACK_RCVD - The call-leg received prack
 *                                         after sending a reliable provisional
 *                                         response.
 * RVSIP_CALL_LEG_PRACK_STATE_PRACK_FINAL_RESPONSE_SENT - final response was sent on a
 *                                         received prack.
 */

typedef enum
{
    RVSIP_CALL_LEG_PRACK_STATE_UNDEFINED = -1,
    RVSIP_CALL_LEG_PRACK_STATE_REL_PROV_RESPONSE_RCVD,
    RVSIP_CALL_LEG_PRACK_STATE_PRACK_SENT,
    RVSIP_CALL_LEG_PRACK_STATE_PRACK_FINAL_RESPONSE_RCVD,
    RVSIP_CALL_LEG_PRACK_STATE_PRACK_RCVD,
    RVSIP_CALL_LEG_PRACK_STATE_PRACK_FINAL_RESPONSE_SENT
} RvSipCallLegPrackState;

/* RvSipCallLegReplacesStatus
 * ---------------------------------
 * The Replaces status enum indicates in what type of header the
 * Replaces option tag appeared
 * in an incoming request.
 * You can get the Replaces status by calling the RvSipCallLegGetReplacesStatus()
 * function.
 */
typedef enum
{
    RVSIP_CALL_LEG_REPLACES_UNDEFINED = -1, /*the Replaces was not found in the request*/
    RVSIP_CALL_LEG_REPLACES_SUPPORTED,      /*the Replaces was found in a Supported header*/
    RVSIP_CALL_LEG_REPLACES_REQUIRED        /*the Replaces was found in a Require header*/
} RvSipCallLegReplacesStatus;

/* RvSipCallLegReplacesReason
 * ---------------------------------
 * The Replaces reason enum indicates why the replaces matched call-leg was
 * not found.
 * It is used in RvSipCallLegReplacesGetMatchedCallExt API function.
 * RVSIP_CALL_LEG_REPLACES_REASON_UNDEFINED - no reason specifed.
 * RVSIP_CALL_LEG_REPLACES_REASON_DIALOG_FOUND_OK -
 *                      The matched call-leg was found correctly.
 * RVSIP_CALL_LEG_REPLACES_REASON_DIALOG_NOT_FOUND -
 *                      The matched call-leg was not found at all.
 * RVSIP_CALL_LEG_REPLACES_REASON_FOUND_NON_INVITE_DIALOG -
 *                      found a dialog, with same dialog identifiers,
 *                      but the dialog was not established with an INVITE request.
 * RVSIP_CALL_LEG_REPLACES_REASON_FOUND_CONFIRMED_DIALOG -
 *                      found a confirmed dialog, but the replaces header contains
 *                      'early-only' parameter, so application should reject the
 *                      request with 486.
 * RVSIP_CALL_LEG_REPLACES_REASON_FOUND_INCOMING_EARLY_DIALOG - found an incoming dialog
 *                      in an early state (offering), which is not allowed by the
 *                      replaces draft.
 * RVSIP_CALL_LEG_REPLACES_REASON_FOUND_TERMINATED_DIALOG -
 *                      found a dialog in state terminated.
 */
typedef enum
{
    RVSIP_CALL_LEG_REPLACES_REASON_UNDEFINED = -1,
    RVSIP_CALL_LEG_REPLACES_REASON_DIALOG_FOUND_OK,
    RVSIP_CALL_LEG_REPLACES_REASON_DIALOG_NOT_FOUND,
    RVSIP_CALL_LEG_REPLACES_REASON_FOUND_NON_INVITE_DIALOG,
    RVSIP_CALL_LEG_REPLACES_REASON_FOUND_CONFIRMED_DIALOG,
    RVSIP_CALL_LEG_REPLACES_REASON_FOUND_INCOMING_EARLY_DIALOG,
    RVSIP_CALL_LEG_REPLACES_REASON_FOUND_TERMINATED_DIALOG
}RvSipCallLegReplacesReason;

/* RvSipCallLegSessionTimerNotificationReason
 * ------------------------------------------
 * The session timer notification reason - describes what is the reason for the
 * session timer notification.
 * RVSIP_CALL_LEG_SESSION_TIMER_NOTIFY_REASON_UNDEFINED -
 *                      no reason specifed.
 * RVSIP_CALL_LEG_SESSION_TIMER_NOTIFY_REASON_SESSION_EXPIRES -
 *                      the reason notify that the session time is about to expire.
 * RVSIP_CALL_LEG_SESSION_TIMER_NOTIFY_REASON_422_RECEIVED -
 *                      the reason notify that 422 response was received during the session timer.
 */
typedef enum
{
    RVSIP_CALL_LEG_SESSION_TIMER_NOTIFY_REASON_UNDEFINED = -1,
    RVSIP_CALL_LEG_SESSION_TIMER_NOTIFY_REASON_SESSION_EXPIRES,
    RVSIP_CALL_LEG_SESSION_TIMER_NOTIFY_REASON_422_RECEIVED
} RvSipCallLegSessionTimerNotificationReason;

/* RvSipCallLegSessionTimerNegotiationReason
 * ------------------------------------------
 * The session timer negotiation reason describes what is the reason
 * that the negotiation didn't succeeded.
 * RVSIP_CALL_LEG_SESSION_TIMER_NEGOTIATION_REASON_DEST_NOT_SUPPORTED,
 *   The remote party doesn't support the session timer extention
 *
 * RVSIP_CALL_LEG_SESSION_TIMER_NEGOTIATION_REASON_REFRESHER_PREFERENCE_REJECT
 *   The refresher preference does not match to the call refresher
 */
typedef enum
{
    RVSIP_CALL_LEG_SESSION_TIMER_NEGOTIATION_REASON_UNDEFINED = -1,
    RVSIP_CALL_LEG_SESSION_TIMER_NEGOTIATION_REASON_DEST_NOT_SUPPORTED,
    RVSIP_CALL_LEG_SESSION_TIMER_NEGOTIATION_REASON_REFRESHER_PREFERENCE_REJECT
} RvSipCallLegSessionTimerNegotiationReason;

/* RvSipCallLegSessionTimerRefresherPreference
 * -------------------------------------------
 * This parameter is used to save the application preference for the call
 * RVSIP_CALL_LEG_SESSION_TIMER_REFRESHER_LOCAL
 *            The UA wishes to be the refresher
 * RVSIP_CALL_LEG_SESSION_TIMER_REFRESHER_REMOTE
 *            The UA wishes the remote party will be the refresher
 * RVSIP_CALL_LEG_SESSION_TIMER_REFRESHER_DONT_CARE
 *            The UA does not care who will be the refresher
 */
typedef enum
{
    RVSIP_CALL_LEG_SESSION_TIMER_REFRESHER_NONE = -1,
    RVSIP_CALL_LEG_SESSION_TIMER_REFRESHER_LOCAL,
    RVSIP_CALL_LEG_SESSION_TIMER_REFRESHER_REMOTE,
    RVSIP_CALL_LEG_SESSION_TIMER_REFRESHER_DONT_CARE
}RvSipCallLegSessionTimerRefresherPreference;




/*-----------------------------------------------------------------------
       C A L L  - L E G:  C A L L - B A C K  F U N C T I O N S
 ------------------------------------------------------------------------*/

/***************************************************************************
 * RvSipCallLegCreatedEv
 * ------------------------------------------------------------------------
 * General:  Notifies that a new call-leg was created, and exchanges handles
 *           with the application.
 * Return Value: (-)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hCallLeg - The new sip stack call-leg handle
 * Output:     phAppCallLeg - The application handle for this call-leg.
 ***************************************************************************/
typedef void
        (RVCALLCONV * RvSipCallLegCreatedEv)(
                                   IN  RvSipCallLegHandle            hCallLeg,
                                   OUT RvSipAppCallLegHandle         *phAppCallLeg);




/***************************************************************************
 * RvSipCallLegStateChangedEv
 * ------------------------------------------------------------------------
 * General: Notifies the application of a call-leg state change.
 *          For each state change the new state is supplied and the
 *          reason for the state change is also given.
 * Return Value: (-)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hCallLeg -    The sip stack call-leg handle
 *            hAppCallLeg - The application handle for this call-leg.
 *            eState -      The new call-leg state
 *            eReason -     The reason for the state change.
 ***************************************************************************/
typedef void
        (RVCALLCONV * RvSipCallLegStateChangedEv)(
                                   IN  RvSipCallLegHandle            hCallLeg,
                                   IN  RvSipAppCallLegHandle         hAppCallLeg,
                                   IN  RvSipCallLegState             eState,
                                   IN  RvSipCallLegStateChangeReason eReason);

/***************************************************************************
 * RvSipCallLegMsgToSendEv
 * ------------------------------------------------------------------------
 * General: An event indicating that a call-leg related outgoing
 *          message is about to be sent.
 * Return Value: RV_OK (the returned status is ignored in the current
 *                           stack version)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hCallLeg -    The sip stack call-leg handle
 *            hAppCallLeg - The application handle for this call-leg.
 *            hMsg -        Handle to the outgoing message.
 ***************************************************************************/
typedef RvStatus
        (RVCALLCONV * RvSipCallLegMsgToSendEv)(
                                   IN  RvSipCallLegHandle            hCallLeg,
                                   IN  RvSipAppCallLegHandle         hAppCallLeg,
                                   IN  RvSipMsgHandle                hMsg);


/***************************************************************************
 * RvSipCallLegMsgReceivedEv
 * ------------------------------------------------------------------------
 * General: An event indicating that a call-leg related incoming
 *          message has been received.
 * Return Value: RV_OK (the returned status is ignored in the current
 *                           stack version)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hCallLeg -    The sip stack call-leg handle
 *            hAppCallLeg - The application handle for this call-leg.
 *            hMsg -        Handle to the outgoing message.
 ***************************************************************************/
typedef RvStatus
        (RVCALLCONV * RvSipCallLegMsgReceivedEv)(
                                    IN  RvSipCallLegHandle            hCallLeg,
                                    IN  RvSipAppCallLegHandle         hAppCallLeg,
                                    IN  RvSipMsgHandle                hMsg);


/***************************************************************************
 * RvSipCallLegModifyStateChangedEv
 * ------------------------------------------------------------------------
 * General: Notifies the application that a the Modify state was changed.
 *          The Modify state is related to a re-INVITE process on a
 *          connected call. Before the call is connected, the Modify
 *          state is undefined. When the call assumes the connected state,
 *          the Modify state assumes the Idle state. Only in this state can
 *          the call-leg initiate or accept a re-INVITE request.
 * Return Value: (-)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hCallLeg -    The SIP Stack call-leg handle
 *            hAppCallLeg - The application handle for this call-leg.
 *            eModifyState -The new modify state.
 *          eReason     - The reason for the new state.
 ***************************************************************************/
typedef void
        (RVCALLCONV * RvSipCallLegModifyStateChangedEv)(
                                    IN  RvSipCallLegHandle            hCallLeg,
                                    IN  RvSipAppCallLegHandle         hAppCallLeg,
                                    IN  RvSipCallLegModifyState       eModifyState,
                                    IN  RvSipCallLegStateChangeReason eReason);


/***************************************************************************
 * RvSipCallLegModifyRequestRcvdEv
 * ------------------------------------------------------------------------
 * General: Notifies the application that a request to modify the session
 *          has been received. (A re-INVITE request).
 *          This call back is obsolete and is kept for backwards compatability
 *          only. Please use the RvSipCallLegModifyStateChangedEv event
 * Return Value: (-)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hCallLeg -    The sip stack call-leg handle
 *            hAppCallLeg - The application handle for this call-leg.
 ***************************************************************************/
typedef void
        (RVCALLCONV * RvSipCallLegModifyRequestRcvdEv)(
                                   IN  RvSipCallLegHandle            hCallLeg,
                                   IN  RvSipAppCallLegHandle         hAppCallLeg);


/***************************************************************************
 * RvSipCallLegModifyResultRcvdEv
 * ------------------------------------------------------------------------
 * General: Notifies the application that a final response to the modify request
 *          the user sent was received.
 * Return Value: (-)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hCallLeg -    The sip stack call-leg handle
 *            hAppCallLeg - The application handle for this call-leg.
 *            status -      The final response code.
 ***************************************************************************/
typedef void
        (RVCALLCONV * RvSipCallLegModifyResultRcvdEv)(
                                    IN  RvSipCallLegHandle            hCallLeg,
                                    IN  RvSipAppCallLegHandle         hAppCallLeg,
                                    IN  RvUint16                     status);



/***************************************************************************
 * RvSipCallLegTrancRequestRcvdEv
 * ------------------------------------------------------------------------
 * General: Notifies the application that a request was received and that
 *          the application should handle it.
 *          This callback is obsolete. You must not register to this callback
 *          if you register to the RvSipCallLegTranscStateChangedEv callback.
 * Return Value: (-)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hCallLeg -    The sip stack call-leg handle
 *            hAppCallLeg - The application handle for this call-leg.
 *            hTransc -     The handle to the transaction the request belongs to.
 *          hAppTransc -  Application handle to the call-leg transc.
 ***************************************************************************/
typedef void
        (RVCALLCONV * RvSipCallLegTrancRequestRcvdEv)(
                                   IN  RvSipCallLegHandle            hCallLeg,
                                   IN  RvSipAppCallLegHandle         hAppCallLeg,
                                   IN  RvSipTranscHandle             hTransc,
                                   IN  RvSipAppTranscHandle          hAppTransc);

/***************************************************************************
 * RvSipCallLegTranscResolvedEv
 * ------------------------------------------------------------------------
 * General: Notifies the application about the result of an outgoing request.
 *          The results are reported only for transactions initiated using
 *          the RvSipCallLegTranscRequest() function.
 *          The results can be a response message or a status code such as
 *          RVSIP_CALL_TRANSC_STATUS_TIME_OUT.
 *          If a response was received the status is given.
 * Return Value: (-)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hCallLeg -    The sip stack call-leg handle
 *            hAppCallLeg - The application handle for this call-leg.
 *            hTransc -     The handle to the transaction that received the
 *                        response
 *            hAppCallLeg - The application handle for this call-leg.
 *          eStatus -     The resolution status. if the status is
 *                        RVSIP_CALL_TRANSC_STATUS_RESPONSE_RECVD the
 *                        responseCode parameter will contain the response
 *                        message status code.
 *            responseCode -      The response status code.
 ***************************************************************************/
typedef void
        (RVCALLCONV * RvSipCallLegTranscResolvedEv)(
                              IN  RvSipCallLegHandle               hCallLeg,
                              IN  RvSipAppCallLegHandle            hAppCallLeg,
                              IN  RvSipTranscHandle                hTransc,
                              IN  RvSipAppTranscHandle             hAppTransc,
                              IN  RvSipCallLegTranscStatus         eStatus,
                              IN  RvUint16                        responseCode);


/***************************************************************************
 * RvSipCallLegTranscCreatedEv
 * ------------------------------------------------------------------------
 * General:Notifies that a new general transaction other then BYE was
 *         created and relates to the specified call-leg.
 *         The application can replace handles with the transaction and
 *         specify whether it wants to handle the request.
 *         If so, it will be notified of the transaction states and
 *         will have to respond to the request.
 * Return Value: (-)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hCallLeg -    The sip stack call-leg handle
 *            hAppCallLeg - The application handle for this call-leg.
 *            hTransc -     The handle to the new transaction
 * Output:  hAppTransc - The application handle to the transaction.
 *          bAppHandleTransc -  RV_TRUE if the application wants to
 *                        handle the request. RV_FALSE is the application
 *                        wants the call-leg to handle the request.
 ***************************************************************************/
typedef void
        (RVCALLCONV * RvSipCallLegTranscCreatedEv)(
                                   IN  RvSipCallLegHandle            hCallLeg,
                                   IN  RvSipAppCallLegHandle         hAppCallLeg,
                                      IN  RvSipTranscHandle             hTransc,
                                   OUT RvSipAppTranscHandle          *hAppTransc,
                                   OUT RvBool                       *bAppHandleTransc);


/***************************************************************************
 * RvSipCallLegTranscStateChangedEv
 * ------------------------------------------------------------------------
 * General: Notifies the application of a state change for a general
 *          transaction that belongs to the supplied call-leg.
 *          When the state indicated that a request was received, the
 *          application can call RvSipCallLegTranscResponse() and respond
 *          to the request. If the application does not want to handle
 *          the request, it should set the bHandleRequest to RV_FALSE.
 *          In this case, the Stack will either handle the transaction by itself or
 *          respond with a 501 not implemented.
 *          When the state indicates that a response was received, the
 *          responseCode parameter will hold the response code.
 * Return Value: (-)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hCallLeg -    The sip stack call-leg handle
 *            hAppCallLeg - The application handle for this call-leg.
 *            hTransc -     The stack handle to the transaction.
 *          hAppTransc -  The application handle to the transaction.
 *          eTranscState - The new state of the call-leg transaction.
 *          eReason      - The reason for the new state.
 * Output: (-).
 ***************************************************************************/
typedef void
        (RVCALLCONV * RvSipCallLegTranscStateChangedEv)(
                                   IN  RvSipCallLegHandle                hCallLeg,
                                   IN  RvSipAppCallLegHandle             hAppCallLeg,
                                   IN  RvSipTranscHandle                 hTransc,
                                   IN  RvSipAppTranscHandle              hAppTransc,
                                   IN  RvSipCallLegTranscState           eTranscState,
                                   IN  RvSipTransactionStateChangeReason eReason);


/***************************************************************************
 * RvSipCallLegByeCreatedEv
 * ------------------------------------------------------------------------
 * General: Notifies that a new BYE transaction was created
 *          and relates to the specified call-leg. The application can replace
 *          handles with the transaction and specify whether it wishes to handle
 *          the request. If so it will be notified of transaction states and will
 *          have to respond to the request.
 * Return Value: (-)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hCallLeg -    The sip stack call-leg handle
 *            hAppCallLeg - The application handle for this call-leg.
 *            hTransc -     The handle to the BYE transaction
 * Output:  hAppTransc - The application handle to the transaction
 *          bAppHandleTransc -  RV_TRUE if the application wishes to handle the
 *                           request. RV_FALSE is the application wants the
 *                           call-leg to handle the request.
 ***************************************************************************/
typedef void
        (RVCALLCONV * RvSipCallLegByeCreatedEv)(
                                   IN  RvSipCallLegHandle            hCallLeg,
                                   IN  RvSipAppCallLegHandle         hAppCallLeg,
                                      IN  RvSipTranscHandle             hTransc,
                                   OUT RvSipAppTranscHandle          *hAppTransc,
                                   OUT RvBool                       *bAppHandleTransc);


/***************************************************************************
 * RvSipCallLegByeStateChangedEv
 * ------------------------------------------------------------------------
 * General: Notifies the application of a state change for a BYE request that belongs
 *          to the supplied call-leg.
 *
 *          When the state indicated that a request was received
 *          the application can use RvSipCallLegByeAccept / RvSipCallLegByeReject
 *          to respond the BYE request.
 * Return Value: (-)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hCallLeg -    The sip stack call-leg handle
 *            hAppCallLeg - The application handle for this call-leg.
 *            hTransc -     The handle to the transaction.
 *          hAppTransc -  The application handle to the transaction.
 *          eTranscState - The call-leg transaction new state.
 *          eReason      - The reason for the new state.
 * Output: (-).
 ***************************************************************************/
typedef void
        (RVCALLCONV * RvSipCallLegByeStateChangedEv)(
                                   IN  RvSipCallLegHandle                hCallLeg,
                                   IN  RvSipAppCallLegHandle             hAppCallLeg,
                                   IN  RvSipTranscHandle                 hTransc,
                                   IN  RvSipAppTranscHandle              hAppTransc,
                                   IN  RvSipCallLegByeState              eByeState,
                                   IN  RvSipTransactionStateChangeReason eReason);

/***************************************************************************
 * RvSipCallLegReferStateChangedEv
 * ------------------------------------------------------------------------
 * General: Notifies the application of a call-leg refer state change.
 *          For each state change the new state is supplied and the
 *          reason for the state change is also given.
 * Return Value: (-)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hCallLeg -    The sip stack call-leg handle
 *            hAppCallLeg - The application handle for this call-leg.
 *            eState -      The new call-leg refer state
 *            eReason -     The reason for the state change.
 ***************************************************************************/
typedef void
        (RVCALLCONV * RvSipCallLegReferStateChangedEv)(
                            IN  RvSipCallLegHandle                    hCallLeg,
                            IN  RvSipAppCallLegHandle                 hAppCallLeg,
                            IN  RvSipCallLegReferState                eState,
                            IN  RvSipCallLegStateChangeReason         eReason);

/***************************************************************************
 * RvSipCallLegReferCancelledEv
 * ------------------------------------------------------------------------
 * General: Obsolete function. Cancel on REFER is rejected by stack with 403.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hCallLeg -    The sip stack call-leg handle
 *            hAppCallLeg - The application handle for this call-leg.
 ***************************************************************************/
typedef RvStatus (RVCALLCONV *RvSipCallLegReferCancelledEv)(
                              IN  RvSipCallLegHandle               hCallLeg,
                              IN  RvSipAppCallLegHandle            hAppCallLeg);

/***************************************************************************
 * RvSipCallLegReferNotifyEv
 * ------------------------------------------------------------------------
 * General: Notifies the application of a refer-notify-related event.
 *          (A refer-notify is a NOTIFY request that is a part of a refer
 *          process). This callback supplies the event that occurred and
 *          the reason for the occurrence of the event.
 *          When RvSipCallLegReferNotifyEv() notifies of a Refer-Notify
 *          Ready event, the response code parameter indicates the final
 *          status of the connect attempt. When RvSipCallLegReferNotifyEv()
 *          notifies of a Notify Received or Notify Sent event, the
 *          response code parameter indicates the response code found in
 *          the body of the NOTIFY message.
 * Return Value: (-)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hCallLeg -    The sip stack call-leg handle
 *            hAppCallLeg - The application handle for this call-leg.
 *            eNotification - The refer notify event.
 *            eReason -     The reason for the event occurrence.
 *          responseCode - This parameter has different meaning for
 *                         different events.
 *                         for RVSIP_CALL_LEG_REFER_NOTIFY_READY,
 *                         RVSIP_CALL_LEG_REFER_NOTIFY_UNAUTHENTICATED and
 *                         RVSIP_CALL_LEG_REFER_NOTIFY_REDIRECTED events the
 *                         response code represent the final status of the
 *                         connect attempt.
 *                         for the events RVSIP_CALL_LEG_REFER_NOTIFY_RECVD and
 *                         RVSIP_CALL_LEG_REFER_NOTIFY_SENT the response code
 *                         represents the status code found in the
 *                         NOTIFY request message body. In all other states
 *                         the response code represents the status code
 *                         of the response to the NOTIFY request.
 *          cSeqStep - This parameter is relevant in the
 *                     RVSIP_CALL_LEG_REFER_NOTIFY_READY,
 *                     RVSIP_CALL_LEG_REFER_NOTIFY_UNAUTHENTICATED and
 *                     RVSIP_CALL_LEG_REFER_NOTIFY_REDIRECTED events. It indicates
 *                     the CSeq step of the REFER transaction that this NOTIFY
 *                     is associated to.
 ***************************************************************************/
typedef void
        (RVCALLCONV * RvSipCallLegReferNotifyEv)(
                            IN  RvSipCallLegHandle              hCallLeg,
                            IN  RvSipAppCallLegHandle           hAppCallLeg,
                            IN  RvSipCallLegReferNotifyEvents   eNotification,
                            IN  RvSipCallLegStateChangeReason   eReason,
                            IN  RvInt16                        responseCode,
                            IN  RvInt32                        cSeqStep);

/***************************************************************************
 * RvSipCallLegPrackStateChangedEv
 * ------------------------------------------------------------------------
 * General: Notifies the application of a call-leg PRACK event.
 *          The PRACK state indicates the status of a PRACK process.
 *          This callback is only a notification to the application
 *          and no response is expected for the different states.
 * Return Value:(-)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hCallLeg    - The sip stack call-leg handle
 *            hAppCallLeg - The application handle for this call-leg.
 *          eState      - The PRACK process state.
 *          eReason     - The state reason.
 *          prackResponseCode - If the state indicates that a response
 *                              was received for a PRACK request, this
 *                              parameter will include the response code.
 ***************************************************************************/
typedef void (RVCALLCONV * RvSipCallLegPrackStateChangedEv) (
                      IN  RvSipCallLegHandle              hCallLeg,
                      IN  RvSipAppCallLegHandle           hAppCallLeg,
                      IN  RvSipCallLegPrackState          eState,
                      IN  RvSipCallLegStateChangeReason   eReason,
                      IN  RvInt16                        prackResponseCode);

/***************************************************************************
 * RvSipCallLegAuthCredentialsFoundEv
 * ------------------------------------------------------------------------
 * General:  Notifies the application that credentials were found in the
 *           Request message. This callback is called only if the
 *           application started the authentication procedure by calling
 *           RvSipCallLegAuthBegin(). The callback supplies the
 *           application with the Authorization header that contains
 *           these credentials. At this stage the application should
 *           use the RvSipCallLegAuthProceed() function. This callback
 *           also indicates whether the SIP Stack is capable of
 *           verifying the credentials that were found. Whenever the SIP
 *           Stack does not support the credentials (for example, if
 *           the algorithm is not MD5) the application can verify the
 *           credentials by itself or instruct the SIP Stack to
 *           continue to the next header.
 * Return Value: (-)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hCallLeg -   The SIP Stack call-leg handle
 *            hAppCallLeg - The application handle for this call-leg.
 *            hTransc -     The handle to the transaction that received the response.
 *          hAuthorization - The handle to the authorization handle that is found.
 *          bCredentialsSupported - Determines whether or not the SIP Stack
 *                        supports the algorithm in the authorization
 *                        header. If the SIP Stack supports the algorithm
 *                        of the header, the user has to return the
 *                        password of this username from the realm database, and
 *                        give it to the SIP Stack in the AuthenticateHeader()
 *                        function. If it is not a supported algorithm,
 *                        the user checks the header and calls AuthenticateHeader()
 *                        in order to continue the procedure.
 ***************************************************************************/
typedef void (RVCALLCONV * RvSipCallLegAuthCredentialsFoundEv)(
                      IN    RvSipCallLegHandle              hCallLeg,
                      IN    RvSipAppCallLegHandle           hAppCallLeg,
                      IN    RvSipTranscHandle               hTransc,
                      IN    RvSipAuthorizationHeaderHandle  hAuthorization,
                      IN    RvBool                         bCredentialsSupported);

/***************************************************************************
 * RvSipCallLegAuthCompletedEv
 * ------------------------------------------------------------------------
 * General:  Called when the authentication procedure is completed.
 *           If the procedure is completed because the correct
 *           authorization header was found, bAuthSucceed is RV_TRUE.
 *           If the procedure is completed because there are no more
 *           authorization headers to check, or because user ordered to
 *           stop the search for the correct header, bAuthSucceed is
 *           RV_FALSE.
 * Return Value: (-)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hCallLeg -    The sip stack call-leg handle
 *            hAppCallLeg - The application handle for this call-leg.
 *            hTransc -     The handle to the transaction that received the response.
 *          bAuthSucceed - RV_TRUE if the correct authorization header
 *                         was found. Otherwise, RV_FALSE.
 ***************************************************************************/
typedef void (RVCALLCONV * RvSipCallLegAuthCompletedEv)(
                      IN    RvSipCallLegHandle       hCallLeg,
                      IN    RvSipAppCallLegHandle    hAppCallLeg,
                      IN    RvSipTranscHandle        hTransc,
                      IN    RvBool                  bAuthSucceed);
/***************************************************************************
 * RvSipCallLegSessionTimerRefreshAlertEv
 * ------------------------------------------------------------------------
 * General:  Called when the alert time (the time in which the
 *           application needs to send a re-INVITE) is expired.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hCallLeg -    The sip stack call-leg handle
 *            hAppCallLeg - The application handle for this call-leg.
 ***************************************************************************/
typedef RvStatus (RVCALLCONV * RvSipCallLegSessionTimerRefreshAlertEv)(
                      IN    RvSipCallLegHandle       hCallLeg,
                      IN    RvSipAppCallLegHandle    hAppCallLeg);

/***************************************************************************
 * RvSipCallLegSessionTimerNotificationEv
 * ------------------------------------------------------------------------
 * General:  Called to notify about session-timer related events,
 *           such as Session-Expires.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hCallLeg -    The sip stack call-leg handle
 *            hAppCallLeg - The application handle for this call-leg.
 *          eReason - The reason for this notification.
 ***************************************************************************/
typedef RvStatus (RVCALLCONV * RvSipCallLegSessionTimerNotificationEv)(
                      IN RvSipCallLegHandle                         hCallLeg,
                      IN RvSipAppCallLegHandle                      hAppCallLeg,
                      IN RvSipCallLegSessionTimerNotificationReason eReason);

/***************************************************************************
 * RvSipCallLegSessionTimerNegotiationFaultEv
 * ------------------------------------------------------------------------
 * General:  Called when there are session-timer negotiation fault events,
 *           such as Refresher Preference Rejected.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hCallLeg -    The sip stack call-leg handle
 *            hAppCallLeg - The application handle for this call-leg.
 *          eReason - The reason for this negotiation fault .
 * Output:  bHandleSessionTimer - RV_TRUE if the application wants to
 *                                 operate the session time of this call.
 *                                 RV_FALSE if the application does not
 *                                 want to operate the session timer of
 *                                 this call.
 ***************************************************************************/
typedef RvStatus (RVCALLCONV * RvSipCallLegSessionTimerNegotiationFaultEv)(
                      IN  RvSipCallLegHandle                         hCallLeg,
                      IN  RvSipAppCallLegHandle                      hAppCallLeg,
                      IN  RvSipCallLegSessionTimerNegotiationReason  eReason,
                      OUT RvBool                                    *bHandleSessionTimer);


/***************************************************************************
 * RvSipCallLegOtherURLAddressFoundEv
 * ------------------------------------------------------------------------
 * General: Notifies the application that a message needs to be sent and
 *          the destination address is a URL type that is currently not
 *          supported by the stack. The URL has to be converted to a SIP URL
 *          for the message to be sent.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hCallLeg       - The sip stack call-leg handle
 *        hAppCallLeg    - The application handle for this call-leg.
 *        hTransc        - The transaction handle
 *        hAppTransc     - The application handle for this transaction.
 *        hMsg           - The message that includes the other URL address.
 *        hAddress       - Handle to unsupport address to be converted.
 * Output:    hSipURLAddress - Handle to the SIP URL address - this is an empty
 *                               address object that the application should fill.
 *        bAddressResolved-Indication wether the SIP URL address was filled.
 ***************************************************************************/
typedef RvStatus (RVCALLCONV *RvSipCallLegOtherURLAddressFoundEv)(
                     IN  RvSipCallLegHandle     hCallLeg,
                     IN  RvSipAppCallLegHandle  hAppCallLeg,
                     IN  RvSipTranscHandle      hTransc,
                     IN  RvSipAppTranscHandle   hAppTransc,
                     IN  RvSipMsgHandle         hMsg,
                     IN  RvSipAddressHandle     hAddress,
                     OUT RvSipAddressHandle     hSipURLAddress,
                     OUT RvBool                *bAddressResolved);




/***************************************************************************
 * RvSipCallLegFinalDestResolvedEv
 * ------------------------------------------------------------------------
 * General: Notifies the application that the call-leg is about to send a 
 *          message after the destination address was resolved.
 *          This callback supplies the final message object and the transaction
 *          that is responsible for sending this message. Changes in the message 
 *          at this stage will not effect the destination address. 
 *          When this callback is called, the application can query the transaction
 *          about the destination address using the 
 *          RvSipTransactionGetCurrentDestAddress() function. If the application 
 *          wishes, it can update the sent-by part of the top-most Via header. 
 *          The application must not update the branch parameter.
 *
 * Return Value: RvStatus. If the application returns a value other then
 *               RV_OK the message will not be sent. The transaction will
 *               terminate with error.The call-leg will also terminate unless
 *               the transaction was initiated by the application (for example
 *               INFO).
 *
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hCallLeg       - The sip stack call-leg handle
 *            hAppCallLeg    - The application handle for this call-leg.
 *            hTransc        - The transaction handle
 *            hAppTransc     - The application handle for this transaction.
 *                             For INVITE/BYE the hAppTransc is NULL.
 *            hMsgToSend     - The handle to the outgoing message.
 ***************************************************************************/
typedef RvStatus (RVCALLCONV * RvSipCallLegFinalDestResolvedEv)(
                      IN  RvSipCallLegHandle     hCallLeg,
                      IN  RvSipAppCallLegHandle  hAppCallLeg,
                      IN  RvSipTranscHandle      hTransc,
                      IN  RvSipAppTranscHandle   hAppTransc,
                      IN  RvSipMsgHandle         hMsgToSend);



#ifdef RV_SIGCOMP_ON
/***************************************************************************
 * RvSipCallLegSigCompMsgNotRespondedEv
 * ------------------------------------------------------------------------
 * General: Notifies the application that the timer of the transaction 
 *          responsible for sending a request has expired and that the
 *          SIP Stack has not yet received a response to the SigComp compressed 
 *          request.
 *          This callback is called in the following cases:
 *              - Before there is a need to retransmit a compressed message. 
 *                This happens when the transaction timer expires and, 
 *                according to RFC 3261, the SIP Stack needs to retransmit the message.
 *              - When the sigCompTcpTimer expires. The SIP Stack added a
 *                timer for SigComp TCP transmissions. When this timer expires
 *                the application can send the message again in a plain format.
 *                (According to RFC 3261, there are no retransmission in TCP).
 *          This callback is part of a recovery mechanism. The callback supplies
 *          information about compression type that was used in the last transmission. 
 *          The callback also gives the application the ability to determine if 
 *          there will be additional retransmissions, and the compression type of 
 *          the next retransmission.
 *          For example, the application can decide that the next retransmission 
 *          will not be compressed.
 *          Note: If you set the peNextMsgComp to
 *                RVSIP_TRANSMITTER_MSG_COMP_TYPE_UNDEFINED, the SIP Stack
 *                will stop the message retransmissions.
 *
 * Return Value: RvStatus. If the application returns a value other then
 *               RV_OK no further messages will be sent.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hCallLeg       - The sip stack call-leg handle
 *            hAppCallLeg    - The application handle for this call-leg.
 *            hTransc        - The transaction handle.
 *            hAppTransc     - The transaction application handle.
 *            retransNo     - The number of retransmissions of the request
 *                            until now.
 *            ePrevMsgComp  - The type of the previous not responded request
 * Output:    peNextMsgComp - The type of the next request to retransmit (
 *                            RVSIP_TRANSMITTER_MSG_COMP_TYPE_UNDEFINED means that the
 *                            application wishes to stop sending requests).
 ***************************************************************************/
typedef RvStatus (RVCALLCONV *RvSipCallLegSigCompMsgNotRespondedEv)(
                     IN  RvSipCallLegHandle           hCallLeg,
                     IN  RvSipAppCallLegHandle        hAppCallLeg,
                     IN  RvSipTranscHandle            hTransc,
                     IN  RvSipAppTranscHandle         hAppTransc,
                     IN  RvInt32                      retransNo,
                     IN  RvSipTransmitterMsgCompType  ePrevMsgComp,
                     OUT RvSipTransmitterMsgCompType *peNextMsgComp);
#endif /* RV_SIGCOMP_ON */

/***************************************************************************
 * RvSipCallLegNestedInitialReqRcvdEv
 * ------------------------------------------------------------------------
 * General: This callback indicates that a nested (second or more) INVITE request
 *          was received, on a call-leg that is not connected yet.
 *          (The second INVITE request has a different cseq value,
 *          so it was not rejected by the transaction layer, according to
 *          transaction merging rules).
 *          When this callback is called the application can order the stack
 *          whether to create a new call-leg for this nested request,
 *          or not, and then the request will be rejected by the stack.
 *
 * Return Value: RvStatus. If the application returns a value other then
 *               RV_OK the message will not be sent.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hExistCallLeg     - The exists call-leg handle.
 *            hExistAppCallLeg  - The application handle for the exists call-leg.
 *            hRcvdMsg          - The handle to the nested INVITE message.
 * Output:    pbCreateCallLeg   - RV_TRUE will cause the creation of a new call-leg.
 *                                RV_FALSE will cause the rejection of the nested INVITE.
 ***************************************************************************/
typedef void (RVCALLCONV * RvSipCallLegNestedInitialReqRcvdEv)(
                      IN  RvSipCallLegHandle     hExistCallLeg,
                      IN  RvSipAppCallLegHandle  hExistAppCallLeg,
                      IN  RvSipMsgHandle         hRcvdMsg,
                      OUT RvBool                 *pbCreateCallLeg);

/***************************************************************************
 * RvSipCallLegNewConnInUseEv
 * ------------------------------------------------------------------------
 * General:Notifies the application that the transaction is now using a new 
 *         connection. The connection can be a totally new one or a suitable 
 *         one that was found in the hash.
 *
 * Return Value: RV_OK (the returned status is ignored in the current
 *                      stack version)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hCallLeg     - The sip stack CallLeg handle
 *            hAppCallLeg  - The application handle for this CallLeg.
 *            hConn          - The connection handle
 *            bNewConnCreated - RV_TRUE if the connection is a newly 
 *                              created connection. RV_FALSE if the connection 
 *                              was found in the connection hash.
 ***************************************************************************/
typedef RvStatus (RVCALLCONV *RvSipCallLegNewConnInUseEv) (
                     IN  RvSipCallLegHandle             hCallLeg,
                     IN  RvSipAppCallLegHandle          hAppCallLeg,
                     IN  RvSipTransportConnectionHandle hConn,
                     IN  RvBool                         bNewConnCreated);

/***************************************************************************
 * RvSipCallLegCreatedDueToForkingEv
 * ------------------------------------------------------------------------
 * General:  An initial INVITE request, might be forked by a proxy. as a result,
 *           several 1xx and 2xx responses may be received from several UASs.
 *           The first incoming response will be mapped to the original call-leg,
 *           that sent the INVITE request. every other incoming response (with a
 *           different to-tag parameter), creates a new 'forked call-leg'.
 *           This callback function, notifies that a new call-leg was created due
 *           to forked 1xx/2xx response, and exchanges handles with the application.
 *
 *           Application may choose to terminate the new call here, using
 *           the pbTerminate argument. if so, call-leg will be destructed
 *           immediately, no callback will be given on this call-leg anymore.
 * Return Value: (-)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hNewCallLeg - The new sip stack call-leg handle
 * Output:    phNewAppCallLeg - The application handle for this call-leg.
 *            pbTerminated - terminate the new call-leg immediately or not.
 ***************************************************************************/
typedef void
        (RVCALLCONV * RvSipCallLegCreatedDueToForkingEv)(
                       IN  RvSipCallLegHandle           hNewCallLeg,
                       OUT RvSipAppCallLegHandle        *phNewAppCallLeg,
                       OUT RvBool                       *pbTerminate);

/* RvSipCallLegEvHandlers
 * ------------------------------------------------------------------------
 * Structure with function pointers to the module's call-back.
 * This structure is used to set the application call-backs in the function
 * RvSipCallLegMgrSetEvHandlers();
 *
 * pfnCallLegCreatedEvHandler    - notify of a new call.
 * pfnStateChangedEvHandler      - notify of call-leg state change.
 * pfnMsgToSendEvHandler         - notify that a message is about to be sent.
 * pfnMsgReceivedEvHandler       - notify that a message was received.
 * pfnModifyRequestRcvdEvHandler - notify of a modify request.
 * pfnModifyResultRcvdEvHandler  - notify of a modify request result.
 * pfnTrancRequestRcvdEvHandler  - notify of an incoming request
 * pfnTranscResolvedEvHandler    - notify the result of an outgoing request
 * pfnReferStateChangedEvHandler - notify of refer state change.
 * pfnReferNotifyEvHandler       - notify of a refer-notify related events.
 * pfnAuthCredentialsFoundEvHandler - notify of new credentials for server authentication.
 * pfnAuthCompletedEvHandler     - notify that server authentication procedure,
 *                                 was completed (with success or failure).
 * RvSipCallLegSessionTimerRefreshAlertEv - Notifies that the alert time
 *                                 (the time in which the application needs to send a re-INVITE to refresh the call) is expires.
 * RvSipCallLegSessionTimerNotificationEv -  Notifies the application of session-timer
 *                                 related events.
 * RvSipCallLegSessionTimerNegotiationFaultEv - Notifies the application of
 *                                  session-timer negotiation fault events, like refresher preference rejected.
 * RvSipCallLegByeCreatedEv      - Notifies the application of a new BYE transaction
 * RvSipCallLegByeStateChangedEv - Notifies the application of a BYE state change.
 * RvSipCallLegOtherURLAddressFoundEv - Notifies the application that other URL address was found
                                   and has to be converted to SIP URL address.
 * RvSipCallLegTranscCreatedEv   - Notifies the application of a new general transaction
 * RvSipCallLegTranscStateChangedEv - Notifies the application of a general transaction state change.
 * RvSipCallLegFinalDestResolvedEv  - Notifies that the final destination address
 *                                 of the register request was resolved.
 * RvSipCallLegSigCompMsgNotRespondedEv - Notifies the application that no response was
 *                                 received to the last sent SigComp message.
 * pfnNestedInitialReqRcvdEvHandler - Notifies the application that a second (or more) INVITE
 *                                 was received on a call-leg that is not in state connected yet.
 *                                 application can decide how to act with this request.
 * RvSipCallLegCreatedDueToForkingEv - Notifies the application of a new call-leg, created
 *                                  due to forked 1xx/2xx response on INVITE.
 */
typedef struct
{
    RvSipCallLegCreatedEv                       pfnCallLegCreatedEvHandler;
    RvSipCallLegStateChangedEv                  pfnStateChangedEvHandler;
    RvSipCallLegMsgToSendEv                     pfnMsgToSendEvHandler;
    RvSipCallLegMsgReceivedEv                   pfnMsgReceivedEvHandler;
    RvSipCallLegModifyStateChangedEv            pfnModifyStateChangedEvHandler;
    RvSipCallLegModifyRequestRcvdEv             pfnModifyRequestRcvdEvHandler;
    RvSipCallLegModifyResultRcvdEv              pfnModifyResultRcvdEvHandler;
    RvSipCallLegTrancRequestRcvdEv              pfnTranscRequestRcvdEvHandler;
    RvSipCallLegTranscResolvedEv                pfnTranscResolvedEvHandler;
    RvSipCallLegReferStateChangedEv             pfnReferStateChangedEvHandler;
    RvSipCallLegReferNotifyEv                   pfnReferNotifyEvHandler;
    RvSipCallLegPrackStateChangedEv             pfnPrackStateChangedEvEvHandler;
    RvSipCallLegReferCancelledEv                pfnReferCancelledEvHandler;
    RvSipCallLegAuthCredentialsFoundEv          pfnAuthCredentialsFoundEvHandler;
    RvSipCallLegAuthCompletedEv                 pfnAuthCompletedEvHandler;
    /* Session Timer call-backs */
    RvSipCallLegSessionTimerRefreshAlertEv      pfnSessionTimerRefreshAlertEvHandler;
    RvSipCallLegSessionTimerNotificationEv      pfnSessionTimerNotificationEvHandler;
    RvSipCallLegSessionTimerNegotiationFaultEv  pfnSessionTimerNegotiationFaultEvHandler;
    /* BYE callbacks */
    RvSipCallLegByeCreatedEv                    pfnByeCreatedEvHandler;
    RvSipCallLegByeStateChangedEv               pfnByeStateChangedEvHandler;
    RvSipCallLegTranscCreatedEv                 pfnTranscCreatedEvHandler;
    RvSipCallLegTranscStateChangedEv            pfnTranscStateChangedEvHandler;
    RvSipCallLegOtherURLAddressFoundEv          pfnOtherURLAddressFoundEvHandler;
    RvSipCallLegFinalDestResolvedEv             pfnFinalDestResolvedEvHandler;
#ifdef RV_SIGCOMP_ON
    RvSipCallLegSigCompMsgNotRespondedEv        pfnSigCompMsgNotRespondedEvHandler;
#endif
    RvSipCallLegNestedInitialReqRcvdEv          pfnNestedInitialReqRcvdEvHandler;
    RvSipCallLegNewConnInUseEv                  pfnNewConnInUseEvHandler;
    RvSipCallLegCreatedDueToForkingEv           pfnCallLegCreatedDueToForkingEvHandler;
} RvSipCallLegEvHandlers;


#endif /* RV_SIP_PRIMITIVES */

#ifdef __cplusplus
}
#endif


#endif /* END OF: #ifndef RV_SIP_CALL_LEG_TYPES_H */
