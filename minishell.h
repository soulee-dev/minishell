/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:41:30 by soulee            #+#    #+#             */
/*   Updated: 2023/03/07 19:13:44 by soulee           ###   ########.fr       */
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
int			parse_line(t_cmd_list **cmd_list, char *line);
void		parse_dollar_sign(t_cmd_list *cmd_list, t_env_list *env_list);

// parser_utils.c
int			parse_quotes(char line, int quotes);
char		*parse_redirection_in(t_cmd_list **cmd_list, char *str, int *is_parse_error);
char		*parse_redirection_out(t_cmd_list **cmd_list, char *str, int *is_parse_error);
void		parse_dollar_sign_loop(t_cmd_list *cmd_list, t_env_list *env_list);
void		add_element_node(t_cmd_list **cmd_list, int cmd_type, char **str, int *is_parse_error);

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
// REMOVE BEFORE FLIGHT
void		iter_node(t_cmd_list *node);

// env_list.c
int			get_env_list_size(t_env_list *node);
char		*ft_getenv(t_env_list *node, char *key);
t_env_list	*create_new_env_node(char *key, char *value);
void		add_env_node_back(t_env_list **node, t_env_list *new);

// env_list_utils.c
char		**convert_env_list_to_arr(t_env_list *node);

// redirection.c
t_cmd_list	*redirect_pipe(t_cmd_list *cmd_list);
void		redirect_fd(int type, char *file_name);
void		read_here_doc(char	*delimiter);

// pipe.c
int			execute(t_cmd_list *cmd_list, char **envp, int pipe_cnt);
int			exe_cmd(char	**cmd, char **path, int pipe_cnt, char **envp);
char		**get_pipe_cmd(t_cmd_list *cmd_list);
int			get_status(int pid);

// pipe_utils.c
char		**get_path(char **envp);
char		*get_cmd(char **path, char *cmd);
int			is_builtin(const char **command, char **envp);
int			get_echo_n_cnt(const char **command);

// file_control.c
int			open_file(char *file_name);
int			create_file(char *file_name);
int			append_file(char *file_name);

// error.c
void		print_error(char *msg);
void		exit_error(char *error_message);

// builtins1.c
void		command_pwd(void);
void		command_cd(const char *path);
void		command_echo(const char *s, int no_newline);

// builtins2.c
void		command_env(char **envp);
void		command_export(t_env_list *env_list, char *key, char *value);
// void		command_unset(t_env_list *env_list, char *key);
#endif