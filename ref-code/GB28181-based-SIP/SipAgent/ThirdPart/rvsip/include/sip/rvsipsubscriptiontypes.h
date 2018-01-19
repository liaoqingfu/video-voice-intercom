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
*                     <RvSipSubscriptionTypes.h>
*
* The RvSipSubscriptionTypes.h file contains all type definitions and
* call-back functions type definitions for the subscription module.
*
* includes:
* 1.Handle Type definitions
* 2.subscription Type definitions
* 3.subscription callback functions
* 4.notification type definitions
* 5.notification callback functions
*
*
*    Author                         Date
*    ------                        ------
*    Ofra Wachsman                  June 2002
*********************************************************************************/


#ifndef RV_SIP_SUBSCRIPTION_TYPES_H
#define RV_SIP_SUBSCRIPTION_TYPES_H

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


	/*-----------------------------------------------------------------------*/
	/*                     COMMON TYPE DEFINITIONS                           */
	/*-----------------------------------------------------------------------*/

	/*
	* RvSipSubsMgrHandle
	* ---------------------------------------------------------------------------
	* Declaration of handle to a Subscription Manager instance. The manager object
	* manages all the module subscriptions and its handle is needed in all manager
	* related API such as creation of new subscriptions.
	*/
	RV_DECLARE_HANDLE(RvSipSubsMgrHandle);


	/*
	* RvSipSubsHandle
	* ---------------------------------------------------------------------------
	* Declaration of a Subscription handle. Subscription is needed in all Subscription
	* API functions and is used to reference the correct subscription object.
	*/
	RV_DECLARE_HANDLE(RvSipSubsHandle);


	/*
	* RvSipAppSubsHandle
	* ---------------------------------------------------------------------------
	* Declaration of application handle to a Subscription. This handle is used by the
	* application in order to associate sip stack subscription objects with application
	* subscription object. The application gives the application handle when
	* a new subscription is created. The sip stack will give this handle back to the
	* application in every callback function.
	*/

	RV_DECLARE_HANDLE(RvSipAppSubsHandle);

	/*
	* RvSipNotifyHandle
	* ---------------------------------------------------------------------------
	* Declaration of a Notification handle. Notification is needed in all notification
	* API functions and is used to reference the correct notification object.
	*/
	RV_DECLARE_HANDLE(RvSipNotifyHandle);


	/*
	* RvSipAppNotifyHandle
	* ---------------------------------------------------------------------------
	* Declaration of application handle to a Notification. This handle is used by the
	* application in order to associate sip stack notification objects with application
	* notification object. The application gives the application handle when
	* a new notification is created. The sip stack will give this handle back to the
	* application in every callback function.
	*/

	RV_DECLARE_HANDLE(RvSipAppNotifyHandle);




	/*-----------------------------------------------------------------------*/
	/*                    SUBSCRIPTION TYPE DEFINITIONS                      */
	/*-----------------------------------------------------------------------*/


	/* RvSipSubsState
	* ----------------------------------------------------------------------
	* RvSipSubsState represents a state in a subscription. The state changes
	* are reported using the RvSipSubsStateChangedEv call back function
	* together with a state change reason that may indicate to the application
	* how the new state was reached
	*
	*  Subscriber States:
	*    RVSIP_SUBS_STATE_SUBS_SENT - After calling Subscribe() and sending an initial SUBSCRIBE,
	*                       the subscription enters the Subs-Sent state.
	*                       The subscription remains in this state until it receives
	*                       a final response from the notifier.
	*                       If 2xx class response is received, the subscription assumes
	*                       the Subs-2xx-rcvd state. If 3xx class response is received,
	*                       the subscription moves to the Redirected state. If the
	*                       subscription is rejected with a 401 or 407 response is
	*                       received, the subscription moves to the Unauthenticated state.
	*                       For all other response codes, subscription assumes the
	*                       Terminated state. If a NOTIFY request is received before
	*                       2xx response is received, the subscription assumes the
	*                       Notify-Before-2xx-Rcvd state.
	*
	*    RVSIP_SUBS_STATE_REDIRECTED - A subscription in the Subs-Sent state may receive a 3xx
	*                       class response. In this case, the subscription assumes
	*                       the Redirected state. At this point, you may confirm the
	*                       redirection by calling the Subscribe() function again.
	*                       You can also decide to terminate the subscription using
	*                       the Terminate() function.
	*
	*    RVSIP_SUBS_STATE_UNAUTHENTICATED - A subscription in the Subs-Sent state may receive
	*                       401 or 407 response. In this case, the subscription assumes
	*                       the Unauthenticated state. At this point, you may re-send
	*                       your request with authentication information by calling
	*                       the Subscribe() function again. You can also terminate
	*                       the call using the Terminate() function.
	*
	*    RVSIP_SUBS_STATE_2XX_RCVD - Upon receipt a 2xx response to an initial SUBSCRIBE
	*                       request, the SIP Stack will assumes the 2xx-rcvd state.
	*                       The subscription remains in this state until it receives
	*                       and accept a NOTIFY request from the notifier. SIP Stack set a timer,
	*                       at this state (called no-notify-timer), if this timer
	*                       expires before the notify request is received, the subscription
	*                       assumes the Terminated state.
	*                       When the notify request is received and accepted by application,
	*                       the subscription assumes the Active or Pending state
	*                       (according to the subscription-state header in notify request).
	*
	*    RVSIP_SUBS_STATE_NOTIFY_BEFORE_2XX_RCVD - If a notify request is received and accepted,
	*                       while subscription is in state Subs-Sent, the SIP Stack assumes
	*                       the Notify-before-2xx-rcvd state. When subscription receives
	*                       the 2xx response on the subscribe request, it will assume
	*                       the Active or Pending state (according to 200 or 202 response).
	*
	*    RVSIP_SUBS_STATE_REFRESHING - A Subscriber subscription in Active state may call Refresh()
	*                       function to send a Refresh subscribe request. After sending
	*                       the refresh, subscription enters the Refreshing state.
	*                       The subscription remains in this state until it receives a
	*                       final response from the notifier.
	*                       If 2xx class response is received, the subscription set the
	*                       subscription timer to the new value that both subscriber and
	*                       notifier had agreed on in the refresh message and 2xx response.
	*                       If a non-2xx response is received, the subscription timer
	*                       remains as it was.
	*                       For both cases, when a response is received for the refresh
	*                       request,  subscription assumes the Active state.
	*    RVSIP_SUBS_STATE_UNSUBSCRIBING - A Subscriber subscription may call Unsubscribe()
	*                       function to send an unsubscribe request. After sending the unsubscribe,
	*                       subscription enters the unsubscribing state. The subscription
	*                       remains in this state until it receives a final response from
	*                       the notifier.
	*                       If 2xx class response is received, subscription assumes the
	*                       Unsubscribe-2xx-Rcvd state, for waiting to the notify request
	*                       that terminates the subscription.
	*                       If a non-2xx response is received, Subscription assumes the
	*                       previous state (the state before sending the unsubscribe request).
	*
	*    RVSIP_SUBS_STATE_UNSUBSCRIBE_2XX_RCVD - Upon receipt a 2xx class response on an unsubscribe
	*                       request, subscription assumes the Unsubscribe-2xx-Rcvd state.
	*                       The subscription remains in this state until it receives a
	*                       notify request from the notifier with 'Subscription-State:Terminated'
	*                       header in it. SIP Stack set a timer, at this state (called
	*                       no-notify-timer), if this timer expires before the notify
	*                       request is received, the subscription assumes the Terminated state.
	*
	*  RVSIP_SUBS_STATE_MSG_SEND_FAILURE - failed to send a subscribe request, because of a
	*                       timeout, network error, or 503 response. Application may try to
	*                       re-send the request to the next ip address in the DNS list.
	*
	*  Notifier States:
	*    RVSIP_SUBS_STATE_SUBS_RCVD - Upon receipt of the initial SUBSCRIBE by a notifier
	*                        subscription, the subscription assumes the Subs-Rcvd state.
	*                        In this state, it is up to the application to decide whether
	*                        to accept or reject the subscription using the subscription API.
	*                        If application accept the SUBSCRIBE request with 200 response,
	*                        it must immediately send a notify(active) request.
	*                        If application accept-pending the SUBSCRIBE request with 202 response,
	*                        it must immediately send a notify(pending) request.
	*
	*    RVSIP_SUBS_STATE_ACTIVATED - When a notifier subscription wants to move from state
	*                         pending to state active, it sends a notify request with
	*                        'Subscription-State:active" header in it.
	*                         When sending it the subscription assumes the Activated state.
	*                         When notifier receives the 2xx response for this notify
	*                         request, the subscription assumes the Active state.
	*                         If notifier receives non-2xx response for this notify request,
	*                         it remains in state Activated.
	*
	*    RVSIP_SUBS_STATE_REFRESH_RCVD - Upon receipt of a refresh SUBSCRIBE by a notifier subscription,
	*                         the subscription assumes the Refresh-Rcvd state.
	*                         In this state, it is up to the application to decide whether
	*                         to accept or reject the subscription refreshing using the
	*                         subscription API.
	*
	*    RVSIP_SUBS_STATE_UNSUBSCRIBE_RCVD - Upon receipt of an UNSUBSCRIBE by a notifier subscription,
	*                         the subscription assumes the Unsubscribe-Rcvd state. In this
	*                         state, it is up to the application to decide whether to accept
	*                         or reject the unsubscribe request using the subscription API.
	*                         If application reject the request, the subscription assumes
	*                         the previous state (state before receiving the unsubscribe
	*                         request). If application accept the request, it must immediately
	*                         send a Notify request with 'Subscription-State:Terminated'
	*                         header in it. When sending this notify request subscription
	*                         assumes the Terminating state.
	*
	*    RVSIP_SUBS_STATE_TERMINATING - When a notifier subscription sends a notify request with
	*                         'Subscription-State: terminated" header in it, the subscription
	*                         assumes the Terminating state. When notifier receives the
	*                         2xx response for this notify request, the subscription assumes
	*                         the Terminated state. If notifier receives non-2xx response
	*                         for this notify request, it remains in state Terminating.
	*
	*  Common States:
	*    RVSIP_SUBS_STATE_IDLE - The Idle state is the initial state of the subscription
	*                         state machine. Upon subscription creation, the subscription
	*                         assumes the Idle state. It remains in this state until
	*                         Subscribe() is called, whereupon it changes to the
	*                         Subs-Sent state.
	*
	*    RVSIP_SUBS_STATE_PENDING - The pending state indicates that the initial subscribe
	*                         request has been received and understood, but the subscription
	*                         is not necessarily has been authorized yet.
	*                         A subscriber subscription reaches this state when 202 final
	*                         response is received for initial subscribe request, and a
	*                         notify request with pending Subscription-State is received
	*                         and accepted.
	*                         A notifier subscription reaches this state when a 202
	*                         final response is sent for an initial subscribe request.
	*
	*    RVSIP_SUBS_STATE_ACTIVE - The subscription is active. This state indicates a successful
	*                         subscription establishment.
	*                         A subscriber subscription reaches this state when 2xx final
	*                         response is received for initial subscribe request, and a
	*                         notify request with active Subscription-State is received
	*                         and accepted.
	*                         A notifier subscription reaches this state when a 200 final
	*                         response is sent for an initial subscribe request, or when
	*                         2xx response is received for a notify request with active
	*                         Subscription-State, which was sent on pending state.
	*
	*    RVSIP_SUBS_STATE_TERMINATED - This state is the final subscription state. When a subscription
	*                         is terminated, it assumes the Terminated state. Upon reaching
	*                         the Terminated state, you can no longer reference the subscription
	*                         object using the subscription API function.
	*
	*/
	typedef enum
	{
		RVSIP_SUBS_STATE_UNDEFINED = -1,
		RVSIP_SUBS_STATE_IDLE,
		RVSIP_SUBS_STATE_SUBS_SENT,
		RVSIP_SUBS_STATE_REDIRECTED,
		RVSIP_SUBS_STATE_UNAUTHENTICATED,
		RVSIP_SUBS_STATE_2XX_RCVD,
		RVSIP_SUBS_STATE_NOTIFY_BEFORE_2XX_RCVD,
		RVSIP_SUBS_STATE_REFRESHING,
		RVSIP_SUBS_STATE_REFRESH_RCVD,
		RVSIP_SUBS_STATE_UNSUBSCRIBING,
		RVSIP_SUBS_STATE_UNSUBSCRIBE_RCVD,
		RVSIP_SUBS_STATE_UNSUBSCRIBE_2XX_RCVD,
		RVSIP_SUBS_STATE_SUBS_RCVD,
		RVSIP_SUBS_STATE_ACTIVATED,
		RVSIP_SUBS_STATE_TERMINATING,
		RVSIP_SUBS_STATE_PENDING,
		RVSIP_SUBS_STATE_ACTIVE,
		RVSIP_SUBS_STATE_MSG_SEND_FAILURE,
		RVSIP_SUBS_STATE_TERMINATED
	} RvSipSubsState;



	/* RvSipSubsStateChangeReason
	* ------------------------------------------------------------------
	* A subscription object has an inner state. The state changes according
	* to the state machine defined for the subscription. Each state change
	* is explained by one of the reasons enumerated bellow.
	*
	* RVSIP_SUBS_REASON_UNDEFINED          - The reason is undefined. this reason is used
	*                                      when there is no need of extra information (for
	*                                      example - state SUBS_RCVD with reason UNDEFINED,
	*                                      means that initial subscribe request was received...)
	* RVSIP_SUBS_REASON_LOCAL_REJECT       - The local party rejected the subscription.
	* RVSIP_SUBS_REASON_LOCAL_FAILURE      - The local party failed. For example it failed to
	*                                      encode the message while sending a request.
	* RVSIP_SUBS_REASON_REMOTE_REJECT      - The remote party rejected the request with 4xx-6xx response,
	*                                      (different than 401, 407 or 481).
	* RVSIP_SUBS_REASON_481_RCVD           - 481 response was received.
	* RVSIP_SUBS_REASON_UNAUTHENTICATED    - 401/407 response was received (for initial or refresh subscribe).
	* RVSIP_SUBS_REASON_UNSUBSCRIBE_UNAUTHENTICATED - 401/407 response was received on unsubscribe request.
	* RVSIP_SUBS_REASON_UNSUBSCRIBE_REJECTED - reject response was received on unsubscribe request.
	* RVSIP_SUBS_REASON_NO_NOTIFY_TIME_OUT - NoNotify timer was expired. (it means that a notify
	*                                        request was not accepted. this timer is set after receiveing
	*                                        2xx on initial subscribe, or on unsubscribe).
	* RVSIP_SUBS_REASON_TRANSC_TIME_OUT    - Transaction timeout occurred.
	* RVSIP_SUBS_REASON_TRANSC_ERROR       - Transaction error occurred.
	* RVSIP_SUBS_REASON_NO_TIMERS          - There are no more timers to set.
	* RVSIP_SUBS_REASON_NETWORK_ERROR      - Network error occurred.
	* RVSIP_SUBS_REASON_503_RECEIVED       - 503 response was received.
	* RVSIP_SUBS_REASON_GIVE_UP_DNS        - local user called the DNSGiveUp function.
	* RVSIP_SUBS_REASON_CONTINUE_DNS       - local user called the DNSContinue function.
	* RVSIP_SUBS_REASON_NOTIFY_ACTIVE_SENT - Notify(active) request with was sent.
	* RVSIP_SUBS_REASON_NOTIFY_TERMINATED_SENT - Notify(terminated) request was sent.
	* RVSIP_SUBS_REASON_NOTIFY_TERMINATED_DEACTIVATED_RCVD - Notify(terminated) request with reason
	*                                      'deactivated' was received.
	* RVSIP_SUBS_REASON_NOTIFY_TERMINATED_PROBATION_RCVD - Notify(terminated) request with reason
	*                                      'probation' was received.
	* RVSIP_SUBS_REASON_NOTIFY_TERMINATED_REJECTED_RCVD - Notify(terminated) request with reason
	*                                      'rejected' was received.
	* RVSIP_SUBS_REASON_NOTIFY_TERMINATED_TIMEOUT_RCVD - Notify(terminated) request with reason
	*                                      'timeout' was received.
	* RVSIP_SUBS_REASON_NOTIFY_TERMINATED_GIVEUP_RCVD - Notify(terminated) request with reason
	*                                      'giveup' was received.
	* RVSIP_SUBS_REASON_NOTIFY_TERMINATED_NORESOURCE_RCVD - Notify(terminated) request with reason
	*                                      'no resource' was received.
	* RVSIP_SUBS_REASON_NOTIFY_2XX_SENT    - 2xx response for Notify request was sent.
	* RVSIP_SUBS_REASON_NOTIFY_2XX_RCVD    - 2xx for Notify request was received.
	* RVSIP_SUBS_REASON_SUBS_TERMINATED    - Subscription is terminated.
	* RVSIP_SUBS_REASON_DIALOG_TERMINATION - the subscription dialog was terminated.
	* RVSIP_SUBS_REASON_REFER_RCVD         - REFER request was received.
	* RVSIP_SUBS_REASON_REFER_RCVD_WITH_REPLACES - REFER request that contains a Replaces header
	*                                        was received.
	* RVSIP_SUBS_REASON_ILLEGAL_REFER_MSG  - illegal REFER request was received. this causes
	*                                        the subscription termination.
	*/
	typedef enum
	{
		RVSIP_SUBS_REASON_UNDEFINED = -1,
		RVSIP_SUBS_REASON_LOCAL_REJECT,
		RVSIP_SUBS_REASON_LOCAL_FAILURE,
		RVSIP_SUBS_REASON_REMOTE_REJECT,
		RVSIP_SUBS_REASON_481_RCVD,
		RVSIP_SUBS_REASON_UNAUTHENTICATED,
		RVSIP_SUBS_REASON_UNSUBSCRIBE_UNAUTHENTICATED, /*5*/
		RVSIP_SUBS_REASON_UNSUBSCRIBE_REJECTED,
		RVSIP_SUBS_REASON_NO_NOTIFY_TIME_OUT,
		RVSIP_SUBS_REASON_TRANSC_TIME_OUT,
		RVSIP_SUBS_REASON_TRANSC_ERROR,
		RVSIP_SUBS_REASON_NO_TIMERS, /*10*/
		RVSIP_SUBS_REASON_NETWORK_ERROR,
		RVSIP_SUBS_REASON_503_RECEIVED,
		RVSIP_SUBS_REASON_GIVE_UP_DNS,
		RVSIP_SUBS_REASON_CONTINUE_DNS,
		RVSIP_SUBS_REASON_NOTIFY_ACTIVE_SENT, /*15 */
		RVSIP_SUBS_REASON_NOTIFY_TERMINATED_SENT,
		RVSIP_SUBS_REASON_NOTIFY_TERMINATED_DEACTIVATED_RCVD,
		RVSIP_SUBS_REASON_NOTIFY_TERMINATED_PROBATION_RCVD,
		RVSIP_SUBS_REASON_NOTIFY_TERMINATED_REJECTED_RCVD,
		RVSIP_SUBS_REASON_NOTIFY_TERMINATED_TIMEOUT_RCVD, /*20*/
		RVSIP_SUBS_REASON_NOTIFY_TERMINATED_GIVEUP_RCVD,
		RVSIP_SUBS_REASON_NOTIFY_TERMINATED_NORESOURCE_RCVD,
		RVSIP_SUBS_REASON_NOTIFY_2XX_SENT,
		RVSIP_SUBS_REASON_NOTIFY_2XX_RCVD,
		RVSIP_SUBS_REASON_SUBS_TERMINATED, /*25*/
		RVSIP_SUBS_REASON_DIALOG_TERMINATION,
		RVSIP_SUBS_REASON_REFER_RCVD,
		RVSIP_SUBS_REASON_REFER_RCVD_WITH_REPLACES,
		RVSIP_SUBS_REASON_ILLEGAL_REFER_MSG
	} RvSipSubsStateChangeReason;

	/* RvSipSubscriptionType
	* ------------------------------------------------------------------
	* Indicates whether the subscription represents a subscriber or a
	* notifier subscription.
	*/
	typedef enum
	{
		RVSIP_SUBS_TYPE_UNDEFINED = -1,
		RVSIP_SUBS_TYPE_SUBSCRIBER,
		RVSIP_SUBS_TYPE_NOTIFIER
	}RvSipSubscriptionType;



	/* RvSipSubsNotifyStatus
	------------------------------------------------------------------
	Enumeration of a notification object status. (used in RvSipSubsNotifyEv)
	*  RVSIP_SUBS_NOTIFY_STATUS_REQUEST_RCVD -
	Upon receipt of a NOTIFY request by a subscriber subscription, the notification
	object informs of the Request-Rcvd status. In this state, it is up to the application
	to decide whether to accept or reject the notify using the subscription notify API.

	*  RVSIP_SUBS_NOTIFY_STATUS_REDIRECTED -
	Upon receipt a 3xx response to a NOTIFY request, the notification object informs the
	Redirected status. At this stage, application may get needed information from the 3xx
	message. After that, the notification object is terminated and inform the Terminated status.

	*  RVSIP_SUBS_NOTIFY_STATUS_UNAUTHENTICATED -
	Upon receipt a 401/407 response to a NOTIFY request, the notification object inform
	the Unauthenticated status. At this stage, application may get needed information from
	the response message. After that, the notification object is terminated and
	inform of the Terminated status.

	*  RVSIP_SUBS_NOTIFY_STATUS_REJECT_RCVD -
	Upon receipt a non-2xx response to a NOTIFY request, the notification object inform of the
	Reject-Rcvd status. At this stage, application may get needed information from the response
	message. After that, the notification object is terminated and inform of the Terminated status.

	*  RVSIP_SUBS_NOTIFY_STATUS_2XX_RCVD -
	Upon receipt a 2xx response to a NOTIFY request, the notification object inform of the
	2xx-rcvd status. At this stage, application may get needed information from the 2xx message.
	After that, the notification object is terminated and inform of the Terminated status.

	*  RVSIP_SUBS_NOTIFY_STATUS_MSG_SEND_FAILURE -
	A notifier who failed to send a notify request (receives a 503 response, transaction timeout
	or network error) informs the Msg-Send-Failure status. At this stage application has to
	decide whether to re-send this message to the next ip address from the DNS list, or to give
	up sending this message.
	If application gives up, the notification object is terminated (and informs the
	Terminated status).
	If application re-sends the request to next ip address, the SIP Stack use the same
	notification object to re-send the notify request.

	*  RVSIP_SUBS_NOTIFY_STATUS_TERMINATED -
	This status is the final notification object. Upon reaching the Terminated state,
	you can no longer reference the notification object .

	*  RVSIP_SUBS_NOTIFY_STATUS_IDLE -
	This status is the initial status of a notification object.

	*  RVSIP_SUBS_NOTIFY_STATUS_REQUEST_SENT -
	Upon sending a NOTIFY request, the notification object inform of the
	Request-Sent status. At this stage, notification object waits for a response.

	*  RVSIP_SUBS_NOTIFY_STATUS_FINAL_RESPONSE_SENT -
	Upon sending a NOTIFY response, the notification object inform of the
	Final-Response-Sent status.
	After that, the notification object is terminated and inform of the Terminated status.
	*/
	typedef enum
	{
		RVSIP_SUBS_NOTIFY_STATUS_UNDEFINED = -1,
		RVSIP_SUBS_NOTIFY_STATUS_IDLE,
		RVSIP_SUBS_NOTIFY_STATUS_REQUEST_RCVD,
		RVSIP_SUBS_NOTIFY_STATUS_2XX_RCVD,
		RVSIP_SUBS_NOTIFY_STATUS_REJECT_RCVD,
		RVSIP_SUBS_NOTIFY_STATUS_REDIRECTED,
		RVSIP_SUBS_NOTIFY_STATUS_UNAUTHENTICATED,
		RVSIP_SUBS_NOTIFY_STATUS_TERMINATED,
		RVSIP_SUBS_NOTIFY_STATUS_MSG_SEND_FAILURE,
		RVSIP_SUBS_NOTIFY_STATUS_REQUEST_SENT,
		RVSIP_SUBS_NOTIFY_STATUS_FINAL_RESPONSE_SENT
	}RvSipSubsNotifyStatus;

	/* RvSipSubsNotifyReason
	* ------------------------------------------------------------------
	* Enumeration of reasons for notification object status. (used in RvSipSubsNotifyEv)
	*
	* RVSIP_SUBS_NOTIFY_REASON_UNDEFINED       - The reason is undefined (this reason is used when there
	*                                          is no extra information. (for example: status is
	*                                          notify request received, and reason is undefined.)
	* RVSIP_SUBS_NOTIFY_REASON_SUBS_TERMINATED - The notification object is terminated, because
	*                                            it's subscription object was terminated.
	* RVSIP_SUBS_NOTIFY_REASON_TRANSC_TIMEOUT  - A timeout of the notify request
	* RVSIP_SUBS_NOTIFY_REASON_TRANSC_ERROR    - Transaction error occured.
	* RVSIP_SUBS_NOTIFY_REASON_NETWORK_ERROR   - Network error occured.
	* RVSIP_SUBS_NOTIFY_REASON_503_RECEIVED    - 503 response was received.
	* RVSIP_SUBS_NOTIFY_REASON_GIVE_UP_DNS     - Local application called to DNSGiveup function.
	* RVSIP_SUBS_NOTIFY_REASON_CONTINUE_DNS    - Local application called to DNSContinue function.
	* RVSIP_SUBS_NOTIFY_REASON_APP_COMMAND     - The reason is application command (application called
	*                                            to RvSipNotifyTerminate() for example).
	* RVSIP_SUBS_NOTIFY_REASON_BAD_REQUEST_MESSAGE - The incoming request message was wrong
	*                                            (e.g missing Subscription-state header)
	* RVSIP_SUBS_NOTIFY_REASON_REFER_NO_SUBSCRIPTION_STATE_HEADER - a NOTIFY request on refer
	*                                             subscription was received without a Subscription-
	*                                             state header in it. This may happen when remote
	*                                             party supports an old version of refer.
	*                                             recommended behavior is to accept this notify
	*                                             request, and terminate the refer subscription.
	* RVSIP_SUBS_NOTIFY_REASON_REFER_NO_EXPIRES_IN_FIRST_NOTIFY - a first NOTIFY request on refer
	*                                             subscription was received without an expires
	*                                             parameter in it. This may happen when remote
	*                                             party supports an old version of refer.
	*                                             recommended behavior is to accept this notify
	*                                             request, and terminate the refer subscription.
	*

	*/
	typedef enum
	{
		RVSIP_SUBS_NOTIFY_REASON_UNDEFINED = -1,
		RVSIP_SUBS_NOTIFY_REASON_SUBS_TERMINATED,
		RVSIP_SUBS_NOTIFY_REASON_TRANSC_TIMEOUT,
		RVSIP_SUBS_NOTIFY_REASON_TRANSC_ERROR,
		RVSIP_SUBS_NOTIFY_REASON_NETWORK_ERROR,
		RVSIP_SUBS_NOTIFY_REASON_503_RECEIVED,
		RVSIP_SUBS_NOTIFY_REASON_GIVE_UP_DNS,
		RVSIP_SUBS_NOTIFY_REASON_CONTINUE_DNS,
		RVSIP_SUBS_NOTIFY_REASON_APP_COMMAND,
		RVSIP_SUBS_NOTIFY_REASON_BAD_REQUEST_MESSAGE,
		RVSIP_SUBS_NOTIFY_REASON_REFER_NO_SUBSCRIPTION_STATE_HEADER,
		RVSIP_SUBS_NOTIFY_REASON_REFER_NO_EXPIRES_IN_FIRST_NOTIFY
	}RvSipSubsNotifyReason;

	/* RvSipSubsEventPackageType
	* -----------------------
	* Enumeration of type of subscription event package.
	* RVSIP_SUBS_EVENT_PACKAGE_TYPE_UNDEFINED  - The event package is undefined.
	* RVSIP_SUBS_EVENT_PACKAGE_TYPE_REFER      - The event package is refer package.
	* RVSIP_SUBS_EVENT_PACKAGE_TYPE_OTHER      - The event package is other package.
	*/
	typedef enum
	{
		RVSIP_SUBS_EVENT_PACKAGE_TYPE_UNDEFINED = -1,
		RVSIP_SUBS_EVENT_PACKAGE_TYPE_REFER,
		RVSIP_SUBS_EVENT_PACKAGE_TYPE_OTHER
	}RvSipSubsEventPackageType;

	/* RvSipSubsReferNotifyReadyReason
	* -----------------------
	* enumeration of the reasons for RvSipSubsReferNotifyReadyEv event to be called.
	* (This identify what caused the decision, that a NOTIFY request should be sent).
	* RVSIP_SUBS_REFER_NOTIFY_READY_REASON_UNDEFINED - The reason is undefined.
	* RVSIP_SUBS_REFER_NOTIFY_READY_REASON_INITIAL_NOTIFY - Initial notify should be
	*                          sent after accepting the refer request.
	* RVSIP_SUBS_REFER_NOTIFY_READY_REASON_1XX_RESPONSE_MSG_RCVD - 1xx response was
	*                          received on the refer subscription associated object.
	* RVSIP_SUBS_REFER_NOTIFY_READY_REASON_FINAL_RESPONSE_MSG_RCVD - final response was
	*                          received on the refer subscription associated object.
	* RVSIP_SUBS_REFER_NOTIFY_READY_REASON_TIMEOUT - timeout on the request of
	*                          the refer subscription associated object.
	* RVSIP_SUBS_REFER_NOTIFY_READY_REASON_ERROR_TERMINATION - error termination of
	*                          the refer subscription associated object (mostly lack
	*                          of resources problem).
	* RVSIP_SUBS_REFER_NOTIFY_READY_REASON_OBJ_TERMINATED - Application terminated the
	*                          object created by refer attempt.
	* RVSIP_SUBS_REFER_NOTIFY_READY_REASON_UNSUPPORTED_AUTH_PARAMS - connect/subscribe/refer
	*                          attempt received 401/407 response, with unsupported
	*                          authentication parameters.
	*/
	typedef enum
	{
		RVSIP_SUBS_REFER_NOTIFY_READY_REASON_UNDEFINED = -1,
		RVSIP_SUBS_REFER_NOTIFY_READY_REASON_INITIAL_NOTIFY,
		RVSIP_SUBS_REFER_NOTIFY_READY_REASON_1XX_RESPONSE_MSG_RCVD,
		RVSIP_SUBS_REFER_NOTIFY_READY_REASON_FINAL_RESPONSE_MSG_RCVD,
		RVSIP_SUBS_REFER_NOTIFY_READY_REASON_TIMEOUT,
		RVSIP_SUBS_REFER_NOTIFY_READY_REASON_ERROR_TERMINATION,
		RVSIP_SUBS_REFER_NOTIFY_READY_REASON_OBJ_TERMINATED,
		RVSIP_SUBS_REFER_NOTIFY_READY_REASON_UNSUPPORTED_AUTH_PARAMS
	}RvSipSubsReferNotifyReadyReason;
	/*-----------------------------------------------------------------------
	S U B S C R I P T I O N :  C A L L - B A C K  F U N C T I O N S
	------------------------------------------------------------------------*/

	/***************************************************************************
	* RvSipSubsCreatedEv
	* ------------------------------------------------------------------------
	* General:  Indicates that a new subscription was created, and exchanges
	*           handles with the application.
	*           if the subscription is related to an already exist call-leg,
	*           hCallLeg and hAppCallLeg parameters contains this call-leg handles.
	*           If it is an independent subscription - both hCallLeg and hAppCallLeg
	*           contains NULL values.
	* Return Value: (-)
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hSubs     - The new sip stack subscription handle
	*          hCallLeg  - Handle to the related call-leg. NULL if this is a subscription
	*                      outside of a call-leg.
	*          hAppCallLeg - Handle to the related application call-leg. NULL if this is a
	*                      subscription outside of a call-leg.
	* Output:     phAppSubs - The application handle for this subscription.
	***************************************************************************/
	typedef void
		(RVCALLCONV * RvSipSubsCreatedEv)(
		IN  RvSipSubsHandle    hSubs,
		IN  RvSipCallLegHandle hCallLeg,
		IN  RvSipAppCallLegHandle hAppCallLeg,
		OUT RvSipAppSubsHandle *phAppSubs);

	/***************************************************************************
	* RvSipSubsStateChangedEv
	* ------------------------------------------------------------------------
	* General: Indicates the application of a subscription state change.
	*          For each state change the new state is supplied and the
	*          reason for the state change is also given.
	* Return Value: (-)
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hSubs    - The sip stack subscription handle
	*            hAppSubs - The application handle for this subscription.
	*            eState   - The new subscription state.
	*            eReason  - The reason for the state change.
	***************************************************************************/
	typedef void
		(RVCALLCONV * RvSipSubsStateChangedEv)(
		IN  RvSipSubsHandle            hSubs,
		IN  RvSipAppSubsHandle         hAppSubs,
		IN  RvSipSubsState             eState,
		IN  RvSipSubsStateChangeReason eReason);

	/***************************************************************************
	* RvSipSubsSubscriptionExpiredEv
	* ------------------------------------------------------------------------
	* General: Indicates application of subscription expiration.
	*          Notifier application should send a Notify(terminated) request,
	*          to move to Subs-Terminating state.
	*          Subscriber application may try to send a refresh request.
	* Return Value: (-)
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hSubs    - The sip stack subscription handle
	*            hAppSubs - The application handle for this subscription.
	***************************************************************************/
	typedef void
		(RVCALLCONV * RvSipSubsSubscriptionExpiredEv)(
		IN  RvSipSubsHandle            hSubs,
		IN  RvSipAppSubsHandle         hAppSubs);


	/***************************************************************************
	* RvSipSubsExpirationAlertEv
	* ------------------------------------------------------------------------
	* General: Alert application that the subscription timer is about to be expired.
	*          Application should use this callback to send a refresh.
	*          The time interval for the subscription alert,
	*          is set with a configuration parameter 'subsAlertTimer'.
	*          (if subsAlertTimer was set to 0, or if subsAutoRefresh was set
	*          to true, this callback function will not be called).
	* Return Value: (-)
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hSubs    - The sip stack subscription handle
	*            hAppSubs - The application handle for this subscription.
	***************************************************************************/
	typedef void
		(RVCALLCONV * RvSipSubsExpirationAlertEv)(
		IN  RvSipSubsHandle            hSubs,
		IN  RvSipAppSubsHandle         hAppSubs);

	/*-----------------------------------------------------------------------
	N O T I F I C A T I O N :  C A L L - B A C K    F U N C T I O N S
	------------------------------------------------------------------------*/

	/***************************************************************************
	* RvSipSubsNotifyCreatedEv
	* ------------------------------------------------------------------------
	* General:  Indicates that a new notification was created, and exchanges
	*           handles with the application.
	* Return Value: (-)
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hSubs         - The sip stack subscription handle
	*            hAppSubs      - The application handle for this subscription.
	*          hNotification - The new created notification object handle.
	*
	* Output:     phAppNotification - The application handle for this notification.
	***************************************************************************/
	typedef void
		(RVCALLCONV * RvSipSubsNotifyCreatedEv)(
		IN  RvSipSubsHandle     hSubs,
		IN  RvSipAppSubsHandle  hAppSubs,
		IN  RvSipNotifyHandle   hNotification,
		OUT RvSipAppNotifyHandle *phAppNotification);

	/***************************************************************************
	* RvSipSubsNotifyEv
	* ------------------------------------------------------------------------
	* General: Indicates of a notify status.
	*          For a subscriber: Gives the received Notify message, and it's related
	*          notification object handle. Application may get all notification
	*          information from the message at this callback.
	*          The message will be destructed when returning from this callback.
	*          For a Notifier: Informs application of a response message that was
	*          received for a Notify request, and supply the response message.
	*          When returning from this callback function, the stack notification
	*          object is destructed.
	*          For both subscriber and notifier it indicates about termination of
	*          the notification object.
	* Return Value: (-)
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hSubs         - The sip stack subscription handle
	*            hAppSubs      - The application handle for this subscription.
	*          hNotification - The new created notification object handle.
	*          hAppNotification - The application handle for this notification. (relevant
	*                          only for a notifier subscription, which set the hAppNotification
	*                          in RvSipSubsCreateNotify().
	*          eNotifyStatus - Status of the notification object.
	*          eNotifyReason - Reason to the indicated status.
	*          hNotifyMsg    - The received msg (notify request or response).
	***************************************************************************/
	typedef void
		(RVCALLCONV * RvSipSubsNotifyEv)(
		IN  RvSipSubsHandle    hSubs,
		IN  RvSipAppSubsHandle hAppSubs,
		IN  RvSipNotifyHandle  hNotification,
		IN  RvSipAppNotifyHandle  hAppNotification,
		IN  RvSipSubsNotifyStatus eNotifyStatus,
		IN  RvSipSubsNotifyReason eNotifyReason,
		IN  RvSipMsgHandle     hNotifyMsg);

	/******************************************************************************
	* RvSipSubsCreatedDueToForkingEv
	* ----------------------------------------------------------------------------
	* General: Notifies the application about the creation of a forked
	*          subscription. A forked subscription is created as the result of
	*          the arrival of a NOTIFY message, sent in response to the forked
	*          SUBSCRIBE request.
	*          For information about forking determination criteria,
	*          see sections 3.3.3 and 4.4.9 of RFC 3265.
	*
	*          Using this callback, the application can decide to reject
	*          the creation of the subscription. To do so, it should set
	*          the pRejectStatus parameter to the error code, which will be set
	*          in response to the NOTIFY message.
	*
	*          The forked subscription will not be created if the original
	*          subscription (the one that generated the SUBSCRIBE request)
	*          is configured to disable forking.
	*          See the RvSipSubsSetForkingEnabledFlag() API function.
	*
	*          If the callback is not set by the application, the NOTIFY message
	*          will be rejected with a 481 response according RFC 3265,
	*          and the transaction will be closed.
	*
	*          The application should not call the Subscription Layer API from
	*          this callback. Since it may affect the state of the Subscription
	*          (for example, RvSipSubsTerminate()).
	*
	*          It is recommended that the application disable forking
	*          for the event package of the REFER type. This means that if
	*          a subscriber subscription is created as the result of an incoming
	*          REFER request with a SUBSCRIBE method (the handle of such object is
	*          returned by RvSipSubsReferAccept()), the application should set
	*          the "ForkingEnabled" flag for the object to RV_FALSE (by means of
	*          the RvSipSubsSetForkingEnabledFlag() function).
	*
	* Return Value: any (the returned status is ignored currently - 03/2004)
	* ----------------------------------------------------------------------------
	* Arguments:
	* Input:   hSubs       - The handle to the created forked Subscription.
	*          pExpires    - A pointer to the expiration value of the subscription
	*                        This value should be set in seconds. If the value was
	*                        not determined, it will be set to ?.
	*                        The value cannot be determined if it was not set in
	*                        the original Subscription. In this case,
	*                        the application should supply the value to limit
	*                        the life cycle of the forked subscription.
	*                        The RvSipSubsUpdateSubscriptionTimer() function can
	*                        be also used for this purpose. On expiration,
	*                        the expiration callback will be called for the forked
	*                        subscription.
	* Output:  pExpires    - A pointer to the memory where the application can set
	*                        the expiration value.
	*          phAppSubs   - The handle that the application sets
	*                        for the subscription.
	*          pRejectStatus-If Application decides to terminate this Subscription
	*                        it should set the pointer to point to positive
	*                        integer, representing Error Code. In this case Stack
	*                        will respond to the NOTIFY with error code and
	*                        will free Subscription object and
	*                        all the Subscription related resources.
	*****************************************************************************/
	typedef RvStatus (RVCALLCONV *RvSipSubsCreatedDueToForkingEv)(
		IN        RvSipSubsHandle    hSubs,
		INOUT     RvInt32            *pExpires,
		OUT       RvSipAppSubsHandle *phAppSubs,
		OUT       RvUint16           *pRejectStatus);

	/*-----------------------------------------------------------------------
	A U T H E N T I C A T I O N :  C A L L - B A C K    F U N C T I O N S
	------------------------------------------------------------------------*/

	/***************************************************************************
	* RvSipSubsAuthCredentialsFoundEv
	* ------------------------------------------------------------------------
	* General:  This callback indicates the application that credentials were found
	*           in the request message (subscribe or notify request).
	*           This callback is called only if application had started the authentication
	*           procedure by calling to RvSipSubsAuthBegin() function.
	*           The callback supplies the application with the Authorization header
	*           that contains those credentials.
	*           At this stage the application should use the RvSipSubsAuthProceed()
	*           function.
	*           This callback also indicates whether the SIP Stack is capable of verifying the
	*           credentials that were found.
	*           Whenever the SIP Stack does not support the credentials (for example,
	*           if the algorithm is not MD5) the application may verify the credentials by itself
	*           or instructing the SIP Stack to continue to the next header.
	*           The authentication procedure may be done for a SUBSCRIBE request or for a
	*           NOTIFY request. for Subscribe request - hNotification is NULL.
	*           else - hNotification is handle to the notification object,
	*           that received the Notify request.
	* Return Value: (-)
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hSubs          - The sip stack subscription handle
	*            hAppSubs       - The application handle for this subscription.
	*          hNotification  - The handle to the notification that received the
	*                           request.
	*          hAuthorization - The handle to the authorization header that contains the credentials.
	*          bCredentialsSupported - Determines whether or not the SIP Stack supports the
	*                           credentials in the authorization header.
	***************************************************************************/
	typedef void (RVCALLCONV * RvSipSubsAuthCredentialsFoundEv)(
		IN    RvSipSubsHandle                 hSubs,
		IN    RvSipAppSubsHandle              hAppSubs,
		IN    RvSipNotifyHandle               hNotification,
		IN    RvSipAuthorizationHeaderHandle  hAuthorization,
		IN    RvBool                         bCredentialsSupported);

	/***************************************************************************
	* RvSipSubsAuthCompletedEv
	* ------------------------------------------------------------------------
	* General:  RvSipSubsAuthCompletedEv() is called when the authentication procedure
	*           is completed.
	*           If it is completed because we found the correct authorization
	*           header, bAuthSucceed is RV_TRUE.
	*           If it is completed because there are no more authorization headers
	*           to check, or because user ordered to stop the searching for
	*           correct header, bAuthSucceed is RV_FALSE.
	*           The authentication procedure may be done for a SUBSCRIBE request or for a
	*           NOTIFY request. for Subscribe request - hNotification is NULL.
	*           else - hNotification is handle to the notification object,
	*           that received the Notify request.
	* Return Value: (-)
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hSubs          - The handle to the subscription that received  the
	*                           Subscribe request. for a NOTIFY request, it is the
	*                           handle to the notification related subscription.
	*            hAppSubs       - The application handle for this subscription.
	*          hNotification  - The handle to the notification that received the
	*                           NOTIFY request. NULL for a SUBSCRIBE request.
	*          bAuthSucceed   - RV_TRUE if we found correct authorization header,
	*                           RV_FALSE if we did not.
	***************************************************************************/
	typedef void (RVCALLCONV * RvSipSubsAuthCompletedEv)(
		IN    RvSipSubsHandle    hSubs,
		IN    RvSipAppSubsHandle hAppSubs,
		IN    RvSipNotifyHandle  hNotification,
		IN    RvBool            bAuthSucceed);

	/*-----------------------------------------------------------------------
	M E S S A G E :  C A L L - B A C K    F U N C T I O N S
	------------------------------------------------------------------------*/
	/***************************************************************************
	* RvSipSubsMsgToSendEv
	* ------------------------------------------------------------------------
	* General: An event indicating that a subscription related outgoing
	*          message is about to be sent.
	*          (subscribe or notify requests and responses)
	* Return Value: RV_OK (the returned status is ignored in the current
	*                           stack version)
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hSubs -      The sip stack subscription handle
	*            hAppSubs -   The application handle for this subscription.
	*          hNotify -    The notify object handle (relevant only for notify message)
	*          hAppNotify - The application notify object handle (relevant only for notify message)
	*            hMsg -       Handle to the outgoing message.
	***************************************************************************/
	typedef RvStatus (RVCALLCONV * RvSipSubsMsgToSendEv)(
		IN    RvSipSubsHandle      hSubs,
		IN    RvSipAppSubsHandle   hAppSubs,
		IN    RvSipNotifyHandle    hNotify,
		IN    RvSipAppNotifyHandle hAppNotify,
		IN    RvSipMsgHandle       hMsg);


	/***************************************************************************
	* RvSipSubsMsgReceivedEv
	* ------------------------------------------------------------------------
	* General: An event indicating that a subscription related incoming
	*          message has been received. (subscribe or notify requests and responses)
	* Return Value: RV_OK (the returned status is ignored in the current
	*                           stack version)
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hSubs -      The sip stack subscription handle
	*            hAppSubs -   The application handle for this subscription.
	*            hNotify -    The notify object handle (relevant only for notify message)
	*          hAppNotify - The application notify object handle (relevant only for notify message)
	*            hMsg -       Handle to the incoming message.
	***************************************************************************/
	typedef RvStatus (RVCALLCONV * RvSipSubsMsgReceivedEv)(
		IN  RvSipSubsHandle      hSubs,
		IN  RvSipAppSubsHandle   hAppSubs,
		IN  RvSipNotifyHandle    hNotify,
		IN  RvSipAppNotifyHandle hAppNotify,
		IN  RvSipMsgHandle       hMsg);


	/***************************************************************************
	* RvSipSubsOtherURLAddressFoundEv
	* ------------------------------------------------------------------------
	* General: Notifies the application that other URL address (URL that is
	*            currently not supported by the RvSip stack) was found and has
	*            to be converted to known SIP URL address.
	* Return Value: RvStatus (RV_OK on success execution or RV_ERROR_UNKNOWN
	*                 otherwise).
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hSubs          - The sip stack subscription handle
	*            hAppSubs       - The application handle for this subscription.
	*            hNotify        - The notify object handle (relevant only for notify request or response)
	*          hAppNotify     - The application notify object handle (relevant only for notify request or response)
	*            hMsg           - The message that includes the other URL address.
	*            hAddress       - Handle to unsupport address to be converted.
	* Output:    hSipURLAddress - Handle to the known SIP URL address.
	*            bAddressResolved-Indication of a successful/failed address
	*                             resolving.
	***************************************************************************/
	typedef RvStatus (RVCALLCONV *RvSipSubsOtherURLAddressFoundEv)(
		IN  RvSipSubsHandle            hSubs,
		IN  RvSipAppSubsHandle        hAppSubs,
		IN  RvSipNotifyHandle        hNotify,
		IN  RvSipAppNotifyHandle    hAppNotify,
		IN  RvSipMsgHandle          hMsg,
		IN  RvSipAddressHandle        hAddress,
		OUT RvSipAddressHandle        hSipURLAddress,
		OUT RvBool                    *bAddressResolved);



	/***************************************************************************
	* RvSipSubsFinalDestResolvedEv
	* ------------------------------------------------------------------------
	* General: Notifies the application that the subscription is about to send a 
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
	*               terminate with error and the subscription will behave according
	*               to its processing rules for transaction error termination.
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hSubs          - The sip stack subscription handle
	*            hAppSubs       - The application handle for this subscription.
	*            hNotify        - The notify object handle (relevant only for notify request or response)
	*            hAppNotify     - The application notify object handle (relevant only for notify request or response)
	*            hTransc        - The transaction handle
	*            hMsgToSend     - The handle to the outgoing message.
	***************************************************************************/
	typedef RvStatus (RVCALLCONV * RvSipSubsFinalDestResolvedEv)(
		IN  RvSipSubsHandle           hSubs,
		IN  RvSipAppSubsHandle        hAppSubs,
		IN  RvSipNotifyHandle         hNotify,
		IN  RvSipAppNotifyHandle      hAppNotify,
		IN  RvSipTranscHandle         hTransc,
		IN  RvSipMsgHandle            hMsgToSend);

	/***************************************************************************
	* RvSipSubsNewConnInUseEv
	* ------------------------------------------------------------------------
	* General:Notifies the application that the transaction is now using a new 
	*         connection. The connection can be a totally new one or a suitable 
	*         one that was found in the hash.
	*
	* Return Value: RV_OK (the returned status is ignored in the current
	*                      stack version)
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hSubs          - The sip stack subscription handle
	*            hAppSubs       - The application handle for this subscription.
	*            hNotify        - The notify object handle (relevant only for notify request or response)
	*            hAppNotify     - The application notify object handle (relevant only for notify request or response)
	*            hConn          - The connection handle
	*            bNewConnCreated - RV_TRUE if the connection is a newly 
	*                              created connection. RV_FALSE if the connection 
	*                              was found in the connection hash.
	***************************************************************************/
	typedef RvStatus (RVCALLCONV *RvSipSubsNewConnInUseEv) (
		IN  RvSipSubsHandle                hSubs,
		IN  RvSipAppSubsHandle             hAppSubs,
		IN  RvSipNotifyHandle              hNotify,
		IN  RvSipAppNotifyHandle           hAppNotify,
		IN  RvSipTransportConnectionHandle hConn,
		IN  RvBool                         bNewConnCreated);


