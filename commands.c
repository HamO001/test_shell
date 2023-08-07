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
	int status;	

	pid_t pid = fork();
	if (pid < 0)
	{
		perror("Fork error");
		return (-1);
	}
	else if (pid == 0)
	{
		/* Child process 
		char *shellPath = "/bin/sh";
		char *shellArgs[] = {"-c", args, NULL};
		char *envp[] ={NULL };

		execve(shellPath, shellArgs, envp);
		
		write(STDOUT_FILENO, "\n", 1);
		execve(args[0], args, NULL);*/
		char args[4];
		int i;

		
		args[0] = "/bin/sh";
		args[1] = "-c";
		args[2] = (char *) args; 
		args[3] = NULL;

		while (args[i])
			i++;

		write(STDOUT_FILENO, "", 1);
		execve(args[0], args, NULL);
		perror(":( Excecution commands error");


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
