#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"
/**
 *main - shell program main
 *
 *Return: Success 0
 */

int main(void)
{
	char *command = NULL;
	size_t command_length = 0;
	char prompt[] = "hsh> ";
	ssize_t read_bytes;
	int is_interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (is_interactive)
		{
			/* Display the prompt and read the user's input using getline*/
			printf("%s", prompt);
		}

		read_bytes = getline(&command, &command_length, stdin);

		if (read_bytes == -1)
		{
			break;
		}
		/* Remove the trailing newline character*/
		if (command[read_bytes - 1] == '\n')
		{
			command[read_bytes - 1] = '\0';
		}
		/* Check if the user entered a command*/
		if (strlen(command) == 0)
		{
			continue; /* Skip if the user entered an empty line*/
		}
		execute_command(command);
	}
	/* Free the dynamically allocated memory for the command*/
	free(command);
	return (0);
}
