/*
 * File: env.c
 * Author: Chidiadi E. Nwosu
 */

#include "main.h"

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




/**
 * _getenv - get an environment variable
 * @name: variable
 *
 * Return: pointer to found variable on success, NULL on failure
 */
char *_getenv(char *name)
{
	char **env = environ;
	size_t len = _strlen(name);

	while (*env != NULL)
	{
		if (_strncmp(name, *env, len) == 0 && (*env)[len] == '=')
		{
			return (&((*env)[len + 1]));
		}
		env++;
	}

	return (NULL);
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
 * _itoa - convert a positive integer to string
 * @num: integr to be converted
 *
 * Return: converted int value
 */
char *_itoa(int num)
{
	int check_neg = num;
	char *output, tmp;
	unsigned int i, len = 0;

	output = malloc(1);
	if (output == NULL)
		return (NULL);
	if (num < 0)
		num = -num;
	else if (num == 0)
	{
		output[len++] = '0';
		output = _realloc(output, len, len + 1);
		output[len] = '\0';
		return (output);
	}
	while (num)
	{
		output[len++] = num % 10 + '0';
		num = num / 10;
		output = _realloc(output, len, len + 1);
		if (output == NULL)
			return (NULL);
	}
	if (check_neg < 0)
	{
		output[len++] = '-';
		output = _realloc(output, len, len + 1);
		if (output == NULL)
			return (NULL);
	}
	output[len] = '\0';
	for (i = 0; i < len / 2; i++)
	{
		tmp = output[i];
		output[i] = output[len - i - 1];
		output[len - i - 1] = tmp;
	}

	return (output);
}
