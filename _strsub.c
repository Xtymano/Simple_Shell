#include <stdio.h>

/**
 * _strchr - str char.
 * @str: string.
 * @character: char
 * Return: null on fail
 */
char *_strchr(const char *str, int character)
{
	while (*str != '\0')
	{
		if (*str == character)
		{
			return ((char *)str);
		}
		str++;
	}
	return (NULL);
}
