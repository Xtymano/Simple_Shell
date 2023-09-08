#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 100

void read_line(char *buffer) {
    printf("CustomShell> ");
    fgets(buffer, MAX_INPUT_SIZE, stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character
}

int parse_line(char *line, char *args[]) {
    int i = 0;
    char *token = strtok(line, " ");
    
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    
    args[i] = NULL; // Null-terminate the argument list
    return i; // Return the number of arguments
}

void execute_command(char *args[]) {
    pid_t pid, wait_pid;
    int status;

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    } else {
        // Parent process
        do {
            wait_pid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

int main() {
    char input[MAX_INPUT_SIZE];
    char *args[MAX_ARGS];

    while (1) {
        read_line(input);

        if (strcmp(input, "exit") == 0) {
            printf("Exiting custom shell...\n");
            break;
        }

        int num_args = parse_line(input, args);

        if (num_args > 0) {
            execute_command(args);
        }
    }

    return 0;
}

