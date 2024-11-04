/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zayaz <zayaz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:58:07 by itulgar           #+#    #+#             */
/*   Updated: 2024/11/03 13:47:24 by zayaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	main_builtin(t_program *program)
{
	if ((zi_strcmp(program->cmd[0], "cd") == 0))
		cd(program, program->cmd);
	else if ((zi_strcmp(program->cmd[0], "unset") == 0))
		zi_unset(program, program->cmd);
	else if ((zi_strcmp(program->cmd[0], "exit") == 0))
		ft_exit(program);
	if (zi_strcmp(program->cmd[0], "env") == 0)
		env(program, program->cmd);
	else if (zi_strcmp(program->cmd[0], "echo") == 0)
		echo(program, program->cmd);
	else if (zi_strcmp(program->cmd[0], "pwd") == 0)
		pwd(program);
	else if ((zi_strcmp(program->cmd[0], "export") == 0))
		export(program, program->cmd);
}

void	child_builtin(t_program *program)
{
	if ((zi_strcmp(program->cmd[0], "cd") == 0))
		cd(program, program->cmd);
	else if ((zi_strcmp(program->cmd[0], "unset") == 0))
		zi_unset(program, program->cmd);
	else if ((zi_strcmp(program->cmd[0], "exit") == 0))
		ft_exit(program);
	if (zi_strcmp(program->cmd[0], "env") == 0)
		env(program, program->cmd);
	else if (zi_strcmp(program->cmd[0], "echo") == 0)
		echo(program, program->cmd);
	else if (zi_strcmp(program->cmd[0], "pwd") == 0)
		pwd(program);
	else if ((zi_strcmp(program->cmd[0], "export") == 0))
		export(program, program->cmd);
	exit(0);
}

int	is_builtin(t_program *program)
{
	if (!program->parser_input || !program->parser_input[0]
		|| !program->parser_input[0][0] || !program->parser_input[0][0]->cmd)
		return (0);
	if ((zi_strcmp(program->cmd[0], "env") == 0) || (zi_strcmp(program->cmd[0],
				"echo") == 0) || (zi_strcmp(program->cmd[0], "pwd") == 0)
		|| (zi_strcmp(program->cmd[0], "cd") == 0)
		|| (zi_strcmp(program->cmd[0], "unset") == 0)
		|| (zi_strcmp(program->cmd[0], "exit") == 0)
		|| (zi_strcmp(program->cmd[0], "export") == 0))

		return (1);

	return (0);
}