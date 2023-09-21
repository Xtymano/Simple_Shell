#include "main.h"

/**
 * _atoi - to int.
 * @str: string.
 * Return: int.
 */
int _atoi(char *str)
{
	int result = 0;
	int sign = 1;

	if (str == NULL || *str == '\0')
	{
		return (0);
	}

	if (*str == '+' || *str == '-')
	{
		sign = *str == '+' ? 1 : -1;
		str++;
	}

	while (*str != '\0')
	{
		if (*str < '0' || *str > '9')
		{
			return (0);
		}
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

