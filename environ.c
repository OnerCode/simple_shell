<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include "shell.h"
=======
#include <stddef.h>
#include <stdio.h>
>>>>>>> master
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
