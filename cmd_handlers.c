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
 * @prog: program name.
 * @hist: history counter.
 *
 * Return: void
 */
void handle_cmd(char *cmd, char *prog, int *hist)
{
	int i = 0;
	char **args = NULL;

	*hist += 1;

	if (!cmd || !(*cmd))
		return;
	if (check_syntax(cmd, prog, *hist))
		return;

	args = parse_args(cmd, ";");
	while (args[i])
	{
		char **sub_args = parse_args(args[i], " ");

		if ((i == 0) && (_strcmp(sub_args[i], "exit") == 0))
		{
			int status = 0;

			if (sub_args[1])
				status = _atoi(sub_args[1]);

			free_args(sub_args);
			free_args(args);
			free(cmd);
			exit(status);
		}
		exec_cmds(sub_args, prog, *hist);
		free_args(sub_args);
		i++;
	}
	free_args(args);
}



/**
 * parse_args - split input into array of strings
 * @cmd: input
 * @delim: refrence delimeter
 *
 * Return: array of string on success, NULL on failure
 */
char **parse_args(char *cmd, const char *delim)
{
	char **args, *tok, *cmd_dup;
	int i = 0;

	if (!cmd || !delim)
		return (NULL);

	cmd_dup = _strdup(cmd);

	tok = _strtok(cmd_dup, delim);
	for (; tok; tok = _strtok(NULL, delim))
		i++;
	free(cmd_dup);

	args = malloc(sizeof(char *) * (i + 1));
	if (!args)
		return (NULL);

	tok = _strtok(cmd, delim);
	for (i = 0; tok; tok = _strtok(NULL, delim))
		args[i++] = _strip(_strdup(tok));

	args[i] = NULL;

	return (args);
}



/**
 * check_syntax - checks for syntax_error
 * @cmd: input
 * @prog: program name.
 * @hist: history counter.
 *
 * Return: TRUE or FALSE
 */
int check_syntax(char *cmd, char *prog, int hist)
{
	int i = 0;

	for (; cmd[i]; i++)
	{
		if (*cmd == ';' || *cmd == '|' || *cmd == '&')
		{
			syntax_error(cmd, prog, hist);
			return (TRUE);
		}
		if (cmd[i] == ';' && (cmd[i + 1] == ';' ||
					cmd[i + 1] == '|' || cmd[i + 1] == '&'))
		{
			syntax_error(cmd + i + 1, prog, hist);
			return (TRUE);
		}
		if (cmd[i] == '|' && (cmd[i + 1] == ';' || cmd[i + 1] == '&'))
		{
			syntax_error(cmd + i + 1, prog, hist);
			return (TRUE);
		}
		if (cmd[i] == '&' && (cmd[i + 1] == ';' || cmd[i + 1] == '|'))
		{
			syntax_error(cmd + i + 1, prog, hist);
			return (TRUE);
		}
	}

	return (FALSE);
}
