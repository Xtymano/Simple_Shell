#include "main.h"

/**
 * _strlen - string length.
 * @str: a string.
 * Return: length
 */
size_t _strlen(const char *str)
{
	size_t length = 0;

	while (*str != '\0')
	{
		length++;
		str++;
	}

	return (length);
}
