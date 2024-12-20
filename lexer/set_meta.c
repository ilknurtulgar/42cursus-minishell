/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_meta.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:24:42 by zayaz             #+#    #+#             */
/*   Updated: 2024/11/07 17:52:57 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	s_dolar(char *meta, char q_type, int *i)
{
	int	j;

	j = 0;
	(*i)++;
	while (meta[*i] && meta[*i] != q_type)
	{
		if (j == 0)
			j = (*i) - 1;
		(*i)++;
	}
	if (zi_strrchr((meta + j), 36, (*i) - j) == 1 && (q_type == '\''
			&& meta[(*i) + 1] == '\0'))
		return (S_Dolar);
	return (0);
}

static int	set_dolar(char *meta)
{
	char	q_type;
	int		i;

	i = 0;
	while (meta[i])
	{
		if (meta[i] == '\'' || meta[i] == '\"')
		{
			q_type = meta[i];
			if (S_Dolar == s_dolar(meta, q_type, &i))
				return (S_Dolar);
			else if (q_type == '\"')
				return (Dolar);
		}
		else if (meta[i] == '$')
			return (Dolar);
		if (meta[i])
			i++;
	}
	return (S_Dolar);
}

static void	set_quote_redi(char *meta, int *i)
{
	char	q_type;

	q_type = '\0';
	q_type = meta[*i];
	(*i)++;
	while (meta[*i] && meta[*i] != q_type)
		(*i)++;
	if (meta[*i])
		(*i)++;
}

static int	set_redirect(char *meta)
{
	int	i;

	i = 0;
	while (meta[i])
	{
		if (meta[i] && (meta[i] == '\"' || meta[i] == '\''))
		{
			set_quote_redi(meta, &i);
			continue ;
		}
		if (meta[i] != '\0' && (meta[i] == '<' || meta[i] == '>'
				|| (meta[i] == '>' && meta[i + 1] == '>') || (meta[i] == '<'
					&& meta[i + 1] == '<')))
		{
			return (Redirect);
		}
		i++;
	}
	return (8);
}

int	set_meta( char *meta)
{
	if ((ft_strchr(meta, 34) == 0) && (ft_strchr(meta, 39) == 0))
	{
		if (!ft_strncmp(meta, "~", ft_strlen(meta)))
			return (Tilde);
		else if (ft_strchr(meta, 36))
			return (Dolar);
	}
	else if (ft_strchr(meta, 36))
		return (set_dolar(meta));
	if (ft_strchr(meta, '<') || ft_strchr(meta, '>'))
		return (set_redirect(meta));
	return (412);
}
