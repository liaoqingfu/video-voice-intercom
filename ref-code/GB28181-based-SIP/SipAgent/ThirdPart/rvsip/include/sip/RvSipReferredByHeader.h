/*

NOTICE:
This document contains information that is proprietary to RADVision LTD..
No part of this publication may be reproduced in any form whatsoever without
written prior approval by RADVision LTD..

RADVision LTD. reserves the right to revise this publication and make changes
without obligation to notify any person of such revisions or changes.

*/

/******************************************************************************
 *                     RvSipReferredByHeader.h                               *
 *                                                                            *
 * The file defines the methods of the Referred-By header object              *
 * construct, destruct, copy, encode, parse and the ability to access and     *
 * change it's parameters.                                                    *
 *                                                                            *
 *                                                                            *
 *      Author           Date                                                 *
 *     ------           ------------                                          *
 *     Tamar Barzuza    Apr.2001                                              *
 ******************************************************************************/


#ifndef RVSIPREFERREDBYHEADER_H
#define RVSIPREFERREDBYHEADER_H

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
/*                   DECLERATIONS                                        */
/*-----------------------------------------------------------------------*/
/*
 * RvSipReferredByHeaderStringName
 * ----------------------
 * This enum defines all the header's strings (for getting it's size)
 * Defines all Referred-By header object fields that are kept in the
 * object in string format.
 */
typedef enum
{
    RVSIP_REFERRED_BY_DISP_NAME,
    RVSIP_REFERRED_BY_OTHER_PARAMS,
    RVSIP_REFERRED_BY_CID_PARAM, 
    RVSIP_REFERRED_BY_BAD_SYNTAX
}RvSipReferredByHeaderStringName;


/****************************************************/
/*        CONSTRUCTORS AND DESTRUCTORS                */
/****************************************************/

