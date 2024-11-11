/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:51:42 by zayaz             #+#    #+#             */
/*   Updated: 2024/11/07 17:58:16 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signo)
{
	(void)signo;
	if (g_global_signal == 0 || g_global_signal == 13)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_global_signal = 13;
	}
	else if (g_global_signal == IN_CAT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
	}
	else if (g_global_signal == IN_HERADOC)
	{
		write(1, "\n", 1);
		exit(1);
	}
}

void	signal_init(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

int	rdr_take_status(t_program *program, int pid)

{
	int	status;

	g_global_signal = IN_PARENT;
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		program->status = 1;
	else
		program->status = WEXITSTATUS(status);
	if (program->status != 0)
		return (3);
	else
		return (0);
}
