#include "unit_tests.h"

void setUp(void) {}

void tearDown(void) {}

int main() {
	UNITY_BEGIN();
	RUN_TEST(test_function_command_is_equal);
	RUN_TEST(test_function_command_ends_with);
	RUN_TEST(test_function_get_content_fd);
	return UNITY_END();
}