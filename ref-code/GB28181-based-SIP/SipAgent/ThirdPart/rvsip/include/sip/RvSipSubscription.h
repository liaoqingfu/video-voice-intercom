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
 *                         <RvSipSubscription.h>
 *
 * The Subscription functions of the RADVISION SIP stack enable you to create and
 * manage subscription and notification objects. Subscription functions may be used
 * for implementing event-notification feature.
 *
 * Subscription API functions are grouped as follows:
 *
 * The Subscription Manager API
 * -----------------------------
 * The subscription manager is in charge of all the subscriptions. It is used
 * to set the event handlers of the subscription module and to create
 * new subscriptions.
 *
 * The Subscription API
 * --------------------
 * A subscription represents a SIP subscription as defined in draft rfc 3265.
 * Using the subscription API, the user can initiate subscriptions, react
 * to incoming subscriptions, refresh subscriptions and ask for terminating a subscription.
 * Functions to set and access the subscription fields are also available in the API.
 * A subscription is a state-full object and has a set of states associated with it.
 *
 * The Notification API
 * --------------------
 * A notification represents a SIP notification as defined in draft rfc 3265.
 * Using the notification API, the user can create notifications, and react
 * to incoming notifications.
 * Functions to set and access the notification fields are also available in the API.
 *
 *    Author                         Date
 *    ------                        ------
 *    Ofra Wachsman                  June 2002
 *********************************************************************************/
#ifndef RV_SIP_SUBSCRIPTION_H
#define RV_SIP_SUBSCRIPTION_H

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                           */
/*-----------------------------------------------------------------------*/
#include "RV_SIP_DEF.h"
#ifndef RV_SIP_PRIMITIVES
#include "RvSipSubscriptionTypes.h"
#include "RvSipCallLegTypes.h"
#include "RvSipTransportDNSTypes.h"
#include "RvSipCommonTypes.h"





/*-----------------------------------------------------------------------*/
/*                SUBSCRIPTION MANAGER  API                              */
/*-----------------------------------------------------------------------*/
/***************************************************************************
 * RvSipSubsMgrSetEvHandlers
 * ------------------------------------------------------------------------
 * General: Set event handlers for all subscription events.
 * Return Value:RV_ERROR_INVALID_HANDLE - The handle to the manager is invalid.
 *              RV_ERROR_NULLPTR        - Bad pointer to the event handler structure.
 *              RV_OK                   - Success.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hMgr        - Handle to the subscription manager.
 *            pEvHandlers - Pointer to structure containing application event
 *                          handler pointers.
 *            structSize  - The size of the event handler structure.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsMgrSetEvHandlers(
                                   IN  RvSipSubsMgrHandle  hMgr,
                                   IN  RvSipSubsEvHandlers *pEvHandlers,
                                   IN  RvInt32             structSize);

/***************************************************************************
 * RvSipSubsMgrCreateSubscription
 * ------------------------------------------------------------------------
 * General: Creates a new subscription and exchange handles with the
 *          application. The new subscription assumes the Idle state.
 *          You may supply a call-leg handle to create the subscription inside
 *          an already established call-leg. Else - set NULL in the call-leg
 *          handle parameter.
 *          To establish a new active subscription
 *          1. Create a new subscription with this function.
 *          2. Init subscription parameters.
 *          3. Call the Subscribe() function.
 *
 * Return Value: RV_ERROR_INVALID_HANDLE -  The handle to the manager is invalid.
 *               RV_ERROR_NULLPTR        -  The pointer to the subscription handle
 *                                          is invalid.
 *               RV_ERROR_OUTOFRESOURCES -  Subscription list is full,subscription was not
 *                                          created.
 *               RV_OK                   -  Success.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hSubsMgr - Handle to the subscription manager
 *          hCallLeg - Handle to a call-leg that own the subscription.
 *                     if NULL, the subscription will create a new dialog,
 *                     and will not be related to any call-leg.
 *          hAppSubs - Application handle to the newly created subscription.
 * Output:  phSubs   - RADVISION SIP stack handle to the subscription.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsMgrCreateSubscription(
                                   IN  RvSipSubsMgrHandle hSubsMgr,
                                   IN  RvSipCallLegHandle hCallLeg,
                                   IN  RvSipAppSubsHandle hAppSubs,
                                   OUT RvSipSubsHandle    *phSubs);

/***************************************************************************
 * RvSipSubsMgrCreateOutOfBandSubscription
 * ------------------------------------------------------------------------
 * General: Creates a new out of band subscription and exchange handles with the
 *          application.
 *          out of band subscription, is a subscription created with no SUBSCRIBE
 *          request. The new subscription assumes the Active state.
 *          You may supply a call-leg handle to create the subscription inside
 *          an already established call-leg. Else - set NULL in the call-leg
 *          handle parameter.
 *          To establish a new out of band subscription
 *          1. Create a new subscription with this function.
 *          2. Init subscription parameters.
 *
 *          NOTE - if you don't supply call-leg handle to this created out-of-band
 *          subscription, on initialization stage, you will have to set the dialog
 *          call-id parameter first, and only then you can call to RvSipSubsInit().
 *
 * Return Value: RV_ERROR_INVALID_HANDLE -  The handle to the manager is invalid.
 *               RV_ERROR_NULLPTR        -  The pointer to the subscription handle 
 *                                          is invalid.
 *               RV_ERROR_OUTOFRESOURCES -  Subscription list is full,subscription 
 *                                          was not created.
 *               RV_OK                   - Success.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hSubsMgr  - Handle to the subscription manager
 *            hCallLeg  - Handle to a call-leg that own the subscription.
 *                        if NULL, the subscription will create a new dialog,
 *                        and will not be related to any call-leg.
 *            hAppSubs  - Application handle to the newly created subscription.
 *            eSubsType - Subscriber or Notifier.
 * Output:    phSubs    - RADVISION SIP stack handle to the subscription.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsMgrCreateOutOfBandSubscription(
                                       IN  RvSipSubsMgrHandle hSubsMgr,
                                       IN  RvSipCallLegHandle hCallLeg,
                                       IN  RvSipAppSubsHandle hAppSubs,
                                       IN  RvSipSubscriptionType eSubsType,
                                       OUT RvSipSubsHandle    *phSubs);

/***************************************************************************
 * RvSipSubsMgrGetStackInstance
 * ------------------------------------------------------------------------
 * General: Returns the handle to the stack instance to which this subscription
 *          manager belongs to.
 *
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hSubsMgr - Handle to the subscription manager
 * Output:    phStackInstance - A valid pointer which will be updated with a
 *                       handle to the stack instance.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsMgrGetStackInstance(
                                   IN  RvSipSubsMgrHandle  hSubsMgr,
                                   OUT void              **phStackInstance);

/***************************************************************************
 * RvSipSubsMgrGetAppMgrHandle
 * ------------------------------------------------------------------------
 * General: Returns the handle to the application subs manger object.
 *          You set this handle in the stack using the
 *          RvSipSubsMgrSetAppMgrHandle() function.
 *
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hSubsMgr    - Handle to the stack subs manager..
 * Output:    pAppSubsMgr - The application subs manager handle.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsMgrGetAppMgrHandle(
                                   IN RvSipSubsMgrHandle hSubsMgr,
                                   OUT void**            pAppSubsMgr);

/***************************************************************************
 * RvSipSubsMgrSetAppMgrHandle
 * ------------------------------------------------------------------------
 * General: The application can have its own subs manager handle.
 *          You can use the RvSipSubsMgrSetAppMgrHandle function to
 *          save this handle in the stack subs manager object.
 *
 * Return Value: RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:    hSubsMgr    - Handle to the stack subs manager.
 *           pAppSubsMgr - The application subs manager handle.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsMgrSetAppMgrHandle(
                                   IN RvSipSubsMgrHandle hSubsMgr,
                                   IN void*              pAppSubsMgr);

/*-----------------------------------------------------------------------*/
/*                 SUBSCRIPTION API                                      */
/*-----------------------------------------------------------------------*/

