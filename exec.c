/*
 * File - main.c
 * Authors: Chidiadi E. Nwosu && Eloghene Otiede
 */

#include "main.h"

/**
 * exec_cmds - executes commands from the shell.
 * @args: input commands.
 * @prog: program name.
 * @hist: history counter.
 *
 * Return: command input from the shell
 */
int exec_cmds(char **args, char *prog, int hist)
{
	char *path;

	if (*args[0] != '/')
	{
		path = get_path(args[0]);
		if (!path)
		{
			cmd_error(args[0], prog, hist);
			return (exit_v = 127);
		}
	}
	else
	{
		path = args[0];
		if (access(path, X_OK) != 0)
		{
			cmd_error(args[0], prog, hist);
			return (exit_v = 127);
		}
	}

	exec_cmd(path, args, prog);

	if (*args[0] != '/')
		free(path);

	return (0);
}





/**
 * exec_cmd - executes commands from the shell.
 * @arg: executable
 * @args: input commands.
 * @prog: program name.
 *
 * Return: command input from the shell
 */
int exec_cmd(char *arg, char **args, char *prog)
{
	int status;
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		if (execve(arg, args, environ) == -1)
		{
			perror(arg);
			free(arg);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, &status, 0);

	(void)prog;
	errno = status % 255;
	return (errno);
}





/**
 * get_path - get command path for input commands without path.
 * @cmd: command from shell
 * * Return: command input from the shell
 */
char *get_path(char *cmd)
{
	int i = 0;
	char *path_env, *path, *path_copy, **dir;

	path_env = _getenv("PATH");
	if (!path_env)
		return (NULL);

	path = malloc(PATH_MAX);
	if (!path)
		return (NULL);

	path_copy = _strdup(path_env);
	if (!path_copy)
	{
		free(path);
		return (NULL);
	}

	dir = parse_args(path_copy, ":");
	while (dir[i])
	{

		_memset(path, 0, PATH_MAX);
		_strcat(path, dir[i]);
		_strcat(path, "/");
		_strcat(path, cmd);

		if (access(path, X_OK) == 0)
		{
			free_args(dir);
			free(path_copy);
			return (path);
		}
		i++;
	}

	free(path);
	free(path_copy);
	free_args(dir);
	return (NULL);
}
