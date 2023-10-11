#ifndef DILITHIUM_API_H
#define DILITHIUM_API_H

#ifdef __cplusplus
extern "C" {
#endif

#define DILITHIUM_PUBLICKEYBYTES 1952
#define DILITHIUM_SECRETKEYBYTES 4016
#define DILITHIUM_BYTES 3293

#define DILITHIUM_NAMESPACE(s) pqcrystals_dilithium3_ref##s


#define crypto_sign_keypair DILITHIUM_NAMESPACE(_keypair)
int crypto_sign_keypair(unsigned char *pk, unsigned char *sk);

#define crypto_sign DILITHIUM_NAMESPACE()
int crypto_sign(unsigned char *sm, unsigned long long *smlen,
                const unsigned char *msg, unsigned long long len,
                const unsigned char *sk);

#define crypto_sign_open DILITHIUM_NAMESPACE(_open)
int crypto_sign_open(unsigned char *m, unsigned long long *mlen,
                     const unsigned char *sm, unsigned long long smlen,
                     const unsigned char *pk);


#ifdef __cplusplus
}
#endif

#endif //DILITHIUM_API_H

