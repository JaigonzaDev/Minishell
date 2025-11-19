/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 21:55:00 by mergarci          #+#    #+#             */
/*   Updated: 2025/10/30 12:15:54 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Verifica si un carácter es un operador de shell
 */
static int is_shell_operator(char c)
{
    return (c == '<' || c == '>' || c == '|');
}

/*
 * Verifica si estamos al inicio de un operador compuesto (>>, <<)
 */
static int is_compound_operator(char *str)
{
    if (!str || !str[0] || !str[1])
        return (0);
    
    return ((str[0] == '>' && str[1] == '>') || 
            (str[0] == '<' && str[1] == '<'));
}

int handle_literal_str(char *str, char last)
{
    if (last == '\"' && ft_strnstr(str, "\"", ft_strlen(str)) != NULL)
        return (1);
    if (last == '\'' && ft_strnstr(str, "\'", ft_strlen(str)) != NULL)
        return (1);
    return (0);
}
/*
 * Separa operadores pegados al texto
 * Ejemplo: "<file" -> "< file", "file>" -> "file >"
 */
char *separate_operators(char *input)
{
    char *result;
    char *temp;
    int i, j;
    int len;
    int new_len;
    
    if (!input)
        return (NULL);
    
    len = ft_strlen(input);
    
    // Calcular nueva longitud (peor caso: cada carácter necesita espacio extra)
    new_len = len * 2;
    result = (char *)ft_calloc(new_len + 1, sizeof(char));
    if (!result)
        return (NULL);
    
    i = 0;
    j = 0;
    
    while (i < len)
    {
        // Si encontramos un operador compuesto (>>, <<)
        if (is_compound_operator(&input[i]))
        {
            // Agregar espacio antes si no estamos al inicio y el carácter anterior no es espacio
            if (j > 0 && result[j - 1] != ' ' && !handle_literal_str(&input[i], result[j - 1]))
                result[j++] = ' ';
            
            // Agregar el operador compuesto
            result[j++] = input[i++];
            result[j++] = input[i++];
            
            // Agregar espacio después si el siguiente carácter no es espacio ni fin de cadena
            if (i < len && input[i] != ' ' && input[i] != '\t' && !handle_literal_str(&input[i], result[j - 1]))
                result[j++] = ' ';
        }
        // Si encontramos un operador simple (<, >, |)
        else if (is_shell_operator(input[i]))
        {
            // Agregar espacio antes si no estamos al inicio y el carácter anterior no es espacio
            if (j > 0 && result[j - 1] != ' ' && !handle_literal_str(&input[i], result[j - 1]))
                result[j++] = ' ';
            
            // Agregar el operador
            result[j++] = input[i++];
            
            // Agregar espacio después si el siguiente carácter no es espacio ni fin de cadena
            if (i < len && input[i] != ' ' && input[i] != '\t' && !handle_literal_str(&input[i], result[j - 1]))
                result[j++] = ' ';
        }
        else
        {
            // Carácter normal, copiarlo tal como está
            result[j++] = input[i++];
        }
    }
    
    result[j] = '\0';
    
    // Redimensionar para ahorrar memoria
    temp = ft_strdup(result);
    free(result);
    
    return (temp);
}
