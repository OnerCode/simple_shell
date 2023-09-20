#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 *my_setenv - set the environment varibles
 *@name: name of varible
 *@value: value to write
 *@overwrite: what to overite value to
 *
 *Return: void
 */
void my_setenv(const char *name, const char *value, int overwrite)
{
	if (overwrite || getenv(name) == NULL)
	{
		if (setenv(name, value, 1) != 0)
		{
			perror("setenv");
		}
	}
}
