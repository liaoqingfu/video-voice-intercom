
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
 *                              RvSipStackTypes.h
 *
 *  This file provides definitions for the stack mgr module of the RADVISION SIP stack.
 *
 *
 *    Author                         Date
 *    ------                        ------
 *  Oren Libis                    20-Nov-2000
 *********************************************************************************/


#ifndef _RV_SIP_STACK_TYPES_H
#define _RV_SIP_STACK_TYPES_H


#ifdef __cplusplus
extern "C" {
#endif


/*-----------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                           */
/*-----------------------------------------------------------------------*/

#include "RV_SIP_DEF.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RvSipCommonTypes.h"
#include "RvSipMsgTypes.h"
#include "RvSipTransportTypes.h"
#ifdef RV_SIGCOMP_ON
#include "RvSigComp.h"
#endif /* RV_SIGCOMP_ON */

/*-----------------------------------------------------------------------*/
/*                          TYPE DEFINITIONS                             */
/*-----------------------------------------------------------------------*/





/* Declares a handle to the Stack Manager object. */
RV_DECLARE_HANDLE(RvSipStackHandle);


/* Declares a handle to the Stack Manager object. */
RV_DECLARE_HANDLE(RvSipAppStackHandle);


/* Defines the different modules of the RADVISION SIP stack.
   The different values are used mainly for defining the logging
   filters of the different modules of the sip stack
   The RVSIP_CORE enumeration is used to set logging filters to all
   the core modules together
   The RVSIP_ADS is used to set logging filters to all ads modules
   together*/
typedef enum {
    RVSIP_CALL, 
    RVSIP_TRANSACTION,
    RVSIP_MESSAGE,
    RVSIP_TRANSPORT,
    RVSIP_PARSER,
    RVSIP_STACK,
    RVSIP_MSGBUILDER,
    RVSIP_AUTHENTICATOR,
    RVSIP_REGCLIENT,
    RVSIP_SUBSCRIPTION,
    RVSIP_COMPARTMENT,
    RVSIP_TRANSMITTER,
    RVSIP_ADS_RLIST,
    RVSIP_ADS_RA,
    RVSIP_ADS_RPOOL,
    RVSIP_ADS_HASH,
    RVSIP_ADS_PQUEUE,
    RVSIP_CORE_SEMAPHORE,
    RVSIP_CORE_MUTEX,
    RVSIP_CORE_LOCK,
    RVSIP_CORE_MEMORY,
    RVSIP_CORE_THREAD,
    RVSIP_CORE_QUEUE,
    RVSIP_CORE_TIMER,
    RVSIP_CORE_TIMESTAMP,
    RVSIP_CORE_CLOCK,
    RVSIP_CORE_TM,
    RVSIP_CORE_SOCKET,
    RVSIP_CORE_PORTRANGE,
    RVSIP_CORE_SELECT,
    RVSIP_CORE_HOST,
    RVSIP_CORE_TLS,
    RVSIP_CORE_ARES ,
    RVSIP_CORE             =100,   /*All core modules*/
    RVSIP_ADS              =101   
}RvSipStackModule;




/***************************************************************************
 * RvSipStackPrintLogEntryEv
 * ------------------------------------------------------------------------
 * General: Notifies the application each time a line should be printed to
 *          the log. The application can decide whether to print the line
 *          to the screen, file or other output device. You set this
 *          callback in the RvSipStackCfg structure before initializing
 *          the stack. If you do not implement this function a default logging
 *          will be used and the line will be written to the SipLog.txt file.
 * Return Value: (-)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     context - The context that was given in the callback registration
 *                    process.
 *          filter -    The filter that this message is using (info, error..)
 *            formattedText - The text to be printed to the log. The text
 *                          is formatted as follows:
 *                          <filer> - <module> - <message>
 *                          for example:
 *                          "INFO  - STACK - Stack was constructed successfully"
 ***************************************************************************/
typedef void
        (RVCALLCONV * RvSipStackPrintLogEntryEv)(
                                         IN void*           context,
                                         IN RvSipLogFilters filter,
                                         IN const RvChar   *formattedText);

/*
 * RvSipStackCoreLogFiltersCfg
 * -----------------------------------------------------------------------------
 * The structure includes an entry for each of the Sip Stack Core components.
 * The structure can be used to configure log filters to each of the core components
 * separately.
 */
typedef struct {
    RvInt32      coreSemaphoreLogFilters;
    RvInt32      coreMutexLogFilters;
    RvInt32      coreLockLogFilters;
    RvInt32      coreMemoryLogFilters;
    RvInt32      coreThreadLogFilters;
    RvInt32      coreQueueLogFilters;
    RvInt32      coreTimerLogFilters;
    RvInt32      coreTimestampLogFilters;
    RvInt32      coreClockLogFilters;
    RvInt32      coreTmLogFilters;
    RvInt32      coreSocketLogFilters;
    RvInt32      corePortRangeLogFilters;
    RvInt32      coreSelectLogFilters;
    RvInt32      coreHostLogFilters;
    RvInt32      coreTlsLogFilters;
    RvInt32      coreAresLogFilters;
    RvInt32      forFutureUse[20];
} RvSipStackCoreLogFiltersCfg;

/*
 * RvSipStackAdsLogFiltersCfg
 * -----------------------------------------------------------------------------
 * The structure includes an entry for each of the Sip Stack Ads components.
 * The structure can be used to configure log filters to each of the Ads components
 * separately.
 */
typedef struct {
    RvInt32      adsRListLogFilters;
    RvInt32      adsRaLogFilters;
    RvInt32      adsRPoolLogFilters;
    RvInt32      adsHashLogFilters;
    RvInt32      adsPQueueLogFilters;
    RvInt32      forFutureUse[20]; 
}RvSipStackAdsLogFiltersCfg;

/********************************************************************************************
 * RvSipStackCfg
 * -----------------------------------------------------------------------------
 * RvSipStackCfg contains the configuration parameters of the
 * RADVISION SIP stack.
 *
 * maxCallLegs
 * -----------
 * The number of call-legs the SIP stack allocates. You should set this
 * value to the maximum number of calls you expect the SIP Stack to
 * handle simultaneously.
 * Default Value: 10
 * Remark: The parameter value must be greater than zero
 *
 * maxTransactions
 * ----------------
 * The number of transactions the SIP Stack allocates. You should set this
 * value to the maximum number of transactions you expect the SIP Stack
 * to handle simultaneously.
 * Default Value: maxTransaction = maxCallLegs + maxSubscriptions
 * Remark: The parameter value must be greater than zero
 *
 * maxRegClients
 * -------------
 * The number of Register-Clients the SIP Stack allocates. You should set
 * this value to the maximum number of register-clients you expect the
 * SIP Stack to handle simultaneously.
 * Default Value: 2
 *
 * messagePoolNumofPages
 * ---------------------
 * The message pool page number.
 * Default Value: 90? messages per transaction
 * Remark: The parameter value must be greater than zero
 *
 * messagePoolPageSize
 * -------------------
 * The message pool page size.
 * Default Value: 2048
 * Remark: The parameter value must be greater than zero
 *
 * generalPoolNumofPages
 * ---------------------
 * The number of pages in the general pool.
 * Default Value: 100? per call, 2 per transaction, 20 for general usage
 * Remark: The parameter value must be greater than zero
 *
 * generalPoolPageSize
 * -------------------
 * The size of a page in the general pool.
 * Default Value: 1024梙alf the size of a message pool page
 * Remark: The parameter value must be greater than zero
 *
 * elementPoolNumofPages
 * ---------------------
 * The number of pages in the element pool.
 * Default Value: 37 ?(maxCallLegs*2 + 0.5*maxSubscriptions + maxTlsSessions +
                        0.75*maxTransmitters) * 1.1
 * Remark: The parameter value must be greater than zero
 *
 * elementPoolPageSize
 * -------------------
 * The size of a page in the element pool.
 * Default Value: 250?for holding an element such as a stand alone header.
 * Remark: The parameter value must be greater than zero
 *
 * sendReceiveBufferSize
 * --------------
 * Indicates the buffer size used by the SIP Stack for receiving and
 * sending SIP messages.
 * Default Value: 2048
 * Remark: The parameter value must be greater than zero
 *
 * localUdpAddress
 * ---------------
 * The local IP of the SIP Stack.
 * Default Value: The local IP address
 * Remark: This parameter can be set to zero or to ?.0.0.0?to indicate a default
 * value. The default for IPv6 is [0:0:0:0:0:0:0:0]
 *
 * localUdpPort
 * -----------
 * The local UDP port on which the SIP Stack listens.
 * Default Value: 5060
 *
 * outboundProxyIpAddress
 * -----------------------
 * Indicates the IP address of an outbound proxy the SIP Stack uses.
 * Default Value: 0梟o outbound proxy
 *
 * outboundProxyPort
 * -----------------
 * Indicates the port of the outbound proxy the SIP Stack uses.
 * To enable full host resolution as described in rfc3263, set to UNDEFINED 
 * Default Value: 5060
 *
 *
 * retransmissionT1
 * ----------------
 * When an unreliable transport protocol such as UDP is used, the user agent
 * should retransmit messages if a response does not arrive. T1 determines the
 * initial retransmission interval as defined in RFC 2543.
 * Default Value: 500
 * Remark: The parameter value cannot be less than 500
 *
 * retransmissionT2
 * ----------------
 * T2 determines the maximum retransmission interval as defined in RFC 2543.
 * Default Value: 4000
 * Remark: The parameter value cannot be less than 4000
 *
 * retransmissionT4
 * ----------------
 * T4 determines several timers as defined in RFC 2543.
 * For example: the time that a UAS waits after receiving an ACK message, before
 * terminating the transaction, when working with an unreliable transport protocol
 * such as UDP.
 * Default Value: 5000
 *
 * generalLingerTimer
 * -------------------
 * After a server sends a final response, when working with unreliable transport,
 * it cannot be sure the client has received the response message. The server
 * should be able to retransmit the response upon receiving retransmissions of the
 * request for generalLingerTimer milliseconds.
 * Default Value: T1*64
 *
 * inviteLingerTimer
 * -------------------
 * After sending an ACK for an INVITE final response, when working with unreliable transport,
 * a client cannot be sure the server has received the ACK message. The client should be
 * able to retransmit the ACK upon receiving retransmissions of the final response for
 * inviteLingerTimer milliseconds.
 * Default Value: 32000.
 *
 * provisionalTimer
 * ----------------
 * The provisional timer is set when receiveing a provisional response on an INVITE
 * transaction. The transaction will stop retransmissions of the INVITE and will wait
 * for the final response until the provisional timer expires. If you set the timer to
 * 0 (zero), no timer is set. The invite transaction will wait forever for the final
 * response.
 * Default Value: 180,000
 *
 * cancelGeneralNoResponseTimer
 * ----------------------------
 * When sending a CANCAL request to a General request the User Agent waits
 * cancelGeneralNoResponseTimer milliseconds before timeout termination.
 * This timer must be a positive number (> 0).
 * Default Value: T1*64
 *
 * cancelInviteNoResponseTimer
 * ---------------------------
 * When sending a CANCAL request to an Invite request the User Agent waits
 * cancelInviteNoResponseTimer milliseconds before timeout termination
 * This timer must be a positive number (> 0).
 * Default Value: T1*64
 *
 * generalRequestTimeoutTimer
 * --------------------------
 * After sending a General request the User Agent waits for a final response
 * generalRequestTimeoutTimer milliseconds before timeout termination (in this time the
 * User Agent retransmits the request every T1, 2*T1, .., T2, .. milliseconds)
 * Default Value: T1*64
 *
 * defaultLogFilters
 * -----------------
 * You can define a default logging level for all the SIP Stack modules
 * using the defaultLogFilters parameter .
 * Default Value: 31梖ull logging information
 *
 * coreLogFilters
 * ---------------
 * Core module log filters.
 * Default Value: 0
 *
 *
 * msgLogFilters
 * --------------
 * Message module log filters.
 * Default Value: 0
 *
 * transportLogFilters
 * -------------------
 * Message module log filters.
 * Default Value: 0
 *
 * transactionLogFilters
 * ---------------------
 * Transaction module log filters.
 * Default Value: 0
 *
 *
 * callLogFilters
 * --------------
 * Call module log filters.
 * Default Value: 0
 *
 * parserLogFilters
 * ----------------
 * Parser module log filters.
 * Default Value: 0
 *
 * stackLogFilters
 * ---------------
 * SIP Stack Manager module log filters.
 * Default Value: 0
 *
 * msgBuilderLogFilters
 * --------------------
 * Message Builder module log filters.
 * Default Value: 0
 *
 * authenticationLogFilters
 * --------------------------
 * Authenticator module log filters.
 * Default Value: 0
 *
 * regClientLogFilters
 * -------------------
 * Register Client module log filters.
 * Default Value: 0
 *
 *=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
 *
 * new parameters for version 1.1
 * ===============================
 *
 *=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
 *
 * new parameters for version 1.2
 * ===============================
 * pfnPrintLogEntryEvHandler
 * -------------------------
 * A function pointer to an application defined log callback. By registering to this
 * callback the user can override the default stack logging and control both
 * the log output device and the log message structure.
 * Default Value: NULL - The default logging system will be used.
 *
 * logContext
 * ----------
 * Application context to the log. This context will be given to the application
 * each time the pfnPrintLogEntryEvHandler() callback is called.
 * Default Value: NULL
 *
 * enableInviteProceedingTimeoutState
 * ----------------------------------
 * Specify whether enable "Request time-out" state.
 * If this state is enabled then if a UAC INVITE transaction reached timeout when
 * in proceeding state, then the transaction will change its state to "Request time-out".
 * In this state the application can decide whether to terminate the transaction
 * or to CANCEL it.
 *
 * enableServerAuth
 * ----------------
 * Indicates whether to enable the server authentication feature.
 * Default Value:RV_FALSE
 *
 * localTcpAddress
 * ----------------
 * Indicates the local TCP address (IP) to which the SIP Stack
 * listens.
 * Default Value:0.0.0.0 or [0:0:0:0:0:0:0:0] for IPv6
 *
 * localTcpPort
 * ------------
 * Indicates the local TCP port on which the SIP Stack
 * listens.
 * Default Value:5060
 *
 * maxConnections
 * --------------
 * Indicates the number of TCP connection sockets to be allocated by the
 * SIP Stack.
 * Default Value:maxTransactions/2
 *
 * tcpEnabled
 * ----------
 * Indicates whether the TCP is enabled. If set to RV_FALSE no connection
 * will be allocated.
 * Default Value:RV_FALSE
 *
 * noResponseTimer
 * ---------------
 * Indicates the maximum time in milliseconds that a transaction waits for final
 * response. This timer is used for requests sent using TCP and when waiting for a
 * response of a request that was cancelled.
 * Default Value:32000
 *
 * supportedExtensionList
 * ----------------------
 * List of supported option-tags, separated by commas, which are supported by the
 * SIP Stack. The list will be added to a Supported header for outgoing messages.
 * Default Value: NULL (empty list)
 *
 * rejectUnsupportedExtensions
 * ---------------------------
 * Indicated whether the stack should reject unsupported extensions found
 * in the Require header of a received request. If set to RV_TRUE, such
 * requests will be rejected with 420 status code.
 * Default Value:RV_FALSE
 *
 * addSupportedListToMsg
 * ---------------------------
 * Indicated whether the stack should add Supported header to outgoing messages
 * with the supported list.
 * Default Value:RV_TRUE
 *
 * manualAckOn2xx
 * --------------
 * Specify whether the ACK on a 2xx response is performed manually by the
 * application (RV_TRUE) or automatically by the call-leg (RV_FALSE).
 * Default value: RV_FALSE - the ACK is sent automatically.
 *
 * manualPrack
 * -----------
 * Specify weather the PRACK message on a reliable provisional response
 * is performed manually by the application (RV_TRUE) or automatically
 * by the call-leg through the transaction layer (RV_FALSE).
 * Default value: RV_FALSE - the PRACK is sent automatically.
 *
 * isProxy
 * --------
 * Indicates whether the application is a proxy implementation.
 * Default value: RV_FALSE
 *
 * proxy2xxRcvdTimer
 * -----------------
 * A successful client Invite transaction of a proxy server includes only the Invite
 * request and the 2xx response. (The Ack is not part of the transaction).
 * After receiving the 2xx response the proxy will wait proxy2xxRcvdTimer
 * before the transaction will terminate.
 * Default value: 32000.
 *
 * proxy2xxSentTimer
 * -----------------
 * A successful server Invite transaction of a proxy server includes only the Invite
 * request and the 2xx response. (The Ack is not part of the transaction).
 * After sending the 2xx response the proxy will wait proxy2xxSentTimer
 * before the transaction will terminate.
 * Default value: 0.
 *
 * localUdpAddresses
 * localUdpPorts
 * -----------------------------------
 * Additional local UDP addresses the stack can listen to.
 * These parameters will be use in multi-home host applications.
 * Default value: NULL (no extra addresses)
 * Note: These arrays must be allocated according to the size given in numOfExtraUdpAddresses
 *       Each of the entries of localUdpAddresses must be allocated as well, in order to
 *         contain the requested IP address.
 *
 * localTcpAddresses
 * localTcpPorts
 * -----------------------------
 * Additional local TCP addresses the stack can listen to.
 * These parameters will be use in multi-homed host applications.
 * Default value: NULL (no extra addresses)
 * Note: These arrays must be allocated according to the size given in numOfExtraTcpAddresses
 *       Each of the entries of localTcpAddresses must be allocated as well, in order to
 *         contain the requested IP address.
 *
 * numOfExtraUdpAddresses
 * ----------------------
 * The size of the localUdpAddresses and localUdpPorts arrays. The application is responsible
 * to allocate these array according to this number.
 *
 * numOfExtraTcpAddresses
 * ----------------------
 * The size of the localTcpAddresses and localTcpPorts arrays. The application is responsible
 * to allocate these array according to this number.
 *
 *=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
 *
 * new parameters for version 2.1.5.0
 * ===============================
 * maxElementsInSingleDnsList
 * -----------------------------------------
 * Maximum number of elements in single DNS List, regardlesss DNS list type. In total,
 * when there are 3 DNS list types (SRV, Host Name & IP address), single DNS object
 * may contain up to 3*maxElementsInSingleDnsList elements.
 *
 *=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
 *
 * new parameters for version 2.2
 * ===============================
 * processingQueueSize
 * ------------------------------------------
 * Maximum length of the processing queue
 *
 * numberOfProcessingThreads
 * -------------------------------------------
 * Number of processing threads to be initiated. If this value is set to 0 or
 * negative number, SIP stack will be executed in the single-thread mode.
 *
 * numOfReadBuffers
 *---------------------------------------------
 * Number of read buffers
 *
 * processingTaskPriority
 * -------------------------------------------
 * this parameter is relevant only for RTOS (VxWorks, NUCLEUS) when stack is executed
 * in multi-threaded mode. It defines priority of processing tasks (see possible
 * parameters in relevant OS documentation).
 *
 * processingTaskStackSize
 * -------------------------------------------
 * this parameter is relevant only for RTOS (VxWorks, NUCLEUS) when stack is executed
 * in multi-threaded mode. It defines size of processing tasks stack in bytes.
 *
 * Subscription parameters:
 * =======================
 * maxSubscriptions
 * -----------------
 * The number of subscriptions the SIP stack allocates. You should set this
 * value to the maximum number of subscriptions you expect the SIP Stack to
 * handle simultaneously.
 * Default Value: 0
 * Remark: The parameter may be zero, if you don't support subscriptions.
 *
 * subsAlertTimer
 * ---------------
 * Indicates the time in milliseconds that an alert is given, before subscription
 * expiration.
 * Default value: 1000
 *
 * subsNoNotifyTimer
 * ------------------------
 * Indicates the maximum time in milliseconds that a subscription waits from receiving
 * 2xx response for a SUBSCRIBE request until receiving first NOTIFY request.
 * If this parameter is 0, noNotifyTimer will not be set. If -1, default value is set.
 * Default Value: 32000
 *
 * subsAutoRefresh
 * -----------------------
 * Specify whether to send a refreshing SUBSCRIBE request, when subscription is going to
 * be expired or not.
 * Default value: RV_FALSE - refreshing request will not be sent automatically.
 *
 * Session Timer parameters:
 * =======================
 *
 * sessionExpires
 * ---------------
 * The time at which an element will consider the call timed out,
 * if no successful INVITE transaction occurs beforehand.(default value 1800 seconds)
 * minSE
 * -----
 * minimum value for the session interval the application is willing to accept.
 * (default value 0)
 *
 * manualSessionTimer
 * ------------------
 * Specify whether the session time performed manually by the
 * application (RV_TRUE) or automatically by the call-leg (RV_FALSE).
 * Default value: RV_FALSE - the session time is sent automatically.
 *
 * manualBehavior
 * --------------
 * Specifies weather the stack allows the application to send messages manually:
 * 1. answer final response to the invite transaction after receiving cancel to the invite
 *    (the stack accepts the cancel automatically).
 * 2. When the call receives 2xx response to an invite message after cancelling it the
 *    application will manually send ACK (in the manual ACK is true), and the stack will not
 *    send BYE automatically.
 *
 * new parameters for version 3.0
 * ===============================
 * bUseRportParamInVia
 * -------------------
 * Indicates whether to add the rport parameter to the via header of outgoing requests.
 * The remote party should fill the rport parameter with the port from were the request was
 * received.
 * Default Value: RV_FALSE
 * Remarks: Group A parameter.
 *
 * ePersistencyLevel
 * -----------------
 * The persistency level to be used by the stack objects.
 * Default value: -1 (undefined - not using persistent connection).
 *
 * serverConnectionTimeout
 * -----------------------
 * Specifies the time duration a server connection is kept open.
 * By default the stack does not close server connections when the connection has no more owners.
 * The stack waits for the remote party to close server connections.
 * However you can use the serverConnectionTimeout to change the default behavior of the stack.
 * If you set serverConnectionTimeout to a value bigger then 0, the stack will set a timer
 * for each server connection and will close it when this timer expires. If you set
 * the serverConnectionTimeout to 0, each server connection will be closed immediately after the last
 * owner detaches from it.
 * Default value: -1 - the stack will not close server connections.
 *
 * outboundProxyHostName
 * ---------------------
 * The host name of an outbound proxy the SIP Stack uses. For each outgoing request
 * the DNS will be queried for this host IP address.
 * Note: If you set the outboundProxyIPAddress parameter, the outboundProxyHostName
 * parameter will be ignored.
 * Default value: NULL
 *
 * outboundProxyTransport
 * ----------------------
 * Indicates the transport of the outbound proxy the SIP Stack uses.
 * Default Value: RVSIP_TRANSPORT_UNDEFINED
 *
 * numOfTlsAddresses
 * -----------------
 * The number of TLS addresses that the application whishes to listen on. Setting this number
 * to 0 means that the application does not want to listen to any TLS addresses. It is the
 * application's responsibility to allocate two arrays with (numOfTlsAddresses) cells that contains
 * addresses and corresponding ports.
 * Default Value: 0
 *
 * localTlsAddresses
 * localTlsPorts
 * -----------------------------
 * Local TLS addresses the stack will listen on.
 * These parameters will be use in multi-homed host applications.
 * Default value: NULL (no TLS addresses)
 * Note: These arrays must be allocated according to the size given in numOfTlsAddresses
 *       Each of the entries of localTlsAddresses must be allocated as well, in order to
 *         contain the requested IP address.
 *
 * numOfTlsEngines
 * ---------------
 * The maximal number of TLS engines. TLS engines are used to give a set of properties to a TLS connection.
 * Default value: 0
 *
 * maxTlsSessions
 * --------------
 * The maximal number of TLS sessions. TLS session is the TLS equivalent on TCP connection and contains TLS
 * data required to manage the TLS connection. The stack will be able to handle a maximum of maxTlsSessions
 * concurrent TLS connections.
 * Default value: maxConnections. (Each opened connection can be used for TLS)
 *
 * bDynamicInviteHandling
 * -------------------
 * Indicates that an incoming INVITE can be handled above the call-leg or the
 * transaction layer according to the application decision. If this parameter is
 * set to RV_TRUE the RvSipTransactionOpenCallLegEv() will be called for every
 * initial INVITE and the application will have to decide whether to open a
 * call-leg for this INVITE or not. If the application chooses not to open a call-leg,
 * this INVITE will be handled using the transaction state machine, callbacks and
 * APIS. The application will get both the RvSipTransactionCreatedEv() and the
 * RvSipTransactionStateChangedEv() for this transaction.
 * Note: When set to RV_TRUE the stack does not handle any transaction automatically.
 *       A Transaction that does not match any call-leg will be given to the
 *       application and the application will have to respond to it.
 * Default Value: RV_FALSE
 * Remarks: Group A parameter.
 *
 * new parameters for version 3.1
 * ===============================
 * bDisableRefer3515Behavior
 * -------------------------
 * Indicates how to handle REFER messages.
 * RFC 3515 defines a new implementation for REFER. According to 3515 REFER
 * messages are handled using Subscription objects.
 * If you set the bDisableRefer3515Behavior parameter to RV_TRUE, 
 * the deprecated REFER behavior and interface will be used.
 * If this parameter is set to RV_FALSE the stack will behave as described in
 * RFC 3515. A new subscription will be created
 * for every incoming REFER, and the subscription callback functions
 * will be called.
 * Note: When you set this parameter to RV_TRUE, the internal REFER behavior
 *       still uses the subscription layer but the interface for the application
 *       remains unchanges. Therefor you must still allocate enough subscription
 *       objects.
 * Default Value: RV_FALSE
 * Remarks: Group A parameter.
 *
 * bEnableSubsForking
 * ------------------
 * Indicates how to handle an incoming NOTIFY message that 
 * does not match any existing dialog and might be the outcome of a SUBSCRIBE
 * message that was forked.
 * If you set this parameter to RV_FALSE, a NOTIFY message that does not
 * match an existing dialog, will be handled as general transactions. 
 * If you set this parameter to RV_TRUE, the stack will check if the NOTIFY 
 * is a result of SUBSCRIBE request forking. If this is the case,
 * new subscription object will be created and will handle this NOTIFY.
 * Default Value: RV_FALSE
 * Remarks: Group A parameter.
 *
 *
 * forkedAckTrxTimeout
 * -------------------
 * The forkedAckTrxTimeout timer is set when after a call-leg that was created due to forking
 * received a 200 response, and send an ACK request. The ACK is sent using a 
 * special ACK Transmitter. Since there might be a need to retransmit the ACK (if more
 * 2xx retransmissions will arrive), this Transmitter is not destructed immediately.
 * A timer is set to time supplied in the forkedAckTrxTimeout parameter and when 
 * this timer expires, the ACK Transmitter will be destructed.
 * If 0 (zero), no timer is set. The ACK transmitter will be destructed only on
 * call-leg destruction.
 * Default Value: 32,000
 * Remarks: Group A parameter.
 *
 * forked1xxTimerTimeout
 * ---------------------
 * The forked1xxTimerTimeout is set when a forked call-leg is created when 1xx response
 * is received and does not match any transaction.
 * If this timer expires, before 200 response is received, the forked call-leg will be terminated.
 * If 0 (zero), no timer is set. The call-leg should be terminated by application. 
 * Default Value: 180000. forked1xxTimerTimeout = provisionalTimer.
 * Remarks: Group B parameter.
 *
 * eOutboundProxyCompression
 * --------------------------
 * Indicates the compression type of the SIP stack messages that are sent to
 * configured outbound proxy.
 * Default Value: RVSIP_COMP_UNDEFINED
 * Remarks: Group A parameter.
 *
 * compartmentLogFilters
 * ------------------
 * Compartment module log filters.
 * Default Value: 0 桸o logging information
 * Remarks: Group A parameter.
 *
 * transmitterLogFilters
 * ------------------
 * Transmitter module log filters.
 * Default Value: 0 桸o logging information
 * Remarks: Group A parameter.
 *
 * maxCompartments
 * ---------------------
 * The maximum number of compartments that the stack allocates.
 * You should set this value to the maximum number of compartments you expect
 * the SIP Stack to handle simultaneously.
 * Default Value: 12
 * Remark: If the SigComp feature is enabled this value must be greater than 0.
 *         Group B parameter: maxCompartments = maxCallLegs + maxRegClients.
 *
 * sigCompTcpTimer
 * ------------------
 * Specifies the time duration the stack waits after a SigComp compressed message
 * is sent over TCP/TLS connection. When this timer expires the callback 
 * RvSipXXXSigCompMsgNotRespondedEv() is called and the application can deside how
 * to proceed.
 * Default Value: 0, no timer is set.
 * Remarks: Group A parameter.
 *
 * maxNumOfLocalAddresses
 * ----------------------
 * The maximum number of local addresses that the stack might use simultaneously.
 * Since the application can add and remove local addresses on run time it should
 * the stack must know the maximum number of concurrently used addresses on
 * initialization.
 * Default Value: 2
 * Remarks: Group B parameter: maxNumOfLocalAddresses = 1+numOfExtraUdpAddresses
 *                                                      +1+numOfExtraTcpAddresses
 *                                                      +numOfTlsAddresses
 * bEnableForking
 * ---------------
 * Indicates how to handle a second (or more) incoming responses that match
 * a single request. This can happen when the initial request was forked.
 * If this parameter is set to RV_FALSE, all responses will be mapped to the original
 * call-leg, and will update it's tag.
 * If this parameter is set to RV_TRUE, a new 'forked call-leg' will be created for 
 * each response.
 * Default Value: RV_FALSE
 * Remarks: Group A parameter
 * 
 * bDisableMerging
 * ---------------
 * Indicates how to handle an incoming request that has arrived more 
 * than once, following different paths, most likely due to forking.
 * According to RFC 3261 if the request has no tag in the To header field, 
 * and the From tag, Call-ID, and CSeq exactly match those associated with
 * an existing transaction, but the request does not match that transaction
 * it should be rejected with 482 (Loop Detected) response.
 * If the  bDisableMerging parameter is set to RV_TRUE, the request will 
 * not be rejected and will create a new server transaction that will be handled 
 * as a regular transaction.
 * If the  bDisableMerging parameter is set to RV_FALSE, the request will
 * be rejected according to the RFC.
 * Default Value: RV_FALSE
 * Remarks: Group A parameter
 *
 * adsLogFilters
 * ---------------
 * Ads module log filters. This filter defines the default logging level for all
 * the components in the ads modules. 
 * Default Value: 0 - no logging information.
 * Remarks: Group A parameter
 *
 * adsFiltersCfg
 * -------------
 * A structure that includes log filters configuration for each of the ads components.
 * Default Value: 0 - no logging information for any of the components.
 * Remarks: Group A parameter
 *
 * coreFiltersCfg
 * -------------
 * A structure that includes log filters configuration for each of the core components.
 * Default Value: 0 - no logging information for any of the components.
 * Remarks: Group A parameter
 *
 * pDnsServers
 * -----------
 * An array allocated by the application that holds DNS servers the stack will use
 * to resolve names. You MUST set the size of this array in the numOfDnsServers configuration
 * parameters.
 * if no DNS servers are listed, the stack will use the DNS servers that the operating
 * system is configured to use when the stack is initialized.
 * if the port number inside any of the addresses is set to 0, the port will be 
 * converted to the default "well known" DNS port (53).
 * Default Value: NULL
 * Remarks: Group A parameter
 *
 * numOfDnsServers
 * ---------------
 * The number of DNS servers in pDnsServers
 * Default Value: UNDEFINED
 * Remarks: Group A parameter
 *
 * pDnsDomains
 * -----------
 * A list of domains for DNS search. 
 * The Sip Stack provides Domain Suffix Search Order capability. The Domain 
 * Suffix Search Order specifies the DNS domain suffixes to be appended to 
 * the host names during name resolution. When attempting to resolve a fully 
 * qualified domain name (FQDN) from a host that includes a name only, 
 * the system will first append the local domain name to the host name and
 * will query the DNS servers. If this is not successful, the system will 
 * use the Domain Suffix list to create additional FQDNs in the order listed 
 * and will query DNS servers for each.
 * If you will not supply a domain list, the domain list will be set according to
 * the computer configuration. 
 * The domain list is given as an array of string pointers. You MUST set the size of
 * the list in the numOfDnsDomains configuration parameter.
 * Default Value: NULL - the domain will be taken from the operating system.
 * Remarks: Group A parameter
 *
 * numOfDnsDomains
 * ---------------
 * The size of the array given in pDnsDomains. (for )
 * Default Value: UNDEFINED
 * Remarks: Group A parameter
 *
 * maxDnsServers
 * -------------
 * The maximal number of DNS servers that the application will use concurrently.
 * The application can change the list of DNS servers on runtime. It must specify
 * in the maxDnsServers the maximum number of DNS servers it is expected to use.
 * Default Value: UNDEFINED
 * Remarks: Group A parameter
 *
 * maxDnsDomains
 * -------------
 * The maximal number of DNS domains that the application will use concurrently.
 * The application can change the list of DNS servers on runtime. It must specify
 * in the maxDnsDomains the maximum number of DNS domain it is expected to use.
 * Default Value: UNDEFINED
 * Remarks: Group A parameter
 *
 * maxDnsBuffLen
 * -------------
 * The maximal length of buffer used by the SIP Stack to read DNS query results 
 * arriving on TCP.
 * Default Value: 1024
 * Remarks: Group A parameter
 * 
 * bDLAEnabled
 * -----------
 * Indicates whether the DLA feature is enabled.
 * The DLS (dynamic local addresses) feature enables the application to add and
 * remove local addresses on run-time. If the feature is enabled the local address
 * list is protected by LOCK.
 * Default Value: RV_FALSE
 * Remarks: Group A parameter
 *
 * maxTransmitters
 * ----------------
 * The number of Transmitters the SIP stack allocates. You should set this
 * value to the maximum number of transmitters you expect the SIP Stack to
 * handle simultaneously. A transmitter is used for sending a message that
 * is not related to transactions such as ACK on 2xx for forked INVITE or
 * responses for messages with syntax errors that fail to create a transaction.
 * A transmitter object can also be used by the application for sending stand alone
 * messages.
 * Note: each stack transaction also uses a transmitter but the transmitters
 *       for the transaction objects are allocated by the stack automatically
 *       and you do not have to add them to the maxTransmitters parameters.
 * Default Value: 10
 * Remarks: Group B parameter: maxTransmitters = 10 + maxCallLegs;
 *          Note: if forking is not enabled there will be only 10 transmitter.
 *
 ********************************************************************************************/
typedef struct {
#ifndef RV_SIP_PRIMITIVES
    RvInt32  maxCallLegs;
#endif /*RV_SIP_PRIMITIVES */
    RvInt32  maxTransactions;
#ifndef RV_SIP_PRIMITIVES
    RvInt32  maxRegClients;
#endif /*RV_SIP_PRIMITIVES */
    RvInt32  messagePoolNumofPages;
    RvInt32  messagePoolPageSize;
    RvInt32  generalPoolNumofPages;
    RvInt32  generalPoolPageSize;
    RvInt32  sendReceiveBufferSize;
    RvChar   localUdpAddress[48];
    RvUint16 localUdpPort;
    RvChar   outboundProxyIpAddress[48];
    RvInt16  outboundProxyPort;
    RvInt32  retransmissionT1;
    RvInt32  retransmissionT2;
    RvInt32  generalLingerTimer;
    RvInt32  inviteLingerTimer;
    RvInt32  provisionalTimer;
    RvInt32  defaultLogFilters;
    RvInt32  coreLogFilters;
    RvInt32  msgLogFilters;
    RvInt32  transportLogFilters;
    RvInt32  transactionLogFilters;
    RvInt32  callLogFilters;
    RvInt32  parserLogFilters;
    RvInt32  stackLogFilters;
    RvInt32  msgBuilderLogFilters;
    RvInt32  authenticatorLogFilters;
    RvInt32  regClientLogFilters;
    /*new parameters for version 2.0*/
    RvSipStackPrintLogEntryEv   pfnPrintLogEntryEvHandler;
    void*                       logContext;
    RvChar   localTcpAddress[48];
    RvUint16 localTcpPort;
    RvInt32  maxConnections;
    RvBool   tcpEnabled;
#ifndef RV_SIP_PRIMITIVES
    RvChar*  supportedExtensionList;
    RvBool   rejectUnsupportedExtensions;
#endif /*RV_SIP_PRIMITIVES */
    RvBool   manualAckOn2xx;  //是否自动回复ACK 2xx
    RvBool   isProxy;
    RvInt32  proxy2xxRcvdTimer;
    RvInt32  proxy2xxSentTimer;
    RvChar** localUdpAddresses;
    RvUint16*localUdpPorts;
    RvChar** localTcpAddresses;
    RvUint16*localTcpPorts;
    RvInt32  numOfExtraUdpAddresses;
    RvInt32  numOfExtraTcpAddresses;

    /*new parameters for version 2.1*/
    RvBool   enableServerAuth;
#ifndef RV_SIP_PRIMITIVES
    RvBool   addSupportedListToMsg;
#endif /*RV_SIP_PRIMITIVES */
    RvBool   enableInviteProceedingTimeoutState;
    RvInt32  retransmissionT4;
    RvInt32  cancelGeneralNoResponseTimer;
    RvInt32  cancelInviteNoResponseTimer;
    RvInt32  generalRequestTimeoutTimer;
    
    /*new parameters for version 2.2*/
    RvUint32 maxElementsInSingleDnsList;
    RvUint32 numberOfProcessingThreads;
    RvInt32  processingQueueSize;
    RvInt32  numOfReadBuffers;
    RvUint32 processingTaskPriority;
    RvUint32 processingTaskStackSize;
    RvInt32  subscriptionLogFilters;
#ifndef RV_SIP_PRIMITIVES
    RvInt32  maxSubscriptions;
    RvInt32  subsAlertTimer;
    RvInt32  subsNoNotifyTimer;
    RvBool   subsAutoRefresh;
    RvInt32  sessionExpires;
    RvInt32  minSE;
    RvBool   manualSessionTimer;
#endif /*RV_SIP_PRIMITIVES */
    RvBool   manualBehavior;

    /*new parameters for version 3.0*/
    RvBool   bUseRportParamInVia;
    RvSipTransportPersistencyLevel ePersistencyLevel;
    RvInt32  serverConnectionTimeout;
    RvChar*  outboundProxyHostName;
    RvSipTransport eOutboundProxyTransport;

    /* Tls */
    RvInt32     numOfTlsAddresses;
    RvChar**    localTlsAddresses;
    RvUint16*   localTlsPorts;
    RvInt32     numOfTlsEngines;
    RvInt32     maxTlsSessions;
                
    RvInt32     elementPoolNumofPages;
    RvInt32     elementPoolPageSize;
    RvBool      bDynamicInviteHandling;

    /*new parameters for version 3.1*/
#ifndef RV_SIP_PRIMITIVES
    RvBool             bDisableRefer3515Behavior;
    RvBool             bEnableSubsForking;
    RvInt32            forkedAckTrxTimeout;
    RvInt32            forked1xxTimerTimeout;
    RvBool             manualPrack;
#endif /*RV_SIP_PRIMITIVES */
    RvSipCompType      eOutboundProxyCompression;
    RvInt32            compartmentLogFilters;
    RvInt32            transmitterLogFilters;
    RvInt32            maxCompartments;
    RvInt32            sigCompTcpTimer;
    RvInt32            maxNumOfLocalAddresses;
    RvBool             bEnableForking;
    RvBool             bDisableMerging;
    RvInt32            adsLogFilters;
    RvSipStackAdsLogFiltersCfg  adsFiltersCfg;
    RvSipStackCoreLogFiltersCfg coreFiltersCfg;
    RvSipTransportAddr* pDnsServers;
    RvInt32             numOfDnsServers;
    RvChar**            pDnsDomains;
    RvInt32             numOfDnsDomains;
    RvInt32             maxDnsServers;
    RvInt32             maxDnsDomains;
    RvInt32             maxDnsBuffLen;
    RvBool              bDLAEnabled;
    RvInt32             maxTransmitters;
}RvSipStackCfg;



#ifdef SIP_DEBUG
/********************************************************************************************
 * RvSipStackStatistics
 * -----------------------------------------------------------------------------
 * RvSipStackStatistics structure manages the statistics of sent and received messages
 *
 * rcvdINVITE
 * -----------
 * Total INVITE messages received (including retransmission)
 *
 * rcvdINVITERetrans
 * -----------------
 * INVITE retransmissions received
 *
 * rcvdNonInviteReq
 * ----------------
 * Total non-INVITE requests received (including retransmission)
 *
 * rcvdNonInviteReqRetrans
 * -----------------------
 * non-INVITE retransmissions received
 *
 * rcvdResponse
 * ------------
 * Total responses received
 *
 * rcvdResponseRetrans
 * -------------------
 * responses retransmissions received
 *
 * sentINVITE
 * ----------
 * Total INVITE messages sent (including retransmission)
 *
 * sentINVITERetrans
 * -----------------
 * INVITE retransmissions sent
 *
 * sentNonInviteReq
 * ----------------
 * Total non-INVITE requests sent (including retransmission)
 *
 * sentNonInviteReqRetrans
 * -----------------------
 * non-INVITE request retransmissions sent
 *
 * sentResponse
 * ------------
 * Total responses sent
 *
 * sentResponseRetrans
 * -------------------
 * Response retransmissions sent
 *
 ********************************************************************************************/
typedef struct
{
    RvUint32 rcvdINVITE;
    RvUint32 rcvdINVITERetrans;
    RvUint32 rcvdNonInviteReq;
    RvUint32 rcvdNonInviteReqRetrans;
    RvUint32 rcvdResponse;
    RvUint32 rcvdResponseRetrans;
    RvUint32 sentINVITE;
    RvUint32 sentINVITERetrans;
    RvUint32 sentNonInviteReq;
    RvUint32 sentNonInviteReqRetrans;
    RvUint32 sentResponse;
    RvUint32 sentResponseRetrans;

} RvSipStackStatistics;

#endif /* SIP_DEBUG */


#ifdef __cplusplus
}
#endif

#endif  /*END OF: define _RV_SIP_STACK_TYPES_H*/
