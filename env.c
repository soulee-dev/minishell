/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 09:28:50 by soulee            #+#    #+#             */
/*   Updated: 2023/02/26 10:06:28 by soulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char **envp, char *key)
{
	char	*temp;
	char	*result;
	char	*modified_key;

	result = 0;
	modified_key = malloc(sizeof(char) * (ft_strlen(key) + 2));
	ft_strlcpy(modified_key, key, ft_strlen(key) + 2);
	modified_key[ft_strlen(key)] = '=';
	modified_key[ft_strlen(key) + 1] = 0;
	while (*envp)
	{
		temp = ft_strnstr(*envp, modified_key, ft_strlen(*envp));
		if (temp)
			result = temp;
		envp++;
	}
	free(modified_key);
	temp = ft_strchr(result, '=');
	if (temp)
	{
		result = temp;
		result++;
	}
	return (result);
}
