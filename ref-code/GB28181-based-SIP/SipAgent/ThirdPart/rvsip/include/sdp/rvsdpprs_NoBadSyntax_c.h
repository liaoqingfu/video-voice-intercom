static char empty_str[] = {""};

static RvpStrPtrN CurString_(char * s,int len) {
	RvpStrPtrN x;
	x.buf = s;
	x.len = len;
	return x;
}

static char CurChar_(char * s) {
	return s[0];
}

static unsigned int AsciiToInt(void * pcb_,char * s,int len) {
	unsigned int acc= *(s+len-1)-'0';
	unsigned int digit10,digit,old_acc = acc;
	unsigned int power=1;
	int i;
	
	for(i=len-2;i>=0;i--) {
		digit10 = (*(s+i)-'0')*power;
		digit = digit10*10;
		if(digit/10 != digit10) 
			rvSdpParseSetSemErr(pcb_,"Field too long");
		acc+=digit;
		power*=10;

		if(old_acc>acc) 
			rvSdpParseSetSemErr(pcb_,"Field too long");
		old_acc = acc;
	}
	return acc;	
}


static unsigned int AsciiToInt16(void * pcb_,char * s,int len) {
	unsigned int max = 0xFFFF;
	unsigned int value = AsciiToInt(pcb_,s,len);

	if(value>max)
		rvSdpParseSetSemErr(pcb_,"Field larger than 0xFFFF");

	return value;	
}


/*

 AnaGram Parsing Engine
 Copyright (c) 1993-2000, Parsifal Software.
 All Rights Reserved.

 Serial number 2P20945U
 Registered to:
   James Adragna
   RADVISION, INC.

*/

#ifndef RVSDPPRS_NOBADSYNTAX_H_1094397748
#include "rvsdpprs_NoBadSyntax.h"
#endif

#ifndef RVSDPPRS_NOBADSYNTAX_H_1094397748
#error Mismatched header file
#endif

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define RULE_CONTEXT (&((PCB).cs[(PCB).ssx]))
#define ERROR_CONTEXT ((PCB).cs[(PCB).error_frame_ssx])
#define CONTEXT ((PCB).cs[(PCB).ssx])


#ifndef PCB_TYPE
#define PCB_TYPE rvSdpParser_pcb_type
#endif


#define PCB (*pcb_pointer)
#define PCB_DECL PCB_TYPE *pcb_pointer
#define PCB_POINTER pcb_pointer

#ifndef CONVERT_CASE

static const char agCaseTable[31] = {
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,    0,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
};

static int agConvertCase(int c) {
  if (c >= 'a' && c <= 'z') return c ^= 0x20;
  if (c >= 0xe0 && c < 0xff) c ^= agCaseTable[c-0xe0];
  return c;
}

#define CONVERT_CASE(c) agConvertCase(c)

#endif


#ifndef TAB_SPACING
#define TAB_SPACING 8
#endif

#define ag_rp_1(PCB_POINTER) (CUR_STRING())

static void ag_rp_7(PCB_DECL) {
/* Line 239, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_NoBadSyntax.syn */
 PRS_STATE->cur_line = PRS_STATE->cur_token  = (char*)PCB.pointer; 
}

static void ag_rp_8(PCB_DECL) {
/* Line 240, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_NoBadSyntax.syn */
 PRS_STATE->cur_line = PRS_STATE->cur_token  = (char*)PCB.pointer; 
}

static void ag_rp_9(PCB_DECL) {
/* Line 243, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_NoBadSyntax.syn */
	BEGIN_TOKEN();
}

static void ag_rp_10(PCB_DECL) {
/* Line 244, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_NoBadSyntax.syn */
	BEGIN_TOKEN();
}

#define ag_rp_11(PCB_POINTER) (BEGIN_TOKEN())

#define ag_rp_12(PCB_POINTER) (BEGIN_TOKEN())

#define ag_rp_13(PCB_POINTER) (BEGIN_TOKEN())

#define ag_rp_14(PCB_POINTER) (BEGIN_TOKEN())

#define ag_rp_15(PCB_POINTER) (BEGIN_TOKEN())

#define ag_rp_16(PCB_POINTER) (BEGIN_TOKEN())

#define ag_rp_17(PCB_POINTER) (BEGIN_TOKEN())

#define ag_rp_18(PCB_POINTER) (BEGIN_TOKEN())

#define ag_rp_19(PCB_POINTER) (PRS_STATE->stat = RV_SDPPARSER_STOP_ZERO)

#define ag_rp_20(PCB_POINTER) (PRS_STATE->stat = RV_SDPPARSER_STOP_DOTLINE)

#define ag_rp_21(PCB_POINTER) (PRS_STATE->stat = RV_SDPPARSER_STOP_BLANKLINE)

#define ag_rp_22(PCB_POINTER) (PRS_STATE->stat = RV_SDPPARSER_STOP_CLOSEBRACE)

#define ag_rp_23(PCB_POINTER) (rvSdpParseAuxResetType(PCB_PTR))

#define ag_rp_24(PCB_POINTER) (rvSdpParseAuxSetType(PCB_PTR,SDP_FIELDTYPE_VERSION))

#define ag_rp_25(PCB_POINTER) (rvSdpParseAuxResetType(PCB_PTR))

static void ag_rp_26(PCB_DECL) {
/* Line 408, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_NoBadSyntax.syn */
 
			if(rvSdpMsgSetVersionN(SDP_MSG,TOKEN_START,TOKEN_LENGTH)!=RV_OK) {
				rvSdpParseSetSemErr(&(PCB),"Field too long");
			} 
		
}

static void ag_rp_27(PCB_DECL) {
/* Line 416, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_NoBadSyntax.syn */
rvSdpParseAuxSetType(PCB_PTR,SDP_FIELDTYPE_ORIGIN);
}

static void ag_rp_28(PCB_DECL, RvpStrPtrN u, RvpStrPtrN i, RvpStrPtrN v) {
/* Line 419, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_NoBadSyntax.syn */
			rvSdpParserAuxSetOriginN(PCB_PTR,SDP_MSG,u.buf,u.len,i.buf,i.len,v.buf,v.len);
			
		
}

#define ag_rp_29(PCB_POINTER) (rvSdpParseAuxSetType(PCB_PTR,SDP_FIELDTYPE_SESSION))

#define ag_rp_30(PCB_POINTER, s) (rvSdpParseAuxResetType(PCB_PTR))

#define ag_rp_31(PCB_POINTER, s) (SDPASSERT_MEM2(rvSdpMsgSetSessionNameN(SDP_MSG,s.buf,s.len)))

#define ag_rp_32(PCB_POINTER) (rvSdpParseAuxResetType(PCB_PTR))

#define ag_rp_33(PCB_POINTER) (SDPASSERT_MEM2(rvSdpMsgSetSessionNameN(SDP_MSG,"",0)))

#define ag_rp_34(PCB_POINTER) (rvSdpParseAuxSetType(PCB_PTR,SDP_FIELDTYPE_INFORMATION))

#define ag_rp_35(PCB_POINTER, s) (rvSdpParseAuxResetType(PCB_PTR))

#define ag_rp_36(PCB_POINTER, s) (SDPASSERT_MEM2(rvSdpCommonFieldsSetInformationN(PRS_STATE->cur_sdp_fields,s.buf,s.len)))

#define ag_rp_37(PCB_POINTER) (rvSdpParseAuxResetType(PCB_PTR))

#define ag_rp_38(PCB_POINTER) (SDPASSERT_MEM2(rvSdpCommonFieldsSetInformationN(PRS_STATE->cur_sdp_fields,"",0)))

#define ag_rp_39(PCB_POINTER) (rvSdpParseAuxSetType(PCB_PTR,SDP_FIELDTYPE_URI))

#define ag_rp_40(PCB_POINTER, u) (rvSdpParseAuxSetURI(PCB_PTR,u.buf,u.len))

static void ag_rp_41(PCB_DECL) {
/* Line 441, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_NoBadSyntax.syn */
rvSdpParseAuxSetType(PCB_PTR,SDP_FIELDTYPE_EMAIL);
}

static void ag_rp_42(PCB_DECL) {
/* Line 443, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_NoBadSyntax.syn */
rvSdpParseAuxResetType(PCB_PTR);
}

static void ag_rp_43(PCB_DECL) {
/* Line 448, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_NoBadSyntax.syn */
rvSdpParseAuxSetType(PCB_PTR,SDP_FIELDTYPE_PHONE);
}

#define ag_rp_44(PCB_POINTER) (rvSdpParseAuxSetType(PCB_PTR,SDP_FIELDTYPE_CONNECTION))

#define ag_rp_45(PCB_POINTER) (rvSdpParseAuxResetType(PCB_PTR))

static void ag_rp_46(PCB_DECL) {
/* Line 454, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_NoBadSyntax.syn */
		rvSdpParserAuxSetConnectionN(PCB_PTR);
	
}

static void ag_rp_47(PCB_DECL, RvpStrPtrN a, RvpStrPtrN ca) {
/* Line 460, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_NoBadSyntax.syn */
 
		rvSdpParserAuxSaveAddr(PCB_PTR, "-", 1, a.buf, a.len, ca.buf, ca.len);
	
}

static void ag_rp_48(PCB_DECL, RvpStrPtrN a, RvpStrPtrN ca) {
/* Line 463, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_NoBadSyntax.syn */
 
		rvSdpParserAuxSaveAddr(PCB_PTR, "$", 1, a.buf, a.len, ca.buf, ca.len);
	
}

static void ag_rp_49(PCB_DECL, RvpStrPtrN a, RvpStrPtrN ca) {
/* Line 466, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_NoBadSyntax.syn */
 
		rvSdpParserAuxSaveAddr(PCB_PTR, "IN", 2, a.buf, a.len, ca.buf, ca.len);
	
}

static void ag_rp_50(PCB_DECL, RvpStrPtrN a, RvpStrPtrN ca) {
/* Line 470, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_NoBadSyntax.syn */
 
		rvSdpParserAuxSaveAddr(PCB_PTR, "TN", 2, a.buf, a.len, ca.buf, ca.len);
	
}

static void ag_rp_51(PCB_DECL, RvpStrPtrN a, RvpStrPtrN ca) {
/* Line 473, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_NoBadSyntax.syn */
 
		rvSdpParserAuxSaveAddr(PCB_PTR, "ATM", 3, a.buf, a.len, ca.buf, ca.len);
	
}

static void ag_rp_52(PCB_DECL, RvpStrPtrN ca) {
/* Line 477, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_NoBadSyntax.syn */
 
		rvSdpParserAuxSaveAddr(PCB_PTR, "ATM", 3, "NSAP", 4, ca.buf, ca.len);
	
}

static void ag_rp_53(PCB_DECL, RvpStrPtrN ca) {
/* Line 480, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_NoBadSyntax.syn */
 
		rvSdpParserAuxSaveAddr(PCB_PTR, "ATM", 3, "E164", 4, ca.buf, ca.len);
	
}

static void ag_rp_54(PCB_DECL, RvpStrPtrN ca) {
/* Line 483, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_NoBadSyntax.syn */
 
		rvSdpParserAuxSaveAddr(PCB_PTR, "ATM", 3, "GWID", 4, ca.buf, ca.len);
	
}

static void ag_rp_55(PCB_DECL, RvpStrPtrN ca) {
/* Line 486, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_NoBadSyntax.syn */
 
		rvSdpParserAuxSaveAddr(PCB_PTR, "ATM", 3, "ALIAS", 5, ca.buf, ca.len);
	
}

static void ag_rp_56(PCB_DECL, RvpStrPtrN addr, RvpStrPtrN a) {
/* Line 490, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_NoBadSyntax.syn */
		rvSdpParserAuxSaveAddr(PCB_PTR, "ATM", 3, addr.buf, addr.len, a.buf, a.len);	
	
}

static void ag_rp_57(PCB_DECL, RvpStrPtrN a) {
/* Line 494, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_NoBadSyntax.syn */
 
		rvSdpParserAuxSaveAddr(PCB_PTR, "IN", 2, "IP4", 3, a.buf, a.len);
	
}

static void ag_rp_58(PCB_DECL, RvpStrPtrN a) {
/* Line 497, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_NoBadSyntax.syn */
 
		rvSdpParserAuxSaveAddr(PCB_PTR, "IN", 2, "IP6", 3, a.buf, a.len);
	
}

static void ag_rp_59(PCB_DECL, RvpStrPtrN addr, RvpStrPtrN a) {
/* Line 502, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_NoBadSyntax.syn */
		rvSdpParserAuxSaveAddr(PCB_PTR, "IN", 2, addr.buf, addr.len, a.buf, a.len);	
	
}

static void ag_rp_60(PCB_DECL, RvpStrPtrN a) {
/* Line 505, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_NoBadSyntax.syn */
 
		rvSdpParserAuxSaveAddr(PCB_PTR, "TN", 2, "RFC2543", 7, a.buf, a.len);
	
}

static void ag_rp_61(PCB_DECL, RvpStrPtrN tn, RvpStrPtrN a) {
/* Line 508, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_NoBadSyntax.syn */
 
		rvSdpParserAuxSaveAddr(PCB_PTR, "TN", 2, tn.buf, tn.len, a.buf, a.len);
	
}

static void ag_rp_62(PCB_DECL, RvpStrPtrN n, RvpStrPtrN a) {
/* Line 513, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_NoBadSyntax.syn */
		rvSdpParserAuxSaveAddr(PCB_PTR, n.buf,n.len, "IP4",3, a.buf, a.len);	
	
}

static void ag_rp_63(PCB_DECL, RvpStrPtrN n, RvpStrPtrN a) {
/* Line 516, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_NoBadSyntax.syn */
		rvSdpParserAuxSaveAddr(PCB_PTR, n.buf,n.len, "IP6",3, a.buf, a.len);	
	
}

static void ag_rp_64(PCB_DECL, RvpStrPtrN n, RvpStrPtrN addr, RvpStrPtrN a) {
/* Line 519, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_NoBadSyntax.syn */
		rvSdpParserAuxSaveAddr(PCB_PTR, n.buf,n.len, addr.buf, addr.len, a.buf, a.len);	
	
}

#define ag_rp_96(PCB_POINTER) (rvSdpParseAuxSetType(PCB_PTR,SDP_FIELDTYPE_BANDWIDTH))

#define ag_rp_97(PCB_POINTER, t, b) (rvSdpParseAuxSetBandwidth(PCB_PTR,t.buf,t.len,b))

#define ag_rp_98(PCB_POINTER) (rvSdpParseAuxSetType(PCB_PTR,SDP_FIELDTYPE_TIME))

#define ag_rp_99(PCB_POINTER) (rvSdpParseAuxResetType(PCB_PTR))

#define ag_rp_100(PCB_POINTER) (rvSdpParseAuxResetType(PCB_PTR))

static void ag_rp_101(PCB_DECL) {
/* Line 592, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_NoBadSyntax.syn */
rvSdpParseAuxResetType(PCB_PTR);rvSdpParseAuxClearRepeat(PCB_PTR);
}

#define ag_rp_102(PCB_POINTER, start, stop) (rvSdpParseAuxAddSessionTime(PCB_PTR,start,stop))

#define ag_rp_103(PCB_POINTER) (rvSdpParseAuxSetType(PCB_PTR,SDP_FIELDTYPE_REPEAT))

#define ag_rp_104(PCB_POINTER, t) (rvSdpParseAuxAddSessionRepeatField(PCB_PTR,t))

#define ag_rp_105(PCB_POINTER, t) (rvSdpParseAuxSetRepeatActiveDuration(PCB_PTR,t))

#define ag_rp_106(PCB_POINTER, t) (rvSdpParseAuxAddRepeatOffset(PCB_PTR,t))

#define ag_rp_107(PCB_POINTER, t, tt) (rvSdpParseAuxAddZoneAdjustment(PCB_PTR,t,tt.time,tt.type))

#define ag_rp_108(PCB_POINTER, t, tt) (rvSdpParseAuxAddZoneAdjustment(PCB_PTR,t,tt.time*(-1),tt.type))

#define ag_rp_109(PCB_POINTER) (rvSdpParseAuxSetType(PCB_PTR,SDP_FIELDTYPE_KEY))

#define ag_rp_110(PCB_POINTER) (rvSdpParseAuxResetType(PCB_PTR))

#define ag_rp_111(PCB_POINTER, t) (rvSdpParserAuxSetKeyN(PCB_PTR,t,empty_str,0))

#define ag_rp_112(PCB_POINTER, t) (rvSdpParserAuxSetKeyN(PCB_PTR,t,empty_str,0))

#define ag_rp_113(PCB_POINTER, t, d) (rvSdpParserAuxSetKeyN(PCB_PTR,t,d.buf,d.len))

#define ag_rp_116(PCB_POINTER) (rvSdpParseAuxSetType(PCB_PTR,SDP_FIELDTYPE_ATTRIBUTE))

#define ag_rp_117(PCB_POINTER, f, v) (rvSdpParseAuxResetType(PCB_PTR))

#define ag_rp_118(PCB_POINTER, f, v) (SDPASSERT_MEM(rvSdpCommonFieldsAddAttrN(PRS_STATE->cur_sdp_fields,f.buf,f.len,v.buf,v.len,PRS_ALLOC)))

#define ag_rp_119(PCB_POINTER, f) (rvSdpParseAuxResetType(PCB_PTR))

#define ag_rp_120(PCB_POINTER, f) (SDPASSERT_MEM(rvSdpCommonFieldsAddAttrN(PRS_STATE->cur_sdp_fields,f.buf,f.len,"",0,PRS_ALLOC)))

#define ag_rp_121(PCB_POINTER) (rvSdpParseAuxSetType(PCB_PTR,SDP_FIELDTYPE_RTP_MAP))

#define ag_rp_122(PCB_POINTER, p, n) (rvSdpParseAuxResetType(PCB_PTR))

#define ag_rp_123(PCB_POINTER, p, n) (SDPASSERT_MEM(rvSdpParseAuxAddRtpMap(PCB_PTR,p,n.buf,n.len,8000)))

#define ag_rp_124(PCB_POINTER, p, n, r) (rvSdpParseAuxResetType(PCB_PTR))

#define ag_rp_125(PCB_POINTER, p, n, r) (SDPASSERT_MEM(rvSdpParseAuxAddRtpMap(PCB_PTR,p,n.buf,n.len,r)))

#define ag_rp_126(PCB_POINTER, p, n, r, pr) (rvSdpParseAuxResetType(PCB_PTR))

static void ag_rp_127(PCB_DECL, int p, RvpStrPtrN n, int r, RvpStrPtrN pr) {
/* Line 666, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_NoBadSyntax.syn */
			RvSdpRtpMap * m = rvSdpParseAuxAddRtpMap(PCB_PTR,p,n.buf,n.len,r);
			
			if(SDPASSERT_MEM(m)!=NULL) {
				SDPASSERT_MEM2(rvSdpRtpMapSetEncodingParametersN(m,pr.buf,pr.len));
			}
		
}

#define ag_rp_128(PCB_POINTER) (rvSdpParseAuxResetType(PCB_PTR))

#define ag_rp_129(PCB_POINTER) (SDPASSERT_MEM2(rvSdpCommonFieldsSetConnectionMode(PRS_STATE->cur_sdp_fields,RV_SDPCONNECTMODE_SENDRECV)))

#define ag_rp_130(PCB_POINTER) (rvSdpParseAuxResetType(PCB_PTR))

#define ag_rp_131(PCB_POINTER) (SDPASSERT_MEM2(rvSdpCommonFieldsSetConnectionMode(PRS_STATE->cur_sdp_fields,RV_SDPCONNECTMODE_SENDONLY)))

#define ag_rp_132(PCB_POINTER) (rvSdpParseAuxResetType(PCB_PTR))

#define ag_rp_133(PCB_POINTER) (SDPASSERT_MEM2(rvSdpCommonFieldsSetConnectionMode(PRS_STATE->cur_sdp_fields,RV_SDPCONNECTMODE_RECVONLY)))

static void ag_rp_134(PCB_DECL, RvpStrPtrN t) {
/* Line 676, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_NoBadSyntax.syn */
rvSdpParseAuxResetType(PCB_PTR);SDPASSERT_MEM(rvSdpCommonFieldsAddAttrN(PRS_STATE->cur_sdp_fields,"recvonly",0,t.buf,t.len,PRS_ALLOC));
}

static void ag_rp_135(PCB_DECL, RvpStrPtrN t) {
/* Line 677, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_NoBadSyntax.syn */
rvSdpParseAuxResetType(PCB_PTR);SDPASSERT_MEM(rvSdpCommonFieldsAddAttrN(PRS_STATE->cur_sdp_fields,"sendrecv",0,t.buf,t.len,PRS_ALLOC));
}

static void ag_rp_136(PCB_DECL, RvpStrPtrN t) {
/* Line 678, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_NoBadSyntax.syn */
rvSdpParseAuxResetType(PCB_PTR);SDPASSERT_MEM(rvSdpCommonFieldsAddAttrN(PRS_STATE->cur_sdp_fields,"sendonly",0,t.buf,t.len,PRS_ALLOC));
}

#define ag_rp_137(PCB_POINTER) (CUR_INT())

#define ag_rp_139(PCB_POINTER) (CUR_INT())

#define ag_rp_141(PCB_POINTER) (rvSdpParseAuxResetType(PCB_PTR))

#define ag_rp_142(PCB_POINTER) (rvSdpParseAuxResetType(PCB_PTR))

#define ag_rp_143(PCB_POINTER) (rvSdpParseAuxResetType(PCB_PTR))

#define ag_rp_144(PCB_POINTER) (rvSdpParseAuxResetType(PCB_PTR))

#define ag_rp_145(PCB_POINTER) (rvSdpParseAuxResetType(PCB_PTR))

#define ag_rp_146(PCB_POINTER) (rvSdpParseAuxResetType(PCB_PTR))

#define ag_rp_147(PCB_POINTER) (PRS_STATE->stat =RV_SDPPARSER_PARSING_MEDIA )

#define ag_rp_148(PCB_POINTER) (rvSdpParseAuxSetType(PCB_PTR,SDP_FIELDTYPE_MEDIA))

#define ag_rp_149(PCB_POINTER) (rvSdpParseAuxResetType(PCB_PTR))

static void ag_rp_150(PCB_DECL) {
/* Line 719, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_NoBadSyntax.syn */
rvSdpParseAuxClearCurMediaDescr(PCB_PTR);
}

#define ag_rp_151(PCB_POINTER) (rvSdpParseAuxResetType(PCB_PTR))

static void ag_rp_152(PCB_DECL) {
/* Line 720, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_NoBadSyntax.syn */
rvSdpParseAuxClearCurMediaDescr(PCB_PTR);
}

static void ag_rp_153(PCB_DECL, RvpStrPtrN m, int p, int sp, RvpStrPtrN pt) {
/* Line 724, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_NoBadSyntax.syn */
 rvSdpParseAuxAddSdpMedia(PCB_PTR,m,p,sp,pt); 
}

static void ag_rp_154(PCB_DECL, RvpStrPtrN m, int p, RvpStrPtrN pt) {
/* Line 725, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_NoBadSyntax.syn */
 rvSdpParseAuxAddSdpMedia(PCB_PTR,m,p,RV_SDPFIELD_NOTSET,pt); 
}

#define ag_rp_155(PCB_POINTER, am) (rvSdpParseAuxAddSdpMediaNAS(PCB_PTR,RV_SDPPORT_NOTSET,RV_SDPFIELD_NOTSET,am.buf,am.len))

#define ag_rp_156(PCB_POINTER, am, p) (rvSdpParseAuxAddSdpMediaNAS(PCB_PTR,p,RV_SDPFIELD_NOTSET,am.buf,am.len))

#define ag_rp_157(PCB_POINTER, am, p, sp) (rvSdpParseAuxAddSdpMediaNAS(PCB_PTR,p,sp,am.buf,am.len))

#define ag_rp_160(PCB_POINTER) (CUR_INT16())

#define ag_rp_161(PCB_POINTER) (RV_SDPPORT_ANY)

#define ag_rp_162(PCB_POINTER) (RV_SDPPORT_IGNORE)

#define ag_rp_163(PCB_POINTER) (RV_SDPPORT_ATM)

#define ag_rp_164(PCB_POINTER) (CUR_INT())

#define ag_rp_165(PCB_POINTER) (rvSdpParseAuxAddMediaDescrFormatN(PCB_PTR,TOKEN_START,TOKEN_LENGTH))

#define ag_rp_173(PCB_POINTER, a) (a)

#define ag_rp_179(PCB_POINTER) (PRS_STATE->ttl = CUR_INT())

#define ag_rp_180(PCB_POINTER) (PRS_STATE->num_addr = CUR_INT())

#define ag_rp_181(PCB_POINTER, t) (t)

#define ag_rp_182(PCB_POINTER) (0)

#define ag_rp_183(PCB_POINTER, t) (t)

#define ag_rp_184(PCB_POINTER) (0)

#define ag_rp_185(PCB_POINTER) (CUR_INT())

#define ag_rp_186(PCB_POINTER) (CUR_INT())

static RvSdpTypedTime ag_rp_187(PCB_DECL, unsigned int t) {
/* Line 880, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_NoBadSyntax.syn */
			RvSdpTypedTime ttime;
			ttime.time = t;
			ttime.type = RV_SDPTIMETYPE_SECOND;
            RV_UNUSED_ARG(pcb_pointer);
			return ttime;
		
}

static RvSdpTypedTime ag_rp_188(PCB_DECL, unsigned int t, short type) {
/* Line 887, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_NoBadSyntax.syn */
			RvSdpTypedTime ttime;
			ttime.time = t;
			ttime.type = (RvSdpTimeUnit)type;
            RV_UNUSED_ARG(pcb_pointer);
			return ttime;
		
}

#define ag_rp_189(PCB_POINTER) (RV_SDPTIMETYPE_DAY)

#define ag_rp_190(PCB_POINTER) (RV_SDPTIMETYPE_HOUR)

#define ag_rp_191(PCB_POINTER) (RV_SDPTIMETYPE_MONTH)

#define ag_rp_192(PCB_POINTER) (RV_SDPTIMETYPE_SECOND)

#define ag_rp_194(PCB_POINTER) (CUR_INT())

#define ag_rp_196(PCB_POINTER, e) (SDPASSERT_MEM(rvSdpMsgAddEmailN(SDP_MSG,e.buf,e.len,"",0)))

#define ag_rp_197(PCB_POINTER, e, s) (SDPASSERT_MEM(rvSdpMsgAddEmailN(SDP_MSG,e.buf,e.len,s.buf,s.len)))

#define ag_rp_198(PCB_POINTER, s, e) (SDPASSERT_MEM(rvSdpMsgAddEmailN(SDP_MSG,e.buf,e.len,s.buf,s.len)))

static void ag_rp_201(PCB_DECL, RvpStrPtrN p) {
/* Line 1003, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_NoBadSyntax.syn */
rvSdpParseAuxResetType(PCB_PTR);rvSdpParseAuxAddPhone(PCB_PTR,p.buf,p.len,"",0);
}

static void ag_rp_202(PCB_DECL, RvpStrPtrN p, RvpStrPtrN s) {
/* Line 1004, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_NoBadSyntax.syn */
rvSdpParseAuxResetType(PCB_PTR);rvSdpParseAuxAddPhone(PCB_PTR,p.buf,p.len,s.buf,s.len);	
}

