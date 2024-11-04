/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zayaz <zayaz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:45:46 by zayaz             #+#    #+#             */
/*   Updated: 2024/11/03 19:40:41 by zayaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	exec_command(t_program *program)
{
	int		i;
	char	*tmp_path;

	fill_env_cmd(program);
	find_path(program);
	i = 0;
	if (search_env("PATH", program->envp_list) == NULL)
	{
		printf("minishell: %s: No such file or directory\n", program->cmd[i]);
		program->status = 127;
		return ;
	}
	if (program->cmd[0][0] == '.' || program->cmd[0][0] == '/')
		relative_path(program);
	while (program->sep_path && program->sep_path[i])
	{
		tmp_path = ft_strjoin(program->sep_path[i], program->cmd[0]);
		if (access(tmp_path, F_OK) != -1)
			execve(tmp_path, program->cmd, program->env_cmd);
		i++;
		free(tmp_path);
	}
	exec_error(program, " command not found", 127);
}
void	run_one_cmd(t_program *program, int *i)
{
	int	stdout_backup;
	int	stdin_backup;

	if (redirect_c(program, i))
	{
		stdout_backup = dup(STDOUT_FILENO);
		stdin_backup = dup(STDIN_FILENO);
		if (program->fd_output >= 2)
			dup2(program->fd_output, STDOUT_FILENO);
		if (program->fd_input >= 2)
			dup2(program->fd_input, STDIN_FILENO);
	}
	main_builtin(program);
	if (redirect_c(program, i))
	{
		if (program->fd_input >= 2)
			dup2(stdin_backup, STDIN_FILENO);
		if (program->fd_output >= 2)
			dup2(stdout_backup, STDOUT_FILENO);
		close(stdin_backup);
		close(stdout_backup);
	}
}

static void	create_fork(t_program *program, int *i)
{
	pid_t	pid_fork;

	pid_fork = 1;
	exec_cmd(program, i);
	if (redirect_c(program, i) || heredoc_count(program) > 0)
	{
		redirect(program, i);
		if (program->rdr_error == 1 || program->rdr_error == 2)
		{
			file_error(program);
			return ;
		}
	}
	if (!program->cmd[0])
		return ;
	if (program->cmd[0] && program->cmd)
	{
		if (is_builtin(program) && program->p_count == 0)
			run_one_cmd(program, i);
		else
		{
			g_global_signal = 1;
			pid_fork = fork();
			if (pid_fork == -1)
				return ;
			if (pid_fork == 0)
			{
				pipe_dup(program, i);
				if (is_builtin(program) && program->p_count > 0)
					child_builtin(program);
				exec_command(program);
				// program->status = 127;
				exit(127);
			}
		}
	}
	program->process[*i].pid = pid_fork;
}

void	close_pipe(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->p_count)
	{
		close(program->process[i].fd[0]);
		close(program->process[i].fd[1]);
		i++;
	}
}
void	zi_exec(t_program *program)
{
	int	i;

	i = 0;
	program->p_count = pipe_count(program);
	program->process = malloc(sizeof(t_process) * (program->p_count + 1));
	program->here_fd = ft_calloc((program->p_count + 1), sizeof(int));
	*program->hd_flag = 0;
	program->redi_flag = 0;
	while (i < program->p_count)
	{
		pipe(program->process[i].fd);
		i++;
	}
	i = 0;
	while (i < program->p_count + 1)
	{
		program->status = 0;
		create_fork(program, &i);
		i++;
	}
	close_pipe(program);
	exit_code_handler(program);
}
