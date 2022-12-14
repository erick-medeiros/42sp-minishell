#include "Unity/unity.h"
#include "executor.h"
#include "minishell.h"
#include "parser.h"
#include "structs.h"

/*
void open_pipes(t_pipeline *pipeline);
void connect_pipes(t_pipeline *pipeline, t_cmd *command);
void close_pipes(t_pipeline *pipeline);

void test_connect_pipes() {
	TEST_IGNORE();
	t_pipeline *pipeline = new_pipeline(OPERATOR_MAIN);
	t_cmd *cmd1 = new_command(0);
	t_cmd *cmd2 = new_command(1);
	t_cmd *cmd3 = new_command(2);
	t_cmd *cmd4 = new_command(3);
	char *expected1 = "one";
	char *expected2 = "two";
	char *expected3 = "three";
	char *content;
	int link1[2];
	int link2[2];
	int link3[2];

	pipeline->command_count = 4;
	add_node(&pipeline->commands, cmd1);
	add_node(&pipeline->commands, cmd2);
	add_node(&pipeline->commands, cmd3);
	add_node(&pipeline->commands, cmd4);
	open_pipes(pipeline);
	connect_pipes(pipeline, cmd1);
	connect_pipes(pipeline, cmd2);
	connect_pipes(pipeline, cmd3);
	connect_pipes(pipeline, cmd4);
	link1[1] = dup(cmd1->output);
	link1[0] = dup(cmd2->input);
	link2[1] = dup(cmd2->output);
	link2[0] = dup(cmd3->input);
	link3[1] = dup(cmd3->output);
	link3[0] = dup(cmd4->input);
	close_pipes(pipeline);
	write(link1[1], expected1, strlen(expected1));
	write(link2[1], expected2, strlen(expected2));
	write(link3[1], expected3, strlen(expected3));
	close(link1[1]);
	close(link2[1]);
	close(link3[1]);
	content = ut_get_content_fd(link1[0]);
	TEST_ASSERT_EQUAL_STRING(expected1, content);
	free(content);
	content = ut_get_content_fd(link2[0]);
	TEST_ASSERT_EQUAL_STRING(expected2, content);
	free(content);
	content = ut_get_content_fd(link3[0]);
	TEST_ASSERT_EQUAL_STRING(expected3, content);
	free(content);
	close(link1[0]);
	close(link2[0]);
	close(link3[0]);
	destroy_pipeline(pipeline);
}
*/

int file_executor_test(void) {
	UNITY_BEGIN();
	// RUN_TEST(test_connect_pipes);
	return UNITY_END();
}
