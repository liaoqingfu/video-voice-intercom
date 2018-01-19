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
 *                              <RvSipTransportTypes.h>
 *
 * The transport layer of the RADVISION SIP toolkit allows you to control sending
 * and receiving of messages over the network.
 * This file defines the prototypes for message-received and message-to-send
 * callbacks.
 *
 *    Author                         Date
 *    ------                        ------
 *    Tamar Barzuza                 Jan 2002
 *********************************************************************************/


#ifndef RVSIP_TRANSPORTTYPES_H
#define RVSIP_TRANSPORTTYPES_H

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
#include "RvSipMsg.h"
#include "RvSipMsgTypes.h"

/*-----------------------------------------------------------------------*/
/*                          TYPE DEFINITIONS                             */
/*-----------------------------------------------------------------------*/
/*Sip default port for UDP and TCP*/
#define RVSIP_TRANSPORT_DEFAULT_PORT 5060

/*Sip default port for TLS (secure port)*/
#define RVSIP_TRANSPORT_DEFAULT_TLS_PORT 5061

/*Length of the string, representing IP, used by Stack*/
#define RVSIP_TRANSPORT_LEN_STRING_IP 51 /* sizeof("[ffff:ffff:ffff:ffff:ffff:ffff:255.255.255.255]%dd")+'\0' */

/*Number of bytes in ipv6 addess*/
#define RVSIP_TRANSPORT_LEN_BYTES_IPV6 16 

/*
 * RvSipTransportMgrHandle
 * ---------------------------------------------------------------------------
 * Declaration of handle to the Transport Manager object.
 */
RV_DECLARE_HANDLE(RvSipTransportMgrHandle);

/*
 * RvSipAppTransportMgrHandle
 * ---------------------------------------------------------------------------
 * Declaration of application handle to a Transport Manager.
 * This handle can be used as a context that the application can hold in the transport
 * manager.
*/
RV_DECLARE_HANDLE(RvSipAppTransportMgrHandle);

/*
 * RvSipTransportConnectionHandle
 * ---------------------------------------------------------------------------
 * Declaration of handle to a Connection object. A connection object is used
 * for TCP/TLS communication.
 */
RV_DECLARE_HANDLE(RvSipTransportConnectionHandle);

/*
 * RvSipTransportConnectionOwnerHandle
 * ---------------------------------------------------------------------------
 * Declaration of handle to the owner of a Connection object. A connection
 * can have several owners. All owners are notified of connection events.
 */
RV_DECLARE_HANDLE(RvSipTransportConnectionOwnerHandle);


/*
 * RvSipTransportTlsEngineHandle
 * ---------------------------------------------------------------------------
 * Declaration of handle to a Transport Tls Engine. The stack toolkit can hold
 * several different Tls engines each with different attributes. different Tls engines
 * can be used to set different sets of Tls attributes to different connections
 */
RV_DECLARE_HANDLE(RvSipTransportTlsEngineHandle);

/*
 * RvSipTransportConnectionAppHandle
 * ---------------------------------------------------------------------------
 * An application handle that the application can set and get from the connection.
 * a connection can hold only one application handle.
 */
RV_DECLARE_HANDLE(RvSipTransportConnectionAppHandle);

/*
 * RvSipTransportLocalAddrHandle
 * ---------------------------------------------------------------------------
 * Handle to the Local Address object, which is used by Stack for receiption
 * or sending messages, and for listening for new connections.
 */
RV_DECLARE_HANDLE(RvSipTransportLocalAddrHandle);

/*
 * RvSipTransportTlsCertificate
 * ---------------------------------------------------------------------------
 * A pointer to a certificate retrieved from a connection or used in the compare
 * certificate call back
 */
RV_DECLARE_HANDLE(RvSipTransportTlsCertificate);

/*
 * RvSipTransportPersistencyLevel
 * ---------------------------------------------------------------------------
 * defines the persistency level in the system. undefined means that there is no
 * persistency of connection. one connection is used for a request and its response.
 * after the response is sent the connection is closed.
 * RVSIP_TRANSPORT_PERSISTENCY_LEVEL_UNDEFINED  -- no persistency of connections
 * RVSIP_TRANSPORT_PERSISTENCY_LEVEL_TRANSC,    -- all messages of a transaction
 *                                                 are sent on the same connection
 * RVSIP_TRANSPORT_PERSISTENCY_LEVEL_TRANSC_USER     -- all messages of a layers
 *                                                  written above the transaction layer.
 */
typedef enum
{
    RVSIP_TRANSPORT_PERSISTENCY_LEVEL_UNDEFINED = -1,
    RVSIP_TRANSPORT_PERSISTENCY_LEVEL_TRANSC,
    RVSIP_TRANSPORT_PERSISTENCY_LEVEL_TRANSC_USER
} RvSipTransportPersistencyLevel;


/* RvSipTransportAddressType
 * ---------------------------
 * The RvSipTransportAddressType Determines whether the address is ip4 or ip6.
 */
typedef enum
{
    RVSIP_TRANSPORT_ADDRESS_TYPE_UNDEFINED = -1,
    RVSIP_TRANSPORT_ADDRESS_TYPE_IP,
    RVSIP_TRANSPORT_ADDRESS_TYPE_IP6
} RvSipTransportAddressType;


