/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 00:56:53 by gmachado          #+#    #+#             */
/*   Updated: 2022/11/05 04:19:54 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"

t_queue	*new_queue(void)
{
	t_queue	*queue;

	queue = malloc(sizeof(*queue));
	if (queue == NULL)
		return (NULL);
	queue->front = NULL;
	queue->rear = NULL;
	return (queue);
}

int	enqueue(t_queue *queue, void *content)
{
	t_node	*new_node;
	int		result;

	if (!queue)
		return (ERR_NOT_FOUND);
	new_node = NULL;
	result = add_node(&new_node, content);
	if (result)
		return (result);
	if (queue->rear == NULL)
	{
		queue->rear = new_node;
		queue->front = new_node;
		return (OK);
	}
	queue->rear->next = new_node;
	queue->rear = new_node;
	return (OK);
}

void	*dequeue(t_queue *queue)
{
	t_node	*tmp;
	void	*content;

	if (queue == NULL || queue->front == NULL)
		return (NULL);
	tmp = queue->front;
	content = tmp->content;
	queue->front = queue->front->next;
	if (queue->front == NULL)
		queue->rear = NULL;
	free(tmp);
	return (content);
}
