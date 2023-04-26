/*
 * File: cmd_handlers.c
 * Author: Chidiadi E. Nwosu
 */

#include "main.h"


/**
 * check_comments - checks if the input contains '#'
 * @s: string input
 *
 * Return: input without comments
 */
char *check_comments(char *s)
{
	int i = 0;
	char *ss = malloc(_strlen(s) + 1);

	if (ss == NULL)
		return (NULL);

	while (s[i])
	{
		if (s[i] == '#')
		{
			ss[i] = '\0';
			free(s);
			return (ss);
		}
		ss[i] = s[i];
		i++;
	}

	free(ss);
	return (s);
}




/**
 * handle_cmd - handle input from commandline
 * @cmd: input
 *
 * Return: void
 */
void handle_cmd(char *cmd)
{
	int i = 0;
	char **tok = split(cmd, ";");

	while (tok[i])
	{
		char **subtok = split(tok[i], " ");

		if (_strcmp(subtok[0], "exit") == 0)
		{
			if (subtok[1] == NULL)
			{
				free(cmd);
				free_args(subtok);
				free_args(tok);
				exit(0);
			}
			else
			{
				int status = _atoi(subtok[1]);

				free(cmd);
				free_args(subtok);
				free_args(tok);
				exit(status);
			}
		}
		exec_cmds(subtok);
		free_args(subtok);
		i++;
	}
	free_args(tok);
}



/**
 * split - split input into array of strings
 * @cmd: input
 * @delim: refrence delimeter
 *
 * Return: array of string on success, NULL on failure
 */
char **split(char *cmd, char *delim)
{
	char **args, *tmp = cmd;
	int i = 0, j = 0, height = 0, width = 0;
	int row = 0, start = 0, ref, n = _strlen(delim);

	for (; cmd[j]; j++)
	{
		if (_strncmp(cmd + j, delim, n) == 0 || cmd[j + 1] == '\0')
			height++;
	}
	args = malloc(sizeof(*args) * (height + 1));
	if (!args)
		return (NULL);

	while (*cmd)
	{
		i++;
		if (_strncmp(cmd, delim, n) == 0 || *(cmd + 1) == '\0')
		{
			if (*(cmd + 1) != '\0')
				ref = i - 1;
			else
				ref = i;
			width = ref - start;
			args[row] = malloc(sizeof(char) * width + 1);
			if (args[row] == NULL)
			{
				free_args(args);
				return (NULL);
			}
			_strncpy(args[row], tmp + start, width);
			args[row][width] = '\0';
			args[row] = _strip(args[row]);

			start = ref + n;
			row++;
		}
		cmd++;
	}
	args[row] = NULL;
	return (args);
}
