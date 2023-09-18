#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_LEN 1024
/**
 *main - shell program main
 *
 *Return: Success 0
 */
int main(void)
{
	char input[MAX_INPUT_LEN];

	while (1)
	{
	printf("$ ");

	if (!fgets(input, sizeof(input), stdin))
		exit(1);
	size_t len = strlen(input);

	if (len > 0 && input[len - 1] == '\n')
		input[len - 1] = '\0';
	char *args[MAX_INPUT_LEN], *token = strtok(input, " ");
	int i = 0;

	while (token)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;
	pid_t pid = fork();

	if (pid == -1)
		exit(1);

	if (pid == 0)
	{
		execvp(args[0], args);
		exit(1);
	}
	else
	{
		int status;

		wait(&status);
	}
}

	return (0);
}
