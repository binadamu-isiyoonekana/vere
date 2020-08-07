#ifndef URCRYPT_H
#define URCRYPT_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <ed25519.h>
#include <ge-additions.h>

#include <openssl/crypto.h>
#include <openssl/aes.h>

typedef void *(*urcrypt_malloc_t)(size_t);
typedef void *(*urcrypt_realloc_t)(void*, size_t);
typedef void (*urcrypt_free_t)(void*);

int urcrypt_init(urcrypt_malloc_t, urcrypt_realloc_t, urcrypt_free_t);

void *urcrypt_malloc(size_t);
void *urcrypt_realloc(void*, size_t);
void urcrypt_free(void*);

int urcrypt_ed_point_add(const uint8_t a[32],
                         const uint8_t b[32],
                         uint8_t out[32]);
int urcrypt_ed_scalarmult(const uint8_t a[32],
                          const uint8_t b[32],
                          uint8_t out[32]);
void urcrypt_ed_scalarmult_base(const uint8_t a[32],
                                uint8_t out[32]);
int urcrypt_ed_add_scalarmult_scalarmult_base(const uint8_t a[32],
                                              const uint8_t a_point[32],
                                              const uint8_t b[32],
                                              uint8_t out[32]);
int urcrypt_ed_add_double_scalarmult(const uint8_t a[32],
                                     const uint8_t a_point[32],
                                     const uint8_t b[32],
                                     const uint8_t b_point[32],
                                     uint8_t out[32]);

void urcrypt_ed_puck(const uint8_t seed[32],
                     uint8_t out[32]);
void urcrypt_ed_shar(const uint8_t public[32],
                     const uint8_t seed[32],
                     uint8_t out[32]);
void urcrypt_ed_sign(const uint8_t *message,
                     size_t length,
                     const uint8_t seed[32],
                     uint8_t out[64]);
bool urcrypt_ed_veri(const uint8_t *message,
                     size_t length,
                     const uint8_t signature[64],
                     const uint8_t public[32]);

int urcrypt_aes_ecba_en(const uint8_t key[16],
                        const uint8_t block[16],
                        uint8_t out[16]);
int urcrypt_aes_ecba_de(const uint8_t key[16],
                        const uint8_t block[16],
                        uint8_t out[16]);
int urcrypt_aes_ecbb_en(const uint8_t key[24],
                        const uint8_t block[16],
                        uint8_t out[16]);
int urcrypt_aes_ecbb_de(const uint8_t key[24],
                        const uint8_t block[16],
                        uint8_t out[16]);
int urcrypt_aes_ecbc_en(const uint8_t key[32],
                        const uint8_t block[16],
                        uint8_t out[16]);
int urcrypt_aes_ecbc_de(const uint8_t key[32],
                        const uint8_t block[16],
                        uint8_t out[16]);

uint8_t* urcrypt_aes_cbca_en(const uint8_t *message,
                             size_t length,
                             const uint8_t key[16],
                             const uint8_t ivec[16],
                             size_t *out_length);


#endif
