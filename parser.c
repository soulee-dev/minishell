/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 21:48:04 by soulee            #+#    #+#             */
/*   Updated: 2023/02/27 20:49:12 by soulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// input, output, heredoc, append null 일때 error 출력

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

int	parse_pipe(int is_pipe, char c, char **str)
{
	if (c == '|')
	{
		if (str)
			add_element_node(TYPE_WORD, str);
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
		is_pipe = parse_pipe(is_pipe, *line, &str);
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
