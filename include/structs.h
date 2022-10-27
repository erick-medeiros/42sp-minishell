/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:11:42 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/27 02:32:51 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stddef.h>
# include <sys/types.h>

typedef enum e_lex_state {
	STATE_APPEND,
	STATE_COMPLETE,
	STATE_DQUOTE,
	STATE_DQINCOMP,
	STATE_HEREDOC,
	STATE_INPUT,
	STATE_INVALID,
	STATE_OUTPUT,
	STATE_PIPE,
	STATE_SKIP,
	STATE_SQUOTE,
	STATE_SQINCOMP,
	STATE_WORD
}	t_lex_state;

enum e_operators {
	OPERATOR_MAIN,
	OPERATOR_PRIORITY,
	OPERATOR_AND,
	OPERATOR_OR
};

typedef enum e_tok_type {
	TOKEN_APPEND,
	TOKEN_DQUOTE,
	TOKEN_DQINCOMP,
	TOKEN_HEREDOC,
	TOKEN_INPUT,
	TOKEN_OUTPUT,
	TOKEN_PIPE,
	TOKEN_SQUOTE,
	TOKEN_SQINCOMP,
	TOKEN_WORD
}	t_tok_type;

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

typedef struct s_node
{
	void			*content;
	struct s_node	*next;
}	t_node;

typedef struct s_node_funcs
{
	void	(*clear)(void *content);
	int		(*cmp)(void *a, void *b);
}	t_node_funcs;

typedef struct s_pipeline
{
	enum e_operators	operator;
	t_node				*commands;
}	t_pipeline;

typedef struct s_token
{
	t_tok_type	type;
	char		*value;
}	t_token;

typedef struct s_val_info
{
	char *prompt;
	size_t	start;
	size_t	len;
	int		active;
}	t_val_info;

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

typedef struct s_minishell
{
	t_vlst	env_list;
	t_node	*token_list;
	t_node	*pipelines;
	char	**envp;
}	t_minishell;

#endif
