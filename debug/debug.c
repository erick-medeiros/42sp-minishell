#include "debug.h"
#include "structs.h"

void debug_token(t_minishell *minishell) {
  t_node *node;
  t_token *token;
  char *types[7];

  types[0] = "TOKEN_WORD";
  types[1] = "TOKEN_PIPE";
  types[2] = "TOKEN_INPUT";
  types[3] = "TOKEN_OUTPUT";
  types[4] = "TOKEN_APPEND";
  types[5] = "TOKEN_SQUOTE";
  types[6] = "TOKEN_DQUOTE";
  node = minishell->token_list;
  printf("token list:\n");
  while (node) {
    token = node->content;
    printf("value (%s) type (%s)\n", token->value, types[token->type]);
    node = node->next;
  }
}

// debug return heredoc and endsinpipe
void debug_content_fd(int fd, char *prompt, int debug) {
  char *content;

  content = get_content_fd(fd);
  if (debug == 1)
    printf("%s", content);
  else
    printf("exec: %s %s\n", prompt, content);
  free(content);
  close(fd);
}

void debug_command(t_command *command) {
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
  if (command->subshell)
    printf("subshell) yes\n");
  else
    printf("subshell) no\n");
  printf("----------\n\n");
}

void debug_pipeline_fds(t_pipeline *pipeline) {
  int i;

  printf("\n----------\n");
  printf("debug pipeline fds:\n\n");
  printf("number) %d\n", pipeline->command_count);
  i = 0;
  while (i < pipeline->command_count - 1) {
    close(pipeline->pipefds[i][0]);
    close(pipeline->pipefds[i][1]);
    printf("pipefds[%d][0] = %d\n", i, pipeline->pipefds[i][0]);
    printf("pipefds[%d][1] = %d\n", i, pipeline->pipefds[i][1]);
    ++i;
  }
  printf("----------\n\n");
}
