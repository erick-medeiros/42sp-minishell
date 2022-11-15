#include <stdio.h>

int main(int argc, char *argv[], char**envp)
// REMOVE THIS FILE
{
	int	idx;

	idx = 0;
	printf("Arguments:\n");
	while (idx < argc)
		printf("%s\n", argv[idx++]);
	while (*envp != NULL)
	{
		printf("%s\n", *envp);
		++envp;
	}
}
