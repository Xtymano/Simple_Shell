#include "main.h"

void display(const char *str)
{
	write(STDOUT_FILENO, str, strlen(str));
}

void sigint_handler(int signo)
{
	(void)signo;

	display("\n");
}

void display_prompt()
{
	display("($) ");
}

ssize_t read_input(char **line, size_t *len)
{
	return (getline(line, len, stdin));
}

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

void execute_builtin_exit()
{
	exit(0);
}

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

void execute_builtin_env(char *env[])
{
	char **env_ptr;

	for (env_ptr = env; *env_ptr != NULL; env_ptr++)
	{
		display(*env_ptr);
		display("\n");
	}
}

char *find_executable(char *tokens[], char **env)
{
	char *executable = NULL;
	char *path_env = getenv("PATH");
	char *path;
	char *token;
	char path_buffer[MAX_PATH];

	if (path_env != NULL)
	{
		path = _strdup(path_env);
		token = strtok(path, ":");
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
	return (executable);
}

void execute_command(char *tokens[], char **env, int token_count)
{
	char *executable;
	char *exec_args[MAX_TOKENS];
	int i;
	char *str;

	executable = find_executable(tokens, env);
	if (executable == NULL)
	{
		display("Command not found: ");
		display(tokens[0]);
		display("\n");
	}
	else
	{
		pid_t pid = fork();
		if (pid == 0)
		{
			for (i = 0; tokens[i] != NULL; i++)
			{
				exec_args[i] = tokens[i];
			}
			exec_args[token_count] = NULL;
			execve(executable, exec_args, env);
			perror(executable);
			exit(EXIT_FAILURE);
		}
		else if (pid < 0)
		{
			perror("Fork failed");
		}
		else
		{
			waitpid(pid, NULL, 0);
		}
		free(executable);
	}
}

int main(int argc, char *argv[], char **env)
{
	char *line = NULL;
	size_t len = 0;
	int token_count;
	ssize_t read;
	char *tokens[MAX_TOKENS];

	signal(SIGINT, sigint_handler);

	while (1)
	{
		display_prompt();
		read = read_input(&line, &len);
		if (read == -1)
		{
			break;
		}
		if (line[_strlen(line) - 1] == '\n')
		{
			line[_strlen(line) - 1] = '\0';
		}
		token_count = tokenize_input(line, tokens, " ");
		if (token_count == 0)
		{
			continue;
		}
		if (_strcmp(tokens[0], "exit") == 0)
		{
			execute_builtin_exit();
		}
		else if (_strcmp(tokens[0], "cd") == 0)
		{
			execute_builtin_cd(tokens);
		}
		else if (_strcmp(tokens[0], "env") == 0)
		{
			execute_builtin_env(env);
		}
		else
		{
			execute_command(tokens, env, token_count);
		}
	}
	free(line);
	return (0);
}
