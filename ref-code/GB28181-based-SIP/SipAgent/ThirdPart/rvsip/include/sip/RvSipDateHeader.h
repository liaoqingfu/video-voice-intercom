/*

NOTICE:
This document contains information that is proprietary to RADVision LTD..
No part of this publication may be reproduced in any form whatsoever without
written prior approval by RADVision LTD..

RADVision LTD. reserves the right to revise this publication and make changes
without obligation to notify any person of such revisions or changes.

*/

/******************************************************************************
 *                             RvSipDateHeader.h                              *
 *                                                                            *
 * The file defines the functions  of the Date header object:                 *
 * The Date header functions enable you to construct, destruct, copy, encode, *
 * parse, access and change Date Header parameters.                           *                        *
 *                                                                            *
 *      Author           Date                                                 *
 *     ------           ------------                                          *
 *     Tamar Barzuza    Jan 2001                                              *
 ******************************************************************************/
#ifndef RVSIPDATEHEADER_H
#define RVSIPDATEHEADER_H

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
 * RvSipDateHeaderStringName
 * ----------------------------
 * This enum defines all the header's strings (for getting it's size)
 * Defines all Date header object fields that are kept in the object 
 * in a string format.
 */
typedef enum
{
    RVSIP_DATE_BAD_SYNTAX
}RvSipDateHeaderStringName;

/*-----------------------------------------------------------------------*/
/*                   CONSTRUCTORS AND DESTRUCTORS                        */
/*-----------------------------------------------------------------------*/

