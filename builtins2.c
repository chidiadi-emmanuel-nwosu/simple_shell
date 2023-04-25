/*
 * File: builtins2.c
 * Author: Chidiadi E. Nwosu
 */

#include "main.h"


/**
 * setenv_cmd - implements setenv command
 * @args: arguments passed in.
 *
 * Return: 0 on success, -1 on failure
 */
int setenv_cmd(char **args)
{
	if (args[1] == NULL)
	{
		cmd_error(args[0]);
	}

	else if (args[2] == NULL)
	{
		if (_setenv(args[1], "", 1) == -1)
			perror(args[1]);
	}

	else
	{
		if (_setenv(args[1], args[2], 1) == -1)
			perror(args[1]);
	}

	return (0);
}




/**
 * unsetenv_cmd - implements unsetenv command
 * @args: arguments passed in.
 *
 * Return: 0 on success, -1 on failure
 */
int unsetenv_cmd(char **args)
{
	if (args[1] == NULL)
		cmd_error(args[0]);

	else
		_unsetenv(args[1]);

	return (0);
}
