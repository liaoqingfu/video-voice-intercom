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
 *                              <RvSipTransactionTypes.h>
 *
 * The RvSipTransactionTypes.h file contains all type definitions and call-back functions
 * type definitions for the Transaction module.
 *
 *    Author                         Date
 *    ------                        ------
 *    Tamar Barzuza                  Nov 2000
 *********************************************************************************/


#ifndef RVSIP_TRANSACTION_TYPES_H
#define RVSIP_TRANSACTION_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                           */
/*-----------------------------------------------------------------------*/
#include "RV_SIP_DEF.h"
#include "RvSipMsg.h"
#include "RvSipPartyHeader.h"
#include "RvSipTransportTypes.h"
#include "RvSipTransmitterTypes.h"

/*-----------------------------------------------------------------------*/
/*                            TYPE DEFINITIONS                           */
/*-----------------------------------------------------------------------*/

/*
 * RvSipTranscMgrHandle
 * ---------------------------------------------------------------------------
 * The declaration of a handle to a Transaction Manager instance. The manager
 * object manages all the transactions and the handle is needed in all
 * manager-related API functions, such as the creation of new transactions.
 */
RV_DECLARE_HANDLE(RvSipTranscMgrHandle);

/*
 * RvSipTranscHandle
 * ---------------------------------------------------------------------------
 * The declaration of a transaction handle. The transaction handle is required by all
 * Transaction API functions, and is used to reference the correct transaction
 * object.
 */
RV_DECLARE_HANDLE(RvSipTranscHandle);

/*
 * RvSipTranscOwnerHandle
 * ---------------------------------------------------------------------------
 * The declaration of the application handle to a transaction. This handle is used by
 * the application in order to associate SIP Stack transaction objects with the
 * application transaction object. The application gives the application handle
 * when a new transaction is created. The SIP Stack will give this handle back to
 * the application in every callback function.
 */
RV_DECLARE_HANDLE(RvSipTranscOwnerHandle);

/*
 * RvSipAppTranscHandle
 * ---------------------------------------------------------------------------
 * The declaration of application handle to a transaction.
 * This handle is used by the application to associate SIP Stack transaction objects
 * with application transaction objects. This handle acts as a context that the
 * application can hold in the transaction. The application can set and get this
 * handle with the RvSipTransactionGetAppHandle() and
 * RvSipTransactionSetAppHandle() API functions.
 * This handle is not supplied in the transaction callback functions. It is used for
 * call-leg transactions.
 */
RV_DECLARE_HANDLE(RvSipAppTranscHandle);