static void ag_rp_203(PCB_DECL, RvpStrPtrN s, RvpStrPtrN p) {
/* Line 1005, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_NoBadSyntax.syn */
rvSdpParseAuxResetType(PCB_PTR),rvSdpParseAuxAddPhone(PCB_PTR,p.buf,p.len,s.buf,s.len);
}

#define ag_rp_213(PCB_POINTER, g) (rvSdpParserAuxSaveVcId(PCB_PTR, RV_SDPVCID_VCCI, g.buf, g.len))

#define ag_rp_214(PCB_POINTER, g) (rvSdpParserAuxSaveVcId(PCB_PTR, RV_SDPVCID_CID, g.buf, g.len))

#define ag_rp_215(PCB_POINTER, g) (rvSdpParserAuxSaveVcId(PCB_PTR, RV_SDPVCID_BCG, g.buf, g.len))

#define ag_rp_216(PCB_POINTER, g) (rvSdpParserAuxSaveVcId(PCB_PTR, RV_SDPVCID_PORT, g.buf, g.len))

#define ag_rp_217(PCB_POINTER, g) (rvSdpParserAuxSaveVcId(PCB_PTR, RV_SDPVCID_VPI, g.buf, g.len))

#define ag_rp_218(PCB_POINTER, g) (rvSdpParserAuxSaveVcId(PCB_PTR, RV_SDPVCID_VCI, g.buf, g.len))

#define ag_rp_219(PCB_POINTER, g) (rvSdpParserAuxSaveVcId(PCB_PTR, RV_SDPVCID_VPCI, g.buf, g.len))

#define ag_rp_220(PCB_POINTER, g) (rvSdpParserAuxSaveVcId(PCB_PTR, RV_SDPVCID_NSAP, g.buf, g.len))

#define ag_rp_221(PCB_POINTER) (rvSdpParserAuxSaveVcId(PCB_PTR, RV_SDPVCID_NSAP, "$", 1))

#define ag_rp_222(PCB_POINTER, g) (rvSdpParserAuxSaveVcId(PCB_PTR, RV_SDPVCID_E164, g.buf, g.len))

#define ag_rp_223(PCB_POINTER) (rvSdpParserAuxSaveVcId(PCB_PTR, RV_SDPVCID_E164, "$", 1))

#define ag_rp_224(PCB_POINTER, g) (rvSdpParserAuxSaveVcId(PCB_PTR, RV_SDPVCID_GWID, g.buf, g.len))

#define ag_rp_225(PCB_POINTER) (rvSdpParserAuxSaveVcId(PCB_PTR, RV_SDPVCID_GWID, "$", 1))

#define ag_rp_226(PCB_POINTER, g) (rvSdpParserAuxSaveVcId(PCB_PTR, RV_SDPVCID_ALIAS, g.buf, g.len))

#define ag_rp_227(PCB_POINTER) (rvSdpParserAuxSaveVcId(PCB_PTR, RV_SDPVCID_ALIAS, "$", 1))


#define READ_COUNTS 
#define WRITE_COUNTS 
#undef V
#define V(i,t) (*(t *) (&(PCB).vs[(PCB).ssx + i]))
#undef VS
#define VS(i) (PCB).vs[(PCB).ssx + i]

#ifndef GET_CONTEXT
#define GET_CONTEXT CONTEXT = (PCB).input_context
#endif

typedef enum {
  ag_action_1,
  ag_action_2,
  ag_action_3,
  ag_action_4,
  ag_action_5,
  ag_action_6,
  ag_action_7,
  ag_action_8,
  ag_action_9,
  ag_action_10,
  ag_action_11,
  ag_action_12
} ag_parser_action;

#ifndef NULL_VALUE_INITIALIZER
#define NULL_VALUE_INITIALIZER = { 0 }
#endif


static rvSdpParser_vs_type const ag_null_value NULL_VALUE_INITIALIZER;

static const unsigned char ag_rpx[] = {
    0,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  1,
    1,  1,  0,  0,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13,  0,  0,
    0,  0,  0,  0, 14, 15, 16, 17,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   18, 19, 20,  0, 21,  0, 22, 23, 24,  0, 25, 26, 27, 28, 29,  0, 30, 31,
   32, 33, 34, 35,  0, 36, 37,  0, 38,  0, 39, 40, 41, 42, 43, 44, 45, 46,
   47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59,  1,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  1,  1,  1,  1,  1,  1,  1,
    0,  0,  1,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  1, 60,
   61, 62,  0,  0,  0,  0,  0,  0, 63,  0, 64,  0, 65,  0,  0,  0,  0, 66,
   67,  0,  0,  0,  0, 68, 69, 70,  0,  0,  0,  0,  0,  0, 71, 72, 73, 74,
    0, 75, 76, 77,  1,  0,  0,  0,  0,  1, 78,  0,  0,  0, 79, 80, 81, 82,
   83,  0, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99,
    0,  0,  0,  1,100,  0,  0,  1,101,  0,  0,  0,  0,  0,  0,  0,  0,102,
    0,103,  0,104,  0,105,  0,106,107,108,  0,109,110,111,112,113,114,115,
  116,117,  0,  0,  0,  0,  0,  0,  0,  1,  1,118,119,120,  0,121,122,  0,
    0,123,  0,  0,  0,  1,  1,  1,  0,  0,  1,  0,  0,  0,  0,  0,  1,  0,
    0,  0,  1,  0,  1,124,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    1,  1,  0,  0,  0,125,126,127,128,129,130,131,  0,  0,  0,132,133,134,
  135,136,137,138,  0,  0,  0,  1,139,  0,  0,  1,140,141,142,  1,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,143,144,145,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  1,  0,  0,  1,  0,  0,  0,  0,  0,  1,  1,  0,
    0,  1,  0,  0,  1,  0,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,
    0,  0,  1,  1,  1,  0,  0,  1,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,
    1,  0,  0,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1
};

static const unsigned char ag_key_itt[] = {
 0
};

static const unsigned short ag_key_pt[] = {
0
};

static const unsigned char ag_key_ch[] = {
    0, 76, 84,255, 52, 54,255, 78, 80,255, 65, 83,255, 69, 70, 84,255, 79,
   82,255, 68,255, 78,255, 69,255, 36, 37, 43, 45, 48, 58, 65, 69, 71, 73,
   78, 82, 83, 84,255, 43,255, 34,255, 48,255, 69, 84,255, 79, 82,255, 68,
  255, 78,255, 69,255, 82, 83,255, 65, 73, 84,255, 46, 64,255, 34, 92,255,
   64,255, 91,255, 78,255, 68, 72, 77, 83,255, 92, 93,255, 46,255, 37, 58,
  255, 58,255, 52, 54,255, 80,255, 73,255, 52, 54,255, 80,255, 65, 69, 71,
   73, 78,255, 82,255, 45,255, 93,255, 37, 43, 47, 63,255,126,255, 47, 63,
  255, 63,255, 37,255, 36, 45,255, 36, 45, 58,255, 37, 43,255, 45,255, 83,
  255, 65,255, 73,255, 76,255, 45,255, 52,255, 54,255, 49,255, 45,255, 68,
  255, 73,255, 87,255, 45,255, 80,255, 65,255, 83,255, 67, 80,255, 65, 66,
   69, 71, 78, 80, 86,255, 58,255, 48,255, 67, 80,255, 86,255, 86,255, 86,
  255, 67, 80,255, 86,255, 67,255, 49, 50, 53,255, 76,255, 65,255, 65, 72,
   82,255, 69, 84,255, 65, 67, 73,255
};

static const unsigned char ag_key_act[] = {
  0,3,3,4,0,0,4,0,2,4,3,3,4,3,3,3,4,3,3,4,2,4,2,4,2,4,0,0,0,0,0,3,2,3,3,
  2,2,2,2,3,4,0,4,0,4,0,4,3,3,4,3,3,4,2,4,2,4,2,4,2,2,4,3,3,3,4,0,0,4,0,
  0,4,0,4,0,4,3,4,0,0,0,0,4,0,0,4,0,4,0,0,4,0,4,0,0,4,2,4,2,4,0,0,4,2,4,
  3,3,3,2,3,4,3,4,0,4,0,4,0,0,0,0,4,0,4,0,0,4,0,4,0,4,0,0,4,0,0,3,4,0,0,
  4,3,4,1,4,2,4,2,4,2,4,3,4,1,4,2,4,2,4,3,4,1,4,2,4,2,4,3,4,1,4,2,4,2,4,
  3,3,4,2,3,2,2,2,3,2,4,3,4,3,4,3,3,4,2,4,3,4,3,4,3,3,4,2,4,3,4,3,3,3,4,
  2,4,2,4,2,3,3,4,3,3,4,3,3,2,4
};

static const unsigned short ag_key_parm[] = {
    0,134,127,  0,137,139,  0,125,  0,  0,264,128,  0,231,141,217,  0,229,
  227,  0,  0,  0,  0,  0,  0,  0,146,385,378, 53,318,304,  0,130,132,  0,
    0,  0,  0,126,  0,378,  0,363,  0,318,  0,231,217,  0,229,227,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,127,125,126,  0,336,333,  0,363,361,  0,
  333,  0,352,  0,264,  0,323,324,325,326,  0,361,358,  0,336,  0,385,369,
    0,369,  0,137,139,  0,  0,  0,  0,  0,137,139,  0,  0,  0,134,130,132,
    0,128,  0,141,  0, 53,  0,358,  0,385,378,376,371,  0,205,  0,376,371,
    0,371,  0,385,  0,146, 53,  0,146, 53,304,  0,385,378,  0,436,  0,134,
    0,  0,  0,  0,  0,  0,  0,434,  0,130,  0,  0,  0,  0,  0,435,  0,132,
    0,  0,  0,  0,  0,433,  0,128,  0,  0,  0,  0,  0,422,432,  0,  0,426,
    0,  0,  0,427,  0,  0,304,  0,437,  0,422,432,  0,  0,  0,431,  0,429,
    0,422,429,  0,  0,  0,424,  0,454,456,457,  0,  0,  0,  0,  0,  0,459,
  458,  0,463,461,  0,460,462,  0,  0
};

static const unsigned char ag_key_jmp[] = {
    0,  2,  6,  0,  0,  0,  0,  0,  4,  0, 16, 18,  0, 21, 28, 34,  0, 39,
   43,  0, 17,  0, 20,  0, 22,  0,  0,  0,  0,  0,  0,  0,  1,  8, 12,  7,
   10, 13, 24, 47,  0,  0,  0,  0,  0,  0,  0, 49, 56,  0, 61, 65,  0, 50,
    0, 53,  0, 55,  0, 47, 57,  0, 69, 72, 74,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0, 76,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0, 93,  0, 96,  0,  0,  0,  0,100,  0, 79, 84, 88,
  103, 92,  0, 96,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,103,  0,  0,  0,  0,105,  0,141,
    0,143,  0,145,  0,147,  0,110,  0,151,  0,153,  0,155,  0,112,  0,159,
    0,161,  0,163,  0,114,  0,167,  0,169,  0,171,  0,120,123,  0,149,107,
  157,165,173,116,175,  0,126,  0,128,  0,130,133,  0,190,  0,136,  0,139,
    0,142,145,  0,199,  0,147,  0,150,152,154,  0,206,  0,210,  0,212,156,
  162,  0,179,183,  0,169,173,218,  0
};

static const unsigned char ag_key_index[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0, 26,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0, 41, 43,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   45, 59,  0,  0, 62, 41, 66, 69,  0, 66, 66, 72,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0, 45, 59,  0,  0, 62,  0,  0,  0,  0, 66,
    0, 43,  0, 43, 66, 66,  0, 74, 43,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0, 76, 78,  0,  0,  0, 45, 45,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 41,  0,  0,  0,  0, 66, 83,
   86,  0,  0, 88, 91,  0,  0,  0,  0,  0,  0, 76, 78,  0,  0, 45, 45,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 98,  0,105,  0,111,  0, 98,
    0,  0,  0, 41,113,  0, 83,115, 74, 86,  0,  0,  0, 88,117,  0,  0,  0,
    0, 76,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,122,
    0,  0, 98,105,111, 98,  0,  0,  0,  0,113,  0,  0,  0,  0,117,124,124,
  127,  0,  0,  0, 76,  0,  0,  0,  0,  0, 45,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,122,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,117,117,129,  0,  0,  0,
    0,  0,  0,  0,  0,  0, 45,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  131,131,131,131,131,  0,129,131,131,  0,134,131,131,131,131,  0,138,  0,
    0,178,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  131,131,131,131,131,129,131,131,  0,134,131,131,131,131,  0,129,  0,  0,
    0,  0,113,113,113,113,113,113,113,113,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,113,  0,  0,  0,  0,  0,  0,  0,  0,129,  0,  0,  0,
    0,  0,  0,  0,186,186,  0,  0, 62,  0,  0,  0,  0,  0,188,188,188,188,
  193,195,197,202,204,214,  0,  0,  0,  0,  0, 78,  0,  0,  0,  0,  0,  0,
    0,  0,186,186,186,  0,  0,  0,  0,  0, 62,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,113,  0,113,  0,  0,  0,113,221,221,221,  0,  0,  0,  0,
    0,  0,  0,  0,  0,186,  0,186,  0,186,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,195,204,188,204,188,195,195,204,188,  0,
  113,214,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,204,  0,
  204,204,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
};

static const unsigned char ag_key_ends[] = {
58,0, 73,65,83,0, 77,0, 49,54,52,0, 87,73,68,0, 83,0, 65,80,0, 
67,86,79,78,76,89,0, 67,50,53,52,51,0, 80,77,65,80,0, 78,76,89,0, 
69,67,86,0, 78,0, 67,86,79,78,76,89,0, 80,77,65,80,0, 78,76,89,0, 
69,67,86,0, 84,77,0, 78,0, 78,0, 65,83,0, 76,73,65,83,0, 
49,54,52,0, 87,73,68,0, 83,65,80,0, 70,67,50,53,52,51,0, 58,0, 
36,0, 67,71,0, 36,0, 36,0, 36,0, 79,82,84,0, 67,73,0, 67,73,0, 
58,0, 88,0, 67,73,0, 67,73,0, 67,73,0, 80,73,0, 67,73,0, 73,0, 
73,68,0, 47,0, 47,0, 47,0, 51,50,51,67,45,0, 
84,80,47,65,86,80,0, 84,77,70,0, 85,83,84,79,77,0, 69,69,58,0, 
85,0, 
};

#define AG_TCV(x) ag_tcv[(x)]

static const unsigned short ag_tcv[] = {
   59,464,464,464,464,464,464,464,464, 37, 31,464,464, 30,464,464,464,464,
  464,464,464,464,464,464,464,464,464,464,464,464,464,464, 36,465,466,467,
  124,468,469,470, 41, 43,471,405,472,121, 60, 39, 13, 11, 12, 14, 15, 17,
  473,473,473,473, 49,474, 45, 51, 47,475,476,208,163,118,477,112,308,478,
  478,102,478,198,478,250,478, 92,116,478,184, 97,167,107, 86,478,409,478,
  192,479,480,479,467,481,467,208,163,118,477,112,308,478,478,102,478,198,
  478,250,478, 92,116,478,184, 97,167,107, 86,478,409,478,192,467,467, 61,
  467,482,482,482,482,482,482,482,482,482,482,482,482,482,482,482,482,482,
  482,482,482,482,482,482,482,482,482,482,482,482,482,482,482,482,482,482,
  482,482,482,482,482,482,482,482,482,482,482,482,482,482,482,482,482,482,
  482,482,482,482,482,482,482,482,482,482,482,482,482,482,482,482,482,482,
  482,482,482,482,482,482,482,482,482,482,482,482,482,482,482,482,482,482,
  482,482,482,482,482,482,482,482,482,482,482,482,482,482,482,482,482,482,
  482,482,482,482,482,482,482,482,482,482,482,482,482,482,482,482,482,482,
  482,482,482,482
};

#ifndef SYNTAX_ERROR
#define SYNTAX_ERROR fprintf(stderr,"%s, line %d, column %d\n", \
  (PCB).error_message, (PCB).line, (PCB).column)
#endif

#ifndef FIRST_LINE
#define FIRST_LINE 1
#endif

#ifndef FIRST_COLUMN
#define FIRST_COLUMN 1
#endif

#ifndef PARSER_STACK_OVERFLOW
#define PARSER_STACK_OVERFLOW {fprintf(stderr, \
   "\nParser stack overflow, line %d, column %d\n",\
   (PCB).line, (PCB).column);}
#endif

#ifndef REDUCTION_TOKEN_ERROR
#define REDUCTION_TOKEN_ERROR {fprintf(stderr, \
    "\nReduction token error, line %d, column %d\n", \
    (PCB).line, (PCB).column);}
#endif


#ifndef INPUT_CODE
#define INPUT_CODE(T) (T)
#endif

typedef enum
  {ag_accept_key, ag_set_key, ag_jmp_key, ag_end_key, ag_no_match_key,
   ag_cf_accept_key, ag_cf_set_key, ag_cf_end_key} key_words;

static void ag_get_key_word(PCB_DECL, int ag_k) {
  int ag_save = (int) ((PCB).la_ptr - (PCB).pointer);
  const  unsigned char *ag_p;
  int ag_ch;
  while (1) {
    switch (ag_key_act[ag_k]) {
    case ag_cf_end_key: {
      const  unsigned char *sp = ag_key_ends + ag_key_jmp[ag_k];
      do {
        if ((ag_ch = *sp++) == 0) {
          int ag_k1 = ag_key_parm[ag_k];
          int ag_k2 = ag_key_pt[ag_k1];
          if (ag_key_itt[ag_k2 + CONVERT_CASE(*(PCB).la_ptr)]) goto ag_fail;
          (PCB).token_number = (rvSdpParser_token_type) ag_key_pt[ag_k1 + 1];
          return;
        }
      } while (CONVERT_CASE(*(PCB).la_ptr++) == ag_ch);
      goto ag_fail;
    }
    case ag_end_key: {
      const  unsigned char *sp = ag_key_ends + ag_key_jmp[ag_k];
      do {
        if ((ag_ch = *sp++) == 0) {
          (PCB).token_number = (rvSdpParser_token_type) ag_key_parm[ag_k];
          return;
        }
      } while (CONVERT_CASE(*(PCB).la_ptr++) == ag_ch);
    }
    case ag_no_match_key:
ag_fail:
      (PCB).la_ptr = (PCB).pointer + ag_save;
      return;
    case ag_cf_set_key: {
      int ag_k1 = ag_key_parm[ag_k];
      int ag_k2 = ag_key_pt[ag_k1];
      ag_k = ag_key_jmp[ag_k];
      if (ag_key_itt[ag_k2 + CONVERT_CASE(*(PCB).la_ptr)]) break;
      ag_save = (int) ((PCB).la_ptr - (PCB).pointer);
      (PCB).token_number = (rvSdpParser_token_type) ag_key_pt[ag_k1+1];
      break;
    }
    case ag_set_key:
      ag_save = (int) ((PCB).la_ptr - (PCB).pointer);
      (PCB).token_number = (rvSdpParser_token_type) ag_key_parm[ag_k];
    case ag_jmp_key:
      ag_k = ag_key_jmp[ag_k];
      break;
    case ag_accept_key:
      (PCB).token_number = (rvSdpParser_token_type) ag_key_parm[ag_k];
      return;
    case ag_cf_accept_key: {
      int ag_k1 = ag_key_parm[ag_k];
      int ag_k2 = ag_key_pt[ag_k1];
      if (ag_key_itt[ag_k2 + CONVERT_CASE(*(PCB).la_ptr)])
        (PCB).la_ptr = (PCB).pointer + ag_save;
      else (PCB).token_number = (rvSdpParser_token_type) ag_key_pt[ag_k1+1];
      return;
    }
    }
    ag_ch = CONVERT_CASE(*(PCB).la_ptr++);
    ag_p = &ag_key_ch[ag_k];
    while (*ag_p < ag_ch) ag_p++;
    if (*ag_p != ag_ch) {
      (PCB).la_ptr = (PCB).pointer + ag_save;
      return;
    }
    ag_k = (int) (ag_p - ag_key_ch);
  }
}


#ifndef AG_NEWLINE
#define AG_NEWLINE 10
#endif

#ifndef AG_RETURN
#define AG_RETURN 13
#endif

#ifndef AG_FORMFEED
#define AG_FORMFEED 12
#endif

#ifndef AG_TABCHAR
#define AG_TABCHAR 9
#endif

static void ag_track(PCB_DECL) {
  int ag_k = (int) ((PCB).la_ptr - (PCB).pointer);
  while (ag_k--) {
    switch (*(PCB).pointer++) {
    case AG_NEWLINE:
      (PCB).column = 1, (PCB).line++;
    case AG_RETURN:
    case AG_FORMFEED:
      break;
    case AG_TABCHAR:
      (PCB).column += (TAB_SPACING) - ((PCB).column - 1) % (TAB_SPACING);
      break;
    default:
      (PCB).column++;
    }
  }
}


static void ag_prot(PCB_DECL) {
  int ag_k = 43 - ++(PCB).btsx;
  if (ag_k <= (PCB).ssx) {
    (PCB).exit_flag = AG_STACK_ERROR_CODE;
    PARSER_STACK_OVERFLOW;
    return;
  }
  (PCB).bts[(PCB).btsx] = (PCB).sn;
  (PCB).bts[ag_k] = (PCB).ssx;
  (PCB).vs[ag_k] = (PCB).vs[(PCB).ssx];
  (PCB).ss[ag_k] = (PCB).ss[(PCB).ssx];
}

static void ag_undo(PCB_DECL) {
  if ((PCB).drt == -1) return;
  while ((PCB).btsx) {
    int ag_k = 43 - (PCB).btsx;
    (PCB).sn = (PCB).bts[(PCB).btsx--];
    (PCB).ssx = (PCB).bts[ag_k];
    (PCB).vs[(PCB).ssx] = (PCB).vs[ag_k];
    (PCB).ss[(PCB).ssx] = (PCB).ss[ag_k];
  }
  (PCB).token_number = (rvSdpParser_token_type) (PCB).drt;
  (PCB).ssx = (PCB).dssx;
  (PCB).sn = (PCB).dsn;
  (PCB).drt = -1;
}


