#include "main.h"

/**
 * execute_builtin_cd - execute cd.
 * @tokens: array of strings.
 */
int execute_builtin_cd(char *tokens[])
{
	char *new_dir;
	char *oldpwd;

	if (tokens[1] == NULL)
	{
		new_dir = getenv("HOME");
	}
	else if (strcmp(tokens[1], "-") == 0)
	{
		oldpwd = getenv("OLDPWD");
		if (oldpwd != NULL)
		{
			new_dir = oldpwd;
		}
		else
		{
			perror("getenv");
			return (1);
		}
	}
	else
	{
		new_dir = tokens[1];
	}
	if (chdir(new_dir) != 0)
	{
		perror("cd");
		return (1);
	}
	if (setenv("PWD", new_dir, 1) != 0)
	{
		perror("setenv");
		return (1);
	}

	return (0);
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
	char *executable = NULL, *exec_args[MAX_TOKENS], *err = malloc(100);
	pid_t pid;
	int i = 0;

	executable = find_executable(tokens, env);
	if (executable == NULL)
	{
		_strcpy(err, "./hsh: ");
		_strcat(err, tokens[0]);
		_strcat(err, ": not found\n");
		write(2, err, _strlen(err));
		free(executable);
		free(err);
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			for (i = 0; tokens[i] != NULL; i++)
				exec_args[i] = tokens[i];
			exec_args[token_count] = NULL;
			if (execve(executable, exec_args, env) == -1)
			{
				perror(executable);
				errno = 127;
				free(executable);
				free(err);
				exit(127);
			}
			free(executable);
		}
		else
		{
			waitpid(pid, NULL, 0);
			free(executable);
		}
		free(err);
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
	int token_count = 0;
	ssize_t read;
	char *tokens[MAX_TOKENS] = {NULL, NULL};
	int exitFlag = 0;

	(void)argc;
	(void)argv;
	signal(SIGINT, sigint_handler);

	while (!exitFlag)
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
		else if (_strcmp(tokens[0], "exit") == 0)
			execute_builtin_exit(tokens);
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
