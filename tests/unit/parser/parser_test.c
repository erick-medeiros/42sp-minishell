#include "Unity/unity.h"
#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include "structs.h"
#include <fcntl.h>
#include <unistd.h>

void test_handle_word_tokens(void) {
	t_tree *cmd_node = new_cmd_node(0);
	t_minishell ms =
		(t_minishell){.env_list = {.list = NULL, .len = 0},
					  .token_list = NULL,
					  .heredoc_queue = {.front = NULL, .rear = NULL},
					  .cmd_list = NULL,
					  .root = NULL,
					  .last_result = 0};
	t_token *cmd_token = malloc(sizeof(*cmd_token));
	t_token *arg_token = malloc(sizeof(*arg_token));

	cmd_token->type = TOKEN_WORD;
	cmd_token->value = ft_strdup("cmd");
	arg_token->type = TOKEN_WORD;
	arg_token->value = ft_strdup("arg");
	add_node(&(ms.token_list), cmd_token);
	add_node(&(ms.token_list), arg_token);
	handle_word_token(cmd_node, &ms);
	ms.token_list = remove_node(ms.token_list, del_token_node);
	handle_word_token(cmd_node, &ms);
	TEST_ASSERT_EQUAL_INT(2, ((t_cmd *)cmd_node->content)->argc);
	TEST_ASSERT_EQUAL_STRING("cmd", ((t_cmd *)cmd_node->content)->argv[0]);
	TEST_ASSERT_EQUAL_STRING("arg", ((t_cmd *)cmd_node->content)->argv[1]);
	clear_list(ms.token_list, del_token_node);
	del_cmd_tree_node(cmd_node);
}

void test_handle_output_word(void) {
	t_tree *cmd_node = new_cmd_node(0);
	t_minishell ms =
		(t_minishell){.env_list = {.list = NULL, .len = 0},
					  .token_list = NULL,
					  .heredoc_queue = {.front = NULL, .rear = NULL},
					  .cmd_list = NULL,
					  .root = NULL,
					  .last_result = 0};
	t_token *output_token = malloc(sizeof(*output_token));
	t_token *filename_token = malloc(sizeof(*filename_token));
	char *filename = "out.txt";
	char *expected = "test";
	char buf[5];
	int fd;
	int result;

	output_token->type = TOKEN_OUTPUT;
	output_token->value = NULL;
	filename_token->type = TOKEN_WORD;
	filename_token->value = ft_strdup(filename);
	add_node(&(ms.token_list), output_token);
	add_node(&(ms.token_list), filename_token);
	result = handle_redirect_token(cmd_node, &ms);
	TEST_ASSERT_NOT_EQUAL_INT(STDOUT, ((t_cmd *)cmd_node->content)->output);
	TEST_ASSERT_EQUAL(OK, result);
	fd = ((t_cmd *)cmd_node->content)->output;
	write(fd, expected, 4);
	close(fd);
	fd = open(filename, O_RDONLY);
	read(fd, &buf, 4);
	buf[4] = '\0';
	TEST_ASSERT_EQUAL_STRING(expected, buf);
	close(fd);
	remove(filename);
	clear_list(ms.token_list, del_token_node);
	del_cmd_tree_node(cmd_node);
}

void test_handle_output_eol(void) {
	t_tree *cmd_node = new_cmd_node(0);
	t_minishell ms =
		(t_minishell){.env_list = {.list = NULL, .len = 0},
					  .token_list = NULL,
					  .heredoc_queue = {.front = NULL, .rear = NULL},
					  .cmd_list = NULL,
					  .root = NULL,
					  .last_result = 0};
	t_token *output_token = malloc(sizeof(*output_token));
	int result;

	output_token->type = TOKEN_OUTPUT;
	output_token->value = NULL;
	add_node(&(ms.token_list), output_token);
	result = handle_redirect_token(cmd_node, &ms);
	TEST_ASSERT_EQUAL_PTR(NULL, ms.token_list);
	TEST_ASSERT_EQUAL(ERR_BAD_SYNTAX, result);
	del_cmd_tree_node(cmd_node);
}

