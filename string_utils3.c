/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:51:38 by soulee            #+#    #+#             */
/*   Updated: 2023/03/25 01:34:39 by soulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_meta_character(const char c)
{
	if (is_whitespace(c)
		|| c == '$'
		|| c == '|'
		|| c == '>'
		|| c == '<'
		|| c == '>'
	)
		return (1);
	return (0);
}

char	**ft_free_strs(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

char	*ft_strdup_free(char *s1, char *s2)
{
	ft_free_str(s1);
	return (ft_strdup(s2));
}
