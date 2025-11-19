/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 19:30:00 by mergarci          #+#    #+#             */
/*   Updated: 2025/10/14 20:07:30 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

/*
 * Obtiene la variable PATH del entorno
 */
static char *get_path_env(char **envp)
{
    int i;
    
    if (!envp)
        return ("/usr/local/bin:/usr/bin:/bin");
    
    i = 0;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], "PATH=", 5) == 0)
            return (envp[i] + 5);
        i++;
    }
    
    // PATH por defecto si no se encuentra
    return ("/usr/local/bin:/usr/bin:/bin");
}

/*
 * Obtiene la variable PATH desde t_env (fallback)
 */
static char *get_path_from_env_list(t_env *env)
{
    t_env *current;
    
    current = env;
    while (current)
    {
        if (current->var && ft_strncmp(current->var, "PATH", 4) == 0)
            return (current->content);
        current = current->next;
    }
    
    // PATH por defecto si no se encuentra
    return ("/usr/local/bin:/usr/bin:/bin");
}

/*
 * Obtiene la variable PATH desde la versión simple del environment
 */
static char *get_path_from_env_simple(void)
{
    char *path = env_get_simple("PATH");
    
    if (path)
        return (path);
    
    // PATH por defecto si no se encuentra
    return ("/usr/local/bin:/usr/bin:/bin");
}

/*
 * Construye la ruta completa del comando
 */
static char *build_command_path(char *dir, char *command)
{
    char *temp;
    char *full_path;
    
    if (!dir || !command)
        return (NULL);
    
    // Si el directorio no termina en '/', añadirlo
    if (dir[ft_strlen(dir) - 1] != '/')
    {
        temp = ft_strjoin(dir, "/");
        if (!temp)
            return (NULL);
        full_path = ft_strjoin(temp, command);
        free(temp);
    }
    else
    {
        full_path = ft_strjoin(dir, command);
    }
    
    return (full_path);
}

/*
 * Busca un comando en el PATH
 */
char *find_command_in_path(char *command, char **envp, t_env *env)
{
    char *path_env;
    char **path_dirs;
    char *full_path;
    int i;
    
    if (!command)
        return (NULL);
    
    // Si el comando contiene '/', es una ruta absoluta o relativa
    if (ft_strchr(command, '/'))
    {
        if (access(command, X_OK) == 0)
            return (ft_strdup(command));
        return (NULL);
    }
    
    // Obtener PATH del entorno (priorizar versión simple)
    path_env = get_path_from_env_simple();
    if (!path_env)
    {
        if (env)
            path_env = get_path_from_env_list(env);
        else
            path_env = get_path_env(envp);
    }
    
    // PATH encontrado o por defecto
    
    if (!path_env)
        return (NULL);
    
    // Dividir PATH en directorios
    path_dirs = ft_split(path_env, ':');
    if (!path_dirs)
        return (NULL);
    
    // Buscar en cada directorio del PATH
    i = 0;
    while (path_dirs[i])
    {
        full_path = build_command_path(path_dirs[i], command);
        if (full_path)
        {
            if (access(full_path, X_OK) == 0)
            {
                // Liberar path_dirs
                int j = 0;
                while (path_dirs[j])
                {
                    free(path_dirs[j]);
                    j++;
                }
                free(path_dirs);
                
                return (full_path);
            }
            free(full_path);
        }
        i++;
    }
    
    // Liberar path_dirs
    i = 0;
    while (path_dirs[i])
    {
        free(path_dirs[i]);
        i++;
    }
    free(path_dirs);
    
    return (NULL);
}

/*
 * Verifica si un comando es ejecutable
 */
int is_command_executable(char *path)
{
    struct stat st;
    
    if (!path)
        return (0);
    
    // Verificar si el archivo existe
    if (stat(path, &st) != 0)
        return (0);
    
    // Verificar si es un archivo regular
    if (!S_ISREG(st.st_mode))
        return (0);
    
    // Verificar permisos de ejecución
    if (access(path, X_OK) != 0)
        return (0);
    
    return (1);
}

/*
 * Prepara el entorno para execve
 */
char **prepare_envp(char **envp, t_env *env)
{
    char **new_envp;
    t_env *current;
    int count;
    int i;
    char *temp;
    
    // Si ya tenemos envp, usarlo
    if (envp)
        return (envp);
    
    // Contar variables de entorno
    count = 0;
    current = env;
    while (current)
    {
        count++;
        current = current->next;
    }
    
    // Crear array de strings
    new_envp = (char **)ft_calloc(count + 1, sizeof(char *));
    if (!new_envp)
        return (NULL);
    
    // Llenar array
    i = 0;
    current = env;
    while (current && i < count)
    {
        if (current->content && current->var)
        {
            temp = ft_strjoin(current->var, "=");
            if (temp)
            {
                new_envp[i] = ft_strjoin(temp, current->content);
                free(temp);
                if (!new_envp[i])
                    new_envp[i] = ft_strdup(""); // Fallback
            }
            else
            {
                new_envp[i] = ft_strdup(""); // Fallback
            }
        }
        else if (current->var)
        {
            new_envp[i] = ft_strdup(current->var);
            if (!new_envp[i])
                new_envp[i] = ft_strdup(""); // Fallback
        }
        else
        {
            new_envp[i] = ft_strdup(""); // Fallback para casos extraños
        }
        
        current = current->next;
        i++;
    }
    new_envp[i] = NULL;
    
    return (new_envp);
}
