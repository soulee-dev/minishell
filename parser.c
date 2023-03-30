/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 21:48:04 by soulee            #+#    #+#             */
/*   Updated: 2023/03/29 23:12:14 by soulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_redirection(t_cmd_list **cmd_list, char **line, char **str)
{
	if (**line == '<' || **line == '>')
	{
		if (*str)
		{
			if (!add_element_node(cmd_list, TYPE_WORD, str))
				return (-1);
		}
		if (**line == '<')
		{
			*line = parse_redirection_in(cmd_list, *line);
			if (!*line)
				return (-1);
		}
		else if (**line == '>')
		{
			*line = parse_redirection_out(cmd_list, *line);
			if (!*line)
				return (-1);
		}
		return (1);
	}
	return (0);
}

int	parse_pipe(t_cmd_list **cmd_list, int is_pipe, char c, char **str)
{
	if (c == '|')
	{
		if (str && *str)
			add_element_node(cmd_list, TYPE_WORD, str);
		if (is_pipe)
		{
			exit_error("syntax error: pipe error");
			return (-1);
		}
		is_pipe = 1;
		add_element_node(cmd_list, TYPE_PIPE, 0);
		return (is_pipe);
	}
	else
	{
		*str = ft_strjoin_char(*str, c);
		is_pipe = 0;
		return (is_pipe);
	}
}

void	parse_quotes(t_cmd_list *cmd_list)
{
	int			i;
	char		*str;
	int			quotes;
	t_cmd_list	*arg_list;

	while (cmd_list)
	{
		if (cmd_list->cmd_type != TYPE_WORD)
		{
			cmd_list = cmd_list->next;
			continue ;
		}
		i = -1;
		str = 0;
		quotes = 0;
		arg_list = 0;
		while (++i < ft_strlen(cmd_list->cmd))
		{
			quotes = count_quotes(cmd_list->cmd[i], quotes);
			if (is_whitespace(cmd_list->cmd[i]))
			{
				if (!quotes)
				{
					if (str)
						add_cmd_node_back(&arg_list, create_new_cmd_node(0, ft_strdup(str), 0));
					str = ft_free_str(str);
				}
			}
			else
			{
				if (quotes)
				{
					i++;
					while (cmd_list->cmd[i]
						&& count_quotes(cmd_list->cmd[i], quotes))
						str = ft_strjoin_char(str, cmd_list->cmd[(i)++]);
					quotes = 0;
				}
				else
				{
					while (cmd_list->cmd[i]
						&& !is_whitespace(cmd_list->cmd[i])
						&& !count_quotes(cmd_list->cmd[i], quotes))
						str = ft_strjoin_char(str, cmd_list->cmd[i++]);
					i--;
				}
			}
		}
		if (str)
			add_cmd_node_back(&arg_list, create_new_cmd_node(0, ft_strdup(str), 0));
		str = ft_free_str(str);
		cmd_list->args = convert_args_lst(arg_list);
		cmd_list = cmd_list->next;
	}
}

void	parse_dollar_sign(t_cmd_list *cmd_list, t_env_list *env_list)
{
	while (cmd_list)
	{
		if (cmd_list->cmd && ft_strchr(cmd_list->cmd, '$'))
			parse_dollar_sign_loop(cmd_list, env_list);
		cmd_list = cmd_list->next;
	}
}

t_cmd_list	*parse_line(t_cmd_list **cmd_list, char *line)
{
	char	*str;
	int		quotes;
	int		is_pipe;
	int		ret_redirection;

	str = NULL;
	quotes = 0;
	is_pipe = 0;
	ret_redirection = 0;
	while (*line)
	{
		quotes = count_quotes(*line, quotes);
		ret_redirection = parse_redirection(cmd_list, &line, &str);
		if (ret_redirection == -1)
			return (0);
		else if (ret_redirection == 1)
			continue ;
		is_pipe = parse_pipe(cmd_list, is_pipe, *line, &str);
		if (is_pipe == -1)
			return (0);
		line++;
	}
	if (str)
	{
		if (!add_element_node(cmd_list, TYPE_WORD, &str))
			return (0);
	}
	else
	{
		if (is_pipe)
		{
			exit_error("syntax error: pipe");
			return (0);
		}
	}
	if (quotes != 0)
	{
		exit_error("syntax error: unclosed quotes");
		return (0);
	}
	return (*cmd_list);
}
