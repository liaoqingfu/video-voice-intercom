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
 *                              <RvSipRegClientTypes.h>
 *
 * The RvSipRegClientTypes.h file contains all type definitions and call-back
 * functions type definitions for the Register-Client module.
 *
 * Three types of handles are defined:
 * 1.RvSipRegClientMgrHandle
 * 2.RvSipRegClientHandle
 * 3.RvSipAppRegClientHandle
 * These handles are used when calling the API function.
 *
 *
 *    Author                         Date
 *    ------                        ------
 *    Tamar Barzuza                 Jan 2001
 *********************************************************************************/


#ifndef RV_SIP_REG_CLIENT_TYPES_H
#define RV_SIP_REG_CLIENT_TYPES_H

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
#include "RvSipCommonTypes.h"



/*-----------------------------------------------------------------------*/
/*                     COMMON TYPE DEFINITIONS                           */
/*-----------------------------------------------------------------------*/


/*
 * RvSipRegClientMgrHandle
 * ---------------------------------------------------------------------------
 * Declaration of handle to a register-clients manager instance. The manager
 * object manages all register-clients and its handle is needed in
 * all manager related API such as creation of new register-client.
 */
RV_DECLARE_HANDLE(RvSipRegClientMgrHandle);


/*
 * RvSipRegClientHandle
 * Declaration of a Register-Client handle. Register-Client handle is needed
 * in all Register-Client API function and is used to reference the
 * Register-Client object.
 */
RV_DECLARE_HANDLE(RvSipRegClientHandle);


/*
 * RvSipAppRegClientHandle
 * ----------------------------------------------------------------------
 * Declaration  of application handle to a Register-Client. This handle is
 * used by the application in order to associate sip stack Register-Client
 * objects with application Register-Client object. The application gives
 * the application handle when a new Register-Client is created. The sip
 * stack will give this handle back to the application in every callback
 * function.
 */
RV_DECLARE_HANDLE(RvSipAppRegClientHandle);



/*-----------------------------------------------------------------------*/
/*                    REG CLIENT TYPE DEFINITIONS                           */
/*-----------------------------------------------------------------------*/


/* RvSipRegClientState
 * ----------------------------------------------------------------------
 * RvSipRegClientState represents the state of a registration process. The
 * state changes are reported using the RvSipRegClientStateChangedEv call
 * back function together with a state change reason that may indicate to
 * the application how the new state was reached
 *
 * RVSIP_REG_CLIENT_STATE_IDLE:    Initial state for a newly created register-
 *                                 Client.
 *                                 The register-client will stay in this state
 *                                 until the Register() method will be called.
 * RVSIP_REG_CLIENT_STATE_REGISTERING: Register message was sent to the
 *                                     destination.
 * RVSIP_REG_CLIENT_STATE_REDIRECTED: A 3xx class response was received in the
 *                                    Registering state. The application may
 *                                    confirm the redirection by calling
 *                                    Register() method.
 * RVSIP_REG_CLIENT_STATE_UNAUTHENTICATED:  A 401 or 407 response was received
 *                                          in the Registering state. The
 *                                          application may try to authenticate
 *                                          the request by calling the
 *                                          Authenticate() method.
 * RVSIP_REG_CLIENT_STATE_REGISTERED: The Register request was accepted by the
 *                                    server. The Reg-Client is not terminated although the
 *                                    registration is successful
 * RVSIP_REG_CLIENT_STATE_FAILED: A 4xx, 5xx, or 6xx (other than 401, 407) was
 *                                received in the Registering state.
 * RVSIP_REG_CLIENT_STATE_TERMINATED: The final register-client state. The
 *                                    register-client resources were freed and
 *                                    the application must no longer reference
 *                                    this register-client object.
 */

typedef enum
{
    RVSIP_REG_CLIENT_STATE_UNDEFINED = -1,
    RVSIP_REG_CLIENT_STATE_IDLE,
    RVSIP_REG_CLIENT_STATE_TERMINATED,

    RVSIP_REG_CLIENT_STATE_REGISTERING,
    RVSIP_REG_CLIENT_STATE_REDIRECTED,
    RVSIP_REG_CLIENT_STATE_UNAUTHENTICATED,
    RVSIP_REG_CLIENT_STATE_REGISTERED,
    RVSIP_REG_CLIENT_STATE_FAILED,
    RVSIP_REG_CLIENT_STATE_MSG_SEND_FAILURE
} RvSipRegClientState;



