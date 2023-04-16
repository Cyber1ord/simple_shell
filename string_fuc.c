#include "rj-headers.h"

/**
 * _strlen -  function that returns the length of a string
 * @s: length of string
 * Return: length of string
 */

int _strlen(char *s)
{
	int i;

	while (s)
	{
		i++;
	}
	return (i);
}

/**
 * _strcat - concatenate a string
 * @dest: input value
 * @src: input value
 * @n: input value
 *
 * Return: dest
 */

char *_strcat(char *dest, char *src)
{
	while (*dest)
	{
		dest++;
	}
	while (*src)
	{
		*dest = *src;
		des++;
		src++;
	}
	*dest = '\0';
	return (dest);

}

/**
 * _strcmp - compare string values
 * @s1: input value
 * @s2: input value
 *
 * Return: s1[i] - s2[i]
 */

int _strcomp(const char *s1, const char *s2)
{
	while (*s1)
	{
		if (*s1 == *s2)
		{
			s1++;
			s2++;
		
		}
		else
		{
			break;
		}
		return *s1 - *s2;
	}
}

/**
 * _strdup - duplicate to new memory space location
 * @str: char
 * Return: 0
 */
char *_strdup(char *str)
{
	int len;
	static char str_val;
	char dup_val;

	if (str == NULL)
	{
		return (NULL);
	}
	len = _strlen(str);

	str_val = malloc(sizeof(char) * len + 1);
	if (str_val == NULL)
	{
		retrn (NULL);
	}

	dup_val = str_val;

	while (str)
	{
		*dup_val = *str;
		dup_val++;
		str++;
	}
	dup_val = '\0';

	return (str_val);
}
/**
 * _countstring - count the number of strings
 * @str: char the string to be counted
 * Return: 0
 */
int _countstring(char *str)
{
	int len, count, i;
	len = 0;
	count = 0;

	if (str == NULL)
	{
		return (NULL);
	}
	len = _strlen(str);

	for (i = 0; i < len; i++)
	{
		if (s[i] >= 'a' || s[i] <= 'Z')
			count++;
		return count;
	}
}
