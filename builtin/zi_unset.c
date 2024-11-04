/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zi_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zayaz <zayaz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:38:58 by zayaz             #+#    #+#             */
/*   Updated: 2024/11/03 19:22:07 by zayaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	del(void *content, void *key)
{
	free(content);
	free(key);
}

static t_list	*zi_lstdelone(t_list **lst, t_list *node, void (*del)(void *,
			void *))
{
	t_list	*tmp;

	if (!lst)
		return (*lst);
	if (*lst == node)
	{
		tmp = (*lst)->next;
		del((*lst)->content, (*lst)->key);
		free(*lst);
		*lst = tmp;
		return (*lst);
	}
	tmp = *lst;
	while (tmp && tmp->next != node)
		tmp = tmp->next;
	if (tmp && tmp->next == node)
	{
		tmp->next = node->next;
		del(node->content, node->key);
		free(node);
	}
	return (*lst);
}

static void	search_del_env(t_program *program, char *key, t_list **lst)
{
	t_list	*current;

	current = *lst;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(current->key)) == 0)
		{
			program->unset_flag = 1;
			*lst = zi_lstdelone(lst, current, del);
			break ;
		}
		else
			program->unset_flag = 0;
		if (!current->next)
			break ;
		current = current->next;
	}
}
void	identifier_error(char *cmd, char *s, char *message)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, ":", 1);
	write(2, "`", 1);
	write(2, s, ft_strlen(s));
	write(2, "'", 1);
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
}

int	check_identifier(char *cmd)
{
	int	i;

	i = 0;
	if (ft_isalpha(cmd[i]) || cmd[i] == 95)
	{
		while (cmd[i])
		{
			if ((cmd[i] >= 32 && cmd[i] <= 47) || (cmd[i] >= 58 && cmd[i] <= 64)
				|| (cmd[i] >= 91 && cmd[i] <= 96 && cmd[i] != 95)
				|| (cmd[i] >= 123 && cmd[i] <= 126))
				return (0);
			i++;
		}
		return (1);
	}
	else
		return (0);
}

void	zi_unset(t_program *program, char **cmd)
{
	int	i;
	int	error_flag;

	error_flag = 0;
	i = 1;
	if (!cmd[1])
		return ;
	if (cmd[i])
	{
		while (cmd[i])
		{
			if (!check_identifier(cmd[i]))
			{
				identifier_error("unset", cmd[i], " :not a valid identifier");
				program->status = 1;
				error_flag = 1;
			}
			else
			{
				search_del_env(program, cmd[i], &program->envp_list);
				search_del_env(program, cmd[i], &program->export_list);
				if (program->unset_flag == 0 && error_flag == 1)
					program->status = 1;
				else
					program->status = 0;
			}
			i++;
		}
	}
}
