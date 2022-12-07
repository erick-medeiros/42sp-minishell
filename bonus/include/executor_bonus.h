/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:14:10 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/07 19:59:43 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_BONUS_H
# define EXECUTOR_BONUS_H

# include "minishell_bonus.h"

// Executor

void	tree_executor(t_exec *exec, t_tree *node, int in, int out);
void	tree_pipe_executor(t_exec *exec, t_tree *node, int in, int out);
void	tree_list_executor(t_exec *exec, t_tree *node, int in, int out);
void	tree_group_executor(t_exec *exec, t_tree *node, int in, int out);
void	destroy_exec(t_exec *exec);

// Expander

int		command_expansion_to_words(t_cmd *cmd, t_vlst *env);
int		command_expansion_to_redirects(t_cmd *cmd, t_vlst *env);

// Converter

t_bool	expandable_token(t_tok_type type);
int		convert_tokens_to_argv(t_cmd *cmd);
t_node	*append_list(t_node *node, t_node *append);

// Redirect

int		command_redirect(t_cmd *cmd);
int		open_redir(char *pathname, int token_type);
void	define_stds(t_cmd *cmd);
void	close_command_redirects(t_cmd *cmd);

// Search

int		command_search(t_cmd *cmd, t_vlst *env);

// Pipeline

void	execution_sync(t_exec *exec, int in, int out);
void	close_tree_redirects(t_tree *root, int in, int out);

// Command

int		execute_command(t_exec *exec, t_cmd *cmd);
void	execute_in_shell(t_exec *exec, t_cmd *cmd);
void	execute_in_subshell(t_exec *exec, t_cmd *cmd);
int		execute_builtin(t_exec *exec, t_cmd *cmd);
int		execute_program(t_exec *exec, t_cmd *cmd);

// Error handling
void	print_signal_error(int exit_status, int coredump);
int		command_not_found_handle(char *name);

#endif
