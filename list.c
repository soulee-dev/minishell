/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 22:19:01 by soulee            #+#    #+#             */
/*   Updated: 2023/02/27 17:16:21 by soulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// list 구현 필요. 단방향 양방향 할지 선택해야 함.
#include "minishell.h"

t_cmd	*create_new_node(int type, char *cmd)
{
	t_cmd	*new_node;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	new_node->type = type;
	new_node->cmd = cmd;
	new_node->next = NULL;
	return (new_node);
}

t_cmd	*get_last_node(t_cmd *node)
{
	if (!node)
		return (NULL);
	while (node)
		node = node->next;
	return (node);
}

void	add_node_back(t_cmd **node, t_cmd *new)
{
	t_cmd	*last;

	if (!*node)
	{
		*node = new;
		return (NULL);
	}
	last = get_last_node(*node);
	last->next = new;
}
