#include "dotp/dotp.h"
#include <time.h>

int dotp_totp_value(char* dest, char* key, size_t key_size,
	size_t duration_len, size_t ndigits) {

	uint64_t counter = (uint64_t)time(0) / duration_len;
	
	return dotp_hotp_value(dest, key, key_size, counter, ndigits);
}
