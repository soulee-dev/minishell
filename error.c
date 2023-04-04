/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:35:34 by soulee            #+#    #+#             */
/*   Updated: 2023/04/04 19:04:47 by subcho           ###   ########.fr       */
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
	g_exit_code = 1;
}

void	cmd_not_found_error(char *cmd)
{
	ft_putstr_fd("🐈: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	g_exit_code = 127;
	exit(127);
}

void	print_export_error(char *identifier)
{
	ft_putstr_fd("🐈: ", 2);
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(identifier, 2);
	ft_putendl_fd("\': not a vaild identifier", 2);
	g_exit_code = 1;
}
