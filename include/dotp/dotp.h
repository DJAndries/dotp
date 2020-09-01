#ifndef DOTP_DOTP_H
#define DOTP_DOTP_H

#include <stdint.h>
#include <stdlib.h>

int dotp_hotp_value(char* dest, char* key, size_t key_size, uint64_t counter, size_t ndigits);

int dotp_totp_value(char* dest, char* key, size_t key_size,
	size_t duration_len, size_t ndigits);

void dotp_b32_encode(char* dest, char* src, size_t src_size);

int dotp_b32_decode(char* dest, size_t* result_size, char* src);

#endif
