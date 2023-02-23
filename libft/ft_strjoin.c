/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:14:13 by soulee            #+#    #+#             */
/*   Updated: 2022/11/08 22:03:23 by soulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		i;
	int			len;
	int			tmp;
	char		*result_str;

	i = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	result_str = malloc(sizeof(char) * (len + 1));
	if (!result_str)
		return (0);
	while (i < ft_strlen(s1))
	{
		result_str[i] = s1[i];
		i++;
	}
	tmp = i;
	i = 0;
	while (i < ft_strlen(s2))
	{
		result_str[tmp + i] = s2[i];
		i++;
	}
	result_str[tmp + i] = 0;
	return (result_str);
}
