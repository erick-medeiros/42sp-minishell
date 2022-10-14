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
		ut_stds_devnull();
		dup2(pipefd[1], STDOUT);
		ut_close_pipefd(pipefd);
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
	pid_t pid;
	char *expected;
	char *content;
	char *current_dir;
	int status;
	int len;
	t_vlst vars;

	vars.list = NULL;
	vars.len = 0;
	current_dir = ut_exec_pwd();
	len = strlen(current_dir) + strlen("./Unity\n") + 1;
	content = ut_mmap(len);
	pid = fork();
	if (pid < 0)
		TEST_IGNORE_MESSAGE("Error fork");
	else if (pid == 0) {
		ut_stds_devnull();
		builtin_cd("./Unity", &vars);
		char *new_dir = ut_exec_pwd();
		strncpy(content, new_dir, len);
		free(new_dir);
		free(current_dir);
		clear_list(vars.list, del_var_node);
		exit(0);
	} else {
		wait(&status);
		if (status != 0)
			TEST_IGNORE_MESSAGE("Error child process");
		current_dir[strlen(current_dir) - 1] = '\0';
		expected = ft_strjoin(current_dir, "/Unity\n");
		TEST_ASSERT_EQUAL_STRING(expected, content);
		free(current_dir);
		free(expected);
	}
}

void test_builtin_pwd(void) {
	char *current_dir;
	char *content;
	pid_t pid;
	int pipefd[2];
	int status;

	current_dir = ut_exec_pwd();
	if (pipe(pipefd) == -1)
		TEST_IGNORE_MESSAGE("Error pipe");
	pid = fork();
	if (pid < 0)
		TEST_IGNORE_MESSAGE("Error fork");
	else if (pid == 0) {
		ut_stds_devnull();
		dup2(pipefd[1], STDOUT);
		ut_close_pipefd(pipefd);
		builtin_pwd();
		free(current_dir);
		exit(0);
	} else {
		close(pipefd[1]);
		wait(&status);
		if (status != 0)
			TEST_IGNORE_MESSAGE("Error in child process");
		content = get_content_fd(pipefd[0]);
		TEST_ASSERT_EQUAL_STRING(current_dir, content);
		free(content);
		free(current_dir);
		close(pipefd[0]);
	}
}

void test_builtin_exit(void) {
	pid_t pid;
	int status;
	int expected;

	expected = 0;
	pid = fork();
	if (pid < 0)
		TEST_IGNORE_MESSAGE("Error fork");
	else if (pid == 0) {
		ut_stds_devnull();
		builtin_exit();
		exit(1);
	} else {
		waitpid(pid, &status, 0);
		if (WIFEXITED(status)) {
			status = WEXITSTATUS(status);
			TEST_ASSERT_EQUAL_INT(expected, status);
		} else
			TEST_IGNORE_MESSAGE("Error in child process");
	}
}

void file_builtins_test(void) {
	RUN_TEST(test_builtin_echo);
	RUN_TEST(test_builtin_cd);
	RUN_TEST(test_builtin_pwd);
	RUN_TEST(test_builtin_exit);
}
