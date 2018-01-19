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

#ifndef RVSDPPRS_BADSYNTAX_H_1094397741
#include "rvsdpprs_BadSyntax.h"
#endif

#ifndef RVSDPPRS_BADSYNTAX_H_1094397741
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
/* Line 239, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
 PRS_STATE->cur_line = PRS_STATE->cur_token  = (char*)PCB.pointer; 
}

static void ag_rp_8(PCB_DECL) {
/* Line 240, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
 PRS_STATE->cur_line = PRS_STATE->cur_token  = (char*)PCB.pointer; 
}

static void ag_rp_9(PCB_DECL) {
/* Line 243, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
	BEGIN_TOKEN();
}

static void ag_rp_10(PCB_DECL) {
/* Line 244, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
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

static void ag_rp_23(PCB_DECL) {
/* Line 356, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
        ATTACH_PARSER_BACK_TO_BUFF(RV_SDPPARSER_PREFIX_CONT);
    
}

static void ag_rp_24(PCB_DECL) {
/* Line 361, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
        ATTACH_PARSER_BACK_TO_BUFF(RV_SDPPARSER_PREFIX_CONT_M);
    
}

static void ag_rp_25(PCB_DECL) {
/* Line 366, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
        ATTACH_PARSER_BACK_TO_BUFF(RV_SDPPARSER_PREFIX_REPARSE);
    
}

static void ag_rp_26(PCB_DECL, RvpStrPtrN s) {
/* Line 368, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
rvSdpMsgSetBadSyntxField(PCB_PTR ,s.buf,s.len);
}

static void ag_rp_27(PCB_DECL) {
/* Line 369, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
rvSdpMsgSetBadSyntxField(PCB_PTR ,"",0);
}

static void ag_rp_28(PCB_DECL) {
/* Line 374, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
        ATTACH_PARSER_BACK_TO_BUFF(RV_SDPPARSER_PREFIX_BAD_SYNTAX);
    
}

static void ag_rp_29(PCB_DECL, RvpStrPtrN s) {
/* Line 376, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
rvSdpMsgSetBadSyntxField(PCB_PTR ,s.buf,s.len);
}

static void ag_rp_30(PCB_DECL) {
/* Line 377, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
rvSdpMsgSetBadSyntxField(PCB_PTR ,"",0);
}

static void ag_rp_31(PCB_DECL, RvpStrPtrN s) {
/* Line 379, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
rvSdpMsgSetBadSyntxField(PCB_PTR ,s.buf,s.len);
}

static void ag_rp_32(PCB_DECL) {
/* Line 380, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
rvSdpMsgSetBadSyntxField(PCB_PTR ,"",0);
}

static void ag_rp_33(PCB_DECL, RvpStrPtrN s) {
/* Line 383, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
rvSdpMsgSetBadSyntxFieldM(PCB_PTR ,s.buf,s.len);
}

static void ag_rp_34(PCB_DECL) {
/* Line 384, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
rvSdpMsgSetBadSyntxFieldM(PCB_PTR ,"",0);
}

static void ag_rp_35(PCB_DECL) {
/* Line 389, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
        ATTACH_PARSER_BACK_TO_BUFF(RV_SDPPARSER_PREFIX_BAD_SYNTAX_M);
    
}

#define ag_rp_36(PCB_POINTER) (CUR_CHAR())

#define ag_rp_37(PCB_POINTER) (rvSdpParseAuxSetType(PCB_PTR,SDP_FIELDTYPE_UNKNOWN_TAG))

#define ag_rp_39(PCB_POINTER, t, v) (SDPASSERT_MEM(rvSdpCommonFieldsAddOtherN(PRS_STATE->cur_sdp_fields,t,v.buf,v.len,PRS_ALLOC)))

#define ag_rp_40(PCB_POINTER) (rvSdpParseAuxResetType(PCB_PTR))

#define ag_rp_41(PCB_POINTER) (rvSdpParseAuxSetType(PCB_PTR,SDP_FIELDTYPE_VERSION))

#define ag_rp_42(PCB_POINTER) (rvSdpParseAuxResetType(PCB_PTR))

static void ag_rp_43(PCB_DECL) {
/* Line 408, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
 
			if(rvSdpMsgSetVersionN(SDP_MSG,TOKEN_START,TOKEN_LENGTH)!=RV_OK) {
				rvSdpParseSetSemErr(&(PCB),"Field too long");
			} 
		
}

static void ag_rp_44(PCB_DECL) {
/* Line 416, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
rvSdpParseAuxSetType(PCB_PTR,SDP_FIELDTYPE_ORIGIN);
}

static void ag_rp_45(PCB_DECL, RvpStrPtrN u, RvpStrPtrN i, RvpStrPtrN v) {
/* Line 419, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
			rvSdpParserAuxSetOriginN(PCB_PTR,SDP_MSG,u.buf,u.len,i.buf,i.len,v.buf,v.len);
			
		
}

#define ag_rp_46(PCB_POINTER) (rvSdpParseAuxSetType(PCB_PTR,SDP_FIELDTYPE_SESSION))

#define ag_rp_47(PCB_POINTER, s) (rvSdpParseAuxResetType(PCB_PTR))

#define ag_rp_48(PCB_POINTER, s) (SDPASSERT_MEM2(rvSdpMsgSetSessionNameN(SDP_MSG,s.buf,s.len)))

#define ag_rp_49(PCB_POINTER) (rvSdpParseAuxResetType(PCB_PTR))

#define ag_rp_50(PCB_POINTER) (SDPASSERT_MEM2(rvSdpMsgSetSessionNameN(SDP_MSG,"",0)))

#define ag_rp_51(PCB_POINTER) (rvSdpParseAuxSetType(PCB_PTR,SDP_FIELDTYPE_INFORMATION))

#define ag_rp_52(PCB_POINTER, s) (rvSdpParseAuxResetType(PCB_PTR))

#define ag_rp_53(PCB_POINTER, s) (SDPASSERT_MEM2(rvSdpCommonFieldsSetInformationN(PRS_STATE->cur_sdp_fields,s.buf,s.len)))

#define ag_rp_54(PCB_POINTER) (rvSdpParseAuxResetType(PCB_PTR))

#define ag_rp_55(PCB_POINTER) (SDPASSERT_MEM2(rvSdpCommonFieldsSetInformationN(PRS_STATE->cur_sdp_fields,"",0)))

#define ag_rp_56(PCB_POINTER) (rvSdpParseAuxSetType(PCB_PTR,SDP_FIELDTYPE_URI))

#define ag_rp_57(PCB_POINTER, u) (rvSdpParseAuxSetURI(PCB_PTR,u.buf,u.len))

static void ag_rp_58(PCB_DECL) {
/* Line 441, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
rvSdpParseAuxSetType(PCB_PTR,SDP_FIELDTYPE_EMAIL);
}

static void ag_rp_59(PCB_DECL) {
/* Line 443, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
rvSdpParseAuxResetType(PCB_PTR);
}

static void ag_rp_60(PCB_DECL) {
/* Line 448, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
rvSdpParseAuxSetType(PCB_PTR,SDP_FIELDTYPE_PHONE);
}

#define ag_rp_61(PCB_POINTER) (rvSdpParseAuxSetType(PCB_PTR,SDP_FIELDTYPE_CONNECTION))

#define ag_rp_62(PCB_POINTER) (rvSdpParseAuxResetType(PCB_PTR))

static void ag_rp_63(PCB_DECL) {
/* Line 454, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
		rvSdpParserAuxSetConnectionN(PCB_PTR);
	
}

static void ag_rp_64(PCB_DECL, RvpStrPtrN a, RvpStrPtrN ca) {
/* Line 460, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
 
		rvSdpParserAuxSaveAddr(PCB_PTR, "-", 1, a.buf, a.len, ca.buf, ca.len);
	
}

static void ag_rp_65(PCB_DECL, RvpStrPtrN a, RvpStrPtrN ca) {
/* Line 463, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
 
		rvSdpParserAuxSaveAddr(PCB_PTR, "$", 1, a.buf, a.len, ca.buf, ca.len);
	
}

static void ag_rp_66(PCB_DECL, RvpStrPtrN a, RvpStrPtrN ca) {
/* Line 466, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
 
		rvSdpParserAuxSaveAddr(PCB_PTR, "IN", 2, a.buf, a.len, ca.buf, ca.len);
	
}

static void ag_rp_67(PCB_DECL, RvpStrPtrN a, RvpStrPtrN ca) {
/* Line 470, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
 
		rvSdpParserAuxSaveAddr(PCB_PTR, "TN", 2, a.buf, a.len, ca.buf, ca.len);
	
}

static void ag_rp_68(PCB_DECL, RvpStrPtrN a, RvpStrPtrN ca) {
/* Line 473, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
 
		rvSdpParserAuxSaveAddr(PCB_PTR, "ATM", 3, a.buf, a.len, ca.buf, ca.len);
	
}

static void ag_rp_69(PCB_DECL, RvpStrPtrN ca) {
/* Line 477, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
 
		rvSdpParserAuxSaveAddr(PCB_PTR, "ATM", 3, "NSAP", 4, ca.buf, ca.len);
	
}

static void ag_rp_70(PCB_DECL, RvpStrPtrN ca) {
/* Line 480, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
 
		rvSdpParserAuxSaveAddr(PCB_PTR, "ATM", 3, "E164", 4, ca.buf, ca.len);
	
}

static void ag_rp_71(PCB_DECL, RvpStrPtrN ca) {
/* Line 483, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
 
		rvSdpParserAuxSaveAddr(PCB_PTR, "ATM", 3, "GWID", 4, ca.buf, ca.len);
	
}

static void ag_rp_72(PCB_DECL, RvpStrPtrN ca) {
/* Line 486, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
 
		rvSdpParserAuxSaveAddr(PCB_PTR, "ATM", 3, "ALIAS", 5, ca.buf, ca.len);
	
}

static void ag_rp_73(PCB_DECL, RvpStrPtrN addr, RvpStrPtrN a) {
/* Line 490, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
		rvSdpParserAuxSaveAddr(PCB_PTR, "ATM", 3, addr.buf, addr.len, a.buf, a.len);	
	
}

static void ag_rp_74(PCB_DECL, RvpStrPtrN a) {
/* Line 494, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
 
		rvSdpParserAuxSaveAddr(PCB_PTR, "IN", 2, "IP4", 3, a.buf, a.len);
	
}

static void ag_rp_75(PCB_DECL, RvpStrPtrN a) {
/* Line 497, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
 
		rvSdpParserAuxSaveAddr(PCB_PTR, "IN", 2, "IP6", 3, a.buf, a.len);
	
}

static void ag_rp_76(PCB_DECL, RvpStrPtrN addr, RvpStrPtrN a) {
/* Line 502, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
		rvSdpParserAuxSaveAddr(PCB_PTR, "IN", 2, addr.buf, addr.len, a.buf, a.len);	
	
}

static void ag_rp_77(PCB_DECL, RvpStrPtrN a) {
/* Line 505, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
 
		rvSdpParserAuxSaveAddr(PCB_PTR, "TN", 2, "RFC2543", 7, a.buf, a.len);
	
}

static void ag_rp_78(PCB_DECL, RvpStrPtrN tn, RvpStrPtrN a) {
/* Line 508, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
 
		rvSdpParserAuxSaveAddr(PCB_PTR, "TN", 2, tn.buf, tn.len, a.buf, a.len);
	
}

static void ag_rp_79(PCB_DECL, RvpStrPtrN n, RvpStrPtrN a) {
/* Line 513, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
		rvSdpParserAuxSaveAddr(PCB_PTR, n.buf,n.len, "IP4",3, a.buf, a.len);	
	
}

static void ag_rp_80(PCB_DECL, RvpStrPtrN n, RvpStrPtrN a) {
/* Line 516, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
		rvSdpParserAuxSaveAddr(PCB_PTR, n.buf,n.len, "IP6",3, a.buf, a.len);	
	
}

static void ag_rp_81(PCB_DECL, RvpStrPtrN n, RvpStrPtrN addr, RvpStrPtrN a) {
/* Line 519, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
		rvSdpParserAuxSaveAddr(PCB_PTR, n.buf,n.len, addr.buf, addr.len, a.buf, a.len);	
	
}

#define ag_rp_113(PCB_POINTER) (rvSdpParseAuxSetType(PCB_PTR,SDP_FIELDTYPE_BANDWIDTH))

#define ag_rp_114(PCB_POINTER, t, b) (rvSdpParseAuxSetBandwidth(PCB_PTR,t.buf,t.len,b))

#define ag_rp_115(PCB_POINTER) (rvSdpParseAuxSetType(PCB_PTR,SDP_FIELDTYPE_TIME))

#define ag_rp_116(PCB_POINTER) (rvSdpParseAuxResetType(PCB_PTR))

#define ag_rp_117(PCB_POINTER) (rvSdpParseAuxResetType(PCB_PTR))

static void ag_rp_118(PCB_DECL) {
/* Line 592, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
rvSdpParseAuxResetType(PCB_PTR);rvSdpParseAuxClearRepeat(PCB_PTR);
}

#define ag_rp_119(PCB_POINTER, start, stop) (rvSdpParseAuxAddSessionTime(PCB_PTR,start,stop))

#define ag_rp_120(PCB_POINTER) (rvSdpParseAuxSetType(PCB_PTR,SDP_FIELDTYPE_REPEAT))

#define ag_rp_121(PCB_POINTER, t) (rvSdpParseAuxAddSessionRepeatField(PCB_PTR,t))

#define ag_rp_122(PCB_POINTER, t) (rvSdpParseAuxSetRepeatActiveDuration(PCB_PTR,t))

#define ag_rp_123(PCB_POINTER, t) (rvSdpParseAuxAddRepeatOffset(PCB_PTR,t))

#define ag_rp_124(PCB_POINTER, t, tt) (rvSdpParseAuxAddZoneAdjustment(PCB_PTR,t,tt.time,tt.type))

#define ag_rp_125(PCB_POINTER, t, tt) (rvSdpParseAuxAddZoneAdjustment(PCB_PTR,t,tt.time*(-1),tt.type))

#define ag_rp_126(PCB_POINTER) (rvSdpParseAuxSetType(PCB_PTR,SDP_FIELDTYPE_KEY))

#define ag_rp_127(PCB_POINTER) (rvSdpParseAuxResetType(PCB_PTR))

#define ag_rp_128(PCB_POINTER, t) (rvSdpParserAuxSetKeyN(PCB_PTR,t,empty_str,0))

#define ag_rp_129(PCB_POINTER, t) (rvSdpParserAuxSetKeyN(PCB_PTR,t,empty_str,0))

#define ag_rp_130(PCB_POINTER, t, d) (rvSdpParserAuxSetKeyN(PCB_PTR,t,d.buf,d.len))

#define ag_rp_133(PCB_POINTER) (rvSdpParseAuxSetType(PCB_PTR,SDP_FIELDTYPE_ATTRIBUTE))

#define ag_rp_134(PCB_POINTER, f, v) (rvSdpParseAuxResetType(PCB_PTR))

#define ag_rp_135(PCB_POINTER, f, v) (SDPASSERT_MEM(rvSdpCommonFieldsAddAttrN(PRS_STATE->cur_sdp_fields,f.buf,f.len,v.buf,v.len,PRS_ALLOC)))

#define ag_rp_136(PCB_POINTER, f) (rvSdpParseAuxResetType(PCB_PTR))

#define ag_rp_137(PCB_POINTER, f) (SDPASSERT_MEM(rvSdpCommonFieldsAddAttrN(PRS_STATE->cur_sdp_fields,f.buf,f.len,"",0,PRS_ALLOC)))

#define ag_rp_138(PCB_POINTER) (rvSdpParseAuxSetType(PCB_PTR,SDP_FIELDTYPE_RTP_MAP))

#define ag_rp_139(PCB_POINTER, p, n) (rvSdpParseAuxResetType(PCB_PTR))

#define ag_rp_140(PCB_POINTER, p, n) (SDPASSERT_MEM(rvSdpParseAuxAddRtpMap(PCB_PTR,p,n.buf,n.len,8000)))

#define ag_rp_141(PCB_POINTER, p, n, r) (rvSdpParseAuxResetType(PCB_PTR))

#define ag_rp_142(PCB_POINTER, p, n, r) (SDPASSERT_MEM(rvSdpParseAuxAddRtpMap(PCB_PTR,p,n.buf,n.len,r)))

#define ag_rp_143(PCB_POINTER, p, n, r, pr) (rvSdpParseAuxResetType(PCB_PTR))

static void ag_rp_144(PCB_DECL, int p, RvpStrPtrN n, int r, RvpStrPtrN pr) {
/* Line 666, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
			RvSdpRtpMap * m = rvSdpParseAuxAddRtpMap(PCB_PTR,p,n.buf,n.len,r);
			
			if(SDPASSERT_MEM(m)!=NULL) {
				SDPASSERT_MEM2(rvSdpRtpMapSetEncodingParametersN(m,pr.buf,pr.len));
			}
		
}

#define ag_rp_145(PCB_POINTER) (rvSdpParseAuxResetType(PCB_PTR))

#define ag_rp_146(PCB_POINTER) (SDPASSERT_MEM2(rvSdpCommonFieldsSetConnectionMode(PRS_STATE->cur_sdp_fields,RV_SDPCONNECTMODE_SENDRECV)))

#define ag_rp_147(PCB_POINTER) (rvSdpParseAuxResetType(PCB_PTR))

#define ag_rp_148(PCB_POINTER) (SDPASSERT_MEM2(rvSdpCommonFieldsSetConnectionMode(PRS_STATE->cur_sdp_fields,RV_SDPCONNECTMODE_SENDONLY)))

#define ag_rp_149(PCB_POINTER) (rvSdpParseAuxResetType(PCB_PTR))

#define ag_rp_150(PCB_POINTER) (SDPASSERT_MEM2(rvSdpCommonFieldsSetConnectionMode(PRS_STATE->cur_sdp_fields,RV_SDPCONNECTMODE_RECVONLY)))

static void ag_rp_151(PCB_DECL, RvpStrPtrN t) {
/* Line 676, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
rvSdpParseAuxResetType(PCB_PTR);SDPASSERT_MEM(rvSdpCommonFieldsAddAttrN(PRS_STATE->cur_sdp_fields,"recvonly",0,t.buf,t.len,PRS_ALLOC));
}

static void ag_rp_152(PCB_DECL, RvpStrPtrN t) {
/* Line 677, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
rvSdpParseAuxResetType(PCB_PTR);SDPASSERT_MEM(rvSdpCommonFieldsAddAttrN(PRS_STATE->cur_sdp_fields,"sendrecv",0,t.buf,t.len,PRS_ALLOC));
}

static void ag_rp_153(PCB_DECL, RvpStrPtrN t) {
/* Line 678, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
rvSdpParseAuxResetType(PCB_PTR);SDPASSERT_MEM(rvSdpCommonFieldsAddAttrN(PRS_STATE->cur_sdp_fields,"sendonly",0,t.buf,t.len,PRS_ALLOC));
}

#define ag_rp_154(PCB_POINTER) (CUR_INT())

#define ag_rp_156(PCB_POINTER) (CUR_INT())

#define ag_rp_158(PCB_POINTER) (rvSdpParseAuxResetType(PCB_PTR))

#define ag_rp_159(PCB_POINTER) (rvSdpParseAuxResetType(PCB_PTR))

#define ag_rp_160(PCB_POINTER) (rvSdpParseAuxResetType(PCB_PTR))

#define ag_rp_161(PCB_POINTER) (rvSdpParseAuxResetType(PCB_PTR))

#define ag_rp_162(PCB_POINTER) (rvSdpParseAuxResetType(PCB_PTR))

#define ag_rp_163(PCB_POINTER) (rvSdpParseAuxResetType(PCB_PTR))

#define ag_rp_164(PCB_POINTER) (rvSdpParseAuxResetType(PCB_PTR))

#define ag_rp_165(PCB_POINTER) (PRS_STATE->stat =RV_SDPPARSER_PARSING_MEDIA )

#define ag_rp_166(PCB_POINTER) (rvSdpParseAuxSetType(PCB_PTR,SDP_FIELDTYPE_MEDIA))

#define ag_rp_167(PCB_POINTER) (rvSdpParseAuxResetType(PCB_PTR))

static void ag_rp_168(PCB_DECL) {
/* Line 719, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
rvSdpParseAuxClearCurMediaDescr(PCB_PTR);
}

#define ag_rp_169(PCB_POINTER) (rvSdpParseAuxResetType(PCB_PTR))

static void ag_rp_170(PCB_DECL) {
/* Line 720, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
rvSdpParseAuxClearCurMediaDescr(PCB_PTR);
}

static void ag_rp_171(PCB_DECL, RvpStrPtrN m, int p, int sp, RvpStrPtrN pt) {
/* Line 724, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
 rvSdpParseAuxAddSdpMedia(PCB_PTR,m,p,sp,pt); 
}

static void ag_rp_172(PCB_DECL, RvpStrPtrN m, int p, RvpStrPtrN pt) {
/* Line 725, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
 rvSdpParseAuxAddSdpMedia(PCB_PTR,m,p,RV_SDPFIELD_NOTSET,pt); 
}

#define ag_rp_173(PCB_POINTER, am) (rvSdpParseAuxAddSdpMediaNAS(PCB_PTR,RV_SDPPORT_NOTSET,RV_SDPFIELD_NOTSET,am.buf,am.len))

#define ag_rp_174(PCB_POINTER, am, p) (rvSdpParseAuxAddSdpMediaNAS(PCB_PTR,p,RV_SDPFIELD_NOTSET,am.buf,am.len))

#define ag_rp_175(PCB_POINTER, am, p, sp) (rvSdpParseAuxAddSdpMediaNAS(PCB_PTR,p,sp,am.buf,am.len))

#define ag_rp_178(PCB_POINTER) (CUR_INT16())

#define ag_rp_179(PCB_POINTER) (RV_SDPPORT_ANY)

#define ag_rp_180(PCB_POINTER) (RV_SDPPORT_IGNORE)

#define ag_rp_181(PCB_POINTER) (RV_SDPPORT_ATM)

#define ag_rp_182(PCB_POINTER) (CUR_INT())

#define ag_rp_183(PCB_POINTER) (rvSdpParseAuxAddMediaDescrFormatN(PCB_PTR,TOKEN_START,TOKEN_LENGTH))

#define ag_rp_191(PCB_POINTER, a) (a)

#define ag_rp_197(PCB_POINTER) (PRS_STATE->ttl = CUR_INT())

#define ag_rp_198(PCB_POINTER) (PRS_STATE->num_addr = CUR_INT())

#define ag_rp_199(PCB_POINTER, t) (t)

#define ag_rp_200(PCB_POINTER) (0)

#define ag_rp_201(PCB_POINTER, t) (t)

#define ag_rp_202(PCB_POINTER) (0)

#define ag_rp_203(PCB_POINTER) (CUR_INT())

#define ag_rp_204(PCB_POINTER) (CUR_INT())

static RvSdpTypedTime ag_rp_205(PCB_DECL, unsigned int t) {
/* Line 880, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
			RvSdpTypedTime ttime;
			ttime.time = t;
			ttime.type = RV_SDPTIMETYPE_SECOND;
            RV_UNUSED_ARG(pcb_pointer);
			return ttime;
		
}

static RvSdpTypedTime ag_rp_206(PCB_DECL, unsigned int t, short type) {
/* Line 887, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
			RvSdpTypedTime ttime;
			ttime.time = t;
			ttime.type = (RvSdpTimeUnit)type;
            RV_UNUSED_ARG(pcb_pointer);
			return ttime;
		
}

#define ag_rp_207(PCB_POINTER) (RV_SDPTIMETYPE_DAY)

#define ag_rp_208(PCB_POINTER) (RV_SDPTIMETYPE_HOUR)

#define ag_rp_209(PCB_POINTER) (RV_SDPTIMETYPE_MONTH)

#define ag_rp_210(PCB_POINTER) (RV_SDPTIMETYPE_SECOND)

#define ag_rp_212(PCB_POINTER) (CUR_INT())

static void ag_rp_214(PCB_DECL, RvpStrPtrN e) {
/* Line 912, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
rvSdpParserAuxAddEmail(PCB_PTR,e.buf,e.len,"",0);
}

#define ag_rp_215(PCB_POINTER, e, s) (rvSdpParserAuxAddEmail(PCB_PTR,e.buf,e.len,s.buf,s.len))

#define ag_rp_216(PCB_POINTER, s, e) (rvSdpParserAuxAddEmail(PCB_PTR,e.buf,e.len,s.buf,s.len))

static void ag_rp_219(PCB_DECL, RvpStrPtrN p) {
/* Line 1003, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
rvSdpParseAuxResetType(PCB_PTR);rvSdpParseAuxAddPhone(PCB_PTR,p.buf,p.len,"",0);
}

static void ag_rp_220(PCB_DECL, RvpStrPtrN p, RvpStrPtrN s) {
/* Line 1004, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
rvSdpParseAuxResetType(PCB_PTR);rvSdpParseAuxAddPhone(PCB_PTR,p.buf,p.len,s.buf,s.len);	
}

static void ag_rp_221(PCB_DECL, RvpStrPtrN s, RvpStrPtrN p) {
/* Line 1005, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_BadSyntax.syn */
rvSdpParseAuxResetType(PCB_PTR),rvSdpParseAuxAddPhone(PCB_PTR,p.buf,p.len,s.buf,s.len);
}

