/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zayaz <zayaz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:46:05 by zayaz             #+#    #+#             */
/*   Updated: 2024/11/07 13:28:42 by zayaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*zi_lstnew(void *content, char *key)
{
	t_list	*lst;

	lst = (t_list *)malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	lst->content = ft_strdup(content);
	lst->key = ft_strdup(key);
	lst->next = NULL;
	return (lst);
}

int	check_key(char *key, t_list *envpx_lst)
{
	t_list	*current;

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
	t_list	*node;
	t_list	*node2;

	if (program->export_flag == 0)
	{
		node = zi_lstnew(content, key);
		node2 = zi_lstnew(content, key);
		ft_lstadd_back(&program->envp_list, node);
		ft_lstadd_back(&program->export_list, node2);
	}
	free(key);
	free(content);
}

void	equals(char *cmd, int *k)
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
	export_add_list(program, key, content);
}