#ifdef RV_SIGCOMP_ON
	/***************************************************************************
	* RvSipSubsSigCompMsgNotRespondedEv
	* ------------------------------------------------------------------------
	* General: Notifies the application that the timer of the transaction 
	*          responsible for sending the SUBSCRIBE or NOTIFY request has expired 
	*          and that the SIP Stack has not yet received a response to the SigComp 
	*          compressed request.
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
	* Input:     hSubs         - The sip stack subscription handle
	*            hAppSubs      - The application handle for this subscription.
	*            hNotify       - The notify object handle (relevant only for notify request or response)
	*            hAppNotify    - The application notify object handle (relevant only for notify request or response)
	*            hTransc       - The transaction handle.
	*            retransNo     - The number of retransmissions of the request
	*                            until now.
	*            ePrevMsgComp  - The type of the previous not responded request
	* Output:    peNextMsgComp - The type of the next request to retransmit (
	*                            RVSIP_TRANSMITTER_MSG_COMP_TYPE_UNDEFINED means that the
	*                            application wishes to stop sending requests).
	***************************************************************************/
	typedef RvStatus (RVCALLCONV *RvSipSubsSigCompMsgNotRespondedEv)(
		IN  RvSipSubsHandle              hSubs,
		IN  RvSipAppSubsHandle           hAppSubs,
		IN  RvSipNotifyHandle            hNotify,
		IN  RvSipAppNotifyHandle         hAppNotify,
		IN  RvSipTranscHandle            hTransc,
		IN  RvInt32                      retransNo,
		IN  RvSipTransmitterMsgCompType  ePrevMsgComp,
		OUT RvSipTransmitterMsgCompType *peNextMsgComp);
