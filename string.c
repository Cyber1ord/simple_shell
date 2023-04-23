#include "shell.h"

/**
 * replace_vars - Replaces variable placeholders in a string
 * @str: The string to modify
 * @status: The exit status of the last executed command
 * @pid: The process ID of the shell
 *
 * Return: The modified string
 */
char *replace_vars(char *str, int status, pid_t pid)
{
	char *ret = malloc(sizeof(char) * (_strlen(str) + 1));
	char *var_start, *var_end, *var_name, *var_value;
	int i = 0, j = 0, k = 0, len;

	if (!ret)
		return (NULL);

	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '\0')
		{
			var_start = &str[i];
			var_end = var_start + 1;
			while (isalnum(*(++var_end)))
				;
			len = var_end - var_start - 1;
			var_name = _strdup(var_start + 1, len);
			if (!var_name)
				return (NULL);
			if (_strcomp(var_name, "?") == 0)
				var_value = _itoa(status);
			else if (_strcomp(var_name, "$") == 0)
				var_value = _itoa(pid);
			else
				var_value = _getenv(var_name);
			if (!var_value)
				var_value = "";
			len = _strlen(var_value);
			while (j < (var_start - str))
				ret[k++] = str[j++];
			j = var_end - str;
			while (*var_value)
				ret[k++] = *(var_value++);
			free(var_name);
			free(var_value);
		}
		else
		{
			ret[k++] = str[j++];
		}
		i++;
	}
	ret[k] = '\0';
	return (ret);
}

/**
 * _itoa - Converts an integer to a string
 * @num: The integer to convert
 *
 * Return: The resulting string
 */
char *_itoa(int num)
{
	int sign = num < 0 ? -1 : 1;
	int i = 0, j;
	char *str = malloc(sizeof(char) * 12);

	if (num == 0)
	{
		str[i++] = '0';
		str[i] = '\0';
		return (str);
	}

	num *= sign;

	while (num)
	{
		str[i++] = (num % 10) + '0';
		num /= 10;
	}

	if (sign == -1)
		str[i++] = '-';

	str[i] = '\0';

	for (j = 0; j < i / 2; j++)
	{
		char temp = str[j];
		str[j] = str[i - j - 1];
		str[i - j - 1] = temp;
	}

	return (str);
}

