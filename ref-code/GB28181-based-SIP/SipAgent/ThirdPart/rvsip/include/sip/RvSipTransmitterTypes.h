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
 *                              <RvSipTransmitterTypes.h>
 *
 * The RvSipTransmitterTypes.h file contains all type definitions and callback functions
 * type definitions for the Transmitter module.
 *
 * includes:
 * 1.Handle Type definitions
 * 2.Transmitter Type definitions
 * 3.Transmitter callback functions
 *
 *
 *    Author                         Date
 *    ------                        ------
 *    Sarit Galanos                 January 2004
 *********************************************************************************/


#ifndef RV_SIP_TRANSMITTER_TYPES_H
#define RV_SIP_TRANSMITTER_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                           */
/*-----------------------------------------------------------------------*/
#include "RV_SIP_DEF.h"
#include "RvSipMsgTypes.h"
#include "RvSipTransportTypes.h"


/*-----------------------------------------------------------------------*/
/*                            TYPE DEFINITIONS                           */
/*-----------------------------------------------------------------------*/

/*
 * RvSipTransmitterMgrHandle
 * ---------------------------------------------------------------------------
 * Declaration of handle to a Transmitter Manager instance. The manager object
 * manages all Transmitters and its handle is needed in all manager
 * related APIs such as creation of new Transmitters.
 */
RV_DECLARE_HANDLE(RvSipTransmitterMgrHandle);


/*
 * RvSipTransmitterHandle
 * ---------------------------------------------------------------------------
 * Declaration of a Transmitter handle. A Transmitter handle is used to
 * reference a Transmitter object.
 */
RV_DECLARE_HANDLE(RvSipTransmitterHandle);


/*
 * RvSipAppTransmitterHandle
 * ---------------------------------------------------------------------------
 * Declaration  of application handle to a Transmitter. This handle is used by the
 * application in order to associate sip stack Transmitter objects with application
 * Transmitter object. The application gives the application handle when
 * a new Transmitter is created. The sip stack will give this handle back to the
 * application in every callback function.
 */

RV_DECLARE_HANDLE(RvSipAppTransmitterHandle);


/*-----------------------------------------------------------------------*/
/*                    TRANSMITTER TYPE DEFINITIONS                           */
/*-----------------------------------------------------------------------*/


