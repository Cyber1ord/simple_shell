#include "shell.h"

/**
 * _strcpy - Copies the string pointed to by src to dest
 * @dest: Destination buffer
 * @src: Source string
 *
 * Return: Pointer to dest
 */
char *_strcpy(char *dest, const char *src)
{
        int i;

        for (i = 0; src[i]; i++)
                dest[i] = src[i];
        dest[i] = '\0';

        return (dest);
}

/**
 * _memcpy - Copies n bytes from memory area src to memory area dest
 * @dest: Destination memory area
 * @src: Source memory area
 * @n: Number of bytes to copy
 *
 * Return: Pointer to dest
 */
void *_memcpy(void *dest, const void *src, size_t n)
{
        char *d = dest;
        const char *s = src;

        while (n--)
                *d++ = *s++;

        return (dest);
}

/**
 * _strcat - Concatenates two strings
 * @dest: Destination string
 * @src: Source string
 *
 * Return: Pointer to dest
 */
char *_strcat(char *dest, const char *src)
{
        int dest_len = strlen(dest);
        int i;

        for (i = 0; src[i]; i++)
                dest[dest_len + i] = src[i];
        dest[dest_len + i] = '\0';

        return (dest);
}

/**
 * _strdup - Duplicates a string
 * @str: String to duplicate
 *
 * Return: Pointer to the newly allocated memory containing the duplicated string
 */
char *_strdup(const char *str)
{
        char *dup;
        size_t len;

        len = strlen(str) + 1;
        dup = malloc(len * sizeof(char));
        if (!dup)
                return NULL;

        return ((char *) memcpy(dup, str, len));
}

