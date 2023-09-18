#include "main.h"

/*
 * countwords - count the words in a string
 * @str: The input string to count words in
 *
 * Return: The number of words in the string
 */
int _strlen(const char *str)
{
	int count = 0;
	int isword = 0;
	int y;

	for (y = 0; str[y] != '\0'; y++)
	{
		if (str[y] == ' ' || str[y] == '\n' || str[y] == '\t')
		{
			isword = 0;
		}
		else if (isword == 0)
		{
			count++;
			isword = 1;
		}
	
	}
	return (count);
}