#define ag_rp_231(PCB_POINTER, g) (rvSdpParserAuxSaveVcId(PCB_PTR, RV_SDPVCID_VCCI, g.buf, g.len))

#define ag_rp_232(PCB_POINTER, g) (rvSdpParserAuxSaveVcId(PCB_PTR, RV_SDPVCID_CID, g.buf, g.len))

#define ag_rp_233(PCB_POINTER, g) (rvSdpParserAuxSaveVcId(PCB_PTR, RV_SDPVCID_BCG, g.buf, g.len))

#define ag_rp_234(PCB_POINTER, g) (rvSdpParserAuxSaveVcId(PCB_PTR, RV_SDPVCID_PORT, g.buf, g.len))

#define ag_rp_235(PCB_POINTER, g) (rvSdpParserAuxSaveVcId(PCB_PTR, RV_SDPVCID_VPI, g.buf, g.len))

#define ag_rp_236(PCB_POINTER, g) (rvSdpParserAuxSaveVcId(PCB_PTR, RV_SDPVCID_VCI, g.buf, g.len))

#define ag_rp_237(PCB_POINTER, g) (rvSdpParserAuxSaveVcId(PCB_PTR, RV_SDPVCID_VPCI, g.buf, g.len))

#define ag_rp_238(PCB_POINTER, g) (rvSdpParserAuxSaveVcId(PCB_PTR, RV_SDPVCID_NSAP, g.buf, g.len))

#define ag_rp_239(PCB_POINTER) (rvSdpParserAuxSaveVcId(PCB_PTR, RV_SDPVCID_NSAP, "$", 1))

#define ag_rp_240(PCB_POINTER, g) (rvSdpParserAuxSaveVcId(PCB_PTR, RV_SDPVCID_E164, g.buf, g.len))

#define ag_rp_241(PCB_POINTER) (rvSdpParserAuxSaveVcId(PCB_PTR, RV_SDPVCID_E164, "$", 1))

#define ag_rp_242(PCB_POINTER, g) (rvSdpParserAuxSaveVcId(PCB_PTR, RV_SDPVCID_GWID, g.buf, g.len))

#define ag_rp_243(PCB_POINTER) (rvSdpParserAuxSaveVcId(PCB_PTR, RV_SDPVCID_GWID, "$", 1))

#define ag_rp_244(PCB_POINTER, g) (rvSdpParserAuxSaveVcId(PCB_PTR, RV_SDPVCID_ALIAS, g.buf, g.len))

#define ag_rp_245(PCB_POINTER) (rvSdpParserAuxSaveVcId(PCB_PTR, RV_SDPVCID_ALIAS, "$", 1))


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

static const unsigned short ag_rpx[] = {
    0,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  1,
    1,  1,  0,  0,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13,  0,  0,
    0,  0,  0,  0, 14, 15, 16, 17,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0, 18, 19,  0, 20, 21, 22, 23, 24, 25, 26, 27,  0, 28, 29, 30, 31, 32,
    0,  0,  0,  1, 33, 34, 35, 36,  0, 37,  0, 38, 39, 40,  0, 41, 42, 43,
   44, 45,  0, 46, 47, 48, 49, 50, 51,  0, 52, 53,  0, 54,  0, 55, 56, 57,
   58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  1,  1,
    1,  1,  1,  1,  1,  0,  0,  1,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,
    0,  0,  0,  1, 76, 77, 78,  0,  0,  0,  0, 79,  0, 80,  0, 81,  0,  0,
    0,  0, 82, 83,  0,  0,  0,  0, 84, 85, 86,  0,  0,  0,  0,  0,  0, 87,
   88, 89, 90,  0, 91, 92, 93,  1,  0,  0,  0,  0,  1, 94,  0,  0,  0, 95,
   96, 97, 98, 99,  0,100,101,102,103,104,105,106,107,108,109,110,111,112,
  113,114,115,  0,  0,  0,  1,116,  0,  0,  1,117,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,118,  0,119,  0,120,  0,121,  0,122,  0,123,124,125,  0,
  126,127,128,129,130,131,132,133,134,  0,  0,  0,  0,  0,  0,  0,  1,  1,
  135,136,137,  0,138,139,  0,  0,140,  0,  0,  0,  1,  1,  1,  0,  0,  1,
    0,  0,  0,  0,  0,  1,  0,  0,  0,  1,  0,  1,141,  1,  1,  1,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,142,143,144,145,146,147,
  148,  0,  0,  0,149,150,151,152,153,154,155,  0,  0,  0,  1,156,  0,  0,
    1,157,158,159,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,160,
  161,162,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  1,  0,
    0,  0,  0,  0,  1,  1,  0,  0,  1,  0,  0,  1,  0,  1,  1,  1,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,163,164,165,166,167,168,169,170,
  171,172,173,174,175,176,177,  0,  0,  1,  1,  1,  0,  0,  1,  0,  0,  0,
    0,  0,  0,  1,  1,  0,  0,  1,  0,  0,  1,  1,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,
    1,  1
};

static const unsigned char ag_key_itt[] = {
 0
};

static const unsigned short ag_key_pt[] = {
0
};

static const unsigned char ag_key_ch[] = {
    0, 58, 77,255, 88,255, 65,255, 84,255, 78,255, 89,255, 83,255, 45,255,
   68,255, 65,255, 58, 77,255, 84,255, 78,255, 79,255, 66, 67, 82,255, 82,
  255, 76, 84,255, 52, 54,255, 78, 80,255, 65, 83,255, 69, 70, 84,255, 79,
   82,255, 68,255, 78,255, 69,255, 36, 37, 43, 45, 48, 58, 65, 69, 71, 73,
   78, 82, 83, 84,255, 48,255, 43,255, 34,255, 69, 84,255, 79, 82,255, 68,
  255, 78,255, 69,255, 82, 83,255, 65, 73, 84,255, 46, 64,255, 34, 92,255,
   64,255, 78,255, 91,255, 68, 72, 77, 83,255, 92, 93,255, 46,255, 37, 58,
  255, 58,255, 52, 54,255, 80,255, 73,255, 52, 54,255, 80,255, 65, 69, 71,
   73, 78,255, 82,255, 45,255, 93,255, 37, 43, 47, 63,255,126,255, 47, 63,
  255, 63,255, 37,255, 45,255, 83,255, 65,255, 73,255, 76,255, 45,255, 52,
  255, 54,255, 49,255, 45,255, 68,255, 73,255, 87,255, 45,255, 80,255, 65,
  255, 83,255, 67, 80,255, 65, 66, 69, 71, 78, 80, 86,255, 36, 45,255, 36,
   45, 58,255, 37, 43,255, 48,255, 67, 80,255, 86,255, 86,255, 86,255, 67,
   80,255, 86,255, 67,255, 49, 50, 53,255, 76,255, 65,255, 65, 72, 82,255,
   58,255, 69, 84,255, 65, 67, 73,255
};

static const unsigned char ag_key_act[] = {
  0,0,3,4,2,4,2,4,2,4,2,4,2,4,2,4,2,4,2,4,2,4,0,3,4,2,4,2,4,2,4,2,2,3,4,
  3,4,3,3,4,0,0,4,0,2,4,3,3,4,3,3,3,4,3,3,4,2,4,2,4,2,4,0,0,0,0,0,3,2,3,
  3,2,2,2,2,3,4,0,4,0,4,0,4,3,3,4,3,3,4,2,4,2,4,2,4,2,2,4,3,3,3,4,0,0,4,
  0,0,4,0,4,3,4,0,4,0,0,0,0,4,0,0,4,0,4,0,0,4,0,4,0,0,4,2,4,2,4,0,0,4,2,
  4,3,3,3,2,3,4,3,4,0,4,0,4,0,0,0,0,4,0,4,0,0,4,0,4,0,4,3,4,1,4,2,4,2,4,
  2,4,3,4,1,4,2,4,2,4,3,4,1,4,2,4,2,4,3,4,1,4,2,4,2,4,3,3,4,2,3,2,2,2,3,
  2,4,0,0,4,0,0,3,4,0,0,4,3,4,3,3,4,2,4,3,4,3,4,3,3,4,2,4,3,4,3,3,3,4,2,
  4,2,4,2,3,3,4,3,4,3,3,4,3,3,2,4
};

static const unsigned short ag_key_parm[] = {
    0,109,114,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,103,104,  0,  0,  0,  0,  0,  0,  0,  0,  0,106,  0,247,
    0,171,164,  0,174,176,  0,162,  0,  0,295,165,  0,261,178,247,  0,259,
  257,  0,  0,  0,  0,  0,  0,  0,183,416,409, 53,349,335,  0,167,169,  0,
    0,  0,  0,163,  0,349,  0,409,  0,394,  0,261,247,  0,259,257,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,164,162,163,  0,367,364,  0,394,392,  0,
  364,  0,295,  0,383,  0,354,355,356,357,  0,392,389,  0,367,  0,416,400,
    0,400,  0,174,176,  0,  0,  0,  0,  0,174,176,  0,  0,  0,171,167,169,
    0,165,  0,178,  0, 53,  0,389,  0,416,409,407,402,  0,236,  0,407,402,
    0,402,  0,416,  0,467,  0,171,  0,  0,  0,  0,  0,  0,  0,465,  0,167,
    0,  0,  0,  0,  0,466,  0,169,  0,  0,  0,  0,  0,464,  0,165,  0,  0,
    0,  0,  0,453,463,  0,  0,457,  0,  0,  0,458,  0,  0,183, 53,  0,183,
   53,335,  0,416,409,  0,468,  0,453,463,  0,  0,  0,462,  0,460,  0,453,
  460,  0,  0,  0,455,  0,485,487,488,  0,  0,  0,  0,  0,  0,490,489,  0,
  335,  0,494,492,  0,491,493,  0,  0
};

static const unsigned char ag_key_jmp[] = {
    0,  0,  0,  0,  1,  0,  4,  0,  6,  0,  8,  0, 10,  0, 12,  0, 14,  0,
   16,  0, 18,  0,  0,  2,  0, 22,  0, 25,  0, 27,  0, 20, 29,  4,  0, 12,
    0, 20, 24,  0,  0,  0,  0,  0, 40,  0, 34, 36,  0, 39, 46, 52,  0, 57,
   61,  0, 53,  0, 56,  0, 58,  0,  0,  0,  0,  0,  0, 18, 37, 26, 30, 43,
   46, 49, 60, 65,  0,  0,  0,  0,  0,  0,  0, 67, 74,  0, 79, 83,  0, 86,
    0, 89,  0, 91,  0, 83, 93,  0, 87, 90, 92,  0,  0,  0,  0,  0,  0,  0,
    0,  0, 94,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,129,  0,132,  0,  0,  0,  0,136,  0, 97,102,106,
  139,110,  0,114,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,121,  0,167,  0,169,  0,171,  0,173,  0,126,  0,177,
    0,179,  0,181,  0,128,  0,185,  0,187,  0,189,  0,130,  0,193,  0,195,
    0,197,  0,136,139,  0,175,123,183,191,199,132,201,  0,  0,  0,  0,  0,
    0,142,  0,  0,  0,  0,144,  0,146,149,  0,224,  0,152,  0,155,  0,158,
  161,  0,233,  0,163,  0,166,168,170,  0,240,  0,244,  0,246,172,178,  0,
  185,  0,197,201,  0,187,191,254,  0
};

static const unsigned short ag_key_index[] = {
   31,  0,  0,  0,  0, 35,  0,  0,  0,  0,  0,  0,  0, 62,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0, 77,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0, 77,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0, 79, 81,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 77,  0,  0, 95,  0,  0, 98,
   79,102,105,  0,102,102,108,  0,  0,  0,  0,  0,  0,  0,110,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 77,  0,  0, 95,  0,  0,
   98,  0,  0,  0,  0,102,  0, 81,  0, 81,102,102,  0,112, 81,  0,  0,  0,
    0,  0,  0,  0,  0,  0,110,  0,  0,  0,  0,  0,  0,  0,114,  0,114,  0,
    0,  0, 77, 77,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0, 79,  0,  0,  0,  0,102,119,122,  0,  0,124,127,  0,
    0,  0,  0,  0,  0,110,  0,  0,  0,  0,114,  0,  0,  0, 77, 77,  0,  0,
    0,  0,  0,  0,  0,  0,  0,134,  0,141,  0,147,  0,134,  0,  0,  0, 79,
  149,  0,119,151,112,122,  0,  0,  0,124,153,  0,  0,  0,  0,110,149,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,158,  0,  0,134,
  141,147,134,  0,  0,  0,  0,149,  0,  0,  0,  0,153,160,160,163,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,158,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,153,153,165,  0,  0,
    0,204,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,212,212,212,212,212,  0,165,212,212,  0,215,212,212,212,212,  0,219,
    0,  0,  0,149,149,149,149,149,149,149,149,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,212,212,212,212,
  212,165,212,212,  0,215,212,212,212,212,  0,165,  0,  0,  0,  0,  0,  0,
    0,222,222,222,222,227,229,231,236,238,248,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,165,  0,  0,  0,  0,  0,  0,  0,252,252,  0,  0,
   98,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,149,  0,149,  0,  0,  0,
  149,257,257,257,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,252,252,252,
    0,  0,  0,  0,  0, 98,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,229,238,222,238,222,229,229,238,222,  0,149,248,  0,  0,  0,  0,
  252,  0,252,  0,252,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,238,  0,238,238,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0
};

static const unsigned char ag_key_ends[] = {
58,0, 58,0, 69,80,65,82,83,69,58,0, 84,80,77,65,80,0, 58,0, 
73,65,83,0, 77,0, 49,54,52,0, 87,73,68,0, 83,0, 65,80,0, 
67,86,79,78,76,89,0, 67,50,53,52,51,0, 80,77,65,80,0, 78,76,89,0, 
69,67,86,0, 78,0, 67,86,79,78,76,89,0, 80,77,65,80,0, 78,76,89,0, 
69,67,86,0, 84,77,0, 78,0, 78,0, 65,83,0, 76,73,65,83,0, 
49,54,52,0, 87,73,68,0, 83,65,80,0, 70,67,50,53,52,51,0, 36,0, 
67,71,0, 36,0, 36,0, 36,0, 79,82,84,0, 67,73,0, 67,73,0, 58,0, 
88,0, 67,73,0, 67,73,0, 67,73,0, 80,73,0, 67,73,0, 73,0, 
73,68,0, 47,0, 47,0, 47,0, 51,50,51,67,45,0, 
84,80,47,65,86,80,0, 58,0, 84,77,70,0, 85,83,84,79,77,0, 
69,69,58,0, 85,0, 
};

#define AG_TCV(x) ag_tcv[(x)]