/***************************************************************************
 * RvSipReferredByHeaderConstructInMsg
 * ------------------------------------------------------------------------
 * General: Constructs a Referred-By header object inside a given message object.
 *          The header is kept in the header list of the message.
 *          You can choose to insert the header either at the head or tail of
 *          the list.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hSipMsg          - Handle to the message object.
 *         pushHeaderAtHead - Boolean value indicating whether the header should be pushed to the head of the
 *                            list—RV_TRUE—or to the tail—RV_FALSE.
 * output: hHeader          - Handle to the newly constructed Referred-By header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipReferredByHeaderConstructInMsg(
                                       IN  RvSipMsgHandle               hSipMsg,
                                       IN  RvBool                      pushHeaderAtHead,
                                       OUT RvSipReferredByHeaderHandle* hHeader);

/***************************************************************************
 * RvSipReferredByHeaderConstruct
 * ------------------------------------------------------------------------
 * General: Constructs and initializes a stand-alone Referred-By Header object.
 *          The header is constructed on a given page taken from a specified
 *          pool. The handle to the new header object is returned.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hMsgMgr - Handle to the Message manager.
 *         hPool   - Handle to the memory pool that the object will use.
 *         hPage   - Handle to the memory page that the object will use.
 * output: hHeader - Handle to the newly constructed Referred-By header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipReferredByHeaderConstruct(
                                        IN  RvSipMsgMgrHandle            hMsgMgr,
                                        IN  HRPOOL                       hPool,
                                        IN  HPAGE                        hPage,
                                        OUT RvSipReferredByHeaderHandle* hHeader);

/***************************************************************************
 * RvSipReferredByHeaderCopy
 * ------------------------------------------------------------------------
 * General: Copies all fields from a source Referred-By header object to a
 *          destination Referred-By header object.
 *          You must construct the destination object before using this function.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hDestination - Handle to the destination Referred-By header object.
 *    hSource      - Handle to the source Referred-By header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipReferredByHeaderCopy(
                                     INOUT RvSipReferredByHeaderHandle hDestination,
                                     IN    RvSipReferredByHeaderHandle hSource);

/***************************************************************************
 * RvSipReferredByHeaderSetCompactForm
 * ------------------------------------------------------------------------
 * General: Instructs the header to use the compact header name when the
 *          header is encoded.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader  - Handle to the ReferredBy header object.
 *        bIsCompact - specify whether or not to use a compact form
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipReferredByHeaderSetCompactForm(
                                   IN    RvSipReferredByHeaderHandle hHeader,
                                   IN    RvBool                bIsCompact);

/***************************************************************************
 * RvSipReferredByHeaderEncode
 * ------------------------------------------------------------------------
 * General: Encodes a Referred-By header object to a textual Referred-By header.
 *          The textual header is placed on a page taken from a specified pool.
 *          In order to copy the textual header
 *          from the page to a consecutive buffer, use RPOOL_CopyToExternal().
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader  - Handle to the Referred-By header object.
 *        hPool    - Handle to the specified memory pool.
 * output: hPage   - The memory page allocated to contain the encoded header.
 *         length  - The length of the encoded information.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipReferredByHeaderEncode(
                                       IN    RvSipReferredByHeaderHandle hHeader,
                                       IN    HRPOOL                      hPool,
                                       OUT   HPAGE*                      hPage,
                                       OUT   RvUint32*                  length);

/***************************************************************************
 * RvSipReferredByHeaderParse
 * ------------------------------------------------------------------------
 * General:Parses a SIP textual Referred-By header—for example, “Referred-by:
 *         <sip:charlie@caller.com>;ref=<sip:me@com>”—into a Referred-By
 *         header object. All the textual fields are placed inside the object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader   - A handle to the Referred-By header object.
 *    buffer    - Buffer containing a textual ReferredBy header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipReferredByHeaderParse(
                                     IN    RvSipReferredByHeaderHandle hHeader,
                                     IN    RvChar*                    buffer);

/***************************************************************************
 * RvSipReferredByHeaderParseValue
 * ------------------------------------------------------------------------
 * General: Parses a SIP textual ReferredBy header value into an ReferredBy
 *          header object.
 *          A SIP header has the following grammer:
 *          header-name:header-value. This function takes the header-value part as
 *          a parameter and parses it into the supplied object.
 *          All the textual fields are placed inside the object.
 *          Note: Use the RvSipReferredByHeaderParse() function to parse
 *          strings that also include the header-name.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader   - The handle to the ReferredBy header object.
 *    buffer    - The buffer containing a textual ReferredBy header value.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipReferredByHeaderParseValue(
                                     IN    RvSipReferredByHeaderHandle hHeader,
                                     IN    RvChar*                    buffer);

/***************************************************************************
 * RvSipReferredByHeaderFix
 * ------------------------------------------------------------------------
 * General: Fixes an ReferredBy header with bad-syntax information.
 *          A SIP header has the following grammer:
 *          header-name:header-value. When a header contains a syntax error,
 *          the header-value is kept as a separate "bad-syntax" string.
 *          Use this function to fix the header. This function parses a given
 *          correct header-value string to the supplied header object.
 *          If parsing succeeds, this function places all fields inside the
 *          object and removes the bad syntax string.
 *          If parsing fails, the bad-syntax string in the header remains as it was.
 * Return Value: RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input: hHeader      - The handle to the header object.
 *        pFixedBuffer - The buffer containing a legal header value.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipReferredByHeaderFix(
                                     IN RvSipReferredByHeaderHandle hHeader,
                                     IN RvChar*                    pFixedBuffer);

/***************************************************************************
 * RvSipReferredByHeaderGetStringLength
 * ------------------------------------------------------------------------
 * General: Some of the Referred-By header fields are kept in a string
 *          format—for example, the referrer display name. In order to get
 *          such a field from the Referred-By header object, your application
 *          should supply an adequate buffer to where the string
 *          will be copied.
 *          This function provides you with the length of the string to enable
 *          you to allocate an appropriate buffer size before calling the Get
 *          function.
 * Return Value: Returns the length of the specified string.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader    - Handle to the Referred-By header object.
 *  stringName - Enumeration of the string name for which you require the length.
 ***************************************************************************/
