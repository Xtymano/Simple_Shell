#include "main.h"

/**
 * _isdigit - checks for digit.
 * @c: char.
 * Return: 1 on succes.
 */
int _isdigit(char c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