static const unsigned short ag_tcv[] = {
   59,495,495,495,495,495,495,495,495, 37, 31,495,495, 30,495,495,495,495,
  495,495,495,495,495,495,495,495,495,495,495,495,495,495, 36,496,497,498,
  161,499,500,501, 41, 43,502,436,503,158, 60, 39, 13, 11, 12, 14, 15, 17,
  504,504,504,504, 49,505, 45, 51, 47,506,507,239,200,155,508,149,339,509,
  509,139,509,229,509,281,509,129,153,509,111,134,110,144,123,509,440,509,
  223,510,511,510,498,512,498,239,200,155,508,149,339,509,509,139,509,229,
  509,281,509,129,153,509,111,134,110,144,123,509,440,509,223,498,498, 61,
  498,513,513,513,513,513,513,513,513,513,513,513,513,513,513,513,513,513,
  513,513,513,513,513,513,513,513,513,513,513,513,513,513,513,513,513,513,
  513,513,513,513,513,513,513,513,513,513,513,513,513,513,513,513,513,513,
  513,513,513,513,513,513,513,513,513,513,513,513,513,513,513,513,513,513,
  513,513,513,513,513,513,513,513,513,513,513,513,513,513,513,513,513,513,
  513,513,513,513,513,513,513,513,513,513,513,513,513,513,513,513,513,513,
  513,513,513,513,513,513,513,513,513,513,513,513,513,513,513,513,513,513,
  513,513,513,513
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
  int ag_k = 44 - ++(PCB).btsx;
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
    int ag_k = 44 - (PCB).btsx;
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
123,114,109,106,104,103,36,31,30,0,1,29,62,63,64,74,75,76,81,82,87,88,105,
  107,112,
31,0,
281,239,229,223,200,155,153,149,144,139,134,129,37,36,0,35,54,55,56,57,
281,239,229,223,200,155,153,149,144,139,134,129,111,110,37,36,0,35,54,55,56,
  57,
36,31,30,0,29,62,
509,508,440,339,281,247,239,229,200,155,153,149,144,139,134,129,111,110,61,
  60,59,31,30,0,66,67,68,69,89,90,91,92,93,94,95,96,97,98,99,100,101,102,
  115,127,147,151,207,211,
509,508,440,339,281,239,229,200,155,61,60,59,31,30,0,83,84,85,86,97,98,100,
  101,102,115,268,271,280,
509,508,440,339,281,239,229,200,155,61,60,59,37,36,31,30,0,35,54,55,56,57,
509,508,440,339,281,239,229,223,200,155,153,149,144,139,134,129,111,110,61,
  60,59,31,30,0,77,78,89,211,212,213,
509,508,440,339,281,239,229,223,200,155,153,149,144,139,134,129,111,110,61,
  60,59,31,30,0,77,78,89,211,212,213,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,31,
  30,0,66,67,68,69,91,92,93,94,95,96,97,98,99,100,101,102,115,127,147,151,
  207,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,31,
  30,0,66,67,68,69,91,92,93,94,95,96,97,98,99,100,101,102,115,127,147,151,
  207,
123,0,65,122,
37,36,0,35,55,
281,239,229,223,200,155,153,149,144,139,134,129,0,
281,239,229,223,200,155,153,149,144,139,134,129,111,110,0,
49,37,36,0,248,
61,60,59,31,30,0,29,58,
51,37,36,0,35,54,55,56,57,
31,30,0,32,33,34,
61,60,59,31,30,0,29,58,
51,37,36,0,204,
51,37,36,0,35,54,55,56,57,
51,37,36,0,240,
51,37,36,0,230,
51,37,36,0,201,
51,37,36,0,156,
51,37,36,0,35,54,55,56,57,152,
51,37,36,0,35,54,55,56,57,148,
51,37,36,0,145,
51,37,36,0,140,
51,37,36,0,135,
51,37,36,0,35,54,55,56,57,128,
509,508,440,339,239,229,200,155,153,149,144,139,134,129,110,0,66,67,91,92,
  93,94,95,96,97,98,99,100,101,102,115,127,147,151,207,
281,61,60,59,31,30,0,70,71,72,73,268,280,
281,0,
509,508,440,339,281,239,229,200,155,61,60,59,31,30,0,279,
509,508,440,339,281,239,229,200,155,61,60,59,31,30,0,278,
509,508,440,339,281,239,229,200,155,61,60,59,31,30,0,277,
509,508,440,339,281,239,229,200,155,61,60,59,31,30,0,276,
509,508,440,339,281,239,229,200,155,61,60,59,31,30,0,275,
509,508,440,339,281,239,229,200,155,61,60,59,31,30,0,83,84,97,98,100,101,
  102,115,268,271,280,
61,60,59,31,30,0,29,58,
509,508,440,339,281,239,229,200,155,61,60,59,31,30,0,83,84,85,86,97,98,100,
  101,102,115,268,271,280,
111,0,89,211,212,
509,508,440,339,281,239,229,223,200,155,153,149,144,139,134,129,110,61,60,
  59,31,30,0,79,80,
509,508,440,339,281,239,229,223,200,155,153,149,144,139,134,129,110,61,60,
  59,31,30,0,79,80,
281,61,60,59,31,30,0,70,71,72,73,268,280,
281,61,60,59,31,30,0,70,71,72,73,268,280,
123,0,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,31,
  30,0,66,67,68,69,91,92,93,94,95,96,97,98,99,100,101,102,115,127,147,151,
  207,
51,37,36,0,35,54,55,56,57,
51,37,36,0,35,54,55,56,57,
51,37,36,0,35,54,55,56,57,
51,37,36,0,35,54,55,56,57,
49,37,36,0,35,54,55,56,57,249,
37,36,31,30,0,35,54,55,56,57,
51,0,50,
31,0,34,
509,508,504,440,349,339,281,239,229,223,200,155,153,149,144,139,134,129,111,
  110,61,60,59,37,36,31,30,17,15,14,12,11,0,35,54,55,56,57,
51,37,36,0,35,54,55,56,57,
51,0,50,
51,37,36,0,35,54,55,56,57,
51,37,36,0,35,54,55,56,57,
51,37,36,0,35,54,55,56,57,
51,37,36,0,35,54,55,56,57,
51,0,50,
51,0,50,
51,37,36,0,35,54,55,56,57,
51,37,36,0,35,54,55,56,57,
51,37,36,0,35,54,55,56,57,
51,0,50,
509,508,440,339,281,239,229,200,155,139,61,60,59,31,30,0,93,270,
281,61,60,59,31,30,0,70,71,268,280,
61,60,59,31,30,0,29,58,
51,37,36,0,35,54,55,56,57,
61,60,59,31,30,0,29,58,
51,37,36,0,35,54,55,56,57,
31,30,0,32,33,34,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,31,
  30,0,66,67,68,69,91,92,93,94,95,96,97,98,99,100,101,102,115,127,147,151,
  207,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,31,
  30,0,66,67,68,69,91,92,93,94,95,96,97,98,99,100,101,102,115,127,147,151,
  207,
61,60,59,31,30,0,29,58,
61,60,59,31,30,0,29,58,
51,37,36,0,124,
281,61,60,59,31,30,0,70,71,72,73,268,280,
51,0,50,
51,0,50,
51,0,50,
51,0,50,
49,0,48,
31,30,0,29,
504,37,36,17,15,14,13,12,11,0,216,
51,0,50,
513,512,511,510,509,508,507,506,505,504,503,502,501,500,499,498,497,496,495,
  440,436,339,281,239,229,223,200,161,158,155,153,149,144,139,134,129,123,
  111,110,61,60,51,49,47,45,43,41,39,37,36,17,15,14,13,12,11,0,117,118,
51,0,50,
51,0,50,
51,0,50,
51,0,50,
512,510,509,508,507,506,505,504,502,501,500,498,497,440,436,409,339,281,239,
  229,223,200,161,158,155,153,149,144,139,134,129,123,111,110,61,60,51,49,
  39,37,36,17,15,14,13,12,11,0,35,54,55,56,57,154,
513,512,510,509,508,507,506,505,504,502,501,500,499,498,497,496,440,436,394,
  339,281,239,229,223,200,161,158,155,153,149,144,139,134,129,123,111,110,
  61,60,51,49,39,37,36,17,15,14,13,12,11,0,21,27,150,362,363,366,377,378,
51,0,50,
51,0,50,
51,0,50,
512,510,509,508,507,506,505,504,502,501,500,498,497,440,436,339,281,239,229,
  223,200,161,158,155,153,149,144,139,134,129,123,111,110,61,60,51,49,39,
  37,36,17,15,14,13,12,11,0,35,54,55,56,57,
509,508,440,339,281,239,229,200,155,61,60,59,31,30,0,269,
509,508,440,339,281,239,229,200,155,61,60,59,31,30,0,97,98,100,101,102,115,
  271,272,273,274,
51,0,50,
51,0,50,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,37,
  36,31,30,0,35,54,55,56,57,
281,61,60,59,31,30,0,70,71,72,73,268,280,
281,61,60,59,31,30,0,70,71,72,73,268,280,
51,37,36,0,35,54,55,56,57,
61,60,59,31,30,0,29,58,
513,512,511,510,509,508,507,506,505,504,503,502,501,500,499,498,497,496,495,
  440,436,339,281,239,229,223,200,161,158,155,153,149,144,139,134,129,123,
  111,110,61,60,51,49,47,45,43,41,39,37,36,31,30,17,15,14,13,12,11,0,2,3,
  7,32,33,34,113,
513,512,511,510,509,508,507,506,505,504,503,502,501,500,499,498,497,496,495,
  440,436,339,281,239,229,223,200,161,158,155,153,149,144,139,134,129,123,
  111,110,61,60,51,49,47,45,43,41,39,37,36,31,30,17,15,14,13,12,11,0,2,3,
  7,32,33,34,
513,512,511,510,509,508,507,506,505,504,503,502,501,500,499,498,497,496,495,
  440,436,339,281,239,229,223,200,161,158,155,153,149,144,139,134,129,123,
  111,110,61,60,51,49,47,45,43,41,39,37,36,31,30,17,15,14,13,12,11,0,2,3,
  7,32,33,34,
513,512,511,510,509,508,507,506,505,504,503,502,501,500,499,498,497,496,495,
  440,436,339,281,239,229,223,200,161,158,155,153,149,144,139,134,129,123,
  111,110,61,60,51,49,47,45,43,41,39,37,36,31,30,17,15,14,13,12,11,0,2,3,
  7,32,33,34,
504,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
504,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
504,349,37,36,17,15,14,12,11,0,35,54,55,56,57,
513,512,511,510,509,508,507,506,505,504,503,502,501,500,499,498,497,496,495,
  440,436,339,281,239,229,223,200,161,158,155,153,149,144,139,134,129,123,
  111,110,61,60,51,49,47,45,43,41,39,37,36,17,15,14,13,12,11,0,120,121,
31,30,0,32,33,34,
513,512,511,510,509,508,507,506,505,504,503,502,501,500,499,498,497,496,495,
  440,436,339,281,261,259,257,247,239,229,223,200,161,158,155,153,149,144,
  139,134,129,123,111,110,61,60,51,49,47,45,43,41,39,37,36,17,15,14,13,12,
  11,0,35,54,55,56,57,241,
512,509,508,504,440,339,281,239,229,223,200,155,153,149,144,139,134,129,123,
  111,110,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
509,508,504,440,436,339,281,239,229,223,200,158,155,153,149,144,139,134,129,
  123,111,110,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
512,509,508,504,440,339,281,239,229,223,200,164,163,162,161,158,155,153,149,
  144,139,134,129,123,111,110,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
512,510,509,508,507,506,505,504,502,501,500,498,497,440,436,409,339,281,239,
  229,223,200,161,158,155,153,149,144,139,134,129,123,111,110,61,60,51,49,
  39,17,15,14,13,12,11,0,5,419,
513,512,509,508,506,504,502,501,500,499,498,496,440,436,367,364,339,281,239,
  229,223,200,161,158,155,153,149,144,139,134,129,123,111,110,61,51,47,41,
  39,37,36,31,30,17,15,14,13,12,11,0,380,381,382,
513,512,510,509,508,507,506,505,504,503,502,501,500,499,498,496,495,440,436,
  394,392,339,281,239,229,223,200,161,158,155,153,149,144,139,134,129,123,
  111,110,61,60,51,49,47,45,43,41,39,37,36,17,15,14,13,12,11,0,385,395,
  396,398,
512,510,509,508,507,506,505,504,502,501,500,498,497,440,436,339,281,239,229,
  223,200,161,158,155,153,149,144,139,134,129,123,111,110,61,60,51,49,45,
  43,39,37,36,31,30,17,15,14,13,12,11,0,24,25,26,
367,364,0,368,369,370,
513,512,510,509,508,507,506,505,504,502,501,500,499,498,497,496,440,436,367,
  364,339,281,239,229,223,200,161,158,155,153,149,144,139,134,129,123,111,
  110,61,60,51,49,45,39,37,36,17,15,14,13,12,11,0,
364,0,
45,0,44,
41,31,30,0,32,33,34,40,
509,508,440,339,281,239,229,223,200,155,153,149,144,139,134,129,123,111,110,
  37,36,0,35,54,55,56,57,
513,512,511,510,509,508,507,506,505,504,503,502,501,500,499,498,497,496,495,
  440,436,339,281,239,229,223,200,161,158,155,153,149,144,139,134,129,123,
  111,110,61,60,51,49,47,45,43,41,39,37,36,31,30,17,15,14,13,12,11,0,2,3,
  7,32,33,34,141,
513,512,511,510,509,508,507,506,505,504,503,502,501,500,499,498,497,496,495,
  440,436,339,281,239,229,223,200,161,158,155,153,149,144,139,134,129,123,
  111,110,61,60,51,49,47,45,43,41,39,37,36,31,30,17,15,14,13,12,11,0,2,3,
  7,32,33,34,136,
512,510,509,508,507,506,505,504,502,501,500,498,497,440,436,339,281,239,229,
  223,200,161,158,155,153,149,144,139,134,129,123,111,110,61,60,51,49,39,
  17,15,14,13,12,11,0,130,361,
509,508,440,339,239,229,200,155,0,97,98,100,101,102,115,271,272,
512,509,508,504,440,339,295,281,239,229,223,200,155,153,149,144,139,134,129,
  123,111,110,39,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
504,37,36,17,15,14,12,11,0,35,54,55,56,57,224,
61,60,59,31,30,0,29,58,
61,60,59,31,30,0,29,58,
51,0,50,
513,512,511,510,509,508,507,506,505,504,503,502,501,500,499,498,497,496,495,
  440,436,339,281,239,229,223,200,161,158,155,153,149,144,139,134,129,123,
  111,110,61,60,51,49,47,45,43,41,39,37,36,17,15,14,13,12,11,0,
509,508,440,339,281,239,229,200,155,61,60,59,37,36,31,30,0,35,54,55,56,57,
31,30,0,32,33,34,
509,508,440,339,281,239,229,223,200,155,153,149,144,139,134,129,111,110,61,
  60,59,37,36,31,30,0,35,54,55,56,57,
31,30,0,32,33,34,
509,508,440,339,281,239,229,223,200,155,153,149,144,139,134,129,111,110,61,
  60,59,37,36,31,30,0,35,54,55,56,57,
31,30,0,32,33,34,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,37,
  36,31,30,0,35,54,55,56,57,
31,30,0,32,33,34,
504,17,15,14,13,12,11,0,19,250,
504,17,15,14,13,12,11,0,19,217,222,352,
504,349,17,15,14,12,11,0,205,206,208,214,228,
513,512,511,510,509,508,507,506,505,504,503,502,501,500,499,498,497,496,495,
  440,436,339,281,239,229,223,200,161,158,155,153,149,144,139,134,129,123,
  111,110,61,60,51,49,47,45,43,41,39,37,36,17,15,14,13,12,11,0,120,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,37,
  36,31,30,0,35,54,55,56,57,
513,512,511,510,509,508,507,506,505,504,503,502,501,500,499,498,497,496,495,
  440,436,339,281,261,259,257,247,239,229,223,200,161,158,155,153,149,144,
  139,134,129,123,111,110,61,60,51,49,47,45,43,41,39,17,15,14,13,12,11,0,
  90,242,243,
512,509,508,504,440,339,281,239,229,223,200,155,153,149,144,139,134,129,123,
  111,110,17,15,14,13,12,11,0,195,196,231,233,
509,508,504,440,436,339,281,239,229,223,200,158,155,153,149,144,139,134,129,
  123,111,110,17,15,14,13,12,11,0,202,359,360,
512,509,508,504,440,339,281,239,229,223,200,164,163,162,161,158,155,153,149,
  144,139,134,129,123,111,110,17,15,14,13,12,11,0,133,182,195,196,
512,510,509,508,507,506,505,504,502,501,500,498,497,440,436,339,281,239,229,
  223,200,161,158,155,153,149,144,139,134,129,123,111,110,61,60,51,49,39,
  37,36,17,15,14,13,12,11,0,21,27,
45,0,44,
504,36,17,15,14,12,11,0,420,421,
41,31,30,0,32,33,34,40,
513,512,509,508,506,504,502,501,500,499,498,496,440,436,339,281,239,229,223,
  200,161,158,155,153,149,144,139,134,129,123,111,110,61,51,39,37,36,17,
  15,14,13,12,11,0,380,
513,512,511,510,509,508,507,506,505,504,503,502,501,500,499,498,497,496,495,
  440,436,339,281,239,229,223,200,161,158,155,153,149,144,139,134,129,123,
  111,110,61,60,51,49,47,45,43,41,39,37,36,31,30,17,15,14,13,12,11,0,
394,0,
512,510,509,508,507,506,505,504,502,501,500,498,497,440,436,339,281,239,229,
  223,200,161,158,155,153,149,144,139,134,129,123,111,110,61,60,51,49,39,
  37,36,17,15,14,13,12,11,0,24,
513,512,509,508,506,504,502,501,500,499,498,496,440,436,394,339,281,239,229,
  223,200,161,158,155,153,149,144,139,134,129,123,111,110,61,51,39,37,36,
  17,15,14,13,12,11,0,27,366,377,378,
367,0,368,
513,512,509,508,506,504,502,501,500,499,498,496,440,436,367,364,339,281,239,
  229,223,200,161,158,155,153,149,144,139,134,129,123,111,110,61,51,47,41,
  39,37,36,31,30,17,15,14,13,12,11,0,380,381,382,
512,510,509,508,507,506,505,504,502,501,500,498,497,440,436,339,281,239,229,
  223,200,161,158,155,153,149,144,139,134,129,123,111,110,61,60,51,49,45,
  43,39,37,36,31,30,17,15,14,13,12,11,0,24,25,26,
513,512,509,508,506,504,502,501,500,499,498,496,440,436,383,339,281,239,229,
  223,200,161,158,155,153,149,144,139,134,129,123,111,110,61,51,39,37,36,
  17,15,14,13,12,11,0,27,365,371,375,376,377,
513,512,509,508,506,504,502,501,500,499,498,496,440,436,394,339,281,239,229,
  223,200,161,158,155,153,149,144,139,134,129,123,111,110,61,51,39,37,36,
  17,15,14,13,12,11,0,27,362,363,366,377,378,
512,510,509,508,507,506,505,504,502,501,500,498,497,440,436,339,281,239,229,
  223,200,161,158,155,153,149,144,139,134,129,123,111,110,61,60,51,49,39,
  37,36,17,15,14,13,12,11,0,21,27,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,37,
  36,31,30,0,35,54,55,56,57,
509,508,440,339,281,239,229,223,200,155,153,149,144,139,134,129,123,111,110,
  0,146,399,405,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,37,
  36,31,30,0,143,
31,30,0,32,33,34,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,37,
  36,31,30,0,138,
31,30,0,32,33,34,
512,510,509,508,507,506,505,504,502,501,500,498,497,440,436,339,281,239,229,
  223,200,161,158,155,153,149,144,139,134,129,123,111,110,61,60,51,49,39,
  17,15,14,13,12,11,0,
37,36,0,35,
512,509,508,504,440,339,295,281,239,229,223,200,155,153,149,144,139,134,129,
  123,111,110,39,17,15,14,13,12,11,0,282,
504,17,15,14,12,11,0,228,
37,36,31,30,0,35,225,226,227,
504,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
509,508,440,339,281,239,229,200,155,61,60,59,37,36,31,30,0,35,54,55,56,57,
509,508,440,339,281,239,229,223,200,155,153,149,144,139,134,129,111,110,61,
  60,59,37,36,31,30,0,35,54,55,56,57,
509,508,440,339,281,239,229,223,200,155,153,149,144,139,134,129,111,110,61,
  60,59,37,36,31,30,0,35,54,55,56,57,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,37,
  36,31,30,0,35,54,55,56,57,
504,17,15,14,13,12,11,0,20,
37,36,0,35,
357,356,355,354,0,353,
37,36,0,35,55,56,
504,17,15,14,13,12,11,0,350,
37,36,0,35,55,56,
509,508,504,440,349,339,281,239,229,223,200,155,153,149,144,139,134,129,111,
  110,61,60,59,37,36,31,30,17,15,14,12,11,0,35,55,56,57,
509,508,504,440,349,339,281,239,229,223,200,155,153,149,144,139,134,129,110,
  61,60,59,31,30,17,15,14,12,11,0,79,80,205,208,214,228,
513,512,511,510,509,508,507,506,505,504,503,502,501,500,499,498,497,496,495,
  440,436,339,281,239,229,223,200,161,158,155,153,149,144,139,134,129,123,
  111,110,61,60,51,47,45,43,41,39,37,36,17,15,14,13,12,11,0,311,314,
49,31,30,0,32,33,34,48,
512,510,509,508,507,506,505,504,502,501,500,498,497,440,436,339,281,239,229,
  223,200,161,158,155,153,149,144,139,134,129,123,111,110,61,60,51,49,39,
  37,36,31,30,17,15,14,13,12,11,0,35,54,55,56,57,
512,510,509,508,507,506,505,504,502,501,500,498,497,440,436,339,281,239,229,
  223,200,161,158,155,153,149,144,139,134,129,123,111,110,61,60,51,49,39,
  37,36,31,30,17,15,14,13,12,11,0,35,54,55,56,57,
512,510,509,508,507,506,505,504,502,501,500,498,497,440,436,339,281,239,229,
  223,200,161,158,155,153,149,144,139,134,129,123,111,110,61,60,51,49,39,
  37,36,31,30,17,15,14,13,12,11,0,35,54,55,56,57,
512,509,508,504,440,339,281,239,229,223,200,155,153,149,144,139,134,129,123,
  111,110,17,15,14,13,12,11,0,195,
49,37,36,31,30,0,35,54,55,56,57,
31,30,0,32,33,34,
509,508,504,440,436,339,281,239,229,223,200,158,155,153,149,144,139,134,129,
  123,111,110,17,15,14,13,12,11,0,359,
49,37,36,0,35,54,55,56,57,
512,509,508,504,440,339,281,239,229,223,200,155,153,149,144,139,134,129,123,
  111,110,17,15,14,13,12,11,0,195,
37,36,0,35,
512,509,508,504,440,339,281,239,229,223,200,155,153,149,144,139,134,129,123,
  111,110,37,36,17,15,14,13,12,11,0,35,195,196,
512,509,508,504,440,339,281,239,229,223,200,155,153,149,144,139,134,129,123,
  111,110,37,36,17,15,14,13,12,11,0,35,195,196,
512,509,508,504,440,339,281,239,229,223,200,155,153,149,144,139,134,129,123,
  111,110,37,36,17,15,14,13,12,11,0,35,195,196,
37,36,0,35,
37,36,0,35,
37,36,31,30,0,35,54,55,56,57,
512,510,509,508,507,506,505,504,502,501,500,498,497,440,436,339,281,239,229,
  223,200,161,158,155,153,149,144,139,134,129,123,111,110,61,60,51,49,39,
  37,36,17,15,14,13,12,11,0,
409,37,36,0,35,54,55,56,57,
36,0,
504,17,15,14,12,11,0,
512,510,509,508,507,506,505,504,502,501,500,498,497,440,436,339,281,239,229,
  223,200,161,158,155,153,149,144,139,134,129,123,111,110,61,60,51,49,39,
  37,36,17,15,14,13,12,11,0,21,27,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,37,
  36,31,30,0,35,54,55,56,57,
513,512,509,508,506,504,502,501,500,499,498,496,440,436,339,281,239,229,223,
  200,161,158,155,153,149,144,139,134,129,123,111,110,61,51,39,37,36,17,
  15,14,13,12,11,0,
513,512,509,508,507,506,505,504,503,502,501,500,499,498,497,496,495,440,436,
  392,389,339,281,239,229,223,200,161,158,155,153,149,144,139,134,129,123,
  111,110,61,60,51,49,47,45,43,41,39,37,36,17,15,14,13,12,11,0,384,385,
  386,387,388,391,
367,47,41,31,30,0,372,373,374,
47,0,46,
43,0,42,
512,509,508,507,504,503,502,501,500,497,496,440,416,400,339,281,239,229,223,
  200,161,158,155,153,149,144,139,134,129,123,111,110,60,43,41,17,15,14,
  13,12,11,0,192,193,413,415,
400,0,
37,36,31,30,0,35,54,55,56,57,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,37,
  36,31,30,0,35,54,55,56,57,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,37,
  36,31,30,0,142,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,37,
  36,31,30,0,35,54,55,56,57,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,37,
  36,31,30,0,137,
508,504,339,239,200,158,155,149,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
512,509,508,504,440,339,295,281,239,229,223,200,155,153,149,144,139,134,129,
  123,111,110,39,17,15,14,13,12,11,0,283,
37,36,0,35,55,56,
504,37,36,17,15,14,12,11,0,35,54,55,56,57,224,
37,36,0,35,225,
504,17,15,14,13,12,11,0,19,125,
504,17,15,14,13,12,11,0,
513,512,511,510,509,508,507,506,505,504,503,502,501,500,499,498,497,496,495,
  440,436,339,281,239,229,223,200,161,158,155,153,149,144,139,134,129,123,
  111,110,61,60,51,49,47,45,43,41,37,36,17,15,14,13,12,11,0,251,264,265,
504,37,36,17,15,14,13,12,11,0,19,35,55,218,222,352,
504,17,15,14,13,12,11,0,
504,349,37,36,17,15,14,12,11,0,35,55,215,228,
509,508,504,440,349,339,281,239,229,223,200,155,153,149,144,139,134,129,111,
  110,61,60,59,31,30,17,15,14,12,11,0,209,210,
513,512,511,510,509,508,507,506,505,504,503,502,501,500,499,498,497,496,495,
  440,436,339,281,239,229,223,200,161,158,155,153,149,144,139,134,129,123,
  111,110,61,60,51,47,45,43,41,39,37,36,17,15,14,13,12,11,0,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,37,
  36,31,30,0,246,
513,512,511,510,509,508,507,506,505,504,503,502,501,500,499,498,497,496,495,
  440,436,339,281,239,229,223,200,161,158,155,153,149,144,139,134,129,123,
  111,110,61,60,51,49,47,45,43,41,39,37,36,17,15,14,13,12,11,0,35,54,55,
  56,57,
512,510,509,508,507,506,505,504,502,501,500,498,497,440,436,339,281,239,229,
  223,200,161,158,155,153,149,144,139,134,129,123,111,110,61,60,51,49,39,
  31,30,17,15,14,13,12,11,0,4,5,32,33,34,
512,510,509,508,507,506,505,504,502,501,500,498,497,440,436,339,281,239,229,
  223,200,161,158,155,153,149,144,139,134,129,123,111,110,61,60,51,49,39,
  31,30,17,15,14,13,12,11,0,4,5,32,33,34,
512,510,509,508,507,506,505,504,502,501,500,498,497,440,436,339,281,239,229,
  223,200,161,158,155,153,149,144,139,134,129,123,111,110,61,60,51,49,39,
  31,30,17,15,14,13,12,11,0,4,5,32,33,34,
49,0,48,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,37,
  36,31,30,0,232,
49,0,48,
512,509,508,504,440,339,281,239,229,223,200,176,174,155,153,149,144,139,134,
  129,123,111,110,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
512,509,508,504,440,339,281,239,229,223,200,155,153,149,144,139,134,129,123,
  111,110,17,15,14,13,12,11,0,195,
512,509,508,504,440,339,281,239,229,223,200,176,174,171,169,167,165,161,158,
  155,153,149,144,139,134,129,123,111,110,37,36,17,15,14,13,12,11,0,35,54,
  55,56,57,
512,509,508,504,440,339,281,239,229,223,200,155,153,149,144,139,134,129,123,
  111,110,17,15,14,13,12,11,0,195,
440,178,161,158,37,36,0,35,54,55,56,57,
512,509,508,504,440,339,281,239,229,223,200,155,153,149,144,139,134,129,123,
  111,110,17,15,14,13,12,11,0,195,
512,509,508,504,440,339,281,239,229,223,200,176,174,161,158,155,153,149,144,
  139,134,129,123,111,110,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
161,158,37,36,0,35,54,55,56,57,
161,158,37,36,0,35,54,55,56,57,
31,30,0,32,33,34,
409,0,419,
504,53,47,41,36,31,30,17,15,14,13,12,11,0,422,423,424,
43,0,42,
513,512,509,508,507,506,505,504,503,502,501,500,499,498,497,496,495,440,436,
  392,339,281,239,229,223,200,161,158,155,153,149,144,139,134,129,123,111,
  110,61,60,51,49,47,45,43,41,39,37,36,17,15,14,13,12,11,0,384,385,386,
  391,
389,0,
513,512,509,508,506,504,502,501,500,499,498,496,440,436,383,339,281,239,229,
  223,200,161,158,155,153,149,144,139,134,129,123,111,110,61,51,39,37,36,
  17,15,14,13,12,11,0,27,371,375,376,377,
367,0,372,
31,30,0,32,33,34,
31,30,0,32,33,34,
508,504,339,239,200,155,149,17,15,14,13,12,11,0,
512,509,508,507,504,503,502,501,500,497,496,440,416,339,281,239,229,223,200,
  161,158,155,153,149,144,139,134,129,123,111,110,60,43,41,17,15,14,13,12,
  11,0,192,413,
512,509,508,507,504,503,502,501,500,497,496,440,416,409,407,402,339,281,239,
  229,223,200,161,158,155,153,149,144,139,134,129,123,111,110,60,43,41,37,
  36,31,30,17,15,14,13,12,11,0,192,401,406,408,413,417,418,
31,30,0,32,33,34,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,37,
  36,31,30,0,35,54,55,56,57,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,37,
  36,31,30,0,35,54,55,56,57,
508,504,339,239,200,158,155,149,17,15,14,13,12,11,0,131,315,
512,509,508,504,440,339,295,281,239,229,223,200,155,153,149,144,139,134,129,
  123,111,110,39,17,15,14,13,12,11,0,284,285,288,290,301,302,
504,53,37,36,17,15,14,13,12,11,0,19,35,52,55,222,352,
37,36,31,30,0,35,54,55,56,57,
513,512,511,510,509,508,507,506,505,504,503,502,501,500,499,498,497,496,495,
  440,436,339,281,239,229,223,200,161,158,155,153,149,144,139,134,129,123,
  111,110,61,60,51,49,47,45,43,41,37,36,17,15,14,13,12,11,0,264,
39,31,30,0,32,33,34,38,
37,36,0,35,55,56,220,221,
504,17,15,14,13,12,11,0,
37,36,31,30,0,35,54,55,56,57,
111,0,77,89,211,212,213,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,37,
  36,31,30,0,35,54,55,56,57,
513,512,511,510,509,508,507,506,505,504,503,502,501,500,499,498,497,496,495,
  440,436,339,281,239,229,223,200,161,158,155,153,149,144,139,134,129,123,
  111,110,61,60,51,49,47,45,43,41,39,17,15,14,13,12,11,0,244,
31,30,0,32,33,34,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,37,
  36,31,30,0,262,
31,30,0,32,33,34,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,37,
  36,31,30,0,260,
31,30,0,32,33,34,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,37,
  36,31,30,0,258,
512,510,509,508,507,506,505,504,502,501,500,498,497,440,436,339,281,239,236,
  229,223,200,161,158,155,153,149,144,139,134,129,123,111,110,61,60,51,49,
  39,37,36,17,15,14,13,12,11,0,234,237,238,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,37,
  36,31,30,0,35,54,55,56,57,
504,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
512,509,508,504,440,339,281,239,229,223,200,176,174,155,153,149,144,139,134,
  129,123,111,110,17,15,14,13,12,11,0,172,195,196,
512,509,508,504,440,339,281,239,229,223,200,176,174,171,169,167,165,161,158,
  155,153,149,144,139,134,129,123,111,110,17,15,14,13,12,11,0,159,172,195,
  196,
440,178,161,158,0,159,180,191,
512,509,508,504,440,339,281,239,229,223,200,176,174,161,158,155,153,149,144,
  139,134,129,123,111,110,17,15,14,13,12,11,0,159,172,195,196,
161,158,0,159,
161,158,0,159,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,37,
  36,31,30,0,157,
47,0,46,
504,53,36,17,15,14,13,12,11,0,422,
37,36,31,30,0,35,54,55,56,57,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,37,
  36,31,30,0,35,54,55,56,57,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,37,
  36,31,30,0,35,54,55,56,57,
508,504,339,239,200,155,149,17,15,14,13,12,11,0,
512,509,508,507,504,503,502,501,500,497,496,440,416,409,339,281,239,229,223,
  200,161,158,155,153,149,144,139,134,129,123,111,110,60,43,41,17,15,14,
  13,12,11,0,192,413,417,
407,0,
407,0,
402,37,36,31,30,0,404,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,37,
  36,31,30,0,35,54,55,56,57,
508,504,339,239,200,155,149,17,15,14,13,12,11,0,316,318,
37,36,0,35,
512,509,508,504,440,339,281,239,229,223,200,155,153,149,144,139,134,129,123,
  111,110,39,17,15,14,13,12,11,0,301,
39,0,38,
37,36,0,35,55,56,
31,30,0,32,33,34,
37,36,0,35,55,56,286,298,299,
504,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
31,30,0,32,33,34,
504,17,15,14,13,12,11,0,19,253,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,37,
  36,31,30,0,252,
504,37,36,17,15,14,13,12,11,0,19,35,55,219,222,352,
37,36,0,35,55,56,220,
504,17,15,14,13,12,11,0,
31,30,0,32,33,34,
513,512,511,510,509,508,507,506,505,504,503,502,501,500,499,498,497,496,495,
  440,436,339,281,239,229,223,200,161,158,155,153,149,144,139,134,129,123,
  111,110,61,60,51,49,47,45,43,41,39,37,36,31,30,17,15,14,13,12,11,0,3,7,
  312,
31,30,0,32,33,34,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,37,
  36,31,30,0,35,54,55,56,57,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,37,
  36,31,30,0,35,54,55,56,57,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,37,
  36,31,30,0,35,54,55,56,57,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,37,
  36,31,30,0,35,54,55,56,57,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,37,
  36,31,30,0,35,54,55,56,57,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,37,
  36,31,30,0,35,54,55,56,57,
512,510,509,508,507,506,505,504,502,501,500,498,497,440,436,339,281,239,236,
  229,223,200,161,158,155,153,149,144,139,134,129,123,111,110,61,60,51,49,
  39,37,36,17,15,14,13,12,11,0,237,
504,17,15,14,13,12,11,0,19,203,
512,509,508,504,440,339,281,239,229,223,200,155,153,149,144,139,134,129,123,
  111,110,17,15,14,13,12,11,0,195,
37,36,0,35,
512,509,508,504,440,339,281,239,229,223,200,155,153,149,144,139,134,129,123,
  111,110,37,36,17,15,14,13,12,11,0,35,195,196,
512,509,508,504,440,339,281,239,229,223,200,155,153,149,144,139,134,129,123,
  111,110,37,36,17,15,14,13,12,11,0,35,195,196,
512,509,508,504,440,339,281,239,229,223,200,155,153,149,144,139,134,129,123,
  111,110,17,15,14,13,12,11,0,195,196,
512,509,508,504,440,339,281,239,229,223,200,155,153,149,144,139,134,129,123,
  111,110,17,15,14,13,12,11,0,195,196,
37,36,0,35,
37,36,0,35,
37,36,0,35,
37,36,0,35,
37,36,0,35,
37,36,0,35,
512,509,508,504,502,500,499,498,496,440,436,339,281,239,229,223,200,161,158,
  155,153,149,144,139,134,129,123,111,110,61,60,37,36,17,15,14,13,12,11,0,
  442,443,444,
37,36,0,35,
37,36,0,35,
37,36,0,35,
37,36,0,35,
512,509,508,504,440,339,281,239,229,223,200,155,153,149,144,139,134,129,123,
  111,110,37,36,17,15,14,13,12,11,0,35,195,196,
512,509,508,504,440,339,281,239,229,223,200,155,153,149,144,139,134,129,123,
  111,110,37,36,17,15,14,13,12,11,0,35,195,196,
37,36,0,35,
37,36,0,35,
37,36,0,35,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,37,
  36,31,30,0,35,54,55,56,57,
37,36,31,30,0,35,54,55,56,57,
31,30,0,32,33,34,
512,509,508,507,504,503,502,501,500,497,496,440,416,409,407,402,339,281,239,
  229,223,200,161,158,155,153,149,144,139,134,129,123,111,110,60,43,41,37,
  36,31,30,17,15,14,13,12,11,0,192,401,406,408,413,417,418,
512,509,508,507,504,503,502,501,500,497,496,440,416,409,407,402,339,281,239,
  229,223,200,161,158,155,153,149,144,139,134,129,123,111,110,60,43,41,37,
  36,31,30,17,15,14,13,12,11,0,192,401,406,408,413,417,418,
512,509,508,507,504,503,502,501,500,497,496,440,416,339,281,239,229,223,200,
  161,158,155,153,149,144,139,134,129,123,111,110,60,43,41,17,15,14,13,12,
  11,0,192,193,403,413,
508,504,339,239,200,155,149,17,15,14,13,12,11,0,
504,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
512,509,508,504,440,339,281,239,229,223,200,155,153,149,144,139,134,129,123,
  111,110,17,15,14,13,12,11,0,195,196,296,
504,467,466,465,464,463,458,457,453,171,169,167,165,161,158,37,36,17,15,14,
  13,12,11,0,19,35,55,291,294,303,445,447,448,451,452,
509,508,440,339,281,239,229,200,155,139,61,60,59,37,36,31,30,0,289,
509,508,504,440,339,281,239,229,223,200,158,155,153,149,144,139,134,129,123,
  111,110,39,37,36,17,15,14,13,12,11,0,35,55,297,305,
37,36,31,30,0,35,55,56,57,298,
31,30,0,32,33,34,
504,17,15,14,13,12,11,0,19,222,352,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,37,
  36,31,30,0,35,54,55,56,57,
39,37,36,31,30,0,35,38,54,55,56,57,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,37,
  36,31,30,0,35,54,55,56,57,
504,17,15,14,13,12,11,0,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,37,
  36,31,30,0,245,
37,36,31,30,0,35,54,55,56,57,
512,509,508,504,440,339,281,239,229,223,200,155,153,149,144,139,134,129,123,
  111,110,60,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
512,509,508,504,440,339,281,239,229,223,200,155,153,149,144,139,134,129,123,
  111,110,17,15,14,13,12,11,0,195,
512,509,508,504,440,339,281,239,229,223,200,155,153,149,144,139,134,129,123,
  111,110,60,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
512,509,508,504,440,339,281,239,229,223,200,155,153,149,144,139,134,129,123,
  111,110,17,15,14,13,12,11,0,195,
512,509,508,504,440,339,281,239,229,223,200,155,153,149,144,139,134,129,123,
  111,110,60,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
512,509,508,504,440,339,281,239,229,223,200,155,153,149,144,139,134,129,123,
  111,110,60,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
512,509,508,504,440,339,281,239,229,223,200,183,158,155,153,149,144,139,134,
  129,123,111,110,60,53,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
512,509,508,504,440,339,281,239,229,223,200,183,158,155,153,149,144,139,134,
  129,123,111,110,60,53,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
504,183,53,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
508,504,339,239,200,183,155,149,53,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
508,504,339,239,200,183,155,149,60,53,37,36,17,15,14,13,12,11,0,35,54,55,56,
  57,
512,509,508,504,502,500,499,498,496,440,436,339,281,239,229,223,200,161,158,
  155,153,149,144,139,134,129,123,111,110,61,60,17,15,14,13,12,11,0,442,
512,509,508,507,504,503,502,501,500,497,496,440,416,339,281,239,229,223,200,
  161,158,155,153,149,144,139,134,129,123,111,110,60,43,41,37,36,17,15,14,
  13,12,11,0,35,54,55,56,57,
504,436,183,53,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
508,504,339,239,200,183,155,149,60,53,37,36,17,15,14,13,12,11,0,35,54,55,56,
  57,
512,509,508,504,440,339,281,239,229,223,200,155,153,149,144,139,134,129,123,
  111,110,60,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
508,504,339,335,239,200,183,155,149,53,37,36,17,15,14,13,12,11,0,35,54,55,
  56,57,
509,508,504,440,339,281,239,229,223,200,183,158,155,153,149,144,139,134,129,
  123,111,110,60,53,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
508,504,339,239,200,183,155,149,60,53,37,36,17,15,14,13,12,11,0,35,54,55,56,
  57,
508,504,339,239,200,183,155,149,60,53,37,36,17,15,14,13,12,11,0,35,54,55,56,
  57,
508,504,339,239,200,183,155,149,60,53,37,36,17,15,14,13,12,11,0,35,54,55,56,
  57,
31,30,0,32,33,34,
512,509,508,507,504,503,502,501,500,497,496,440,416,409,339,281,239,229,223,
  200,161,158,155,153,149,144,139,134,129,123,111,110,60,43,41,37,36,31,
  30,17,15,14,13,12,11,0,192,410,413,
504,17,15,14,13,12,11,0,20,132,319,
512,509,508,504,440,339,281,239,229,223,200,155,153,149,144,139,134,129,123,
  111,110,17,15,14,13,12,11,0,195,
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
509,508,440,339,281,239,229,200,155,139,61,60,59,37,36,31,30,0,35,54,55,56,
  57,
509,508,504,440,339,281,239,229,223,200,158,155,153,149,144,139,134,129,123,
  111,110,39,17,15,14,13,12,11,0,
509,508,504,440,339,281,239,229,223,200,158,155,153,149,144,139,134,129,123,
  111,110,39,37,36,17,15,14,13,12,11,0,35,55,297,305,
509,508,440,339,281,239,229,200,155,139,61,60,59,37,36,31,30,0,287,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,31,
  30,0,126,
509,508,504,440,339,281,239,229,223,200,155,153,149,144,139,134,129,123,111,
  110,17,15,14,13,12,11,0,255,267,
31,30,0,32,33,34,
504,17,15,14,13,12,11,0,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,37,
  36,31,30,0,35,54,55,56,57,
31,30,0,32,33,34,
512,509,508,504,440,339,281,239,229,223,200,155,153,149,144,139,134,129,123,
  111,110,60,17,15,14,13,12,11,0,173,198,199,
512,509,508,504,440,339,281,239,229,223,200,155,153,149,144,139,134,129,123,
  111,110,60,17,15,14,13,12,11,0,173,198,199,
512,509,508,504,440,339,281,239,229,223,200,155,153,149,144,139,134,129,123,
  111,110,60,17,15,14,13,12,11,0,173,198,199,
512,509,508,504,440,339,281,239,229,223,200,155,153,149,144,139,134,129,123,
  111,110,60,17,15,14,13,12,11,0,173,198,199,
512,509,508,504,440,339,281,239,229,223,200,183,158,155,153,149,144,139,134,
  129,123,111,110,60,53,17,15,14,13,12,11,0,170,186,428,429,
512,509,508,504,440,339,281,239,229,223,200,183,158,155,153,149,144,139,134,
  129,123,111,110,60,53,17,15,14,13,12,11,0,170,186,428,429,
504,183,53,17,15,14,13,12,11,0,20,168,185,
508,504,339,239,200,183,155,149,53,17,15,14,13,12,11,0,166,184,332,
508,504,339,239,200,183,155,149,60,53,17,15,14,13,12,11,0,160,187,430,431,
512,509,508,507,504,503,502,501,500,497,496,440,416,339,281,239,229,223,200,
  161,158,155,153,149,144,139,134,129,123,111,110,60,43,41,17,15,14,13,12,
  11,0,181,192,193,413,
504,436,183,53,17,15,14,13,12,11,0,179,190,432,433,
508,504,339,239,200,183,155,149,60,53,17,15,14,13,12,11,0,160,187,430,431,
512,509,508,504,440,339,281,239,229,223,200,155,153,149,144,139,134,129,123,
  111,110,60,17,15,14,13,12,11,0,173,198,199,
508,504,339,335,239,200,183,155,149,53,17,15,14,13,12,11,0,177,189,323,324,
  325,338,340,343,
509,508,504,440,339,281,239,229,223,200,183,158,155,153,149,144,139,134,129,
  123,111,110,60,53,17,15,14,13,12,11,0,175,188,320,321,425,426,
508,504,339,239,200,183,155,149,60,53,17,15,14,13,12,11,0,160,187,430,431,
508,504,339,239,200,183,155,149,60,53,17,15,14,13,12,11,0,160,187,430,431,
508,504,339,239,200,183,155,149,60,53,17,15,14,13,12,11,0,160,187,430,431,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,37,
  36,31,30,0,35,54,55,56,57,
512,509,508,507,504,503,502,501,500,497,496,440,416,339,281,239,229,223,200,
  161,158,155,153,149,144,139,134,129,123,111,110,60,43,41,17,15,14,13,12,
  11,0,192,193,403,413,
504,17,15,14,13,12,11,0,
37,36,0,35,
504,161,158,37,36,17,15,14,13,12,11,0,19,35,55,291,
512,509,508,504,440,339,281,239,229,223,200,158,155,153,149,144,139,134,129,
  123,111,110,60,17,15,14,13,12,11,0,186,428,429,
512,509,508,504,440,339,281,239,229,223,200,158,155,153,149,144,139,134,129,
  123,111,110,60,17,15,14,13,12,11,0,186,428,429,
504,17,15,14,13,12,11,0,20,185,
508,504,339,239,200,155,149,17,15,14,13,12,11,0,184,332,
504,468,161,17,15,14,13,12,11,0,454,
504,468,161,17,15,14,13,12,11,0,459,
504,468,161,17,15,14,13,12,11,0,8,456,
504,468,161,17,15,14,13,12,11,0,454,
463,453,0,445,451,
462,0,450,
460,0,449,
460,453,0,445,449,
455,0,446,
512,509,508,504,490,489,488,487,485,440,339,281,239,229,223,200,158,155,153,
  149,144,139,134,129,123,111,110,39,37,36,17,15,14,13,12,11,0,35,55,293,
  307,308,309,
504,17,15,14,13,12,11,0,19,292,
509,508,440,339,281,239,229,200,155,139,61,60,59,37,36,31,30,0,35,54,55,56,
  57,
509,508,504,440,339,281,239,229,223,200,155,153,149,144,139,134,129,123,111,
  110,17,15,14,13,12,11,0,
37,36,31,30,0,35,54,55,56,57,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,37,
  36,31,30,0,254,
504,17,15,14,13,12,11,0,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,37,
  36,31,30,0,35,54,55,56,57,
512,509,508,504,440,339,281,239,229,223,200,155,153,149,144,139,134,129,123,
  111,110,60,17,15,14,13,12,11,0,198,
512,509,508,504,440,339,281,239,229,223,200,158,155,153,149,144,139,134,129,
  123,111,110,60,17,15,14,13,12,11,0,428,
504,17,15,14,13,12,11,0,
508,504,339,239,200,155,149,17,15,14,13,12,11,0,
60,0,
508,504,339,239,200,155,149,60,17,15,14,13,12,11,0,430,
512,509,508,507,504,503,502,501,500,497,496,440,416,339,281,239,229,223,200,
  161,158,155,153,149,144,139,134,129,123,111,110,60,43,41,17,15,14,13,12,
  11,0,192,413,
504,158,37,36,31,30,17,15,14,13,12,11,0,437,438,439,
504,17,15,14,12,11,0,
508,339,239,200,155,149,0,
508,504,339,239,200,155,149,17,15,14,13,12,11,0,
508,504,339,239,200,155,149,17,15,14,13,12,11,0,332,
508,339,239,200,155,149,0,
508,504,339,239,200,155,149,60,37,36,31,30,17,15,14,13,12,11,0,327,328,332,
  337,
335,49,0,334,344,
335,49,0,334,
509,508,504,440,339,281,239,229,223,200,158,155,153,149,144,139,134,129,123,
  111,110,60,17,15,14,13,12,11,0,425,
39,0,38,322,
512,509,508,504,440,339,281,239,229,223,200,164,163,162,161,158,155,153,149,
  144,139,134,129,123,111,110,37,36,17,15,14,13,12,11,0,35,54,55,56,57,
39,37,36,31,30,0,35,38,55,56,57,
504,39,37,36,17,15,14,13,12,11,0,475,
508,504,339,239,200,155,149,17,15,14,13,12,11,0,
504,39,17,15,14,13,12,11,0,484,
508,504,339,239,200,155,149,17,15,14,13,12,11,0,
504,17,15,14,13,12,11,0,
504,17,15,14,13,12,11,0,16,
504,17,15,14,13,12,11,0,
508,504,339,239,200,155,149,17,15,14,13,12,11,0,
39,0,38,
39,0,38,
53,0,52,
39,0,38,
53,0,52,
39,0,38,
39,0,38,
39,0,38,
53,0,52,
512,510,509,508,507,506,505,504,502,501,500,498,497,494,493,492,491,440,436,
  339,281,239,229,223,200,161,158,155,153,149,144,139,134,129,123,111,110,
  61,60,51,49,39,17,15,14,13,12,11,0,361,486,
512,510,509,508,507,506,505,504,502,501,500,498,497,494,493,492,491,440,436,
  339,281,239,229,223,200,161,158,155,153,149,144,139,134,129,123,111,110,
  61,60,51,49,39,17,15,14,13,12,11,0,361,486,
512,510,509,508,507,506,505,504,502,501,500,498,497,494,493,492,491,440,436,
  339,281,239,229,223,200,161,158,155,153,149,144,139,134,129,123,111,110,
  61,60,51,49,39,17,15,14,13,12,11,0,361,486,
512,509,508,504,440,339,281,239,229,223,200,158,155,153,149,144,139,134,129,
  123,111,110,39,17,15,14,13,12,11,0,307,
37,36,0,35,55,56,
31,30,0,32,33,34,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,37,
  36,31,30,0,35,54,55,56,57,
504,17,15,14,13,12,11,0,
508,504,339,239,200,155,149,17,15,14,13,12,11,0,332,427,
504,17,15,14,13,12,11,0,
504,158,17,15,14,13,12,11,0,437,
504,17,15,14,13,12,11,0,433,
508,504,339,239,200,155,149,17,15,14,13,12,11,0,332,
508,504,339,239,200,155,149,17,15,14,13,12,11,0,332,
508,504,339,239,200,155,149,17,15,14,13,12,11,0,
508,504,339,335,239,200,155,149,60,49,37,36,31,30,17,15,14,13,12,11,0,332,
  333,
335,60,49,37,36,31,30,0,329,330,331,
60,37,36,31,30,0,326,345,
508,504,339,239,200,155,149,60,37,36,31,30,17,15,14,13,12,11,0,327,328,332,
  337,
508,504,339,239,200,155,149,17,15,14,13,12,11,0,327,328,332,
60,37,36,31,30,0,326,345,
504,17,15,14,13,12,11,0,8,346,
512,509,508,504,440,339,281,239,229,223,200,164,163,162,161,158,155,153,149,
  144,139,134,129,123,111,110,17,15,14,13,12,11,0,133,182,195,196,
504,17,15,14,13,12,11,0,19,292,
504,39,37,36,17,15,14,13,12,11,0,473,
508,504,339,239,200,155,149,39,37,36,17,15,14,13,12,11,0,474,
504,39,17,15,14,13,12,11,0,483,
508,504,339,239,200,155,149,39,17,15,14,13,12,11,0,479,
504,17,15,14,13,12,11,0,
17,15,14,13,12,11,0,18,
504,60,39,37,36,31,30,17,15,14,13,12,11,0,
504,60,39,37,36,31,30,17,15,14,13,12,11,0,
504,60,39,37,36,31,30,17,15,14,13,12,11,0,
504,60,39,37,36,31,30,17,15,14,13,12,11,0,
504,60,39,37,36,31,30,17,15,14,13,12,11,0,
504,17,15,14,13,12,11,0,
508,504,339,239,200,155,149,39,37,36,17,15,14,13,12,11,0,469,
462,0,450,
455,0,446,
504,468,161,17,15,14,13,12,11,0,454,
455,0,446,
504,468,161,17,15,14,13,12,11,0,461,
462,0,450,
462,0,450,
455,0,446,
504,468,161,17,15,14,13,12,11,0,8,456,
512,510,509,508,507,506,505,504,502,501,500,498,497,440,436,339,281,239,229,
  223,200,161,158,155,153,149,144,139,134,129,123,111,110,61,60,51,49,39,
  17,15,14,13,12,11,0,
53,0,
512,509,508,504,490,489,488,487,485,440,339,281,239,229,223,200,158,155,153,
  149,144,139,134,129,123,111,110,39,37,36,17,15,14,13,12,11,0,35,55,293,
  307,308,309,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,37,
  36,31,30,0,256,
504,17,15,14,13,12,11,0,
508,504,339,239,200,155,149,17,15,14,13,12,11,0,
60,0,
508,504,339,239,200,155,149,17,15,14,13,12,11,0,
508,504,339,239,200,155,149,17,15,14,13,12,11,0,328,332,
49,0,329,
504,17,15,14,13,12,11,0,8,
335,60,37,36,31,30,0,336,
39,37,36,31,30,0,38,348,
37,36,31,30,0,35,54,55,56,57,
37,36,31,30,0,35,55,56,57,
504,39,37,36,17,15,14,13,12,11,0,472,
508,504,339,239,200,155,149,39,37,36,17,15,14,13,12,11,0,470,
504,39,17,15,14,13,12,11,0,482,
508,504,339,239,200,155,149,39,17,15,14,13,12,11,0,478,
39,0,38,
504,39,17,15,14,13,12,11,0,473,
508,504,339,239,200,155,149,17,15,14,13,12,11,0,
39,0,38,
39,0,38,
508,504,339,239,200,155,149,17,15,14,13,12,11,0,318,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,37,
  36,31,30,0,35,54,55,56,57,
504,37,36,31,30,17,15,14,13,12,11,0,20,351,
508,504,339,239,200,155,149,17,15,14,13,12,11,0,
508,504,339,239,200,155,149,17,15,14,13,12,11,0,332,427,
60,0,
508,504,339,239,200,155,149,17,15,14,13,12,11,0,327,328,332,
504,17,15,14,13,12,11,0,19,347,
31,30,0,32,33,34,
504,39,37,36,17,15,14,13,12,11,0,471,
508,504,339,239,200,155,149,39,37,36,17,15,14,13,12,11,0,469,
504,39,17,15,14,13,12,11,0,481,
508,504,339,239,200,155,149,39,17,15,14,13,12,11,0,477,
455,0,446,
508,504,339,239,200,155,149,39,17,15,14,13,12,11,0,470,
455,0,446,
455,0,446,
508,504,339,239,200,155,149,17,15,14,13,12,11,0,
504,17,15,14,13,12,11,0,
60,0,
504,17,15,14,13,12,11,0,8,
509,508,440,339,281,239,229,200,155,153,149,144,139,134,129,110,61,60,59,37,
  36,31,30,0,35,54,55,56,57,
504,39,17,15,14,13,12,11,0,480,
508,504,339,239,200,155,149,39,17,15,14,13,12,11,0,476,
508,504,339,239,200,155,149,17,15,14,13,12,11,0,332,427,
60,0,
504,39,17,15,14,13,12,11,0,475,
508,504,339,239,200,155,149,39,17,15,14,13,12,11,0,474,
60,0,
504,17,15,14,13,12,11,0,8,
508,504,339,239,200,155,149,17,15,14,13,12,11,0,332,427,
60,0,
508,504,339,239,200,155,149,17,15,14,13,12,11,0,332,427,
60,0,
508,504,339,239,200,155,149,17,15,14,13,12,11,0,332,427,
60,0,
508,504,339,239,200,155,149,17,15,14,13,12,11,0,332,427,
60,0,
508,504,339,239,200,155,149,17,15,14,13,12,11,0,332,427,
60,0,
508,504,339,239,200,155,149,17,15,14,13,12,11,0,332,427,
60,0,
508,504,339,239,200,155,149,17,15,14,13,12,11,0,332,

};


