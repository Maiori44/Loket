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
	free(mode);
	return 0;
}

char *getarg(int n, char *msg) {
	if (n < gargc)
		return gargv[n];
	else {
		puts(msg);
		char *result = malloc(sizeof(char) * 200);
		scanf(" %[^\n]%*c", result);
		size_t len;
		for (len = strlen(result); isspace(result[len - 1]); --len)
			result[len - 1] = '\0';
		if (len >= 200) {
			puts("The given text is too long!");
			exit(1);
		}
		return result;
	}
}
