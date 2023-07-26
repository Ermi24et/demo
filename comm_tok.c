#include "shell.h"

/**
 * comm_tok - tokenizes a string
 * @str: the string to parse
 * @delimiters: delimiters used to parse
 * Return: tokenized string
 */

char **comm_tok(char *str, char *delimiters)
{
	char *token = NULL;
	char **tokens = NULL;
	int num_words, str_len, i = 0;

	if (str == NULL)
		return (NULL);

	str_len = _strlen(str);

	token = malloc((str_len + 1) * sizeof(char));

	if (token == NULL)
		return (NULL);

	_strncpy(token, str, str_len);
	token[str_len] = '\0';

	num_words = count_str(token, delimiters);
	free(token);

	if (num_words == 0)
		return (NULL);

	tokens = malloc(sizeof(char *) * (num_words + 1));

	if (!tokens)
		return (NULL);

	str = strtok(str, delimiters);

	while (str)
	{
		tokens[i++] = str;
		str = strtok(NULL, delimiters);
	}
	tokens[i] = NULL;

	return (tokens);

}

/**
 * count_str - Counts group of characters in string
 * @str: String parameter
 * @delimiters: delimiters used to parse
 * Return: number of characters
 */

int count_str(char *str, char *delimiters)
{
	char *str_copy = NULL;
	char *token = NULL;
	unsigned int count = 0;

	if (str == NULL || delimiters == NULL)
		return (0);

	str_copy = malloc(_strlen(str) + 1);

	if (str_copy == NULL)
		return (0);

	_strcpy(str_copy, str);

	token = strtok(str_copy, delimiters);

	while (token)
	{
		count++;
		token = strtok(NULL, delimiters);
	}

	free(str_copy);
	str_copy = NULL;

	return (count);
}
