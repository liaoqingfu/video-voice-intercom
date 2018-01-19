/*

NOTICE:
This document contains information that is proprietary to RADVision LTD..
No part of this publication may be reproduced in any form whatsoever without
written prior approval by RADVision LTD..

RADVision LTD. reserves the right to revise this publication and make changes
without obligation to notify any person of such revisions or changes.

*/

/******************************************************************************
 *                          RvSipBodyPart.h                                   *
 *                                                                            *
 * The file defines the methods of the body part object:                      *
 * construct, destruct, copy, encode, parse and the ability to access         *
 * and change it's body and headers.                                          *
 *                                                                            *
 *      Author           Date                                                 *
 *     ------           ------------                                          *
 *     Tamar Barzuza    Aug 2001                                              *
 ******************************************************************************/

#ifndef RVSIPBODYPART_H
#define RVSIPBODYPART_H

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                           */
/*-----------------------------------------------------------------------*/
#include "RV_SIP_DEF.h"
#ifndef RV_SIP_PRIMITIVES

#include "RvSipMsgTypes.h"
#include "rpool_API.h"


/*-----------------------------------------------------------------------*/
/*                   CONSTRUCTORS AND DESTRUCTORS                        */
/*-----------------------------------------------------------------------*/

/***************************************************************************
 * RvSipBodyPartConstructInBody
 * ------------------------------------------------------------------------
 * General: Constructs a Body-Part object inside a given Body object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hBody              - Handle to the Body object
 *         pushBodyPartAtHead - Boolean value indicating whether the body
 *                              part should be pushed to the head of the
 *                              list—RV_TRUE—or to the tail—RV_FALSE.
 * output: hBodyPart - Handle to the new Body-Part object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipBodyPartConstructInBody(
                               IN  RvSipBodyHandle       hBody,
                               IN  RvBool               pushBodyPartAtHead,
                               OUT RvSipBodyPartHandle  *hBodyPart);

/***************************************************************************
 * RvSipBodyPartConstruct
 * ------------------------------------------------------------------------
 * General: Constructs and initializes a stand-alone Body-Part
 *          object. The Body-Part object is constructed on a given page
 *          taken from a specified pool. The handle to the new Body-Part
 *          object is returned.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hMsgMgr  - Handle to the message manager.
 *         hPool    - Handle to the memory pool that the object will use.
 *         hPage    - Handle to the memory page that the object will use.
 * output: hBody    - Handle to the newly constructed Body-Part object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipBodyPartConstruct(
                                    IN  RvSipMsgMgrHandle       hMsgMgr,
                                    IN  HRPOOL                  hPool,
                                    IN  HPAGE                   hPage,
                                    OUT RvSipBodyPartHandle    *hBodyPart);

/***************************************************************************
 * RvSipBodyPartCopy
 * ------------------------------------------------------------------------
 * General: Copies all fields from a source Body-Part object to a
 *          destination Body-Part object.
 *          You must construct the destination object before using this
 *          function.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hDestination - Handle to the destination Body-Part object.
 *    hSource      - Handle to the source Body-Part object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipBodyPartCopy(
                                  INOUT  RvSipBodyPartHandle hDestination,
                                  IN     RvSipBodyPartHandle hSource);

/***************************************************************************
 * RvSipBodyPartEncode
 * ------------------------------------------------------------------------
 * General: Encodes a Body-Part object to a textual Body-Part.
 *          The headers of the Body-Part are encoded, the
 *          body of the body part is encoded according to the definition of
 *          RvSipBodyEncode(), and they are concatinated seperated by CRLF.
 *          The textual Body-Part is placed on a page taken from a specified
 *          pool. In order to copy the textual Body-Part from the
 *          page to a consecutive buffer, use RPOOL_CopyToExternal().
 *          The application must free the allocated page, using
 *          RPOOL_FreePage(). The Allocated page must be freed only if this
 *          function returns RV_OK.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:
 *         hBodyPart    - Handle to the Body-Part object.
 *         hPool        - Handle to the specified memory pool.
 * Output:
 *         hPage        - The memory page allocated to contain the encoded
 *                        object.
 *         length       - The length of the encoded information.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipBodyPartEncode(
                                  IN    RvSipBodyPartHandle      hBodyPart,
                                  IN    HRPOOL                   hPool,
                                  OUT   HPAGE*                   hPage,
                                  OUT   RvUint32*               length);

/***************************************************************************
 * RvSipBodyPartParse
 * ------------------------------------------------------------------------
 * General:Parses a SIP textual Body-Part into a Body-Part object.
 *         An example of a textual Body-Part is:
 *         “Content-Type: application/SDP; charset=ISO-10646
 *
 *          v=0
 *          o=audet 2890844526 2890842807 5 IN IP4 134.177.64.4
 *          s=SDP seminar
 *          c=IN IP4 MG141.nortelnetworks.com
 *          t= 2873397496 2873404696
 *          m=audio 9092 RTP/AVP 0 3 4”
 *         The headers are parsed and set to the Body-Part object.
 *         The body is identified and set as a string to the body part
 *         object.
 *         If the body is of type multipart, you can parse it using
 *         RvSipBodyMultipartParse() using the following instructions:
 *         1. Get the body object from the Body-Part object using
 *         RvSipBodyPartGetBodyObject().
 *         2. Get the body string from the body object using
 *         RvSipBodyGetBodyStr().
 *         3. Parse the body string you received in 2 to the body object
 *         you received in 1, using RvSipBodyMultipartParse().
 *
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *  Input:
 *        hBodyPart       - A handle to the Body-Part object.
 *        strBodyPart     - A buffer containning the Body-Part string.
 *        length          - The length of the buffer.
 *
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipBodyPartParse(
                               IN      RvSipBodyPartHandle       hBodyPart,
                               IN      RvChar                   *strBodyPart,
                               IN      RvUint                    length);

/*-----------------------------------------------------------------------
                         G E T  A N D  S E T  M E T H O D S
 ------------------------------------------------------------------------*/

