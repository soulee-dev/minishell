/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:41:30 by soulee            #+#    #+#             */
/*   Updated: 2023/02/27 22:37:22 by soulee           ###   ########.fr       */
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

typedef struct s_cmd_list {
	int					cmd_type;
	char				*cmd;
	struct s_cmd		*next;
}	t_cmd_list;

typedef struct s_env_list {
	char				*key;
	char				*value;
	struct s_env_list	*next;
}	t_env_list;

// parser.c
void		parse_line(char *line);
void		parse_envp(t_env_list **node, char **envp);

// parser_utils.c
char		*parse_redirection_in(char *str);
char		*parse_redirection_out(char *str);
int			parse_quotes(char line, int quotes);
void		add_element_node(int cmd_type, char **str);

// string_utils.c
void		ft_free_str(char **str);
size_t		ft_strlenbl(const char *s);
char		*ft_strndup(const char *s1, size_t n);
char		*ft_strjoin_char(char const *s1, char s2);

// string_utils2.c
char	*ft_strjoin_free(char const *s1, char const *s2);
char	*ft_strjoin_no_free(char const *s1, char const *s2);

// env_list.c
int			get_env_list_size(t_env_list *node);
char		*ft_getenv(t_env_list *node, char *key);
t_env_list	*create_new_env_node(char *key, char *value);
void		add_env_node_back(t_env_list **node, t_env_list *new);

// env_list_utils.c
char		**convert_env_list_to_arr(t_env_list *node);

// error.c
void		exit_error(char *error_message);
#endif