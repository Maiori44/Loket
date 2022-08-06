#ifndef ENCRYPTOR
#define ENCRYPTOR

#include <stdlib.h>
#include "dynstack.h"

void encryptfile(char *path, dynstack *chars, size_t pathlen);
void decryptfile(char *path, dynstack *chars, size_t pathlen);

#endif