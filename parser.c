/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 21:48:04 by soulee            #+#    #+#             */
/*   Updated: 2023/02/27 17:26:54 by soulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		quotes = parse_set_quotes(*line, quotes);
		if (*line == '<' || *line == '>')
		{
			if (str)
			{
				printf("%s\n", str);
				ft_free_str(&str);
			}
			if (*line == '<')
				line = parse_redirection_in(line);
			else if (*line == '>')
				line = parse_redirection_out(line);
			continue ;
		}
		if (*line == '|')
		{
			if (str)
			{
				printf("%s\n", str);
				ft_free_str(&str);
			}
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
	{
		printf("%s\n", str);
		ft_free_str(&str);
	}
	else
	{
		if (is_pipe)
			printf("pipe error");
	}
	if (quotes != 0)
		printf("quote error");
}
