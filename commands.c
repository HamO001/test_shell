#include "commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * execute_command - function to excecute command
 * @args: arguements
 * Return: integer
 */

int execute_command(char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid < 0)
	{
		perror("Fork error");
		return (-1);
	}
	else if (pid == 0)
	{
		/* Child process */
		/*char *args[] = {"argv[1]", NULL};*/
		execve(args[0], args, NULL);
		perror(":(Command execution error");
		exit(EXIT_FAILURE);
	}
	else
	{
		/* Parent process */
		waitpid(pid, &status, 0);

		if (WIFEXITED(status))
		{
			return (WEXITSTATUS(status)); /* Return the exit status */
		}
		else
		{
			perror("Command execution error$$$$$");
			return (-1);
		}
	}
}
