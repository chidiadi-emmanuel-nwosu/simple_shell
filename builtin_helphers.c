/*
 * File: builtins.c
 * Author: Chidiadi E. Nwosu
 */

#include "main.h"

/**
 * get_cmd_func - function pointer for builtins commands.
 * @s: input command.
 *
 * Return: called function
 */
int (*get_cmd_func(char *s))(char **)
{
	op_t builtins[] = {
		{"cd", cd_cmd},
		{"exit", exit_cmd},
		{"setenv", setenv_cmd},
		{"unsetenv", unsetenv_cmd},
		{NULL, NULL}
	};
	int i = 0;

	while (builtins[i].op)
	{
		if (_strcmp(builtins[i].op, s) == 0)
			return (builtins[i].f);
		i++;
	}
	return (NULL);
}
