/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 21:48:04 by soulee            #+#    #+#             */
/*   Updated: 2023/02/25 23:09:22 by soulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_char(char const *s1, char s2)
{
	int		s1_len;
	char	*result_str;
	
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(&s2));
	if (!s2)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	result_str = malloc(sizeof(char) * (s1_len + 1 + 1));
	if (!result_str)
		return (NULL);
	ft_strlcpy(result_str, s1, s1_len + 1);
	ft_strlcpy(result_str + s1_len, &s2, 2);
	return (result_str);
}

void	check_redirection(int const *in_redirect, int const *out_redirect)
{
	if (*in_redirect == 1)
		printf("<\n");
	else if (*in_redirect == 2)
		printf("<<\n");
	else if (*out_redirect == 1)
		printf(">\n");
	else if (*out_redirect == 2)
		printf(">>\n");
}

void	parse_line(char *line)
{
	int	in_redirect;
	int	out_redirect;

	in_redirect = 0;
	out_redirect = 0;

	while (*line)
	{
		if (*line == '<')
			in_redirect++;
		else if (*line == '>')
			out_redirect++;
		else
		{
			check_redirection(&in_redirect, &out_redirect);
				printf("%c", *line);
			in_redirect = 0;
			out_redirect = 0;
		}
		line++;
	}
	check_redirection(&in_redirect, &out_redirect);
	in_redirect = 0;
	out_redirect = 0;
}
