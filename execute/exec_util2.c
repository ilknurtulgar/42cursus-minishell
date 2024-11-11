/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_util2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:00:15 by zayaz             #+#    #+#             */
/*   Updated: 2024/11/08 17:10:49 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redi_skip(t_lexer **parser_input, int *z, int *j)
{
	char	redi_type;

	if (parser_input[*j]->cmd[*z] && parser_input[*j]->cmd[*z] != '\''
		&& parser_input[*j]->cmd[*z] != '\"')
	{
		redi_type = parser_input[*j]->cmd[*z];
		(*z)++;
		if (parser_input[*j]->cmd[*z] == redi_type)
			(*z)++;
	}
	if (parser_input[*j]->cmd[*z] == '\0')
	{
		(*j)++;
		*z = 0;
	}
	while (parser_input[*j]->cmd[*z] && (parser_input[*j]->cmd[*z] != '<'
			&& parser_input[*j]->cmd[*z] != '>'))
	{
		if (parser_input[*j]->cmd[*z] && parser_input[*j]->cmd[*z] != '\''
			&& parser_input[*j]->cmd[*z] != '\"')
			(*z)++;
		else
			quote_skip(parser_input[*j]->cmd, z);
	}
}

void	fillable_count(char *cmd, int *z, int *count)
{
	while (cmd[*z] && (cmd[*z] != '<' && cmd[*z] != '>'))
	{
		if (cmd[*z] != '\'' && cmd[*z] != '\"')
			(*z)++;
		else
			quote_skip(cmd, z);
	}
	if (cmd[*z] == '\0' || (cmd[*z] == '<' || cmd[*z] == '>'))
		(*count)++;
}

int	redirect_c(t_program *program, int *i)
{
	int	j;

	j = 0;
	while (program->parser_input[*i] && program->parser_input[*i][j])
	{
		if (program->parser_input[*i][j]->key == 7)
			return (1);
		if (program->parser_input[*i][j]->key)
			j++;
	}
	return (0);
}

void	exec_command(t_program *program)
{
	int		i;
	char	*tmp_path;

	fill_env_cmd(program);
	find_path(program);
	i = 0;
	if (search_env("PATH", program->envp_list) == NULL
		&& program->cmd[0][0] != '/')
	{
		printf("minishell: %s: No such file or directory\n", program->cmd[i]);
		program->status = 127;
		return ;
	}
	if (program->cmd[0][0] == '.' || program->cmd[0][0] == '/'
		|| ft_strchr(program->cmd[0], '/'))
		relative_path(program);
	while (program->sep_path && program->sep_path[i])
	{
		tmp_path = ft_strjoin(program->sep_path[i], program->cmd[0]);
		if (access(tmp_path, F_OK) != -1)
			execve(tmp_path, program->cmd, program->env_cmd);
		i++;
		free(tmp_path);
	}
	free_path(program);
}

void	run_one_cmd(t_program *program, int *i)
{
	int	stdout_backup;
	int	stdin_backup;

	if (redirect_c(program, i))
	{
		stdout_backup = dup(STDOUT_FILENO);
		stdin_backup = dup(STDIN_FILENO);
		if (program->fd_input >= 2)
			dup2(program->fd_input, STDIN_FILENO);
		if (program->fd_output >= 2)
			dup2(program->fd_output, STDOUT_FILENO);
	}
	main_builtin(program);
	if (redirect_c(program, i))
	{
		if (program->fd_input >= 2)
			dup2(stdin_backup, STDIN_FILENO);
		if (program->fd_output >= 2)
			dup2(stdout_backup, STDOUT_FILENO);
		close(stdin_backup);
		close(stdout_backup);
	}
}
