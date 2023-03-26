/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 21:48:04 by soulee            #+#    #+#             */
/*   Updated: 2023/03/27 01:14:33 by soulee           ###   ########.fr       */
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
		add_element_node(cmd_list, TYPE_PIPE, 0);
		return (is_pipe);
	}
	else
	{
		*str = ft_strjoin_char(*str, c);
		is_pipe = 0;
		return (is_pipe);
	}
}

void	parse_quotes(t_cmd_list *cmd_list)
{
	int		i;
	int		quotes;
	char	*str;

	while (cmd_list)
	{
		i = -1;
		str = 0;
		quotes = 0;
		while (++i < ft_strlen(cmd_list->cmd))
		{
			quotes = count_quotes(cmd_list->cmd[i], quotes);
			str = parse_quotes_loop(cmd_list, &i, str, &quotes);
		}
		printf("%s\n", str);
		cmd_list = cmd_list->next;
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
		quotes = count_quotes(*line, quotes);
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
			exit_error("syntax error: pipe");
	}
	if (quotes != 0)
		exit_error("syntax error: unclosed quotes");
	return (*cmd_list);
}
