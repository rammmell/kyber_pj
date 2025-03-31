#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ntt.h"
#include "sha3.h"

int main(void)
{
    uint16_t a[256] = {0};
    uint16_t twiddles[256];
    uint16_t twiddles_inv[256];

    for (int i = 0; i < 256; i++) {
        a[i] = rand() % 3329;
    }
    printf("Original array: ");
    for (int i = 0; i < 256; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    ntt(a, twiddles);
    printf("NTT array: ");
    for (int i = 0; i < 256; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    invntt(a, twiddles_inv);
    printf("InvNTT array: ");
    for (int i = 0; i < 256; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    uint8_t input[100];
    uint8_t output[100];
    for (int i = 0; i < 100; i++) {
        input[i] = rand() % 256;
    }
    for (int i = 0; i < 100; i++) {
        printf("%d ", input[i]);
    }
    printf("\n");
    sha3_hash(output, 100, input, 100, 128, 1);
    printf("SHAKE128 output: ");
    for (int i = 0; i < 100; i++) {
        printf("%d ", output[i]);
    }
    printf("\n");


    return 0;
}
