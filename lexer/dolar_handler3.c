/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolar_handler3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zayaz <zayaz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:05:55 by zayaz             #+#    #+#             */
/*   Updated: 2024/11/06 21:36:53 by zayaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*before_empty_dollar(char *env_str, char *after_dolar, char *tmp)
{
	if (after_dolar[0] != '\0')
		tmp = ft_strjoin(env_str, after_dolar);
	else
		tmp = ft_strdup(env_str);
	return (tmp);
}

char	*dollar_join(char *env_str, char *before_cmd, char *after_dolar,
		char *tmp)
{
	char	*str;

	if (env_str == NULL || env_str[0] == '\0')
		tmp = ft_strjoin(before_cmd, after_dolar);
	else
	{
		if (env_str != NULL)
		{
			if (before_cmd[0] == '\0')
				tmp = before_empty_dollar(env_str, after_dolar, tmp);
			else
			{
				str = ft_strjoin(before_cmd, env_str);
				tmp = ft_strjoin(str, after_dolar);
				free(str);
			}
		}
		else
			tmp = ft_strjoin(before_cmd, after_dolar);
	}
	return (tmp);
}

char	*set_expand_dollar_variables(t_lexer *parser_input, int *i,
		char *env_str, char *key, t_program *program)
{
	if ((parser_input->cmd[(*i) + 1] == '@' || parser_input->cmd[(*i)
			+ 1] == '*') || parser_input->cmd[(*i) + 1] == '#')
	{
		(*i) += 2;
		return (NULL);
	}
	if ((parser_input->cmd[(*i) + 1] != 32 || ft_isalpha(parser_input->cmd[(*i)
				+ 1])))
	{
		if (ft_isdigit(parser_input->cmd[(*i) + 1]))
		{
			env_str = ft_strdup(&parser_input->cmd[(*i) + 1]);
			(*i) += 2;
		}
		else
			env_str = env_count_str(parser_input, i);
		key = dolar_env(program, env_str);
		if (env_str)
			free(env_str);
		return (key);
	}
	else if (parser_input->cmd[(*i)] == 36 && parser_input->cmd[(*i) + 1] == 32)
	{
		env_str = ft_strdup("$");
		(*i)++;
		return (env_str);
	}
	return (NULL);
}

char	*before_dolar(t_lexer *parser_input, int *i, int is_in)
{
	int		len;
	char	*before_cmd;

	len = 0;
	len = zi_strlen(parser_input->cmd + *i, 36, is_in);
	before_cmd = ft_substr(parser_input->cmd, *i, len);
	while (*i < len)
		(*i)++;
	return (before_cmd);
}
