/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:12:01 by mergarci          #+#    #+#             */
/*   Updated: 2025/11/25 17:39:57 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipes.h"

char	*read_line(int type)
{
	char	*buf;

	buf = NULL;
	(void)type;
	while (1)
	{
		buf = readline(prompt(E_PROMPT_MAIN));
		if (buf == NULL)
		{
			if (feof(stdin))
				exit(EXIT_SUCCESS);
			else if (errno == EINTR)
			{
				errno = 0;
			}
			else
				exit(EXIT_FAILURE);
		}
		break ;
	}
	if (buf[0] != '\0')
		add_history(buf);
	return (buf);
}

int	bash_execute(t_token *tokens, t_env *env)
{
	int	status;

	if (!tokens)
		return (1);
	// Ejecutar usando el sistema de pipes
	status = execute_pipeline(tokens, env);
	return (status);
}

int	main(int argc, char **argv, char **envp)
{
	char *line;
	t_token *tokens;
	t_env *env;
	int status;
	(void)argc;
	(void)argv;

	env = NULL;
	tokens = NULL;
	line = NULL;
	// Carlos: >Inicializar g_last_exit_status para $?<
	g_last_exit_status = 0;
	main_signal_config();
	// Carlos: >Mover env_save ANTES del bucle (solo esta línea cambió de posición)<
	env_save(envp, &env);
	while ((line = read_line(E_PROMPT_MAIN)))
	{
		// Carlos: >QUITAR env_save de aquí para que las variables persistan<
		// env_save(envp, &env);  ← COMENTADO/ELIMINADO

		// Si la línea empieza por '#', se ignora
		if (line[0] == '#')
		{
			free(line);
			// Carlos: >Añadir continue para evitar ejecutar código siguiente<
			continue ;
		}

		// Separar operadores pegados al texto
		char *separated_line = separate_operators(line);
		if (separated_line)
		{
			free(line);
			line = separated_line;
		}
		tokens = bash_split(&line, env);
		if ((status = parse_commands_new(&tokens)) == 0)
		{
			debug_parsing(tokens);
			status = bash_execute(tokens, env);
			// Carlos: >Actualizar exit status después de ejecutar<
			update_exit_status(status);
		}
		// Carlos: >También actualizar si hay error de parsing<
		else
		{
			update_exit_status(status);
		}
		// Carlos: >NO añadir free aquí porque bash_split/execute_pipeline ya liberan<
	}
	// Carlos: >Mover env_freeall FUERA del bucle para liberar al final del programa<
	env_freeall(&env);
	// Carlos: >Retornar el último exit status<
	return (g_last_exit_status);
}