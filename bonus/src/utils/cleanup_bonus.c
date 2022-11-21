/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 15:32:03 by gmachado          #+#    #+#             */
/*   Updated: 2022/11/21 04:05:47 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	clear_list(t_node *lst, void (*del_node)(void *))
{
	t_node	*tmp;

	while (lst)
	{
		if (del_node)
			del_node(lst->content);
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
}

void	*clear_envp(char **envp)
{
	char	**tmp;

	if (!envp)
		return (NULL);
	tmp = envp;
	while (*tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(envp);
	return (NULL);
}

void	del_var_node(void *content)
{
	if (!content)
		return ;
	free(((t_var *)content)->name);
	free(((t_var *)content)->val);
	free(((t_var *)content));
}

void	del_token_node(void *content)
{
	if (!content)
		return ;
	free(((t_token *)content)->value);
	free(((t_token *)content));
}

void	del_heredoc_node(void *content)
{
	if (!content)
		return ;
	free(((t_heredoc *)content)->delimiter);
	free(((t_heredoc *)content));
}
