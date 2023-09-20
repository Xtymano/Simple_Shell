#include "main.h"

/**
 * display - prints output.
 * @str: string.
 */
void display(const char *str)
{
	write(STDOUT_FILENO, str, strlen(str));
}

/**
 * sigint_handler - handles signint.
 * @signo: signo.
 */
void sigint_handler(int signo)
{
	(void)signo;

	display("\n");
}

/**
 * display_prompt - displays $ sign.
 */
void display_prompt(void)
{
	display("");
}