/*  RvSipTransportAddr
 * -------------------
 *  A structure contains some parameters of the address, that can be used
 *  by Stack for network communication.
 *
 *  eTransportType  - type of the transport protocol, used with the address.
 *  eAddrType       - type of IP address. E.g IPv4, IPv6.
 *  port            - port.
 *  strIP           - NULL terminated string, representing IP. 
 *                    (IPv6 in this string will be represented by xxxx:xxxx:..:xxxx)
 */
typedef struct
{
    RvSipTransport              eTransportType;
    RvSipTransportAddressType   eAddrType;
    RvUint16                    port;
    RvChar                      strIP[RVSIP_TRANSPORT_LEN_STRING_IP];
    RvInt                       Ipv6Scope;
} RvSipTransportAddr;

/* RvSipTransportBsAction
 * ---------------------------
 * The RvSipTransportBsAction determines how to proceed handling a received
 * message with bad-syntax.
 * This definition is for use as an output parameter, in RvSipTransportBadSyntaxMsgEv
 * and RvSipTransportBadSyntaxStartLineMsgEv callback functions.
 * RVSIP_TRANSPORT_BS_ACTION_DISCARD_MSG - Do nothing, discard the bad-syntax message.
 *                                        (same behavior as was in stack version 2.2)
 * RVSIP_TRANSPORT_BS_ACTION_REJECT_MSG - Send 400 response for the bad-syntax message.
 *                                        (relevant only for request messages).
 * RVSIP_TRANSPORT_BS_ACTION_CONTINUE_PROCESS - Stack continue in message processing,
 *                                        as much as can be done. stack will process the
 *                                        bad-syntax message, until it will find that an
 *                                        essential header has a syntax error, then send
 *                                        400 response. if all essential headers are correct,
 *                                        the message will be process successfully by stack.
 */
typedef enum
{
    RVSIP_TRANSPORT_BS_ACTION_UNDEFINED = -1,
    RVSIP_TRANSPORT_BS_ACTION_DISCARD_MSG,
    RVSIP_TRANSPORT_BS_ACTION_REJECT_MSG,
    RVSIP_TRANSPORT_BS_ACTION_CONTINUE_PROCESS
}RvSipTransportBsAction;


/*  RvSipTransportConnectionCfg
 * --------------------------------
 *  A structure containing all configuration needed in order to initialize
 *  a new connection. You need to supply this structure when calling the
 *  RvSipTransportConnectionInit function.
 *
 *  eTransportType - transport type - TCP/TLS
 *  strLocalIp - local ip as a string - ipv6 should be in []%sid format. If null
 *               is supplied a default local ip is chosen.
 *  localPort  - the local port. Zero is replaced with the transport default port
 *               (5060 for TCP and 5061 for TLS).
 *               the local port is ignored if the strLocalIp was not specified.
 *
 *  strDestIp - destination ip as a string - ipv6 should be supplied in a [] format.
 *  strDestPort - destination port.  Zero is replaced with the transport default port
 *               (5060 for TCP and 5061 for TLS).
 *  bEnablePersistency- specifies whether to insert the connection to the hash or not.
 *
 *  strHostName - If the connection type is TLS this string will be used for post connection assertion
 */
typedef struct
{
     IN  RvSipTransport      eTransportType;
     IN  RvChar*            strLocalIp;
     IN  RvUint16           localPort;
     IN  RvChar*            strDestIp;
     IN  RvUint16           destPort;
     IN  RvChar*            strHostName;
} RvSipTransportConnectionCfg;


/*  RvSipTransportConnectionState
 * --------------------------------
 * The connection state.
 */
typedef enum
{
    RVSIP_TRANSPORT_CONN_STATE_UNDEFINED = -1,
    RVSIP_TRANSPORT_CONN_STATE_IDLE,
    RVSIP_TRANSPORT_CONN_STATE_READY,
    RVSIP_TRANSPORT_CONN_STATE_CONNECTING,
    RVSIP_TRANSPORT_CONN_STATE_TCP_CONNECTED,
    RVSIP_TRANSPORT_CONN_STATE_CLOSING,
    RVSIP_TRANSPORT_CONN_STATE_CLOSED,
    RVSIP_TRANSPORT_CONN_STATE_TERMINATED
}RvSipTransportConnectionState;


/* RvSipTransportConnectionTlsState
 * --------------------------------
 * The connection's TLS state.
 * RVSIP_TRANSPORT_CONN_TLS_STATE_UNDEFINED - No TLS sequence was initiated on the connection.
 * RVSIP_TRANSPORT_CONN_TLS_STATE_HANDSHAKE_COMPLETED - Handshake procedure on the connection was completed.
 * RVSIP_TRANSPORT_CONN_TLS_STATE_HANDSHAKE_READY - The connection is TCP connected and is ready to start the TLS handshake.
 * RVSIP_TRANSPORT_CONN_TLS_STATE_HANDSHAKE_STARTED - The connection is performing handshake.
 * RVSIP_TRANSPORT_CONN_TLS_STATE_HANDSHAKE_FAILED - The TLS handshake has failed. No data can be transmitted on the connection.
 * RVSIP_TRANSPORT_CONN_TLS_STATE_CLOSE_SEQUENSE_STARTED - The connection has received or sent a close request but is not closed yet.
 * RVSIP_TRANSPORT_CONN_TLS_STATE_CONNECTED - Data can be sent on the connection.
 * RVSIP_TRANSPORT_CONN_TLS_STATE_TERMINATED - The connection is terminated. After that point the connection may not be accessed again.
 */
