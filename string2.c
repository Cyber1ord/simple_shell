#include "shell.h"

/**
 * _strncmp - compares two strings
 * @s1: first string
 * @s2: second string
 * @n: number of characters to compare
 *
 * Return: 0 if strings are equal, negative value if s1 is less than s2,
 * positive value if s1 is greater than s2
 */
int _strcomp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	for (i = 0; i < n && s1[i] != '\0' && s2[i] != '\0'; i++)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	}

	if (i == n)
		return (0);

	return (s1[i] - s2[i]);
}

/**
 * _strconcat - concatenates two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: pointer to newly allocated string containing s1 followed by s2,
 * or NULL on failure
 */
char *_strconcat(const char *s1, const char *s2)
{
	size_t len1, len2, len;
	char *result;

	len1 = _strlen(s1);
	len2 = _strlen(s2);
	len = len1 + len2 + 1;

	result = malloc(len * sizeof(char));
	if (result == NULL)
		return (NULL);

	_strcpy(result, s1);
	_strcat(result, s2);

	return (result);
}

/**
 * _realloc_ptr - reallocates memory for a pointer
 * @ptr: pointer to reallocate memory for
 * @old_size: size of the old memory allocation
 * @new_size: size of the new memory allocation
 *
 * Return: pointer to the newly allocated memory, or NULL on failure
 */
void *_realloc_ptr(void *ptr, size_t old_size, size_t new_size)
{
	void *new_ptr;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size <= old_size)
		return (ptr);

	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);

	_memcpy(new_ptr, ptr, old_size);
	free(ptr);

	return (new_ptr);
}

/**
 * _strlen - calculates the length of a string
 * @s: the string to calculate the length of
 *
 * Return: the length of the string
 */
size_t _strlen(const char *s)
{
	size_t len = 0;

	while (*s != '\0')
	{
		len++;
		s++;
	}

	return (len);
}

