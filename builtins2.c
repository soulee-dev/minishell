/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 22:42:37 by soulee            #+#    #+#             */
/*   Updated: 2023/03/07 19:30:16 by soulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO fix unset
// TODO add exportw
void	command_export(t_env_list *env_list, char *key, char *value)
{
	t_env_list	*temp;

	temp = env_list;
	while (temp)
	{
		if (!ft_strncmp(temp->key, key, ft_strlen(key)))
		{
			ft_free_str(&(env_list->value));
			temp->value = ft_strdup(value);
			return ;
		}
		temp = temp->next;
	}
	add_env_node_back(&env_list, create_new_env_node(key, value));
}

void	command_unset(t_env_list *env_list, char *key)
{
	t_env_list	*temp;

	while (env_list)
	{
		if (!ft_strncmp(env_list->key, key, ft_strlen(key)))
		{
			temp = env_list;
			env_list = env_list->next;
			free(temp->key);
			free(temp->value);
			free(temp);
		}
		env_list = env_list->next;
	}
}

void	command_env(char **envp)
{
	while (*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}
}
