#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "dynstack.h"
#include "encryptor.h"

#define ARG(arg) memcmp(argv[1], arg, (size_t) sizeof arg) == 0

int gargc;
char **gargv;
char *getarg(int n, char *msg);

int main(int argc, char *argv[]) {
	//Check for flags
	if (argc >= 2 && argv[1][0] == '-') {
		if (ARG("-V") || ARG("--version")) {
			puts("loket 1.0-indev");
			return 0;
		} else if (ARG("-L") || ARG("--license")) {
#include "license.h"
			puts(LICENSE);
			return 0;
		}
	}

	//Get path and key
	gargc = argc;
	gargv = argv;
	char *path = getarg(1, "Insert path:");
	char *key = getarg(2, "Insert key:");
	size_t pathlen = strlen(path);

	//Read file
	FILE *file = fopen(path, "rb");
	if (!file) {
		puts("File not found!");
		free(path);
		free(key);
		return 1;
	}
	fseek(file, 0L, SEEK_END);
	int size = ftell(file);
	rewind(file);
	dynstack *chars = newstack(size + 2);
	int c;
	while ((c = fgetc(file)) != EOF)
		pushstack(chars, c);
	fclose(file);

	//Create key data
	dynstack *fullkey = newstack(size);
	size_t keylen = strlen(key);
	for (int i = 0; i <= size; i++)
		pushstack(fullkey, key[i % keylen]);
	uint16_t checksum = 0;
	for (int i = 0; i < keylen; i++)
		checksum += key[i];
	free(key);

	//Encrypt/decrypt and save
	if (pathlen >= 4 && memcmp(path + pathlen - 4, ".lok", 4) == 0)
		decryptfile(chars, fullkey, checksum, path, pathlen);
	else
		encryptfile(chars, fullkey, checksum, path);
	if (access(path, F_OK) == 0) {
		printf("Cannot save output as \"%s\" because the file already exists, overwrite? (Y/N) ", path);
		char reply;
		scanf("%c", &reply);
		if (tolower(reply) == 'n') {
			
		}
	}
	FILE *output = fopen(path, "w+b");
	ITERATE_STACK(chars)
		fprintf(output, "%c", chars->stack[i]);
	fclose(output);

	//Free allocated memory
	freestack(chars);
	freestack(fullkey);
	free(path);
	return 0;
}

char *getarg(int n, char *msg) {
	char *result = malloc(sizeof(char) * 204);
	if (n < gargc)
		strcpy(result, gargv[n]);
	else {
		puts(msg);
		scanf(" %[^\n]%*c", result);
	}
	size_t len;
	for (len = strlen(result); isspace(result[len - 1]); --len)
		result[len - 1] = '\0';
	if (len >= 200) {
		puts("The given text is too long!");
		free(result);
		exit(1);
	}
	return result;
}
