/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 01:06:31 by soulee            #+#    #+#             */
/*   Updated: 2023/03/27 01:33:16 by soulee           ###   ########.fr       */
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

char	*parse_dollar_sign_loop2(t_env_list *env_list, int quotes,
		char *key, char *str)
{
	if (quotes != 1)
	{
		if (!ft_strcmp(key, "?"))
			str = ft_strjoin_free(str, ft_itoa(g_exit_code));
		else
			str = ft_strjoin_free(str, ft_getenv(env_list, key));
	}
	else
	{
		str = ft_strjoin_char(str, '$');
		str = ft_strjoin_free(str, key);
	}
	return (str);
}
