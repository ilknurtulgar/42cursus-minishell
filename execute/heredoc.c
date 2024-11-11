/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 18:20:33 by zayaz             #+#    #+#             */
/*   Updated: 2024/11/08 14:36:07 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	fork_with_heredoc(t_process hd_process, char *st)
{
	char	*line;

	close(hd_process.fd[0]);
	while (1)
	{
		line = readline(">");
		if (!line)
			break ;
		if (zi_strcmp(st, line) == 0)
		{
			close(hd_process.fd[1]);
			free(line);
			break ;
		}
		ft_putstr_fd(line, hd_process.fd[1]);
		ft_putchar_fd('\n', hd_process.fd[1]);
		free(line);
	}
	free(st);
}

static void	handle_heredoc(t_program *program, char *s)
{
	t_process	hd_process;
	char		*dst;
	char		*st;

	dst = NULL;
	st = NULL;
	if (pipe(hd_process.fd) == -1)
	{
		perror("minishell: pipe creation failed");
		exit(1);
	}
	hd_process.pid = fork();
	if (hd_process.pid == -1)
		return ;
	if (hd_process.pid == 0)
	{
		g_global_signal = IN_HERADOC;
		st = del_quote(dst, s, ft_strlen(s));
		fork_with_heredoc(hd_process, st);
		free(dst);
		close(hd_process.fd[1]);
		exit(0);
	}
	else
		parent_heredoc(program, hd_process);
}

void	doc_name_heredoc(t_program *program, int *i, int *j, int *z)
{
	char	*doc;

	doc = NULL;
	program->redi_type = program->parser_input[*i][*j]->cmd[*z];
	if (program->parser_input[*i][*j]->cmd[*z] == '<'
		&& (program->parser_input[*i][*j]->cmd[*z + 1]
			&& program->parser_input[*i][*j]->cmd[*z + 1] == '<')
		&& program->finish_check != 3)
	{
		(*z)++;
		doc = take_redi_doc(program, i, j, z);
		handle_heredoc_redirect(program, handle_heredoc, doc);
	}
}

static void	find_heredoc_loc(t_program *program, int *i, int *j, int *z)
{
	while (program->parser_input[*i][*j]->cmd[*z])
	{
		quote_skip(program->parser_input[*i][*j]->cmd, z);
		if (program->parser_input[*i][*j]->cmd[*z] == '<')
			doc_name_heredoc(program, i, j, z);
		if (program->parser_input[*i][*j]->cmd[*z] == '<'
			&& program->parser_input[*i][*j]->cmd[*z + 1]
			&& program->parser_input[*i][*j]->cmd[*z + 1] == '<')
			continue ;
		else if (program->parser_input[*i][*j]->cmd[*z]
			&& program->parser_input[*i][*j]->cmd[*z] != '\''
			&& program->parser_input[*i][*j]->cmd[*z] != '\"')
			(*z)++;
	}
}

void	heredoc_main(t_program *program)
{
	int	j;
	int	z;
	int	i;

	i = 0;
	program->redi_type = '\0';
	j = 0;
	z = 0;
	while (program->parser_input[i])
	{
		j = 0;
		while (program->parser_input[i][j] != NULL
			&& program->parser_input[i][j]->cmd)
		{
			z = 0;
			find_heredoc_loc(program, &i, &j, &z);
			if (program->finish_check == 3)
				return ;
			j++;
		}
		i++;
	}
}
