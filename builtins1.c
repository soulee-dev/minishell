/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 21:58:42 by soulee            #+#    #+#             */
/*   Updated: 2023/03/06 16:49:38 by subcho           ###   ########.fr       */
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
	printf("%s", path);
	chdir(path);
}

void	pwd(void)
{
	char	*curr_dir;

	curr_dir = getcwd(NULL, 0);
	printf("%s\n", curr_dir);
	free(curr_dir);
}
