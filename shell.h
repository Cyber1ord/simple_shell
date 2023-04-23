#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/time.h>
#include <fcntl.h>
#include <errno.h>
#include <limits.h>

extern char **environ;

#define clear() printf("\033[H\033[J")
#define MAX_HISTORY 100
#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"
#define PATH_BUFSIZE 1024
#define CMD_BUFSIZE 1024

extern char **environ;

char *builtin_str[] = {
	"cd",
	"help",
	"exit",
	"env",
	"setenv",
	"unsetenv"
};


void init_shell(void);
int prompt(void);
char *_read(void);

/* program logic */


char **_strtoken(char *buffer, char *delim);
int  _forkprocess(char **argv, char *buffer, char *pathbuffer);
char *check_path(char *cmd, char *path);
void exit_shell(char *status);
int checkbuiltins(char **argv, char *buffer, int exitstatus);
int env_builtin(char **env);
char *_getline(void);
int setenv_builtin(char **argv);
int unsetenv_builtin(char **argv);
int cd_builtin(char **args);
int _strcomp(const char *s1, const char *s2, size_t n);
char *_strconcat(const char *s1, const char *s2);
void *_realloc_ptr(void *ptr, size_t old_size, size_t new_size);
size_t _strlen(const char *s);
char *_getenv(const char *name);
int _setenv(const char *name, const char *value);
void _puts(char *str);
int _putchar(char c);
void add_to_history(char *command);
void print_history();
char *get_command_from_history(int n);
char *replace_vars(char *str, int status, pid_t pid);
char *_itoa(int num);
char *_strcpy(char *dest, const char *src);
void *_memcpy(void *dest, const void *src, size_t n);
char *_strcat(char *dest, const char *src);
char *_strdup(const char *str);

#endif

