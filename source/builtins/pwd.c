/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 12:44:27 by mergarci          #+#    #+#             */
/*   Updated: 2025/09/13 12:44:28 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void ft_pwd(void)
{
	char *cwd;
	
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		ft_printf("pwd: error getting current directory\n");
		return;
	}
	
	ft_printf("%s\n", cwd);
	free(cwd);
}