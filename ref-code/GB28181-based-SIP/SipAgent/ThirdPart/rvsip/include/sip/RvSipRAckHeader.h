
/*

NOTICE:
This document contains information that is proprietary to RADVision LTD..
No part of this publication may be reproduced in any form whatsoever without
written prior approval by RADVision LTD..

RADVision LTD. reserves the right to revise this publication and make changes
without obligation to notify any person of such revisions or changes.

*/

/******************************************************************************
 *                          RvSipRAckHeader.h                                 *
 *                                                                            *
 * The file defines the methods of the RAck header object:                    *
 * construct, destruct, copy, encode, parse and the ability to access and     *
 * change it's parameters.                                                    *
 *                                                                            *
 *      Author           Date                                                 *
 *     ------           ------------                                          *
 *      Sarit             Aug.2001                                            *
 ******************************************************************************/

#ifndef RVSIPRACKHEADER_H
#define RVSIPRACKHEADER_H

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                           */
/*-----------------------------------------------------------------------*/
#include "RV_SIP_DEF.h"
#ifndef RV_SIP_PRIMITIVES
#include "RvSipMsgTypes.h"
#include "RvSipCSeqHeader.h"
#include "rpool_API.h"

/*-----------------------------------------------------------------------*/
/*                   DECLERATIONS                                        */
/*-----------------------------------------------------------------------*/
/*
 * RvSipRAckHeaderStringName
 * ----------------------------
 * This enum defines all the header's strings (for getting it's size)
 * Defines all RAck header object fields that are kept in the object 
 * in a string format.
 */
typedef enum
{
    RVSIP_RACK_BAD_SYNTAX
}RvSipRAckHeaderStringName;

/*-----------------------------------------------------------------------*/
/*                   CONSTRUCTORS AND DESTRUCTORS                        */
/*-----------------------------------------------------------------------*/

/***************************************************************************
 * RvSipRAckHeaderConstructInMsg
 * ------------------------------------------------------------------------
 * General: Constructs a RAck header object inside a given message object.
 *          The header is kept in the header list of the message.
 *          You can choose to insert the header either at the head or tail of
 *          the header list.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hSipMsg - Handle to the message related to the new header object.
 * output: hHeader - Handle to the RAck header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRAckHeaderConstructInMsg(
                                           IN  RvSipMsgHandle          hSipMsg,
                                           IN  RvBool                 pushHeaderAtHead,
                                           OUT RvSipRAckHeaderHandle *hHeader);

/***************************************************************************
 * RvSipRAckHeaderConstruct
 * ------------------------------------------------------------------------
 * General: Constructs and initializes a stand-alone RAck Header object. The header is
 *          constructed on a given page taken from a specified pool. The handle to the new
 *          header object is returned.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hMsgMgr - Handle to the Message manager.
 *         hPool   - Handle to the memory pool that the object will use.
 *         hPage   - Handle to the memory page that the object will use.
 * output: hHeader - Handle to the newly constructed RAck header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRAckHeaderConstruct(
                                           IN  RvSipMsgMgrHandle      hMsgMgr,
                                           IN  HRPOOL                 hPool,
                                           IN  HPAGE                  hPage,
                                           OUT RvSipRAckHeaderHandle* hHeader);

/***************************************************************************
 * RvSipRAckHeaderCopy
 * ------------------------------------------------------------------------
 * General: Copies all fields from a source RAck header object to a destination RAck header
 *          object.
 *          You must construct the destination object before using this function.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hDestination - Handle to the destination RAck header object.
 *    hSource      - Handle to the source RAck header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRAckHeaderCopy(
                                       INOUT    RvSipRAckHeaderHandle hDestination,
                                       IN       RvSipRAckHeaderHandle hSource);

/***************************************************************************
 * RvSipRAckHeaderEncode
 * ------------------------------------------------------------------------
 * General: Encodes a RAck header object to a textual RAck header. The textual header is
 *          placed on a page taken from a specified pool. In order to copy the textual header
 *          from the page to a consecutive buffer, use RPOOL_CopyToExternal().
 *          The application must free the allocated page, using RPOOL_FreePage(). The
 *          allocated page must be freed only if this function returns RV_OK.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hHeader  - Handle to the RAck header object.
 *         hPool    - Handle to the specified memory pool.
 * output: hPage    - The memory page allocated to contain the encoded header.
 *         length   - The length of the encoded information.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRAckHeaderEncode(
                                          IN    RvSipRAckHeaderHandle  hHeader,
                                          IN    HRPOOL                 hPool,
                                          OUT   HPAGE*                 hPage,
                                          OUT   RvUint32*             length);

/***************************************************************************
 * RvSipRAckHeaderParse
 * ------------------------------------------------------------------------
 * General:Parses a SIP textual RAck header—for example, “RAck:43”—into a
 *         RAck header object. All the textual fields are placed inside the object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader   - A handle to the RAck header object.
 *    buffer    - Buffer containing a textual RAck header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRAckHeaderParse(
                                     IN    RvSipRAckHeaderHandle    hHeader,
                                     IN    RvChar*                 buffer);

/***************************************************************************
 * RvSipRAckHeaderParseValue
 * ------------------------------------------------------------------------
 * General: Parses a SIP textual RAck header value into an RAck header object.
 *          A SIP header has the following grammer:
 *          header-name:header-value. This function takes the header-value part as
 *          a parameter and parses it into the supplied object.
 *          All the textual fields are placed inside the object.
 *          Note: Use the RvSipRAckHeaderParse() function to parse strings that also
 *          include the header-name.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader   - The handle to the RAck header object.
 *    buffer    - The buffer containing a textual RAck header value.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRAckHeaderParseValue(
                                     IN    RvSipRAckHeaderHandle    hHeader,
                                     IN    RvChar*                 buffer);

/***************************************************************************
 * RvSipRAckHeaderFix
 * ------------------------------------------------------------------------
 * General: Fixes an RAck header with bad-syntax information.
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
RVAPI RvStatus RVCALLCONV RvSipRAckHeaderFix(
                                     IN RvSipRAckHeaderHandle hHeader,
                                     IN RvChar*              pFixedBuffer);

/*-----------------------------------------------------------------------
                         G E T  A N D  S E T  M E T H O D S
 ------------------------------------------------------------------------*/
