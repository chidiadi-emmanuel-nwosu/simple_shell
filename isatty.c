/*
 * File: isatty.c
 * Author: Chidiadi E. Nwosu
 */

#include "main.h"

/**
 * _non_isatty - runs non-interactive mode with an input from pipe
 *
 * Return: void
 */
void _non_isatty(void)
{
	char buffer[BUF_SIZE], **tmp;
	ssize_t n;

	n = read(STDIN_FILENO, buffer, BUF_SIZE);
	buffer[n - 1] = '\0';

	tmp = split(buffer, "\n");

	for (n = 0; tmp[n]; n++)
		handle_cmd(tmp[n]);
	printf("%li\n", n);

	free_args(tmp);

	exit(0);
}




/**
 * _isatty - runs interactive mode of the shell
 *
 * Return: void
 */
void _isatty(void)
{
	char *cmd;

	signal(SIGINT, signal_handler);
	while (TRUE)
	{
		prompt();
		cmd = get_cmd();
		if (*cmd == ';' || *cmd == '|' || *cmd == '&')
		{
			syntax_error(cmd);
			free(cmd);
			continue;
		}

		handle_cmd(cmd);
		free(cmd);
	}
}




/**
 * file_input - runs non-interactive mode with an input from file
 * @av: input from commandline
 *
 * Return: void
 */
void file_input(char **av)
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
		handle_cmd(tmp[n]);

	free_args(tmp);
	close(fd);
	exit(0);
}
