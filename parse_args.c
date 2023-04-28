/*
 * File - parse_args.c
 * Authors: Chidiadi E. Nwosu && Eloghene Otiede
 */
#include "main.h"

/**
 * parse_args - split input into array of strings
 * @cmd: input
 * @delim: refrence delimeter
 *
 * Return: array of string on success, NULL on failure
 */
char **parse_args(char *cmd, const char *delim)
{
	char **args, *tok, *tmp;
	int i = 0;

	if (!cmd || !delim)
		return (NULL);

	tmp = _strdup(cmd);

	tok = _strtok(tmp, delim);
	for (; tok; tok = _strtok(NULL, delim))
		i++;
	free(tmp);

	args = malloc(sizeof(char *) * (i + 1));
	if (!args)
		return (NULL);

	tok = _strtok(cmd, delim);
	for (i = 0; tok; tok = _strtok(NULL, delim))
		args[i++] = _strdup(tok);

	args[i] = NULL;

	return (args);
}





/**
 * _strtok - breaks a string into a sequence of zero or more nonempty tokens.
 * @str: input string
 * @delim: specifies a set of bytes that delimit the tokens in the
 *         parsed string.
 *
 * Return: pointer to the next token, or NULL if there are no more tokens.
 */
char *_strtok(char *str, const char *delim)
{
	static char *saveptr;
	char *tok;

	if (str)
		saveptr = str;
	if (!saveptr)
		return (NULL);

	tok = saveptr;
	while (*saveptr)
	{
		const char *d = delim;

		while (*d)
		{
			if (*saveptr == *d)
			{
				*saveptr = '\0';
				saveptr++;

				if (tok != saveptr)
				{
					return (tok);
				}
				else
				{
					tok++;
					break;
				}
			}
			d++;
		}
		saveptr++;
	}
	saveptr = NULL;
	if (tok == saveptr)
		return (NULL);
	else
		return (tok);
}
