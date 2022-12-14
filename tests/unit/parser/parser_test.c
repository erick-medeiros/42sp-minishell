#include "Unity/unity.h"
#include "lexer.h"
#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include "structs.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

void test_handle_word_tokens(void) {
	t_tree *cmd_node = new_cmd_node(0);
	t_minishell ms;
	t_node *word_tokens;
	t_token *token;
	init_minishell(&ms, NULL);
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
	TEST_ASSERT_EQUAL_INT(0, ((t_cmd *)cmd_node->content)->argc);
	word_tokens = ((t_cmd *)cmd_node->content)->word_tokens;
	token = word_tokens->content;
	TEST_ASSERT_EQUAL_STRING("cmd", token->value);
	word_tokens = ((t_node *)word_tokens->next);
	token = word_tokens->content;
	TEST_ASSERT_EQUAL_STRING("arg", token->value);
	clear_list(ms.token_list, del_token_node);
	del_cmd_tree_node(cmd_node);
}

void test_handle_output_word(void) {
	TEST_IGNORE();
	t_tree *cmd_node = new_cmd_node(0);
	t_minishell ms;
	init_minishell(&ms, NULL);
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
	t_minishell ms;
	init_minishell(&ms, NULL);
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
	TEST_IGNORE();
	t_tree *cmd_node = new_cmd_node(0);
	t_minishell ms;
	init_minishell(&ms, NULL);
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
	t_minishell ms;
	init_minishell(&ms, NULL);
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

void test_get_complete_command(void) {
	t_tree *cmd_node = NULL;
	t_minishell ms;
	init_minishell(&ms, NULL);
	t_val_info vi;
	char *cmd = "echo";
	char *arg1 = "'a'";
	char *arg2 = "b";
	char *arg3 = "\"c\"";
	char *in_filename = "in.txt";
	char *out_filename = "out.txt";
	int result;
	int fd;
	t_node *word_tokens;
	t_token *token;

	fd = open(in_filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
	close(fd);
	vi = (t_val_info){.line = cmd, .start = 0, .len = ft_strlen(cmd)};
	new_token_with_val(&(ms.token_list), TOKEN_WORD, &vi);
	vi = (t_val_info){.line = arg1, .start = 0, .len = ft_strlen(arg1)};
	new_token_with_val(&(ms.token_list), TOKEN_WORD, &vi);
	new_token(&(ms.token_list), TOKEN_INPUT);
	vi = (t_val_info){
		.line = in_filename, .start = 0, .len = ft_strlen(in_filename)};
	new_token_with_val(&(ms.token_list), TOKEN_WORD, &vi);
	new_token(&(ms.token_list), TOKEN_OUTPUT);
	vi = (t_val_info){
		.line = out_filename, .start = 0, .len = ft_strlen(out_filename)};
	new_token_with_val(&(ms.token_list), TOKEN_WORD, &vi);
	vi = (t_val_info){.line = arg2, .start = 0, .len = ft_strlen(arg2)};
	new_token_with_val(&(ms.token_list), TOKEN_WORD, &vi);
	vi = (t_val_info){.line = arg3, .start = 0, .len = ft_strlen(arg3)};
	new_token_with_val(&(ms.token_list), TOKEN_WORD, &vi);
	result = get_command(&cmd_node, &ms, 0);
	TEST_ASSERT_EQUAL_INT(OK, result);
	TEST_ASSERT_NOT_EQUAL(NULL, cmd_node);
	TEST_ASSERT_EQUAL_INT(0, ((t_cmd *)cmd_node->content)->argc);
	word_tokens = ((t_cmd *)cmd_node->content)->word_tokens;
	token = word_tokens->content;
	TEST_ASSERT_EQUAL_STRING(cmd, token->value);
	word_tokens = word_tokens->next;
	token = word_tokens->content;
	TEST_ASSERT_EQUAL_STRING(arg1, token->value);
	word_tokens = word_tokens->next;
	token = word_tokens->content;
	TEST_ASSERT_EQUAL_STRING(arg2, token->value);
	word_tokens = word_tokens->next;
	token = word_tokens->content;
	TEST_ASSERT_EQUAL_STRING(arg3, token->value);
	TEST_ASSERT_EQUAL_PTR(NULL, word_tokens->next);
	TEST_ASSERT_EQUAL(STDIN, ((t_cmd *)cmd_node->content)->input);
	TEST_ASSERT_EQUAL(STDOUT, ((t_cmd *)cmd_node->content)->output);
	TEST_ASSERT_EQUAL_PTR(NULL, ms.token_list);
	remove(in_filename);
	remove(out_filename);
	del_cmd_tree_node(cmd_node);
}

void test_get_complete_command_pipe(void) {
	t_tree *cmd_node = NULL;
	t_minishell ms =
		(t_minishell){.env_list = {.list = NULL, .len = 0},
					  .token_list = NULL,
					  .heredoc_queue = {.front = NULL, .rear = NULL},
					  .cmd_list.front = NULL,
					  .cmd_list.rear = NULL,
					  .root = NULL};
	t_val_info vi;
	char *cmd_a = "echo";
	char *arg_a1 = "'a'";
	char *arg_a2 = "b";
	char *arg_a3 = "\"c\"";
	int result;
	t_node *word_tokens;

	vi = (t_val_info){.line = cmd_a, .start = 0, .len = ft_strlen(cmd_a)};
	new_token_with_val(&(ms.token_list), TOKEN_WORD, &vi);
	vi = (t_val_info){.line = arg_a1, .start = 0, .len = ft_strlen(arg_a1)};
	new_token_with_val(&(ms.token_list), TOKEN_WORD, &vi);
	vi = (t_val_info){.line = arg_a2, .start = 0, .len = ft_strlen(arg_a2)};
	new_token_with_val(&(ms.token_list), TOKEN_WORD, &vi);
	vi = (t_val_info){.line = arg_a3, .start = 0, .len = ft_strlen(arg_a3)};
	new_token_with_val(&(ms.token_list), TOKEN_WORD, &vi);
	new_token(&(ms.token_list), TOKEN_PIPE);
	result = get_command(&cmd_node, &ms, 0);
	TEST_ASSERT_EQUAL_INT(OK, result);
	TEST_ASSERT_NOT_EQUAL(NULL, cmd_node);
	TEST_ASSERT_EQUAL_INT(0, ((t_cmd *)cmd_node->content)->argc);
	word_tokens = ((t_cmd *)cmd_node->content)->word_tokens;
	TEST_ASSERT_EQUAL_STRING(cmd_a, ((t_token *)word_tokens->content)->value);
	word_tokens = word_tokens->next;
	TEST_ASSERT_EQUAL_STRING(arg_a1, ((t_token *)word_tokens->content)->value);
	word_tokens = word_tokens->next;
	TEST_ASSERT_EQUAL_STRING(arg_a2, ((t_token *)word_tokens->content)->value);
	word_tokens = word_tokens->next;
	TEST_ASSERT_EQUAL_STRING(arg_a3, ((t_token *)word_tokens->content)->value);
	TEST_ASSERT_EQUAL_PTR(NULL, word_tokens->next);
	TEST_ASSERT_NOT_EQUAL(NULL, ms.token_list);
	TEST_ASSERT_EQUAL(TOKEN_PIPE, ((t_token *)ms.token_list->content)->type);
	del_cmd_tree_node(cmd_node);
	clear_list(ms.token_list, del_token_node);
}

int file_parser_test(void) {
	UNITY_BEGIN();
	RUN_TEST(test_handle_word_tokens);
	RUN_TEST(test_handle_output_word);
	RUN_TEST(test_handle_output_eol);
	RUN_TEST(test_handle_output_word_output_word);
	RUN_TEST(test_handle_output_pipe);
	RUN_TEST(test_get_complete_command);
	RUN_TEST(test_get_complete_command_pipe);
	return UNITY_END();
}
