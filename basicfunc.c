#include "shell.h"

/**
 * _strtoken - Splits a string into an array of tokens
 * @str: The string to split
 *
 * Return: An array of strings (tokens) or NULL on failure
 */
char **_strtoken(char *str)
{
	int bufsize = TOK_BUFSIZE;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;
	int i = 0;

	if (!tokens)
	{
		perror("malloc error");
		return (NULL);
	}

	token = strtok(str, TOK_DELIM);
	while (token != NULL)
	{
		tokens[i] = token;
		i++;

		if (i >= bufsize)
		{
			bufsize += TOK_BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				perror("realloc error");
				return (NULL);
			}
		}

		token = strtok(NULL, TOK_DELIM);
	}
	tokens[i] = NULL;

	return (tokens);
}

/**
 * _forkprocess - creates a child process to execute a command
 * @argv: double pointer containing the command and its arguments
 * @buffer: user input buffer
 * @pathbuffer: double pointer to a buffer containing directories from PATH
 *
 * Return: 1 on success, 0 on failure
 */
int _forkprocess(char **argv, char *buffer, char *pathbuffer)
{
	pid_t pid;
	char *command;

	pid = fork();
	if (pid == -1)
	{
		perror("Error: fork failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		command = check_path(argv[0], pathbuffer);
		if (command == NULL)
		{
			printf("./hsh: %d: %s: not found\n", linecount, argv[0]);
			free(pathbuffer);
			free(argv);
			free(buffer);
			exit(EXIT_SUCCESS);
		}
		if (execve(command, argv, environ) == -1)
		{
			perror("Error");
			free(pathbuffer);
			free(argv);
			free(buffer);
			exit(EXIT_FAILURE);
		}
	}
	else
		wait(NULL);
	return (1);
}

/**
 * check_path - checks if command exists in PATH directories
 * @cmd: command to search for
 * @path: colon-separated list of directories in PATH
 * Return: pointer to full path of command if found, otherwise NULL
 */
char *check_path(char *cmd, char *path)
{
	char *dir;
	char *fullpath;
	struct stat st;
	int len_cmd, len_dir;

	while ((dir = _strtok(path, ":")))
	{
		len_cmd = _strlen(cmd);
		len_dir = _strlen(dir);
		fullpath = malloc(sizeof(char) * (len_cmd + len_dir + 2));
		if (!fullpath)
			return (NULL);
		_strcpy(fullpath, dir);
		_strcat(fullpath, "/");
		_strcat(fullpath, cmd);
		if (stat(fullpath, &st) == 0)
		{
			if (S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR))
				return (fullpath);
		}
		free(fullpath);
	}
	return (NULL);
}


/**
 * exit_shell - Exits the shell
 * @status: The status to exit with
 */
void exit_shell(char *status)
{
	int exit_status = 0;

	if (status != NULL)
		exit_status = _atoi(status);

	exit(exit_status);
}


/**
 * checkbuiltins - Checks if the command is a built-in and executes it
 * @argv: The argument vector containing the command and its arguments
 * @buffer: The buffer containing the command line entered by the user
 * @exitstatus: The exit status of the previous command
 *
 * Return: 1 if the command is a built-in, 0 otherwise
 */
int checkbuiltins(char **argv, char *buffer, int exitstatus)
{
	if (_strcmp(argv[0], "exit") == 0)
	{
		free(buffer);
		free_argv(argv);
		exit_shell(exitstatus);
	}
	else if (_strcmp(argv[0], "env") == 0)
	{
		env_builtin();
	}
	else if (_strcmp(argv[0], "setenv") == 0)
	{
		setenv_builtin(argv);
	}
	else if (_strcmp(argv[0], "unsetenv") == 0)
	{
		unsetenv_builtin(argv);
	}
	else
	{
		return (0);
	}

	return (1);
}

