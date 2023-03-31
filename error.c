/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@studnet.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:35:34 by soulee            #+#    #+#             */
/*   Updated: 2023/03/31 17:20:44 by soulee           ###   ########.fr       */
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
