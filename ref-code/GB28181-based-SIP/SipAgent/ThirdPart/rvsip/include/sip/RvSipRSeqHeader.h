
/*

NOTICE:
This document contains information that is proprietary to RADVision LTD..
No part of this publication may be reproduced in any form whatsoever without
written prior approval by RADVision LTD..

RADVision LTD. reserves the right to revise this publication and make changes
without obligation to notify any person of such revisions or changes.

*/

/******************************************************************************
 *                          RvSipRSeqHeader.h                                 *
 *                                                                            *
 * The file defines the methods of the RSeq header object:                    *
 * construct, destruct, copy, encode, parse and the ability to access and     *
 * change it's parameters.                                                    *
 *                                                                            *
 *      Author           Date                                                 *
 *     ------           ------------                                          *
 *      Sarit             Aug.2001                                            *
 ******************************************************************************/

#ifndef RVSIPRSEQHEADER_H
#define RVSIPRSEQHEADER_H

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
 * RvSipRSeqHeaderStringName
 * ----------------------------
 * This enum defines all the header's strings (for getting it's size)
 */
typedef enum
{
    RVSIP_RSEQ_BAD_SYNTAX

}RvSipRSeqHeaderStringName;

/*-----------------------------------------------------------------------*/
/*                   CONSTRUCTORS AND DESTRUCTORS                        */
/*-----------------------------------------------------------------------*/

/***************************************************************************
 * RvSipRSeqHeaderConstructInMsg
 * ------------------------------------------------------------------------
 * General: Constructs a RSeq header object inside a given message object.
 *          The header is kept in the header list of the message.
 *          You can choose to insert the header either at the head or tail of
 *          the header list.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hSipMsg - Handle to the message related to the new header object.
 * output: hHeader - Handle to the RSeq header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRSeqHeaderConstructInMsg(
                                           IN  RvSipMsgHandle          hSipMsg,
                                           IN  RvBool                 pushHeaderAtHead,
                                           OUT RvSipRSeqHeaderHandle *hHeader);

/***************************************************************************
 * RvSipRSeqHeaderConstruct
 * ------------------------------------------------------------------------
 * General: Constructs and initializes a stand-alone RSeq Header object. The header is
 *          constructed on a given page taken from a specified pool. The handle to the new
 *          header object is returned.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hMsgMgr - Handle to the Message manager.
 *         hPool   - Handle to the memory pool that the object will use.
 *         hPage   - Handle to the memory page that the object will use.
 * output: hHeader - Handle to the newly constructed RSeq header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRSeqHeaderConstruct(
                                           IN  RvSipMsgMgrHandle      hMsgMgr,
                                           IN  HRPOOL                 hPool,
                                           IN  HPAGE                  hPage,
                                           OUT RvSipRSeqHeaderHandle* hHeader);

/***************************************************************************
 * RvSipRSeqHeaderCopy
 * ------------------------------------------------------------------------
 * General: Copies all fields from a source RSeq header object to a destination RSeq header
 *          object.
 *          You must construct the destination object before using this function.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hDestination - Handle to the destination RSeq header object.
 *    hSource      - Handle to the source RSeq header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRSeqHeaderCopy(
                                       INOUT    RvSipRSeqHeaderHandle hDestination,
                                       IN       RvSipRSeqHeaderHandle hSource);

/***************************************************************************
 * RvSipRSeqHeaderEncode
 * ------------------------------------------------------------------------
 * General: Encodes a RSeq header object to a textual RSeq header. The textual header is
 *          placed on a page taken from a specified pool. In order to copy the textual header
 *          from the page to a consecutive buffer, use RPOOL_CopyToExternal().
 *          The application must free the allocated page, using RPOOL_FreePage(). The
 *          allocated page must be freed only if this function returns RV_OK.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hHeader  - Handle to the RSeq header object.
 *         hPool    - Handle to the specified memory pool.
 * output: hPage    - The memory page allocated to contain the encoded header.
 *         length   - The length of the encoded information.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRSeqHeaderEncode(
                                          IN    RvSipRSeqHeaderHandle  hHeader,
                                          IN    HRPOOL                 hPool,
                                          OUT   HPAGE*                 hPage,
                                          OUT   RvUint32*             length);

/***************************************************************************
 * RvSipRSeqHeaderParse
 * ------------------------------------------------------------------------
 * General:Parses a SIP textual RSeq header—for example, “RSeq:43”—into a
 *         RSeq header object. All the textual fields are placed inside the object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader   - A handle to the RSeq header object.
 *    buffer    - Buffer containing a textual RSeq header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRSeqHeaderParse(
                                     IN    RvSipRSeqHeaderHandle    hHeader,
                                     IN    RvChar*                 buffer);

/***************************************************************************
 * RvSipRSeqHeaderParseValue
 * ------------------------------------------------------------------------
 * General: Parses a SIP textual RSeq header value into an RSeq header object.
 *          A SIP header has the following grammer:
 *          header-name:header-value. This function takes the header-value part as
 *          a parameter and parses it into the supplied object.
 *          All the textual fields are placed inside the object.
 *          Note: Use the RvSipRSeqHeaderParse() function to parse strings that also
 *          include the header-name.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader   - The handle to the RSeq header object.
 *    buffer    - The buffer containing a textual RSeq header value.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRSeqHeaderParseValue(
                                IN RvSipRSeqHeaderHandle hHeader,
                                IN RvChar*               buffer);

/***************************************************************************
 * RvSipRSeqHeaderFix
 * ------------------------------------------------------------------------
 * General: Fixes an RSeq header with bad-syntax information.
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
RVAPI RvStatus RVCALLCONV RvSipRSeqHeaderFix(
                                IN RvSipRSeqHeaderHandle hHeader,
                                IN RvChar*               pFixedBuffer);

/*-----------------------------------------------------------------------
                         G E T  A N D  S E T  M E T H O D S
 ------------------------------------------------------------------------*/
