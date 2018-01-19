/***********************************************************************
Filename   : rvtooldefs.h
Description: definitions used by compiler tool configuration headers
************************************************************************
        Copyright (c) 2001 RADVISION Inc. and RADVISION Ltd.
************************************************************************
NOTICE:
This document contains information that is confidential and proprietary
to RADVISION Inc. and RADVISION Ltd.. No part of this document may be
reproduced in any form whatsoever without written prior approval by
RADVISION Inc. or RADVISION Ltd..

RADVISION Inc. and RADVISION Ltd. reserve the right to revise this
publication and make changes without obligation to notify any person of
such revisions or changes.
***********************************************************************/
#ifndef RV_TOOLDEFS_H
#define RV_TOOLDEFS_H

/* Note: Adding a tool requires changing the makefiles too since */
/* these definitions are set in rvbuildconfig.h, which is generated */
/* by the makefiles. */

/* Supported Compiler Tools - list specifics versions below */
#define RV_TOOL_TYPE_GNU 0
#define RV_TOOL_TYPE_SUN 1
#define RV_TOOL_TYPE_DIAB 2
#define RV_TOOL_TYPE_GHS 3
#define RV_TOOL_TYPE_ADS 4
#define RV_TOOL_TYPE_MSVC 5
#define RV_TOOL_TYPE_EMVC 6
#define RV_TOOL_TYPE_CADUL 7
#define RV_TOOL_TYPE_HPUXC 8
#define RV_TOOL_TYPE_COMPAQC 9
#define RV_TOOL_TYPE_MWCCSYM 10

/***** Specific Tool Versions *****/

/* RV_TOOL_TYPE_GNU */
#define RV_TOOL_GNU_CYG_2_7 0
#define RV_TOOL_GNU_2_9 1
#define RV_TOOL_GNU_3_0 2
#define RV_TOOL_GNU_3_2 3
#define RV_TOOL_GNU_3_3 4

/* RV_TOOL_TYPE_SUN */
#define RV_TOOL_SUN_SPARCWORKS_4 0
#define RV_TOOL_SUN_WORKSHOP_5 1
#define RV_TOOL_SUN_FORTE_6 2

/* RV_TOOL_TYPE_DIAB */
#define RV_TOOL_DIAB_4_3 0
#define RV_TOOL_DIAB_5_5 1

/* RV_TOOL_TYPE_GHS */
#define RV_TOOL_GHS_3_0_COMPAT 0
#define RV_TOOL_GHS_3_5 1
#define RV_TOOL_GHS_3_5_COMPAT 2

/* RV_TOOL_TYPE_ADS */
#define RV_TOOL_ADS_1_0 0
#define RV_TOOL_ADS_1_1 1
#define RV_TOOL_ADS_1_2 2

/* RV_TOOL_TYPE_MSVC */
#define RV_TOOL_MSVC_6 0

/* RV_TOOL_TYPE_EMVC */
#define RV_TOOL_EMVC_3 0

/* RV_TOOL_TYPE_COMPAQC */
#define RV_TOOL_COMPAQC_5_6 0
#define RV_TOOL_COMPAQC_6_4 1

/* RV_TOOL_TYPE_CADUL */
#define RV_TOOL_CADUL_7_00x 0

/* RV_TOOL_TYPE_HPUXC */
#define RV_TOOL_HPUXC_A_10_32_20 0
#define RV_TOOL_HPUXC_A_11_01_00 1

/* RV_TOOL_TYPE_MWCCSYM */
#define RV_TOOL_MWCCSYM_2_4_7 0

#endif /* RV_TOOLDEFS_H */
