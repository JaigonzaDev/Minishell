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
#include "libft.h"

static int is_valid_exit_code(char *str)
{
	int i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void ft_exit(char **args, t_env **environment)
{
	int exit_code;

	exit_code = 0;
	// Si hay argumento, intentar parsearlo
	if (args[1])
	{
		if (!is_valid_exit_code(args[1]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			exit_code = 2;
		}
		else if (args[2])
		{
			// Si hay más de un argumento
			ft_putendl_fd("minishell: exit: too many arguments", 2);
			// En este caso bash NO sale, solo retorna 1
			// Pero el subject puede requerir salir igual
			// Por ahora salimos con código 1
			exit_code = 1;
		}
		else
		{
			// Parsear el código (ft_atol para manejar números grandes)
			long num = ft_atol(args[1]);
			// Módulo 256 para comportamiento correcto (bash usa 8 bits)
			exit_code = (unsigned char)(num % 256);
		}
	}
	// Liberar environment antes de salir
	if (environment != NULL && *environment != NULL)
	{
		env_freeall(environment);
		*environment = NULL;
	}
	exit(exit_code);
}