static const unsigned short ag_tstt[] = {
86,36,31,30,0,1,29,62,63,64,
31,0,
36,31,30,0,29,62,
86,0,65,85,
86,0,
250,208,198,167,163,118,116,112,107,102,97,92,61,60,59,31,30,0,66,67,68,69,
  74,75,76,77,78,79,80,81,82,83,84,90,110,114,173,
51,37,36,0,87,
51,37,36,0,168,
51,37,36,0,209,
51,37,36,0,199,
51,37,36,0,164,
51,37,36,0,119,
51,37,36,0,35,54,55,56,57,115,
51,37,36,0,35,54,55,56,57,111,
51,37,36,0,108,
51,37,36,0,103,
51,37,36,0,98,
51,37,36,0,35,54,55,56,57,91,
208,198,167,163,118,116,112,107,102,97,92,0,66,67,74,75,76,77,78,79,80,81,
  82,83,84,90,110,114,173,
250,61,60,59,31,30,0,70,71,72,73,238,249,
51,37,36,0,35,54,55,56,57,
51,37,36,0,35,54,55,56,57,
51,37,36,0,35,54,55,56,57,
51,37,36,0,35,54,55,56,57,
51,37,36,0,35,54,55,56,57,
51,37,36,0,35,54,55,56,57,
37,36,0,35,55,
51,0,50,
51,0,50,
51,37,36,0,35,54,55,56,57,
51,37,36,0,35,54,55,56,57,
51,37,36,0,35,54,55,56,57,
51,0,50,
250,0,
250,208,198,163,118,102,61,60,59,31,30,0,76,240,
250,61,60,59,31,30,0,70,71,238,249,
61,60,59,31,30,0,29,58,
51,0,50,
51,0,50,
51,0,50,
51,0,50,
51,0,50,
51,0,50,
481,479,478,477,476,475,474,473,471,470,469,467,466,409,405,378,308,250,208,
  198,192,184,167,163,124,121,118,116,112,107,102,97,92,86,61,60,51,49,39,
  37,36,17,15,14,13,12,11,0,35,54,55,56,57,117,
482,481,479,478,477,476,475,474,473,471,470,469,468,467,466,465,409,405,363,
  308,250,208,198,192,184,167,163,124,121,118,116,112,107,102,97,92,86,61,
  60,51,49,39,37,36,17,15,14,13,12,11,0,21,27,113,331,332,335,346,347,
51,0,50,
51,0,50,
51,0,50,
481,479,478,477,476,475,474,473,471,470,469,467,466,409,405,308,250,208,198,
  192,184,167,163,124,121,118,116,112,107,102,97,92,86,61,60,51,49,39,37,
  36,17,15,14,13,12,11,0,35,54,55,56,57,
51,37,36,0,35,54,55,56,57,
250,208,198,163,118,61,60,59,31,30,0,239,
250,208,198,163,118,61,60,59,31,30,0,80,81,83,84,241,242,243,244,
37,36,31,30,0,35,54,55,56,57,
473,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
473,318,37,36,17,15,14,12,11,0,35,54,55,56,57,
482,481,480,479,478,477,476,475,474,473,472,471,470,469,468,467,466,465,464,
  409,405,308,250,231,229,227,217,208,198,192,184,167,163,124,121,118,116,
  112,107,102,97,92,86,61,60,51,49,47,45,43,41,39,37,36,17,15,14,13,12,11,
  0,35,54,55,56,57,210,
481,478,477,473,409,308,250,208,198,192,184,167,163,118,116,112,107,102,97,
  92,86,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
478,477,473,409,405,308,250,208,198,192,184,167,163,121,118,116,112,107,102,
  97,92,86,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
481,478,477,473,409,308,250,208,198,192,184,167,163,127,126,125,124,121,118,
  116,112,107,102,97,92,86,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
481,479,478,477,476,475,474,473,471,470,469,467,466,409,405,378,308,250,208,
  198,192,184,167,163,124,121,118,116,112,107,102,97,92,86,61,60,51,49,39,
  17,15,14,13,12,11,0,5,388,
482,481,478,477,475,473,471,470,469,468,467,465,409,405,336,333,308,250,208,
  198,192,184,167,163,124,121,118,116,112,107,102,97,92,86,61,51,47,41,39,
  37,36,31,30,17,15,14,13,12,11,0,349,350,351,
482,481,479,478,477,476,475,474,473,472,471,470,469,468,467,465,464,409,405,
  363,361,308,250,208,198,192,184,167,163,124,121,118,116,112,107,102,97,
  92,86,61,60,51,49,47,45,43,41,39,37,36,17,15,14,13,12,11,0,354,364,365,
  367,
481,479,478,477,476,475,474,473,471,470,469,467,466,409,405,308,250,208,198,
  192,184,167,163,124,121,118,116,112,107,102,97,92,86,61,60,51,49,45,43,
  39,37,36,31,30,17,15,14,13,12,11,0,24,25,26,
336,333,0,337,338,339,
482,481,479,478,477,476,475,474,473,471,470,469,468,467,466,465,409,405,336,
  333,308,250,208,198,192,184,167,163,124,121,118,116,112,107,102,97,92,
  86,61,60,51,49,45,39,37,36,17,15,14,13,12,11,0,
333,0,
45,0,44,
41,31,30,0,32,33,34,40,
478,477,409,308,250,208,198,192,184,167,163,118,116,112,107,102,97,92,86,37,
  36,0,35,54,55,56,57,
482,481,480,479,478,477,476,475,474,473,472,471,470,469,468,467,466,465,464,
  409,405,308,250,208,198,192,184,167,163,124,121,118,116,112,107,102,97,
  92,86,61,60,51,49,47,45,43,41,39,37,36,31,30,17,15,14,13,12,11,0,2,3,7,
  32,33,34,104,
482,481,480,479,478,477,476,475,474,473,472,471,470,469,468,467,466,465,464,
  409,405,308,250,208,198,192,184,167,163,124,121,118,116,112,107,102,97,
  92,86,61,60,51,49,47,45,43,41,39,37,36,31,30,17,15,14,13,12,11,0,2,3,7,
  32,33,34,99,
481,479,478,477,476,475,474,473,471,470,469,467,466,409,405,308,250,208,198,
  192,184,167,163,124,121,118,116,112,107,102,97,92,86,61,60,51,49,39,17,
  15,14,13,12,11,0,93,330,
51,0,50,
250,208,198,163,118,61,60,59,31,30,0,248,
250,208,198,163,118,61,60,59,31,30,0,247,
250,208,198,163,118,61,60,59,31,30,0,246,
250,208,198,163,118,61,60,59,31,30,0,245,
208,198,163,118,0,80,81,83,84,241,242,
31,30,0,29,
473,17,15,14,13,12,11,0,19,88,
473,318,17,15,14,12,11,0,169,170,174,182,197,
482,481,480,479,478,477,476,475,474,473,472,471,470,469,468,467,466,465,464,
  409,405,308,250,231,229,227,217,208,198,192,184,167,163,124,121,118,116,
  112,107,102,97,92,86,61,60,51,49,47,45,43,41,39,17,15,14,13,12,11,0,211,
  212,213,
481,478,477,473,409,308,250,208,198,192,184,167,163,118,116,112,107,102,97,
  92,86,17,15,14,13,12,11,0,158,159,200,202,
478,477,473,409,405,308,250,208,198,192,184,167,163,121,118,116,112,107,102,
  97,92,86,17,15,14,13,12,11,0,165,328,329,
481,478,477,473,409,308,250,208,198,192,184,167,163,127,126,125,124,121,118,
  116,112,107,102,97,92,86,17,15,14,13,12,11,0,96,145,158,159,
481,479,478,477,476,475,474,473,471,470,469,467,466,409,405,308,250,208,198,
  192,184,167,163,124,121,118,116,112,107,102,97,92,86,61,60,51,49,39,37,
  36,17,15,14,13,12,11,0,21,27,
45,0,44,
473,36,17,15,14,12,11,0,389,390,
41,31,30,0,32,33,34,40,
482,481,478,477,475,473,471,470,469,468,467,465,409,405,308,250,208,198,192,
  184,167,163,124,121,118,116,112,107,102,97,92,86,61,51,39,37,36,17,15,
  14,13,12,11,0,349,
482,481,480,479,478,477,476,475,474,473,472,471,470,469,468,467,466,465,464,
  409,405,308,250,208,198,192,184,167,163,124,121,118,116,112,107,102,97,
  92,86,61,60,51,49,47,45,43,41,39,37,36,31,30,17,15,14,13,12,11,0,
363,0,
481,479,478,477,476,475,474,473,471,470,469,467,466,409,405,308,250,208,198,
  192,184,167,163,124,121,118,116,112,107,102,97,92,86,61,60,51,49,39,37,
  36,17,15,14,13,12,11,0,24,
482,481,478,477,475,473,471,470,469,468,467,465,409,405,363,308,250,208,198,
  192,184,167,163,124,121,118,116,112,107,102,97,92,86,61,51,39,37,36,17,
  15,14,13,12,11,0,27,335,346,347,
336,0,337,
482,481,478,477,475,473,471,470,469,468,467,465,409,405,336,333,308,250,208,
  198,192,184,167,163,124,121,118,116,112,107,102,97,92,86,61,51,47,41,39,
  37,36,31,30,17,15,14,13,12,11,0,349,350,351,
481,479,478,477,476,475,474,473,471,470,469,467,466,409,405,308,250,208,198,
  192,184,167,163,124,121,118,116,112,107,102,97,92,86,61,60,51,49,45,43,
  39,37,36,31,30,17,15,14,13,12,11,0,24,25,26,
482,481,478,477,475,473,471,470,469,468,467,465,409,405,352,308,250,208,198,
  192,184,167,163,124,121,118,116,112,107,102,97,92,86,61,51,39,37,36,17,
  15,14,13,12,11,0,27,334,340,344,345,346,
482,481,478,477,475,473,471,470,469,468,467,465,409,405,363,308,250,208,198,
  192,184,167,163,124,121,118,116,112,107,102,97,92,86,61,51,39,37,36,17,
  15,14,13,12,11,0,27,331,332,335,346,347,
481,479,478,477,476,475,474,473,471,470,469,467,466,409,405,308,250,208,198,
  192,184,167,163,124,121,118,116,112,107,102,97,92,86,61,60,51,49,39,37,
  36,17,15,14,13,12,11,0,21,27,
31,0,34,
250,208,198,167,163,118,116,112,107,102,97,92,61,60,59,37,36,31,30,0,35,54,
  55,56,57,
478,477,409,308,250,208,198,192,184,167,163,118,116,112,107,102,97,92,86,0,
  109,368,374,
482,481,480,479,478,477,476,475,474,473,472,471,470,469,468,467,466,465,464,
  409,405,308,250,208,198,192,184,167,163,124,121,118,116,112,107,102,97,
  92,86,61,60,51,49,47,45,43,41,39,37,36,17,15,14,13,12,11,0,
250,208,198,167,163,118,116,112,107,102,97,92,61,60,59,37,36,31,30,0,106,
31,30,0,32,33,34,
250,208,198,167,163,118,116,112,107,102,97,92,61,60,59,37,36,31,30,0,101,
31,30,0,32,33,34,
481,479,478,477,476,475,474,473,471,470,469,467,466,409,405,308,250,208,198,
  192,184,167,163,124,121,118,116,112,107,102,97,92,86,61,60,51,49,39,17,
  15,14,13,12,11,0,
37,36,0,35,
481,478,477,473,409,308,264,250,208,198,192,184,167,163,118,116,112,107,102,
  97,92,86,39,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
473,17,15,14,13,12,11,0,20,
37,36,31,30,0,35,54,55,56,57,
473,17,15,14,13,12,11,0,319,
37,36,0,35,55,56,
473,318,250,208,198,192,184,167,163,118,116,112,107,102,97,92,61,60,59,37,
  36,31,30,17,15,14,12,11,0,35,55,56,57,
473,318,250,208,198,192,167,163,118,116,112,107,102,97,92,61,60,59,31,30,17,
  15,14,12,11,0,169,171,172,174,182,197,
482,481,480,479,478,477,476,475,474,473,472,471,470,469,468,467,466,465,464,
  409,405,308,250,208,198,192,184,167,163,124,121,118,116,112,107,102,97,
  92,86,61,60,51,47,45,43,41,39,37,36,17,15,14,13,12,11,0,280,283,
49,31,30,0,32,33,34,48,
481,479,478,477,476,475,474,473,471,470,469,467,466,409,405,308,250,208,198,
  192,184,167,163,124,121,118,116,112,107,102,97,92,86,61,60,51,49,39,37,
  36,31,30,17,15,14,13,12,11,0,35,54,55,56,57,
481,479,478,477,476,475,474,473,471,470,469,467,466,409,405,308,250,208,198,
  192,184,167,163,124,121,118,116,112,107,102,97,92,86,61,60,51,49,39,37,
  36,31,30,17,15,14,13,12,11,0,35,54,55,56,57,
481,479,478,477,476,475,474,473,471,470,469,467,466,409,405,308,250,208,198,
  192,184,167,163,124,121,118,116,112,107,102,97,92,86,61,60,51,49,39,37,
  36,31,30,17,15,14,13,12,11,0,35,54,55,56,57,
49,37,36,0,218,
481,478,477,473,409,308,250,208,198,192,184,167,163,118,116,112,107,102,97,
  92,86,17,15,14,13,12,11,0,158,
49,37,36,31,30,0,35,54,55,56,57,
31,30,0,32,33,34,
478,477,473,409,405,308,250,208,198,192,184,167,163,121,118,116,112,107,102,
  97,92,86,17,15,14,13,12,11,0,328,
49,37,36,0,35,54,55,56,57,
481,478,477,473,409,308,250,208,198,192,184,167,163,118,116,112,107,102,97,
  92,86,17,15,14,13,12,11,0,158,
37,36,0,35,
481,478,477,473,409,308,250,208,198,192,184,167,163,118,116,112,107,102,97,
  92,86,37,36,17,15,14,13,12,11,0,35,158,159,
481,478,477,473,409,308,250,208,198,192,184,167,163,118,116,112,107,102,97,
  92,86,37,36,17,15,14,13,12,11,0,35,158,159,
481,478,477,473,409,308,250,208,198,192,184,167,163,118,116,112,107,102,97,
  92,86,37,36,17,15,14,13,12,11,0,35,158,159,
37,36,0,35,
37,36,0,35,
37,36,31,30,0,35,54,55,56,57,
481,479,478,477,476,475,474,473,471,470,469,467,466,409,405,308,250,208,198,
  192,184,167,163,124,121,118,116,112,107,102,97,92,86,61,60,51,49,39,37,
  36,17,15,14,13,12,11,0,
378,37,36,0,35,54,55,56,57,
36,0,
473,17,15,14,12,11,0,
481,479,478,477,476,475,474,473,471,470,469,467,466,409,405,308,250,208,198,
  192,184,167,163,124,121,118,116,112,107,102,97,92,86,61,60,51,49,39,37,
  36,17,15,14,13,12,11,0,21,27,
250,208,198,167,163,118,116,112,107,102,97,92,61,60,59,37,36,31,30,0,35,54,
  55,56,57,
482,481,478,477,475,473,471,470,469,468,467,465,409,405,308,250,208,198,192,
  184,167,163,124,121,118,116,112,107,102,97,92,86,61,51,39,37,36,17,15,
  14,13,12,11,0,
482,481,478,477,476,475,474,473,472,471,470,469,468,467,466,465,464,409,405,
  361,358,308,250,208,198,192,184,167,163,124,121,118,116,112,107,102,97,
  92,86,61,60,51,49,47,45,43,41,39,37,36,17,15,14,13,12,11,0,353,354,355,
  356,357,360,
336,47,41,31,30,0,341,342,343,
47,0,46,
43,0,42,
481,478,477,476,473,472,471,470,469,466,465,409,385,369,308,250,208,198,192,
  184,167,163,124,121,118,116,112,107,102,97,92,86,60,43,41,17,15,14,13,
  12,11,0,155,156,382,384,
369,0,
37,36,31,30,0,35,54,55,56,57,
250,208,198,167,163,118,116,112,107,102,97,92,61,60,59,37,36,31,30,0,35,54,
  55,56,57,
250,208,198,167,163,118,116,112,107,102,97,92,61,60,59,37,36,31,30,0,105,
250,208,198,167,163,118,116,112,107,102,97,92,61,60,59,37,36,31,30,0,35,54,
  55,56,57,
250,208,198,167,163,118,116,112,107,102,97,92,61,60,59,37,36,31,30,0,100,
477,473,308,208,163,121,118,112,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
481,478,477,473,409,308,264,250,208,198,192,184,167,163,118,116,112,107,102,
  97,92,86,39,17,15,14,13,12,11,0,251,
473,17,15,14,13,12,11,0,
31,30,0,32,33,34,
473,17,15,14,13,12,11,0,
473,318,37,36,17,15,14,12,11,0,35,55,183,197,
473,318,250,208,198,192,184,167,163,118,116,112,107,102,97,92,61,60,59,31,
  30,17,15,14,12,11,0,175,177,
51,37,36,0,35,54,55,56,57,
31,30,0,32,33,34,
482,481,480,479,478,477,476,475,474,473,472,471,470,469,468,467,466,465,464,
  409,405,308,250,208,198,192,184,167,163,124,121,118,116,112,107,102,97,
  92,86,61,60,51,47,45,43,41,39,37,36,17,15,14,13,12,11,0,
250,208,198,167,163,118,116,112,107,102,97,92,61,60,59,37,36,31,30,0,216,
482,481,480,479,478,477,476,475,474,473,472,471,470,469,468,467,466,465,464,
  409,405,308,250,208,198,192,184,167,163,124,121,118,116,112,107,102,97,
  92,86,61,60,51,49,47,45,43,41,39,37,36,17,15,14,13,12,11,0,35,54,55,56,
  57,
481,479,478,477,476,475,474,473,471,470,469,467,466,409,405,308,250,208,198,
  192,184,167,163,124,121,118,116,112,107,102,97,92,86,61,60,51,49,39,31,
  30,17,15,14,13,12,11,0,4,5,32,33,34,
481,479,478,477,476,475,474,473,471,470,469,467,466,409,405,308,250,208,198,
  192,184,167,163,124,121,118,116,112,107,102,97,92,86,61,60,51,49,39,31,
  30,17,15,14,13,12,11,0,4,5,32,33,34,
481,479,478,477,476,475,474,473,471,470,469,467,466,409,405,308,250,208,198,
  192,184,167,163,124,121,118,116,112,107,102,97,92,86,61,60,51,49,39,31,
  30,17,15,14,13,12,11,0,4,5,32,33,34,
49,37,36,0,35,54,55,56,57,219,
49,0,48,
250,208,198,167,163,118,116,112,107,102,97,92,61,60,59,37,36,31,30,0,201,
49,0,48,
481,478,477,473,409,308,250,208,198,192,184,167,163,139,137,118,116,112,107,
  102,97,92,86,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
481,478,477,473,409,308,250,208,198,192,184,167,163,118,116,112,107,102,97,
  92,86,17,15,14,13,12,11,0,158,
481,478,477,473,409,308,250,208,198,192,184,167,163,139,137,134,132,130,128,
  124,121,118,116,112,107,102,97,92,86,37,36,17,15,14,13,12,11,0,35,54,55,
  56,57,
481,478,477,473,409,308,250,208,198,192,184,167,163,118,116,112,107,102,97,
  92,86,17,15,14,13,12,11,0,158,
409,141,124,121,37,36,0,35,54,55,56,57,
481,478,477,473,409,308,250,208,198,192,184,167,163,118,116,112,107,102,97,
  92,86,17,15,14,13,12,11,0,158,
481,478,477,473,409,308,250,208,198,192,184,167,163,139,137,124,121,118,116,
  112,107,102,97,92,86,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
124,121,37,36,0,35,54,55,56,57,
124,121,37,36,0,35,54,55,56,57,
31,30,0,32,33,34,
378,0,388,
473,53,47,41,36,31,30,17,15,14,13,12,11,0,391,392,393,
43,0,42,
482,481,478,477,476,475,474,473,472,471,470,469,468,467,466,465,464,409,405,
  361,308,250,208,198,192,184,167,163,124,121,118,116,112,107,102,97,92,
  86,61,60,51,49,47,45,43,41,39,37,36,17,15,14,13,12,11,0,353,354,355,360,
358,0,
482,481,478,477,475,473,471,470,469,468,467,465,409,405,352,308,250,208,198,
  192,184,167,163,124,121,118,116,112,107,102,97,92,86,61,51,39,37,36,17,
  15,14,13,12,11,0,27,340,344,345,346,
336,0,341,
31,30,0,32,33,34,
31,30,0,32,33,34,
477,473,308,208,163,118,112,17,15,14,13,12,11,0,
481,478,477,476,473,472,471,470,469,466,465,409,385,308,250,208,198,192,184,
  167,163,124,121,118,116,112,107,102,97,92,86,60,43,41,17,15,14,13,12,11,
  0,155,382,
481,478,477,476,473,472,471,470,469,466,465,409,385,378,376,371,308,250,208,
  198,192,184,167,163,124,121,118,116,112,107,102,97,92,86,60,43,41,37,36,
  31,30,17,15,14,13,12,11,0,155,370,375,377,382,386,387,
31,30,0,32,33,34,
250,208,198,167,163,118,116,112,107,102,97,92,61,60,59,37,36,31,30,0,35,54,
  55,56,57,
250,208,198,167,163,118,116,112,107,102,97,92,61,60,59,37,36,31,30,0,35,54,
  55,56,57,
477,473,308,208,163,121,118,112,17,15,14,13,12,11,0,94,284,
481,478,477,473,409,308,264,250,208,198,192,184,167,163,118,116,112,107,102,
  97,92,86,39,17,15,14,13,12,11,0,252,
250,208,198,167,163,118,116,112,107,102,97,92,61,60,59,37,36,31,30,0,35,54,
  55,56,57,
473,17,15,14,13,12,11,0,
37,36,31,30,0,35,54,55,56,57,
184,0,176,178,179,180,181,
51,0,50,
250,208,198,167,163,118,116,112,107,102,97,92,61,60,59,37,36,31,30,0,35,54,
  55,56,57,
250,208,198,167,163,118,116,112,107,102,97,92,61,60,59,37,36,31,30,0,35,54,
  55,56,57,
482,481,480,479,478,477,476,475,474,473,472,471,470,469,468,467,466,465,464,
  409,405,308,250,208,198,192,184,167,163,124,121,118,116,112,107,102,97,
  92,86,61,60,51,49,47,45,43,41,39,17,15,14,13,12,11,0,214,
31,30,0,32,33,34,
250,208,198,167,163,118,116,112,107,102,97,92,61,60,59,37,36,31,30,0,232,
31,30,0,32,33,34,
250,208,198,167,163,118,116,112,107,102,97,92,61,60,59,37,36,31,30,0,230,
31,30,0,32,33,34,
250,208,198,167,163,118,116,112,107,102,97,92,61,60,59,37,36,31,30,0,228,
49,0,48,
481,479,478,477,476,475,474,473,471,470,469,467,466,409,405,308,250,208,205,
  198,192,184,167,163,124,121,118,116,112,107,102,97,92,86,61,60,51,49,39,
  37,36,17,15,14,13,12,11,0,203,206,207,
250,208,198,167,163,118,116,112,107,102,97,92,61,60,59,37,36,31,30,0,35,54,
  55,56,57,
473,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
481,478,477,473,409,308,250,208,198,192,184,167,163,139,137,118,116,112,107,
  102,97,92,86,17,15,14,13,12,11,0,135,158,159,
481,478,477,473,409,308,250,208,198,192,184,167,163,139,137,134,132,130,128,
  124,121,118,116,112,107,102,97,92,86,17,15,14,13,12,11,0,122,135,158,
  159,
409,141,124,121,0,122,143,154,
481,478,477,473,409,308,250,208,198,192,184,167,163,139,137,124,121,118,116,
  112,107,102,97,92,86,17,15,14,13,12,11,0,122,135,158,159,
124,121,0,122,
124,121,0,122,
250,208,198,167,163,118,116,112,107,102,97,92,61,60,59,37,36,31,30,0,120,
47,0,46,
473,53,36,17,15,14,13,12,11,0,391,
37,36,31,30,0,35,54,55,56,57,
250,208,198,167,163,118,116,112,107,102,97,92,61,60,59,37,36,31,30,0,35,54,
  55,56,57,
250,208,198,167,163,118,116,112,107,102,97,92,61,60,59,37,36,31,30,0,35,54,
  55,56,57,
477,473,308,208,163,118,112,17,15,14,13,12,11,0,
481,478,477,476,473,472,471,470,469,466,465,409,385,378,308,250,208,198,192,
  184,167,163,124,121,118,116,112,107,102,97,92,86,60,43,41,17,15,14,13,
  12,11,0,155,382,386,
376,0,
376,0,
371,37,36,31,30,0,373,
250,208,198,167,163,118,116,112,107,102,97,92,61,60,59,37,36,31,30,0,35,54,
  55,56,57,
477,473,308,208,163,118,112,17,15,14,13,12,11,0,285,287,
37,36,0,35,
481,478,477,473,409,308,264,250,208,198,192,184,167,163,118,116,112,107,102,
  97,92,86,39,17,15,14,13,12,11,0,253,254,257,259,270,271,
250,208,198,167,163,118,116,112,107,102,97,92,61,60,59,31,30,0,89,
473,17,15,14,13,12,11,0,
31,30,0,32,33,34,
51,37,36,0,35,54,55,56,57,
31,30,0,32,33,34,
184,0,178,179,180,
473,37,36,17,15,14,12,11,0,35,54,55,56,57,193,
482,481,480,479,478,477,476,475,474,473,472,471,470,469,468,467,466,465,464,
  409,405,308,250,208,198,192,184,167,163,124,121,118,116,112,107,102,97,
  92,86,61,60,51,49,47,45,43,41,39,37,36,31,30,17,15,14,13,12,11,0,3,7,
  281,
31,30,0,32,33,34,
250,208,198,167,163,118,116,112,107,102,97,92,61,60,59,37,36,31,30,0,35,54,
  55,56,57,
250,208,198,167,163,118,116,112,107,102,97,92,61,60,59,37,36,31,30,0,35,54,
  55,56,57,
250,208,198,167,163,118,116,112,107,102,97,92,61,60,59,37,36,31,30,0,35,54,
  55,56,57,
250,208,198,167,163,118,116,112,107,102,97,92,61,60,59,37,36,31,30,0,35,54,
  55,56,57,
250,208,198,167,163,118,116,112,107,102,97,92,61,60,59,37,36,31,30,0,35,54,
  55,56,57,
250,208,198,167,163,118,116,112,107,102,97,92,61,60,59,37,36,31,30,0,35,54,
  55,56,57,
473,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
481,479,478,477,476,475,474,473,471,470,469,467,466,409,405,308,250,208,205,
  198,192,184,167,163,124,121,118,116,112,107,102,97,92,86,61,60,51,49,39,
  37,36,17,15,14,13,12,11,0,206,
473,17,15,14,13,12,11,0,19,166,
481,478,477,473,409,308,250,208,198,192,184,167,163,118,116,112,107,102,97,
  92,86,17,15,14,13,12,11,0,158,
37,36,0,35,
481,478,477,473,409,308,250,208,198,192,184,167,163,118,116,112,107,102,97,
  92,86,37,36,17,15,14,13,12,11,0,35,158,159,
481,478,477,473,409,308,250,208,198,192,184,167,163,118,116,112,107,102,97,
  92,86,37,36,17,15,14,13,12,11,0,35,158,159,
481,478,477,473,409,308,250,208,198,192,184,167,163,118,116,112,107,102,97,
  92,86,17,15,14,13,12,11,0,158,159,
481,478,477,473,409,308,250,208,198,192,184,167,163,118,116,112,107,102,97,
  92,86,17,15,14,13,12,11,0,158,159,
37,36,0,35,
37,36,0,35,
37,36,0,35,
37,36,0,35,
37,36,0,35,
37,36,0,35,
481,478,477,473,471,469,468,467,465,409,405,308,250,208,198,192,184,167,163,
  124,121,118,116,112,107,102,97,92,86,61,60,37,36,17,15,14,13,12,11,0,
  411,412,413,
37,36,0,35,
37,36,0,35,
37,36,0,35,
37,36,0,35,
481,478,477,473,409,308,250,208,198,192,184,167,163,118,116,112,107,102,97,
  92,86,37,36,17,15,14,13,12,11,0,35,158,159,
481,478,477,473,409,308,250,208,198,192,184,167,163,118,116,112,107,102,97,
  92,86,37,36,17,15,14,13,12,11,0,35,158,159,
37,36,0,35,
37,36,0,35,
37,36,0,35,
250,208,198,167,163,118,116,112,107,102,97,92,61,60,59,37,36,31,30,0,35,54,
  55,56,57,
37,36,31,30,0,35,54,55,56,57,
31,30,0,32,33,34,
481,478,477,476,473,472,471,470,469,466,465,409,385,378,376,371,308,250,208,
  198,192,184,167,163,124,121,118,116,112,107,102,97,92,86,60,43,41,37,36,
  31,30,17,15,14,13,12,11,0,155,370,375,377,382,386,387,
481,478,477,476,473,472,471,470,469,466,465,409,385,378,376,371,308,250,208,
  198,192,184,167,163,124,121,118,116,112,107,102,97,92,86,60,43,41,37,36,
  31,30,17,15,14,13,12,11,0,155,370,375,377,382,386,387,
481,478,477,476,473,472,471,470,469,466,465,409,385,308,250,208,198,192,184,
  167,163,124,121,118,116,112,107,102,97,92,86,60,43,41,17,15,14,13,12,11,
  0,155,156,372,382,
477,473,308,208,163,118,112,17,15,14,13,12,11,0,
473,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
481,478,477,473,409,308,250,208,198,192,184,167,163,118,116,112,107,102,97,
  92,86,39,17,15,14,13,12,11,0,270,
39,0,38,
37,36,0,35,55,56,
31,30,0,32,33,34,
37,36,0,35,55,56,255,267,268,
473,17,15,14,13,12,11,0,
51,0,50,
473,318,250,208,198,192,184,167,163,118,116,112,107,102,97,92,61,60,59,37,
  36,31,30,17,15,14,12,11,0,35,54,55,56,57,
473,17,15,14,12,11,0,197,
37,36,31,30,0,35,194,195,196,
250,208,198,167,163,118,116,112,107,102,97,92,61,60,59,37,36,31,30,0,215,
473,17,15,14,13,12,11,0,19,220,
37,36,31,30,0,35,54,55,56,57,
481,478,477,473,409,308,250,208,198,192,184,167,163,118,116,112,107,102,97,
  92,86,60,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
481,478,477,473,409,308,250,208,198,192,184,167,163,118,116,112,107,102,97,
  92,86,17,15,14,13,12,11,0,158,
481,478,477,473,409,308,250,208,198,192,184,167,163,118,116,112,107,102,97,
  92,86,60,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
481,478,477,473,409,308,250,208,198,192,184,167,163,118,116,112,107,102,97,
  92,86,17,15,14,13,12,11,0,158,
481,478,477,473,409,308,250,208,198,192,184,167,163,118,116,112,107,102,97,
  92,86,60,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
481,478,477,473,409,308,250,208,198,192,184,167,163,118,116,112,107,102,97,
  92,86,60,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
481,478,477,473,409,308,250,208,198,192,184,167,163,146,121,118,116,112,107,
  102,97,92,86,60,53,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
481,478,477,473,409,308,250,208,198,192,184,167,163,146,121,118,116,112,107,
  102,97,92,86,60,53,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
473,146,53,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
477,473,308,208,163,146,118,112,53,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
477,473,308,208,163,146,118,112,60,53,37,36,17,15,14,13,12,11,0,35,54,55,56,
  57,
481,478,477,473,471,469,468,467,465,409,405,308,250,208,198,192,184,167,163,
  124,121,118,116,112,107,102,97,92,86,61,60,17,15,14,13,12,11,0,411,
481,478,477,476,473,472,471,470,469,466,465,409,385,308,250,208,198,192,184,
  167,163,124,121,118,116,112,107,102,97,92,86,60,43,41,37,36,17,15,14,13,
  12,11,0,35,54,55,56,57,
473,405,146,53,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
477,473,308,208,163,146,118,112,60,53,37,36,17,15,14,13,12,11,0,35,54,55,56,
  57,
481,478,477,473,409,308,250,208,198,192,184,167,163,118,116,112,107,102,97,
  92,86,60,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
477,473,308,304,208,163,146,118,112,53,37,36,17,15,14,13,12,11,0,35,54,55,
  56,57,
478,477,473,409,308,250,208,198,192,184,167,163,146,121,118,116,112,107,102,
  97,92,86,60,53,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
477,473,308,208,163,146,118,112,60,53,37,36,17,15,14,13,12,11,0,35,54,55,56,
  57,
477,473,308,208,163,146,118,112,60,53,37,36,17,15,14,13,12,11,0,35,54,55,56,
  57,
477,473,308,208,163,146,118,112,60,53,37,36,17,15,14,13,12,11,0,35,54,55,56,
  57,
31,30,0,32,33,34,
481,478,477,476,473,472,471,470,469,466,465,409,385,378,308,250,208,198,192,
  184,167,163,124,121,118,116,112,107,102,97,92,86,60,43,41,37,36,31,30,
  17,15,14,13,12,11,0,155,379,382,
473,17,15,14,13,12,11,0,20,95,288,
481,478,477,473,409,308,250,208,198,192,184,167,163,118,116,112,107,102,97,
  92,86,17,15,14,13,12,11,0,158,159,265,
473,436,435,434,433,432,427,426,422,134,132,130,128,124,121,37,36,17,15,14,
  13,12,11,0,19,35,55,260,263,272,414,416,417,420,421,
250,208,198,163,118,102,61,60,59,37,36,31,30,0,258,
478,477,473,409,308,250,208,198,192,184,167,163,121,118,116,112,107,102,97,
  92,86,39,37,36,17,15,14,13,12,11,0,35,55,266,274,
37,36,31,30,0,35,55,56,57,267,
31,30,0,32,33,34,
473,17,15,14,13,12,11,0,
473,37,36,17,15,14,13,12,11,0,185,
37,36,0,35,55,56,
473,37,36,17,15,14,12,11,0,35,54,55,56,57,193,
37,36,0,35,194,
250,208,198,167,163,118,116,112,107,102,97,92,61,60,59,37,36,31,30,0,35,54,
  55,56,57,
37,36,0,35,
31,30,0,32,33,34,
481,478,477,473,409,308,250,208,198,192,184,167,163,118,116,112,107,102,97,
  92,86,60,17,15,14,13,12,11,0,136,161,162,
481,478,477,473,409,308,250,208,198,192,184,167,163,118,116,112,107,102,97,
  92,86,60,17,15,14,13,12,11,0,136,161,162,
481,478,477,473,409,308,250,208,198,192,184,167,163,118,116,112,107,102,97,
  92,86,60,17,15,14,13,12,11,0,136,161,162,
481,478,477,473,409,308,250,208,198,192,184,167,163,118,116,112,107,102,97,
  92,86,60,17,15,14,13,12,11,0,136,161,162,
481,478,477,473,409,308,250,208,198,192,184,167,163,146,121,118,116,112,107,
  102,97,92,86,60,53,17,15,14,13,12,11,0,133,149,397,398,
481,478,477,473,409,308,250,208,198,192,184,167,163,146,121,118,116,112,107,
  102,97,92,86,60,53,17,15,14,13,12,11,0,133,149,397,398,
473,146,53,17,15,14,13,12,11,0,20,131,148,
477,473,308,208,163,146,118,112,53,17,15,14,13,12,11,0,129,147,301,
477,473,308,208,163,146,118,112,60,53,17,15,14,13,12,11,0,123,150,399,400,
481,478,477,476,473,472,471,470,469,466,465,409,385,308,250,208,198,192,184,
  167,163,124,121,118,116,112,107,102,97,92,86,60,43,41,17,15,14,13,12,11,
  0,144,155,156,382,
473,405,146,53,17,15,14,13,12,11,0,142,153,401,402,
477,473,308,208,163,146,118,112,60,53,17,15,14,13,12,11,0,123,150,399,400,
481,478,477,473,409,308,250,208,198,192,184,167,163,118,116,112,107,102,97,
  92,86,60,17,15,14,13,12,11,0,136,161,162,
477,473,308,304,208,163,146,118,112,53,17,15,14,13,12,11,0,140,152,292,293,
  294,307,309,312,
478,477,473,409,308,250,208,198,192,184,167,163,146,121,118,116,112,107,102,
  97,92,86,60,53,17,15,14,13,12,11,0,138,151,289,290,394,395,
477,473,308,208,163,146,118,112,60,53,17,15,14,13,12,11,0,123,150,399,400,
477,473,308,208,163,146,118,112,60,53,17,15,14,13,12,11,0,123,150,399,400,
477,473,308,208,163,146,118,112,60,53,17,15,14,13,12,11,0,123,150,399,400,
250,208,198,167,163,118,116,112,107,102,97,92,61,60,59,37,36,31,30,0,35,54,
  55,56,57,
481,478,477,476,473,472,471,470,469,466,465,409,385,308,250,208,198,192,184,
  167,163,124,121,118,116,112,107,102,97,92,86,60,43,41,17,15,14,13,12,11,
  0,155,156,372,382,
473,17,15,14,13,12,11,0,
37,36,0,35,
481,478,477,473,409,308,250,208,198,192,184,167,163,118,116,112,107,102,97,
  92,86,17,15,14,13,12,11,0,158,
37,36,0,35,55,56,
53,0,52,
53,0,52,
53,0,52,
53,0,52,
53,0,52,
53,0,52,
53,0,52,
53,0,52,
39,0,38,
39,0,38,
39,0,38,
39,0,38,
39,0,38,
37,36,0,35,55,56,
39,0,38,
250,208,198,163,118,102,61,60,59,37,36,31,30,0,35,54,55,56,57,
478,477,473,409,308,250,208,198,192,184,167,163,121,118,116,112,107,102,97,
  92,86,39,17,15,14,13,12,11,0,
478,477,473,409,308,250,208,198,192,184,167,163,121,118,116,112,107,102,97,
  92,86,39,37,36,17,15,14,13,12,11,0,35,55,266,274,
250,208,198,163,118,102,61,60,59,37,36,31,30,0,256,
473,17,15,14,13,12,11,0,
473,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
473,53,37,36,17,15,14,13,12,11,0,19,35,52,55,191,321,
482,481,480,479,478,477,476,475,474,473,472,471,470,469,468,467,466,465,464,
  409,405,308,250,208,198,192,184,167,163,124,121,118,116,112,107,102,97,
  92,86,61,60,51,49,47,45,43,41,37,36,17,15,14,13,12,11,0,221,234,235,
250,208,198,167,163,118,116,112,107,102,97,92,61,60,59,37,36,31,30,0,35,54,
  55,56,57,
481,478,477,473,409,308,250,208,198,192,184,167,163,118,116,112,107,102,97,
  92,86,60,17,15,14,13,12,11,0,161,
481,478,477,473,409,308,250,208,198,192,184,167,163,121,118,116,112,107,102,
  97,92,86,60,17,15,14,13,12,11,0,397,
473,17,15,14,13,12,11,0,
477,473,308,208,163,118,112,17,15,14,13,12,11,0,
60,0,
477,473,308,208,163,118,112,60,17,15,14,13,12,11,0,399,
481,478,477,476,473,472,471,470,469,466,465,409,385,308,250,208,198,192,184,
  167,163,124,121,118,116,112,107,102,97,92,86,60,43,41,17,15,14,13,12,11,
  0,155,382,
473,121,37,36,31,30,17,15,14,13,12,11,0,406,407,408,
473,17,15,14,12,11,0,
477,308,208,163,118,112,0,
477,473,308,208,163,118,112,17,15,14,13,12,11,0,
477,473,308,208,163,118,112,17,15,14,13,12,11,0,301,
477,308,208,163,118,112,0,
477,473,308,208,163,118,112,60,37,36,31,30,17,15,14,13,12,11,0,296,297,301,
  306,
304,49,0,303,313,
304,49,0,303,
478,477,473,409,308,250,208,198,192,184,167,163,121,118,116,112,107,102,97,
  92,86,60,17,15,14,13,12,11,0,394,
39,0,38,291,
481,478,477,473,409,308,250,208,198,192,184,167,163,127,126,125,124,121,118,
  116,112,107,102,97,92,86,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
473,124,121,37,36,17,15,14,13,12,11,0,19,35,55,260,
481,478,477,473,409,308,250,208,198,192,184,167,163,121,118,116,112,107,102,
  97,92,86,60,17,15,14,13,12,11,0,149,397,398,
481,478,477,473,409,308,250,208,198,192,184,167,163,121,118,116,112,107,102,
  97,92,86,60,17,15,14,13,12,11,0,149,397,398,
473,17,15,14,13,12,11,0,20,148,
477,473,308,208,163,118,112,17,15,14,13,12,11,0,147,301,
473,437,124,17,15,14,13,12,11,0,423,
473,437,124,17,15,14,13,12,11,0,428,
473,437,124,17,15,14,13,12,11,0,8,425,
473,437,124,17,15,14,13,12,11,0,423,
432,422,0,414,420,
431,0,419,
429,0,418,
429,422,0,414,418,
424,0,415,
481,478,477,473,459,458,457,456,454,409,308,250,208,198,192,184,167,163,121,
  118,116,112,107,102,97,92,86,39,37,36,17,15,14,13,12,11,0,35,55,262,276,
  277,278,
473,17,15,14,13,12,11,0,19,261,
250,208,198,163,118,102,61,60,59,37,36,31,30,0,35,54,55,56,57,
473,17,15,14,13,12,11,0,
473,17,15,14,13,12,11,0,19,186,191,321,
473,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
326,325,324,323,0,322,
482,481,480,479,478,477,476,475,474,473,472,471,470,469,468,467,466,465,464,
  409,405,308,250,208,198,192,184,167,163,124,121,118,116,112,107,102,97,
  92,86,61,60,51,49,47,45,43,41,37,36,17,15,14,13,12,11,0,234,
39,31,30,0,32,33,34,38,
477,473,308,208,163,118,112,17,15,14,13,12,11,0,301,396,
473,17,15,14,13,12,11,0,
473,121,17,15,14,13,12,11,0,406,
473,17,15,14,13,12,11,0,402,
477,473,308,208,163,118,112,17,15,14,13,12,11,0,301,
477,473,308,208,163,118,112,17,15,14,13,12,11,0,301,
477,473,308,208,163,118,112,17,15,14,13,12,11,0,
477,473,308,304,208,163,118,112,60,49,37,36,31,30,17,15,14,13,12,11,0,301,
  302,
304,60,49,37,36,31,30,0,298,299,300,
60,37,36,31,30,0,295,314,
477,473,308,208,163,118,112,60,37,36,31,30,17,15,14,13,12,11,0,296,297,301,
  306,
477,473,308,208,163,118,112,17,15,14,13,12,11,0,296,297,301,
60,37,36,31,30,0,295,314,
473,17,15,14,13,12,11,0,8,315,
481,478,477,473,409,308,250,208,198,192,184,167,163,127,126,125,124,121,118,
  116,112,107,102,97,92,86,17,15,14,13,12,11,0,96,145,158,159,
39,37,36,31,30,0,35,38,55,56,57,
473,39,37,36,17,15,14,13,12,11,0,444,
477,473,308,208,163,118,112,17,15,14,13,12,11,0,
473,39,17,15,14,13,12,11,0,453,
477,473,308,208,163,118,112,17,15,14,13,12,11,0,
473,17,15,14,13,12,11,0,
473,17,15,14,13,12,11,0,16,
473,17,15,14,13,12,11,0,
477,473,308,208,163,118,112,17,15,14,13,12,11,0,
39,0,38,
39,0,38,
53,0,52,
39,0,38,
53,0,52,
39,0,38,
39,0,38,
39,0,38,
53,0,52,
481,479,478,477,476,475,474,473,471,470,469,467,466,463,462,461,460,409,405,
  308,250,208,198,192,184,167,163,124,121,118,116,112,107,102,97,92,86,61,
  60,51,49,39,17,15,14,13,12,11,0,330,455,
481,479,478,477,476,475,474,473,471,470,469,467,466,463,462,461,460,409,405,
  308,250,208,198,192,184,167,163,124,121,118,116,112,107,102,97,92,86,61,
  60,51,49,39,17,15,14,13,12,11,0,330,455,
481,479,478,477,476,475,474,473,471,470,469,467,466,463,462,461,460,409,405,
  308,250,208,198,192,184,167,163,124,121,118,116,112,107,102,97,92,86,61,
  60,51,49,39,17,15,14,13,12,11,0,330,455,
481,478,477,473,409,308,250,208,198,192,184,167,163,121,118,116,112,107,102,
  97,92,86,39,17,15,14,13,12,11,0,276,
37,36,0,35,55,56,
473,17,15,14,13,12,11,0,
37,36,0,35,55,56,
473,17,15,14,13,12,11,0,19,191,321,
473,17,15,14,13,12,11,0,19,223,
250,208,198,167,163,118,116,112,107,102,97,92,61,60,59,37,36,31,30,0,222,
477,473,308,208,163,118,112,17,15,14,13,12,11,0,
60,0,
477,473,308,208,163,118,112,17,15,14,13,12,11,0,
477,473,308,208,163,118,112,17,15,14,13,12,11,0,297,301,
49,0,298,
473,17,15,14,13,12,11,0,8,
304,60,37,36,31,30,0,305,
39,37,36,31,30,0,38,317,
37,36,31,30,0,35,54,55,56,57,
473,17,15,14,13,12,11,0,19,261,
473,39,37,36,17,15,14,13,12,11,0,442,
477,473,308,208,163,118,112,39,37,36,17,15,14,13,12,11,0,443,
473,39,17,15,14,13,12,11,0,452,
477,473,308,208,163,118,112,39,17,15,14,13,12,11,0,448,
473,17,15,14,13,12,11,0,
17,15,14,13,12,11,0,18,
473,60,39,37,36,31,30,17,15,14,13,12,11,0,
473,60,39,37,36,31,30,17,15,14,13,12,11,0,
473,60,39,37,36,31,30,17,15,14,13,12,11,0,
473,60,39,37,36,31,30,17,15,14,13,12,11,0,
473,60,39,37,36,31,30,17,15,14,13,12,11,0,
473,17,15,14,13,12,11,0,
477,473,308,208,163,118,112,39,37,36,17,15,14,13,12,11,0,438,
431,0,419,
424,0,415,
473,437,124,17,15,14,13,12,11,0,423,
424,0,415,
473,437,124,17,15,14,13,12,11,0,430,
431,0,419,
431,0,419,
424,0,415,
473,437,124,17,15,14,13,12,11,0,8,425,
481,479,478,477,476,475,474,473,471,470,469,467,466,409,405,308,250,208,198,
  192,184,167,163,124,121,118,116,112,107,102,97,92,86,61,60,51,49,39,17,
  15,14,13,12,11,0,
53,0,
481,478,477,473,459,458,457,456,454,409,308,250,208,198,192,184,167,163,121,
  118,116,112,107,102,97,92,86,39,37,36,17,15,14,13,12,11,0,35,55,262,276,
  277,278,
473,37,36,31,30,17,15,14,13,12,11,0,20,320,
473,37,36,17,15,14,13,12,11,0,19,35,55,187,191,321,
39,37,36,31,30,0,35,38,54,55,56,57,
250,208,198,167,163,118,116,112,107,102,97,92,61,60,59,37,36,31,30,0,35,54,
  55,56,57,
477,473,308,208,163,118,112,17,15,14,13,12,11,0,
477,473,308,208,163,118,112,17,15,14,13,12,11,0,301,396,
60,0,
477,473,308,208,163,118,112,17,15,14,13,12,11,0,296,297,301,
473,17,15,14,13,12,11,0,19,316,
31,30,0,32,33,34,
37,36,31,30,0,35,55,56,57,
473,39,37,36,17,15,14,13,12,11,0,441,
477,473,308,208,163,118,112,39,37,36,17,15,14,13,12,11,0,439,
473,39,17,15,14,13,12,11,0,451,
477,473,308,208,163,118,112,39,17,15,14,13,12,11,0,447,
39,0,38,
473,39,17,15,14,13,12,11,0,442,
477,473,308,208,163,118,112,17,15,14,13,12,11,0,
39,0,38,
39,0,38,
477,473,308,208,163,118,112,17,15,14,13,12,11,0,287,
473,17,15,14,13,12,11,0,
37,36,0,35,55,56,189,190,
478,477,473,409,308,250,208,198,192,184,167,163,118,116,112,107,102,97,92,
  86,17,15,14,13,12,11,0,225,237,
31,30,0,32,33,34,
60,0,
473,17,15,14,13,12,11,0,8,
250,208,198,167,163,118,116,112,107,102,97,92,61,60,59,37,36,31,30,0,35,54,
  55,56,57,
473,39,37,36,17,15,14,13,12,11,0,440,
477,473,308,208,163,118,112,39,37,36,17,15,14,13,12,11,0,438,
473,39,17,15,14,13,12,11,0,450,
477,473,308,208,163,118,112,39,17,15,14,13,12,11,0,446,
424,0,415,
477,473,308,208,163,118,112,39,17,15,14,13,12,11,0,439,
424,0,415,
424,0,415,
477,473,308,208,163,118,112,17,15,14,13,12,11,0,
473,37,36,17,15,14,13,12,11,0,19,35,55,188,191,321,
37,36,0,35,55,56,189,
478,477,473,409,308,250,208,198,192,184,167,163,118,116,112,107,102,97,92,
  86,17,15,14,13,12,11,0,
37,36,31,30,0,35,54,55,56,57,
250,208,198,167,163,118,116,112,107,102,97,92,61,60,59,37,36,31,30,0,224,
477,473,308,208,163,118,112,17,15,14,13,12,11,0,301,396,
60,0,
473,39,17,15,14,13,12,11,0,449,
477,473,308,208,163,118,112,39,17,15,14,13,12,11,0,445,
31,30,0,32,33,34,
250,208,198,167,163,118,116,112,107,102,97,92,61,60,59,37,36,31,30,0,35,54,
  55,56,57,
60,0,
473,17,15,14,13,12,11,0,8,
473,39,17,15,14,13,12,11,0,444,
477,473,308,208,163,118,112,39,17,15,14,13,12,11,0,443,
250,208,198,167,163,118,116,112,107,102,97,92,61,60,59,37,36,31,30,0,226,
477,473,308,208,163,118,112,17,15,14,13,12,11,0,301,396,
250,208,198,167,163,118,116,112,107,102,97,92,61,60,59,37,36,31,30,0,35,54,
  55,56,57,
60,0,
477,473,308,208,163,118,112,17,15,14,13,12,11,0,301,396,
60,0,
477,473,308,208,163,118,112,17,15,14,13,12,11,0,301,396,
60,0,
477,473,308,208,163,118,112,17,15,14,13,12,11,0,301,396,
60,0,
477,473,308,208,163,118,112,17,15,14,13,12,11,0,301,396,
60,0,
477,473,308,208,163,118,112,17,15,14,13,12,11,0,301,396,
60,0,
477,473,308,208,163,118,112,17,15,14,13,12,11,0,301,

};


