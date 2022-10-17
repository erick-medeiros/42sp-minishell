/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:12:26 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/17 19:38:34 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "architecture.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

void	execute_commands(t_minishell *minishell, t_node *commands);
void	child_process(t_minishell *minishell, t_command *command);

	/*
	char **envp,
	char	**paths;
	char	*temp;
	int		i;

	paths = NULL;
	while (envp != NULL && *envp != NULL && ft_strncmp("PATH", *envp, 4))
		envp++;
	if (envp != NULL && *envp != NULL)
		paths = ft_split(*envp + 5, ':');
	i = -1;
	if (paths != NULL)
	{
		while (paths[++i] != NULL)
		{
			temp = paths[i];
			paths[i] = ft_strjoin(paths[i], "/");
			free(temp);
		}
	}
	if (strrchr(cmd_exec, '/') != NULL) //remover dps
	{
		if (access(cmd_exec, F_OK | X_OK) == 0)
			return (ft_strdup(cmd_exec));
		return (NULL);
	}
	while (paths != NULL && *paths != NULL)
	{
		runpath = ft_strjoin(*paths, cmd_exec);
		if (access(runpath, F_OK | X_OK) == 0)
			return (runpath);
		free(runpath);
		paths++;
	}
	*/

static char	*get_runpath(char *cmd_exec)
{
	char	*runpath;

	runpath = ft_strjoin("/usr/bin/", cmd_exec);
	if (access(runpath, F_OK | X_OK) == 0)
		return (ft_strdup(runpath));
	free(runpath);
	if (access(cmd_exec, F_OK | X_OK) == 0)
		return (ft_strdup(cmd_exec));
	return (NULL);
}

void	executor(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (minishell->command_table[i] != NULL)
	{
		if (minishell->command_table[i]->logical_operator == LOGICAL_COMMAND)
			execute_commands(minishell, minishell->command_table[i]->commands);
		++i;
	}
}

void	free_command(void *content)
{
	t_command	*cmd;
	int			i;

	cmd = (t_command *) content;
	i = 0;
	while (cmd->args && cmd->args[i])
	{
		free(cmd->args[i]);
		++i;
	}
	free(cmd->args);
	free(cmd->pathname);
	free(cmd);
}

void	free_minishell(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (minishell->command_table && minishell->command_table[i])
	{
		clear_list(minishell->command_table[i]->commands, free_command);
		free(minishell->command_table[i]);
		++i;
	}
	free(minishell->command_table);
	clear_list(minishell->token_list, free);
}

void	execute_commands(t_minishell *minishell, t_node *commands)
{
	t_node		*node;
	t_command	*cmd;

	node = commands;
	while (node)
	{
		cmd = (t_command *) node->content;
		if (ft_strncmp(cmd->args[0], "exit", 4) == 0)
		{
			free_minishell(minishell);
			builtin_exit();
		}
		cmd->pid = fork();
		if (cmd->pid < 0)
			write(STDERR, "Error", 5);
		else if (cmd->pid == 0)
			child_process(minishell, cmd);
		else
			node = node->next;
	}
	node = commands;
	while (node)
	{
		cmd = (t_command *) node->content;
		waitpid(cmd->pid, &cmd->exit_code, 0);
		if (WIFEXITED(cmd->exit_code))
			cmd->exit_code = WEXITSTATUS(cmd->exit_code);
		if (cmd->exit_code != 0)
			write(STDOUT, "Error", 5);
		node = node->next;
	}
}

void	child_process(t_minishell *minishell, t_command *command)
{
	char	*new_runpath;

	new_runpath = get_runpath(command->pathname);
	if (new_runpath == NULL)
	{
		free_minishell(minishell);
		exit(0);
	}
	if (execve(new_runpath, command->args, minishell->envp) == -1)
		write(STDERR, "Error", 5);
}
