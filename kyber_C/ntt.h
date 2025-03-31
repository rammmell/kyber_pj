#ifndef NTT_H
#define NTT_H

#include <stdint.h>

void ntt(uint16_t *a, uint16_t *twiddles);

void invntt(uint16_t *a, uint16_t *twiddles_inv);

#endif
