/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 17:28:34 by subcho            #+#    #+#             */
/*   Updated: 2023/03/31 17:30:37 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_pipe_cmd(t_cmd_list *cmd_list)
{
	char	**cmd;

	cmd = 0;
	while (cmd_list && cmd_list->cmd_type != TYPE_PIPE)
	{
		if (cmd_list->cmd_type == TYPE_WORD)
		{
			cmd = cmd_list->args;
			break ;
		}
		cmd_list = cmd_list->next;
	}
	if (!cmd)
		return (0);
	return (cmd);
}

t_exe_list	*set_exe_list(t_cmd_list *cmd_list, t_env_list *env_list,
		int pipe_cnt)
{
	t_exe_list	*exe_list;

	exe_list = malloc(sizeof(t_exe_list));
	exe_list->cmd_list = cmd_list;
	exe_list->env_list = env_list;
	exe_list->pipe_cnt = pipe_cnt;
	exe_list->std = dup_std();
	exe_list->fd_in = STDIN_FILENO;
	exe_list->fd_out = STDOUT_FILENO;
	return (exe_list);
}

int	get_status(int pid)
{
	int	status;
	int	last_pid;
	int	temp;

	last_pid = pid;
	while (pid != -1)
	{
		pid = wait(&temp);
		if (pid == last_pid)
		{
			status = temp;
			g_exit_code = WEXITSTATUS(status);
		}
	}
	return (g_exit_code);
}
