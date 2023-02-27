/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:25:02 by soulee            #+#    #+#             */
/*   Updated: 2023/02/27 17:28:32 by soulee           ###   ########.fr       */
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

char	*parse_redirection_in(char delimiter, char *str)
{
	int		len;
	char	*n_str;
	char	*file_name;

	n_str = ft_strchr(str, '<');
	if (n_str && *n_str == '<')
	{
		n_str++;
		if (*n_str == '<')
		{
			n_str++;
			printf("here_doc in\n");
		}
		while (*n_str == ' ')
			n_str++;
		len = ft_strlenbl(n_str);
		file_name = ft_strndup(n_str, len);
		printf("infile : %s\n", file_name);
		free(file_name);
		return (n_str + len);
	}
	return (str);
}

char	*parse_redirection_out(char *str)
{
	int		len;
	char	*n_str;
	char	*file_name;

	n_str = ft_strchr(str, '>');
	if (n_str && *n_str == '>')
	{
		n_str++;
		if (*n_str == '>')
		{
			n_str++;
			printf("append out\n");
		}
		while (*n_str == ' ')
			n_str++;
		len = ft_strlenbl(n_str);
		file_name = ft_strndup(n_str, len);
		printf("outfile : %s\n", file_name);
		free(file_name);
		return (n_str + len);
	}
	return (str);
}
