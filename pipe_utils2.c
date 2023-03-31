/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@studnet.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 17:28:34 by subcho            #+#    #+#             */
/*   Updated: 2023/03/31 23:45:30 by soulee           ###   ########.fr       */
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

int	get_status(void)
{
	int	i;
	int	status;
	int	sig_no;

	i = 0;
	while (wait(&status) != -1)
	{
		if (WIFSIGNALED(status))
		{
			sig_no = WTERMSIG(status);
			if (sig_no == SIGINT && i++ == 0)
				ft_putendl_fd("^C", 2);
			else if (sig_no == SIGQUIT && i++ == 0)
				ft_putendl_fd("^\\Quit: 3", 2);
			g_exit_code = 128 + sig_no;
		}
		else
			g_exit_code = WEXITSTATUS(status);
	}
	return (g_exit_code);
}
