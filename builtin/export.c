/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:47:05 by zayaz             #+#    #+#             */
/*   Updated: 2024/11/03 20:52:02 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	*check_key(char *key, t_list *envpx_lst)
{
	t_list	*current;

	current = envpx_lst;
	while (current && current->key)
	{
		if (zi_strcmp(current->key, key) == 0)
			return(1);
		current = current->next;
	}
	return (0);
}

static void	export_env(t_program *program)
{
	t_list	*list;

	list = program->export_list;
	while (list != NULL)
	{
		if (list && (list->content != NULL && list->key != NULL))
		{
			if ((zi_strcmp(list->content, "(null)")) != 0)
				printf("declare -x %s=\"%s\"\n", (char *)list->key,
					(char *)list->content);
			else if (zi_strcmp(list->content, "(null)") == 0)
				printf("declare -x %s\n", (char *)list->key);
		}
		list = list->next;
	}
}

static char	*equals_key(char *cmd)
{
	char	*equ_key;
	int		len;
	int		i;

	equ_key = NULL;
	len = ft_strlen(cmd);
	equ_key = malloc(sizeof(char *) * (len + 1));
	if (equ_key == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (cmd[i] == 61)
		{
			equ_key[i] = '\0';
			return (equ_key);
		}
		equ_key[i] = cmd[i];
		i++;
	}
	equ_key[i] = '\0';
	return (equ_key);
}

static void	export_run(t_program *program, char **cmd, int i)
{
	char	*equ_key;
	t_list	*node;

	while (cmd[i])
	{
		equ_key = equals_key(cmd[i]);
		if (!check_identifier(equ_key))
			identifier_error(program, "export", cmd[i],
				":not a valid identifier");
		else  if (ft_strchr(cmd[i], 61) != 0)
		{
			equal_in_export(program, cmd, &i);
			program->status = 0;
		}
		else
		{
			if(check_key(cmd[i],program.export_list))
			{
			node = ft_lstnew("(null)", cmd[i]);
			ft_lstadd_back(&program->export_list, node);

			}
			program->status = 0;
			
		}
		if (equ_key)
			free(equ_key);
		i++;
	}
}

void	export(t_program *program, char **cmd)
{
	int	i;

	i = 1;
	if (!cmd[i])
		export_env(program);
	else if (cmd[i])
		export_run(program, cmd, i);
}
