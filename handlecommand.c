#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

/**
 * executeCommand - Execute a command in a child process with arguments
 * @command: The command to be executed (with arguments)
 */
void executeCommand(const char *command)
{
pid_t pid;

char *args[64];
char *token;
int i = 0;

token = strtok((char *)command, " ");
while (token != NULL)
{
args[i] = token;
token = strtok(NULL, " ");
i++;
}
args[i] = NULL;

pid = fork();
if (pid == -1)
{
perror("fork");
exit(EXIT_FAILURE);
}
else if (pid == 0)
{
execvp(args[0], args);
perror("execvp");
_exit(EXIT_FAILURE);
}
else
{
wait(NULL);
}
}

/**
 * readCommand - Read a command from the user and return it as a string
 * Return: A pointer to the string containing the user's command
 */
char *readCommand()
{
char *buffer = NULL;
size_t bufsize = 0;
ssize_t characters;

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

