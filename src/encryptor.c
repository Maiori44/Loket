#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "dynstack.h"
#include "encryptor.h"

void encryptfile(dynstack *chars, dynstack *fullkey, uint16_t checksum, char *path) {
	uint8_t kc1 = (checksum & 0xFF) + fullkey->stack[0];
	uint8_t kc2 = (checksum >> 8) + fullkey->stack[1];
	ITERATE_STACK(chars)
		chars->stack[i] += popstack(fullkey) + checksum;
	pushstack(chars, kc1);
	pushstack(chars, kc2);
	strcat(path, ".lok");
}

void decryptfile(dynstack *chars, dynstack *fullkey, uint16_t checksum, char *path, size_t pathlen) {
	uint8_t kc2 = popstack(chars) - fullkey->stack[1];
	uint8_t kc1 = popstack(chars) - fullkey->stack[0];
	if (checksum != ((kc2 << 8) | kc1)) {
		puts("Incorrect key!");
		freestack(chars);
		freestack(fullkey);
		free(path);
		exit(1);
	}
	popstack(fullkey);
	popstack(fullkey);
	ITERATE_STACK(chars)
		chars->stack[i] = (chars->stack[i] - popstack(fullkey)) - checksum;
	path[pathlen - 4] = '\0';
}