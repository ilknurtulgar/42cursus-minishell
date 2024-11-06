/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:53:16 by zayaz             #+#    #+#             */
/*   Updated: 2024/11/06 10:29:17 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	zi_redirectchr(const char *s, char c)
{
	char	type;

	while (*s)
	{
		if (*s == '\'' || *s == '\"')
		{
			type = *s;
			s++;
			while (*s && *s != type)
				s++;
			if (*s == type)
				s++;
		}
		if (*s == c && *(s + 1) == c)
			return (1);
		if (*s)
			s++;
	}
	return (0);
}

void	quote_skip(char *cmd, int *z)
{
	char	q_type;

	if (cmd[*z] == '\'' || cmd[*z] == '\"')
	{
		q_type = cmd[*z];
		(*z)++;
		while (cmd[*z] && cmd[*z] != q_type)
			(*z)++;
		if (cmd[*z] == q_type)
			(*z)++;
	}
}

void	find_loc(char *cmd, int *z)
{
	while (cmd[*z] != '\0' && cmd[*z] != '>' && cmd[*z] != '<')
	{
		quote_skip(cmd, z);
		if (cmd[*z] && (cmd[*z] != '\'' && cmd[*z] != '\"') && (cmd[*z] != '>'
				&& cmd[*z] != '<'))
			(*z)++;
	}
}

void	load_redi(t_program *program, void run_redirect(t_program *, char *),
		int *i, int *j, int *z)
{
	int		start;
	char	*doc;
	char	*clean_doc;

	clean_doc = NULL;
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
	if (doc != NULL)
	{
		// if(clean_doc!=NULL)
		// 	free(clean_doc);
		clean_doc = del_quote(clean_doc, doc, ft_strlen(doc));
		free(doc);
		// if (program->fd_input > 2)
		// 	close(program->fd_input);
		// if (program->fd_output > 2)
		// 	close(program->fd_output);
		if (program->rdr_error == 2 || program->rdr_error == 1)
		{
			free(clean_doc);
			return ;
		}
		if (program->status != 1)
			run_redirect(program, clean_doc);
		free(clean_doc);
	}
}

void	redirect(t_program *program, int *i)
{
	int	j;
	int	z;

	if (*program->hd_flag == 0 && heredoc_count(program))
	{
		heredoc_run(program);
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
		{
			quote_skip(program->parser_input[*i][j]->cmd, &z);
			if (program->parser_input[*i][j]->cmd[z] == '<'
				|| program->parser_input[*i][j]->cmd[z] == '>')
			{
				program->redi_type = program->parser_input[*i][j]->cmd[z];
				if (program->parser_input[*i][j]->cmd[z] == '<'
					&& (program->parser_input[*i][j]->cmd[z + 1]
						&& program->parser_input[*i][j]->cmd[z + 1] == '<'))
				{
					z += 2;
				}
				if (program->parser_input[*i][j]->cmd[z] == '>'
					&& (program->parser_input[*i][j]->cmd[z + 1]
						&& program->parser_input[*i][j]->cmd[z + 1] == '>'))
				{
					z++;
					load_redi(program, append_output, i, &j, &z);
					program->redi_flag = 1;
				}
				if (program->parser_input[*i][j]->cmd[z] == '<')
				{
					load_redi(program, run_input, i, &j, &z);
					program->redi_flag = 1;
				}
				if ((program->parser_input[*i][j]->cmd[z] == '>'
						&& ft_strncmp(program->parser_input[*i][j]->cmd + z,
							">>", 2) != 0))
				{
					load_redi(program, run_output, i, &j, &z);
					program->redi_flag = 1;
				}
			}
			else if (program->parser_input[*i][j]->cmd[z]
				&& program->parser_input[*i][j]->cmd[z] != '\''
				&& program->parser_input[*i][j]->cmd[z] != '\"')
				z++;
		}
		j++;
	}
}
