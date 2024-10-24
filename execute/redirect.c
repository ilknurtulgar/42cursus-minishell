/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zayaz <zayaz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:53:16 by zayaz             #+#    #+#             */
/*   Updated: 2024/10/23 20:00:17 by zayaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int zi_redirectchr(const char *s, char c)
{
	char type;

	while (*s)
	{
		if (*s == '\'' || *s == '\"')
		{
			type = *s;
			s++;
			while (*s && *s != type)
				s++;
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

void	load_redi(t_program *program, void run_redirect(char *), int *i, int *j,
		int *z)
{
	int		start;
	int		size;
	char	*doc;
	char	*clean_doc;

	clean_doc = NULL;
	start = 0;
	size = 0;
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
		clean_doc = del_quote(clean_doc, doc, ft_strlen(doc));
		printf("clean_doc:%s\n",clean_doc);
		run_redirect(clean_doc);
		free(doc);
		free(clean_doc);
	}
}
//<here>>ben>sen<<yo (abort)
//input yoksa devam etme
void	redirect(t_program *program, int *i)
{
	int	j;
	int	z;

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
				}//"<<"gi <hi>abu">>"anam"dunnya">>gell gel"sene">">>a"<<susma > sutukca
				if (program->parser_input[*i][j]->cmd[z] == '>'
					&& (program->parser_input[*i][j]->cmd[z + 1]
						&& program->parser_input[*i][j]->cmd[z + 1] == '>'))
				{
					z++;
					load_redi(program, append_output, i, &j, &z);
				}
				if (program->parser_input[*i][j]->cmd[z] == '<'){
					printf("inputum\n");
					load_redi(program, run_input, i, &j, &z);
				}
				if (program->parser_input[*i][j]->cmd[z] == '>')
					load_redi(program, run_output, i, &j, &z);
			}
			else if (program->parser_input[*i][j]->cmd[z]
				&& program->parser_input[*i][j]->cmd[z] != '\''
				&& program->parser_input[*i][j]->cmd[z] != '\"')
				z++;
		}
		j++;
	}
}
//gel"sene">">>a"<<susma