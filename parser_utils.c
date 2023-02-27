/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:25:02 by soulee            #+#    #+#             */
/*   Updated: 2023/02/27 18:29:05 by soulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_str(char **str)
{
	free(*str);
	*str = 0;
}

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
	int		len;
	char	*n_str;
	char	*file_name;
	int		cmd_type;

	cmd_type = TYPE_REDIRECT_INPUT;
	n_str = ft_strchr(str, '<');
	if (n_str && *n_str == '<')
	{
		n_str++;
		if (*n_str == '<')
		{
			n_str++;
			cmd_type = TYPE_REDIRECT_HEREDOC;
		}
		while (*n_str == ' ')
			n_str++;
		len = ft_strlenbl(n_str);
		file_name = ft_strndup(n_str, len);
		add_element_node(cmd_type, &file_name);
		return (n_str + len);
	}
	return (str);
}

char	*parse_redirection_out(char *str)
{
	int		len;
	char	*n_str;
	char	*file_name;
	int		cmd_type;

	
	cmd_type = TYPE_REDIRECT_OUTPUT;
	n_str = ft_strchr(str, '>');
	if (n_str && *n_str == '>')
	{
		n_str++;
		if (*n_str == '>')
		{
			n_str++;
			cmd_type = TYPE_REDIRECT_APPEND;
		}
		while (*n_str == ' ')
			n_str++;
		len = ft_strlenbl(n_str);
		file_name = ft_strndup(n_str, len);
		add_element_node(cmd_type, &file_name);
		return (n_str + len);
	}
	return (str);
}