static unsigned const char ag_astt[12063] = {
  8,2,2,2,2,2,1,1,1,7,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,7,5,5,5,5,5,5,5,5,5,5,
  5,5,2,2,7,1,1,1,1,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,7,1,1,1,1,1,9,9,1,5,3,
  3,2,2,2,2,8,1,1,1,1,1,2,2,1,1,1,2,1,1,5,5,5,5,5,7,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,4,1,1,1,1,8,8,8,8,8,7,1,1,1,1,1,1,1,1,1,1,
  1,1,1,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,7,1,1,1,1,1,5,5,5,5,5,5,5,8,5,5,5,5,
  5,5,5,5,1,5,5,5,5,5,5,7,1,1,1,1,1,1,5,5,5,5,5,5,5,8,5,5,5,5,5,5,5,5,1,5,5,
  5,5,5,5,7,1,1,1,1,1,1,2,2,2,2,8,1,1,1,1,2,2,1,1,1,2,1,5,5,5,5,5,7,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,8,1,1,1,1,2,2,1,1,1,2,1,5,5,5,5,
  5,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,7,1,1,2,2,5,3,3,1,1,1,1,1,
  1,1,1,1,1,1,1,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,4,4,4,7,1,2,1,2,2,1,7,2,3,5,
  2,2,7,1,1,1,1,1,2,1,7,1,1,2,2,1,2,2,1,7,2,3,4,4,4,7,1,5,2,2,7,1,1,1,1,1,4,
  4,4,7,1,4,4,4,7,1,4,4,4,7,1,4,4,4,7,1,5,2,2,7,1,1,1,1,1,3,5,2,2,7,1,1,1,1,
  1,3,4,4,4,7,1,4,4,4,7,1,4,4,4,7,1,5,2,2,7,1,1,1,1,1,3,2,2,2,2,1,1,1,1,2,2,
  1,1,1,2,1,5,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,3,4,8,8,8,8,8,7,1,1,1,1,1,
  1,1,7,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,3,4,4,
  4,4,4,4,4,4,4,4,4,4,4,4,7,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,3,4,4,4,4,4,4,4,
  4,4,4,4,4,4,4,7,3,2,2,2,2,4,1,1,1,1,5,5,5,5,5,7,3,3,1,1,1,1,1,1,3,3,1,2,1,
  2,2,1,7,2,3,2,2,2,2,4,1,1,1,1,8,8,8,8,8,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5,3,
  1,3,8,8,8,8,5,8,8,1,8,8,8,8,8,8,8,8,8,5,5,5,5,5,7,1,1,8,8,8,8,5,8,8,1,8,8,
  8,8,8,8,8,8,8,5,5,5,5,5,7,1,1,4,8,8,8,8,8,7,1,1,1,1,1,1,4,8,8,8,8,8,7,1,1,
  1,1,1,1,1,7,2,2,2,2,8,1,1,1,1,2,2,1,1,1,2,1,5,5,5,5,5,7,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,5,2,2,7,1,1,1,1,1,5,2,2,7,1,1,1,1,1,5,2,2,7,1,1,1,
  1,1,5,2,2,7,1,1,1,1,1,5,2,2,7,1,1,1,1,1,3,2,2,5,5,7,1,1,1,1,1,2,7,1,2,7,2,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,5,5,5,5,5,7,1,2,1,1,
  2,5,2,2,7,1,1,1,1,1,2,7,1,5,2,2,7,1,1,1,1,1,5,2,2,7,1,1,1,1,1,5,2,2,7,1,1,
  1,1,1,5,2,2,7,1,1,1,1,1,2,7,1,2,7,1,5,2,2,7,1,1,1,1,1,5,2,2,7,1,1,1,1,1,5,
  2,2,7,1,1,1,1,1,2,7,1,8,8,8,8,5,8,8,8,8,1,5,5,5,5,5,7,1,1,4,5,5,5,5,5,7,3,
  3,1,1,2,1,2,2,1,7,2,3,5,2,2,7,1,1,1,1,1,2,1,2,2,1,7,2,3,5,2,2,7,1,1,1,1,1,
  2,1,7,1,1,2,2,2,2,2,8,1,1,1,1,2,2,1,1,1,2,1,5,5,5,5,5,7,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,8,1,1,1,1,2,2,1,1,1,2,1,5,5,5,5,5,7,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,2,2,1,7,2,3,2,1,2,2,1,7,2,3,4,4,4,
  7,1,4,8,8,8,8,8,7,1,1,1,1,1,1,2,7,1,2,7,1,2,7,1,2,7,1,2,7,1,2,1,7,2,4,4,4,
  4,4,4,4,4,4,7,1,2,7,1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,1,1,2,7,1,2,
  7,1,2,7,1,2,7,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,7,1,1,2,1,1,1,1,1,2,7,1,2,7,1,2,7,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,4,4,4,
  4,4,4,4,4,4,4,4,4,4,4,7,3,2,2,2,2,5,1,1,1,1,5,5,5,5,5,7,1,1,1,1,1,1,1,1,1,
  3,2,7,1,2,7,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,7,1,3,1,1,3,4,
  8,8,8,8,8,7,1,1,1,1,1,1,4,8,8,8,8,8,7,1,1,1,1,1,1,5,2,2,7,1,1,1,1,1,2,1,2,
  2,1,7,2,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,7,1,2,1,1,1,2,3,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,7,1,2,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,2,1,1,1,1,1,1,1,7,1,2,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,
  7,1,2,1,1,1,2,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,
  5,5,2,2,5,5,5,5,5,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,1,
  2,1,7,1,1,2,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,3,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,5,5,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5,5,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,5,5,1,1,1,5,5,1,1,1,1,1,1,7,1,1,3,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,8,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,5,5,1,1,1,5,5,1,1,1,1,1,1,7,1,1,2,1,5,7,1,1,3,1,
  9,1,9,9,1,9,1,9,9,9,9,1,9,1,1,9,9,5,5,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  9,1,9,1,4,9,9,9,9,9,9,9,9,9,7,1,7,2,7,1,2,2,1,7,1,1,2,1,5,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,2,2,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,
  1,1,7,1,2,1,1,1,2,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,7,1,2,1,1,1,
  2,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,7,1,1,2,2,2,2,1,1,1,1,5,1,1,1,1,1,1,3,3,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,5,2,2,5,5,5,5,5,
  7,1,1,1,1,1,1,2,1,2,2,1,7,2,3,2,1,2,2,1,7,2,3,2,7,1,9,9,9,9,9,9,9,9,9,9,9,
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  9,9,9,9,9,9,9,9,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,7,1,2,1,1,2,2,1,7,1,1,2,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,7,1,2,1,1,2,2,1,7,1,1,2,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,7,1,2,1,1,2,2,1,7,1,1,2,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,7,1,2,1,1,2,2,1,7,1,1,2,1,1,
  1,1,2,1,1,7,2,1,1,1,1,1,2,1,1,7,2,1,2,1,1,2,1,1,1,1,1,7,1,1,1,1,2,9,9,9,9,
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,4,3,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,
  2,5,5,7,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
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
  7,1,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,7,1,2,1,1,2,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,1,1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
  4,4,4,4,7,1,2,1,7,1,1,2,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,1,
  2,1,7,1,1,2,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  9,9,9,9,9,9,9,9,9,9,9,9,9,4,2,2,7,1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
  4,4,4,4,4,4,4,4,4,4,7,1,1,1,1,1,1,1,7,1,2,2,5,5,7,1,1,1,3,5,2,2,5,5,5,5,5,
  5,7,1,1,1,1,1,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,7,1,2,1,1,2,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,7,1,2,1,1,2,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,2,2,5,5,7,1,2,1,1,2,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,
  2,5,5,7,1,2,1,1,2,1,1,1,1,1,1,1,5,1,2,2,7,1,2,2,2,2,4,2,2,2,7,1,1,1,1,1,1,
  1,1,1,1,7,2,2,2,7,1,1,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,
  5,5,5,5,5,5,5,7,1,1,1,1,5,5,1,5,2,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,
  1,1,1,1,7,1,3,3,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,2,1,2,2,1,7,1,
  1,2,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  5,5,5,5,2,2,5,5,5,5,5,5,5,5,7,1,1,1,1,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,5,5,5,5,5,5,7,1,1,1,1,1,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  5,2,2,5,5,5,5,5,5,5,5,7,1,1,1,1,1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  9,9,9,9,9,9,9,4,3,5,2,2,4,4,7,1,1,1,1,1,2,1,7,1,1,2,9,9,9,9,9,9,9,9,9,9,9,
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,4,3,5,2,2,7,1,1,1,1,1,9,9,9,9,9,9,9,9,9,
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,4,3,2,2,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,2,2,1,1,1,1,1,1,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  2,2,1,1,1,1,1,1,7,1,1,1,2,2,7,1,2,2,7,1,2,2,5,5,7,1,1,1,1,1,9,1,9,9,1,9,1,
  9,9,9,9,9,1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,1,9,1,9,9,9,9,9,9,9,
  9,9,4,5,2,2,7,1,1,1,1,1,9,5,1,1,1,1,1,1,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,1,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,7,1,2,1,1,2,1,9,9,9,9,9,9,9,9,1,9,1,
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,5,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,8,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,1,1,1,1,1,1,5,5,5,5,7,1,1,3,2,7,1,2,7,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,7,1,1,1,3,1,7,2,2,5,5,7,1,1,1,1,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  5,5,2,2,5,5,7,1,2,1,1,2,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,1,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,7,1,2,1,1,2,4,4,4,4,4,4,4,4,
  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,1,5,5,5,5,5,5,5,5,2,2,5,5,5,5,5,5,7,1,1,1,
  1,1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,1,2,2,7,1,
  1,1,5,2,2,5,5,5,5,5,7,1,1,1,1,1,3,2,2,5,1,3,1,1,1,1,2,1,1,7,2,1,9,9,9,9,9,
  9,9,5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,1,1,1,2,2,1,1,1,2,1,1,7,2,3,
  3,1,2,1,1,1,1,1,1,1,1,7,1,2,2,2,1,1,1,1,1,7,3,3,1,2,4,4,4,4,4,4,4,4,4,4,4,
  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,1,3,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  9,9,9,5,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,1,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  5,5,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,7,1,2,1,1,2,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,
  1,1,1,1,7,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,7,1,2,1,1,2,2,7,1,4,4,4,4,4,4,4,4,4,
  4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,1,2,7,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  5,5,5,5,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  9,9,9,9,9,9,9,9,9,4,3,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  5,5,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  9,9,9,9,9,9,9,4,3,5,5,5,5,2,2,7,1,1,1,1,1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  9,9,9,9,9,9,9,9,9,9,9,4,3,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,5,5,2,2,7,1,1,1,1,1,5,5,2,2,7,1,1,1,1,1,2,1,
  7,1,1,2,1,7,1,1,1,5,5,1,5,5,1,1,1,1,1,1,7,1,1,2,2,7,1,9,9,9,9,9,9,9,9,9,9,
  9,9,9,9,9,9,9,9,9,1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  9,9,9,9,9,9,9,9,5,3,3,3,3,3,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,3,3,3,3,1,5,3,2,1,7,1,1,2,
  2,1,7,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,7,9,9,9,9,9,9,9,9,9,9,9,9,1,9,9,9,9,
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,5,3,3,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,8,5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5,5,5,5,1,1,1,1,1,1,7,
  1,1,1,1,1,1,1,2,1,7,1,1,2,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,7,
  1,2,1,1,2,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,7,1,2,1,1,2,8,8,8,
  8,8,1,8,8,8,8,8,8,8,8,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,7,3,1,1,1,1,1,1,2,2,2,1,1,1,2,1,1,7,2,3,1,3,2,1,2,2,5,5,7,1,1,
  1,1,1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,4,3,2,2,1,7,1,1,2,1,2,2,7,1,1,1,
  1,1,1,1,1,1,1,1,1,7,2,2,5,5,7,1,1,1,1,1,1,7,3,1,1,1,1,5,5,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,2,2,5,5,7,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,
  1,2,1,7,1,1,2,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,1,2,1,7,1,1,
  2,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,1,2,1,7,1,1,2,4,4,4,4,4,
  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,2,1,1,5,5,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,7,1,3,1,1,3,5,2,2,5,5,5,5,5,5,7,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,
  1,1,1,1,1,2,2,7,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,7,1,1,1,1,2,2,7,1,2,2,7,1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
  4,4,4,4,7,1,2,7,1,9,9,9,9,9,9,9,9,9,5,3,2,2,5,5,7,1,1,1,1,1,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,7,1,2,1,1,2,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  5,5,5,5,2,2,5,5,7,1,2,1,1,2,3,3,3,3,3,3,3,3,3,3,3,3,3,7,9,9,9,9,9,9,9,9,9,
  9,9,9,1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,5,3,3,3,1,
  5,1,5,1,5,5,5,5,7,2,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,7,1,2,1,
  1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,7,2,1,2,2,7,1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  9,9,9,9,9,9,9,9,9,9,9,9,9,4,3,2,7,1,2,2,7,1,1,1,2,1,7,1,1,2,2,2,7,1,1,1,1,
  1,1,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,2,1,7,1,1,2,1,1,1,1,2,1,1,7,2,1,4,4,4,4,
  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,1,1,2,2,1,1,1,2,1,1,7,2,3,3,3,2,1,
  2,2,5,1,1,1,3,1,1,1,1,1,1,1,7,2,1,7,2,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5,5,1,
  1,1,1,1,1,7,2,1,2,2,1,7,1,1,2,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,
  5,7,1,2,1,1,2,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,7,1,2,1,1,2,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,7,1,2,1,1,2,5,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,2,2,5,5,7,1,2,1,1,2,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  5,5,2,2,5,5,7,1,2,1,1,2,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,7,1,
  2,1,1,2,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,4,3,1,1,1,1,2,1,1,7,2,1,9,9,9,9,9,9,9,9,9,9,9,
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,4,3,2,2,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,2,2,1,1,1,1,1,1,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,2,2,1,1,1,1,1,1,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,1,
  2,2,7,1,2,2,7,1,2,2,7,1,2,2,7,1,2,2,7,1,2,2,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5,5,1,1,1,1,1,1,7,1,1,3,2,2,7,1,2,2,7,
  1,2,2,7,1,2,2,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,
  1,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,7,1,1,
  1,2,2,7,1,2,2,7,1,2,2,7,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,7,
  1,2,1,1,2,2,2,5,5,7,1,1,1,1,1,2,1,7,2,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,8,5,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5,5,5,5,1,1,1,1,1,1,7,1,3,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,8,5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,5,5,5,5,1,1,1,1,1,1,7,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,1,3,1,9,9,9,9,9,9,9,9,9,
  9,9,9,9,5,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,7,1,1,1,1,2,2,2,2,1,1,1,1,1,1,1,1,2,2,2,2,1,1,1,2,1,1,
  7,2,3,3,1,1,2,1,1,1,1,1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,7,3,3,3,1,2,2,5,5,7,1,1,1,
  3,3,2,1,7,1,1,2,1,1,1,1,2,1,1,7,2,2,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  5,2,2,5,5,7,1,1,1,1,1,2,2,2,5,5,7,1,1,1,1,1,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  5,5,5,5,5,2,2,5,5,7,1,2,1,1,2,1,1,1,1,1,1,1,7,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
  4,4,4,4,4,4,4,4,4,7,1,2,2,5,5,7,1,1,1,1,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  9,9,9,9,9,9,9,9,9,9,4,3,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,
  5,5,5,5,5,7,1,1,1,1,1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  9,4,3,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,5,5,5,5,7,1,1,1,
  1,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,5,5,5,5,7,1,1,1,1,
  1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,5,5,5,5,7,1,1,
  1,1,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,5,5,5,5,7,
  1,1,1,1,1,5,5,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,5,5,5,5,5,5,5,5,5,2,2,5,5,5,5,
  5,5,7,1,1,1,1,1,5,5,5,5,5,5,5,5,5,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,9,9,9,9,9,
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,5,3,5,5,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,5,5,
  5,5,7,1,1,1,1,1,5,5,5,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,5,5,5,5,5,5,5,5,5,5,2,
  2,5,5,5,5,5,5,7,1,1,1,1,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,
  5,5,5,5,5,5,7,1,1,1,1,1,5,5,5,5,5,5,5,5,5,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,
  5,5,5,5,5,5,5,5,5,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,5,5,5,5,5,5,5,5,5,5,2,2,5,
  5,5,5,5,5,7,1,1,1,1,1,5,5,5,5,5,5,5,5,5,5,2,2,5,5,5,5,5,5,7,1,1,1,1,1,2,1,
  7,1,1,2,9,9,9,9,9,9,9,9,9,9,9,9,1,1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  9,9,5,5,5,5,9,9,9,9,9,9,7,3,3,3,1,1,1,1,1,1,1,7,1,1,2,9,9,9,9,9,9,9,9,9,9,
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,4,3,2,2,4,1,1,1,2,7,1,2,7,1,2,7,1,2,7,1,
  2,7,1,2,7,1,2,7,1,2,7,1,2,7,1,2,7,1,2,7,1,2,7,1,2,5,1,2,2,7,1,1,1,2,5,1,5,
  5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,7,1,2,1,1,2,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  9,9,9,9,9,9,9,9,9,9,9,9,9,4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,
  2,1,1,1,1,1,1,5,3,3,3,1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,1,4,4,4,4,4,4,
  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,7,1,1,2,1,7,1,1,2,1,1,1,1,1,1,1,7,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  5,5,5,5,5,2,2,5,5,7,1,2,1,1,2,2,1,7,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,7,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,7,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,7,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,2,1,
  1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,7,2,2,1,1,
  1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,7,2,2,1,1,1,
  2,2,1,1,1,1,1,1,7,1,2,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,7,2,2,1,1,1,1,1,1,2,
  1,1,1,2,1,1,1,1,1,1,7,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,2,1,1,1,1,1,2,2,1,1,1,1,1,1,7,2,2,2,
  2,1,1,1,1,1,2,1,1,1,2,1,1,1,1,1,1,7,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,7,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,7,2,2,2,
  2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,7,2,
  2,2,1,1,1,1,1,1,1,1,2,1,1,1,2,1,1,1,1,1,1,7,2,2,1,1,1,1,1,1,1,2,1,1,1,2,1,
  1,1,1,1,1,7,2,2,1,1,1,1,1,1,1,2,1,1,1,2,1,1,1,1,1,1,7,2,2,1,1,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,7,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,1,3,1,9,9,9,9,9,9,
  9,5,2,2,7,1,1,2,2,2,2,1,1,1,2,1,1,7,2,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,7,2,1,1,1,1,1,1,1,1,1,7,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,
  7,2,1,1,1,2,1,1,1,1,1,1,7,2,1,1,2,1,1,1,1,1,1,7,2,1,1,2,1,1,1,2,1,1,7,2,2,
  1,1,2,1,1,1,1,1,1,7,2,1,1,7,1,1,1,7,1,1,7,1,1,1,7,1,1,1,7,3,1,1,1,1,2,2,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,7,3,3,2,1,1,2,1,
  1,1,1,2,1,1,7,2,1,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,7,1,2,1,1,2,9,9,9,9,9,
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,4,2,2,5,5,7,1,1,1,1,1,4,4,4,4,4,
  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,1,1,1,1,1,1,1,1,7,5,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,2,2,5,5,7,1,2,1,1,2,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  9,9,9,9,9,9,9,9,9,9,9,4,3,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  9,9,9,9,9,4,3,9,9,9,9,9,9,9,4,3,3,3,3,3,3,3,3,3,3,3,3,3,7,1,7,9,9,9,9,9,9,
  9,9,9,9,9,9,9,9,4,3,9,9,9,9,9,9,9,9,9,9,9,9,1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  9,9,9,9,9,9,9,9,9,9,9,9,9,4,3,3,1,1,5,5,5,5,1,1,1,1,1,1,7,1,1,3,1,1,1,1,1,
  1,7,3,3,3,3,3,3,7,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,1,1,1,1,1,1,1,1,1,1,1,1,7,
  3,3,1,3,3,3,3,7,1,1,1,1,1,1,1,8,5,5,5,5,1,1,1,1,1,1,7,1,1,1,1,1,1,7,1,2,1,
  1,7,3,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,4,3,2,4,1,2,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,5,5,5,5,7,1,1,
  1,1,1,2,2,2,5,5,7,1,1,1,1,2,1,5,5,5,1,1,1,1,1,1,7,2,1,1,1,1,1,1,1,1,1,1,1,
  1,1,7,1,5,1,1,1,1,1,1,7,2,1,1,1,1,1,1,1,1,1,1,1,1,1,7,3,3,3,3,3,3,3,5,3,1,
  1,1,1,1,1,5,1,1,1,1,1,1,1,1,5,1,1,1,1,1,1,1,1,1,1,1,1,1,7,2,7,1,2,5,1,2,7,
  1,2,5,1,2,7,1,2,7,1,2,7,1,2,5,1,2,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,2,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,7,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,2,9,9,9,9,9,9,9,9,9,9,9,9,9,
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,4,3,2,2,7,1,1,1,2,1,7,1,1,2,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,5,5,2,2,5,5,7,1,2,1,1,2,1,1,1,1,1,1,1,7,1,1,1,1,1,1,1,
  1,1,1,1,1,1,7,1,1,3,3,3,3,3,3,3,7,9,1,9,9,9,9,9,9,5,3,1,1,1,1,1,1,1,7,3,1,
  1,1,1,1,1,1,1,1,1,1,1,1,7,3,1,1,1,1,1,1,1,1,1,1,1,1,1,7,3,3,3,3,3,3,3,3,3,
  3,3,3,3,3,5,1,1,1,5,1,1,1,1,5,5,5,5,5,5,1,1,1,1,1,1,7,3,3,5,5,1,5,5,5,5,7,
  1,1,3,1,5,5,5,5,7,2,2,1,1,1,1,1,1,1,5,5,5,5,5,1,1,1,1,1,1,7,3,1,1,3,1,1,1,
  1,1,1,1,1,1,1,1,1,1,7,1,1,1,1,5,5,5,5,7,3,3,1,1,1,1,2,1,1,7,2,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,1,1,1,1,1,1,1,2,
  1,1,7,2,1,1,5,5,5,1,1,1,1,1,1,7,3,1,1,1,1,1,1,1,5,5,5,1,1,1,1,1,1,7,2,1,5,
  1,1,1,1,1,1,7,3,1,1,1,1,1,1,1,5,1,1,1,1,1,1,7,2,3,3,3,3,3,3,3,7,3,3,3,3,3,
  3,5,3,5,5,5,5,5,5,5,5,5,5,5,5,5,7,5,5,5,5,5,5,5,5,5,5,5,5,5,7,5,5,5,5,5,5,
  5,5,5,5,5,5,5,7,5,5,5,5,5,5,5,5,5,5,5,5,5,7,5,5,5,5,5,5,5,5,5,5,5,5,5,7,3,
  3,3,3,3,3,3,5,2,2,2,2,2,2,2,5,5,5,2,2,2,2,2,2,7,2,1,7,1,1,7,3,1,1,2,1,1,1,
  1,1,1,7,2,1,7,3,1,1,2,1,1,1,1,1,1,7,2,1,7,1,1,7,1,1,7,3,1,1,2,1,1,1,2,1,1,
  7,2,2,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  9,9,9,9,9,9,9,9,9,9,5,1,7,1,1,1,1,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,2,2,1,1,1,1,1,1,7,3,3,2,1,1,2,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
  4,4,4,4,4,7,1,1,1,1,1,1,1,1,7,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,7,3,3,3,3,3,3,
  3,3,3,3,3,3,3,5,1,1,1,1,1,1,1,1,1,1,1,1,1,7,3,1,1,5,3,1,1,1,1,1,1,1,7,1,1,
  5,5,5,5,5,7,3,2,5,5,5,5,7,1,3,2,2,5,5,7,1,1,1,1,1,2,2,5,5,7,1,1,1,2,1,5,5,
  5,1,1,1,1,1,1,7,3,1,1,1,1,1,1,1,5,5,5,1,1,1,1,1,1,7,3,1,5,1,1,1,1,1,1,7,3,
  1,1,1,1,1,1,1,5,1,1,1,1,1,1,7,3,2,5,1,1,5,1,1,1,1,1,1,7,2,1,1,1,1,1,1,1,1,
  1,1,1,1,1,7,2,5,1,2,5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,5,5,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,2,2,5,5,7,1,2,1,1,2,1,5,5,5,5,1,1,1,1,1,1,7,1,3,3,3,3,3,
  3,3,3,3,3,3,3,3,3,7,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,1,1,7,1,1,1,1,1,1,1,1,1,
  1,1,1,1,7,3,1,1,1,1,1,1,2,1,1,7,2,3,2,1,7,1,1,2,3,5,5,5,3,3,3,3,3,3,7,3,3,
  3,3,3,3,3,3,5,5,5,3,3,3,3,3,3,7,3,1,5,1,1,1,1,1,1,7,3,1,1,1,1,1,1,1,5,1,1,
  1,1,1,1,7,3,1,7,3,1,1,1,1,1,1,1,5,1,1,1,1,1,1,7,2,1,7,3,1,7,3,9,9,9,9,9,9,
  9,9,9,9,9,9,9,5,9,9,9,9,9,9,9,5,1,7,1,1,1,1,1,1,1,7,1,5,5,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,2,2,5,5,7,1,2,1,1,2,1,5,1,1,1,1,1,1,7,3,1,1,1,1,1,1,1,5,
  1,1,1,1,1,1,7,3,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,1,1,7,1,5,1,1,1,1,1,1,7,3,1,
  1,1,1,1,1,1,5,1,1,1,1,1,1,7,3,1,7,1,1,1,1,3,1,1,7,3,1,1,1,1,1,1,1,1,1,1,1,
  1,1,7,1,1,1,7,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,1,1,7,1,1,1,1,1,1,1,1,1,1,1,1,
  1,7,1,1,1,7,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,1,1,7,1,1,1,1,1,1,1,1,1,1,1,1,1,
  7,1,1,1,7,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,1,1,7,1,1,1,1,1,1,1,1,1,1,1,1,1,7,
  2
};