/* RvSipTransactionState
 * ---------------------
 * Represents the state of the transaction between the server and the client. The
 * RvSipTransactionStateChangedEv() callback reports transaction state changes
 * and state change reasons. The state change reason indicates why the transaction
 * reached the new state. The transaction associates with the states enumerated
 * below:
 *
 * RVSIP_TRANSC_STATE_UNDEFINED: The state is not defined.
 * RVSIP_TRANSC_STATE_IDLE:
 *                          The Idle state is the initial state of the transaction
 *                          state machine. Upon transaction creation, the transaction
 *                          assumes the Idle state. It remains in this state until
 *                          Request() is called. If the request method is INVITE, the
 *                          transaction will assume the Client-Invite-Calling state.
 *                          If the request is a general request, the transaction will
 *                          assume the Client-General-Request-Sent state. If the request
 *                          is CANCEL, the transaction will assume the
 *                          Client-Cancel-Request-Sent state.
 * RVSIP_TRANSC_STATE_SERVER_GEN_REQUEST_RCVD:
 *                         Upon receipt of a request (that is not a retransmission)
 *                         by a server transaction, the transaction assumes the
 *                         Server-General-Request-Received state. In this state,
 *                           it is up to you to respond to the request using the
 *                           transaction API. You may begin with sending provisional
 *                           responses. You must end with sending a final response,
 *                           or terminating the transaction.
 * RVSIP_TRANSC_STATE_SERVER_GEN_FINAL_RESPONSE_SENT:
 *                          When calling Respond(), the transaction generates and sends
 *                          a response message. The transaction will then assume the
 *                          Server-General-Final-Response-Sent state. When entering this
 *                          state, a transaction timer is set to generalLingerTimer if the
 *                          transport is an unreliable transport. When this timer expires,
 *                          the transaction is terminated and assumes the Terminated state.
 *                          If the transport is a reliable transport, the transaction is
 *                          terminated and assumes the Terminated state immediately when
 *                          it reaches this state. (Timer J as defined in RFC 543).
 * RVSIP_TRANSC_STATE_CLIENT_GEN_REQUEST_SENT:
 *                            After calling Request() with a method other than INVITE,
 *                          which generates and sends a Request message, the transaction
 *                          enters the Client-General-Request-Sent state. The client
 *                          transaction remains in this state until it receives a
 *                          provisional or final response from the server. Receipt of a
 *                          provisional response will cause the transaction to assume the
 *                          Client-General-Proceeding state.
 *                          Receipt of a final response will cause the transaction to assume
 *                          the Client-General-Response-Received state. While in the
 *                          request Sent state, the transaction retransmits the request message
 *                          according to the rules defined in RFC 3261, and the values configured
 *                          for T1, T2 and generalRequestTimeoutTimer (timer F).
 *                          The retransmissions take place only if the transport is an
 *                          unreliable transport. If no response is received when
 *                          generalRequestTimeoutTimer is expired, the transaction is terminated
 *                          automatically and assumes the Terminated state (in any transport).
 *    RVSIP_TRANSC_STATE_CLIENT_GEN_PROCEEDING:
 *                          Upon receipt of a provisional response by a client transaction
 *                          (not a retransmission), the transaction assumes the
 *                          Client-General-Proceeding state.
 *                          The transaction will continue to retransmit the request message
 *                          until the generalRequest Timeout Timer is expired using a consistent
 *                          interval of T2 seconds as defined in RFC 3261 (only if the transport
 *                          is unreliable). Receipt of a final response will move the transaction
 *                          to the Client-General-Final-Response-Rcvd state.
 *                          If no final response is received when the generalRequest Timeout
 *                          Timer is expired, the transaction is terminated and assumes the
 *                          Terminated state.
 *    RVSIP_TRANSC_STATE_CLIENT_INVITE_CALLING:
 *                           After calling Request() with the INVITE method
 *                         which generates and sends an INVITE
 *                           request message, the transaction enters the Client Invite
 *                         Calling state. The client transaction remains
 *                           in this state until it receives a provisional or final
 *                           response from the server. Receipt of a provisional
 *                           response will cause the transaction to assume the
 *                           Client Invite Proceeding state. Receipt of a final
 *                           response will cause the transaction to assume the
 *                           Client Invite Finel Response Rcvd state.
 *                         While in this state, the transaction retransmits the
 *                         request message according to the
 *                           rules defined in RFC 2543, and the value
 *                           configured for T1. If no response is received
 *                           after 7 transmissions, the transaction will
 *                           terminate automatically and will asume the Terminated
 *                         state. In reliable mode (TCP), the transaction is
 *                         terminated after the noResponseTimer expires, unless
 *                         the state has changed.
 *    RVSIP_TRANSC_STATE_CLIENT_INVITE_PROCEEDING:
 *                         Upon receipt of a provisional response by a client
 *                         invite transaction (not a retransmission), the transaction
 *                         assumes the Client Invite Proceeding state.
 *                         When entering this state, a transaction timer is set to
 *                         provisionalTimer. When this timer expires, the
 *                         transaction is terminated. This way the transaction will
 *                         not wait forever for its other party.
 *                         Receipt of a final response will move the transaction
 *                         to Client Invite Final Response Rcvd state.
 *  RVSIP_TRANSC_STATE_CLIENT_INVITE_PROCEEDING_TIMEOUT:
 *                          Upon reaching timeout on the
 *                          RVSIP_TRANSC_STATE_CLIENT_INVITE_PROCEEDING state the
 *                          transaction assumes the Invite Request TimeOut state, if the
 *                          enableInviteProceedingTimeoutState flag is checked.
 *                          In this state the application has to decide whether to terminate
 *                          the transaction or to CANCEL it.
 *    RVSIP_TRANSC_STATE_CLIENT_INVITE_FINAL_RESPONSE_RCVD:
 *                         Upon receipt of an Invite final response, The transaction
 *                         assumes the Client Invite Final Response Rcvd state.
 *                         At this state the application can initiate the ACK
 *                         request by calling the Ack() function.
 *                         After sending the ack the transaction will move to the
 *                         Client Invite Ack Sent state.
 *    RVSIP_TRANSC_STATE_CLIENT_INVITE_ACK_SENT:
 *                         After calling Ack() which generates and sends an ACK
 *                           request message, the transaction enters the Client Invite
 *                         Ack Sent state.
 *                         The transaction object retransmits the ACK request
 *                         according to the reliability mechanism defined in the
 *                         protocol.
 *                         When entering this state, a transaction timer is set
 *                         to inviteLingerTimer. When this timer expires, the
 *                         transaction is terminated. This way the transaction
 *                         will not wait forever for retransmissions from the
 *                         other party.
 *     RVSIP_TRANSC_STATE_SERVER_INVITE_REQUEST_RCVD:
 *                         Upon receipt of an INVITE request (that is not a retransmission)
 *                         by a server invite transaction, the transaction assumes the
 *                            Server Invite Request Received state. In this state,
 *                           it is up to you to respond to the request using the
 *                           transaction API. You may begin with sending provisional
 *                           responses. You must end with sending a final response,
 *                           or terminating the transaction.
 *    RVSIP_TRANSC_STATE_SERVER_INVITE_FINAL_RESPONSE_SENT:
 *                         When calling Respond() on an Invite transaction, the
 *                         transaction generates and
 *                         sends a response message. The transaction will then
 *                         assume the Server Invite Final Response Sent state.
 *                         The transaction object retransmits the final response
 *                         according to the reliability mechanism defined in the
 *                         protocol. After 7 transmissions  timeouts the
 *                         transaction is terminated (unless the state has changed).
 *                         If an ACK message is received, the transaction moves
 *                         to the Terminated state.
 *                         This state is used only for a proxy inplementation when
 *                         the call-leg layer is not used.
 *  RVSIP_TRANSC_STATE_SERVER_INVITE_ACK_RCVD:
 *                         When the server receives an ACK message the transaction
 *                         timer is set to T4 if the transport is unreliable, or to 0
 *                         otherwise. Only after this timer is expired the transaction is
 *                         terminated.
 *    RVSIP_TRANSC_STATE_TERMINATED:
 *                         This is the final state of the transaction.
 *                         When a transaction is terminated, the transaction
 *                         assumes the Terminated state. Upon reaching the
 *                         Terminated state, you can no longer reference the
 *                         transaction object.
 *    RVSIP_TRANSC_STATE_SERVER_PRACK_FINAL_RESPONSE_SENT:
 *                         this state is not used anymore instead we use
 *                           RVSIP_TRANSC_STATE_SERVER_GEN_FINAL_RESPONSE_SENT
 *    RVSIP_TRANSC_STATE_SERVER_INVITE_REL_PROV_RESPONSE_SENT:
 *                         After calling the ResponseReliable() function in the
 *                         Server Invite Request Rcvd state the a reliable
 *                         provisional response will be sent and the transaction
 *                         will assume the Server Invite Rel Prov Response Sent state.
 *                         The transaction object retransmits the Reliable
 *                         Provisional Response as any final response to the
 *                         INVITE request. After 7 transmission timeouts, the
 *                         transaction is terminated, unless the state has changed.
 *                         Receipt of the PRACK and its automatic response
 *                         moves the transaction to the
 *                         Server Invite Prack Completed State.
 *    RVSIP_TRANSC_STATE_SERVER_INVITE_PRACK_COMPLETED:
 *                         While in the Server Invite Rel Prov Resposne Sent state
 *                         the invite server transaction waits for a PRACK frocess
 *                         to be completed. The PRACK process is handled by a separate
 *                         prack server transaction. When the process is completed (PRACK
 *                         request is received and respoded) the invite server transaction
 *                         assumes the Server Invite Prack Completed state. you can
 *                         continue by sending one or more provisional response and
 *                         must finish with a final response.
 *     RVSIP_TRANSC_STATE_CLIENT_INVITE_PROXY_2XX_RESPONSE_RCVD:
 *                         Upon receipt of an Invite 2xx final response by a
 *                         proxy Client Invite transaction, The transaction
 *                         assumes the Proxy Client Invite 2xx Response Rcvd state.
 *                         When entering this state, the
 *                         transaction timer is set to proxy2xxRcvdTimer.
 *                         When this timer expires, the transaction
 *                         is terminated.
 *                         This state is used only for a proxy inplementation.
 *    RVSIP_TRANSC_STATE_SERVER_INVITE_PROXY_2XX_RESPONSE_SENT:
 *                         When proxing an invte 2xx response with the RespondMsg()
 *                         function, the transaction
 *                         sends a response message. The transaction will then
 *                         assume the Proxy Server Invite Final Response Sent state.
 *                         This state is used only for a proxy inplementation when
 *                         the call-leg layer is not used.
 *                         When entering this state, the
 *                         transaction timer is set to proxy2xxSentTimer.
 *                         When this timer expires, the transaction
 *                         is terminated.
 *                         This state is used only for a proxy inplementation.
 *  RVSIP_TRANSC_STATE_SERVER_CANCEL_REQUEST_RCVD:
 *                         For Proxies Only.
 *                         Upon receipt of a CANCEL request (that is not a retransmission)
 *                         by a server transaction, the transaction assumes the
 *                            Server Cancel Request Received state. In this state,
 *                           it is up to you to respond to the request using the
 *                           transaction API. You must end with sending a final response,
 *                           or terminating the transaction.
 *    RVSIP_TRANSC_STATE_CLIENT_INVITE_CANCELLING:
 *                         When calling the Cancel() function on a client invite
 *                         transaction the transaction assumes the Client Invite
 *                         Cancelled state.
 *                         This state indicates that the cancelling process has
 *                         begun. In practice, a new Client Cancel transaction
 *                         is created and CANCEL request is sent.
 *                         Upon receipt of an Invite final response, The transaction
 *                         assumes the Client Invite Final Response Rcvd state.
 *                         When entering this state a transaction timer is set
 *                         to noResponseTimer. When this timer expires, the
 *                         transaction is terminated and does not wait indefinitely
 *                         while the other party sends retransmissions.
 *    RVSIP_TRANSC_STATE_CLIENT_GEN_CANCELLING:
 *                         When calling the Cancel() function on a client general
 *                         transaction the transaction assumes the Client General
 *                         Cancelled state.
 *                         This state indicates that the cancelling process has
 *                         begun. In practice, a new Client Cancel transaction
 *                         is created and CANCEL request is sent.
 *                         Upon receipt of a final response, The transaction
 *                         assumes the Client General Final Response Rcvd state.
 *                         When entering this state a transaction timer is set
 *                         to noResponseTimer. When this timer expires, the
 *                         transaction is terminated and does not wait indefinitely
 *                         while the other party sends retransmissions.
 *    RVSIP_TRANSC_STATE_CLIENT_CANCEL_SENT:
 *                         When calling the Cancel() function a new Client Cancel
 *                         transaction is created and CANCEL request is sent.
 *                         The client cancel transaction assumes the Client Cancel
 *                         Sent State.
 *                         The transaction object retransmits the cancel request
 *                         according to the reliability mechanism defined in the
 *                         protocol. After 11 retransmission timeouts the
 *                         transaction is terminated, unless the state has changed.
 *                         Receipt of a 1xx response message moves the transaction
 *                         to Client Cancel Proceeding state.
 *                         Receipt of a final response (2xx-6xx) moves the
 *                         transaction to terminated state.
 *    RVSIP_TRANSC_STATE_CLIENT_CANCEL_PROCEEDING:
 *                         Upon receipt of a provisional response by a client
 *                         cancel transaction (not a retransmission), the transaction
 *                         assumes the Client Cancel Proceeding state.
 *                         The transaction will continue to retransmit the
 *                         request message up to 11 times using a consistent
 *                         interval of T2 seconds as defined in REF 2543.
 *                         Receipt of a final response will move the transaction
 *                         to Terminated state.
 *    RVSIP_TRANSC_STATE_SERVER_CANCEL_FINAL_RESPONSE_SENT:
 *                         When a cancel is received  it is
 *                         automaically handled by the transaction layer. The
 *                         transaction object will initiate the response to the
 *                         CANCEL by it self and the transaction will assume the
 *                         Server Cancel Final Response Sent state.
 *                         The transaction object retransmits the final response
 *                         according to the reliability mechanism defined in the
 *                         protocol. When entering this state, the
 *                         transaction timer is set to generalLingerTimer.
 *                         When this timer expires, the transaction
 *                         is terminated.
 *    RVSIP_TRANSC_STATE_CLIENT_CANCEL_FINAL_RESPONSE_RCVD:
 *                         Upon receipt of a cancel final response, The transaction
 *                         assumes the Client Cancel Final Response Rcvd state.
 *                         When reaching this state the transaction timer is set to T4
 *                         if the stack works with unreliable transport, otherwise the
 *                         timer is set to 0.
 *    RVSIP_TRANSC_STATE_CLIENT_GEN_FINAL_RESPONSE_RCVD:
 *                         Upon receipt of a final response, The transaction
 *                         assumes the Client General Final Response Rcvd state.
 *                         When reaching this state the transaction timer is set to T4
 *                         if the stack works with unreliable transport, otherwise the
 *                         timer is set to 0.
 * RVSIP_TRANSC_STATE_CLIENT_MSG_SEND_FAILURE:
 *                          The transaction assumes this state when sending a Message-Fail
 *                          due to a timeout (timer B or F expired and no response was
 *                          received), network error, or a 503 final response.
 *                          In this state, it is the responsibility of the application to
 *                          decide whether to terminate the transaction or call the
 *                          continue-DNS function that opens a new transaction and sends
 *                          the message to the next address in the DNS list. If you decide
 *                          to continue-DNS then it is the SIP Stack responsibility to
 *                          terminate the transaction. This state can be reached from the
 *                          following states:
 *                          RVSIP_TRANSC_STATE_CLIENT_GEN_REQUEST_SENT,
 *                          RVSIP_TRANSC_STATE_CLIENT_GEN_PROCEEDING
 *                          (when 503 response is received),
 *                          RVSIP_TRANSC_STATE_CLIENT_INVITE_CALLING,
 *                          RVSIP_TRANSC_STATE_CLIENT_INVITE_PROCEEDING
 *                          (when 503 response is received),
 *                          RVSIP_TRANSC_STATE_CLIENT_INVITE_ACK_SENT.
 */
