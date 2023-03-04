/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 21:07:21 by subcho            #+#    #+#             */
/*   Updated: 2023/03/04 19:13:42 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_cmd(t_cmd_list *cmd_list, char **envp, int pipe_cnt)
{
	int		fd;
	pid_t	pid;
	int		std[2];
	int		pipefd[2];
	char	**path;
	int		status;

	std[0] = dup(STDIN_FILENO);
	std[1] = dup(STDOUT_FILENO);
	path = get_path(envp);
	// cmd_list 첫 번째가 here_doc일 때 here_doc file 만들어서 handle할 것
	while (pipe_cnt)
	{
		while (cmd_list && cmd_list->cmd_type != TYPE_PIPE)
		{
			char	**split_cmd = ft_split(cmd_list->cmd, ' ');
			if (cmd_list->cmd_type == TYPE_REDIRECT_INPUT)
				fd = open_file(split_cmd[0]);
			else if (cmd_list->cmd_type == TYPE_WORD)
			{
				pipe(pipefd);
				pid = fork();
				if (pid < 0)
					print_error(0);
				else if (pid == 0)
				{
					close(pipefd[0]);
					if (fd > 0)
					{
						dup2(fd, STDIN_FILENO);
						close(fd);
						fd = 0;
					}
					if (pipe_cnt != 1)
						dup2(pipefd[1], STDOUT_FILENO);
					execve(get_cmd(path, split_cmd[0]), split_cmd, envp);
					close(pipefd[1]);
					free_str(split_cmd);
				}
				close(pipefd[1]);
				dup2(pipefd[0], STDIN_FILENO);
				close(pipefd[0]);
			}
			free_str(split_cmd);
			cmd_list = cmd_list->next;
		}
		if (cmd_list)
			cmd_list = cmd_list->next;
		pipe_cnt--;
	}
	dup2(std[0], STDIN_FILENO);
	dup2(std[1], STDOUT_FILENO);
	free_str(path);
	return (get_status(pid));
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
