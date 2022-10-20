/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:27:27 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/20 18:43:38 by eandre-f         ###   ########.fr       */
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

// List-related functions
int		add_node(t_node **lst, void *content);
int		change_node_content(t_node *lst, void *old_content,
			void *new_content, t_node_funcs *funcs);
t_node	*find_node_by_content(t_node *lst, void *content,
			int (*cmp_content)(void *, void *));
t_node	*remove_node(t_node *current, void (*del_node)(void *));
int		remove_node_by_content(t_node **lst, void *content,
			void (*del_node)(void *), int (*cmp_content)(void *, void *));

// Environment variable-related functions
int		cmp_vars_by_name(void *a, void *b);
void	envp_to_list(char **envp, t_vlst *vars);
char	**list_to_envp(t_vlst *vars, int quote);
t_var	*new_var_node_from_name_val(char *name, char *val);
t_var	*new_var_node_from_str(char *str);
int		split_name_val(char *str, char *equal_pos, t_var *content);
int		update_var(t_vlst *vars, t_var *content);

// Cleanup functions
void	*clear_envp(char **envp);
void	clear_list(t_node *lst, void (*del_node)(void *));
void	del_var_node(void *content);
void	free_minishell(t_minishell *minishell);
void	free_string_list(char **str);

// Prompt

int		command_ends_with(char *cmd, char c);
int		command_is_equal(char *cmd, char *str);
int		ends_in_pipe(void);
char	*get_content_fd(int fd);
int		here_doc(char	*limiter);
void	miniprompt(t_minishell *minishell);

// Builtins

void	builtins(t_minishell *minishell, t_command *command);
void	builtin_cd(char *path, t_vlst *vars);
void	builtin_echo(char *option, char *string);
void	builtin_env(t_vlst *vars);
void	builtin_exit(void);
void	builtin_export(int argc, char *argv[], t_vlst *vars);
void	builtin_pwd(void);
void	builtin_unset(int argc, char *argv[], t_vlst *vars);
char	*get_pwd(void);

// Commands

t_node	*lexer(char *prompt);
void	parser(t_minishell *minishell);
void	executor(t_minishell *minishell);

#endif
