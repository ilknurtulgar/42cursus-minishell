/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zayaz <zayaz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:45:46 by zayaz             #+#    #+#             */
/*   Updated: 2024/11/06 19:56:42 by zayaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	run_execve_cmd(t_program *program, int *i, pid_t *pid_fork)
{
	program->built_check = is_builtin(program);
	if (is_builtin(program) && program->p_count == 0)
		run_one_cmd(program, i);
	else
	{
		g_global_signal = 1;
		*pid_fork = fork();
		if (*pid_fork == -1)
			return ;
		if (*pid_fork == 0)
		{
			pipe_dup(program, i);
			if (is_builtin(program) && program->p_count > 0)
				child_builtin(program);
			exec_command(program);
			exit(127);
		}
		return ;
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
		if (program->finish_check == 3)
			return ;
		if (program->rdr_error == 1 || program->rdr_error == 2)
		{
			file_error(program);
			return ;
		}
	}
	if (!program->cmd[0])
		return ;
	if (program->cmd[0] && program->cmd)
		run_execve_cmd(program, i, &pid_fork);
	program->process[*i].pid = pid_fork;
}

static void	handle_cmd(t_program *program, int *i)
{
	program->rdr_error = 0;
	program->status = 0;
	if (program->redi_flag == 1)
		program->redi_flag = 0;
	create_fork(program, i);
	if (program->cmd != NULL)
		free_array(program->cmd);
	return ;
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
		handle_cmd(program, &i);
		if (program->finish_check == 3)
			break ;
		i++;
	}
	free(program->here_fd);
	close_pipe(program);
	exit_code_handler(program);
}
