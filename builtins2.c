/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 22:42:37 by soulee            #+#    #+#             */
/*   Updated: 2023/03/09 20:56:46 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO fix unset
// TODO add exportw
void	command_export(t_env_list *env_list, const char **command)
{
	int			i;
	int			flag;
	t_env_list	*temp;
	char		**cmd;

	i = 0;
	while (command[++i])
	{
		flag = 0;
		temp = env_list;
		cmd = ft_split(command[i], '=');
		while (temp && !flag)
		{
			if (!ft_strncmp(temp->key, cmd[0], ft_strlen(cmd[0])))
			{
				ft_free_str(&(env_list->value));
				temp->value = ft_strdup(cmd[1]);
				ft_free_strs(cmd);
				flag = 1;
			}
			temp = temp->next;
		}
		if (!flag)
			add_env_node_back(&env_list, create_new_env_node(cmd[0], cmd[1]));
	}
}

void	command_unset(t_env_list *env_list, const char *key)
{
	t_env_list	*temp;
	t_env_list	*before;

	before = 0;
	while (env_list)
	{
		if (!ft_strncmp(env_list->key, key, ft_strlen(key)))
		{
			temp = env_list;
			env_list = env_list->next;
			if (before)
				before->next = env_list;
			free(temp->key);
			free(temp->value);
			free(temp);
		}
		before = env_list;
		env_list = env_list->next;
	}
}

void	command_env(t_env_list *env_list)
{
	char	**envp;

	envp = convert_env_list_to_arr(env_list);
	while (*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}
	//ft_free_strs(envp);
	envp = 0;
}
