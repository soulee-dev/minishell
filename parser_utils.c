/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:25:02 by soulee            #+#    #+#             */
/*   Updated: 2023/03/10 00:55:53 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_element_node(t_cmd_list **cmd_list, int cmd_type, char **str)
{
	char	*cmd;

	if (cmd_type == TYPE_PIPE)
	{
		add_cmd_node_back(cmd_list, create_new_cmd_node(TYPE_PIPE, 0));
		return ;
	}
	if (!*str)
		exit_error("syntax error");
	if (!is_str_all_blank(*str))
	{
		cmd = ft_strdup(*str);
		add_cmd_node_back(cmd_list, create_new_cmd_node(cmd_type, cmd));
	}
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

void	parse_dollar_sign_loop(t_cmd_list *cmd_list, t_env_list *env_list)
{
	int		i;
	char	*str;
	char	*key;

	i = 0;
	key = 0;
	str = NULL;
	while (i < ft_strlen(cmd_list->cmd))
	{
		if (cmd_list->cmd[i] == '$')
		{
			i++;
			while (cmd_list->cmd[i]
				&& !check_is_whitespace(cmd_list->cmd[i]))
				key = ft_strjoin_char(key, cmd_list->cmd[i++]);
			str = ft_strjoin_free(str, ft_getenv(env_list, key));
			ft_free_str(&key);
		}
		str = ft_strjoin_char(str, cmd_list->cmd[i]);
		i++;
	}
	ft_free_str(&(cmd_list->cmd));
	cmd_list->cmd = str;
}
