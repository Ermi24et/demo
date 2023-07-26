#include "shell.h"

/**
 * c_execute - it creates process and executes
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
			exit(EXIT_FAILURE);
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
		perror("fork error\n");
}
