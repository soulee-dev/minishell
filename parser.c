/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 21:48:04 by soulee            #+#    #+#             */
/*   Updated: 2023/02/27 23:06:45 by soulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_redirection(t_cmd_list **cmd_list, char **line, char **str)
{
	if (**line == '<' || **line == '>')
	{
		if (*str)
			add_element_node(cmd_list, TYPE_WORD, str);
		if (**line == '<')
			*line = parse_redirection_in(cmd_list, *line);
		else if (**line == '>')
			*line = parse_redirection_out(cmd_list, *line);
		return (1);
	}
	return (0);
}

int	parse_pipe(t_cmd_list **cmd_list, int is_pipe, char c, char **str)
{
	if (c == '|')
	{
		if (str)
			add_element_node(cmd_list, TYPE_WORD, str);
		if (is_pipe)
			printf("pipe error");
		is_pipe = 1;
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

t_cmd_list	*parse_line(t_cmd_list **cmd_list, char *line)
{
	char		*str;
	int			quotes;
	int			is_pipe;

	str = NULL;
	quotes = 0;
	is_pipe = 0;
	while (*line)
	{
		quotes = parse_quotes(*line, quotes);
		if (parse_redirection(cmd_list, &line, &str))
			continue ;
		is_pipe = parse_pipe(cmd_list, is_pipe, *line, &str);
		line++;
	}
	if (str)
		add_element_node(cmd_list, TYPE_WORD, &str);
	else
	{
		if (is_pipe)
			exit_error("syntax error");
	}
	if (quotes != 0)
		exit_error("syntax error");
	return (*cmd_list);
}
