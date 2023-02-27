/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 21:07:21 by subcho            #+#    #+#             */
/*   Updated: 2023/02/28 02:33:42 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_cmd(t_cmd_list *cmd_list, char **envp)
{
	char	**path;
	int		status;

	path = get_path(envp);
	// cmd_list 첫 번째가 here_doc일 때 here_doc file 만들어서 handle할 것
	status = handle_cmd(cmd_list, path, envp);
	return (status);
}

int	handle_cmd(t_cmd_list *cmd_list, char **path, char **envp)
{
	pid_t	pid;
	int		std[2];
	char	**cmd;
	int		pipefd[2];

	std[0] = dup(STDIN_FILENO);
	std[1] = dup(STDOUT_FILENO);
	while (cmd_list)
	{
		pipe(pipefd);
		pid = fork();
		if (pid < 0)
			print_error(NULL);
		if (pid == 0)
		{
			cmd = ft_split(cmd_list->cmd, ' ');
			if (!(!cmd_list->next && cmd_list->cmd_type != TYPE_REDIRECT_OUTPUT && cmd_list->cmd_type != TYPE_REDIRECT_APPEND))
				pipe_child(cmd_list->cmd_type, cmd[0], pipefd);
			execve(get_cmd(path, cmd[0]), cmd, envp);
			free_str(cmd);
		}
		else
			pipe_parent(pipefd);
		cmd_list = cmd_list->next;
	}
	free_str(path);
	dup2(std[0], STDIN_FILENO);
	dup2(std[1], STDOUT_FILENO);
	// process 여러 개 뜨는 거 확인할 것
	return (get_status(pid));
}

void	pipe_child(int type, char *cmd, int pipefd[])
{
	close(pipefd[0]);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		print_error(NULL);
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
