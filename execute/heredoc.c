/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zayaz <zayaz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 18:20:33 by zayaz             #+#    #+#             */
/*   Updated: 2024/11/06 19:57:23 by zayaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	parent_heredoc(t_program *program, t_process hd_process)
{
	program->rdr_error = rdr_take_status(program, hd_process.pid);
	program->finish_check = program->rdr_error;
	close(hd_process.fd[1]);
	program->here_fd[0] = hd_process.fd[0];
}

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
		perror("pipe creation failed");
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

static void	find_heredoc_loc(t_program *program, int *i, int *j, int *z)
{
	char	*doc;

	doc = NULL;
	while (program->parser_input[*i][*j]->cmd[*z])
	{
		quote_skip(program->parser_input[*i][*j]->cmd, z);
		if (program->parser_input[*i][*j]->cmd[*z] == '<')
		{
			program->redi_type = program->parser_input[*i][*j]->cmd[*z];
			if (program->parser_input[*i][*j]->cmd[*z] == '<'
				&& (program->parser_input[*i][*j]->cmd[*z + 1]
					&& program->parser_input[*i][*j]->cmd[*z + 1] == '<')
				&& program->finish_check != 3)
			{
				(*z)++;
				doc = take_redi_doc(program, i, j, z);
				handle_redirect(program, handle_heredoc, doc);
			}
		}
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
			j++;
		}
		i++;
	}
}
