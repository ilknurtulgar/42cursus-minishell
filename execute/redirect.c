/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:53:16 by zayaz             #+#    #+#             */
/*   Updated: 2024/11/08 15:44:18 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*take_redi_doc(t_program *program, int *i, int *j, int *z)
{
	int		start;
	char	*doc;

	start = 0;
	doc = NULL;
	if (program->parser_input[*i][*j]->cmd[*z])
	{
		(*z)++;
		if (program->parser_input[*i][*j]->cmd[*z] == '\0')
		{
			start = 0;
			*z = 0;
			(*j)++;
		}
		else
			start = (*z);
	}
	find_loc(program->parser_input[*i][*j]->cmd, z);
	doc = ft_substr(program->parser_input[*i][*j]->cmd, start, ((*z) - start));
	return (doc);
}

static void	handle_redirect(t_program *program, void run_redirect(t_program *,
			char *), char *doc)
{
	char	*clean_doc;

	clean_doc = NULL;
	if (doc != NULL)
	{
		clean_doc = del_quote(clean_doc, doc, ft_strlen(doc));
		free(doc);
		if (program->rdr_error == 2 || program->rdr_error == 1)
		{
			free(clean_doc);
			return ;
		}
		if (program->status != 1)
			run_redirect(program, clean_doc);
		free(clean_doc);
		program->redi_flag = 1;
	}
}

static void	take_type_redi(t_program *program, int *i, int *j, int *z)
{
	char	*doc;

	doc = NULL;
	if (program->parser_input[*i][*j]->cmd[*z] == '>'
		&& (program->parser_input[*i][*j]->cmd[*z + 1]
			&& program->parser_input[*i][*j]->cmd[*z + 1] == '>'))
	{
		(*z)++;
		doc = take_redi_doc(program, i, j, z);
		handle_redirect(program, append_output, doc);
	}
	if (program->parser_input[*i][*j]->cmd[*z] == '<')
	{
		doc = take_redi_doc(program, i, j, z);
		handle_redirect(program, run_input, doc);
	}
	if ((program->parser_input[*i][*j]->cmd[*z] == '>'
		&& ft_strncmp(program->parser_input[*i][*j]->cmd + *z, ">>",
		2) != 0))
	{
		doc = take_redi_doc(program, i, j, z);
		handle_redirect(program, run_output, doc);
	}
}

static void	find_redirect(t_program *program, int *i, int *j, int *z)
{
	quote_skip(program->parser_input[*i][*j]->cmd, z);
	if (program->parser_input[*i][*j]->cmd[*z] == '<'
		|| program->parser_input[*i][*j]->cmd[*z] == '>')
	{
		program->redi_type = program->parser_input[*i][*j]->cmd[*z];
		if (program->parser_input[*i][*j]->cmd[*z] == '<'
			&& (program->parser_input[*i][*j]->cmd[*z + 1]
				&& program->parser_input[*i][*j]->cmd[*z + 1] == '<'))
		{
			(*z) += 2;
		}
		take_type_redi(program, i, j, z);
	}
	else if (program->parser_input[*i][*j]->cmd[*z]
		&& program->parser_input[*i][*j]->cmd[*z] != '\''
		&& program->parser_input[*i][*j]->cmd[*z] != '\"')
		(*z)++;
}

void	redirect(t_program *program, int *i)
{
	int	j;
	int	z;

	if (*program->hd_flag == 0 && heredoc_count(program))
	{
		heredoc_main(program);
		*program->hd_flag = 1;
	}
	program->redi_type = '\0';
	j = 0;
	z = 0;
	while (program->parser_input[*i][j] != NULL
		&& program->parser_input[*i][j]->cmd)
	{
		z = 0;
		while (program->parser_input[*i][j]->cmd[z])
			find_redirect(program, i, &j, &z);
		j++;
	}
}
