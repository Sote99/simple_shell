#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
/**
 * main - Entry point
 * executeCommand - Functions to execute command
 * readCOmmand - Function to read command
 * Return: 0
 */
#define BUFFER_SIZE 102

void executeCommand(const char *command)
{
char *args[] = {NULL, NULL};
args[0] = strdup(command);

pid_t pid = fork();
if (pid == -1);
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
char *readCommand()
{
char *buffer = NULL;
size_t bufsize = 0;
ssize_t characters;

write("$ ");
characters = getline(&buffer, &bufsize, stdin);

if(characters == -1)
{
if (feof(stdin))
{
write("\n");
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

