#include <string.h>
#include "dynstack.h"
#include "encryptor.h"

void encryptfile(dynstack *chars, dynstack *fullkey, int checksum, char *path) {
	ITERATE_STACK(chars)
		chars->stack[i] += popstack(fullkey);
	strcat(path, ".lok");
}

void decryptfile(dynstack *chars, dynstack *fullkey, int checksum, char *path, size_t pathlen) {
	ITERATE_STACK(chars)
		chars->stack[i] -= popstack(fullkey);
	path[pathlen - 4] = '\0';
}