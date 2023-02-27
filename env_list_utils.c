/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 22:21:31 by soulee            #+#    #+#             */
/*   Updated: 2023/02/27 22:43:06 by soulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(t_env_list *node, char *key)
{
	while (node)
	{
		if (!node->key)
			return (0);
		if (!ft_strncmp(node->key, key, ft_strlen(key)))
			return (node->value);
		node = node->next;
	}
	return (0);
}

char	**convert_env_list_to_arr(t_env_list *node)
{
	int		i;
	char	*temp;
	char	**env;

	i = 0;
	env = (char **)malloc(sizeof(char *) * (get_env_list_size(node) + 1));
	if (!env)
		return (NULL);
	while (node)
	{
		temp = ft_strjoin_no_free(node->key, "=");
		temp = ft_strjoin_free(temp, node->value);
		env[i] = temp;
		node = node->next;
		i++;
	}
	return (env);
}
