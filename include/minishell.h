/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:27:27 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/07 10:59:26 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stddef.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <unistd.h>
# include <errno.h>

# include "libft.h"
# include "structs.h"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define PROMPT_STRING "minishell "
# define HEREDOC_STRING "here_doc> "
# define ENDSINPIPE_STRING "> "

// Error definitions
# define OK 0
# define ERR_ALLOC 1
# define ERR_NOT_FOUND 2
# define ERR_LEXER 3

// List-related functions
int			add_node(t_node **lst, void *content);
int			change_node_content(t_node *lst, void *old_content,
				void *new_content, t_node_funcs *funcs);
t_node		*find_node_by_content(t_node *lst, void *content,
				int (*cmp_content)(void *, void *));
t_node		*remove_node(t_node *current, void (*del_node)(void *));
int			remove_node_by_content(t_node **lst, void *content,
				void (*del_node)(void *), int (*cmp_content)(void *, void *));

// Tree

t_tree		*new_tree_node(t_tree_type type);
void		destroy_execution_tree(t_tree *root);
void		*destroy_tree(t_tree *root, void (*destroy_content)(t_tree *));

// Init

t_cmd		*new_command(int number);
t_pipeline	*new_pipeline(t_operator operator);
void		init_minishell(t_minishell *minishell, char **envp);

// Cleanup functions
void		*clear_envp(char **envp);
void		clear_list(t_node *lst, void (*del_node)(void *));
void		del_token_node(void *content);
void		del_var_node(void *content);
void		destroy_command(t_cmd *command);
void		destroy_redirect(t_redirect *redirect);
void		destroy_pipeline(t_pipeline	*pipeline);
void		destroy_minishell(t_minishell *minishell);
void		free_minishell(t_minishell *minishell);
void		free_string_list(char **str);

// Prompt

int			command_ends_with(char *cmd, char c);
int			command_is_equal(char *cmd, char *str);
int			ends_in_pipe(void);
char		*get_content_fd(int fd);
int			here_doc(char	*limiter);
void		miniprompt(t_minishell *minishell);

// Commands

int			lexer(char *prompt, t_node **tokens, t_lex_state start_state);
void		executor(t_minishell *minishell);
void		parser(t_minishell *minishell);

// Remove

void		panic_error(char *msg);

// Signal

void		handle_signal(int sig, void *handler);
void		prompt_signal_handler(int sig);
void		command_signal_handler(int sig);

// Interactive

void		shell(t_minishell *minishell, char *line);
void		shell_loop(t_minishell *minishell);

#endif
