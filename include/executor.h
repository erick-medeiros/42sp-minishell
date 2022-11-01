/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:14:10 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/01 19:26:58 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"
# include <stddef.h>

// Executor

void	pipeline_executor(t_minishell *minishell, t_pipeline *pipeline);
void	run_command(t_minishell *minishell, t_pipeline *pipeline,
			t_cmd *command);
void	command_exit_status(t_cmd *command);
void	builtins(t_minishell *minishell, t_cmd *command);

// Pipeline

void	open_pipes(t_pipeline *pipeline);
void	connect_pipes(t_pipeline *pipeline, t_cmd *command);
void	close_pipes(t_pipeline *pipeline);
void	connect_pipeline(t_cmd *cmd, t_tree *grandparent, t_tree *parent,
			t_tree *node);
void	close_pipeline(t_tree *root);

// Subshell

void	subshell(t_minishell *minishell, t_pipeline *pipeline, t_cmd *command);
void	subshell_redirect(t_minishell *minishell, t_cmd *command);
void	exit_subshell(t_minishell *minishell, int status);
void	process_exit_status(t_cmd *command);

// Execute

void	execute_builtin(t_minishell *minishell, t_cmd *command);
void	execute_program(t_minishell *minishell, t_cmd *command);

// Tree

t_tree	*convert_list_to_tree(t_pipeline *pipeline);
void	tree_executor(t_minishell *minishell, t_pipeline *pipeline);

#endif