/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 22:19:01 by soulee            #+#    #+#             */
/*   Updated: 2023/02/27 19:24:28 by soulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// list 구현 필요. 단방향 양방향 할지 선택해야 함.
#include "minishell.h"

t_cmd_list	*create_new_node(int type, char *cmd)
{
	t_cmd_list	*new_node;

	new_node = (t_cmd_list *)malloc(sizeof(t_cmd_list));
	if (!new_node)
		return (NULL);
	new_node->cmd_type = type;
	new_node->cmd = cmd;
	new_node->next = NULL;
	return (new_node);
}

t_cmd_list	*get_last_node(t_cmd_list *node)
{
	if (!node)
		return (NULL);
	while (node)
		node = node->next;
	return (node);
}

void	add_node_back(t_cmd_list **node, t_cmd_list *new)
{
	t_cmd_list	*last;

	if (!*node)
	{
		*node = new;
		return (NULL);
	}
	last = get_last_node(*node);
	last->next = new;
}
