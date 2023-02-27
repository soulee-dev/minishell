/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:25:02 by soulee            #+#    #+#             */
/*   Updated: 2023/02/27 23:05:22 by soulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// input, output, heredoc, append, cmd 하나라도 null 일때 error 출력
void	add_element_node(t_cmd_list **cmd_list, int cmd_type, char **str)
{
	char	*cmd;

	if (!*str)
		exit_error("syntax error");
	cmd = ft_strdup(*str);
	if (cmd_type == TYPE_WORD)
		add_cmd_node_back(cmd_list, create_new_cmd_node(TYPE_WORD, cmd));
	if (cmd_type == TYPE_REDIRECT_INPUT)
		add_cmd_node_back(cmd_list, create_new_cmd_node(TYPE_REDIRECT_INPUT, cmd));
	if (cmd_type == TYPE_REDIRECT_OUTPUT)
		add_cmd_node_back(cmd_list, create_new_cmd_node(TYPE_REDIRECT_OUTPUT, cmd));
	if (cmd_type == TYPE_REDIRECT_HEREDOC)
		add_cmd_node_back(cmd_list, create_new_cmd_node(TYPE_REDIRECT_HEREDOC, cmd));
	if (cmd_type == TYPE_REDIRECT_APPEND)
		add_cmd_node_back(cmd_list, create_new_cmd_node(TYPE_REDIRECT_APPEND, cmd));
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

char	*parse_redirection_in(t_cmd_list **cmd_list, char *str)
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
		add_element_node(cmd_list, cmd_type, &file_name);
		return (n_str + len);
	}
	return (str);
}

char	*parse_redirection_out(t_cmd_list **cmd_list, char *str)
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
		add_element_node(cmd_list, cmd_type, &file_name);
		return (n_str + len);
	}
	return (str);
}
