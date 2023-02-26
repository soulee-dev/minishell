/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:19:10 by soulee            #+#    #+#             */
/*   Updated: 2023/02/26 12:30:13 by soulee           ###   ########.fr       */
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
	while (*s != ' ' && *s != '|' && *s != '>' && *s != '<' && *s++)
		count++;
	if (*s == ' ')
		count++;
	return (count);
}