typedef enum
{
    RVSIP_TRANSPORT_CONN_TLS_STATE_UNDEFINED = -1,
    RVSIP_TRANSPORT_CONN_TLS_STATE_HANDSHAKE_COMPLETED,
    RVSIP_TRANSPORT_CONN_TLS_STATE_HANDSHAKE_READY,
    RVSIP_TRANSPORT_CONN_TLS_STATE_HANDSHAKE_STARTED,
    RVSIP_TRANSPORT_CONN_TLS_STATE_HANDSHAKE_FAILED,
    RVSIP_TRANSPORT_CONN_TLS_STATE_CLOSE_SEQUENSE_STARTED,
    RVSIP_TRANSPORT_CONN_TLS_STATE_CONNECTED,
    RVSIP_TRANSPORT_CONN_TLS_STATE_TERMINATED
}RvSipTransportConnectionTlsState;

/*  RvSipTransportConnectionStatus
 * -----------------------------------
 * The status of a connection.
 * ERROR - the connection has an error
 * MSG_SENT - A message was sent successfully by the connection
 *                         This notification is given only to the owner that actually sent the
 *                         message such  as a transaction. The application will never receive this
 *                         status.
 * MSG_NOT_SENT - A message wasn't sent successfully over the connection
*/
typedef enum
{
    RVSIP_TRANSPORT_CONN_STATUS_UNDEFINED = 1,
    RVSIP_TRANSPORT_CONN_STATUS_ERROR,
    RVSIP_TRANSPORT_CONN_STATUS_MSG_SENT,
    RVSIP_TRANSPORT_CONN_STATUS_MSG_NOT_SENT
}RvSipTransportConnectionStatus;


/*  RvSipTransportConnectionStateChangedReason
 *  ------------------------------------------
 *  A reason supplied with the state changes function of a connection.
 *  The reason is used only if it supplies more information about the new
 *  state. Otherwise the reason is undefined.
 */
typedef enum
{
    RVSIP_TRANSPORT_CONN_REASON_UNDEFINED = -1,
    RVSIP_TRANSPORT_CONN_REASON_ERROR,
    RVSIP_TRANSPORT_CONN_REASON_CLIENT_CONNECTED,
    RVSIP_TRANSPORT_CONN_REASON_SERVER_CONNECTED,
    RVSIP_TRANSPORT_CONN_REASON_TLS_POST_CONNECTION_ASSERTION_FAILED,
    RVSIP_TRANSPORT_CONN_REASON_DISCONNECTED
}RvSipTransportConnectionStateChangedReason;


/* RvSipPrivateKeyType
 * ---------------------------
 * The RvSipTransportAddressType Determines the key type to use in a TLS engine.
 */
typedef enum
{
    RVSIP_TRANSPORT_PRIVATE_KEY_TYPE_UNDEFINED = -1,
    RVSIP_TRANSPORT_PRIVATE_KEY_TYPE_RSA_KEY
}RvSipTransportPrivateKeyType;

/* RvSipTlsMethod
 * ---------------------------
 * The RvSipTlsMethod Determines the version of TLS to use in an engine.
 */
typedef enum
{
    RVSIP_TRANSPORT_TLS_METHOD_UNDEFINED = -1,
    RVSIP_TRANSPORT_TLS_METHOD_SSL_V2,
    RVSIP_TRANSPORT_TLS_METHOD_SSL_V3,
    RVSIP_TRANSPORT_TLS_METHOD_TLS_V1
}RvSipTransportTlsMethod;

/* RvSipTransportTlsHandshakeSide
 * ---------------------------
 * The RvSipTransportTlsHandshakeSide Determines side of TLS handshake to assume.
 * Default means TCP client will act as TLS client and TCP server will act as TLS server.
 * Default is the recommended way of working.
 */
typedef enum
{
    RVSIP_TRANSPORT_TLS_HANDSHAKE_SIDE_UNDEFINED = -1,
    RVSIP_TRANSPORT_TLS_HANDSHAKE_SIDE_DEFAULT,
    RVSIP_TRANSPORT_TLS_HANDSHAKE_SIDE_CLIENT,
    RVSIP_TRANSPORT_TLS_HANDSHAKE_SIDE_SERVER
}RvSipTransportTlsHandshakeSide;

/*  RvSipTransportMsgAddrCfg
 * --------------------------------
 *  A structure containing all configuration needed in order to inject a
 *  message to the SIP Stack.
 *  You need to supply this structure when calling the RvSipTransportInjectMsg function.
 *  The given addresses indicates how the stack shall demonstrate the receiving of
 *  this message:
 *  local address is the address that demonstrated to receive this message. this is the
 *  stack address, that the response will be sent from.
 *  dest address is the address that demonstrated to be the remote party that sent this
 *  message. this is the address to send the response to.
 *
 *  eTransportType - transport type - UDP/TCP/TLS. if UUNDEFINED, use the default UDP.
 *  strLocalIp - local ip as a string - ipv6 should be in []%sid format. If null
 *               is supplied a default local ip is chosen.
 *  localPort  - the local port. Zero is replaced with the transport default port
 *               (5060 for UDP/TCP and 5061 for TLS).
 *
 *  strDestIp   - destination ip as a string - ipv6 should be supplied in a [] format.
 *                If NULL, no destination address will be set, and response will be
 *                sent, according to the address in the top via header.
 *  strDestPort - destination port.  Zero is replaced with the transport default port
 *               (5060 for UDP/TCP and 5061 for TLS).
 */
