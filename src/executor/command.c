/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:48:35 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/22 15:18:17 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "expander.h"
#include "builtins.h"

int	execute_command(t_exec *exec, t_etree *node, t_vlst *env)
{
	node->cmd->input = node->input;
	node->cmd->output = node->output;
	node->cmd->status = command_expansion(node->cmd, env);
	if (node->cmd->status != OK)
		return (node->cmd->status);
	node->cmd->status = command_redirect(node->cmd);
	if (node->cmd->status != OK)
		return (node->cmd->status);
	if (node->cmd->argc == 0)
		return (0);
	node->cmd->status = command_search(node->cmd, env);
	if (node->cmd->status != OK && node->cmd->status != ERR_CMD_NOT_FOUND)
		return (node->cmd->status);
	if (node->cmd->isbuiltin && !node->ispipeline)
		node->status = execute_builtin(node->cmd, env);
	else
		subshell(exec, node, env);
	return (0);
}

void	subshell(t_exec *exec, t_etree *node, t_vlst *env)
{
	int	status;

	handle_signal(SIGINT, command_signal_handler);
	handle_signal(SIGQUIT, command_signal_handler);
	node->pid = fork();
	if (node->pid < 0)
		node->status = error_message2(1, "fork failed", strerror(errno));
	else if (node->pid == 0)
	{
		if (node->cmd->isbuiltin)
			status = execute_builtin(node->cmd, env);
		else
			status = execute_program(node, env);
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

int	execute_program(t_etree *node, t_vlst *env)
{
	dup2(node->input, STDIN);
	dup2(node->output, STDOUT);
	close_safe(node->input);
	close_safe(node->output);
	if (!node->cmd->pathname)
		return (command_not_found_handle(node->cmd->argv[0]));
	node->cmd->envp = list_to_envp(env, NULL, 0);
	execve(node->cmd->pathname, node->cmd->argv, node->cmd->envp);
	return (error_message2(1, node->cmd->argv[0], strerror(errno)));
}

int	command_exit_status(t_cmd *cmd, int *coredump)
{
	if (cmd->pid > 0)
	{
		waitpid(cmd->pid, &cmd->status, 0);
		if (WIFEXITED(cmd->status))
			cmd->status = WEXITSTATUS(cmd->status);
		else if (WIFSIGNALED(cmd->status))
		{
			if (coredump)
				*coredump = WCOREDUMP(cmd->status);
			cmd->status = 128 + WTERMSIG(cmd->status);
		}
	}
	return (cmd->status);
}
