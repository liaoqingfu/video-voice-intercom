/*

NOTICE:
This document contains information that is proprietary to RADVision LTD..
No part of this publication may be reproduced in any form whatsoever without
written prior approval by RADVision LTD..

RADVision LTD. reserves the right to revise this publication and make changes
without obligation to notify any person of such revisions or changes.

*/

/******************************************************************************
 *                     RvSipOtherHeader.h                                       *
 *                                                                            *
 * The file defines the methods of the Other header object:                   *
 * construct, destruct, copy, encode, parse and the ability to access and     *
 * change it's parameters.                                                    *
 * The OtherHeader should be use for every header that has no specific object *
 * (not to use for To, From, Cseq ... that have specific objects)             *
 *                                                                            *
 *      Author           Date                                                 *
 *     ------           ------------                                          *
 *      Ofra             Nov.2000                                             *
 ******************************************************************************/
#ifndef RVSIPOTHERHEADER_H
#define RVSIPOTHERHEADER_H

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                           */
/*-----------------------------------------------------------------------*/
#include "RV_SIP_DEF.h"
#include "RvSipMsgTypes.h"
#include "rpool_API.h"

/*-----------------------------------------------------------------------*/
/*                   DECLERATIONS                                        */
/*-----------------------------------------------------------------------*/
/*
 * RvSipOtherHeaderStringName
 * ----------------------
 * This enum defines all the header's strings (for getting it's size)
 * Defines all Other Header object fields that are kept in the object 
 * in a string format.
 */
typedef enum
{
    RVSIP_OTHER_HEADER_NAME,
    RVSIP_OTHER_HEADER_VALUE,
    RVSIP_OTHER_BAD_SYNTAX
}RvSipOtherHeaderStringName;


/*-----------------------------------------------------------------------*/
/*                   CONSTRUCTORS AND DESTRUCTORS                        */
/*-----------------------------------------------------------------------*/

/***************************************************************************
 * RvSipOtherHeaderConstructInMsg
 * ------------------------------------------------------------------------
 * General: Constructs a Other header object inside a given message object. The header is
 *          kept in the header list of the message. You can choose to insert the header either
 *          at the head or tail of the list.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hSipMsg          - Handle to the message object.
 *         pushHeaderAtHead - Boolean value indicating whether the header should be pushed to the head of the
 *                            list—RV_TRUE—or to the tail—RV_FALSE.
 * output: hHeader          - Handle to the newly constructed Other header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipOtherHeaderConstructInMsg(
                                           IN  RvSipMsgHandle          hSipMsg,
                                           IN  RvBool                 pushHeaderAtHead,
                                           OUT RvSipOtherHeaderHandle* hHeader);

#ifndef RV_SIP_PRIMITIVES
/***************************************************************************
 * RvSipOtherHeaderConstructInBodyPart
 * ------------------------------------------------------------------------
 * General: Constructs a Other header object inside a given message body
 *          part object. The header is kept in the other headers list of
 *          the message body part object. You can choose to insert the
 *          header either at the head or tail of the list.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hBodyPart        - Handle to the message body-part object.
 *         pushHeaderAtHead - Boolean value indicating whether the header
 *                            should be pushed to the head of the list?
 *                            RV_TRUE—or to the tail—RV_FALSE.
 * output: hHeader          - Handle to the newly constructed Other header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipOtherHeaderConstructInBodyPart(
                                    IN  RvSipBodyPartHandle     hBodyPart,
                                    IN  RvBool                 pushHeaderAtHead,
                                    OUT RvSipOtherHeaderHandle* hHeader);
#endif /* #ifndef RV_SIP_PRIMITIVES */

