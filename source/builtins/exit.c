/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 14:49:37 by mergarci          #+#    #+#             */
/*   Updated: 2025/08/30 15:05:44 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void ft_exit(t_env **environment)
{
	if (environment  != NULL && *environment != NULL)
	{
		env_freeall(environment);
		*environment = NULL; // Marcar como liberado
	}
	exit(0);
}