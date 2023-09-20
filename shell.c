#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"
/**
 *exe_com - execute the user command
 *@command: command to accept
 *@args: arguments to accept
 *@com_num: command number
 *@prg_nme: program name
 *
 *Return: Success 0
 */
void exe_com(char *command, char *args[], int *com_num, const char *prg_nme)
{
	int i = 0;
	char *token = strtok(command, " ");

	while (token != NULL && i < 31)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;
	execute_command(args, (*com_num)++, prg_nme);
}
/**
 * handle_env_command - Function to handle the "env" command
 *
 * Return: void
 */
void handle_env_command(void)
{
	print_environment();
}
/**
 *main - main shell program
 *@argc: argument count
 *@argv: aguments to accept
 *
 *Return: 0 Success
 */
int main(int argc, char **argv)
{
	char *command = NULL, *args[32], prompt[] = "hsh> ";
	size_t command_length = 0;
	ssize_t read_bytes;
	int is_interactive = isatty(STDIN_FILENO);
	int com_num = 1;
	const char *prg_nme = (argc > 0) ? argv[0] : "hsh";

	if (argc > 1)
	{
		return (execute_command(&argv[1], com_num, prg_nme), 0);
	}
	while (1)
	{
		if (is_interactive)
		{
			printf("%s", prompt);
		}
		read_bytes = getline(&command, &command_length, stdin);

		if (read_bytes == -1)
			break;
		if (command[read_bytes - 1] == '\n')
		{
			command[read_bytes - 1] = '\0';
		}
		if (strcmp(command, "exit") == 0)
			break;
		if (strcmp(command, "env") == 0)
		{
			handle_env_command();
			continue;
		}
		if (strlen(command) == 0)
			continue;
		exe_com(command, args, &com_num, prg_nme);
	}
	free(command);
	return (0);
}