/***************************************************************************
 * RvSipSubsInit
 * ------------------------------------------------------------------------
 * General: Initiate a subscription with mandatory parameters: To and From headers
 *          of the dialog, expiresVal of the subscription, and Event header of
 *          the subscription.
 *          If the subscription was created inside of a call-leg you should not
 *          set the To and From headers.
 *          This function initialized the subscription, but do not send any request.
 *          You should call RvSipSubsSubscribe() in order to send a Subscribe
 *          request.
 * Return Value: RV_ERROR_INVALID_HANDLE - The handle to the subscription is invalid.
 *               RV_ERROR_ILLEGAL_ACTION - Invalid subscription state for this action.
 *               RV_ERROR_OUTOFRESOURCES - subscription failed to create a new header.
 *               RV_ERROR_BADPARAM - Bad parameter was given by the application.
 *               RV_ERROR_NULLPTR - Bad pointer was given by the application.
 *               RV_OK - Initialization was done successfully.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hSubs - Handle to the subscription the user wishes to initialize.
 *          hFrom - Handle to a party header, contains the from header information.
 *          hTo   - Handle to a party header, contains the from header information.
 *          expiresVal - Expires value to be set in first SUBSCRIBE request - in seconds.
 *                  value of this argument must be smaller than 0xFFFFFFF/1000.
 *                 (This is not necessarily the final expires value. Notifier may
 *                  decide of a shorter expires value in the 2xx response.)
 *                  If equals to UNDEFINED, no expires header will be set in the
 *                  SUBSCRIBE request.
 *          hEvent - Handle to an Event header. this header identify the subscription.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsInit(
                                         IN  RvSipSubsHandle        hSubs,
                                         IN  RvSipPartyHeaderHandle hFrom,
                                         IN  RvSipPartyHeaderHandle hTo,
                                         IN  RvInt32                expiresVal,
                                         IN  RvSipEventHeaderHandle hEvent);

/***************************************************************************
 * RvSipSubsInitStr
 * ------------------------------------------------------------------------
 * General: Init a subscription with mandatory parameters, given in a string format:
 *          To and From header value strings strings of the dialog, expiresVal of
 *          the subscription, and Event header string value of the subscription.
 *          If the subscription was created inside of a call-leg you should not
 *          set the To and From values.
 *          This function initialized the subscription, but do not send any request.
 *          You should call RvSipSubsSubscribe() in order to send a Subscribe
 *          request.
 * Return Value: RV_ERROR_INVALID_HANDLE - The handle to the subscription is invalid.
 *               RV_ERROR_ILLEGAL_ACTION - Invalid subscription state for this action.
 *               RV_ERROR_OUTOFRESOURCES - subscription failed to create a new header.
 *               RV_ERROR_BADPARAM - Bad parameter was given by the application.
 *               RV_ERROR_NULLPTR - Bad pointer was given by the application.
 *               RV_OK - Initialization was done successfully.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hSubs - Handle to the subscription the user wishes to initialize.
 *          strFrom - String of the From header value. for Example: "A<sip:176.56.23.4:4444>"
 *          strTo -  String of the To header value. for Example: "B<sip:176.56.23.4;transport=TCP>"
 *          expiresVal - Expires value to be set in first SUBSCRIBE request - in seconds.
 *                  value of this argument must be smaller than 0xFFFFFFF/1000.
 *                 (This is not necessarily the final expires value. Notifier may
 *                  decide of a shorter expires value in the 2xx response.)
 *                  If equals to UNDEFINED, no expires header will be set in the
 *                  SUBSCRIBE request.
 *          strEvent - String to the Event header value. this header identify the
 *                  subscription. for Example: "eventPackageX.eventTemplateY"
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsInitStr(
                                         IN  RvSipSubsHandle hSubs,
                                         IN  RvChar*         strFrom,
                                         IN  RvChar*         strTo,
                                         IN  RvInt32         expiresVal,
                                         IN  RvChar*         strEvent);

/***************************************************************************
 * RvSipSubsDialogInit
 * ------------------------------------------------------------------------
 * General: Initiate a subscription with dialog parameters: To, From, remote
 *          contact and local contact headers.
 *          This function is relevant only for subscription that was created
 *          outside of a call-leg.
 *          This function initializes the dialog of the subscription, but do not
 *          initialize the subscription parameters.
 *          You should call RvSipSubsInit() or RvSipSubsReferInit() in order
 *          to initialize the subscription parameters.
 * Return Value: RV_ERROR_INVALID_HANDLE - The handle to the subscription is invalid.
 *               RV_ERROR_ILLEGAL_ACTION - Invalid subscription state for this action,
 *                                         or subscription inside call-leg.
 *               RV_ERROR_OUTOFRESOURCES - subscription failed to create a new header.
 *               RV_ERROR_BADPARAM       - Bad parameter was given by the application.
 *               RV_ERROR_NULLPTR        - Bad pointer was given by the application.
 *               RV_OK                   - Initialization was done successfully.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hSubs - Handle to the subscription the user wishes to initialize.
 *          hFrom - Handle to a party header, contains the from header information.
 *          hTo -   Handle to a party header, contains the from header information.
 *          hLocalContactAddr - Handle to address, contains the local contact
 *                  Address information.
 *          hRemoteContactAddr - Handle to address, contains the remote
 *                  contact address information.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsDialogInit(
                                         IN  RvSipSubsHandle        hSubs,
                                         IN  RvSipPartyHeaderHandle hFrom,
                                         IN  RvSipPartyHeaderHandle hTo,
                                         IN  RvSipAddressHandle     hLocalContactAddr,
                                         IN  RvSipAddressHandle     hRemoteContactAddr);

/***************************************************************************
 * RvSipSubsDialogInitStr
 * ------------------------------------------------------------------------
 * General: Initiate a subscription with dialog parameters in string format: 
 *          To, From, remote contact and local contact headers.
 *          This function is relevant only for subscription that was created
 *          outside of a call-leg.
 *          This function initializes the dialog if the subscription, but do not
 *          initialize the subscription parameters.
 *          You should call RvSipSubsInitStr() or RvSipSubsReferInitStr() in order
 *          to initialize the subscription parameters.
 * Return Value: RV_ERROR_INVALID_HANDLE - The handle to the subscription is invalid.
 *               RV_ERROR_ILLEGAL_ACTION - Invalid subscription state for this action,
 *                                         or subscription inside call-leg.
 *               RV_ERROR_OUTOFRESOURCES - subscription failed to create a new header.
 *               RV_ERROR_BADPARAM       - Bad parameter was given by the application.
 *               RV_ERROR_NULLPTR        - Bad pointer was given by the application.
 *               RV_OK                   - Initialization was done successfully.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hSubs   - Handle to the subscription the user wishes to initialize.
 *          strFrom - String of the From header value.
 *                    for Example: "A<sip:176.56.23.4:4444>"
 *          strTo   - String of the To header value.
 *                    for Example: "B<sip:176.56.23.4;transport=TCP>"
 *          strLocalRemote - String of the local contact address value,
 *                    for Example: "sip:176.56.23.4:4444"
 *          strRemoteContact - String of the remote contact address value.
 *                    for Example: "sip:176.56.23.4:4444"
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsDialogInitStr(
                                         IN  RvSipSubsHandle hSubs,
                                         IN  RvChar*         strFrom,
                                         IN  RvChar*         strTo,
                                         IN  RvChar*         strLocalContactAddr,
                                         IN  RvChar*         strRemoteContactAddr);

/***************************************************************************
 * RvSipSubsSubscribe
 * ------------------------------------------------------------------------
 * General: establish a subscription by sending a SUBSCRIBE request.
 *          This function may be called only after the subscription was initialized
 *          with To, From, Event and Expires parameters.
 *          (If this is a subscription of an already established call-leg, To and
 *          From parameters are taken from the call-leg).
 *          Calling this function causes a SUBSCRIBE to be sent out and the
 *          subscription state machine to progress to the Subs_Sent state.
 * Return Value: RV_ERROR_INVALID_HANDLE -  The handle to the subscription is invalid.
 *               RV_ERROR_ILLEGAL_ACTION - Invalid subscription state for this action.
 *               RV_ERROR_OUTOFRESOURCES - Subscription failed to create a new transaction.
 *               RV_ERROR_UNKNOWN - An error occurred while trying to send the
 *                            message (Couldn't send a message to the given
 *                            Request-Uri).
 *               RV_OK - Subscribe message was sent successfully.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hSubs - Handle to the subscription the user wishes to subscribe.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsSubscribe(IN  RvSipSubsHandle   hSubs);

/***************************************************************************
 * RvSipSubsRefresh
 * ------------------------------------------------------------------------
 * General: Refresh a subscription by sending a SUBSCRIBE request in the
 *          subscription. This method may be called only on SUBS_ACTIVE state.
 *          Calling to refresh causes a SUBSCRIBE request to be sent out, and the
 *          subscription state machine to progress to the Subs_Refresing state.
 * Return Value: RV_ERROR_INVALID_HANDLE - The handle to the subscription is invalid.
 *               RV_ERROR_ILLEGAL_ACTION - Illegal subscription state for this action.
 *               RV_ERROR_OUTOFRESOURCES - Subscription failed to create a new transaction.
 *               RV_ERROR_UNKNOWN - An error occurred while trying to send the
 *                            message (Couldn't send a message to the given
 *                            Request-Uri).
 *               RV_OK - Subscribe message was sent successfully.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hSubs             - Handle to the subscription the user wishes to refresh.
 *            refreshExpiresVal - Expires value to be set in the refresh request
 *                                in seconds. 
 *                                value of this argument must be smaller than 0xFFFFFFF/1000.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsRefresh(
                                         IN  RvSipSubsHandle   hSubs,
                                         IN  RvInt32           refreshExpiresVal);

/***************************************************************************
 * RvSipSubsUnsubscribe
 * ------------------------------------------------------------------------
 * General: Asks Notifier to terminate the subscription by sending a SUBSCRIBE
 *          request with 'Expires:0' header in the subscription.
 *          This method may be called on states SUBS_ACTIVE, SUBS_PENDING and
 *          SUBS_2XX_RCVD.
 *          The function progress the subscription state machine to the
 *          Subs_Unsubscribing state.
 * Return Value: RV_ERROR_INVALID_HANDLE - The handle to the subscription is invalid.
 *               RV_ERROR_ILLEGAL_ACTION - Invalid subscription state for this action.
 *               RV_ERROR_OUTOFRESOURCES - Subscription failed to create a new transaction.
 *               RV_ERROR_UNKNOWN        - An error occurred while trying to send the
 *                                         message (Couldn't send a message to the given
 *                                         Request-Uri).
 *               RV_OK                   - Subscribe message was sent successfully.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hSubs - Handle to the subscription the user wishes to unsubscribe.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsUnsubscribe(IN  RvSipSubsHandle   hSubs);

/***************************************************************************
 * RvSipSubsRespondAccept
 * ------------------------------------------------------------------------
 * General: Sends a 200 response on a subscribe request and updates the
 *          subscription state machine.
 *          You may use this function to accept an initial subscribe request,
 *          refresh or unsubscribe requests.
 *          Note that this function does not send a notify request!!!
 *          It is the responsibility of the application to create and send a
 *          notify(active) request, immediately after it accepts the
 *          subscribe request by calling to this function.
 * Return Value: RV_ERROR_INVALID_HANDLE -  The handle to the subscription is invalid.
 *               RV_ERROR_ILLEGAL_ACTION -  Invalid subscription state for this action.
 *               RV_ERROR_UNKNOWN        -  Failed to accept the call. (failed
 *                                          while trying to send the 200 response).
 *               RV_OK                   -  Accept final response was sent successfully.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hSubs      - Handle to the subscription the user wishes to accept.
 *          expiresVal - Expires value to be set in the 200 response - in seconds.
 *                       value of this argument must be smaller than 0xFFFFFFF/1000.
 *                       if UNDEFINED, the expires value will be the same as in
 *                       the subscribe request.
 *                       Note that if there was no expires header in the incoming
 *                       SUBSCRIBE request, you must not give an UNDEFINED
 *                       expires value.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsRespondAccept (
                                        IN  RvSipSubsHandle   hSubs,
                                        IN  RvInt32          expiresVal);


/***************************************************************************
 * RvSipSubsRespondPending
 * ------------------------------------------------------------------------
 * General: Sends a 202 response for an initial subscribe request, and update
 *          the subscription state machine to Subs_Pending state.
 *          You may use this function only for an initial subscribe request.
 *          Note that this function does not send a notify request!!!
 *          It is user responsibility to create and send a notify(pending) request,
 *          immediately after he respondPending to the subscribe request!!!
 * Return Value: RV_ERROR_INVALID_HANDLE -  The handle to the subscription is invalid.
 *               RV_ERROR_ILLEGAL_ACTION -  Invalid subscription state for this action.
 *               RV_ERROR_UNKNOWN        -  Failed to accept the call. (failed
 *                                          while trying to send the 200 response).
 *               RV_OK                   -  Accept final response was sent successfully.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hSubs      - Handle to the subscription.
 *          expiresVal - Expires value to be set in the 202 response - in seconds.
 *                       value of this argument must be smaller than 0xFFFFFFF/1000.
 *                       if UNDEFINED, the expires value will be the same as in
 *                       the subscribe request.
 *                       Note that if there was no expires header in the incoming
 *                       SUBSCRIBE request, you must not give an UNDEFINED
 *                       expires value.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsRespondPending (
                                        IN  RvSipSubsHandle   hSubs,
                                        IN  RvInt32          expiresVal);

/***************************************************************************
* RvSipSubsRespondProvisional
* ------------------------------------------------------------------------
* General:  Send 1xx on subscribe request (initial subscribe, refresh
*           or unsubscribe).
*           Can be used in the RVSIP_SUBS_STATE_SUBS_RCVD, RVSIP_SUBS_STATE_REFRESH_RCVD
*           or RVSIP_SUBS_STATE_UNSUBSCRIBE_RCVD states.
*           Note - According to RFC 3265, sending provisional response on
*           SUBSCRIBE request is not allowed.
*           According to RFC 3515, only 100 response on REFER request is allowed.
* Return Value: RV_ERROR_INVALID_HANDLE    - The handle to the subscription is invalid.
*               RV_ERROR_BADPARAM          - The status code is invalid.
*               RV_ERROR_ILLEGAL_ACTION    - Invalid subscription state for this action.
*               RV_ERROR_UNKNOWN           - Failed to reject the subscription. (failed
*                                            while trying to send the reject response).
*               RV_OK                      - 1xx was sent successfully.
* ------------------------------------------------------------------------
* Arguments:
* Input:    hSubs      - Handle to the subscription the user wishes to send 1xx for.
*           statusCode - The 1xx value.
*           strReasonPhrase - Reason phrase to be set in the sent message.
*                        (May be NULL, to set a default reason phrase.)
***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsRespondProvisional(
                                       IN  RvSipSubsHandle  hSubs,
                                       IN  RvUint16         statusCode,
                                       IN  RvChar*          strReasonPhrase);

/***************************************************************************
* RvSipSubsRespondReject
* ------------------------------------------------------------------------
* General:  Reject an incoming subscribe request (initial subscribe, refresh
*           or unsubscribe).
*           Can be used in the RVSIP_SUBS_STATE_SUBS_RCVD, RVSIP_SUBS_STATE_REFRESH_RCVD
*           or RVSIP_SUBS_STATE_UNSUBSCRIBE_RCVD states.
* Return Value: RV_ERROR_INVALID_HANDLE    - The handle to the subscription is invalid.
*               RV_ERROR_BADPARAM          - The status code is invalid.
*               RV_ERROR_ILLEGAL_ACTION    - Invalid subscription state for this action.
*               RV_ERROR_UNKNOWN           - Failed to reject the subscription. (failed
*                                            while trying to send the reject response).
*               RV_OK                      - Reject final response was sent successfully.
* ------------------------------------------------------------------------
* Arguments:
* Input:     hSubs      - Handle to the subscription the user wishes to reject
*            statusCode - The rejection response code.
*            strReasonPhrase - Reason phrase to be set in the sent reject message.
*                        (May be NULL, to set a default reason phrase.)
***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsRespondReject (
                                         IN  RvSipSubsHandle  hSubs,
                                         IN  RvUint16         statusCode,
                                         IN  RvChar*          strReasonPhrase);


/***************************************************************************
 * RvSipSubsAutoRefresh
 * ------------------------------------------------------------------------
 * General: Set the autoRefresh flag of a specific subscription.
 *          When autoRefresh is set to RV_TRUE, an automatic refreshing subscribe
 *          request is sent when needed.
 *          This parameter default value is taken from configuration.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hSubs  - Handle to the subscription.
 *            bAutoRefresh - RV_TRUE to set on auto refresh, RV_FALSE to set it off.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsAutoRefresh (
                                         IN  RvSipSubsHandle  hSubs,
                                         IN  RvBool           bAutoRefresh);


/***************************************************************************
 * RvSipSubsSetAlertTimer
 * ------------------------------------------------------------------------
 * General: Set the alert timer value of a specific subscription.
 *          Alert timer value defines when an alert before expiration of a
 *          subscription, is given.
 *          This parameter default value is taken from configuration.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hSubs  - Handle to the subscription.
 *            alertValue - value in milliseconds.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsSetAlertTimer(
                                         IN  RvSipSubsHandle  hSubs,
                                         IN  RvInt32          alertValue);

/***************************************************************************
* RvSipSubsSetNoNotifyTimer
* ------------------------------------------------------------------------
* General: Set the no-notify timer value of a specific subscription.
*          No-Notify timer value defines when the subscription is terminated,
*          if no notify request is received and accepted after 2xx on
*          subscribe request was received.
*          This parameter default value is taken from configuration.
* Return Value: RvStatus
* ------------------------------------------------------------------------
* Arguments:
* Input:     hSubs         - Handle to the subscription.
*            noNotifyValue - Value in milliseconds.
***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsSetNoNotifyTimer(
                                          IN  RvSipSubsHandle  hSubs,
                                          IN  RvInt32          noNotifyValue);

/***************************************************************************
 * RvSipSubsTerminate
 * ------------------------------------------------------------------------
 * General: Terminates a subscription without sending any messages (unsubscribe or
 *          notify(terminated)). The subscription will assume the Terminated state.
 *          Calling this function will cause an abnormal termination.
 *          All notifications and transactions related to the subscription will be
 *          terminated as well.
 *          If this is subscription was created with no related call-leg,
 *          the subscription dialog will be terminated as well.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hSubs  - Handle to the subscription the user wishes to terminate.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsTerminate (IN  RvSipSubsHandle   hSubs);

/***************************************************************************
* RvSipSubsDetachOwner
* ------------------------------------------------------------------------
 * General: Detach the Subscription object from its owner. After calling this function
 *          the user will stop receiving events for this Subscription object. This function
 *          can be called only when the object is in terminated state.
* Return Value: RvStatus
* ------------------------------------------------------------------------
* Arguments:
* Input:     hSubs  - Handle to the subscription the user wishes to detach from owner.
***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsDetachOwner (
                                               IN  RvSipSubsHandle   hSubs);

/***************************************************************************
 * RvSipSubsUpdateSubscriptionTimer
 * ------------------------------------------------------------------------
 * General: Sets the subscription timer. when RvSipSubsSubscriptionExpiredEv
 *          callback function is called, the subscription timer is no longer
 *          active. calling this function will activate this timer again.
 *          (on next expiration, RvSipSubsSubscriptionExpiredEv will be called again).
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hSubs           - Handle to the subscription object.
 *          expirationValue - The expiration value, in milli-seconds.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsUpdateSubscriptionTimer(
                                     IN  RvSipSubsHandle   hSubs,
                                     IN  RvInt32           expirationValue);

/*-----------------------------------------------------------------------
       S U B S C R I P T I O N - S R V   A U T H    F U N C T I O N S
 ------------------------------------------------------------------------*/
