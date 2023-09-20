#include "main.h"

/**
 * _strcpy - string copy.
 * @dest: destination.
 * @src: source.
 * Return: dest_start.
 */
char *_strcpy(char *dest, const char *src)
{
	char *dest_start = dest;

	if (dest == NULL || src == NULL)
	{
		return (NULL);
	}

	while (*src != '\0')
	{
		*dest++ = *src++;
	}
	*dest = '\0';
	return (dest_start);
}
