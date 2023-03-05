/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 21:58:42 by soulee            #+#    #+#             */
/*   Updated: 2023/03/04 22:59:34 by soulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(const char *s, int no_newline)
{
	if (no_newline)
		printf("%s", s);
	else
		printf("%s\n", s);
}

// TODO add exit
void	cd(const char *path)
{
	chdir(path);
}

void	pwd(void)
{
	char	*curr_dir;

	curr_dir = getcwd(NULL, 0);
	printf("%s\n", curr_dir);
	free(curr_dir);
}

int	is_builtin(const char *command)
{
	size_t	len;

	len = ft_strlen(command);
	if (!ft_strncmp(command, "echo", len))
		return (1);
	if (!ft_strncmp(command, "cd", len))
		return (2);
	if (!ft_strncmp(command, "pwd", len))
		return (3);
	if (!ft_strncmp(command, "export", len))
		return (4);
	if (!ft_strncmp(command, "unset", len))
		return (5);
	if (!ft_strncmp(command, "env", len))
		return (6);
	if (!ft_strncmp(command, "exit", len))
		return (7);
	return (0);
}