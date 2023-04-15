#include "rj-headers.h"

char *builtin_str[] = {
	"cd",
	"help",
	"cat",
	"ls",
	"cls",
	"exit"
};

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
 * _myhelp - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myhelp(char **args)
{
	int i;

	printf("Adeyemo Raphael's CYB\n");

	printf("The following are built in:\n");

	for (i = 0; i < sizeof(builtin_str) / sizeof(char*); i++)
	{
		printf("  %s\n", builtin_str[i]);
	}

	printf("Use the man command for information on other programs.\n");
	return (1);
}


/**
 * _mycd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */

