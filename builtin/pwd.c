/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:37:45 by zayaz             #+#    #+#             */
/*   Updated: 2024/10/05 16:58:20 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd(void)
{
	// büyük küçük harf duyarsız
	char pwd[1024];
	getcwd(pwd, sizeof(pwd));
	printf("%s\n", pwd);
}