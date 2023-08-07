#include "shell.h"
#include <stdlib.h>

#define BUFFER_SIZE 1024

char *_getline(void)
{
	static char buffer[BUFFER_SIZE];
	static int pos = 0;
	static int size = 0;

	char *line = NULL;
	int line_pos = 0;

	while (1)
	{
		/*if the buffer is empty*/
		if (pos >= size)
		{
			pos = 0;
			size = read(STDIN_FILENO, buffer, BUFFER_SIZE);
			if (size == 0)
			{
				/*End of file reached, return the line if any*/
				if  (line_pos == 0)
					return (NULL);
				break;
			}
			if (size == -1)
			{
				perror("read");
				exit(EXIT_FAILURE);
			}
		}
		/*copy characters from buffer to line until newline is encounterd*/
		while (pos < size)
		{
			if (buffer[pos] == '\n')
			{
				pos++;
				break;
			}
			if (line_pos == 0)
			{
				line = malloc(BUFFER_SIZE);
			}
			else if (line_pos % BUFFER_SIZE == 0)
			{
				line = realloc(line, line_pos + BUFFER_SIZE);
			}
			if (line == NULL)
			{
				perror("malloc/realloc");
				exit(EXIT_FAILURE);
			}
			line[line_pos++] = buffer[pos++];
		}
		/*If newline was encounterd, return the line*/
		if (buffer[pos - 1] == '\n')
			break;
	}
	/*Null-terminate the line and return it*/
	if (line_pos > 0)
	{
		line[line_pos] = '\0';
	}
	return (line);
}
