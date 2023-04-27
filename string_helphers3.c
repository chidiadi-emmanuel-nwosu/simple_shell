/*
 * File: string_helphers3.c
 * Author: Chidiadi E. Nwosu
 */
#include "main.h"

/**
 * _strchr - locates a character in a string
 * @s: string input
 * @c: character to locate
 *
 * Return: pointer to first occurence a c
 */
char *_strchr(char *s, char c)
{
	int i = 0;

	do {
		if (*(s + i) == c)
			return (s + i);
		i++;
	} while (s[i - 1] != '\0');

	return ('\0');
}



/**
 * _strspn - gets the length of a prefix substring
 * @s: string input1
 * @accept: string input2
 *
 * Return: number of bytes from accept
 */
unsigned int _strspn(char *s, char *accept)
{
	int i = 0;
	int count = 0;

	while (s[i] != '\0')
	{
		int j = 0;

		while (accept[j] != '\0')
		{
			if (s[i] == accept[j])
			{
				count++;
				break;
			}
			j++;
		}
		if (accept[j] == '\0')
			break;
		i++;
	}
	return (count);
}



/**
 * _strpbrk - searches a string for any of a set of bytes.
 * @s: string input1
 * @accept: string input2
 *
 * Return: pointer to the byte in s that matches one of the
 *         bytes in accept, or NULL if no such byte is found
 */
char *_strpbrk(char *s, char *accept)
{
	int i = 0;

	while (s[i] != '\0')
	{
		int j = 0;

		while (accept[j] != '\0')
		{
			if (s[i] == accept[j])
				return (s + i);
			j++;
		}
		i++;
	}
	return (s = 0);
}




/**
 * _strstr - locates a substring
 * @haystack: string
 * @needle: substring to locate
 *
 * Return: pointer to the beginning of the located subtring,
 *         or NULL if the substring is not found
 */
char *_strstr(char *haystack, char *needle)
{
	int i;

	if (*needle == 0)
		return (haystack);

	while (*haystack)
	{
		i = 0;

		if (needle[i] == haystack[i])
		{
			do {
				if (needle[i + 1] == '\0')
					return (haystack);
				i++;
			} while (needle[i] == haystack[i]);
		}
		haystack++;
	}
	return (NULL);
}






/**
 * _strtok - breaks a string into a sequence of zero or more nonempty tokens.
 * @str: input string
 * @delim: specifies a set of bytes that delimit the tokens in the
 *         parsed string.
 *
 * Return: pointer to the next token, or NULL if there are no more tokens.
 */
char *_strtok(char *str, const char *delim)
{
	static char *saveptr;
	char *tok;

	if (str)
		saveptr = str;
	if (!saveptr)
		return (NULL);

	tok = saveptr;
	while (*saveptr)
	{
		const char *d = delim;

		while (*d)
		{
			if (*saveptr == *d)
			{
				*saveptr = '\0';
				saveptr++;

				if (tok != saveptr)
				{
					return (tok);
				}
				else
				{
					tok++;
					break;
				}
			}
			d++;
		}
		saveptr++;
	}
	saveptr = NULL;
	if (tok == saveptr)
		return (NULL);
	else
		return (tok);
}
