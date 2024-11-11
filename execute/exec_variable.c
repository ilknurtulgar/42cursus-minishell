/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_variable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:41:36 by zayaz             #+#    #+#             */
/*   Updated: 2024/11/07 19:15:44 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_env_cmd(t_program *program)
{
	char	*tmp;
	int		env_size;
	int		i;
	t_mlist	*list;

	list = program->envp_list;
	i = 0;
	env_size = zi_lstsize(program->envp_list);
	program->env_cmd = malloc(sizeof(char *) * (env_size + 1));
	if (!program->env_cmd)
		return ;
	while (list != NULL)
	{
		tmp = ft_strjoin(list->key, "=");
		program->env_cmd[i] = ft_strjoin(tmp, list->content);
		free(tmp);
		list = list->next;
		i++;
	}
	program->env_cmd[i] = NULL;
}

void	find_path(t_program *program)
{
	int		i;
	char	*content;
	char	*new_path;

	i = 0;
	content = search_env("PATH", program->envp_list);
	if (content == NULL)
		program->sep_path = NULL;
	program->sep_path = ft_split(content, ':');
	while (program->sep_path && program->sep_path[i])
	{
		new_path = ft_strjoin(program->sep_path[i], "/");
		if (program->sep_path[i])
			free(program->sep_path[i]);
		program->sep_path[i] = new_path;
		i++;
	}
}

void	exec_error(t_program *program, char *s, int exit_codes)
{
	write(2, "minishell: ", ft_strlen("minishell: "));
	write(2, program->cmd[0], ft_strlen(program->cmd[0]));
	write(2, ":", 1);
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	program->status = exit_codes;
	exit(exit_codes);
}

static void	handle_path_error(t_program *program)
{
	if (access(program->cmd[0], F_OK) == -1 && ft_strchr(program->cmd[0], 47))
		exec_error(program, "No such file or directory", 127);
	else
		exec_error(program, "command not found", 127);
}

void	relative_path(t_program *program)
{
	struct stat	file_stat;

	if (stat(program->cmd[0], &file_stat) == 0)
	{
		if (S_ISREG(file_stat.st_mode) == 1)
		{
			if (file_stat.st_mode & S_IXUSR)
			{
				execve(program->cmd[0], program->cmd, program->env_cmd);
				exit(0);
			}
			else
				exec_error(program, "permission denied", 126);
		}
		else if (zi_strcmp(program->cmd[0], ".") == 0)
			exec_error(program, "filename argument required", 2);
		else if (zi_strcmp(program->cmd[0], "..") == 0)
			exec_error(program, "command not found", 127);
		else
			exec_error(program, "is a directory", 126);
	}
	else
		handle_path_error(program);
}
