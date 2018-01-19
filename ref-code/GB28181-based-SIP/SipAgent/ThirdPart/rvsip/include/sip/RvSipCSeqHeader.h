/*

NOTICE:
This document contains information that is proprietary to RADVision LTD..
No part of this publication may be reproduced in any form whatsoever without
written prior approval by RADVision LTD..

RADVision LTD. reserves the right to revise this publication and make changes
without obligation to notify any person of such revisions or changes.

*/

/******************************************************************************
 *                          RvSipCSeqHeader.h                                 *
 *                                                                            *
 * The file defines the methods of the CSeq header object:                    *
 * construct, destruct, copy, encode, parse and the ability to access and     *
 * change it's parameters.                                                    *
 *                                                                            *
 *      Author           Date                                                 *
 *     ------           ------------                                          *
 *      Ofra             Nov.2000                                             *
 ******************************************************************************/

#ifndef RVSIPCSEQHEADER_H
#define RVSIPCSEQHEADER_H

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                           */
/*-----------------------------------------------------------------------*/
#include "RV_SIP_DEF.h"
#include "RvSipMsgTypes.h"
#include "rpool_API.h"

#ifndef RV_SIP_PRIMITIVES
#include "RvSipRAckHeader.h"
#endif /* #ifndef RV_SIP_PRIMITIVES*/
/*-----------------------------------------------------------------------*/
/*                   DECLERATIONS                                        */
/*-----------------------------------------------------------------------*/
/*
 * RvSipCSeqHeaderStringName
 * ----------------------------
 * This enum defines all the header's strings (for getting it's size)
 * Defines all CSeq header object fields that are kept in the object
 * in a string format.
 */
typedef enum
{
    RVSIP_CSEQ_METHOD,
    RVSIP_CSEQ_BAD_SYNTAX
}RvSipCSeqHeaderStringName;

/*-----------------------------------------------------------------------*/
/*                   CONSTRUCTORS AND DESTRUCTORS                        */
/*-----------------------------------------------------------------------*/

/***************************************************************************
 * RvSipCSeqHeaderConstructInMsg
 * ------------------------------------------------------------------------
 * General: Constructs a CSeq header object inside a given message object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hSipMsg - Handle to the message related to the new header object.
 * output: hHeader - Handle to the CSeq header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipCSeqHeaderConstructInMsg(
                                           IN  RvSipMsgHandle         hSipMsg,
                                           OUT RvSipCSeqHeaderHandle *hHeader);

/***************************************************************************
 * RvSipCSeqHeaderConstruct
 * ------------------------------------------------------------------------
 * General: Constructs and initializes a stand-alone CSeq Header object. The header is
 *          constructed on a given page taken from a specified pool. The handle to the new
 *          header object is returned.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hMsgMgr - Handle to the Message manager.
 *         hPool   - Handle to the memory pool that the object will use.
 *         hPage   - Handle to the memory page that the object will use.
 * output: hHeader - Handle to the newly constructed CSeq header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipCSeqHeaderConstruct(
                                           IN  RvSipMsgMgrHandle      hMsgMgr,
                                           IN  HRPOOL                 hPool,
                                           IN  HPAGE                  hPage,
                                           OUT RvSipCSeqHeaderHandle* hHeader);

#ifndef RV_SIP_PRIMITIVES
/***************************************************************************
 * RvSipCSeqHeaderConstructInRAckHeader
 * ------------------------------------------------------------------------
 * General: Constructs a CSeq header object in a given RAck header.
 *          The header handle is returned.
 * Return Value: RV_OK, RV_ERROR_INVALID_HANDLE, RV_ERROR_NULLPTR, RV_ERROR_OUTOFRESOURCES
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hHeader - Handle to the RAck Header
 * output: phCSeq - Handle to the newly constructed CSeq object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipCSeqHeaderConstructInRAckHeader(
                                       IN  RvSipRAckHeaderHandle  hHeader,
                                       OUT RvSipCSeqHeaderHandle  *phCSeq);

#endif /*#ifndef RV_SIP_PRIMITIVES*/

