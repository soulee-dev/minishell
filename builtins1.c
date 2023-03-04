/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 21:58:42 by soulee            #+#    #+#             */
/*   Updated: 2023/03/04 22:53:15 by soulee           ###   ########.fr       */
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
