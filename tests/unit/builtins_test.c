#include "Unity/unity.h"
#include "libft.h"
#include "minishell.h"
#include "unit_tests_utils.h"
#include <string.h>
#include <unistd.h>

void test_builtin_echo(void) {
	int pipefd[2];
	pid_t pid;
	char *expected;
	char *content;

	expected = "echo\necho";
	if (pipe(pipefd) == -1)
		TEST_IGNORE_MESSAGE("Error pipe");
	pid = fork();
	if (pid < 0)
		TEST_IGNORE_MESSAGE("Error fork");
	else if (pid == 0) {
		int fd_devnull = open("/dev/null", O_WRONLY);
		dup2(fd_devnull, STDIN);
		dup2(pipefd[1], STDOUT);
		dup2(fd_devnull, STDERR);
		close(fd_devnull);
		builtin_echo("", "echo");
		builtin_echo("-n", "echo");
		exit(0);
	} else {
		close(pipefd[1]);
		wait(NULL);
		content = get_content_fd(pipefd[0]);
		TEST_ASSERT_EQUAL_STRING(expected, content);
		free(content);
		close(pipefd[0]);
	}
}

void test_builtin_cd(void) {
	int pipefd[2];
	pid_t pid;
	char *expected;
	char *content;
	char *current_dir;
	int status;

	if (pipe(pipefd) == -1)
		TEST_IGNORE_MESSAGE("Error pipe");
	pid = fork();
	if (pid < 0)
		TEST_IGNORE_MESSAGE("Error fork");
	else if (pid == 0) {
		ut_stds_devnull();
		builtin_cd("./Unity");
		current_dir = ut_exec_pwd();
		write(pipefd[1], current_dir, strlen(current_dir));
		ut_close_pipefd(pipefd);
		free(current_dir);
		exit(0);
	} else {
		close(pipefd[1]);
		wait(&status);
		if (status != 0)
			TEST_IGNORE_MESSAGE("Error child process");
		current_dir = ut_exec_pwd();
		current_dir[strlen(current_dir) - 1] = '\0';
		expected = ft_strjoin(current_dir, "/Unity\n");
		content = get_content_fd(pipefd[0]);
		TEST_ASSERT_EQUAL_STRING(expected, content);
		free(content);
		free(current_dir);
		free(expected);
		close(pipefd[0]);
	}
}

void file_builtins_test(void) {
	RUN_TEST(test_builtin_echo);
	RUN_TEST(test_builtin_cd);
}
