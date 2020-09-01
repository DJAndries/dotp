#include "dotp/dotp.h"

static const char base32map[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";

void dotp_b32_encode(char* dest, char* src, size_t src_size) {
	size_t si, di, bits_loaded;
	int buffer = 0;

	bits_loaded = di = 0;
	for (si = 0; si < src_size; si++) {
		buffer <<= 8;
		buffer |= src[si];
		bits_loaded += 8;

		while (bits_loaded / 5) {
			dest[di++] = base32map[(buffer >> (bits_loaded - 5)) & 0x1F];
			bits_loaded -= 5;
		}
	}

	if (bits_loaded)
		dest[di++] = base32map[(buffer << (5 - bits_loaded)) & 0x1F]; 

	while (di % 8) dest[di++] = '=';
	dest[di] = 0;
}

int dotp_b32_decode(char* dest, size_t* result_size, char* src) {
	size_t si, di, bits_loaded;
	char val;
	int buffer = 0;

	bits_loaded = di = 0;
	for (si = 0; src[si] != 0; si++) {
		val = src[si];
		if (val >= 'A' && val <= 'Z') {
				val -= 'A';
		} else if (val >= '2' && val <= '7') {
				val -= '2' - 26;
		} else if (src[si] == '=') {
				continue;
		} else {
				return 1;
		}
		buffer <<= 5; 
		buffer |= val;
		bits_loaded += 5;

		while (bits_loaded / 8) {
				dest[di++] = (buffer >> (bits_loaded - 8)) & 0xFF;
				bits_loaded -= 8;
		}
	}

	*result_size = di;
	return 0;
}
