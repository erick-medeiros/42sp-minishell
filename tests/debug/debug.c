#include "debug.h"

void debug_token(t_node *token_list) {
	const char *types[] = {
		"TOKEN_AND",		  "TOKEN_APPEND",	"TOKEN_BRCINCOMP",
		"TOKEN_DQUOTE",		  "TOKEN_DQBRACE",	"TOKEN_DQINCOMP",
		"TOKEN_HEREDOC",	  "TOKEN_IGNORE",	"TOKEN_INPUT",
		"TOKEN_OR",			  "TOKEN_OUTPUT",	"TOKEN_OPARENTHESIS",
		"TOKEN_CPARENTHESIS", "TOKEN_PIPE",		"TOKEN_SQUOTE",
		"TOKEN_SQBRACE",	  "TOKEN_SQINCOMP", "TOKEN_SUBSHELL",
		"TOKEN_WORD",		  "TOKEN_NL",		NULL};
	t_node *node;
	t_token *token;

	node = token_list;
	printf("token list:\n");
	while (node) {
		token = node->content;
		printf("value (%s) type (%s)\n", token->value, types[token->type]);
		node = node->next;
	}
}

void debug_cmd_list(t_node *list) {
	t_node *nodetmp;

	nodetmp = list;
	while (nodetmp) {
		printf("cmdl[%d]", ((t_tree *)nodetmp->content)->type);
		nodetmp = nodetmp->next;
	}
	printf("\n");
}

void debug_command(t_cmd *command) {
	int i;

	printf("\n----------\n");
	printf("debug command:\n\n");
	printf("number) %d\n", command->number);
	printf("pid) %d\n", command->pid);
	printf("pathname) %s\n", command->pathname);
	printf("argc) %d\n", command->argc);
	i = -1;
	while (command->argv && command->argv[++i])
		printf("argv%d) %s\n", i, command->argv[i]);
	if (command->argv)
		printf("argv%d) %s\n", i, command->argv[i]);
	printf("status) %d\n", command->status);
	printf("input) %d\n", command->input);
	printf("output) %d\n", command->output);
	printf("word_tokens %p\n", command->word_tokens);
	printf("redirect %p\n", command->redirect);
	printf("envp %p\n", command->envp);
	if (command->isbuiltin)
		printf("isbuiltin) yes\n");
	else
		printf("isbuiltin) no\n");
	printf("----------\n\n");
}

void debug_queue_cmds(t_queue *cmds) {
	t_node *node;
	t_tree *tree;

	node = cmds->front;
	while (node) {
		tree = node->content;
		debug_tree(tree);
		printf("=============\n");
		node = node->next;
	}
}