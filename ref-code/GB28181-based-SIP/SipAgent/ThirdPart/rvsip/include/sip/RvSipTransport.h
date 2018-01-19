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
 *                              <RvSipTransport.h>
 *
 * The transport layer of the RADVISION SIP toolkit allows you to control sending
 * and receiving of messages over the network.
 * This file defines the API for the transport layer.
 *
 *    Author                         Date
 *    ------                        ------
 *    Tamar Barzuza                 Jan 2002
 *********************************************************************************/


#ifndef RVSIP_TRANSPORT_H
#define RVSIP_TRANSPORT_H

#ifdef __cplusplus
extern "C" {
#endif


#include "RV_SIP_DEF.h"
#include "RvSipTransportTypes.h"
#include "RvSipTransportDNS.h"

/*-----------------------------------------------------------------------*/
/*                TRANSPORT MANAGER  API                                  */
/*-----------------------------------------------------------------------*/



/***************************************************************************
 * RvSipTransportMgrSetEvHandlers
 * ------------------------------------------------------------------------
 * General: Set event handlers for all transport events.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTransportMgr - Handle to the transport manager.
 *            hAppTransportMgr - An application handle. This handle will be supplied
 *                        with some of transport callbacks
 *          pHandlers   - Pointer to structure containing application event
 *                        handler pointers.
 *          evHandlerStructSize - The size of the event handler structure.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportMgrSetEvHandlers(
                        IN RvSipTransportMgrHandle          hTransportMgr,
                        IN RvSipAppTransportMgrHandle       hAppTransportMgr,
                        IN RvSipTransportMgrEvHandlers     *pHandlers,
                        IN RvUint32                        evHandlerStructSize);

/***************************************************************************
 * RvSipTransportMgrSetAppMgrHandle
 * ------------------------------------------------------------------------
 * General: Sets the handle to the application transport manger object.
 *          You can also supply this handle when calling
 *          RvSipTransportMgrSetEvHandlers().
 *
 * Return Value: RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTransportMgr - Handle to the stack transport manager.
 *           phAppTransportMgr - The application transport manager handle.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportMgrSetAppMgrHandle(
                                   IN RvSipTransportMgrHandle      hTransportMgr,
                                   IN RvSipAppTransportMgrHandle   phAppTransportMgr);

/***************************************************************************
 * RvSipTransportMgrGetAppMgrHandle
 * ------------------------------------------------------------------------
 * General: Returns the handle to the application transport manger object.
 *          You set this handle in the stack using the
 *          RvSipTransportMgrSetEvHandlers() function.
 *
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTransportMgr - Handle to the transport manager.
 * Output:     hAppTransportMgr - The application transport manager handle.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportMgrGetAppMgrHandle(
                         IN RvSipTransportMgrHandle        hTransportMgr,
                         OUT RvSipAppTransportMgrHandle*   hAppTransportMgr);



/***************************************************************************
 * RvSipTransportMgrGetStackInstance
 * ------------------------------------------------------------------------
 * General: Returns the handle to the stack instance to which this transport
 *          manager belongs to.
 *
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTransportMgr   - Handle to the transport manager.
 * Output:     phStackInstance - A valid pointer which will be updated with a
 *                            handle to the stack instance. In order to use this
 *                            pointer as a stack handle you need to cast it to
 *                            RvSipStackHandle.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportMgrGetStackInstance(
                                   IN RvSipTransportMgrHandle hTransportMgr,
                                   OUT  void*                *phStackInstance);

/*-----------------------------------------------------------------------*/
/*                TRANSPORT MANAGER  UTILITY FUNCTIONS                   */
/*-----------------------------------------------------------------------*/


/***************************************************************************
 * RvSipTransportConvertStringToIp
 * ------------------------------------------------------------------------
 * General: Converts an ip from string format to binary format
 * Return Value: RV_OK, RV_ERROR_UNKNOWN or RV_ERROR_BADPARAM
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTransportMgr     - Handle to the transport manager
 *          pszIpAsString    - a NULL terminated string representing an ip address
 *                             (d.d.d.d for ipv4, x:x:x:x:x:x:x:x for ipv6)
 *                             Note: do not use [] for ipv6 addresses.
 *             eAddressType     - represent the type of address ipv6/ipv4
 * Output:  pIpAsBinary      - the ip address represented in binary.
 *                             (16 bytes for ipv6, 4 bytes for ipv4)
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportConvertStringToIp (IN  RvSipTransportMgrHandle   hTransportMgr,
                                                            IN  RvChar*                  strIpAsString,
                                                            IN  RvSipTransportAddressType eAddressType,
                                                            OUT RvUint8*                  pIpAsBinary);

/***************************************************************************
 * RvSipTransportConvertIpToString
 * ------------------------------------------------------------------------
 * General: Converts an IP address from a binary format to a string format
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTransportMgr     - Handle to the transport manager
 *          pIpAsBinary      - The ip address represented in a binary format.
 *                             (16 bytes for ipv6, 4 bytes for ipv4)
 *          stringLen        - the size of the buffer.
 *             eAddressType     - represent the type of address ipv6/ipv4
 * Output:  strIpAsString    - a NULL terminated string representing an ip address
 *                             (d.d.d.d for ipv4, x:x:x:x:x:x:x:x for ipv6)
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportConvertIpToString (IN  RvSipTransportMgrHandle   hTransportMgr,
                                                            IN  RvUint8*                  pIpAsBinary,
                                                            IN  RvSipTransportAddressType eAddressType,
                                                            IN  RvInt32                  stringLen,
                                                            OUT RvChar*                  strIpAsString);
#ifndef RV_SIP_PRIMITIVES
/***************************************************************************
 * RvSipTransportInjectMsg
 * ------------------------------------------------------------------------
 * General: This function enables the application to 'inject' a message to the stack.
 *          The message will be handled by the stack as if it was received from the
 *          network.
 *          The message may be given as a string or as a message object.
 *          You can optionally supply a local and remote addresses for this message.
 *          Suppling a local address is useful in the case of multihomed host when
 *          you want to simulate a message that is received from a specific network
 *          card. For request messages this will cause the response to be sent from
 *          the same card. If you supply a remote address this address will be set
 *          as the received parameter of the Via header for incoming requests. Responses
 *          will then be sent to this address.
 *          If you want to simulate a message that was received on a specific connection
 *          you can supply a connection handle. In that the local and remote addresses
 *          will be taken from the connection and the pAddressInfo will be ignored.
 *          Note: If you don't care about addresses you can supply NULL value in the
 *          pAddressInfo and the hConn parameter.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTransportMgr  - Handle to the transport manager.
 *          pMsgBuffer     - The 'injected' message in a string format.
 *          totalMsgLength - Total length of the massage given in pMsgBuffer.
 *          hMsg           - Handle to the 'injected' message, in a message object format.
 *            hConn          - The connection handle that the message is 'injected' to.
 *          pAddressInfo   - Structure contains the local address and remote address.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportInjectMsg(
                        IN  RvSipTransportMgrHandle            hTransportMgr,
                        IN  RvChar                        *pMsgBuffer,
                        IN  RvUint32                       totalMsgLength,
                        IN  RvSipMsgHandle                  hMsg,
                        IN  RvSipTransportConnectionHandle  hConn,
                        IN  RvSipTransportMsgAddrCfg       *pAddressInfo);

#endif /*#ifndef RV_SIP_PRIMITIVES */

/*-----------------------------------------------------------------------*/
/*                TRANSPORT CONNECTION API                               */
/*-----------------------------------------------------------------------*/
/***************************************************************************
 * RvSipTransportMgrCreateConnection
 * ------------------------------------------------------------------------
 * General: Constructs a new un-initialized connection and attach the supplied
 *          owner to the connection. The owner's event handlers structure
 *          is saved together with the connection owner.
 *          The new connection assumes the IDLE state.
 *          Calling the RvSipTransportConnectionInit() function at this state
 *          will initialize the connection and will cause the connection to move
 *          to the READY state.
 *          NOTE: This function does not connect the connection. In order to
 *          connect the connection you must first initialize it.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTransportMgr - Handle to the transport manager.
 *          hOwner     - An handle to the connection owner.
 *          pEvHanders  - Event handlers structure for this connection owner.
 *          sizeofEvHandlers - The size of the Event handler structure
 * Output:  phConn     - handle to a newly creates connection.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportMgrCreateConnection(
     IN  RvSipTransportMgrHandle                 hTransportMgr,
     IN  RvSipTransportConnectionOwnerHandle     hOwner,
     IN  RvSipTransportConnectionEvHandlers      *pEvHandlers,
     IN  RvInt32                                sizeofEvHandlers,
     OUT RvSipTransportConnectionHandle          *phConn);



/***************************************************************************
 * RvSipTransportConnectionInit
 * ------------------------------------------------------------------------
 * General: Initializes a connection with all needed configuration parameters
 *          found in the RvSipTransportConnectionCfg structure. You can call
 *          this function only on the IDLE state. This function will cause the
 *          connection to move to the READY state.
 *          The initialized connection is inserted to the connection hash
 *          and therefor can be used by any persistent stack object.
 *          Note: This function does not connect the connection. The connection
 *          will be connected when a stack object will use it for
 *          sending a message or if you will specifically call the
 *          RvSipTransportConnectionConnect() function. In both cases the connection
 *          will assume the TCP_CONNECTING and then the TCP_CONNECTED states.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hConn - Handle to the connection to be initialized.
 *          pCfg  - The configuration to use when initializing the connection.
 *          sizeofCfg - The size of the configuration structure.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportConnectionInit(
                        IN RvSipTransportConnectionHandle      hConn,
                        IN RvSipTransportConnectionCfg        *pCfg,
                        IN RvInt32                             sizeofCfg);

/***************************************************************************
 * RvSipTransportConnectionConnect
 * ------------------------------------------------------------------------
 * General: Connects a Connection. You can call this function only on the
 *          READY state. Calling this function will
 *          cause the connection to move to the CONNECTING state. The connection
 *          will move to the CONNECTED state when an indication that the connection
 *          was successfully connected will be received from the network.
 *          Note:
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hConn - Handle to the connection to connect.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportConnectionConnect(
                        IN RvSipTransportConnectionHandle hConn);

/***************************************************************************
 * RvSipTransportConnectionTerminate
 * ------------------------------------------------------------------------
 * General: The function behavior depends on the connection state.
 *          If the connection is in the TCP_CONNECTED or TLS_CONNECTED state the
 *          connection will start a normal disconnection process. TCP connections
 *          will move to the CLOSING state. TLS connections will move to the
 *          TLS_CLOSE_SEQUENSE_STARTED and then to the CLOSING state.
 *          For all other states the connection will close it internal socket if
 *          the socket was opened and will terminate. After termination the connection
 *          will assume the TERMINATED state.
 *          Note: If the connection has messages that it is about to send these
 *          messages will be lost. It is therefor not recommended to use this
 *          function. If you no longer need this connection call the
 *          RvSipTransportConnectionDetachOwner() function. The connection will be
 *          closed only when the last owner is detached. This means that if the
 *          connection is still beeing used by other stack objects it will not
 *          be closed until these objects will detach from it.
 *
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hConn - Handle to the connection to be terminated
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportConnectionTerminate(
                        IN  RvSipTransportConnectionHandle  hConn);

/***************************************************************************
 * RvSipTransportConnectionAttachOwner
 * ------------------------------------------------------------------------
 * General: Attach a new owner to the supplied connection together with a set
 *          of callback functions that will be used to notify this owner about
 *          connection events. You can use this function only if
 *          the connection is connected or in the process of being connected.
 *          You cannot attach an owner to a connection that started its
 *          disconnection process.
 *          Notes:
 *          Note: The connection will not disconnect as long as it has owners
 *          attached to it.
 *              Application can't attach owner to incoming connection.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hConn - Handle to the connection.
 *          hOwner - The owner handle
 *          pEvHanders  - Event handlers structure for this connection owner.
 *          sizeofEvHandlers - The size of the event handler tructure.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportConnectionAttachOwner(
            IN  RvSipTransportConnectionHandle            hConn,
            IN  RvSipTransportConnectionOwnerHandle       hOwner,
            IN  RvSipTransportConnectionEvHandlers        *pEvHandlers,
            IN  RvInt32                                  sizeofEvHandlers);


/***************************************************************************
 * RvSipTransportConnectionDetachOwner
 * ------------------------------------------------------------------------
 * General: Detach an owner from the supplied connection.
 *          If the connection is left with no other owners it will be closed.
 *          If the same owner attached to a connection more then once the first
 *          matching owner will be removed.
 *          Note: After detaching from a connection you will stop getting
 *          connection events and you must not use the connection handle any more.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hConn - Handle to the connection.
 *          hOwner - Handle to the owner to detach from the connection
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportConnectionDetachOwner(
            IN  RvSipTransportConnectionHandle            hConn,
            IN  RvSipTransportConnectionOwnerHandle       hOwner);


/***************************************************************************
 * RvSipTransportConnectionEnable
 * ------------------------------------------------------------------------
 * General: Inserts a connection object to the hash so that persistent objects
 *          will be able to use it.
 *          Note: When ever a connection is initialized with the function
 *          RvSipTransportConnectionInit() it is automatically inserted to
 *          the hash.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hConn       - Handle to the connection.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportConnectionEnable(
                                        IN  RvSipTransportConnectionHandle hConn);

/***************************************************************************
 * RvSipTransportConnectionDisable
 * ------------------------------------------------------------------------
 * General: Removes a connection object from the hash so that persistent objects
 *          will not be able to use it. Objects that are already using the connection
 *          (are in the connection owners list) will continue to use the connection.
 *          however, other objects will not be able to use the connection as long
 *          as the connection is Disabled.
 *          Note: in order to insert the connection back to the hash use
 *          RvSipTransportConnectionEnable().
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hConn       - Handle to the connection.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportConnectionDisable(
                                        IN  RvSipTransportConnectionHandle hConn);


/***************************************************************************
 * RvSipTransportConnectionIsEnabled
 * ------------------------------------------------------------------------
 * General: Returns whether the connection is enabled (in the hash) or not.
 *          An enabled connection is a connection that can be used by persistent
 *          objects.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hConn       - Handle to the connection.
 * Output   pbIsEnabled  - RV_TRUE if the connection is enabled. RV_FALSE otherwise.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportConnectionIsEnabled(
                                        IN  RvSipTransportConnectionHandle hConn,
                                        OUT RvBool             *pbIsEnabled);


/***************************************************************************
 * RvSipTransportConnectionGetCurrentState
 * ------------------------------------------------------------------------
 * General: Retrieves the connection current state
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hConn       - Handle to the connection.
 * Output:  peState    - The connection current state
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportConnectionGetCurrentState(
                        IN  RvSipTransportConnectionHandle  hConn,
                        OUT RvSipTransportConnectionState  *peState);

/***************************************************************************
 * RvSipTransportConnectionIsTcpClient
 * ------------------------------------------------------------------------
 * General: Returns whether the connection is a TCP client or TCP server
 *          connection.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hConn       - Handle to the connection.
 * Output:  pbIsClient  - RV_TRUE if the connection is a TCP client. RV_FALSE otherwise.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportConnectionIsTcpClient(
                        IN  RvSipTransportConnectionHandle  hConn,
                        OUT RvBool                         *pbIsClient);

/***************************************************************************
 * RvSipTransportConnectionGetNumOfOwners
 * ------------------------------------------------------------------------
 * General: Retrieves the number of owners currently attached to the connection.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hConn       - Handle to the connection.
 * Output:  pNumOfOwners    - Number of connection owners.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportConnectionGetNumOfOwners(
                                        IN  RvSipTransportConnectionHandle hConn,
                                        OUT RvInt32                *pNumOfOwners);

/***************************************************************************
 * RvSipTransportConnectionGetTransportType
 * ------------------------------------------------------------------------
 * General: Retrieves the connection transport (TCP/TLS)
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hConn       - Handle to the connection.
 * Output:  peTransport - The connection transport
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportConnectionGetTransportType(
                                        IN  RvSipTransportConnectionHandle hConn,
                                        OUT RvSipTransport          *peTransport);

/***************************************************************************
 * RvSipTransportConnectionGetLocalAddress
 * ------------------------------------------------------------------------
 * General: Retrieves the local address of the connection. The local address
 *          includes the local IP, local Port and the address type (IPv4 or IPv6).
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:
 *            hConn       - Handle to the connection.
 * Output:  pAddress    - A previously allocated buffer to where the local address
 *                        will be copied to.
 *                        The buffer should have a minimum size of 48.
 *          pPort       - The local port.
 *          peAddressType - The local address type IPV4/IPv6
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportConnectionGetLocalAddress(
                                        IN  RvSipTransportConnectionHandle hConn,
                                        OUT RvChar             *strAddress,
                                        OUT RvUint16           *pPort,
                                        OUT RvSipTransportAddressType *peAddressType);

/***************************************************************************
 * RvSipTransportConnectionGetRemoteAddress
 * ------------------------------------------------------------------------
 * General: Retrieves the remote address of the connection. The remote address
 *          includes the remote IP, remote Port and the remote address type
 *         (IPv4 or IPv6).
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:
 *            hConn       - Handle to the connection.
 * Output:  srtAddress    - A previously allocated buffer to where the remote address
 *                        will be copied to.
 *                        The buffer should have a minimum size of 48.
 *          pPort       - The remote port.
 *          peAddressType - The remote address type IPV4/IPv6
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportConnectionGetRemoteAddress(
                                        IN  RvSipTransportConnectionHandle hConn,
                                        OUT RvChar             *strAddress,
                                        OUT RvUint16           *pPort,
                                        OUT RvSipTransportAddressType *peAddressType);

/***************************************************************************
 * RvSipTransportConnectionGetStackInstance
 * ------------------------------------------------------------------------
 * General: Returns the handle to the stack instance to which this transport
 *          manager belongs to.
 *
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hRegClientMgr   - Handle to the register-client manager.
 * Output:     phStackInstance - A valid pointer which will be updated with a
 *                            handle to the stack instance.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportConnectionGetStackInstance(
                                   IN  RvSipTransportConnectionHandle  hConn,
                                   OUT void                 **phStackInstance);

/***************************************************************************
 * RvSipTransportConnectionGetAppHandle
 * ------------------------------------------------------------------------
 * General: retrieves the connection's application handle
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hConn          - The connection handle
 * Output:  phAppHandle - The connection application handle
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportConnectionGetAppHandle(
                        IN  RvSipTransportConnectionHandle  hConn,
                        OUT RvSipTransportConnectionAppHandle *phAppHandle);

/***************************************************************************
 * RvSipTransportConnectionSetAppHandle
 * ------------------------------------------------------------------------
 * General: sets the connection's application handle
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hConn         - The connection handle
 *      :   hAppHandle - The connection application handle
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportConnectionSetAppHandle(
                        IN  RvSipTransportConnectionHandle  hConn,
                        IN  RvSipTransportConnectionAppHandle hAppHandle);


/*-----------------------------------------------------------------------*/
/*                TRANSPORT TLS API                                      */
/*-----------------------------------------------------------------------*/
/***************************************************************************
 * RvSipTransportConnectionGetCurrentTlsState
 * ------------------------------------------------------------------------
 * General: retrieves the connection current TLS state
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hConn       - The connection handle
 * Output:  peState    - The connection current TLS state
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportConnectionGetCurrentTlsState(
                        IN RvSipTransportConnectionHandle hConn,
                        OUT RvSipTransportConnectionTlsState* peState);

/***************************************************************************
 * RvSipTransportTlsEngineConstruct
 * ------------------------------------------------------------------------
 * General: Constructs a TLS engine.
 *          Tls Engine is an entity that holds together a number of characteristics
 *          related to TLS sessions. When making a TLS handshake you have to
 *          provide an engine. The handshake parameters will be derived from the
 *          engines parameters.
 *          For example, you can create a "TLS client" engine by calling
 *          RvSipTransportTlsEngineAddTrastedCA() after an engine has been
 *          constructed.
 *          Once an engine has been constructed it can be used to preform TLS
 *          handshakes. A handshake that uses an engine will 'inherit' it TLS
 *          characteristics, (e.g. TLS version)
 *
 *
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTransportMgr - Handle to the transport manager.
 *          pTlsEngineCfg - a pointer to a configuration struct the holds data
 *          for the TLS engine.
 *          sizeofCfg - The size of the configuration structure
 * Output:  phTlsEngine     - a newly creates Tls engine.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportTlsEngineConstruct(
                        IN RvSipTransportMgrHandle          hTransportMgr,
                        IN RvSipTransportTlsEngineCfg*      pTlsEngineCfg,
                        IN RvInt32                         sizeofCfg,
                        OUT RvSipTransportTlsEngineHandle*  phTlsEngine);

/***************************************************************************
 * RvSipTransportTlsEngineAddCertificateToChain
 * ------------------------------------------------------------------------
 * General: Adds a TLS certificate to chain of certificate. The engine holds
 *          a chain of certificates needed for its approval (usually ending
 *          with a self signed certificate).
 *          The engine will display the chain of certificates during handshakes
 *          in which it is required to present certificates.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTransportMgr - Handle to the transport manager.
 *          hTlsEngine    - A handle to Tls engine.
 *          strCert       - The certificate encoded as ASN.1 string representation .
 *          certLen       - The length of the certificate
 * Output:
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportTlsEngineAddCertificateToChain(
                        IN RvSipTransportMgrHandle          hTransportMgr,
                        IN RvSipTransportTlsEngineHandle    hTlsEngine,
                        IN RvChar                          *strCert,
                        IN RvInt32                         certLen);

/***************************************************************************
 * RvSipTransportTlsEngineAddTrustedCA
 * ------------------------------------------------------------------------
 * General: Adds a trusted certificate authority to an engine.
 *          After that function is used the engine will approve all certificates
 *          issued by the CA.
 *          A CA (Certificate Authority) is an entity that issues certificates.
 *          Most TLS clients on the net trust one or more CAs and approve only
 *          certificates that were issued by those CAs. After adding a trusted CA
 *          to an engine you can use it as a "TLS client" engine and use that
 *          connection on handshakes in which you request the other side of the
 *          connection to display it certificates.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTransportMgr - Handle to the transport manager.
 *          hTlsEngine    - A handle to Tls engine.
 *          strCert       - The certificate encoded as ASN.1 string representation .
 *          certLen       - The length of the certificate
 * Output:
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportTlsEngineAddTrustedCA(
                        IN RvSipTransportMgrHandle          hTransportMgr,
                        IN RvSipTransportTlsEngineHandle    hTlsEngine,
                        IN RvChar                          *strCert,
                        IN RvInt32                         certLen);

/***************************************************************************
 * RvSipTransportConnectionTlsHandshake
 * ------------------------------------------------------------------------
 * General: starts TLS negotiation on a connection
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input: hConnection - connection on which to start the handshake
 *        hEngine     - The TLS engine that will be associated with the connection.
 *                    The connection will "inherit" the engine's parameters.
 *        eHandshakeSide - the TLS handshake side that the
 *                    connection will play on the TLS handshake. Using
 *                    the default enumeration will set the handshake side to be
 *                    client for TCP clients and Server for TCP servers
 *        pfnVerifyCertEvHandler - callback to check certificates that arrived
 *                    during handshake.
 *                    Client handshake side: NULL means use the default callback - valid
 *                                           certificates will be approved and invalid
 *                                           certificates will be rejected, causing a handshake
 *                                           failure.
 *                                           The callback function supplied here overrides that default.
 *                    Server handshake side: NULL means no client certificates.
 *                                           The callback function supplied here will require
 *                                           client certificate.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportConnectionTlsHandshake(
                 IN RvSipTransportConnectionHandle         hConnection,
                 IN RvSipTransportTlsEngineHandle          hEngine,
                 IN RvSipTransportTlsHandshakeSide         eHandshakeSide,
                 IN RvSipTransportVerifyCertificateEv      pfnVerifyCertEvHandler);

/***************************************************************************
 * RvSipTransportConnectionTlsGetEncodedCert
 * ------------------------------------------------------------------------
 * General: Retrieves a certificate from a connection.if the allocated buffer
 * is insufficient, the length of the buffer needed will be inserted in pCertLen.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hConnection - connection on to get cert of
 *          pCertLen    - The allocated cert buffer len
 * OutPut:  pCertLen    - The real size of the certificate in case the buffer was not sufficient.
 *          strCert     - an allocated buffer to hold the certificate.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportConnectionTlsGetEncodedCert(
                         IN    RvSipTransportConnectionHandle         hConnection,
                         INOUT RvInt32                              *pCertLen,
                         OUT   RvChar                               *strCert);

/***************************************************************************
 * RvSipTransportTlsEncodeCert
 * ------------------------------------------------------------------------
 * General: Encodes a certificate to a buffer in DER(ASN.1) format.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hCert - the certificate to encode
 *          pCertLen - the buffer length
 * Output:  strCert - the certificate encoded into Asn.1 format
 *       :  pCertLen    - The length of the certificate. (bytes)
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportTlsEncodeCert(
                        IN    RvSipTransportTlsCertificate           hCert,
                        INOUT RvInt32                              *pCertLen,
                        OUT   RvChar                               *strCert);

/***************************************************************************
 * RvSipTransportTlsGetCertVerificationError
 * ------------------------------------------------------------------------
 * General: retrieves an error string in the the verification callback
 * Return Value: the error string.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hCert - the handle of the certificate
 * Output:  strError - the error string
 ***************************************************************************/
RVAPI RvChar* RVCALLCONV RvSipTransportTlsGetCertVerificationError(
                         IN    RvSipTransportTlsCertificate           hCert,
                         OUT   RvChar                              **strError);

/***************************************************************************
 * RvSipTransportTlsEngineCheckPrivateKey
 * ------------------------------------------------------------------------
 * General: Checks the consistency of a private key with the corresponding
 *          certificate loaded into the engine. If more than one key/certificate pair
 *          (RSA/DSA) is installed, the last item installed will be checked. If e.g.
 *          the last item was a RSA certificate or key, the RSA key/certificate
 *          pair will be checked.
 *          This is a utility function for the application to make sure the key and
 *          certificate were loaded correctly into the engine.
 * Return Value: RV_OK - the key and certificate match
 *               RV_ERROR_UNKNOWN - the key and certificate does not match
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTransportMgr - Handle to the transport manager.
 *          hTlsEngine    - A Tls engine.
 * Output:
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportTlsEngineCheckPrivateKey(
                        IN RvSipTransportMgrHandle          hTransportMgr,
                        IN RvSipTransportTlsEngineHandle    hTlsEngine);


/*---------------FUNCTIONS FOR INTERNAL USAGE (not to be documented)------------*/

/***************************************************************************
 * RvSipTransportSendObjectEvent
 * ------------------------------------------------------------------------
 * General: Sends an event through the event queue.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:
 *          hTransportMgr - The transport manager handle.
 *          pObj          - Pointer to the object to be terminated.
 *          pEventInfo    - Pointer to an allocated uninitialised structure
 *                          used for queueing object events.
 *          reason        - event reason
 *          func          - event callback function - this function will be
 *                          called when the event will be poped
 *                          from the event queue.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportSendObjectEvent(
                                    IN RvSipTransportMgrHandle          hTransportMgr,
                                    IN void*                            pObj,
                                    IN RvSipTransportObjEventInfo*      pEventInfo,
                                    IN RvInt32                          reason,
                                    IN RvSipTransportObjectEventHandler func);



/***************************************************************************
 * RvSipTransportGetNumOfIPv4LocalAddresses
 * ------------------------------------------------------------------------
 * General: Returns the number of local addresses that the stack listens to.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:
 *          pTransportMgr    - A pointer to the transport manager
 *          pNumberOfAddresses - The number of local addresses for which the
 *                              stack listens.
 *
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportGetNumOfIPv4LocalAddresses(
                                     IN   RvSipTransportMgrHandle    hTransportMgr,
                                     OUT  RvUint32                 *pNumberOfAddresses);

/***************************************************************************
 * RvSipTransportGetIPv4LocalAddressByIndex
 * ------------------------------------------------------------------------
 * General: Retrieves the local address by index. Used when the stack was
 *          initialized with IPv4 local address of 0, and therefore listens
 *          on several distinct local addresses.
 *          To know how many local addresses are available by this function
 *          call RvSipTransportGetNumOfIPv4LocalAddresses. If for example this
 *          function returns 5 then you can call
 *          SipTransportGetIPv4LocalAddressByIndex with indexes going from
 *          0 to 4.
 *          Note: The IPv4 address requires 4-BYTEs of memory. This is the
 *          same as an unsigned int (RvUint32). This function requires
 *          pLocalAddr to be a pointer to a 4-BYTE allocated memory.
 *          It can also be a pointer to RvUint32 with an appropriate casting.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:
 *          pTransportMgr    - A pointer to the transport manager
 *          index - The index for the local address to retrieve
 *          pLocalAddr - A pointer to a 4-BYTE memory space to be filled
 *                        with the selected local address.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportGetIPv4LocalAddressByIndex(
                                     IN   RvSipTransportMgrHandle    hTransportMgr,
                                     IN   RvUint                   index,
                                     OUT  RvUint8                  *pLocalAddr);

/***************************************************************************
 * RvSipTransportGetIPv6LocalAddress
 * ------------------------------------------------------------------------
 * General: Retrieves the local address that was actually open for listening
 *          when the stack was initiated with local address 0:0:0:0:0:0:0:0.
 *          Note: The IPv6 address requires 16-BYTEs of memory. This function
 *          requires pLocalAddr to be a pointer to a 16-BYTE allocated memory.
 * Return Value: RvStatus
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:
 *          pTransportMgr    - A pointer to the transport manager
 *          pLocalAddr  - A pointer to a 16-BYTE memory space to be filled
 *                        with the selected local address.
 *
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportGetIPv6LocalAddress(
                                     IN   RvSipTransportMgrHandle    hTransportMgr,
                                     OUT  RvUint8                  *pLocalAddr);

/******************************************************************************
 * RvSipTransportMgrLocalAddressAdd
 * ------------------------------------------------------------------------
 * General: add new local address,on which Stack will receive and send messages
 *
 * Return Value: RvStatus.
 *               RV_OK on success, error code on failure.
 *               See possible error codes in RV_SIP_DEF.h
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hTransportMgr   - handle of the Transport Manager.
 *          pAddressDetails - pointer to the memory, where the details of
 *                            the address to be added are stored.
 *          addrStructSize  - size of the structure with details.
 *          eLocationInList - indication, where the new address should be placed
 *                            in the list of local addresses.
 *          hBaseLocalAddr  - An existing address in the list, before or after
 *                            which the new addresses can be added.
 *                            The parameter is meaningless, if eLocationInList
 *                            is not set to RVSIP_PREV_ELEMENT or
 *                            RVSIP_NEXT_ELEMENT.
 * Output : phLocalAddr     - pointer to the memory, where the handle of the added
 *                            address will be stored by the function.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportMgrLocalAddressAdd(
                        IN  RvSipTransportMgrHandle hTransportMgr,
                        IN  RvSipTransportAddr      *pAddressDetails,
                        IN  RvUint32                addrStructSize,
                        IN  RvSipListLocation       eLocationInList,
                        IN  RvSipTransportLocalAddrHandle hBaseLocalAddr,
                        OUT RvSipTransportLocalAddrHandle *phLocalAddr);

/******************************************************************************
 * RvSipTransportMgrLocalAddressRemove
 * ------------------------------------------------------------------------
 * General: remove the local address,on which Stack receives and sends messages
 *          The socket will be closed immediately.
 *          Reliable connections, created to / from the address will be not
 *          closed.
 *
 * Return Value: RvStatus.
 *               RV_OK on success, error code on failure.
 *               See possible error codes in RV_SIP_DEF.h
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hTransportMgr   - handle to the Transport Manager
 *          hLocalAddr      - handle to the address to be removed
 * Output : none
*****************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportMgrLocalAddressRemove(
                            IN  RvSipTransportMgrHandle         hTransportMgr,
                            IN  RvSipTransportLocalAddrHandle   hLocalAddr);

/******************************************************************************
 * RvSipTransportMgrLocalAddressFind
 * ------------------------------------------------------------------------
 * General: Finds the local address in the SIP  Stack that matches the details
 *          supplied by pAddressDetails.
 *
 * Return Value: RvStatus.
 *               RV_OK on success, error code on failure.
 *               See possible error codes in RV_SIP_DEF.h
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hTransportMgr   - handle of the Transport Manager.
 *          pAddressDetails - pointer to the memory, where the details of
 *                            the address to be added are stored.
 *          addrStructSize  - size of the structure with details.
 * Output : phLocalAddr     - pointer to the memory, where the handle of
 *                            the found address will be stored by the function.
 *                            NULL will be stored, if no matching address
 *                            was found.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportMgrLocalAddressFind(
                        IN  RvSipTransportMgrHandle         hTransportMgr,
                        IN  RvSipTransportAddr              *pAddressDetails,
                        IN  RvUint32                        addrStructSize,
                        OUT RvSipTransportLocalAddrHandle   *phLocalAddr);

/******************************************************************************
 * RvSipTransportMgrLocalAddressGetDetails
 * ------------------------------------------------------------------------
 * General: Returns the details of the local address, the handle of which
 *          is supplied to the function as a parameter.
 *
 * Return Value: RvStatus.
 *               RV_OK on success, error code on failure.
 *               See possible error codes in RV_SIP_DEF.h
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hLocalAddr      - handle of the Local Address.
 *          addrStructSize  - size of the structure with details.
 * Output : pAddressDetails - pointer to the memory, where the details of
 *                            the address to be added are stored.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportMgrLocalAddressGetDetails(
                        IN  RvSipTransportLocalAddrHandle   hLocalAddr,
                        IN  RvUint32                        addrStructSize,
                        OUT RvSipTransportAddr              *pAddressDetails);

/******************************************************************************
 * RvSipTransportMgrLocalAddressGetFirst
 * ------------------------------------------------------------------------
 * General: gets handle of the Local Address, which is located at the head
 *          of the List of Local Addresses of the requested Transport Protocol
 *          type.
 *
 * Return Value: RvStatus.
 *               RV_OK on success, error code on failure.
 *               See possible error codes in RV_SIP_DEF.h
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hTransportMgr   - handle of the Transport Manager.
 *          eTransportType  - type of the Transport Protocol.
 * Output : phLocalAddr     - pointer to the memory, where the handle of
 *                            the found address will be stored by the function.
 *                            NULL will be stored, if no matching address
 *                            was found.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportMgrLocalAddressGetFirst(
                        IN  RvSipTransportMgrHandle         hTransportMgr,
                        IN  RvSipTransport                  eTransportType,
                        OUT RvSipTransportLocalAddrHandle   *phLocalAddr);

/******************************************************************************
 * RvSipTransportMgrLocalAddressGetNext
 * ------------------------------------------------------------------------
 * General: Gets the handle of the local address that is located in the list of
 *          local addresses next to the address whose handle is supplied
 *          as a parameter to the function.
 *
 * Return Value: RvStatus.
 *               RV_OK on success, error code on failure.
 *               See possible error codes in RV_SIP_DEF.h
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hBaseLocalAddr  - The handle to the local address that is located
 *                            before the requested address.
 * Output : phLocalAddr     - pointer to the memory, where the handle of
 *                            the found address will be stored by the function.
 *                            NULL will be stored, if no matching address
 *                            was found.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportMgrLocalAddressGetNext(
                        IN  RvSipTransportLocalAddrHandle   hBaseLocalAddr,
                        OUT RvSipTransportLocalAddrHandle   *phLocalAddr);

/******************************************************************************
 * RvSipTransportMgrLocalAddressSetIpTosSockOption
 * ------------------------------------------------------------------------
 * General: Sets the IP_TOS socket option when the value is in decimal form.
 *          Note that the option does not provide QoS functionality
 *          in operation systems that support a more powerful DSCP mechanism
 *          in place of the previous TOS byte mechanism.
 *          The function can be called any time during the address life cycle.
 *
 * Return Value: RvStatus.
 *               RV_OK on success, error code on failure.
 *               See possible error codes in RV_SIP_DEF.h, rverror.h
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hLocalAddr      - handle to the local address to be updated.
 *          typeOfService   - number, to be set as a TOS byte value.
 * Output : none.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportMgrLocalAddressSetIpTosSockOption(
                            IN RvSipTransportLocalAddrHandle   hLocalAddr,
                            IN RvInt32                         typeOfService);

/******************************************************************************
 * RvSipTransportMgrLocalAddressGetIpTosSockOption
 * ------------------------------------------------------------------------
 * General: Gets the value of the IP_TOS option that is set for the socket,
 *          which serves the specified local address.
 *
 * Return Value: RvStatus.
 *               RV_OK on success, error code on failure.
 *               See possible error codes in RV_SIP_DEF.h, rverror.h
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hLocalAddr      - handle to the local address to be updated.
 * Output : pTypeOfService  - pointer to the memory, where the option value
 *                            will be stored
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportMgrLocalAddressGetIpTosSockOption(
                            IN RvSipTransportLocalAddrHandle   hLocalAddr,
                            IN RvInt32                         *pTypeOfService);

/******************************************************************************
 * RvSipTransportConnectionSetIpTosSockOption
 * ------------------------------------------------------------------------
 * General: Sets the IP_TOS socket option for the socket serving the connection
 *          The option value is in decimal form.
 *          Note that the option does not provide QoS functionality
 *          in operation systems that support a more powerful DSCP mechanism
 *          in place of the previous TOS byte mechanism.
 *          The function can be called any time during the address life cycle.
 *
 * Return Value: RV_OK on success, error code otherwise (see RV_SIP_DEF.h)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:  hConn         - handle to the connection to be updated.
 *         typeOfService - number to be set as a TOS byte value.
 * Output: none.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportConnectionSetIpTosSockOption(
                            IN  RvSipTransportConnectionHandle  hConn,
                            IN  RvInt32                         typeOfService);


/******************************************************************************
 * RvSipTransportConnectionGetIpTosSockOption
 * ------------------------------------------------------------------------
 * General: Gets the value of the IP_TOS option that is set for the socket,
 *          which serves the specified connection.
 *
 * Return Value: RV_OK on success, error code otherwise
 *               (see RV_SIP_DEF.h, rverror.h)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:  hConn           - handle to the connection to be updated.
 * Output: pTypeOfService  - pointer to the memory, where the option value
 *                           will be stored
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportConnectionGetIpTosSockOption(
                            IN  RvSipTransportConnectionHandle  hConn,
                            IN  RvInt32                         *pTypeOfService);

#ifdef __cplusplus
}
#endif


#endif /* END OF: #ifndef RVSIP_TRANSPORT_H */



