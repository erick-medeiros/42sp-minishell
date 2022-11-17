/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 20:14:41 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/17 17:59:28 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "structs.h"
#include "expander.h"

int	find_env_var(void *str, void *var)
{
	if (ft_streq(str, ((t_var *)var)->name))
		return (0);
	return (1);
}

char	*convert_list_to_string(t_node *list)
{
	t_node	*node;
	char	*result;
	int		len;
	char	*tmp;

	len = 0;
	node = list;
	while (node)
	{
		len += ft_strlen(node->content);
		node = node->next;
	}
	result = malloc(sizeof(char) * (len + 1));
	node = list;
	len = 0;
	while (node)
	{
		tmp = node->content;
		while (tmp && *tmp)
			result[len++] = *(tmp++);
		node = node->next;
	}
	result[len] = '\0';
	clear_list(list, free);
	return (result);
}
