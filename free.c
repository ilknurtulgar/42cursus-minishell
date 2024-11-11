/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:47:51 by itulgar           #+#    #+#             */
/*   Updated: 2024/11/07 18:59:25 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_envp_list(t_mlist *envp_list)
{
	t_mlist	*temp;

	while (envp_list)
	{
		temp = envp_list->next;
		free(envp_list->content);
		free(envp_list->key);
		free(envp_list);
		envp_list = temp;
	}
}

void	free_array(char **tmp)
{
	int	i;

	i = 0;
	while (tmp && tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	if (tmp)
		free(tmp);
}

void	free_parser_input(t_program *program)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!program->parser_input)
		return ;
	while (program->parser_input[i])
	{
		j = 0;
		while (program->parser_input[i][j])
		{
			if (program->parser_input[i][j]->cmd)
				free(program->parser_input[i][j]->cmd);
			free(program->parser_input[i][j]);
			j++;
		}
		free(program->parser_input[i]);
		i++;
	}
	free(program->parser_input);
}

void	free_program(t_program *program)
{
	if (!program)
		return ;
	if (program->input)
		free(program->input);
	if (program->parser_input)
		free_parser_input(program);
	if (program->envp_list)
		free_envp_list(program->envp_list);
	free(program);
}

void	dolar_free(char *env_str, char *after_dolar)
{
	if (env_str != NULL && env_str[0] != '\0')
		free(env_str);
	if (after_dolar)
		free(after_dolar);
}
