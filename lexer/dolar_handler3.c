/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolar_handler3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:05:55 by zayaz             #+#    #+#             */
/*   Updated: 2024/11/03 20:49:42 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
char    *dollar_join(char *env_str, char *before_cmd, char *after_dolar,
        char *tmp)
{
    char    *str;
    if (env_str == NULL || env_str[0] == '\0')
        tmp = ft_strjoin(before_cmd, after_dolar);
    else
    {
        if (env_str != NULL)
        {
            if (before_cmd[0] == '\0')
            {
                if (after_dolar[0] != '\0')
                    tmp = ft_strjoin(env_str, after_dolar);
                else
                    tmp = ft_strdup(env_str);
            }
            else
            {
                str = ft_strjoin(before_cmd, env_str);
                tmp = ft_strjoin(str, after_dolar);
            }
        }
        else
            tmp = ft_strjoin(before_cmd, after_dolar);
    }
    return (tmp);
}
char    *set_expand_dollar_variables(t_lexer *parser_input, int *i, char *env_str,
        char *key, t_program *program)
{
    if (ft_isdigit(ft_atoi(&parser_input->cmd[(*i) + 1]))
        || (parser_input->cmd[(*i) + 1] == '@' || parser_input->cmd[(*i)
            + 1] == '*') || parser_input->cmd[(*i) + 1] == '#')
    {
        (*i) += 2;
        return (NULL);
    }
    else if ((parser_input->cmd[(*i) + 1] != 32)
        && (!ft_isdigit(parser_input->cmd[(*i) + 1])
            || ft_isalpha(parser_input->cmd[(*i) + 1])))
    {
        env_str = env_count_str(parser_input, i);
        key = dolar_env(program, env_str);
        return (key);
    }
    else if (parser_input->cmd[(*i) + 1] == 32)
    {
        env_str = ft_strdup("$");
        (*i)++;
        return (env_str);
    }
    return NULL;
}
