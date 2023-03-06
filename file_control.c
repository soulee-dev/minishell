/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 22:19:41 by subcho            #+#    #+#             */
/*   Updated: 2023/03/05 23:02:55 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	append_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		print_error(file_name);
	return (fd);
}
