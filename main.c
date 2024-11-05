/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zayaz <zayaz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:25:29 by zayaz             #+#    #+#             */
/*   Updated: 2024/11/05 17:25:33 by zayaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//patlıyor echo "$USER$USERasd$PWD"
int	main(int argc, char **argv, char **envp)
{
	t_program *program;
	char *tmp;

	program = NULL;
	(void)argv;
	if (argc != 1)
	{
		error_message("Unvalid argument");
		exit(0);
	}
	program = malloc(sizeof(t_program));
	if (!program)
		return (0);
	ft_init_program(program, envp);
	while (1)
	{
		g_global_signal = 0;
		program->input = readline("minishell 🐥>");
		if (g_global_signal == 13)
		{
			program->status = 1;
			g_global_signal = 0;
		}
		tmp = ft_strtrim(program->input, " ");
		free(program->input);
		program->input = tmp;
		if (program->input)
			add_history(program->input);
		if (program->input == NULL)
			exit(1);
		if (!ft_parser(program, program->input))
			continue ;
		zi_exec(program);
		free_parser_input(program);
		free(tmp);
		free(program->process);
	}
	free_program(program);
	// system("leaks minishell");
}
