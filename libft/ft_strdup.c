/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:08:28 by soulee            #+#    #+#             */
/*   Updated: 2023/03/09 20:43:46 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dest, const char *src)
{
	char	*ptr;

	ptr = dest;
	while (*src != '\0')
	{
		*dest++ = *src++;
	}
	*dest = 0;
	return (ptr);
}

char	*ft_strdup(const char *src)
{
	char	*str_ptr;

	if (!src)
		return (0);
	str_ptr = malloc(sizeof(char) * ft_strlen(src) + 1);
	if (!str_ptr)
		return (0);
	ft_strcpy(str_ptr, src);
	return (str_ptr);
}
