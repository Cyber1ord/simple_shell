#include "shell.h"

/**
 * change_directory - changes the current working directory
 * @mydata: structure containing potential arguments
 * @dir: the directory to change to
 * Return: 1 on failure, 0 on success
 */
int change_directory(data_t *mydata, char *dir)
{
	char buffer[1024];
	int chdir_ret;

	chdir_ret = chdir(dir);
	if (chdir_ret == -1)
	{
		print_error(mydata, "can't cd to ");
		_eputs(dir);
		_eputchar('\n');
		return (1);
	}
	else
	{
		_setenv(mydata, "OLDPWD", _getenv(mydata, "PWD="));
		_setenv(mydata, "PWD", getcwd(buffer, 1024));
		return (0);
	}
}

/**
 * cd_home - changes the current working directory to HOME
 * @mydata: structure containing potential arguments
 * Return: 1 on failure, 0 on success
 */
int cd_home(data_t *mydata)
{
	char *dir;

	dir = _getenv(mydata, "HOME=");
	if (!dir)
	{
		dir = _getenv(mydata, "PWD=");
	}
	while (dir && *dir && *dir == ' ')
	{
		dir++;
	}
	return (change_directory(mydata, dir));
}

/**
 * cd_prev - changes the current working directory to the previous directory
 * @mydata: structure containing potential arguments
 * Return: 1 on failure, 0 on success
 */
int cd_prev(data_t *mydata)
{
	char *dir, buffer[1024];

	dir = _getenv(mydata, "OLDPWD=");
	if (!dir)
	{
		_puts(getcwd(buffer, 1024));
		_putchar('\n');
		return (1);
	}
	while (dir && *dir && (*dir == ' '))
	{
		dir++;
	}
	_puts(dir);
	_putchar('\n');
	return (change_directory(mydata, dir));
}

/**
 * _cd - changes the current directory of the process
 * @mydata: structure containing potential arguments
 * Return: Always 0
 */
int _cd(data_t *mydata)
{
	char *dir;

	if (!mydata->argv[1])
	{
		return (cd_home(mydata));
	}
	else if (_strcmp(mydata->argv[1], "-") == 0)
	{
		return (cd_prev(mydata));
	}
	dir = mydata->argv[1];
	while (dir && *dir && *dir == ' ')
	{
		dir++;
	}
	return (change_directory(mydata, dir));
}
