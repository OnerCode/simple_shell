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

int main(int argc, char **argv)
{
	char *command = NULL;
	size_t command_length = 0;
	char prompt[] = "hsh> ";
	ssize_t read_bytes;
	int is_interactive = isatty(STDIN_FILENO);
	char *args[32]; /* Adjust the size as needed*/
	char *token;
	int i = 0;

	if (argc > 1)
	{
	/* If command line arguments are provided, execute the command directly*/
	execute_command(&argv[1]);
	return (0);
}
while (1)
{
	if (is_interactive)
{
	/* Display the prompt and read the user's input using getline*/
	printf("%s", prompt);

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
	if (strcmp(command, "env") == 0)
{
		print_environment();
		continue; /* Skip the rest of the loop iteration*/
}
/* Check if the user entered a command*/
	if (strlen(command) == 0)
{
	continue; /* Skip if the user entered an empty line*/
}
	/* Tokenize the command to separate arguments*/
	token = strtok(command, " ");

while (token != NULL && i < 31)
{
	args[i++] = token;
	token = strtok(NULL, " ");
}
	args[i] = NULL;
	execute_command(args);
}
	/* Free the dynamically allocated memory for the command*/
	free(command);
	return (0);
}
