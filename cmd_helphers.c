/*
 * File: builtins.c
 * Author: Chidiadi E. Nwosu
 */

#include "main.h"

/**
 * get_cmd - get commands from the shell.
 *
 * Return: command input from the shell
 */
char *get_cmd()
{
	char *cmd = NULL;
	size_t size = 0;
	int n_read = 0;

	n_read = _getline(&cmd, &size, stdin);
	if (n_read == -1)
	{
		free(cmd);
		write(STDOUT_FILENO, "\n", 1);
		exit(EXIT_FAILURE);
	}

	if (n_read > 0 && cmd[n_read - 1] == '\n')
		cmd[n_read - 1] = '\0';

	return (_strip(check_comments(cmd)));
}



/**
 * get_cmd_path - get command path for input commands without path.
 * @cmd: command from shell
 * * Return: command input from the shell
 */
char *get_cmd_path(char *cmd)
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

	dir = split(path_copy, ":");
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

	if (get_cmd_func(args[0]))
	{
		get_cmd_func(args[0])(args, prog, hist);
		return (exit_v = 0);
	}

	if (*args[0] != '/')
	{
		path = get_cmd_path(args[0]);
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

	if (echo_cmd(path, args) == 0)
	{
		if (*args[0] != '/')
			free(path);
		return (0);
	}
	exec_cmd(path, args);

	if (*args[0] != '/')
		free(path);

	return (0);
}




/**
 * exec_cmd - executes commands from the shell.
 * @arg: executable
 * @args: input commands.
 *
 * Return: command input from the shell
 */
int exec_cmd(char *arg, char **args)
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

	return (WEXITSTATUS(status));
}




/**
 * echo_cmd - checks for $ in the echo command
 * @arg: executable
 * @args: input commands.
 *
 * Return: 0 on success, -1 on failure
 */
int echo_cmd(char *arg, char **args)
{
	if (_strcmp(arg, "/usr/bin/echo") == 0 && *(args[1]) == '$')
	{

		if (_strcmp(args[1], "$$") == 0)
		{
			char *pid = _itoa(getpid());

			write(STDOUT_FILENO, pid, _strlen(pid));
			write(STDOUT_FILENO, "\n", 1);
			free(pid);
		}
		else if (_strcmp(args[1], "$?") == 0)
		{
			char *_exit_v = _itoa(exit_v);

			write(STDOUT_FILENO, _exit_v, _strlen(_exit_v));
			write(STDOUT_FILENO, "\n", 1);
			free(_exit_v);
		}
		else
		{
			char *tmp = _strdup(args[1] + 1);
			char *env = _getenv(tmp);

			write(STDOUT_FILENO, env, _strlen(env));
			write(STDOUT_FILENO, "\n", 1);
			free(tmp);
		}
		return (0);
	}
	return (-1);
}
