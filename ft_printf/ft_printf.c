/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 16:53:32 by subcho            #+#    #+#             */
/*   Updated: 2022/12/21 21:58:53 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_formatch(char c, va_list ap)
{
	if (c == 'c')
		return (ft_putchar(va_arg(ap, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(ap, char *)));
	else if (c == 'p')
		return (ft_putaddress(va_arg(ap, void *)));
	else if (c == 'd')
		return (ft_putnbr(va_arg(ap, int)));
	else if (c == 'i')
		return (ft_putnbr(va_arg(ap, int)));
	else if (c == 'u')
		return (ft_putunsinednbr(va_arg(ap, unsigned int)));
	else if (c == 'x')
		return (ft_putlowerhex(va_arg(ap, unsigned int)));
	else if (c == 'X')
		return (ft_putupperhex(va_arg(ap, unsigned int)));
	else if (c == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list			ap;
	int				i;
	int				count;
	int				now;

	i = -1;
	count = 0;
	va_start(ap, format);
	while (format[++i])
	{
		if (format[i] == '%')
			now = ft_formatch(format[i++ + 1], ap);
		else
		{
			if (ft_putchar(format[i]) == -1)
				return (-1);
			now = 1;
		}
		if (now == -1)
			return (-1);
		count += now;
	}
	va_end(ap);
	return (count);
}
