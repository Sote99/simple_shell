#include <unistd.h>

/**
 * main - Entry point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
char *str = "Hello, Betty!\n";
int len = 13;

write(1, str, len);

return (0);
}