#endif /* RV_SIGCOMP_ON */
	/* ------------------------------------------------------------------------
	R E F E R   S U B S C R I P T I O N   C A L L B A C K S
	------------------------------------------------------------------------ */
	/***************************************************************************
	* RvSipSubsReferNotifyReadyEv
	* ------------------------------------------------------------------------
	* General: Indicates that a refer notifier subscription is ready to
	*          send a notify request.
	*          This callback is called after accepting a REFER request, and for
	*          every incoming provisional or final response for the related
	*          object establishment attempt.
	*          When RvSipSubsReferNotifyReadyEv() is called, application should
	*          create and send a new notify request, with status of the establish
	*          attempt of the refer related object.
	*          The response code parameter indicates the response code that should
	*          be set in the body of the NOTIFY message.
	*          The function also provides the incoming response message of the
	*          establishment attempt. (note that the message not always exists.
	*          in case of timeout termination, for example, this parameter will
	*          be NULL).
	* Return Value: (-)
	* ------------------------------------------------------------------------
	* Arguments:
	* Input:     hSubs         - The sip stack subscription handle
	*            hAppSubs      - The application handle for this subscription.
	*          eReason       - The reason for a NOTIFY request to be sent
	*          responseCode  - The response code that should be set in the
	*                          NOTIFY message body.
	*          hResponseMsg  - The message that was received on the refer related
	*                          object (provisional or final response).
	***************************************************************************/
	typedef void
		(RVCALLCONV * RvSipSubsReferNotifyReadyEv)(
		IN  RvSipSubsHandle                  hSubs,
		IN  RvSipAppSubsHandle               hAppSubs,
		IN  RvSipSubsReferNotifyReadyReason  eReason,
		IN  RvInt16                          responseCode,
		IN  RvSipMsgHandle                   hResponseMsg);



	/* RvSipSubsEvHandlers
	* ------------------------------------------------------------------------
	* Structure with function pointers to the module's call-back.
	* This structure is used to set the application call-backs in the function
	* RvSipSubsMgrSetEvHandlers();
	*
	* pfnSubsCreatedEvHandler       - indicates of a new subscription.
	* pfnStateChangedEvHandler      - indicates of subscription state change.
	* pfnSubsExpiredEvHandler       - indicates that subscription expired.
	* pfnExpirationAlertEvHandler   - indicates that subscription is about to be expired.
	* pfnNotifyEvHandler            - indicates of a notify request or response.
	* pfnAuthCredentialsFoundEvHandler - indicates of new credentials for server authentication.
	* pfnAuthCompletedEvHandler     - indicates that server authentication procedure,
	*                                 was completed (with success or failure).
	* pfnMsgToSendEvHandler         - indicates that a new message is going to be sent.
	* pfnMsgReceivedEvHandler       - indicates that a new message was received.
	* pfnNotifyCreatedEvHandler     - indicates of a new notification object.
	* pfnOtherURLAddressFoundEvHandler   - Notifies the application that other URL address was
	*                                      was found and has to be converted to SIP URL address.
	* pfnFinalDestResolvedEvHandler      - Notifies that the final destination address
	*                                      of the register request was resolved.
	* pfnSigCompMsgNotRespondedEvHandler - Notifies that no response was received to the
	*                                      last SigComp sent message.
	* pfnSubsCreatedDueToForkingEvHandler  - Notifies the application about new
	*                                  Subscription, created as a result of forked
	*                                  NOTIFY arrival.
	*                                  If it is not set, the NOTIFY will be rejected
	*                                  with 481 response, no Subscription will be
	*                                  created.
	*/
	typedef struct
	{
		RvSipSubsCreatedEv                  pfnSubsCreatedEvHandler;
		RvSipSubsStateChangedEv             pfnStateChangedEvHandler;
		RvSipSubsSubscriptionExpiredEv      pfnSubsExpiredEvHandler;
		RvSipSubsExpirationAlertEv          pfnExpirationAlertEvHandler;
		RvSipSubsNotifyEv                   pfnNotifyEvHandler;
		RvSipSubsAuthCredentialsFoundEv     pfnAuthCredentialsFoundEvHandler;
		RvSipSubsAuthCompletedEv            pfnAuthCompletedEvHandler;
		RvSipSubsMsgToSendEv                pfnMsgToSendEvHandler;
		RvSipSubsMsgReceivedEv              pfnMsgReceivedEvHandler;
		RvSipSubsNotifyCreatedEv            pfnNotifyCreatedEvHandler;
		RvSipSubsOtherURLAddressFoundEv     pfnOtherURLAddressFoundEvHandler;
		RvSipSubsFinalDestResolvedEv        pfnFinalDestResolvedEvHandler;
		RvSipSubsReferNotifyReadyEv         pfnReferNotifyReadyEvHandler;
#ifdef RV_SIGCOMP_ON
		RvSipSubsSigCompMsgNotRespondedEv   pfnSigCompMsgNotRespondedEvHandler;
#endif
		RvSipSubsNewConnInUseEv             pfnNewConnInUseEvHandler;
		RvSipSubsCreatedDueToForkingEv      pfnSubsCreatedDueToForkingEvHandler;
	} RvSipSubsEvHandlers;


#endif /*#ifndef RV_SIP_PRIMITIVES */

#ifdef __cplusplus
}
#endif


#endif /* END OF: #ifndef RV_SIP_SUBSCRIPTION_TYPES_H */