/* RvSipTransmitterState
 * ----------------------------------------------------------------------
 * The Transmitter state machine represents the state of the transmitter 
 * in the message sending activity. The RvSipTransmitterStateChangedEv() 
 * callback reports transmitter state changes and state change reasons. 
 * The state change reason indicates the reason for the
 * new state of the transmitter. 
 * The transmitter associates with the following states:
 * 
 * RVSIP_TRANSMITTER_STATE_UNDEFINED
 * Indicates that the transmitter was not yet initialized.
 * 
 * RVSIP_TRANSMITTER_STATE_IDLE
 * The initial state of the transmitter. Upon transmitter creation, the transmitter
 * assumes the IDLE state. It remains in this state until
 * RvSipTransmitterSendMessage() is called. The transmitter then moves to the
 * RESOLVING_ADDR state and starts the address resolution process.
 * 
 * RVSIP_TRANSMITTER_STATE_RESOLVING_ADDR
 * Indicates that the transmitter is about to start the address resolution process.
 * After RvSipTransmitterSendMessage() is called, the transmitter copies the
 * supplied message object and moves to the RESOLVING_ADDR state. The
 * transmitter then uses RFC 3261 rules to get the remote URI from the message
 * object, and the procedures of RFC 3263 to resolve the address by querying the
 * DNS server. When the DNS procedure is completed and the destination address
 * is determined, the transmitter moves to the FINAL_DEST_RESOLVED state.
 * 
 * RVSIP_TRANSMITTER_STATE_FINAL_DEST_RESOLVED
 * Indicates that the transmitter has completed the address resolution process and
 * that it has a destination address to use. The application can use the
 * RvSipTransmitterGetDestAddress() function to get the destination address. The
 * application can change the destination address using the
 * RvSipTransmitterSetDestAddress() function. If the application did not set the
 * Fix Via flag, the FINAL_DEST_RESOLVED state is the last chance for the
 * application to fix the Via by itself before the message is sent.
 * In this state, the application can hold the message sending activity by calling the
 * RvSipTransmitterHoldSending() function. If so, the transmitter will move to the
 * ON_HOLD state. Otherwise, the message will be sent when the state changed
 * callback returns.
 * 
 * RVSIP_TRANSMITTER_STATE_ON_HOLD
 * The transmitter assumes the ON_HOLD state if the
 * RvSipTransmitterHoldSending() function is called in the
 * FINAL_DEST_RESOLVED state. The application should call this function if it
 * wishes to manipulate the transmitter destination address and DNS list before the
 * message is sent. In this state, the application can use the
 * RvSipTransmitterSetDestAddress() function to change the current destination
 * address or it can supply NULL values to this function and reset the destination
 * address. The application can also manipulate the DNS list that contains the rest
 * of the DNS results. Resetting the destination address will cause the transmitter
 * to return to its DNS list for further address resolution.
 * To continue the sending activities, the application must call the
 * RvSipTransmitterResumeSending() function. If the transmitter has a valid
 * destination address, it will continue with the message sending and proceed to the
 * READY_FOR_SENDING state. Otherwise the transmitter will return to the
 * RESOLVING_ADDR state.
 * 
 * RVSIP_TRANSMITTER_STATE_READY_FOR_SENDING
 * Indicates that the transmitter is ready to send the message to the remote party.
 * The message in this state has its final format, and the application should no
 * longer change the message content or remote address. This state is informative
 * only.
 * 
 * RVSIP_TRANSMITTER_STATE_NEW_CONN_IN_USE
 * Indicates that the transmitter is about to use a new connection. The connection
 * can be a totally new connection created by the transmitter object or a connection
 * that the transmitter found in the connection hash. In both cases the pExtraInfo
 * will hold a pointer to a structure of type
 * RvSipTransmitterNewConnInUseStateInfo that includes the connection handle.
 * Two reasons are associated with this state:
 *    RVSIP_TRANSMITTER_REASON_NEW_CONN_CREATED 
 *         indicates that the transmitter created a new connection.
 *        
 *   RVSIP_TRANSMITTER_REASON_CONN_FOUND_IN_HASH
 *         indicates that the transmitter found an existing
 *         connection in the connection hash and that the transmitter is
 *         about to use the connection.
 * 
 * 
 * RVSIP_TRANSMITTER_STATE_MSG_SENT
 * Indicates that the message was sent successfully to the remote party. This state
 * does not supply the message object. The message is most likely destructed when
 * this state is reached. This state is also an indication that the application should
 * now terminate the transmitter object that has completed all its tasks and cannot
 * be used any longer.
 * 
 * RVSIP_TRANSMITTER_STATE_MSG_SEND_FAILURE
 * Indicates that an error occurred and the transmitter will not be able to send the
 * message. The state change reason indicates the type of failure. The following
 * reasons are associated with this state:
 *    RVSIP_TRANSMITTER_REASON_UNDEFINED 
 *         a general error caused the failure.
 *     RVSIP_TRANSMITTER_REASON_NETWORK_ERROR
 *         a network error occurred while trying to send the request or
 *         during the DNS procedure.
 *     RVSIP_TRANSMITTER_REASON_CONNECTION_ERROR
 *         An error occurred on the connection that was used to send the
 *         message.
 *     RVSIP_TRANSMITTER_REASON_OUT_OF_RESOURCES 
 *         The message cannot be sent because of a lack of resources.
 * In the message send failure, the application can do one of two things:
 *     * Terminate the transmitter using the
 *       RvSipTransmitterTerminate() function.
 *     * Send the message again to the next address in the DNS list by
 *       calling the RvSipTransmitterSendMessage() function. This
 *       option is available only if the enhanced DNS feature is enabled. 
 */
typedef enum
{
    RVSIP_TRANSMITTER_STATE_UNDEFINED = -1,
    RVSIP_TRANSMITTER_STATE_IDLE,
    RVSIP_TRANSMITTER_STATE_RESOLVING_ADDR,
    RVSIP_TRANSMITTER_STATE_FINAL_DEST_RESOLVED,
    RVSIP_TRANSMITTER_STATE_ON_HOLD,
    RVSIP_TRANSMITTER_STATE_NEW_CONN_IN_USE,
    RVSIP_TRANSMITTER_STATE_READY_FOR_SENDING,
    RVSIP_TRANSMITTER_STATE_MSG_SEND_FAILURE,
    RVSIP_TRANSMITTER_STATE_MSG_SENT,
    RVSIP_TRANSMITTER_STATE_TERMINATED
} RvSipTransmitterState;


