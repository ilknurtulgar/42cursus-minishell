/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zayaz <zayaz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:03:58 by zayaz             #+#    #+#             */
/*   Updated: 2024/11/06 13:44:10 by zayaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static long	ft_atol(const char *str)
{
	long	num;
	int		sign;
	int		i;

	num = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num * sign);
}

static int	ft_isnumeric(char *str)
{
	int		i;
	long	num;

	num = ft_atol(str);
	i = 0;
	if (!str || !str[i])
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	if (num < INT_MIN || num > INT_MAX)
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	ft_exit_error(char *str, int status)
{
	if (str && str[0] != '\0')
		write(2, str, ft_strlen(str));
	exit(status);
}

void	ft_exit(t_program *program)
{
	write(1, "exit\n", 5);
	if (program->p_count == 0)
	{
		if (program->cmd[1] == NULL)
			ft_exit_error("", 0);
		if (!ft_isnumeric(program->cmd[1]))
		{
			exit_error("exit", program->cmd[1], ": numeric argument required");
			exit(255);
		}
		if (program->cmd[2] != NULL)
		{
			exit_error("exit", "", "too many arguments");
			program->status = 1;
			return ;
		}
		program->status = ft_atoi(program->cmd[1]) % 256;
		ft_exit_error("", program->status);
	}
}
