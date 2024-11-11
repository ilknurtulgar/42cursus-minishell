/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 12:45:31 by itulgar           #+#    #+#             */
/*   Updated: 2024/11/08 15:34:36 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	fillable_cmd(t_program *program, t_lexer *input, int *z, int *k)
{
	char	*clean_cmd;

	clean_cmd = NULL;
	program->start_cmd = *z;
	while (input->cmd[*z] && (input->cmd[*z] != '<' && input->cmd[*z] != '>'))
	{
		if (input->cmd[*z] != '\'' && input->cmd[*z] != '\"')
			(*z)++;
		else
			quote_skip(input->cmd, z);
	}
	if (input->cmd[*z] == '\0' || (input->cmd[*z] == '<'
			|| input->cmd[*z] == '>'))
	{
		clean_cmd = del_quote(clean_cmd, input->cmd, ft_strlen(input->cmd));
		program->cmd[*k] = ft_substr(clean_cmd, program->start_cmd, (*z
					- program->start_cmd));
		free(clean_cmd);
		(*k)++;
	}
}

static int	cmd_counter(t_program *program, int *i)
{
	int	j;
	int	count;
	int	z;

	j = 0;
	count = 0;
	z = 0;
	while (program->parser_input[*i] != NULL && program->parser_input[*i][j]
		&& program->parser_input[*i][j]->cmd)
	{
		z = 0;
		while (program->parser_input[*i][j]->cmd[z])
		{
			if (program->parser_input[*i][j]->cmd[z] != '<'
				&& program->parser_input[*i][j]->cmd[z] != '>')
				fillable_count(program->parser_input[*i][j]->cmd, &z, &count);
			else
				redi_skip(program->parser_input[*i], &z, &j);
		}
		j++;
	}
	return (count);
}

static void	fill_cmd(t_program *program, int *i)
{
	int	z;
	int	k;
	int	j;

	z = 0;
	k = 0;
	j = 0;
	while (program->parser_input[*i] && program->parser_input[*i][j]
		&& program->parser_input[*i][j]->cmd)
	{
		z = 0;
		while (program->parser_input[*i][j]->cmd[z])
		{
			if (program->parser_input[*i][j]->cmd[z] != '<'
				&& program->parser_input[*i][j]->cmd[z] != '>')
				fillable_cmd(program, program->parser_input[*i][j], &z, &k);
			else
				redi_skip(program->parser_input[*i], &z, &j);
		}
		j++;
	}
	program->cmd[k] = NULL;
}

void	exec_cmd(t_program *program, int *i)
{
	int	cmd_len;

	cmd_len = 0;
	cmd_len = cmd_counter(program, i);
	program->cmd = malloc(sizeof(char **) * (cmd_len + 1));
	if (!program->cmd)
	{
		perror("memory failure allocation");
		exit(1);
	}
	fill_cmd(program, i);
}
