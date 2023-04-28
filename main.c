/*
 * File: builtins.c
 * Author: Chidiadi E. Nwosu
 */

#include "main.h"


/**
 * main - UNIX command line interpreter.
 * @ac: number of commandline arguments.
 * @av: array of commandline arguments.
 *
 * Return: 0 (success)
 */
int main(__attribute__((unused)) int ac, char **av)
{
	int hist = 0;
	char *prog = av[0];

	if (!isatty(STDIN_FILENO))
		_non_isatty(prog, &hist);

	else if (ac != 1)
		file_input(av, prog, &hist);

	else
		_isatty(prog, &hist);

	return (0);
}




/**
 * prompt - prompts the shell.
 *
 * Return: void
 */
void prompt(void)
{
	write(STDOUT_FILENO, "chiElo$ ", 8);
	fflush(stdout);
}


/**
 * signal_handler - reprompts the shell.
 * @signal: input signal
 *
 * Return: void
 */
void signal_handler(__attribute__((unused)) int signal)
{
	write(STDOUT_FILENO, "\n", 1);
	prompt();
}


/**
 * free_args - free args
 * @args: input
 *
 * Return: void
 */
void free_args(char **args)
{
	int i = 0;

	for (; args[i]; i++)
		free(args[i]);
	free(args);
}
