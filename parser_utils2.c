/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@studnet.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 01:06:31 by soulee            #+#    #+#             */
/*   Updated: 2023/03/31 16:38:28 by soulee           ###   ########.fr       */
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

char	**convert_args_lst(t_cmd_list *arg_list)
{
	int			i;
	char		**args;
	t_cmd_list	*temp;

	i = 0;
	temp = arg_list;
	args = malloc(sizeof(char *) * (count_cmd_list_node(arg_list, 0) + 1));
	if (!args)
		return (NULL);
	while (arg_list)
	{
		args[i] = ft_strdup(arg_list->cmd);
		i++;
		arg_list = arg_list->next;
	}
	args[i] = NULL;
	clear_cmd_list(&temp);
	return (args);
}

int	check_syntax_error(char *str, int is_pipe, int quotes)
{
	if (!str && is_pipe)
	{
		exit_error("syntax error: pipe");
		return (0);
	}
	if (quotes != 0)
	{
		exit_error("syntax error: unclosed quotes");
		return (0);
	}
	return (1);
}

void	init_parser(char **str, int *quotes, int *is_pipe, int *ret_redirect)
{
	*str = NULL;
	*quotes = 0;
	*is_pipe = 0;
	*ret_redirect = 0;
}
