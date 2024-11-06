/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:02:45 by itulgar           #+#    #+#             */
/*   Updated: 2024/11/06 12:18:45 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    pipe_dup(t_program *program, int *i)
{
    if (*i == 0)
        dup2(program->process[*i].fd[1], STDOUT_FILENO);
    else if (*i == program->p_count)
        dup2(program->process[(*i) - 1].fd[0], STDIN_FILENO);
    else
    {
        dup2(program->process[*i - 1].fd[0], STDIN_FILENO);
        dup2(program->process[*i].fd[1], STDOUT_FILENO);
    }
    if (redirect_c(program, i) && program->redi_flag == 1)
    {
        if (program->fd_output >= 2)
            dup2(program->fd_output, STDOUT_FILENO);
         if (program->fd_input >= 2)
            dup2(program->fd_input, STDIN_FILENO);
    }
    if (program->here_fd[0] >= 0 && *program->hd_flag == 1)
    {
        dup2(program->here_fd[0], STDIN_FILENO);
        *program->hd_flag = 2;
    }
    close_pipe(program);
}

