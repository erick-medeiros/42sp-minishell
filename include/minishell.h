/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:27:27 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/12 23:55:42 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
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
# define PROMPT_EXTRA_SQ "continue single quote> "
# define PROMPT_EXTRA_DQ "continue double quote> "
# define PROMPT_EXTRA_BRC "continue brace> "
# define PROMPT_EXTRA_PIPE "continue pipe> "
# define HEREDOC_STRING "here_doc> "
# define ENDSINPIPE_STRING "> "

// Error definitions
# define OK 0
# define ERR_ALLOC 1
# define ERR_NOT_FOUND 2
# define ERR_LEXER 3
# define ERR_BAD_SYNTAX 4
# define ERR_INCOMP_PIPE 5
# define ERR_INCOMP_DQ 6
# define ERR_INCOMP_SQ 7
# define ERR_INCOMP_BRC 8
# define ERR_INCOMP_BRC_DQ 9
# define ERR_INCOMP_BRC_SQ 10
# define ERR_BAD_TOKEN 11
# define ERR_FILE_OPEN 12

// List-related functions

int			add_node(t_node **lst, void *content);
int			change_node_content(t_node *lst, void *old_content,
				void *new_content, t_node_funcs *funcs);
t_node		*find_node_by_content(t_node *lst, void *content,
				int (*cmp_content)(void *, void *));
t_node		*remove_node(t_node *current, void (*del_node)(void *));
int			remove_node_by_content(t_node **lst, void *content,
				void (*del_node)(void *), int (*cmp_content)(void *, void *));
int			push_node(t_node **lst, void *content);
void		*pop_node(t_node **src);

// Variable-related functions
int			change_or_create_var(t_vlst *vars, char *name, char *val);
void		print_sorted_vars(t_vlst *vars, char *prefix);
int			split_name_val(char *str, char **name, char **val);

// Queue

t_queue		*new_queue(void);
int			enqueue(t_queue *queue, void *content);
void		*dequeue(t_queue *queue);

// Tree

t_tree		*new_tree_node(t_tree_type type);
void		destroy_execution_tree(void *root);
void		*destroy_tree(t_tree *root, void (*destroy_content)(void *));
void		del_cmd_tree_node(void *tree);

// Init

t_cmd		*new_command(int number);
void		init_minishell(t_minishell *minishell, char **envp);
int			initialize_command(t_cmd *command);

// Cleanup functions

void		*clear_envp(char **envp);
void		clear_list(t_node *lst, void (*del_node)(void *));
void		del_token_node(void *content);
void		del_var_node(void *content);
void		del_heredoc_node(void *content);
void		destroy_command(t_cmd *command);
void		destroy_redirect(t_redirect *redirect);
void		destroy_minishell(t_minishell *minishell);
void		free_minishell(t_minishell *minishell);
void		free_string_list(char **str);
void		destroy_queue(t_queue *queue, void (*del_node)(void *));

// Prompt

int			command_ends_with(char *cmd, char c);
int			command_is_equal(char *cmd, char *str);
char		*get_content_fd(int fd);
int			here_doc(char	*limiter);
void		miniprompt(t_minishell *minishell);
t_lex_state	get_lex_state(int result);
void		handle_parse_result(int result, char **line,
				char **history, t_minishell *ms);

// Commands

void		process_line(char **line, t_minishell *minishell);
int			lexer(char **line, t_node **tokens, t_lex_state st);
void		executor(t_minishell *minishell);
int			parser(t_minishell *ms, int cmd_num);
int			get_command(t_tree **cmd_node, t_minishell *ms, int num);

// Remove

void		panic_error(char *msg);

// Signal

void		handle_signal(int sig, void *handler);
void		prompt_signal_handler(int sig);
void		command_signal_handler(int sig);

// Interactive

void		shell(t_minishell *minishell, char **line);
void		shell_loop(t_minishell *minishell);

// Expander

int			expander(char *src, char **dst, t_minishell *ms);

// Quicksort string list

void		quicksort(char **envp, size_t start_idx, size_t end_idx);

#endif
