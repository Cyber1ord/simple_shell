#include "rj-headers.h"

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
<<<<<<< HEAD
 * @datash: data structure (args and input)
=======
 * @info: data structure (args and input)
>>>>>>> 0cc015fca5d44a194aff3a55b3745a218c55be16
 * Return: Always 1
 */
int _myhelp(info_t *info)
{
	/* Define help messages */
	char *help_general = "Type help [builtin] for more information about a command.\n\n"
		"Builtins:\n"
		"\tcd\n"
		"\tsetenv\n"
		"\tunsetenv\n"
		"\tenv\n"
		"\texit\n"
		"\thelp\n";
	char *help_setenv = "Usage: setenv [VARIABLE] [VALUE]\n\n"
		"Set an environment variable.\n";
	char *help_env = "Usage: env\n\n"
		"Print the environment variables.\n";
	char *help_unsetenv = "Usage: unsetenv [VARIABLE]\n\n"
		"Unset an environment variable.\n";
	char *help_exit = "Usage: exit [STATUS]\n\n"
		"Exit the shell with a given status.\n";
	char *help_cd = "Usage: cd [DIRECTORY]\n\n"
		"Change the current working directory.\n";
	char *help_alias = "Usage: alias [ALIAS] [VALUE]\n\n"
		"Create an alias for a command.\n";

	/* Check for correct number of arguments */
	if (info->args[1] == NULL || info->args[2] != NULL)
	{
		write(STDERR_FILENO, info->args[0], _strlen(info->args[0]));
		info->status = 2;
		return (1);
	}

	/* Print help message based on argument */
	switch (get_builtin(info->args[1]))
	{
		case BUILTIN_GENERAL:
			write(STDOUT_FILENO, help_general, _strlen(help_general));
			break;
		case BUILTIN_CD:
			write(STDOUT_FILENO, help_cd, _strlen(help_cd));
			break;
		case BUILTIN_SETENV:
			write(STDOUT_FILENO, help_setenv, _strlen(help_setenv));
			break;
		case BUILTIN_UNSETENV:
			write(STDOUT_FILENO, help_unsetenv, _strlen(help_unsetenv));
			break;
		case BUILTIN_ENV:
			write(STDOUT_FILENO, help_env, _strlen(help_env));
			break;
		case BUILTIN_EXIT:
			write(STDOUT_FILENO, help_exit, _strlen(help_exit));
			break;
		case BUILTIN_ALIAS:
			write(STDOUT_FILENO, help_alias, _strlen(help_alias));
			break;
		default:
			write(STDERR_FILENO, info->args[0], _strlen(info->args[0]));
			info->status = 2;
			return (1);
	}

	info->status = 0;
	return (1);
}

<<<<<<< HEAD
=======
/**
 * _mycd - changes the current working directory of the shell process
 * @info: pointer to a info_t containing arguments for cd command
 *
 * Return: Always returns 1
 */
int _mycd(info_t *info)
{
	char *dir = info->args[1];

	if (dir == NULL)
	{
		cd_to_home(info);
	}
	else if (strcmp("$HOME", dir) == 0 || strcmp("~", dir) == 0 || strcmp("--", dir) == 0)
	{
		cd_to_home(info);
	}
	else if (strcmp("-", dir) == 0)
	{
		cd_previous(info);
	}
	else if (strcmp(".", dir) == 0 || strcmp("..", dir) == 0)
	{
		cd_dot(info);
	}
	else
	{
		cd_to(info);
	}

	return (1);
}

>>>>>>> 0cc015fca5d44a194aff3a55b3745a218c55be16
