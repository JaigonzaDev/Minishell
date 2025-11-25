/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 14:48:52 by mergarci          #+#    #+#             */
/*   Updated: 2025/11/25 16:01:49 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <stdlib.h>
#include "minishell.h"

void ft_env(t_env *enviroment)
{
    // (void)enviroment; // Usar la versión simple por seguridad
    
    // env_print_simple();
    t_env *tmp;
    tmp = enviroment;
    while(tmp->next != NULL)
    {
        printf("%s=%s\n", tmp->var, tmp->content);
        tmp = tmp->next;
    }
}