static unsigned const char ag_astt[10361] = {
  8,1,1,1,7,0,1,1,1,1,3,7,9,9,1,5,3,3,4,7,1,1,1,7,8,1,1,1,1,1,2,2,1,1,1,2,5,
  5,5,5,5,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,4,4,7,1,4,4,4,7,1,4,4,4,
  7,1,4,4,4,7,1,4,4,4,7,1,4,4,4,7,1,5,2,2,7,1,1,1,1,1,3,5,2,2,7,1,1,1,1,1,3,
  4,4,4,7,1,4,4,4,7,1,4,4,4,7,1,5,2,2,7,1,1,1,1,1,3,1,1,1,1,1,2,2,1,1,1,2,5,
  3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,1,3,4,8,8,8,8,8,7,1,1,1,1,1,1,5,2,2,7,1,1,1,
  1,1,5,2,2,7,1,1,1,1,1,5,2,2,7,1,1,1,1,1,5,2,2,7,1,1,1,1,1,5,2,2,7,1,1,1,1,
  1,5,2,2,7,1,1,1,1,1,2,2,5,3,3,2,7,1,2,7,1,5,2,2,7,1,1,1,1,1,5,2,2,7,1,1,1,
  1,1,5,2,2,7,1,1,1,1,1,2,7,1,1,7,5,8,8,8,8,1,5,5,5,5,5,7,1,1,4,5,5,5,5,5,7,
  3,3,1,1,2,1,2,2,1,7,2,3,2,7,1,2,7,1,2,7,1,2,7,1,2,7,1,2,7,1,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,5,
  5,5,5,7,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,1,2,1,1,1,1,1,2,7,1,2,7,
  1,2,7,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  5,5,5,5,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,5,2,2,7,1,1,1,1,1,4,4,4,4,4,4,4,4,4,
  4,7,3,5,1,1,1,1,5,5,5,5,5,7,1,1,1,1,1,1,1,3,2,2,5,5,7,1,1,1,1,1,5,2,2,5,5,
  5,5,5,5,7,1,1,1,1,1,5,5,2,2,5,5,5,5,5,7,1,1,1,1,1,5,5,5,5,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  5,5,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,3,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  5,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  5,5,5,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,5,5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5,5,1,1,1,5,5,1,1,
  1,1,1,1,7,1,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,8,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5,5,1,1,1,
  5,5,1,1,1,1,1,1,7,1,1,2,1,5,7,1,1,3,1,9,1,9,9,1,9,1,9,9,9,9,1,9,1,1,9,9,5,
  5,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,1,9,1,4,9,9,9,9,9,9,9,9,9,7,1,7,2,
  7,1,2,2,1,7,1,1,2,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,7,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,7,1,2,1,1,1,2,3,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,2,1,1,1,1,1,1,1,7,1,2,1,1,1,2,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,1,2,7,1,4,4,4,
  4,4,4,4,4,4,4,7,3,4,4,4,4,4,4,4,4,4,4,7,3,4,4,4,4,4,4,4,4,4,4,7,3,4,4,4,4,
  4,4,4,4,4,4,7,3,1,1,1,1,5,1,1,1,1,3,3,2,1,7,2,1,1,1,1,2,1,1,7,2,1,1,2,1,1,
  1,1,1,7,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,3,3,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,2,1,2,
  7,1,8,1,8,8,8,8,8,7,1,1,2,2,1,7,1,1,2,1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,5,3,3,3,3,3,3,3,3,3,3,
  3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
  3,3,3,3,3,3,3,3,3,3,3,3,7,3,7,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,5,3,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,3,3,
  3,1,5,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5,5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,5,5,1,1,1,5,5,1,1,1,1,1,1,7,1,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5,5,1,1,1,5,5,1,1,1,1,1,1,7,1,1,2,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,7,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  7,1,1,2,7,2,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,7,1,2,1,1,2,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,1,1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,5,
  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,1,2,1,7,1,1,2,4,4,4,4,4,4,4,4,4,4,
  4,4,4,4,4,4,4,4,4,7,1,2,1,7,1,1,2,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,4,2,2,7,1,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,1,1,1,1,1,1,1,5,
  1,2,2,5,5,7,1,1,1,1,1,1,1,1,1,1,1,1,7,2,2,2,7,1,1,1,5,5,5,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,2,2,5,5,5,5,5,5,5,7,1,1,1,1,1,2,5,5,5,1,5,5,5,5,5,5,5,5,5,
  5,5,5,5,5,1,1,1,1,1,7,3,1,3,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,2,
  1,2,2,1,7,1,1,2,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,2,2,5,5,5,5,5,5,5,5,7,1,1,1,1,1,5,5,5,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,5,5,5,5,5,5,
  7,1,1,1,1,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,2,2,5,5,5,5,5,5,5,5,7,1,1,1,1,1,4,4,4,7,1,9,9,9,9,9,9,9,9,9,
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,4,3,5,2,2,4,4,7,1,1,1,1,1,2,1,7,1,1,2,
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,4,3,5,2,2,7,1,1,1,
  1,1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,4,3,2,2,7,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,7,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,7,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,7,1,1,1,2,2,7,1,2,2,7,1,2,2,5,5,7,1,
  1,1,1,1,9,1,9,9,1,9,1,9,9,9,9,9,1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  9,1,9,1,9,9,9,9,9,9,9,9,9,4,5,2,2,7,1,1,1,1,1,9,5,1,1,1,1,1,1,7,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,7,1,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,7,1,2,1,1,2,1,9,9,9,9,
  9,9,9,9,1,9,1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  9,5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,8,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,1,1,1,1,1,1,5,5,5,5,7,1,1,3,
  2,7,1,2,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,7,1,1,1,3,1,7,2,2,5,5,7,1,1,1,1,1,5,5,5,5,5,5,5,5,5,5,
  5,5,5,5,5,2,2,5,5,7,1,2,1,1,2,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,1,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,7,1,2,1,1,2,4,4,4,4,4,4,4,4,4,4,4,4,4,
  4,4,4,4,4,4,7,1,5,5,5,5,5,5,5,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,4,4,4,4,4,4,4,
  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,1,9,9,9,9,9,9,9,5,2,1,7,1,1,
  2,1,1,1,1,1,1,1,7,1,2,2,2,1,1,1,1,1,7,3,3,1,2,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
  4,4,4,4,4,4,4,4,4,4,4,4,7,1,3,5,2,2,7,1,1,1,1,1,2,1,7,1,1,2,9,9,9,9,9,9,9,
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  9,9,9,9,9,9,9,9,9,9,9,5,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,1,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,7,1,2,1,1,2,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  2,1,1,1,1,1,1,1,7,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,7,1,2,1,1,2,5,2,2,7,1,1,1,1,
  1,3,2,7,1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,1,2,7,1,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,9,9,9,9,9,9,9,9,
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,4,3,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,9,9,9,9,9,9,9,9,9,9,
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,4,3,5,5,5,5,2,2,7,1,1,1,1,1,9,9,9,9,9,9,
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,4,3,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,5,5,2,2,7,1,1,1,1,1,5,5,
  2,2,7,1,1,1,1,1,2,1,7,1,1,2,1,7,1,1,1,5,5,1,5,5,1,1,1,1,1,1,7,1,1,2,2,7,1,
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,5,3,3,3,3,3,7,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,3,3,3,
  3,1,5,3,2,1,7,1,1,2,2,1,7,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,7,9,9,9,9,9,9,9,
  9,9,9,9,9,1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,5,3,3,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,8,5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5,
  5,5,5,1,1,1,1,1,1,7,1,1,1,1,1,1,1,2,1,7,1,1,2,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  5,2,2,5,5,7,1,2,1,1,2,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,7,1,2,1,1,2,8,
  8,8,8,8,1,8,8,8,8,8,8,8,8,7,1,1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
  4,4,4,4,4,4,4,4,7,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,7,1,1,1,1,1,1,1,
  1,1,1,1,1,7,2,2,5,5,7,1,1,1,1,1,1,7,3,1,1,1,1,2,7,1,5,5,5,5,5,5,5,5,5,5,5,
  5,5,5,5,2,2,5,5,7,1,3,1,1,3,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,7,1,2,1,
  1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,2,1,7,1,1,2,4,4,4,4,4,4,4,4,4,4,
  4,4,4,4,4,4,4,4,4,7,1,2,1,7,1,1,2,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,
  1,2,1,7,1,1,2,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,1,2,7,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,4,2,1,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,7,1,3,1,1,3,5,2,2,5,
  5,5,5,5,5,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,7,1,1,1,1,1,1,2,2,7,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,7,1,1,1,1,2,2,7,1,2,2,7,1,4,4,4,4,4,4,4,4,4,4,4,4,
  4,4,4,4,4,4,4,7,1,2,7,1,9,9,9,9,9,9,9,9,9,5,3,2,2,5,5,7,1,1,1,1,1,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,7,1,2,1,1,2,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,
  2,5,5,7,1,2,1,1,2,3,3,3,3,3,3,3,3,3,3,3,3,3,7,9,9,9,9,9,9,9,9,9,9,9,9,1,9,
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,5,3,3,3,1,5,1,5,1,5,
  5,5,5,7,2,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,7,1,2,1,1,2,1,1,1,1,1,1,1,
  1,1,1,1,1,1,7,2,1,2,2,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,7,3,1,1,1,1,1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,3,1,1,1,1,1,1,
  1,7,2,1,7,2,1,2,5,2,2,7,1,1,1,1,1,2,1,7,1,1,2,1,5,3,1,3,5,2,2,5,5,5,5,5,7,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5,5,1,1,1,1,1,1,7,2,1,2,2,1,7,1,1,2,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,7,1,2,1,1,2,5,5,5,5,5,5,5,5,5,5,5,5,
  5,5,5,2,2,5,5,7,1,2,1,1,2,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,7,1,2,1,1,
  2,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,7,1,2,1,1,2,5,5,5,5,5,5,5,5,5,5,5,
  5,5,5,5,2,2,5,5,7,1,2,1,1,2,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,7,1,2,1,
  1,2,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,4,3,1,1,1,1,2,1,1,7,
  2,1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,4,3,2,2,7,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,7,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,7,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,7,1,1,2,2,7,1,2,2,7,1,2,2,7,1,2,2,7,1,2,2,7,1,2,2,7,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5,5,1,1,1,1,
  1,1,7,1,1,3,2,2,7,1,2,2,7,1,2,2,7,1,2,2,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,2,2,1,1,1,1,1,1,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,2,2,1,1,1,1,1,1,7,1,1,1,2,2,7,1,2,2,7,1,2,2,7,1,5,5,5,5,5,5,5,5,5,5,5,
  5,5,5,5,2,2,5,5,7,1,2,1,1,2,2,2,5,5,7,1,1,1,1,1,2,1,7,2,1,2,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,8,5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5,5,5,5,1,1,1,
  1,1,1,7,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,8,5,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,5,5,5,5,1,1,1,1,1,1,7,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,1,3,1,
  9,9,9,9,9,9,9,9,9,9,9,9,9,5,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,9,9,9,9,9,9,9,9,
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,4,3,2,7,1,2,2,7,1,1,1,2,1,7,1,1,2,
  2,2,7,1,1,1,1,1,1,1,1,1,1,1,1,1,7,2,7,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  5,5,2,2,5,5,5,5,5,5,5,7,1,2,1,1,2,1,1,1,1,1,1,7,1,2,2,5,5,7,1,1,1,3,4,4,4,
  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,1,1,1,1,1,2,1,1,7,2,1,2,2,5,5,7,1,1,1,1,
  1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,4,3,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,9,9,9,9,9,9,9,9,9,
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,4,3,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  5,5,5,5,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  5,5,5,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,5,5,5,2,2,5,5,5,5,5,5,7,1,1,1,
  1,1,5,5,5,5,5,5,5,5,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,5,5,5,5,5,5,5,5,5,5,2,2,
  5,5,5,5,5,5,7,1,1,1,1,1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  9,9,9,9,9,9,9,9,9,9,9,9,5,3,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,5,5,5,5,2,2,5,5,5,5,5,5,
  7,1,1,1,1,1,5,5,5,5,5,5,5,5,5,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,5,5,5,5,5,5,5,5,
  5,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  5,5,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,5,5,5,5,5,5,5,5,5,5,2,2,5,5,5,5,5,5,7,1,
  1,1,1,1,5,5,5,5,5,5,5,5,5,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,5,5,5,5,5,5,5,5,5,
  5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,2,1,7,1,1,2,9,9,9,9,9,9,9,9,9,9,9,9,1,1,9,9,
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,5,5,5,5,9,9,9,9,9,9,7,3,3,3,1,1,1,1,
  1,1,1,7,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,1,
  1,1,2,2,2,2,1,1,1,1,1,1,1,1,2,2,2,2,1,1,1,2,1,1,7,2,3,3,1,1,2,1,1,1,1,1,4,
  4,4,4,4,4,4,4,4,4,4,4,4,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,
  2,1,1,1,1,1,1,7,3,3,3,1,2,2,5,5,7,1,1,1,3,3,2,1,7,1,1,2,1,1,1,1,1,1,1,7,4,
  4,4,4,4,4,4,4,4,7,1,2,2,7,1,1,1,5,2,2,5,5,5,5,5,7,1,1,1,1,1,3,2,2,5,1,3,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,7,1,2,1,1,2,2,2,7,1,2,1,7,1,1,2,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,2,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,7,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,
  1,2,1,1,1,1,1,1,7,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,
  2,1,1,1,1,1,1,7,2,2,1,1,1,2,2,1,1,1,1,1,1,7,1,2,2,1,1,1,1,1,2,1,1,2,1,1,1,
  1,1,1,7,2,2,1,1,1,1,1,1,2,1,1,1,2,1,1,1,1,1,1,7,2,2,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,2,1,1,1,1,
  1,2,2,1,1,1,1,1,1,7,2,2,2,2,1,1,1,1,1,2,1,1,1,2,1,1,1,1,1,1,7,2,2,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,2,1,1,1,1,1,1,1,1,2,
  1,1,2,1,1,1,1,1,1,7,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,
  1,1,1,1,2,1,1,1,1,1,1,7,2,2,2,1,1,1,1,1,1,1,1,2,1,1,1,2,1,1,1,1,1,1,7,2,2,
  1,1,1,1,1,1,1,2,1,1,1,2,1,1,1,1,1,1,7,2,2,1,1,1,1,1,1,1,2,1,1,1,2,1,1,1,1,
  1,1,7,2,2,1,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,7,1,2,1,1,2,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,
  1,3,1,9,9,9,9,9,9,9,5,2,2,7,1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  9,9,9,9,9,4,3,2,2,4,1,1,1,2,7,1,2,7,1,2,7,1,2,7,1,2,7,1,2,7,1,2,7,1,2,7,1,
  2,7,1,2,7,1,2,7,1,2,7,1,2,5,1,2,2,7,1,1,1,2,5,1,5,5,5,5,5,5,5,5,5,2,2,5,5,
  7,1,2,1,1,2,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,4,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,5,3,3,3,1,4,4,4,4,
  4,4,4,4,4,4,4,4,4,7,1,1,1,1,1,1,1,1,7,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,1,2,2,
  2,1,1,1,2,1,1,7,2,3,1,3,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,1,1,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,7,1,2,1,1,2,9,9,9,9,9,9,9,9,9,9,9,9,9,
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,4,3,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  9,9,9,9,9,9,9,9,9,4,3,9,9,9,9,9,9,9,4,3,3,3,3,3,3,3,3,3,3,3,3,3,7,1,7,9,9,
  9,9,9,9,9,9,9,9,9,9,9,9,4,3,9,9,9,9,9,9,9,9,9,9,9,9,1,9,9,9,9,9,9,9,9,9,9,
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,4,3,3,1,1,5,5,5,5,1,1,1,1,1,1,7,1,1,3,1,
  1,1,1,1,1,7,3,3,3,3,3,3,7,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,1,1,1,1,1,1,1,1,1,
  1,1,1,7,3,3,1,3,3,3,3,7,1,1,1,1,1,1,1,8,5,5,5,5,1,1,1,1,1,1,7,1,1,1,1,1,1,
  7,1,2,1,1,7,3,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,4,3,
  2,4,1,2,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,5,5,5,
  5,7,1,1,1,1,1,1,2,2,2,2,1,1,1,2,1,1,7,2,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,7,2,1,1,1,1,1,1,1,1,1,7,1,2,1,1,1,1,1,1,1,1,1,1,1,1,
  1,7,2,1,1,1,2,1,1,1,1,1,1,7,2,1,1,2,1,1,1,1,1,1,7,2,1,1,2,1,1,1,2,1,1,7,2,
  2,1,1,2,1,1,1,1,1,1,7,2,1,1,7,1,1,1,7,1,1,7,1,1,1,7,1,1,1,7,3,1,1,1,1,2,2,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,7,3,3,2,1,1,2,
  1,1,1,1,2,1,1,7,2,1,5,5,5,5,5,5,5,5,5,2,2,5,5,7,1,2,1,1,2,1,1,1,1,1,1,1,7,
  1,1,1,1,2,1,1,7,2,1,2,1,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,2,2,2,2,4,2,9,9,9,9,
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,4,3,2,2,1,7,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  7,1,1,3,3,3,3,3,3,3,7,9,1,9,9,9,9,9,9,5,3,1,1,1,1,1,1,1,7,3,1,1,1,1,1,1,1,
  1,1,1,1,1,1,7,3,1,1,1,1,1,1,1,1,1,1,1,1,1,7,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,
  1,1,1,5,1,1,1,1,5,5,5,5,5,5,1,1,1,1,1,1,7,3,3,5,5,1,5,5,5,5,7,1,1,3,1,5,5,
  5,5,7,2,2,1,1,1,1,1,1,1,5,5,5,5,5,1,1,1,1,1,1,7,3,1,1,3,1,1,1,1,1,1,1,1,1,
  1,1,1,1,7,1,1,1,1,5,5,5,5,7,3,3,1,1,1,1,2,1,1,7,2,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,1,1,1,2,2,2,5,5,7,1,1,1,1,2,
  1,5,5,5,1,1,1,1,1,1,7,2,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,5,1,1,1,1,1,1,7,2,1,
  1,1,1,1,1,1,1,1,1,1,1,1,7,3,3,3,3,3,3,3,5,3,1,1,1,1,1,1,5,1,1,1,1,1,1,1,1,
  5,1,1,1,1,1,1,1,1,1,1,1,1,1,7,2,7,1,2,5,1,2,7,1,2,5,1,2,7,1,2,7,1,2,7,1,2,
  5,1,2,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,2,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,7,1,2,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  9,9,4,3,2,2,7,1,1,1,1,1,1,1,1,1,1,7,2,2,7,1,1,1,1,1,1,1,2,1,1,7,2,2,1,1,1,
  1,1,2,1,1,7,2,1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,7,1,7,3,3,3,3,3,3,3,3,3,3,3,3,3,5,1,1,1,1,1,1,1,1,1,1,1,1,1,7,3,
  1,1,5,3,1,1,1,1,1,1,1,7,1,1,5,5,5,5,5,7,3,2,5,5,5,5,7,1,3,2,2,5,5,7,1,1,1,
  1,1,1,1,1,1,2,1,1,7,2,1,1,5,5,5,1,1,1,1,1,1,7,3,1,1,1,1,1,1,1,5,5,5,1,1,1,
  1,1,1,7,2,1,5,1,1,1,1,1,1,7,3,1,1,1,1,1,1,1,5,1,1,1,1,1,1,7,2,3,3,3,3,3,3,
  3,7,3,3,3,3,3,3,5,3,5,5,5,5,5,5,5,5,5,5,5,5,5,7,5,5,5,5,5,5,5,5,5,5,5,5,5,
  7,5,5,5,5,5,5,5,5,5,5,5,5,5,7,5,5,5,5,5,5,5,5,5,5,5,5,5,7,5,5,5,5,5,5,5,5,
  5,5,5,5,5,7,3,3,3,3,3,3,3,5,2,2,2,2,2,2,2,5,5,5,2,2,2,2,2,2,7,2,1,7,1,1,7,
  3,1,1,2,1,1,1,1,1,1,7,2,1,7,3,1,1,2,1,1,1,1,1,1,7,2,1,7,1,1,7,1,1,7,3,1,1,
  2,1,1,1,2,1,1,7,2,2,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,5,1,7,1,1,1,1,2,2,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,7,3,3,2,1,1,2,1,5,5,5,5,1,1,1,1,1,1,
  7,1,3,1,2,2,1,1,1,2,1,1,7,2,3,3,1,2,1,2,2,2,5,5,7,1,1,1,1,1,1,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,2,2,5,5,7,1,2,1,1,2,3,3,3,3,3,3,3,3,3,3,3,3,3,7,1,1,1,1,
  1,1,1,1,1,1,1,1,1,7,1,1,1,7,1,1,1,1,1,1,1,1,1,1,1,1,1,7,3,1,1,1,1,1,1,2,1,
  1,7,2,3,2,1,7,1,1,2,2,2,5,5,7,1,1,1,2,1,5,5,5,1,1,1,1,1,1,7,3,1,1,1,1,1,1,
  1,5,5,5,1,1,1,1,1,1,7,3,1,5,1,1,1,1,1,1,7,3,1,1,1,1,1,1,1,5,1,1,1,1,1,1,7,
  3,2,5,1,1,5,1,1,1,1,1,1,7,2,1,1,1,1,1,1,1,1,1,1,1,1,1,7,2,5,1,2,5,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,7,1,9,9,9,9,9,9,9,5,2,2,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,1,2,1,7,1,1,2,1,7,1,1,1,1,1,1,1,7,1,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,7,1,2,1,1,2,3,5,5,5,3,3,3,3,3,3,7,3,
  3,3,3,3,3,3,3,5,5,5,3,3,3,3,3,3,7,3,1,5,1,1,1,1,1,1,7,3,1,1,1,1,1,1,1,5,1,
  1,1,1,1,1,7,3,1,7,3,1,1,1,1,1,1,1,5,1,1,1,1,1,1,7,2,1,7,3,1,7,3,9,9,9,9,9,
  9,9,9,9,9,9,9,9,5,1,2,2,1,1,1,2,1,1,7,2,3,3,3,2,1,2,2,5,1,1,1,3,9,9,9,9,9,
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,4,2,2,5,5,7,1,1,1,1,1,4,4,4,4,4,
  4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,1,1,7,1,5,1,
  1,1,1,1,1,7,3,1,1,1,1,1,1,1,5,1,1,1,1,1,1,7,3,2,1,7,1,1,2,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,2,2,5,5,7,1,2,1,1,2,1,7,1,1,1,1,3,1,1,7,3,1,5,1,1,1,1,1,1,7,
  3,1,1,1,1,1,1,1,5,1,1,1,1,1,1,7,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,7,
  1,2,1,1,2,1,7,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,1,1,7,1,1,1,1,1,1,1,1,1,1,1,1,
  1,7,1,1,1,7,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,1,1,7,1,1,1,1,1,1,1,1,1,1,1,1,1,
  7,1,1,1,7,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,1,1,7,1,1,1,1,1,1,1,1,1,1,1,1,1,7,
  2
};


