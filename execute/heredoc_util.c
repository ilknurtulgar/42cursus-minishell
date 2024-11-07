/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zayaz <zayaz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 20:40:03 by zayaz             #+#    #+#             */
/*   Updated: 2024/11/07 11:30:57 by zayaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parent_heredoc(t_program *program, t_process hd_process)
{
	program->rdr_error = rdr_take_status(program, hd_process.pid);
	program->finish_check = program->rdr_error;
	close(hd_process.fd[1]);
	program->here_fd[0] = hd_process.fd[0];
}

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

void	handle_heredoc_redirect(t_program *program,
		void run_redirect(t_program *, char *), char *doc)
{
	char	*clean_doc;

	clean_doc = NULL;
	if (doc != NULL)
	{
		clean_doc = del_quote(clean_doc, doc, ft_strlen(doc));
		free(doc);
		if (program->rdr_error == 2 || program->rdr_error == 1)
		{
			free(clean_doc);
			return ;
		}
		if (program->status != 1)
			run_redirect(program, clean_doc);
		free(clean_doc);
	}
}
