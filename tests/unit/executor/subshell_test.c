#include "Unity/unity.h"
#include "executor.h"
#include "minishell.h"
#include "parser.h"
#include "structs.h"
#include "unit_tests_utils.h"
#include <string.h>
#include <unistd.h>

void test_function_subshell_redirect(void) {
	t_minishell minishell;
	t_cmd *command;
	int pipefd_in[2];
	int pipefd_out[2];
	pid_t pid;

	init_minishell(&minishell, NULL);
	if (pipe(pipefd_in) == -1)
		TEST_FAIL();
	if (pipe(pipefd_out) == -1)
		TEST_FAIL();
	command = new_command(0);
	pid = fork();
	if (pid < 0)
		TEST_FAIL();
	else if (pid == 0) {
		command->input = dup(pipefd_in[0]);
		command->output = dup(pipefd_out[1]);
		ut_close_pipefd(pipefd_in);
		ut_close_pipefd(pipefd_out);
		subshell_redirect(command);
		char *content = ut_get_content_fd(STDIN);
		printf("%s", content);
		free(content);
		destroy_command(command);
		destroy_minishell(&minishell);
		exit(0);
	} else {
		char *expected = "hello";
		write(pipefd_in[1], expected, strlen(expected));
		ut_close_pipefd(pipefd_in);
		close(pipefd_out[1]);
		int status;
		wait(&status);
		ut_exit_status(&status);
		if (status != 0)
			TEST_IGNORE_MESSAGE(UT_ERR_PROC);
		char *content = ut_get_content_fd(pipefd_out[0]);
		TEST_ASSERT_EQUAL_STRING(expected, content);
		free(content);
		destroy_command(command);
		destroy_minishell(&minishell);
		close(pipefd_out[0]);
	}
}

void test_function_execute_program(void) {
	char *expected = "oi";
	t_cmd *cmd = new_command(0);
	t_minishell minishell;
	int pipefd[2];

	cmd->pathname = strdup("/usr/bin/echo");
	cmd->argc = 3;
	cmd->argv = malloc(sizeof(char *) * (cmd->argc + 1));
	cmd->argv[0] = strdup("echo");
	cmd->argv[1] = strdup("-n");
	cmd->argv[2] = strdup(expected);
	cmd->argv[3] = NULL;
	if (pipe(pipefd) == -1)
		TEST_FAIL();
	pid_t pid = fork();
	if (pid < 0)
		TEST_FAIL();
	else if (pid == 0) {
		dup2(pipefd[1], STDOUT);
		ut_close_pipefd(pipefd);
		init_minishell(&minishell, NULL);
		execute_program(&minishell, cmd);
		exit(1);
	} else {
		close(pipefd[1]);
		int status = ut_wait();
		if (status != 0)
			TEST_IGNORE_MESSAGE(UT_ERR_PROC);
		char *content = ut_get_content_fd(pipefd[0]);
		TEST_ASSERT_EQUAL_STRING(expected, content);
		free(content);
		destroy_command(cmd);
		close(pipefd[0]);
	}
}

void test_function_exit_subshell(void) {
	t_minishell minishell;
	pid_t pid;
	int expected;

	expected = 3;
	init_minishell(&minishell, NULL);
	pid = fork();
	if (pid < 0)
		TEST_FAIL();
	if (pid == 0) {
		exit_subshell(&minishell, expected);
	} else {
		int status;
		waitpid(pid, &status, 0);
		ut_exit_status(&status);
		TEST_ASSERT_EQUAL(expected, status);
		destroy_minishell(&minishell);
	}
}

int file_subshell_test() {
	UNITY_BEGIN();
	RUN_TEST(test_function_subshell_redirect);
	RUN_TEST(test_function_execute_program);
	RUN_TEST(test_function_exit_subshell);
	return UNITY_END();
}