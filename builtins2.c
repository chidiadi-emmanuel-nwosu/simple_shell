/*
 * File: builtins2.c
 * Author: Chidiadi E. Nwosu
 */

#include "main.h"


/**
 * setenv_cmd - implements setenv command
 * @args: arguments passed in.
 * @prog: program name.
 * @hist: history counter.
 *
 * Return: 0 on success, -1 on failure
 */
int setenv_cmd(char **args, char *prog, int hist)
{
	if (args[1] && args[2])
		_setenv(args[1], args[2], 0);

	(void)prog;
	(void)hist;
	return (0);
}




/**
 * unsetenv_cmd - implements unsetenv command
 * @args: arguments passed in.
 * @prog: program name.
 * @hist: history counter.
 *
 * Return: 0 on success, -1 on failure
 */
int unsetenv_cmd(char **args, char *prog, int hist)
{
	if (args[1])
		_unsetenv(args[1]);

	(void)prog;
	(void)hist;
	return (0);
}