typedef struct
{
     IN  RvSipTransport      eTransportType;
     IN  RvChar*            strLocalIp;
     IN  RvUint16           localPort;
     IN  RvChar*            strDestIp;
     IN  RvUint16           destPort;
} RvSipTransportMsgAddrCfg;


/*  RvSipTransportOutboundProxyCfg
 * --------------------------------
 *  A structure containing all configuration needed in order to set
 *  the outbound proxy details, that will be use in case of outgoing
 *  messages toward a proxy.
 *
 * strIpAddress
 * -----------------------
 * Indicates the IP address of an outbound proxy the SIP Stack uses.
 * Default Value: 0—no outbound proxy
 *
 * port
 * -----------------
 * Indicates the port of the outbound proxy the SIP Stack uses.
 * Default Value: 5060
 *
 * strHostName
 * ---------------------
 * The host name of an outbound proxy the SIP Stack uses. For each outgoing request
 * the DNS will be queried for this host IP address.
 * Note: If you set the outboundProxyIPAddress parameter, the outboundProxyHostName
 * parameter will be ignored.
 * Default value: NULL
 *
 * eTransport
 * ----------------------
 * Indicates the transport of the outbound proxy the SIP Stack uses.
 * Default Value: RVSIP_TRANSPORT_UNDEFINED
 *
 * eCompression
 * --------------------------
 * Indicates the compression type of the SIP stack messages that are sent to
 * the outbound proxy.
 * Default Value: RVSIP_COMP_UNDEFINED
 *
 */
typedef struct
{
    RvChar       *strIpAddress;
    RvInt32       port;
    RvChar       *strHostName;
    RvSipTransport eTransport;
#ifdef RV_SIGCOMP_ON
    RvSipCompType  eCompression;
#endif
} RvSipTransportOutboundProxyCfg;

/******************************************************************************
 * RvSipTransportConnectionStateChangedEv
 * ----------------------------------------------------------------------------
 * General: The connection is a statefull object that can assume different
 *          states according to the Connection state machine.
 *          Through this function, you receive notifications
 *          of connection state changes and the associated state change reason.
 *          In a regular connection life cycle, the reason for the state is set
 *          to RVSIP_TRANSPORT_CONN_REASON_UNDEFINED. When the connection
 *          is closed because of an error, the reason is set to
 *          RVSIP_TRANSPORT_CONN_REASON_ERROR.
 *          Note You do not have to register to this callback
 *          if you do not want to get connection states.
 * Return Value: Ignored.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hConn   -   The connection handle
 *          hObject -   For server connection: application handle
 *                      for client connection: handle to the connection owner
 *          eState  -   The connection state
 *          eReason -   A reason for the new state or undefined if there is
 *                      no special reason.
 *****************************************************************************/
typedef RvStatus (RVCALLCONV *RvSipTransportConnectionStateChangedEv) (
                        IN RvSipTransportConnectionHandle              hConn,
                        IN RvSipTransportConnectionOwnerHandle         hObject,
                        IN RvSipTransportConnectionState               eState,
                        IN RvSipTransportConnectionStateChangedReason  eReason);

/***************************************************************************
 * RvSipTransportConnectionStatusEv
 * ------------------------------------------------------------------------
 * General: The connection notifies about events that do not effect the
 *   connection state using the connection status callback. If, for example,
 *   there was an error in the connection, the connection will notify the
 *   application with RVSIP_TRANSPORT_CONN_STATUS_ERROR. The connection will then
 *   disconnect with the RVSIP_TRANSPORT_CONN_REASON_ERROR reason.
 *   Note You do not have to register to this callback if you do not want to get
 *   connection statuses.
 * Return Value: Ignored.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:      hConn   -   The connection handle
 *           hOwner  -   Handle to the connection owner.
 *           eStatus -   The connection status
 *           pInfo   -   For future usage.
 ***************************************************************************/
typedef RvStatus (RVCALLCONV *RvSipTransportConnectionStatusEv) (
                        IN RvSipTransportConnectionHandle      hConn,
                        IN RvSipTransportConnectionOwnerHandle hOwner,
                        IN RvSipTransportConnectionStatus      eStatus,
                        IN void*                               pInfo);




/***************************************************************************
 * RvSipTransportVerifyCertificateEv
 * ------------------------------------------------------------------------
 * General:  This function is called to application whenever a certificate
 *           needs to be processed. to leave the stack decision regarding a
 *           certificate return the prevError param as the return value
 * Return Value: RvInt32
 * ------------------------------------------------------------------------
 * Arguments: prevError - Error previously detected by the stack. a positive
 *            number indicates that the certificate is OK.
 *            Certificate - the certificate the callback is called for. this
 *            certificate can be encoded using RvSipTransportTlsEncodeCert()
 * Input:
 ***************************************************************************/
