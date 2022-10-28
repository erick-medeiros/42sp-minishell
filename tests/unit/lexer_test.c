#include "Unity/unity.h"
#include "minishell.h"
#include "structs.h"

void test_new_token(void) {
	t_node *tokens = NULL;

	new_token(&tokens, TOKEN_OUTPUT);
	new_token(&tokens, TOKEN_PIPE);
	TEST_ASSERT_NOT_EQUAL(NULL, tokens);
	TEST_ASSERT_EQUAL(TOKEN_OUTPUT, ((t_token *)tokens->content)->type);
	TEST_ASSERT_EQUAL(NULL, ((t_token *)tokens->content)->value);
	TEST_ASSERT_NOT_EQUAL(NULL, tokens->next);
	TEST_ASSERT_EQUAL(TOKEN_PIPE, ((t_token *)tokens->next->content)->type);
	TEST_ASSERT_EQUAL(NULL, ((t_token *)tokens->next->content)->value);
	TEST_ASSERT_EQUAL(NULL, tokens->next->next);
	clear_list(tokens, del_token_node);
}

void test_new_token_with_value(void) {
	char *prompt = " abcde ";
	t_node *tokens = NULL;
	t_val_info vi =
		(t_val_info){.start = 1, .len = 5, .prompt = prompt, .active = 1};

	new_token_with_val(&tokens, TOKEN_WORD, &vi);
	TEST_ASSERT_NOT_EQUAL(NULL, tokens);
	TEST_ASSERT_EQUAL(TOKEN_WORD, ((t_token *)tokens->content)->type);
	TEST_ASSERT_EQUAL_STRING("abcde", ((t_token *)tokens->content)->value);
	TEST_ASSERT_EQUAL(NULL, tokens->next);
	TEST_ASSERT_EQUAL_INT(0, vi.active);
	TEST_ASSERT_EQUAL_INT(0, vi.len);
	clear_list(tokens, del_token_node);
}

void test_init_word_value(void) {
	t_lex_state result;
	size_t idx = 2;
	t_val_info vi =
		(t_val_info){.start = 0, .len = 0, .prompt = NULL, .active = 0};

	result = init_word_value(idx, &vi, STATE_APPEND);
	TEST_ASSERT_EQUAL(STATE_APPEND, result);
	TEST_ASSERT_EQUAL_INT(idx, vi.start);
	TEST_ASSERT_EQUAL_INT(1, vi.len);
	TEST_ASSERT_EQUAL_INT(1, vi.active);
	TEST_ASSERT_EQUAL_PTR(NULL, vi.prompt);
}

void test_handle_append(void) {
	char *prompt = "";
	t_lex_state next_state;
	t_node *tokens = NULL;
	t_val_info vi =
		(t_val_info){.start = 0, .len = 0, .prompt = prompt, .active = 0};
	size_t idx = 0;

	next_state = handle_append_state(idx, &tokens, &vi);
	TEST_ASSERT_EQUAL(STATE_COMPLETE, next_state);
	TEST_ASSERT_NOT_EQUAL(NULL, tokens);
	TEST_ASSERT_EQUAL(TOKEN_APPEND, ((t_token *)tokens->content)->type);
	TEST_ASSERT_EQUAL(NULL, ((t_token *)tokens->content)->value);
	TEST_ASSERT_EQUAL(NULL, tokens->next);
	clear_list(tokens, del_token_node);
}

void test_handle_dquote_complete(void) {
	char *prompt = "\"abc\"";
	t_lex_state next_state;
	t_node *tokens = NULL;
	t_val_info vi =
		(t_val_info){.start = 0, .len = 0, .prompt = prompt, .active = 0};
	size_t idx = 0;

	while (++idx < 5)
		next_state = handle_dquote_state(idx, &tokens, &vi);
	TEST_ASSERT_EQUAL(STATE_SKIP, next_state);
	TEST_ASSERT_NOT_EQUAL(NULL, tokens);
	TEST_ASSERT_EQUAL(TOKEN_DQUOTE, ((t_token *)tokens->content)->type);
	TEST_ASSERT_EQUAL_STRING("abc", ((t_token *)tokens->content)->value);
	TEST_ASSERT_EQUAL(NULL, tokens->next);
	clear_list(tokens, del_token_node);
}

