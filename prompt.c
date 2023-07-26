#include "shell.h"

/**
 * signal_handler - Handles Ctr C signal
 * @signal: Signal parameter
 * Return: void
 */

void signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(STDERR_FILENO, "\n$ ", 4);
		fflush(stdout);
	}
}

/**
 * non_interactive - it reads a file
 * Return: created line
 */

char *non_interactive()
{
	char *glptr = NULL;
	ssize_t gl_result;
	size_t len = 0;

	gl_result = getline(&glptr, &len, stdin);

	if (gl_result == -1)
	{
		free(glptr);
		exit(EXIT_FAILURE);
	}
	return (glptr);
}

/**
 * _prompt - it reads and prompts user
 * @prompt: accepts sign
 * Return: created line
 */
char *_prompt(char *prompt)
{
	char *glptr = NULL;
	ssize_t gl_result;
	size_t len = 0;

	write(STDOUT_FILENO, prompt, _strlen(prompt));
	gl_result = getline(&glptr, &len, stdin);

	if (gl_result == -1)
	{
		write(STDOUT_FILENO, "\n", 1);
		free(glptr);
		exit(EXIT_FAILURE);
	}
	return (glptr);
}

/**
 * main - it reads, prases and executes
 * @argc: number of arguments
 * @argv: arguments
 * Return: Success (0)
 */

int main(int argc __attribute__((unused)), char **argv)
{
	char *prompt = "$ ", *glptr = NULL, **tok_str = NULL;
	int check_term = 1, count = 1;

	while (check_term)
	{
		signal(SIGINT, signal_handler);
		if (isatty(STDIN_FILENO) == 1)
			glptr = _prompt(prompt);
		else
			glptr = non_interactive();
		tok_str = comm_tok(glptr, " \n\r\t");
		if (tok_str != NULL && tok_str[0] != NULL)
		{
			if (_strcmp(tok_str[0], "exit") == 0)
			{
				free(tok_str[0]);
				free(tok_str);
				break;
			}
			if (_strcmp(tok_str[0], "env") == 0)
			{
				free(tok_str[0]);
				print_environment();
				free(tok_str);
				continue;
			}
			if (cmd_ok(tok_str, count, argv))
			{
				c_execute(tok_str);
				if (glptr[0] != '/')
					free(glptr);
				free(tok_str[0]);
			}
		}
		free(tok_str);
		count++;
	}
	return (0);
}

/**
 * cmd_ok - checks the first character
 * @tok_str: tokenized string
 * @count: counter of execution
 * @argv: entered command
 * Return: Success(1), Failure(0)
 */

int cmd_ok(char **tok_str, int count, char **argv)
{
	char *path = NULL;

	if (tok_str[0][0] != '/')
	{
		path = find_path(tok_str[0]);
		if (path != NULL)
		{
			tok_str[0] = _strdup(path);
			free(path);
		}
		else
		{
			handle_error(argv[0], tok_str[0], count);
			return (0);
		}
	}
	return (1);
}
