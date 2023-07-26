#include "shell.h"

/**
 * find_path - it finds a path and concatenate the command to it.
 * @command: a command to find
 * Return: full path
 */

char *find_path(char *command)
{
	char *path = NULL;
	char *directory = NULL;
	char *fullpath = NULL;
	int dir_len, cmd_len, total_len, max = 1024;
	char *tmp = NULL;

	path = _getenv("PATH");
	tmp = _strdup(path);
	directory = strtok(tmp, ":");
	fullpath = malloc(max * sizeof(char));
	while (directory != NULL)
	{
		dir_len = _strlen(directory);
		cmd_len = _strlen(command);
		total_len = dir_len + cmd_len + 2;

		if (total_len <= max)
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
