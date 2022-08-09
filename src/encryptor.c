#include <stdint.h>
#include <string.h>
#include "dynstack.h"
#include "encryptor.h"

void encryptfile(dynstack *chars, dynstack *fullkey, uint16_t checksum, char *path) {
	int kc1 = fullkey->stack[0], kc2 = fullkey->stack[1];
	ITERATE_STACK(chars)
		chars->stack[i] += popstack(fullkey);
	strcat(path, ".lok");
}

void decryptfile(dynstack *chars, dynstack *fullkey, uint16_t checksum, char *path, size_t pathlen) {
	ITERATE_STACK(chars)
		chars->stack[i] -= popstack(fullkey);
	path[pathlen - 4] = '\0';
}