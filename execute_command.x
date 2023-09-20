#include "main.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_TOKENS 100

void execute_command(char *tokens[], char **env, int token_count)
{
    char *executable;
    char *exec_args[MAX_TOKENS];
    char *err = malloc(100); 
    int i;
    pid_t pid;
    int status;
    int pipe_stdout[2];
    int pipe_stderr[2];
    char stdout_buffer[1024];
    char stderr_buffer[1024];
    int stdout_len;
    int stderr_len;

    if (err == NULL)
    {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    executable = find_executable(tokens, env);
    if (executable == NULL)
    {
        strcpy(err, "./hsh: ");
        strcat(err, tokens[0]);
        strcat(err, ": not found");
        write(STDERR_FILENO, err, strlen(err)); 
        free(err);
    }
    else
    {
       

        if (pipe(pipe_stdout) == -1 || pipe(pipe_stderr) == -1)
        {
            perror("pipe failed");
            free(executable);
            free(err);
            exit(EXIT_FAILURE);
        }

        pid = fork();
        if (pid == 0)
        {
           
            close(pipe_stdout[0]);
            close(pipe_stderr[0]);

            dup2(pipe_stdout[1], STDOUT_FILENO);
            dup2(pipe_stderr[1], STDERR_FILENO);

            close(pipe_stdout[1]);
            close(pipe_stderr[1]);

            for (i = 0; tokens[i] != NULL; i++)
            {
                exec_args[i] = tokens[i];
            }
            exec_args[i] = NULL;
            execve(executable, exec_args, env);
            perror(executable);
            free(executable); 
            exit(EXIT_FAILURE);
        }
        else if (pid < 0)
        {
            perror("Fork failed");
        }
        else
        {
         
            close(pipe_stdout[1]);
            close(pipe_stderr[1]);

       
   

            stdout_len = read(pipe_stdout[0], stdout_buffer, sizeof(stdout_buffer));
            stderr_len = read(pipe_stderr[0], stderr_buffer, sizeof(stderr_buffer));

            
            close(pipe_stdout[0]);
            close(pipe_stderr[0]);

        
            waitpid(pid, &status, 0);
            free(executable); 
        }
        free(err);
    }
}

