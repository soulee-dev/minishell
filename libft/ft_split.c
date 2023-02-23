/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 20:52:54 by soulee            #+#    #+#             */
/*   Updated: 2022/11/12 18:16:47 by soulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_string(const char *str, int start, int len)
{
	int		i;
	char	*result_str;

	result_str = malloc(sizeof(char) * (len + 1));
	if (!result_str)
		return (NULL);
	i = 0;
	while (str[start + i] != 0 && i < len)
	{
		result_str[i] = str[start + i];
		i++;
	}
	result_str[i] = 0;
	return (result_str);
}

int	count_words(const char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != 0)
	{
		while (str[i] == c)
			i++;
		if (str[i])
			count++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (count);
}

void	iterate_string(char **result_str, const char *str, int *i, char c)
{
	int	count_idx;
	int	prev_idx;
	int	j;

	j = 0;
	count_idx = 0;
	prev_idx = 0;
	while (str[*i] != 0)
	{
		if (str[*i] == c)
		{
			if (count_idx > 0)
				result_str[j++] = get_string(str, prev_idx, count_idx);
			count_idx = 0;
			prev_idx = *i + 1;
		}
		else
			count_idx++;
		(*i)++;
	}
	if (count_idx > 0)
		result_str[j++] = get_string(str, prev_idx, count_idx);
	result_str[j] = 0;
}

char	**freeall(char **strs, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		*ptr_i;
	int		count_len;
	char	**result_str;

	i = 0;
	ptr_i = &i;
	count_len = count_words(s, c);
	result_str = malloc(sizeof(char *) * (count_len + 1));
	if (!result_str)
		return (NULL);
	iterate_string(result_str, s, ptr_i, c);
	i = -1;
	while (++i < count_len)
	{
		if (result_str[i] == 0)
			return (freeall(result_str, count_len));
	}
	return (result_str);
}
