#include <stdio.h>
#include <stdlib.h>
/**
 *my_unsetenv - unset an environment variable
 *@name: vname of variable to unset
 *
 *Return: void
 */
void my_unsetenv(const char *name)
{
	if (unsetenv(name) != 0)
	{
		perror("unsetenv");
	}
}
