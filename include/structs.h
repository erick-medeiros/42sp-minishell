/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:11:42 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/31 15:28:25 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stddef.h>
# include <sys/types.h>

typedef enum e_bool {
	FALSE,
	TRUE
}	t_bool;

typedef enum e_operator {
	OPERATOR_MAIN,
	OPERATOR_PRIORITY,
	OPERATOR_AND,
	OPERATOR_OR
}	t_operator;

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

typedef struct s_cmd
{
	pid_t	pid;
	char	*pathname;
	int		argc;
	char	**argv;
	int		status;
	int		input;
	int		output;
	int		number;
	char	**envp;
	t_bool	subshell;
	t_bool	isbuiltin;
}	t_cmd;

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
	t_operator	operator;
	t_node		*commands;
	int			command_count;
	int			**pipefds;
}	t_pipeline;

typedef struct s_token
{
	t_tok_type	type;
	char		*value;
}	t_token;

typedef struct s_var
{
	char	*name;
	char	*val;
}	t_var;

typedef struct s_val_info
{
	char	*prompt;
	size_t	start;
	size_t	len;
	int		active;
}	t_val_info;

typedef struct s_vlst
{
	t_node	*list;
	size_t	len;
}	t_vlst;

typedef enum e_tree_type {
	TREE_TYPE_CMD,
	TREE_TYPE_PIPE
}		t_tree_type;

typedef struct s_tree {
	t_tree_type		type;
	void			*content;
	struct s_tree	*left;
	struct s_tree	*right;
}		t_tree;

typedef struct s_minishell
{
	t_vlst	env_list;
	t_node	*token_list;
	t_node	*pipelines;
	char	**path_list;
	t_tree	*root;
}	t_minishell;

#endif
