#include "shell.h"

/**
 * _getenv - retrieves the value of an environment variable
 * @name: name of the variable
 * Return: returns a pointer, otherwise NULL
 */

char *_getenv(const char *name)
{
	int i;
	char *env_var;
	int name_len = _strlen(name);

	for (i = 0; environ[i] != NULL; i++)
	{
		env_var = environ[i];
		if (_strncmp(name, env_var, name_len) == 0 && env_var[name_len] == '=')
		{
			return (env_var + name_len + 1);
		}
	}

	return (NULL);
}

/**
 * print_environment - prints environment variables to the terminal
 * Return: void
 */

void print_environment(void)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
}
