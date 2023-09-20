#include "main.h"

/**
 * _strcmp - string compare function.
 * @str1: A string.
 * @str2: A string.
 * Return: 0 success
 */
int _strcmp(const char *str1, const char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}

	return (*str1 - *str2);
}