typedef RvInt32   (* RvSipTransportVerifyCertificateEv)(
                                                        IN    RvInt32 prevError,
                                                        IN    RvSipTransportTlsCertificate  certificate);
/*  RvSipTransportTlsEngineCfg
 * --------------------------------
 *  A structure containing all configuration needed in order to initialize
 *  a new TLS engine. You need to supply this structure when calling the
 *  RvSipTransportTlsEngineConstruct function.
 *
 *  eTlsMethod      - SSL/TLS version
 *  strPrivateKey   - The private key for the engine
 *  ePrivateKeyType - Private key type.
 *  privateKeyLen   - size of key
 *  strCert         - certificate issued for that engine.
 *  certLen         - size of certificate
 *  certDepth       - how long can a chain of certificate be before is is considered invalid.
 */

typedef struct
{
    RvSipTransportTlsMethod                        eTlsMethod;
    RvChar*                                       strPrivateKey;
    RvSipTransportPrivateKeyType                   ePrivateKeyType;
    RvInt32                                       privateKeyLen;
    RvChar*                                       strCert;
    RvInt32                                       certLen;
    RvInt32                                       certDepth;
} RvSipTransportTlsEngineCfg;

/***************************************************************************
 * RvSipTransportConnectionTlsSequenceStartedEv
 * ------------------------------------------------------------------------
 * General:  Notifies that a connection has reached the state where TLS
 *           Sequence has started.
 *           This is the place for the application to exchange handles with
 *           the TLS connection. If an AppHandle was previously set to the connection
 *           it will be in phAppConn, that way the application can keep track
 *           if the connection was created by the application
 * Return Value: (-)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hConn - A connection that has started the TLS sequence
 * Output:     phAppConn - The handle given by the application
 ***************************************************************************/
typedef void
        (RVCALLCONV * RvSipTransportConnectionTlsSequenceStartedEv)(
                                   IN  RvSipTransportConnectionHandle            hConn,
                                   INOUT RvSipTransportConnectionAppHandle*   phAppConn);

/***************************************************************************
 * RvSipTransportConnectionTlsStateChangedEv
 * ------------------------------------------------------------------------
 * General:  This callback is used to notify the application on TLS
 *           connection state changes. This callback is called only for
 *           TLS state changes and not for connection state changes
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hConnection  - The handle of the connection that changed TLS state
 *          hAppHandle   - An application handle for the connection
 *           eState       - The connection state
 *          eReason      - The reason for the state change
 ***************************************************************************/
typedef RvStatus (RVCALLCONV * RvSipTransportConnectionTlsStateChangedEv)(
                                                        IN    RvSipTransportConnectionHandle             hConnection,
                                                        IN    RvSipTransportConnectionAppHandle       hAppConnection,
                                                        IN    RvSipTransportConnectionTlsState              eState,
                                                        IN    RvSipTransportConnectionStateChangedReason eReason);

/***************************************************************************
 * RvSipTransportConnectionTlsPostConnectionAssertionEv
 * ------------------------------------------------------------------------
 * General:  This callback is used to override the stack's default post connection
 *           assertion. once a connection has completed the hand shake, it is
 *           necessary to make sure that the certificate presented was indeed issued
 *           for the address to which the connection was made. that assertion is
 *           automaticly done by the stack, if for some reason, the application would
 *           like to over ride a failed assertion it can implement this callback.
 *           for example: This callback can be used to compare the host name against
 *           a predefined list of outgoing proxies.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hConnection   - The handle of the connection that changed TLS state
 *          hAppConnection - The application handle for the connection
 *           strHostName   - A NULL terminated string, indicating the host name
 *                          (IP/FQDN) that the connection was meant to connect to.
 *          hMsg          - a message if the connection was asserted against a message.
 * Output: pbAsserted     - Fill that boolean with the result of your assertion.
 *                          RV_TRUE - indicated you asserted the connection, succesfully.
 *                          RV_FALSE - indicates the assertion failed. the connection
 *                                     will be terminated automaticly.
 ***************************************************************************/
typedef void (RVCALLCONV * RvSipTransportConnectionTlsPostConnectionAssertionEv)(
                                                        IN    RvSipTransportConnectionHandle             hConnection,
                                                        IN    RvSipTransportConnectionAppHandle          hAppConnection,
                                                        IN    RvChar*                                   strHostName,
                                                        IN    RvSipMsgHandle                             hMsg,
                                                        OUT   RvBool*                                   pbAsserted);

/***************************************************************************
 * RvSipTransportObjectEventHandler
 * ------------------------------------------------------------------------
 * General:  This function process the event of a specific object
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     pObj        - A pointer to the object to terminate.
 *           eventReason -  The reason of the event
 ***************************************************************************/
typedef RvStatus   (RVCALLCONV* RvSipTransportObjectEventHandler)(
                                                        IN    void      *pObj,
                                                        IN    RvInt32   eventReason);

/* RvSipTransportObjEventInfo
 * ------------------------------
 * Each object that wishes to terminate using the event queue must hold such
 * a structure.
 * next                    - pointer to next object to be terminated
 * reason                - termination reason
 * func                    - termination function to be applied
 */
typedef struct TransportObjEventInfo {
    struct TransportObjEventInfo                *next;
    RvInt32                                    reason;
    RvSipTransportObjectEventHandler            func;
    void*                                       objHandle;
} RvSipTransportObjEventInfo;

