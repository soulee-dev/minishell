/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 21:48:04 by soulee            #+#    #+#             */
/*   Updated: 2023/02/26 12:09:30 by subcho           ###   ########.fr       */
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
	result_str[s1_len + 1] = 0;
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

char	*parse_redirection_in(char *str)
{
	char	*n_str;
	char	*file_name;
	int		len;

	n_str = ft_strchr(str, '<');
	if (n_str && *n_str == '<')
	{
		n_str++;
		if (*n_str == '<')
		{
			printf("here_doc in\n");
			return (str);
		}
		while (*n_str == ' ')
			n_str++;
		len = ft_strlenbl(n_str);
		file_name = ft_strndup(n_str, len);
		printf("infile : %s\n",file_name);
		free(file_name);
		return (n_str + len);
	}
	return (str);
}

char	*parse_redirection_out(char *str)
{
	char	*n_str;
	char	*file_name;
	int		len;

	n_str = ft_strchr(str, '>');
	if (n_str && *n_str == '>')
	{
		n_str++;
		if (*n_str == '>')
		{
			printf("here_doc out\n");
			return (str);
		}
		while (*n_str == ' ')
			n_str++;
		len = ft_strlenbl(n_str);
		file_name = ft_strndup(n_str, len);
		printf("outfile : %s\n",file_name);
		free(file_name);
		return (n_str + len);
	}
	return (str);
}

void	parse_line(char *line)
{
	char	*str;
	int		quotes;
	int		is_pipe;
	int		is_redir;

	quotes = 0;
	is_pipe = 0;
	str = 0;
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
		}
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