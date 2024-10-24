/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_redirection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zayaz <zayaz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 20:19:08 by zayaz             #+#    #+#             */
/*   Updated: 2024/10/16 18:45:21 by zayaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char *skip_quote(char *input)
{

	char type;
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

int p_redirection(t_program *program, char *input)
{
	(void)program;
	while ( *input)
	{
		//"<<"gı <hı>abu">>"anam"dünya">>gel gel"sene">">>>"<<susma > sustukca
		if (*input && (*input == '\'' || *input == '\"'))
		{
			input = skip_quote(input);
			if (*input == '\0')
				break;
		}
		if (!count_redirect(input))
			return (error_message("syntax error to redirection2"));

		if ((*input == '<' || *input == '>'))
		{
			if ((*input == '<' && *(input + 1) == '>') || (*input == '>' && *(input + 1) == '<'))
			{
				return (error_message("syntax error to redirection1"));
			}
			while (*input == 32)
				input++;
			if (*input == '\0' || ((*(input) == '<' || *(input) == '>') && *(input + 1) == '\0'))
				return (error_message("syntax error to redirection3"));
		}
		if (*input && *input != '\'' && *input != '\"')
			input++;
	}
	return (1);
}
