// https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/

#include "debug.h"
#include <malloc.h>
#include <stdio.h>
#define COUNT 10

void debug_tree_recursive(t_tree *root, int space) {
	t_cmd *cmd;
	t_token *token;
	if (root == NULL)
		return;

	space += COUNT;
	debug_tree_recursive(root->right, space);
	printf("\n");
	for (int i = COUNT; i < space; i++)
		printf(" ");
	if (root->type == TREE_TYPE_CMD) {
		cmd = root->content;
		token = (t_token *)cmd->word_tokens->content;
		printf("(%s)\n", token->value);
	} else if (root->type == TREE_TYPE_PIPE)
		printf("(|)\n");
	else if (root->type == TREE_TYPE_OR)
		printf("(||)\n");
	else if (root->type == TREE_TYPE_AND)
		printf("(&&)\n");
	debug_tree_recursive(root->left, space);
}

void debug_tree(t_tree *root) { debug_tree_recursive(root, 0); }