typedef enum
{
    RVSIP_TRANSC_STATE_UNDEFINED = -1,
    RVSIP_TRANSC_STATE_IDLE,
    RVSIP_TRANSC_STATE_SERVER_GEN_REQUEST_RCVD,
    RVSIP_TRANSC_STATE_SERVER_GEN_FINAL_RESPONSE_SENT,
    RVSIP_TRANSC_STATE_CLIENT_GEN_REQUEST_SENT,
    RVSIP_TRANSC_STATE_CLIENT_GEN_PROCEEDING,
    RVSIP_TRANSC_STATE_CLIENT_INVITE_CALLING,
    RVSIP_TRANSC_STATE_CLIENT_INVITE_PROCEEDING,
    RVSIP_TRANSC_STATE_CLIENT_INVITE_FINAL_RESPONSE_RCVD,
    RVSIP_TRANSC_STATE_CLIENT_INVITE_ACK_SENT,
    RVSIP_TRANSC_STATE_SERVER_INVITE_REQUEST_RCVD,
    RVSIP_TRANSC_STATE_SERVER_INVITE_FINAL_RESPONSE_SENT,
    RVSIP_TRANSC_STATE_TERMINATED,
    RVSIP_TRANSC_STATE_SERVER_PRACK_FINAL_RESPONSE_SENT 
         = RVSIP_TRANSC_STATE_SERVER_GEN_FINAL_RESPONSE_SENT,
    RVSIP_TRANSC_STATE_SERVER_INVITE_PRACK_COMPLETED = 13,
    RVSIP_TRANSC_STATE_SERVER_INVITE_REL_PROV_RESPONSE_SENT,
    RVSIP_TRANSC_STATE_CLIENT_INVITE_PROXY_2XX_RESPONSE_RCVD,
    RVSIP_TRANSC_STATE_SERVER_INVITE_PROXY_2XX_RESPONSE_SENT,
    RVSIP_TRANSC_STATE_SERVER_CANCEL_REQUEST_RCVD,
    RVSIP_TRANSC_STATE_CLIENT_INVITE_CANCELLING,
    RVSIP_TRANSC_STATE_CLIENT_GEN_CANCELLING,
    RVSIP_TRANSC_STATE_CLIENT_CANCEL_SENT,
    RVSIP_TRANSC_STATE_CLIENT_CANCEL_PROCEEDING,
    RVSIP_TRANSC_STATE_SERVER_CANCEL_FINAL_RESPONSE_SENT,
    RVSIP_TRANSC_STATE_CLIENT_GEN_FINAL_RESPONSE_RCVD,
    RVSIP_TRANSC_STATE_CLIENT_INVITE_PROCEEDING_TIMEOUT,
    RVSIP_TRANSC_STATE_SERVER_INVITE_ACK_RCVD,
    RVSIP_TRANSC_STATE_CLIENT_CANCEL_FINAL_RESPONSE_RCVD,
    RVSIP_TRANSC_STATE_CLIENT_MSG_SEND_FAILURE
} RvSipTransactionState;



