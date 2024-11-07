/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_redirection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zayaz <zayaz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 20:19:08 by zayaz             #+#    #+#             */
/*   Updated: 2024/11/07 14:07:02 by zayaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*skip_quote(char *input)
{
	char	type;

	type = *input;
	input++;
	while (*input && *input != type)
		input++;
	if (*input == type)
		input++;
	return (input);
}

static int	count_redirect(char *input)
{
	int	i;

	i = 0;
	if (input == NULL)
		return (0);
	while (*input && (*input == '<' || *input == '>'))
	{
		input++;
		i++;
	}
	if (i > 2)
		return (0);
	return (1);
}

static int	redirect_check(char *input)
{
	if ((*input == '<' || *input == '>'))
	{
		if ((*input == '<' && *(input + 1) == '>') || (*input == '>' && *(input
					+ 1) == '<'))
		{
			return (0);
		}
		while (*input == 32)
			input++;
		if (*input == '\0' || ((*(input) == '<' || *(input) == '>') && *(input
					+ 1) == '\0'))
			return (0);
	}
	return (1);
}

int	p_redirection(t_program *program, char *input)
{
	while (*input)
	{
		if (*input && (*input == '\'' || *input == '\"'))
		{
			input = skip_quote(input);
			if (*input == '\0')
				break ;
		}
		if (!redirect_check(input))
			return (p_error(program, "syntax error to redirection"));
		if (!count_redirect(input))
			return (p_error(program, "syntax error to redirection"));
		if (*input && *input != '\'' && *input != '\"')
			input++;
	}
	return (1);
}
