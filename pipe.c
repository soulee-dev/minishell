/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 21:07:21 by subcho            #+#    #+#             */
/*   Updated: 2023/03/30 22:49:18 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_pipe_cmd(t_cmd_list *cmd_list)
{
	char	**cmd;

	cmd = 0;
	while (cmd_list && cmd_list->cmd_type != TYPE_PIPE)
	{
		if (cmd_list->cmd_type == TYPE_WORD)
		{
			cmd = cmd_list->args;
			break ;
		}
		cmd_list = cmd_list->next;
	}
	if (!cmd)
		return (0);
	return (cmd);
}

int	exe_cmd(char **cmd, char **env_list_str, t_exe_list *exe_list)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) < 0)
	{
		print_error(0);
		return (-1);
	}
	pid = fork();
	if (pid < 0)
		print_error(0);
	else if (pid == 0)
	{
		close(pipefd[0]);
		if (exe_list->pipe_cnt)
			dup2(pipefd[1], STDOUT_FILENO);
		dup2(exe_list->fd_out, STDOUT_FILENO);
		close(pipefd[1]);
		if ((!is_builtin1(exe_list, cmd) && !is_builtin2(exe_list, cmd)))
			execve(get_cmd(get_path(env_list_str), cmd[0]), cmd, env_list_str);
		exit(0);
	}
	else
	{
		//waitpid(pid, NULL, 0);
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
	return (pid);
}

int	execute_pipeline(t_exe_list *exe_list)
{
	int		status;
	char	**cmd_args;
	char	**env_list_str;

	env_list_str = convert_env_list_to_arr(exe_list->env_list);
	while (--(exe_list->pipe_cnt) >= 0)
	{
		if (!exe_list->pipe_cnt)
			exe_list->fd_out = dup2(exe_list->std[1], STDOUT_FILENO);
		cmd_args = get_pipe_cmd(exe_list->cmd_list);
		if (redirect_pipe(exe_list) == -1 && cmd_args)
			status = exe_cmd(0, env_list_str, exe_list);
		else if (!cmd_args)
			continue ;
		else if (exe_list->pipe_cnt || (!exe_list->pipe_cnt
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

t_exe_list	*set_exe_list(t_cmd_list *cmd_list, t_env_list *env_list,
		int pipe_cnt)
{
	t_exe_list	*exe_list;

	exe_list = malloc(sizeof(t_exe_list));
	exe_list->cmd_list = cmd_list;
	exe_list->env_list = env_list;
	exe_list->pipe_cnt = pipe_cnt;
	exe_list->std = dup_std();
	exe_list->fd_in = STDIN_FILENO;
	exe_list->fd_out = STDOUT_FILENO;
	return (exe_list);
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

int	get_status(int pid)
{
	int	status;
	int	last_pid;
	int	temp;

	last_pid = pid;
	while (pid != -1)
	{
		pid = wait(&temp);
		if (pid == last_pid)
			status = temp;
	}
	return (WEXITSTATUS(status));
}
