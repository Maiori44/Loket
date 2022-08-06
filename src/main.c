#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int gargc;
char **gargv;
char *getarg(int n, char *msg);

int main(int argc, char *argv[]) {
	gargc = argc;
	gargv = argv;
	char *mode = getarg(1, "Insert mode: (encrypt/decrypt)");
	char *path = getarg(2, "Insert path:");
	char *key  = getarg(3, "Insert key:");
	//printf("Mode: %s\nPath: %s\nKey:  %s\n", mode, path, key);
	free(mode);
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