/* RvSipRegClientStateChangeReason
 * ------------------------------------------------------------------
 * A register-client object has an inner state. The state changes according
 * to the state machine defined for the register-client. Each state change
 * is explained by one of the reasons enumerated bellow.
 *
 * RVSIP_REG_CLIENT_REASON_UNDEFINED         - The reason is undefined.
 * RVSIP_REG_CLIENT_REASON_USER_REQUEST      - The change in state was in
 *                                             reaction to a user's request.
 * RVSIP_REG_CLIENT_REASON_RESPONSE_SUCCESSFUL_RECEIVED  - 2xx was received.
 * RVSIP_REG_CLIENT_REASON_RESPONSE_REDIRECTION_RECEIVED - 3XX was received
 * RVSIP_REG_CLIENT_REASON_RESPONSE_UNAUTHENTICATED_RECEIVED - 401 or 407
 *                                                             was received.
 * RVSIP_REG_CLIENT_REASON_RESPONSE_REJECT_RECEIVED - 4xx, 5xx or 6xx other
 *                                                    than 401, 407 received.
 * RVSIP_REG_CLIENT_REASON_TRANSACTION_TIMEOUT - The register transaction had
 *                                               a timeout. This means that
 *                                               no final response was received
 */
typedef enum
{

    RVSIP_REG_CLIENT_REASON_UNDEFINED = -1,
    RVSIP_REG_CLIENT_REASON_USER_REQUEST,
    RVSIP_REG_CLIENT_REASON_RESPONSE_SUCCESSFUL_RECVD,
    RVSIP_REG_CLIENT_REASON_RESPONSE_REDIRECTION_RECVD,
    RVSIP_REG_CLIENT_REASON_RESPONSE_UNAUTHENTICATED_RECVD,
    RVSIP_REG_CLIENT_REASON_RESPONSE_REQUEST_FAILURE_RECVD,
    RVSIP_REG_CLIENT_REASON_RESPONSE_SERVER_FAILURE_RECVD,
    RVSIP_REG_CLIENT_REASON_RESPONSE_GLOBAL_FAILURE_RECVD,
    RVSIP_REG_CLIENT_REASON_LOCAL_FAILURE,
    RVSIP_REG_CLIENT_REASON_TRANSACTION_TIMEOUT,
    RVSIP_REG_CLIENT_REASON_NORMAL_TERMINATION,
    RVSIP_REG_CLIENT_REASON_GIVE_UP_DNS,
    RVSIP_REG_CLIENT_REASON_NETWORK_ERROR,
    RVSIP_REG_CLIENT_REASON_503_RECEIVED,
    RVSIP_REG_CLIENT_REASON_CONTINUE_DNS
} RvSipRegClientStateChangeReason;



/*-----------------------------------------------------------------------
       R E G  C L I E N T:  C A L L - B A C K  F U N C T I O N S
 ------------------------------------------------------------------------*/



/***************************************************************************
 * RvSipRegClientStateChangedEv
 * ------------------------------------------------------------------------
 * General: Notifies the application of a register-client state change.
 *          For each state change the new state is supplied and the
 *          reason for the state change is also given.
 * Return Value: (-)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hRegClient - The SIP stack register-client handle.
 *          hAppRegClient - The application handle for this register-client.
 *          eNewState - The new state of the register-client object.
 *          eReason - The reason for the change in state.
 ***************************************************************************/
typedef void
        (RVCALLCONV * RvSipRegClientStateChangedEv)(
                            IN  RvSipRegClientHandle            hRegClient,
                            IN  RvSipAppRegClientHandle         hAppRegClient,
                            IN  RvSipRegClientState             eNewState,
                            IN  RvSipRegClientStateChangeReason eReason);


/***************************************************************************
 * RvSipRegClientMsgToSendEv
 * ------------------------------------------------------------------------
 * General: An event indicating that a new register-client related outgoing
 *          message is about to be sent (not a retransmission).
 * Return Value: RV_OK (the returned status is ignored in the current
 *                           stack version)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient    - The sip stack register-client handle
 *            hAppRegClient - The application handle for this register-client.
 *            hMsg          - Handle to the outgoing message.
 ***************************************************************************/