/***************************************************************************
 * RvSipDateHeaderConstructInMsg
 * ------------------------------------------------------------------------
 * General: Constructs a Date header object inside a given message object.
 *          The header is kept in the header list of the message.
 *          You can choose to insert the header either at the head or tail
 *          of the list.
 * Return Value: RV_OK, RV_ERROR_INVALID_HANDLE, RV_ERROR_NULLPTR, RV_ERROR_OUTOFRESOURCES
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hSipMsg - Handle of the message object.
 *         pushHeaderAtHead - Boolean value indicating whether the header
 *                            should be pushed to the head of the
 *                            list—RV_TRUE—or to the tail—RV_FALSE.
 * output: phHeader - Handle of the newly constructed date header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipDateHeaderConstructInMsg(
                                IN  RvSipMsgHandle            hSipMsg,
                                IN  RvBool                   pushHeaderAtHead,
                                OUT RvSipDateHeaderHandle*    phHeader);


/***************************************************************************
 * RvSipDateConstructInExpiresHeader
 * ------------------------------------------------------------------------
 * General: Constructs a Date header object in a given Expires header.
 *          The header handle is returned.
 * Return Value: RV_OK, RV_ERROR_INVALID_HANDLE, RV_ERROR_NULLPTR, RV_ERROR_OUTOFRESOURCES
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hHeader - Handle to the Expires header that relates to this date.
 * output: phDate - Handle to the newly constructed date object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipDateConstructInExpiresHeader(
                                       IN  RvSipExpiresHeaderHandle  hHeader,
                                       OUT RvSipDateHeaderHandle    *phDate);


#ifndef RV_SIP_PRIMITIVES
/***************************************************************************
 * RvSipDateConstructInRetryAfterHeader
 * ------------------------------------------------------------------------
 * General: Constructs a Date header object in a given Retry-After header.
 *          The header handle is returned.
 * Return Value: RV_OK, RV_ERROR_INVALID_HANDLE, RV_ERROR_NULLPTR, RV_ERROR_OUTOFRESOURCES
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hHeader - Handle to the RetryAfter header that relates to this date.
 * output: phDate - Handle to the newly constructed date object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipDateConstructInRetryAfterHeader(
                                       IN  RvSipRetryAfterHeaderHandle  hHeader,
                                       OUT RvSipDateHeaderHandle        *phDate);

#endif /*#ifndef RV_SIP_PRIMITIVES*/
/***************************************************************************
 * RvSipDateHeaderConstruct
 * ------------------------------------------------------------------------
 * General: Constructs and initializes a stand-alone Date Header object.
 *          The header is constructed on a given page taken from a specified
 *          pool. The handle to the new header object is returned.
 * Return Value: RV_OK, RV_ERROR_INVALID_HANDLE, RV_ERROR_NULLPTR, RV_ERROR_OUTOFRESOURCES.
 * ------------------------------------------------------------------------
 * Arguments:
 * input:  hMsgMgr  - Handle to the message manager.
 *         hPool    - Handle to the memory pool that the object will use
 *         hPage    - Handle of the memory page that the object will use
 * output: phHeader - Handle to the newly constructed date object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipDateHeaderConstruct(
                                        IN  RvSipMsgMgrHandle         hMsgMgr,
                                        IN  HRPOOL                    hPool,
                                        IN  HPAGE                     hPage,
                                        OUT RvSipDateHeaderHandle*    phHeader);


/***************************************************************************
 * RvSipDateHeaderCopy
 * ------------------------------------------------------------------------
 * General:Copies all fields from a source Date header object to a destination
 *         Date header object.
 *         You must construct the destination object before using this function.
 * Return Value: RV_OK, RV_ERROR_OUTOFRESOURCES, RV_ERROR_INVALID_HANDLE.
 * ------------------------------------------------------------------------
 * Arguments:
 *    pDestination - Handle to the destination Date header object.
 *    pSource      - Handle to the source Date header object.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipDateHeaderCopy(
                                     INOUT RvSipDateHeaderHandle hDestination,
                                     IN    RvSipDateHeaderHandle hSource);


/***************************************************************************
 * RvSipDateHeaderEncode
 * ------------------------------------------------------------------------
 * General: Encodes a Date header object to a textual Date header.
 *          The textual header is placed on a page taken from a specified pool.
 *          In order to copy the textual header
 *          from the page to a consecutive buffer, use RPOOL_CopyToExternal().
 *          The application must free the allocated page, using RPOOL_FreePage().
 *          The allocated page must be freed only if this function returns
 *          RV_OK.
 * Return Value: RV_OK          - If succeeded.
 *               RV_ERROR_OUTOFRESOURCES   - If allocation failed (no resources)
 *               RV_ERROR_UNKNOWN          - In case of a failure.
 *               RV_ERROR_BADPARAM - If hHeader or hPool are NULL or the
 *                                     header is not initialized.
 *               RV_ERROR_NULLPTR       - pLength or phPage are NULL.
 * ------------------------------------------------------------------------
 * Arguments:
 * input: hHeader  - Handle of the Date header object.
 *        hPool    - Handle to the specified memory pool.
 * output: phPage   - The memory page allocated to contain the encoded header.
 *         pLength  - The length of the encoded information.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipDateHeaderEncode(
                                      IN    RvSipDateHeaderHandle    hHeader,
                                      IN    HRPOOL                   hPool,
                                      OUT   HPAGE*                   phPage,
                                      OUT   RvUint32*               pLength);


/***************************************************************************
 * RvSipDateHeaderParse
 * ------------------------------------------------------------------------
 * General:Parses a SIP textual Date header into a Date header object.
 *         All the textual fields are placed inside the object.
 *         You must construct a Date header before using this function.
 * Return Value: RV_OK, RV_ERROR_OUTOFRESOURCES,RV_ERROR_INVALID_HANDLE,
 *                 RV_ERROR_ILLEGAL_SYNTAX,RV_ERROR_ILLEGAL_SYNTAX.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader   -    A handle to the Date header object.
 *    strBuffer -    Buffer containing a textual Date header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipDateHeaderParse(
                                     IN    RvSipDateHeaderHandle    hHeader,
                                     IN    RvChar*                 strBuffer);

/***************************************************************************
 * RvSipDateHeaderParseValue
 * ------------------------------------------------------------------------
 * General: Parses a SIP textual Date header value into an Date header object.
 *          A SIP header has the following grammer:
 *          header-name:header-value. This function takes the header-value part as
 *          a parameter and parses it into the supplied object.
 *          All the textual fields are placed inside the object.
 *          Note: Use the RvSipDateHeaderParse() function to parse strings that also
 *          include the header-name.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader   - The handle to the Date header object.
 *    buffer    - The buffer containing a textual Date header value.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipDateHeaderParseValue(
                                     IN    RvSipDateHeaderHandle    hHeader,
                                     IN    RvChar*                 strBuffer);

/***************************************************************************
 * RvSipDateHeaderFix
 * ------------------------------------------------------------------------
 * General: Fixes an Date header with bad-syntax information.
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
RVAPI RvStatus RVCALLCONV RvSipDateHeaderFix(
                                     IN RvSipDateHeaderHandle hHeader,
                                     IN RvChar*              pFixedBuffer);

/*-----------------------------------------------------------------------
                         G E T  A N D  S E T  M E T H O D S
 ------------------------------------------------------------------------*/


/***************************************************************************
 * RvSipDateHeaderGetWeekDay
 * ------------------------------------------------------------------------
 * General: Gets the week-day enumeration. RVSIP_WEEKDAY_UNDEFINED is returned
 *          if the weekday is not set.
 * Return Value: The enumeration of the week day.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input: hHeader - Handle of the Date header object.
 ***************************************************************************/
