#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/err.h>

#include "rsacrypto.h"

// TODO: Code style, patch up.
// TODO: Docs

RSA *create_rsa_key(const unsigned char *key, const bool is_public);

size_t encrypt(const unsigned char *key, const unsigned char *input,
			const size_t input_size, unsigned char *result)
{
	RSA *rsa = create_rsa_key(key, true);

	if (!rsa)
		return 0;

	int size = RSA_public_encrypt(input_size, input, result, rsa,
					RSA_PKCS1_PADDING);

	RSA_free(rsa);

	return size;
}

size_t decrypt(const unsigned char *key, const unsigned char *input,
			const size_t input_size, unsigned char *result)
{
	RSA *rsa = create_rsa_key(key, false);

	if (!rsa)
		return 0;

	int size = RSA_private_decrypt(input_size, input, result, rsa,
					RSA_PKCS1_PADDING);

	RSA_free(rsa);

	return size;
}

size_t sign(const unsigned char *key, const unsigned char *input,
			const size_t input_size, unsigned char *signature)
{
	
	RSA *rsa = create_rsa_key(key, false);
	if (!rsa)
		return 0;

	EVP_PKEY *priv_key = EVP_PKEY_new();
	EVP_PKEY_assign_RSA(priv_key, rsa);
 
	size_t sign_len = 0;
 
	// Create the Message Digest Context
	EVP_MD_CTX *mdctx = NULL;
	if (!(mdctx = EVP_MD_CTX_create()))
		goto err;
 
 	// Initialize the Message Digest Contex, use SHA256
	if (1 != EVP_DigestSignInit(mdctx, NULL, EVP_sha256(), NULL, priv_key))
		goto err;
 
	// Call update with the message which is signed
	if (1 != EVP_DigestSignUpdate(mdctx, input, input_size))
		goto err;

	/*
	 * Finalise the DigestSign operation
	 *
	 * First call EVP_DigestSignFinal with a NULL sig parameter to obtain
	 * the length of the signature. Length is returned in slen.
	 * 
	 * TODO: The signature should have enough memory allocated (256 bytes)?
	 * TODO: Is the first call actually required? Is the digest size not just 256?
	 */
	if (1 != EVP_DigestSignFinal(mdctx, NULL, &sign_len))
		goto err;
	if (1 != EVP_DigestSignFinal(mdctx, signature, &sign_len))
		goto err;

	// Label 'err' for cleanup if applicable.
	err:
	if(mdctx)
		EVP_MD_CTX_destroy(mdctx);
	if (rsa)
		RSA_free(rsa);

	return sign_len;
}

bool verify(const unsigned char *key, const unsigned char *signature,
			const size_t signature_size, const unsigned char *input,
			const size_t input_size)
{
	RSA *rsa = create_rsa_key(key, 1);
	if (!rsa)
		return false;

	EVP_PKEY *pub_key = EVP_PKEY_new();
	EVP_PKEY_assign_RSA(pub_key, rsa);

	EVP_MD_CTX *mdctx = EVP_MD_CTX_create();

	bool verified = false;

	/* Initialize `key` with a public key */
	if (1 != EVP_DigestVerifyInit(mdctx, NULL, EVP_sha256(), NULL, pub_key))
		goto err;

	/* Initialize `key` with a public key */
	if (1 != EVP_DigestVerifyUpdate(mdctx, input, input_size))
		goto err;

	if (1 == EVP_DigestVerifyFinal(mdctx, signature, signature_size))
		verified = true;

	// Label 'err' for cleanup if applicable.
	err:
	if (mdctx)
		EVP_MD_CTX_destroy(mdctx);
	if (rsa)
		RSA_free(rsa);
	
	return verified;

}

/**
 * Create an RSA struct from a public or private key.
 * 
 * @key: public or private key PEM
 * @is_public: create a public key if true, else a private key
 */
RSA *create_rsa_key(const unsigned char *key, const bool is_public)
{
	RSA *rsa = NULL;
	BIO *keybio = BIO_new_mem_buf(key, -1);

	if (!keybio)
		return NULL;

	if (is_public)
		rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa, NULL, NULL);
	else
		rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa, NULL, NULL);

	return rsa;
}
