/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 12:44:20 by mergarci          #+#    #+#             */
/*   Updated: 2025/11/25 17:23:03 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

// void ft_echo(char **args)
// {
// 	int i;
// 	bool newline;
		
// 	if (args == NULL)
// 	{
// 		ft_printf("\n");
// 		return;
// 	}
	
// 	i = 1; // Empezar desde el primer argumento (args[0] es "echo")
// 	newline = TRUE; // Por defecto, imprimir nueva línea
	
// 	// Verificar si el primer argumento es "-n"
// 	if (args[i] != NULL && ft_strncmp(args[i], "-n", 2) == 0)
// 	{
// 		newline = FALSE;
// 		i++; // Saltar el "-n"
// 	}
	
// 	// Imprimir todos los argumentos
// 	while (args[i])
// 	{
// 		ft_printf("%s", args[i]);
// 		if (args[i + 1] != NULL)
// 			ft_printf(" ");
// 		i++;
// 	}
// 	if (newline)
// 		ft_printf("\n");
// }

void ft_echo(char **args)
{
    int i;
    bool newline;

    if (args == NULL || args[0] == NULL)
    {
        ft_printf("\n");
        return;
    }

    i = 1; // Empezar desde el primer argumento (args[0] es "echo")
    newline = TRUE; // Por defecto, imprimir nueva línea

    // Manejar múltiples opciones "-n"
    while (args[i] != NULL && ft_strncmp(args[i], "-n", 2) == 0)
    {
        int j = 2;
        while (args[i][j] == 'n') // Verificar si todos los caracteres son 'n'
            j++;
        if (args[i][j] == '\0') // Si es una opción válida "-n"
        {
            newline = FALSE;
            i++;
        }
        else
            break; // Salir si no es una opción válida
    }

    // Imprimir todos los argumentos restantes
    while (args[i])
    {
        ft_printf("%s", args[i]);
        if (args[i + 1] != NULL)
            ft_printf(" ");
        i++;
    }

    // Imprimir nueva línea si corresponde
    if (newline)
        ft_printf("\n");
}