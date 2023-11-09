#include "shell.h"

/**
 * exit_builtin - exit built-in handles
 * @cmd: the command entered
 * @status: pass status with exit
 */

void exit_builtin(char *cmd, char *status)
{
	int a = 0, exit_status;


	if (status == NULL)
	{
		exit(0);
	}
	while (status[a] != '\0')
	{
		if (!(status[a] >= '0' && status[a] <= '9'))
		{
			print_error(_getenv("_"));
			print_error(": 1: exit: Illegal number: ");
			write(2, status, strlen(status));
			write(2, "\n", 1);
			return;
		}
		a++;
	}
	exit_status = _atoi(status);
	free(cmd);
	cmd = NULL;
	exit(exit_status);
}

/**
 * _atoi - string converted to integer
 * @str: converted string
 * Return: 0
 */

int _atoi(char *str)
{
	int result = 0, sign = 1, a = 0;

	if (str[0] == '-')
	{
		sign = -1;
		a++;
	}
	while (str[a] >= '0' && str[a] <= '9')
	{
		result = result * 10 + (str[a] - '0');
		++a;
	}

	return (sign * result);
}
