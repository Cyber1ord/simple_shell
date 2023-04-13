#include "rj-headers.h"

/**
 * main - entry point for simple shell
 * @argc: argument count
 * @argv: argument vector
 * @env: environment variables
 * Authors: Adeyemo Raphael and Joseph Obi
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv, char **env)
{
	char *buffer = NULL;
	size_t bufsize = 0;
	ssize_t bytes_read;
	char *path;
	int status;
	pid_t pid;

	while (1)
	{
		argc = 0;

		printf("$ ");

		bytes_read = getline(&buffer, &bufsize, stdin);

		if (bytes_read == -1)
		{
			if (feof(stdin))
			{
				printf("\n");
				exit(EXIT_SUCCESS);
			}
			else
			{
				perror("getline");
				exit(EXIT_FAILURE);
			}
		}

		buffer[bytes_read - 1] = '\0';

		if (strcmp(buffer, "exit") == 0)
		{
			exit(EXIT_SUCCESS);
		}

		pid = fork();

		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			char *args[64];
			char *token;
			int i = 0;

			token = strtok(buffer, " ");

			while (token != NULL)
			{
				args[i++] = token;
				token = strtok(NULL, " ");
			}

			args[i] = NULL;

			if (execve(buffer, args, env) == -1)
			{
				path = getenv("PATH");

				if (path == NULL)
				{
					perror("getenv");
					exit(EXIT_FAILURE);
				}

				token = strtok(path, ":");

				while (token != NULL)
				{
					char path_buffer[128];
					sprintf(path_buffer, "%s/%s", token, buffer);

					if (execve(path_buffer, args, env) != -1)
						break;

					token = strtok(NULL, ":");
				}

				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(&status);
		}
	}

	return (0);
}
