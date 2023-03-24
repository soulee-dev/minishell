/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:51:38 by soulee            #+#    #+#             */
/*   Updated: 2023/03/24 21:41:03 by soulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_splitted_str(const char **splitted_str)
{
	int	count;

	count = 0;
	while (*splitted_str)
	{
		count++;
		splitted_str++;
	}
	return (count);
}

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
