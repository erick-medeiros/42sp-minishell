#include "Unity/unity.h"
#include "lexer.h"
#include "minishell.h"
#include "structs.h"

void test_tokenize_empty_string(void) {
	char *prompt = "";
	t_node *tokens = NULL;
	int result;

	result = lexer(prompt, &tokens, STATE_SKIP);
	TEST_ASSERT_EQUAL_INT(OK, result);
	TEST_ASSERT_EQUAL_INT(NULL, tokens);
	TEST_ASSERT_EQUAL(NULL, tokens->next);
}

void test_tokenize_word_pipe_word_no_space(void) {
	char *prompt = "abc|def";
	t_node *tokens = NULL;
	int result;

	result = lexer(prompt, &tokens, STATE_SKIP);
	TEST_ASSERT_EQUAL_INT(OK, result);
	TEST_ASSERT_NOT_EQUAL(NULL, tokens);
	TEST_ASSERT_EQUAL(TOKEN_WORD, ((t_token *)tokens->content)->type);
	TEST_ASSERT_EQUAL_STRING("abc", ((t_token *)tokens->content)->value);
	TEST_ASSERT_EQUAL(TOKEN_PIPE, ((t_token *)tokens->next->content)->type);
	TEST_ASSERT_EQUAL_PTR(NULL, ((t_token *)tokens->next->content)->value);
	TEST_ASSERT_EQUAL(TOKEN_WORD,
					  ((t_token *)tokens->next->next->content)->type);
	TEST_ASSERT_EQUAL_STRING("def",
							 ((t_token *)tokens->next->next->content)->value);
	TEST_ASSERT_EQUAL(NULL, tokens->next->next->next);
	clear_list(tokens, del_token_node);
}

void test_tokenize_word_pipe_word_space(void) {
	char *prompt = "abc | def";
	t_node *tokens = NULL;
	int result;

	result = lexer(prompt, &tokens, STATE_SKIP);
	TEST_ASSERT_EQUAL_INT(OK, result);
	TEST_ASSERT_NOT_EQUAL(NULL, tokens);
	TEST_ASSERT_EQUAL(TOKEN_WORD, ((t_token *)tokens->content)->type);
	TEST_ASSERT_EQUAL_STRING("abc", ((t_token *)tokens->content)->value);
	TEST_ASSERT_EQUAL(TOKEN_PIPE, ((t_token *)tokens->next->content)->type);
	TEST_ASSERT_EQUAL_PTR(NULL, ((t_token *)tokens->next->content)->value);
	TEST_ASSERT_EQUAL(TOKEN_WORD,
					  ((t_token *)tokens->next->next->content)->type);
	TEST_ASSERT_EQUAL_STRING("def",
							 ((t_token *)tokens->next->next->content)->value);
	TEST_ASSERT_EQUAL(NULL, tokens->next->next->next);
	clear_list(tokens, del_token_node);
}

void test_tokenize_word_pipe_dquote(void) {
	char *prompt = "abc | \"def\"";
	t_node *tokens = NULL;
	int result;

	result = lexer(prompt, &tokens, STATE_SKIP);
	TEST_ASSERT_EQUAL_INT(OK, result);
	TEST_ASSERT_NOT_EQUAL(NULL, tokens);
	TEST_ASSERT_EQUAL(TOKEN_WORD, ((t_token *)tokens->content)->type);
	TEST_ASSERT_EQUAL_STRING("abc", ((t_token *)tokens->content)->value);
	TEST_ASSERT_EQUAL(TOKEN_PIPE, ((t_token *)tokens->next->content)->type);
	TEST_ASSERT_EQUAL_PTR(NULL, ((t_token *)tokens->next->content)->value);
	TEST_ASSERT_EQUAL(TOKEN_DQUOTE,
					  ((t_token *)tokens->next->next->content)->type);
	TEST_ASSERT_EQUAL_STRING("def",
							 ((t_token *)tokens->next->next->content)->value);
	TEST_ASSERT_EQUAL(NULL, tokens->next->next->next);
	clear_list(tokens, del_token_node);
}

