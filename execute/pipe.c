/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:02:45 by itulgar           #+#    #+#             */
/*   Updated: 2024/10/27 20:36:45 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// 1  out yazma
// 0 input   okuma
// cat main.c | echo a | efj
void	pipe_dup(t_program *program, int *i)
{
	if (*i == 0)
		dup2(program->process[*i].fd[1], STDOUT_FILENO);
	else if (program->cmd[*i] && program->cmd[(*i) + 1] == NULL)
		dup2(program->process[*i].fd[0], STDIN_FILENO);
	else
	{
		dup2(program->process[*i].fd[1], STDOUT_FILENO);
		dup2(program->process[(*i) -1 ].fd[0], STDIN_FILENO);
	}
	close(program->process[*i].fd[0]);
	close(program->process[*i].fd[1]);
}