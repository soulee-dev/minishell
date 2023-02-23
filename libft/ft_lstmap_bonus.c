/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 01:18:33 by soulee            #+#    #+#             */
/*   Updated: 2022/11/12 17:24:48 by soulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void*(*f)(void *), void(*del)(void *))
{
	void	*temp;
	t_list	*new_node;
	t_list	*temp_node;

	if (!lst)
		return (NULL);
	new_node = NULL;
	while (lst)
	{
		temp = (*f)(lst->content);
		temp_node = ft_lstnew(temp);
		if (!temp_node)
		{
			del(temp);
			ft_lstclear(&new_node, del);
			return ((void *)(0));
		}
		ft_lstadd_back(&new_node, temp_node);
		lst = lst->next;
	}
	return (new_node);
}
