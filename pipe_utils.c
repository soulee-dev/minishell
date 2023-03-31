/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 21:10:01 by subcho            #+#    #+#             */
/*   Updated: 2023/03/30 22:58:37 by subcho           ###   ########.fr       */
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
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found", 19);
	write(2, "\n", 1);
	g_exit_code = 127;
	exit(127);
	return (0);
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

int	is_builtin1(t_exe_list *t_exe_list, char **cmd_args)
{
	const char	**cmd;

	cmd = (const char **)cmd_args;
	if (!ft_strcmp(cmd[0], "echo"))
	{
		if (cmd[1] && !ft_strcmp(cmd[1], "-n"))
			command_echo(cmd + get_echo_n_cnt(cmd), 1);
		else
			command_echo(cmd + 1, 0);
		return (1);
	}
	if (!ft_strcmp(cmd[0], "cd"))
	{
		command_cd(cmd[1]);
		return (1);
	}
	if (!ft_strcmp(cmd[0], "unset"))
	{
		command_unset(t_exe_list->env_list, cmd[1]);
		return (1);
	}
	return (0);
}

int	is_builtin2(t_exe_list *t_exe_list, char **cmd_args)
{
	const char	**cmd;

	cmd = (const char **)cmd_args;
	if (!ft_strcmp(cmd[0], "exit"))
	{
		command_exit(cmd[1]);
		return (1);
	}
	if (!ft_strcmp(cmd[0], "pwd"))
	{
		command_pwd();
		return (1);
	}
	if (!ft_strcmp(cmd[0], "export"))
	{
		command_export(t_exe_list->env_list, cmd);
		return (1);
	}
	if (!ft_strcmp(cmd[0], "env"))
	{
		command_env(t_exe_list->env_list);
		return (1);
	}
	return (0);
}