/***************************************************************************
 * RvSipCSeqHeaderCopy
 * ------------------------------------------------------------------------
 * General: Copies all fields from a source CSeq header object to a destination CSeq header
 *          object.
 *          You must construct the destination object before using this function.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hDestination - Handle to the destination CSeq header object.
 *    hSource      - Handle to the source CSeq header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipCSeqHeaderCopy(
                                       INOUT    RvSipCSeqHeaderHandle hDestination,
                                       IN       RvSipCSeqHeaderHandle hSource);

/***************************************************************************
 * RvSipCSeqHeaderEncode
 * ------------------------------------------------------------------------
 * General: Encodes a CSeq header object to a textual CSeq header. The textual header is
 *          placed on a page taken from a specified pool. In order to copy the textual header
 *          from the page to a consecutive buffer, use RPOOL_CopyToExternal().
 *          The application must free the allocated page, using RPOOL_FreePage(). The
 *          allocated page must be freed only if this function returns RV_OK.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hHeader  - Handle to the CSeq header object.
 *         hPool    - Handle to the specified memory pool.
 * output: hPage    - The memory page allocated to contain the encoded header.
 *         length   - The length of the encoded information.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipCSeqHeaderEncode(
                                          IN    RvSipCSeqHeaderHandle  hHeader,
                                          IN    HRPOOL                 hPool,
                                          OUT   HPAGE*                 hPage,
                                          OUT   RvUint32*             length);

/***************************************************************************
 * RvSipCSeqHeaderParse
 * ------------------------------------------------------------------------
 * General:Parses a SIP textual CSeq header—for example, “CSeq: 1 INVITE”—into a
 *         CSeq header object. All the textual fields are placed inside the object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader   - A handle to the CSeq header object.
 *    buffer    - Buffer containing a textual CSeq header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipCSeqHeaderParse(
                                     IN    RvSipCSeqHeaderHandle    hHeader,
                                     IN    RvChar*                 buffer);

/***************************************************************************
 * RvSipCSeqHeaderParseValue
 * ------------------------------------------------------------------------
 * General: Parses a SIP textual CSeq header value into an CSeq header object.
 *          A SIP header has the following grammer:
 *          header-name:header-value. This function takes the header-value part as
 *          a parameter and parses it into the supplied object.
 *          All the textual fields are placed inside the object.
 *          Note: Use the RvSipCSeqHeaderParse() function to parse strings that also
 *          include the header-name.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader   - The handle to the CSeq header object.
 *    buffer    - The buffer containing a textual CSeq header value.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipCSeqHeaderParseValue(
                                     IN    RvSipCSeqHeaderHandle    hHeader,
                                     IN    RvChar*                 buffer);

/***************************************************************************
 * RvSipCSeqHeaderFix
 * ------------------------------------------------------------------------
 * General: Fixes an CSeq header with bad-syntax information.
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
RVAPI RvStatus RVCALLCONV RvSipCSeqHeaderFix(
                                     IN RvSipCSeqHeaderHandle hHeader,
                                     IN RvChar*              pFixedBuffer);

/*-----------------------------------------------------------------------
                         G E T  A N D  S E T  M E T H O D S
 ------------------------------------------------------------------------*/
/***************************************************************************
 * RvSipCSeqHeaderGetStringLength
 * ------------------------------------------------------------------------
 * General: Some of the CSeq header fields are kept in a string format—for example, the
 *          CSeq header method. In order to get such a field from the CSeq header object,
 *          your application should supply an adequate buffer to where the string will be
 *          copied.
 *          This function provides you with the length of the string to enable you to
 *          allocate an appropriate buffer size before calling the Get function.
 * Return Value: Returns the length of the specified string.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader    - Handle to the CSeq header object.
 *  stringName - Enumeration of the string name for which you require the length.
 ***************************************************************************/
RVAPI RvUint RVCALLCONV RvSipCSeqHeaderGetStringLength(
                                      IN  RvSipCSeqHeaderHandle     hHeader,
                                      IN  RvSipCSeqHeaderStringName stringName);

/***************************************************************************
 * RvSipCSeqHeaderGetStep
 * ------------------------------------------------------------------------
 * General: Gets the step value from the CSeq header object.
 * Return Value: Returns the step number value, or UNDEFINED if the step is not set.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader - Handle to the CSeq header object.
 ***************************************************************************/
