/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   late_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 19:30:00 by mergarci          #+#    #+#             */
/*   Updated: 2025/10/14 20:06:53 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Expande $? en una cadena justo antes de la ejecución
 */
char *expand_exit_status_in_string(char *str)
{
    char *result;
    char *exit_status_str;
    char *pos;
    char *before;
    char *after;
    char *temp;
    
    if (!str)
        return (NULL);
    
    // Caso especial: si la cadena es exactamente "$?"
    if (ft_strncmp(str, "$?", 3) == 0 && ft_strlen(str) == 2)
    {
        return (get_exit_status_string());
    }
    
    // Buscar $? en la cadena
    pos = ft_strnstr(str, "$?", ft_strlen(str));
    if (!pos)
        return (ft_strdup(str));  // No hay $?, devolver copia
    
    // Obtener el estado de salida como string
    exit_status_str = get_exit_status_string();
    if (!exit_status_str)
        return (ft_strdup(str));
    
    // Dividir la cadena en antes y después de $?
    before = ft_substr(str, 0, pos - str);
    after = ft_strdup(pos + 2);  // +2 para saltar "$?"
    
    if (!before || !after)
    {
        free(before);
        free(after);
        free(exit_status_str);
        return (ft_strdup(str));
    }
    
    // Construir el resultado: before + exit_status + after
    temp = ft_strjoin(before, exit_status_str);
    if (!temp)
    {
        free(before);
        free(after);
        free(exit_status_str);
        return (ft_strdup(str));
    }
    
    result = ft_strjoin(temp, after);
    
    // Limpiar memoria
    free(before);
    free(after);
    free(exit_status_str);
    free(temp);
    
    // Si hay más $? en el resultado, expandir recursivamente
    if (result && ft_strnstr(result, "$?", ft_strlen(result)))
    {
        char *final_result = expand_exit_status_in_string(result);
        free(result);
        return (final_result);
    }
    
    return (result ? result : ft_strdup(str));
}

/*
 * Expande $? en todos los argumentos de un array
 */
char **expand_exit_status_in_args(char **args)
{
    char **result;
    int i;
    int count;
    
    if (!args)
        return (NULL);
    
    // Contar argumentos
    count = 0;
    while (args[count])
        count++;
    
    // Crear array resultado
    result = malloc(sizeof(char *) * (count + 1));
    if (!result)
        return (NULL);
    
    // Expandir cada argumento
    for (i = 0; i < count; i++)
    {
        result[i] = expand_exit_status_in_string(args[i]);
        if (!result[i])
        {
            // Error: limpiar y devolver NULL
            while (--i >= 0)
                free(result[i]);
            free(result);
            return (NULL);
        }
    }
    result[count] = NULL;
    
    return (result);
}
