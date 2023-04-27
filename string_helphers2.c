/*
 * File: string_helphers2.c
 * Author: Chidiadi E. Nwosu
 */

#include "main.h"

/**
 * _getline - custom getline that reads input from a stream
 * @lineptr: a buffer to store read input
 * @n: size of the buffer
 * @stream: input stream
 *
 * Return: number of bytes read
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	char *buffer = NULL;
	ssize_t buf_size = 0;

	if (!stream)
		stream = stdin;
	if (!lineptr)
		return (-1);

	if (*lineptr == NULL)
		*n = 0;
	else
		buf_size = *n;

	return (_readline(buffer, lineptr, n, &buf_size));

}




/**
 * readline - helper to _getline function
 * @lineptr: a buffer to store read input
 * @n: size of the buffer
 * @buffer: input storage
 * @buf_size: size of intitial read
 *
 * Return: number of bytes read
 */
ssize_t _readline(char *buffer, char **lineptr, size_t *n, ssize_t *buf_size)
{
	ssize_t read_bytes = 0;

	while (TRUE)
	{
		ssize_t r;

		if (!(*buf_size))
		{
			*buf_size = BUF_SIZE;
			buffer = malloc(*buf_size);
			if (!buffer)
				return (-1);
		}
		else if (read_bytes >= *buf_size)
		{
			buffer = _realloc(buffer, *buf_size, *buf_size * 2);
			if (!buffer)
				return (-1);
			*buf_size *= 2;
		}

		r = read(STDIN_FILENO, buffer + read_bytes, *buf_size - read_bytes);
		if (r == -1 || (r == 0 && read_bytes == 0))
		{
			free(buffer);
			return (-1);
		}
		if (!r)
			break;
		read_bytes += r;
		if (buffer[read_bytes - 1] == '\n')
		{
			buffer[read_bytes - 1] = '\0';
			break;
		}
	}
	*lineptr = buffer;
	*n = *buf_size;

	return (read_bytes);
}




/**
 * _strip - function thaat removes white spaces from left and right
 * @str: input string
 *
 * Return: stripped string
 */

char *_strip(char *str)
{
	int i = 0, j = 0;
	char *sstr;

	sstr = malloc(_strlen(str) + 1);
	if (!sstr)
		return (NULL);

	while (str[i] == ' ')
		i++;

	while (str[i])
	{
		if (str[i] == ' ' && (str[i + 1] == ' ' || str[i + 1] == '\0'))
		{
			i++;
			continue;
		}
		sstr[j++] = str[i++];
	}

	sstr[j] = '\0';

	free(str);
	return (sstr);
}



/**
 * _memset - fills memory with a constant byte
 * @s: memory area
 * @b: constant byte
 * @n: number of bytes
 *
 * Return: pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		*(s + i) = b;
	return (s);
}



/**
 * _memcpy - copies memory area
 * @dest: memory area destination
 * @src: memory area source
 * @n: number of bytes
 *
 * Return: pointer to dest
 */
char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		*(dest + i) = src[i];
	return (dest);
}