/* RvSipTransactionStateChangeReason
 * ---------------------------------
 * A transaction object has an inner state. The state changes according
 * to the state machine defined for the transactions. Each state change
 * is explained by one of the reasons enumerated bellow.
 */
typedef enum
{
    RVSIP_TRANSC_REASON_ERROR = -2,
    RVSIP_TRANSC_REASON_UNDEFINED,
    RVSIP_TRANSC_REASON_USER_COMMAND,
    RVSIP_TRANSC_REASON_TIME_OUT,
    RVSIP_TRANSC_REASON_RAN_OUT_OF_TIMERS,
    RVSIP_TRANSC_REASON_NORMAL_TERMINATION,
    RVSIP_TRANSC_REASON_TRANSACTION_MANAGER_COMMAND,
    RVSIP_TRANSC_REASON_REQUEST_RECEIVED,
    RVSIP_TRANSC_REASON_ACK_RECEIVED,
    RVSIP_TRANSC_REASON_PROVISIONAL_RESPONSE_RECEIVED, /* 1xx received. */
    RVSIP_TRANSC_REASON_RESPONSE_SUCCESSFUL_RECVD,     /* 2xx received. */
    RVSIP_TRANSC_REASON_RESPONSE_REDIRECTION_RECVD,    /* 3xx received. */
    RVSIP_TRANSC_REASON_RESPONSE_REQUEST_FAILURE_RECVD,/* 4xx received. */
    RVSIP_TRANSC_REASON_RESPONSE_SERVER_FAILURE_RECVD, /* 5xx received. */
    RVSIP_TRANSC_REASON_RESPONSE_GLOBAL_FAILURE_RECVD,
    RVSIP_TRANSC_REASON_TRANSACTION_CANCELED,
    RVSIP_TRANSC_REASON_RELIABLE_PROVISIONAL_RCVD,
    RVSIP_TRANSC_REASON_TRANSACTION_COMMAND,
    RVSIP_TRANSC_REASON_UNSUPPORTED_OPTION,
    RVSIP_TRANSC_REASON_NETWORK_ERROR,
    RVSIP_TRANSC_REASON_503_RECEIVED,
    RVSIP_TRANSC_REASON_CONTINUE_DNS,
    RVSIP_TRANSC_REASON_CALL_LEG_MANAGER_COMMAND,
    RVSIP_TRANSC_REASON_DETACH_OWNER,
    RVSIP_TRANSC_REASON_REL_PROV_RESP_TIME_OUT,
    RVSIP_TRANSC_REASON_OUT_OF_RESOURCES
} RvSipTransactionStateChangeReason;



#ifndef RV_SIP_PRIMITIVES

/* RvSipTransaction100RelStatus
 * ---------------------------------
 * Indicates in which type of header the 100rel option tag appeared in an incoming
 * request.
 * You can get the 100 rel status by calling the function,
 * RvSipTransactionGet100RelStatus().
 */
typedef enum
{
    RVSIP_TRANSC_100_REL_UNDEFINED = -1, /*the 100 rel was not found in the request*/
    RVSIP_TRANSC_100_REL_SUPPORTED,      /*the 100 rel was found in a Supported header*/
    RVSIP_TRANSC_100_REL_REQUIRED        /*the 100 rel was found in a Require header*/
} RvSipTransaction100RelStatus;

#endif /* #ifndef RV_SIP_PRIMITIVES*/
/* RvSipTransactionAuthAction
 * ---------------------------------
 * Indicates to the RvSipTransactionAuthProceed function
 * with which action to proceed the authentication process.,
 *
 * RVSIP_TRANSC_AUTH_ACTION_USE_PASSWORD   - order to check the given authorization header,
 *                                           using the given password.
 * RVSIP_TRANSC_AUTH_ACTION_SUCCESS        - The user had checked the authorization header
 *                                           and it is correct. (This will cause AuthCompletedEv
 *                                           to be called, with Success status).
 * RVSIP_TRANSC_AUTH_ACTION_FAILURE        - The user wants to stop the loop that searches
 *                                           for authorization headers. (This will cause
 *                                           AuthCompletedEv to be called, with Failure
 *                                           status).
 * RVSIP_TRANSC_AUTH_ACTION_SKIP           - Orders to skip the given header, and continue
 *                                           the authentication procedure with the next header
 *                                          (if it exists). (This will cause AuthCredentialFoundEv
 *                                          to be called, or AuthCompletedEv (with Failure
 *                                          status) if there are no more authorization headers.
 */
typedef enum
{
    RVSIP_TRANSC_AUTH_ACTION_UNDEFINED = -1,
    RVSIP_TRANSC_AUTH_ACTION_USE_PASSWORD,
    RVSIP_TRANSC_AUTH_ACTION_SUCCESS,
    RVSIP_TRANSC_AUTH_ACTION_FAILURE,
    RVSIP_TRANSC_AUTH_ACTION_SKIP
} RvSipTransactionAuthAction;

/* RvSipTransactionStringName
 * ---------------------------
 * The RvSipTransactionStringName includes transaction parameters that are
 * kept as a string. It the application wishes to use and RPOOL pointer in
 * order to set a parameter into the transaction it should specify the string
 * parameter using this enumeration.
 */
typedef enum
{
    RVSIP_TRANSC_VIA_BRANCH      /*the via branch parameter*/
} RvSipTransactionStringName;


/*-----------------------------------------------------------------------
       T R A N S A C T I O N S:  C A L L - B A C K  F U N C T I O N S
 ------------------------------------------------------------------------*/

