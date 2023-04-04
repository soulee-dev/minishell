/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@studnet.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 21:48:04 by soulee            #+#    #+#             */
/*   Updated: 2023/04/04 21:21:00 by soulee           ###   ########.fr       */
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
	int				i;
	t_cmd_list		*arg_list;
	t_parse_env_lst	parse_env_lst;

	while (cmd_list)
	{
		i = -1;
		parse_env_lst.str = 0;
		parse_env_lst.quotes = 0;
		arg_list = 0;
		while (++i < (int)(ft_strlen(cmd_list->cmd)))
		{
			parse_quotes_loop(cmd_list, &parse_env_lst,
				&arg_list, &i);
		}
		if (parse_env_lst.str)
			add_cmd_node_back(&arg_list,
				create_new_cmd_node(0, ft_strdup(parse_env_lst.str), 0));
		parse_env_lst.str = ft_free_str(parse_env_lst.str);
		cmd_list->args = convert_args_lst(arg_list);
		free(cmd_list->cmd);
		cmd_list->cmd = ft_strdup(cmd_list->args[0]);
		cmd_list = cmd_list->next;
	}
}

void	parse_dollar_sign(t_cmd_list *cmd_list, t_env_list *env_list)
{
	while (cmd_list)
	{
		if (cmd_list->cmd && ft_strchr(cmd_list->cmd, '$')
			&& cmd_list->cmd_type != TYPE_REDIRECT_HEREDOC)
			parse_dollar_sign_loop(cmd_list, env_list);
		cmd_list = cmd_list->next;
	}
}

t_cmd_list	*parse_line(t_cmd_list **cmd_list, char *line)
{
	int					is_pipe;
	t_parse_env_lst		parse_env_lst;
	int					ret_parser;

	parse_env_lst.quotes = 0;
	parse_env_lst.str = NULL;
	is_pipe = 0;
	while (*line)
	{
		ret_parser = parse_line_loop(cmd_list,
				&parse_env_lst, &line, &is_pipe);
		if (ret_parser == 0)
			continue ;
		else if (ret_parser == -1)
			return (clear_return_zero(cmd_list));
		line++;
	}
	if (parse_env_lst.str
		&& !add_element_node(cmd_list, TYPE_WORD, &parse_env_lst.str))
		return (clear_return_zero(cmd_list));
	if (!check_syntax_error(parse_env_lst.str, is_pipe, parse_env_lst.quotes))
		return (clear_return_zero(cmd_list));
	return (*cmd_list);
}
