/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_simple.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 18:00:00 by mergarci          #+#    #+#             */
/*   Updated: 2025/11/25 15:57:32 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

/*
 * Versión simple y segura para almacenar environment
 * Usa un array de strings en lugar de lista enlazada
 */

static char **g_env_copy = NULL;
static int g_env_count = 0;

/*
 * Copia el environment de forma segura
 */
void env_save_simple(char **envp)
{
    int i;
    
    if (!envp)
        return;
    
    // Contar variables
    g_env_count = 0;
    while (envp[g_env_count])
        g_env_count++;
    
    // Asignar memoria para el array
    g_env_copy = malloc((g_env_count + 1) * sizeof(char *));
    if (!g_env_copy)
        return;
    
    // Copiar cada string
    for (i = 0; i < g_env_count; i++)
    {
        g_env_copy[i] = ft_strdup(envp[i]);
        if (!g_env_copy[i])
        {
            // Error: liberar lo que ya se copió
            while (--i >= 0)
                free(g_env_copy[i]);
            free(g_env_copy);
            g_env_copy = NULL;
            g_env_count = 0;
            return;
        }
    }
    g_env_copy[g_env_count] = NULL;
}

/*
 * Imprime el environment de forma segura
 */
void env_print_simple(void)
{
    int i;
    
    if (!g_env_copy)
    {
        ft_printf("Environment not initialized\n");
        return;
    }
    
    for (i = 0; i < g_env_count && i < 10; i++) // Limitar para debug
    {
        if (g_env_copy[i])
            ft_printf("%s\n", g_env_copy[i]);
    }
}

/*
 * Libera el environment
 */
void env_free_simple(void)
{
    int i;
    
    if (!g_env_copy)
        return;
    
    for (i = 0; i < g_env_count; i++)
    {
        if (g_env_copy[i])
            free(g_env_copy[i]);
    }
    free(g_env_copy);
    g_env_copy = NULL;
    g_env_count = 0;
}

/*
 * Obtiene una variable de entorno
 */
char *env_get_simple(const char *name)
{
    int i;
    int name_len;
    
    if (!g_env_copy || !name)
        return NULL;
    
    name_len = ft_strlen(name);
    
    for (i = 0; i < g_env_count; i++)
    {
        if (g_env_copy[i] && 
            ft_strncmp(g_env_copy[i], name, name_len) == 0 &&
            g_env_copy[i][name_len] == '=')
        {
            return g_env_copy[i] + name_len + 1;
        }
    }
    
    return NULL;
}
