/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolar_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 12:24:13 by itulgar           #+#    #+#             */
/*   Updated: 2024/11/08 17:31:32 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*after_quote(t_lexer *parser_input, char *before_cmd, int *i)
{
	char	*se_dolar;
	char	*before_tmp;

	se_dolar = before_dolar(parser_input, i, 0);
	if (se_dolar)
	{
		before_tmp = ft_strjoin(before_cmd, se_dolar);
		free(se_dolar);
	}
	while (parser_input->cmd[*i] && parser_input->cmd[*i] != 36)
		(*i)++;
	return (before_tmp);
}

static char	*before_dolar_assign(t_program *program, t_lexer *parser_input,
		char *before_cmd, int *i)
{
	char	*env_str;
	char	*after_dolar;
	char	*tmp;
	int		len;

	len = 0;
	tmp = NULL;
	env_str = NULL;
	env_str = expand_dollar_variables(program, i, parser_input);
	after_dolar = ft_substr(parser_input->cmd, *i, (ft_strlen(parser_input->cmd)
				- *i));
	len = zi_strlen(parser_input->cmd + *i, 36, 1);
	while (*i < len)
		(*i)++;
	tmp = dollar_join(env_str, before_cmd, after_dolar, tmp);
	dolar_free(env_str, after_dolar);
	return (tmp);
}

static void	dq_dolar_env(t_program *program, t_lexer *parser_input, int *i,
		char *before_cmd)
{
	char	*tmp;

	if (parser_input->cmd[*i] == '\"')
		before_cmd = after_quote(parser_input, before_cmd, i);
	if (parser_input->cmd[*i] == 36)
	{
		tmp = before_dolar_assign(program, parser_input, before_cmd, i);
		free(parser_input->cmd);
		if (tmp == NULL || tmp[0] == '\0')
			parser_input->cmd = ft_strdup("\0");
		else
			parser_input->cmd = ft_strdup(tmp);
		if (before_cmd)
			free(before_cmd);
		if (tmp)
			free(tmp);
	}
	return ;
}

int	dolar_handler_last(t_program *program, t_lexer *parser_input, int *i,
		char *before_cmd)
{
	int	len;

	len = 0;
	dq_dolar_env(program, parser_input, i, before_cmd);
	if (ft_strchr(parser_input->cmd, 36) == 0)
		len = *i;
	else
	{
		len = ft_strlen(parser_input->cmd);
		*i = 0;
	}
	return (len);
}

void	dolar_handler(t_program *program, t_lexer *parser_input)
{
	char	*before_cmd;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(parser_input->cmd);
	while (i < len)
	{
		if (!is_single_dollar(parser_input->cmd))
			break ;
		before_cmd = before_dolar(parser_input, &i, 1);
		if (parser_input->cmd[i] && (parser_input->cmd[i + 1] == '\0'))
			break ;
		else if (parser_input->cmd[i] && parser_input->cmd[i + 1] == 32
			&& ft_strchr(parser_input->cmd + i + 1, 36) == 0)
			break ;
		if (i >= len)
		{
			if (before_cmd)
				free(before_cmd);
			break ;
		}
		len = dolar_handler_last(program, parser_input, &i, before_cmd);
	}
}
