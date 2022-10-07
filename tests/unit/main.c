#include "Unity/unity.h"
#include "minishell.h"

void file_list_test(void);
void file_prompt(void);
void file_builtins_test(void);

void setUp(void) {}

void tearDown(void) {}

int main() {
	UNITY_BEGIN();
	file_prompt();
	file_list_test();
	file_builtins_test();
	return UNITY_END();
}
