/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 12:44:20 by mergarci          #+#    #+#             */
/*   Updated: 2025/09/13 12:44:21 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void ft_echo(char **args)
{
	int i;
	bool newline;
		
	if (args == NULL)
	{
		ft_printf("\n");
		return;
	}
	
	i = 1; // Empezar desde el primer argumento (args[0] es "echo")
	newline = true; // Por defecto, imprimir nueva línea
	
	// Verificar si el primer argumento es "-n"
	if (args[i] != NULL && ft_strncmp(args[i], "-n", 3) == 0)
	{
		newline = false;
		i++; // Saltar el "-n"
	}
	
	// Imprimir todos los argumentos
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
	if (newline)
		ft_printf("\n");
}