typedef RvStatus
        (RVCALLCONV * RvSipRegClientMsgToSendEv)(
                                   IN  RvSipRegClientHandle    hRegClient,
                                   IN  RvSipAppRegClientHandle hAppRegClient,
                                   IN  RvSipMsgHandle          hMsg);


/***************************************************************************
 * RvSipRegClientMsgReceivedEv
 * ------------------------------------------------------------------------
 * General: An event indicating that a new register-client related incoming
 *          message was received (not a retransmission).
 * Return Value: RV_OK (the returned status is ignored in the current
 *                           stack version)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient    - The sip stack register-client handle
 *            hAppRegClient - The application handle for this register-client.
 *            hMsg          - Handle to the incoming message.
 ***************************************************************************/
typedef RvStatus
        (RVCALLCONV * RvSipRegClientMsgReceivedEv)(
                                    IN  RvSipRegClientHandle    hRegClient,
                                    IN  RvSipAppRegClientHandle hAppRegClient,
                                    IN  RvSipMsgHandle          hMsg);


/***************************************************************************
 * RvSipRegClientOtherURLAddressFoundEv
 * ------------------------------------------------------------------------
 * General: Notifies the application that a message needs to be sent and
 *          the destination address is a URL type that is currently not
 *          supported by the stack. The URL has to be converted to a SIP URL
 *          for the message to be sent.
 * Return Value: RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient    - The sip stack register-client handle
 *            hAppRegClient - The application handle for this register-client.
 *            hMsg           - The message that includes the other URL address.
 *            hAddress       - Handle to unsupport address to be converted.
 * Output:    hSipURLAddress - HHandle to the SIP URL address - this is an empty
 *                               address object that the application should fill.
 *            bAddressResolved-RV_TRUE if the SIP URL address was filled. RV_FALSE otherwise.
 ***************************************************************************/
typedef RvStatus (RVCALLCONV *RvSipRegClientOtherURLAddressFoundEv)(
                     IN  RvSipRegClientHandle    hRegClient,
                     IN  RvSipAppRegClientHandle hAppRegClient,
                     IN  RvSipMsgHandle          hMsg,
                     IN  RvSipAddressHandle         hAddress,
                     OUT RvSipAddressHandle         hSipURLAddress,
                     OUT RvBool                *bAddressResolved);




/***************************************************************************
 * RvSipRegClientFinalDestResolvedEv
 * ------------------------------------------------------------------------
 * General: Notifies the application that the register-client is about to send a 
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
 *               terminate with error and the register-client will move to the
 *               Failed state.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient     - Handle to the register client.
 *            hAppRegClient  - The application handle for this register client.
 *            hTransc        - The transaction handle
 *            hMsgToSend     - The handle to the outgoing message.
 ***************************************************************************/
typedef RvStatus (RVCALLCONV * RvSipRegClientFinalDestResolvedEv)(
                      IN  RvSipRegClientHandle    hRegClient,
                      IN  RvSipAppRegClientHandle hAppRegClient,
                      IN  RvSipTranscHandle       hTransc,
                      IN  RvSipMsgHandle          hMsgToSend);

/***************************************************************************
 * RvSipRegClientNewConnInUseEv
 * ------------------------------------------------------------------------
 * General:Notifies the application that the transaction is now using a new 
 *         connection. The connection can be a totally new one or a suitable 
 *         one that was found in the hash.
 *
 * Return Value: RV_OK (the returned status is ignored in the current
 *                      stack version)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClient     - Handle to the register client.
 *            hAppRegClient  - The application handle for this register client.
 *            hConn          - The connection handle
 *            bNewConnCreated - RV_TRUE if the connection is a newly 
 *                              created connection. RV_FALSE if the connection 
 *                              was found in the connection hash.
 ***************************************************************************/
typedef RvStatus (RVCALLCONV *RvSipRegClientNewConnInUseEv) (
                     IN  RvSipRegClientHandle           hRegClient,
                     IN  RvSipAppRegClientHandle        hAppRegClient,
                     IN  RvSipTransportConnectionHandle hConn,
                     IN  RvBool                         bNewConnCreated);
