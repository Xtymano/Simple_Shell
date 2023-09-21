#include "main.h"

/**
 * execute_builtin_cd - execute cd.
 * @tokens: array of strings.
 */
void execute_builtin_cd(char *tokens[])
{
	if (tokens[1] == NULL)
	{
		display("Usage: cd <directory>\n");
	}
	else
	{
		if (chdir(tokens[1]) != 0)
		{
			perror("cd");
		}
	}
}

/**
 * execute_builtin_env - execute env.
 * @env: array of strings.
 */
void execute_builtin_env(char *env[])
{
	char **env_ptr;

	for (env_ptr = env; *env_ptr != NULL; env_ptr++)
	{
		display(*env_ptr);
		display("\n");
	}
}

/**
 * find_executable - search for the executable.
 * @tokens: array of strings.
 * @env: array of strings.
 * Return: the executable.
 */
char *find_executable(char *tokens[], char **env)
{
	char *executable = NULL;
	char *path_env = getenv("PATH");
	char *path;
	char *token;
	char path_buffer[MAX_PATH];

	(void)env;
	if (_strchr(tokens[0], '/') != NULL)
	{
		if (access(tokens[0], X_OK) == 0)
		{
			executable = _strdup(tokens[0]);
		}
	}
	else
	{
		if (path_env != NULL)
		{
			path = _strdup(path_env);
			token =	strtok(path, ":");
			while (token != NULL)
			{
				_strcpy(path_buffer, token);
				_strcat(path_buffer, "/");
				_strcat(path_buffer, tokens[0]);
				if (access(path_buffer, X_OK) == 0)
				{
					executable = _strdup(path_buffer);
					break;
				}
				token = strtok(NULL, ":");
			}
			free(path);
		}
	}
	return (executable);
}

/**
 * execute_command - command execution.
 * @tokens: array of strings.
 * @env: array of strings.
 * @token_count: nu,ber of tokens.
 */
void execute_command(char *tokens[], char **env, int token_count)
{
	char *executable;
	char *exec_args[MAX_TOKENS];
	char *err = malloc(100);
	int i;
	pid_t pid;

	executable = find_executable(tokens, env);
	if (executable == NULL)
	{
		_strcpy(err, "./hsh: ");
		_strcat(err, "1: ");
		_strcat(err, tokens[0]);
		_strcat(err, ": not found\n");
		write(STDERR_FILENO, err, _strlen(err));
		free(err);
		exit(127);
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			for (i = 0; tokens[i] != NULL; i++)
				exec_args[i] = tokens[i];
			exec_args[token_count] = NULL;
			execve(executable, exec_args, env);
			perror(executable);
			free(executable);
			exit(EXIT_FAILURE);
		}
		else if (pid < 0)
			perror("Fork failed");
		else
		{
			waitpid(pid, NULL, 0);
		/*	free(executable);*/
		}
		free(err);
		free(executable);
	}
}

/**
 * main - entry point.
 * @argc: argument count.
 * @argv: argument vector.
 * @env: array of stings.
 * Return: (0) on success.
 */
int main(int argc, char *argv[], char **env)
{
	char *line = NULL;
	size_t len = 0;
	int token_count;
	ssize_t read;
	char *tokens[MAX_TOKENS];

	(void)argc;
	(void)argv;
	signal(SIGINT, sigint_handler);

	while (1)
	{
		display_prompt();
		read = read_input(&line, &len);
		if (read == -1)
			break;
		if (line[_strlen(line) - 1] == '\n')
			line[_strlen(line) - 1] = '\0';
		token_count = tokenize_input(line, tokens, " ");
		if (token_count == 0)
			continue;
		else if (_strsub(line, "exit") == true)
			execute_builtin_exit(line);
		else if (_strcmp(tokens[0], "cd") == 0)
			execute_builtin_cd(tokens);
		else if (_strcmp(tokens[0], "env") == 0)
			execute_builtin_env(env);
		else
			execute_command(tokens, env, token_count);
	}
	free(line);
	return (0);
}
