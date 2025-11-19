/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 14:48:52 by mergarci          #+#    #+#             */
/*   Updated: 2025/08/30 17:50:13 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <stdlib.h>

void ft_env(t_env *enviroment)
{
    (void)enviroment; // Usar la versión simple por seguridad
    
    env_print_simple();
}

