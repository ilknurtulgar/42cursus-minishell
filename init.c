/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:32:15 by itulgar           #+#    #+#             */
/*   Updated: 2024/11/05 17:28:38 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*set_env(char **envp)
{
	int		i;
	t_list	*tmp_list;
	char	**tmp;

	tmp_list = NULL;
	i = 0;
	while (envp[i])
	{
		tmp = ft_split(envp[i], '=');
		if (tmp[0] && tmp[1])
			ft_lstadd_back(&tmp_list, ft_lstnew(tmp[1], tmp[0]));
		free_array(tmp);
		i++;
	}
	return (tmp_list);
}

void	ft_init_program(t_program *program, char **envp)
{
	program->input = NULL;
	program->envp_list = set_env(envp);
	program->export_list = set_env(envp);
	program->check_quote = 1;
	program->p_count = 0;
	program->fd_input = 0;
	program->fd_output = 0;
	program->control_q_split = 0;
	program->control_p_split = 0;
	program->status = 0;
	program->hd_flag = malloc(sizeof(int));
	*program->hd_flag = 0;
	program->rdr_error = 0;
	signal_init();
}