/***************************************************************************
 * RvSipSubsAuthBegin - Server authentication
 * ------------------------------------------------------------------------
 * General: Begin the server authentication process. challenge an incoming
 *          SUBSCRIBE, REFER or NOTIFY request.
 *          If the request is SUBSCRIBE or REFER, hSubs handle should be given,
 *          and hNotify should be NULL.
 *          If the request is NOTIFY, hNotify should be given, and
 *          hSubs should be NULL.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hSubs   - Handle to the subscription the user wishes to challenge.
 *          hNotify - Handle to the notification user wishes to challenge.
 ***************************************************************************/
RVAPI  RvStatus RVCALLCONV RvSipSubsAuthBegin(
                                           IN  RvSipSubsHandle    hSubs,
                                           IN  RvSipNotifyHandle  hNotify);

/***************************************************************************
 * RvSipSubsAuthProceed - Server authentication
 * ------------------------------------------------------------------------
 * General: The function order the stack to proceed in authentication procedure.
 *          actions options are:
 *          RVSIP_TRANSC_AUTH_ACTION_USE_PASSWORD
 *          - Check the given authorization header, with the given password.
 *
 *          RVSIP_TRANSC_AUTH_ACTION_SUCCESS
 *          - user had checked the authorization header by himself, and it is
 *            correct. (will cause RvSipSubsAuthCompletedEv() to be called,
 *            with status success)..
 *
 *          RVSIP_TRANSC_AUTH_ACTION_FAILURE
 *          - user wants to stop the loop that searchs for authorization headers.
 *            (will cause RvSipSubsAuthCompletedEv() to be called, with status failure).
 *
 *          RVSIP_TRANSC_AUTH_ACTION_SKIP
 *          - Order to skip the given header, and continue the authentication
 *            procedure with next header (if exists).
 *            (will cause RvSipSubsAuthCredentialsFoundEv() to be called, or
 *            RvSipSubsAuthCompletedEv(failure) if there are no more
 *            authorization headers.
 *
 * Return Value: RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hSubs -          Handle to the subscription user challenges.
 *          hNotify -        Handle to the notification user challenges.
 *          action -         With which action to proceed. (see above)
 *          hAuthorization - Handle of the authorization header that the function
 *                           will check authentication for. (needed if action is
 *                           RVSIP_TRANSC_AUTH_ACTION_USE_PASSWORD, else NULL.)
 *          password -       The password for the realm+userName in the header.
 *                           (needed if action is
 *                           RVSIP_TRANSC_AUTH_ACTION_USE_PASSWORD, else NULL.)
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsAuthProceed(
                                   IN  RvSipSubsHandle                hSubs,
                                   IN  RvSipNotifyHandle              hNotify,
                                   IN  RvSipTransactionAuthAction     action,
                                   IN  RvSipAuthorizationHeaderHandle hAuthorization,
                                   IN  RvChar                        *password);


/***************************************************************************
 * RvSipSubsRespondUnauthenticated - Server authentication
 * ------------------------------------------------------------------------
 * General: Sends 401/407 response on a SUBSCRIBE, REFER or NOTIFY request.
 *          Add a copy of the given header to the response message.
 *          The given header should contain the authentication parameters.
 *          (should be of Authentication header type or Other header type)
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hSubs -          Handle to the subscription..
 *          hNotify -        Handle to the notification.
 *          responseCode -   401 or 407.
 *          strReasonPhrase - May be NULL, for default reason phrase.
 *          headerType -     The type of the given header
 *          hHeader -        Pointer to the header to be set in the msg.
 ***************************************************************************/
