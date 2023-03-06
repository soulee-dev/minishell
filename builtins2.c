/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 22:42:37 by soulee            #+#    #+#             */
/*   Updated: 2023/03/06 16:52:47 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO fix unset
// TODO add exportw
void	unset(t_env_list *env_list, char *key)
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

void	env(char **envp)
{
	while (*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}
}
