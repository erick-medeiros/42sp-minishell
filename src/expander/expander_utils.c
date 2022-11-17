/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 20:14:41 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/17 19:18:31 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static char	*list_to_string(t_node *list, size_t len);

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

	len = 0;
	node = list;
	while (node)
	{
		len += ft_strlen(node->content);
		if (!node->content)
		{
			clear_list(list, free);
			return (NULL);
		}
		node = node->next;
	}
	result = list_to_string(list, len);
	clear_list(list, free);
	return (result);
}

static char	*list_to_string(t_node *list, size_t len)
{
	t_node	*node;
	char	*result;
	char	*tmp;

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
	return (result);
}
