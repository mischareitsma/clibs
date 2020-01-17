#ifndef __CRYPTO_GTM__
#define __CRYPOT_GTM__

#include "gtmxc_types.h"

void gtm_encrypt(int count, gtm_string_t *key, gtm_string_t *input,
			gtm_string_t *result);

void gtm_decrypt(int count, gtm_string_t *key, gtm_string_t *input,
			gtm_string_t *output);

void gtm_sign(int count, gtm_string_t *key, gtm_string_t *input,
			gtm_string_t *signature);

gtm_int_t gtm_verify(int count, gtm_string_t *key, gtm_string_t *input,
			gtm_string_t *signature);

#endif
