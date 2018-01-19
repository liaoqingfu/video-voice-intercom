/*

NOTICE:
This document contains information that is proprietary to RADVision LTD..
No part of this publication may be reproduced in any form whatsoever without
written prior approval by RADVision LTD..

RADVision LTD. reserves the right to revise this publication and make changes
without obligation to notify any person of such revisions or changes.

*/

/******************************************************************************
 *                        RvSipHeader.h                                       *
 *                                                                            *
 * The file defines general methods to handle headers by its types.           *
 *                                                                            *
 *                                                                            *
 *      Author           Date                                                 *
 *     ------           ------------                                          *
 *      Ofra             April 2003                                           *
 ******************************************************************************/

#ifndef RVSIPHEADER_H
#define RVSIPHEADER_H

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

/***************************************************************************
 * RvSipHeaderEncode
 * ------------------------------------------------------------------------
 * General: Encodes a header of any type to a textual header.
 *          The textual header is placed on a page taken from a specified pool.
 *          In order to copy the textual header from the page to a
 *          consecutive buffer, use RPOOL_CopyToExternal().
 * Return Value:
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     pHeader - Handle to the header structure.
 *          eType   - Type of the header to encode.
 *          hPool   - Handle to the specified memory pool.
 * output:  hPage   - The memory page allocated to contain the encoded header.
 *          length  - The length of the encoded information.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipHeaderEncode(IN    void*           pHeader,
                                             IN    RvSipHeaderType eType,
                                             IN    HRPOOL          hPool,
                                             OUT   HPAGE*          hPage,
                                             OUT   RvUint32*      length);

/***************************************************************************
 * RvSipHeaderParse
 * ------------------------------------------------------------------------
 * General: Parses a SIP textual header, of any type into a header object.
 *          All the textual fields are placed inside the object.
 *
 * Return Value: RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hHeader - A handle to the header object.
 *          eType   - Type of the header to parse.
 *          buffer  - Buffer containing a textual header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipHeaderParse(
                                          IN    void*           hHeader,
                                          IN    RvSipHeaderType eType,
                                          IN    RvChar*        buffer);

/***************************************************************************
 * RvSipHeaderParseValue
 * ------------------------------------------------------------------------
 * General: Parses a SIP textual header value, of any header type, into a
 *          header object.
 *          A SIP header has the following grammer:
 *          header-name:header-value. This function takes the header-value part as
 *          a parameter and parses it into the supplied object.
 *          All the textual fields are placed inside the object.
 *          Note: Use the RvSipHeaderParse() function to parse strings that also
 *          include the header-name.
 *
 * Return Value: RvStatus.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     hHeader - The handle to the header object.
 *          eType   - Type of the header to parse.
 *          buffer  - The buffer containing thea textual header.
 ***************************************************************************/
RVAPI RvStatus RVCALLCONV RvSipHeaderParseValue(
                                          IN    void*           hHeader,
                                          IN    RvSipHeaderType eType,
                                          IN    RvChar*        buffer);

/***************************************************************************
 * RvSipHeaderIsBadSyntax
 * ------------------------------------------------------------------------
 * General: Checks if the given header is a "bad-syntax" header or not.
 *          A SIP header has the following grammer:
 *          header-name:header-value. When a header contains a syntax error,
 *          the header-value is kept as a separate "bad-syntax" string.
 *          Use this function to check wether this header contains a "bad-
 *          syntax" string or not..
 *
 * Return Value: RV_TRUE  - if header contains a bad-syntax string.
 *               RV_FALSE - if header does not contain a bad-syntax string.
 *                 If pHeader is NULL the function returns RV_FALSE.
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:     pHeader     - A handle to the header object.
 *          eHeaderType - Type of given header.
 ***************************************************************************/
RVAPI RvBool RVCALLCONV RvSipHeaderIsBadSyntax(IN void*           pHeader,
                                                IN RvSipHeaderType eHeaderType);

#ifdef __cplusplus
}
#endif


#endif /* RVSIPHEADER_H */

