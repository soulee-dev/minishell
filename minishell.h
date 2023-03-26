/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:41:30 by soulee            #+#    #+#             */
/*   Updated: 2023/03/26 23:18:46 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_printf/ft_printf.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>

# define TYPE_WORD 0
# define TYPE_REDIRECT_INPUT 1
# define TYPE_REDIRECT_OUTPUT 2
# define TYPE_REDIRECT_HEREDOC 3
# define TYPE_REDIRECT_APPEND 4
# define TYPE_PIPE 5

typedef struct s_cmd_list
{
	int					cmd_type;
	char				*cmd;
	char				*args;
	struct s_cmd_list	*next;
}						t_cmd_list;

typedef struct s_env_list
{
	char				*key;
	char				*value;
	struct s_env_list	*next;
}						t_env_list;

int						g_exit_code;

// parser.c
void					parse_envp(t_env_list **node, char **envp);
t_cmd_list				*parse_line(t_cmd_list **cmd_list, char *line);
void					parse_dollar_sign(t_cmd_list *cmd_list,
							t_env_list *env_list);

// parser_utils.c
int						parse_quotes(const char c, int quotes);
char					*parse_redirection_in(t_cmd_list **cmd_list, char *str);
char					*parse_redirection_out(t_cmd_list **cmd_list,
							char *str);
void					add_element_node(t_cmd_list **cmd_list, int cmd_type,
							char **str);
void					parse_dollar_sign_loop(t_cmd_list *cmd_list,
							t_env_list *env_list);

// string_utils.c
char					*ft_free_str(char *str);
size_t					ft_strlenbl(const char *s);
int						is_whitespace(const char c);
int						is_whitespace_str(const char *line);
char					*ft_strndup(const char *s1, size_t n);

// string_utils2.c
char					*ft_strjoin_char(char const *s1, char s2);
char					*ft_strjoin_free(char const *s1, char const *s2);
char					*ft_strjoin_no_free(char const *s1, char const *s2);
int						ft_strcmp(const char *s1, const char *s2);
int						is_str_all_blank(char *str);

// string_utils3.c
int						is_meta_character(const char c);
char					**ft_free_strs(char **str);
char					*ft_strdup_free(char *s1, char *s2);

// cmd_list.c
void					clear_cmd_list(t_cmd_list **node);
t_cmd_list				*create_new_cmd_node(int type, char *cmd);
int						count_cmd_list_node(t_cmd_list *node, int cmd_type);
void					add_cmd_node_back(t_cmd_list **node, t_cmd_list *new);
// REMOVE BEFORE FLIGHT
void					iter_node(t_cmd_list *node);

// env_list.c
int						get_env_list_size(t_env_list *node);
char					*ft_getenv(t_env_list *node, char *key);
t_env_list				*create_new_env_node(char *key, char *value);
void					add_env_node_back(t_env_list **node, t_env_list *new);

// env_list_utils.c
char					**convert_env_list_to_arr(t_env_list *node);

// redirection.c
int						redirect_pipe(t_cmd_list **cmd_list, int *fd_in,
							int *fd_out);
int						redirect_fd(int type, char *file_name, int *fd_in,
							int *fd_out);
int						*dup_std(void);
void					redirect_std(int *std);

// pipe.c
int						execute(t_cmd_list *cmd_list, t_env_list *env_list,
							int pipe_cnt);
int						exe_cmd(char **cmd, int pipe_cnt, t_env_list *env_list,
							char **env_list_str, int fd_out, int fd_in);
char					**get_pipe_cmd(t_cmd_list *cmd_list);
int						get_status(int pid);

// pipe_utils.c
char					**get_path(char **envp);
char					*get_cmd(char **path, char *cmd);
int						is_builtin(const char **command, t_env_list *env_list);
int						get_echo_n_cnt(const char **command);

// here_doc.c
void					read_here_doc(int fd, char *delimiter,
							t_env_list *env_list);
void					delete_here_doc(int here_doc_cnt);
int						is_here_doc_exist(t_cmd_list **cmd_list, int pipe_cnt,
							t_env_list *env_list);
char					*create_here_doc_file(int count, char *delimiter,
							char *here_doc_org, t_env_list *env_list);

char					*get_env_line(char *line, t_env_list *env_list);

// file_control.c
int						open_file(char *file_name);
int						create_file(char *file_name);
int						append_file(char *file_name);

// error.c
void					print_error(char *msg);
void					exit_error(char *error_message);

// builtins1.c
void					command_pwd(void);
void					command_cd(const char *path);
void					command_exit(const char *str);
void					command_echo(const char **s, int no_newline);

// builtins2.c
void					command_env(t_env_list *env_list);
void					command_export(t_env_list *env_list,
							const char **command);
void					command_unset(t_env_list *env_list, const char *key);

// builtin_utils.c
void					exit_numberic_argument(void);
int						is_over_long_long(long long sum, int sign, int num);
void					preprocess_atoi(const char **str, long long *sign);
#endif