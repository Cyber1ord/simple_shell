#include "shell.h"

/**
 *main - Basic shell project
 *
 *
 *Return:  return 0 (success)
 */
int main(void)
{
	char *pathbuffer = NULL;
	char *copy = NULL;
	char *buffer = NULL;
	char *PATH = NULL;
	char **argv = NULL;
	int exitstatus = 0;

	signal(SIGINT, SIG_IGN);
	PATH = _getenv("PATH");
	if (PATH == NULL)
		return (EXIT_FAILURE);
	while (1)
	{
		prompt();
		buffer = _read();
		if (*buffer != '\0')
		{
			char **cmds = _strtoken(buffer, ";");
			if (cmds == NULL)
			{
				free(buffer);
				continue;
			}
			int i = 0, exec_next = 1;
			while (cmds[i] != NULL)
			{
				char **argv = _strtoken(cmds[i], " ");
				if (argv == NULL)
				{
					free(cmds[i]);
					i++;
					continue;
				}
				pathbuffer = _pathbuffer(argv, PATH, copy);
				if (strcmp(argv[0], "cd") == 0)
				{
					if (cd_builtin(argv[1]) == -1)
						fprintf(stderr, "cd: can't cd to %s\n", argv[1]);
					else
						setenv("PWD", getcwd(NULL, 0), 1);
					free(argv);
					free(cmds[i]);
					i++;
					continue;
				}
				if (checkbuiltins(argv, buffer, exitstatus) == 1)
				{
					free(argv);
					free(cmds[i]);
					i++;
					continue;
				}
				if (exec_next == 1)
					exitstatus = _forkprocess(argv, buffer, pathbuffer);
				if (strcmp(argv[_strlen(argv) - 1], "&&") == 0)
				{
					if (exitstatus == 0)
						exec_next = 1;
					else
						exec_next = 0;
				}
				else if (strcmp(argv[_strlen(argv) - 1], "||") == 0)
				{
					if (exitstatus != 0)
						exec_next = 1;
					else
						exec_next = 0;
				}
				else
					exec_next = 1;
				free(argv);
				free(cmds[i]);
				i++;
			}
			free(cmds);
		}
		else
			free(buffer);
	}