void test_handle_output_word_output_word(void) {
	t_tree *cmd_node = new_cmd_node(0);
	t_minishell ms =
		(t_minishell){.env_list = {.list = NULL, .len = 0},
					  .token_list = NULL,
					  .heredoc_queue = {.front = NULL, .rear = NULL},
					  .cmd_list = NULL,
					  .root = NULL,
					  .last_result = 0};
	t_token *output1_token = malloc(sizeof(*output1_token));
	t_token *filename1_token = malloc(sizeof(*filename1_token));
	t_token *output2_token = malloc(sizeof(*output2_token));
	t_token *filename2_token = malloc(sizeof(*filename2_token));
	char *filename1 = "out1.txt";
	char *filename2 = "out2.txt";
	char *expected = "test";
	char buf[5];
	int fd;
	int result;
	int num_read;

	output1_token->type = TOKEN_OUTPUT;
	output1_token->value = NULL;
	filename1_token->type = TOKEN_WORD;
	filename1_token->value = ft_strdup(filename1);
	output2_token->type = TOKEN_OUTPUT;
	output2_token->value = NULL;
	filename2_token->type = TOKEN_WORD;
	filename2_token->value = ft_strdup(filename2);
	add_node(&(ms.token_list), output1_token);
	add_node(&(ms.token_list), filename1_token);
	add_node(&(ms.token_list), output2_token);
	add_node(&(ms.token_list), filename2_token);
	result = handle_redirect_token(cmd_node, &ms);
	TEST_ASSERT_NOT_EQUAL_INT(STDOUT, ((t_cmd *)cmd_node->content)->output);
	TEST_ASSERT_EQUAL(OK, result);
	ms.token_list = remove_node(ms.token_list, del_token_node);
	result = handle_redirect_token(cmd_node, &ms);
	TEST_ASSERT_NOT_EQUAL_INT(STDOUT, ((t_cmd *)cmd_node->content)->output);
	TEST_ASSERT_EQUAL(OK, result);
	fd = ((t_cmd *)cmd_node->content)->output;
	write(fd, expected, 4);
	close(fd);
	fd = open(filename1, O_RDONLY);
	num_read = read(fd, &buf, 4);
	TEST_ASSERT_EQUAL_INT(0, num_read);
	close(fd);
	fd = open(filename2, O_RDONLY);
	read(fd, &buf, 4);
	buf[4] = '\0';
	TEST_ASSERT_EQUAL_STRING(expected, buf);
	close(fd);
	remove(filename1);
	remove(filename2);
	clear_list(ms.token_list, del_token_node);
	del_cmd_tree_node(cmd_node);
}

void test_handle_output_pipe(void) {
	t_tree *cmd_node = new_cmd_node(0);
	t_minishell ms =
		(t_minishell){.env_list = {.list = NULL, .len = 0},
					  .token_list = NULL,
					  .heredoc_queue = {.front = NULL, .rear = NULL},
					  .cmd_list = NULL,
					  .root = NULL,
					  .last_result = 0};
	t_token *output_token = malloc(sizeof(*output_token));
	t_token *pipe_token = malloc(sizeof(*pipe_token));
	int result;

	output_token->type = TOKEN_OUTPUT;
	output_token->value = NULL;
	pipe_token->type = TOKEN_PIPE;
	pipe_token->value = NULL;
	add_node(&(ms.token_list), output_token);
	add_node(&(ms.token_list), pipe_token);
	result = handle_redirect_token(cmd_node, &ms);
	TEST_ASSERT_EQUAL_INT(STDOUT, ((t_cmd *)cmd_node->content)->output);
	TEST_ASSERT_EQUAL(ERR_BAD_SYNTAX, result);
	clear_list(ms.token_list, del_token_node);
	del_cmd_tree_node(cmd_node);
}

int file_parser_test(void) {
	UNITY_BEGIN();
	RUN_TEST(test_handle_word_tokens);
	RUN_TEST(test_handle_output_word);
	RUN_TEST(test_handle_output_eol);
	RUN_TEST(test_handle_output_word_output_word);
	RUN_TEST(test_handle_output_pipe);
	return UNITY_END();
}
