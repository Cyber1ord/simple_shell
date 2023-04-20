#include "rj-headers.h"

#define BUFFER_SIZE 1024

/**
 * cd - changes to the directory given by the user or the parent directory
 *
 * @info: data relevant (environ)
 *
 * Return: no return
 */

void get_error(char *msg, int exit_status) {
	fprintf(stderr, "%s\n", msg);
	exit(exit_status);
}

void cd(int argc, char **argv) {
	char *dir;
	if (argc < 2) {
		dir = getenv("HOME");
		if (dir == NULL) {
			get_error("cd: HOME environment variable not set", 1);
		}
	} else {
		dir = malloc(BUFFER_SIZE * sizeof(char));
		strcpy(dir, argv[1]);
	}
	int ret = chdir(dir);
	if (ret != 0) {
		get_error("cd: failed to change directory", 1);
	}
	free(dir);
}

int main(int argc, char **argv) {
	cd(argc, argv);
	return 0;
}

