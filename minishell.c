/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:24:12 by soulee            #+#    #+#             */
/*   Updated: 2023/02/28 04:21:12 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_ascii_art(void)
{
	printf("   ___     _ _ _        _   ___ _        _ _ \n");
	printf("  / __|_ _(_) | |___ __| | / __| |_  ___| | |\n");
	printf(" | (_ | '_| | | / -_) _` | \\__ \\ ' \\/ -_) | |\n");
	printf("  \\___|_| |_|_|_\\___\\__,_| |___/_||_\\___|_|_|\n");
	printf("\n");
}

int	check_whitespace(char *line)
{
	while (*line)
	{
		if (*line == 32 || (*line >= 9 && *line <= 13))
			return (1);
		line++;
	}
	return (0);
}

int	main(int argc, char *argv[], char **envp)
{
	char			*line;
	int				status;
	t_env_list		*env_list;
	t_cmd_list		*cmd_list;
	int				count_pipe;

	line = NULL;
	env_list = NULL;
	parse_envp(&env_list, envp);
	print_ascii_art();
	while (1)
	{
		line = readline("GrilledShell $ ");
		if (!line)
			break ;
		if (*line != '\0')
		{
			add_history(line);
			cmd_list = parse_line(&cmd_list, line);
			// iter_node(cmd_list);
			status = execute_cmd(cmd_list, convert_env_list_to_arr(env_list), count_cmd_list_node(cmd_list, TYPE_PIPE) + 1);
			clear_cmd_list(&cmd_list);
		}
		free(line);
		line = NULL;
	}
}
