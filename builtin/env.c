/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:46:48 by zayaz             #+#    #+#             */
/*   Updated: 2024/11/07 21:45:46 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env(t_program *program, char **cmd)
{
	t_mlist	*current;
	int		i;

	i = 0;
	while (cmd[i] != NULL && ft_strncmp(cmd[i], "env", ft_strlen("env")) == 0
		&& cmd[i][3] == '\0')
		i++;
	if (cmd[i] == NULL)
	{
		if (search_env("PATH", program->envp_list) == NULL)
		{
			build_error(program, cmd[0], " No such file or directory");
			program->status=127;
			return ;
		}
		current = program->envp_list;
		while (current != NULL)
		{
			printf("%s=%s\n", (char *)current->key, (char *)current->content);
			current = current->next;
			program->status = 0;
		}
	}
	else
		build_error(program, cmd[i], " No such file or directory");
}
