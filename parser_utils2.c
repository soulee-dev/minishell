/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@studnet.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 01:06:31 by soulee            #+#    #+#             */
/*   Updated: 2023/03/31 23:21:50 by soulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_dollar_sign_loop2(t_env_list *env_list, int quotes,
		char *key, char *str)
{
	char	*itoa_code;

	if (quotes != 1)
	{
		if (!ft_strcmp(key, "?"))
		{
			itoa_code = ft_itoa(g_exit_code);
			str = ft_strjoin_free(str, itoa_code);
			free(itoa_code);
		}
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

void	parse_quotes_loop2(t_cmd_list *cmd_list,
		int *i, t_parse_env_lst *parse_env_lst)
{
	int	flag;

	flag = 0;
	if (parse_env_lst->quotes)
	{
		(*i)++;
		while (cmd_list->cmd[*i]
			&& count_quotes(cmd_list->cmd[*i], parse_env_lst->quotes))
			parse_env_lst->str = ft_strjoin_char(
					parse_env_lst->str, cmd_list->cmd[(*i)++]);
		parse_env_lst->quotes = 0;
	}
	else
	{
		while (cmd_list->cmd[*i]
			&& !is_whitespace(cmd_list->cmd[*i])
			&& !count_quotes(cmd_list->cmd[*i], parse_env_lst->quotes))
		{
			parse_env_lst->str = ft_strjoin_char(
					parse_env_lst->str, cmd_list->cmd[(*i)++]);
			flag = 1;
		}
		if (flag)
			(*i)--;
	}
}

void	parse_quotes_loop(t_cmd_list *cmd_list, t_parse_env_lst *parse_env_lst,
						t_cmd_list **arg_list, int *i)
{
	parse_env_lst->quotes = count_quotes(cmd_list->cmd[*i],
			parse_env_lst->quotes);
	if (is_whitespace(cmd_list->cmd[*i])
		&& !parse_env_lst->quotes && parse_env_lst->str)
	{
		add_cmd_node_back(arg_list,
			create_new_cmd_node(0, ft_strdup(parse_env_lst->str), 0));
		parse_env_lst->str = ft_free_str(parse_env_lst->str);
	}
	else
		parse_quotes_loop2(cmd_list, i, parse_env_lst);
}

