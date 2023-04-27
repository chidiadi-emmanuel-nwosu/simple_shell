/*
 * File: string_helphers.c
 * Author: Chidiadi E. Nwosu
 */

#include "main.h"

/**
 * _strlen - returns the length of a string
 * @s: string length to return
 *
 * Return: void
 */
int _strlen(char *s)
{
	int count = 0;

	while ((*(s++) != '\0'))
		count++;

	return (count);
}




/**
 * _strcpy - copies string
 * @dest: destination string
 * @src: source string
 *
 * Return: dest
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == NULL)
		return (NULL);

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}

	dest[i] = '\0';

	return (dest);
}




/**
 * _strcmp - compares two strings
 * @s1: string1
 * @s2: string2
 *
 * Return: 0 if s1 and s2 are the same, +ve or -ve value otherwise
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;
	int sum;

	while (!(s1[i] == '\0' || s2[i] == '\0'))
	{
		sum = s1[i] - s2[i];

		if (sum != 0)
			break;
		i++;
	}
	return (sum);
}




/**
 * _strncmp - compares two strings
 * @s1: string1
 * @s2: string2
 * @n: max number of bytes to check
 *
 * Return: 0 if s1 and s2 are the same, +ve or -ve value otherwise
 */
int _strncmp(char *s1, char *s2, int n)
{
	int i = 0;
	int sum;

	while (i < n)
	{
		if (s1[i] == '\0' || s2[i] == '\0')
			return (-1);

		sum = s1[i] - s2[i];

		if (sum != 0)
			break;
		i++;
	}
	return (sum);
}


/**
 * _strcat - concatenates two strings
 * @dest: destination string
 * @src: source string
 *
 * Return: dest
 */
char *_strcat(char *dest, char *src)
{
	int i = 0;

	while (1)
	{
		if (dest[i] == '\0')
		{
			int j = 0;

			while (1)
			{
				dest[i++] = src[j++];

				if (src[j - 1] == '\0')
					break;
			}

			break;
		}
		i++;
	}
	return (dest);
}
