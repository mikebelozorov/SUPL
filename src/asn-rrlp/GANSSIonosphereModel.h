/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "RRLP-Components"
 * 	found in "../rrlp-components.asn"
 */

#ifndef	_GANSSIonosphereModel_H_
#define	_GANSSIonosphereModel_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeInteger.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* GANSSIonosphereModel */
typedef struct GANSSIonosphereModel {
	long	 ai0;
	long	 ai1;
	long	 ai2;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} GANSSIonosphereModel_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_GANSSIonosphereModel;

#ifdef __cplusplus
}
#endif

#endif	/* _GANSSIonosphereModel_H_ */
#include <asn_internal.h>
