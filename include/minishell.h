/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:27:27 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/03 21:03:43 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <unistd.h>

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

// Cleanup functions
void	clear_list(t_node *lst, void (*del_node)(void *));
void	del_ptr_content(void *content);

// Prompt

int		command_is_equal(char *cmd, char *str);
int		command_ends_with(char *cmd, char c);
char	*get_content_fd(int fd);
int		here_doc(char	*limiter);
int		ends_in_pipe(void);

#endif