/***************************************************************************
 * RvSipTransactionCreatedEv
 * ------------------------------------------------------------------------
 * General: Notifies the application that a new server transaction has been
 *          created. The newly created transaction always assumes the Idle
 *          state. You should decide whether you wish to handle this transaction.
 *          If so, your application can exchange handles with the SIP Stack
 *          using this callback.
 * Return Value: (-)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTransc     - The new SIP Stack transaction handle.
 *           pAppContext - The application context which you supplied.
 * Output:  hAppTransc  - Application handle for the transaction.
 *          b_handleTransc - Indicated wether the application wishes to handle
 *                           the transaction - RV_TRUE.
 *                           if set tp RV_FALSE the stack will handle the
 *                           transaction by itself. The normal behavior will
 *                           be returning of 501 not implemented.
 ***************************************************************************/
typedef void (RVCALLCONV * RvSipTransactionCreatedEv)(
                      IN    RvSipTranscHandle        hTransc,
                      IN    void                     *pAppContext,
                      OUT   RvSipTranscOwnerHandle   *hAppTransc,
                      OUT   RvBool                  *b_handleTransc);


/***************************************************************************
 * RvSipTransactionStateChangedEv
 * ------------------------------------------------------------------------
 * General: Notifies the application of a transaction state change and the
 *          associated state change reason.
 *          This function is probably the most useful of the events that the
 *          SIP transaction reports. When you receive notifications of SIP
 *          transaction state changes, your application can act upon the state.
 *          For example, upon receipt of a Server-General-Request-Received state
 *          notification, your application can respond with a desired response code.
 * Return Value: (-)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTransc      - The transaction handle.
 *            hTranscOwner - The application handle for this transaction.
 *            eState       - The new transaction state.
 *            eReason      - The reason for the state change.
 ***************************************************************************/
typedef void (RVCALLCONV  * RvSipTransactionStateChangedEv)(
                            IN RvSipTranscHandle                 hTransc,
                             IN RvSipTranscOwnerHandle            hTranscOwner,
                              IN RvSipTransactionState             eState,
                            IN RvSipTransactionStateChangeReason eReason);

/***************************************************************************
 * RvSipTransactionMsgToSendEv
 * ------------------------------------------------------------------------
 * General: Indicates that a transaction-related outgoing message is about
 *          to be sent.
 * Return Value: RV_OK (the returned status is ignored in the current
 *                           stack version)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTransc      - The transaction handle.
 *            hTranscOwner - The application handle for this transaction.
 *            hMsgToSend   - The handle to the outgoing message.
 ***************************************************************************/
typedef RvStatus (RVCALLCONV * RvSipTransactionMsgToSendEv)(
                            IN RvSipTranscHandle       hTransc,
                             IN RvSipTranscOwnerHandle  hTranscOwner,
                            IN RvSipMsgHandle          hMsgToSend);

/***************************************************************************
 * RvSipTransactionMsgReceivedEv
 * ------------------------------------------------------------------------
 * General: Indicates that a transaction-related incoming message has been
 *          received.
 * Return Value: RV_OK (the returned status is ignored in the current
 *                           stack version)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTransc      - The transaction handle.
 *            hTranscOwner - The application handle for this transaction.
 *            hMsgReceived - Handle to the incoming message.
 ***************************************************************************/
typedef RvStatus (RVCALLCONV * RvSipTransactionMsgReceivedEv)(
                            IN RvSipTranscHandle      hTransc,
                              IN RvSipTranscOwnerHandle hTranscOwner,
                            IN RvSipMsgHandle         hMsgReceived);


/***************************************************************************
 * RvSipTransactionInternalClientCreatedEv
 * ------------------------------------------------------------------------
 * General: RvSipTransactionCreatedEv() notifies the application that a new
 *          client transaction has been created by the SIP Stack. The newly
 *          created transaction always assumes the Idle state.
 *          This callback is called for CANCEL and PRACK transactions that are
 *          created automatically by the SIP Stack.RvSipTransactionCreatedEv()
 *          notifies the application that a new client transaction has been
 *          created by the SIP Stack. The newly created transaction always
 *          assumes the Idle state.
 *          This callback is called for CANCEL and PRACK transactions that are
 *          created automatically by the SIP Stack.
 *
 * Return Value: (-)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTransc     - The new SIP Stack transaction handle.
 *           pAppContext - The application context. You supply this context when
 *                        setting the event handles.
 * Output:  hAppTransc  - The application handle for the transaction.
 ***************************************************************************/
typedef void (RVCALLCONV * RvSipTransactionInternalClientCreatedEv)(
                      IN    RvSipTranscHandle        hTransc,
                      IN    void                     *pAppContext,
                      OUT   RvSipTranscOwnerHandle   *hAppTransc);

/***************************************************************************
 * RvSipTransactionSupplyTranscParamsEv
 * ------------------------------------------------------------------------
 * General: This callback is called if an internally created client transaction
 *          needs a CSeq step and a Request URI from its owner.
 *          The application should supply these parameters to the transaction.
 *          In this version, this callback is called only for PRACK client
 *          transactions.
 * Return Value: (-)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTransc      - The new SIP Stack transaction handle.
 *          hAppTransc   - The application handle for the transaction.
 * Output:  pCSeqStep    - The CSeq step for the transaction.
 *          phRequestUri - Request URI for the transaction.
 ***************************************************************************/
typedef void (RVCALLCONV * RvSipTransactionSupplyTranscParamsEv)(
                      IN    RvSipTranscHandle        hTransc,
                      IN    RvSipTranscOwnerHandle   hAppTransc,
                      OUT   RvInt32                 *pCSeqStep,
                      OUT   RvSipAddressHandle       *phRequestUri);

/***************************************************************************
 * RvSipTransactionCancelledEv
 * ------------------------------------------------------------------------
 * General: Notifies the application when a CANCEL request is received on a
 *          transaction.
 *          Note: This is not the CANCEL transaction but the cancelled
 *          transaction. For example an INVITE request that was cancelled.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTransc      - The transaction handle
 *            hTranscOwner - The application handle for this transaction.
 ***************************************************************************/
typedef RvStatus (RVCALLCONV *RvSipTransactionCancelledEv)
                     (IN RvSipTranscHandle      hTransc,
                      IN RvSipTranscOwnerHandle hTranscOwner);

/***************************************************************************
 * RvSipTransactionAuthCredentialsFoundEv
 * ------------------------------------------------------------------------
 * General:  Supply an authorization header, to pass it to the user,
 *           that will continue the authentication procedure, according to
 *           the realm and username parameters in it.
 *           in order to coninue the procedure, user shall use
 *           RvSipAuthProceed().
 *           Note - You must get the credentials from the give authorization
 *           header synchronic. when having the credentials you may check
 *           validity, and continue with RvSipAuthProceed asynchronic.
 * Return Value: (-)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTransc         - The sip stack transaction handle
 *          hAppTransc      - Application handle for the transaction
 *          hAuthorization  - Handle to the Authorization header that was found.
 *          bCredentialsSupported - TRUE if supported, FALSE elsewhere.
 ***************************************************************************/
