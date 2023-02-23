/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:08:28 by soulee            #+#    #+#             */
/*   Updated: 2022/11/18 09:10:18 by soulee           ###   ########.fr       */
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

	str_ptr = malloc(sizeof(char) * ft_strlen(src) + 1);
	if (!str_ptr)
		return (0);
	ft_strcpy(str_ptr, src);
	return (str_ptr);
}
