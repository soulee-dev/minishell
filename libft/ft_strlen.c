/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:19:10 by soulee            #+#    #+#             */
/*   Updated: 2023/02/26 11:42:44 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (*s++)
		count++;
	return (count);
}

size_t	ft_strlenbl(const char *s)
{
	size_t	count;

	count = 0;
	while (*s != ' ' && *s != '|' && *s++)
		count++;
	if (*s == ' ')
		count++;
	return (count);
}