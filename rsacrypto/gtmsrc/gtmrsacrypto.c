#include "gtmxc_types.h"
#include "rsacrypto.h"
#include <stdio.h>


void gtm_encrypt(int count, gtm_string_t *key, gtm_string_t *input,
			gtm_string_t *result)
{
	result->length = rc_encrypt((unsigned char *)key->address,
			(unsigned char *)input->address, input->length,
			(unsigned char *)result->address);
}

void gtm_decrypt(int count, gtm_string_t *key, gtm_string_t *input,
			gtm_string_t *result)
{
	result->length = rc_decrypt((unsigned char *)key->address,
			(unsigned char *)input->address, input->length,
			(unsigned char *)result->address);
}

void gtm_sign(int count, gtm_string_t *key, gtm_string_t *input,
			gtm_string_t *signature)
{
	signature->length = rc_sign((unsigned char *)key->address,
			(unsigned char *)input->address, input->length,
			(unsigned char *)signature->address);
}

gtm_int_t gtm_verify(int count, gtm_string_t *key, gtm_string_t *input,
			gtm_string_t *signature)
{
	return rc_verify((unsigned char *)key->address,
			(unsigned char *)signature->address, signature->length,
			(unsigned char *)input->address, input->length);
}
