/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:51:38 by soulee            #+#    #+#             */
/*   Updated: 2023/04/03 19:23:13 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_meta_character(const char c)
{
	if (c == '$'
		|| c == '|'
		|| c == '>'
		|| c == '<'
		|| c == '>'
		|| c == '\''
		|| c == '\"'
	)
		return (1);
	return (0);
}

int	is_white_meta_char(const char c)
{
	if (is_whitespace(c)
		|| c == '$'
		|| c == '|'
		|| c == '>'
		|| c == '<'
		|| c == '>'
		|| c == '\''
		|| c == '\"'
		|| c == '.'
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

int	ft_is_string(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]))
		return (0);
	while (str[++i])
	{
		if (!ft_isalnum(str[i]))
			return (0);
	}
	return (1);
}