typedef void (RVCALLCONV * RvSipTransactionAuthCredentialsFoundEv)(
                      IN    RvSipTranscHandle               hTransc,
                      IN    RvSipTranscOwnerHandle          hAppTransc,
                      IN    RvSipAuthorizationHeaderHandle  hAuthorization,
                      IN    RvBool                         bCredentialsSupported);

/***************************************************************************
 * RvSipTransactionAuthCompletedEv
 * ------------------------------------------------------------------------
 * General:  Notify that authentication procedure is completed.
 *           If it is completed because a correct authorization was found,
 *           bAuthSucceed is RV_TRUE.
 *           If it is completed because there are no more authorization headers
 *           to check, or because user ordered to stop the searching for
 *           correct header, bAuthSucceed is RV_FALSE.
 * Return Value: (-)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTransc      - The sip stack transaction handle
 *          hAppTransc   - Application handle for the transaction
 *          bAuthSucceed - RV_TRUE if we found correct authorization header,
 *                         RV_FALSE if we did not.
 ***************************************************************************/
typedef void (RVCALLCONV * RvSipTransactionAuthCompletedEv)(
                      IN    RvSipTranscHandle        hTransc,
                      IN    RvSipTranscOwnerHandle   hAppTransc,
                      IN    RvBool                  bAuthSucceed);

/***************************************************************************
 * RvSipTransactionOtherURLAddressFoundEv
 * ------------------------------------------------------------------------
 * General: Notifies the application that a message needs to be sent and
 *          the destination address is a URL type that is currently not
 *          supported by the stack. The URL has to be converted to a SIP URL
 *          for the message to be sent.
 * Return Value: RvStatus (RV_OK on success execution or RV_ERROR_UNKNOWN
 *                 otherwise).
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTransc        - The transaction handle
 *            hAppTransc     - The application handle for this transaction.
 *            hMsg           - The message that includes the other URL address.
 *            hAddress       - Handle to unsupport address to be converted.
 * Output:    hSipURLAddress - Handle to the SIP URL address - this is an empty
 *                               address object that the application should fill.
 *            bAddressResolved- RV_TRUE if the SIP URL address was filled. RV_FALSE otherwise.
 ***************************************************************************/
typedef RvStatus (RVCALLCONV * RvSipTransactionOtherURLAddressFoundEv)(
                     IN  RvSipTranscHandle      hTransc,
                     IN  RvSipTranscOwnerHandle hAppTransc,
                     IN  RvSipMsgHandle         hMsg,
                     IN  RvSipAddressHandle        hAddress,
                     OUT RvSipAddressHandle        hSipURLAddress,
                     OUT RvBool                *bAddressResolved);

/***************************************************************************
 * RvSipTransactionFinalDestResolvedEv
 * ------------------------------------------------------------------------
 * General: This callback indicates that the transaction is about to send
 *          a message after the destination address was resolved.
 *          The callback supplies the final message object.
 *          Changes in the message at this stage will
 *          not effect the destination address.
 *          When this callback is called the application can query the
 *          transaction about the destination address using the
 *          RvSipTransactionGetCurrentDestAddress() API function.
 *          If the application wishes it can update the sent-by part of
 *          the top most via. The application must not update the branch parameter.
 *
 * Return Value: RvStatus. If the application returns a value other then
 *               RV_OK the message will not be sent. The transaction will 
 *               terminate with an error.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTransc      - The transaction handle.
 *            hTranscOwner - The application handle of this transaction.
 *            hMsgToSend   - The handle to the outgoing message.
 ***************************************************************************/
typedef RvStatus (RVCALLCONV * RvSipTransactionFinalDestResolvedEv)(
                            IN RvSipTranscHandle       hTransc,
                            IN RvSipTranscOwnerHandle  hTranscOwner,
                            IN RvSipMsgHandle          hMsgToSend);

#ifdef RV_SIGCOMP_ON
/***************************************************************************
 * RvSipTransactionSigCompMsgNotRespondedEv
 * ------------------------------------------------------------------------
 * General: This callback notifies the application that the transaction timer 
 *          has expired and that the stack has not yet received a response
 *	        to a SigComp compressed request or an ACK on a SigComp compresses 
 *          response. 
 *          The callback is called in the following cases:
 *          1. Before there is a need to retransmit a compressed message.
 *             This happens when the transaction timer expires and
 *             according to RFC 3261 the stack needs to retransmit the
 *             message.
 *          2. When the sigCompTcpTimer expires. The sip stack 
 *             added a timer for SigComp TCP transmissions. When this timer
 *             expires the application can send the message again in a plain
 *             format. (According to RFC 3261 there are no retransmission in TCP).
 *             
 *          This callback is part of a recovery mechanism. The callback supplies 
 *          information about compression type that was used in the last transmission.
 *          The callback also gives the application the ability to determine if there will be
 *          additional retransmissions and the compression type of the next retransmission.
 *          For example the application can decide that the next retransmission
 *          will not be compressed.
 *          NOTE: if you set the peNextMsgComp to
 *          RVSIP_TRANSMITTER_MSG_COMP_TYPE_UNDEFINED the stack will stop
 *          the message retransmissions.
 *
 * Return Value: RvStatus. If the application returns a value other then
 *               RV_OK no further messages will be sent.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTransc       - The transaction handle.
 *            hTranscOwner  - The application handle for this transaction.
 *            retransNo     - The number of retransmissions of the request
 *                            until now.
 *            ePrevMsgComp  - The compression type that we used in the previous
 *                            retransmission.
 * Output:    peNextMsgComp - he compression type that the transaction should use
 *                            for the next retransmission.
 ***************************************************************************/
typedef RvStatus (RVCALLCONV *RvSipTransactionSigCompMsgNotRespondedEv)(
                     IN  RvSipTranscHandle            hTransc,
                     IN  RvSipTranscOwnerHandle       hTranscOwner,
                     IN  RvInt32                      retransNo,
                     IN  RvSipTransmitterMsgCompType  ePrevMsgComp,
                     OUT RvSipTransmitterMsgCompType *peNextMsgComp);
#endif /* RV_SIGCOMP_ON */

#ifndef RV_SIP_PRIMITIVES
/***************************************************************************
 * RvSipTransactionOpenCallLegEv
 * ------------------------------------------------------------------------
 * General: When a request that is suitable for opening a dialog is received
 *          (INVITE/ REFER/SUBSCRIBE—with no To tag), the Transaction layer
 *          asks the application whether to open a call-leg for this transaction.
 *          For a proxy application, the callback is called for INVITE/REFER/
 *          SUBSCRIBE methods.
 *          This function can be used by proxies that wish to handle specific
 *          requests in a call-leg context by themselves. For UA applications,
 *          the callback is called only for initial REFER/SUBSCRIBE methods.
 *          An application that does not want the Stack implementation that
 *          opens a new dialog for REFER and SUBSCRIBE should implement
 *          this callback.
 * Return Value: (-)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hTranscMgr  - The handle of the new server transaction.
 *          pAppMgr     - The application context. You supply this context
 *                        when setting the event handles.
 *          hTransc     - The handle of the new server transaction.
 * OUT:     bOpenCalled - RV_TRUE if the application wishes that the stack
 *                        will handle the transaction in a call-leg context.
 *                        RV_FALSE otherwise.
 ***************************************************************************/
