/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:02:45 by itulgar           #+#    #+#             */
/*   Updated: 2024/11/06 10:53:01 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// 1  out yazma terminalden veriir
// 0 input   okuma terminalden alıe
// cat main.c | echo a | efj


// void	pipe_dup(t_program *program, int *i)
// {
// 	if (*i < program->p_count)
// 	{
// 		dup2(program->process[*i].fd[1], STDOUT_FILENO);
// 		close(program->process[*i].fd[0]);
// 	}
// 	if (*i != 0)
// 		dup2(program->process[*i - 1].fd[0], STDIN_FILENO);
// 	close_pipe(program);
// 	if (program->here_fd[0] >= 0 && *program->hd_flag == 1
// 		&& *program->hd_flag != 2)
// 	{
// 		dup2(program->here_fd[0], STDIN_FILENO);
// 		*program->hd_flag = 2;
// 		close(program->here_fd[0]);
// 	}
// 	else if (program->redi_flag == 1)
// 	{
// 		if (program->fd_output >= 2)
// 		{
// 			dup2(program->fd_output, STDOUT_FILENO);
// 			close(program->fd_output);
// 		}
// 		if (program->fd_input >= 2)
// 		{
// 			dup2(program->fd_input, STDIN_FILENO);
// 			close(program->fd_input);
// 		}
// 	}

// }

void	pipe_dup(t_program *program, int *i)
{

	if (*i == 0)
		dup2(program->process[*i].fd[1], STDOUT_FILENO);
	else if (*i == program->p_count)
		dup2(program->process[(*i) - 1].fd[0], STDIN_FILENO);
	
	else
	{
		dup2(program->process[*i - 1].fd[0], STDIN_FILENO);
		//if (*program->hd_flag != 1 && *program->hd_flag != 2)
			dup2(program->process[*i].fd[1], STDOUT_FILENO);
	}
	if (redirect_c(program, i) && program->redi_flag == 1)
	{
		if (program->fd_output >= 2)
			dup2(program->fd_output, STDOUT_FILENO);
		else if (program->fd_input >= 2)
			dup2(program->fd_input, STDIN_FILENO);
	}
	if (program->process[*i].fd[0] >= 0 && *program->hd_flag == 1)
	{
		dup2(program->here_fd[0], STDIN_FILENO);
		*program->hd_flag = 2;
	}
	close_pipe(program);
}

