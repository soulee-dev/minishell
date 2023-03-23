/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 21:40:13 by subcho            #+#    #+#             */
/*   Updated: 2022/12/21 21:58:53 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	if (write(1, &c, 1) == -1)
		return (-1);
	return (1);
}

int	ft_putstr(char *s)
{
	int	count;

	count = 0;
	if (!s)
		return (write(1, &"(null)", 6));
	while (s[count])
	{
		if (write(1, &s[count], 1) == -1)
			return (-1);
		count++;
	}
	return (count);
}

int	ft_putaddress(void *v)
{
	unsigned long long	pointer_address;
	int					count;
	int					now;

	count = 2;
	pointer_address = (unsigned long long)v;
	if (write(1, "0x", 2) == -1)
		return (-1);
	now = ft_getaddress(pointer_address);
	if (now == -1)
		return (-1);
	count += now;
	return (count);
}

int	ft_getaddress(unsigned long long pointer_address)
{
	int			count;
	int			mod;
	int			now;

	now = 0;
	count = 0;
	mod = pointer_address % 16;
	if (pointer_address >= 16)
	{
		count = ft_getaddress(pointer_address / 16);
		if (count == -1)
			return (-1);
	}
	if (write(1, &("0123456789abcdef"[mod]), 1) == -1)
		return (-1);
	now++;
	return (now + count);
}

int	ft_putnbr(int n)
{
	int	now;
	int	mod;
	int	count;

	now = 0;
	count = 0;
	if (n < 0 && ++now)
	{
		if (n == -2147483648)
			return (write(1, "-2147483648", 11));
		if (write(1, "-", 1) == -1)
			return (-1);
		n *= -1;
	}
	mod = n % 10 + '0';
	if (n >= 10)
	{
		count = ft_putnbr(n / 10);
		if (count == -1)
			return (-1);
	}
	if (write(1, &mod, 1) == -1)
		return (-1);
	now++;
	return (now + count);
}