/***************************************************************************
 * RvSipTransportMsgToSendEv
 * ------------------------------------------------------------------------
 * General:  RvSipTransportMsgToSendEv() notifies the application that a
 *           new message is about to be sent.
 *           The application can decide whether the transport layer
 *           should not transmit the message to its destination.
 * Return Value: RV_TURE to transmit the message. RV_FALSE to discard the
 *               message without transmiting it to destination.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTransportMgr - A handle to the transport manager object.
 *           hAppTransportMgr - The application handle. You supply this handle
 *                         when setting the event handles
 *          msgBuffer - The about to be sent message (given in a consecutive
 *                      buffer).
 *          bufferLen - The length of the message buffer.
 ***************************************************************************/
typedef RvBool (RVCALLCONV * RvSipTransportMsgToSendEv)(
                      IN    RvSipTransportMgrHandle   hTransportMgr,
                      IN    RvSipAppTransportMgrHandle hAppTransportMgr,
                      IN    RvChar                  *msgBuffer,
                      IN    RvUint                   bufferLen);


/***************************************************************************
 * RvSipTransportMsgReceivedEv
 * ------------------------------------------------------------------------
 * General:  RvSipTransportMsgReceivedEv() notifies the application that a
 *           new message is received.
 *           The application can decide whether the transport layer
 *           should discard the message, in which case the stack will not
 *           process this message.
 * Return Value: RV_TURE to accept the receipt of the message and process it
 *               in the stack. RV_FALSE to discard the message without
 *               further processing.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTransportMgr - A handle to the transport manager object.
 *           hAppTransportMgr - The application handle. You supply this handle
 *                         when setting the event handles
 *          hMsgReveived - The received message.
 ***************************************************************************/
typedef RvBool (RVCALLCONV * RvSipTransportMsgReceivedEv)(
                      IN    RvSipTransportMgrHandle   hTransportMgr,
                      IN    RvSipAppTransportMgrHandle hAppTransportMgr,
                      IN    RvSipMsgHandle            hMsgReceived);

/***************************************************************************
 * RvSipTransportMsgThreadError
 * ------------------------------------------------------------------------
 * General:  Notifies that one of the stack processing threads has terminated
 *           unexpectedly. Multithreaded applications can register to this
 *           callback.
 * Return Value: (-)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTransportMgr - A handle to the transport manager object.
 *           error         -  RV_ERROR_NUM_OF_THREADS_DECREASED
 ***************************************************************************/
typedef void (RVCALLCONV * RvSipTransportMsgThreadError)(
                     IN RvSipTransportMgrHandle   hTransportMgr,
                     IN RvStatus                  error);

/***************************************************************************
 * RvSipTransportBadSyntaxMsgEv
 * ------------------------------------------------------------------------
 * General:  RvSipTransportBadSyntaxMsgReceivedEv() notifies the application
 *           that a new bad-syntax message is received.
 *           The application can fix the message in this callback and no later.
 *           The application should use the eAction parameter to decide how
 *           stack will handle this message: discard it, continue with message
 *           processing, or send 400 response (in case of request message).
 *           see the RvSipTransportBsAction definition for more details.
 *           If application did not implemented this callback, the bad-syntax
 *           message will be discard.
 * Return Value: RV_OK.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTransportMgr    - A handle to the transport manager object.
 *           hAppTransportMgr - The application handle. You supply this handle
 *                             when setting the event handles
 *          hMsgReveived     - The received bad-syntax message.
 * Output:  peAction         - User decision of stack way of handling this message.
 ***************************************************************************/
typedef RvStatus (RVCALLCONV * RvSipTransportBadSyntaxMsgEv)(
                      IN    RvSipTransportMgrHandle   hTransportMgr,
                      IN    RvSipAppTransportMgrHandle hAppTransportMgr,
                      IN    RvSipMsgHandle            hMsgReceived,
                      OUT   RvSipTransportBsAction    *peAction);

/***************************************************************************
 * RvSipTransportBadSyntaxStartLineMsgEv
 * ------------------------------------------------------------------------
 * General:  RvSipTransportBadSyntaxStartLineMsgEv() notifies the application
 *           that a new message is received, with bad-syntax start-line.
 *           The application can fix the message in this callback and no later.
 *           The application should use the eAction parameter to decide how
 *           stack will handle this message: discard it, continue with message
 *           processing, or send 400 response (in case of request message).
 *           see the RvSipTransportBsAction definition for more details.
 *           If application did not implemented this callback, the bad-syntax
 *           message will be discard.
 * Return Value: RV_OK.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTransportMgr    - A handle to the transport manager object.
 *           hAppTransportMgr - The application handle. You supply this handle
 *                             when setting the event handles
 *          hMsgReveived     - The received message, with bad-syntax start-line.
 * Output:  peAction         - User decision of stack way of handling this message.
 ***************************************************************************/
typedef RvStatus (RVCALLCONV * RvSipTransportBadSyntaxStartLineMsgEv)(
                      IN    RvSipTransportMgrHandle   hTransportMgr,
                      IN    RvSipAppTransportMgrHandle hAppTransportMgr,
                      IN    RvSipMsgHandle            hMsgReceived,
                      OUT   RvSipTransportBsAction    *peAction);

