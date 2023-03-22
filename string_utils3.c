/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:51:38 by soulee            #+#    #+#             */
/*   Updated: 2023/03/22 17:55:12 by soulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	count_splitted_str(const char **splitted_str)
{
	int	count;

	count = 0;
	while (*splitted_str)
	{
		count++;
		splitted_str++;
	}
	return (count);
}
