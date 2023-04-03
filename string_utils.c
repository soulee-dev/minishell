/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@studnet.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 17:00:14 by soulee            #+#    #+#             */
/*   Updated: 2023/04/03 22:20:15 by soulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_free_str(char *str)
{
	if (str)
		free(str);
	return (NULL);
}

size_t	ft_strlenbl(const char *s)
{
	int		quotes;
	size_t	count;

	count = 0;
	quotes = count_quotes(s[count], 0);
	if (quotes)
	{
		count++;
		while (count_quotes(s[count], quotes))
			count++;
		count++;
	}
	else
	{
		while (*s != ' ' && *s != '|' && *s != '>' && *s != '<' && *s++)
			count++;
		if (*s == ' ')
			count++;
	}
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
	*(p + i) = 0;
	return (org_p);
}

int	is_whitespace(const char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	is_whitespace_str(const char *line)
{
	while (*line)
	{
		if (is_whitespace(*line))
			return (1);
		line++;
	}
	return (0);
}
