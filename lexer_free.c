/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:25:23 by zayaz             #+#    #+#             */
/*   Updated: 2024/11/01 17:47:30 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dolar_free(char *env_str, char *after_dolar)
{
	if (env_str != NULL && env_str[0] != '\0')

		free(env_str);

	if (after_dolar)
		free(after_dolar);
}