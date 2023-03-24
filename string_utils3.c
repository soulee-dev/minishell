/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:51:38 by soulee            #+#    #+#             */
/*   Updated: 2023/03/24 22:12:03 by soulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_meta_character(const char c)
{
	if (check_is_whitespace(c)
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
