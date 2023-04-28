/*
 * File: builtins.c
 * Author: Chidiadi E. Nwosu
 */

#include "main.h"

/**
 * cd_cmd - implements cd command
 * @args: arguments passed in.
 * @prog: program name.
 * @hist: history counter.
 *
 * Return: 0 on success, -1 on failure
 */
int cd_cmd(char **args, char *prog, int hist)
{
	char cur_pwd[BUF_SIZE], *tmp;

	getcwd(cur_pwd, sizeof(cur_pwd));

	if (args[1] == NULL)
	{
		tmp = _getenv("HOME");
		if (tmp)
			chdir(_getenv("HOME"));
	}

	else if (*(args[1]) == '-')
	{
		tmp = _getenv("OLDPWD");
		if (tmp)
			chdir(_getenv("OLDPWD"));
	}

	else if (chdir(args[1]) == -1)
	{
		perror(args[1]);
	}

	_setenv("OLDPWD", cur_pwd, 1);
	(void)prog;
	(void)hist;
	return (0);
}



/**
 * env_cmd - implements env command
 * @args: arguments passed in.
 * @prog: program name.
 * @hist: history counter.
 *
 * Return: 0 on success, -1 on failure
 */
int env_cmd(char **args, char *prog, int hist)
{
	int i = 0;

	if (environ)
	{
		while (environ[i])
		{
			write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
			write(STDOUT_FILENO, "\n", 1);
			i++;
		}
	}

	(void)prog;
	(void)hist;
	(void)args;
	return (0);
}



/**
 * exit_cmd - implements exit command
 * @args: arguments passed in.
 * @prog: program name.
 * @hist: history counter.
 *
 * Return: 0 on success, -1 on failure
 */
int exit_cmd(char **args, char *prog, int hist)
{
	if (hist && prog)
	{}
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