/******************************************************************************
 * RvSipTransportConnectionCreatedEv
 * ----------------------------------------------------------------------------
 * General: Notifies the application about an incoming TCP connection.
 *          The callback is called immediately after the connection is accepted
 *          The application can order the SIP  Stack to close the connection
 *          by means of the pbDrop parameter. In this case, the connection
 *          will be closed immediately after returning from the callback and
 *          its resources will be freed. No data will be received or sent
 *          on the connection. If application did not register to this callback
 *          the connection will not be closed, and will be used for data
 *          sending and reception.
 *
 * Return Value: none.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hTransportMgr    - A handle to the transport manager object.
 *          hAppTransportMgr - The application handle. You supply this handle
 *                             when setting the event handles.
 *          hConn            - handle to the created connection.
 * Output:  phAppConn        - The handle that the application set for the
 *                             connection.
 *          pbDrop           - If set to RV_TRUE by application, the connection
 *                             will be dropped immediately after returning from
 *                             the callback. Otherwise, the connection will not
 *                             be dropped and will be used for data reception
 *                             and sending. The default value is RV_FALSE.
 *****************************************************************************/
typedef void (RVCALLCONV * RvSipTransportConnectionCreatedEv)(
                    IN  RvSipTransportMgrHandle             hTransportMgr,
                    IN  RvSipAppTransportMgrHandle          hAppTransportMgr,
                    IN  RvSipTransportConnectionHandle      hConn,
                    OUT RvSipTransportConnectionAppHandle   *phAppConn,
                    OUT RvBool                              *pbDrop);

/***************************************************************************
 * RvSipTransportBufferReceivedEv
 * ------------------------------------------------------------------------
 * General: Exposes the raw data buffer to an application that contains exactly
 *          one SIP message that was received on the TCP/UDP layer.
 *          The application can dump the data by means of this callback.
 *          Also, the application can order the SIP Stack to discard the buffer
 *          and not to parse it, by means of the pbDiscardBuffer parameter.
 *
 * Return Value: none.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hTransportMgr    - A handle to the transport manager object.
 *          hAppTransportMgr - The application handle. You supply this handle
 *                             when setting the event handles
 *          hLocalAddr       - Handle to Local Address object, corresponding to
 *                             address on which the buffer was received.
 *          pSenderAddrDetails - A pointer to Transport Address structure,
 *                             which contains details of the address from which
 *                             the message was sent.
 *          hConn            - handle of the connection, on which the buffer
 *                             was received. NULL for UDP.
 *          hAppConn         - handle, set by Application for the connection.
 *          buffer           - pointer to the buffer,which contains the message
 *          buffLen          - length of the message in the buffer (in bytes)
 * Output:  bDiscardBuffer   - if set to RV_TRUE, the buffer will be not
 *                             processed, the resources will be freed. 
 ***************************************************************************/
typedef void (RVCALLCONV * RvSipTransportBufferReceivedEv)(
                    IN  RvSipTransportMgrHandle             hTransportMgr,
                    IN  RvSipAppTransportMgrHandle          hAppTransportMgr,
                    IN  RvSipTransportLocalAddrHandle       hLocalAddr,
                    IN  RvSipTransportAddr                  *pSenderAddrDetails,
                    IN  RvSipTransportConnectionHandle      hConn,
                    IN  RvSipTransportConnectionAppHandle   hAppConn,
                    IN  RvChar                              *buffer,
                    IN  RvUint32                            buffLen,
                    OUT RvBool                              *pbDiscardBuffer);

/***************************************************************************
 * RvSipTransportBufferToSendEv
 * ------------------------------------------------------------------------
 * General: Exposes the raw data buffer to an application, which contains
 *          exactly one SIP message, that is going to be sent on TCP/UDP layer.
 *          The application can dump the data by means of this callback.
 *          Also, the application can decide whether the Transport layer should
 *          not transmit the message to its destination.
 *          Note that discarding does not affect the state of the sender object
 *          This ability to discard was developed to simulate
 *          message loss on net.
 *
 * Return Value: none.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hTransportMgr    - A handle to the transport manager object.
 *          hAppTransportMgr - The application handle. You supply this handle
 *                             when setting the event handles
 *          hLocalAddr       - Handle to Local Address object, corresponding to
 *                             address from which the buffer is going to be sent
 *          pDestAddrDetails - pointer to the Transport Address structure,
 *                             which contains details of the address,
 *                             to which the message is going to be sent.
 *          hConn            - handle of the connection, on which the buffer
 *                             is going to be sent. NULL for UDP.
 *          hAppConn         - handle, set by Application for the connection.
 *          buffer           - pointer to the buffer,which contains the message
 *          buffLen          - length of the message in the buffer (in bytes)
 * Output:  bDiscardBuffer   - if set to RV_TRUE, the buffer will be not sent,
 *                             the resources will be freed. 
 ***************************************************************************/
typedef void (RVCALLCONV * RvSipTransportBufferToSendEv)(
                    IN  RvSipTransportMgrHandle             hTransportMgr,
                    IN  RvSipAppTransportMgrHandle          hAppTransportMgr,
                    IN  RvSipTransportLocalAddrHandle       hLocalAddr,
                    IN  RvSipTransportAddr                  *pDestAddrDetails,
                    IN  RvSipTransportConnectionHandle      hConn,
                    IN  RvSipTransportConnectionAppHandle   hAppConn,
                    IN  RvChar                              *buffer,
                    IN  RvUint32                            buffLen,
                    OUT RvBool                              *pbDiscardBuffer);

