/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:25:02 by soulee            #+#    #+#             */
/*   Updated: 2023/02/27 20:57:24 by soulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	parse_quotes(char line, int quotes)
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
	int		cmd_type;
	char	*file_name;

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
	int		cmd_type;
	char	*file_name;

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