void test_tokenize_word_pipe_dquote_incomplete(void) {
	char *prompt = "abc | \"def";
	t_node *tokens = NULL;
	int result;

	result = lexer(prompt, &tokens, STATE_SKIP);
	TEST_ASSERT_EQUAL_INT(OK, result);
	TEST_ASSERT_NOT_EQUAL(NULL, tokens);
	TEST_ASSERT_EQUAL(TOKEN_WORD, ((t_token *)tokens->content)->type);
	TEST_ASSERT_EQUAL_STRING("abc", ((t_token *)tokens->content)->value);
	TEST_ASSERT_EQUAL(TOKEN_PIPE, ((t_token *)tokens->next->content)->type);
	TEST_ASSERT_EQUAL_PTR(NULL, ((t_token *)tokens->next->content)->value);
	TEST_ASSERT_EQUAL(TOKEN_DQINCOMP,
					  ((t_token *)tokens->next->next->content)->type);
	TEST_ASSERT_EQUAL_STRING("def",
							 ((t_token *)tokens->next->next->content)->value);
	TEST_ASSERT_EQUAL(NULL, tokens->next->next->next);
	clear_list(tokens, del_token_node);
}

void test_tokenize_word_pipe_squote(void) {
	char *prompt = "abc | 'def'";
	t_node *tokens = NULL;
	int result;

	result = lexer(prompt, &tokens, STATE_SKIP);
	TEST_ASSERT_EQUAL_INT(OK, result);
	TEST_ASSERT_NOT_EQUAL(NULL, tokens);
	TEST_ASSERT_EQUAL(TOKEN_WORD, ((t_token *)tokens->content)->type);
	TEST_ASSERT_EQUAL_STRING("abc", ((t_token *)tokens->content)->value);
	TEST_ASSERT_EQUAL(TOKEN_PIPE, ((t_token *)tokens->next->content)->type);
	TEST_ASSERT_EQUAL_PTR(NULL, ((t_token *)tokens->next->content)->value);
	TEST_ASSERT_EQUAL(TOKEN_SQUOTE,
					  ((t_token *)tokens->next->next->content)->type);
	TEST_ASSERT_EQUAL_STRING("def",
							 ((t_token *)tokens->next->next->content)->value);
	TEST_ASSERT_EQUAL(NULL, tokens->next->next->next);
	clear_list(tokens, del_token_node);
}

void test_tokenize_word_pipe_squote_incomplete(void) {
	char *prompt = "abc | 'def";
	t_node *tokens = NULL;
	int result;

	result = lexer(prompt, &tokens, STATE_SKIP);
	TEST_ASSERT_EQUAL_INT(OK, result);
	TEST_ASSERT_NOT_EQUAL(NULL, tokens);
	TEST_ASSERT_EQUAL(TOKEN_WORD, ((t_token *)tokens->content)->type);
	TEST_ASSERT_EQUAL_STRING("abc", ((t_token *)tokens->content)->value);
	TEST_ASSERT_EQUAL(TOKEN_PIPE, ((t_token *)tokens->next->content)->type);
	TEST_ASSERT_EQUAL_PTR(NULL, ((t_token *)tokens->next->content)->value);
	TEST_ASSERT_EQUAL(TOKEN_SQINCOMP,
					  ((t_token *)tokens->next->next->content)->type);
	TEST_ASSERT_EQUAL_STRING("def",
							 ((t_token *)tokens->next->next->content)->value);
	TEST_ASSERT_EQUAL(NULL, tokens->next->next->next);
	clear_list(tokens, del_token_node);
}

void test_tokenize_word_append_squote(void) {
	char *prompt = "abc >> 'def'";
	t_node *tokens = NULL;
	int result;

	result = lexer(prompt, &tokens, STATE_SKIP);
	TEST_ASSERT_EQUAL_INT(OK, result);
	TEST_ASSERT_NOT_EQUAL(NULL, tokens);
	TEST_ASSERT_EQUAL(TOKEN_WORD, ((t_token *)tokens->content)->type);
	TEST_ASSERT_EQUAL_STRING("abc", ((t_token *)tokens->content)->value);
	TEST_ASSERT_EQUAL(TOKEN_APPEND, ((t_token *)tokens->next->content)->type);
	TEST_ASSERT_EQUAL_PTR(NULL, ((t_token *)tokens->next->content)->value);
	TEST_ASSERT_EQUAL(TOKEN_SQUOTE,
					  ((t_token *)tokens->next->next->content)->type);
	TEST_ASSERT_EQUAL_STRING("def",
							 ((t_token *)tokens->next->next->content)->value);
	TEST_ASSERT_EQUAL(NULL, tokens->next->next->next);
	clear_list(tokens, del_token_node);
}

