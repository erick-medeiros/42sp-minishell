#include "Unity/unity.h"
#include "executor.h"
#include "minishell.h"
#include "parser.h"
#include "structs.h"
#include "unit_tests_utils.h"
#include <string.h>
#include <unistd.h>

void test_function_command_exit_status(void) {
	t_cmd *cmd;
	int size = 3;
	int test_list[3] = {1, 2, 127};
	int status;

	int index = -1;
	while (++index < size) {
		status = test_list[index];
		cmd = new_command(index);
		cmd->pid = fork();
		if (cmd->pid < 0)
			TEST_FAIL();
		if (cmd->pid == 0) {
			destroy_command(cmd);
			exit(status);
		} else {
			waitpid(cmd->pid, &cmd->status, 0);
			TEST_ASSERT_NOT_EQUAL(status, cmd->status);
			command_exit_status(cmd);
			TEST_ASSERT_EQUAL(status, cmd->status);
			destroy_command(cmd);
		}
		wait(NULL);
	}
	status = 0;
	cmd = new_command(0);
	cmd->pid = fork();
	if (cmd->pid < 0)
		TEST_FAIL();
	if (cmd->pid == 0) {
		destroy_command(cmd);
		exit(status);
	} else {
		waitpid(cmd->pid, &cmd->status, 0);
		TEST_ASSERT_EQUAL(status, cmd->status);
		command_exit_status(cmd);
		TEST_ASSERT_EQUAL(status, cmd->status);
		destroy_command(cmd);
	}
}

int file_executor_test(void) {
	UNITY_BEGIN();
	RUN_TEST(test_function_command_exit_status);
	return UNITY_END();
}
