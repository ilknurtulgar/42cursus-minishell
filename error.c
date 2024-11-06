/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zayaz <zayaz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 14:42:00 by itulgar           #+#    #+#             */
/*   Updated: 2024/11/06 21:21:39 by zayaz            ###   ########.fr       */
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