static const unsigned short ag_pstt[] = {
12,123,115,112,110,109,4,4,1,0,0,4,4,4,12,11,10,9,8,7,6,5,5,3,2,
38,1,
55,55,55,55,55,55,55,55,55,55,55,55,43,42,2,13,14,13,13,14,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,3,13,15,13,13,15,
65,65,1,67,65,65,
124,124,124,124,34,16,23,24,25,26,157,154,29,30,31,137,18,21,71,71,71,71,71,
  5,33,33,33,34,20,17,33,33,33,33,33,33,33,33,33,33,33,33,22,32,28,27,33,
  19,
124,124,124,124,320,23,24,25,26,42,42,42,42,42,6,41,41,41,42,40,39,38,37,36,
  22,41,41,35,
55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,7,13,43,13,13,43,
81,81,81,81,81,81,81,45,81,81,81,81,81,81,81,81,18,81,81,81,81,81,81,8,45,
  45,44,19,44,44,
81,81,81,81,81,81,81,46,81,81,81,81,81,81,81,81,18,81,81,81,81,81,81,9,46,
  46,44,19,44,44,
124,124,124,124,47,23,24,25,26,157,154,29,30,31,137,21,71,71,71,71,71,10,33,
  33,33,47,33,33,33,33,33,33,33,33,33,33,33,33,22,32,28,27,33,
124,124,124,124,48,23,24,25,26,157,154,29,30,31,137,21,71,71,71,71,71,11,33,
  33,33,48,33,33,33,33,33,33,33,33,33,33,33,33,22,32,28,27,33,
131,12,50,49,
43,42,56,54,54,
51,51,51,51,51,51,51,51,51,51,51,51,14,
54,54,54,54,54,54,54,54,54,54,54,54,52,53,15,
273,273,273,16,55,
61,56,58,60,1,17,60,96,
55,43,42,18,13,57,13,13,57,
41,58,19,59,58,41,
61,56,58,60,1,20,60,95,
222,222,222,21,60,
55,43,42,22,13,61,13,13,61,
265,265,265,23,62,
253,253,253,24,63,
220,220,220,25,64,
159,159,159,26,65,
55,43,42,27,13,66,13,13,66,156,
55,43,42,28,13,67,13,13,67,153,
151,151,151,29,68,
145,145,145,30,69,
139,139,139,31,70,
55,43,42,32,13,71,13,13,71,136,
124,124,124,124,23,24,25,26,157,154,29,30,31,137,21,72,70,70,70,70,70,70,70,
  70,70,70,70,70,70,70,22,32,28,27,70,
320,74,74,74,74,74,34,73,73,73,74,72,35,
75,35,
318,318,318,318,318,318,318,318,318,318,318,318,318,318,36,319,
316,316,316,316,316,316,316,316,316,316,316,316,316,316,37,317,
314,314,314,314,314,314,314,314,314,314,314,314,314,314,38,315,
312,312,312,312,312,312,312,312,312,312,312,312,312,312,39,313,
310,310,310,310,310,310,310,310,310,310,310,310,310,310,40,311,
124,124,124,124,320,23,24,25,26,91,91,91,91,91,41,89,89,40,39,38,37,36,22,
  89,89,35,
61,56,58,60,1,42,60,93,
124,124,124,124,320,23,24,25,26,76,76,76,76,76,43,41,41,41,76,40,39,38,37,
  36,22,41,41,35,
18,235,234,19,234,
79,79,79,79,83,79,79,77,79,79,79,79,79,79,79,79,79,83,83,83,83,83,45,78,79,
80,80,80,80,83,80,80,77,80,80,80,80,80,80,80,80,80,83,83,83,83,83,46,78,80,
320,81,81,81,81,81,47,73,73,73,81,72,35,
320,82,82,82,82,82,48,73,73,73,82,72,35,
83,49,
124,124,124,124,84,23,24,25,26,157,154,29,30,31,137,21,71,71,71,71,71,50,33,
  33,33,84,33,33,33,33,33,33,33,33,33,33,33,33,22,32,28,27,33,
55,43,42,51,13,85,13,13,85,
55,43,42,52,13,86,13,13,86,
55,43,42,53,13,87,13,13,87,
55,43,42,54,13,88,13,13,88,
55,43,42,55,13,89,13,13,89,274,
43,42,55,55,56,13,90,13,13,90,
50,57,91,
40,58,40,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,
  55,55,55,55,55,55,55,59,13,231,13,13,231,
55,43,42,60,13,92,13,13,92,
50,61,93,
55,43,42,62,13,94,13,13,94,
55,43,42,63,13,95,13,13,95,
55,43,42,64,13,96,13,13,96,
55,43,42,65,13,97,13,13,97,
50,66,98,
50,67,99,
55,43,42,68,13,100,13,13,100,
55,43,42,69,13,101,13,13,101,
55,43,42,70,13,102,13,13,102,
50,71,103,
105,105,105,105,300,105,105,105,105,30,300,300,300,300,300,72,104,105,
320,77,77,77,77,77,73,75,75,72,35,
61,56,58,60,1,74,60,94,
55,43,42,75,13,106,13,13,106,
61,56,58,60,1,76,60,92,
55,43,42,77,13,107,13,13,107,
41,58,78,108,58,41,
124,124,124,124,109,23,24,25,26,157,154,29,30,31,137,21,71,71,71,71,71,79,
  33,33,33,109,33,33,33,33,33,33,33,33,33,33,33,33,22,32,28,27,33,
124,124,124,124,110,23,24,25,26,157,154,29,30,31,137,21,71,71,71,71,71,80,
  33,33,33,110,33,33,33,33,33,33,33,33,33,33,33,33,22,32,28,27,33,
61,56,58,60,1,81,60,80,
61,56,58,60,1,82,60,79,
132,132,132,83,111,
320,112,112,112,112,112,84,73,73,73,112,72,35,
50,85,113,
50,86,114,
50,87,115,
50,88,116,
49,89,117,
59,1,90,59,
237,237,237,237,237,237,237,237,237,91,118,
50,92,119,
125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,
  125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,
  125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,
  125,93,121,120,
50,94,122,
50,95,123,
50,96,124,
50,97,125,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,
  55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,55,55,55,55,98,13,
  126,13,13,126,158,
127,131,129,131,131,129,131,129,131,131,131,131,127,131,129,127,131,131,128,
  131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,
  131,129,131,129,131,131,131,131,131,131,131,131,131,99,133,131,155,134,
  132,130,130,130,
50,100,135,
50,101,136,
50,102,137,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,
  55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,55,55,55,55,103,13,
  138,13,13,138,
299,299,299,299,299,299,299,299,299,299,299,299,299,299,104,301,
124,124,124,124,305,23,24,25,26,305,305,305,305,305,105,40,39,38,37,36,22,
  139,139,139,307,
50,106,140,
50,107,141,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,108,13,
  84,13,13,84,
320,142,142,142,142,142,109,73,73,73,142,72,35,
320,143,143,143,143,143,110,73,73,73,143,72,35,
55,43,42,111,13,144,13,13,144,
61,56,58,60,1,112,60,78,
145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,
  145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,
  145,145,145,145,145,145,145,145,145,145,145,145,145,41,58,145,145,145,
  145,145,145,113,147,1,145,146,58,41,120,
145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,
  145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,
  145,145,145,145,145,145,145,145,145,145,145,145,145,41,58,145,145,145,
  145,145,145,114,149,1,145,148,58,41,
145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,
  145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,
  145,145,145,145,145,145,145,145,145,145,145,145,145,41,58,145,145,145,
  145,145,145,115,151,1,145,150,58,41,
145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,
  145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,
  145,145,145,145,145,145,145,145,145,145,145,145,145,41,58,145,145,145,
  145,145,145,116,153,1,145,152,58,41,
55,43,42,55,55,55,55,55,55,117,13,154,13,13,154,
55,43,42,55,55,55,55,55,55,118,13,155,13,13,155,
55,55,43,42,55,55,55,55,55,119,13,156,13,13,156,
157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,
  157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,
  157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,
  157,120,157,157,
41,58,121,158,58,41,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,
  55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,
  55,55,55,43,42,55,55,55,55,55,55,122,13,159,13,13,159,266,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,
  55,55,55,55,123,13,160,13,13,160,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,
  55,55,55,55,55,124,13,161,13,13,161,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,
  55,43,42,55,55,55,55,55,55,125,13,162,13,13,162,
163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,165,163,163,163,
  163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,
  163,163,163,163,163,163,163,163,126,164,166,
167,167,167,167,167,167,167,167,167,167,167,167,167,167,457,457,167,167,167,
  167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,457,
  457,167,167,167,457,457,167,167,167,167,167,167,127,167,167,459,
169,169,169,169,169,169,169,169,169,169,169,169,169,169,169,169,169,169,169,
  169,168,169,169,169,169,169,169,169,169,169,169,169,169,169,169,169,169,
  169,169,169,169,169,169,169,169,169,169,169,169,169,169,169,169,169,169,
  169,128,169,169,169,169,
170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,
  170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,
  30,30,170,170,170,30,30,170,170,170,170,170,170,129,170,170,32,
171,440,130,172,172,442,
173,34,174,34,34,174,34,174,34,34,34,34,173,34,174,173,34,34,460,460,34,34,
  34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,174,34,174,35,34,34,
  34,34,34,34,34,34,34,131,
175,132,
47,133,176,
45,41,58,134,178,58,41,177,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,135,13,179,
  13,13,179,
145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,
  145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,
  145,145,145,145,145,145,145,145,145,145,145,145,145,41,58,145,145,145,
  145,145,145,136,181,1,145,180,58,41,146,
145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,
  145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,
  145,145,145,145,145,145,145,145,145,145,145,145,145,41,58,145,145,145,
  145,145,145,137,183,1,145,182,58,41,140,
184,184,184,184,184,184,184,184,184,184,184,184,184,184,184,184,184,184,184,
  184,184,184,184,184,184,184,184,184,184,184,184,184,184,184,184,184,184,
  184,184,184,184,184,184,184,138,185,184,
124,124,124,124,23,24,25,26,306,40,39,38,37,36,22,304,304,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,
  55,55,55,55,55,55,140,13,186,13,13,186,
55,43,42,55,55,55,55,55,141,13,187,13,13,187,188,
61,56,58,60,1,142,60,86,
61,56,58,60,1,143,60,85,
50,144,189,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,146,13,122,13,13,122,
41,58,147,190,58,41,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,
  148,13,119,13,13,119,
41,58,149,191,58,41,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,
  150,13,117,13,13,117,
41,58,151,192,58,41,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,152,13,
  114,13,13,114,
41,58,153,193,58,41,
194,194,194,194,290,194,194,154,290,195,
194,194,194,194,418,194,194,155,418,197,242,196,
198,411,198,198,198,198,198,156,201,201,200,199,410,
128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
  128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
  128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
  128,129,128,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,158,13,
  130,13,13,130,
202,202,202,202,202,202,202,202,202,202,202,202,202,202,202,202,202,202,202,
  202,202,202,202,204,205,206,16,202,202,202,202,202,202,202,202,202,202,
  202,202,202,202,202,202,202,202,202,202,202,202,202,202,202,202,202,202,
  202,202,202,159,267,268,203,
207,207,207,207,207,207,207,207,207,207,207,207,207,207,207,207,207,207,207,
  207,207,207,207,207,207,207,207,160,207,207,209,208,
210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,
  210,210,210,210,210,210,210,210,210,161,211,210,210,
212,212,212,212,212,212,212,212,212,212,212,214,215,216,217,218,212,212,212,
  212,212,212,212,212,212,212,212,212,212,212,212,212,162,219,213,212,212,
220,129,220,220,129,220,129,220,220,220,220,220,129,220,220,220,220,220,220,
  220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,129,220,129,
  220,220,220,220,220,220,220,220,220,163,37,220,
47,164,221,
223,222,223,223,223,223,223,165,222,223,
45,41,58,166,225,58,41,224,
456,456,456,456,456,456,456,456,456,456,456,456,456,456,456,456,456,456,456,
  456,456,456,456,456,456,456,456,456,456,456,456,456,456,456,456,456,456,
  456,456,456,456,456,456,458,456,
471,471,471,471,471,471,471,471,471,471,471,471,471,471,471,471,471,471,471,
  471,471,471,471,471,471,471,471,471,471,471,471,471,471,471,471,471,471,
  471,471,471,471,471,471,471,471,471,471,471,471,471,471,471,471,471,471,
  471,471,471,168,
475,169,
29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,
  29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,31,29,
127,226,226,226,226,226,226,226,226,127,226,127,226,226,128,226,226,226,226,
  226,226,226,226,226,226,226,226,226,226,226,226,226,226,226,226,226,226,
  226,226,226,226,226,226,226,171,226,437,437,437,
171,441,439,
167,167,167,167,167,167,167,167,167,167,167,167,167,167,457,457,167,167,167,
  167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,457,
  457,167,167,167,457,457,167,167,167,167,167,167,173,167,167,461,
170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,
  170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,
  30,30,170,170,170,30,30,170,170,170,170,170,170,174,170,170,36,
127,226,226,226,226,226,226,226,226,127,226,127,226,226,227,226,226,226,226,
  226,226,226,226,226,226,226,226,226,226,226,226,226,226,226,226,226,226,
  226,226,226,226,226,226,226,175,226,436,228,228,228,228,
127,226,226,226,226,226,226,226,226,127,226,127,226,226,128,226,226,226,226,
  226,226,226,226,226,226,226,226,226,226,226,226,226,226,226,226,226,226,
  226,226,226,226,226,226,226,176,226,229,132,130,130,130,
220,129,220,220,129,220,129,220,220,220,220,220,129,220,220,220,220,220,220,
  220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,129,220,129,
  220,220,220,220,220,220,220,220,220,177,230,220,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,178,13,
  433,13,13,433,
231,231,231,231,231,231,231,231,231,231,231,231,231,231,231,231,231,231,231,
  179,233,232,232,
149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,
  149,149,149,149,180,234,
41,58,181,235,58,41,
143,143,143,143,143,143,143,143,143,143,143,143,143,143,143,143,143,143,143,
  143,143,143,143,182,236,
41,58,183,237,58,41,
431,431,431,431,431,431,431,431,431,431,431,431,431,431,431,431,431,431,431,
  431,431,431,431,431,431,431,431,431,431,431,431,431,431,431,431,431,431,
  431,431,431,431,431,431,431,432,
43,42,185,238,
321,321,321,321,321,321,321,321,321,321,321,321,321,321,321,321,321,321,321,
  321,321,321,321,321,321,321,321,321,321,186,239,
198,198,198,198,198,198,187,240,
43,42,248,248,188,241,242,242,250,
55,43,42,55,55,55,55,55,55,189,13,243,13,13,243,
55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,190,13,121,13,13,121,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,
  191,13,118,13,13,118,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,
  192,13,116,13,13,116,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,193,13,
  113,13,13,113,
244,244,244,244,244,244,244,22,244,
43,42,195,245,
424,423,422,421,419,420,
43,42,197,246,246,246,
247,247,247,247,247,247,247,198,414,
43,42,199,248,248,248,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,
  55,55,55,55,55,55,55,200,13,13,13,249,
83,83,198,83,411,83,83,83,83,77,83,83,83,83,83,83,83,83,83,83,83,83,83,83,
  198,198,198,198,198,201,78,225,224,200,199,410,
250,250,250,250,250,250,250,250,250,250,250,250,250,250,250,250,250,250,250,
  250,250,250,250,250,250,250,250,250,250,250,250,250,250,250,250,250,250,
  250,250,250,250,250,250,250,250,250,250,250,250,250,250,250,250,250,250,
  202,356,250,
49,41,58,203,251,58,41,252,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,
  55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,55,55,55,55,55,55,
  204,13,253,13,13,253,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,
  55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,55,55,55,55,55,55,
  205,13,254,13,13,254,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,
  55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,55,55,55,55,55,55,
  206,13,255,13,13,255,
208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,
  208,208,208,208,208,208,208,208,259,208,
55,43,42,256,256,208,13,256,13,13,256,
41,58,209,257,58,41,
427,427,427,427,427,427,427,427,427,427,427,427,427,427,427,427,427,427,427,
  427,427,427,427,427,427,427,427,427,428,427,
55,43,42,211,13,258,13,13,258,
208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,
  208,208,208,208,208,208,208,208,209,208,
43,42,213,259,
260,260,260,260,260,260,260,260,260,260,260,260,260,260,260,260,260,260,260,
  260,260,43,42,260,260,260,260,260,260,214,261,260,260,
262,262,262,262,262,262,262,262,262,262,262,262,262,262,262,262,262,262,262,
  262,262,43,42,262,262,262,262,262,262,215,263,262,262,
264,264,264,264,264,264,264,264,264,264,264,264,264,264,264,264,264,264,264,
  264,264,43,42,264,264,264,264,264,264,216,265,264,264,
43,42,217,266,
43,42,218,267,
43,42,55,55,219,13,268,13,13,268,
34,174,34,34,174,34,174,34,34,34,34,34,174,34,34,34,34,34,34,34,34,34,34,34,
  34,34,34,34,34,34,34,34,34,34,174,34,174,34,34,34,34,34,34,34,34,34,35,
55,43,42,221,13,269,13,13,269,
507,509,
270,270,270,270,270,270,223,
220,129,220,220,129,220,129,220,220,220,220,220,129,220,220,220,220,220,220,
  220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,129,220,129,
  220,220,220,220,220,220,220,220,220,224,271,220,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,225,13,
  503,13,13,503,
173,34,34,34,34,34,34,34,34,173,34,173,34,34,34,34,34,34,34,34,34,34,34,34,
  34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,460,
272,272,272,272,272,272,272,272,272,272,272,272,272,272,272,272,272,272,272,
  168,273,272,272,272,272,272,272,272,272,272,272,272,272,272,272,272,272,
  272,272,272,272,272,272,272,272,272,272,272,272,272,272,272,272,272,272,
  272,227,272,272,272,272,273,272,
274,446,446,446,446,228,275,275,448,
48,229,276,
46,230,277,
279,279,279,279,279,279,279,279,279,279,279,279,278,493,279,279,279,279,279,
  279,279,279,279,279,279,279,279,279,279,279,279,279,279,279,279,279,279,
  279,279,279,279,231,279,279,279,495,
280,232,
43,42,55,55,233,13,281,13,13,281,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,234,13,
  150,13,13,150,
147,147,147,147,147,147,147,147,147,147,147,147,147,147,147,147,147,147,147,
  147,147,147,147,235,282,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,236,13,
  144,13,13,144,
141,141,141,141,141,141,141,141,141,141,141,141,141,141,141,141,141,141,141,
  141,141,141,141,237,283,
55,55,55,55,55,55,55,55,43,42,55,55,55,55,55,55,238,13,284,13,13,284,
322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,
  322,322,322,322,322,322,322,322,322,322,239,285,
43,42,240,286,286,286,
55,43,42,55,55,55,55,55,241,13,187,13,13,187,245,
43,42,249,241,247,
194,194,194,194,135,194,194,243,135,287,
24,24,24,24,24,24,24,25,
288,288,288,288,288,288,288,288,288,288,288,288,288,288,288,288,288,288,288,
  288,288,288,288,288,288,288,288,288,288,288,288,288,288,288,288,288,288,
  288,288,288,288,288,288,288,288,288,288,288,288,288,288,288,288,288,288,
  245,289,288,288,
194,43,42,194,194,194,418,194,194,246,418,54,54,290,243,196,
291,291,291,291,291,291,291,247,
198,413,43,42,198,198,198,198,198,248,54,54,292,412,
229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,227,
  229,229,229,229,229,229,229,229,229,229,229,249,293,230,
361,361,361,361,361,361,361,361,361,361,361,361,361,361,361,361,361,361,361,
  361,361,361,361,361,361,361,361,361,361,361,361,361,361,361,361,361,361,
  361,361,361,361,361,361,361,361,361,361,361,361,361,361,361,361,361,361,
  362,
271,271,271,271,271,271,271,271,271,271,271,271,271,271,271,271,271,271,271,
  271,271,271,271,251,294,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,
  55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,
  42,55,55,55,55,55,55,252,13,295,13,13,295,
163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,
  163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,
  163,41,58,163,163,163,163,163,163,253,296,2,297,58,41,
163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,
  163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,
  163,41,58,163,163,163,163,163,163,254,298,2,299,58,41,
163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,
  163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,
  163,41,58,163,163,163,163,163,163,255,300,2,301,58,41,
49,256,302,
254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,
  254,254,254,254,257,303,
49,258,304,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,
  55,55,55,55,55,55,259,13,305,13,13,305,
208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,
  208,208,208,208,208,208,208,208,211,208,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,
  55,55,55,55,43,42,55,55,55,55,55,55,261,13,306,13,13,306,
208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,
  208,208,208,208,208,208,208,208,212,208,
55,55,55,55,43,42,263,13,307,13,13,307,
208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,
  208,208,208,208,208,208,208,208,210,208,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,
  43,42,55,55,55,55,55,55,265,13,308,13,13,308,
55,55,43,42,266,13,309,13,13,309,
55,55,43,42,267,13,310,13,13,310,
41,58,268,311,58,41,
165,269,312,
313,313,515,515,313,515,515,313,313,313,313,313,313,270,313,313,517,
46,271,314,
465,465,465,465,465,465,465,465,465,465,465,465,465,465,465,465,465,465,465,
  168,465,465,465,465,465,465,465,465,465,465,465,465,465,465,465,465,465,
  465,465,465,465,465,465,465,465,465,465,465,465,465,465,465,465,465,465,
  467,465,465,465,465,
468,273,
127,226,226,226,226,226,226,226,226,127,226,127,226,226,227,226,226,226,226,
  226,226,226,226,226,226,226,226,226,226,226,226,226,226,226,226,226,226,
  226,226,226,226,226,226,226,274,226,443,443,443,443,
274,447,445,
41,58,276,315,58,41,
41,58,277,316,58,41,
317,317,317,317,317,317,317,317,317,317,317,317,317,278,
204,204,204,204,204,204,204,204,204,204,204,204,278,204,204,204,204,204,204,
  204,204,204,204,204,204,204,204,204,204,204,204,204,204,204,204,204,204,
  204,204,204,494,204,204,
318,318,318,318,318,318,318,318,318,318,318,318,278,318,320,502,318,318,318,
  318,318,318,318,318,318,318,318,318,318,318,318,318,318,318,318,318,318,
  502,502,502,502,318,318,318,318,318,318,280,318,321,320,319,318,318,318,
41,58,281,322,58,41,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,282,13,
  148,13,13,148,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,283,13,
  142,13,13,142,
323,323,323,323,323,323,323,323,323,323,323,323,323,323,284,324,323,
325,325,325,325,325,325,326,325,325,325,325,325,325,325,325,325,325,325,325,
  325,325,325,325,325,325,325,325,325,325,285,323,329,328,327,325,325,
194,51,43,42,194,194,194,418,194,194,286,418,54,330,54,251,196,
43,42,55,55,287,13,331,13,13,331,
293,293,293,293,293,293,293,293,293,293,293,293,293,293,293,293,293,293,293,
  293,293,293,293,293,293,293,293,293,293,293,293,293,293,293,293,293,293,
  293,293,293,293,293,293,293,293,293,293,293,293,293,293,293,293,293,293,
  294,293,
44,41,58,289,333,58,41,332,
43,42,290,334,334,334,335,335,
336,336,336,336,336,336,336,291,
43,42,55,55,292,13,337,13,13,337,
18,293,228,44,19,44,44,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,294,13,
  272,13,13,272,
338,338,338,338,338,338,338,338,338,338,338,338,338,338,338,338,338,338,338,
  338,338,338,338,338,338,338,338,338,338,338,338,338,338,338,338,338,338,
  338,338,338,338,338,338,338,338,338,338,338,338,338,338,338,338,338,295,
  339,
41,58,296,340,58,41,
285,285,285,285,285,285,285,285,285,285,285,285,285,285,285,285,285,285,285,
  285,285,285,285,297,341,
41,58,298,342,58,41,
283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,
  283,283,283,283,299,343,
41,58,300,344,58,41,
281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,
  281,281,281,281,301,345,
346,346,346,346,346,346,346,346,346,346,346,346,346,346,346,346,346,346,346,
  346,346,346,346,346,346,346,346,346,346,346,346,346,346,346,346,346,346,
  346,346,346,346,346,346,346,346,346,346,257,258,346,346,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,303,13,
  255,13,13,255,
55,43,42,55,55,55,55,55,55,304,13,347,13,13,347,
348,348,348,348,348,348,348,348,348,348,348,350,351,348,348,348,348,348,348,
  348,348,348,348,348,348,348,348,348,348,305,349,348,348,
348,348,348,348,348,348,348,348,348,348,348,352,353,355,356,357,358,190,189,
  348,348,348,348,348,348,348,348,348,348,348,348,348,348,348,348,306,359,
  354,348,348,
360,362,190,189,307,363,361,202,
348,348,348,348,348,348,348,348,348,348,348,365,366,190,189,348,348,348,348,
  348,348,348,348,348,348,348,348,348,348,348,348,308,367,364,348,348,
190,189,309,368,
190,189,310,369,
160,160,160,160,160,160,160,160,160,160,160,160,160,160,160,160,160,160,160,
  160,160,160,160,311,370,
48,312,371,
514,514,514,514,514,514,514,514,514,516,514,
43,42,55,55,314,13,372,13,13,372,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,315,13,
  435,13,13,435,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,316,13,
  434,13,13,434,
496,496,496,496,496,496,496,496,496,496,496,496,496,317,
500,500,500,500,500,500,500,500,500,500,500,500,278,500,500,500,500,500,500,
  500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,
  500,500,500,500,501,500,500,500,
373,484,
374,482,
375,478,478,478,478,321,480,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,322,13,
  152,13,13,152,
376,376,376,376,376,376,376,376,376,376,376,376,376,323,365,376,
43,42,324,377,
339,339,339,339,339,339,339,339,339,339,339,339,339,339,339,339,339,339,339,
  339,339,339,339,339,339,339,339,339,340,339,
44,326,378,
43,42,327,379,379,379,
41,58,328,380,58,41,
43,42,329,381,381,381,383,382,382,
55,43,42,55,55,55,55,55,55,330,13,384,13,13,384,
41,58,331,385,58,41,
194,194,194,194,295,194,194,332,295,386,
275,275,275,275,275,275,275,275,275,275,275,275,275,275,275,275,275,275,275,
  275,275,275,275,333,387,
194,43,42,194,194,194,418,194,194,334,418,54,54,238,244,196,
43,42,241,334,334,334,240,
388,388,388,388,388,388,388,336,
41,58,337,236,58,41,
145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,
  145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,
  145,145,145,145,145,145,145,145,145,145,145,145,145,357,357,145,145,145,
  145,145,145,338,359,145,359,
41,58,339,389,58,41,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,340,13,
  287,13,13,287,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,341,13,
  286,13,13,286,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,342,13,
  289,13,13,289,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,343,13,
  284,13,13,284,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,344,13,
  288,13,13,288,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,345,13,
  282,13,13,282,
263,263,263,263,263,263,263,263,263,263,263,263,263,263,263,263,263,263,263,
  263,263,263,263,263,263,263,263,263,263,263,263,263,263,263,263,263,263,
  263,263,263,263,263,263,263,263,263,263,264,263,
194,194,194,194,429,194,194,347,429,390,
208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,
  208,208,208,208,208,208,208,208,213,208,
43,42,349,391,
392,392,392,392,392,392,392,392,392,392,392,392,392,392,392,392,392,392,392,
  392,392,43,42,392,392,392,392,392,392,350,393,392,392,
394,394,394,394,394,394,394,394,394,394,394,394,394,394,394,394,394,394,394,
  394,394,43,42,394,394,394,394,394,394,351,395,394,394,
392,392,392,392,392,392,392,392,392,392,392,392,392,392,392,392,392,392,392,
  392,392,392,392,392,392,392,392,352,392,392,
394,394,394,394,394,394,394,394,394,394,394,394,394,394,394,394,394,394,394,
  394,394,394,394,394,394,394,394,353,394,394,
43,42,354,396,
43,42,355,397,
43,42,356,398,
43,42,357,399,
43,42,358,400,
43,42,359,401,
402,402,402,402,402,402,402,402,402,402,402,402,402,402,402,402,402,402,402,
  402,402,402,402,402,402,402,402,402,402,402,402,551,551,402,402,402,402,
  402,402,360,402,402,553,
43,42,361,403,
43,42,362,404,
43,42,363,405,
43,42,364,406,
392,392,392,392,392,392,392,392,392,392,392,392,392,392,392,392,392,392,392,
  392,392,43,42,392,392,392,392,392,392,365,407,392,392,
394,394,394,394,394,394,394,394,394,394,394,394,394,394,394,394,394,394,394,
  394,394,43,42,394,394,394,394,394,394,366,408,394,394,
43,42,367,409,
43,42,368,410,
43,42,369,411,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,370,13,
  161,13,13,161,
43,42,55,55,371,13,412,13,13,412,
41,58,372,504,58,41,
318,318,318,318,318,318,318,318,318,318,318,318,278,318,320,502,318,318,318,
  318,318,318,318,318,318,318,318,318,318,318,318,318,318,318,318,318,318,
  502,502,502,502,318,318,318,318,318,318,373,318,485,320,319,318,318,318,
318,318,318,318,318,318,318,318,318,318,318,318,278,318,320,502,318,318,318,
  318,318,318,318,318,318,318,318,318,318,318,318,318,318,318,318,318,318,
  502,502,502,502,318,318,318,318,318,318,374,318,483,320,319,318,318,318,
413,413,413,413,413,413,413,413,413,413,413,413,278,413,413,413,413,413,413,
  413,413,413,413,413,413,413,413,413,413,413,413,413,413,413,413,413,413,
  413,413,413,375,413,413,479,413,
367,367,367,367,367,367,367,367,367,367,367,367,367,368,
55,43,42,55,55,55,55,55,55,377,13,414,13,13,414,
415,415,415,415,415,415,415,415,415,415,415,415,415,415,415,415,415,415,415,
  415,415,415,415,415,415,415,415,378,415,415,416,
194,582,580,578,576,421,422,423,424,417,418,419,420,343,344,43,42,194,194,
  194,342,194,194,379,342,54,54,431,430,346,429,428,427,426,425,
326,326,326,326,326,326,326,326,326,326,326,326,326,326,326,326,326,380,432,
433,433,433,433,433,433,433,433,433,433,433,433,433,433,433,433,433,433,433,
  433,433,433,43,42,433,433,433,433,433,433,381,54,54,333,433,
43,42,55,55,382,434,434,434,336,335,
41,58,383,435,58,41,
194,194,194,194,418,194,194,384,418,252,196,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,385,13,
  436,13,13,436,
44,43,42,55,55,386,13,437,438,13,13,438,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,387,13,
  276,13,13,276,
439,439,439,439,439,439,439,388,
269,269,269,269,269,269,269,269,269,269,269,269,269,269,269,269,269,269,269,
  269,269,269,269,389,440,
43,42,55,55,390,13,441,13,13,441,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,
  55,55,55,55,55,391,13,442,13,13,442,
208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,
  208,208,208,208,208,208,208,208,215,208,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,
  55,55,55,55,55,393,13,443,13,13,443,
208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,
  208,208,208,208,208,208,208,208,214,208,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,
  55,55,55,55,55,395,13,444,13,13,444,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,
  55,55,55,55,55,396,13,445,13,13,445,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,
  43,42,55,55,55,55,55,55,397,13,446,13,13,446,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,
  43,42,55,55,55,55,55,55,398,13,447,13,13,447,
55,55,55,43,42,55,55,55,55,55,55,399,13,448,13,13,448,
55,55,55,55,55,55,55,55,55,43,42,55,55,55,55,55,55,400,13,449,13,13,449,
55,55,55,55,55,55,55,55,55,55,43,42,55,55,55,55,55,55,401,13,450,13,13,450,
550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,
  550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,
  552,550,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,
  55,55,55,55,55,55,55,55,55,43,42,55,55,55,55,55,55,403,13,451,13,13,451,
55,55,55,55,43,42,55,55,55,55,55,55,404,13,452,13,13,452,
55,55,55,55,55,55,55,55,55,55,43,42,55,55,55,55,55,55,405,13,453,13,13,453,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,
  55,55,55,55,55,406,13,454,13,13,454,
55,55,55,55,55,55,55,55,55,55,43,42,55,55,55,55,55,55,407,13,455,13,13,455,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,
  42,55,55,55,55,55,55,408,13,456,13,13,456,
55,55,55,55,55,55,55,55,55,55,43,42,55,55,55,55,55,55,409,13,457,13,13,457,
55,55,55,55,55,55,55,55,55,55,43,42,55,55,55,55,55,55,410,13,458,13,13,458,
55,55,55,55,55,55,55,55,55,55,43,42,55,55,55,55,55,55,411,13,459,13,13,459,
41,58,412,460,58,41,
204,204,204,204,204,204,204,204,204,204,204,204,278,461,204,204,204,204,204,
  204,204,204,204,204,204,204,204,204,204,204,204,204,204,204,204,486,486,
  486,486,204,204,204,204,204,204,413,204,488,204,
462,462,462,462,462,462,462,414,462,463,369,
208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,
  208,208,208,208,208,208,208,208,341,208,
43,42,330,464,464,464,
51,417,465,
51,418,466,
51,419,467,
51,420,468,
51,421,469,
51,422,470,
51,423,471,
51,424,472,
44,425,473,
44,426,474,
44,427,475,
44,428,476,
44,554,477,
43,42,430,478,478,478,
44,345,479,
55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,432,13,327,13,13,327,
349,349,349,349,349,349,349,349,349,349,349,349,349,349,349,349,349,349,349,
  349,349,349,349,349,349,349,349,349,350,
433,433,433,433,433,433,433,433,433,433,433,433,433,433,433,433,433,433,433,
  433,433,433,43,42,433,433,433,433,433,433,56,54,54,333,433,
324,324,324,324,324,324,324,324,324,324,324,324,324,324,324,324,324,435,480,
133,133,133,133,133,133,133,133,133,133,133,133,133,133,133,133,133,133,133,
  133,133,436,134,
481,481,481,481,481,481,481,481,481,481,481,481,481,481,481,481,481,481,481,
  481,481,481,481,481,481,481,437,482,481,
41,58,438,483,58,41,
484,484,484,484,484,484,484,439,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,440,13,
  270,13,13,270,
41,58,441,485,58,41,
486,486,486,486,486,486,486,486,486,486,486,486,486,486,486,486,486,486,486,
  486,486,486,486,486,486,486,486,486,442,179,486,486,
486,486,486,486,486,486,486,486,486,486,486,486,486,486,486,486,486,486,486,
  486,486,486,486,486,486,486,486,486,443,178,486,486,
486,486,486,486,486,486,486,486,486,486,486,486,486,486,486,486,486,486,486,
  486,486,486,486,486,486,486,486,486,444,177,486,486,
486,486,486,486,486,486,486,486,486,486,486,486,486,486,486,486,486,486,486,
  486,486,486,486,486,486,486,486,486,445,171,486,486,
487,487,487,487,487,487,487,487,487,487,487,187,487,487,487,487,487,487,487,
  487,487,487,487,487,186,487,487,487,487,487,487,446,170,188,487,487,
487,487,487,487,487,487,487,487,487,487,487,187,487,487,487,487,487,487,487,
  487,487,487,487,487,186,487,487,487,487,487,487,447,169,188,487,487,
488,184,183,488,488,488,488,488,488,448,488,168,185,
489,489,489,489,489,181,489,489,180,489,489,489,489,489,489,449,167,182,490,
491,491,491,491,491,192,491,491,491,191,491,491,491,491,491,491,450,166,193,
  491,491,
492,492,492,492,492,492,492,492,492,492,492,492,278,492,492,492,492,492,492,
  492,492,492,492,492,492,492,492,492,492,492,492,492,492,492,492,492,492,
  492,492,492,451,176,492,492,492,
493,494,200,199,493,493,493,493,493,493,452,175,201,536,537,
491,491,491,491,491,192,491,491,491,191,491,491,491,491,491,491,453,165,193,
  491,491,
486,486,486,486,486,486,486,486,486,486,486,486,486,486,486,486,486,486,486,
  486,486,486,486,486,486,486,486,486,454,174,486,486,
495,496,498,499,495,495,197,495,495,196,496,496,496,496,496,496,455,173,198,
  535,374,375,501,497,500,
502,502,502,502,502,502,502,502,502,502,373,502,502,502,502,502,502,502,502,
  502,502,502,502,194,502,502,502,502,502,502,456,172,172,172,503,502,502,
491,491,491,491,491,192,491,491,491,191,491,491,491,491,491,491,457,164,193,
  491,491,
491,491,491,491,491,192,491,491,491,191,491,491,491,491,491,491,458,163,193,
  491,491,
491,491,491,491,491,192,491,491,491,191,491,491,491,491,491,491,459,162,193,
  491,491,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,460,13,
  505,13,13,505,
413,413,413,413,413,413,413,413,413,413,413,413,278,413,413,413,413,413,413,
  413,413,413,413,413,413,413,413,413,413,413,413,413,413,413,413,413,413,
  413,413,413,461,413,413,487,413,
24,24,24,24,24,24,24,370,
43,42,463,504,
194,343,344,43,42,194,194,194,342,194,194,464,342,54,54,505,
487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,
  487,487,487,487,487,487,487,487,487,487,465,581,487,487,
487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,
  487,487,487,487,487,487,487,487,487,487,466,579,487,487,
488,488,488,488,488,488,488,467,488,577,
489,489,489,489,489,489,489,489,489,489,489,489,489,468,575,490,
506,507,605,506,506,506,506,506,506,469,574,
508,509,626,508,508,508,508,508,508,470,571,
510,513,587,510,510,510,586,511,512,471,586,570,
506,507,605,506,506,506,506,506,506,472,568,
421,424,473,515,514,
516,474,517,
518,475,519,
518,424,476,521,520,
522,477,555,
526,526,526,526,631,630,523,524,525,526,526,526,526,526,526,526,526,526,526,
  526,526,526,526,526,526,526,526,526,43,42,526,526,526,526,526,526,478,
  54,54,329,526,526,355,
194,194,194,194,347,194,194,479,347,527,
55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,480,13,325,13,13,325,
297,297,297,297,297,297,297,297,297,297,297,297,297,297,297,297,297,297,297,
  297,297,297,297,297,297,297,298,
43,42,55,55,482,13,528,13,13,528,
277,277,277,277,277,277,277,277,277,277,277,277,277,277,277,277,277,277,277,
  277,277,277,277,483,529,
530,530,530,530,530,530,530,484,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,485,13,
  221,13,13,221,
218,218,218,218,218,218,218,218,218,218,218,218,218,218,218,218,218,218,218,
  218,218,218,218,218,218,218,218,218,219,218,
529,529,529,529,529,529,529,529,529,529,529,529,529,529,529,529,529,529,529,
  529,529,529,529,529,529,529,529,529,529,530,529,
24,24,24,24,24,24,24,527,
524,524,524,524,524,524,524,524,524,524,524,524,524,489,
531,490,
532,532,532,532,532,532,532,532,532,532,532,532,532,532,533,532,
204,204,204,204,204,204,204,204,204,204,204,204,278,204,204,204,204,204,204,
  204,204,204,204,204,204,204,204,204,204,204,204,204,204,204,204,204,204,
  204,204,204,205,204,204,
533,532,545,545,545,545,533,533,533,533,533,533,493,533,533,547,
534,534,534,534,534,534,494,
396,396,396,396,396,396,495,
535,535,535,535,535,535,535,535,535,535,535,535,535,496,
489,489,489,489,489,489,489,489,489,489,489,489,489,497,398,
397,536,397,397,397,397,498,
537,537,537,537,537,537,537,540,391,391,391,391,537,537,537,537,537,537,499,
  540,539,538,540,
541,542,500,543,403,
541,542,501,395,
519,519,519,519,519,519,519,519,519,519,519,519,519,519,519,519,519,519,519,
  519,519,519,519,519,519,519,519,519,520,519,
44,371,544,372,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,
  55,43,42,55,55,55,55,55,55,504,13,545,13,13,545,
44,43,42,55,55,505,13,546,13,13,331,
547,602,602,602,547,547,547,547,547,547,506,604,
548,548,548,548,548,548,548,548,548,548,548,548,548,507,
549,623,549,549,549,549,549,549,508,625,
550,550,550,550,550,550,550,550,550,550,550,550,550,509,
7,7,7,7,7,7,7,6,
7,552,553,554,557,555,556,6,551,
558,558,558,558,558,558,558,6,
559,559,559,559,559,559,559,559,559,559,559,559,559,513,
44,514,560,
44,564,561,
51,516,562,
44,562,563,
51,518,564,
44,519,565,
44,520,566,
44,556,567,
51,522,568,
569,569,569,569,569,569,569,569,569,569,569,569,569,570,629,629,629,569,569,
  569,569,569,569,569,569,569,569,569,569,569,569,569,569,569,569,569,569,
  569,569,569,569,569,569,569,569,569,569,569,523,569,629,
569,569,569,569,569,569,569,569,569,569,569,569,569,570,628,628,628,569,569,
  569,569,569,569,569,569,569,569,569,569,569,569,569,569,569,569,569,569,
  569,569,569,569,569,569,569,569,569,569,569,524,569,628,
569,569,569,569,569,569,569,569,569,569,569,569,569,570,627,627,627,569,569,
  569,569,569,569,569,569,569,569,569,569,569,569,569,569,569,569,569,569,
  569,569,569,569,569,569,569,569,569,569,569,525,569,627,
353,353,353,353,353,353,353,353,353,353,353,353,353,353,353,353,353,353,353,
  353,353,353,353,353,353,353,353,353,353,354,353,
43,42,527,571,571,571,
41,58,528,572,58,41,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,529,13,
  278,13,13,278,
573,573,573,573,573,573,573,530,
489,489,489,489,489,489,489,489,489,489,489,489,489,531,574,575,
541,541,541,541,541,541,541,532,
544,532,544,544,544,544,544,544,546,544,
493,493,493,493,493,493,493,534,540,
489,489,489,489,489,489,489,489,489,489,489,489,489,535,399,
489,489,489,489,489,489,489,489,489,489,489,489,489,536,394,
524,524,524,524,524,524,524,524,524,524,524,524,524,387,
576,576,576,383,576,576,576,576,383,383,383,383,383,383,576,576,576,576,576,
  576,538,386,386,
380,380,577,380,380,380,380,539,578,578,382,
579,400,400,400,400,540,404,404,
537,537,537,537,537,537,537,391,391,391,391,391,537,537,537,537,537,537,541,
  393,539,538,393,
537,537,537,537,537,537,537,537,537,537,537,537,537,542,580,539,538,
579,400,400,400,400,543,402,402,
510,510,510,510,408,511,512,544,408,581,
212,212,212,212,212,212,212,212,212,212,212,214,215,216,217,218,212,212,212,
  212,212,212,212,212,212,212,212,212,212,212,212,212,545,582,213,212,212,
194,194,194,194,347,194,194,546,347,583,
584,595,595,595,584,584,584,584,584,584,547,603,
585,585,585,585,585,585,585,599,599,599,585,585,585,585,585,585,548,601,
586,621,586,586,586,586,586,586,549,624,
587,587,587,587,587,587,587,612,587,587,587,587,587,587,550,614,
14,14,14,14,14,14,14,551,
21,21,21,21,21,21,7,21,
13,7,7,7,7,7,7,13,13,13,13,13,13,553,
12,7,7,7,7,7,7,12,12,12,12,12,12,554,
11,7,7,7,7,7,7,11,11,11,11,11,11,555,
10,7,7,7,7,7,7,10,10,10,10,10,10,556,
9,7,7,7,7,7,7,9,9,9,9,9,9,557,
8,8,8,8,8,8,8,7,
585,585,585,585,585,585,585,583,583,583,585,585,585,585,585,585,559,585,
516,560,588,
522,561,565,
506,507,605,506,506,506,506,506,506,562,573,
522,563,563,
589,590,598,589,589,589,589,589,589,564,572,
516,565,591,
516,566,592,
522,567,557,
510,513,587,510,510,510,586,511,512,568,586,569,
431,431,431,431,431,431,431,431,431,431,431,431,431,431,431,431,431,431,431,
  431,431,431,431,431,431,431,431,431,431,431,431,431,431,431,431,431,431,
  431,431,431,431,431,431,431,636,
593,570,
526,526,526,526,631,630,523,524,525,526,526,526,526,526,526,526,526,526,526,
  526,526,526,526,526,526,526,526,526,43,42,526,526,526,526,526,526,571,
  54,54,328,526,526,355,
279,279,279,279,279,279,279,279,279,279,279,279,279,279,279,279,279,279,279,
  279,279,279,279,572,594,
595,595,595,595,595,595,595,573,
596,596,596,596,596,596,596,596,596,596,596,596,596,574,
597,575,
524,524,524,524,524,524,524,524,524,524,524,524,524,385,
537,537,537,537,537,537,537,537,537,537,537,537,537,577,377,538,
577,381,379,
510,510,510,510,598,511,512,579,598,
599,388,388,388,388,388,580,390,
44,405,405,405,405,581,600,407,
43,42,55,55,582,13,601,13,13,601,
43,42,55,55,583,13,13,13,332,
602,593,593,593,602,602,602,602,602,602,584,596,
603,603,603,603,603,603,603,588,588,588,603,603,603,603,603,603,585,600,
604,619,604,604,604,604,604,604,586,622,
605,605,605,605,605,605,605,610,605,605,605,605,605,605,587,613,
44,566,606,
584,595,584,584,584,584,584,584,589,597,
607,607,607,607,607,607,607,607,607,607,607,607,607,590,
44,558,608,
44,560,609,
610,610,610,610,610,610,610,610,610,610,610,610,610,593,610,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,594,13,
  280,13,13,280,
611,415,415,415,415,611,611,611,611,611,611,595,611,417,
525,525,525,525,525,525,525,525,525,525,525,525,525,596,
489,489,489,489,489,489,489,489,489,489,489,489,489,597,574,612,
613,598,
537,537,537,537,537,537,537,537,537,537,537,537,537,599,389,539,538,
194,194,194,194,409,194,194,600,409,406,
41,58,601,614,58,41,
594,591,591,591,594,594,594,594,594,594,602,594,
589,589,589,589,589,589,589,583,583,583,589,589,589,589,589,589,603,589,
615,617,615,615,615,615,615,615,604,620,
616,616,616,616,616,616,616,608,616,616,616,616,616,616,605,611,
522,606,567,
603,603,603,603,603,603,603,588,603,603,603,603,603,603,607,590,
522,608,559,
522,609,561,
367,367,367,367,367,367,367,367,367,367,367,367,367,635,
24,24,24,24,24,24,24,416,
617,612,
510,510,510,510,618,511,512,613,618,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,43,42,55,55,614,13,
  138,13,13,138,
619,615,619,619,619,619,619,619,615,618,
620,620,620,620,620,620,620,606,620,620,620,620,620,620,616,609,
489,489,489,489,489,489,489,489,489,489,489,489,489,617,574,621,
622,618,
547,602,547,547,547,547,547,547,619,616,
585,585,585,585,585,585,585,599,585,585,585,585,585,585,620,607,
623,621,
510,510,510,510,376,511,512,622,376,
489,489,489,489,489,489,489,489,489,489,489,489,489,623,574,624,
625,624,
489,489,489,489,489,489,489,489,489,489,489,489,489,625,574,626,
627,626,
489,489,489,489,489,489,489,489,489,489,489,489,489,627,574,628,
629,628,
489,489,489,489,489,489,489,489,489,489,489,489,489,629,574,630,
631,630,
489,489,489,489,489,489,489,489,489,489,489,489,489,631,574,632,
633,632,
489,489,489,489,489,489,489,489,489,489,489,489,489,633,574,634,
635,634,
489,489,489,489,489,489,489,489,489,489,489,489,489,635,526,

};


