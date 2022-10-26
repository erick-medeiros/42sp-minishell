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
	int status;

	expected = "echo\necho";
	ut_pipe(pipefd);
	pid = ut_fork();
	if (pid == 0) {
		ut_stds_devnull();
		dup2(pipefd[1], STDOUT);
		ut_close_pipefd(pipefd);
		builtin_echo("", "echo");
		builtin_echo("-n", "echo");
		exit(0);
	} else {
		close(pipefd[1]);
		status = ut_wait();
		if (status != 0)
			TEST_IGNORE_MESSAGE(UT_ERR_PROC);
		content = get_content_fd(pipefd[0]);
		TEST_ASSERT_EQUAL_STRING(expected, content);
		free(content);
		close(pipefd[0]);
	}
}

void test_builtin_cd(void) {
	pid_t pid;
	char *expected;
	char *content;
	int status;
	int len;

	expected = "/tmp";
	len = strlen(expected) + 1;
	content = ut_mmap(len);
	pid = ut_fork();
	if (pid == 0) {
		ut_stds_devnull();
		builtin_cd(expected, NULL);
		char *new_dir = ut_getcwd();
		strncpy(content, new_dir, len);
		free(new_dir);
		exit(0);
	} else {
		wait(&status);
		if (status != 0)
			TEST_IGNORE_MESSAGE(UT_ERR_PROC);
		TEST_ASSERT_EQUAL_STRING(expected, content);
	}
}

void test_builtin_pwd(void) {
	char *current_dir;
	char *expected;
	char *content;
	pid_t pid;
	int pipefd[2];
	int status;

	ut_pipe(pipefd);
	pid = ut_fork();
	if (pid == 0) {
		ut_stds_devnull();
		dup2(pipefd[1], STDOUT);
		ut_close_pipefd(pipefd);
		builtin_pwd();
		exit(0);
	} else {
		close(pipefd[1]);
		wait(&status);
		if (status != 0)
			TEST_IGNORE_MESSAGE(UT_ERR_PROC);
		current_dir = ut_getcwd();
		content = get_content_fd(pipefd[0]);
		expected = ft_strjoin(current_dir, "\n");
		TEST_ASSERT_EQUAL_STRING(expected, content);
		free(content);
		free(expected);
		free(current_dir);
		close(pipefd[0]);
	}
}

void test_builtin_exit(void) {
	pid_t pid;
	int status;
	int expected;

	pid = ut_fork();
	if (pid == 0) {
		ut_stds_devnull();
		builtin_exit();
		exit(1);
	}
	expected = 0;
	status = ut_wait();
	TEST_ASSERT_EQUAL_INT(expected, status);
}

int file_builtins_test(void) {
	UNITY_BEGIN();
	RUN_TEST(test_builtin_echo);
	RUN_TEST(test_builtin_cd);
	RUN_TEST(test_builtin_pwd);
	RUN_TEST(test_builtin_exit);
	return UNITY_END();
}
