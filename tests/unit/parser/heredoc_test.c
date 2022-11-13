#include "Unity/unity.h"
#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include "structs.h"

void test_enqueue_heredoc_word(void) {
	t_tree *cmd_node = new_cmd_node(0);
	t_minishell ms;
	init_minishell(&ms, NULL);
	t_token *heredoc_token = malloc(sizeof(*heredoc_token));
	t_token *delimiter_token = malloc(sizeof(*delimiter_token));
	char *delimiter = "EOF";
	int result;

	heredoc_token->type = TOKEN_HEREDOC;
	heredoc_token->value = NULL;
	delimiter_token->type = TOKEN_WORD;
	delimiter_token->value = ft_strdup(delimiter);
	add_node(&(ms.token_list), heredoc_token);
	add_node(&(ms.token_list), delimiter_token);
	result = enqueue_heredoc(cmd_node, &ms);
	TEST_ASSERT_NOT_EQUAL(NULL, ms.heredoc_queue.front);
	TEST_ASSERT_NOT_EQUAL(NULL, ms.heredoc_queue.rear);
	TEST_ASSERT_EQUAL_PTR(ms.heredoc_queue.front, ms.heredoc_queue.rear);
	TEST_ASSERT_EQUAL(OK, result);
	TEST_ASSERT_EQUAL_STRING(
		delimiter, ((t_heredoc *)ms.heredoc_queue.front->content)->delimiter);
	TEST_ASSERT_EQUAL_PTR(cmd_node->content,
						  ((t_heredoc *)ms.heredoc_queue.front->content)->cmd);
	clear_list(ms.token_list, del_token_node);
	clear_list(ms.heredoc_queue.front, del_heredoc_node);
	del_cmd_tree_node(cmd_node);
}

void test_enqueue_heredoc_eol(void) {
	t_tree *cmd_node = new_cmd_node(0);
	t_minishell ms;
	init_minishell(&ms, NULL);
	t_token *heredoc_token = malloc(sizeof(*heredoc_token));
	int result;

	heredoc_token->type = TOKEN_HEREDOC;
	heredoc_token->value = NULL;
	add_node(&(ms.token_list), heredoc_token);
	result = enqueue_heredoc(cmd_node, &ms);
	TEST_ASSERT_EQUAL_PTR(NULL, ms.heredoc_queue.front);
	TEST_ASSERT_EQUAL_PTR(NULL, ms.heredoc_queue.rear);
	TEST_ASSERT_EQUAL(ERR_BAD_SYNTAX, result);
	clear_list(ms.token_list, del_token_node);
	del_cmd_tree_node(cmd_node);
}

int file_heredoc_test(void) {
	UNITY_BEGIN();
	RUN_TEST(test_enqueue_heredoc_word);
	RUN_TEST(test_enqueue_heredoc_eol);
	return UNITY_END();
}
