#include "main.h"

char *_strdup(const char *src)
{
	size_t len = strlen(src);
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
