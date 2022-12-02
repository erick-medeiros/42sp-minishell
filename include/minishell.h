/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:27:27 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/02 12:29:53 by eandre-f         ###   ########.fr       */
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
# define PROMPT_EXTRA_OP "continue pipe> "
# define HEREDOC_STRING "here_doc> "
# define ENDSINPIPE_STRING "> "

// Error definitions
# define OK 0
# define ERR_ALLOC 1
# define ERR_NOT_FOUND 2
# define ERR_LEXER 3
# define ERR_BAD_SYNTAX 4
# define ERR_INCOMP_OP 5
# define ERR_INCOMP_DQ 6
# define ERR_INCOMP_SQ 7
# define ERR_INCOMP_BRC 8
# define ERR_INCOMP_BRC_DQ 9
# define ERR_INCOMP_BRC_SQ 10
# define ERR_BAD_TOKEN 11
# define ERR_FILE_OPEN 12
# define ERR_BAD_SUBST 13
# define ERR_IS_DIR 14
# define ERR_TOO_LONG 15
# define ERR_OTHER 16
# define ERR_ACCESS 17
# define ERR_NO_PATH 18
# define ERR_CMD_NOT_FOUND 19

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
t_bool		is_valid_name(char *name);

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

t_cmd		*new_command(void);
void		init_minishell(t_ms *ms, char **envp);
void		init_system_vars(t_vlst *env);

// Cleanup functions

void		*clear_envp(char **envp);
void		clear_list(t_node *lst, void (*del_node)(void *));
void		del_token_node(void *content);
void		del_var_node(void *content);
void		del_heredoc_node(void *content);
void		destroy_command(t_cmd *command);
void		destroy_minishell(t_ms *ms);
void		free_minishell(t_ms *ms);
void		free_string_list(char **str);
void		free_token(void *content);
void		destroy_queue(t_queue *queue, void (*del_node)(void *));
void		close_safe(int fd);

// Prompt

int			ft_streq(char *cmd, char *str);
int			here_doc(char	*limiter);
void		miniprompt(t_ms *ms);
t_lex_state	get_lex_state(int result);
void		handle_parse_result(int result, char **line,
				char **history, t_ms *ms);

// Commands

void		process_line(char **line, t_ms *ms);
int			lexer(char **line, t_node **tokens, t_lex_state st);
void		executor(t_tree *root, t_vlst *env);
int			parser(t_ms *ms, int cmd_num);
int			get_command(t_tree **cmd_node, t_ms *ms, int num);

// Error

int			error_message(int status, char *fields[]);
int			error_message1(int status, char *field1);
int			error_message2(int status, char *field1, char *field2);
int			error_message3(int status, char *field1, char *field2,
				char *field3);
// Signal

void		handle_signal(int sig, void *handler);
void		prompt_signal_handler(int sig);
void		command_signal_handler(int sig);

// Interactive

void		shell(t_ms *ms, char **line);
void		shell_loop(t_ms *ms);

// Quicksort string list

void		quicksort(char **envp, size_t start_idx, size_t end_idx);

#endif