RVAPI RvSipDateWeekDay RVCALLCONV RvSipDateHeaderGetWeekDay(
                                        IN  RvSipDateHeaderHandle hHeader);


/***************************************************************************
 * RvSipDateHeaderSetWeekDay
 * ------------------------------------------------------------------------
 * General: Sets the week-day parameter of the Date header.
 * Return Value: RV_OK - success.
 *               RV_ERROR_INVALID_HANDLE - The Expires header handle is invalid.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input: hHeader - Handle of the Date header object.
 *         eWeekDay - The week-day enumeration.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipDateHeaderSetWeekDay(
                                       IN  RvSipDateHeaderHandle    hHeader,
                                       IN  RvSipDateWeekDay         eWeekDay);


/***************************************************************************
 * RvSipDateHeaderGetDay
 * ------------------------------------------------------------------------
 * General: Gets the number for the day of the month in the given Date header.
 *
 * Return Value: Returns the day number. If the integer number for the day of the
 *               month is not set, UNDEFINED is returned.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input: hHeader - Handle of the Date header object.
 ***************************************************************************/
RVAPI RvInt8 RVCALLCONV RvSipDateHeaderGetDay(
                                        IN  RvSipDateHeaderHandle hHeader);


/***************************************************************************
 * RvSipDateHeaderSetDay
 * ------------------------------------------------------------------------
 * General: Sets the number for the day of the month parameter of the Date header.
 * Return Value: RV_OK - success.
 *               RV_ERROR_INVALID_HANDLE - The Expires header handle is invalid.
 *               RV_Invalid parameter - The day integer is negative
 *                                      other than UNDEFINED.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input: hHeader - Handle of the Date header object.
 *         day - The day number.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipDateHeaderSetDay(
                                       IN  RvSipDateHeaderHandle    hHeader,
                                       IN  RvInt8                  day);


/***************************************************************************
 * RvSipDateHeaderGetMonth
 * ------------------------------------------------------------------------
 * General: Gets the month enumeration of the given Date header.
 *          RVSIP_MONTH_UNDEFINED is returned if the month field is not set.
 * Return Value: The month enumeration.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input: hHeader - Handle of the Date header object.
 ***************************************************************************/
RVAPI RvSipDateMonth RVCALLCONV RvSipDateHeaderGetMonth(
                                        IN  RvSipDateHeaderHandle hHeader);


/***************************************************************************
 * RvSipDateHeaderSetMonth
 * ------------------------------------------------------------------------
 * General: Sets the month parameter of the Date header.
 * Return Value: RV_OK - success.
 *               RV_ERROR_INVALID_HANDLE - The Date header handle is invalid.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input: hHeader - Handle to the Date header object.
 *         eMonth - The month enumeration.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipDateHeaderSetMonth(
                                       IN  RvSipDateHeaderHandle    hHeader,
                                       IN  RvSipDateMonth           eMonth);


/***************************************************************************
 * RvSipDateHeaderGetYear
 * ------------------------------------------------------------------------
 * General: Get the year of the given Date header.
 *          If the year integer was not initialized UNDEFINED is returned.
 * Return Value: Returns the year number. If the year field is not set,
 *               UNDEFINED is returned.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input: hHeader - Handle of the Date header object.
 ***************************************************************************/
RVAPI RvInt16 RVCALLCONV RvSipDateHeaderGetYear(
                                        IN  RvSipDateHeaderHandle hHeader);


/***************************************************************************
 * RvSipDateHeaderSetYear
 * ------------------------------------------------------------------------
 * General: Sets the year number parameter of the Date header.
 * Return Value: RV_OK - success.
 *               RV_ERROR_INVALID_HANDLE - The Expires header handle is invalid.
 *               RV_Invalid parameter - The year integer is negative
 *                                      other than UNDEFINED.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input: hHeader - Handle of the Date header object.
 *         year - The year number.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipDateHeaderSetYear(
                                       IN  RvSipDateHeaderHandle    hHeader,
                                       IN  RvInt16                 year);


/***************************************************************************
 * RvSipDateHeaderGetHour
 * ------------------------------------------------------------------------
 * General: Get the hour of the given Date header.
 * Return Value: Returns the hour number. If the hour field is not set,
 *               UNDEFINED is returned.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input: hHeader - Handle to the Date header object.
 ***************************************************************************/
RVAPI RvInt8 RVCALLCONV RvSipDateHeaderGetHour(
                                        IN  RvSipDateHeaderHandle hHeader);


