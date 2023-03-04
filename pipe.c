/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 21:07:21 by subcho            #+#    #+#             */
/*   Updated: 2023/03/04 22:55:29 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_cmd(t_cmd_list *cmd_list, char **envp, int pipe_cnt)
{
	int		i;
	int		fd;
	pid_t	pid;
	int		std[2];
	char	**path;
	int		pipefd[2];
	char	**split_cmd;

	std[0] = dup(STDIN_FILENO);
	std[1] = dup(STDOUT_FILENO);
	path = get_path(envp);
	i = 0;
	while (i < pipe_cnt)
	{
		while (cmd_list && cmd_list->cmd_type != TYPE_PIPE)
		{
			pipe(pipefd);
			pid = fork();
			if (pid < 0)
				print_error(0);
			else if (pid == 0)
			{
				split_cmd = ft_split(cmd_list->cmd, ' ');
				close(pipefd[0]);
				if (cmd_list->cmd_type == TYPE_REDIRECT_INPUT)
				{
					fd = open_file(split_cmd[0]);
					dup2(fd, STDIN_FILENO);
				}
				else if (cmd_list->cmd_type == TYPE_REDIRECT_OUTPUT)
				{
					printf("hello? \n");
					fd = create_file(split_cmd[0]);
					dup2(fd, STDOUT_FILENO);
				}
				else if (cmd_list->cmd_type == TYPE_WORD)
				{
					if (i + 1 != pipe_cnt)
						dup2(pipefd[1], STDOUT_FILENO);
					execve(get_cmd(path, split_cmd[0]), split_cmd, envp);
					exit(0);
				}
				close(pipefd[1]);
				free_str(split_cmd);
			}
			else
			{
				if (i > 0 && i + 1 < pipe_cnt)
				{
					close(pipefd[1]);
					dup2(pipefd[0], STDIN_FILENO);
					close(pipefd[0]);
				}
			}
			cmd_list = cmd_list->next;
		}
		if (cmd_list)
			cmd_list = cmd_list->next;
		i++;
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
