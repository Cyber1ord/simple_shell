#include "rj-headers.h"

/**
 * _myenv - prints the current environment
 * @info: Structure Used to maintain
 *         constant function prototype.
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	int i;

	for (i = 0; environ[i]; i++)
		printf("%s\n", environ[i]);

	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @info: Structure Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv(info_t *info, const char *name)
{
	int i, j, len_name, len_env;
	char *value;

	len_name = _strlen(name);
	for (i = 0; environ[i]; i++)
	{
		len_env = _strlen(environ[i]);
		if (len_env > len_name)
		{
			for (j = 0; j < len_name; j++)
			{
				if (environ[i][j] != name[j])
					break;
			}
			if (j == len_name && environ[i][j] == '=')
			{
				value = environ[i] + len_name + 1;
				return (value);
			}
		}
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize or modify a new environment variable
 * @info: Structure Used to maintain constant function prototype.
 *  Return: Always 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("The number of arguments provided is incorrect\n");
		return (1);
	}
	if (setenv(info->argv[1], info->argv[2], 1) == -1)
		return (1);
	return (0);
}

/**
 * _myunsetenv - Remove environment variable
 * @info: Structure Used to maintain constant function prototype.
 *  Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i < info->argc; i++)
	{
		if (unsetenv(info->argv[i]) == -1)
			return (1);
	}
	return (0);
}

/**
 * populate_env_list - populates env list
 * @info: Structure Used to maintain constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	int i, len;
	char **new_environ;

	for (len = 0; environ[len]; len++)
		;
	new_environ = malloc(sizeof(char *) * (len + 1));
	if (!new_environ)
		return (-1);

	for (i = 0; environ[i]; i++)
	{
		new_environ[i] = _strdup(environ[i]);
		if (!new_environ[i])
		{
			free_env(new_environ);
			return (-1);
		}
	}
	new_environ[i] = NULL;

	info->env = new_environ;
	return (0);
}