/* RvSipTransmitterReason
 * ------------------------------------------------------------------
 * A Transmitter object has an inner state. The state changes according
 * to the state machine defined for the Transmitter. Each state change
 * is explained by one of the reasons enumerated bellow.
 *
 * RVSIP_TRANSMITTER_REASON_UNDEFINED           
 *         The reason is undefined.
 * RVSIP_TRANSMITTER_REASON_NETWORK_ERROR 
 *         a network error occurred while trying to send the request or
 *         during the DNS procedure.
 * RVSIP_TRANSMITTER_REASON_CONNECTION_ERROR 
 *         An error occurred on the connection that was used to send the
 *         message.
 * RVSIP_TRANSMITTER_REASON_OUT_OF_RESOURCES 
 *         The message cannot be sent because of a lack of resources.
 * RVSIP_TRANSMITTER_REASON_NEW_CONN_CREATED
 *         Indicates that the transmitter created a new connection.
 * RVSIP_TRANSMITTER_REASON_CONN_FOUND_IN_HASH 
 *         indicates that the transmitter found an existing
 *         connection in the connection hash and that the transmitter is
 *         about to use the connection.
 * RVSIP_TRANSMITTER_REASON_USER_COMMAND
 *         The state was reached due to a user command
 */
typedef enum
{
    RVSIP_TRANSMITTER_REASON_UNDEFINED = -1,
    RVSIP_TRANSMITTER_REASON_NETWORK_ERROR,
    RVSIP_TRANSMITTER_REASON_CONNECTION_ERROR,
    RVSIP_TRANSMITTER_REASON_OUT_OF_RESOURCES,
    RVSIP_TRANSMITTER_REASON_NEW_CONN_CREATED,
    RVSIP_TRANSMITTER_REASON_CONN_FOUND_IN_HASH,
    RVSIP_TRANSMITTER_REASON_USER_COMMAND
} RvSipTransmitterReason;



/* RvSipTransmitterMsgCompType
 * -----------------------------------
 * This enum unifies all the possible message types
 * when using the SigComp feature for compressing ASCII SIP
 * requests/response. With this enumeration the application
 * indicates if the message should be compressed, uncompresses or
 * compressed with byte code included.
 *
 * RVSIP_TRANSMITTER_MSG_COMP_TYPE_UNCOMPRESSED      
 *                              - Uncompressed outgoing message.
 * RVSIP_TRANSMITTER_MSG_COMP_TYPE_SIGCOMP_COMPRESSED 
 *                              - SigComp compressed outgoing message.
 * RVSIP_TRANSMITTER_MSG_COMP_TYPE_SIGCOMP_COMPRESSED_INCLUDE_BYTECODE
 *                              - SigComp compressed outgoing message
 *                                that includes decompression byte code.
 */
typedef enum
{
    RVSIP_TRANSMITTER_MSG_COMP_TYPE_UNDEFINED = -1,
    RVSIP_TRANSMITTER_MSG_COMP_TYPE_UNCOMPRESSED,
    RVSIP_TRANSMITTER_MSG_COMP_TYPE_SIGCOMP_COMPRESSED,
    RVSIP_TRANSMITTER_MSG_COMP_TYPE_SIGCOMP_COMPRESSED_INCLUDE_BYTECODE
} RvSipTransmitterMsgCompType;


/* RvSipTransmitterExtOptions
 * ------------------------------------------------------------------
 * This structure is used to instruct the transmitter to use a specific
 * mechanism when sending the message. In the current version the application
 * can instruct the transmitter to compress the outgoing message.
 * eMsgCompType - Compression type
 */
typedef struct
{
    RvInt dummy; /* So that the structure will never be empty */
#ifdef RV_SIGCOMP_ON
    RvSipTransmitterMsgCompType  eMsgCompType;
#endif /* RV_SIGCOMP_ON */
} RvSipTransmitterExtOptions;



