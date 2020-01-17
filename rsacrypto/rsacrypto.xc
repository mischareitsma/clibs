/home/mreitsma/Workspace/clibs/rsacrypto/lib/libgtmrsacrypto.so
encrypt: void      gtm_encrypt(I:gtm_string_t *, I:gtm_string_t *, O:gtm_string_t *[512]);
decrypt: void      gtm_decrypt(I:gtm_string_t *, I:gtm_string_t *, O:gtm_string_t *[512]);
sign:    void      gtm_sign(I:gtm_string_t *, I:gtm_string_t *, O:gtm_string_t *[512]);
verify:  gtm_int_t gtm_verify(I:gtm_string_t *, I:gtm_string_t *, I:gtm_string_t *);
