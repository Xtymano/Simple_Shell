#include <stdio.h>
#include <string.h>

/*
 * countwords - count the words in a string
 * @str: The input string to count words in
 *
 * Return: The number of words in the string
 */

int countwords (char* str)
{
	int count = 0;
	int isword = 0; // flag to check a word

	for (int y = 0; str[y]) != '\0'; y++)
	{
		if (str[y] == ' ' || str [y] == '\ln' || str [y] == '\t')
		{
			isword = 0;
		}
		else if (isword == 0)
		{
			count++;
			isword = 1;
		}
	
	}
	return count;
}

/**
 *  main - Entry point of the program
 *
 * Return: Always 0 (success)
 */

int main()
{
	char str[1000];

	printf("Enter a string: ");
	fgets(str, sizeof(str), stdin);

	int words = countwords(str);
	printf("Number of character in the string: %d\n", character);

	return 0;
}
