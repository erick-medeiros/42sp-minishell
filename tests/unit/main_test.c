#include "Unity/unity.h"
#include <string.h>

void file_list_test(void);
void file_prompt_test(void);
void file_builtins_test(void);
void file_environment_test(void);
void file_pathname_test(void);
void file_subshell_test(void);

void setUp(void) {}

void tearDown(void) {}

void run_all_test() {
	file_prompt_test();
	file_list_test();
	file_builtins_test();
	file_environment_test();
	file_pathname_test();
	file_subshell_test();
}

int main(int argc, char *argv[]) {
	UNITY_BEGIN();

	if (argc == 1)
		run_all_test();
	else {
		char *file = argv[1];
		if (strcmp("list", file) == 0)
			file_list_test();
		else if (strcmp("prompt", file) == 0)
			file_prompt_test();
		else if (strcmp("builtins", file) == 0)
			file_builtins_test();
		else if (strcmp("environment", file) == 0)
			file_environment_test();
		else if (strcmp("pathname", file) == 0)
			file_pathname_test();
		else if (strcmp("subshell", file) == 0)
			file_subshell_test();
	}

	return UNITY_END();
}