void test_tokenize_word_heredoc_squote(void) {
	char *prompt = "abc << 'def'";
	t_node *tokens = NULL;
	int result;

	result = lexer(prompt, &tokens, STATE_SKIP);
	TEST_ASSERT_EQUAL_INT(OK, result);
	TEST_ASSERT_NOT_EQUAL(NULL, tokens);
	TEST_ASSERT_EQUAL(TOKEN_WORD, ((t_token *)tokens->content)->type);
	TEST_ASSERT_EQUAL_STRING("abc", ((t_token *)tokens->content)->value);
	TEST_ASSERT_EQUAL(TOKEN_HEREDOC, ((t_token *)tokens->next->content)->type);
	TEST_ASSERT_EQUAL_PTR(NULL, ((t_token *)tokens->next->content)->value);
	TEST_ASSERT_EQUAL(TOKEN_SQUOTE,
					  ((t_token *)tokens->next->next->content)->type);
	TEST_ASSERT_EQUAL_STRING("def",
							 ((t_token *)tokens->next->next->content)->value);
	TEST_ASSERT_EQUAL(NULL, tokens->next->next->next);
	clear_list(tokens, del_token_node);
}

void test_tokenize_word_input_squote(void) {
	char *prompt = "abc < 'def'";
	t_node *tokens = NULL;
	int result;

	result = lexer(prompt, &tokens, STATE_SKIP);
	TEST_ASSERT_EQUAL_INT(OK, result);
	TEST_ASSERT_NOT_EQUAL(NULL, tokens);
	TEST_ASSERT_EQUAL(TOKEN_WORD, ((t_token *)tokens->content)->type);
	TEST_ASSERT_EQUAL_STRING("abc", ((t_token *)tokens->content)->value);
	TEST_ASSERT_EQUAL(TOKEN_INPUT, ((t_token *)tokens->next->content)->type);
	TEST_ASSERT_EQUAL_PTR(NULL, ((t_token *)tokens->next->content)->value);
	TEST_ASSERT_EQUAL(TOKEN_SQUOTE,
					  ((t_token *)tokens->next->next->content)->type);
	TEST_ASSERT_EQUAL_STRING("def",
							 ((t_token *)tokens->next->next->content)->value);
	TEST_ASSERT_EQUAL(NULL, tokens->next->next->next);
	clear_list(tokens, del_token_node);
}

void test_tokenize_word_output_squote(void) {
	char *prompt = "abc > 'def'";
	t_node *tokens = NULL;
	int result;

	result = lexer(prompt, &tokens, STATE_SKIP);
	TEST_ASSERT_EQUAL_INT(OK, result);
	TEST_ASSERT_NOT_EQUAL(NULL, tokens);
	TEST_ASSERT_EQUAL(TOKEN_WORD, ((t_token *)tokens->content)->type);
	TEST_ASSERT_EQUAL_STRING("abc", ((t_token *)tokens->content)->value);
	TEST_ASSERT_EQUAL(TOKEN_OUTPUT, ((t_token *)tokens->next->content)->type);
	TEST_ASSERT_EQUAL_PTR(NULL, ((t_token *)tokens->next->content)->value);
	TEST_ASSERT_EQUAL(TOKEN_SQUOTE,
					  ((t_token *)tokens->next->next->content)->type);
	TEST_ASSERT_EQUAL_STRING("def",
							 ((t_token *)tokens->next->next->content)->value);
	TEST_ASSERT_EQUAL(NULL, tokens->next->next->next);
	clear_list(tokens, del_token_node);
}

int file_lexer_test(void) {
	UNITY_BEGIN();
	RUN_TEST(test_tokenize_word_pipe_dquote);
	RUN_TEST(test_tokenize_word_pipe_dquote_incomplete);
	RUN_TEST(test_tokenize_word_pipe_squote);
	RUN_TEST(test_tokenize_word_pipe_squote_incomplete);
	RUN_TEST(test_tokenize_word_append_squote);
	RUN_TEST(test_tokenize_word_heredoc_squote);
	RUN_TEST(test_tokenize_word_input_squote);
	RUN_TEST(test_tokenize_word_output_squote);
	return UNITY_END();
}
