/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 22:12:15 by subcho            #+#    #+#             */
/*   Updated: 2023/04/04 19:05:25 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_pipe(t_exe_list *exe_list)
{
	int	fd;

	exe_list->fd_in = STDIN_FILENO;
	exe_list->fd_out = STDOUT_FILENO;
	while (exe_list->cmd_list && exe_list->cmd_list->cmd_type != TYPE_PIPE)
	{
		if (exe_list->cmd_list->cmd_type != TYPE_WORD && fd != -1)
			fd = redirect_fd(exe_list->cmd_list->cmd_type,
					exe_list->cmd_list->cmd, exe_list);
		if (exe_list->cmd_list->next)
			exe_list->cmd_list = exe_list->cmd_list->next;
		else
			break ;
	}
	if (exe_list->cmd_list && exe_list->cmd_list->cmd_type == TYPE_PIPE)
		exe_list->cmd_list = exe_list->cmd_list->next;
	if (exe_list->fd_in > STDIN_FILENO)
		dup2(exe_list->fd_in, STDIN_FILENO);
	if (exe_list->fd_out > STDOUT_FILENO)
		dup2(exe_list->fd_out, STDOUT_FILENO);
	return (fd);
}

int	redirect_fd(int type, char *file_name, t_exe_list *exe_list)
{
	int		fd;

	if (type == TYPE_REDIRECT_INPUT)
	{
		exe_list->fd_in = open_file(file_name);
		return (exe_list->fd_in);
	}
	else if (type == TYPE_REDIRECT_OUTPUT)
	{
		exe_list->fd_out = create_file(file_name);
		return (exe_list->fd_out);
	}
	else if (type == TYPE_REDIRECT_APPEND)
	{
		exe_list->fd_out = append_file(file_name);
		return (exe_list->fd_out);
	}
	return (fd);
}

int	*dup_std(void)
{
	int	*std;

	std = malloc(sizeof(int) * 2);
	std[0] = dup(STDIN_FILENO);
	std[1] = dup(STDOUT_FILENO);
	return (std);
}

void	redirect_std(int *std)
{
	dup2(std[0], STDIN_FILENO);
	dup2(std[1], STDOUT_FILENO);
	close(std[0]);
	close(std[1]);
	free(std);
	std = 0;
}