RVAPI RvInt32 RVCALLCONV RvSipCSeqHeaderGetStep(
                                          IN RvSipCSeqHeaderHandle hHeader);



/***************************************************************************
 * RvSipCSeqHeaderSetStep
 * ------------------------------------------------------------------------
 * General:Sets the CSeq step value in the CSeq header object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader - Handle to the CSeq header object.
 *    step    - CSeq value to be set in the object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipCSeqHeaderSetStep(
                                          IN    RvSipCSeqHeaderHandle hHeader,
                                          IN    RvInt32              step);


/***************************************************************************
 * RvSipCSeqHeaderGetMethodType
 * ------------------------------------------------------------------------
 * General: Gets the method type enumeration from the CSeq header object.
 *          If this function returns RVSIP_METHOD_OTHER, call
 *          RvSipCseqHeaderGetStrMethodType() to get the actual method in a string
 *          format.
 * Return Value: Returns the method type enumeration from the CSeq header object.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader   - Handle to the CSeq header object.
 ***************************************************************************/
RVAPI RvSipMethodType RVCALLCONV RvSipCSeqHeaderGetMethodType(
                                          IN  RvSipCSeqHeaderHandle hHeader);

/***************************************************************************
 * RvSipCSeqHeaderGetStrMethodType
 * ------------------------------------------------------------------------
 * General: Copies the method type string from the CSeq header object into a given buffer.
 *          Use this function if RvSipCSeqHeaderGetMethodType() returns
 *          RVSIP_METHOD_OTHER.
 *          If the bufferLen is adequate, the function copies the requested parameter into
 *          strBuffer. Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and actualLen
 *          contains the required buffer length.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader    - Handle to the CSeq header object.
 *        strBuffer  - Buffer to fill with the requested parameter.
 *        bufferLen  - The length of the buffer.
 * output:actualLen - The length of the requested parameter, + 1 to include a NULL value at the end.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipCSeqHeaderGetStrMethodType(
                                          IN  RvSipCSeqHeaderHandle hHeader,
                                          IN  RvChar*              strBuffer,
                                          IN  RvUint               bufferLen,
                                          OUT RvUint*              actualLen);

/***************************************************************************
 * RvSipCSeqHeaderSetMethodType
 * ------------------------------------------------------------------------
 * General:Sets the method type in the CSeq object.
 *         If eMethodType is RVSIP_METHOD_OTHER, strMethodType is copied to the
 *         header. Otherwise strMethodType is ignored.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader       - Handle to the CSeq header object.
 *  eMethodType   - The method type to be set in the object.
 *    strMethodType - You can use this parameter only if the eMethodType parameter is set to
 *                  RVSIP_METHOD_OTHER. In this case, you can supply the method as a string.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipCSeqHeaderSetMethodType(
                                             IN    RvSipCSeqHeaderHandle hHeader,
                                             IN    RvSipMethodType       eMethodType,
                                             IN    RvChar*              strMethodType);

/***************************************************************************
 * RvSipCSeqHeaderGetStrBadSyntax
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
 *          implementation if the message contains a bad CSeq header,
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
RVAPI RvStatus RVCALLCONV RvSipCSeqHeaderGetStrBadSyntax(
                                          IN  RvSipCSeqHeaderHandle hHeader,
                                          IN  RvChar*              strBuffer,
                                          IN  RvUint               bufferLen,
                                          OUT RvUint*              actualLen);

/***************************************************************************
 * RvSipCSeqHeaderSetStrBadSyntax
 * ------------------------------------------------------------------------
 * General: Sets a bad-syntax string in the object.
 *          A SIP header has the following grammer:
 *          header-name:header-value. When a header contains a syntax error,
 *          the header-value is kept as a separate "bad-syntax" string.
 *          By using this function you can create a header with "bad-syntax".
 *          Setting a bad syntax string to the header will mark the header as
 *          an invalid syntax header.
 *          You can use his function when you want to send an illegal CSeq header.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader      - The handle to the header object.
 *  strBadSyntax - The bad-syntax string.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipCSeqHeaderSetStrBadSyntax(
                                  IN RvSipCSeqHeaderHandle hHeader,
                                  IN RvChar*                     strBadSyntax);


#ifdef __cplusplus
}
#endif
#endif /* RVSIPCSEQHEADER_H */
