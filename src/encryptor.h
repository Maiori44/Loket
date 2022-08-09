#include <stdint.h>
#include <string.h>
#include "dynstack.h"

void encryptfile(dynstack *chars, dynstack *fullkey, uint16_t checksum, char *path);
void decryptfile(dynstack *chars, dynstack *fullkey, uint16_t checksum, char *path, size_t pathlen);