/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:25:00 by zayaz             #+#    #+#             */
/*   Updated: 2024/11/08 16:53:42 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	zi_strrchr(const char *s, int c, int i)
{
	if (!s[i])
		return (0);
	while (i >= 0 && s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (1);
		i--;
	}
	return (0);
}

char	*zi_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	dst = (char *)malloc(dstsize * sizeof(char) + 1);
	i = 0;
	if (!src || !dstsize)
		return (dst);
	while (i <= (dstsize - 1) && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

int	zi_strchr(const char *s, int c, char type)
{
	while (*s && *s != (char)c && *s != type)
		s++;
	if (*s == (char)c)
		return (1);
	return (0);
}

size_t	zi_strlen(char *s, char c, int dhand)
{
	int		i;
	char	q_type;

	i = 0;
	while (s[i])
	{
		if ((s[i] == '\"' || s[i] == '\'') && dhand)
		{
			q_type = s[i];
			if (is_close_quote(s, i, q_type))
				find_dollar_in_quotes(s, q_type, &i);
			else
				i++;
		}
		if (s[i] == c)
			return (i);
		if (s[i])
			i++;
	}
	return (i);
}
