/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 21:31:16 by subcho            #+#    #+#             */
/*   Updated: 2022/12/21 21:58:52 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>

int			ft_printf(const char *format, ...);
int			ft_formatch(char c, va_list ap);
int			ft_putchar(char c);
int			ft_putstr(char *s);
int			ft_putaddress(void *v);
int			ft_putnbr(int n);
int			ft_putunsinednbr(unsigned int n);
int			ft_putlowerhex(unsigned int n);
int			ft_putupperhex(unsigned int n);
int			ft_getaddress(unsigned long long pointer_address);

#endif