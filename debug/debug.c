#include "debug.h"
#include "structs.h"

void debug_token(t_minishell *minishell) {
  t_node *node;
  t_token *token;
  char *types[10];

  types[0] = "TOKEN_APPEND";
  types[1] = "TOKEN_DQUOTE";
  types[2] = "TOKEN_DQINCOMP";
  types[3] = "TOKEN_HEREDOC";
  types[4] = "TOKEN_INPUT";
  types[5] = "TOKEN_OUTPUT";
  types[6] = "TOKEN_PIPE";
  types[7] = "TOKEN_SQUOTE";
  types[8] = "TOKEN_SQINCOMP";
  types[9] = "TOKEN_WORD";
  node = minishell->token_list;
  printf("token list:\n");
  while (node) {
    token = node->content;
    printf("value (%s) type (%s)\n", token->value, types[token->type]);
    node = node->next;
  }
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
  printf("argv%d) %s\n", i, command->argv[i]);
  printf("status) %d\n", command->status);
  printf("input) %d\n", command->input);
  printf("output) %d\n", command->output);
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