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
 *                              <RvSipTranportDNS.h>
 *
 * The transport layer of the RADVISION SIP toolkit allows you to control sending
 * and receiving of messages over the network.
 * This file defines the API for the DNS list in the transport layer.
 *
 *    Author                         Date
 *    ------                        ------
 *    Shiri Margel                 May 2002
 *********************************************************************************/


#ifndef RVSIP_DNS_TRANSPORT_H
#define RVSIP_DNS_TRANSPORT_H

#ifdef __cplusplus
extern "C" {
#endif


#include "RV_SIP_DEF.h"
#include "RvSipCommonTypes.h"
#include "RvSipTransportTypes.h"
#include "RvSipTransportDNSTypes.h"

/***************************************************************************
 * RvSipTransportDNSListGetSrvElement
 * ------------------------------------------------------------------------
 * General: retrieves SRV element from the SRV list of the DNS list object
 * according to specified by input location.
 * Return Value: RV_OK, RV_ERROR_UNKNOWN, RV_ERROR_INVALID_HANDLE or RV_ERROR_BADPARAM
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTransportMgr    - Handle to the transport manager
 *          hDnsList        - Handle of the DNS list object
 *          location        - starting element location
 *             pRelative        - relative SRV element. Used when location
 *                            is 'next' or 'previous'
 * Output:  pSrvElement     - found element
 *            pRelative        - new relative SRV element for get consequent
 *                            RvSipTransportDNSListGetSrvElement function
 *                            calls.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportDNSListGetSrvElement (
                                           IN     RvSipTransportMgrHandle           hTransportMgr,
                                           IN     RvSipTransportDNSListHandle        hDnsList,
                                           IN     RvSipListLocation                    location,
                                           INOUT  void                                **pRelative,
                                           OUT    RvSipTransportDNSSRVElement        *pSrvElement);

/***************************************************************************
 * RvSipTransportDNSListGetHostElement
 * ------------------------------------------------------------------------
 * General: retrieves host element from the host elements list of the DNS
 * list object according to specified by input location.
 * Return Value: RV_OK or RV_ERROR_BADPARAM
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTransportMgr    - Handle to the transport manager
 *          hDnsList        - Handle of the DNS list object
 *          location        - starting element location
 *            pRelative        - relative host name element for 'next' or 'previous'
 *                            locations
 * Output:  pHostElement    - found element
 *            pRelative        - new relative host name element for consequent
 *            call to the RvSipTransportDNSListGetHostElement function.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportDNSListGetHostElement (
                                           IN  RvSipTransportMgrHandle          hTransportMgr,
                                           IN  RvSipTransportDNSListHandle        hDnsList,
                                           IN  RvSipListLocation                location,
                                           INOUT  void                            **pRelative,
                                           OUT RvSipTransportDNSHostNameElement    *pHostElement);

/***************************************************************************
 * RvSipTransportDNSListRemoveTopmostSrvElement
 * ------------------------------------------------------------------------
 * General: removes topmost SRV element from the SRV elements list of the
 * DNS list object.
 * Return Value: RV_OK or RV_ERROR_BADPARAM
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTransportMgr    - Handle to the transport manager
 *          hDnsList        - Handle of the DNS list object
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportDNSListRemoveTopmostSrvElement(
                                          IN RvSipTransportMgrHandle     hTransportMgr,
                                          IN RvSipTransportDNSListHandle hDnsList);

/***************************************************************************
 * RvSipTransportDNSListRemoveTopmostHostElement
 * ------------------------------------------------------------------------
 * General: removes topmost host element from the head of the host elements
 * list of the DNS list object.
 * Return Value: RV_OK or RV_ERROR_BADPARAM
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTransportMgr    - Handle to the transport manager
 *          hDnsList        - Handle of the DNS list object
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportDNSListRemoveTopmostHostElement(
                                        IN RvSipTransportMgrHandle     hTransportMgr,
                                        IN RvSipTransportDNSListHandle hDnsList);


/***************************************************************************
 * RvSipTransportDNSListPopSrvElement
 * ------------------------------------------------------------------------
 * General: retrieves and removes topmost SRV name element from the SRV
 * elements list of the DNS list object.
 * Return Value: RV_OK or RV_ERROR_BADPARAM
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTransportMgr    - Handle to the transport manager
 *          hDnsList        - Handle of the DNS list object
 * Output:  pSrvElement     - retrieved element
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportDNSListPopSrvElement (
                                  IN  RvSipTransportMgrHandle       hTransportMgr,
                                  IN  RvSipTransportDNSListHandle   hDnsList,
                                  OUT RvSipTransportDNSSRVElement    *pSrvElement);


/***************************************************************************
 * RvSipTransportDNSListPopHostElement
 * ------------------------------------------------------------------------
 * General: retrieves and removes topmost host element from the list of host
 * elements in the DNS list object.
 * Return Value: RV_OK or RV_ERROR_BADPARAM
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTransportMgr    - Handle to the transport manager
 *          hDnsList        - Handle of the DNS list object
 * Output:  pHostElement    - element
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportDNSListPopHostElement (
                                       IN  RvSipTransportMgrHandle          hTransportMgr,
                                       IN  RvSipTransportDNSListHandle        hDnsList,
                                       OUT RvSipTransportDNSHostNameElement    *pHostElement);

/***************************************************************************
 * RvSipTransportDNSListPushSrvElement
 * ------------------------------------------------------------------------
 * General: adds single SRV element to the head of the SRV names list of the
 * DNS list object.
 *
 * Return Value: RV_OK or RV_ERROR_BADPARAM
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTransportMgr    - Handle to the transport manager
 *          hDnsList        - Handle of the DNS list object
 *          pSrvElement        - SRV element structure to be added to the list
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportDNSListPushSrvElement(
                                    IN RvSipTransportMgrHandle      hTransportMgr,
                                    IN RvSipTransportDNSListHandle    hDnsList,
                                    IN RvSipTransportDNSSRVElement    *pSrvElement);

/***************************************************************************
 * RvSipTransportDNSListPushHostElement
 * ------------------------------------------------------------------------
 * General: adds host element to the head of the host elements list of the
 * DNS list object.
 *
 * Return Value: RV_OK or RV_ERROR_BADPARAM
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTransportMgr    - Handle to the transport manager
 *          hDnsList        - Handle of the DNS list object
 *          pHostElement    - host name element structure to be added to the list
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportDNSListPushHostElement(
                                              IN RvSipTransportMgrHandle          hTransportMgr,
                                              IN RvSipTransportDNSListHandle      hDnsList,
                                                IN RvSipTransportDNSHostNameElement *pHostElement);


/***************************************************************************
 * RvSipTransportDNSListGetIPElement
 * ------------------------------------------------------------------------
 * General: retrieves IP address element from the DNS list objects IP
 * addresses list according to specified by input location.
 * Return Value: RV_OK, RV_ERROR_UNKNOWN or RV_ERROR_BADPARAM
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTransportMgr    - Handle to the transport manager
 *          hDnsList        - Handle of the DNS list object
 *          location        - starting element location
 *            pRelative        - relative IP element for get next/previous
 * Output:  pIPElement      - found element
 *            pRelative        - new relative IP element for consequent
 *            call to the RvSipTransportDNSListGetIPElement function.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportDNSListGetIPElement (
                                           IN     RvSipTransportMgrHandle       hTransportMgr,
                                           IN     RvSipTransportDNSListHandle    hDnsList,
                                           IN     RvSipListLocation                 location,
                                           INOUT  void                            **pRelative,
                                           OUT    RvSipTransportDNSIPElement    *pIPElement);

/***************************************************************************
 * RvSipTransportDNSListRemoveTopmostIPElement
 * ------------------------------------------------------------------------
 * General: removes topmost element from the head of the DNS list
 * object IP addresses list.
 * Return Value: RV_OK or RV_ERROR_BADPARAM
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTransportMgr    - Handle to the transport manager
 *          hDnsList        - Handle of the DNS list object
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportDNSListRemoveTopmostIPElement(
                                           IN RvSipTransportMgrHandle     hTransportMgr,
                                           IN RvSipTransportDNSListHandle hDnsList);


/***************************************************************************
 * RvSipTransportDNSListPopIPElement
 * ------------------------------------------------------------------------
 * General: retrieves and removes from the IP addresses list of the DNS
 * list object the topmost IP address element.
 * Return Value: RV_OK or RV_ERROR_BADPARAM
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTransportMgr    - Handle to the transport manager
 *          hDnsList        - handle of the DNS list object
 * Output:  pIpElement      - element
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportDNSListPopIPElement(
                                        IN  RvSipTransportMgrHandle     hTransportMgr,
                                        IN  RvSipTransportDNSListHandle    hDnsList,
                                        OUT RvSipTransportDNSIPElement    *pIPElement);

/***************************************************************************
 * RvSipTransportDNSListPushIPElement
 * ------------------------------------------------------------------------
 * General: adds single IP address element to the head of the IP addresses list of the
 * DNS list object.
 *
 * Return Value: RV_OK or RV_ERROR_BADPARAM
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTransportMgr    - Handle to the transport manager
 *          hDnsList        - Handle of the DNS list object
 *          pIPElement        - IP address element structure to be added to the list
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportDNSListPushIPElement(
                                           IN RvSipTransportMgrHandle           hTransportMgr,
                                           IN RvSipTransportDNSListHandle    hDnsList,
                                           IN RvSipTransportDNSIPElement    *pIPElement);


/***************************************************************************
 * RvSipTransportGetNumberOfDNSListEntries
 * ------------------------------------------------------------------------
 * General: Retrives number of elements in each of the DNS list object lists.
 *
 * Return Value: RV_OK or RV_ERROR_BADPARAM
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hTransportMgr    - Handle to the transport manager
 *          hDnsList            - Handle of the DNS list object
 * Output:  pSrvElements        - number of SRV elements
 *            pHostNameElements    - number of host elements
 *            pIpAddrElements        - number of IP address elements
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportGetNumberOfDNSListEntries(
                                           IN  RvSipTransportMgrHandle      hTransportMgr,
                                           IN  RvSipTransportDNSListHandle    hDnsList,
                                           OUT RvUint32                    *pSrvElements,
                                           OUT RvUint32                    *pHostNameElements,
                                           OUT RvUint32                    *pIpAddrElements);


/***************************************************************************
 * RvSipTransportDNSListGetUsedHostElement
 * ------------------------------------------------------------------------
 * General: retrieves host name element, used to produce the IP list
 *
 * Return Value: RV_OK or RV_ERROR_BADPARAM
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   pTransportMgr   - pointer to the transport manager
 *          pDnsList        - Handle of the DNS list object
 * Output:  pHostElement    - last used host name element
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportDNSListGetUsedHostElement(
    IN  RvSipTransportMgrHandle                pTransportMgr,
    IN  RvSipTransportDNSListHandle            pDnsList,
    OUT RvSipTransportDNSHostNameElement    *pHostElement);

/***************************************************************************
 * RvSipTransportDNSListGetUsedSRVElement
 * ------------------------------------------------------------------------
 * General: retrieves SRV element, used to produce the host name list
 *
 * Return Value: RV_OK or RV_ERROR_BADPARAM
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   pTransportMgr   - pointer to the transport manager
 *          pDnsList        - Handle of the DNS list object
 * Output:  pSRVElement     - last used SRV element
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipTransportDNSListGetUsedSRVElement(
    IN  RvSipTransportMgrHandle                pTransportMgr,
    IN  RvSipTransportDNSListHandle            pDnsList,
    OUT RvSipTransportDNSSRVElement            *pSRVElement);


/***************************************************************************
 * RvSipTransportDNSListSetUsedSRVElement
 * ------------------------------------------------------------------------
 * General: retrieves SRV element, used to produce the IP list
 *
 * Return Value: RV_OK or RV_ERROR_BADPARAM
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hTransportMgr   - handle to the transport manager
 *          hDnsList        - Handle of the DNS list object
 *          pHostElement    - host name element structure to be added to the list
 ***************************************************************************/
 RvStatus RVCALLCONV RvSipTransportDNSListSetUsedSRVElement(
      IN  RvSipTransportMgrHandle   hTransportMgr,
      IN  RvSipTransportDNSListHandle hDnsList,
      IN RvSipTransportDNSSRVElement*    pSRVElement);


/***************************************************************************
 * RvSipTransportDNSListSetUsedHostElement
 * ------------------------------------------------------------------------
 * General: sets host name element, used to produce the IP list
 *
 * Return Value: RV_OK or RV_ERROR_BADPARAM
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hTransportMgr   - handle to the transport manager
 *          hDnsList        - Handle of the DNS list object
 *          pHostElement    - host name element structure to be added to the list
 ***************************************************************************/
 RvStatus RVCALLCONV RvSipTransportDNSListSetUsedHostElement(
      IN  RvSipTransportMgrHandle   hTransportMgr,
      IN  RvSipTransportDNSListHandle hDnsList,
      IN RvSipTransportDNSHostNameElement* pHostElement);

#ifdef __cplusplus
}
#endif


#endif /* END OF: #ifndef RVSIP_DNS_TRANSPORT_H */



