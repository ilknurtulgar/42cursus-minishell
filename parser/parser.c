/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:57:38 by itulgar           #+#    #+#             */
/*   Updated: 2024/11/08 15:52:12 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	space_cmd(t_lexer *parser_input, char *split_space, int z)
{
	parser_input->cmd = ft_strdup(split_space);
	parser_input->key = set_meta(split_space);
	z++;
	return (z);
}

static int	fill_pipe_input(t_program *program, char *pipe_input, int *k)
{
	char	**split_space;
	int		j;
	int		z;

	split_space = NULL;
	split_space = zi_split(program, pipe_input, ' ', 1);
	program->parser_input[*k] = (t_lexer **)malloc((zi_count_string(pipe_input,
					' ') + 1) * sizeof(char *));
	if (!program->parser_input[*k])
	{
		free_array(split_space);
		free(pipe_input);
		return (error_message("Memory allocation"), -1);
	}
	j = 0;
	z = 0;
	while (split_space[j])
	{
		program->parser_input[*k][z] = (t_lexer *)malloc(sizeof(t_lexer));
		z = space_cmd(program->parser_input[*k][z], split_space[j], z);
		j++;
	}
	free_array(split_space);
	return (z);
}

static int	clean_input_helper(t_program *program, char **pipe_input, int *k)
{
	char	*trimmed;
	int		z;

	z = 0;
	while (pipe_input[*k])
	{
		trimmed = ft_strtrim(pipe_input[*k], " ,\t");
		free(pipe_input[*k]);
		pipe_input[*k] = trimmed;
		z = fill_pipe_input(program, pipe_input[*k], k);
		if (z == -1)
		{
			free_array(pipe_input);
			return (0);
		}
		program->parser_input[*k][z] = NULL;
		(*k)++;
	}
	return (1);
}

static int	clean_input(t_program *program, char *input)
{
	char	**pipe_input;
	int		k;

	k = 0;
	pipe_input = zi_split(program, input, '|', 0);
	program->parser_input = (t_lexer ***)malloc((zi_count_string(input, '|')
				+ 1) * sizeof(char **));
	if (!program->parser_input)
	{
		free_array(pipe_input);
		return (error_message("Memory allocation"));
	}
	if (clean_input_helper(program, pipe_input, &k) == 0)
		return (0);
	program->parser_input[k] = NULL;
	free_array(pipe_input);
	return (1);
}

int	ft_parser(t_program *program, char *input)
{
	if (!p_quote(program, input))
		return (0);
	if (!p_pipe(program, input))
		return (0);
	if (!p_redirection(program, program->input))
		return (0);
	if (!clean_input(program, input))
		return (0);
	run_dolar(program);
	if (program->fd_output > 2)
	{
		close(program->fd_output);
		program->fd_output = -1;
	}
	if (program->fd_input > 2)
	{
		close(program->fd_input);
		program->fd_input = -1;
	}
	return (1);
}
