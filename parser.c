/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 21:48:04 by soulee            #+#    #+#             */
/*   Updated: 2023/03/06 16:51:51 by soulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_redirection(t_cmd_list **cmd_list, char **line, char **str, int *is_parse_error)
{
	if (**line == '<' || **line == '>')
	{
		if (*str)
			add_element_node(cmd_list, TYPE_WORD, str, is_parse_error);
		if (**line == '<')
			*line = parse_redirection_in(cmd_list, *line, is_parse_error);
		else if (**line == '>')
			*line = parse_redirection_out(cmd_list, *line, is_parse_error);
		return (1);
	}
	return (0);
}

int	parse_pipe(t_cmd_list **cmd_list, int is_pipe, char c, char **str, int *is_parse_error)
{
	if (c == '|')
	{
		if (str)
			add_element_node(cmd_list, TYPE_WORD, str, is_parse_error);
		if (is_pipe)
			printf("pipe error");
		is_pipe = 1;
		add_element_node(cmd_list, TYPE_PIPE, 0, is_parse_error);
		return (is_pipe);
	}
	else
	{
		*str = ft_strjoin_char(*str, c);
		is_pipe = 0;
		return (is_pipe);
	}
}

void	parse_envp(t_env_list **node, char **envp)
{
	char		*key;
	int			flag;
	char		*value;

	while (*envp)
	{
		flag = 1;
		key = NULL;
		value = NULL;
		while (**envp)
		{
			if (**envp == '=')
				flag = 0;
			else
			{
				if (flag)
					key = ft_strjoin_char(key, **envp);
				else
					value = ft_strjoin_char(value, **envp);
			}
			(*envp)++;
		}
		add_env_node_back(node, create_new_env_node(key, value));
		envp++;
	}
}

void	parse_dollar_sign(t_cmd_list *cmd_list, t_env_list *env_list)
{
	while (cmd_list)
	{
		if (cmd_list->cmd && ft_strchr(cmd_list->cmd, '$'))
			parse_dollar_sign_loop(cmd_list, env_list);
		cmd_list = cmd_list->next;
	}
}

int	parse_line(t_cmd_list **cmd_list, char *line)
{
	char		*str;
	int			quotes;
	int			is_pipe;
	int			is_parse_error;

	str = NULL;
	quotes = 0;
	is_pipe = 0;
	is_parse_error = 0;
	while (*line)
	{
		quotes = parse_quotes(*line, quotes);
		if (parse_redirection(cmd_list, &line, &str, &is_parse_error))
			continue ;
		is_pipe = parse_pipe(cmd_list, is_pipe, *line, &str, &is_parse_error);
		line++;
	}
	if (str)
		add_element_node(cmd_list, TYPE_WORD, &str, &is_parse_error);
	else
	{
		if (is_pipe)
		{
			exit_error("syntax error");
			is_parse_error = 1;
		}
	}
	if (quotes != 0)
	{
		exit_error("syntax error");
		is_parse_error = 1;
	}
	return (is_parse_error);
}
