/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zayaz <zayaz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:04:18 by zayaz             #+#    #+#             */
/*   Updated: 2024/11/06 20:40:50 by zayaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	zi_redirectchr(const char *s, char c)
{
	char	type;

	while (*s)
	{
		if (*s == '\'' || *s == '\"')
		{
			type = *s;
			s++;
			while (*s && *s != type)
				s++;
			if (*s == type)
				s++;
		}
		if (*s == c && *(s + 1) == c)
			return (1);
		if (*s)
			s++;
	}
	return (0);
}

void	quote_skip(char *cmd, int *z)
{
	char	q_type;

	if (cmd[*z] == '\'' || cmd[*z] == '\"')
	{
		q_type = cmd[*z];
		(*z)++;
		while (cmd[*z] && cmd[*z] != q_type)
			(*z)++;
		if (cmd[*z] == q_type)
			(*z)++;
	}
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

void	find_loc(char *cmd, int *z)
{
	while (cmd[*z] != '\0' && cmd[*z] != '>' && cmd[*z] != '<')
	{
		quote_skip(cmd, z);
		if (cmd[*z] && (cmd[*z] != '\'' && cmd[*z] != '\"') && (cmd[*z] != '>'
				&& cmd[*z] != '<'))
			(*z)++;
	}
}