static const unsigned short ag_pstt[] = {
3,2,2,1,0,0,2,2,2,3,
38,1,
65,65,1,67,65,65,
90,3,5,4,
6,4,
19,8,9,7,10,11,116,113,14,15,16,96,71,71,71,71,71,5,18,18,18,19,18,18,18,18,
  18,18,18,18,18,18,18,17,13,12,18,
91,91,91,6,20,
181,181,181,7,21,
226,226,226,8,22,
214,214,214,9,23,
179,179,179,10,24,
118,118,118,11,25,
55,43,42,12,26,27,26,26,27,115,
55,43,42,13,26,28,26,26,28,112,
110,110,110,14,29,
104,104,104,15,30,
98,98,98,16,31,
55,43,42,17,26,32,26,26,32,95,
8,9,7,10,11,116,113,14,15,16,96,72,70,70,70,70,70,70,70,70,70,70,70,70,70,
  17,13,12,70,
277,36,36,36,36,36,19,35,35,35,36,34,33,
55,43,42,20,26,37,26,26,37,
55,43,42,21,26,38,26,26,38,
55,43,42,22,26,39,26,26,39,
55,43,42,23,26,40,26,26,40,
55,43,42,24,26,41,26,26,41,
55,43,42,25,26,42,26,26,42,
43,42,56,54,54,
50,27,43,
50,28,44,
55,43,42,29,26,45,26,26,45,
55,43,42,30,26,46,26,26,46,
55,43,42,31,26,47,26,26,47,
50,32,48,
49,33,
261,51,51,51,51,15,261,261,261,261,261,34,50,51,
277,77,77,77,77,77,35,75,75,34,33,
61,52,58,60,1,36,60,78,
50,37,53,
50,38,54,
50,39,55,
50,40,56,
50,41,57,
50,42,58,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,
  55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,55,55,55,55,43,26,
  59,26,26,59,117,
60,64,62,64,64,62,64,62,64,64,64,64,60,64,62,60,64,64,61,64,64,64,64,64,64,
  64,64,64,64,64,64,64,64,64,64,64,64,64,62,64,62,64,64,64,64,64,64,64,64,
  64,44,66,64,114,67,65,63,63,63,
50,45,68,
50,46,69,
50,47,70,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,
  55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,55,55,55,55,48,26,71,
  26,26,71,
55,43,42,49,26,72,26,26,72,
260,260,260,260,260,260,260,260,260,260,50,262,
266,8,9,10,11,266,266,266,266,266,51,76,75,74,73,77,77,77,268,
43,42,55,55,52,26,78,26,26,78,
55,43,42,55,55,55,55,55,55,53,26,79,26,26,79,
55,55,43,42,55,55,55,55,55,54,26,80,26,26,80,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,
  55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,
  55,55,55,43,42,55,55,55,55,55,55,55,26,81,26,26,81,227,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,
  55,55,55,55,56,26,82,26,26,82,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,
  55,55,55,55,55,57,26,83,26,26,83,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,
  55,43,42,55,55,55,55,55,55,58,26,84,26,26,84,
85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,87,85,85,85,85,85,85,85,85,85,
  85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,59,86,88,
89,89,89,89,89,89,89,89,89,89,89,89,89,89,414,414,89,89,89,89,89,89,89,89,
  89,89,89,89,89,89,89,89,89,89,89,89,414,414,89,89,89,414,414,89,89,89,
  89,89,89,60,89,89,416,
91,91,91,91,91,91,91,91,91,91,91,91,91,91,91,91,91,91,91,91,90,91,91,91,91,
  91,91,91,91,91,91,91,91,91,91,91,91,91,91,91,91,91,91,91,91,91,91,91,91,
  91,91,91,91,91,91,91,61,91,91,91,91,
92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,
  92,92,92,92,92,92,92,92,92,92,92,92,30,30,92,92,92,30,30,92,92,92,92,92,
  92,62,92,92,32,
93,397,63,94,94,399,
95,34,96,34,34,96,34,96,34,34,34,34,95,34,96,95,34,34,417,417,34,34,34,34,
  34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,96,34,96,35,34,34,34,34,34,
  34,34,34,34,64,
97,65,
47,66,98,
45,41,100,67,101,100,41,99,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,68,26,102,26,
  26,102,
103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,
  103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,
  103,103,103,103,103,103,103,103,103,103,103,103,103,41,100,103,103,103,
  103,103,103,69,105,1,103,104,100,41,105,
103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,
  103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,
  103,103,103,103,103,103,103,103,103,103,103,103,103,41,100,103,103,103,
  103,103,103,70,107,1,103,106,100,41,99,
108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,
  108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,
  108,108,108,108,108,108,108,71,109,108,
50,72,110,
275,275,275,275,275,275,275,275,275,275,73,276,
273,273,273,273,273,273,273,273,273,273,74,274,
271,271,271,271,271,271,271,271,271,271,75,272,
269,269,269,269,269,269,269,269,269,269,76,270,
8,9,10,11,267,76,75,74,73,265,265,
59,1,78,59,
111,111,111,111,94,111,111,79,94,112,
113,368,113,113,113,113,113,80,116,116,115,114,367,
117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,
  117,117,117,117,119,120,121,122,117,117,117,117,117,117,117,117,117,117,
  117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,
  117,117,117,81,228,229,118,
123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,
  123,123,123,123,123,123,123,123,82,123,123,125,124,
126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,
  126,126,126,126,126,126,126,126,126,83,127,126,126,
128,128,128,128,128,128,128,128,128,128,128,128,128,130,131,132,133,134,128,
  128,128,128,128,128,128,128,128,128,128,128,128,128,84,135,129,128,128,
136,62,136,136,62,136,62,136,136,136,136,136,62,136,136,136,136,136,136,136,
  136,136,136,136,136,136,136,136,136,136,136,136,136,136,62,136,62,136,
  136,136,136,136,136,136,136,136,85,37,136,
47,86,137,
139,138,139,139,139,139,139,87,138,139,
45,41,100,88,141,100,41,140,
413,413,413,413,413,413,413,413,413,413,413,413,413,413,413,413,413,413,413,
  413,413,413,413,413,413,413,413,413,413,413,413,413,413,413,413,413,413,
  413,413,413,413,413,413,415,413,
428,428,428,428,428,428,428,428,428,428,428,428,428,428,428,428,428,428,428,
  428,428,428,428,428,428,428,428,428,428,428,428,428,428,428,428,428,428,
  428,428,428,428,428,428,428,428,428,428,428,428,428,428,428,428,428,428,
  428,428,428,90,
432,91,
29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,
  29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,31,29,
60,142,142,142,142,142,142,142,142,60,142,60,142,142,61,142,142,142,142,142,
  142,142,142,142,142,142,142,142,142,142,142,142,142,142,142,142,142,142,
  142,142,142,142,142,142,93,142,394,394,394,
93,398,396,
89,89,89,89,89,89,89,89,89,89,89,89,89,89,414,414,89,89,89,89,89,89,89,89,
  89,89,89,89,89,89,89,89,89,89,89,89,414,414,89,89,89,414,414,89,89,89,
  89,89,89,95,89,89,418,
92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,
  92,92,92,92,92,92,92,92,92,92,92,92,30,30,92,92,92,30,30,92,92,92,92,92,
  92,96,92,92,36,
60,142,142,142,142,142,142,142,142,60,142,60,142,142,143,142,142,142,142,
  142,142,142,142,142,142,142,142,142,142,142,142,142,142,142,142,142,142,
  142,142,142,142,142,142,142,97,142,393,144,144,144,144,
60,142,142,142,142,142,142,142,142,60,142,60,142,142,61,142,142,142,142,142,
  142,142,142,142,142,142,142,142,142,142,142,142,142,142,142,142,142,142,
  142,142,142,142,142,142,98,142,145,65,63,63,63,
136,62,136,136,62,136,62,136,136,136,136,136,62,136,136,136,136,136,136,136,
  136,136,136,136,136,136,136,136,136,136,136,136,136,136,62,136,62,136,
  136,136,136,136,136,136,136,136,99,146,136,
40,100,40,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,101,26,390,26,26,
  390,
147,147,147,147,147,147,147,147,147,147,147,147,147,147,147,147,147,147,147,
  102,149,148,148,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,
  104,150,
41,100,105,151,100,41,
102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,
  106,152,
41,100,107,153,100,41,
388,388,388,388,388,388,388,388,388,388,388,388,388,388,388,388,388,388,388,
  388,388,388,388,388,388,388,388,388,388,388,388,388,388,388,388,388,388,
  388,388,388,388,388,388,388,389,
43,42,109,154,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,
  55,55,55,55,55,55,110,26,155,26,26,155,
156,156,156,156,156,156,156,22,156,
43,42,55,55,112,26,157,26,26,157,
158,158,158,158,158,158,158,113,371,
43,42,114,159,159,159,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,55,55,
  55,55,55,115,26,26,26,160,
113,368,184,184,184,161,184,184,184,184,184,184,184,184,184,184,184,184,184,
  184,113,113,113,113,113,116,183,162,186,115,114,367,
163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,
  163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,
  163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,
  117,313,163,
49,41,100,118,164,100,41,165,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,
  55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,55,55,55,55,55,55,
  119,26,166,26,26,166,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,
  55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,55,55,55,55,55,55,
  120,26,167,26,26,167,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,
  55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,55,55,55,55,55,55,
  121,26,168,26,26,168,
234,234,234,122,169,
167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,
  167,167,167,167,167,167,167,167,220,167,
55,43,42,217,217,124,26,170,26,26,170,
41,100,125,171,100,41,
384,384,384,384,384,384,384,384,384,384,384,384,384,384,384,384,384,384,384,
  384,384,384,384,384,384,384,384,384,385,384,
55,43,42,127,26,172,26,26,172,
167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,
  167,167,167,167,167,167,167,167,168,167,
43,42,129,173,
174,174,174,174,174,174,174,174,174,174,174,174,174,174,174,174,174,174,174,
  174,174,43,42,174,174,174,174,174,174,130,175,174,174,
176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,
  176,176,43,42,176,176,176,176,176,176,131,177,176,176,
178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,
  178,178,43,42,178,178,178,178,178,178,132,179,178,178,
43,42,133,180,
43,42,134,181,
43,42,55,55,135,26,182,26,26,182,
34,96,34,34,96,34,96,34,34,34,34,34,96,34,34,34,34,34,34,34,34,34,34,34,34,
  34,34,34,34,34,34,34,34,34,96,34,96,34,34,34,34,34,34,34,34,34,35,
55,43,42,137,26,183,26,26,183,
464,466,
184,184,184,184,184,184,139,
136,62,136,136,62,136,62,136,136,136,136,136,62,136,136,136,136,136,136,136,
  136,136,136,136,136,136,136,136,136,136,136,136,136,136,62,136,62,136,
  136,136,136,136,136,136,136,136,140,185,136,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,141,26,460,26,26,
  460,
95,34,34,34,34,34,34,34,34,95,34,95,34,34,34,34,34,34,34,34,34,34,34,34,34,
  34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,417,
186,186,186,186,186,186,186,186,186,186,186,186,186,186,186,186,186,186,186,
  90,187,186,186,186,186,186,186,186,186,186,186,186,186,186,186,186,186,
  186,186,186,186,186,186,186,186,186,186,186,186,186,186,186,186,186,186,
  186,143,186,186,186,186,187,186,
188,403,403,403,403,144,189,189,405,
48,145,190,
46,146,191,
193,193,193,193,193,193,193,193,193,193,193,193,192,450,193,193,193,193,193,
  193,193,193,193,193,193,193,193,193,193,193,193,193,193,193,193,193,193,
  193,193,193,193,147,193,193,193,452,
194,148,
43,42,55,55,149,26,195,26,26,195,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,150,26,109,26,26,
  109,
106,106,106,106,106,106,106,106,106,106,106,106,106,106,106,106,106,106,106,
  151,196,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,152,26,103,26,26,
  103,
100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,
  153,197,
55,55,55,55,55,55,55,55,43,42,55,55,55,55,55,55,154,26,198,26,26,198,
278,278,278,278,278,278,278,278,278,278,278,278,278,278,278,278,278,278,278,
  278,278,278,278,278,278,278,278,278,278,155,199,
24,24,24,24,24,24,24,25,
41,100,157,200,100,41,
201,201,201,201,201,201,201,158,
113,370,43,42,113,113,113,113,113,159,54,54,202,369,
190,190,190,190,190,190,188,190,190,190,190,190,190,190,190,190,190,190,190,
  190,190,190,190,190,190,190,160,203,191,
55,43,42,161,26,204,26,26,204,
41,100,162,205,100,41,
318,318,318,318,318,318,318,318,318,318,318,318,318,318,318,318,318,318,318,
  318,318,318,318,318,318,318,318,318,318,318,318,318,318,318,318,318,318,
  318,318,318,318,318,318,318,318,318,318,318,318,318,318,318,318,318,318,
  319,
232,232,232,232,232,232,232,232,232,232,232,232,232,232,232,232,232,232,232,
  164,206,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,
  55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,
  42,55,55,55,55,55,55,165,26,207,26,26,207,
85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,
  85,85,85,85,85,85,85,85,85,85,85,85,85,41,100,85,85,85,85,85,85,166,208,
  2,209,100,41,
85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,
  85,85,85,85,85,85,85,85,85,85,85,85,85,41,100,85,85,85,85,85,85,167,210,
  2,211,100,41,
85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,
  85,85,85,85,85,85,85,85,85,85,85,85,85,41,100,85,85,85,85,85,85,168,212,
  2,213,100,41,
55,43,42,169,26,214,26,26,214,235,
49,170,215,
215,215,215,215,215,215,215,215,215,215,215,215,215,215,215,215,215,215,215,
  171,216,
49,172,217,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,
  55,55,55,55,55,55,173,26,218,26,26,218,
167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,
  167,167,167,167,167,167,167,167,170,167,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,
  55,55,55,55,43,42,55,55,55,55,55,55,175,26,219,26,26,219,
167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,
  167,167,167,167,167,167,167,167,171,167,
55,55,55,55,43,42,177,26,220,26,26,220,
167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,
  167,167,167,167,167,167,167,167,169,167,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,
  43,42,55,55,55,55,55,55,179,26,221,26,26,221,
55,55,43,42,180,26,222,26,26,222,
55,55,43,42,181,26,223,26,26,223,
41,100,182,224,100,41,
87,183,225,
226,226,472,472,226,472,472,226,226,226,226,226,226,184,226,226,474,
46,185,227,
422,422,422,422,422,422,422,422,422,422,422,422,422,422,422,422,422,422,422,
  90,422,422,422,422,422,422,422,422,422,422,422,422,422,422,422,422,422,
  422,422,422,422,422,422,422,422,422,422,422,422,422,422,422,422,422,422,
  424,422,422,422,422,
425,187,
60,142,142,142,142,142,142,142,142,60,142,60,142,142,143,142,142,142,142,
  142,142,142,142,142,142,142,142,142,142,142,142,142,142,142,142,142,142,
  142,142,142,142,142,142,142,188,142,400,400,400,400,
188,404,402,
41,100,190,228,100,41,
41,100,191,229,100,41,
230,230,230,230,230,230,230,230,230,230,230,230,230,192,
163,163,163,163,163,163,163,163,163,163,163,163,192,163,163,163,163,163,163,
  163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,
  163,163,163,451,163,163,
231,231,231,231,231,231,231,231,231,231,231,231,192,231,233,459,231,231,231,
  231,231,231,231,231,231,231,231,231,231,231,231,231,231,231,231,231,231,
  459,459,459,459,231,231,231,231,231,231,194,231,234,233,232,231,231,231,
41,100,195,235,100,41,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,196,26,107,26,26,
  107,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,197,26,101,26,26,
  101,
236,236,236,236,236,236,236,236,236,236,236,236,236,236,198,237,236,
279,279,279,279,279,279,279,279,279,279,279,279,279,279,279,279,279,279,279,
  279,279,279,279,279,279,279,279,279,279,199,238,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,200,26,239,26,26,
  239,
240,240,240,240,240,240,240,201,
43,42,55,55,202,26,241,26,26,241,
242,203,189,244,243,244,244,
50,204,245,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,205,26,185,26,26,
  185,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,206,26,233,26,26,
  233,
246,246,246,246,246,246,246,246,246,246,246,246,246,246,246,246,246,246,246,
  246,246,246,246,246,246,246,246,246,246,246,246,246,246,246,246,246,246,
  246,246,246,246,246,246,246,246,246,246,246,246,246,246,246,246,246,207,
  247,
41,100,208,248,100,41,
246,246,246,246,246,246,246,246,246,246,246,246,246,246,246,246,246,246,246,
  209,249,
41,100,210,250,100,41,
244,244,244,244,244,244,244,244,244,244,244,244,244,244,244,244,244,244,244,
  211,251,
41,100,212,252,100,41,
242,242,242,242,242,242,242,242,242,242,242,242,242,242,242,242,242,242,242,
  213,253,
49,214,254,
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
  255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
  255,255,255,255,255,255,255,255,255,255,218,219,255,255,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,216,26,216,26,26,
  216,
55,43,42,55,55,55,55,55,55,217,26,256,26,26,256,
257,257,257,257,257,257,257,257,257,257,257,257,257,259,260,257,257,257,257,
  257,257,257,257,257,257,257,257,257,257,218,258,257,257,
257,257,257,257,257,257,257,257,257,257,257,257,257,261,262,264,265,266,267,
  149,148,257,257,257,257,257,257,257,257,257,257,257,257,257,257,219,268,
  263,257,257,
269,271,149,148,220,272,270,161,
257,257,257,257,257,257,257,257,257,257,257,257,257,274,275,149,148,257,257,
  257,257,257,257,257,257,257,257,257,257,257,257,221,276,273,257,257,
149,148,222,277,
149,148,223,278,
119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,
  224,279,
48,225,280,
471,471,471,471,471,471,471,471,471,473,471,
43,42,55,55,227,26,281,26,26,281,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,228,26,392,26,26,
  392,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,229,26,391,26,26,
  391,
453,453,453,453,453,453,453,453,453,453,453,453,453,230,
457,457,457,457,457,457,457,457,457,457,457,457,192,457,457,457,457,457,457,
  457,457,457,457,457,457,457,457,457,457,457,457,457,457,457,457,457,457,
  457,457,457,457,458,457,457,457,
282,441,
283,439,
284,435,435,435,435,234,437,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,235,26,111,26,26,
  111,
285,285,285,285,285,285,285,285,285,285,285,285,285,236,322,285,
43,42,237,286,
287,287,287,287,287,287,288,287,287,287,287,287,287,287,287,287,287,287,287,
  287,287,287,287,287,287,287,287,287,287,238,280,291,290,289,287,287,
92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,239,93,
292,292,292,292,292,292,292,240,
41,100,241,197,100,41,
55,43,42,242,26,293,26,26,293,
41,100,243,294,100,41,
242,196,195,243,195,
55,43,42,55,55,55,55,55,245,26,295,26,26,295,296,
103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,
  103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,
  103,103,103,103,103,103,103,103,103,103,103,103,103,314,314,103,103,103,
  103,103,103,246,316,103,316,
41,100,247,297,100,41,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,248,26,248,26,26,
  248,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,249,26,247,26,26,
  247,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,250,26,250,26,26,
  250,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,251,26,245,26,26,
  245,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,252,26,249,26,26,
  249,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,253,26,243,26,26,
  243,
55,43,42,55,55,55,55,55,55,254,26,298,26,26,298,
224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,
  224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,
  224,224,224,224,224,224,224,224,224,224,225,224,
111,111,111,111,386,111,111,256,386,299,
167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,
  167,167,167,167,167,167,167,167,172,167,
43,42,258,300,
301,301,301,301,301,301,301,301,301,301,301,301,301,301,301,301,301,301,301,
  301,301,43,42,301,301,301,301,301,301,259,302,301,301,
303,303,303,303,303,303,303,303,303,303,303,303,303,303,303,303,303,303,303,
  303,303,43,42,303,303,303,303,303,303,260,304,303,303,
301,301,301,301,301,301,301,301,301,301,301,301,301,301,301,301,301,301,301,
  301,301,301,301,301,301,301,301,261,301,301,
303,303,303,303,303,303,303,303,303,303,303,303,303,303,303,303,303,303,303,
  303,303,303,303,303,303,303,303,262,303,303,
43,42,263,305,
43,42,264,306,
43,42,265,307,
43,42,266,308,
43,42,267,309,
43,42,268,310,
311,311,311,311,311,311,311,311,311,311,311,311,311,311,311,311,311,311,311,
  311,311,311,311,311,311,311,311,311,311,311,311,508,508,311,311,311,311,
  311,311,269,311,311,510,
43,42,270,312,
43,42,271,313,
43,42,272,314,
43,42,273,315,
301,301,301,301,301,301,301,301,301,301,301,301,301,301,301,301,301,301,301,
  301,301,43,42,301,301,301,301,301,301,274,316,301,301,
303,303,303,303,303,303,303,303,303,303,303,303,303,303,303,303,303,303,303,
  303,303,43,42,303,303,303,303,303,303,275,317,303,303,
43,42,276,318,
43,42,277,319,
43,42,278,320,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,279,26,120,26,26,
  120,
43,42,55,55,280,26,321,26,26,321,
41,100,281,461,100,41,
231,231,231,231,231,231,231,231,231,231,231,231,192,231,233,459,231,231,231,
  231,231,231,231,231,231,231,231,231,231,231,231,231,231,231,231,231,231,
  459,459,459,459,231,231,231,231,231,231,282,231,442,233,232,231,231,231,
231,231,231,231,231,231,231,231,231,231,231,231,192,231,233,459,231,231,231,
  231,231,231,231,231,231,231,231,231,231,231,231,231,231,231,231,231,231,
  459,459,459,459,231,231,231,231,231,231,283,231,440,233,232,231,231,231,
322,322,322,322,322,322,322,322,322,322,322,322,192,322,322,322,322,322,322,
  322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,
  322,322,322,284,322,322,436,322,
324,324,324,324,324,324,324,324,324,324,324,324,324,325,
55,43,42,55,55,55,55,55,55,286,26,323,26,26,323,
296,296,296,296,296,296,296,296,296,296,296,296,296,296,296,296,296,296,296,
  296,296,296,296,296,296,296,296,296,297,296,
44,288,324,
43,42,289,325,325,325,
41,100,290,326,100,41,
43,42,291,327,327,327,329,328,328,
330,330,330,330,330,330,330,292,
50,293,331,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,55,55,
  55,55,55,294,26,192,26,26,192,
113,113,113,113,113,113,295,332,
43,42,209,209,296,333,334,334,211,
230,230,230,230,230,230,230,230,230,230,230,230,230,230,230,230,230,230,230,
  297,335,
111,111,111,111,251,111,111,298,251,336,
43,42,55,55,299,26,337,26,26,337,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,
  55,55,55,55,55,300,26,338,26,26,338,
167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,
  167,167,167,167,167,167,167,167,174,167,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,
  55,55,55,55,55,302,26,339,26,26,339,
167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,
  167,167,167,167,167,167,167,167,173,167,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,
  55,55,55,55,55,304,26,340,26,26,340,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,
  55,55,55,55,55,305,26,341,26,26,341,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,
  43,42,55,55,55,55,55,55,306,26,342,26,26,342,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,
  43,42,55,55,55,55,55,55,307,26,343,26,26,343,
55,55,55,43,42,55,55,55,55,55,55,308,26,344,26,26,344,
55,55,55,55,55,55,55,55,55,43,42,55,55,55,55,55,55,309,26,345,26,26,345,
55,55,55,55,55,55,55,55,55,55,43,42,55,55,55,55,55,55,310,26,346,26,26,346,
507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,
  507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,
  509,507,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,
  55,55,55,55,55,55,55,55,55,43,42,55,55,55,55,55,55,312,26,347,26,26,347,
55,55,55,55,43,42,55,55,55,55,55,55,313,26,348,26,26,348,
55,55,55,55,55,55,55,55,55,55,43,42,55,55,55,55,55,55,314,26,349,26,26,349,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,
  55,55,55,55,55,315,26,350,26,26,350,
55,55,55,55,55,55,55,55,55,55,43,42,55,55,55,55,55,55,316,26,351,26,26,351,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,
  42,55,55,55,55,55,55,317,26,352,26,26,352,
55,55,55,55,55,55,55,55,55,55,43,42,55,55,55,55,55,55,318,26,353,26,26,353,
55,55,55,55,55,55,55,55,55,55,43,42,55,55,55,55,55,55,319,26,354,26,26,354,
55,55,55,55,55,55,55,55,55,55,43,42,55,55,55,55,55,55,320,26,355,26,26,355,
41,100,321,356,100,41,
163,163,163,163,163,163,163,163,163,163,163,163,192,357,163,163,163,163,163,
  163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,443,443,
  443,443,163,163,163,163,163,163,322,163,445,163,
358,358,358,358,358,358,358,323,358,359,326,
360,360,360,360,360,360,360,360,360,360,360,360,360,360,360,360,360,360,360,
  360,360,360,360,360,360,360,360,324,360,360,361,
111,539,537,535,533,366,367,368,369,362,363,364,365,300,301,43,42,111,111,
  111,299,111,111,325,299,54,54,376,375,303,374,373,372,371,370,
283,283,283,283,283,283,283,283,283,283,283,283,283,326,377,
378,378,378,378,378,378,378,378,378,378,378,378,378,378,378,378,378,378,378,
  378,378,378,43,42,378,378,378,378,378,378,327,54,54,290,378,
43,42,55,55,328,379,379,379,293,292,
41,100,329,380,100,41,
381,381,381,381,381,381,381,330,
198,198,198,198,198,198,198,198,198,331,382,
43,42,332,383,383,383,
55,43,42,55,55,55,55,55,333,26,295,26,26,295,206,
43,42,210,333,208,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,335,26,231,26,26,
  231,
43,42,336,384,
41,100,337,385,100,41,
386,386,386,386,386,386,386,386,386,386,386,386,386,386,386,386,386,386,386,
  386,386,386,386,386,386,386,386,386,338,138,386,386,
386,386,386,386,386,386,386,386,386,386,386,386,386,386,386,386,386,386,386,
  386,386,386,386,386,386,386,386,386,339,137,386,386,
386,386,386,386,386,386,386,386,386,386,386,386,386,386,386,386,386,386,386,
  386,386,386,386,386,386,386,386,386,340,136,386,386,
386,386,386,386,386,386,386,386,386,386,386,386,386,386,386,386,386,386,386,
  386,386,386,386,386,386,386,386,386,341,130,386,386,
387,387,387,387,387,387,387,387,387,387,387,387,387,146,387,387,387,387,387,
  387,387,387,387,387,145,387,387,387,387,387,387,342,129,147,387,387,
387,387,387,387,387,387,387,387,387,387,387,387,387,146,387,387,387,387,387,
  387,387,387,387,387,145,387,387,387,387,387,387,343,128,147,387,387,
388,143,142,388,388,388,388,388,388,344,388,127,144,
389,389,389,389,389,140,389,389,139,389,389,389,389,389,389,345,126,141,390,
391,391,391,391,391,151,391,391,391,150,391,391,391,391,391,391,346,125,152,
  391,391,
392,392,392,392,392,392,392,392,392,392,392,392,192,392,392,392,392,392,392,
  392,392,392,392,392,392,392,392,392,392,392,392,392,392,392,392,392,392,
  392,392,392,347,135,392,392,392,
393,394,159,158,393,393,393,393,393,393,348,134,160,493,494,
391,391,391,391,391,151,391,391,391,150,391,391,391,391,391,391,349,124,152,
  391,391,
386,386,386,386,386,386,386,386,386,386,386,386,386,386,386,386,386,386,386,
  386,386,386,386,386,386,386,386,386,350,133,386,386,
395,396,398,399,395,395,156,395,395,155,396,396,396,396,396,396,351,132,157,
  492,331,332,401,397,400,
402,402,402,402,402,402,402,402,402,402,402,402,330,402,402,402,402,402,402,
  402,402,402,402,153,402,402,402,402,402,402,352,131,131,131,403,402,402,
391,391,391,391,391,151,391,391,391,150,391,391,391,391,391,391,353,123,152,
  391,391,
391,391,391,391,391,151,391,391,391,150,391,391,391,391,391,391,354,122,152,
  391,391,
391,391,391,391,391,151,391,391,391,150,391,391,391,391,391,391,355,121,152,
  391,391,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,356,26,462,26,26,
  462,
322,322,322,322,322,322,322,322,322,322,322,322,192,322,322,322,322,322,322,
  322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,
  322,322,322,357,322,322,444,322,
24,24,24,24,24,24,24,327,
43,42,359,404,
167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,
  167,167,167,167,167,167,167,167,298,167,
43,42,287,405,405,405,
51,362,406,
51,363,407,
51,364,408,
51,365,409,
51,366,410,
51,367,411,
51,368,412,
51,369,413,
44,370,414,
44,371,415,
44,372,416,
44,373,417,
44,511,418,
43,42,375,419,419,419,
44,302,420,
55,55,55,55,55,55,55,55,55,43,42,55,55,377,26,284,26,26,284,
306,306,306,306,306,306,306,306,306,306,306,306,306,306,306,306,306,306,306,
  306,306,306,306,306,306,306,306,306,307,
378,378,378,378,378,378,378,378,378,378,378,378,378,378,378,378,378,378,378,
  378,378,378,43,42,378,378,378,378,378,378,56,54,54,290,378,
281,281,281,281,281,281,281,281,281,281,281,281,281,380,421,
422,422,422,422,422,422,422,381,
55,43,42,55,55,55,55,55,55,382,26,423,26,26,423,
111,51,43,42,111,111,111,375,111,111,383,375,54,424,54,212,425,
426,426,426,426,426,426,426,426,426,426,426,426,426,426,426,426,426,426,426,
  426,426,426,426,426,426,426,426,426,426,426,426,426,426,426,426,426,426,
  426,426,426,426,426,426,426,426,426,426,426,426,426,426,426,426,426,426,
  384,427,426,426,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,385,26,180,26,26,
  180,
177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,
  177,177,177,177,177,177,177,177,177,178,177,
486,486,486,486,486,486,486,486,486,486,486,486,486,486,486,486,486,486,486,
  486,486,486,486,486,486,486,486,486,486,487,486,
24,24,24,24,24,24,24,484,
481,481,481,481,481,481,481,481,481,481,481,481,481,389,
428,390,
489,489,489,489,489,489,489,489,489,489,489,489,489,489,490,489,
163,163,163,163,163,163,163,163,163,163,163,163,192,163,163,163,163,163,163,
  163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,
  163,163,163,164,163,163,
430,429,502,502,502,502,430,430,430,430,430,430,393,430,430,504,
431,431,431,431,431,431,394,
353,353,353,353,353,353,395,
432,432,432,432,432,432,432,432,432,432,432,432,432,396,
389,389,389,389,389,389,389,389,389,389,389,389,389,397,355,
354,433,354,354,354,354,398,
434,434,434,434,434,434,434,437,348,348,348,348,434,434,434,434,434,434,399,
  437,436,435,437,
438,439,400,440,360,
438,439,401,352,
476,476,476,476,476,476,476,476,476,476,476,476,476,476,476,476,476,476,476,
  476,476,476,476,476,476,476,476,476,477,476,
44,328,441,329,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,
  55,43,42,55,55,55,55,55,55,404,26,442,26,26,442,
111,300,301,43,42,111,111,111,299,111,111,405,299,54,54,443,
387,387,387,387,387,387,387,387,387,387,387,387,387,387,387,387,387,387,387,
  387,387,387,387,387,387,387,387,387,387,406,538,387,387,
387,387,387,387,387,387,387,387,387,387,387,387,387,387,387,387,387,387,387,
  387,387,387,387,387,387,387,387,387,387,407,536,387,387,
388,388,388,388,388,388,388,408,388,534,
389,389,389,389,389,389,389,389,389,389,389,389,389,409,532,390,
444,445,562,444,444,444,444,444,444,410,531,
446,447,583,446,446,446,446,446,446,411,528,
448,451,544,448,448,448,543,449,450,412,543,527,
444,445,562,444,444,444,444,444,444,413,525,
366,369,414,453,452,
454,415,455,
456,416,457,
456,369,417,459,458,
460,418,512,
464,464,464,464,588,587,461,462,463,464,464,464,464,464,464,464,464,464,464,
  464,464,464,464,464,464,464,464,464,43,42,464,464,464,464,464,464,419,
  54,54,286,464,464,312,
111,111,111,111,304,111,111,420,304,465,
55,55,55,55,55,55,55,55,55,43,42,55,55,421,26,282,26,26,282,
466,466,466,466,466,466,466,422,
111,111,111,111,375,111,111,423,375,467,203,425,
55,43,42,55,55,55,55,55,55,424,26,468,26,26,468,
381,380,379,378,376,377,
254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,
  254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,
  254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,
  255,254,
44,41,100,427,470,100,41,469,
389,389,389,389,389,389,389,389,389,389,389,389,389,428,471,472,
498,498,498,498,498,498,498,429,
501,429,501,501,501,501,501,501,503,501,
393,393,393,393,393,393,393,431,497,
389,389,389,389,389,389,389,389,389,389,389,389,389,432,356,
389,389,389,389,389,389,389,389,389,389,389,389,389,433,351,
481,481,481,481,481,481,481,481,481,481,481,481,481,344,
473,473,473,340,473,473,473,473,340,340,340,340,340,340,473,473,473,473,473,
  473,435,343,343,
337,337,474,337,337,337,337,436,475,475,339,
476,357,357,357,357,437,361,361,
434,434,434,434,434,434,434,348,348,348,348,348,434,434,434,434,434,434,438,
  350,436,435,350,
434,434,434,434,434,434,434,434,434,434,434,434,434,439,477,436,435,
476,357,357,357,357,440,359,359,
448,448,448,448,365,449,450,441,365,478,
128,128,128,128,128,128,128,128,128,128,128,128,128,130,131,132,133,134,128,
  128,128,128,128,128,128,128,128,128,128,128,128,128,442,479,129,128,128,
44,43,42,55,55,443,26,480,26,26,288,
481,559,559,559,481,481,481,481,481,481,444,561,
482,482,482,482,482,482,482,482,482,482,482,482,482,445,
483,580,483,483,483,483,483,483,446,582,
484,484,484,484,484,484,484,484,484,484,484,484,484,447,
7,7,7,7,7,7,7,6,
7,486,487,488,491,489,490,6,485,
492,492,492,492,492,492,492,6,
493,493,493,493,493,493,493,493,493,493,493,493,493,451,
44,452,494,
44,521,495,
51,454,496,
44,519,497,
51,456,498,
44,457,499,
44,458,500,
44,513,501,
51,460,502,
503,503,503,503,503,503,503,503,503,503,503,503,503,504,586,586,586,503,503,
  503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,
  503,503,503,503,503,503,503,503,503,503,503,461,503,586,
503,503,503,503,503,503,503,503,503,503,503,503,503,504,585,585,585,503,503,
  503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,
  503,503,503,503,503,503,503,503,503,503,503,462,503,585,
503,503,503,503,503,503,503,503,503,503,503,503,503,504,584,584,584,503,503,
  503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,
  503,503,503,503,503,503,503,503,503,503,503,463,503,584,
310,310,310,310,310,310,310,310,310,310,310,310,310,310,310,310,310,310,310,
  310,310,310,310,310,310,310,310,310,310,311,310,
43,42,465,505,505,505,
506,506,506,506,506,506,506,466,
43,42,467,507,507,507,
111,111,111,111,375,111,111,468,375,213,425,
111,111,111,111,256,111,111,469,256,508,
236,236,236,236,236,236,236,236,236,236,236,236,236,236,236,236,236,236,236,
  470,509,
510,510,510,510,510,510,510,510,510,510,510,510,510,471,
511,472,
481,481,481,481,481,481,481,481,481,481,481,481,481,342,
434,434,434,434,434,434,434,434,434,434,434,434,434,474,334,435,
474,338,336,
448,448,448,448,512,449,450,476,512,
513,345,345,345,345,345,477,347,
44,362,362,362,362,478,514,364,
43,42,55,55,479,26,515,26,26,515,
111,111,111,111,304,111,111,480,304,516,
517,552,552,552,517,517,517,517,517,517,481,560,
518,518,518,518,518,518,518,556,556,556,518,518,518,518,518,518,482,558,
519,578,519,519,519,519,519,519,483,581,
520,520,520,520,520,520,520,569,520,520,520,520,520,520,484,571,
14,14,14,14,14,14,14,485,
21,21,21,21,21,21,7,21,
13,7,7,7,7,7,7,13,13,13,13,13,13,487,
12,7,7,7,7,7,7,12,12,12,12,12,12,488,
11,7,7,7,7,7,7,11,11,11,11,11,11,489,
10,7,7,7,7,7,7,10,10,10,10,10,10,490,
9,7,7,7,7,7,7,9,9,9,9,9,9,491,
8,8,8,8,8,8,8,7,
542,542,542,542,542,542,542,540,540,540,542,542,542,542,542,542,493,542,
454,494,521,
460,495,522,
444,445,562,444,444,444,444,444,444,496,530,
460,497,520,
522,523,555,522,522,522,522,522,522,498,529,
454,499,524,
454,500,525,
460,501,514,
448,451,544,448,448,448,543,449,450,502,543,526,
388,388,388,388,388,388,388,388,388,388,388,388,388,388,388,388,388,388,388,
  388,388,388,388,388,388,388,388,388,388,388,388,388,388,388,388,388,388,
  388,388,388,388,388,388,388,593,
526,504,
464,464,464,464,588,587,461,462,463,464,464,464,464,464,464,464,464,464,464,
  464,464,464,464,464,464,464,464,464,43,42,464,464,464,464,464,464,505,
  54,54,285,464,464,312,
527,372,372,372,372,527,527,527,527,527,527,506,527,374,
111,43,42,111,111,111,375,111,111,507,375,54,54,528,204,425,
44,43,42,55,55,508,26,529,530,26,26,530,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,509,26,237,26,26,
  237,
482,482,482,482,482,482,482,482,482,482,482,482,482,510,
389,389,389,389,389,389,389,389,389,389,389,389,389,511,471,531,
532,512,
434,434,434,434,434,434,434,434,434,434,434,434,434,513,346,436,435,
111,111,111,111,366,111,111,514,366,363,
41,100,515,533,100,41,
43,42,55,55,516,26,26,26,289,
534,550,550,550,534,534,534,534,534,534,517,553,
535,535,535,535,535,535,535,545,545,545,535,535,535,535,535,535,518,557,
536,576,536,536,536,536,536,536,519,579,
537,537,537,537,537,537,537,567,537,537,537,537,537,537,520,570,
44,523,538,
517,552,517,517,517,517,517,517,522,554,
539,539,539,539,539,539,539,539,539,539,539,539,539,523,
44,515,540,
44,517,541,
542,542,542,542,542,542,542,542,542,542,542,542,542,526,542,
24,24,24,24,24,24,24,373,
43,42,528,543,543,543,544,544,
545,545,545,545,545,545,545,545,545,545,545,545,545,545,545,545,545,545,545,
  545,545,545,545,545,545,545,529,546,545,
41,100,530,547,100,41,
548,531,
448,448,448,448,549,449,450,532,549,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,533,26,97,26,26,97,
551,548,548,548,551,551,551,551,551,551,534,551,
546,546,546,546,546,546,546,540,540,540,546,546,546,546,546,546,535,546,
550,574,550,550,550,550,550,550,536,577,
551,551,551,551,551,551,551,565,551,551,551,551,551,551,537,568,
460,538,524,
535,535,535,535,535,535,535,545,535,535,535,535,535,535,539,547,
460,540,516,
460,541,518,
324,324,324,324,324,324,324,324,324,324,324,324,324,592,
111,43,42,111,111,111,375,111,111,543,375,54,54,199,205,425,
43,42,202,543,543,543,201,
258,258,258,258,258,258,258,258,258,258,258,258,258,258,258,258,258,258,258,
  258,258,258,258,258,258,258,259,
43,42,55,55,546,26,552,26,26,552,
238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,
  547,553,
389,389,389,389,389,389,389,389,389,389,389,389,389,548,471,554,
555,549,
556,572,556,556,556,556,556,556,550,575,
557,557,557,557,557,557,557,563,557,557,557,557,557,557,551,566,
41,100,552,558,100,41,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,553,26,239,26,26,
  239,
559,554,
448,448,448,448,333,449,450,555,333,
481,559,481,481,481,481,481,481,556,573,
518,518,518,518,518,518,518,556,518,518,518,518,518,518,557,564,
240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,
  558,560,
389,389,389,389,389,389,389,389,389,389,389,389,389,559,471,561,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,560,26,241,26,26,
  241,
562,561,
389,389,389,389,389,389,389,389,389,389,389,389,389,562,471,563,
564,563,
389,389,389,389,389,389,389,389,389,389,389,389,389,564,471,565,
566,565,
389,389,389,389,389,389,389,389,389,389,389,389,389,566,471,567,
568,567,
389,389,389,389,389,389,389,389,389,389,389,389,389,568,471,569,
570,569,
389,389,389,389,389,389,389,389,389,389,389,389,389,570,471,571,
572,571,
389,389,389,389,389,389,389,389,389,389,389,389,389,572,483,

};


