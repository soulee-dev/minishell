/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 22:12:15 by subcho            #+#    #+#             */
/*   Updated: 2023/03/05 22:19:11 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_list	*redirect_pipe(t_cmd_list *cmd_list)
{
	while (cmd_list && cmd_list->cmd_type != TYPE_PIPE)
	{
		if (cmd_list->cmd_type != TYPE_WORD)
			redirect_fd(cmd_list->cmd_type, cmd_list->cmd);
		if (cmd_list->next)
			cmd_list = cmd_list->next;
		else
			break ;
	}
	if (cmd_list->cmd_type == TYPE_PIPE)
		cmd_list = cmd_list->next;
	return (cmd_list);
}

void	redirect_fd(int type, char *file_name)
{
	int		fd;
	char	**split_file_name;

	split_file_name = ft_split(file_name, ' ');
	if (type == TYPE_REDIRECT_INPUT)
	{
		fd = open_file(split_file_name[0]);
		dup2(fd, STDIN_FILENO);
	}
	else if (type == TYPE_REDIRECT_OUTPUT)
	{
		fd = create_file(split_file_name[0]);
		dup2(fd, STDOUT_FILENO);
	}
	else if (type == TYPE_REDIRECT_APPEND)
	{
		fd = append_file(split_file_name[0]);
		dup2(fd, STDOUT_FILENO);
	}
	ft_free_str(split_file_name);
}
