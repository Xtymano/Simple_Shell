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

int _strcmp(char *x, char *y);
void display(char *x);
int _strlen(char *x);

#endif /*MAIN_H*/
