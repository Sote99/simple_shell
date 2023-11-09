#include "shell.h"

/**
 * prompt - display prompt for shell
 */

void prompt(void)
{
	int prmpt;

	prmpt = write(STDOUT_FILENO, "$ ", 2);  /* Display prompt */
	if (prmpt == -1)
	{
		perror("Error: ");
		exit(EXIT_FAILURE);
	}
}

/**
 * main - Entry point
 * @ac: Arg count
 * @av: Arg vector
 * Return: 0.
 */

int main(int ac __attribute__((unused)), char **av __attribute__((unused)))
{
	size_t bufsize = 0;
	ssize_t characters;
	char *status = NULL, *exit_str = "exit ", *status_copy, *dup;

	char *cmd = NULL;
	int updated = 0;

	signal(SIGINT, handle_signal);

	while (1)

	{
		if (isatty(STDIN_FILENO))
			prompt();  /* Display the shell prompt if running */
		characters = getline(&cmd, &bufsize, stdin);
		if (characters == -1)
		{
			break; /* Exit the loop if getline encounters an error or EOF */
		}
		cmd[characters - 1] = '\0'; /* Remove the newline character at */
		if (_strlen(cmd) == 0 || _strspn(cmd, " \t\r\n") ==
			(size_t)_strlen(cmd))
			continue; /* Skip empty or whitespace-only lines */

		/* check for comments, handle_comment modifies cmd */
		if (handle_comment(cmd) == NULL)
{
			free(cmd);
			cmd = NULL;
			continue;
		}
		if (_strcmp(cmd, "env") == 0)
		{
			handle_env(); /* Handle the "env" command */
			free(cmd);
			cmd = NULL;
			continue;
		}
		if (_strcmp(cmd, "exit") == 0)
		{
			free(cmd);
			cmd = NULL;
			exit_builtin(cmd, NULL); /* Handle the "exit" command */
			continue;
		}
		/* Handle cd command */
		dup = _strdup(cmd);
		if (_strcmp(strtok(dup, " \t\r\n"), "cd") == 0)
		{
			change_dir(cmd);
			free(cmd);
			free(dup);
			dup = cmd = NULL;
			continue;
		}
		free(dup);
		if (_strncmp(cmd, exit_str, _strlen(exit_str)) == 0)
		{
			status = cmd + _strlen(exit_str);
			if (status[0] == '\0')
				status = NULL;
			status_copy = (status != NULL) ? _strdup(status) : NULL;
			free(cmd);
			cmd = NULL;
			exit_builtin(status_copy, status_copy); /* Handle "exit <status>" */
			free(status_copy);
			status_copy = NULL;
			continue;
		}
		execute_cmd(cmd, NULL); /* Execute other commands */
		free(cmd);
		cmd = NULL;
	}
	free(cmd);
	cmd = NULL;
	return (0);
}

/**
 * handle_signal - signal handler
 * @sig: holds SIGINT
 * Return: 0
 */
void handle_signal(int sig)
{
	write(1, "\n", 1); /* Print a newline character */
	if (sig == SIGINT)
	{
		if (cmd != NULL)
		{
			free(cmd); /* Free the command buffer if it exists */
			cmd = NULL;
		}
		if (updated == 1)
		{
			free_environ(environ); /* Free environment variables if updated */
		}
		exit(0);
	}
}
