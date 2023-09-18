#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include "shell.h"
/**
 *execute_command - execute a command
 *@command: command to accept
 *
 *Return: none
 */
void execute_command(char *command)
{
	int status;
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		/*child process*/
		char *args[2];

		args[0] = command;
		args[1] = NULL;
		if (execve(command, args, NULL) == -1)
		{
			perror("hsh:1");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/*parent process*/
		waitpid(pid, &status, 0);

	}
}
