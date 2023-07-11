#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TOKEN_BUFSIZE 64
#define TOKEN_DELIMITERS " \t\r\n\a"

char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t characters_read = getline(&line, &bufsize, stdin);

	if (characters_read == -1)
	{
		perror("getline error");
		exit(EXIT_FAILURE);
	}

	return (line);
}

char **parse_line(char *line)
{
	char *token = strtok(line, TOKEN_DELIMITERS);
	int bufsize = TOKEN_BUFSIZE;
	int position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));

	if (!tokens)
	{
		perror("Memory allocation error");
		exit(EXIT_FAILURE);
	}

	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= bufsize)
		{
			bufsize += TOKEN_BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char *));

			if (!tokens)
			{
				perror("Memory allocation error");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, TOKEN_DELIMITERS);
	}

	tokens[position] = NULL;
	return (tokens);
}
