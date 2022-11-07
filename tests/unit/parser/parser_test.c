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
	char *filename = "a.txt";
	char *expected = "test";
	char buf[5];
	int fd;

	output_token->type = TOKEN_OUTPUT;
	output_token->value = NULL;
	filename_token->type = TOKEN_WORD;
	filename_token->value = ft_strdup(filename);
	add_node(&(ms.token_list), output_token);
	add_node(&(ms.token_list), filename_token);
	handle_redirect_token(cmd_node, &ms);
	TEST_ASSERT_NOT_EQUAL_INT(STDOUT, ((t_cmd *)cmd_node->content)->output);
	fd = ((t_cmd *)cmd_node->content)->output;
	write(fd, expected, 4);
	close(fd);
	fd = open(filename, O_RDONLY);
	read(fd, &buf, 4);
	buf[4] = '\0';
	TEST_ASSERT_EQUAL_STRING(expected, buf);
	clear_list(ms.token_list, del_token_node);
	del_cmd_tree_node(cmd_node);
}

int file_parser_test(void) {
	UNITY_BEGIN();
	RUN_TEST(test_handle_word_tokens);
	RUN_TEST(test_handle_output_word);
	return UNITY_END();
}
