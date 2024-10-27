/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:04:12 by zayaz             #+#    #+#             */
/*   Updated: 2024/10/27 20:29:20 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_output(t_program *program, char *s)
{
	int	fd;

	fd = open(s, O_CREAT | O_RDWR | O_TRUNC, 0644);
	program->fd = dup(fd);
	if (fd == -1)
	{
		perror("Error opening file");
		exit(1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("Error opening file");
		close(fd);
		return ;
	}
	close(fd);
}

void	run_input(t_program *program, char *s)
{
	int	fd;

	fd = open(s, O_RDONLY);
	program->fd = dup(fd);
	if (fd == -1)
	{
		write(0, "minishell: ", 14);
		perror(s);
		return ;
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("Error opening file");
		close(fd);
		return ;
	}
	close(fd);
}

void	append_output(t_program *program, char *s)
{
	int	fd;

	fd = open(s, O_CREAT | O_RDWR | O_APPEND, 0644);
	program->fd = dup(fd);
	if (fd == -1)
	{
		perror("Error opening file");
		return ;
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("Error opening file");
		close(fd);
		return ;
	}
	close(fd);
}
