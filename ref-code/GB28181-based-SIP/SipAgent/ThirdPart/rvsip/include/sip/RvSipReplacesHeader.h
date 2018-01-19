
/*

NOTICE:
This document contains information that is proprietary to RADVision LTD..
No part of this publication may be reproduced in any form whatsoever without
written prior approval by RADVision LTD..

RADVision LTD. reserves the right to revise this publication and make changes
without obligation to notify any person of such revisions or changes.

*/

/******************************************************************************
 *                     RvSipReplacesHeader.h                                  *
 *                                                                            *
 * The file defines the methods of the Replaces header object:                *
 * construct, destruct, copy, encode, parse and the ability to access and     *
 * change it's parameters.                                                    *
 *                                                                            *
 *                                                                            *
 *      Author           Date                                                 *
 *     --------         ----------                                            *
 *     Shiri Margel      Jun.2002                                             *
 ******************************************************************************/

#ifndef RVSIPREPLACESHEADER_H
#define RVSIPREPLACESHEADER_H

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
 * RvSipReplacesHeaderStringName
 * ------------------------------
 * This enum defines all the header's strings (for getting it's size)
 * Defines all Replaces header object fields that are kept in the
 * object in string format.
 */
typedef enum
{
    RVSIP_REPLACES_CALL_ID,
    RVSIP_REPLACES_FROM_TAG,
    RVSIP_REPLACES_TO_TAG,
    RVSIP_REPLACES_OTHER_PARAMS,
    RVSIP_REPLACES_BAD_SYNTAX
}RvSipReplacesHeaderStringName;

/****************************************************/
/*        CONSTRUCTORS AND DESTRUCTORS                */
/****************************************************/

