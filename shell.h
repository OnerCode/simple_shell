#ifndef SHELL_H
#define SHELL_H

void execute_command(char **args, int com_num, const char *prg_nme);
void print_environment(void);
void my_unsetenv(const char *name);
void my_setenv(const char *name, const char *value, int overwrite);

#endif