/***************************************************************************
 * RvSipBodyPartGetContentDisposition
 * ------------------------------------------------------------------------
 * General: Get the Content-Disposition header from the Body-Part object.
 * Return Value: Returns the Content-Disposition header handle, or NULL if
 *               there is no Content-Disposition set for this Body-Part.
 * ------------------------------------------------------------------------
 * Arguments:
 *  Input:
 *        hBodyPart - Handle to the message Body-Part object.
 ***************************************************************************/
RVAPI RvSipContentDispositionHeaderHandle RVCALLCONV
                                RvSipBodyPartGetContentDisposition(
                                            IN RvSipBodyPartHandle hBodyPart);

/***************************************************************************
 * RvSipBodyPartSetContentDisposition
 * ------------------------------------------------------------------------
 * General:Set Content-Disposition header to the Body-Part object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *  Input:
 *        hBodyPart     - Handle to the Body-Part object.
 *        hContentDisp  - Content-Disposition header to be set in the
 *                      Body-Part object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipBodyPartSetContentDisposition(
                        IN  RvSipBodyPartHandle                 hBodyPart,
                        IN  RvSipContentDispositionHeaderHandle hContentDisp);

/***************************************************************************
 * RvSipBodyPartGetBodyObject
 * ------------------------------------------------------------------------
 * General: Get the body of the Body-Part object.
 * Return Value: Returns the body handle, or NULL if the body is not set.
 * ------------------------------------------------------------------------
 * Arguments:
 *  Input:
 *        hBodyPart - Handle to the Body-Part object.
 ***************************************************************************/
RVAPI RvSipBodyHandle RVCALLCONV RvSipBodyPartGetBodyObject(
                                           IN RvSipBodyPartHandle hBodyPart);

/***************************************************************************
 * RvSipBodyPartSetBodyObject
 * ------------------------------------------------------------------------
 * General:Set the body of the Body-Part object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hBodyPart    - Handle to the Body-Part object.
 *    hBody        - Body object to be set to the Body-Part object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipBodyPartSetBodyObject(
                                      IN  RvSipBodyPartHandle    hBodyPart,
                                      IN  RvSipBodyHandle        hBody);

/***************************************************************************
 * RvSipBodyPartGetHeader
 * ------------------------------------------------------------------------
 * General: Gets a header from the headers list. The Body-Part object
 *          holds all headers other than Content-Disposition and
 *          Content-Type in a sequential list. All the headers in the list
 *          are other-headers (represented by RvSipOtherHeaderHandle).
 *          Use the location parameter to define the location of the header
 *          you request, and the relative parameter to supply a valid
 *          relative header when you request a next or previous location.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *  Input:
 *        hBodyPart    - Handle of the Body-Part object.
 *        location     - The location in list — next, previous, first or last.
 *        hRelative    - Handle to the current position in the list (a relative
 *                       header from the list). Supply this value if you choose
 *                       next or previous in the location parameter.
 *  Output:
 *        hHeader      - Handle to the requested header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipBodyPartGetHeader(
                                 IN  RvSipBodyPartHandle        hBodyPart,
                                 IN  RvSipHeadersLocation       location,
                                 IN  RvSipOtherHeaderHandle     hRelative,
                                 OUT RvSipOtherHeaderHandle    *hHeader);

/***************************************************************************
 * RvSipBodyPartPushHeader
 * ------------------------------------------------------------------------
 * General: Inserts a given header into the header list based on a given
 *          location - first, last, before or after a given relative
 *          element. The Body-Part object holds all headers other than
 *          Content-Disposition and Content-Type in a sequential list. All
 *          the headers in the list are other-headers (represented by
 *          RvSipOtherHeaderHandle).
 *          The header you supply is copied before it is inserted into the list.
 *          The function returns the handle to the header object that was
 *          actually inserted to the list, which can be used in following
 *          calls to this function as the relative header.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hBodyPart    - Handle of the Body-Part object.
 *          location     - The location in list — next, previous, first or
 *                         last.
 *          hHeader      - Handle to the header to be pushed into the list.
 *          hRelative    - Handle to the current position in the list (a
 *                         relative header from the list). Supply this
 *                         value if you choose next or previous in the
 *                         location parameter.
 *  Output:
 *          hNewHeader   - Handle to a copy of hHeader that was inserted
 *                         to the headers list. Can be used in further
 *                         calls for this function as hRelative.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipBodyPartPushHeader(
                              IN   RvSipBodyPartHandle          hBodyPart,
                              IN   RvSipHeadersLocation         location,
                              IN   RvSipOtherHeaderHandle       hHeader,
                              IN   RvSipOtherHeaderHandle       hRelative,
                              OUT  RvSipOtherHeaderHandle      *hNewHeader);

/***************************************************************************
 * RvSipBodyPartRemoveHeader
 * ------------------------------------------------------------------------
 * General: Removes a header from the headers list. You should supply this
 *          function the handle to the header you wish to remove.
 * Return Value: returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hBodyPart  - Handle to the Body-Part object.
 *         hHeader    - Handle to the header to be removed.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipBodyPartRemoveHeader(
                                     IN  RvSipBodyPartHandle    hBodyPart,
                                     IN  RvSipOtherHeaderHandle hHeader);

#endif /*RV_SIP_PRIMITIVES*/

#ifdef __cplusplus
}
#endif
#endif /* RVSIPBODYPART_H */
