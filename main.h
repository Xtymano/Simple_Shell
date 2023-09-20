#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdbool.h>

#define MAX_INPUT_SIZE 1024
#define MAX_TOKENS 64
#define MAX_PATH 100

size_t _strlen(const char *str);
int _strcmp(const char *str1, const char *str2);
char *_strdup(const char *src);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
void execute_builtin_exit(void);
int tokenize_input(char *line, char *tokens[], char *delimiters);
ssize_t read_input(char **line, size_t *len);
void display_prompt(void);
void sigint_handler(int signo);
void display(const char *str);
char *_strchr(const char *str, int character);
void execute_command(char *tokens[], char **env, int token_count);

#endif /*MAIN_H*/
