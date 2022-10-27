/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:27:27 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/27 12:31:35 by eandre-f         ###   ########.fr       */
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

# define PROMPT_STRING "minishell> "
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

// Environment variable-related functions
int			cmp_vars_by_name(void *a, void *b);
void		envp_to_list(char **envp, t_vlst *vars);
char		**list_to_envp(t_vlst *vars, int quote);
t_var		*new_var_node_from_name_val(char *name, char *val);
t_var		*new_var_node_from_str(char *str);
int			split_name_val(char *str, char *equal_pos, t_var *content);
int			update_var(t_vlst *vars, t_var *content);

// Cleanup functions
void		*clear_envp(char **envp);
void		clear_list(t_node *lst, void (*del_node)(void *));
void		del_token_node(void *content);
void		del_var_node(void *content);
void		free_minishell(t_minishell *minishell);
void		destroy_minishell(t_minishell *minishell);
void		free_string_list(char **str);

// Prompt

int			command_ends_with(char *cmd, char c);
int			command_is_equal(char *cmd, char *str);
int			ends_in_pipe(void);
char		*get_content_fd(int fd);
int			here_doc(char	*limiter);
void		miniprompt(t_minishell *minishell);

// Builtins

void		builtins(t_minishell *minishell, t_cmd *command);
void		builtin_cd(char *path, t_vlst *vars);
void		builtin_echo(char *option, char *string);
void		builtin_env(t_vlst *vars);
void		builtin_exit(void);
void		builtin_export(int argc, char *argv[], t_vlst *vars);
void		builtin_pwd(void);
void		builtin_unset(int argc, char *argv[], t_vlst *vars);
char		*get_pwd(void);

// Commands

void		executor(t_minishell *minishell);
void		parser(t_minishell *minishell);

// Lexer

t_lex_state	handle_append_state(size_t idx, t_node **tokens, t_val_info *vi);
t_lex_state	handle_dquote_state(size_t idx, t_node **tokens, t_val_info *vi);
t_lex_state	handle_heredoc_state(size_t idx, t_node **tokens, t_val_info *vi);
t_lex_state	handle_input_state(size_t idx, t_node **tokens, t_val_info *vi);
t_lex_state	handle_output_state(size_t idx, t_node **tokens, t_val_info *vi);
t_lex_state	handle_pipe_state(size_t idx, t_node **tokens, t_val_info *vi);
t_lex_state	handle_skip_state(size_t idx, t_val_info *vi);
t_lex_state	handle_squote_state(size_t idx, t_node **tokens, t_val_info *vi);
t_lex_state	handle_word_state(size_t idx, t_node **tokens, t_val_info *vi);
int			lexer(char *prompt, t_node **tokens, t_lex_state start_state);
int			new_token(t_node **tokens, t_tok_type tok_type);
int			new_token_with_val(t_node **tokens, t_tok_type tok_type,
				t_val_info *vi);
t_lex_state	init_word_value(size_t idx, t_val_info *vi, t_lex_state st);
t_lex_state	init_quote_value(size_t idx, t_val_info *vi, t_lex_state st);

// Error

void		panic_error(char *msg);

// Minishell

void		init_minishell(t_minishell *minishell, char **envp);

// Error

void		panic_error(char *msg);

// Minishell

void		init_minishell(t_minishell *minishell, char **envp);

// Remove

char		**get_paths(char *envp[]);

#endif