/******************************************************************************
 * RvSipTransportConnectionParserResultEv
 * ----------------------------------------------------------------------------
 * General: Indicates the parsing result for the message to an application
 *          which arrived over the TCP connection.
 *          If the parser encounters bad syntax, the bLegalSyntax is RV_FALSE.
 *          Otherwise it is RV_TRUE.
 *
 * Return Value: none.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hTransportMgr    - A handle to the transport manager object.
 *          hAppTransportMgr - The application handle. You supply this handle
 *                             when setting the event handles.
 *          hMsg             - The handle to the message that was parsed.
 *          hConn            - A handle to the connection, on which the message
 *                             to be parsed, arrived.
 *          hAppConn         - The handle that the application sets for
 *                             the connection.
 *          bLegalSyntax     - RV_TRUE, if no bad syntax was discovered by
 *                             parser. RV_FALSE - otherwise.
 * Output:  none. 
*****************************************************************************/
typedef void (RVCALLCONV * RvSipTransportConnectionParserResultEv)(
                        IN  RvSipTransportMgrHandle           hTransportMgr,
                        IN  RvSipAppTransportMgrHandle        hAppTransportMgr,
                        IN  RvSipMsgHandle                    hMsg,
                        IN  RvSipTransportConnectionHandle    hConn,
                        IN  RvSipTransportConnectionAppHandle hAppConn,
                        IN  RvBool                            bLegalSyntax);


/* RvSipTransportMgrEvHandlers
 * ------------------------------------------------------------------------
 * Structure with function pointers to the transport module call-back.
 * This structure is used to set the application call-backs in the function
 * RvSipTransportMgrSetEvHandlers();
 *
 * pfnEvMsgToSend       - Notify that a message is about to be sent. Allow
 *                        the application to decide whether to continue
 *                        sending this message or not.
 * pfnEvMsgReceived     - notify that a message was received. Allow
 *                        the application to decide whether to continue
 *                        processing this message or not.
 * pfnThreadError       - notify according to thread exit events.
 * pfnEvBadSyntaxMsg    - notify that a bad-syntax message was received.
 * pfnEvBadSyntaxStartLineMsg - notify that a message with bad-syntax
 *                        start-line was received.
 * pfnEvTlsStateChanged - notifies the application on TLS connection state
 *                        changes.
 * pfnEvTlsPostConnectionAssertion - if set to something other the NULL,
 *                        will enable the application to control
 *                        post connection assertions.
 * pfnEvTlsSeqStarted   - Indicates the beginning of a TLS procedure
 *                        on a connection
 * pfnEvBufferReceived  - Gives the application the opportunity to discard
 *                        the buffer before parsing. The remote and local
 *                        addresses are supplied.
 *                        The application can also dump the buffer.
 * pfnEvBufferToSend    - Allows the application to dump the message buffer.
 * pfnEvConnCreated     - Notifies application about creation of connection
 *                        object for incoming TCP connection.
 * pfnEvConnParserResult- Indicates the result of parsing of incoming message
 * pfnEvConnStateChanged- Notifies application about incoming Connection
 *                        state change.
 */
typedef struct
{
    RvSipTransportMsgToSendEv                               pfnEvMsgToSend;
    RvSipTransportMsgReceivedEv                             pfnEvMsgRecvd;
    RvSipTransportMsgThreadError                            pfnThreadError;
    RvSipTransportBadSyntaxMsgEv                            pfnEvBadSyntaxMsg;
    RvSipTransportBadSyntaxStartLineMsgEv                   pfnEvBadSyntaxStartLineMsg;
    RvSipTransportConnectionTlsStateChangedEv               pfnEvTlsStateChanged;
    RvSipTransportConnectionTlsPostConnectionAssertionEv    pfnEvTlsPostConnectionAssertion;
    RvSipTransportConnectionTlsSequenceStartedEv            pfnEvTlsSeqStarted;
    RvSipTransportBufferReceivedEv                          pfnEvBufferReceived;
    RvSipTransportBufferToSendEv                            pfnEvBufferToSend;
    RvSipTransportConnectionCreatedEv                       pfnEvConnCreated;
    RvSipTransportConnectionParserResultEv                  pfnEvConnParserResult;
    RvSipTransportConnectionStateChangedEv                  pfnEvConnStateChanged;
} RvSipTransportMgrEvHandlers;


/* RvSipTransportMgrEvHandlers
 * ------------------------------------------------------------------------
 * Structure with function pointers to the connection call-backs.
 * You should supply this structure for every new connection.
 * pfnConnStateChangedEvHandler - A callback function to notify the owner
 *                                about connection status.
 * pfnConnStausEvHandler - A callback function to notify owner about connection
 *                         status such as ERROR.
 */
typedef struct
{
    RvSipTransportConnectionStateChangedEv  pfnConnStateChangedEvHandler;
    RvSipTransportConnectionStatusEv        pfnConnStausEvHandler;
} RvSipTransportConnectionEvHandlers;


#ifdef __cplusplus
}
#endif


#endif /* END OF: #ifndef RVSIP_TRANSPORTTYPES_H */