/***************************************************************************
 * RvSipDateHeaderSetHour
 * ------------------------------------------------------------------------
 * General: Sets the hour number parameter of the Date header.
 * Return Value: RV_OK - success.
 *               RV_ERROR_INVALID_HANDLE - The Date header handle is invalid.
 *               RV_Invalid parameter - The hour integer is negative
 *                                      other than UNDEFINED.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input: hHeader - Handle to the Date header object.
 *         year - The hour number.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipDateHeaderSetHour(
                                       IN  RvSipDateHeaderHandle    hHeader,
                                       IN  RvInt8                  hour);


/***************************************************************************
 * RvSipDateHeaderGetMinute
 * ------------------------------------------------------------------------
 * General: Gets the minute of the given Date header.
 * Return Value: Returns the minute number. If the minute field is not set,
 *               UNDEFINED is returned.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input: hHeader - Handle to the Date header object.
 ***************************************************************************/
RVAPI RvInt8 RVCALLCONV RvSipDateHeaderGetMinute(
                                        IN  RvSipDateHeaderHandle hHeader);


/***************************************************************************
 * RvSipDateHeaderSetMinute
 * ------------------------------------------------------------------------
 * General: Sets the minute number parameter of the Date header.
 * Return Value: RV_OK - success.
 *               RV_ERROR_INVALID_HANDLE - The Date header handle is invalid.
 *               RV_Invalid parameter - The minute integer is negative
 *                                      other than UNDEFINED.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input: hHeader - Handle to the Date header object.
 *         minute - The minute number.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipDateHeaderSetMinute(
                                       IN  RvSipDateHeaderHandle    hHeader,
                                       IN  RvInt8                  minute);


/***************************************************************************
 * RvSipDateHeaderGetSecond
 * ------------------------------------------------------------------------
 * General: Gets the second number of the given Date header.
 * Return Value: Returns the second number. If the second field is not set,
 *               UNDEFINED is returned.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input: hHeader - Handle to the Date header object.
 ***************************************************************************/
RVAPI RvInt8 RVCALLCONV RvSipDateHeaderGetSecond(
                                        IN  RvSipDateHeaderHandle hHeader);


/***************************************************************************
 * RvSipDateHeaderSetSecond
 * ------------------------------------------------------------------------
 * General: Sets the second number parameter of the Date header.
 * Return Value: RV_OK - success.
 *               RV_ERROR_INVALID_HANDLE - The Date header handle is invalid.
 *               RV_Invalid parameter - The second integer is negative
 *                                      other than UNDEFINED.
 * ------------------------------------------------------------------------
 * Arguments:
 *    Input: hHeader - Handle to the Date header object.
 *         second - The second number.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipDateHeaderSetSecond(
                                       IN  RvSipDateHeaderHandle    hHeader,
                                       IN  RvInt8                  second);

/***************************************************************************
 * RvSipDateHeaderGetStringLength
 * ------------------------------------------------------------------------
 * General: Some of the Date header fields are kept in a string format.
 *          In order to get such a field from the Date header object,
 *          your application should supply an adequate buffer to where the
 *          string will be copied.
 *          This function provides you with the length of the string to enable
 *          you to allocate an appropriate buffer size before calling the Get function.
 * Return Value: Returns the length of the specified string.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader    - Handle to the Date header object.
 *  stringName - Enumeration of the string name for which you require the length.
 ***************************************************************************/
RVAPI RvUint RVCALLCONV RvSipDateHeaderGetStringLength(
                                      IN  RvSipDateHeaderHandle     hHeader,
                                      IN  RvSipDateHeaderStringName stringName);

/***************************************************************************
 * RvSipDateHeaderGetStrBadSyntax
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
 *          implementation if the message contains a bad Date header,
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
RVAPI RvStatus RVCALLCONV RvSipDateHeaderGetStrBadSyntax(
                                       IN RvSipDateHeaderHandle hHeader,
                                       IN RvChar*                 strBuffer,
                                       IN RvUint                  bufferLen,
                                       OUT RvUint*                actualLen);

/***************************************************************************
 * RvSipDateHeaderSetStrBadSyntax
 * ------------------------------------------------------------------------
 * General: Sets a bad-syntax string in the object.
 *          A SIP header has the following grammer:
 *          header-name:header-value. When a header contains a syntax error,
 *          the header-value is kept as a separate "bad-syntax" string.
 *          By using this function you can create a header with "bad-syntax".
 *          Setting a bad syntax string to the header will mark the header as
 *          an invalid syntax header.
 *          You can use his function when you want to send an illegal Date header.
 * Return Value: Returns RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 *    hHeader      - The handle to the header object.
 *  strBadSyntax - The bad-syntax string.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipDateHeaderSetStrBadSyntax(
                                  IN RvSipDateHeaderHandle hHeader,
                                  IN RvChar*                     strBadSyntax);


#ifdef __cplusplus
}
#endif

#endif /* END OF: #ifndef RVSIPDATEHEADER_H */