/***************************************************************************
 * RvSipRAckHeaderGetStringLength
 * ------------------------------------------------------------------------
 * General: Some of the RAck header fields are kept in a string format.
 *          In order to get such a field from the RAck header object,
 *          your application should supply an adequate buffer to where the
 *          string will be copied.
 *          This function provides you with the length of the string to enable
 *          you to allocate an appropriate buffer size before calling the Get function.
 * Return Value: Returns the length of the specified string.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader    - Handle to the RAck header object.
 *  stringName - Enumeration of the string name for which you require the length.
 ***************************************************************************/
RVAPI RvUint RVCALLCONV RvSipRAckHeaderGetStringLength(
                                      IN  RvSipRAckHeaderHandle     hHeader,
                                      IN  RvSipRAckHeaderStringName stringName);

/***************************************************************************
 * RvSipRAckHeaderGetResponseNum
 * ------------------------------------------------------------------------
 * General: Gets the response num value from the RAck header object.
 * Return Value: Returns the response number value, or UNDEFINED if the number
 *               is not set.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader - Handle to the RAck header object.
 ***************************************************************************/
RVAPI RvInt32 RVCALLCONV RvSipRAckHeaderGetResponseNum(
                                          IN RvSipRAckHeaderHandle hHeader);



/***************************************************************************
 * RvSipRAckHeaderSetResponseNum
 * ------------------------------------------------------------------------
 * General:Sets the response num value in the RAck header object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader - Handle to the RAck header object.
 *    responseNum    - response num value to be set in the object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRAckHeaderSetResponseNum(
                                          IN    RvSipRAckHeaderHandle hHeader,
                                          IN    RvInt32              responseNum);



/***************************************************************************
 * RvSipRAckHeaderGetCSeqHandle
 * ------------------------------------------------------------------------
 * General: Gets the Cseq Handle frp, tje RAck header.
 * Return Value: Returns the handle to the CSeq header object, or NULL
 *               if the CSeq header object does not exist.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input: hHeader - Handle to the RAck header object.
 ***************************************************************************/
RVAPI RvSipCSeqHeaderHandle RVCALLCONV RvSipRAckHeaderGetCSeqHandle(
                                        IN  RvSipRAckHeaderHandle hHeader);


/***************************************************************************
 * RvSipRAckHeaderSetCSeqHandle
 * ------------------------------------------------------------------------
 * General: Sets a new CSeq header in the RAck header object.
 * Return Value: RV_OK - success.
 *               RV_ERROR_INVALID_HANDLE - The RAck header handle is invalid.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input: hHeader - Handle to the RAck header object.
 *         hDate - The CSeq handle to be set in the RAck header.
 *                 If the CSeq handle is NULL, the existing CSeq header
 *                 is removed from the RAck header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRAckHeaderSetCSeqHandle(
                                       IN  RvSipRAckHeaderHandle hHeader,
                                       IN  RvSipCSeqHeaderHandle hCSeq);

/***************************************************************************
 * RvSipRAckHeaderGetStrBadSyntax
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
 *          implementation if the message contains a bad RAck header,
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
RVAPI RvStatus RVCALLCONV RvSipRAckHeaderGetStrBadSyntax(
                                               IN RvSipRAckHeaderHandle hHeader,
                                               IN RvChar*                 strBuffer,
                                               IN RvUint                  bufferLen,
                                               OUT RvUint*                actualLen);

/***************************************************************************
 * RvSipRAckHeaderSetStrBadSyntax
 * ------------------------------------------------------------------------
 * General: Sets a bad-syntax string in the object.
 *          A SIP header has the following grammer:
 *          header-name:header-value. When a header contains a syntax error,
 *          the header-value is kept as a separate "bad-syntax" string.
 *          By using this function you can create a header with "bad-syntax".
 *          Setting a bad syntax string to the header will mark the header as
 *          an invalid syntax header.
 *          You can use his function when you want to send an illegal RAck header.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader      - The handle to the header object.
 *  strBadSyntax - The bad-syntax string.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipRAckHeaderSetStrBadSyntax(
                                  IN RvSipRAckHeaderHandle hHeader,
                                  IN RvChar*              strBadSyntax);

#endif /* RV_SIP_PRIMITIVES*/

#ifdef __cplusplus
}
#endif

#endif /* RVSIPRACKHEADER_H */

