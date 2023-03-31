/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@studnet.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 21:53:35 by soulee            #+#    #+#             */
/*   Updated: 2023/03/31 23:05:04 by soulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_ambigous_redirect(t_cmd_list *cmd_list)
{
	char	**args;

	while (cmd_list)
	{
		if (!(*cmd_list->args))
		{
			if (cmd_list->cmd_type == TYPE_WORD)
			{
				args = malloc(sizeof(char *) * 2);
				if (!args)
					return (exit_error("malloc error"));
				if (cmd_list->args)
					ft_free_strs(cmd_list->args);
				args[0] = ft_strdup("");
				args[1] = 0;
				cmd_list->args = args;
				cmd_list->cmd = ft_strdup(args[0]);
			}
			if (cmd_list->cmd_type != TYPE_PIPE
				&& cmd_list->cmd_type != TYPE_WORD)
				return (exit_error("ambiguous redirect"));
		}
		cmd_list = cmd_list->next;
	}
	return (1);
}

int	parser(t_cmd_list **cmd_list, t_env_list **env_list, char *line)
{
	*cmd_list = parse_line(cmd_list, line);
	if (!cmd_list)
	{
		clear_cmd_list(cmd_list);
		return (0);
	}
	parse_dollar_sign(*cmd_list, *env_list);
	parse_quotes(*cmd_list);
	if (!check_ambigous_redirect(*cmd_list))
	{
		clear_cmd_list(cmd_list);
		return (0);
	}
	return (1);
}

int	parse_line_loop(t_cmd_list **cmd_list, t_parse_env_lst *parse_env_lst,
		char **line, int *is_pipe)
{
	int		ret_redirect;

	parse_env_lst->quotes = count_quotes(**line, parse_env_lst->quotes);
	if (!parse_env_lst->quotes)
	{
		ret_redirect = parse_redirection(
				cmd_list, line, &(parse_env_lst->str));
		if (ret_redirect == -1)
			return (-1);
		else if (ret_redirect == 1)
			return (0);
		*is_pipe = parse_pipe(
				cmd_list, *is_pipe, **line, &(parse_env_lst->str));
		if (*is_pipe == -1)
			return (-1);
	}
	else
		parse_env_lst->str = ft_strjoin_char(parse_env_lst->str, **line);
	return (1);
}
