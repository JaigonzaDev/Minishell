/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_substitution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 19:00:00 by mergarci          #+#    #+#             */
/*   Updated: 2025/10/30 10:40:22 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipes.h"
#include <sys/wait.h>
#include <unistd.h>

// Variable global para el estado de salida del último comando
int g_last_exit_status = 0;

/*
 * Ejecuta un comando y captura su salida
 */
char *execute_command_capture_output(char *command, t_env *env)
{
    int pipefd[2];
    pid_t pid;
    char *output;
    char buffer[4096];
    ssize_t bytes_read;
    // size_t total_size;
    char *temp;
    int status;
    
    
    if (!command || ft_strlen(command) == 0)
        return (ft_strdup(""));
    
    // Crear pipe para capturar salida
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return (ft_strdup(""));
    }
    
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        close(pipefd[0]);
        close(pipefd[1]);
        return (ft_strdup(""));
    }
    
    if (pid == 0)
    {
        // Proceso hijo: ejecutar comando
        close(pipefd[0]); // Cerrar lectura
        dup2(pipefd[1], STDOUT_FILENO); // Redirigir stdout al pipe
        close(pipefd[1]);
        
        // Tokenizar y ejecutar el comando
        t_token *tokens = bash_split(&command, env);
        if (tokens)
        {
            if ((status = parse_commands_new(&tokens)) == 0)
                status = bash_execute(tokens, env);
            update_exit_status(status);
            free_token_list(tokens);
        }
        exit(0);
    }
    else
    {
        // Proceso padre: leer salida
        close(pipefd[1]); // Cerrar escritura
        
        output = ft_strdup("");
        // total_size = 0;
        
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0)
        {
            buffer[bytes_read] = '\0';
            
            // Expandir output
            temp = ft_strjoin(output, buffer);
            free(output);
            output = temp;
            // total_size += bytes_read;
            
            if (!output)
            {
                close(pipefd[0]);
                waitpid(pid, NULL, 0);
                return (ft_strdup(""));
            }
        }
        
        close(pipefd[0]);
        
        // Esperar al proceso hijo y capturar estado de salida
        int status;
        waitpid(pid, &status, 0);
        // NO actualizar g_last_exit_status aquí - la sustitución de comandos
        // no debe afectar el estado de salida del shell principal
        
        // Eliminar newline final si existe
        if (output && ft_strlen(output) > 0 && output[ft_strlen(output) - 1] == '\n')
            output[ft_strlen(output) - 1] = '\0';
        
        return (output ? output : ft_strdup(""));
    }
}

/*
 * Obtiene el valor de $?
 */
char *get_exit_status_string(void)
{
    return (ft_itoa(g_last_exit_status));
}

/*
 * Actualiza el estado de salida
 */
void update_exit_status(int status)
{
    g_last_exit_status = status;
}

/*
 * Procesa sustitución de comandos $()
 */
char *process_command_substitution(char *command, t_env *env)
{
    char *result;
    char *trimmed_command;
    
    if (!command)
        return (ft_strdup(""));
    
    // Eliminar espacios al inicio y final
    trimmed_command = ft_strtrim(command, " \t\n");
    if (!trimmed_command)
        return (ft_strdup(""));
    
    // Ejecutar comando y capturar salida
    result = execute_command_capture_output(trimmed_command, env);
    
    free(trimmed_command);
    return (result);
}

/*
 * Procesa backticks `command`
 */
char *process_backtick_substitution(char *command, t_env *env)
{
    // Los backticks funcionan igual que $()
    return (process_command_substitution(command, env));
}
