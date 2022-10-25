#include "Unity/unity.h"
#include "executor_internals.h"
#include "minishell.h"
#include "parser_internals.h"
#include "structs.h"
#include "unit_tests_utils.h"

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

int file_subshell_test() {
	UNITY_BEGIN();
	RUN_TEST(test_function_process_exit_status);
	RUN_TEST(test_function_exit_process);
	return UNITY_END();
}