static const unsigned short ag_sbt[] = {
     0,  10,  12,  18,  22,  24,  61,  66,  71,  76,  81,  86,  91, 101,
   111, 116, 121, 126, 136, 165, 178, 187, 196, 205, 214, 223, 232, 237,
   240, 243, 252, 261, 270, 273, 275, 289, 300, 308, 311, 314, 317, 320,
   323, 326, 380, 439, 442, 445, 448, 500, 509, 521, 540, 550, 565, 580,
   647, 682, 718, 758, 806, 859, 920, 974, 980,1033,1035,1038,1046,1073,
  1139,1205,1252,1255,1267,1279,1291,1303,1314,1318,1328,1341,1403,1435,
  1467,1504,1553,1556,1566,1574,1619,1678,1680,1728,1777,1780,1833,1887,
  1938,1989,2038,2041,2066,2089,2146,2167,2173,2194,2200,2245,2249,2286,
  2295,2305,2314,2320,2353,2385,2443,2451,2505,2559,2613,2618,2647,2658,
  2664,2694,2703,2732,2736,2769,2802,2835,2839,2843,2853,2900,2909,2911,
  2918,2967,2992,3036,3099,3108,3111,3114,3160,3162,3172,3197,3218,3243,
  3264,3286,3317,3325,3331,3339,3353,3382,3391,3397,3453,3474,3536,3588,
  3640,3692,3702,3705,3726,3729,3766,3795,3838,3867,3879,3908,3947,3957,
  3967,3973,3976,3993,3996,4056,4058,4108,4111,4117,4123,4137,4180,4235,
  4241,4266,4291,4308,4339,4364,4372,4382,4389,4392,4417,4442,4498,4504,
  4525,4531,4552,4558,4579,4582,4633,4658,4673,4706,4746,4754,4790,4794,
  4798,4819,4822,4833,4843,4868,4893,4907,4952,4954,4956,4963,4988,5004,
  5008,5044,5063,5071,5077,5086,5092,5097,5112,5174,5180,5205,5230,5255,
  5280,5305,5330,5345,5394,5404,5433,5437,5470,5503,5533,5563,5567,5571,
  5575,5579,5583,5587,5630,5634,5638,5642,5646,5679,5712,5716,5720,5724,
  5749,5759,5765,5820,5875,5920,5934,5949,5979,5982,5988,5994,6003,6011,
  6014,6048,6056,6065,6086,6096,6106,6142,6171,6207,6236,6272,6308,6347,
  6386,6403,6426,6450,6489,6537,6555,6579,6615,6639,6677,6701,6725,6749,
  6755,6804,6815,6846,6881,6896,6931,6941,6947,6955,6966,6972,6987,6992,
  7017,7021,7027,7059,7091,7123,7155,7191,7227,7240,7259,7280,7325,7340,
  7361,7393,7418,7455,7476,7497,7518,7543,7588,7596,7600,7629,7635,7638,
  7641,7644,7647,7650,7653,7656,7659,7662,7665,7668,7671,7674,7680,7683,
  7702,7731,7766,7781,7789,7804,7821,7880,7905,7935,7966,7974,7988,7990,
  8006,8049,8065,8072,8079,8093,8108,8115,8138,8143,8147,8177,8181,8221,
  8237,8270,8303,8313,8329,8340,8351,8363,8374,8379,8382,8385,8390,8393,
  8436,8446,8465,8473,8485,8500,8506,8563,8571,8587,8595,8605,8614,8629,
  8644,8658,8681,8692,8700,8723,8740,8748,8758,8795,8806,8818,8832,8842,
  8856,8864,8873,8881,8895,8898,8901,8904,8907,8910,8913,8916,8919,8922,
  8973,9024,9075,9106,9112,9120,9126,9137,9147,9168,9182,9184,9198,9214,
  9217,9226,9234,9242,9252,9262,9274,9292,9302,9318,9326,9334,9348,9362,
  9376,9390,9404,9412,9430,9433,9436,9447,9450,9461,9464,9467,9470,9482,
  9527,9529,9572,9586,9602,9614,9639,9653,9669,9671,9688,9698,9704,9713,
  9725,9743,9753,9769,9772,9782,9796,9799,9802,9817,9825,9833,9862,9868,
  9870,9879,9904,9916,9934,9944,9960,9963,9979,9982,9985,9999,10015,10022,
  10049,10059,10080,10096,10098,10108,10124,10130,10155,10157,10166,10176,
  10192,10213,10229,10254,10256,10272,10274,10290,10292,10308,10310,10326,
  10328,10344,10346,10361
};


