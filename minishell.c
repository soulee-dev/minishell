/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@studnet.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:24:12 by soulee            #+#    #+#             */
/*   Updated: 2023/03/30 22:16:14 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_minishell(int argc, char **line,
			t_env_list **env_list, t_cmd_list **cmd_list)
{
	if (argc != 1)
	{
		print_error("arguments error");
		exit(1);
	}
	*line = NULL;
	*env_list = NULL;
	*cmd_list = NULL;
	ft_printf("\nMewww  |\\      _,,,—,,_        \n");
	ft_printf("       /,`.-'`'   ._  \\-;;,_    \n");
	ft_printf("      |,4-  ) )_   .;.(  `'-'   \n");
	ft_printf("     '—''(_/._)-'(_\\_)     Mewww…   \n");
	ft_printf("  ___     _       _   _    _ _   "
		"                  ___ _        _ _ \n");
	ft_printf(" / __| __| |_  _ (_)_(_)__| (_)_ _"
		"  __ _ ___ _ _  / __| |_  ___| | |\n");
	ft_printf(" \\__ \\/ _| ' \\| '_/ _ \\/ _` | | "
		"' \\/ _` / -_) '_| \\__ \\ ' \\/ -_) | |\n");
	ft_printf(" |___/\\__|_||_|_| \\___/\\__,_|_"
		"|_||_\\__, \\___|_|   |___/_||_\\___|_|_|\n");
	ft_printf("                                   "
		"|___/                            \n");
	ft_printf("                                       "
		"       Mewww…                      \n\n");
}

int	main(int argc, char *argv[], char **envp)
{
	char			*line;
	t_env_list		*env_list;
	t_cmd_list		*cmd_list;

	init_minishell(argc, &line, &env_list, &cmd_list);
	parse_envp(&env_list, envp);
	while (1)
	{
		line = readline("🐈 $ ");
		if (!line)
			break ;
		if (*line != '\0')
		{
			add_history(line);
			if (!parser(&cmd_list, &env_list, line))
				continue ;
			g_exit_code = execute_main(cmd_list, env_list,
					count_cmd_list_node(cmd_list, TYPE_PIPE) + 1);
			clear_cmd_list(&cmd_list);
			ft_printf("code : %d\n", g_exit_code);
		}
		line = ft_free_str(line);
	}
}
