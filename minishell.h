/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:41:30 by soulee            #+#    #+#             */
/*   Updated: 2023/03/04 22:40:02 by soulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
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
# define TYPE_PIPE 5

typedef struct s_cmd_list {
	int					cmd_type;
	char				*cmd;
	struct s_cmd_list	*next;
}	t_cmd_list;

typedef struct s_env_list {
	char				*key;
	char				*value;
	struct s_env_list	*next;
}	t_env_list;

// parser.c
void		parse_envp(t_env_list **node, char **envp);
t_cmd_list	*parse_line(t_cmd_list **cmd_list, char *line);
void		parse_dollar_sign(t_cmd_list *cmd_list, t_env_list *env_list);

// parser_utils.c
int			parse_quotes(char line, int quotes);
char		*parse_redirection_in(t_cmd_list **cmd_list, char *str);
char		*parse_redirection_out(t_cmd_list **cmd_list, char *str);
void		add_element_node(t_cmd_list **cmd_list, int cmd_type, char **str);
void		parse_dollar_sign_loop(t_cmd_list *cmd_list, t_env_list *env_list);

// string_utils.c
void		ft_free_str(char **str);
size_t		ft_strlenbl(const char *s);
int			check_is_whitespace(char c);
int			check_whitespace_str(char *line);
char		*ft_strndup(const char *s1, size_t n);

// string_utils2.c
char		*ft_strjoin_char(char const *s1, char s2);
char		*ft_strjoin_free(char const *s1, char const *s2);
char		*ft_strjoin_no_free(char const *s1, char const *s2);

// cmd_list.c
void		clear_cmd_list(t_cmd_list **node);
t_cmd_list	*create_new_cmd_node(int type, char *cmd);
int			count_cmd_list_node(t_cmd_list *node, int cmd_type);
void		add_cmd_node_back(t_cmd_list **node, t_cmd_list *new);
void		iter_node(t_cmd_list *node);

// env_list.c
int			get_env_list_size(t_env_list *node);
char		*ft_getenv(t_env_list *node, char *key);
t_env_list	*create_new_env_node(char *key, char *value);
void		add_env_node_back(t_env_list **node, t_env_list *new);

// env_list_utils.c
char		**convert_env_list_to_arr(t_env_list *node);

// pipe.c
int			execute_cmd(t_cmd_list *cmd_list, char **envp, int pipe_cnt);
void		handle_cmd(int type, char *cmd, char **path, char **envp, int pipefd[], pid_t pid, int pipe_cnt, int *fd);
int			get_status(int pid);

// pipe_utils.c
void		print_error(char *msg);
char		**get_path(char **envp);
char		*get_cmd(char **path, char *cmd);
int			open_file(char *file_name);
int			create_file(char *file_name);
void		free_str(char **str);

// error.c
void		exit_error(char *error_message);

// builtins.c
void		pwd();
void		cd(const char *path);
void		env(t_env_list *env_list);
// void		unset(t_env_list *env_list, char *key);
#endif