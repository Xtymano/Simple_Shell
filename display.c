#include "main.h"

void display(char *x)
{
	write(STDOUT_FILENO, x, _strlen(x));
}
