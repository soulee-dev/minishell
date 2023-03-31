/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:35:34 by soulee            #+#    #+#             */
/*   Updated: 2023/03/31 19:40:08 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_error(char *error_message)
{
	ft_putendl_fd(error_message, 2);
	return (0);
}

void	print_error(char *msg)
{
	perror(msg);
}

void	cmd_not_found_error(char *cmd)
{
	write(2, "🐈: ", ft_strlen("🐈: "));
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found", 19);
	write(2, "\n", 1);
	g_exit_code = 127;
	exit(127);
}
