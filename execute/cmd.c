/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 12:45:31 by itulgar           #+#    #+#             */
/*   Updated: 2024/11/01 15:30:22 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fillable_cmd(t_program *program, t_lexer *input, int *z, int *start,
		int *k)
{
	char	*clean_cmd;

	clean_cmd = NULL;
	*start = *z;
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
		if (input->key == 8 || input->key == 5 || input->key == 6)
		{
			clean_cmd = del_quote(clean_cmd, input->cmd, ft_strlen(input->cmd));
			program->cmd[*k] = ft_substr(clean_cmd, *start, (*z - *start));
			free(clean_cmd);
		}
		else
		{
			program->cmd[*k] = ft_substr(input->cmd, *start, (*z - *start));
		}
		(*k)++;
	}
}

void	fillable_count(char *cmd, int *z, int *count)
{
	while (cmd[*z] && (cmd[*z] != '<' && cmd[*z] != '>'))
	{
		if (cmd[*z] != '\'' && cmd[*z] != '\"')
			(*z)++;
		else
			quote_skip(cmd, z);
	}
	if (cmd[*z] == '\0' || (cmd[*z] == '<' || cmd[*z] == '>'))
		(*count)++;
}
void	redi_skip(t_lexer **parser_input, int *z, int *j)
{
	char	redi_type;

	if (parser_input[*j]->cmd[*z] && parser_input[*j]->cmd[*z] != '\''
		&& parser_input[*j]->cmd[*z] != '\"')
	{
		redi_type = parser_input[*j]->cmd[*z];
		(*z)++;
		if (parser_input[*j]->cmd[*z] == redi_type)
			(*z)++;
	}
	if (parser_input[*j]->cmd[*z] == '\0')
	{
		(*j)++;
		*z = 0;
	}
	while (parser_input[*j]->cmd[*z] && (parser_input[*j]->cmd[*z] != '<'
			&& parser_input[*j]->cmd[*z] != '>'))
	{
		if (parser_input[*j]->cmd[*z] && parser_input[*j]->cmd[*z] != '\''
			&& parser_input[*j]->cmd[*z] != '\"')
			(*z)++;
		else
			quote_skip(parser_input[*j]->cmd, z);
	}
}

int	cmd_counter(t_program *program, int *i)
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

void	fill_cmd(t_program *program, int *i)
{
	int	z;
	int	k;
	int	start;
	int	j;

	z = 0;
	k = 0;
	start = 0;
	j = 0;
	j = 0;
	while (program->parser_input[*i] && program->parser_input[*i][j]
		&& program->parser_input[*i][j]->cmd)
	{
		z = 0;
		while (program->parser_input[*i][j]->cmd[z])
		{
			if (program->parser_input[*i][j]->cmd[z] != '<'
				&& program->parser_input[*i][j]->cmd[z] != '>')
				fillable_cmd(program, program->parser_input[*i][j], &z, &start,
					&k);
			else
				redi_skip(program->parser_input[*i], &z, &j);
		}
		j++;
	}
	program->cmd[k] = NULL;
}

// minishell 🐥>echo $a

// minishell 🐥>echo "$a"
// '
// minishell 🐥>echo '$a'
// $a
// minishell 🐥>echo $a"nkj"$a
// "nkj"$a
void	exec_cmd(t_program *program, int *i)
{
	int cmd_len;
	cmd_len = cmd_counter(program, i);
	program->cmd = malloc(sizeof(char **) * (cmd_len + 1));
	if (!program->cmd)
	{
		perror("memory failure allocation");
		exit(1);
	}
	fill_cmd(program, i);
}