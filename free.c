/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:47:51 by itulgar           #+#    #+#             */
/*   Updated: 2024/09/08 18:22:34 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **tmp)
{
	int i = 0;
	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	if(tmp)
		free(tmp);
}