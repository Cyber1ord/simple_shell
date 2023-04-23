#include "shell.h"

/**
 * _getenv - Get the value of an environment variable.
 * @name: The name of the environment variable.
 *
 * Return: A pointer to the value of the environment variable, or NULL if the
 *         environment variable doesn't exist.
 */
char *_getenv(const char *name)
{
	int i, len;
	char *value;

	if (name == NULL)
		return (NULL);

	len = _strlen((char *) name);

	for (i = 0; environ[i] != NULL; i++)
	{
		if (_strcomp(name, environ[i], len) == 0 && environ[i][len] == '=')

		{
			value = environ[i] + len + 1;
			return (value);
		}
	}

	return (NULL);
}

/**
 * _setenv - Set the value of an environment variable.
 * @name: The name of the environment variable.
 * @value: The value of the environment variable.
 *
 * Return: 0 on success, -1 on failure.
 */
int _setenv(const char *name, const char *value)
{
	int i, len;
	char *env_str;

	if (name == NULL || value == NULL)
		return (-1);

	len = _strlen((char *) name);

	for (i = 0; environ[i] != NULL; i++)
	{
		if (_strcomp(name, environ[i], len) == 0 && environ[i][len] == '=')
		{
			env_str = _strconcat(name, "=", value);
			if (env_str == NULL)
				return (-1);
			free(environ[i]);
			environ[i] = env_str;
			return (0);
		}
	}

	env_str = _strconcat(name, "=", value);
	if (env_str == NULL)
		return (-1);
	if (_realloc_ptr((void **)&environ, sizeof(char *) * (i + 2), sizeof(char *) * (i + 1)) == NULL)
	{
		free(env_str);
		return (-1);
	}
	environ[i] = env_str;
	environ[i + 1] = NULL;

	return (0);
}


/**
 * _puts - Prints a string to stdout
 *
 * @str: The string to be printed
 */
void _puts(char *str)
{
	int i = 0;

	while (str[i])
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - Writes a character to stdout
 *
 * @c: The character to be written
 *
 * Return: On success 1, on error -1
 */
int _putchar(char c)
{
	return (write(STDOUT_FILENO, &c, 1));
}
