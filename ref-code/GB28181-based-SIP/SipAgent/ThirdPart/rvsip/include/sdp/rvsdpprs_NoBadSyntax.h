#ifndef RVSDPPRS_NOBADSYNTAX_H_1094397748
#define RVSDPPRS_NOBADSYNTAX_H_1094397748

typedef union {
  long alignment;
  char ag_vt_2[sizeof(int)];
  char ag_vt_4[sizeof(RvpStrPtrN)];
  char ag_vt_5[sizeof(unsigned int)];
  char ag_vt_6[sizeof(RvSdpTypedTime)];
  char ag_vt_7[sizeof(short)];
} rvSdpParser_vs_type;

typedef enum {
  rvSdpParser_announcement_token = 1, rvSdpParser_text_token,
  rvSdpParser_byte_string_token, rvSdpParser_text_no_space_token,
  rvSdpParser_email_safe_string_no_space_token, rvSdpParser_ANY_BYTE_token,
  rvSdpParser_decimal_uchar_token = 8, rvSdpParser_DIGIT_token,
  rvSdpParser_POS_DIGIT_token, rvSdpParser_integer_token = 19,
  rvSdpParser_email_safe_string_token = 21,
  rvSdpParser_EMAIL_SAFE_ONLY_token, rvSdpParser_EMAIL_ATOM_N_SAFE_token,
  rvSdpParser_SAFE_token = 28, rvSdpParser_EOL_token,
  rvSdpParser_eol_token = 32, rvSdpParser_CR_token, rvSdpParser_LF_token,
  rvSdpParser_space_token, rvSdpParser_SPACE_token, rvSdpParser_TAB_token,
  rvSdpParser_fwdslash_token, rvSdpParser_opar_token = 40,
  rvSdpParser_clpar_token = 42, rvSdpParser_obrkt_token = 44,
  rvSdpParser_clbrkt_token = 46, rvSdpParser_colon_token = 48,
  rvSdpParser_equal_token = 50, rvSdpParser_minus_token = 52,
  rvSdpParser_omwsp_token = 54, rvSdpParser_EOM_token = 58,
  rvSdpParser_EOF_token, rvSdpParser_proto_version_token = 65,
  rvSdpParser_body_fields_token, rvSdpParser_media_description_token = 70,
  rvSdpParser_origin_field_token = 74, rvSdpParser_session_name_field_token,
  rvSdpParser_information_field_token, rvSdpParser_uri_field_token,
  rvSdpParser_email_field_token, rvSdpParser_phone_field_token,
  rvSdpParser_connection_field_token, rvSdpParser_bandwidth_field_token,
  rvSdpParser_time_fields_token, rvSdpParser_key_field_token,
  rvSdpParser_attribute_token, rvSdpParser_sdp_version_token = 88,
  rvSdpParser_origin_head_token = 90, rvSdpParser_origin_body_token,
  rvSdpParser_username_token = 93, rvSdpParser_sess_id_token,
  rvSdpParser_sess_version_token, rvSdpParser_net_type_addr_token,
  rvSdpParser_session_body_token = 99,
  rvSdpParser_information_body_token = 104, rvSdpParser_uri_token = 109,
  rvSdpParser_email_header_token, rvSdpParser_email_body_token,
  rvSdpParser_email_address_token = 113, rvSdpParser_phone_header_token,
  rvSdpParser_phone_body_token, rvSdpParser_phone_number_token = 117,
  rvSdpParser_other_addr_type_token = 122, rvSdpParser_other_addr_all_token,
  rvSdpParser_nsap_addr_all_token = 129,
  rvSdpParser_e164_addr_all_token = 131,
  rvSdpParser_alias_addr_all_token = 133,
  rvSdpParser_addrtype_str_token = 135, rvSdpParser_any_addr_token,
  rvSdpParser_ip4_addr_all_token = 138,
  rvSdpParser_ip6_addr_all_token = 140, rvSdpParser_tn_addr_all_token = 142,
  rvSdpParser_tn_other_type_token, rvSdpParser_tn_other_all_token,
  rvSdpParser_nettype_str_token, rvSdpParser_nsap_str_token = 147,
  rvSdpParser_e164_str_token, rvSdpParser_alias_str_token,
  rvSdpParser_other_str_token, rvSdpParser_ip4_str_token,
  rvSdpParser_ip6_str_token, rvSdpParser_tn_str_token,
  rvSdpParser_tnothertype_token, rvSdpParser_xalpha_token,
  rvSdpParser_bwtype_token = 165, rvSdpParser_bandwidth_token,
  rvSdpParser_time_description_token = 169,
  rvSdpParser_zone_adjustments_token = 171,
  rvSdpParser_session_time_token = 174,
  rvSdpParser_repeat_lines_token = 176, rvSdpParser_repeat_line_token = 178,
  rvSdpParser_repeat_fields_token, rvSdpParser_start_time_token = 182,
  rvSdpParser_stop_time_token, rvSdpParser_repeat_interval_token = 186,
  rvSdpParser_active_duration_token, rvSdpParser_time_offset_token,
  rvSdpParser_typed_time_token = 191,
  rvSdpParser_zone_adjustment_token = 193, rvSdpParser_time_token = 197,
  rvSdpParser_sdp_key_token = 200, rvSdpParser_key_type_token = 202,
  rvSdpParser_key_data_token, rvSdpParser_EMAIL_SAFE_token,
  rvSdpParser_attribute_body_token = 210, rvSdpParser_rtpmap_token,
  rvSdpParser_sendmode_token, rvSdpParser_att_field_token,
  rvSdpParser_att_value_token, rvSdpParser_rtpmapbody_token = 219,
  rvSdpParser_payload_type_token, rvSdpParser_encoding_name_token,
  rvSdpParser_clock_rate_token = 223, rvSdpParser_enc_params_token = 225,
  rvSdpParser_ALPHA_NUMERIC_token = 236, rvSdpParser_media_line_token = 238,
  rvSdpParser_media_fields_token = 241, rvSdpParser_media_body_token = 253,
  rvSdpParser_media_data_token, rvSdpParser_format_list_token,
  rvSdpParser_media_data_nas_token = 257, rvSdpParser_media_token = 259,
  rvSdpParser_port_token, rvSdpParser_subport_token,
  rvSdpParser_proto_token, rvSdpParser_ex_port_token,
  rvSdpParser_nas_access_method_token = 265, rvSdpParser_fmt_token,
  rvSdpParser_vcId_token = 272, rvSdpParser_ALPHA_NUMERIC_ATM_token,
  rvSdpParser_known_transport_proto_token = 278,
  rvSdpParser_ANY_BYTE_NO_SPACE_token,
  rvSdpParser_byte_string_before_colon_token,
  rvSdpParser_hexstring_token = 285, rvSdpParser_HEX_token,
  rvSdpParser_integerstring_token = 288,
  rvSdpParser_ip4_connection_address_token, rvSdpParser_addr_token,
  rvSdpParser_ip4_multicast_address_token,
  rvSdpParser_ip6_connection_address_token,
  rvSdpParser_multicast_ipv6_hexpart_token, rvSdpParser_IP6_address_token,
  rvSdpParser_partial_IP4_address_token, rvSdpParser_hexseq_token,
  rvSdpParser_hex1to4_token, rvSdpParser_hex2_token = 301,
  rvSdpParser_ipv6_suffix_token = 303,
  rvSdpParser_multicast_ipv6_prefix_token = 307,
  rvSdpParser_unicast_ipv6_prefix_alpha_token = 309,
  rvSdpParser_unicast_ipv6_prefix_token = 312,
  rvSdpParser_unicast_ipv6_suffix_token, rvSdpParser_ttl_token = 315,
  rvSdpParser_num_of_addr_token, rvSdpParser_DIGIT9_token = 319,
  rvSdpParser_number_token = 321, rvSdpParser_fixed_len_time_unit_token,
  rvSdpParser_email_token = 331, rvSdpParser_local_part_token,
  rvSdpParser_domain_token = 334, rvSdpParser_word_token,
  rvSdpParser_sub_domain_token = 340, rvSdpParser_domain_ref_token = 344,
  rvSdpParser_domain_literal_token, rvSdpParser_atom_token,
  rvSdpParser_quoted_string_token, rvSdpParser_EMAIL_ATOM_ONLY_token,
  rvSdpParser_dtext_token = 353, rvSdpParser_quoted_pair_token,
  rvSdpParser_CHAR_token = 362, rvSdpParser_qtext_token = 364,
  rvSdpParser_scheme_token = 368, rvSdpParser_path_token = 370,
  rvSdpParser_search_token = 372, rvSdpParser_ialpha_token = 374,
  rvSdpParser_void_token, rvSdpParser_xpalphas_token = 377,
  rvSdpParser_URI_SAFE_token = 380, rvSdpParser_URI_EXTRA_token,
  rvSdpParser_uri_escape_token, rvSdpParser_ALPHA_token,
  rvSdpParser_phone_token = 388, rvSdpParser_FQDN_token = 394,
  rvSdpParser_hex4_token = 396, rvSdpParser_aliasstr_token,
  rvSdpParser_otherstr_token = 399, rvSdpParser_global_tnaddr_token = 401,
  rvSdpParser_local_tnaddr_token, rvSdpParser_ex_vcci_token = 414,
  rvSdpParser_ex_cid_token, rvSdpParser_ex_bcg_token,
  rvSdpParser_ex_portid_token, rvSdpParser_ex_vpi_token,
  rvSdpParser_ex_vci_token, rvSdpParser_ex_vpci_token,
  rvSdpParser_atm_type_addr_m_token, rvSdpParser_genericU16_token = 423,
  rvSdpParser_genericU8_token = 425, rvSdpParser_genericU32_token = 428,
  rvSdpParser_genericU12_token = 430,
  rvSdpParser_transport_list_token = 455
} rvSdpParser_token_type;

