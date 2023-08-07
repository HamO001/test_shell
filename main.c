#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "commands.h"

/**
 * shell_loop - looping fuunction
 * Return: nothing
 */
void hell_loop(void)
{
	char *line;
	char **args;
	int status;
	size_t buffer_size = 0;
	int interactive = isatty(STDIN_FILENO);

	do {
		if (interactive)
		{
			write(STDOUT_FILENO, "$ ", 2);
		}

		line = NULL;
		if (_getline(&line, &buffer_size, stdin) == -1)
		{
			perror("getline");
			exit(EXIT_FAILURE);
		}

		args = parse_line(line);
		status = execute_command(args);

		free(line);
		free(args);
	} while (interactive || status == 1);
}

/**
 * main - main function
 * Return: zero
 */
int main(void)

{
	isatty(STDIN_FILENO);

	hell_loop();

	return (EXIT_SUCCESS);
}
