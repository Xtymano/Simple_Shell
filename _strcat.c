#include "main.h"

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
