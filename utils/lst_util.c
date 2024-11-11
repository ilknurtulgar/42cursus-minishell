/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:12:08 by itulgar           #+#    #+#             */
/*   Updated: 2024/11/07 19:18:15 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_mlist	*zi_lstnew(void *content, char *key)
{
	t_mlist	*lst;

	lst = (t_mlist *)malloc(sizeof(t_mlist));
	if (!lst)
		return (NULL);
	lst->content = ft_strdup(content);
	lst->key = ft_strdup(key);
	lst->next = NULL;
	return (lst);
}

t_mlist	*zi_lstlast(t_mlist *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	zi_lstadd_back(t_mlist **lst, t_mlist *new)
{
	if (!lst || !new)
		return ;
	if (*lst)
		zi_lstlast(*lst)->next = new;
	else
		*lst = new;
}

int	zi_lstsize(t_mlist *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}
