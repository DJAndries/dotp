#include "dotp/dotp.h"
#include <math.h>
#include <string.h>
#include <openssl/hmac.h>
#include <openssl/evp.h>

static unsigned int sha1_truncate(unsigned char* hash, size_t ndigits) {
	size_t start_index = hash[19] & 0x0F;
	unsigned int result = (hash[start_index + 3] & 0xFF) |
		(hash[start_index + 2] & 0xFF) << 8 | (hash[start_index + 1] & 0xFF) << 16 | 
		(hash[start_index] & 0xFF) << 24;
	return (result & 0x7FFFFFFF) % (unsigned int)pow(10, ndigits);
}

int dotp_hotp_value(char* dest, char* key, size_t key_size,
		uint64_t counter, size_t ndigits) {
	size_t i;
	unsigned char hash[20];
	unsigned char data[8];

	for (i = 0; i < 8; i++) {
		data[i] = (counter >> (56 - (i * 8))) & 0xFF;
	}

	if (HMAC(EVP_sha1(), key, key_size, data, 8,
		hash, 0) == 0) {
		return 1;
	}

	sprintf(dest, "%0*u", (int)ndigits, sha1_truncate(hash, ndigits));

	return 0;
}
