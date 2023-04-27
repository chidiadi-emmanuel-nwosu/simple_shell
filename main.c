/*
 * File - main.c
 * Authors: Chidiadi E. Nwosu && Eloghene Otiede
 */
#include "main.h"

/**
 * main - entry point
 * @ac: number of command line arguments(av).
 * @av: array of command line arguments
 *
 * Return: 0 on success
 */
int main(__attribute__((unused)) int ac, char **av)
{
	shell_t cmd;
	const char *delim = " \t\n\r";
	char *buffer = NULL;
	ssize_t r;
	size_t n;

	cmd.prog = av[0];
	cmd.hist = 0;

	prompt();
	signal(SIGINT, signal_handler);
	while ((r = getline(&buffer, &n, stdin)) != -1)
	{
		cmd.hist++;
		if (r > 0 && (buffer[r - 1]) == '\n')
			buffer[r - 1] = '\0';
		cmd.args = parse_args(buffer, delim);

		exec_cmds(cmd.args, cmd.prog, cmd.hist);
		free_args(cmd.args);

		prompt();
	}

	free(buffer);
	(void)av;
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