/***************************************************************************
 * RvSipReplacesHeaderConstructInMsg
 * ------------------------------------------------------------------------
 * General: Constructs a Replaces header object inside a given message object.
 *          The header is kept in the header list of the message.
 *          You can choose to insert the header either at the head or tail of
 *          the list.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hSipMsg          - Handle to the message object.
 *         pushHeaderAtHead - Boolean value indicating whether the header should be pushed to the head of the
 *                            list—RV_TRUE—or to the tail—RV_FALSE.
 * output: hHeader          - Handle to the newly constructed Replaces header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipReplacesHeaderConstructInMsg(
                                       IN  RvSipMsgHandle            hSipMsg,
                                       IN  RvBool                   pushHeaderAtHead,
                                       OUT RvSipReplacesHeaderHandle* hHeader);

/***************************************************************************
 * RvSipReplacesHeaderConstructInReferToHeader
 * ------------------------------------------------------------------------
 * General: Constructs a Replaces header inside a given Refer-To
 *          header. The address handle is returned.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hHeader   - Handle to the Refer-To header.
 * output: phReplacesHeader  - Handle to the newly constructed Replaces header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipReplacesHeaderConstructInReferToHeader(
                                          IN  RvSipReferToHeaderHandle   hHeader,
                                          OUT RvSipReplacesHeaderHandle *phReplacesHeader);

/***************************************************************************
 * RvSipReplacesHeaderConstruct
 * ------------------------------------------------------------------------
 * General: Constructs and initializes a stand-alone Replaces Header object.
 *          The header is constructed on a given page taken from a specified
 *          pool. The handle to the new header object is returned.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hMsgMgr - Handle to the Message manager.
 *         hPool   - Handle to the memory pool that the object will use.
 *         hPage   - Handle to the memory page that the object will use.
 * output: hHeader - Handle to the newly constructed Replaces header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipReplacesHeaderConstruct(
                                        IN  RvSipMsgMgrHandle         hMsgMgr,
                                        IN  HRPOOL                    hPool,
                                        IN  HPAGE                     hPage,
                                        OUT RvSipReplacesHeaderHandle* hHeader);

/***************************************************************************
 * RvSipReplacesHeaderCopy
 * ------------------------------------------------------------------------
 * General: Copies all fields from a source Replaces header object to a
 *          destination Refer-To header object.
 *          You must construct the destination object before using this function.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hDestination - Handle to the destination Replaces header object.
 *    hSource      - Handle to the source Replaces header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipReplacesHeaderCopy(
                                    INOUT  RvSipReplacesHeaderHandle hDestination,
                                    IN     RvSipReplacesHeaderHandle hSource);

/***************************************************************************
 * RvSipReplacesHeaderEncode
 * ------------------------------------------------------------------------
 * General: Encodes a Replaces header object to a textual Replaces header.
 *          The textual header is placed on a page taken from a specified pool.
 *          In order to copy the textual header
 *          from the page to a consecutive buffer, use RPOOL_CopyToExternal().
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader  - Handle to the Replaces header object.
 *        hPool    - Handle to the specified memory pool.
 * output: hPage   - The memory page allocated to contain the encoded header.
 *         length  - The length of the encoded information.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipReplacesHeaderEncode(
                                        IN    RvSipReplacesHeaderHandle hHeader,
                                        IN    HRPOOL                   hPool,
                                        OUT   HPAGE*                   hPage,
                                        OUT   RvUint32*               length);

/***************************************************************************
 * RvSipReplacesHeaderParse
 * ------------------------------------------------------------------------
 * General:Parses a SIP textual Replaces header—for example,
 *         "Replaces: 123@sshhdd;to-tag=asdf;from-tag=12345”—into a Replaces header
 *           object. All the textual fields are placed inside the object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader   - A handle to the Replaces header object.
 *    buffer    - Buffer containing a textual Replaces header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipReplacesHeaderParse(
                                     IN  RvSipReplacesHeaderHandle  hHeader,
                                     IN  RvChar*                   buffer);

/***************************************************************************
 * RvSipReplacesHeaderParseValue
 * ------------------------------------------------------------------------
 * General: Parses a SIP textual Replaces header value into an Replaces header object.
 *          A SIP header has the following grammer:
 *          header-name:header-value. This function takes the header-value part as
 *          a parameter and parses it into the supplied object.
 *          All the textual fields are placed inside the object.
 *          Note: Use the RvSipReplacesHeaderParse() function to parse strings that also
 *          include the header-name.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader   - The handle to the Replaces header object.
 *    buffer    - The buffer containing a textual Replaces header value.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipReplacesHeaderParseValue(
                                     IN  RvSipReplacesHeaderHandle  hHeader,
                                     IN  RvChar*                   buffer);

/***************************************************************************
 * RvSipReplacesHeaderFix
 * ------------------------------------------------------------------------
 * General: Fixes an Replaces header with bad-syntax information.
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
RVAPI RvStatus RVCALLCONV RvSipReplacesHeaderFix(
                                     IN RvSipReplacesHeaderHandle hHeader,
                                     IN RvChar*                  pFixedBuffer);

/***************************************************************************
 * RvSipReplacesHeaderGetToTag
 * ------------------------------------------------------------------------
 * General: Copies the To Tag parameter of the Replaces header object into a given buffer.
 *          If the bufferLen is adequate, the function copies the requested parameter into
 *          strBuffer. Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and actualLen
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
RVAPI RvStatus RVCALLCONV RvSipReplacesHeaderGetToTag(
                                               IN RvSipReplacesHeaderHandle   hHeader,
                                               IN RvChar*                    strBuffer,
                                               IN RvUint                     bufferLen,
                                               OUT RvUint*                   actualLen);

/***************************************************************************
 * RvSipReplacesHeaderGetFromTag
 * ------------------------------------------------------------------------
 * General: Copies the From Tag parameter of the Replaces header object into a given buffer.
 *          If the bufferLen is adequate, the function copies the requested parameter into
 *          strBuffer. Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and actualLen
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
RVAPI RvStatus RVCALLCONV RvSipReplacesHeaderGetFromTag(
                                               IN RvSipReplacesHeaderHandle   hHeader,
                                               IN RvChar*                    strBuffer,
                                               IN RvUint                     bufferLen,
                                               OUT RvUint*                   actualLen);

/***************************************************************************
 * RvSipReplacesHeaderGetCallID
 * ------------------------------------------------------------------------
 * General: Copies the Call ID parameter of the Replaces header object into a given buffer.
 *          If the bufferLen is adequate, the function copies the requested parameter into
 *          strBuffer. Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and actualLen
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
RVAPI RvStatus RVCALLCONV RvSipReplacesHeaderGetCallID(
                                               IN RvSipReplacesHeaderHandle   hHeader,
                                               IN RvChar*                    strBuffer,
                                               IN RvUint                     bufferLen,
                                               OUT RvUint*                   actualLen);

/***************************************************************************
 * RvSipReplacesHeaderGetOtherParams
 * ------------------------------------------------------------------------
 * General: Copies the other parameters string of the Replaces header object into a given buffer.
 *          If the bufferLen is adequate, the function copies the requested parameter into
 *          strBuffer. Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and actualLen
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
RVAPI RvStatus RVCALLCONV RvSipReplacesHeaderGetOtherParams(
                                    IN RvSipReplacesHeaderHandle      hHeader,
                                    IN RvChar*                       strBuffer,
                                    IN RvUint                        bufferLen,
                                    OUT RvUint*                      actualLen);

/***************************************************************************
 * RvSipReplacesHeaderGetStrBadSyntax
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
 *          implementation if the message contains a bad Replaces header,
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
RVAPI RvStatus RVCALLCONV RvSipReplacesHeaderGetStrBadSyntax(
                                               IN RvSipReplacesHeaderHandle hHeader,
                                               IN RvChar*                 strBuffer,
                                               IN RvUint                  bufferLen,
                                               OUT RvUint*                actualLen);

/***************************************************************************
 * RvSipReplacesHeaderSetStrBadSyntax
 * ------------------------------------------------------------------------
 * General: Sets a bad-syntax string in the object.
 *          A SIP header has the following grammer:
 *          header-name:header-value. When a header contains a syntax error,
 *          the header-value is kept as a separate "bad-syntax" string.
 *          By using this function you can create a header with "bad-syntax".
 *          Setting a bad syntax string to the header will mark the header as
 *          an invalid syntax header.
 *          You can use his function when you want to send an illegal Replaces header.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader      - The handle to the header object.
 *  strBadSyntax - The bad-syntax string.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipReplacesHeaderSetStrBadSyntax(
                                  IN RvSipReplacesHeaderHandle hHeader,
                                  IN RvChar*                     strBadSyntax);

/***************************************************************************
 * RvSipReplacesHeaderSetToTag
 * ------------------------------------------------------------------------
 * General: Sets the To Tag field in the Replaces header object
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader   - Handle to the Replaces header object.
 *    strToTag  - The To Tag field to be set in the Replaces header object. If NULL
 *              is supplied, the existing To Tag is removed from the header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipReplacesHeaderSetToTag(
                                         IN    RvSipReplacesHeaderHandle hHeader,
                                         IN    RvChar *              strToTag);

/***************************************************************************
 * RvSipReplacesHeaderSetFromTag
 * ------------------------------------------------------------------------
 * General: Sets the From Tag field in the Replaces header object
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader   - Handle to the Replaces header object.
 *    strToTag  - The From Tag field to be set in the Replaces header object.  If NULL
 *              is supplied, the existing From Tag is removed from the header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipReplacesHeaderSetFromTag(
                                         IN    RvSipReplacesHeaderHandle hHeader,
                                         IN    RvChar *              strFromTag);

/***************************************************************************
 * RvSipReplacesHeaderSetCallID
 * ------------------------------------------------------------------------
 * General: Sets the Call-ID field in the Replaces header object
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader   - Handle to the Replaces header object.
 *    strToTag  - The Call-ID field to be set in the Replaces header object. If NULL
 *              is supplied, the existing Call-ID is removed from the header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipReplacesHeaderSetCallID(
                                         IN    RvSipReplacesHeaderHandle hHeader,
                                         IN    RvChar *              strCallID);


/***************************************************************************
 * RvSipReplacesHeaderSetOtherParams
 * ------------------------------------------------------------------------
 * General: Sets the other parameters string in the Replaces header object
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader   - Handle to the Replaces header object.
 *    strToTag  - The other parameters string to be set in the Replaces header object. If
 *                NULL is supplied, the existing other parameters string is removed from
 *              the header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipReplacesHeaderSetOtherParams(
                                 IN   RvSipReplacesHeaderHandle  hHeader,
                                 IN   RvChar                    *otherParams);

/***************************************************************************
 * RvSipReplaceHeaderGetStringLength
 * ------------------------------------------------------------------------
 * General: Some of the Replaces header fields are kept in a string format—
 *          for example, the Refer-To header display name. In order to get
 *          such a field from the Refer-To header object, your application
 *          should supply an adequate buffer to where the string
 *          will be copied.
 *          This function provides you with the length of the string to
 *          enable you to allocate an appropriate buffer size before calling
 *          the Get function.
 * Return Value: Returns the length of the specified string.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader    - Handle to the Replaces header object.
 *  stringName - Enumeration of the string name for which you require the
 *               length.
 ***************************************************************************/
