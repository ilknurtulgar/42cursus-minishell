/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:04:12 by zayaz             #+#    #+#             */
/*   Updated: 2024/11/08 14:26:24 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_output(t_program *program, char *s)
{
	program->fd_output = open(s, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (program->fd_output == -1)
	{
		write(2, "minishell: ", 12);
		perror(s);
		program->rdr_error = 2;
		return ;
	}
}

void	run_input(t_program *program, char *s)
{
	program->fd_input = open(s, O_RDONLY);
	if (program->fd_input == -1)
	{
		write(2, "minishell: ", 12);
		perror(s);
		program->rdr_error = 1;
		return ;
	}
}

void	append_output(t_program *program, char *s)
{
	program->fd_output = open(s, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (program->fd_output == -1)
	{
		write(2, "minishell: ", 12);
		perror(s);
		program->rdr_error = 2;
		return ;
	}
}
