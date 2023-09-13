#include "main.h"

int tokenize_input(char *line, char *tokens[], char *delimiters)
{
	int token_count = 0;
	char *token = strtok(line, delimiters);
	while (token != NULL)
	{
		tokens[token_count++] = token;
		token = strtok(NULL, delimiters);
	}
	return (token_count);
}

void sigint_handler(int signo)
{
	(void)signo;
	display("\n");
}

int main(int token_count, char *tokens[MAX_TOKENS], char **env)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	int status;
	pid_t pid;
	char *X;

	signal(SIGINT, sigint_handler);
	while (true)
	{
		display("($) ");
		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			break; /* Exit on Ctrl+D (EOF)*/
		}
		if (line[_strlen(line) - 1] == '\n')
		{
			line[_strlen(line) - 1] = '\0';
		}
		token_count = tokenize_input(line, tokens, " ");
		if (token_count == 0)
		{
			continue; /* Empty input, go back to the prompt*/
		}
        /* Implement built-in commands*/
		if (_strcmp(tokens[0], "exit") == 0)
		{
			break; /* Exit the shell*/
		}
		else if (_strcmp(tokens[0], "cd") == 0)
		{
			if (token_count < 2)
			{
				X = "Usage: cd <directory>";
				write(STDERR_FILENO, X, _strlen(X));
				display("\n");
			}
			else
			{
				if (chdir(tokens[1]) != 0)
				{
					perror("cd");
				}
			}
			continue; /* Go back to the prompt*/
		}
		pid = fork();
		if (pid == 0)
		{ /* Child process*/
			execve(tokens[0], tokens, env);
			perror(tokens[0]);
			exit(EXIT_FAILURE);
		}
		else if (pid < 0)
		{
			perror("Fork failed");
		}
		else
		{
			waitpid(pid, &status, 0);
		}
	}
	free(line);
	return (0);
}

