/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 22:12:15 by subcho            #+#    #+#             */
/*   Updated: 2023/03/27 01:18:14 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_pipe(t_cmd_list **cmd_list, int *fd_in, int *fd_out)
{
	int	fd;

	while (*cmd_list && (*cmd_list)->cmd_type != TYPE_PIPE)
	{
		if ((*cmd_list)->cmd_type != TYPE_WORD && fd != -1)
			fd = redirect_fd((*cmd_list)->cmd_type, (*cmd_list)->cmd, fd_in,
					fd_out);
		if ((*cmd_list)->next)
			*cmd_list = (*cmd_list)->next;
		else
			break ;
	}
	if (*cmd_list && (*cmd_list)->cmd_type == TYPE_PIPE)
		*cmd_list = (*cmd_list)->next;
	return (fd);
}

int	redirect_fd(int type, char *file_name, int *fd_in, int *fd_out)
{
	int		fd;
	char	**split_file_name;

	split_file_name = ft_split(file_name, ' ');
	if (type == TYPE_REDIRECT_INPUT)
	{
		fd = open_file(split_file_name[0]);
		dup2(fd, STDIN_FILENO);
		*fd_in = fd;
	}
	else if (type == TYPE_REDIRECT_OUTPUT)
	{
		fd = create_file(split_file_name[0]);
		dup2(fd, STDOUT_FILENO);
		*fd_out = fd;
	}
	else if (type == TYPE_REDIRECT_APPEND)
	{
		fd = append_file(split_file_name[0]);
		dup2(fd, STDOUT_FILENO);
		*fd_out = fd;
	}
	ft_free_strs(split_file_name);
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
	free(std);
}
