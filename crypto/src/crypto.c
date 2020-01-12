#include "crypto.h"

#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/err.h>

#include <stdio.h>
#include <stdlib.h>

RSA *create_rsa_key(char *key, int is_public);

size_t crypto_decrypt(char *key, char **result, char *input, size_t input_size)
{
	RSA *rsa = create_rsa_key(key, 0);

	// Keysize varies, for now only support 2048
	char *decrypted = malloc(256 * sizeof(char));

	int size = RSA_private_decrypt(input_size, (unsigned char *)input,
			(unsigned char *)decrypted, rsa, RSA_PKCS1_PADDING);

	*result = decrypted;

	RSA_free(rsa);

	return size;
}

RSA *create_rsa_key(char *key, int is_public)
{
	RSA *rsa = NULL;
	BIO *keybio = BIO_new_mem_buf(key, -1);
	if (keybio == NULL ) {
		printf("Failed to create key BIO\n");
		return NULL;
	}

	// TODO: There are read methods as well, without bio, that take FILE *
	if (is_public) {
		rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa,
		NULL, NULL);
	}
	else {
		rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa,
		NULL, NULL);
	}

	if (rsa == NULL) {
		printf("Failed to create RSA\n");
	}

	return rsa;
}
