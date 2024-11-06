/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolar_handler2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zayaz <zayaz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:24:51 by zayaz             #+#    #+#             */
/*   Updated: 2024/11/06 21:13:57 by zayaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*dolar_env(t_program *program, char *parser_input)
{
	t_list	*current;

	current = program->envp_list;
	while (current)
	{
		if (!zi_strcmp(current->key, parser_input))
		{
			return (zi_strlcpy(parser_input, current->content,
					ft_strlen(current->content)));
		}
		current = current->next;
	}
	return (NULL);
}

char	*env_count_str(t_lexer *parser_input, int *i)
{
	char	*env_str;
	int		env_len;
	int		start_env;

	env_len = 0;
	(*i)++;
	start_env = *i;
	while (parser_input->cmd[*i] && (ft_isdigit(parser_input->cmd[*i])
			|| ft_isalpha(parser_input->cmd[*i])))
	{
		env_len++;
		(*i)++;
	}
	env_str = ft_substr(parser_input->cmd, start_env, env_len);
	return (env_str);
}

char	*set_dolar_question(t_program *program, char *cmd, int *i, char *key)
{
	if (cmd[(*i) + 1] && cmd[(*i) + 1] == '?')
	{
		(*i)++;
		key = ft_itoa(program->status);
		return (key);
	}
	return (NULL);
}

char	*expand_dollar_variables(t_program *program, int *i,
		t_lexer *parser_input)
{
	char	*key;
	char	*env_str;

	key = NULL;
	env_str = NULL;
	key = set_dolar_question(program, parser_input->cmd, i, key);
	if (key == NULL)
		return (set_expand_dollar_variables(parser_input, i, env_str, key,
				program));
	else
	{
		(*i)++;
		return (key);
	}
	return (env_str);
}

int	is_single_dollar(char *cmd)
{
	if (zi_strcmp(cmd, "\"$\"") == 0)
		return (0);
	if (zi_strcmp(cmd, "$") == 0)
		return (0);
	return (1);
}