RVAPI  RvStatus RVCALLCONV RvSipSubsRespondUnauthenticated(
                                   IN  RvSipSubsHandle      hSubs,
                                   IN  RvSipNotifyHandle    hNotify,
                                   IN  RvUint16            responseCode,
                                   IN  RvChar*             strReasonPhrase,
                                   IN  RvSipHeaderType      headerType,
                                   IN  void*                hHeader);


/***************************************************************************
 * RvSipSubsRespondUnauthenticatedDigest - Server authentication
 * ------------------------------------------------------------------------
 * General: Sends 401/407 response on a SUBSCRIBE, REFER or NOTIFY request.
 *          Build an authentication header containing all given parameters,
 *          and add it to the response message.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hSubs -          Handle to the subscription..
 *          hNotify -        Handle to the notification.
 *          responseCode -   401 or 407
 *          strReasonPhrase - May be NULL, for default reason phrase.
 *          strRealm -       mandatory.
 *          strDomain -      Optional string. may be NULL.
 *          strNonce -       Optional string. may be NULL.
 *          strOpaque -      Optional string. may be NULL.
 *          bStale -         TRUE or FALSE
 *          eAlgorithm -     enumeration of algorithm. if RVSIP_AUTH_ALGORITHM_OTHER
 *                           the algorithm value is taken from the the next argument.
 *          strAlgorithm -   String of algorithm. this parameters will be set only if
 *                           eAlgorithm parameter is set to be RVSIP_AUTH_ALGORITHM_OTHER.
 *          eQop -           enumeration of qop. if RVSIP_AUTH_QOP_OTHER, the qop value
 *                           will be taken from the next argument.
 *          strQop -         String of qop. this parameter will be set only if eQop
 *                           argument is set to be RVSIP_AUTH_QOP_OTHER.
 ***************************************************************************/
