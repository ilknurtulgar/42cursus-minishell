/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_quote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zayaz <zayaz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:10:17 by zayaz             #+#    #+#             */
/*   Updated: 2024/11/03 17:10:56 by zayaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*quote_check(t_program *program, char *input, char c)
{
	int	i;

	i = 0;
	program->check_quote = 0;
	while (input[i])
	{
		if (input[i] == c)
		{
			program->check_quote = 1;
			break ;
		}
		i++;
	}
	return (input + i);
}

static char	*quote_handler(t_program *program, char *input, char quote)
{
	input = quote_check(program, input + 1, quote);
	return (input);
}

int	p_quote(t_program *program, char *input)
{
	while (*input)
	{
		if (*input == '\'' || *input == '\"')
			input = quote_handler(program, input, *input);
		if (program->check_quote == 0)
			return (p_error(program, "syntax error to quote"), 0);
		if (!*input)
			break ;
		input++;
	}
	return (1);
}
