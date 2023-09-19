#include <stddef.h>
#include <stdio.h>
/**
 * print_environment -  print env on output
 *
 * Return: void
 */

void print_environment(void)
{
	extern char **environ; /* acess the environment variables*/

	char **env = environ;

	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
}
