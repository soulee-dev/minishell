/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@studnet.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 21:58:42 by soulee            #+#    #+#             */
/*   Updated: 2023/03/23 18:01:49 by soulee           ###   ########.fr       */
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
}

void	command_cd(const char *path)
{
	chdir(path);
}

void	command_pwd(void)
{
	char	*curr_dir;

	curr_dir = getcwd(NULL, 0);
	ft_printf("%s\n", curr_dir);
	free(curr_dir);
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
			check_long_long(num, (int)sign, *str - '0');
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
