/*
 * File: env.c
 * Author: Chidiadi E. Nwosu
 */

#include "main.h"


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
 * _setenv - change or add an environment variable
 * @name: variable
 * @value: value attached to the variable
 * @overwrite: 1 to overwrite existing, 0 otherwise
 *
 * Return: 0 on succes, -1 otherwise
 */
int _setenv(char *name, char *value, int overwrite)
{
	char **env = environ;
	char *new_value, *old_value;
	size_t name_len = _strlen(name), value_len = _strlen(value);

	new_value = malloc(name_len + value_len + 2);
	if (!new_value)
		return (-1);

	while (*env)
	{
		if (_strncmp(*env, name, _strlen(name)) == 0 && (*env)[_strlen(name)] == '=')
		{
			if (!overwrite)
			{
				free(new_value);
				return (0);
			}

			_memcpy(new_value, name, name_len);
			new_value[name_len] = '=';
			_memcpy(new_value + name_len + 1, value, value_len);
			new_value[name_len + value_len + 1] = '\0';
			old_value = *env;
			*env = new_value;

			free(old_value);
			return (0);
		}
		env++;
	}

	_memcpy(new_value, name, name_len);
	new_value[name_len] = '=';
	_memcpy(new_value + name_len + 1, value, value_len);
	new_value[name_len + value_len + 1] = '\0';
	*(env++) = _strdup(new_value);
	*env = NULL;
	free(new_value);

	return (0);
}





/**
 * _unsetenv - removes an environment variable
 * @name: variable
 *
 * Return: 0 on succes, -1 otherwise
 */
int _unsetenv(char *name)
{
	char **env = environ;

	while (*env)
	{
		if (_strncmp(*env, name, _strlen(name)) == 0 && (*env)[_strlen(name)] == '=')
		{
			char **tmp = env;

			while (*tmp)
			{
				*tmp = *(tmp + 1);
				tmp++;
			}
			return (0);
		}
		env++;
	}

	return (-1);
}