static const unsigned short ag_sbt[] = {
     0,  25,  27,  47,  69,  75, 123, 151, 173, 203, 233, 276, 319, 323,
   328, 341, 356, 361, 369, 378, 384, 392, 397, 406, 411, 416, 421, 426,
   436, 446, 451, 456, 461, 471, 506, 519, 521, 537, 553, 569, 585, 601,
   627, 635, 663, 668, 693, 718, 731, 744, 746, 789, 798, 807, 816, 825,
   835, 845, 848, 851, 889, 898, 901, 910, 919, 928, 937, 940, 943, 952,
   961, 970, 973, 991,1002,1010,1019,1027,1036,1042,1085,1128,1136,1144,
  1149,1162,1165,1168,1171,1174,1177,1181,1192,1195,1254,1257,1260,1263,
  1266,1320,1379,1382,1385,1388,1440,1456,1481,1484,1487,1516,1529,1542,
  1551,1559,1625,1690,1755,1820,1835,1850,1865,1924,1930,1997,2032,2068,
  2108,2156,2209,2270,2324,2330,2383,2385,2388,2396,2423,2489,2555,2602,
  2619,2656,2671,2679,2687,2690,2747,2769,2775,2806,2812,2843,2849,2878,
  2884,2894,2906,2919,2977,3006,3068,3100,3132,3169,3218,3221,3231,3239,
  3284,3343,3345,3393,3442,3445,3498,3552,3603,3654,3703,3732,3755,3780,
  3786,3811,3817,3862,3866,3897,3905,3914,3929,3951,3982,4013,4042,4051,
  4055,4061,4067,4076,4082,4119,4155,4213,4221,4275,4329,4383,4412,4423,
  4429,4459,4468,4497,4501,4534,4567,4600,4604,4608,4618,4665,4674,4676,
  4683,4732,4761,4805,4868,4877,4880,4883,4929,4931,4941,4970,4995,5024,
  5049,5071,5102,5108,5123,5128,5138,5146,5205,5221,5229,5243,5276,5332,
  5357,5419,5471,5523,5575,5578,5603,5606,5643,5672,5715,5744,5756,5785,
  5824,5834,5844,5850,5853,5870,5873,5933,5935,5985,5988,5994,6000,6014,
  6057,6112,6118,6147,6176,6193,6229,6246,6256,6313,6321,6329,6337,6347,
  6354,6383,6439,6445,6470,6476,6501,6507,6532,6583,6612,6627,6660,6700,
  6708,6744,6748,6752,6777,6780,6791,6801,6830,6859,6873,6918,6920,6922,
  6929,6958,6974,6978,7008,7011,7017,7023,7032,7047,7053,7063,7088,7104,
  7111,7119,7125,7187,7193,7222,7251,7280,7309,7338,7367,7416,7426,7455,
  7459,7492,7525,7555,7585,7589,7593,7597,7601,7605,7609,7652,7656,7660,
  7664,7668,7701,7734,7738,7742,7746,7775,7785,7791,7846,7901,7946,7960,
  7975,8006,8041,8060,8095,8105,8111,8122,8151,8163,8192,8200,8225,8235,
  8271,8300,8336,8365,8401,8437,8476,8515,8532,8555,8579,8618,8666,8684,
  8708,8744,8768,8806,8830,8854,8878,8884,8933,8944,8973,8979,8982,8985,
  8988,8991,8994,8997,9000,9003,9006,9009,9012,9015,9018,9024,9027,9050,
  9079,9114,9133,9156,9185,9191,9199,9228,9234,9266,9298,9330,9362,9398,
  9434,9447,9466,9487,9532,9547,9568,9600,9625,9662,9683,9704,9725,9754,
  9799,9807,9811,9827,9860,9893,9903,9919,9930,9941,9953,9964,9969,9972,
  9975,9980,9983,10026,10036,10059,10086,10096,10121,10129,10158,10188,
  10219,10227,10241,10243,10259,10302,10318,10325,10332,10346,10361,10368,
  10391,10396,10400,10430,10434,10474,10485,10497,10511,10521,10535,10543,
  10552,10560,10574,10577,10580,10583,10586,10589,10592,10595,10598,10601,
  10652,10703,10754,10785,10791,10797,10826,10834,10850,10858,10868,10877,
  10892,10907,10921,10944,10955,10963,10986,11003,11011,11021,11058,11068,
  11080,11098,11108,11124,11132,11140,11154,11168,11182,11196,11210,11218,
  11236,11239,11242,11253,11256,11267,11270,11273,11276,11288,11333,11335,
  11378,11403,11411,11425,11427,11441,11457,11460,11469,11477,11485,11495,
  11504,11516,11534,11544,11560,11563,11573,11587,11590,11593,11608,11637,
  11651,11665,11681,11683,11700,11710,11716,11728,11746,11756,11772,11775,
  11791,11794,11797,11811,11819,11821,11830,11859,11869,11885,11901,11903,
  11913,11929,11931,11940,11956,11958,11974,11976,11992,11994,12010,12012,
  12028,12030,12046,12048,12063
};


