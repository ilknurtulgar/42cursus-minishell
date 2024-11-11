/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:23:50 by zayaz             #+#    #+#             */
/*   Updated: 2024/11/08 17:21:07 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	update_env(t_program *program, char *cwd)
{
	char	*oldpwd;
	char	*oldpwd_export;

	oldpwd = search_env("PWD", program->envp_list);
	oldpwd_export = search_env("PWD", program->export_list);
	if (!oldpwd || !oldpwd_export)
	{
		search_set_env(program, "OLDPWD", "\"\"", program->envp_list);
		search_set_env(program, "OLDPWD", "\"\"", program->export_list);
	}
	else
	{
		search_set_env(program, "OLDPWD", oldpwd, program->envp_list);
		search_set_env(program, "PWD", cwd, program->envp_list);
		search_set_env(program, "OLDPWD", oldpwd_export, program->export_list);
		search_set_env(program, "PWD", cwd, program->export_list);
	}
}

void	cd_add_list(t_program *program, char *key, char *content)
{
	t_mlist	*node_env;
	t_mlist	*node_export;

	node_env = zi_lstnew(content, key);
	node_export = zi_lstnew(content, key);
	zi_lstadd_back(&program->envp_list, node_env);
	zi_lstadd_back(&program->export_list, node_export);
}

static void	cd_path_helper(t_program *program, char *path)
{
	char	cwd[1024];

	if (chdir(path) == 0)
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			update_env(program, cwd);
	}
}

static void	cd_path(t_program *program, char *cmd)
{
	char		*path;
	struct stat	path_stat;

	path = cmd;
	if (access(path, F_OK) == 0)
	{
		stat(path, &path_stat);
		if (S_ISDIR(path_stat.st_mode))
			cd_path_helper(program, path);
		else
		{
			printf("minishell: cd: %s: Not a directory\n", path);
			program->status = 1;
		}
	}
	else
	{
		printf("cd: %s: No such file or directory\n", path);
		program->status = 1;
	}
}

void	cd(t_program *program, char **cmd)
{
	char	*home;
	char	cwd[1024];

	cd_helper(program);
	if (cmd[1] == NULL || (zi_strcmp(cmd[1], "~") == 0))
	{
		home = search_env("HOME", program->envp_list);
		if (home && chdir(home) == 0)
			getcwd(cwd, sizeof(cwd));
	}
	else if (zi_strcmp(cmd[1], "..") == 0)
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			if (chdir("..") == 0)
				getcwd(cwd, sizeof(cwd));
		}
	}
	else if (cmd[1])
	{
		cd_path(program, cmd[1]);
		return ;
	}
	update_env(program, cwd);
	program->status = 0;
}
