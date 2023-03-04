/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 21:10:01 by subcho            #+#    #+#             */
/*   Updated: 2023/03/02 18:16:28 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *msg)
{
	perror(msg);
	exit(1);
}

char	**get_path(char **envp)
{
	char	*path;

	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	path = *envp + 5;
	return (ft_split(path, ':'));
}

char	*get_cmd(char **path, char *cmd)
{
	int		i;
	char	*pathname;
	char	*cmd_pathname;

	if (access(cmd, F_OK) == 0)
		return (cmd);
	i = 0;
	while (path[i])
	{
		pathname = ft_strjoin_no_free(path[i], "/");
		cmd_pathname = ft_strjoin_free(pathname, cmd);
		if (access(cmd_pathname, F_OK) == 0)
			return (cmd_pathname);
		free(cmd_pathname);
		i++;
	}
	write(2, "command not found: ", 19);
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
	exit(1);
	return (0);
}

int	open_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		print_error(file_name);
	return (fd);
}

int	create_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		print_error(file_name);
	return (fd);
}

void	free_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
