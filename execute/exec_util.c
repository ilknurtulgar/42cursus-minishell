/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 13:40:25 by zayaz             #+#    #+#             */
/*   Updated: 2024/11/08 16:57:33 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_code_handler(t_program *program)
{
	int	staus_check;
	int	i;

	staus_check = 0;
	i = 0;
	while (i <= program->p_count)
	{
		waitpid(program->process[i].pid, &staus_check, 0);
		if (program->built_check == 0 && (program->rdr_error != 1
				&& program->rdr_error != 2 && program->finish_check != 3))
		{
			if (WIFSIGNALED(staus_check) && WTERMSIG(staus_check) == SIGINT)
				program->status = 130;
			program->status = staus_check / 256;
		}
		i++;
	}
	program->rdr_error = 0;
}

int	pipe_count(t_program *program)
{
	int	i;

	i = 0;
	while (program->parser_input[i] != NULL)
		i++;
	return (i - 1);
}

int	is_close_quote(char *str, size_t i, char q_type)
{
	i++;
	while (str[i] && str[i] != q_type)
		i++;
	if (str[i] == q_type)
		return (1);
	return (0);
}

static void	process_quotes(char *dst, char *src, size_t *i, size_t *j)
{
	char	q_type;

	q_type = src[*i];
	if (is_close_quote(src, *i, q_type))
	{
		(*i)++;
		while (src[*i] && q_type != src[*i])
			dst[(*j)++] = src[(*i)++];
		if (q_type == src[*i])
			(*i)++;
	}
	else if (is_close_quote(src, *i, src[*i]) == 0 && (src[*i] == '\"'
			|| src[*i] == '\''))
		dst[(*j)++] = src[(*i)++];
}

char	*del_quote(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	dst = (char *)malloc(dstsize * sizeof(char) + 1);
	i = 0;
	j = 0;
	if (!src || dstsize == 0)
		return (dst);
	while (src[i] && j < dstsize)
	{
		if (src[i] && (src[i] == '\'' || src[i] == '\"'))
		{
			process_quotes(dst, src, &i, &j);
			if (i == 0)
				dst[j++] = src[i++];
		}
		else
			dst[j++] = src[i++];
	}
	dst[j] = '\0';
	return (dst);
}
