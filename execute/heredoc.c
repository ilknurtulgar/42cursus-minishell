/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zayaz <zayaz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 18:20:33 by zayaz             #+#    #+#             */
/*   Updated: 2024/11/03 18:45:34 by zayaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	heredoc_count(t_program *program)
{
	int	i;
	int	j;
	int	hd;

	i = 0;
	j = 0;
	hd = 0;
	while (program->parser_input[i])
	{
		j = 0;
		while (program->parser_input[i][j])
		{
			if (zi_redirectchr(program->parser_input[i][j]->cmd, '<') != 0
				&& program->parser_input[i][j]->key == 7)
				hd++;
			j++;
		}
		i++;
	}
	return (hd);
}

int	zi_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i]))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	built_strcmp(const char *s1, const char *s2, size_t dest_size)
{
	size_t	i;

	i = 0;
	if (!s1[i] || !s2[i])
		return (-1);
	while (s1[i] == s2[i] && s1[i] && s2[i] && dest_size > i)
		i++;
	if (i == dest_size && (s2[i] == '\0' || s2[i] == ' '))
		return (0);
	return (-1);
}

static void	parent_heredoc(t_program *program, t_process hd_process)
{
	program->rdr_error = rdr_take_status(program, hd_process.pid);
	//waitpid(hd_process.pid, &program->status, 0);
	close(hd_process.fd[1]);
	program->here_fd[0] = hd_process.fd[0];
}

void	heredoc(t_program *program, char *s)
{
	char		*line;
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
		free(dst);
		close(hd_process.fd[1]);
		exit(0);
	}
	else
		parent_heredoc(program, hd_process);
}

void	heredoc_run(t_program *program)
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
			while (program->parser_input[i][j]->cmd[z])
			{
				quote_skip(program->parser_input[i][j]->cmd, &z);
				if (program->parser_input[i][j]->cmd[z] == '<')
				{
					program->redi_type = program->parser_input[i][j]->cmd[z];
					if (program->parser_input[i][j]->cmd[z] == '<'
						&& (program->parser_input[i][j]->cmd[z + 1]
							&& program->parser_input[i][j]->cmd[z + 1] == '<'))
					{
						z++;
						load_redi(program, heredoc, &i, &j, &z);
					}
				}
				if (program->parser_input[i][j]->cmd[z]
					&& program->parser_input[i][j]->cmd[z] != '\''
					&& program->parser_input[i][j]->cmd[z] != '\"')
					z++;
			}
			j++;
		}
		i++;
	}
}
