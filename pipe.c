/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 21:07:21 by subcho            #+#    #+#             */
/*   Updated: 2023/02/28 05:29:01 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_cmd(t_cmd_list *cmd_list, char **envp, int pipe_cnt)
{
	pid_t	pid;
	int		std[2];
	int		pipefd[2];
	char	**path;
	int		status;

	std[0] = dup(STDIN_FILENO);
	std[1] = dup(STDOUT_FILENO);
	path = get_path(envp);
	// cmd_list 첫 번째가 here_doc일 때 here_doc file 만들어서 handle할 것
	while (pipe_cnt && cmd_list)
	{
		pipe(pipefd);
		pid = fork();
		while (cmd_list && cmd_list->cmd_type != TYPE_PIPE)
		{
			if (cmd_list->cmd_type == TYPE_WORD)
			{
				handle_cmd(cmd_list, path, envp, pipefd, pid, pipe_cnt);
			}
			cmd_list = cmd_list->next;
		}
		if (!cmd_list)
			break ;
		if (cmd_list->next)
			cmd_list = cmd_list->next;
		pipe_cnt--;
	}
	status = get_status(pid);
	dup2(std[0], STDIN_FILENO);
	dup2(std[1], STDOUT_FILENO);
	free_str(path);
	return (status);
}

void	handle_cmd(t_cmd_list *cmd_list, char **path, char **envp, int pipefd[], pid_t pid, int pipe_cnt)
{
	char	**cmd;

	if (pid < 0)
			print_error(NULL);
	if (pid == 0)
	{
		cmd = ft_split(cmd_list->cmd, ' ');
		if (pipe_cnt != 1)
			pipe_child(cmd_list->cmd_type, cmd[0], pipefd);
		char *path_cmd = get_cmd(path, cmd[0]);
		execve(path_cmd, cmd, envp);
		printf("path : %s, cmd : %s\n", path_cmd, cmd[0]);
		exit(0); // ㅇㅖ오ㅣ처리
	}
	else
		pipe_parent(pipefd);
}

void	pipe_child(int type, char *cmd, int pipefd[])
{
	int	file;
	
	close(pipefd[0]);
	if (type == TYPE_REDIRECT_INPUT)
	{
		file = open_file(cmd);
        if (dup2(file, STDIN_FILENO) == -1)
            print_error(NULL);
        close(file);
	}
	else
	{
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			print_error(NULL);
	}
	close(pipefd[1]);
}

void	pipe_parent(int pipefd[])
{
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		print_error(NULL);
	close(pipefd[0]);
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