typedef RvStatus (RVCALLCONV *RvSipTransactionOpenCallLegEv)
                    (IN  RvSipTranscMgrHandle    hTranscMgr,
                     IN  void                   *pAppMgr,
                     IN  RvSipTranscHandle       hTransc,
                     OUT RvBool                 *bOpenCalled);



#endif /*#ifndef RV_SIP_PRIMITIVES*/

/***************************************************************************
 * RvSipTransactionNewConnInUseEv
 * ------------------------------------------------------------------------
 * General: This callback indicates that the Transaction is now using a new
 *          connection. The connection can be a totally new connection or
 *          a suitable connection that was found in the hash.
 *
 * Return Value: RvStatus (the returned status is ignored in the current
 *                      stack version)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTransc     - The sip stack transaction handle
 *            hTranscOwner  - The owner of this transaction.
 *            hConn       - The connection handle
 *            bNewConnCreated - RV_TRUE if the connection is a newly created connection.
 *                              RV_FALSE if the connection was found in the connection hash.
 ***************************************************************************/
typedef RvStatus (RVCALLCONV *RvSipTransactionNewConnInUseEv) (
                     IN  RvSipTranscHandle              hTransc,
                     IN  RvSipTranscOwnerHandle         hTranscOwner,
                     IN  RvSipTransportConnectionHandle hConn,
                     IN  RvBool                         bNewConnCreated);
/***************************************************************************
 * RvSipTranscMgrOutOfContextMsgEv
 * ------------------------------------------------------------------------
 * General: Called when the transaction manager receives a message the does
 *          not match any existing transaction.
 *          The callback is called in the following cases:
 *          1. For a response message that does not match any client transaction.
 *          2. When ACK for 2xx response is received.
 *          3. When CANCEL is received and the canceled transaction is not found.
 *          This callback is used only for proxy applications. For user agent
 *          applications the ACK for 2xx is handles in the context of the invite
 *          transaction, responses that cannot be matched to any existing transaction
 *          are ignored and a CANCEL is responded with 481 automatically.
 * Return Value: (-)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTranscMgr - The transaction manager which received the message
 *           pAppMgr    - The application context. You supply this context
 *                       when setting the event handles.
 *          hMsg       - Received an Out of Context message.
 *          localPort  - The port from which the message was received.
 *          eLocalTransportType - The transport from which the message was received.
 *          eAddressType  - The address type(IP4 or IP6).
 *          localAddress - The local address the message was received on
 ***************************************************************************/
typedef RvStatus (RVCALLCONV *RvSipTranscMgrOutOfContextMsgEv)
                    (IN RvSipTranscMgrHandle      hTranscMgr,
                     IN void                      *pAppMgr,
                     IN RvSipMsgHandle            hMsg,
                     IN RvUint16                 localPort,
                     IN RvSipTransport            eLocalTransportType,
                     IN RvSipTransportAddressType eAddressType,
                     IN RvChar                   *strlocalAddress);

/***************************************************************************
 * RvSipTranscMgrNewRequestRcvdEv
 * ------------------------------------------------------------------------
 * General: Called when the transaction manager receives a new request that
 *          is not a retransmission and not an ACK request.
 *          The application should instruct the stack whether it should
 *          create a new transaction for the request or not.
 *          If you do not implement this callback, a new transaction
 *          will be created by default. Stateless proxies will usually want
 *          to prevent the stack from creating a new transaction.
 * Return Value: RvStatus - ignored in this version.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTranscMgr - The transaction manager that received the request.
 *           pAppMgr    - The application context. You supply this context
 *                       when setting the event handles.
 *          hMsg       - The handle to the new request message.
 * Output:  pbCreateTransc - Indicates whether the stack should handle the
 *                       new request by creating a new transaction.
 ***************************************************************************/
typedef RvStatus (RVCALLCONV *RvSipTranscMgrNewRequestRcvdEv)
                    (IN RvSipTranscMgrHandle    hTranscMgr,
                     IN void                    *pAppMgr,
                     IN RvSipMsgHandle          hMsg,
                     OUT RvBool                *pbCreateTransc);

/***************************************************************************
 * RvSipTranscMgrOtherURLAddressFoundEv
 * ------------------------------------------------------------------------
 * General: Notifies the application that an out of context message needs to be sent and
 *          the destination address is a URL type that is currently not
 *          supported by the stack. The URL has to be converted to a SIP URL
 *          for the message to be sent.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:    hTranscMgr     - The transaction manager handle.
 *           pAppMgr        - The application context.
 *           hMsg           - The handle to the new request message.
 *           hAddress       - Handle to unsupport address to be converted.
 * Output:   hSipURLAddress - Handle to the SIP URL address - this is an empty
 *                            address object that the application should fill.
 *           bAddressResolved-Indication wether the SIP URL address was filled.
 ***************************************************************************/
typedef RvStatus (RVCALLCONV * RvSipTranscMgrOtherURLAddressFoundEv)(
                     IN  RvSipTranscMgrHandle   hTranscMgr,
                     IN  void                  *pAppMgr,
                     IN  RvSipMsgHandle         hMsg,
                     IN  RvSipAddressHandle        hAddress,
                     OUT RvSipAddressHandle        hSipURLAddress,
                     OUT RvBool                *bAddressResolved);

/***************************************************************************
 * RvSipTranscMgrFinalDestResolvedEv
 * ------------------------------------------------------------------------
 * General: This callback indicates that the Transaction Manager
 *          is about to send a message after the destination
 *          address was resolved. The message was sent using the out of
 *          context mechanism of the Transaction Manager.
 *          The callback supplies the final message object, the remote
 *          address the message will be sent to and the local address the
 *          message will be sent from.
 *          Changes in the message at this stage will
 *          not effect the destination address.
 *          Using this callback the application can change the local
 *          IP and port the message will use for the supplied transport and
 *          address types.
 *          If the application wishes it can update the sent-by part of
 *          the top most via.
 *          The application must not update the branch parameter.
 *          Note: You must not lock any application object in this callback.
 *          Doing so might cause deadlocks.
 *
 * Return Value: RvStatus. If you return a value other then RV_OK the message
 *          will not be sent.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTranscMgr     - The transaction manager handle.
 *           pAppMgr        - The application context.
 *            hMsg           - The handle to the message that is about to be sent.
 *          eTransportType - The transport for the local and remote addresses
 *          eAddressType   - The address type for the local and remote addresses
 *          strDestAddress - The destination IP address
 *          destPort       - The destination port.
 * InputOutput:
 *          strLocalAddress - The local IP address the message will be sent from
 *          pLocalPort      - The local port the message will be sent from.
 ***************************************************************************/
