/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:24:12 by soulee            #+#    #+#             */
/*   Updated: 2023/02/27 22:43:35 by soulee           ###   ########.fr       */
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
	t_env_list		*env_list;

	line = NULL;
	env_list = NULL;
	parse_envp(&env_list, envp);
	print_ascii_art();
	while (1)
	{
		line = readline("🔥🐚 $ ");
		if (!line)
			break ;
		if (*line != '\0')
		{
			add_history(line);
			parse_line(line);
		}
		free(line);
		line = NULL;
	}
}
