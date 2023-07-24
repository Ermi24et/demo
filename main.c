/* standard headers for the files */
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

/* declaring an external environment variables */
extern char **environ;
int MAX_PATH_LEN = 1024;

/* function prototypes for our shell */
void print_environment(void);
int cmd_ok(char **tok_str, int count, char **argv);
void c_execute(char **comm);
char **comm_tok(char *str, char *delimiters);
char *_getenv(const char *name);
char *find_path(char *command);
void handle_error(char *pro_name, char *com, int counter);
int count_str(char *str, char *delimiters);
void signal_handler(int signal);
char *_prompt(char *prompt);

/* function prototypes for utility functions */
char *int_to_str(int val);
int _strlen(const char *s);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *str1, const char *str2, size_t n);
char *_strcpy(char *dest, char *src);
char *_strncpy(char *dest, char *src, int n);
char *_strdup(char *str);

/**
* signal_handler - Handles Ctrl C signal
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
 * _prompt - it reads and promptes user
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
 * main - it reads and prases and executes
 * @argc: number of arguments
 * @argv: arguments
 * Return: Success(0)
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
 * Return: Success(1), Fail(0)
 */

int cmd_ok(char **tok_str, int count, char **argv)
{
	char *path = NULL;

	if (tok_str[0][0] != '/')
	{
		path = find_path(tok_str[0]);
		if (path != NULL)
		{
			tok_str[0] = _strdup(path);;
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
* count_str - Counts group of characters in str
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

/**
 * find_path - it finds the command in the PATH
 * @command: a command to find
 * Return: full path
 */

char *find_path(char *command)
{
	char *path = NULL;
	char *directory = NULL;
	char *fullpath = NULL;
	int dir_len, cmd_len, total_len;
	char *tmp = NULL;

	path = _getenv("PATH");
	tmp = _strdup(path);
	directory = strtok(tmp,":");
	fullpath = malloc(MAX_PATH_LEN * sizeof(char));
	while (directory != NULL)
	{
		dir_len = _strlen(directory);
		cmd_len = _strlen(command);
		total_len = dir_len + cmd_len + 2;

		if (total_len <= MAX_PATH_LEN)
		{
			_strncpy(fullpath, directory, dir_len);
			fullpath[dir_len] = '/';
			_strncpy(fullpath + dir_len + 1, command, cmd_len);
			fullpath[total_len - 1] = '\0';
		}
		if (access(fullpath, X_OK) == 0)
		{
			free(tmp);
			return (fullpath);
		}
		directory = strtok(NULL, ":");
	}
	free(fullpath);
	free(directory);
	free(tmp);
	return (NULL);
}

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
 * print_environment - printing env variables to std output
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

/**
 *handle_error - handles error
 *@pro_name: program name
 *@com: command enterd
 *@counter: counts number of execution
 *Return: void
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
 * c_execute - it creates process and execute
 * @comm: a command to execute
 * Return: void
 */

void c_execute(char **comm)
{
	int status;
	pid_t pid = fork();

	if (pid == 0)
	{
		if (execve(comm[0], comm, environ) == -1)
		{
			exit(EXIT_FAILURE);
		}
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
		perror("fork");
}

/**
 * _strlen - returns the length of a string
 * @s: the string to count
 * Return: string length
 */

int _strlen(const char *s)
{
	int i;

	for (i = 0; s[i]; i++)
	{
		;
	}
	return (i);
}

/**
 * _strcmp - compares two strins
 * @s1: string to compare
 * @s2: string to compare
 * Return: the difference between the first char that are not the same
 */

int _strcmp(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i] && s2[i]; i++)
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
	}

	return (s1[i] - s2[i]);
}

/**
 * _strncmp - compares n bytes of two strings
 * @str1: string to compare
 * @str2: string to compare
 * @n: number of strings to compare
 * Return: 0 if they are equal
 */

int _strncmp(const char *str1, const char *str2, size_t n)
{
	size_t i;

	for (i = 0; i < n && str1[i] && str2[i]; i++)
	{
		if (str1[i] != str2[i])
		{
			return (str1[i] - str2[i]);
		}
	}

	if (i == n)
	{
		return (0);
	}

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
	{
		dest[i] = src[i];
	}

	for (; i < n; i++)
	{
		dest[i] = '\0';
	}

	return (dest);
}
/**
 * _strcpy - copy the string pointed to by src to dest
 * @dest: char to check
 *@src: char to check
 * Return: the value of the pointer to dest.
 */
char *_strcpy(char *dest, char *src)
{
	int a;

	for (a = 0; src[a] != '\0'; a++)
		dest[a] = src[a];
	dest[a] = '\0';
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
