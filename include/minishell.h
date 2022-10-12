/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:27:27 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/12 14:00:54 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stddef.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <unistd.h>
# include <errno.h>

# include "libft.h"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define TRUE 1
# define FALSE 0

# define PROMPT_STRING "minishell> "
# define HEREDOC_STRING "here_doc> "
# define ENDSINPIPE_STRING "> "

// Error definitions
# define OK 0
# define ERR_ALLOC 1
# define ERR_NOT_FOUND 2

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

void	miniprompt(void);

// List-related functions
int		add_node(t_node **lst, void *content);
int		change_node_content(t_node *lst, void *old_content,
			void *new_content, int (*cmp_content)(void *, void *));
t_node	*find_node_by_content(t_node *lst, void *content,
			int (*cmp_content)(void *, void *));
t_node	*remove_node(t_node *current, void (*del_node)(void *));
int		remove_node_by_content(t_node **lst, void *content,
			void (*del_node)(void *), int (*cmp_content)(void *, void *));

// Environment variable-related functions
int		cmp_vars_by_name(void *a, void *b);
t_vlst	envp_to_list(char **envp, t_vlst *vars);
char	**list_to_envp(t_vlst *vars);
t_var	*new_var_node(char *str);
int		split_name_val(char *str, char *equal_pos, t_var *content);

// Cleanup functions
void	clear_list(t_node *lst, void (*del_node)(void *));
void	*clear_envp(char **envp);
void	del_var_node(void *content);

// Prompt

int		command_is_equal(char *cmd, char *str);
int		command_ends_with(char *cmd, char c);
char	*get_content_fd(int fd);
int		here_doc(char	*limiter);
int		ends_in_pipe(void);

// Builtins

void	builtins(char *prompt);
void	builtin_echo(char *option, char *string);
void	builtin_cd(char *path);
void	builtin_pwd(void);
void	builtin_exit(void);
void	builtin_unset(int argc, char *argv[], t_vlst *vars);
void	builtin_env(t_vlst *vars);
void	builtin_export(int argc, char *argv[], t_vlst *vars);
#endif