static const unsigned short ag_sbe[] = {
     9,  26,  41,  63,  72,  98, 137, 167, 196, 226, 254, 297, 320, 325,
   340, 355, 359, 366, 372, 380, 389, 395, 400, 409, 414, 419, 424, 429,
   439, 449, 454, 459, 464, 486, 512, 520, 535, 551, 567, 583, 599, 615,
   632, 649, 664, 690, 715, 724, 737, 745, 767, 792, 801, 810, 819, 828,
   839, 846, 849, 883, 892, 899, 904, 913, 922, 931, 938, 941, 946, 955,
   964, 971, 988, 997,1007,1013,1024,1030,1038,1063,1106,1133,1141,1147,
  1155,1163,1166,1169,1172,1175,1179,1190,1193,1251,1255,1258,1261,1264,
  1313,1370,1380,1383,1386,1434,1454,1470,1482,1485,1510,1522,1535,1545,
  1556,1617,1683,1748,1813,1829,1844,1859,1921,1926,1990,2026,2062,2102,
  2153,2205,2265,2320,2326,2382,2384,2386,2391,2417,2481,2547,2599,2610,
  2650,2664,2676,2684,2688,2746,2763,2771,2800,2808,2837,2845,2872,2880,
  2891,2901,2913,2975,3000,3064,3095,3128,3164,3215,3219,3228,3234,3282,
  3342,3344,3391,3437,3443,3494,3548,3596,3647,3700,3726,3751,3778,3782,
  3809,3813,3861,3864,3895,3903,3909,3923,3945,3976,4007,4036,4049,4053,
  4059,4063,4074,4078,4114,4148,4210,4216,4269,4323,4377,4410,4417,4425,
  4457,4462,4495,4499,4530,4563,4596,4602,4606,4612,4664,4668,4675,4682,
  4729,4755,4804,4861,4873,4878,4881,4924,4930,4935,4964,4993,5018,5047,
  5065,5100,5104,5116,5125,5135,5145,5201,5214,5228,5238,5273,5331,5355,
  5413,5465,5517,5569,5576,5601,5604,5637,5670,5709,5742,5750,5783,5818,
  5828,5838,5846,5851,5866,5871,5928,5934,5979,5986,5990,5996,6013,6054,
  6104,6114,6141,6170,6190,6222,6239,6250,6311,6316,6323,6336,6341,6348,
  6377,6437,6441,6468,6472,6499,6503,6530,6579,6606,6621,6656,6695,6704,
  6739,6746,6750,6775,6778,6789,6795,6824,6853,6872,6914,6919,6921,6927,
  6952,6971,6976,7006,7009,7013,7019,7025,7041,7049,7060,7086,7097,7106,
  7118,7121,7183,7189,7216,7245,7274,7303,7332,7361,7414,7423,7453,7457,
  7488,7521,7552,7582,7587,7591,7595,7599,7603,7607,7648,7654,7658,7662,
  7666,7697,7730,7736,7740,7744,7769,7779,7787,7838,7893,7941,7959,7969,
  8002,8029,8058,8090,8099,8107,8118,8145,8156,8186,8199,8223,8229,8265,
  8298,8330,8363,8395,8431,8470,8509,8526,8549,8573,8616,8660,8678,8702,
  8738,8762,8800,8824,8848,8872,8880,8929,8940,8971,8975,8980,8983,8986,
  8989,8992,8995,8998,9001,9004,9007,9010,9013,9016,9020,9025,9044,9078,
  9109,9131,9154,9182,9187,9198,9222,9230,9262,9294,9326,9358,9393,9429,
  9443,9462,9482,9527,9542,9563,9596,9616,9655,9678,9699,9720,9748,9794,
  9806,9809,9822,9856,9889,9900,9916,9928,9939,9950,9962,9966,9970,9973,
  9977,9981,10019,10033,10053,10085,10090,10119,10128,10152,10186,10217,
  10226,10240,10242,10257,10299,10314,10324,10331,10345,10359,10367,10386,
  10393,10398,10428,10431,10468,10479,10495,10510,10519,10534,10542,10550,
  10559,10573,10575,10578,10581,10584,10587,10590,10593,10596,10599,10649,
  10700,10751,10783,10787,10793,10820,10833,10847,10857,10866,10875,10890,
  10905,10920,10941,10951,10960,10981,10999,11008,11018,11053,11065,11078,
  11096,11106,11122,11131,11138,11153,11167,11181,11195,11209,11217,11234,
  11237,11240,11251,11254,11265,11268,11271,11274,11285,11332,11334,11371,
  11401,11410,11424,11426,11440,11454,11458,11467,11475,11482,11489,11499,
  11514,11532,11542,11558,11561,11571,11586,11588,11591,11606,11631,11648,
  11664,11678,11682,11696,11707,11712,11726,11744,11754,11770,11773,11789,
  11792,11795,11810,11818,11820,11828,11853,11867,11883,11898,11902,11911,
  11927,11930,11938,11953,11957,11971,11975,11989,11993,12007,12011,12025,
  12029,12043,12047,12061,12063
};


