/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 22:19:01 by soulee            #+#    #+#             */
/*   Updated: 2023/03/04 20:19:42 by soulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_list	*create_new_cmd_node(int type, char *cmd)
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

t_cmd_list	*get_last_cmd_node(t_cmd_list *node)
{
	if (!node)
		return (NULL);
	while (node->next)
		node = node->next;
	return (node);
}

void	add_cmd_node_back(t_cmd_list **node, t_cmd_list *new)
{
	t_cmd_list	*last;

	if (!*node)
	{
		*node = new;
		return ;
	}
	last = get_last_cmd_node(*node);
	last->next = new;
}

void	iter_node(t_cmd_list *node)
{
	// REMOVE BEFORE FLIGHT
	while (node)
	{
		printf("[%d]=%s\n", node->cmd_type, node->cmd);
		node = node->next;
	}
}

int	count_cmd_list_node(t_cmd_list *node, int cmd_type)
{
	int	count;

	count = 0;
	while (node)
	{
		if (node->cmd_type == cmd_type)
			count++;
		node = node->next;
	}
	return (count);
}

void	clear_cmd_list(t_cmd_list **node)
{
	t_cmd_list	*temp;

	if (!*node)
		return ;
	while (*node)
	{
		temp = (*node)->next;
		free((*node)->cmd);
		free(*node);
		*node = temp;
	}
	*node = 0;
}
