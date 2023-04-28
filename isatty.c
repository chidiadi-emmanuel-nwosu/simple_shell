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
	char buffer[BUF_SIZE], **tmp, *buffer_d;
	ssize_t n;

	n = read(STDIN_FILENO, buffer, BUF_SIZE);
	buffer[n - 1] = '\0';

	buffer_d = malloc(n + 1);
	if (!buffer_d)
		exit(EXIT_FAILURE);
	buffer_d = _strcpy(buffer_d, buffer);
	buffer_d = _strip(check_comments(buffer_d));

	tmp = split(buffer_d, "\n");

	for (n = 0; tmp[n]; n++)
		handle_cmd(tmp[n], prog, hist);
	free_args(tmp);
	free(buffer_d);

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
	char buffer[BUF_SIZE], *buffer_d = NULL, **tmp;
	ssize_t fd = 0, r = 0, n = 0;
	size_t count = 0;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		cannot_open_error(av[1], prog, *hist);
		exit(127);
	}

	while ((r = read(fd, buffer, BUF_SIZE)) > 0)
	{
		if (r == -1)
		{	free(buffer_d);
			exit(127);
		}
		buffer_d = _realloc(buffer_d, count, count + r + 1);
		for (n = 0; n < r; n++)
			buffer_d[count++] = buffer[n];
	}
	close(fd);

	buffer_d[count] = '\0';
	buffer_d = _strip(check_comments(buffer_d));
	tmp = parse_args(buffer_d, "\n");

	for (n = 0; tmp[n]; n++)
		handle_cmd(tmp[n], prog, hist);

	free(buffer_d);
	free_args(tmp);
	close(fd);
}