static const unsigned char ag_fl[] = {
  1,1,1,1,2,1,1,2,3,1,1,1,1,1,3,1,1,1,1,1,1,3,1,1,2,2,1,1,1,2,0,1,2,1,2,
  1,3,2,2,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,2,0,1,1,1,3,1,1,1,1,1,2,0,1,1,1,
  2,0,1,1,1,2,0,1,5,4,4,0,1,0,3,6,6,1,1,2,0,1,4,3,4,3,3,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,8,7,1,8,7,8,7,6,3,2,1,1,0,1,1,2,2,6,0,0,0,11,1,2,1,16,
  0,5,0,4,0,3,0,5,0,4,0,3,0,9,2,1,3,2,1,3,0,0,10,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,2,
  1,2,2,2,1,2,2,1,1,2,1,0,13,0,1,2,7,1,0,4,0,3,3,1,1,2,1,5,0,2,1,2,9,1,1,
  1,2,1,2,0,1,5,4,6,0,0,9,1,3,4,1,1,1,1,2,1,0,5,2,2,0,8,0,5,0,3,0,9,0,12,
  0,14,0,5,0,5,0,5,5,5,5,1,1,1,2,1,1,1,2,1,0,0,2,1,1,2,0,1,3,1,1,0,2,0,2,
  0,2,0,2,0,2,0,0,0,8,0,5,0,4,7,5,3,6,8,2,1,2,2,1,1,2,1,1,1,1,1,1,1,1,1,
  2,1,1,1,2,1,1,2,0,1,2,1,2,1,0,1,2,1,2,1,1,1,1,2,1,1,1,6,2,1,2,0,1,2,0,
  1,1,2,1,0,2,3,0,1,2,3,2,2,2,2,3,0,1,2,2,3,0,2,3,1,1,1,1,1,1,2,0,1,10,1,
  1,2,1,1,1,1,1,1,2,1,1,1,2,1,3,6,6,3,2,1,2,0,1,2,2,1,2,0,1,2,1,1,1,1,1,
  1,1,2,0,1,2,1,3,1,1,1,2,0,1,3,1,1,2,0,1,1,3,1,1,0,2,4,1,1,3,1,3,0,2,2,
  1,1,1,1,0,1,2,3,1,1,1,2,1,0,4,7,9,1,2,0,1,1,1,1,1,2,0,1,4,1,2,1,1,1,1,
  2,3,21,1,1,2,1,1,2,1,1,1,1,1,1,1,3,2,1,1,2,0,1,2,1,1,2,0,1,2,1,3,3,5,5,
  7,5,7,3,5,3,5,5,7,3,3,3,3,3,3,3,3,1,3,1,3,1,3,1,0,1,3,1,1,0,2,3,0,1,0,
  2,0,2,2,1,0,2,3,0,2,2,1,0,2,0,2,0,2,0,2,3,0,2,0,2,0,2,0,2,0,2,2,1,2,2,
  2,1,1,1,1,1,3,1,1,1,1
};

static const unsigned short ag_ptt[] = {
    0,  2,  4,  7,  7,  3,  8,  8,  8, 16, 16, 16, 16, 16,  8, 18, 18, 18,
   18, 18, 18,  8, 19, 20, 20, 19, 24, 24, 25, 25, 26, 26, 21, 27, 27, 21,
   21,  5, 29, 29, 32, 32, 35, 35, 38, 40, 42, 44, 46, 48, 50, 52, 55, 56,
   56, 57, 57, 54, 58, 58, 58, 58, 62, 62, 63, 63, 64, 64, 67, 68, 68, 69,
   69, 71, 72, 72, 73, 73,  1,  1,  1, 78, 78, 80, 80,  1,  1, 84, 85, 85,
   86, 86,  1,  1,  1,  1,  1, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66,
   66, 74, 82, 88,105, 75, 75,107, 76, 76, 81, 81, 87,113,113,112,115,118,
  120,121,121,117,102,122,124,126, 65,125, 91,127,128,135, 92,137,136,138,
  136,140, 93,142,141,143,141,145, 94, 95,147,148, 96,151,152,156,157, 97,
  133,133,133,133,133,133,133,133,133,133,133,133,133,133,133,133,133,133,
  166,166,166,168,168,168,170,170,170,159,159,160,160,160,175,175,177,177,
  177,179,179,179,180,193,193,181,195,196,196,182,182,182,182,172,172,172,
  198,199,199,173,201, 98,204,206,206,207, 99,209,205,210,205, 89,212,213,
  213, 77,208,216,220,221,221,211,217,218,219,225,226,226,227,227, 79,224,
  224,230,232,100,231,231,231,233,237,237,238,238,234,240,101,241,241,245,
  241,246,241,248, 90,252,249,254,249,256,249,258,242,260,242,262,242,242,
  242,242,250,264,265,265,251,253,267,267,255,269,270,270,272,273,273,274,
  274, 70, 83, 83,275,271,276,271,277,271,278,271,279,271,280,282,283,268,
  287,284,289,284,285,285,288,288,288,298,299,299,286,301,302,302,290,296,
  291,291,291,294,294,292,305,305,297,307,308,308,293,293,243,312,312,244,
  314,314,311,315,315,131,318,318,316,132,319,320,320,320,323,323,326,329,
  330,330,331,331,327,333,333,333,328,328,336,336,334,337,337,334,338,324,
  340,340,343,343,345,345,344,325,325,348,348,322,346,347,214,214,215,215,
  228,351,351,350,352,222,222,353,353,353,353,359,360,360,202,203,361,361,
  130,150,150,150,362,368,369,369,370,370,363,372,373,373,374,374,365,371,
  371,366,366,380,380,381,381,382,382,377,377,377,386,386,387,387,388,388,
  376,391,384,385,396,396,396,378,398,395,404,404,146,399,401,401,401,401,
  410,410,403,192,192,192,192,415,415,405,413,417,417,418,418,408,406,154,
  154,154,420,420,421,421,422,422,422,423,423,424,424,419,426,426,321,425,
  425,425,332,427,184,185,429,429,186,431,431,187,188,189,190,190,430,428,
  432,437,437,438,438,439,439,433,442,443,443,444,444,191,303,303,303,303,
  303,303,303,303,303,303,303,303,303,303,445,446,447,448,449,450,451,452,
  452,452,452,452,452,452,452,469,469,456,456,456,470,470,461,471,471,472,
  472,473,473,461,461,474,474,454,475,475,454,454,476,476,477,477,478,478,
  479,479,459,480,480,481,481,482,482,483,483,484,484,459,459,309,309,309,
  309,309,486,486,486,486,486,375, 33, 34
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
    case 21: ag_rp_26(PCB_POINTER, V(5,RvpStrPtrN)); break;
    case 22: ag_rp_27(PCB_POINTER); break;
    case 23: ag_rp_28(PCB_POINTER); break;
    case 24: ag_rp_29(PCB_POINTER, V(5,RvpStrPtrN)); break;
    case 25: ag_rp_30(PCB_POINTER); break;
    case 26: ag_rp_31(PCB_POINTER, V(5,RvpStrPtrN)); break;
    case 27: ag_rp_32(PCB_POINTER); break;
    case 28: ag_rp_33(PCB_POINTER, V(0,RvpStrPtrN)); break;
    case 29: ag_rp_34(PCB_POINTER); break;
    case 30: ag_rp_35(PCB_POINTER); break;
    case 31: V(0,char) = ag_rp_36(PCB_POINTER); break;
    case 32: ag_rp_37(PCB_POINTER); break;
    case 33: ag_rp_39(PCB_POINTER, V(0,char), V(3,RvpStrPtrN)); break;
    case 34: ag_rp_40(PCB_POINTER); break;
    case 35: ag_rp_41(PCB_POINTER); break;
    case 36: ag_rp_42(PCB_POINTER); break;
    case 37: ag_rp_43(PCB_POINTER); break;
    case 38: ag_rp_44(PCB_POINTER); break;
    case 39: ag_rp_45(PCB_POINTER, V(3,RvpStrPtrN), V(6,RvpStrPtrN), V(9,RvpStrPtrN)); break;
    case 40: ag_rp_46(PCB_POINTER); break;
    case 41: ag_rp_47(PCB_POINTER, V(-2,RvpStrPtrN)); break;
    case 42: ag_rp_48(PCB_POINTER, V(0,RvpStrPtrN)); break;
    case 43: ag_rp_49(PCB_POINTER); break;
    case 44: ag_rp_50(PCB_POINTER); break;
    case 45: ag_rp_51(PCB_POINTER); break;
    case 46: ag_rp_52(PCB_POINTER, V(-2,RvpStrPtrN)); break;
    case 47: ag_rp_53(PCB_POINTER, V(0,RvpStrPtrN)); break;
    case 48: ag_rp_54(PCB_POINTER); break;
    case 49: ag_rp_55(PCB_POINTER); break;
    case 50: ag_rp_56(PCB_POINTER); break;
    case 51: ag_rp_57(PCB_POINTER, V(5,RvpStrPtrN)); break;
    case 52: ag_rp_58(PCB_POINTER); break;
    case 53: ag_rp_59(PCB_POINTER); break;
    case 54: ag_rp_60(PCB_POINTER); break;
    case 55: ag_rp_61(PCB_POINTER); break;
    case 56: ag_rp_62(PCB_POINTER); break;
    case 57: ag_rp_63(PCB_POINTER); break;
    case 58: ag_rp_64(PCB_POINTER, V(3,RvpStrPtrN), V(6,RvpStrPtrN)); break;
    case 59: ag_rp_65(PCB_POINTER, V(3,RvpStrPtrN), V(6,RvpStrPtrN)); break;
    case 60: ag_rp_66(PCB_POINTER, V(3,RvpStrPtrN), V(6,RvpStrPtrN)); break;
    case 61: ag_rp_67(PCB_POINTER, V(3,RvpStrPtrN), V(6,RvpStrPtrN)); break;
    case 62: ag_rp_68(PCB_POINTER, V(3,RvpStrPtrN), V(6,RvpStrPtrN)); break;
    case 63: ag_rp_69(PCB_POINTER, V(6,RvpStrPtrN)); break;
    case 64: ag_rp_70(PCB_POINTER, V(6,RvpStrPtrN)); break;
    case 65: ag_rp_71(PCB_POINTER, V(6,RvpStrPtrN)); break;
    case 66: ag_rp_72(PCB_POINTER, V(6,RvpStrPtrN)); break;
    case 67: ag_rp_73(PCB_POINTER, V(3,RvpStrPtrN), V(6,RvpStrPtrN)); break;
    case 68: ag_rp_74(PCB_POINTER, V(6,RvpStrPtrN)); break;
    case 69: ag_rp_75(PCB_POINTER, V(6,RvpStrPtrN)); break;
    case 70: ag_rp_76(PCB_POINTER, V(3,RvpStrPtrN), V(6,RvpStrPtrN)); break;
    case 71: ag_rp_77(PCB_POINTER, V(6,RvpStrPtrN)); break;
    case 72: ag_rp_78(PCB_POINTER, V(3,RvpStrPtrN), V(6,RvpStrPtrN)); break;
    case 73: ag_rp_79(PCB_POINTER, V(0,RvpStrPtrN), V(6,RvpStrPtrN)); break;
    case 74: ag_rp_80(PCB_POINTER, V(0,RvpStrPtrN), V(6,RvpStrPtrN)); break;
    case 75: ag_rp_81(PCB_POINTER, V(0,RvpStrPtrN), V(3,RvpStrPtrN), V(6,RvpStrPtrN)); break;
    case 76: ag_rp_113(PCB_POINTER); break;
    case 77: ag_rp_114(PCB_POINTER, V(5,RvpStrPtrN), V(9,int)); break;
    case 78: ag_rp_115(PCB_POINTER); break;
    case 79: ag_rp_116(PCB_POINTER); break;
    case 80: ag_rp_117(PCB_POINTER); break;
    case 81: ag_rp_118(PCB_POINTER); break;
    case 82: ag_rp_119(PCB_POINTER, V(0,unsigned int), V(2,unsigned int)); break;
    case 83: ag_rp_120(PCB_POINTER); break;
    case 84: ag_rp_121(PCB_POINTER, V(0,RvSdpTypedTime)); break;
    case 85: ag_rp_122(PCB_POINTER, V(0,RvSdpTypedTime)); break;
    case 86: ag_rp_123(PCB_POINTER, V(0,RvSdpTypedTime)); break;
    case 87: ag_rp_124(PCB_POINTER, V(1,unsigned int), V(3,RvSdpTypedTime)); break;
    case 88: ag_rp_125(PCB_POINTER, V(1,unsigned int), V(5,RvSdpTypedTime)); break;
    case 89: ag_rp_126(PCB_POINTER); break;
    case 90: ag_rp_127(PCB_POINTER); break;
    case 91: ag_rp_128(PCB_POINTER, V(0,RvpStrPtrN)); break;
    case 92: ag_rp_129(PCB_POINTER, V(0,RvpStrPtrN)); break;
    case 93: ag_rp_130(PCB_POINTER, V(0,RvpStrPtrN), V(3,RvpStrPtrN)); break;
    case 94: ag_rp_133(PCB_POINTER); break;
    case 95: ag_rp_134(PCB_POINTER, V(-5,RvpStrPtrN), V(-2,RvpStrPtrN)); break;
    case 96: ag_rp_135(PCB_POINTER, V(1,RvpStrPtrN), V(4,RvpStrPtrN)); break;
    case 97: ag_rp_136(PCB_POINTER, V(-2,RvpStrPtrN)); break;
    case 98: ag_rp_137(PCB_POINTER, V(1,RvpStrPtrN)); break;
    case 99: ag_rp_138(PCB_POINTER); break;
    case 100: ag_rp_139(PCB_POINTER, V(-4,int), V(-2,RvpStrPtrN)); break;
    case 101: ag_rp_140(PCB_POINTER, V(3,int), V(5,RvpStrPtrN)); break;
    case 102: ag_rp_141(PCB_POINTER, V(-7,int), V(-5,RvpStrPtrN), V(-3,int)); break;
    case 103: ag_rp_142(PCB_POINTER, V(3,int), V(5,RvpStrPtrN), V(7,int)); break;
    case 104: ag_rp_143(PCB_POINTER, V(-9,int), V(-7,RvpStrPtrN), V(-5,int), V(-3,RvpStrPtrN)); break;
    case 105: ag_rp_144(PCB_POINTER, V(3,int), V(5,RvpStrPtrN), V(7,int), V(9,RvpStrPtrN)); break;
    case 106: ag_rp_145(PCB_POINTER); break;
    case 107: ag_rp_146(PCB_POINTER); break;
    case 108: ag_rp_147(PCB_POINTER); break;
    case 109: ag_rp_148(PCB_POINTER); break;
    case 110: ag_rp_149(PCB_POINTER); break;
    case 111: ag_rp_150(PCB_POINTER); break;
    case 112: ag_rp_151(PCB_POINTER, V(2,RvpStrPtrN)); break;
    case 113: ag_rp_152(PCB_POINTER, V(2,RvpStrPtrN)); break;
    case 114: ag_rp_153(PCB_POINTER, V(2,RvpStrPtrN)); break;
    case 115: V(0,int) = ag_rp_154(PCB_POINTER); break;
    case 116: V(0,int) = ag_rp_156(PCB_POINTER); break;
    case 117: ag_rp_158(PCB_POINTER); break;
    case 118: ag_rp_159(PCB_POINTER); break;
    case 119: ag_rp_160(PCB_POINTER); break;
    case 120: ag_rp_161(PCB_POINTER); break;
    case 121: ag_rp_162(PCB_POINTER); break;
    case 122: ag_rp_163(PCB_POINTER); break;
    case 123: ag_rp_164(PCB_POINTER); break;
    case 124: ag_rp_165(PCB_POINTER); break;
    case 125: ag_rp_166(PCB_POINTER); break;
    case 126: ag_rp_167(PCB_POINTER); break;
    case 127: ag_rp_168(PCB_POINTER); break;
    case 128: ag_rp_169(PCB_POINTER); break;
    case 129: ag_rp_170(PCB_POINTER); break;
    case 130: ag_rp_171(PCB_POINTER, V(0,RvpStrPtrN), V(2,int), V(4,int), V(6,RvpStrPtrN)); break;
    case 131: ag_rp_172(PCB_POINTER, V(0,RvpStrPtrN), V(2,int), V(4,RvpStrPtrN)); break;
    case 132: ag_rp_173(PCB_POINTER, V(2,RvpStrPtrN)); break;
    case 133: ag_rp_174(PCB_POINTER, V(2,RvpStrPtrN), V(4,int)); break;
    case 134: ag_rp_175(PCB_POINTER, V(2,RvpStrPtrN), V(4,int), V(6,int)); break;
    case 135: V(0,int) = ag_rp_178(PCB_POINTER); break;
    case 136: V(0,int) = ag_rp_179(PCB_POINTER); break;
    case 137: V(0,int) = ag_rp_180(PCB_POINTER); break;
    case 138: V(0,int) = ag_rp_181(PCB_POINTER); break;
    case 139: V(0,int) = ag_rp_182(PCB_POINTER); break;
    case 140: ag_rp_183(PCB_POINTER); break;
    case 141: V(0,RvpStrPtrN) = ag_rp_191(PCB_POINTER, V(0,RvpStrPtrN)); break;
    case 142: ag_rp_197(PCB_POINTER); break;
    case 143: ag_rp_198(PCB_POINTER); break;
    case 144: V(0,unsigned int) = ag_rp_199(PCB_POINTER, V(0,unsigned int)); break;
    case 145: V(0,unsigned int) = ag_rp_200(PCB_POINTER); break;
    case 146: V(0,unsigned int) = ag_rp_201(PCB_POINTER, V(0,unsigned int)); break;
    case 147: V(0,unsigned int) = ag_rp_202(PCB_POINTER); break;
    case 148: V(0,unsigned int) = ag_rp_203(PCB_POINTER); break;
    case 149: V(0,unsigned int) = ag_rp_204(PCB_POINTER); break;
    case 150: V(0,RvSdpTypedTime) = ag_rp_205(PCB_POINTER, V(0,unsigned int)); break;
    case 151: V(0,RvSdpTypedTime) = ag_rp_206(PCB_POINTER, V(0,unsigned int), V(1,short)); break;
    case 152: V(0,short) = ag_rp_207(PCB_POINTER); break;
    case 153: V(0,short) = ag_rp_208(PCB_POINTER); break;
    case 154: V(0,short) = ag_rp_209(PCB_POINTER); break;
    case 155: V(0,short) = ag_rp_210(PCB_POINTER); break;
    case 156: V(0,int) = ag_rp_212(PCB_POINTER); break;
    case 157: ag_rp_214(PCB_POINTER, V(0,RvpStrPtrN)); break;
    case 158: ag_rp_215(PCB_POINTER, V(0,RvpStrPtrN), V(2,RvpStrPtrN)); break;
    case 159: ag_rp_216(PCB_POINTER, V(0,RvpStrPtrN), V(2,RvpStrPtrN)); break;
    case 160: ag_rp_219(PCB_POINTER, V(1,RvpStrPtrN)); break;
    case 161: ag_rp_220(PCB_POINTER, V(1,RvpStrPtrN), V(3,RvpStrPtrN)); break;
    case 162: ag_rp_221(PCB_POINTER, V(1,RvpStrPtrN), V(4,RvpStrPtrN)); break;
    case 163: ag_rp_231(PCB_POINTER, V(2,RvpStrPtrN)); break;
    case 164: ag_rp_232(PCB_POINTER, V(2,RvpStrPtrN)); break;
    case 165: ag_rp_233(PCB_POINTER, V(2,RvpStrPtrN)); break;
    case 166: ag_rp_234(PCB_POINTER, V(2,RvpStrPtrN)); break;
    case 167: ag_rp_235(PCB_POINTER, V(2,RvpStrPtrN)); break;
    case 168: ag_rp_236(PCB_POINTER, V(2,RvpStrPtrN)); break;
    case 169: ag_rp_237(PCB_POINTER, V(2,RvpStrPtrN)); break;
    case 170: ag_rp_238(PCB_POINTER, V(2,RvpStrPtrN)); break;
    case 171: ag_rp_239(PCB_POINTER); break;
    case 172: ag_rp_240(PCB_POINTER, V(2,RvpStrPtrN)); break;
    case 173: ag_rp_241(PCB_POINTER); break;
    case 174: ag_rp_242(PCB_POINTER, V(2,RvpStrPtrN)); break;
    case 175: ag_rp_243(PCB_POINTER); break;
    case 176: ag_rp_244(PCB_POINTER, V(2,RvpStrPtrN)); break;
    case 177: ag_rp_245(PCB_POINTER); break;
  }
  (PCB).la_ptr = (PCB).pointer;
}

#define TOKEN_NAMES rvSdpParser_token_names
const char *const rvSdpParser_token_names[514] = {
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
  "continue",
  "bad_syntax",
  "bad_syntax_time",
  "repeat_lines",
  "",
  "zone_adjustments",
  "",
  "bad_syntax_repeat",
  "continuem",
  "media_line_or_fields",
  "",
  "",
  "",
  "bad_syntaxm",
  "reparse",
  "repeat_line",
  "rtpmap",
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
  "other_field",
  "\"CONT:\"",
  "\"CONTM:\"",
  "REPARSE PREF",
  "\"REPARSE:\"",
  "BAD SYNTAX PREF",
  "",
  "\"BAD-SYNTAX:\"",
  "'t'",
  "'r'",
  "BAD SYNTAX PREFM",
  "badsyntaxmlinebody",
  "\"BAD-SYNTAXM:\"",
  "field_tag",
  "UNKNOWN_TAG",
  "field_value",
  "",
  "LINE_TEXT",
  "",
  "",
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
  "",
  "time_description",
  "",
  "",
  "session_time",
  "",
  "",
  "repeat_fields",
  "",
  "",
  "start_time",
  "stop_time",
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
  if ((PCB).ssx >= 44) {
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


