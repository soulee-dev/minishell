/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 21:48:04 by soulee            #+#    #+#             */
/*   Updated: 2023/02/27 18:57:37 by soulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// input, output, heredoc, append null 일때 error 출력
void	add_element_node(int cmd_type, char **str)
{
	if (cmd_type == TYPE_WORD)
		printf("cmd: %s\n", *str);
	if (cmd_type == TYPE_REDIRECT_INPUT)
		printf("input: %s\n", *str);
	if (cmd_type == TYPE_REDIRECT_OUTPUT)
		printf("output: %s\n", *str);
	if (cmd_type == TYPE_REDIRECT_HEREDOC)
		printf("herdoc: %s\n", *str);
	if (cmd_type == TYPE_REDIRECT_APPEND)
		printf("append: %s\n", *str);
	if (*str)
		ft_free_str(str);
}

int	parse_redirection(char **line, char **str)
{
	if (**line == '<' || **line == '>')
	{
		if (*str)
			add_element_node(TYPE_WORD, str);
		if (**line == '<')
			*line = parse_redirection_in(*line);
		else if (**line == '>')
			*line = parse_redirection_out(*line);
		return (1);
	}
	return (0);
}

void	parse_line(char *line)
{
	char	*str;
	int		quotes;
	int		is_pipe;

	str = 0;
	quotes = 0;
	is_pipe = 0;
	while (*line)
	{
		quotes = parse_quotes(*line, quotes);
		if (parse_redirection(&line, &str))
			continue ;
		if (*line == '|')
		{
			if (str)
				add_element_node(TYPE_WORD, &str);
			if (is_pipe)
				printf("pipe error");
			is_pipe = 1;
		}
		else
		{
			str = ft_strjoin_char(str, *line);
			is_pipe = 0;
		}
		line++;
	}
	if (str)
		add_element_node(TYPE_WORD, &str);
	else
	{
		if (is_pipe)
			printf("pipe error");
	}
	if (quotes != 0)
		printf("quote error");
}
