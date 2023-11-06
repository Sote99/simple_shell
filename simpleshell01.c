#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
/**
 * executeCommand - Execute a command in a child process
 * @command: The command to be executed
 */
void executeCommand(const char *command)

#define BUFFER_SIZE 1024
{
char *args[] = {NULL, NULL};
pid_t pid;

args[0] = strdup(command);

pid = fork();
if (pid == -1)
{
perror("fork");
exit(EXIT_FAILURE);
}
else if (pid == 0)
{
execve(args[0], args, NULL);
perror("execve");
_exit(EXIT_FAILURE);
}
else
{
wait(NULL);
}

free(args[0]);
}
/**
 * readCommand - Read a command from the user
 *
 * This function reads a command from the user and returns it as a string.
 *
 * return: A pointer to the string containing the user's command
 */

char *readCommand()
{
char *buffer = NULL;
size_t bufsize = 0;
ssize_t characters;
}

printf("$ ");
characters = getline(&buffer, &bufsize, stdin);

if (characters == -1)
{
if (feof(stdin))
{
printf("\n");
exit(EXIT_SUCCESS);
}
else
{
perror("getline");
exit(EXIT_FAILURE);
}
}

buffer[strcspn(buffer, "\n")] = 0;
return (buffer);
}
/**
 * main - Entry point
 * Return: 0
 */
int main(void)
{
while (1)
{
char *command = readCommand();
executeCommand(command);
free(command);
}

return (0);
}

