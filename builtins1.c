/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 21:58:42 by soulee            #+#    #+#             */
/*   Updated: 2023/03/07 18:15:21 by soulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_echo(const char *s, int no_newline)
{
	if (no_newline)
		printf("%s", s);
	else
		printf("%s\n", s);
}

void	command_cd(const char *path)
{
	printf("%s", path);
	chdir(path);
}

void	command_pwd(void)
{
	char	*curr_dir;

	curr_dir = getcwd(NULL, 0);
	printf("%s\n", curr_dir);
	free(curr_dir);
}

void	command_exit(char *str)
{
	long long	num;
	long long	sign;

	num = 0;
	sign = 1;
	while (((int)(*str) >= 9 && (int)(*str) <= 13) || (int)(*str) == 32)
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
		{
			num = num * 10 + (*str - '0');
			str++;
		}
		else
		{
			printf("numeric argument required\n");
			exit(255);
		}
	}
	if (sign * num > INT64_MAX || sign * num < INT64_MIN
	|| (sign == -1 && num == 0))
	{
		printf("numeric argument required\n");
		exit(255);
	}
	exit((unsigned char)(sign * num));
}
