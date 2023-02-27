/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:41:30 by soulee            #+#    #+#             */
/*   Updated: 2023/02/27 18:48:05 by soulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <termios.h>
# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>

# define TYPE_WORD 0
# define TYPE_REDIRECT_INPUT 1
# define TYPE_REDIRECT_OUTPUT 2
# define TYPE_REDIRECT_HEREDOC 3
# define TYPE_REDIRECT_APPEND 4

typedef struct s_cmd {
	int				cmd_type;
	char			*cmd;
	struct s_cmd	*next;
}	t_cmd;

// parser.c
void	parse_line(char *line);
void	add_element_node(int cmd_type, char **str);

// parser_utils.c
void	ft_free_str(char **str);
char	*parse_redirection_out(char *str);
int		parse_set_quotes(char line, int quotes);
char	*ft_strjoin_char(char const *s1, char s2);
char	*parse_redirection_in(char *str);
// env.c
char	*get_env_value(char **envp, char *key);

// string_utils.c
size_t	ft_strlenbl(const char *s);
char	*ft_strndup(const char *s1, size_t n);
#endif