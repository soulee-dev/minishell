/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 21:07:21 by subcho            #+#    #+#             */
/*   Updated: 2023/03/07 22:31:06 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_pipe_cmd(t_cmd_list *cmd_list)
{
	char	*cmd;

	cmd = 0;
	while (cmd_list && cmd_list->cmd_type != TYPE_PIPE)
	{
		if (cmd_list->cmd_type == TYPE_WORD)
			cmd = cmd_list->cmd;
		cmd_list = cmd_list->next;
	}
	if (!cmd)
		return (0);
	return (ft_split(cmd, ' '));
}

int	exe_cmd(char **cmd, char **path, int pipe_cnt, char **envp)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid < 0)
		print_error(0);
	else if (pid == 0)
	{
		if (pipe_cnt != 1)
			dup2(pipefd[1], STDOUT_FILENO);
		if (!is_builtin((const char **)cmd, envp))
			execve(get_cmd(path, cmd[0]), cmd, envp);
		exit(0);
	}
	else
	{
		if (pipe_cnt != 1)
		{
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
		}
	}
	return (pid);
}

int	execute(t_cmd_list *cmd_list, char **envp, int pipe_cnt)
{
	int		std[2];
	int		status;
	char	**path;
	char	**split_cmd;
	int		here_doc_cnt;

	std[0] = dup(STDIN_FILENO);
	std[1] = dup(STDOUT_FILENO);
	path = get_path(envp);
	here_doc_cnt = is_here_doc_exist(&cmd_list, pipe_cnt);
	while (pipe_cnt)
	{
		split_cmd = get_pipe_cmd(cmd_list);
		cmd_list = redirect_pipe(cmd_list);
		if (pipe_cnt == 1 && is_builtin((const char **)split_cmd, envp))
		{
			ft_free_strs(split_cmd);
			break ;
		}
		if (split_cmd)
		{
			status = exe_cmd(split_cmd, path, pipe_cnt, envp);
			ft_free_strs(split_cmd);
		}
		pipe_cnt--;
	}
	ft_free_strs(path);
	delete_here_doc(here_doc_cnt);
	dup2(std[0], STDIN_FILENO);
	dup2(std[1], STDOUT_FILENO);
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
