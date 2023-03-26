/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 01:06:31 by soulee            #+#    #+#             */
/*   Updated: 2023/03/27 01:15:22 by soulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_quotes_loop(t_cmd_list *cmd_list, int *i, char *str, int *quotes)
{
	if (*quotes)
	{
		(*i)++;
		while (cmd_list->cmd[*i]
			&& count_quotes(cmd_list->cmd[*i], *quotes))
			str = ft_strjoin_char(str, cmd_list->cmd[(*i)++]);
		*quotes = 0;
	}
	else
	{
		while (cmd_list->cmd[*i]
			&& !count_quotes(cmd_list->cmd[*i], *quotes))
			str = ft_strjoin_char(str, cmd_list->cmd[(*i)++]);
	}
	return (str);
}
