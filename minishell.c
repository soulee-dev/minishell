/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:24:12 by soulee            #+#    #+#             */
/*   Updated: 2023/02/23 22:46:47 by soulee           ###   ########.fr       */
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

int	check_whitespace(char *str)
{
	while (*str)
	{
		if (*str == 32 || (*str >= 9 && *str <= 13))
			return (1);
		str++;
	}
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	struct termios	term;
	char			*line;

	print_ascii_art();
	while (1)
	{
		line = readline("GrilledShell $ ");
		if (!line)
			break ;
		if (*line != '\0')
			add_history(line);
		if (*line != '\0' && !check_whitespace(line))
		{
			// printf("%s", line);
		}
		free(line);
	}
}
