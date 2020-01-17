#ifndef _RSACRYPTO_H_
#define _RSACRYPTO_H_

#include <stdbool.h>
#include <stddef.h>

// TODO: Docs?

size_t encrypt(const unsigned char *key, const unsigned char *input,
			const size_t input_size, unsigned char *result);
			
size_t decrypt(const unsigned char *key, const unsigned char *input,
			const size_t input_size, unsigned char *result);

size_t sign(const unsigned char *key, const unsigned char *input,
			const size_t input_size, unsigned char *signature);

bool verify(const unsigned char *key, const unsigned char *signature,
			const size_t signature_size, const unsigned char *input,
			const size_t input_size);

#endif
