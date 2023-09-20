#include "main.h"

/**
 * read_input - gets input from the user.
 * @line: double pointer to char.
 * @len: size of chars.
 * Return: command.
 */
ssize_t read_input(char **line, size_t *len)
{
	return (getline(line, len, stdin));
}

/**
 * tokenize_input - devides command.
 * @line: a string.
 * @tokens: array of strings.
 * @delimiters: separators.
 * Return: number of tokens.
 */
int tokenize_input(char *line, char *tokens[], char *delimiters)
{
	int token_count = 0;
	char *token;

	token = strtok(line, delimiters);
	while (token != NULL)
	{
		tokens[token_count++] = token;
		token = strtok(NULL, delimiters);
	}
	return (token_count);
}

/**
 * execute_builtin_exit - exit from shell.
 */
void execute_builtin_exit(void)
{
	exit(0);
}
