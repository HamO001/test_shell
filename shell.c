#include "shell.h"
#include "commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void shell_loop(void)
{
	char *line;
	char **args;
	int status;
	size_t buffer_size = 0;
	int interactive = isatty(STDIN_FILENO);
	ssize_t read;

	do {
		if (interactive)
		{
			write(STDOUT_FILENO, "$ ", 2);
		}

		line = NULL;
		read = getline(&line, &buffer_size, stdin);

		if (read == -1)
		{
			if (interactive)
				putchar('\n');
			break;
		}

		args = parse_line(line);
		status = execute_command(args);

		free(line);
		free(args);
	} while (interactive || status == 1);
}
