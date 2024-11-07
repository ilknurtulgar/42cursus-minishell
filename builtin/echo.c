/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:36:01 by itulgar           #+#    #+#             */
/*   Updated: 2024/11/07 18:42:03 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	flag_helper(char *cmd, char c)
{
	if (*cmd == '\0')
		return (0);
	while (*cmd)
	{
		if (*cmd == c)
			cmd++;
		else if (*cmd != '\0')
			return (0);
	}
	return (1);
}

static int	flag_control(char **cmd, int *i)
{
	if (cmd[1][0] == '-' && cmd[1][1] == 'n')
	{
		if (cmd[*i] && cmd[*i][0] == '-' && (flag_helper(&cmd[*i][1], 'n') == 1
				|| zi_strcmp(&cmd[*i][1], "-n") == 0))
		{
			while (cmd[*i] && cmd[*i][0] == '-')
			{
				if (flag_helper(&cmd[*i][1], 'n') == 1 || zi_strcmp(&cmd[*i][1],
						"-n") == 1)
				{
					(*i)++;
					return (1);
				}
				if (cmd[*i])
					(*i)++;
			}
			return (1);
		}
	}
	return (0);
}

void	echo(t_program *program, char **cmd)
{
	int	flag;
	int	i;

	i = 1;
	if (cmd[i])
		flag = flag_control(cmd, &i);
	else
		flag = 0;
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		i++;
		if (cmd[i])
			printf(" ");
	}
	if (!flag)
		printf("\n");
	program->status = 0;
}
