/*
 * File: errors.c
 * Author: Chidiadi E. Nwosu
 */

#include "main.h"

/**
 * cmd_error - prints command not found
 * @cmd: cmd input
 * @prog: program name.
 * @hist: history counter.
 *
 * Return: void
 */
void cmd_error(char *cmd, char *prog, int hist)
{
	char *hst = _itoa(hist);

	write(STDOUT_FILENO, prog, _strlen(prog));
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, hst, _strlen(hst));
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, cmd, _strlen(cmd));
	write(STDOUT_FILENO, ": not found\n", 12);
	free(hst);
}




/**
 * syntax_error - prints syntax error
 * @cmd: cmd input
 * @prog: program name.
 * @hist: history counter.
 *
 * Return: void
 */
void syntax_error(char *cmd, char *prog, int hist)
{
	if (hist || prog)
	{}
	write(STDOUT_FILENO, "syntax error near unexpected token `", 36);
	write(STDOUT_FILENO, cmd, 1);
	write(STDOUT_FILENO, "'\n", 2);
}
