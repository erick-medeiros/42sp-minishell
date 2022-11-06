#include "lexer.h"
#include "minishell.h"
#include "structs.h"

static void print_token_list(t_node *tokens);

void test_postfix_to_postfix(void) {
	t_node *tokens = NULL;
	char *prompt = " abcde ";
	t_val_info vi =
		(t_val_info){.start = 1, .len = 5, .prompt = prompt, .active = 1};

	new_token_with_val(&tokens, TOKEN_WORD, &vi);
	new_token(&tokens, TOKEN_PIPE);
	new_token_with_val(&tokens, TOKEN_WORD, &vi);
	print_token_list(tokens);
	postfix_to_postfix(&tokens);
	print_token_list(tokens);
}

static void print_token_list(t_node *tokens)
{
	char *type_name[] = {
		"TOKEN_APPEND",
	"TOKEN_DQUOTE",
	"TOKEN_DQINCOMP",
	"TOKEN_HEREDOC",
	"TOKEN_INPUT",
	"TOKEN_OUTPUT",
	"TOKEN_PIPE",
	"TOKEN_SQUOTE",
	"TOKEN_SQINCOMP",
	"TOKEN_WORD"
	};
	printf("Token list start\n");
	while (tokens != NULL)
	{
		printf("Token: type = %s, value = %s\n",
				type_name[((t_token *)tokens->content)->type],
				((t_token *)tokens->content)->value);
		tokens = tokens->next;
	}
	printf("Token list end\n");
}

int main(void)
{
	test_postfix_to_postfix();
}
