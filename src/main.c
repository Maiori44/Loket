#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "dynstack.h"

int gargc;
char **gargv;
char *getarg(int n, char *msg);

int main(int argc, char *argv[]) {
	//Check for -V or --version
	if (argc >= 2 && (memcmp(argv[1], "-V", 2) || memcmp(argv[1], "--version", 9))) {
		puts("loket 1.0.0");
		return 0;
	}

	//Get path and key
	gargc = argc;
	gargv = argv;
	char *path = getarg(1, "Insert path:");
	char *key = getarg(2, "Insert key:");
	size_t pathlen = strlen(path);
	bool decrypt = pathlen >= 4 && memcmp(path + pathlen - 4, ".lok", 4) == 0;

	//Read file
	FILE *file = fopen(path, "r");
	if (!file) {
		puts("File not found!");
		return 1;
	}
	fseek(file, 0L, SEEK_END);
	int size = ftell(file);
	rewind(file);
	dynstack *chars = newstack(size);
	int c;
	while ((c = fgetc(file)) != EOF)
		pushstack(chars, c);
	fclose(file);

	//Create full key
	dynstack *fullkey = newstack(size);
	size_t keylen = strlen(key);
	int m = decrypt ? -1 : 1;
	for (int i = 0; i <= size; i++)
		pushstack(fullkey, key[i % keylen] * m);

	//Encrypt/decrypt and save
	ITERATE_STACK(chars)
		chars->stack[i] += popstack(fullkey);
	if (decrypt)
		path[pathlen - 4] = '\0';
	else
		strcat(path, ".lok");
	FILE *output = fopen(path, "w+");
	ITERATE_STACK(chars)
		fprintf(output, "%c", chars->stack[i]);
	fclose(output);

	//Free allocated memory
	freestack(chars);
	freestack(fullkey);
	free(path);
	free(key);
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
		exit(1);
	}
	return result;
}
