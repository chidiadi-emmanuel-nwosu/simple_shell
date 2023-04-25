/*
 * File: errors.c
 * Author: Chidiadi E. Nwosu
 */

#include "main.h"

/**
 * cmd_error - prints command not found
 * @cmd: cmd input
 *
 * Return: void
 */
void cmd_error(char *cmd)
{
	write(STDOUT_FILENO, cmd, _strlen(cmd));
	write(STDOUT_FILENO, ": command not found\n", 20);
}




/**
 * syntax_error - prints syntax error
 * @cmd: cmd input
 *
 * Return: void
 */
void syntax_error(char *cmd)
{
	write(STDOUT_FILENO, "syntax error near unexpected token `", 36);
	write(STDOUT_FILENO, cmd, 1);
	write(STDOUT_FILENO, "'\n", 2);
}
