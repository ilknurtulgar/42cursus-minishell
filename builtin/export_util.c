/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:46:05 by zayaz             #+#    #+#             */
/*   Updated: 2024/11/08 17:50:21 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_key(char *key, t_mlist *envpx_lst)
{
	t_mlist	*current;

	current = envpx_lst;
	while (current && current->key)
	{
		if (zi_strcmp(current->key, key) == 0)
			return (1);
		current = current->next;
	}
	return (0);
}

static void	export_add_list(t_program *program, char *key, char *content)
{
	t_mlist	*node_env;
	t_mlist	*node_export;

	if (program->export_flag == 0)
	{
		node_env = zi_lstnew(content, key);
		node_export = zi_lstnew(content, key);
		zi_lstadd_back(&program->envp_list, node_env);
		zi_lstadd_back(&program->export_list, node_export);
	}
	free(key);
	free(content);
}

static void	equals(char *cmd, int *k)
{
	while (cmd[*k] != '\0' && cmd[*k] != 61)
		(*k)++;
	if (cmd && cmd[*k] == 61)
		(*k)++;
}

void	equal_in_export(t_program *program, char **cmd, int *i)
{
	char	*key;
	int		k;
	char	*content;
	int		equal;

	k = 0;
	equal = 0;
	equals(cmd[*i], &k);
	equal = k;
	key = ft_substr(cmd[*i], 0, k - 1);
	equals(cmd[*i], &k);
	content = ft_substr(cmd[*i], equal, k);
	search_set_env(program, key, content, program->export_list);
	search_set_env(program, key, content, program->envp_list);
	export_add_list(program, key, content);
}
