/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:11:09 by soulee            #+#    #+#             */
/*   Updated: 2022/11/08 23:04:25 by soulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_digits(int n)
{
	int	count;

	count = 0;
	if (n < 0)
		count++;
	if (n == 0)
		count++;
	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*result_str;

	len = count_digits(n);
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	result_str = malloc(sizeof(char) * (len + 1));
	if (!result_str)
		return (0);
	result_str[len--] = 0;
	if (n < 0)
	{
		result_str[0] = '-';
		n *= -1;
	}
	while (n)
	{
		result_str[len--] = ('0' + (n % 10));
		n /= 10;
	}
	return (result_str);
}
