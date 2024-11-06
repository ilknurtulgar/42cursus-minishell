/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zayaz <zayaz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 14:42:00 by itulgar           #+#    #+#             */
/*   Updated: 2024/11/06 17:36:58 by zayaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_message(char *str)
{
	printf("<< Error: %s honey >>\n", str);
	return (0);
}

int	p_error(t_program *program, char *str)
{
	write(2, "<< Error: ", ft_strlen("<< Error: "));
	write(2, str, ft_strlen(str));
	write(2, " honey >>\n", ft_strlen(" honey >>\n"));
	program->status = 258;
	return (0);
}
void	file_error(t_program *program)
{
	program->status = 1;
}

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