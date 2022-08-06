#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dynstack.h"

int gargc;
char **gargv;
char *getarg(int n, char *msg);

int main(int argc, char *argv[]) {
	gargc = argc;
	gargv = argv;
	char *path = getarg(1, "Insert path:");
	char *key = getarg(2, "Insert key:");
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
	free(path);
	free(key);
	return 0;
}

char *getarg(int n, char *msg) {
	char *result = malloc(sizeof(char) * 200);
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
