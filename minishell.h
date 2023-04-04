/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulee <soulee@studnet.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:41:30 by soulee            #+#    #+#             */
/*   Updated: 2023/04/04 21:20:32 by soulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <termios.h>
# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include "ft_printf/ft_printf.h"

// Command Type
# define TYPE_WORD 0
# define TYPE_REDIRECT_INPUT 1
# define TYPE_REDIRECT_OUTPUT 2
# define TYPE_REDIRECT_HEREDOC 3
# define TYPE_REDIRECT_APPEND 4
# define TYPE_PIPE 5

// Signals
# define SHELL 100
# define DEFAULT 101
# define IGNORE 102
# define HEREDOC 103

typedef struct s_cmd_list
{
	int					cmd_type;
	char				*cmd;
	char				**args;
	struct s_cmd_list	*next;
}						t_cmd_list;

typedef struct s_env_list
{
	char				*key;
	char				*value;
	struct s_env_list	*next;
}						t_env_list;

typedef struct s_exe_list
{
	int				*std;
	int				fd_in;
	int				fd_out;
	int				pipe_cnt;
	t_env_list		*env_list;
	t_cmd_list		*cmd_list;
}					t_exe_list;

typedef struct s_parse_env_lst
{
	char			*str;
	int				quotes;
}					t_parse_env_lst;

int						g_exit_code;

// parser.c
int						parse_redirection(t_cmd_list **cmd_list,
							char **line, char **str);
int						parse_pipe(t_cmd_list **cmd_list,
							int is_pipe, char c, char **str);
t_cmd_list				*parse_line(t_cmd_list **cmd_list, char *line);
void					parse_quotes(t_cmd_list *cmd_list);
void					parse_dollar_sign(t_cmd_list *cmd_list,
							t_env_list *env_list);

// parser_utils.c
int						count_quotes(const char c, int quotes);
char					*parse_redirection_in(t_cmd_list **cmd_list, char *str);
char					*parse_redirection_out(t_cmd_list **cmd_list,
							char *str);
int						add_element_node(t_cmd_list **cmd_list,
							int cmd_type, char **str);
void					parse_dollar_sign_loop(t_cmd_list *cmd_list,
							t_env_list *env_list);

// parser_utils2.c
void					parse_quotes_loop(t_cmd_list *cmd_list,
							t_parse_env_lst *parse_env_lst,
							t_cmd_list **arg_list, int *i);
char					*parse_dollar_sign_loop2(t_env_list *env_list,
							int quotes, char *key, char *str);
char					**convert_args_lst(t_cmd_list *arg_list);
int						check_syntax_error(char *str, int is_pipe, int quotes);

// parser_utils3.c
int						parser(t_cmd_list **cmd_list, t_env_list **env_list,
							char *line, char *argv[]);
int						parse_line_loop(t_cmd_list **cmd_list,
							t_parse_env_lst *parse_env_lst,
							char **line, int *is_pipe);
t_cmd_list				*clear_return_zero(t_cmd_list **cmd_list);

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
int						is_white_meta_char(const char c);
char					**ft_free_strs(char **str);
char					*ft_strdup_free(char *s1, char *s2);
int						ft_is_string(char *str);

// cmd_list.c
void					clear_cmd_list(t_cmd_list **node);
t_cmd_list				*create_new_cmd_node(int type, char *cmd, char **args);
int						count_cmd_list_node(t_cmd_list *node, int cmd_type);
void					add_cmd_node_back(t_cmd_list **node, t_cmd_list *new);

// env_list.c
int						get_env_list_size(t_env_list *node);
char					*ft_getenv(t_env_list *node, char *key);
t_env_list				*create_new_env_node(char *key, char *value);
void					add_env_node_back(t_env_list **node, t_env_list *new);

// env_list_utils.c
char					**convert_env_list_to_arr(t_env_list *node);
char					**convert_env_list_to_export(t_env_list *node);
void					parse_envp(t_env_list **node, char **envp);
void					ft_swap(char **s1, char **s2);

// redirection.c
int						redirect_pipe(t_exe_list *exe_list);
int						redirect_fd(int type, char *file_name,
							t_exe_list *exe_list);
int						*dup_std(void);
void					redirect_std(int *std);

// pipe.c
int						execute_main(t_cmd_list *cmd_list, t_env_list *env_list,
							int pipe_cnt);
int						exe_cmd(char **cmd, char **env_list_str,
							t_exe_list *exe_list);
int						exe_child(char **env_list_str, char **cmds,
							t_exe_list *exe_list, int pipefd[]);
int						execute_pipeline(t_exe_list *exe_list);

// pipe_utils.c
char					**get_path(char **envp);
char					*get_cmd(char **path, char *cmd);
int						get_echo_n_cnt(const char **command);
int						is_builtin1(t_exe_list *t_exe_list, char **cmd_args);
int						is_builtin2(t_exe_list *t_exe_list, char **cmd_args);

// pipe_utils2.c
char					**get_pipe_cmd(t_cmd_list *cmd_list);
t_exe_list				*set_exe_list(t_cmd_list *cmd_list,
							t_env_list *env_list, int pipe_cnt);
int						get_status(void);

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
int						exit_error(char *error_message);
void					cmd_not_found_error(char *cmd);
void					print_export_error(char *identifier);

// builtins1.c
void					command_pwd(void);
void					command_cd(t_env_list *env_list, const char *path);
void					command_exit(const char *str);
void					command_echo(const char **s, int no_newline);

// builtins2.c
void					command_env(t_env_list *env_list);
void					command_export(t_env_list *env_list,
							const char **command);
void					command_unset(t_env_list *env_list, const char *key);
int						is_env_exist(t_env_list	*temp, char	**cmd);
void					print_export(t_env_list *env_list);

// builtin_utils.c
void					exit_numberic_argument(void);
int						is_over_long_long(long long sum, int sign, int num);
void					preprocess_atoi(const char **str, long long *sign);

// signal.c
void					set_signal(int sig_int, int sig_quit);
#endif