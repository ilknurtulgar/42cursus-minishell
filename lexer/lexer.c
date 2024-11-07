/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zayaz <zayaz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:42:31 by itulgar           #+#    #+#             */
/*   Updated: 2024/11/07 12:46:04 by zayaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*pass_quote_cmd(t_lexer *parser_input, char *tmp, int *j, int *i)
{
	char	q_type;

	if (parser_input->cmd[*i] == '\'' || parser_input->cmd[*i] == '\"')
	{
		q_type = parser_input->cmd[*i];
		(*i)++;
		while (parser_input->cmd[*i] && parser_input->cmd[*i] != q_type)
		{
			tmp[*j] = parser_input->cmd[*i];
			(*i)++;
			(*j)++;
		}
	}
	else if (parser_input->cmd[*i] && parser_input->cmd[*i] != '\"'
		&& parser_input->cmd[*i] != '\'')
	{
		tmp[*j] = parser_input->cmd[*i];
		(*j)++;
	}
	return (tmp);
}

void	f(t_lexer *parser_inputiz)
{
	int		i;
	char	*tmp;
	int		j;

	tmp = (char *)malloc((ft_strlen(parser_inputiz->cmd) + 1) * sizeof(char));
	if (!tmp)
		printf("Memory allocation");
	else
	{
		j = 0;
		i = 0;
		while (parser_inputiz->cmd[i] != '\0')
		{
			tmp = pass_quote_cmd(parser_inputiz, tmp, &j, &i);
			if (parser_inputiz->cmd[i])
				i++;
		}
		tmp[j] = '\0';
		free(parser_inputiz->cmd);
		parser_inputiz->cmd = ft_strdup(tmp);
		free(tmp);
	}
}

void	quote_clean(t_program *program)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (program->parser_input[i])
	{
		j = 0;
		while (program->parser_input[i][j])
		{
			if (ft_strchr(program->parser_input[i][j]->cmd, 36))
				dolar_handler(program, program->parser_input[i][j]);
			j++;
		}
		i++;
	}
}
