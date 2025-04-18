#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(x[0]))
#define INPUT "ckczppom"

// sneakly stolen from php-src :p
char* md5_to_hex(char *md5str, const unsigned char *digest, int len) {
	static const char hexits[] = "0123456789abcdef";
	int i;

	for (i = 0; i < len; i++) {
		md5str[i * 2]       = hexits[digest[i] >> 4];
		md5str[(i * 2) + 1] = hexits[digest[i] & 0x0F];
	}

	md5str[len * 2] = '\0';
}

void hash(char* data, size_t data_length, unsigned char result[EVP_MAX_MD_SIZE]) {
    const EVP_MD *md5 = EVP_md5();
    unsigned char md5_bytes[16];
    unsigned int md5_size;

    EVP_Digest((void*) data, data_length, md5_bytes, &md5_size, md5, NULL);
    md5_to_hex(result, md5_bytes, md5_size);
}

int main() {
    unsigned int count = 0;
    unsigned char result[EVP_MAX_MD_SIZE];
    unsigned char data[32];

    while(strncmp("000000", result, 6) != 0) {
        snprintf(data, ARRAY_LENGTH(data), "%s%d", INPUT, count++);
        hash(data, strlen(data), result);
    }

    printf("%d\r\n", count - 1);

    return EXIT_SUCCESS;
}
