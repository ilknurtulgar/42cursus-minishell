/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zayaz <zayaz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 21:21:02 by zayaz             #+#    #+#             */
/*   Updated: 2024/11/06 21:21:50 by zayaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error(char *cmd, char *s, char *message)
{
	write(2, "minishell: ", ft_strlen("minishell: "));
	write(2, cmd, ft_strlen(cmd));
	write(2, ":", 1);
	write(2, " ", 1);
	if (s[0] != '\0')
		write(2, s, ft_strlen(s));
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
}

void	build_error(t_program *program, char *cmd, char *message)
{
	program->status = 1;
	write(2, "minishell: ", ft_strlen("minishell: "));
	write(2, cmd, ft_strlen(cmd));
	write(2, ":", 1);
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
}

void	identifier_error(t_program *program, char *cmd, char *s, char *message)
{
	program->status = 1;
	write(2, cmd, ft_strlen(cmd));
	write(2, ":", 1);
	write(2, "`", 1);
	write(2, s, ft_strlen(s));
	write(2, "'", 1);
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
}