/* RvSipTransmitterNewConnInUseStateInfo
 * ------------------------------------------------------------------
 * This structure is used in the state RVSIP_TRANSMITTER_STATE_NEW_CONN_IN_USE
 * to supply additional information regarding the state.
 * hConn -  The connection handle.
 */
typedef struct
{
    RvSipTransportConnectionHandle hConn;
} RvSipTransmitterNewConnInUseStateInfo;




/*-----------------------------------------------------------------------
       T R A N S M I T T E R:  C A L L - B A C K  F U N C T I O N S
 ------------------------------------------------------------------------*/

/***************************************************************************
 * RvSipTransmitterStateChangedEv
 * ------------------------------------------------------------------------
 * General: Notifies the application of a transmitter state change. Each step of 
 *          the message sending process of the transmitter is represented by a state. 
 *          The application is notified of this state through the 
 *          RvSipTransmitterStateChangedEv() callback. For each
 *          state change, the new state is supplied with the reason for the new state, and the
 *          message object when valid. An additional parameter, pExtraInfo, will hold
 *          specific state information.
 *          Most of the states are informative only. The final message sending states
 *          (MSG_SENT and MSG_SEND_FAILURE) indicate that the application should
 *          now terminate the transmitter object.
 *          Remark: Currently the pExtraInfo parameter is used only in the
 *          NEW_CONN_IN_USE state.
 *
 * Return Value: (-)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTrx    -    The sip stack Transmitter handle
 *            hAppTrx -    The application handle for this Transmitter.
 *            eState  -    The new Transmitter state
 *            eReason -    The reason for the state change.
 *            hMsg    -    When the state relates to the outgoing message, the
 *                         message is supplied.
 *            pExtraInfo - Specific information for the new state.
 ***************************************************************************/
typedef void
        (RVCALLCONV * RvSipTransmitterStateChangedEv)(
                                   IN  RvSipTransmitterHandle            hTrx,
                                   IN  RvSipAppTransmitterHandle         hAppTrx,
                                   IN  RvSipTransmitterState             eState,
                                   IN  RvSipTransmitterReason            eReason,
                                   IN  RvSipMsgHandle                    hMsg,
                                   IN  void*                             pExtraInfo);


/***************************************************************************
 * RvSipTransmitterOtherURLAddressFoundEv
 * ------------------------------------------------------------------------
 * General: Notifies the application that a message needs to be sent and 
 *          the destination address is a URL type that is currently not 
 *          supported by the SIP Stack (for example a tel URL). 
 *          The application must convert the URL to a SIP URL for the
 *          message to be sent.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input: hTrx           - The sip stack Transmitter handle
 *        hAppTrx        - The application handle for this Transmitter.
 *        hMsg           - The message that includes the other URL address.
 *        hAddress       - Handle to unsupport address to be converted.
 * Output:hSipURLAddress - Handle to the SIP URL address - this is an empty
 *                         address object that the application should fill.
 *        pbAddressResolved -Indication wether the SIP URL address was filled.
 ***************************************************************************/
typedef RvStatus (RVCALLCONV *RvSipTransmitterOtherURLAddressFoundEv)(
                     IN  RvSipTransmitterHandle     hTrx,
                     IN  RvSipAppTransmitterHandle  hAppTrx,
                     IN  RvSipMsgHandle             hMsg,
                     IN  RvSipAddressHandle         hAddress,
                     OUT RvSipAddressHandle         hSipURLAddress,
                     OUT RvBool                    *pbAddressResolved);


/* RvSipTransmitterEvHandlers
 * ------------------------------------------------------------------------
 * Structure with function pointers to the module callbacks.
 * you supply this structure when creating a new transmitter.
 *
 * pfnStateChangedEvHandler         - Notifies of Transmitter state change event.
 * pfnOtherURLAddressFoundEvHandler - Notifies the application that other URL address was found
 *                                    and has to be converted to SIP URL address.
 */
typedef struct
{
    RvSipTransmitterStateChangedEv                  pfnStateChangedEvHandler;
    RvSipTransmitterOtherURLAddressFoundEv          pfnOtherURLAddressFoundEvHandler;
} RvSipTransmitterEvHandlers;



#ifdef __cplusplus
}
#endif


#endif /* END OF: #ifndef RV_SIP_TRANSMITTER_TYPES_H */
