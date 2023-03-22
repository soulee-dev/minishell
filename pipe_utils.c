/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 21:10:01 by subcho            #+#    #+#             */
/*   Updated: 2023/03/22 20:08:24 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path(char **envp)
{
	char	*path;

	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	path = *envp + 5;
	return (ft_split(path, ':'));
}

char	*get_cmd(char **path, char *cmd)
{
	int		i;
	char	*pathname;
	char	*cmd_pathname;

	if (access(cmd, F_OK) == 0)
		return (cmd);
	i = 0;
	while (path[i])
	{
		pathname = ft_strjoin_no_free(path[i], "/");
		cmd_pathname = ft_strjoin_free(pathname, cmd);
		if (access(cmd_pathname, F_OK) == 0)
			return (cmd_pathname);
		free(cmd_pathname);
		i++;
	}
	write(2, "command not found: ", 19);
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
	return (0);
}

void	ft_free_strs(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = 0;
}

int	get_echo_n_cnt(const char **command)
{
	int	i;

	i = 1;
	while (++i && command[i])
	{
		if (ft_strcmp(command[i], "-n"))
			break ;
	}
	return (i);
}

int	is_builtin(const char **command, t_env_list *env_list)
{
	if (!ft_strcmp(command[0], "echo"))
	{
		if (command[1] && !ft_strcmp(command[1], "-n"))
			command_echo(command + get_echo_n_cnt(command), 1);
		else
			command_echo(command + 1, 0);
		return (1);
	}
	if (!ft_strcmp(command[0], "cd"))
	{
		command_cd(command[1]);
		return (1);
	}
	if (!ft_strcmp(command[0], "pwd"))
	{
		command_pwd();
		return (1);
	}
	if (!ft_strcmp(command[0], "export"))
	{
		command_export(env_list, command);
		return (1);
	}
	if (!ft_strcmp(command[0], "unset"))
	{
		command_unset(env_list, command[1]);
		return (1);
	}
	if (!ft_strcmp(command[0], "env"))
	{
		command_env(env_list);
		return (1);
	}
	if (!ft_strcmp(command[0], "exit"))
	{
		command_exit(command[1]);
		return (1);
	}
	return (0);
}