typedef struct rvSdpParser_pcb_struct{
  rvSdpParser_token_type token_number, reduction_token, error_frame_token;
  int input_code;
  int input_value;
  int line, column;
  int ssx, sn, error_frame_ssx;
  int drt, dssx, dsn;
  int ss[43];
  rvSdpParser_vs_type vs[43];
  int ag_ap;
  char *error_message;
  char read_flag;
  char exit_flag;
  int bts[43], btsx;
  unsigned char * pointer;
  unsigned char * la_ptr;
  const unsigned char *key_sp;
  int save_index, key_state;
  char ag_msg[82];
/*  Line 106, D:/dev/RVSDP/SDP/rvsdp/sdpparser/rvsdpprs_NoBadSyntax.syn */
					    
	RvSdpMsg * sdp_msg;
	RvSdpParserState_ sdp_prs_state;




  } rvSdpParser_pcb_type;

#ifndef PRULE_CONTEXT
#define PRULE_CONTEXT(pcb)  (&((pcb).cs[(pcb).ssx]))
#define PERROR_CONTEXT(pcb) ((pcb).cs[(pcb).error_frame_ssx])
#define PCONTEXT(pcb)       ((pcb).cs[(pcb).ssx])
#endif

#ifndef AG_RUNNING_CODE_CODE
/* PCB.exit_flag values */
#define AG_RUNNING_CODE         0
#define AG_SUCCESS_CODE         1
#define AG_SYNTAX_ERROR_CODE    2
#define AG_REDUCTION_ERROR_CODE 3
#define AG_STACK_ERROR_CODE     4
#define AG_SEMANTIC_ERROR_CODE  5
#endif
void init_rvSdpParser(rvSdpParser_pcb_type *);
void rvSdpParser(rvSdpParser_pcb_type *);
#endif

