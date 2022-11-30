// https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/

#include "debug.h"

void debug_tree_recursive(t_tree *root, int space) {
	const int count = 10;
	t_cmd *cmd;
	t_token *token;
	if (!root)
		return;
	space += count;
	debug_tree_recursive(root->right, space);
	printf("\n");
	for (int i = count; i < space; i++)
		printf(" ");
	if (root->type == TREE_TYPE_CMD) {
		cmd = root->content;
		if (cmd->word_tokens) {
			token = (t_token *)cmd->word_tokens->content;
			if (cmd->word_tokens->next)
				printf("(%s %s)\n", token->value,
					   ((t_token *)cmd->word_tokens->next->content)->value);
			else
				printf("(%s)\n", token->value);
		} else
			printf("(cmd)\n");
	} else if (root->type == TREE_TYPE_PIPE)
		printf("(|)\n");
	else if (root->type == TREE_TYPE_OR)
		printf("(||)\n");
	else if (root->type == TREE_TYPE_AND)
		printf("(&&)\n");
	else if (root->type == TREE_TYPE_IGNORE)
		printf("(IG)\n");
	else if (root->type == TREE_TYPE_GROUP)
		printf("(GR %5p)\n", root->content);
	debug_tree_recursive(root->left, space);
}

void debug_tree(t_tree *root) { debug_tree_recursive(root, 0); }
