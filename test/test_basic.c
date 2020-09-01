#include <stdio.h>
#include "dotp/dotp.h"

int main() {
    size_t i;
    char key[128];
    char code[10];
    size_t key_len;

    if (dotp_b32_decode(key, &key_len, "QVSPZOAOHXQE3MR4")) {
	perror("Failed to decode key");
	return 1;
    }

    if (dotp_totp_value(code, key, key_len, 30, 6)) {
	perror("Failed to generate value");
	return 2;
    }

    printf("Key: ");
    for (i = 0; i < key_len; i++) {
	printf("%x ", key[i] & 0xFF);
    }

    printf("\nKey size: %lu bytes, %lu bits\n", key_len, key_len * 8);

    printf("%s\n", code);

    return 0;
}
