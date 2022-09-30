/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:27:27 by eandre-f          #+#    #+#             */
/*   Updated: 2022/09/29 23:07:31 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

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
int		change_node_content(t_node *list, void *old_content,
			void *new_content, int (*cmp_content)(void *, void *));
t_node	*find_node_by_content(t_node *list, void *content,
			int (*cmp_content)(void *, void *));
t_node	*remove_node(t_node *current, void (*del_node)(void *));
int		remove_node_by_content(t_node **lst, void *content,
			void (*del_node)(void *), int (*cmp_content)(void *, void *));

// Libft functions
char	*ft_strdup(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
