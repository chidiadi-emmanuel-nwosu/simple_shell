/*
 * File: builtins.c
 * Author: Chidiadi E. Nwosu
 */

#include "main.h"

/**
 * cd_cmd - implements cd command
 * @args: arguments passed in.
 *
 * Return: 0 on success, -1 on failure
 */
int cd_cmd(char **args)
{
	if (args[1] == NULL)
		chdir(_getenv("HOME"));

	else if (chdir(args[1]) == -1)
		perror(args[1]);

	return (0);
}



/**
 * env_cmd - implements env command
 * @args: arguments passed in.
 *
 * Return: 0 on success, -1 on failure
 */
int env_cmd(__attribute__((unused)) char **args)
{
	char *var = *environ;

	while (var)
	{
		write(STDOUT_FILENO, var, _strlen(var));
		write(STDOUT_FILENO, "\n", 1);
		var = *(environ++);
	}

	return (0);
}



/**
 * exit_cmd - implements exit command
 * @args: arguments passed in.
 *
 * Return: 0 on success, -1 on failure
 */
int exit_cmd(char **args)
{
	if (args[1] == NULL)
	{
		free_args(args);
		exit(0);
	}
	else
	{
		int status = _atoi(args[1]);

		free_args(args);
		exit(status);
	}

	return (0);
}
