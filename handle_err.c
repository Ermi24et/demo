#include "shell.h"

/**
 * handle_error - handles error
 * @pro_name: the program name
 * @com: command entered
 * @counter: counts number of execution
 * Return: void
 */

void handle_error(char *pro_name, char *com, int counter)
{
	char *loop_count = int_to_str(counter);
	char *not_found = "not found\n";
	char *separator = ": ";

	write(STDOUT_FILENO, pro_name, _strlen(pro_name));
	write(STDOUT_FILENO, separator, _strlen(separator));
	write(STDOUT_FILENO, loop_count, _strlen(loop_count));
	write(STDOUT_FILENO, separator, _strlen(separator));
	write(STDOUT_FILENO, com, _strlen(com));
	write(STDOUT_FILENO, separator, _strlen(separator));
	write(STDOUT_FILENO, not_found, _strlen(not_found));

	free(loop_count);
}

/**
 * int_to_str - converts integer to string
 * @val: value to convert
 * Return: string
 */

char *int_to_str(int val)
{
	int num_digits = 1;
	int temp = val;
	char *num = NULL;

	while (temp /= 10)
		num_digits++;
	num = malloc((num_digits + 1) * sizeof(char));

	if (!num)
		return (NULL);
	num[num_digits] = '\0';

	while (num_digits--)
	{
		num[num_digits] = (val % 10) + '0';
		val /= 10;
	}
	return (num);
}

/**
 * _strcpy - copy the string pointed to by src to dest
 * @dest: char to check
 * @src: char to check
 * Return: the value of the pointer to dest
 */

char *_strcpy(char *dest, char *src)
{
	int a;

	for (a = 0; src[a] != '\0'; a++)
		dest[a] = src[a];
	dest[a] = '\0';
	return (dest);
}