RVAPI RvUint RVCALLCONV RvSipReferredByHeaderGetStringLength(
                                 IN  RvSipReferredByHeaderHandle     hHeader,
                                 IN  RvSipReferredByHeaderStringName stringName);

/***************************************************************************
 * RvSipReferredByHeaderGetDispName
 * ------------------------------------------------------------------------
 * General: Copies the referrer display name parameter of the Referred-By
 *          header object into a given buffer. If the bufferLen is adequate,
 *          the function copies the requested parameter into strBuffer.
 *          Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and actualLen
 *          contains the required buffer length.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader    - Handle to the header object.
 *        strBuffer  - Buffer to include the requested parameter.
 *        bufferLen  - The length of the buffer.
 * output:actualLen - The length of the requested parameter, + 1 to include a NULL value at the end
 *                     of the parameter.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipReferredByHeaderGetDispName(
                                      IN RvSipReferredByHeaderHandle  hHeader,
                                      IN RvChar*                     strBuffer,
                                      IN RvUint                      bufferLen,
                                      OUT RvUint*                    actualLen);

/***************************************************************************
 * RvSipReferredByHeaderSetDispName
 * ------------------------------------------------------------------------
 * General: Sets the referred display name field in the Referred-By header
 *          object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader - Handle to the Referred-By header object.
 *    strDispName  - The display name field to be set in the Referred-By header
 *                 object. If NULL is supplied, the existing display name is
 *                 removed from the header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipReferredByHeaderSetDispName(
                                    IN RvSipReferredByHeaderHandle hHeader,
                                    IN RvChar *                   strDispName);

/***************************************************************************
 * RvSipReferredByHeaderGetAddrSpec
 * ------------------------------------------------------------------------
 * General: Returns the referrer-url address spec.
 * Return Value: Returns a handle to the Address Spec object, or NULL
 *               if this Address Spec object does not exist.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader - Handle to the Referred-By header object.
 ***************************************************************************/
RVAPI RvSipAddressHandle RVCALLCONV RvSipReferredByHeaderGetAddrSpec(
                                    IN RvSipReferredByHeaderHandle hHeader);

