#include "debug.h"
#include "minishell.h"
#include "structs.h"

void debug_token(t_node *token_list) {
  t_node *node;
  t_token *token;
  char *types[] = {"TOKEN_APPEND",   "TOKEN_BRCINCOMP",
                   "TOKEN_DQUOTE",   "TOKEN_DQBRACE",
                   "TOKEN_DQINCOMP", "TOKEN_HEREDOC",
                   "TOKEN_INPUT",    "TOKEN_OUTPUT",
                   "TOKEN_PIPE",     "TOKEN_SQUOTE",
                   "TOKEN_SQBRACE",  "TOKEN_SQINCOMP",
                   "TOKEN_WORD",     NULL};
  node = token_list;
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
  if (command->argv)
    printf("argv%d) %s\n", i, command->argv[i]);
  printf("status) %d\n", command->status);
  printf("input) %d\n", command->input);
  printf("output) %d\n", command->output);
  printf("piping read) %d\n", command->piping[READ_PIPE]);
  printf("piping write) %d\n", command->piping[WRITE_PIPE]);
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