// https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/

#include "executor.h"
#include "minishell.h"
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
