#include "main.h"

/**
 * _strcat - str concatination.
 * @dest: destination.
 * @src: source.
 * Return: dest_start.
 */
char *_strcat(char *dest, const char *src)
{
	char *dest_start;

	if (dest == NULL || src == NULL)
	{
		return (NULL);
	}

	dest_start = dest;
	while (*dest != '\0')
	{
		dest++;
	}
	while (*src != '\0')
	{
		*dest++ = *src++;
	}
	*dest = '\0';
	return (dest_start);
}
