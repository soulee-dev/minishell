/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 21:48:04 by soulee            #+#    #+#             */
/*   Updated: 2023/02/26 08:16:50 by soulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_char(char const *s1, char s2)
{
	int		s1_len;
	char	*result_str;
	
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(&s2));
	if (!s2)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	result_str = malloc(sizeof(char) * (s1_len + 1 + 1));
	if (!result_str)
		return (NULL);
	ft_strlcpy(result_str, s1, s1_len + 1);
	ft_strlcpy(result_str + s1_len, &s2, 2);
	return (result_str);
}

void	ft_free_str(char **str)
{
	free(*str);
	*str = 0;
}

int	parse_set_quotes(char line, int quotes)
{
	int	result;
	
	result = quotes;
	if (line == '\'')
	{
		if (quotes == 1)
			result = 0;
		else if (quotes == 2)
			result = 2;
		else
			result = 1;
	}
	else if (line == '\"')
	{
		if (quotes == 2)
			result = 0;
		else if (quotes == 1)
			result = 1;
		else
			result = 2;
	}
	return (result);
}

void	parse_redirection(char *str)
{
	str = ft_strchr(str, '<');
	if (str)
	{
		str++;
		if (*str == '<')
			// <<
		else
			//공백 전까지 infile name
	}
	
}

void	parse_line(char *line)
{
	char	*str;
	int		quotes;
	int		is_pipe;

	quotes = 0;
	is_pipe = 0;
	while (*line)
	{
		quotes = parse_set_quotes(*line, quotes);
		if (*line == '|')
		{
			if (str)
			{
				printf("%s\n", str);
				ft_free_str(&str);
			}
			else
				printf("pipe error");
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
	if (quotes != 0)
	{
		printf("quote error");
	}
}