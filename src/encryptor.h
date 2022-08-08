#include <string.h>
#include "dynstack.h"

void encryptfile(dynstack *chars, dynstack *fullkey, char *path);
void decryptfile(dynstack *chars, dynstack *fullkey, char *path, size_t pathlen);