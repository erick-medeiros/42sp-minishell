/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:48:35 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/08 19:44:32 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_bonus.h"
#include "executor_bonus.h"
#include "expander_bonus.h"
#include "minishell_bonus.h"

int	execute_command(t_exec *exec, t_cmd *cmd)
{
	cmd->status = command_expansion_to_words(cmd, exec->env);
	if (cmd->status != OK)
		return (cmd->status);
	cmd->status = command_search(cmd, exec->env);
	if (cmd->status != OK && cmd->status != ERR_CMD_NOT_FOUND)
		return (cmd->status);
	if (cmd->output == STDOUT)
		handle_signal(SIGPIPE, SIG_DFL);
	else
		handle_signal(SIGPIPE, SIG_IGN);
	if (cmd->isbuiltin && !cmd->subshell)
		execute_in_shell(exec, cmd);
	else
		execute_in_subshell(exec, cmd);
	return (cmd->status);
}

void	execute_in_shell(t_exec *exec, t_cmd *cmd)
{
	cmd->status = command_redirect(cmd, exec->env);
	if (cmd->status != OK)
		return ;
	if (cmd->argc > 0)
		cmd->status = execute_builtin(exec, cmd);
}

void	execute_in_subshell(t_exec *exec, t_cmd *cmd)
{
	handle_signal(SIGINT, command_signal_handler);
	handle_signal(SIGQUIT, command_signal_handler);
	cmd->pid = fork();
	if (cmd->pid < 0)
		cmd->status = error_message2(1, "fork failed", strerror(errno));
	else if (cmd->pid == 0)
	{
		cmd->status = command_redirect(cmd, exec->env);
		if (cmd->status != OK)
			builtin_exit(exec, cmd->status);
		if (cmd->argc == 0)
			builtin_exit(exec, cmd->status);
		dup2(cmd->input, STDIN);
		dup2(cmd->output, STDOUT);
		close_safe(cmd->input);
		close_safe(cmd->output);
		cmd->input = STDIN;
		cmd->output = STDOUT;
		if (cmd->isbuiltin)
			exec->env->last_status = execute_builtin(exec, cmd);
		else
			exec->env->last_status = execute_program(exec, cmd);
		builtin_exit(exec, exec->env->last_status);
	}
}

int	execute_builtin(t_exec *exec, t_cmd *cmd)
{
	if (ft_streq(cmd->argv[0], "echo"))
		cmd->status = builtin_echo(cmd->output, cmd->argv);
	else if (ft_streq(cmd->argv[0], "cd"))
		cmd->status = builtin_cd(cmd->argc, cmd->argv, exec->env);
	else if (ft_streq(cmd->argv[0], "pwd"))
		cmd->status = builtin_pwd(cmd->output);
	else if (ft_streq(cmd->argv[0], "export"))
		cmd->status = builtin_export(cmd->argc, cmd->argv, exec->env);
	else if (ft_streq(cmd->argv[0], "unset"))
		cmd->status = builtin_unset(cmd->argc, cmd->argv, exec->env);
	else if (ft_streq(cmd->argv[0], "env"))
		cmd->status = builtin_env(cmd->output, exec->env);
	else if (ft_streq(cmd->argv[0], "exit"))
	{
		if (cmd->argc > 1)
			builtin_exit_arg(exec, cmd->argc, cmd->argv);
		else
			builtin_exit(exec, exec->env->last_status);
	}
	else if (ft_streq(cmd->argv[0], "true"))
		cmd->status = 0;
	else if (ft_streq(cmd->argv[0], "false"))
		cmd->status = 1;
	return (cmd->status);
}

int	execute_program(t_exec *exec, t_cmd *cmd)
{
	if (!cmd->pathname)
		return (command_not_found_handle(cmd->argv[0]));
	close_tree_redirects(exec->commands, STDIN, STDOUT);
	cmd->envp = list_to_envp(exec->env, NULL, 0);
	execve(cmd->pathname, cmd->argv, cmd->envp);
	return (error_message2(1, cmd->argv[0], strerror(errno)));
}