RVAPI RvUint RVCALLCONV RvSipReplaceHeaderGetStringLength(
                                IN  RvSipReplacesHeaderHandle     hHeader,
                                IN  RvSipReplacesHeaderStringName stringName);

/***************************************************************************
 * RvSipReplacesHeaderSetEarlyFlagParam
 * ------------------------------------------------------------------------
 * General: Sets the early flag parameter..
 *          The BNF definition of this parameter is "early-only;".
 *          However, you can also set this parameter to be "early-only=1;"
 *          or "early-only=true;" (these options are not standard compliant!!!)
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader    - The handle to the header object.
 *  eEarlyFlag - The early flag value.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipReplacesHeaderSetEarlyFlagParam(
                                  IN RvSipReplacesHeaderHandle hHeader,
                                  IN RvSipReplacesEarlyFlagType eEarlyFlag);

/***************************************************************************
 * RvSipReplacesHeaderGetEarlyFlagParam
 * ------------------------------------------------------------------------
 * General: Gets the early flag parameter..
 *          The BNF definition of this parameter is "early-only;".
 *          However, you can also set this parameter to be "early-only=1;"
 *          or "early-only=true;" (these options are not standard compliant!!!)
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader    - The handle to the header object.
 *  peEarlyFlag - The early flag value.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipReplacesHeaderGetEarlyFlagParam(
                                  IN  RvSipReplacesHeaderHandle   hHeader,
                                  OUT RvSipReplacesEarlyFlagType *peEarlyFlag);


#endif /*#ifndef RV_SIP_PRIMITIVES*/

#ifdef __cplusplus
}
#endif

#endif /* RVSIPREPLACESHEADER_H */

