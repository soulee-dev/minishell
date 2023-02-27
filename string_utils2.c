/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 22:35:09 by soulee            #+#    #+#             */
/*   Updated: 2023/02/27 22:38:34 by soulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_free(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*result_str;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strndup(s2, ft_strlen(s2)));
	if (!s2)
		return (ft_strndup(s1, ft_strlen(s1)));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result_str = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!result_str)
	{
		free((void *)s1);
		return (NULL);
	}
	result_str[s1_len] = 0;
	ft_strlcpy(result_str, s1, s1_len + 1);
	free((void *)s1);
	ft_strlcpy(result_str + s1_len, (char *)s2, s2_len + 1);
	return (result_str);
}

char	*ft_strjoin_no_free(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*result_str;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strndup(s2, ft_strlen(s2)));
	if (!s2)
		return (ft_strndup(s1, ft_strlen(s1)));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result_str = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!result_str)
		return (NULL);
	result_str[s1_len] = 0;
	ft_strlcpy(result_str, s1, s1_len + 1);
	ft_strlcpy(result_str + s1_len, (char *)s2, s2_len + 1);
	return (result_str);
}
