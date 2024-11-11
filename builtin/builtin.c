/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:58:07 by itulgar           #+#    #+#             */
/*   Updated: 2024/11/08 17:00:05 by itulgar          ###   ########.fr       */
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

void	handle_unset_identifier(t_program *program, char **cmd, int *i)
{
	int	error_flag;

	error_flag = 0;
	if (!check_identifier(cmd[*i]))
	{
		identifier_error(program, "unset", cmd[*i], " :not a valid identifier");
		error_flag = 1;
	}
	else
	{
		search_del_env(program, cmd[*i], &program->envp_list);
		search_del_env(program, cmd[*i], &program->export_list);
		if (program->unset_flag == 0 && error_flag == 1)
			program->status = 1;
		else if (program->flag_identifier != 1)
			program->status = 0;
	}
}
