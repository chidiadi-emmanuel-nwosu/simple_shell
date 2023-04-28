/*
 * File: isatty.c
 * Author: Chidiadi E. Nwosu
 */

#include "main.h"

/**
 * _non_isatty - runs non-interactive mode with an input from pipe
 * @prog: program name.
 * @hist: history counter.
 *
 * Return: void
 */
void _non_isatty(char *prog, int *hist)
{
	char *cmd = NULL, **tmp;
	size_t size = 0;
	int n_read = 0, n;

	n_read = _getline(&cmd, &size, stdin);
	if (n_read == -1)
	{
		free(cmd);
		write(STDOUT_FILENO, "\n", 1);
		exit(EXIT_FAILURE);
	}

	if (n_read > 0 && cmd[n_read - 1] == '\n')
		cmd[n_read - 1] = '\0';


	cmd = _strip(check_comments(cmd));
	tmp = split(cmd, "\n");

	for (n = 0; tmp[n]; n++)
		handle_cmd(tmp[n], prog, hist);
	free_args(tmp);
	free(cmd);

	exit(0);
}




/**
 * _isatty - runs interactive mode of the shell
 * @prog: program name.
 * @hist: history counter.
 *
 * Return: void
 */
void _isatty(char *prog, int *hist)
{
	char *cmd;

	signal(SIGINT, signal_handler);
	while (TRUE)
	{
		prompt();
		cmd = get_cmd();

		handle_cmd(cmd, prog, hist);
		free(cmd);
	}
}




/**
 * file_input - runs non-interactive mode with an input from file
 * @av: input from commandline
 * @prog: program name.
 * @hist: history counter.
 *
 * Return: void
 */
void file_input(char **av, char *prog, int *hist)
{
	char buffer[BUF_SIZE], **tmp;
	ssize_t fd = 0, n = 0;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		perror(av[1]);
		exit(EXIT_FAILURE);
	}

	n = read(fd, buffer, BUF_SIZE);
	buffer[n - 1] = '\0';

	tmp = split(buffer, "\n");

	for (n = 0; tmp[n]; n++)
		handle_cmd(tmp[n], prog, hist);

	free_args(tmp);
	close(fd);
	exit(0);
}
