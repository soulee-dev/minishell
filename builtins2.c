/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 22:42:37 by soulee            #+#    #+#             */
/*   Updated: 2023/04/03 20:12:54 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_export(t_env_list *env_list, const char **command)
{
	int			i;
	t_env_list	*temp;
	char		**cmd;

	i = 0;
	while (command[++i])
	{
		temp = env_list;
		if (!ft_strcmp(command[i], "="))
			cmd = ft_split(command[i], ' ');
		else
			cmd = ft_split(command[i], '=');
		if (!is_env_exist(temp, cmd))
		{
			if (!ft_is_string(cmd[0]))
				print_export_error(cmd[0]);
			else
				add_env_node_back(&env_list,
					create_new_env_node(ft_strdup(cmd[0]), ft_strdup(cmd[1])));
		}
		cmd = ft_free_strs(cmd);
	}
}

void	command_unset(t_env_list *env_list, const char *key)
{
	t_env_list	*temp;
	t_env_list	*before;

	before = 0;
	while (env_list)
	{
		if (!ft_strcmp(env_list->key, key))
		{
			temp = env_list;
			env_list = env_list->next;
			if (before)
				before->next = env_list;
			free(temp->key);
			free(temp->value);
			free(temp);
			return ;
		}
		before = env_list;
		env_list = env_list->next;
	}
}

void	command_env(t_env_list *env_list)
{
	int		i;
	char	**envp;

	i = 0;
	envp = convert_env_list_to_arr(env_list);
	while (envp[i])
	{
		ft_printf("%s\n", envp[i]);
		i++;
	}
	envp = ft_free_strs(envp);
}

int	is_env_exist(t_env_list	*temp, char	**cmd)
{
	while (temp)
	{
		if (!ft_strcmp(temp->key, cmd[0]))
		{
			temp->value = ft_strdup_free(temp->value, cmd[1]);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}
