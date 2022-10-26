#include "Unity/unity.h"
#include "executor_internals.h"
#include "minishell.h"
#include "parser_internals.h"
#include "structs.h"
#include "unit_tests_utils.h"
#include <string.h>
#include <unistd.h>

void test_function_process_exit_status(void) {
	t_cmd *cmd;
	int size = 3;
	int test_list[3] = {1, 2, 127};
	int status;

	int index = -1;
	while (++index < size) {
		status = test_list[index];
		cmd = new_command();
		cmd->pid = fork();
		if (cmd->pid < 0)
			TEST_IGNORE_MESSAGE(UT_ERR_FORK);
		if (cmd->pid == 0) {
			destroy_command(cmd);
			exit(status);
		} else {
			waitpid(cmd->pid, &cmd->status, 0);
			TEST_ASSERT_NOT_EQUAL(status, cmd->status);
			process_exit_status(cmd);
			TEST_ASSERT_EQUAL(status, cmd->status);
			destroy_command(cmd);
		}
		wait(NULL);
	}
	status = 0;
	cmd = new_command();
	cmd->pid = fork();
	if (cmd->pid < 0)
		TEST_IGNORE_MESSAGE(UT_ERR_FORK);
	if (cmd->pid == 0) {
		destroy_command(cmd);
		exit(status);
	} else {
		waitpid(cmd->pid, &cmd->status, 0);
		TEST_ASSERT_EQUAL(status, cmd->status);
		process_exit_status(cmd);
		TEST_ASSERT_EQUAL(status, cmd->status);
		destroy_command(cmd);
	}
}

void test_function_exit_process(void) {
	t_minishell minishell;
	pid_t pid;
	int expected;

	expected = 3;
	init_minishell(&minishell, NULL);
	pid = fork();
	if (pid < 0)
		TEST_IGNORE_MESSAGE(UT_ERR_FORK);
	if (pid == 0) {
		exit_process(&minishell, expected);
	} else {
		int status;
		waitpid(pid, &status, 0);
		ut_exit_status(&status);
		TEST_ASSERT_EQUAL(expected, status);
		destroy_minishell(&minishell);
	}
}

void test_function_update_io(void) {
	t_minishell minishell;
	t_cmd *command;
	int pipefd_in[2];
	int pipefd_out[2];
	pid_t pid;

	init_minishell(&minishell, NULL);
	ut_pipe(pipefd_in);
	ut_pipe(pipefd_out);
	command = new_command();
	pid = fork();
	if (pid < 0)
		TEST_IGNORE_MESSAGE(UT_ERR_FORK);
	else if (pid == 0) {
		command->input = dup(pipefd_in[0]);
		command->output = dup(pipefd_out[1]);
		ut_close_pipefd(pipefd_in);
		ut_close_pipefd(pipefd_out);
		update_io(&minishell, command);
		char *content = get_content_fd(STDIN);
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
		char *content = get_content_fd(pipefd_out[0]);
		TEST_ASSERT_EQUAL_STRING(expected, content);
		destroy_command(command);
		destroy_minishell(&minishell);
		close(pipefd_out[0]);
	}
}

void test_function_child_process(void) {
	char *expected = "oi";
	t_cmd *cmd = new_command();
	t_minishell minishell;
	int pipefd[2];

	cmd->pathname = strdup("/usr/bin/echo");
	cmd->argc = 3;
	cmd->argv = malloc(sizeof(char *) * cmd->argc + 1);
	cmd->argv[0] = strdup("echo");
	cmd->argv[1] = strdup("-n");
	cmd->argv[2] = strdup(expected);
	cmd->argv[3] = NULL;
	ut_pipe(pipefd);
	pid_t pid = ut_fork();
	if (pid == 0) {
		dup2(pipefd[1], STDOUT);
		ut_close_pipefd(pipefd);
		init_minishell(&minishell, NULL);
		child_process(&minishell, cmd);
		destroy_command(cmd);
		destroy_minishell(&minishell);
	} else {
		close(pipefd[1]);
		int status = ut_wait();
		if (status != 0)
			TEST_IGNORE_MESSAGE(UT_ERR_PROC);
		char *content = get_content_fd(pipefd[0]);
		TEST_ASSERT_EQUAL_STRING(expected, content);
		free(content);
		destroy_command(cmd);
		close(pipefd[0]);
	}
}

int file_subshell_test() {
	UNITY_BEGIN();
	RUN_TEST(test_function_process_exit_status);
	RUN_TEST(test_function_exit_process);
	RUN_TEST(test_function_update_io);
	RUN_TEST(test_function_child_process);
	return UNITY_END();
}