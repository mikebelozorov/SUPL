/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "RRLP-Messages"
 * 	found in "../rrlp-messages.asn"
 */

#include "RRLP-Component.h"

static asn_per_constraints_t asn_PER_type_RRLP_Component_constr_1 = {
	{ APC_CONSTRAINED | APC_EXTENSIBLE,  3,  3,  0,  4 }	/* (0..4,...) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_RRLP_Component_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct RRLP_Component, choice.msrPositionReq),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MsrPosition_Req,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"msrPositionReq"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct RRLP_Component, choice.msrPositionRsp),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MsrPosition_Rsp,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"msrPositionRsp"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct RRLP_Component, choice.assistanceData),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_AssistanceData,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"assistanceData"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct RRLP_Component, choice.assistanceDataAck),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NULL,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"assistanceDataAck"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct RRLP_Component, choice.protocolError),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ProtocolError,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"protocolError"
		},
};
static asn_TYPE_tag2member_t asn_MAP_RRLP_Component_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* msrPositionReq at 21 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* msrPositionRsp at 22 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* assistanceData at 23 */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* assistanceDataAck at 24 */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 } /* protocolError at 25 */
};
static asn_CHOICE_specifics_t asn_SPC_RRLP_Component_specs_1 = {
	sizeof(struct RRLP_Component),
	offsetof(struct RRLP_Component, _asn_ctx),
	offsetof(struct RRLP_Component, present),
	sizeof(((struct RRLP_Component *)0)->present),
	asn_MAP_RRLP_Component_tag2el_1,
	5,	/* Count of tags in the map */
	0,
	5	/* Extensions start */
};
asn_TYPE_descriptor_t asn_DEF_RRLP_Component = {
	"RRLP-Component",
	"RRLP-Component",
	CHOICE_free,
	CHOICE_print,
	CHOICE_constraint,
	CHOICE_decode_ber,
	CHOICE_encode_der,
	CHOICE_decode_xer,
	CHOICE_encode_xer,
	CHOICE_decode_uper,
	CHOICE_encode_uper,
	CHOICE_outmost_tag,
	0,	/* No effective tags (pointer) */
	0,	/* No effective tags (count) */
	0,	/* No tags (pointer) */
	0,	/* No tags (count) */
	&asn_PER_type_RRLP_Component_constr_1,
	asn_MBR_RRLP_Component_1,
	5,	/* Elements count */
	&asn_SPC_RRLP_Component_specs_1	/* Additional specs */
};

