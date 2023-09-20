#include "main.h"

/**
 * _strdup - duplicate a string.
 * @src: source.
 * Return: destination.
 */
char *_strdup(const char *src)
{
	size_t len = _strlen(src);
	char *dest = (char *)malloc(len + 1);

	if (src == NULL)
	{
		return (NULL);
	}
	if (dest != NULL)
	{
		_strcpy(dest, src);
	}
	return (dest);
}
