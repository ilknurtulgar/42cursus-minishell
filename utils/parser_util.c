/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zayaz <zayaz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:25:09 by zayaz             #+#    #+#             */
/*   Updated: 2024/11/07 14:31:57 by zayaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*in_quote_string(char *s, char c)
{
	s++;
	while (*s && *s != c)
		s++;
	if (*s == c)
		s++;
	return (s);
}

int	zi_count_string(char *s, char c)
{
	int		count;
	char	quote_type;

	count = 0;
	while (*s)
	{
		if (*s == '\'' || *s == '\"')
		{
			quote_type = *s;
			s = in_quote_string(s, quote_type);
		}
		else
		{
			while (*s && *s != c && (*s != '\'' && *s != '\"'))
				s++;
		}
		if (*s == c || *s == '\0')
		{
			if (*s)
				s++;
			count++;
		}
	}
	return (count);
}

static int	in_quote_char(char *s, int i)
{
	char	quote_type;

	quote_type = s[i];
	i++;
	while (s[i] && s[i] != quote_type)
		i++;
	if (s[i] == quote_type)
		i++;
	return (i);
}

static int	zi_count_char(char *s, char c)
{
	int	i;
	int	f;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			i = in_quote_char(s, i);
		else
		{
			if (i == 0)
			{
				f = i;
				while (s[f] && s[f] == c)
					f++;
			}
			while (s[i] && s[i] != c && s[i] != '\'' && s[i] != '\"')
				i++;
			if (s[i] == c || s[i] == '\0')
				return (i);
		}
	}
	return (i);
}

char	**zi_split(t_program *program, char *s, char c, int is_space)
{
	int word = 0;
	int i = 0;
	int x = 0;
	char **s1;
	if (!s)
		return (NULL);
	word = zi_count_string(s, c);
	s1 = ft_calloc(word + 1, sizeof(char *));
	if (!s1)
		return (NULL);
	while (*s)
	{
		i = zi_count_char(s, c);

		s1[x++] = ft_substr(s, 0, i);
		s = walk_string(program, s, c, is_space);
	}
	s1[x] = NULL;
	return (s1);
}