void test_handle_dquote_incomplete(void) {
	char *prompt = "\"abc";
	t_lex_state next_state;
	t_node *tokens = NULL;
	t_val_info vi =
		(t_val_info){.start = 0, .len = 0, .prompt = prompt, .active = 0};
	size_t idx = 0;

	while (++idx < 5)
		next_state = handle_dquote_state(idx, &tokens, &vi);
	TEST_ASSERT_EQUAL(STATE_DQINCOMP, next_state);
	TEST_ASSERT_NOT_EQUAL(NULL, tokens);
	TEST_ASSERT_EQUAL(TOKEN_DQINCOMP, ((t_token *)tokens->content)->type);
	TEST_ASSERT_EQUAL_STRING("abc", ((t_token *)tokens->content)->value);
	TEST_ASSERT_EQUAL(NULL, tokens->next);
	clear_list(tokens, del_token_node);
}

void test_handle_heredoc(void) {
	char *prompt = "";
	t_lex_state next_state;
	t_node *tokens = NULL;
	t_val_info vi =
		(t_val_info){.start = 0, .len = 0, .prompt = prompt, .active = 0};
	size_t idx = 0;

	next_state = handle_heredoc_state(idx, &tokens, &vi);
	TEST_ASSERT_EQUAL(STATE_COMPLETE, next_state);
	TEST_ASSERT_NOT_EQUAL(NULL, tokens);
	TEST_ASSERT_EQUAL(TOKEN_HEREDOC, ((t_token *)tokens->content)->type);
	TEST_ASSERT_EQUAL(NULL, ((t_token *)tokens->content)->value);
	TEST_ASSERT_EQUAL(NULL, tokens->next);
	clear_list(tokens, del_token_node);
}

void test_handle_input(void) {
	char *prompt = "";
	t_lex_state next_state;
	t_node *tokens = NULL;
	t_val_info vi =
		(t_val_info){.start = 0, .len = 0, .prompt = prompt, .active = 0};
	size_t idx = 0;

	next_state = handle_input_state(idx, &tokens, &vi);
	TEST_ASSERT_EQUAL(STATE_COMPLETE, next_state);
	TEST_ASSERT_NOT_EQUAL(NULL, tokens);
	TEST_ASSERT_EQUAL(TOKEN_INPUT, ((t_token *)tokens->content)->type);
	TEST_ASSERT_EQUAL(NULL, ((t_token *)tokens->content)->value);
	TEST_ASSERT_EQUAL(NULL, tokens->next);
	clear_list(tokens, del_token_node);
}

void test_handle_output(void) {
	char *prompt = "";
	t_lex_state next_state;
	t_node *tokens = NULL;
	t_val_info vi =
		(t_val_info){.start = 0, .len = 0, .prompt = prompt, .active = 0};
	size_t idx = 0;

	next_state = handle_output_state(idx, &tokens, &vi);
	TEST_ASSERT_EQUAL(STATE_COMPLETE, next_state);
	TEST_ASSERT_NOT_EQUAL(NULL, tokens);
	TEST_ASSERT_EQUAL(TOKEN_OUTPUT, ((t_token *)tokens->content)->type);
	TEST_ASSERT_EQUAL(NULL, ((t_token *)tokens->content)->value);
	TEST_ASSERT_EQUAL(NULL, tokens->next);
	clear_list(tokens, del_token_node);
}

void test_handle_pipe(void) {
	char *prompt = "";
	t_lex_state next_state;
	t_node *tokens = NULL;
	t_val_info vi =
		(t_val_info){.start = 0, .len = 0, .prompt = prompt, .active = 0};
	size_t idx = 0;

	next_state = handle_pipe_state(idx, &tokens, &vi);
	TEST_ASSERT_EQUAL(STATE_COMPLETE, next_state);
	TEST_ASSERT_NOT_EQUAL(NULL, tokens);
	TEST_ASSERT_EQUAL(TOKEN_PIPE, ((t_token *)tokens->content)->type);
	TEST_ASSERT_EQUAL(NULL, ((t_token *)tokens->content)->value);
	TEST_ASSERT_EQUAL(NULL, tokens->next);
	clear_list(tokens, del_token_node);
}

