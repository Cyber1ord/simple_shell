#include "shell.h"

/**
 * cd_builtin - change the current working directory of the shell
 * @args: the list of arguments to the command
 *
 * Return: 1 on success, 0 otherwise
 */
int cd_builtin(char **args)
{
	char *dir;
	char cwd[1024];

	if (!args[1] || (*args[1] == '~' && !*(args[1] + 1)))
	{
		dir = _getenv("HOME");
		if (!dir)
		{
			perror("cd");
			return (0);
		}
	}
	else if (*args[1] == '-')
	{
		dir = _getenv("OLDPWD");
		if (!dir)
		{
			perror("cd");
			return (0);
		}
		printf("%s\n", dir);
	}
	else
		dir = args[1];

	if (chdir(dir) == -1)
	{
		perror("cd");
		return (0);
	}

	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("cd");
		return (0);
	}

	if (_setenv("OLDPWD", _getenv("PWD")) == -1)
		perror("cd");

	if (_setenv("PWD", cwd) == -1)
		perror("cd");

	return (1);
}

