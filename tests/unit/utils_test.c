#include "Unity/unity.h"
#include "minishell.h"
#include "parser_internals.h"
#include "structs.h"

void test_function_init_minishell(void) {
	t_minishell minishell;

	init_minishell(&minishell, NULL);
	TEST_ASSERT_EQUAL(NULL, minishell.path_list);
	TEST_ASSERT_EQUAL(NULL, minishell.token_list);
	TEST_ASSERT_EQUAL(NULL, minishell.envp);
	TEST_ASSERT_EQUAL(NULL, minishell.pipelines);
	TEST_ASSERT_EQUAL(NULL, minishell.env_list.list);
	TEST_ASSERT_EQUAL(0, minishell.env_list.len);
}

void test_function_new_command() {
	t_cmd *cmd;

	cmd = new_command();
	TEST_ASSERT_NOT_EQUAL(NULL, cmd);
	TEST_ASSERT_EQUAL(NULL, cmd->pathname);
	TEST_ASSERT_EQUAL(0, cmd->argc);
	TEST_ASSERT_EQUAL(NULL, cmd->argv);
	TEST_ASSERT_EQUAL(NULL, cmd->envp);
	TEST_ASSERT_EQUAL(STDIN, cmd->input);
	TEST_ASSERT_EQUAL(STDOUT, cmd->output);
	TEST_ASSERT_EQUAL(0, cmd->number);
	TEST_ASSERT_EQUAL(FALSE, cmd->isbuiltin);
	TEST_ASSERT_EQUAL(0, cmd->pid);
	TEST_ASSERT_EQUAL(0, cmd->status);
	TEST_ASSERT_EQUAL(TRUE, cmd->subshell);
	destroy_command(cmd);
}

void test_function_new_pipeline() {
	t_pipeline *pipeline;

	pipeline = new_pipeline(OPERATOR_MAIN);
	TEST_ASSERT_NOT_EQUAL(NULL, pipeline);
	TEST_ASSERT_EQUAL(OPERATOR_MAIN, pipeline->operator);
	TEST_ASSERT_EQUAL(0, pipeline->command_count);
	TEST_ASSERT_EQUAL(NULL, pipeline->commands);
	TEST_ASSERT_EQUAL(NULL, pipeline->pipefds);
	destroy_pipeline(pipeline);
}

int test_group_new(void) {
	UNITY_BEGIN();
	RUN_TEST(test_function_init_minishell);
	RUN_TEST(test_function_new_command);
	RUN_TEST(test_function_new_pipeline);
	return (UNITY_END());
}

int file_utils_test(void) {
	int err;
	err = test_group_new();
	if (!err)
		return (err);
	return (0);
}