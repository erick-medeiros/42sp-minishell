/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:11:42 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/04 10:24:39 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stddef.h>
# include <sys/types.h>

typedef struct s_node	t_node;
typedef struct s_queue	t_queue;
typedef struct s_tree	t_tree;
typedef struct s_vlst	t_vlst;

typedef enum e_bool {
	FALSE,
	TRUE
}	t_bool;

typedef enum e_tok_type {
	TOKEN_AND,
	TOKEN_APPEND,
	TOKEN_BRCINCOMP,
	TOKEN_DQUOTE,
	TOKEN_DQBRACE,
	TOKEN_DQINCOMP,
	TOKEN_HEREDOC,
	TOKEN_IGNORE,
	TOKEN_INPUT,
	TOKEN_OR,
	TOKEN_OUTPUT,
	TOKEN_OPARENTHESIS,
	TOKEN_CPARENTHESIS,
	TOKEN_PIPE,
	TOKEN_SQUOTE,
	TOKEN_SQBRACE,
	TOKEN_SQINCOMP,
	TOKEN_SUBSHELL,
	TOKEN_WORD,
	TOKEN_NL
}	t_tok_type;

typedef enum e_lex_state {
	STATE_AMPERSAND,
	STATE_AND,
	STATE_APPEND,
	STATE_BRACE,
	STATE_COMPLETE,
	STATE_CONTINUE,
	STATE_CPARENTHESIS,
	STATE_DQUOTE,
	STATE_HEREDOC,
	STATE_INCOMPLETE,
	STATE_INPUT,
	STATE_INVALID,
	STATE_OPARENTHESIS,
	STATE_OR,
	STATE_OUTPUT,
	STATE_PIPE,
	STATE_SKIP,
	STATE_SQUOTE,
	STATE_WORD
}	t_lex_state;

typedef struct s_cmd
{
	pid_t	pid;
	char	*pathname;
	int		argc;
	char	**argv;
	int		status;
	int		input;
	int		output;
	int		piping[2];
	int		redir[2];
	int		group_redir[2];
	t_node	*redirect;
	t_node	*word_tokens;
	int		number;
	char	**envp;
	t_bool	isbuiltin;
	t_bool	ispipeline;
}	t_cmd;

typedef struct s_exec
{
	t_tree	*commands;
	t_queue	*queue;
	t_vlst	*env;
}	t_exec;

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
	char	*line;
	size_t	start;
	size_t	len;
	t_bool	in_braces;
}	t_val_info;

typedef struct s_vlst
{
	t_node	*list;
	size_t	len;
	int		last_status;
}	t_vlst;

typedef enum e_tree_type {
	TREE_TYPE_AND,
	TREE_TYPE_CMD,
	TREE_TYPE_OR,
	TREE_TYPE_PIPE,
	TREE_TYPE_OPAR,
	TREE_TYPE_CPAR,
	TREE_TYPE_IGNORE,
	TREE_TYPE_GROUP
}		t_tree_type;

typedef struct s_tree {
	t_tree_type		type;
	void			*content;
	struct s_tree	*left;
	struct s_tree	*right;
}		t_tree;

typedef struct s_queue
{
	t_node	*front;
	t_node	*rear;
}	t_queue;

typedef struct s_ms
{
	t_vlst	env_list;
	t_node	*token_list;
	t_tree	*tmp_cmd;
	t_node	*opstack;
	t_queue	cmd_list;
	int		num_pars;
	t_bool	set_history;
}	t_ms;

typedef struct s_heredoc
{
	char	*delimiter;
	t_cmd	*cmd;
}	t_heredoc;

#endif
