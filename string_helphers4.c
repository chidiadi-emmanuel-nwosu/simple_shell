/*
 * File: string_helphers4.c
 * Author: Chidiadi E. Nwosu
 */

#include "main.h"
/**
 * _strdup - returns a pointer to a newly allocated space
 *           in memory, which contains a copy of the string
 *           given as parameter.
 * @str: input string
 *
 * Return: array pointer
 */
char *_strdup(char *str)
{
	if (str == NULL)
	{
		return (NULL);
	}
	else
	{
		int i = 0, j;
		char *ptr;

		while (*(str + i))
			i++;

		ptr = malloc(sizeof(char) * i + 1);
		if (ptr == NULL)
			return (NULL);

		for (j = 0; j < i; j++)
			*(ptr + j) = *(str + j);

		ptr[i] = '\0';

		return (ptr);
	}
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




/**
 * _realloc - reallocates a memory block using malloc and free
 * @ptr: pointer to the memory previously allocated
 * @old_size: the size, in bytes, of the allocated space for ptr
 * @new_size: the new size, in bytes of the new memory block
 *
 * Return: pointer to the allocated memory
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *p;
	unsigned int i = 0;

	if (new_size == old_size)
	{
		return (ptr);
	}
	else if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	else if (ptr == NULL)
	{
		p = malloc(new_size);
		if (p == NULL)
			return (NULL);
		else
			return (p);
	}
	else
	{
		char *cast_p, *cast_ptr;

		p = malloc(new_size);
		if (p == NULL)
			return (NULL);
		cast_p = (char *)p;
		cast_ptr = (char *)ptr;
		for (; i < old_size; i++)
			cast_p[i] = cast_ptr[i];

		cast_p = (void *)cast_p;

		free(cast_ptr);
		return (cast_p);
	}
}




/**
 * _strncpy - copies strings
 * @dest: destination string
 * @src: source string
 * @n: bytes from src
 *
 * Return: dest
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i = 0;

	while (i < n)
	{
		dest[i] = src[i];
		if (dest[i] == '\0')
			break;
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
