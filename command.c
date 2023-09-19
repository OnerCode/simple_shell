#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include "shell.h"

int find_command_in_path(const char *command, char *full_path);
/**
 *command_exists - check if command exists
 *@command: command to be checked
 *
 *Return: 0 success
 */
int command_exists(const char *command)
{
	char full_path[256];

	if (!command || command[0] == '\0')
	{
		return (0);
	}
	if (find_command_in_path(command, full_path))
	{
		return (1);
	}
	if (access(command, F_OK) == 0)
	{
		return (1);
	}
	return (0);
}
/**
 *execute_command - execute a command
 *@args: arguments to accept
 *@com_num: command number
 *@prg_nme: program name
 *
 *Return: none
 */
void execute_command(char **args, int com_num, const char *prg_nme)
{
	pid_t child_pid = fork();
	int status;
	char full_path[256];

	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
	{
		if (args[0][0] == '/')
		{
			if (access(args[0], X_OK) == 0)
			{
				if (execve(args[0], args, NULL) == -1)
				{
					perror("execve:hsh");
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				fprintf(stderr, "%s: %d: %s: not found\n", prg_nme, com_num, args[0]);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (find_command_in_path(args[0], full_path))
			{
				if (execve(full_path, args, NULL) == -1)
				{
					perror("execve:hsh");
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				fprintf(stderr, "%s: %d: %s: not found\n", prg_nme, com_num, args[0]);
				exit(EXIT_FAILURE);
			}
		}
	}
	else
	{
		if (args[0][strlen(args[0]) - 1] != '&')
		{
			do {
				wait(&status);
			} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		}
	}
}
/**
 *find_command_in_path - finding a command in PATH
 *@command: command to find
 *@full_path: full path of command
 *
 *Return: 0 success
 */
int find_command_in_path(const char *command, char *full_path)
{
	char *path = getenv("PATH");
	char *path_copy = strdup(path), *token = strtok(path_copy, ":");

	if (!path)
	{
		fprintf(stderr, "PATH environment variable not found\n");
		exit(EXIT_FAILURE);
	}
	if (!path_copy)
	{
		perror("strdup");
		exit(EXIT_FAILURE);
	}
	while (token)
	{
		snprintf(full_path, 256, "%s/%s", token, command);
		if (access(full_path, F_OK) == 0)
		{
			free(path_copy);
			return (1);
		}
		token = strtok(NULL, ":");
	}
	free(path_copy);
	return (0);
}
