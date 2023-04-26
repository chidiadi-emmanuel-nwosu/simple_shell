/*
 * File: string_helphers2.c
 * Author: Chidiadi E. Nwosu
 */

#include "main.h"

/**
 * _getline - custom getline that reads input from a stream
 * @lineptr: a buffer to store read input
 * @n: size of the buffer
 * @str: input stream
 *
 * Return: number of bytes read
 */

ssize_t _getline(char **lineptr, size_t *n, __attribute__((unused)) FILE * str)
{
	ssize_t read_byte = 0;
	size_t count = 0;
	char c;

	if (*lineptr == NULL || *n == 0)
	{
		*lineptr = malloc(BUF_SIZE);
		if (*lineptr == NULL)
			return (-1);

		*n = MAX_LINE;
	}

	read_byte = read(STDIN_FILENO, &c, 1);

	while (read_byte)
	{
		if (read_byte == -1)
		{
			free(*lineptr);
			return (-1);
		}

		if (c == '\n')
			break;

		(*lineptr)[count++] = c;
		read_byte = read(STDIN_FILENO, &c, 1);
	}

	if (read_byte == 0 && count == 0)
		return (-1);

	(*lineptr)[count] = '\0';
	return (read_byte);
}



/**
 * _atoi - convert a string to an integer
 * @s: string to be converted
 *
 * Return: converted int value
 */
int _atoi(char *s)
{
	int c_nve = 0;
	int i = 0;
	unsigned int result = 0;

	while ((s[i] != '\0'))
	{
		if (s[i] >= '0' && s[i] <= '9')
			break;
		else if (s[i] == '-')
			c_nve++;

		i++;
	}

	while ((s[i] != '\0'))
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			break;

		result = result * 10 + s[i] - '0';
		i++;
	}

	if ((c_nve % 2) != 0)
		result = -result;

	return (result);
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
