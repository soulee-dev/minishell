/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 22:21:31 by soulee            #+#    #+#             */
/*   Updated: 2023/04/03 21:54:37 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(t_env_list *node, char *key)
{
	if (!key)
		return ("$");
	while (node)
	{
		if (!ft_strcmp(node->key, key))
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
	env = (char **)malloc(sizeof(char *) * (get_env_list_size(node)) + 1);
	if (!env)
		return (NULL);
	while (node)
	{
		temp = ft_strjoin_no_free(node->key, "=");
		if (node->value)
			temp = ft_strjoin_free(temp, node->value);
		env[i] = temp;
		node = node->next;
		temp = 0;
		i++;
	}
	env[i] = 0;
	return (env);
}

char	**convert_env_list_to_export(t_env_list *node)
{
	int		i;
	char	*temp;
	char	**env;

	i = 0;
	env = (char **)malloc(sizeof(char *) * (get_env_list_size(node)) + 1);
	if (!env)
		return (NULL);
	while (node)
	{
		temp = ft_strdup(node->key);
		if (node->value)
		{
			temp = ft_strjoin_free(temp, "=\"");
			temp = ft_strjoin_free(temp, node->value);
			temp = ft_strjoin_free(temp, "\"");
		}
		env[i] = temp;
		node = node->next;
		temp = 0;
		i++;
	}
	env[i] = 0;
	return (env);
}

void	parse_envp(t_env_list **node, char **envp)
{
	char		*key;
	int			flag;
	char		*value;

	while (*envp)
	{
		flag = 1;
		key = NULL;
		value = NULL;
		while (**envp)
		{
			if (**envp == '=')
				flag = 0;
			else
			{
				if (flag)
					key = ft_strjoin_char(key, **envp);
				else
					value = ft_strjoin_char(value, **envp);
			}
			(*envp)++;
		}
		add_env_node_back(node, create_new_env_node(key, value));
		envp++;
	}
}

void	ft_swap(char **s1, char **s2)
{
	char	*temp;

	temp = *s2;
	*s2 = *s1;
	*s1 = temp;
}
