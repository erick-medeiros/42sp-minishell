/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 03:11:10 by gmachado          #+#    #+#             */
/*   Updated: 2022/12/08 09:40:33 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	partition(char **envp, size_t start_idx, size_t end_idx)
{
	char	*pivot;
	char	*tmp;
	size_t	i;
	size_t	j;

	pivot = envp[end_idx];
	i = start_idx;
	j = start_idx;
	while (j < end_idx)
	{
		if (ft_strcmp(envp[j], pivot) <= 0)
		{
			tmp = envp[j];
			envp[j] = envp[i];
			envp[i] = tmp;
			i++;
		}
		j++;
	}
	tmp = envp[end_idx];
	envp[end_idx] = envp[i];
	envp[i] = tmp;
	return (i);
}

void	quicksort(char **envp, size_t start_idx, size_t end_idx)
{
	size_t	pivot_idx;

	if (start_idx < end_idx)
	{
		pivot_idx = partition(envp, start_idx, end_idx);
		if (pivot_idx == 0)
			return ;
		quicksort(envp, start_idx, pivot_idx - 1);
		quicksort(envp, pivot_idx + 1, end_idx);
	}
}
