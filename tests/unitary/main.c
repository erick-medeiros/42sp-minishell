#include "Unity/unity.h"
#include "minishell.h"

void setUp(void) {}

void tearDown(void) {}

void test_function_command_is_equal(void) {
	TEST_ASSERT_TRUE(command_is_equal("exit", "exit"));
	TEST_ASSERT_FALSE(command_is_equal("exita", "exit"));
	TEST_ASSERT_FALSE(command_is_equal("exi", "exit"));
}

int main() {
	UNITY_BEGIN();
	RUN_TEST(test_function_command_is_equal);
	return UNITY_END();
}