#ifdef RV_SIGCOMP_ON
/***************************************************************************
 * RvSipRegClientSigCompMsgNotRespondedEv
 * ------------------------------------------------------------------------
 * General: Notifies the application that the timer of the transaction 
 *          responsible for sending the REGISTER request has expired and that the
 *          SIP Stack has not yet received a response to the SigComp compressed 
 *          REGISTER request.
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
 * Input:     hRegClient    - Handle to the register client.
 *            hAppRegClient - The application handle for this reg-client.
 *            hTransc       - The transaction handle.
 *            retransNo     - The number of retransmissions of the request
 *                            until now.
 *            ePrevMsgComp  - The type of the previous not responded request
 * Output:    peNextMsgComp - The type of the next request to retransmit (
 *                            RVSIP_TRANSMITTER_MSG_COMP_TYPE_UNDEFINED means that the
 *                            application wishes to stop sending requests).
 ***************************************************************************/
typedef RvStatus (RVCALLCONV *RvSipRegClientSigCompMsgNotRespondedEv) (
                     IN  RvSipRegClientHandle         hRegClient,
                     IN  RvSipAppRegClientHandle      hAppRegClient,
                     IN  RvSipTranscHandle            hTransc,
                     IN  RvInt32                      retransNo,
                     IN  RvSipTransmitterMsgCompType  ePrevMsgComp,
                     OUT RvSipTransmitterMsgCompType *peNextMsgComp);
#endif /* RV_SIGCOMP_ON */

/* RvSipRegClientEvHandlers
 * ------------------------------------------------------------------------
 * Structure with function pointers to the module's call-backs.
 * This structure is used to set the application call-backs in the function
 * RvSipRegClientMgrSetEvHandlers();
 *
 * pfnStateChangedEvHandler         - notify of register-client state change.
 * pfnMsgToSendEvHandler            - notify that a message is about to be sent.
 * pfnMsgReceivedEvHandler          - notify that a message was received.
 * pfnOtherURLAddressFoundEvHandler - notify that abs url address was found and
 *                                      has to be converted to SIP URL address.
 * pfnFinalDestResolvedEvHandler    - notifies that the final destination address
 *                                    of the register request was resolved.
 * pfnFinalDestResolvedEvHandler    - Notifies that the register-client is about 
 *                                    to send a message after the destination
 *                                    address was resolved. This callback supplies 
 *                                    the final message object and the transaction
 *                                    that is responsible for sending this message. 
 *                                    The application can use the transaction API 
 *                                    to get the destination address.
 * pfnNewConnInUseEvHandler         - Notifies that the register-client is now 
 *                                    using a new connection. The connection can
 *                                    be a totally new connection or a suitable 
 *                                    connection that was found in the hash.
 * pfnSigCompMsgNotRespondedEvHandler - Notifies that a timer expired before the 
 *                                      SIP Stack received a response to a REGISTER
 *                                      SigComp compressed request. This callback 
 *                                      is part of a recovery mechanism
 *                                      and it supplies information about the sent 
 *                                      request. The application can decide if
 *                                      it wishes to continue with compressed 
 *                                      retransmissions. 
 */
typedef struct
{
    RvSipRegClientStateChangedEv           pfnStateChangedEvHandler;
    RvSipRegClientMsgToSendEv              pfnMsgToSendEvHandler;
    RvSipRegClientMsgReceivedEv            pfnMsgReceivedEvHandler;
    RvSipRegClientOtherURLAddressFoundEv   pfnOtherURLAddressFoundEvHandler;
    RvSipRegClientFinalDestResolvedEv      pfnFinalDestResolvedEvHandler;
    RvSipRegClientNewConnInUseEv           pfnNewConnInUseEvHandler;
#ifdef RV_SIGCOMP_ON
    RvSipRegClientSigCompMsgNotRespondedEv pfnSigCompMsgNotRespondedEvHandler;
#endif
} RvSipRegClientEvHandlers;


#endif /* RV_SIP_PRIMITIVES */

#ifdef __cplusplus
}
#endif


#endif /* END OF: #ifndef RV_SIP_REG_CLIENT_TYPES_H */
