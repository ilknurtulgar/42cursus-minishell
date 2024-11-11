/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:03:53 by itulgar           #+#    #+#             */
/*   Updated: 2024/11/08 17:14:13 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*search_env(char *key, t_mlist *envpx_lst)
{
	t_mlist	*current;
	char	*envpx;

	envpx = NULL;
	current = envpx_lst;
	while (current && current->key)
	{
		if (zi_strcmp(current->key, key) == 0)
		{
			envpx = current->content;
			break ;
		}
		current = current->next;
	}
	return (envpx);
}

void	search_set_env(t_program *program, char *key, char *content,
		t_mlist *envpx_list)
{
	t_mlist	*current;

	current = envpx_list;
	while (current)
	{
		if (zi_strcmp(current->key, key) == 0)
		{
			program->export_flag = 1;
			free(current->content);
			current->content = ft_strdup(content);
			return ;
		}
		if (!current->next)
			break ;
		current = current->next;
	}
	program->export_flag = 0;
}

void	cd_helper(t_program *program)
{
	char	path_cwd[1024];

	if (search_env("PWD", program->envp_list) == NULL)
	{
		getcwd(path_cwd, sizeof(path_cwd));
		cd_add_list(program, "PWD", path_cwd);
	}
}
