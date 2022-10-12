#include "Unity/unity.h"
#include "minishell.h"
#include "unit_tests_utils.h"
#include <string.h>
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

void test_here_doc(void) {
	int pipefd[2];
	char *expected;
	char *write_line1;
	char *write_line2;
	char *string;
	int len;
	pid_t pid;

	write_line1 = "42\n";
	write_line2 = "sp\n";
	expected = "42\nsp\n";
	len = strlen(write_line1) + strlen(write_line2) + 1;
	string = ut_mmap(sizeof(char) * len);
	if (pipe(pipefd) == -1)
		TEST_IGNORE_MESSAGE("Error pipe");
	pid = fork();
	if (pid < 0)
		TEST_IGNORE_MESSAGE("Error fork");
	else if (pid == 0) {
		ut_stds_devnull();
		dup2(pipefd[0], STDIN);
		ut_close_pipefd(pipefd);
		int fd = here_doc("EOF");
		char *content = get_content_fd(fd);
		strncpy(string, content, len);
		free(content);
		close(fd);
		exit(0);
	} else {
		write(pipefd[1], write_line1, strlen(write_line1));
		write(pipefd[1], write_line2, strlen(write_line2));
		write(pipefd[1], "EOF", 3);
		ut_close_pipefd(pipefd);
		wait(NULL);
		TEST_ASSERT_EQUAL_STRING(expected, string);
	}
}

void test_ends_in_pipe(void) {
	int pipefd[2];
	char *string;
	char *expected;
	char *write_line1;
	char *write_line2;
	pid_t pid;
	int len;

	write_line1 = "cat |";
	write_line2 = "cat";
	expected = "cat | cat";
	len = strlen(write_line1) + strlen(write_line2) + 1;
	string = ut_mmap(sizeof(char) * len);
	if (pipe(pipefd) == -1)
		TEST_IGNORE_MESSAGE("Error pipe");
	pid = fork();
	if (pid < 0)
		TEST_IGNORE_MESSAGE("Error fork");
	else if (pid == 0) {
		ut_stds_devnull();
		dup2(pipefd[0], STDIN);
		ut_close_pipefd(pipefd);
		int fd = ends_in_pipe();
		char *content = get_content_fd(fd);
		strncpy(string, content, len);
		free(content);
		close(fd);
		exit(0);
	} else {
		write(pipefd[1], write_line1, strlen(write_line1));
		write(pipefd[1], "\n", 1);
		write(pipefd[1], write_line2, strlen(write_line2));
		write(pipefd[1], "\n", 1);
		ut_close_pipefd(pipefd);
		wait(NULL);
		TEST_ASSERT_EQUAL_STRING(expected, string);
	}
}

void file_prompt_test(void) {
	RUN_TEST(test_function_command_is_equal);
	RUN_TEST(test_function_command_ends_with);
	RUN_TEST(test_function_get_content_fd);
	RUN_TEST(test_here_doc);
	RUN_TEST(test_ends_in_pipe);
}