/***************************************************************************
 * RvSipOtherHeaderConstruct
 * ------------------------------------------------------------------------
 * General: Constructs and initializes a stand-alone Other Header object. The header is
 *          constructed on a given page taken from a specified pool. The handle to the new
 *          header object is returned.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hMsgMgr - Handle to the Message manager.
 *         hPool   - Handle to the memory pool that the object will use.
 *         hPage   - Handle to the memory page that the object will use.
 * output: hHeader - Handle to the newly constructed Other header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipOtherHeaderConstruct(
                                           IN  RvSipMsgMgrHandle       hMsgMgr,
                                           IN  HRPOOL                  hPool,
                                           IN  HPAGE                   hPage,
                                           OUT RvSipOtherHeaderHandle* hHeader);

/***************************************************************************
 * RvSipOtherHeaderCopy
 * ------------------------------------------------------------------------
 * General: Copies all fields from a source Other header object to a destination Other header
 *          object.
 *          You must construct the destination object before using this function.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hDestination - Handle to the destination Other header object.
 *    hSource      - Handle to the source Other header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipOtherHeaderCopy(
                                         INOUT    RvSipOtherHeaderHandle hDestination,
                                         IN       RvSipOtherHeaderHandle hSource);

/***************************************************************************
 * RvSipOtherHeaderEncode
 * ------------------------------------------------------------------------
 * General: Encodes a contact header object to a textual Other header. The textual header is
 *          placed on a page taken from a specified pool. In order to copy the textual header
 *          from the page to a consecutive buffer, use RPOOL_CopyToExternal().
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader  - Handle to the Other header object.
 *        hPool    - Handle to the specified memory pool.
 * output: hPage   - The memory page allocated to contain the encoded header.
 *         length  - The length of the encoded information.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipOtherHeaderEncode(
                                          IN    RvSipOtherHeaderHandle hHeader,
                                          IN    HRPOOL                 hPool,
                                          OUT   HPAGE*                 hPage,
                                          OUT   RvUint32*             length);

/***************************************************************************
 * RvSipOtherHeaderParse
 * ------------------------------------------------------------------------
 * General:Parses a SIP textual Other header—for example, “Content–Disposition:
 *         session”—into a Other header object. All the textual fields are placed inside the
 *         object.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader   - A handle to the Other header object.
 *    buffer    - Buffer containing a textual Other header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipOtherHeaderParse(
                                     IN    RvSipOtherHeaderHandle   hHeader,
                                     IN    RvChar*                 buffer);
/*-----------------------------------------------------------------------
                         G E T  A N D  S E T  M E T H O D S
 ------------------------------------------------------------------------*/
/***************************************************************************
 * RvSipOtherHeaderGetStringLength
 * ------------------------------------------------------------------------
 * General: Some of the Other header fields are kept in a string format—for example, the
 *          Other header display name. In order to get such a field from the Other header
 *          object, your application should supply an adequate buffer to where the string
 *          will be copied.
 *          This function provides you with the length of the string to enable you to
 *          allocate an appropriate buffer size before calling the Get function.
 * Return Value: Returns the length of the specified string.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader    - Handle to the Other header object.
 *  stringName - Enumeration of the string name for which you require the length.
 ***************************************************************************/
RVAPI RvUint RVCALLCONV RvSipOtherHeaderGetStringLength(
                                      IN  RvSipOtherHeaderHandle     hHeader,
                                      IN  RvSipOtherHeaderStringName stringName);

