/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 21:07:21 by subcho            #+#    #+#             */
/*   Updated: 2023/03/09 23:25:23 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_pipe_cmd(t_cmd_list *cmd_list)
{
	char	*cmd;

	while (cmd_list && cmd_list->cmd_type != TYPE_PIPE)
	{
		cmd = 0;
		if (cmd_list->cmd_type == TYPE_WORD)
			cmd = cmd_list->cmd;
		cmd_list = cmd_list->next;
	}
	if (!cmd)
		return (0);
	return (ft_split(cmd, ' '));
}

int	exe_cmd(char **cmd, int pipe_cnt, t_env_list *env_list, char **env_list_str)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid < 0)
		print_error(0);
	else if (!pid)
	{
		if (pipe_cnt)
			dup2(pipefd[1], STDOUT_FILENO);
		if (!is_builtin((const char **)cmd, env_list))
			execve(get_cmd(get_path(env_list_str), cmd[0]), cmd, env_list_str);
		exit(0);
	}
	if (pipe_cnt)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
	return (pid);
}

int	execute(t_cmd_list *cmd_list, t_env_list *env_list, int pipe_cnt)
{
	int		*std;
	int		status;
	char	**split_cmd;
	int		here_doc_cnt;
	char	**env_list_str;

	std = dup_std();
	env_list_str = convert_env_list_to_arr(env_list);
	here_doc_cnt = is_here_doc_exist(&cmd_list, pipe_cnt);
	while (--pipe_cnt >= 0)
	{
		split_cmd = get_pipe_cmd(cmd_list);
		if (redirect_pipe(&cmd_list) == -1 && split_cmd)
			status = exe_cmd(0, pipe_cnt, env_list, env_list_str);
		else if (!split_cmd)
			continue ;
		else if (pipe_cnt || !pipe_cnt
			&& !is_builtin((const char **)split_cmd, env_list))
			status = exe_cmd(split_cmd, pipe_cnt, env_list, env_list_str);
		ft_free_strs(split_cmd);
	}
	delete_here_doc(here_doc_cnt);
	ft_free_strs(env_list_str);
	redirect_std(std);
	return (get_status(status));
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
			status = temp;
	}
	return (status << 8);
}
