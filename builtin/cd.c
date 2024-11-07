/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:23:50 by zayaz             #+#    #+#             */
/*   Updated: 2024/11/07 22:01:07 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*search_env(char *key, t_mlist *envpx_lst)
{
	t_mlist	*current;
	char	*envpx;

	envpx = NULL;
	current = envpx_lst;
	while (current && current->key)
	{
		if (zi_strcmp(current->key, key) == 0)
		{
			envpx = current->content;
			break ;
		}
		current = current->next;
	}
	return (envpx);
}

void	search_set_env(t_program *program, char *key, char *content,
		t_mlist *envpx_list)
{
	t_mlist	*current;

	current = envpx_list;
	while (current)
	{
		if (zi_strcmp(current->key, key) == 0)
		{
			program->export_flag = 1;
			free(current->content);
			current->content = ft_strdup(content);
			return ;
		}
		if (!current->next)
			break ;
		current = current->next;
	}
	program->export_flag = 0;
}

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

static void	cd_add_list(t_program *program, char *key, char *content)
{
	t_mlist	*node_env;
	t_mlist	*node_export;

	node_env = zi_lstnew(content, key);
	node_export = zi_lstnew(content, key);
	zi_lstadd_back(&program->envp_list, node_env);
	zi_lstadd_back(&program->export_list, node_export);
}

static void	cd_path(t_program *program, char *cmd)
{
	char		*path;
	char		cwd[1024];
	struct stat	path_stat;

	path = cmd;
	if (access(path, F_OK) == 0)
	{
		stat(path, &path_stat);
		if (S_ISDIR(path_stat.st_mode))
		{
			if (chdir(path) == 0)
			{
				if (getcwd(cwd, sizeof(cwd)) != NULL)
					update_env(program, cwd);
			}
		}
		else
		{
			printf("cd: %s: Not a directory\n", path);
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
	char	path_cwd[1024];

	if (search_env("PWD", program->envp_list) == NULL)
	{
		getcwd(path_cwd, sizeof(path_cwd));
		cd_add_list(program,"PWD",path_cwd);
	}
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

