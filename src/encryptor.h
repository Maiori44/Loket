#include <string.h>
#include "dynstack.h"

void encryptfile(dynstack *chars, dynstack *fullkey, int checksum, char *path);
void decryptfile(dynstack *chars, dynstack *fullkey, int checksum, char *path, size_t pathlen);