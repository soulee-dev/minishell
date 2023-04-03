/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 21:07:21 by subcho            #+#    #+#             */
/*   Updated: 2023/04/03 22:02:35 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exe_cmd(char **cmd, char **env_list_str, t_exe_list *exe_list)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) < 0)
	{
		print_error(0);
		return (-1);
	}
	set_signal(DEFAULT, DEFAULT);
	pid = fork();
	if (pid < 0)
		print_error(0);
	else if (pid == 0)
	{
		close(pipefd[0]);
		if (exe_list->pipe_cnt)
			dup2(pipefd[1], STDOUT_FILENO);
		exe_child(env_list_str, cmd, exe_list, pipefd);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		set_signal(SHELL, IGNORE);
	}
	return (pid);
}

int	exe_child(char **env_list_str, char **cmds,
			t_exe_list *exe_list, int pipefd[])
{
	char	**path;
	int		exit_code;
	char	*cmd;

	if (is_builtin1(exe_list, cmds) || is_builtin2(exe_list, cmds))
		exit(0);
	path = get_path(env_list_str);
	cmd = get_cmd(path, cmds[0]);
	dup2(exe_list->fd_out, STDOUT_FILENO);
	close(pipefd[1]);
	g_exit_code = execve(cmd, cmds, env_list_str);
	g_exit_code = 126;
	exit(126);
}

int	execute_pipeline(t_exe_list *exe_list)
{
	int		status;
	char	**cmd_args;
	int		redirection;
	char	**env_list_str;

	env_list_str = convert_env_list_to_arr(exe_list->env_list);
	while (--(exe_list->pipe_cnt) >= 0)
	{
		if (!exe_list->pipe_cnt)
			exe_list->fd_out = dup2(exe_list->std[1], STDOUT_FILENO);
		cmd_args = get_pipe_cmd(exe_list->cmd_list);
		redirection = redirect_pipe(exe_list);
		if (!cmd_args || redirection == -1)
			exe_cmd(0, env_list_str, exe_list);
		else if (exe_list->pipe_cnt || (exe_list->pipe_cnt == 0
				&& !is_builtin1(exe_list, cmd_args)
				&& !is_builtin2(exe_list, cmd_args)))
			status = exe_cmd(cmd_args, env_list_str, exe_list);
		if (exe_list->fd_in > STDIN_FILENO)
			close(exe_list->fd_in);
		if (exe_list->fd_out > STDOUT_FILENO)
			close(exe_list->fd_out);
	}
	env_list_str = ft_free_strs(env_list_str);
	return (status);
}

int	execute_main(t_cmd_list *cmd_list, t_env_list *env_list, int pipe_cnt)
{
	int			status;
	t_exe_list	*exe_list;
	int			here_doc_cnt;

	here_doc_cnt = is_here_doc_exist(&cmd_list, pipe_cnt, env_list);
	exe_list = set_exe_list(cmd_list, env_list, pipe_cnt);
	status = execute_pipeline(exe_list);
	delete_here_doc(here_doc_cnt);
	redirect_std(exe_list->std);
	free(exe_list);
	exe_list = 0;
	g_exit_code = get_status(status);
	return (g_exit_code);
}