static const unsigned short ag_sbe[] = {
     4,  11,  15,  19,  23,  41,  64,  69,  74,  79,  84,  89,  94, 104,
   114, 119, 124, 129, 147, 171, 181, 190, 199, 208, 217, 226, 234, 238,
   241, 246, 255, 264, 271, 274, 286, 295, 305, 309, 312, 315, 318, 321,
   324, 373, 430, 440, 443, 446, 494, 503, 519, 531, 544, 559, 574, 640,
   676, 712, 752, 803, 855, 915, 970, 976,1032,1034,1036,1041,1067,1131,
  1197,1249,1253,1265,1277,1289,1301,1307,1316,1325,1335,1399,1430,1463,
  1499,1550,1554,1563,1569,1617,1677,1679,1726,1772,1778,1829,1883,1931,
  1982,2035,2039,2060,2085,2145,2165,2169,2192,2196,2244,2247,2280,2293,
  2299,2312,2316,2348,2378,2440,2446,2499,2553,2607,2616,2645,2652,2660,
  2692,2697,2730,2734,2765,2798,2831,2837,2841,2847,2899,2903,2910,2917,
  2964,2986,3035,3092,3104,3109,3112,3155,3161,3166,3191,3216,3237,3262,
  3280,3315,3324,3327,3338,3348,3379,3385,3393,3452,3472,3530,3582,3634,
  3686,3695,3703,3724,3727,3760,3793,3832,3865,3873,3906,3941,3951,3961,
  3969,3974,3989,3994,4051,4057,4102,4109,4113,4119,4136,4177,4227,4237,
  4260,4285,4305,4337,4358,4371,4376,4383,4390,4411,4436,4496,4500,4523,
  4527,4550,4554,4577,4580,4629,4652,4667,4702,4741,4750,4785,4792,4796,
  4817,4820,4831,4837,4862,4887,4906,4948,4953,4955,4961,4982,5001,5006,
  5037,5061,5070,5073,5080,5088,5093,5105,5170,5176,5199,5224,5249,5274,
  5299,5324,5339,5392,5401,5431,5435,5466,5499,5530,5560,5565,5569,5573,
  5577,5581,5585,5626,5632,5636,5640,5644,5675,5708,5714,5718,5722,5743,
  5753,5761,5812,5867,5915,5933,5943,5977,5980,5984,5990,5996,6010,6012,
  6042,6054,6060,6084,6093,6100,6136,6169,6201,6234,6266,6302,6341,6380,
  6397,6420,6444,6487,6531,6549,6573,6609,6633,6671,6695,6719,6743,6751,
  6800,6811,6842,6869,6894,6926,6935,6943,6954,6964,6968,6980,6989,7011,
  7019,7023,7055,7087,7119,7151,7186,7222,7236,7255,7275,7320,7335,7356,
  7389,7409,7448,7471,7492,7513,7537,7583,7595,7598,7627,7631,7636,7639,
  7642,7645,7648,7651,7654,7657,7660,7663,7666,7669,7672,7676,7681,7696,
  7730,7761,7779,7788,7798,7814,7876,7899,7933,7964,7973,7987,7989,8004,
  8046,8061,8071,8078,8092,8106,8114,8133,8140,8145,8175,8178,8215,8232,
  8266,8299,8310,8326,8338,8349,8360,8372,8376,8380,8383,8387,8391,8429,
  8443,8459,8472,8480,8494,8504,8561,8566,8584,8594,8603,8612,8627,8642,
  8657,8678,8688,8697,8718,8736,8745,8755,8790,8800,8816,8831,8840,8855,
  8863,8871,8880,8894,8896,8899,8902,8905,8908,8911,8914,8917,8920,8970,
  9021,9072,9104,9108,9119,9122,9133,9144,9166,9181,9183,9197,9211,9215,
  9224,9232,9239,9246,9259,9272,9290,9300,9316,9325,9332,9347,9361,9375,
  9389,9403,9411,9428,9431,9434,9445,9448,9459,9462,9465,9468,9479,9526,
  9528,9565,9583,9595,9607,9633,9652,9666,9670,9684,9695,9700,9708,9723,
  9741,9751,9767,9770,9780,9795,9797,9800,9815,9824,9827,9859,9864,9869,
  9877,9898,9914,9932,9942,9958,9961,9977,9980,9983,9998,10008,10017,10048,
  10053,10078,10093,10097,10106,10122,10126,10149,10156,10164,10174,10190,
  10211,10226,10248,10255,10269,10273,10287,10291,10305,10309,10323,10327,
  10341,10345,10359,10361
};


static const unsigned char ag_fl[] = {
  1,1,1,1,2,1,1,2,3,1,1,1,1,1,3,1,1,1,1,1,1,3,1,1,2,2,1,1,1,2,0,1,2,1,2,
  1,3,2,2,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,2,0,1,1,1,3,1,1,1,1,1,2,0,1,1,1,
  2,0,1,1,1,2,0,1,5,1,1,1,1,1,1,1,1,1,1,1,0,0,0,11,1,2,1,16,0,5,0,4,0,3,
  0,5,0,4,0,3,0,9,2,1,3,2,1,3,0,0,10,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,2,1,2,2,2,1,2,
  2,1,1,2,1,0,13,0,1,2,0,3,7,1,0,4,0,3,3,1,1,2,1,5,0,2,1,2,9,1,1,1,2,1,2,
  0,1,5,4,6,0,0,9,1,3,4,1,1,1,1,2,1,0,5,2,2,0,8,0,5,0,3,0,9,0,12,0,14,0,
  5,0,5,0,5,5,5,5,1,1,1,2,1,1,1,2,1,0,0,2,1,1,2,0,1,3,0,2,0,2,0,2,0,2,0,
  0,0,8,0,5,0,4,7,5,3,6,8,2,1,2,2,1,1,2,1,1,1,1,1,1,1,1,1,2,1,1,1,2,1,1,
  2,0,1,2,1,2,1,0,1,2,1,2,1,1,1,1,2,1,1,1,6,2,1,2,0,1,2,0,1,1,2,1,0,2,3,
  0,1,2,3,2,2,2,2,3,0,1,2,2,3,0,2,3,1,1,1,1,1,1,2,0,1,10,1,1,2,1,1,1,1,1,
  1,2,1,1,1,2,1,3,6,6,3,2,1,2,0,1,2,2,1,2,0,1,2,1,1,1,1,1,1,1,2,0,1,2,1,
  3,1,1,1,2,0,1,3,1,1,2,0,1,1,3,1,1,0,2,4,1,1,3,1,3,0,2,2,1,1,1,1,0,1,2,
  3,1,1,1,2,1,0,4,7,9,1,2,0,1,1,1,1,1,2,0,1,4,1,2,1,1,1,1,2,3,21,1,1,2,1,
  1,2,1,1,1,1,1,1,1,3,2,1,1,2,0,1,2,1,1,2,0,1,2,1,3,3,5,5,7,5,7,3,5,3,5,
  5,7,3,3,3,3,3,3,3,3,1,3,1,3,1,3,1,0,1,3,1,1,0,2,3,0,1,0,2,0,2,2,1,0,2,
  3,0,2,2,1,0,2,0,2,0,2,0,2,3,0,2,0,2,0,2,0,2,0,2,2,1,2,2,2,1,1,1,1,1,3,
  1,1,1,1
};

static const unsigned short ag_ptt[] = {
    0,  2,  4,  7,  7,  3,  8,  8,  8, 16, 16, 16, 16, 16,  8, 18, 18, 18,
   18, 18, 18,  8, 19, 20, 20, 19, 24, 24, 25, 25, 26, 26, 21, 27, 27, 21,
   21,  5, 29, 29, 32, 32, 35, 35, 38, 40, 42, 44, 46, 48, 50, 52, 55, 56,
   56, 57, 57, 54, 58, 58, 58, 58, 62, 62, 63, 63, 64, 64, 67, 68, 68, 69,
   69, 71, 72, 72, 73, 73,  1, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66,
   85, 87, 89, 65, 88, 74, 90, 91, 98, 75,100, 99,101, 99,103, 76,105,104,
  106,104,108, 77, 78,110,111, 79,114,115,119,120, 80, 96, 96, 96, 96, 96,
   96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96,129,129,129,131,131,
  131,133,133,133,122,122,123,123,123,138,138,140,140,140,142,142,142,143,
  156,156,144,158,159,159,145,145,145,145,135,135,135,161,162,162,136,164,
   81,168,170,170,172,172,173, 82,175,169,177,169,178,180,181,181,176,174,
  185,189,190,190,179,186,187,188,194,195,195,196,196,171,193,193,199,201,
   83,200,200,200,202,206,206,207,207,203,209, 84,210,210,215,210,216,210,
  218,211,222,219,224,219,226,219,228,212,230,212,232,212,212,212,212,220,
  234,235,235,221,223,237,237,225,239,240,240,242,243,243,244,244, 70,245,
  241,246,241,247,241,248,241,249,251,252,238,256,253,258,253,254,254,257,
  257,257,267,268,268,255,270,271,271,259,265,260,260,260,263,263,261,274,
  274,266,276,277,277,262,262,213,281,281,214,283,283,280,284,284, 94,287,
  287,285, 95,288,289,289,289,292,292,295,298,299,299,300,300,296,302,302,
  302,297,297,305,305,303,306,306,303,307,293,309,309,312,312,314,314,313,
  294,294,317,317,291,315,316,182,182,183,183,197,320,320,319,321,191,191,
  322,322,322,322,328,329,329,165,166,330,330, 93,113,113,113,331,337,338,
  338,339,339,332,341,342,342,343,343,334,340,340,335,335,349,349,350,350,
  351,351,346,346,346,355,355,356,356,357,357,345,360,353,354,365,365,365,
  347,367,364,373,373,109,368,370,370,370,370,379,379,372,155,155,155,155,
  384,384,374,382,386,386,387,387,377,375,117,117,117,389,389,390,390,391,
  391,391,392,392,393,393,388,395,395,290,394,394,394,301,396,147,148,398,
  398,149,400,400,150,151,152,153,153,399,397,401,406,406,407,407,408,408,
  402,411,412,412,413,413,154,272,272,272,272,272,272,272,272,272,272,272,
  272,272,272,414,415,416,417,418,419,420,421,421,421,421,421,421,421,421,
  438,438,425,425,425,439,439,430,440,440,441,441,442,442,430,430,443,443,
  423,444,444,423,423,445,445,446,446,447,447,448,448,428,449,449,450,450,
  451,451,452,452,453,453,428,428,278,278,278,278,278,455,455,455,455,455,
  344, 33, 34
};


static void ag_ra(PCB_DECL)
{
  switch(ag_rpx[(PCB).ag_ap]) {
    case 1: V(0,RvpStrPtrN) = ag_rp_1(PCB_POINTER); break;
    case 2: ag_rp_7(PCB_POINTER); break;
    case 3: ag_rp_8(PCB_POINTER); break;
    case 4: ag_rp_9(PCB_POINTER); break;
    case 5: ag_rp_10(PCB_POINTER); break;
    case 6: ag_rp_11(PCB_POINTER); break;
    case 7: ag_rp_12(PCB_POINTER); break;
    case 8: ag_rp_13(PCB_POINTER); break;
    case 9: ag_rp_14(PCB_POINTER); break;
    case 10: ag_rp_15(PCB_POINTER); break;
    case 11: ag_rp_16(PCB_POINTER); break;
    case 12: ag_rp_17(PCB_POINTER); break;
    case 13: ag_rp_18(PCB_POINTER); break;
    case 14: ag_rp_19(PCB_POINTER); break;
    case 15: ag_rp_20(PCB_POINTER); break;
    case 16: ag_rp_21(PCB_POINTER); break;
    case 17: ag_rp_22(PCB_POINTER); break;
    case 18: ag_rp_23(PCB_POINTER); break;
    case 19: ag_rp_24(PCB_POINTER); break;
    case 20: ag_rp_25(PCB_POINTER); break;
    case 21: ag_rp_26(PCB_POINTER); break;
    case 22: ag_rp_27(PCB_POINTER); break;
    case 23: ag_rp_28(PCB_POINTER, V(3,RvpStrPtrN), V(6,RvpStrPtrN), V(9,RvpStrPtrN)); break;
    case 24: ag_rp_29(PCB_POINTER); break;
    case 25: ag_rp_30(PCB_POINTER, V(-2,RvpStrPtrN)); break;
    case 26: ag_rp_31(PCB_POINTER, V(0,RvpStrPtrN)); break;
    case 27: ag_rp_32(PCB_POINTER); break;
    case 28: ag_rp_33(PCB_POINTER); break;
    case 29: ag_rp_34(PCB_POINTER); break;
    case 30: ag_rp_35(PCB_POINTER, V(-2,RvpStrPtrN)); break;
    case 31: ag_rp_36(PCB_POINTER, V(0,RvpStrPtrN)); break;
    case 32: ag_rp_37(PCB_POINTER); break;
    case 33: ag_rp_38(PCB_POINTER); break;
    case 34: ag_rp_39(PCB_POINTER); break;
    case 35: ag_rp_40(PCB_POINTER, V(5,RvpStrPtrN)); break;
    case 36: ag_rp_41(PCB_POINTER); break;
    case 37: ag_rp_42(PCB_POINTER); break;
    case 38: ag_rp_43(PCB_POINTER); break;
    case 39: ag_rp_44(PCB_POINTER); break;
    case 40: ag_rp_45(PCB_POINTER); break;
    case 41: ag_rp_46(PCB_POINTER); break;
    case 42: ag_rp_47(PCB_POINTER, V(3,RvpStrPtrN), V(6,RvpStrPtrN)); break;
    case 43: ag_rp_48(PCB_POINTER, V(3,RvpStrPtrN), V(6,RvpStrPtrN)); break;
    case 44: ag_rp_49(PCB_POINTER, V(3,RvpStrPtrN), V(6,RvpStrPtrN)); break;
    case 45: ag_rp_50(PCB_POINTER, V(3,RvpStrPtrN), V(6,RvpStrPtrN)); break;
    case 46: ag_rp_51(PCB_POINTER, V(3,RvpStrPtrN), V(6,RvpStrPtrN)); break;
    case 47: ag_rp_52(PCB_POINTER, V(6,RvpStrPtrN)); break;
    case 48: ag_rp_53(PCB_POINTER, V(6,RvpStrPtrN)); break;
    case 49: ag_rp_54(PCB_POINTER, V(6,RvpStrPtrN)); break;
    case 50: ag_rp_55(PCB_POINTER, V(6,RvpStrPtrN)); break;
    case 51: ag_rp_56(PCB_POINTER, V(3,RvpStrPtrN), V(6,RvpStrPtrN)); break;
    case 52: ag_rp_57(PCB_POINTER, V(6,RvpStrPtrN)); break;
    case 53: ag_rp_58(PCB_POINTER, V(6,RvpStrPtrN)); break;
    case 54: ag_rp_59(PCB_POINTER, V(3,RvpStrPtrN), V(6,RvpStrPtrN)); break;
    case 55: ag_rp_60(PCB_POINTER, V(6,RvpStrPtrN)); break;
    case 56: ag_rp_61(PCB_POINTER, V(3,RvpStrPtrN), V(6,RvpStrPtrN)); break;
    case 57: ag_rp_62(PCB_POINTER, V(0,RvpStrPtrN), V(6,RvpStrPtrN)); break;
    case 58: ag_rp_63(PCB_POINTER, V(0,RvpStrPtrN), V(6,RvpStrPtrN)); break;
    case 59: ag_rp_64(PCB_POINTER, V(0,RvpStrPtrN), V(3,RvpStrPtrN), V(6,RvpStrPtrN)); break;
    case 60: ag_rp_96(PCB_POINTER); break;
    case 61: ag_rp_97(PCB_POINTER, V(5,RvpStrPtrN), V(9,int)); break;
    case 62: ag_rp_98(PCB_POINTER); break;
    case 63: ag_rp_99(PCB_POINTER); break;
    case 64: ag_rp_100(PCB_POINTER); break;
    case 65: ag_rp_101(PCB_POINTER); break;
    case 66: ag_rp_102(PCB_POINTER, V(0,unsigned int), V(2,unsigned int)); break;
    case 67: ag_rp_103(PCB_POINTER); break;
    case 68: ag_rp_104(PCB_POINTER, V(0,RvSdpTypedTime)); break;
    case 69: ag_rp_105(PCB_POINTER, V(0,RvSdpTypedTime)); break;
    case 70: ag_rp_106(PCB_POINTER, V(0,RvSdpTypedTime)); break;
    case 71: ag_rp_107(PCB_POINTER, V(1,unsigned int), V(3,RvSdpTypedTime)); break;
    case 72: ag_rp_108(PCB_POINTER, V(1,unsigned int), V(5,RvSdpTypedTime)); break;
    case 73: ag_rp_109(PCB_POINTER); break;
    case 74: ag_rp_110(PCB_POINTER); break;
    case 75: ag_rp_111(PCB_POINTER, V(0,RvpStrPtrN)); break;
    case 76: ag_rp_112(PCB_POINTER, V(0,RvpStrPtrN)); break;
    case 77: ag_rp_113(PCB_POINTER, V(0,RvpStrPtrN), V(3,RvpStrPtrN)); break;
    case 78: ag_rp_116(PCB_POINTER); break;
    case 79: ag_rp_117(PCB_POINTER, V(-5,RvpStrPtrN), V(-2,RvpStrPtrN)); break;
    case 80: ag_rp_118(PCB_POINTER, V(1,RvpStrPtrN), V(4,RvpStrPtrN)); break;
    case 81: ag_rp_119(PCB_POINTER, V(-2,RvpStrPtrN)); break;
    case 82: ag_rp_120(PCB_POINTER, V(1,RvpStrPtrN)); break;
    case 83: ag_rp_121(PCB_POINTER); break;
    case 84: ag_rp_122(PCB_POINTER, V(-4,int), V(-2,RvpStrPtrN)); break;
    case 85: ag_rp_123(PCB_POINTER, V(3,int), V(5,RvpStrPtrN)); break;
    case 86: ag_rp_124(PCB_POINTER, V(-7,int), V(-5,RvpStrPtrN), V(-3,int)); break;
    case 87: ag_rp_125(PCB_POINTER, V(3,int), V(5,RvpStrPtrN), V(7,int)); break;
    case 88: ag_rp_126(PCB_POINTER, V(-9,int), V(-7,RvpStrPtrN), V(-5,int), V(-3,RvpStrPtrN)); break;
    case 89: ag_rp_127(PCB_POINTER, V(3,int), V(5,RvpStrPtrN), V(7,int), V(9,RvpStrPtrN)); break;
    case 90: ag_rp_128(PCB_POINTER); break;
    case 91: ag_rp_129(PCB_POINTER); break;
    case 92: ag_rp_130(PCB_POINTER); break;
    case 93: ag_rp_131(PCB_POINTER); break;
    case 94: ag_rp_132(PCB_POINTER); break;
    case 95: ag_rp_133(PCB_POINTER); break;
    case 96: ag_rp_134(PCB_POINTER, V(2,RvpStrPtrN)); break;
    case 97: ag_rp_135(PCB_POINTER, V(2,RvpStrPtrN)); break;
    case 98: ag_rp_136(PCB_POINTER, V(2,RvpStrPtrN)); break;
    case 99: V(0,int) = ag_rp_137(PCB_POINTER); break;
    case 100: V(0,int) = ag_rp_139(PCB_POINTER); break;
    case 101: ag_rp_141(PCB_POINTER); break;
    case 102: ag_rp_142(PCB_POINTER); break;
    case 103: ag_rp_143(PCB_POINTER); break;
    case 104: ag_rp_144(PCB_POINTER); break;
    case 105: ag_rp_145(PCB_POINTER); break;
    case 106: ag_rp_146(PCB_POINTER); break;
    case 107: ag_rp_147(PCB_POINTER); break;
    case 108: ag_rp_148(PCB_POINTER); break;
    case 109: ag_rp_149(PCB_POINTER); break;
    case 110: ag_rp_150(PCB_POINTER); break;
    case 111: ag_rp_151(PCB_POINTER); break;
    case 112: ag_rp_152(PCB_POINTER); break;
    case 113: ag_rp_153(PCB_POINTER, V(0,RvpStrPtrN), V(2,int), V(4,int), V(6,RvpStrPtrN)); break;
    case 114: ag_rp_154(PCB_POINTER, V(0,RvpStrPtrN), V(2,int), V(4,RvpStrPtrN)); break;
    case 115: ag_rp_155(PCB_POINTER, V(2,RvpStrPtrN)); break;
    case 116: ag_rp_156(PCB_POINTER, V(2,RvpStrPtrN), V(4,int)); break;
    case 117: ag_rp_157(PCB_POINTER, V(2,RvpStrPtrN), V(4,int), V(6,int)); break;
    case 118: V(0,int) = ag_rp_160(PCB_POINTER); break;
    case 119: V(0,int) = ag_rp_161(PCB_POINTER); break;
    case 120: V(0,int) = ag_rp_162(PCB_POINTER); break;
    case 121: V(0,int) = ag_rp_163(PCB_POINTER); break;
    case 122: V(0,int) = ag_rp_164(PCB_POINTER); break;
    case 123: ag_rp_165(PCB_POINTER); break;
    case 124: V(0,RvpStrPtrN) = ag_rp_173(PCB_POINTER, V(0,RvpStrPtrN)); break;
    case 125: ag_rp_179(PCB_POINTER); break;
    case 126: ag_rp_180(PCB_POINTER); break;
    case 127: V(0,unsigned int) = ag_rp_181(PCB_POINTER, V(0,unsigned int)); break;
    case 128: V(0,unsigned int) = ag_rp_182(PCB_POINTER); break;
    case 129: V(0,unsigned int) = ag_rp_183(PCB_POINTER, V(0,unsigned int)); break;
    case 130: V(0,unsigned int) = ag_rp_184(PCB_POINTER); break;
    case 131: V(0,unsigned int) = ag_rp_185(PCB_POINTER); break;
    case 132: V(0,unsigned int) = ag_rp_186(PCB_POINTER); break;
    case 133: V(0,RvSdpTypedTime) = ag_rp_187(PCB_POINTER, V(0,unsigned int)); break;
    case 134: V(0,RvSdpTypedTime) = ag_rp_188(PCB_POINTER, V(0,unsigned int), V(1,short)); break;
    case 135: V(0,short) = ag_rp_189(PCB_POINTER); break;
    case 136: V(0,short) = ag_rp_190(PCB_POINTER); break;
    case 137: V(0,short) = ag_rp_191(PCB_POINTER); break;
    case 138: V(0,short) = ag_rp_192(PCB_POINTER); break;
    case 139: V(0,int) = ag_rp_194(PCB_POINTER); break;
    case 140: ag_rp_196(PCB_POINTER, V(0,RvpStrPtrN)); break;
    case 141: ag_rp_197(PCB_POINTER, V(0,RvpStrPtrN), V(2,RvpStrPtrN)); break;
    case 142: ag_rp_198(PCB_POINTER, V(0,RvpStrPtrN), V(2,RvpStrPtrN)); break;
    case 143: ag_rp_201(PCB_POINTER, V(1,RvpStrPtrN)); break;
    case 144: ag_rp_202(PCB_POINTER, V(1,RvpStrPtrN), V(3,RvpStrPtrN)); break;
    case 145: ag_rp_203(PCB_POINTER, V(1,RvpStrPtrN), V(4,RvpStrPtrN)); break;
    case 146: ag_rp_213(PCB_POINTER, V(2,RvpStrPtrN)); break;
    case 147: ag_rp_214(PCB_POINTER, V(2,RvpStrPtrN)); break;
    case 148: ag_rp_215(PCB_POINTER, V(2,RvpStrPtrN)); break;
    case 149: ag_rp_216(PCB_POINTER, V(2,RvpStrPtrN)); break;
    case 150: ag_rp_217(PCB_POINTER, V(2,RvpStrPtrN)); break;
    case 151: ag_rp_218(PCB_POINTER, V(2,RvpStrPtrN)); break;
    case 152: ag_rp_219(PCB_POINTER, V(2,RvpStrPtrN)); break;
    case 153: ag_rp_220(PCB_POINTER, V(2,RvpStrPtrN)); break;
    case 154: ag_rp_221(PCB_POINTER); break;
    case 155: ag_rp_222(PCB_POINTER, V(2,RvpStrPtrN)); break;
    case 156: ag_rp_223(PCB_POINTER); break;
    case 157: ag_rp_224(PCB_POINTER, V(2,RvpStrPtrN)); break;
    case 158: ag_rp_225(PCB_POINTER); break;
    case 159: ag_rp_226(PCB_POINTER, V(2,RvpStrPtrN)); break;
    case 160: ag_rp_227(PCB_POINTER); break;
  }
  (PCB).la_ptr = (PCB).pointer;
}