typedef RvStatus (RVCALLCONV * RvSipTranscMgrFinalDestResolvedEv)(
                     IN    RvSipTranscMgrHandle      hTranscMgr,
                     IN    void                      *pAppMgr,
                     IN    RvSipMsgHandle            hMsg,
                     IN    RvSipTransport            eTransportType,
                     IN    RvSipTransportAddressType eAddressType,
                     IN    RvChar                   *strDestAddress,
                     IN    RvUint16                 destPort,
                     INOUT RvChar                   *strLocalAddress,
                     INOUT RvUint16                 *pLocalPort);
#ifdef RV_SIP_PRIMITIVES
/***************************************************************************
 * RvSipTransactionMgrForkedInviteResponseEv	
 * ------------------------------------------------------------------------
 * General: Called when the transaction manager receives a new 1xx/2xx response 
 *          for an INVITE request, and the response does not match any existing
 *          transaction.
 *          (This is usually the case when INVITE request was forked by proxy
 *          to several UAS, and each one of them returns 1xx and 2xx).
 *          Note: This callback is available only if the stack is compiled 
 *          with the RV_SIP_PRIMITIVES compilation flag.
 * Return Value: RV_Status - ignored in this version.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input: 	hTranscMgr   - The transaction manager that received the response.
 *   	    hResponseMsg - The handle to the received response message.
 ***************************************************************************/
typedef RvStatus (RVCALLCONV *RvSipTransactionMgrForkedInviteResponseEv)
                    (IN void*                   hTranscMgr,
					 IN RvSipMsgHandle          hResponseMsg);

#endif /*#ifdef RV_SIP_PRIMITIVES*/




/* RvSipTransactionEvHandlers
 * ------------------------------------------------------------------------
 * A structure with function pointers to the callback of the module.
 * This structure is used to set the application callbacks in the function,
 * RvSipCallLegMgrSetEvHandlers().
 *
 * pfnEvTransactionCreated  - Notifies that a new server transaction was created.
 * pfnEvStateChanged        - Notifies of a transaction state change.
 * pfnEvMsgToSend           - Notifies that a message is about to be sent.
 * pfnEvMsgReceived         - Notifies that a message was received.
 * pfnEvInternalTranscCreated - Notifies that an internal client transaction was created.
 *                          This callback is called for CANCEL and PRACK transactions
 *                          that are created automatically by the SIP Stack.
 * pfnEvTranscCancelled     - Notifies that a transaction was cancelled by an incoming
 *                          CANCEL request.
 * pfnEvSupplyParams        - Requests the application parameters for the outgoing PRACK
 *                          request. The parameters needed are the cseq step and the
 *                          request URI.
 * pfnEvDNSMsgSendFailure   - Notifies about message send failure.
 * pfnEvAuthCredentialsFound - Supplies an authorization header to the application so that
 *                          an authentication check will be performed for an incoming
 *                          request.
 * pfnEvAuthCompleted      - Notifies that the authentication procedure is completed.
 * pfnEvOpenCallLeg           - Notifies the application that a request that is suitable
 *                          for opening a dialog was received (INVITE/REFER/SUBSCRIBE—with
 *                          no To tag). The application should decide whether to open a new
 *                          dialog or handle the request above the Transaction layer.
 * pfnEvOtherURLAddressFound   - Notifies about Other URL address that was found.
 * pfnEvFinalDestResolved      - Notifies that the final destination address
 *                               of the register request was resolved.
 * pfnEvSigCompMsgNotResponded - Notifies that no response was received to the last sent
 *                               SigComp message.
 *
 */
typedef struct
{
    RvSipTransactionCreatedEv                       pfnEvTransactionCreated;
    RvSipTransactionStateChangedEv                  pfnEvStateChanged;
    RvSipTransactionMsgToSendEv                     pfnEvMsgToSend;
    RvSipTransactionMsgReceivedEv                   pfnEvMsgReceived;
    RvSipTransactionInternalClientCreatedEv         pfnEvInternalTranscCreated;
    RvSipTransactionCancelledEv                     pfnEvTranscCancelled;
    RvSipTransactionSupplyTranscParamsEv            pfnEvSupplyParams;
    RvSipTransactionAuthCredentialsFoundEv          pfnEvAuthCredentialsFound;
    RvSipTransactionAuthCompletedEv                 pfnEvAuthCompleted;
#ifndef RV_SIP_PRIMITIVES
    RvSipTransactionOpenCallLegEv                   pfnEvOpenCallLeg;
#endif /* #ifndef RV_SIP_PRIMITIVES*/
    RvSipTransactionOtherURLAddressFoundEv          pfnEvOtherURLAddressFound;
    RvSipTransactionFinalDestResolvedEv             pfnEvFinalDestResolved;
    RvSipTransactionNewConnInUseEv                  pfnEvNewConnInUse;
#ifdef RV_SIP_PRIMITIVES
    RvSipTransactionMgrForkedInviteResponseEv       pfnEvForkedInviteRespRcvd;
#endif /*#ifdef RV_SIP_PRIMITIVES*/
#ifdef RV_SIGCOMP_ON
    RvSipTransactionSigCompMsgNotRespondedEv        pfnEvSigCompMsgNotResponded;
#endif
} RvSipTransactionEvHandlers;

/* RvSipTransactionProxyEvHandlers
 * ------------------------------------------------------------------------
 * A structure with function pointers to the proxy-related call-back.
 * This structure is used to set the proxy application call-backs in the function,
 * RvSipTransactionMgrSetProxyEvHandlers().
 *
 * RvSipTransactionOutOfContextMsg  - Notifies the proxy about reception of an
 *                                  Out of Context message.
 * pfnEvNewRequestRcvd              - Notifies the proxy when a new request is
 *                                  received. The proxy has to determine whether or
 *                                  not to open a new transaction for that request.
 * pfnEvOtherURLAddressFound        - Notifies the application that other URL address
 *                                    was found and has to be converted to known SIP
 *                                    URL address.
 * pfnEvFinalDestResolved
 */
typedef struct
{
    RvSipTranscMgrOutOfContextMsgEv         pfnEvOutOfContextMsg;
    RvSipTranscMgrNewRequestRcvdEv          pfnEvNewRequestRcvd;
    RvSipTranscMgrOtherURLAddressFoundEv    pfnEvOtherURLAddressFound;
    RvSipTranscMgrFinalDestResolvedEv       pfnEvFinalDestResolved;
}RvSipTransactionProxyEvHandlers;

#ifdef __cplusplus
}
#endif

#endif /* END OF: #ifndef RVSIP_TRANSACTION_TYPES_H */


