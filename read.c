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

bool _strsub(const char *haystack, const char *needle) {
 	 const char *temp_haystack = haystack;
         const char *temp_needle = needle;
	
	while (*haystack != '\0') {

        while (*temp_needle != '\0' && *temp_haystack == *temp_needle) {
            temp_haystack++;
            temp_needle++;
        }

        if (*temp_needle == '\0') {
            return true;
        }

        haystack++;
    }

    return false;
}
/**
 * execute_builtin_exit - exit from shell.
 */
void execute_builtin_exit(char *line)
{

	char *token = strtok(line, " ");

    if (token != NULL && strcmp(token, "exit") == 0) 
    {
        token = strtok(NULL, " "); 

        if (token != NULL) {
            /*exitStatus = atoi(token); 

            if (exitStatus == 0) {
                exit(2); 
            } else {*/
                exit(2); 
            }
        } else {
            exit(0); 
        }
    
}
