#include <stdio.h>

int main(int argc, char *argv[], char**envp)
{
	(void)argc;
	(void)argv;
	while (*envp != NULL)
	{
		printf("%s\n", *envp);
		++envp;
	}
}
