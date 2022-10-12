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

void test_function_here_doc(void) {
	int pipefd_expected[2];
	int pipefd_std[2];
	char *content;
	char *expected;
	char *write_line1;
	char *write_line2;
	pid_t pid;
	int fd;

	write_line1 = "42";
	write_line2 = "sp";
	expected = "42\nsp\n";
	if (pipe(pipefd_std) == -1)
		TEST_IGNORE_MESSAGE("Error pipe");
	if (pipe(pipefd_expected) == -1)
		TEST_IGNORE_MESSAGE("Error pipe");
	pid = fork();
	if (pid < 0)
		TEST_IGNORE_MESSAGE("Error fork");
	if (pid == 0) {
		int fd_devnull = open("/dev/null", O_WRONLY);
		dup2(pipefd_std[0], STDIN);
		dup2(fd_devnull, STDOUT);
		dup2(fd_devnull, STDERR);
		close(fd_devnull);
		close(pipefd_std[0]);
		close(pipefd_std[1]);
		close(pipefd_expected[0]);
		fd = here_doc("EOF");
		content = get_content_fd(fd);
		write(pipefd_expected[1], content, strlen(content));
		close(pipefd_expected[1]);
		exit(0);
	} else {
		close(pipefd_std[0]);
		close(pipefd_expected[1]);
		write(pipefd_std[1], write_line1, strlen(write_line1));
		write(pipefd_std[1], "\n", 1);
		write(pipefd_std[1], write_line2, strlen(write_line2));
		write(pipefd_std[1], "\n", 1);
		write(pipefd_std[1], "EOF", 3);
		close(pipefd_std[1]);
		wait(NULL);
		content = get_content_fd(pipefd_expected[0]);
		TEST_ASSERT_EQUAL_STRING(expected, content);
		close(pipefd_expected[0]);
	}
}

void test_function_ends_in_pipe(void) {
	int pipefd_expected[2];
	int pipefd_std[2];
	char *content;
	char *expected;
	char *write_line1;
	char *write_line2;
	pid_t pid;
	int fd;

	write_line1 = "cat |";
	write_line2 = "cat";
	expected = "cat | cat";
	if (pipe(pipefd_std) == -1)
		TEST_IGNORE_MESSAGE("Error pipe");
	if (pipe(pipefd_expected) == -1)
		TEST_IGNORE_MESSAGE("Error pipe");
	pid = fork();
	if (pid < 0)
		TEST_IGNORE_MESSAGE("Error fork");
	if (pid == 0) {
		int fd_devnull = open("/dev/null", O_WRONLY);
		dup2(pipefd_std[0], STDIN);
		dup2(fd_devnull, STDOUT);
		dup2(fd_devnull, STDERR);
		close(fd_devnull);
		close(pipefd_std[0]);
		close(pipefd_std[1]);
		close(pipefd_expected[0]);
		fd = ends_in_pipe();
		content = get_content_fd(fd);
		write(pipefd_expected[1], content, strlen(content));
		close(pipefd_expected[1]);
		exit(0);
	} else {
		close(pipefd_std[0]);
		close(pipefd_expected[1]);
		write(pipefd_std[1], write_line1, strlen(write_line1));
		write(pipefd_std[1], "\n", 1);
		write(pipefd_std[1], write_line2, strlen(write_line2));
		write(pipefd_std[1], "\n", 1);
		close(pipefd_std[1]);
		wait(NULL);
		content = get_content_fd(pipefd_expected[0]);
		TEST_ASSERT_EQUAL_STRING(expected, content);
		close(pipefd_expected[0]);
	}
}

void file_prompt(void) {
	RUN_TEST(test_function_command_is_equal);
	RUN_TEST(test_function_command_ends_with);
	RUN_TEST(test_function_get_content_fd);
	RUN_TEST(test_function_here_doc);
	RUN_TEST(test_function_ends_in_pipe);
}