/***************************************************************************
 * RvSipRSeqHeaderGetStringLength
 * ------------------------------------------------------------------------
 * General: Some of the RSeq header fields are kept in a string format.
 *          In order to get such a field from the RSeq header object,
 *          your application should supply an adequate buffer to where the
 *          string will be copied.
 *          This function provides you with the length of the string to enable
 *          you to allocate an appropriate buffer size before calling the Get function.
 * Return Value: Returns the length of the specified string.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader    - Handle to the RSeq header object.
 *  stringName - Enumeration of the string name for which you require the length.
 ***************************************************************************/
RVAPI RvUint RVCALLCONV RvSipRSeqHeaderGetStringLength(
                                      IN  RvSipRSeqHeaderHandle     hHeader,
                                      IN  RvSipRSeqHeaderStringName stringName);

/***************************************************************************
 * RvSipRSeqHeaderGetResponseNum
 * ------------------------------------------------------------------------
 * General: Gets the response num value from the RSeq header object.
 * Return Value: Returns the response number value, or UNDEFINED if the number
 *               is not set.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader - Handle to the RSeq header object.
 ***************************************************************************/
RVAPI RvInt32 RVCALLCONV RvSipRSeqHeaderGetResponseNum(
                                          IN RvSipRSeqHeaderHandle hHeader);



/***************************************************************************
 * RvSipRSeqHeaderSetResponseNum
 * ------------------------------------------------------------------------
 * General:Sets the response num value in the RSeq header object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader - Handle to the RSeq header object.
 *    responseNum    - response num value to be set in the object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRSeqHeaderSetResponseNum(
                                          IN    RvSipRSeqHeaderHandle hHeader,
                                          IN    RvInt32              responseNum);

/***************************************************************************
 * RvSipRSeqHeaderGetStrBadSyntax
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
 *          implementation if the message contains a bad RSeq header,
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
RVAPI RvStatus RVCALLCONV RvSipRSeqHeaderGetStrBadSyntax(
                                               IN RvSipRSeqHeaderHandle hHeader,
                                               IN RvChar*                 strBuffer,
                                               IN RvUint                  bufferLen,
                                               OUT RvUint*                actualLen);
/***************************************************************************
 * RvSipRSeqHeaderSetStrBadSyntax
 * ------------------------------------------------------------------------
 * General: Sets a bad-syntax string in the object.
 *          A SIP header has the following grammer:
 *          header-name:header-value. When a header contains a syntax error,
 *          the header-value is kept as a separate "bad-syntax" string.
 *          By using this function you can create a header with "bad-syntax".
 *          Setting a bad syntax string to the header will mark the header as
 *          an invalid syntax header.
 *          You can use his function when you want to send an illegal RSeq header.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader      - The handle to the header object.
 *  strBadSyntax - The bad-syntax string.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRSeqHeaderSetStrBadSyntax(
                                  IN RvSipRSeqHeaderHandle hHeader,
                                  IN RvChar*              strBadSyntax);

#endif /*RV_SIP_PRIMITIVES*/

#ifdef __cplusplus
}
#endif
#endif /* RVSIPRSEQHEADER_H */
