#include "shell.h"

/**
 *main - Basic shell project
 *@argv: arguement variable
 *@argc: arguement counter
 *Return:  return 0 (success)
 */

int main(int argc, char **argv)
{
	char *buffer = NULL;
	char **argv_list = NULL;
	char *pathbuffer = NULL;
	int exitstatus = 0;
	size_t copy = 0;
	FILE *fp = NULL;

	if (argc == 2)
		fp = fopen(argv[1], "r");

	while (fp ? getline(&buffer, &copy, fp) != -1 : 1)
	{
		if (fp)
			buffer[strlen(buffer) - 1] = '\0';

		if (strcmp(buffer, "history\n") == 0)
		{
			print_history();
			continue;
		}

		if (buffer[0] == '!')
		{
			int n;
			char *cmd;

			n = atoi(&buffer[1]);
			cmd = get_command_from_history(n);
			if (cmd == NULL)
			{
				printf("No such command in history\n");
				continue;
			}
			strcpy(buffer, cmd);
			printf("%s\n", buffer);
		}

		add_to_history(buffer);

		argv_list = _strtoken(buffer, " \t\n");
		if (!argv_list)
			continue;

		if (argv_list[0][0] == '#')
		{
			free(argv_list);
			continue;
		}

		if (strcmp(argv_list[0], "cd") == 0)
		{
			if (checkbuiltins(argv_list[1]) == -1)
				fprintf(stderr, "cd: can't cd to %s\n", argv_list[1]);
			else
				setenv("PWD", getcwd(NULL, 0), 1);

			free(argv_list);
			continue;
		}

		if (strcmp(argv_list[0], "exit") == 0)
		{
			if (argv_list[1])
				exitstatus = _atoi(argv_list[1]);
			else
				exitstatus = 0;

			free(argv_list);
			break;
		}

		if (checkbuiltins(argv_list, buffer, &exitstatus) == -1)
		{
			free(argv_list);
			continue;
		}

		pathbuffer = _pathbuffer(argv_list, PATH, copy);
		exitstatus = _forkprocess(argv_list, buffer, pathbuffer);

		free(pathbuffer);
		free(argv_list);
	}

	if (fp)
		free(buffer);

	exit_shell(exitstatus);
	return (EXIT_SUCCESS);
}
