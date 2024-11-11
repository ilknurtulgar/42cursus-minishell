/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:46:48 by zayaz             #+#    #+#             */
/*   Updated: 2024/11/08 16:59:51 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	env_print(t_program *program)
{
	t_mlist	*current;

	current = program->envp_list;
	while (current != NULL)
	{
		printf("%s=%s\n", (char *)current->key, (char *)current->content);
		current = current->next;
		program->status = 0;
	}
}

void	env(t_program *program, char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != NULL && ft_strncmp(cmd[i], "env", ft_strlen("env")) == 0
		&& cmd[i][3] == '\0')
		i++;
	if (search_env("PATH", program->envp_list) == NULL)
	{
		build_error(program, cmd[0], " No such file or directory");
		program->status = 127;
		return ;
	}
	if (program->cmd[i])
	{
		build_error(program, cmd[i], " No such file or directory");
		program->status = 127;
		return ;
	}
	env_print(program);
}
