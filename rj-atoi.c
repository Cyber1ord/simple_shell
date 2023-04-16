#include "rj-headers.h"

/**
 * interactive - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */

int interactive(info_t *info)
{
	if (isatty(STDIN_FILENO) && info->readfd <= 2)
		return (1);
	return (0);
}


/**
 * is_delim - checks if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */

int is_delim(char c, char *delim)
{
	for (; *delim; delim++)
	{
		if (c == *delim)
			return (1);
	}
	return (0);
}


/**
 *_isalpha - checks for alphabetic character
 *@c: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */
int _isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
 *_atoi - converts a string to an integer
 *@s: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */
int _atoi(char *s)
{
	int sign = 1, num = 0;

	while (*s)
	{
		if (*s == '-')
			sign = -sign;

		if (*s >= '0' && *s <= '9')
		{
			num = num * 10 + (*s - '0');
			if (num > INT_MAX / 10)
			{
				if (sign == 1)
					return (INT_MAX);
				else
					return (INT_MIN);
			}
			num *= sign;
		}
		else if (num != 0)
		{
			break;
		}

		s++;
	}

	return (num);
}
