/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@studnet.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:25:02 by soulee            #+#    #+#             */
/*   Updated: 2023/04/04 19:05:43 by soulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_element_node(t_cmd_list **cmd_list, int cmd_type, char **str)
{
	char	*cmd;

	if (cmd_type == TYPE_PIPE)
	{
		add_cmd_node_back(cmd_list, create_new_cmd_node(TYPE_PIPE, 0, 0));
		return (1);
	}
	if (!*str)
		return (exit_error("syntax error"));
	if (!is_str_all_blank(*str))
	{
		cmd = ft_strdup(*str);
		add_cmd_node_back(cmd_list, create_new_cmd_node(cmd_type, cmd, 0));
	}
	if (*str)
		*str = ft_free_str(*str);
	return (1);
}

int	count_quotes(const char c, int quotes)
{
	int	result;

	result = quotes;
	if (c == '\'')
	{
		if (quotes == 1)
			result = 0;
		else if (quotes == 2)
			result = 2;
		else
			result = 1;
	}
	else if (c == '\"')
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
		if (!add_element_node(cmd_list, cmd_type, &file_name))
			return (0);
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
		if (!add_element_node(cmd_list, cmd_type, &file_name))
			return (0);
		return (n_str + len);
	}
	return (str);
}

void	parse_dollar_sign_loop(t_cmd_list *cmd_list, t_env_list *env_list)
{
	int		i;
	char	*str;
	char	*key;
	int		quotes;

	i = -1;
	key = 0;
	str = NULL;
	quotes = 0;
	while (++i < (int)(ft_strlen(cmd_list->cmd)))
	{
		quotes = count_quotes(cmd_list->cmd[i], quotes);
		if (cmd_list->cmd[i] == '$')
		{
			while (cmd_list->cmd[++i] && !is_white_meta_char(cmd_list->cmd[i]))
				key = ft_strjoin_char(key, cmd_list->cmd[i]);
			str = parse_dollar_sign_loop2(env_list, quotes, key, str);
			key = ft_free_str(key);
			i--;
		}
		else
			str = ft_strjoin_char(str, cmd_list->cmd[i]);
	}
	cmd_list->cmd = ft_free_str(cmd_list->cmd);
	cmd_list->cmd = str;
}
