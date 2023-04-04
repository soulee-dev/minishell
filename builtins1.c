/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@studnet.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 21:58:42 by soulee            #+#    #+#             */
/*   Updated: 2023/04/04 14:54:28 by soulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_echo(const char **s, int no_newline)
{
	int	quote;

	quote = 0;
	while (*s)
	{
		if (**s == '"')
		{
			quote = 1;
			while (*(*s + quote) && *(*s + quote) != '"')
			{
				ft_putchar_fd(*(*s + quote), 1);
				quote++;
			}
		}
		else
			ft_putstr_fd((char *)*s, 1);
		s++;
		if (*s)
			ft_putchar_fd(' ', 1);
	}
	if (!no_newline)
		ft_putchar_fd('\n', 1);
	g_exit_code = 0;
}

void	command_cd(t_env_list *env_list, const char *path)
{
	char	*temp_path;
	char	*old_path;
	char	*new_path;
	char	**commands;

	commands = malloc(sizeof(char *) * 3);
	temp_path = getcwd(NULL, 0);
	old_path = ft_strjoin_no_free("OLDPWD=", temp_path);
	commands[0] = ft_strdup("export");
	commands[1] = old_path;
	commands[2] = 0;
	command_export(env_list, (const char **)commands);
	free(commands[0]);
	free(old_path);
	free(temp_path);
	chdir(path);
	temp_path = getcwd(NULL, 0);
	new_path = ft_strjoin_no_free("PWD=", temp_path);
	commands[0] = ft_strdup("export");
	commands[1] = new_path;
	commands[2] = 0;
	command_export(env_list, (const char **)commands);
	free(temp_path);
	commands = ft_free_strs(commands);
	g_exit_code = 0;
}

void	command_pwd(void)
{
	char	*curr_dir;

	curr_dir = getcwd(NULL, 0);
	ft_printf("%s\n", curr_dir);
	free(curr_dir);
	g_exit_code = 0;
}

void	command_exit(const char *str)
{
	long long	num;
	long long	sign;
	int			count;

	num = 0;
	sign = 1;
	count = 0;
	preprocess_atoi(&str, &sign);
	while (*str != 0)
	{
		if (count > 18)
			exit_numberic_argument();
		if (*str >= '0' && *str <= '9')
		{
			is_over_long_long(num, (int)sign, *str - '0');
			num = num * 10 + (*str - '0');
			str++;
			count++;
		}
		else
			exit_numberic_argument();
	}
	if (sign == -1 && num == 0)
		exit_numberic_argument();
	exit((unsigned char)(sign * num));
}
