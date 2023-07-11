#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "commands.h"

void shell_loop(void)
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
		if (getline(&line, &buffer_size, stdin) == -1)
		{
			perror("getline");
			exit(EXIT_FAILURE);
		}

		args = parse_line(line);
		status = execute_command(args);

		free(line);
		free(args);
	} while (status);
}

int main(void)

{
	int interactive = isatty(STDIN_FILENO);

	shell_loop();

	return (EXIT_SUCCESS);
}
