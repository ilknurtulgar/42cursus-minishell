/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zayaz <zayaz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:02:45 by itulgar           #+#    #+#             */
/*   Updated: 2024/11/03 19:47:04 by zayaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// 1  out yazma terminalden veriir
// 0 input   okuma terminalden alıe
// cat main.c | echo a | efj
int	is_mu_builtin(t_program *program)
{
	if ((zi_strcmp(program->cmd[0], "cd") == 0) || (zi_strcmp(program->cmd[0],
				"unset") == 0) || (zi_strcmp(program->cmd[0], "export") == 0))
		return (1);
	return (0);
}

void	pipe_dup(t_program *program, int *i)
{
	if (*i < program->p_count)
	{
		dup2(program->process[*i].fd[1], STDOUT_FILENO);
		close(program->process[*i].fd[0]);
	}
	if (*i != 0)
		dup2(program->process[*i - 1].fd[0], STDIN_FILENO);
	close_pipe(program);
	if (program->here_fd[0] >= 0 && *program->hd_flag == 1
		&& *program->hd_flag != 2)
	{
		dup2(program->here_fd[0], STDIN_FILENO);
		*program->hd_flag = 2;
		close(program->here_fd[0]);
	}
	else if (program->redi_flag == 1)
	{
		if (program->fd_output >= 2)
		{
			dup2(program->fd_output, STDOUT_FILENO);
			close(program->fd_output);
		}
		else if (program->fd_input >= 2)
		{
			dup2(program->fd_input, STDIN_FILENO);
			close(program->fd_input);
		}
	}
	
}
