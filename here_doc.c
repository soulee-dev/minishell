/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:37:33 by subcho            #+#    #+#             */
/*   Updated: 2023/03/24 22:12:19 by soulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_here_doc_file(int count, char *delimiter, char *here_doc_org)
{
	int		fd;
	char	*cnt_str;
	char	*here_doc_str;

	cnt_str = ft_itoa(count);
	here_doc_str = ft_strjoin_no_free(here_doc_org, cnt_str);
	fd = open(here_doc_str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		print_error(NULL);
	read_here_doc(fd, delimiter);
	close(fd);
	free(cnt_str);
	return (here_doc_str);
}

int	is_here_doc_exist(t_cmd_list **cmd_list, int pipe_cnt)
{
	t_cmd_list	*top;
	int			count;
	char		*here_doc_org;

	count = 0;
	here_doc_org = "/tmp/.here_doc";
	top = *cmd_list;
	while (--pipe_cnt >= 0)
	{
		while (*cmd_list && (*cmd_list)->cmd_type != TYPE_PIPE)
		{
			if ((*cmd_list)->cmd_type == TYPE_REDIRECT_HEREDOC)
			{
				(*cmd_list)->cmd = create_here_doc_file(count,
						(*cmd_list)->cmd, here_doc_org);
				(*cmd_list)->cmd_type = TYPE_REDIRECT_INPUT;
				count++;
			}
			*cmd_list = (*cmd_list)->next;
		}
		if ((*cmd_list) && (*cmd_list)->next)
			*cmd_list = (*cmd_list)->next;
	}
	*cmd_list = top;
	return (count);
}

void	delete_here_doc(int here_doc_cnt)
{
	char	*cnt_str;
	char	*here_doc_org;
	char	*here_doc_str;

	if (!here_doc_cnt)
		return ;
	here_doc_org = "/tmp/.here_doc";
	while (--here_doc_cnt >= 0)
	{
		cnt_str = ft_itoa(here_doc_cnt);
		here_doc_str = ft_strjoin_no_free(here_doc_org, cnt_str);
		if (access(here_doc_str, F_OK) == 0)
			unlink(here_doc_str);
		free(cnt_str);
		free(here_doc_str);
	}
}

void	read_here_doc(int fd, char *delimiter)
{
	char	*line;
	char	**split_delimiter;

	split_delimiter = ft_split(delimiter, ' ');
	while (1)
	{
		line = readline("> ");
		if (!ft_strcmp(line, split_delimiter[0]))
			break ;
		line = ft_strjoin_char(line, '\n');
		write(fd, line, ft_strlen(line));
		free(line);
		line = NULL;
	}
	split_delimiter = ft_free_strs(split_delimiter);
}
