#include "shell.h"

/**
 * custom_env - prints the current environment
 * @env: array of environment variables
 */
int env_builtin(char **env)
{
	int i = 0;

	while (env[i] != NULL)
	{
		_puts(env[i]);
		_putchar('\n');
		i++;
	}
}

#define READ_SIZE 1024

/**
 * _getline - Read a line of input from stdin.
 * Return: Pointer to the input line (which should be freed),
 * or NULL on EOF or error.
 */
char *_getline(void)
{
	char buffer[READ_SIZE + 1];
	char *pos;
	int bytes_left = 0;
	char *line = NULL;
	int n = 0;

	/* Read more input into buffer if necessary. */
	if (bytes_left <= 0)
	{
		n = read(STDIN_FILENO, buffer, READ_SIZE);
		if (n <= 0)
		{
			return (NULL);
		}
		pos = buffer;
		bytes_left = n;
	}

	/* Find the end of the current line (if there is one). */
	char *newline_pos;
	int i;

	newline_pos = NULL;
	for (i = 0; i < bytes_left; i++)
	{
		if (pos[i] == '\n')
		{
			newline_pos = pos + i;
			break;
		}
	}

	/* If a newline, extract  the line and update the buffer. */
	if (newline_pos != NULL)
	{
		/* Allocate memory for the line. */
		line = malloc((newline_pos - pos + 1) * sizeof(char));
		if (line == NULL)
		{
			return (NULL);
		}
		/* Copy the line from the buffer to the line array. */
		int i;

		for (i = 0; i < newline_pos - pos; i++)
		{
			line[i] = pos[i];
		}
		line[newline_pos - pos] = '\0';
		pos = newline_pos + 1;
		bytes_left -= (newline_pos - pos + 1);
	}
	/* If we didn't find a newline,
	 * return NULL to indicate incomplete input. */
	else
	{
		return (NULL);
	}

	return (line);

	/**
	 * setenv_builtin - Initialize a new environment variable or modify an existing one
	 * @argv: The argument vector passed to the command
	 *
	 * Return: Always returns 1, to continue executing the shell loop
	 */
	int setenv_builtin(char **argv)
	{
		if (argv[1] == NULL || argv[2] == NULL)
		{
			fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
			return (1);
		}

		if (setenv(argv[1], argv[2], 1) == -1)
		{
			perror("setenv");
		}

		return (1);
	}

	/**
	 * unsetenv_builtin - Remove an environment variable
	 * @argv: The argument vector passed to the command
	 *
	 * Return: Always returns 1, to continue executing the shell loop
	 */
	int unsetenv_builtin(char **argv)
	{
		if (argv[1] == NULL)
		{
			fprintf(stderr, "Usage: unsetenv VARIABLE\n");
			return (1);
		}

		if (unsetenv(argv[1]) == -1)
		{
			perror("unsetenv");
		}

		return (1);
	}
}
