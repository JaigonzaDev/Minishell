/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:12:01 by mergarci          #+#    #+#             */
/*   Updated: 2025/11/19 17:35:27 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipes.h"


char *read_line(int type)
{
    char *buf = NULL;

    while (1)
    {
        printf("llega\n");
        buf = readline(prompt(type));
        if (buf == NULL)
        {
            if (feof(stdin))
                exit(EXIT_SUCCESS);
            else if (errno == EINTR)
            {
                clearerr(stdin);
                continue;
            }
            else
            {
                perror("readline");
                exit(EXIT_FAILURE);
            }
        }
        break;
    }
    if (buf[0] != '\0')
        add_history(buf);
    return (buf);
}

int bash_execute(t_token *tokens, t_env *env)
{
	int status;
	
	if (!tokens)
		return (1);
	
	// Ejecutar usando el sistema de pipes
	status = execute_pipeline(tokens, env);
	
    return (status);
	// // Actualizar status en variable global para $?
	// update_exit_status(status);
}

int main()
{
    char *line;
    t_token *tokens;
    t_env *env;
    int status;
    pid_t pid;


    env = NULL;
    tokens = NULL;
    line = NULL;
	main_signal_config();

    while ((line = read_line(E_PROMPT_MAIN)))
    {
        // Si la línea empieza por '#', se ignora
        if (line[0] == '#')
        {
            free(line);
            continue;
        }
        prompt(E_PROMPT_MAIN);
        // Crear un nuevo proceso para manejar la línea
        pid = fork();
        if (pid < 0)
        {
            perror("fork");
            continue;
        }
        else if (pid == 0)
        {
    		child_signal_config();
            // Separar operadores pegados al texto
            char *separated_line = separate_operators(line);
            if (separated_line)
            {
                free(line);
                line = separated_line;
            }
            tokens = bash_split(&line, env);
            debug_parsing(tokens);
            if ((status = parse_commands_new(&tokens)) == 0)
                status = bash_execute(tokens, env);
            update_exit_status(status);
        }
        else
            waitpid(pid, NULL, 0);
    }
    return (EXIT_SUCCESS);
}