/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:28:37 by soulee            #+#    #+#             */
/*   Updated: 2023/03/25 01:35:40 by soulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_numberic_argument(void)
{
	ft_printf("numeric argument required\n");
	exit(255);
}

int	is_over_long_long(long long sum, int sign, int num)
{
	if (sum == 922337203685477580)
	{
		if (sign == 1)
		{
			if (num > 7)
				exit_numberic_argument();
		}
		else
		{
			if (num > 8)
				exit_numberic_argument();
		}
	}
	return (1);
}

void	preprocess_atoi(const char **str, long long *sign)
{
	if (!*str)
		exit(0);
	while (((int)(**str) >= 9 && (int)(**str) <= 13) || (int)(**str) == 32)
		(*str)++;
	if (**str == '-')
		*sign = -1;
	if (**str == '+' || **str == '-')
		(*str)++;
}
