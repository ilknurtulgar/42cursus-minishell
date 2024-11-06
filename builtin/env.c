/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zayaz <zayaz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:46:48 by zayaz             #+#    #+#             */
/*   Updated: 2024/11/06 13:43:49 by zayaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env(t_program *program, char **cmd)
{
	t_list	*current;
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