RVAPI  RvStatus RVCALLCONV RvSipSubsRespondUnauthenticatedDigest(
                                   IN  RvSipSubsHandle    hSubs,
                                   IN  RvSipNotifyHandle  hNotify,
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
       S U B S C R I P T I O N - N O T I F Y  F U N C T I O N S
 ------------------------------------------------------------------------*/
/***************************************************************************
 * RvSipSubsCreateNotify
 * ------------------------------------------------------------------------
 * General: Creates a new notification object, related to a given subscription
 *          and exchange handles with the application notification object.
 *          For setting notify state information in the NOTIFY request, before
 *          sending, use RvSipNotifyGetOutboundMsg function.
 *
 * Return Value: RV_ERROR_INVALID_HANDLE - The handle to the subscription is invalid.
 *               RV_ERROR_NULLPTR        - Bad pointer was given by the application.
 *               RV_ERROR_OUTOFRESOURCES - Not enough memory to allocate.
 *               RV_OK                   - Success.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hSubs      - Handle to the subscription, relates to the new notification.
 *            hAppNotify - Handle to the application notification object.
 * Output:    phNotify   - Handle to the new created notification object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsCreateNotify(IN  RvSipSubsHandle      hSubs,
                                                IN  RvSipAppNotifyHandle hAppNotify,
                                                OUT RvSipNotifyHandle    *phNotify);

/***************************************************************************
 * RvSipSubsNotifyCreate
 * ------------------------------------------------------------------------
 * General: This function is DEPRECATED!!!
 *          you should use RvSipSubsCreateNotify instead.
 *          note that the retrieved message handle is for one notify request,
 *          after sending this notify request you must not use this message handle
 *          again.
 * Return Value: RV_ERROR_INVALID_HANDLE - The handle to the subscription is invalid.
 *               RV_ERROR_NULLPTR        - Bad pointer was given by the application.
 *               RV_ERROR_OUTOFRESOURCES - Not enough memory to allocate.
 *               RV_OK                   - Success.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hSubs       - Handle to the subscription, relates to the new notification.
 *          hAppNotify  - Handle to the application notification object.
 * Output:  phNotify    - Handle to the new created notification object.
 *          phNotifyMsg - Handle to the notify message that was constructed inside
 *                        the notification object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsNotifyCreate(
                                   IN  RvSipSubsHandle      hSubs,
                                   IN  RvSipAppNotifyHandle hAppNotify,
                                   OUT RvSipNotifyHandle    *phNotify,
                                   OUT RvSipMsgHandle       *phNotifyMsg);

/***************************************************************************
 * RvSipNotifySend
 * ------------------------------------------------------------------------
 * General: Sends the notify message placed in the notification object.
 *
 * Return Value: RV_ERROR_INVALID_HANDLE -  The handle to the notification is invalid.
 *               RV_ERROR_ILLEGAL_ACTION -  Invalid subscription state for this action.
 *               RV_ERROR_UNKNOWN        -  Failed to send the notify request.
 *               RV_OK                   -  Sent successfully.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hNotify    - Handle to the notification object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipNotifySend(IN  RvSipNotifyHandle hNotify);


/***************************************************************************
* RvSipNotifyAccept
* ------------------------------------------------------------------------
* General: Sends a 200 response on a NOTIFY request, and destruct the notification
*          object. 
*          The function influence the subscription state machine as follows:
*          state SUBS_Sent + accepting Notify(active or pending) ->
*                                        moves to state SUBS_Notify_Before_2xx_Rcvd.
*          state SUBS_2xx_Rcvd + accepting Notify(pending) -> state SUBS_Pending.
*          state SUBS_2xx_Rcvd + accepting Notify(active) -> state SUBS_Active.
*          state SUBS_Pending + accepting Notify(active) -> state SUBS_Active.
*          all states + accepting Notify(terminated) -> state SUBS_Terminated.
* Return Value: RV_ERROR_INVALID_HANDLE -  The handle to the notification is invalid.
*               RV_ERROR_UNKNOWN        -  Failed to send the 200 response.
*               RV_OK                   -  Response was sent successfully.
* ------------------------------------------------------------------------
* Arguments:
* Input:   hNotify    - Handle to the notification object.
***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipNotifyAccept(IN  RvSipNotifyHandle hNotify);


/***************************************************************************
* RvSipNotifyReject
* ------------------------------------------------------------------------
* General: Sends a non-2xx response on a NOTIFY request, and destruct the
*          notification object.
*          This function does not influence the subscription state machine.
* Return Value: RV_ERROR_INVALID_HANDLE -  The handle to the notification is invalid.
*               RV_ERROR_UNKNOWN        -  Failed to send the response.
*               RV_OK                   -  Response was sent successfully.
* ------------------------------------------------------------------------
* Arguments:
* Input:    hNotify    - Handle to the notification object.
*           statusCode - Response code.
***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipNotifyReject(IN  RvSipNotifyHandle hNotify,
                                            IN  RvUint16          statusCode);


/***************************************************************************
 * RvSipNotifyTerminate
 * ------------------------------------------------------------------------
 * General: Terminates a notification object without sending any messages.
 *          The notification object will inform of the Terminated status.
 *          Calling this function will cause an abnormal termination.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hNotify    - Handle to the notification object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipNotifyTerminate (IN  RvSipNotifyHandle hNotify);

/***************************************************************************
* RvSipNotifyDetachOwner
* ------------------------------------------------------------------------
 * General: Detach the Notify object from its owner. After calling this function
 *          the user will stop receiving events for this Notify object. This function
 *          can be called only when the object is in terminated state.
* Return Value: RvStatus
* ------------------------------------------------------------------------
* Arguments:
* Input:    hNotify    - Handle to the notification object.
***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipNotifyDetachOwner (IN  RvSipNotifyHandle hNotify);

/***************************************************************************
 * RvSipNotifyGetOutboundMsg
 * ------------------------------------------------------------------------
 * General: Gets the message (request or response) that is going to be sent
 *          by the notification. You may get the message only in states where
 *          notification may send a message.
 *          You can call this function before you call a control API functions
 *          that sends a message (e.g. RvSipNotifySend() or RvSipNotifyAccept()).
 *          Note: The message you receive from this function is not complete.
 *          In some cases it might even be empty.
 *          You should use this function to add headers and body to the message 
 *          before it is sent. 
 *          To view the complete message use event message to send.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hNotify -  The notification handle.
 * Output:  phMsg   -  pointer to the message.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipNotifyGetOutboundMsg(
                                     IN  RvSipNotifyHandle  hNotify,
                                     OUT RvSipMsgHandle        *phMsg);

/***************************************************************************
* RvSipNotifyGetSubsState
* ------------------------------------------------------------------------
* General: Returns the value of the Subscription-State header, that was
*          set by application to the NOTIFY message of this notify object.
* Return Value: RvStatus
* ------------------------------------------------------------------------
* Arguments:
* Input:    hNotify    - Handle to the notification object.
* Output:   peSubsState - The SubsState: active, pending, terminated or other.
***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipNotifyGetSubsState (
                                    IN  RvSipNotifyHandle hNotify,
                                    OUT RvSipSubscriptionSubstate* peSubsState);

/***************************************************************************
 * RvSipNotifySetSubscriptionStateParams
 * ------------------------------------------------------------------------
 * General: Create and set the Subscription-State header in the notification object.
 *          This header will be set to the outbound NOTIFY request.
 * Return Value: RV_ERROR_INVALID_HANDLE -  The handle to the notification is invalid.
 *               RV_ERROR_UNKNOWN        -  General Failure.
 *               RV_OK                   -  Set successfully.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hNotify    - Handle to the notification object.
 *          eSubsState - SubsState to set in Subscription-State header.
 *          eReason    - reason to set in Subscription-State header
 *                       (RVSIP_SUBSCRIPTION_REASON_UNDEFINED for no reason).
 *          expiresParamVal - expires parameter value to set in Subscription-State
 *                       header (may be UNDEFINED)
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipNotifySetSubscriptionStateParams(
                                    IN  RvSipNotifyHandle         hNotify,
                                    IN  RvSipSubscriptionSubstate eSubsState,
                                    IN  RvSipSubscriptionReason   eReason,
                                    IN  RvInt32                   expiresParamVal);

/***************************************************************************
 * RvSipNotifyGetStackInstance
 * ------------------------------------------------------------------------
 * General: Returns the handle to the stack instance to which this notification
 *          object belongs to.
 *
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hNotify         - The notification handle.
 * Output:    phStackInstance - A valid pointer which will be updated with a
 *                              handle to the stack instance.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipNotifyGetStackInstance(
                                     IN  RvSipNotifyHandle   hNotify,
                                     OUT void                **phStackInstance);
/*-----------------------------------------------------------------------
        D N S   A P I
 ------------------------------------------------------------------------*/
/***************************************************************************
 * RvSipSubsDNSGiveUp
 * ------------------------------------------------------------------------
 * General: This function is for use at MSG_SEND_FAILURE state of a subscription
 *          or notification object.
 *          Calling to this function, stops the sending of the request message,
 *          and returns the state machine to its previous state.
 *          You can use this function for a SUBSCRIBE, REFER or NOTIFY request.
 *          For SUBSCRIBE and REFER messages, use it if state was changed to
 *          MSG_SEND_FAILURE state. in this case set hNotify to be NULL.
 *          Use this function for a NOTIFY request, if you were informed of the
 *          MSG_SEND_FAILURE status in RvSipSubsNotifyEv() event. In this case,
 *          you should supply the notify handle.
 * Return Value: RV_ERROR_INVALID_HANDLE - The handles to the objects are invalid.
 *               RV_ERROR_ILLEGAL_ACTION - Invalid state for this action.
 *               RV_ERROR_OUTOFRESOURCES - Request failed due to resource problem.
 *               RV_ERROR_UNKNOWN        - General failure.
 *               RV_OK                   - Success.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hSubs    - Handle to the subscription that sent the request.
 *          hNotify  - Handle to the notify object, in case of notify request.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsDNSGiveUp (IN  RvSipSubsHandle   hSubs,
                                              IN  RvSipNotifyHandle hNotify);

/***************************************************************************
 * RvSipSubsDNSContinue
 * ------------------------------------------------------------------------
 * General: This function is for use at MSG_SEND_FAILURE state of a subscription
 *          or notification object.
 *          The function creates a new cloned transaction, with a new DNS
 *          list, and terminates the old transaction. Application may get
 *          the outbound message at this stage, and set information to it
 *          (the same information that was set in the message of the original
 *          transaction). When message is ready, application should send
 *          the new message to the next ip address with RvSipSubsDNSReSendRequest()
 *          You can use this function for a SUBSCRIBE, REFER or NOTIFY request.
 *          For SUBSCRIBE and REFER messages, use it if state was changed to
 *          MSG_SEND_FAILURE state. in this case set hNotify to be NULL.
 *          Use this function for a NOTIFY request, if you were informed of the
 *          MSG_SEND_FAILURE status in RvSipSubsNotifyEv() event.
 *          In this case, you should supply the notify handle.
 * Return Value: RV_ERROR_INVALID_HANDLE - The handles to the objects are invalid.
 *               RV_ERROR_ILLEGAL_ACTION - Invalid state for this action.
 *               RV_ERROR_OUTOFRESOURCES - Request failed due to resource problem.
 *               RV_ERROR_UNKNOWN        - General failure.
 *               RV_OK                   - Success.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hSubs    - Handle to the subscription that sent the request.
 *          hNotify  - Handle to the notify object, in case of notify request.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsDNSContinue (IN  RvSipSubsHandle   hSubs,
                                                IN  RvSipNotifyHandle hNotify);

/***************************************************************************
 * RvSipSubsDNSReSendRequest
 * ------------------------------------------------------------------------
 * General: This function is for use at MSG_SEND_FAILURE state of a subscription
 *          or notification object.
 *          Calling to this function, re-send the cloned transaction to the next ip
 *          address, and change state of the state machine back to the sending
 *          state.
 *          Note - Before calling this function, you should set all information
 *          that you set in the message at the first sending, (such as notify body)
 *          (You may use RvSipSubsGetOutboundMsg() API function, and then
 *          set your parameters to this message).
 *
 *          You can use this function for a SUBSCRIBE, REFER or NOTIFY request.
 *          For SUBSCRIBE and REFER messages, use it if state was changed to
 *          MSG_SEND_FAILURE state. in this case set hNotify to be NULL.
 *          Use this function for a NOTIFY request, if you were informed of the
 *          MSG_SEND_FAILURE status in RvSipSubsNotifyEv() event. In this case,
 *          you should supply the notify handle.
 *
 * Return Value: RV_ERROR_INVALID_HANDLE - The handles to the objects are invalid.
 *               RV_ERROR_ILLEGAL_ACTION - Invalid state for this action.
 *               RV_ERROR_OUTOFRESOURCES - Request failed due to resource problem.
 *               RV_ERROR_UNKNOWN        - General failure.
 *               RV_OK                   - Success.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hSubs    - Handle to the subscription that sent the request.
 *          hNotify  - Handle to the notify object, in case of notify request.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsDNSReSendRequest(IN  RvSipSubsHandle   hSubs,
                                                    IN  RvSipNotifyHandle hNotify);

/***************************************************************************
* RvSipSubsDNSGetList
* ------------------------------------------------------------------------
* General: Returns DNS list object from the transaction object.
*          You can use this function for a SUBSCRIBE, REFER or NOTIFY request.
*          For a SUBSCRIBE or REFER message, use it if state was changed to
*          MSG_SEND_FAILURE state. in this case set hNotify to be NULL.
*          Use this function for a NOTIFY request, if you were informed of the
*          MSG_SEND_FAILURE status in RvSipSubsNotifyEv() event.
*          In this case, you should supply the notify handle.
* Return Value: RV_OK or RV_ERROR_BADPARAM
* ------------------------------------------------------------------------
* Arguments:
* Input:   hSubs     - Handle to the subscription that sent the request.
*          hNotify   - Handle to the notify object, in case of notify request.
* Output   phDnsList - DNS list handle
***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsDNSGetList(
                                   IN  RvSipSubsHandle   hSubs,
                                   IN  RvSipNotifyHandle hNotify,
                                   OUT RvSipTransportDNSListHandle *phDnsList);

/*-----------------------------------------------------------------------
       R E F E R   S U B S C R I P T I O N  A P I
 ------------------------------------------------------------------------*/
/***************************************************************************
 * RvSipSubsReferInit
 * ------------------------------------------------------------------------
 * General: Initiate a refer subscription with it's refer parameters:
 *          refer-to and referred-by headers. (refer-to is mandatory).
 *          If the subscription was not created inside of a call-leg you must
 *          also initiate its dialog parameters first, by calling RvSipSubsDialogInit()
 *          before calling this function.
 *          This function initialized the refer subscription, but do not send
 *          any request. Use RvSipSubsRefer() for sending a refer request.
 * Return Value: RV_ERROR_INVALID_HANDLE    - The handle to the subscription is invalid.
 *               RV_ERROR_ILLEGAL_ACTION    - Invalid subscription state for this action.
 *               RV_ERROR_OUTOFRESOURCES    - subscription failed to create a new header.
 *               RV_ERROR_BADPARAM          - Bad parameter was given by the application.
 *               RV_ERROR_NULLPTR           - Bad pointer was given by the application.
 *               RV_OK                      - Initialization was done successfully.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hSubs       - Handle to the subscription the user wishes to initialize.
 *          hReferTo    - Handle to a refer-to header to set in the subscription.
 *          hReferredBy - Handle to a referred-by header to set in the subscription.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsReferInit(
                                 IN  RvSipSubsHandle             hSubs,
                                 IN  RvSipReferToHeaderHandle    hReferTo,
                                 IN  RvSipReferredByHeaderHandle hReferredBy);

/***************************************************************************
 * RvSipSubsReferInitStr
 * ------------------------------------------------------------------------
 * General: Initiate a refer subscription with it's refer parameters in a string format:
 *          refer-to and referred-by headers. (refer-to is mandatory), and optional
 *          repleaces header, to be set in the refer-to header.
 *          If the subscription was not created inside of a call-leg you must
 *          also initiate its dialog parameters first, by calling RvSipSubsDialogInit()
 *          before calling this function.
 *          This function initialized the refer subscription, but do not send
 *          any request. Use RvSipSubsRefer() for sending a refer request.
 * Return Value: RV_ERROR_INVALID_HANDLE - The handle to the subscription is invalid.
 *               RV_ERROR_ILLEGAL_ACTION - Invalid subscription state for this action.
 *               RV_ERROR_OUTOFRESOURCES - subscription failed to create a new header.
 *               RV_ERROR_BADPARAM - Bad parameter was given by the application.
 *               RV_ERROR_NULLPTR - Bad pointer was given by the application.
 *               RV_OK - Initialization was done successfully.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hSubs         - Handle to the subscription the user wishes to initialize.
 *          strReferTo    - String of the Refer-To header value.
 *                          for Example: "A<sip:176.56.23.4:4444;method=INVITE>"
 *          strReferredBy - String of the Referred-By header value.
 *                          for Example: "<sip:176.56.23.4:4444>"
 *          strReplaces  -  The Replaces header to be set in the Refer-To header of
 *                          the REFER request. The Replaces header string must not
 *                          contain the 'Replaces:' prefix.
 *                          The Replaces header will be kept in the Refer-To header 
 *                          of the subscription object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsReferInitStr(
                                 IN  RvSipSubsHandle hSubs,
                                 IN  RvChar*        strReferTo,
                                 IN  RvChar*        strReferredBy,
                                 IN  RvChar*        strReplaces);

/***************************************************************************
 * RvSipSubsRefer
 * ------------------------------------------------------------------------
 * General: Establishes a refer subscription by sending a REFER request.
 *          This function may be called only after the subscription was initialized
 *          with To, From, Refer-To and optional Referred-By parameters.
 *          (If this is a subscription of an already established call-leg, To and
 *          From parameters are taken from the call-leg).
 *          Calling this function causes a REFER to be sent out, and the
 *          subscription state machine to progress to the Subs_Sent state.
 * Return Value: RV_ERROR_INVALID_HANDLE - The handle to the subscription is invalid.
 *               RV_ERROR_ILLEGAL_ACTION - Invalid subscription state for this action.
 *               RV_ERROR_OUTOFRESOURCES - Subscription failed to create a new transaction.
 *               RV_ERROR_UNKNOWN        - An error occurred while trying to send the
 *                                         message (Couldn't send a message to the given
 *                                         Request-Uri).
 *               RV_OK                   - Refer message was sent successfully.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hSubs - Handle to the subscription the user wishes to refer.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsRefer(IN  RvSipSubsHandle   hSubs);


/***************************************************************************
 * RvSipSubsReferAccept
 * ------------------------------------------------------------------------
 * General: Sends a 202 response on a REFER request and updates the
 *          subscription state machine.
 *
 *          Accepting of the REFER request, creates a new object associated
 *          with the refer subscription.
 *          The type of the new object is according to the method parameter
 *          in the URL of the Refer-To header.
 *          if method=SUBSCRIBE or method=REFER, a new subscription object is created.
 *          if method=INVITE or no method parameter exists in the Refer-To URL,
 *          a new call-leg object is created.
 *          for all other methods - a new transaction object is created.
 *          The new created object contains the following parameters:
 *          Call-Id: The Call-Id of the REFER request,
 *          To:      The Refer-To header of the REFER request,
 *          From:    The local contact of the refer subscription.
 *          Referred-By: The Referred-By header of the RFEER request.
 *          Event:   In case of method = SUBSCRIBE.
 *          Refer-To: in case of method=REFER.
 *
 *          This function associates the refer subscription only with dialog-creating
 *          objects (call-leg or subscription). This means that the callback
 *          RvSipSubsReferNotifyReadyEv will be called only if the new object is
 *          call-leg or subscription. In case of a new transaction object, application 
 *          has to save the association by itself.
 *
 *          application should check the method parameter, in order to know which
 *          application object to allocate (and to give in the hAppNewObj argument), 
 *          and which handle type to supply this function as an output parameter.
 *
 *          To complete the acceptens of the REFER request the application must
 *          use the newly created object and establish it by calling to
 *          RvSipCallLegConnect in case of a new call-leg, RvSipSubsSubscribe in
 *          case of a new subscription, RvSipSubsRefer in case of a new refer
 *          subscription.
 *
 *          Note that this function does not send a notify request!!!
 *          It is the responsibility of the application to create and send an initializing
 *          notify(active) request. (application can do it from RvSipSubsReferNotifyReadyEv
 *          callback).
 *
 * Return Value: RV_ERROR_INVALID_HANDLE -  The handle to the subscription is invalid.
 *               RV_ERROR_ILLEGAL_ACTION -  Invalid subscription state for this action.
 *               RV_ERROR_UNKNOWN        -  Failed to accept the request. (failed
 *                                          while trying to send the 202 response).
 *               RV_OK                   -  Accept. final response was sent successfully.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hSubs      - Handle to the subscription the user wishes to accept.
 *          hAppNewObj - Handle to the new application object. (RvSipAppCallLegHandle
 *                       in case of method=INVITE or no method parameter,
 *                       RvSipAppSubsHandle in case of method=SUBSCRIBE/REFER
 *                       RvSipAppTranscHandle in all other cases).
 *          eForceObjType - In case application wants to force the stack to create
 *                       a specific object type (e.g. create a transaction and
 *                       not call-leg for method=INVITE in the refer-to url) it
 *                       can set the type in this argument. otherwise it should be 
 *                       RVSIP_COMMON_STACK_OBJECT_TYPE_UNDEFINED.
 * Output:  peCreatedObjType - The type of object that was created by stack.
 *                       if application gave eForceObjType parameter, it will be
 *                       equal to eForceObjType. Otherwise it will be according
 *                       to the method parameter in the refer-to url.
 *          phNewObj   - Handle to the new object that was created by SIP Stack.
 *                       (RvSipCallLegHandle in case of method=INVITE or no
 *                       method parameter,
 *                       RvSipSubsHandle in case of method=SUBSCRIBE/REFER,
 *                       RvSipTranscHandle in all other cases).
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsReferAccept (
                                IN    RvSipSubsHandle             hSubs,
                                IN    void*                       hAppNewObj,
                                IN    RvSipCommonStackObjectType  eForceObjType,
                                OUT   RvSipCommonStackObjectType *peCreatedObjType,
                                OUT   void*                      *phNewObj);

/***************************************************************************
 * RvSipNotifySetReferNotifyBody
 * ------------------------------------------------------------------------
 * General: Builds the body for a notify request of a refer subscription.
 *          The function sets the correct body and content-type header
 *          in the notify outbound message.
 * Return Value: RV_ERROR_INVALID_HANDLE -  The handle to the notification is invalid.
 *               RV_ERROR_UNKNOWN        -  Failed to set the notify body.
 *               RV_OK                   -  set successfully.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hNotify    - Handle to the notification object.
 *          statusCode - status code to be set in NOTIFY message body.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipNotifySetReferNotifyBody(
                                            IN  RvSipNotifyHandle   hNotify,
                                            IN  RvInt16             statusCode);

/***************************************************************************
* RvSipSubsGetReferToHeader
* ------------------------------------------------------------------------
* General: Returns the Refer-To header associated with the subscription.
*
* Return Value: RV_ERROR_INVALID_HANDLE  - The subscription handle is invalid.
*               RV_ERROR_NULLPTR         - Bad pointer was given by the application.
*               RV_OK                    - Refer-To header was returned successfully.
* ------------------------------------------------------------------------
* Arguments:
* Input:     hSubs     - Handle to the subscription.
* Output:    phReferTo - Pointer to the subscription Refer-To header handle.
***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsGetReferToHeader (
                                IN  RvSipSubsHandle        hSubs,
                                OUT RvSipReferToHeaderHandle *phReferTo);

/***************************************************************************
* RvSipSubsGetReferredByHeader
* ------------------------------------------------------------------------
* General: Returns the Referred-By header associated with the subscription.
*
* Return Value: RV_ERROR_INVALID_HANDLE  - The subscription handle is invalid.
*               RV_ERROR_NULLPTR         - Bad pointer was given by the application.
*               RV_OK                    - Referred-By header was returned successfully.
* ------------------------------------------------------------------------
* Arguments:
* Input:     hSubs   - Handle to the subscription.
* Output:    phReferredBy - Pointer to the subscription Referred-By header handle.
***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsGetReferredByHeader (
                            IN  RvSipSubsHandle             hSubs,
                            OUT RvSipReferredByHeaderHandle *phReferredBy);

/***************************************************************************
* RvSipSubsGetReferFinalStatus
* ------------------------------------------------------------------------
* General: Returns the status code that was received in the body of the final 
*          notify request of a refer subscription.
*
* Return Value: RV_ERROR_INVALID_HANDLE  - The subscription handle is invalid.
*               RV_ERROR_NULLPTR         - Bad pointer was given by the application.
*               RV_OK                    - final status was returned successfully.
* ------------------------------------------------------------------------
* Arguments:
* Input:  hSubs             - Handle to the subscription.
* Output: pReferFinalStatus - Pointer to the refer final status value.
***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsGetReferFinalStatus (
                                        IN  RvSipSubsHandle  hSubs,
                                        OUT RvInt32        *pReferFinalStatus);


/*-----------------------------------------------------------------------
       S U B S C R I P T I O N:  G E T   A N D   S E T    A P I
 ------------------------------------------------------------------------*/
                                        
/***************************************************************************
* RvSipSubsIsOutOfBand
* ------------------------------------------------------------------------
* General: Indicates whether the given subscription is an out-of-band subscription.
* Return Value: RV_ERROR_INVALID_HANDLE  - The subscription handle is invalid.
*               RV_OK - Success.
* ------------------------------------------------------------------------
* Arguments:
* Input:   hSubs - Handle to the subscription.
* Output:  pbIsOutOfBand - A valid pointer which will be updated with the
*                          subscription out-of-band boolean.
***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsIsOutOfBand (IN  RvSipSubsHandle hSubs,
                                                OUT RvBool*         pbIsOutOfBand);

/***************************************************************************
 * RvSipSubsSetEventHeader
 * ------------------------------------------------------------------------
 * General: Sets the event header associated with the subscription. 
 *          Note that the event header identify the subscription, so you must not
 *          change it after subscription was initialized.
 * Return Value: RV_ERROR_INVALID_HANDLE  - The subscription handle is invalid.
 *               RV_ERROR_NULLPTR         - Bad pointer was given by the application.
 *               RV_OK                    - Event header was set successfully.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hSubs  - Handle to the subscription.
 *            hEvent - Handle to an application constructed event header to be set
 *                     in the subscription object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsSetEventHeader (
                                      IN  RvSipSubsHandle         hSubs,
                                      IN  RvSipEventHeaderHandle  hEvent);

/***************************************************************************
 * RvSipSubsGetEventHeader
 * ------------------------------------------------------------------------
 * General: Returns the Event header associated with the subscription.
 *          Note that the event header identify the subscription,so you must not
 *          change it after subscription was initialized.
 * Return Value: RV_ERROR_INVALID_HANDLE  - The subscription handle is invalid.
 *               RV_ERROR_NULLPTR         - Bad pointer was given by the application.
 *               RV_OK                    - Event header was returned successfully.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hSubs   - Handle to the subscription.
 * Output:    phEvent - A valid pointer which will be updated with the Pointer to 
 *                      the subscription Event header handle.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsGetEventHeader (
                                      IN  RvSipSubsHandle        hSubs,
                                      OUT RvSipEventHeaderHandle *phEvent);


/***************************************************************************
 * RvSipSubsSetExpiresVal
 * ------------------------------------------------------------------------
 * General: Sets the expires header value (in seconds) associated with the subscription.
 *          You may set the expires value, only before sending the first subscribe
 *          request. later on you should change it only with API functions of
 *          refresh. This is because the expires value is set according to the 2xx
 *          response, or notify messages.
 *          You must not change it after subscription was initialized.
 * Return Value: RV_ERROR_INVALID_HANDLE  - The subscription handle is invalid.
 *               RV_OK - Expires value was set successfully.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hSubs      - Handle to the subscription.
 *          expiresVal - time for subscription expiration - in seconds.
 *                       value of this argument must be smaller than 0xFFFFFFF/1000.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsSetExpiresVal (
                                      IN  RvSipSubsHandle   hSubs,
                                      IN  RvInt32            expiresVal);


/***************************************************************************
 * RvSipSubsGetExpiresVal
 * ------------------------------------------------------------------------
 * General: Returns the Expires value of the subscription, in seconds.
 *          For notifier subscription: The function retrieve the last expires
 *          value that was set by notifier in 2xx response,
 *          or in a notify request.
 *          If notifier want the expires value from the incoming SUBSCRIBE
 *          request it should use RvSipSubsGetRequestedExpiresVal function.
 *          For subscriber subscription: The function retrieve the value that
 *          was set on initialization of the subscription, or updated
 *          value, in case notifier updated it already.
 * Return Value: RV_ERROR_INVALID_HANDLE  - The subscription handle is invalid.
 *               RV_ERROR_NULLPTR     - Bad pointer was given by the application.
 *               RV_OK        - Expires value was returned successfully.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hSubs   - Handle to the subscription.
 * Output:    pExpires - Pointer to the Expires value.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsGetExpiresVal (
                                      IN  RvSipSubsHandle   hSubs,
                                      OUT RvInt32          *pExpires);

/***************************************************************************
 * RvSipSubsGetRequestedExpiresVal
 * ------------------------------------------------------------------------
 * General: Returns the requested expires value, in seconds.
 *          When a new SUBSCRIBE request is received, it's expires value
 *          can be retrieve using this function.
 *          This function is relevant only for notifier subscription.
 *          (note - this function is different from RvSipSubsGetExpiresVal,
 *           because it only retrieve value, when there is an incoming SUBSCRIBE
 *           request, waiting for a response. RvSipSubsGetExpiresVal retrieve
 *           the last expires value that was set by notifier in 2xx response,
 *           or in a notify request).
 * Return Value: RV_ERROR_INVALID_HANDLE  - The subscription handle is invalid.
 *               RV_ERROR_NULLPTR         - Bad pointer was given by the application.
 *               RV_OK                    - Expires value was returned successfully.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hSubs             - Handle to the subscription.
 * Output:    pRequestedExpires - Pointer to the requested Expires value.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsGetRequestedExpiresVal (
                                   IN  RvSipSubsHandle   hSubs,
                                   OUT RvInt32          *pRequestedExpires);

/***************************************************************************
 * RvSipSubsGetRemainingTime
 * ------------------------------------------------------------------------
 * General: Returns the remaining time of a subscription, in seconds.
 *
 * Return Value: RV_ERROR_INVALID_HANDLE  - The subscription handle is invalid.
 *               RV_ERROR_NULLPTR         - Bad pointer was given by the application.
 *               RV_OK                    - Remaining time value was returned successfully.
 * Note -
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hSubs   - Handle to the subscription.
 * Output:    pRemainingTime - Pointer to the remaining time value.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsGetRemainingTime (
                                                   IN  RvSipSubsHandle   hSubs,
                                                   OUT RvInt32          *pRemainingTime);

/***************************************************************************
* RvSipSubsGetDialogObj
* ------------------------------------------------------------------------
* General: Returns handle to the dialog object, related to this subscription.
*          (the function is relevant for a subscription that was not created
*          in a connected call-leg).
*          The user can use this dialog handle to set or get parameters that
*          are kept inside the dialog, and not within the subscription
*          (such as call-Id, cseq, To, From and OutboundAddress).
*          You can get and set dialog parameters with the call-leg API functions.
*          Note - you must not change the dialog parameters after the subscription
*          was established.
* Return Value: RV_ERROR_INVALID_HANDLE  - The subscription handle is invalid.
*               RV_ERROR_NULLPTR         - Bad pointer was given by the application.
*               RV_OK                    - Dialog object was returned successfully.
* ------------------------------------------------------------------------
* Arguments:
* Input:     hSubs    - Handle to the subscription.
* Output:    phDialog - Pointer to the dialog handle.
***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsGetDialogObj (
                                                  IN  RvSipSubsHandle     hSubs,
                                                  OUT RvSipCallLegHandle *phDialog);

/***************************************************************************
* RvSipSubsSetAppSubsHandle
* ------------------------------------------------------------------------
* General: Sets the application subscription handle.
* Return Value: RV_ERROR_INVALID_HANDLE  - The subscription handle is invalid.
*               RV_OK                    - application handle was set successfully.
* ------------------------------------------------------------------------
* Arguments:
* Input:     hSubs    - Handle to the subscription.
*            hAppSubs - Handle to the application subscription.
***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsSetAppSubsHandle (
                                          IN  RvSipSubsHandle     hSubs,
                                          IN  RvSipAppSubsHandle  hAppSubs);

/***************************************************************************
* RvSipSubsGetAppSubsHandle
* ------------------------------------------------------------------------
* General: Returns the application subscription handle.
* Return Value: RV_ERROR_INVALID_HANDLE  - The subscription handle is invalid.
*               RV_ERROR_NULLPTR         - Bad pointer was given by the application.
*               RV_OK                    - application handle was returned successfully.
* ------------------------------------------------------------------------
* Arguments:
* Input:     hSubs     - Handle to the subscription.
* Output:    phAppSubs - Handle to the application subscription.
***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsGetAppSubsHandle (
                                          IN  RvSipSubsHandle     hSubs,
                                          OUT RvSipAppSubsHandle *phAppSubs);

/***************************************************************************
* RvSipSubsGetSubsMgr
* ------------------------------------------------------------------------
* General: Returns the subs manager handle and the application subs manager 
*          handle of the given subscription.
* Return Value: RvStatus
* ------------------------------------------------------------------------
* Arguments:
* Input:    hSubs        - Handle to the subscription.
* Output:   phSubsMgr    - The subs manager handle.
*           phSubsAppMgr - The application subs manager handle.
***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsGetSubsMgr (
                                        IN  RvSipSubsHandle     hSubs,
                                        OUT RvSipSubsMgrHandle *phSubsMgr,
                                        OUT void               **phSubsAppMgr);

/***************************************************************************
 * RvSipSubsGetCurrentState
 * ------------------------------------------------------------------------
 * General: Gets the subscription current state
 * Return Value: RV_ERROR_INVALID_HANDLE - if the given subscription handle is invalid
 *               RV_ERROR_NULLPTR    - Bad pointer was given by the application.
 *               RV_OK.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hSubs   - Handle to the subscription.
 * Output:    peState - The subscription current state.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsGetCurrentState (
                                      IN  RvSipSubsHandle    hSubs,
                                      OUT RvSipSubsState    *peState);

/***************************************************************************
* RvSipSubsGetSubsType
* ------------------------------------------------------------------------
* General: Gets the subscription type. A subscription can be either a
*          Subscriber or a Notifier.
* Return Value: RV_ERROR_INVALID_HANDLE - if the given subscription handle is invalid
*               RV_ERROR_NULLPTR    - Bad pointer was given by the application.
*               RV_OK.
* ------------------------------------------------------------------------
* Arguments:
* Input:    hSubs      - Handle to the subscription.
* Output:   peSubsType - The subscription type.
***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsGetSubsType (
                                     IN  RvSipSubsHandle        hSubs,
                                     OUT RvSipSubscriptionType  *peSubsType);

/***************************************************************************
 * RvSipSubsGetReceivedMsg
 * ------------------------------------------------------------------------
 * General: Gets the message that was received by the subscription. You can
 *          call this function from the state changed callback function
 *          when the new state indicates that a message was received.
 *          If there is no valid received message, NULL will be returned.
 *
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hSubs   - Handle to the subscription.
 * Output:    phMsg   - Pointer to the received message.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsGetReceivedMsg(
                                            IN  RvSipSubsHandle  hSubs,
                                            OUT RvSipMsgHandle  *phMsg);

/***************************************************************************
 * RvSipSubsGetOutboundMsg
 * ------------------------------------------------------------------------
 * General: Gets the message (request or response) that is going to be sent
 *          by the subscription. 
 *          You may get the message only in states where subscription may send a message.
 *          You can call this function before you call a control API functions
 *          that sends a message (such as RvSipSubsSubscribe()), or from
 *          the expirationAlert call-back function when a refresh message is
 *          going to be sent.
 *          Note: The outbound message you receive is not complete.
 *          In some cases it might even be empty.
 *          You should use this function to add headers to the message before
 *          it is sent. 
 *          To view the complete message use event message to send.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hSubs   - The subscription handle.
 * Output:    phMsg   - Pointer to the message.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsGetOutboundMsg(
                                     IN  RvSipSubsHandle     hSubs,
                                     OUT RvSipMsgHandle     *phMsg);

/***************************************************************************
 * RvSipSubsGetStackInstance
 * ------------------------------------------------------------------------
 * General: Returns the handle to the stack instance to which this subscription
 *          object belongs to.
 *
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hSubs     - Handle to the subscription object.
 * Output:    phStackInstance - A valid pointer which will be updated with a
 *                        handle to the stack instance.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsGetStackInstance(
                                     IN  RvSipSubsHandle     hSubs,
                                     OUT void                **phStackInstance);

/***************************************************************************
 * RvSipSubsGetEventPackageType
 * ------------------------------------------------------------------------
 * General: Return the event package type of the given subscription.
 * Return Value: RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hSubs         - Handle to the Subscription.
 * Output:  pePackageType - Pointer to the event package type.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsGetEventPackageType(
                            IN  RvSipSubsHandle            hSubs,
                            OUT RvSipSubsEventPackageType* pePackageType);


/***************************************************************************
* RvSipSubsGetNewHeaderHandle
* ------------------------------------------------------------------------
* General: The function allocates new header of type specified by user, on
*          the subscription page.
*          the function is available for headers that exists in a subscription
*          object: event, refer-to, referred-by.
*          Note that application must still assign this header to the subscription
*          object. (e.g. after getting new event header handle with this
*          function and filling it, application must call RvSipSubsSetEventHeader
*          to assign this header to the subscription object)
* Return Value: RV_ERROR_INVALID_HANDLE  - The subscription handle is invalid.
*               RV_ERROR_NULLPTR         - Bad pointer was given by the application.
*               RV_OK                    - Header was constructed successfully.
* ------------------------------------------------------------------------
* Arguments:
* Input:    hSubs       - Handle to the subscription.
*           eHeaderType - Type of header to allocate.
* Output:   phHeader    - Pointer to the new header handle.
***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsGetNewHeaderHandle (
                            IN  RvSipSubsHandle hSubs,
                            IN  RvSipHeaderType eHeaderType,
                            OUT void*           *phHeader);

/***************************************************************************
 * RvSipSubsGetTranscCurrentLocalAddress
 * ------------------------------------------------------------------------
 * General: Gets the local address that is used by a specific subscription
 *          transaction. 
 *          Supply a subscription handle to get local address of a subscribe transaction,
 *          or a notification handle to get local address of a notify transaction,.
 * Return Value: RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hSubs   - Handle to the subscription holding the transaction.
 *          hNotify - Handle to the notification holding the transaction.
 * Output:  eTransporType - The transport type(UDP, TCP, SCTP, TLS).
 *          eAddressType  - The address type(IP4 or IP6).
 *          localAddress  - The local address this transaction is using(must be longer than 48 bytes).
 *          localPort     - The local port this transaction is using.
 ***************************************************************************/
RVAPI  RvStatus RVCALLCONV RvSipSubsGetTranscCurrentLocalAddress(
                            IN  RvSipSubsHandle            hSubs,
                            IN  RvSipNotifyHandle          hNotify,
                            OUT RvSipTransport            *eTransportType,
                            OUT RvSipTransportAddressType *eAddressType,
                            OUT RvChar                   *localAddress,
                            OUT RvUint16                 *localPort);

/******************************************************************************
 * RvSipSubsSetForkingEnabledFlag
 * ----------------------------------------------------------------------------
 * General: Sets the "Forking Enabled" flag to the subscription.
 *          In case the SUBSCRIBE request was forked by proxy to several
 *          notifiers, the subscription may get NOTIFY requests from several
 *          notifiers, which are referred to as "Forked NOTIFY requests".
 *          Setting the "Forking Enabled" flag of the subscription to RV_TRUE
 *          will create a new Subscription object for each Forked NOTIFY
 *          request received for the original subscription (the subscription
 *          that sent the SUBSCRIBE request).
 *          Setting the "Forking Enabled" flag of a subscription to RV_FALSE
 *          will cause the original subscription to reject with a 481 response
 *          (No Matching Call) for every Forked NOTIFY request that is received
 *          For forking details, see sections 3.3.3 and 4.4.9 of RFC 3265.
 *
 * Return Value: RV_OK on success,
 *               Error Code, defined in RV_SIP_DEF.h or rverror.h, otherwise.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:    hSubs   - Handle to the subscription that sent the request.
 *           bForkingEnabled - Forking-enabled flag value.
 * Output:   none.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsSetForkingEnabledFlag(
                                                IN  RvSipSubsHandle hSubs,
                                                IN  RvBool          bForkingEnabled);

/******************************************************************************
 * RvSipSubsGetForkingEnabledFlag
 * ----------------------------------------------------------------------------
 * General: Gets the "Forking Enabled" flag to the subscription.
 *          In case the SUBSCRIBE request was forked by proxy to several
 *          notifiers, the subscription may get NOTIFY requests from several
 *          notifiers, which are referred to as "Forked NOTIFY requests".
 *          Setting the "Forking Enabled" flag of the subscription to RV_TRUE
 *          will create a new Subscription object for each Forked NOTIFY
 *          request received for the original subscription (the subscription
 *          that sent the SUBSCRIBE request).
 *          Setting the "Forking Enabled" flag of a subscription to RV_FALSE
 *          will cause the original subscription to reject with a 481 response
 *          (No Matching Call) for every Forked NOTIFY request that is received
 *          For forking details, see sections 3.3.3 and 4.4.9 of RFC 3265.
 *
 * Return Value: RV_OK on success,
 *               Error Code, defined in RV_SIP_DEF.h or rverror.h, otherwise.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:    hSubs            - Handle to the subscription that sent the request.
 * Output:   pbForkingEnabled - A requested flag value.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsGetForkingEnabledFlag(
                                                IN  RvSipSubsHandle hSubs,
                                                OUT RvBool          *pbForkingEnabled);

/******************************************************************************
* RvSipSubsGetOriginalSubs
* -----------------------------------------------------------------------------
* General:  Gets handle of the Original Subscription.
*           In case SUBSCRIBE request was forked by proxy to several notifiers,
*           subscription may get notify requests from several notifiers.
*           The original subscription, is the subscription that actually sent the
*           SUBSCRIBE request.
*           If no original subscription exists, NULL will be retrieved.
*           The function is intended for use with Forked Subscriptions.
*           For forking details see RFC 3265, sections 3.3.3 and 4.4.9.
*
* Return Value: RV_OK on success,
*               Error Code, defined in RV_SIP_DEF.h or rverror.h, otherwise.
* -----------------------------------------------------------------------------
* Arguments:
* Input:    hSubs   - Handle to the subscription that sent the request.
* Output:   phOriginalSubs  - A valid pointer which will be updated with the
*                     original subscription handle.
******************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsGetOriginalSubs(
                                        IN  RvSipSubsHandle hSubs,
                                        OUT RvSipSubsHandle *phOriginalSubs);


/*-----------------------------------------------------------------------
       SUBSCRIPTION   HIGH AVAILABILITY   F U N C T I O N S
 ------------------------------------------------------------------------*/
/***************************************************************************
 * RvSipSubsGetActiveSubsStorageSize
 * ------------------------------------------------------------------------
 * General: Gets the size of buffer needed to store all parameters of an active subs.
 *          (The size of buffer, that should be supplied in RvSipSubsStoreActiveSubs()).
 * Return Value:RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hSubs - Handle to the active subscription that will be stored.
 * Output:  pLen  - the size of buffer needed to store all subscription parameters. 
 *                  UNDEFINED in case of failure.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsGetActiveSubsStorageSize(
                                       IN  RvSipSubsHandle     hSubs,
                                       OUT RvInt32            *pLen); 

/***************************************************************************
 * RvSipSubsStoreActiveSubs
 * ------------------------------------------------------------------------
 * General: Copies all subscription parameters from a given subscription to a 
 *          given buffer.
 *          This buffer should be supplied when restoring the subscription.
 *          In order to store subs information the subscription must be in the
 *          active state.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hSubs    - Handle to the active subscription that will be stored.
 *          memBuff  - The buffer that will be filled with the subscription information.
 *          buffLen  - The length of the given buffer.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsStoreActiveSubs(
                                       IN RvSipSubsHandle    hSubs,
                                       IN void*              memBuff,
                                       IN RvUint32           buffLen);

/***************************************************************************
 * RvSipSubsRestoreActiveSubs
 * ------------------------------------------------------------------------
 * General: Restore all subscription information into a given subscription. 
 *          The subscription will assume the active state and all subscription
 *          parameters will be initialized from the given buffer.
 *          
 * Return Value:RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hSubs   - Handle to the restored active subscription.
 *          memBuff - The buffer that stores all the subscription information
 *          buffLen - The buffer size
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipSubsRestoreActiveSubs(
                                       IN RvSipSubsHandle    hSubs,
                                       IN void              *memBuff,
                                       IN RvUint32           buffLen);

#endif /*#ifndef RV_SIP_PRIMITIVES */

#ifdef __cplusplus
}
#endif


#endif /* END OF: #ifndef RV_SIP_SUBSCRIPTION_H */


