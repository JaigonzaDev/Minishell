/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 10:51:51 by mergarci          #+#    #+#             */
/*   Updated: 2025/10/14 20:08:09 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

bool ft_is_builtin(char *command)
{
    if (!command)
        return (false);
    
    return (ft_strncmp(command, "cd", 3) == 0 ||
            ft_strncmp(command, "echo", 5) == 0 ||
            ft_strncmp(command, "env", 4) == 0 ||
            ft_strncmp(command, "exit", 5) == 0 ||
            ft_strncmp(command, "export", 7) == 0 ||
            ft_strncmp(command, "pwd", 4) == 0 ||
            ft_strncmp(command, "unset", 6) == 0 ||
            ft_strncmp(command, "true", 5) == 0 ||
            ft_strncmp(command, "false", 6) == 0);
}

int ft_execute_builtin(char **args, t_env **environment)
{
    int status = 0;  // Por defecto, éxito
    
    if (ft_strncmp(args[0], "cd", 3) == 0)
    {
        ft_cd(args[1], environment);
        status = 0;  // cd siempre retorna 0 por ahora
    }
    else if (ft_strncmp(args[0], "echo", 5) == 0)
    {
        ft_echo(args);
        status = 0;  // echo siempre tiene éxito
    }
    else if (ft_strncmp(args[0], "env", 4) == 0)
    {
        ft_env(*environment);
        status = 0;  // env siempre tiene éxito
    }
    else if (ft_strncmp(args[0], "exit", 5) == 0)
    {
        ft_exit(environment);
        status = 0;  // exit no debería retornar
    }
    else if (ft_strncmp(args[0], "export", 7) == 0)
    {
        status = ft_export(args, environment);  // Pasar todo el array args
    }
    else if (ft_strncmp(args[0], "pwd", 4) == 0)
    {
        ft_pwd();
        status = 0;  // pwd siempre tiene éxito
    }
    else if (ft_strncmp(args[0], "unset", 6) == 0)
    {
        ft_unset(args[1], environment);
        status = 0;  // unset siempre tiene éxito por ahora
    }
    else if (ft_strncmp(args[0], "true", 5) == 0)
    {
        status = ft_true();
    }
    else if (ft_strncmp(args[0], "false", 6) == 0)
    {
        status = ft_false();
    }
    
    update_exit_status(status);
    return (status);
}
