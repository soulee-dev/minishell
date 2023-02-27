/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 17:00:14 by soulee            #+#    #+#             */
/*   Updated: 2023/02/27 22:14:05 by soulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_str(char **str)
{
	free(*str);
	*str = NULL;
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

char	*ft_strndup(const char *s1, size_t n)
{
	char	*p;
	char	*org_p;
	size_t	i;

	s1 = (char *)s1;
	i = 0;
	if (!n)
		return (0);
	p = (char *)malloc(sizeof(char) * n + 1);
	if (!p)
	{
		free((void *)s1);
		return (0);
	}
	org_p = p;
	while (*(s1 + i) && i < n)
	{
		*(p + i) = *(s1 + i);
		i++;
	}
	*(p + i) = NULL;
	return (org_p);
}

char	*ft_strjoin_char(char const *s1, char s2)
{
	int		s1_len;
	char	*result_str;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(&s2));
	if (!s2)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	result_str = malloc(sizeof(char) * (s1_len + 1 + 1));
	if (!result_str)
		return (NULL);
	ft_strlcpy(result_str, s1, s1_len + 1);
	ft_strlcpy(result_str + s1_len, &s2, 2);
	result_str[s1_len + 1] = 0;
	free((void *)s1);
	return (result_str);
}
