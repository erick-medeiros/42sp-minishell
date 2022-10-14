#include "unit_tests.h"

void file_list_test(void);
void file_prompt_test(void);
void file_builtins_test(void);
void file_environment_test(void);

void setUp(void) {}

void tearDown(void) {}

int main() {
	UNITY_BEGIN();
	file_prompt_test();
	file_list_test();
	file_builtins_test();
	file_environment_test();
	return UNITY_END();
}
