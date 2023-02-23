/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:39:02 by soulee            #+#    #+#             */
/*   Updated: 2022/11/08 18:48:01 by soulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*pdst;
	unsigned char	*psrc;

	pdst = dst;
	psrc = (unsigned char *)src;
	if (!n || dst == src)
		return (dst);
	if (!dst && !src)
		return (0);
	while (n--)
		*pdst++ = *psrc++;
	return (dst);
}
