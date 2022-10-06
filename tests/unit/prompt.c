#include "unit_tests.h"
#include <unistd.h>

TEST_GROUP(test_prompt);

TEST_SETUP(test_prompt) {}

TEST_TEAR_DOWN(test_prompt) {}

TEST(test_prompt, command_is_equal) {
	TEST_ASSERT_TRUE(command_is_equal("exit", "exit"));
	TEST_ASSERT_FALSE(command_is_equal("exita", "exit"));
	TEST_ASSERT_FALSE(command_is_equal("exi", "exit"));
}

TEST(test_prompt, command_ends_with) {
	TEST_ASSERT_TRUE(command_ends_with("cmd |", '|'));
	TEST_ASSERT_TRUE(command_ends_with("|", '|'));
	TEST_ASSERT_FALSE(command_ends_with("cmd", '|'));
	TEST_ASSERT_FALSE(command_ends_with("", '|'));
	TEST_ASSERT_FALSE(command_ends_with(NULL, '|'));
}

TEST(test_prompt, get_content_fd) {
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

TEST_GROUP_RUNNER(test_prompt)
{
    RUN_TEST_CASE(test_prompt, command_is_equal);
    RUN_TEST_CASE(test_prompt, command_ends_with);
    RUN_TEST_CASE(test_prompt, get_content_fd);
}