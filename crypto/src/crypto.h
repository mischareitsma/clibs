#ifndef _CRYPTO_H_
#define _CRYPTO_H_

#include <stddef.h>

/* Encrypt, decrypt, sign, verify

Wrappers around OpenSSL implementation of RSA cryptographic functions.

All functions except verify have the following format:

size_t function(key_content, char **result, char *input, size_t input_size);

Where the return size_t gives the size of the result.

function | type of key | input           | output
-------- | ----------- | --------------- | ------
encrypt  | public key  | plain text      | encyrpted bytes
decrypt  | private key | encrypted bytes | plain text
sign     | private key | plain text      | signature on text

The verify method will return an integer depending on the status of the
verification.
*/

size_t crypto_encrypt(char *key, char **result, char *input, size_t input_size);
size_t crypto_decrypt(char *key, char **result, char *input, size_t input_size);

size_t crypto_sign(char *key, char **signature, char *input, size_t input_size);
int crypto_verify(char *key, char *signature, size_t signature_size,
		  char *input, size_t input_size);

#endif