#define TOKEN_NAMES rvSdpParser_token_names
const char *const rvSdpParser_token_names[483] = {
  "announcement",
  "announcement",
  "text",
  "byte_string",
  "text_no_space",
  "email_safe_string_no_space",
  "ANY_BYTE",
  "",
  "decimal_uchar",
  "DIGIT",
  "POS_DIGIT",
  "'1'",
  "'2'",
  "'0'",
  "'3'",
  "'4'",
  "",
  "'5'",
  "",
  "integer",
  "",
  "email_safe_string",
  "EMAIL_SAFE_ONLY",
  "EMAIL_ATOM_N_SAFE",
  "",
  "",
  "",
  "",
  "SAFE",
  "EOL",
  "",
  "",
  "eol",
  "CR",
  "LF",
  "space",
  "SPACE",
  "TAB",
  "fwdslash",
  "'/'",
  "opar",
  "'('",
  "clpar",
  "')'",
  "obrkt",
  "'<'",
  "clbrkt",
  "'>'",
  "colon",
  "':'",
  "equal",
  "'='",
  "minus",
  "\"-\"",
  "omwsp",
  "",
  "",
  "",
  "EOM",
  "EOF",
  "'.'",
  "'}'",
  "",
  "",
  "",
  "proto_version",
  "body_fields",
  "",
  "",
  "",
  "media_description",
  "",
  "",
  "",
  "origin_field",
  "session_name_field",
  "information_field",
  "uri_field",
  "email_field",
  "phone_field",
  "connection_field",
  "bandwidth_field",
  "time_fields",
  "key_field",
  "attribute",
  "",
  "'v'",
  "",
  "sdp_version",
  "",
  "origin_head",
  "origin_body",
  "'o'",
  "username",
  "sess_id",
  "sess_version",
  "net_type_addr",
  "'s'",
  "",
  "session_body",
  "",
  "",
  "'i'",
  "",
  "information_body",
  "",
  "",
  "'u'",
  "",
  "uri",
  "email_header",
  "email_body",
  "'e'",
  "email_address",
  "phone_header",
  "phone_body",
  "'p'",
  "phone_number",
  "'c'",
  "",
  "",
  "'-'",
  "other_addr_type",
  "other_addr_all",
  "'$'",
  "\"IN\"",
  "\"TN\"",
  "\"ATM\"",
  "\"NSAP\"",
  "nsap_addr_all",
  "\"E164\"",
  "e164_addr_all",
  "\"GWID\"",
  "alias_addr_all",
  "\"ALIAS\"",
  "addrtype_str",
  "any_addr",
  "\"IP4\"",
  "ip4_addr_all",
  "\"IP6\"",
  "ip6_addr_all",
  "\"RFC2543\"",
  "tn_addr_all",
  "tn_other_type",
  "tn_other_all",
  "nettype_str",
  "\"$\"",
  "nsap_str",
  "e164_str",
  "alias_str",
  "other_str",
  "ip4_str",
  "ip6_str",
  "tn_str",
  "tnothertype",
  "xalpha",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "'b'",
  "",
  "bwtype",
  "bandwidth",
  "'t'",
  "",
  "time_description",
  "",
  "zone_adjustments",
  "",
  "",
  "session_time",
  "",
  "repeat_lines",
  "",
  "repeat_line",
  "repeat_fields",
  "",
  "",
  "start_time",
  "stop_time",
  "'r'",
  "",
  "repeat_interval",
  "active_duration",
  "time_offset",
  "",
  "",
  "typed_time",
  "'z'",
  "zone_adjustment",
  "",
  "",
  "",
  "time",
  "'k'",
  "",
  "sdp_key",
  "",
  "key_type",
  "key_data",
  "EMAIL_SAFE",
  "\"~\"",
  "",
  "",
  "'a'",
  "",
  "attribute_body",
  "rtpmap",
  "sendmode",
  "att_field",
  "att_value",
  "",
  "",
  "\"RTPMAP\"",
  "",
  "rtpmapbody",
  "payload_type",
  "encoding_name",
  "",
  "clock_rate",
  "",
  "enc_params",
  "",
  "\"SENDRECV\"",
  "",
  "\"SENDONLY\"",
  "",
  "\"RECVONLY\"",
  "",
  "",
  "",
  "",
  "ALPHA_NUMERIC",
  "",
  "media_line",
  "",
  "",
  "media_fields",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "'m'",
  "",
  "",
  "media_body",
  "media_data",
  "format_list",
  "",
  "media_data_nas",
  "",
  "media",
  "port",
  "subport",
  "proto",
  "ex_port",
  "\"NAS\"",
  "nas_access_method",
  "fmt",
  "",
  "",
  "",
  "",
  "",
  "vcId",
  "ALPHA_NUMERIC_ATM",
  "",
  "",
  "",
  "",
  "known_transport_proto",
  "ANY_BYTE_NO_SPACE",
  "byte_string_before_colon",
  "",
  "",
  "",
  "",
  "hexstring",
  "HEX",
  "",
  "integerstring",
  "ip4_connection_address",
  "addr",
  "ip4_multicast_address",
  "ip6_connection_address",
  "multicast_ipv6_hexpart",
  "IP6_address",
  "partial_IP4_address",
  "hexseq",
  "hex1to4",
  "",
  "",
  "",
  "hex2",
  "",
  "ipv6_suffix",
  "\"::\"",
  "",
  "",
  "multicast_ipv6_prefix",
  "",
  "unicast_ipv6_prefix_alpha",
  "",
  "",
  "unicast_ipv6_prefix",
  "unicast_ipv6_suffix",
  "",
  "ttl",
  "num_of_addr",
  "",
  "\"0\"",
  "DIGIT9",
  "",
  "number",
  "fixed_len_time_unit",
  "\"D\"",
  "\"H\"",
  "\"M\"",
  "\"S\"",
  "",
  "",
  "",
  "",
  "email",
  "local_part",
  "\"@\"",
  "domain",
  "word",
  "\".\"",
  "",
  "",
  "",
  "sub_domain",
  "",
  "",
  "",
  "domain_ref",
  "domain_literal",
  "atom",
  "quoted_string",
  "EMAIL_ATOM_ONLY",
  "",
  "",
  "",
  "\"[\"",
  "dtext",
  "quoted_pair",
  "",
  "",
  "",
  "\"]\"",
  "",
  "",
  "\"\\\\\"",
  "CHAR",
  "\"\\\"\"",
  "qtext",
  "",
  "",
  "",
  "scheme",
  "\":\"",
  "path",
  "\"?\"",
  "search",
  "",
  "ialpha",
  "void",
  "\"/\"",
  "xpalphas",
  "\"+\"",
  "",
  "URI_SAFE",
  "URI_EXTRA",
  "uri_escape",
  "ALPHA",
  "",
  "\"%\"",
  "",
  "",
  "phone",
  "",
  "",
  "",
  "",
  "",
  "FQDN",
  "",
  "hex4",
  "aliasstr",
  "",
  "otherstr",
  "",
  "global_tnaddr",
  "local_tnaddr",
  "",
  "",
  "'+'",
  "",
  "",
  "",
  "'X'",
  "",
  "",
  "",
  "",
  "ex_vcci",
  "ex_cid",
  "ex_bcg",
  "ex_portid",
  "ex_vpi",
  "ex_vci",
  "ex_vpci",
  "atm_type_addr_m",
  "\"VCCI\"",
  "genericU16",
  "\"CID\"",
  "genericU8",
  "\"BCG\"",
  "\"PORT\"",
  "genericU32",
  "\"VPI\"",
  "genericU12",
  "\"VCI\"",
  "\"VPCI\"",
  "\"NSAP-$\"",
  "\"E164-$\"",
  "\"GWID-$\"",
  "\"ALIAS-$\"",
  "\"0X\"",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "\"AAL1/\"",
  "transport_list",
  "\"AAL2/\"",
  "\"AAL5/\"",
  "\"RTP/AVP\"",
  "\"H323C-\"",
  "\"ATMF\"",
  "\"ITU\"",
  "\"CUSTOM\"",
  "\"IEEE:\"",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",

};

#ifndef MISSING_FORMAT
#define MISSING_FORMAT "Missing %s"
#endif
#ifndef UNEXPECTED_FORMAT
#define UNEXPECTED_FORMAT "Unexpected %s"
#endif
#ifndef UNNAMED_TOKEN
#define UNNAMED_TOKEN "input"
#endif


static void ag_diagnose(PCB_DECL) {
  int ag_snd = (PCB).sn;
  int ag_k = ag_sbt[ag_snd];

  if (*TOKEN_NAMES[ag_tstt[ag_k]] && ag_astt[ag_k + 1] == ag_action_8) {
    sprintf((PCB).ag_msg, MISSING_FORMAT, TOKEN_NAMES[ag_tstt[ag_k]]);
  }
  else if (ag_astt[ag_sbe[(PCB).sn]] == ag_action_8
          && (ag_k = (int) ag_sbe[(PCB).sn] + 1) == (int) ag_sbt[(PCB).sn+1] - 1
          && *TOKEN_NAMES[ag_tstt[ag_k]]) {
    sprintf((PCB).ag_msg, MISSING_FORMAT, TOKEN_NAMES[ag_tstt[ag_k]]);
  }
  else if ((PCB).token_number && *TOKEN_NAMES[(PCB).token_number]) {
    sprintf((PCB).ag_msg, UNEXPECTED_FORMAT, TOKEN_NAMES[(PCB).token_number]);
  }
  else if (isprint(INPUT_CODE((*(PCB).pointer))) && INPUT_CODE((*(PCB).pointer)) != '\\') {
    char buf[20];
    sprintf(buf, "\'%c\'", (char) INPUT_CODE((*(PCB).pointer)));
    sprintf((PCB).ag_msg, UNEXPECTED_FORMAT, buf);
  }
  else sprintf((PCB).ag_msg, UNEXPECTED_FORMAT, UNNAMED_TOKEN);
  (PCB).error_message = (PCB).ag_msg;


}
static int ag_action_1_r_proc(PCB_DECL);
static int ag_action_2_r_proc(PCB_DECL);
static int ag_action_3_r_proc(PCB_DECL);
static int ag_action_4_r_proc(PCB_DECL);
static int ag_action_1_s_proc(PCB_DECL);
static int ag_action_3_s_proc(PCB_DECL);
static int ag_action_1_proc(PCB_DECL);
static int ag_action_2_proc(PCB_DECL);
static int ag_action_3_proc(PCB_DECL);
static int ag_action_4_proc(PCB_DECL);
static int ag_action_5_proc(PCB_DECL);
static int ag_action_6_proc(PCB_DECL);
static int ag_action_7_proc(PCB_DECL);
static int ag_action_8_proc(PCB_DECL);
static int ag_action_9_proc(PCB_DECL);
static int ag_action_10_proc(PCB_DECL);
static int ag_action_11_proc(PCB_DECL);
static int ag_action_8_proc(PCB_DECL);


static int (*const  ag_r_procs_scan[])(PCB_DECL) = {
  ag_action_1_r_proc,
  ag_action_2_r_proc,
  ag_action_3_r_proc,
  ag_action_4_r_proc
};

static int (*const  ag_s_procs_scan[])(PCB_DECL) = {
  ag_action_1_s_proc,
  ag_action_2_r_proc,
  ag_action_3_s_proc,
  ag_action_4_r_proc
};

static int (*const  ag_gt_procs_scan[])(PCB_DECL) = {
  ag_action_1_proc,
  ag_action_2_proc,
  ag_action_3_proc,
  ag_action_4_proc,
  ag_action_5_proc,
  ag_action_6_proc,
  ag_action_7_proc,
  ag_action_8_proc,
  ag_action_9_proc,
  ag_action_10_proc,
  ag_action_11_proc,
  ag_action_8_proc
};


static int ag_action_10_proc(PCB_DECL) {
  int ag_t = (PCB).token_number;
  (PCB).btsx = 0, (PCB).drt = -1;
  do {
    ag_track(PCB_POINTER);
    (PCB).token_number = (rvSdpParser_token_type) AG_TCV(INPUT_CODE(*(PCB).la_ptr));
    (PCB).la_ptr++;
    if (ag_key_index[(PCB).sn]) {
      unsigned ag_k = ag_key_index[(PCB).sn];
      int ag_ch = CONVERT_CASE(INPUT_CODE(*(PCB).pointer));
      while (ag_key_ch[ag_k] < ag_ch) ag_k++;
      if (ag_key_ch[ag_k] == ag_ch) ag_get_key_word((PCB_TYPE *)PCB_POINTER, ag_k);
    }
  } while ((PCB).token_number == (rvSdpParser_token_type) ag_t);
  (PCB).la_ptr =  (PCB).pointer;
  return 1;
}

static int ag_action_11_proc(PCB_DECL) {
  int ag_t = (PCB).token_number;

  (PCB).btsx = 0, (PCB).drt = -1;
  do {
    (*(int *) &(PCB).vs[(PCB).ssx]) = *(PCB).pointer;
    (PCB).ssx--;
    ag_track(PCB_POINTER);
    ag_ra(PCB_POINTER);
    if ((PCB).exit_flag != AG_RUNNING_CODE) return 0;
    (PCB).ssx++;
    (PCB).token_number = (rvSdpParser_token_type) AG_TCV(INPUT_CODE(*(PCB).la_ptr));
    (PCB).la_ptr++;
    if (ag_key_index[(PCB).sn]) {
      unsigned ag_k = ag_key_index[(PCB).sn];
      int ag_ch = CONVERT_CASE(INPUT_CODE(*(PCB).pointer));
      while (ag_key_ch[ag_k] < ag_ch) ag_k++;
      if (ag_key_ch[ag_k] == ag_ch) ag_get_key_word((PCB_TYPE *)PCB_POINTER, ag_k);
    }
  }
  while ((PCB).token_number == (rvSdpParser_token_type) ag_t);
  (PCB).la_ptr =  (PCB).pointer;
  return 1;
}

static int ag_action_3_r_proc(PCB_DECL) {
  int ag_sd = ag_fl[(PCB).ag_ap] - 1;
  if (ag_sd) (PCB).sn = (PCB).ss[(PCB).ssx -= ag_sd];
  (PCB).btsx = 0, (PCB).drt = -1;
  (PCB).reduction_token = (rvSdpParser_token_type) ag_ptt[(PCB).ag_ap];
  ag_ra(PCB_POINTER);
  return (PCB).exit_flag == AG_RUNNING_CODE;
}

static int ag_action_3_s_proc(PCB_DECL) {
  int ag_sd = ag_fl[(PCB).ag_ap] - 1;
  if (ag_sd) (PCB).sn = (PCB).ss[(PCB).ssx -= ag_sd];
  (PCB).btsx = 0, (PCB).drt = -1;
  (PCB).reduction_token = (rvSdpParser_token_type) ag_ptt[(PCB).ag_ap];
  ag_ra(PCB_POINTER);
  return (PCB).exit_flag == AG_RUNNING_CODE;;
}

static int ag_action_4_r_proc(PCB_DECL) {
  int ag_sd = ag_fl[(PCB).ag_ap] - 1;
  if (ag_sd) (PCB).sn = (PCB).ss[(PCB).ssx -= ag_sd];
  (PCB).reduction_token = (rvSdpParser_token_type) ag_ptt[(PCB).ag_ap];
  return 1;
}

static int ag_action_2_proc(PCB_DECL) {
  (PCB).btsx = 0, (PCB).drt = -1;
  if ((PCB).ssx >= 43) {
    (PCB).exit_flag = AG_STACK_ERROR_CODE;
    PARSER_STACK_OVERFLOW;
  }
  (*(int *) &(PCB).vs[(PCB).ssx]) = *(PCB).pointer;
  (PCB).ss[(PCB).ssx] = (PCB).sn;
  (PCB).ssx++;
  (PCB).sn = (PCB).ag_ap;
  ag_track(PCB_POINTER);
  return 0;
}

static int ag_action_9_proc(PCB_DECL) {
  if ((PCB).drt == -1) {
    (PCB).drt=(PCB).token_number;
    (PCB).dssx=(PCB).ssx;
    (PCB).dsn=(PCB).sn;
  }
  ag_prot(PCB_POINTER);
  (PCB).vs[(PCB).ssx] = ag_null_value;
  (PCB).ss[(PCB).ssx] = (PCB).sn;
  (PCB).ssx++;
  (PCB).sn = (PCB).ag_ap;
  (PCB).la_ptr =  (PCB).pointer;
  return (PCB).exit_flag == AG_RUNNING_CODE;
}

static int ag_action_2_r_proc(PCB_DECL) {
  (PCB).ssx++;
  (PCB).sn = (PCB).ag_ap;
  return 0;
}

static int ag_action_7_proc(PCB_DECL) {
  --(PCB).ssx;
  (PCB).la_ptr =  (PCB).pointer;
  (PCB).exit_flag = AG_SUCCESS_CODE;
  return 0;
}

static int ag_action_1_proc(PCB_DECL) {
  ag_track(PCB_POINTER);
  (PCB).exit_flag = AG_SUCCESS_CODE;
  return 0;
}

static int ag_action_1_r_proc(PCB_DECL) {
  (PCB).exit_flag = AG_SUCCESS_CODE;
  return 0;
}

static int ag_action_1_s_proc(PCB_DECL) {
  (PCB).exit_flag = AG_SUCCESS_CODE;
  return 0;
}

static int ag_action_4_proc(PCB_DECL) {
  int ag_sd = ag_fl[(PCB).ag_ap] - 1;
  (PCB).reduction_token = (rvSdpParser_token_type) ag_ptt[(PCB).ag_ap];
  (PCB).btsx = 0, (PCB).drt = -1;
  (*(int *) &(PCB).vs[(PCB).ssx]) = *(PCB).pointer;
  if (ag_sd) (PCB).sn = (PCB).ss[(PCB).ssx -= ag_sd];
  else (PCB).ss[(PCB).ssx] = (PCB).sn;
  ag_track(PCB_POINTER);
  while ((PCB).exit_flag == AG_RUNNING_CODE) {
    unsigned ag_t1 = ag_sbe[(PCB).sn] + 1;
    unsigned ag_t2 = ag_sbt[(PCB).sn+1] - 1;
    do {
      unsigned ag_tx = (ag_t1 + ag_t2)/2;
      if (ag_tstt[ag_tx] < (const unsigned short)(PCB).reduction_token) ag_t1 = ag_tx + 1;
      else ag_t2 = ag_tx;
    } while (ag_t1 < ag_t2);
    (PCB).ag_ap = ag_pstt[ag_t1];
    if ((ag_s_procs_scan[ag_astt[ag_t1]])(PCB_POINTER) == 0) break;
  }
  return 0;
}

static int ag_action_3_proc(PCB_DECL) {
  int ag_sd = ag_fl[(PCB).ag_ap] - 1;
  (PCB).btsx = 0, (PCB).drt = -1;
  (*(int *) &(PCB).vs[(PCB).ssx]) = *(PCB).pointer;
  if (ag_sd) (PCB).sn = (PCB).ss[(PCB).ssx -= ag_sd];
  else (PCB).ss[(PCB).ssx] = (PCB).sn;
  ag_track(PCB_POINTER);
  (PCB).reduction_token = (rvSdpParser_token_type) ag_ptt[(PCB).ag_ap];
  ag_ra(PCB_POINTER);
  while ((PCB).exit_flag == AG_RUNNING_CODE) {
    unsigned ag_t1 = ag_sbe[(PCB).sn] + 1;
    unsigned ag_t2 = ag_sbt[(PCB).sn+1] - 1;
    do {
      unsigned ag_tx = (ag_t1 + ag_t2)/2;
      if (ag_tstt[ag_tx] < (const unsigned short)(PCB).reduction_token) ag_t1 = ag_tx + 1;
      else ag_t2 = ag_tx;
    } while (ag_t1 < ag_t2);
    (PCB).ag_ap = ag_pstt[ag_t1];
    if ((ag_s_procs_scan[ag_astt[ag_t1]])(PCB_POINTER) == 0) break;
  }
  return 0;
}

static int ag_action_8_proc(PCB_DECL) {
  ag_undo(PCB_POINTER);
  (PCB).la_ptr =  (PCB).pointer;
  (PCB).exit_flag = AG_SYNTAX_ERROR_CODE;
  ag_diagnose(PCB_POINTER);
  SYNTAX_ERROR;
  {(PCB).la_ptr = (PCB).pointer + 1; ag_track(PCB_POINTER);}
  return (PCB).exit_flag == AG_RUNNING_CODE;
}

static int ag_action_5_proc(PCB_DECL) {
  int ag_sd = ag_fl[(PCB).ag_ap];
  (PCB).btsx = 0, (PCB).drt = -1;
  if (ag_sd) (PCB).sn = (PCB).ss[(PCB).ssx -= ag_sd];
  else {
    (PCB).ss[(PCB).ssx] = (PCB).sn;
  }
  (PCB).la_ptr =  (PCB).pointer;
  (PCB).reduction_token = (rvSdpParser_token_type) ag_ptt[(PCB).ag_ap];
  ag_ra(PCB_POINTER);
  while ((PCB).exit_flag == AG_RUNNING_CODE) {
    unsigned ag_t1 = ag_sbe[(PCB).sn] + 1;
    unsigned ag_t2 = ag_sbt[(PCB).sn+1] - 1;
    do {
      unsigned ag_tx = (ag_t1 + ag_t2)/2;
      if (ag_tstt[ag_tx] < (const unsigned short)(PCB).reduction_token) ag_t1 = ag_tx + 1;
      else ag_t2 = ag_tx;
    } while (ag_t1 < ag_t2);
    (PCB).ag_ap = ag_pstt[ag_t1];
    if ((ag_r_procs_scan[ag_astt[ag_t1]])(PCB_POINTER) == 0) break;
  }
  return (PCB).exit_flag == AG_RUNNING_CODE;
}

static int ag_action_6_proc(PCB_DECL) {
  int ag_sd = ag_fl[(PCB).ag_ap];
  (PCB).reduction_token = (rvSdpParser_token_type) ag_ptt[(PCB).ag_ap];
  if ((PCB).drt == -1) {
    (PCB).drt=(PCB).token_number;
    (PCB).dssx=(PCB).ssx;
    (PCB).dsn=(PCB).sn;
  }
  if (ag_sd) {
    (PCB).sn = (PCB).ss[(PCB).ssx -= ag_sd];
  }
  else {
    ag_prot(PCB_POINTER);
    (PCB).vs[(PCB).ssx] = ag_null_value;
    (PCB).ss[(PCB).ssx] = (PCB).sn;
  }
  (PCB).la_ptr =  (PCB).pointer;
  while ((PCB).exit_flag == AG_RUNNING_CODE) {
    unsigned ag_t1 = ag_sbe[(PCB).sn] + 1;
    unsigned ag_t2 = ag_sbt[(PCB).sn+1] - 1;
    do {
      unsigned ag_tx = (ag_t1 + ag_t2)/2;
      if (ag_tstt[ag_tx] < (const unsigned short)(PCB).reduction_token) ag_t1 = ag_tx + 1;
      else ag_t2 = ag_tx;
    } while (ag_t1 < ag_t2);
    (PCB).ag_ap = ag_pstt[ag_t1];
    if ((ag_r_procs_scan[ag_astt[ag_t1]])(PCB_POINTER) == 0) break;
  }
  return (PCB).exit_flag == AG_RUNNING_CODE;
}


void init_rvSdpParser(rvSdpParser_pcb_type *PCB_POINTER) {
  (PCB).la_ptr = (PCB).pointer;
  (PCB).ss[0] = (PCB).sn = (PCB).ssx = 0;
  (PCB).exit_flag = AG_RUNNING_CODE;
  (PCB).line = FIRST_LINE;
  (PCB).column = FIRST_COLUMN;
  (PCB).btsx = 0, (PCB).drt = -1;
}

void rvSdpParser(rvSdpParser_pcb_type *PCB_POINTER) {
  init_rvSdpParser(PCB_POINTER);
  (PCB).exit_flag = AG_RUNNING_CODE;
  while ((PCB).exit_flag == AG_RUNNING_CODE) {
    unsigned ag_t1 = ag_sbt[(PCB).sn];
    if (ag_tstt[ag_t1]) {
      unsigned ag_t2 = ag_sbe[(PCB).sn] - 1;
      (PCB).token_number = (rvSdpParser_token_type) AG_TCV(INPUT_CODE(*(PCB).la_ptr));
      (PCB).la_ptr++;
      if (ag_key_index[(PCB).sn]) {
        unsigned ag_k = ag_key_index[(PCB).sn];
        int ag_ch = CONVERT_CASE(INPUT_CODE(*(PCB).pointer));
        while (ag_key_ch[ag_k] < ag_ch) ag_k++;
        if (ag_key_ch[ag_k] == ag_ch) ag_get_key_word((PCB_TYPE *)PCB_POINTER, ag_k);
      }
      do {
        unsigned ag_tx = (ag_t1 + ag_t2)/2;
        if (ag_tstt[ag_tx] > (const unsigned short)(PCB).token_number)
          ag_t1 = ag_tx + 1;
        else ag_t2 = ag_tx;
      } while (ag_t1 < ag_t2);
      if (ag_tstt[ag_t1] != (const unsigned short)(PCB).token_number)
        ag_t1 = ag_sbe[(PCB).sn];
    }
    (PCB).ag_ap = ag_pstt[ag_t1];
    (ag_gt_procs_scan[ag_astt[ag_t1]])((PCB_TYPE *)PCB_POINTER);
  }
}


