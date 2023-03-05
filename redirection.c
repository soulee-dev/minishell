/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 22:12:15 by subcho            #+#    #+#             */
/*   Updated: 2023/03/05 22:53:45 by subcho           ###   ########.fr       */
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

void	read_here_doc(char	*delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
			break ;
		free(line);
		line = NULL;
	}
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
	else if (type == TYPE_REDIRECT_HEREDOC)
	{
		dup2(STDOUT_FILENO, STDIN_FILENO);
		read_here_doc(split_file_name[0]);
	}
	ft_free_str(split_file_name);
}
