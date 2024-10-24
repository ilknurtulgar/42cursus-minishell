/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zayaz <zayaz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:04:12 by zayaz             #+#    #+#             */
/*   Updated: 2024/10/23 19:35:25 by zayaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_output(char *s)
{
	int		fd;

	fd = open(s, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Error opening file");
		exit(1) ;
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("Error opening file");
		close(fd);
		return ;
	}
	close(fd);
}

void	run_input(char *s)
{
	int	fd;
	printf("s---:%s\n",s);
	fd = open(s, O_RDONLY);
	if (fd == -1)
	{
		write(0, "minishellim: ", 14);
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

void	append_output(char *s)
{
	int		fd;

	fd = open(s, O_CREAT | O_RDWR | O_APPEND, 0644);
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
