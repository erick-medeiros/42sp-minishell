/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   architecture.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:11:42 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/19 12:01:00 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARCHITECTURE_H
# define ARCHITECTURE_H

# include <stddef.h>
# include <sys/types.h>

typedef struct s_node
{
	void			*content;
	struct s_node	*next;
}	t_node;

typedef struct s_var
{
	char	*name;
	char	*val;
}	t_var;

typedef struct s_vlst
{
	t_node	*list;
	size_t	len;
}	t_vlst;

typedef struct s_node_funcs
{
	void	(*clear)(void *content);
	int		(*cmp)(void *a, void *b);
}	t_node_funcs;

enum e_operators {
	OPERATOR_MAIN,
	OPERATOR_PRIORITY,
	OPERATOR_AND,
	OPERATOR_OR
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
	enum e_operators	operator;
	t_node				*commands;
}	t_pipeline;

typedef struct s_minishell
{
	t_vlst	env_list;
	t_node	*token_list;
	t_node	*pipelines;
	char	**envp;
}	t_minishell;

enum e_token {
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_INPUT,
	TOKEN_OUTPUT,
	TOKEN_APPEND,
	TOKEN_SQUOTE,
	TOKEN_DQUOTE
};

typedef struct s_token
{
	enum e_token	type;
	char			*value;
}	t_token;

t_node	*lexer(char *prompt);
void	parser(t_minishell *minishell);
void	executor(t_minishell *minishell);
void	free_minishell(t_minishell *minishell);

#endif