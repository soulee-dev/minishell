/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:44:31 by soulee            #+#    #+#             */
/*   Updated: 2022/11/08 20:32:55 by soulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*pdst;
	unsigned char	*psrc;

	pdst = dst;
	psrc = (unsigned char *)src;
	if (dst > src)
	{
		while (len--)
			pdst[len] = psrc[len];
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
