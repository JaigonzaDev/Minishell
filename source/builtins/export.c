/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 12:44:24 by mergarci          #+#    #+#             */
/*   Updated: 2025/09/13 12:44:25 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// Carlos: >Imprimir todas las variables exportadas (export sin argumentos)<
static void print_exported_vars(t_env *env)
{
    t_env *tmp;
    
    tmp = env;
    while (tmp)
    {
        // Imprimir en formato: declare -x KEY="value"
        if (tmp->content && tmp->content[0] != '\0')
            printf("declare -x %s=\"%s\"\n", tmp->var, tmp->content);
        else
            printf("declare -x %s\n", tmp->var);
        tmp = tmp->next;
    }
}

// Carlos: >Validar que el nombre de variable sea válido (letras, números, _)<
static int is_valid_identifier(const char *str)
{
    int i;
    
    if (!str || !*str)
        return (0);
    
    // Primer carácter: letra o underscore
    if (!ft_isalpha(str[0]) && str[0] != '_')
        return (0);
    
    i = 1;
    while (str[i] && str[i] != '=')
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

// Carlos: >Extraer nombre de variable de "VAR=value"<
static char *extract_var_name(const char *arg)
{
    char *equal_sign;
    int len;
    
    equal_sign = ft_strchr(arg, '=');
    if (equal_sign)
        len = equal_sign - arg;
    else
        len = ft_strlen(arg);
    
    return (ft_substr(arg, 0, len));
}

// Carlos: >Extraer valor de "VAR=value"<
static char *extract_var_value(const char *arg)
{
    char *equal_sign;
    
    equal_sign = ft_strchr(arg, '=');
    if (equal_sign)
        return (ft_strdup(equal_sign + 1));
    return (NULL);
}

// Carlos: >Crear nodo de entorno<
static t_env *create_env_node(char *key, char *value)
{
    t_env *new_node;
    
    new_node = (t_env *)malloc(sizeof(t_env));
    if (!new_node)
        return (NULL);
    
    new_node->var = ft_strdup(key);
    new_node->content = ft_strdup(value ? value : "");
    new_node->next = NULL;
    
    return (new_node);
}

// Carlos: >Añadir o actualizar variable en el entorno<
static void add_or_update_env(t_env **env, char *key, char *value)
{
    t_env *current;
    t_env *new_node;
    
    // Buscar si ya existe
    current = *env;
    while (current)
    {
        if (ft_strncmp(current->var, key, ft_strlen(key) + 1) == 0)
        {
            // Actualizar valor existente
            if (value)
            {
                free(current->content);
                current->content = ft_strdup(value);
            }
            return;
        }
        current = current->next;
    }
    
    // No existe, crear nuevo nodo
    new_node = create_env_node(key, value);
    if (!new_node)
        return;
    
    // Añadir al final de la lista
    if (!*env)
    {
        *env = new_node;
        return;
    }
    
    current = *env;
    while (current->next)
        current = current->next;
    current->next = new_node;
}

// Carlos: >Función principal de export (firma corregida)<
int ft_export(char **args, t_env **env)
{
    int i;
    char *var_name;
    char *var_value;
    int exit_status;
    
    exit_status = 0;
    
    // Carlos: >Sin argumentos: mostrar todas las variables exportadas<
    if (!args[1])
    {
        print_exported_vars(*env);
        return (0);
    }
    
    // Carlos: >Con argumentos: exportar variables<
    i = 1;
    while (args[i])
    {
        var_name = extract_var_name(args[i]);
        
        // Validar identificador
        if (!is_valid_identifier(var_name))
        {
            ft_putstr_fd("minishell: export: `", STDERR_FILENO);
            ft_putstr_fd(args[i], STDERR_FILENO);
            ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
            free(var_name);
            exit_status = 1;
            i++;
            continue;
        }
        
        // Verificar si tiene valor (VAR=value)
        if (ft_strchr(args[i], '='))
        {
            var_value = extract_var_value(args[i]);
            add_or_update_env(env, var_name, var_value);
            free(var_value);
        }
        else
        {
            // Solo exportar sin cambiar valor (export VAR)
            add_or_update_env(env, var_name, NULL);
        }
        
        free(var_name);
        i++;
    }
    
    return (exit_status);
}