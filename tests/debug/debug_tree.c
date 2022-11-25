// https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/

#include "debug.h"
#include <malloc.h>
#include <stdio.h>
#define COUNT 10

void debug_tree_recursive(t_tree *root, int space) {
	if (root == NULL)
		return;

	space += COUNT;
	debug_tree_recursive(root->right, space);
	printf("\n");
	for (int i = COUNT; i < space; i++)
		printf(" ");
	if (root->type == TREE_TYPE_CMD)
		printf("(cmd%d)\n", ((t_cmd *)root->content)->number);
	else if (root->type == TREE_TYPE_PIPE)
		printf("(|)\n");
	debug_tree_recursive(root->left, space);
}

void debug_tree(t_tree *root) { debug_tree_recursive(root, 0); }

void debug_etree(t_etree *root) {
	const char *op[] = {"OP_AND", "OP_NONE", "OP_OR", "OP_PIPE", NULL};
	t_etree *node;
	t_queue groups;

	groups.front = NULL;
	groups.rear = NULL;
	printf("===== debug etree =====\n");
	node = root;
	while (node) {
		if (node->group) {
			enqueue(&groups, node->group);
			printf("[group]");
		} else if (node->cmd.word_tokens != NULL)
			printf("%s", ((t_token *)node->cmd.word_tokens->content)->value);
		else
			printf("[cmd]");
		node = node->next;
		if (node)
			printf(" %s ", op[node->operator]);
	}
	printf("\n");
	node = dequeue(&groups);
	while (node) {
		debug_etree(node);
		node = dequeue(&groups);
	}
}
