#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "dynstack.h"
#include "encryptor.h"

void encryptfile(dynstack *chars, dynstack *fullkey, char *path) {
	ITERATE_STACK(chars)
		chars->stack[i] += popstack(fullkey);
	strcat(path, ".lok");
}

void decryptfile(dynstack *chars, dynstack *fullkey, char *path, size_t pathlen) {
	/*if (checksum != ((kc2 << 8) | kc1)) {
		puts("Incorrect key!");
		freestack(chars);
		freestack(fullkey);
		free(path);
		exit(1);
	}*/
	ITERATE_STACK(chars)
		chars->stack[i] -= popstack(fullkey);
	path[pathlen - 4] = '\0';
}