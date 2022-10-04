#include "Unity/unity.h"
#include "minishell.h"
#include <unistd.h>

void test_function_command_is_equal(void) {
	TEST_ASSERT_TRUE(command_is_equal("exit", "exit"));
	TEST_ASSERT_FALSE(command_is_equal("exita", "exit"));
	TEST_ASSERT_FALSE(command_is_equal("exi", "exit"));
}

void test_function_command_ends_with(void) {
	TEST_ASSERT_TRUE(command_ends_with("cmd |", '|'));
	TEST_ASSERT_TRUE(command_ends_with("|", '|'));
	TEST_ASSERT_FALSE(command_ends_with("cmd", '|'));
	TEST_ASSERT_FALSE(command_ends_with("", '|'));
	TEST_ASSERT_FALSE(command_ends_with(NULL, '|'));
}

void test_function_get_content_fd(void) {
	const char *expected = "test";
	char *content;
	int pipefd[2];

	if (pipe(pipefd) == -1)
		TEST_IGNORE_MESSAGE("Error pipe");
	write(pipefd[1], expected, strlen(expected));
	close(pipefd[1]);
	content = get_content_fd(pipefd[0]);
	close(pipefd[0]);
	TEST_ASSERT_EQUAL_STRING(expected, content);
	free(content);
}

void file_prompt(void) {
	RUN_TEST(test_function_command_is_equal);
	RUN_TEST(test_function_command_ends_with);
	RUN_TEST(test_function_get_content_fd);
}