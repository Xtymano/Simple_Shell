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

#endif /*MAIN_H*/
