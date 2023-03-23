/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 16:53:06 by subcho            #+#    #+#             */
/*   Updated: 2022/12/21 21:58:50 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putunsinednbr(unsigned int n)
{
	int			count;
	int			mod;
	int			now;

	count = 0;
	now = 0;
	mod = n % 10 + '0';
	if (n >= 10)
	{
		count = ft_putunsinednbr(n / 10);
		if (count == -1)
			return (-1);
	}
	if (write(1, &mod, 1) == -1)
		return (-1);
	now++;
	return (now + count);
}

int	ft_putlowerhex(unsigned int n)
{
	int			count;
	int			mod;
	int			now;

	count = 0;
	now = 0;
	mod = n % 16;
	if (n >= 16)
	{
		count = ft_putlowerhex(n / 16);
		if (count == -1)
			return (-1);
	}
	if (write(1, &("0123456789abcdef"[mod]), 1) == -1)
		return (-1);
	now++;
	return (now + count);
}

int	ft_putupperhex(unsigned int n)
{
	int			count;
	int			mod;
	int			now;

	count = 0;
	now = 0;
	mod = n % 16;
	if (n >= 16)
	{
		count = ft_putupperhex(n / 16);
		if (count == -1)
			return (-1);
	}
	if (write(1, &("0123456789ABCDEF"[mod]), 1) == -1)
		return (-1);
	now++;
	return (now + count);
}