/***************************************************************************
 * RvSipReferredByHeaderSetAddrSpec
 * ------------------------------------------------------------------------
 * General: Sets the referrer-url address spec in the Referred-By header
 *          object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader   - Handle to the Referred-by header object.
 *  hAddrSpec - Handle to the Address Spec address object to be set in the
 *              Referred-By header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipReferredByHeaderSetAddrSpec(
                                    IN RvSipReferredByHeaderHandle hHeader,
                                    IN RvSipAddressHandle          hAddrSpec);

/***************************************************************************
 * RvSipReferredByHeaderGetCidParam
 * ------------------------------------------------------------------------
 * General: Copies the referrer cid parameter of the Referred-By
 *          header object into a given buffer. If the bufferLen is adequate,
 *          the function copies the requested parameter into strBuffer.
 *          Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and actualLen
 *          contains the required buffer length.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader    - Handle to the header object.
 *        strBuffer  - Buffer to include the requested parameter.
 *        bufferLen  - The length of the buffer.
 * output:actualLen  - The length of the requested parameter, + 1 to include
 *                     a NULL value at the end of the parameter.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipReferredByHeaderGetCidParam(
                                        IN RvSipReferredByHeaderHandle  hHeader,
                                        IN RvChar*                     strBuffer,
                                        IN RvUint                      bufferLen,
                                        OUT RvUint*                    actualLen);


/***************************************************************************
 * RvSipReferredByHeaderSetCidParam
 * ------------------------------------------------------------------------
 * General: Sets the cid parameter in the Referred-By header
 *          object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader      - Handle to the Referred-By header object.
 *    strCidParam  - The cid parameter to be set in the Referred-By header
 *                 object. If NULL is supplied, the existing cid param is
 *                 removed from the header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipReferredByHeaderSetCidParam(
                                    IN RvSipReferredByHeaderHandle hHeader,
                                    IN RvChar *                   strCidParam);

/***************************************************************************
 * RvSipReferredByHeaderGetOtherParams
 * ------------------------------------------------------------------------
 * General: Copies the Referred-By header other params field of the
 *          Referred-By header object into a given buffer.
 *          Not all the Referred-By header parameters have separated fields
 *          in the Referred-By header object.
 *          Parameters with no specific fields are refered to as other params.
 *          They are kept in the object in one concatenated string in the form—
 *          ”name=value;name=value...”. This list includes also the signature
 *          parameters.
 *          If the bufferLen is adequate, the function copies the requested
 *          parameter into strBuffer. Otherwise, the function returns
 *          RV_ERROR_INSUFFICIENT_BUFFER and actualLen contains the required buffer
 *          length.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader    - Handle to the Referred-By header object.
 *        strBuffer  - Buffer to fill with the requested parameter.
 *        bufferLen  - The length of the buffer.
 * output:actualLen - The length of the requested parameter, + 1 to include a NULL value at the end of
 *                     the parameter.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipReferredByHeaderGetOtherParams(
                                    IN  RvSipReferredByHeaderHandle   hHeader,
                                    IN  RvChar*                      strBuffer,
                                    IN  RvUint                       bufferLen,
                                    OUT RvUint*                      actualLen);

/***************************************************************************
 * RvSipReferredByHeaderSetOtherParams
 * ------------------------------------------------------------------------
 * General: Sets the other params field in the Referred-By header object.
 *          Not all the Referred-By header parameters have separated fields
 *          in the Referred-By header object. Parameters with no specific
 *          fields are refered to as other params. They are kept in the
 *          object in one concatenated string in the form— ”name=value;
 *          name=value...”. This list includes also the signature parameters.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader        - Handle to the Referred-By header object.
 *    strOtherParams - The other Params string to be set in the Referred-By
 *                   header. If NULL is supplied, the
 *                   existing other params field is removed from the header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipReferredByHeaderSetOtherParams(
                              IN RvSipReferredByHeaderHandle hHeader,
                              IN RvChar *                   strOtherParams);

/***************************************************************************
 * RvSipReferredByHeaderGetStrBadSyntax
 * ------------------------------------------------------------------------
 * General: Copies the bad-syntax string from the header object into a
 *          given buffer.
 *          A SIP header has the following grammer:
 *          header-name:header-value. When a header contains a syntax error,
 *          the header-value is kept as a separate "bad-syntax" string.
 *          You use this function to retrieve the bad-syntax string.
 *          If the value of bufferLen is adequate, this function copies
 *          the requested parameter into strBuffer. Otherwise, the function
 *          returns RV_ERROR_INSUFFICIENT_BUFFER and actualLen contains the required
 *          buffer length.
 *          Use this function in the RvSipTransportBadSyntaxMsgEv() callback
 *          implementation if the message contains a bad ReferredBy header,
 *          and you wish to see the header-value.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader    - The handle to the header object.
 *        strBuffer  - The buffer with which to fill the bad syntax string.
 *        bufferLen  - The length of the buffer.
 * output:actualLen  - The length of the bad syntax + 1, to include
 *                     a NULL value at the end of the parameter.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipReferredByHeaderGetStrBadSyntax(
                                               IN RvSipReferredByHeaderHandle hHeader,
                                               IN RvChar*                 strBuffer,
                                               IN RvUint                  bufferLen,
                                               OUT RvUint*                actualLen);
/***************************************************************************
 * RvSipReferredByHeaderSetStrBadSyntax
 * ------------------------------------------------------------------------
 * General: Sets the bad-syntax string in object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader      - Handle to the header object.
 *  strBadSyntax - The bad-syntax string.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipReferredByHeaderSetStrBadSyntax(
                                  IN RvSipReferredByHeaderHandle hHeader,
                                  IN RvChar*                     strBadSyntax);

#endif /*#ifndef RV_SIP_PRIMITIVES*/

#ifdef __cplusplus
}
#endif

#endif /* RVSIPREFERREDBYHEADER_H */



