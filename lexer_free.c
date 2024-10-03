/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zayaz <zayaz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:25:23 by zayaz             #+#    #+#             */
/*   Updated: 2024/10/01 19:25:25 by zayaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dolar_free(char *env_str, char *after_dolar)
{
	if (env_str[0] != '\0')
		free(env_str);
	if (after_dolar)
		free(after_dolar);
}