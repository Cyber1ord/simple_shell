#include "rj-headers.h"

/**
 * _myexit - Exit the shell with a given status code
 * @info: Pointer to a struct containing shell information
 *
 * Return: Always returns -2 to indicate that the shell should exit
 */

int _myexit(info_t *info)
{
	int exitcode = 0;

	if (info->argv[1] != NULL) /* If there is an exit argument */
	{
		exitcode = atoi(info->argv[1]); /* Convert argument to integer */
		if (exitcode == 0 && strcmp(info->argv[1], "0") != 0)
		{
			/* If conversion failed, print an error message */
			fprintf(stderr, "%s: %s: numeric argument required\n",
					info->argv[0], info->argv[1]);
			info->status = 2; /* Set status to indicate an error */
			return (1);
		}
		if (exitcode < 0 || exitcode > INT_MAX)
		{
			/* If number is out of range, print an error message */
			fprintf(stderr, "%s: %s: exit status out of range\n",
					info->argv[0], info->argv[1]);
			info->status = 2; /* Set status to indicate an error */
			return (1);
		}
		info->err_num = exitcode; /* Set error number to exitcode */
	}

	return (-2); /* Indicate that the shell should exit */
}

/**
 * _myhelp - function that retrieves help messages according to builtin command
 * @info: data structure (args and input)
 * Return: Always 1
 */

int _myhelp(info_t *info)
{
	int i, j;
	char *name;

	switch (find_builtin(info->argv[1]))
	{
		case BUILTIN_EXIT:
			name = "exit";
			break;
		case BUILTIN_CD:
			name = "cd";
			break;
		case BUILTIN_HELP:
			name = "help";
			break;
		case BUILTIN_HISTORY:
			name = "history";
			break;
		default:
			name = NULL;
			break;
	}

	if (name == NULL)
	{
		printf("No help topics match `%s'.  Try `help help'.\n", info->argv[1]);
	}
	else
	{
		if (strcmp(name, "exit") == 0)
		{
			printf("exit: exit [n]\n\tExit the shell.\n\n");
		}
		else if (strcmp(name, "cd") == 0)
		{
			printf("cd: cd [dir]\n\tChange the shell working directory.\n\n");
		}
		else if (strcmp(name, "help") == 0)
		{
			printf("help: help [builtin]\n\tDisplay information about built-in commands.\n\n");
		}
		else if (strcmp(name, "history") == 0)
		{
			printf("history: history\n\tDisplay the command history.\n\n");
		}
		else
		{
			printf("Unknown help topic. Try `help help'.\n");
		}
	}

	return (1);
}
