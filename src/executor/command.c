/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:48:35 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/22 19:11:17 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "executor.h"
#include "expander.h"
#include "minishell.h"

int	execute_command(t_exec *exec, t_cmd *cmd, t_vlst *env)
{
	cmd->status = command_expansion(cmd, env);
	if (cmd->status != OK)
		return (cmd->status);
	cmd->status = command_redirect(cmd);
	if (cmd->status != OK)
		return (cmd->status);
	if (cmd->argc == 0)
		return (0);
	cmd->status = command_search(cmd, env);
	if (cmd->status != OK && cmd->status != ERR_CMD_NOT_FOUND)
		return (cmd->status);
	if (cmd->isbuiltin && !cmd->ispipeline)
		cmd->status = execute_builtin(cmd, env);
	else
		subshell(exec, cmd, env);
	return (0);
}

void	subshell(t_exec *exec, t_cmd *cmd, t_vlst *env)
{
	int	status;

	handle_signal(SIGINT, command_signal_handler);
	handle_signal(SIGQUIT, command_signal_handler);
	cmd->pid = fork();
	if (cmd->pid < 0)
		cmd->status = error_message2(1, "fork failed", strerror(errno));
	else if (cmd->pid == 0)
	{
		if (cmd->isbuiltin)
			status = execute_builtin(cmd, env);
		else
			status = execute_program(cmd, env);
		destroy_exec(exec);
		builtin_exit(status, NULL);
	}
}

int	execute_builtin(t_cmd *cmd, t_vlst *env)
{
	if (ft_streq(cmd->argv[0], "echo"))
		cmd->status = builtin_echo(cmd->output, cmd->argv);
	else if (ft_streq(cmd->argv[0], "cd"))
		cmd->status = builtin_cd(cmd->argc, cmd->argv, env);
	else if (ft_streq(cmd->argv[0], "pwd"))
		cmd->status = builtin_pwd(cmd->output);
	else if (ft_streq(cmd->argv[0], "export"))
		cmd->status = builtin_export(cmd->argc, cmd->argv, env);
	else if (ft_streq(cmd->argv[0], "unset"))
		cmd->status = builtin_unset(cmd->argc, cmd->argv, env);
	else if (ft_streq(cmd->argv[0], "env"))
		cmd->status = builtin_env(cmd->output, env);
	else if (ft_streq(cmd->argv[0], "exit"))
		builtin_exit(env->last_status, cmd);
	return (cmd->status);
}

int	execute_program(t_cmd *cmd, t_vlst *env)
{
	dup2(cmd->input, STDIN);
	dup2(cmd->output, STDOUT);
	close_safe(cmd->input);
	close_safe(cmd->output);
	if (!cmd->pathname)
		return (command_not_found_handle(cmd->argv[0]));
	cmd->envp = list_to_envp(env, NULL, 0);
	execve(cmd->pathname, cmd->argv, cmd->envp);
	return (error_message2(1, cmd->argv[0], strerror(errno)));
}
