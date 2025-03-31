#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ind_cpa.h"
#include "parameter.h"
#include "randombytes.h"
#include "sha3.h"

uint16_t compress_poly(uint16_t *a, uint16_t b)
{
    for (int i = 0; i < KYBER_N; i++) {
        a[i] = round(a[i] * pow(2, b) / KYBER_Q) % pow(2, b);
    }
    return a;
}

uint16_t decompress_poly(uint16_t *a, uint16_t b)
{
    for (int i = 0; i < KYBER_N; i++) {
        a[i] = round(a[i] * KYBER_Q / pow(2, b));
    }
    return a;
}

uint16_t indcpa_keygen(void)
{
    uint16_t rho[256];
    uint16_t sigma[256];
    randombytes(rho, 256);
    randombytes(sigma, 256);

    uint16_t *A[2][2];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            sha3_hash(A[i][j], 256, rho, 256, SHAKE128, USE_SHAKE);
        }
    }
    return 0;
}

uint16_t indcpa_enc(uint16_t *pk, uint16_t *m)
{
    int i;
    for (i = 0; i < 100; i++) {
        printf("%d ", i);
    }
    return 0;
}

uint16_t indcpa_dec(uint16_t *sk, uint16_t *c)
{
    int i;
    for (i = 0; i < 100; i++) {
        printf("%d ", i);
    }
    return 0;
}