#include "Unity/unity.h"
#include "executor_internals.h"
#include "minishell.h"
#include "parser_internals.h"
#include "structs.h"
#include "unit_tests_utils.h"

void test_function_process_exit_status(void) {
	t_command *cmd;
	int size = 3;
	int test_list[3] = {1, 2, 127};
	int status;

	int index = -1;
	while (++index < size) {
		status = test_list[index];
		cmd = init_command();
		cmd->pid = fork();
		if (cmd->pid < 0)
			TEST_IGNORE_MESSAGE(UT_ERR_FORK);
		if (cmd->pid == 0) {
			free(cmd);
			exit(status);
		} else {
			waitpid(cmd->pid, &cmd->status, 0);
			TEST_ASSERT_NOT_EQUAL(status, cmd->status);
			process_exit_status(cmd);
			TEST_ASSERT_EQUAL(status, cmd->status);
			free(cmd);
		}
		wait(NULL);
	}
	status = 0;
	cmd = init_command();
	cmd->pid = fork();
	if (cmd->pid < 0)
		TEST_IGNORE_MESSAGE(UT_ERR_FORK);
	if (cmd->pid == 0) {
		free(cmd);
		exit(status);
	} else {
		waitpid(cmd->pid, &cmd->status, 0);
		TEST_ASSERT_EQUAL(status, cmd->status);
		process_exit_status(cmd);
		TEST_ASSERT_EQUAL(status, cmd->status);
		free(cmd);
	}
}

int file_subshell_test() {
	UNITY_BEGIN();
	RUN_TEST(test_function_process_exit_status);
	return UNITY_END();
}