/***************************************************************************
 * RvSipOtherHeaderGetName
 * ------------------------------------------------------------------------
 * General: Copies the name of the Other header into a given buffer.
 *          If the bufferLen is adequate, the function copies the requested parameter into
 *          strBuffer. Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and actualLen
 *          contains the required buffer length.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader    - Handle to the header object.
 *        strBuffer  - Buffer to fill with the requested parameter.
 *        bufferLen  - The length of the buffer.
 * output:actualLen - The length of the requested parameter, + 1 to include a NULL value at the end
 *                     of the parameter.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipOtherHeaderGetName(
                                               IN RvSipOtherHeaderHandle   hHeader,
                                               IN RvChar*                 strBuffer,
                                               IN RvUint                  bufferLen,
                                               OUT RvUint*                actualLen);

/***************************************************************************
 * RvSipOtherHeaderSetName
 * ------------------------------------------------------------------------
 * General: Sets the name of the header.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader   - Handle of the Other header object.
 *    strName   - The name of the header to be set in the Other header. If NULL is supplied, the
 *              existing header name is removed.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipOtherHeaderSetName(
                                         IN    RvSipOtherHeaderHandle hHeader,
                                         IN    RvChar*               strName);

/***************************************************************************
 * RvSipOtherHeaderGetValue
 * ------------------------------------------------------------------------
 * General: Copies the value of the Other header into a given buffer.
 *          If the bufferLen is adequate, the function copies the requested parameter into
 *          strBuffer. Otherwise, the function returns RV_ERROR_INSUFFICIENT_BUFFER and actualLen
 *          contains the required buffer length.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader    - Handle of the Other header object.
 *        strBuffer  - buffer to fill with the requested parameter.
 *        bufferLen  - the length of the buffer.
 * output:actualLen - The length of the requested parameter, + 1 to include a NULL value at the end
 *                     of the parameter.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipOtherHeaderGetValue(
                                               IN RvSipOtherHeaderHandle   hHeader,
                                               IN RvChar*                 strBuffer,
                                               IN RvUint                  bufferLen,
                                               OUT RvUint*                actualLen);

/***************************************************************************
 * RvSipOtherHeaderSetValue
 * ------------------------------------------------------------------------
 * General: Sets the value of the header.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader  - Handle of the Other header object.
 *    strValue - The header value to be set in the Other header. If NULL is supplied, the existing
 *             header value is removed.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipOtherHeaderSetValue(
                                        IN    RvSipOtherHeaderHandle hHeader,
                                        IN    RvChar*               strValue);

/***************************************************************************
 * RvSipOtherHeaderGetStrBadSyntax
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
 *          implementation if the message contains a bad Other header,
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
RVAPI RvStatus RVCALLCONV RvSipOtherHeaderGetStrBadSyntax(
                                               IN RvSipOtherHeaderHandle hHeader,
                                               IN RvChar*                 strBuffer,
                                               IN RvUint                  bufferLen,
                                               OUT RvUint*                actualLen);

/***************************************************************************
 * RvSipOtherHeaderSetStrBadSyntax
 * ------------------------------------------------------------------------
 * General: Sets a bad-syntax string in the object.
 *          A SIP header has the following grammer:
 *          header-name:header-value. When a header contains a syntax error,
 *          the header-value is kept as a separate "bad-syntax" string.
 *          By using this function you can create a header with "bad-syntax".
 *          Setting a bad syntax string to the header will mark the header as
 *          an invalid syntax header.
 *          You can use his function when you want to send an illegal Other header.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader      - The handle to the header object.
 *  strBadSyntax - The bad-syntax string.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipOtherHeaderSetStrBadSyntax(
                                  IN RvSipOtherHeaderHandle hHeader,
                                  IN RvChar*               strBadSyntax);

#ifndef RV_SIP_PRIMITIVES
/***************************************************************************
 * RvSipOtherHeaderGetRpoolString
 * ------------------------------------------------------------------------
 * General: Copy a string parameter from the Other header into a given page
 *          from a specified pool. The copied string is not consecutive.
 * Return Value: RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input: hSipOtherHeader - Handle to the Other header object.
 *           eStringName   - The string the user wish to get
 *  Input/Output:
 *         pRpoolPtr     - pointer to a location inside an rpool. You need to
 *                         supply only the pool and page. The offset where the
 *                         returned string was located will be returned as an
 *                         output patameter.
 *                         If the function set the returned offset to
 *                         UNDEFINED is means that the parameter was not
 *                         set to the Other header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipOtherHeaderGetRpoolString(
                             IN    RvSipOtherHeaderHandle      hSipOtherHeader,
                             IN    RvSipOtherHeaderStringName  eStringName,
                             INOUT RPOOL_Ptr                     *pRpoolPtr);


/***************************************************************************
 * RvSipOtherHeaderSetRpoolString
 * ------------------------------------------------------------------------
 * General: Sets a string into a specified parameter in the Other header
 *          object. The given string is located on an RPOOL memory and is
 *          not consecutive.
 * Return Value: RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input: hSipOtherHeader - Handle to the Other header object.
 *           eStringName   - The string the user wish to set
 *         pRpoolPtr     - pointer to a location inside an rpool where the
 *                         new string is located.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipOtherHeaderSetRpoolString(
                             IN    RvSipOtherHeaderHandle      hSipOtherHeader,
                             IN    RvSipOtherHeaderStringName  eStringName,
                             IN    RPOOL_Ptr                 *pRpoolPtr);
#endif



#ifdef __cplusplus
}
#endif
#endif /*RVSIPOTHERHEADER_H */
