#include <stdint.h>
#include "ntt.h"
#include "parameter.h"

const int16_t q = 3329; // 2^8*13 + 1 
const int16_t n = 256;  // 2^8
const int16_t w = 17;   // primitive root of q

//Modular Binary Exponentiation
uint16_t modexp(uint16_t base, uint16_t exp) {
    uint16_t result = 1;
    base %= KYBER_Q;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % KYBER_Q;
        base = (base * base) % KYBER_Q;
        exp >>= 1;
    }
    return result;
}

// Forward NTT (Cooley-Tukey)
void ntt(uint16_t *a, uint16_t *twiddles) {
    int len, start, j, k;

    twiddles[0] = 1;  
    uint16_t root = modexp(w, (KYBER_Q - 1) / KYBER_N);  
    for (int i = 1; i < KYBER_N; i++) {
        twiddles[i] = (twiddles[i - 1] * root) % KYBER_Q;  
    }

    for (len = 1; len < KYBER_N; len <<= 1) { 
        for (start = 0; start < KYBER_N; start += k * len) { 
            for (j = 0; j < len; j++) {  
                uint16_t u = a[start + j];  
                uint16_t v = (a[start + j + len] * twiddles[KYBER_N / (2 * len) * j]) % KYBER_Q;  

                a[start + j] = (u + v) % KYBER_Q;  
                a[start + j + len] = (u + 4 * KYBER_Q - v) % KYBER_Q;  
            }
        }
    }
}

// Inverse NTT (Gentleman-Sande)
void invntt(uint16_t *a, uint16_t *twiddles_inv) {
    int len, start, j;

    twiddles_inv[0] = 1;
    uint16_t root_inv = modexp(modexp(w, (KYBER_Q - 1) / KYBER_N), KYBER_Q - 2);  
    for (int i = 1; i < KYBER_N; i++) {
        twiddles_inv[i] = (twiddles_inv[i - 1] * root_inv) % KYBER_Q;
    }

    for (len = KYBER_N >> 1; len >= 1; len >>= 1) {  
        for (start = 0; start < KYBER_N; start += 2 * len) { 
            for (j = 0; j < len; j++) {  
                uint16_t u = a[start + j];
                uint16_t v = a[start + j + len];

                a[start + j] = (u + v) % KYBER_Q;  
                a[start + j + len] = ((u + 4 * KYBER_Q - v) * twiddles_inv[KYBER_N / (2 * len) * j]) % KYBER_Q;  
            }
        }
    }

    
    uint16_t n_inv = modexp(KYBER_N, KYBER_Q - 2);  
    for (int i = 0; i < KYBER_N; i++) {
        a[i] = (a[i] * n_inv) % KYBER_Q;
    }
}