void test_handle_skip(void) {
	char *prompt = "";
	t_lex_state next_state;
	t_node *tokens = NULL;
	t_val_info vi =
		(t_val_info){.start = 0, .len = 0, .prompt = prompt, .active = 0};
	size_t idx = 0;

	next_state = handle_skip_state(idx, &vi);
	TEST_ASSERT_EQUAL(STATE_COMPLETE, next_state);
	TEST_ASSERT_EQUAL(NULL, tokens);
}

void test_handle_squote_complete(void) {
	char *prompt = "'abc'";
	t_lex_state next_state;
	t_node *tokens = NULL;
	t_val_info vi =
		(t_val_info){.start = 0, .len = 0, .prompt = prompt, .active = 0};
	size_t idx = 0;

	while (++idx < 5)
		next_state = handle_squote_state(idx, &tokens, &vi);
	TEST_ASSERT_EQUAL(STATE_SKIP, next_state);
	TEST_ASSERT_NOT_EQUAL(NULL, tokens);
	TEST_ASSERT_EQUAL(TOKEN_SQUOTE, ((t_token *)tokens->content)->type);
	TEST_ASSERT_EQUAL_STRING("abc", ((t_token *)tokens->content)->value);
	TEST_ASSERT_EQUAL(NULL, tokens->next);
	clear_list(tokens, del_token_node);
}

void test_handle_squote_incomplete(void) {
	char *prompt = "'abc";
	t_lex_state next_state;
	t_node *tokens = NULL;
	t_val_info vi =
		(t_val_info){.start = 0, .len = 0, .prompt = prompt, .active = 0};
	size_t idx = 0;

	while (++idx < 5)
		next_state = handle_squote_state(idx, &tokens, &vi);
	TEST_ASSERT_EQUAL(STATE_SQINCOMP, next_state);
	TEST_ASSERT_NOT_EQUAL(NULL, tokens);
	TEST_ASSERT_EQUAL(TOKEN_SQINCOMP, ((t_token *)tokens->content)->type);
	TEST_ASSERT_EQUAL_STRING("abc", ((t_token *)tokens->content)->value);
	TEST_ASSERT_EQUAL(NULL, tokens->next);
	clear_list(tokens, del_token_node);
}

void test_handle_word(void) {
	char *prompt = "abc";
	t_lex_state next_state;
	t_node *tokens = NULL;
	t_val_info vi =
		(t_val_info){.start = 0, .len = 0, .prompt = prompt, .active = 0};
	size_t idx = 0;

	init_word_value(idx, &vi, STATE_WORD);
	while (++idx < 4)
		next_state = handle_word_state(idx, &tokens, &vi);
	TEST_ASSERT_EQUAL(STATE_COMPLETE, next_state);
	TEST_ASSERT_NOT_EQUAL(NULL, tokens);
	TEST_ASSERT_EQUAL(TOKEN_WORD, ((t_token *)tokens->content)->type);
	TEST_ASSERT_EQUAL_STRING("abc", ((t_token *)tokens->content)->value);
	TEST_ASSERT_EQUAL(NULL, tokens->next);
	clear_list(tokens, del_token_node);
}

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
	RUN_TEST(test_new_token);
	RUN_TEST(test_new_token_with_value);
	RUN_TEST(test_init_word_value);
	RUN_TEST(test_handle_append);
	RUN_TEST(test_handle_dquote_complete);
	RUN_TEST(test_handle_dquote_incomplete);
	RUN_TEST(test_handle_heredoc);
	RUN_TEST(test_handle_input);
	RUN_TEST(test_handle_output);
	RUN_TEST(test_handle_pipe);
	RUN_TEST(test_handle_skip);
	RUN_TEST(test_handle_squote_complete);
	RUN_TEST(test_handle_squote_incomplete);
	RUN_TEST(test_handle_word);
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
