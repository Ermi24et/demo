#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @s: the string to count
 * Return: string length
 */

int _strlen(const char *s)
{
	int i;

	for (i = 0; s[i]; i++)
		;

	return (i);
}

/**
 * _strcmp - compares two strings
 * @s1: string to compare
 * @s2: string two to compare
 * Return: the difference between the first char that are not the same
 */

int _strcmp(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i] && s2[i]; i++)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	}

	return (s1[i] - s2[i]);
}

/**
 * _strncmp - compares n bytes of two strings
 * @str1: string one to compare
 * @str2: string two to compare
 * @n: number of characters to compare
 * Return: 0 if they are equal
 */

int _strncmp(const char *str1, const char *str2, size_t n)
{
	size_t i;

	for (i = 0; i < n && str1[i] && str2[i]; i++)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
	}
	if (i == n)
		return (0);

	return (str1[i] - str2[i]);
}

/**
 * _strncpy - function that copies a string
 * @dest: the destination of the string
 * @src: source of a string
 * @n: length of a string
 * Return: pointer to the resulting string destination
 */

char *_strncpy(char *dest, char *src, int n)
{
	int i;

	for (i = 0; i < n && src[i]; i++)
		dest[i] = src[i];

	for (; i < n; i++)
		dest[i] = '\0';

	return (dest);
}

/**
 * _strdup - a function that returns a pointer to a newly allocated space
 * @str: a string to be copied
 * Return: returns a pointer or NULL if insufficient memory
 */

char *_strdup(char *str)
{
	char *res = NULL;
	int i = 0, j = 0;

	if (str == NULL)
		return (NULL);

	while (str[i] != '\0')
		i++;
	res = malloc(sizeof(*res) * (i + 1));
	if (res == NULL)
		return (NULL);
	for (j = 0; str[j]; j++)
		res[j] = str[j];
	res[j] = '\0';
	return (res);
}
