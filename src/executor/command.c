/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:48:35 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/30 12:40:18 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "executor.h"
#include "expander.h"
#include "minishell.h"

int	execute_command(t_exec *exec, t_cmd *cmd)
{
	cmd->status = command_expansion(cmd, exec->env);
	if (cmd->status != OK)
		return (cmd->status);
	cmd->status = command_redirect(cmd);
	if (cmd->status != OK)
		return (cmd->status);
	if (cmd->argc == 0)
		return (0);
	cmd->status = command_search(cmd, exec->env);
	if (cmd->status != OK && cmd->status != ERR_CMD_NOT_FOUND)
		return (cmd->status);
	if (cmd->isbuiltin && !cmd->ispipeline)
		cmd->status = execute_builtin(exec, cmd);
	else
		execute_in_subshell(exec, cmd);
	return (0);
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
		dup2(cmd->input, STDIN);
		dup2(cmd->output, STDOUT);
		close_pipeline(exec->commands);
		update_command_input(cmd, STDIN);
		update_command_output(cmd, STDOUT);
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
	cmd->envp = list_to_envp(exec->env, NULL, 0);
	execve(cmd->pathname, cmd->argv, cmd->envp);
	return (error_message2(1, cmd->argv[0], strerror(errno)));
}
