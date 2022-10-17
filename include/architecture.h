/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   architecture.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:11:42 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/17 19:18:22 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARCHITECTURE_H
# define ARCHITECTURE_H

# include <stddef.h>
# include <sys/types.h>

typedef struct s_node	t_node;

enum e_logical_operator {
	LOGICAL_COMMAND,
	LOGICAL_AND,
	LOGICAL_OR
};

typedef struct s_command
{
	pid_t	pid;
	char	*pathname;
	char	**args;
	int		exit_code;
	int		input;
	int		output;
	char	**envp;
}	t_command;

typedef struct s_pipeline
{
	t_node	*commands;
	int		logical_operator;
}	t_pipeline;

typedef struct s_minishell
{
	t_node		*env_list;
	t_node		*token_list;
	t_pipeline	**command_table;
	char		**envp;
}	t_minishell;

t_node	*lexer(char *prompt);
void	parser(t_minishell *minishell);
void	executor(t_minishell *minishell);
void	free_minishell(t_minishell *minishell);

#endif