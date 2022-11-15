#include "Unity/unity.h"
#include "executor.h"
#include "minishell.h"
#include "structs.h"

/*
void open_pipes(t_pipeline *pipeline);
void connect_pipes(t_pipeline *pipeline, t_cmd *command);
void close_pipes(t_pipeline *pipeline);

void test_open_pipes_no_open() {
	TEST_IGNORE();
	t_pipeline *pipeline = new_pipeline(OPERATOR_MAIN);

	TEST_ASSERT_EQUAL(NULL, pipeline->pipefds);
	pipeline->command_count = 0;
	open_pipes(pipeline);
	TEST_ASSERT_EQUAL(NULL, pipeline->pipefds);
	pipeline->command_count = 1;
	open_pipes(pipeline);
	TEST_ASSERT_EQUAL(NULL, pipeline->pipefds);
	destroy_pipeline(pipeline);
}

void test_open_pipes_one_pipe() {
	TEST_IGNORE();
	t_pipeline *pipeline = new_pipeline(OPERATOR_MAIN);
	char *expected;
	int fd;
	char *content;

	pipeline->command_count = 2;
	open_pipes(pipeline);
	TEST_ASSERT_NOT_EQUAL(NULL, pipeline->pipefds);
	expected = "one pipe\n";
	write(pipeline->pipefds[0][1], expected, strlen(expected));
	fd = dup(pipeline->pipefds[0][0]);
	close_pipes(pipeline);
	content = ut_get_content_fd(fd);
	close(fd);
	TEST_ASSERT_EQUAL_STRING(expected, content);
	free(content);
	destroy_pipeline(pipeline);
}

void test_open_pipes_two_pipes() {
	TEST_IGNORE();
	t_pipeline *pipeline = new_pipeline(OPERATOR_MAIN);
	char *expected;
	char *expected2;
	char *content;
	char *content2;
	int fd;
	int fd2;

	pipeline->command_count = 3;
	open_pipes(pipeline);
	TEST_ASSERT_NOT_EQUAL(NULL, pipeline->pipefds);
	expected = "one pipe\n";
	expected2 = "two pipes\n";
	write(pipeline->pipefds[0][1], expected, strlen(expected));
	write(pipeline->pipefds[1][1], expected2, strlen(expected2));
	fd = dup(pipeline->pipefds[0][0]);
	fd2 = dup(pipeline->pipefds[1][0]);
	close_pipes(pipeline);
	content = ut_get_content_fd(fd);
	content2 = ut_get_content_fd(fd2);
	TEST_ASSERT_EQUAL_STRING(expected, content);
	TEST_ASSERT_EQUAL_STRING(expected2, content2);
	free(content);
	free(content2);
	close(fd);
	close(fd2);
	destroy_pipeline(pipeline);
}
*/
int file_pipeline_test(void) {
	UNITY_BEGIN();
	// RUN_TEST(test_open_pipes_no_open);
	// RUN_TEST(test_open_pipes_one_pipe);
	// RUN_TEST(test_open_pipes_two_pipes);
	return UNITY_END();
}
