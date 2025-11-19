/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:42:59 by mergarci          #+#    #+#             */
/*   Updated: 2025/10/14 20:07:05 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

// ft_free_str eliminada - no se usa en la nueva implementación

// ft_free_strings eliminada - no se usa en la nueva implementación

/*Function adds NULL to the end of the args pointer*/
static char	**ft_add_null(char **args)
{
	char	**aux;
	int		num;
	int		i;

	num = ft_count_string(args);
	i = 0;
	aux = (char **)ft_calloc(num + 1, sizeof(char *));
	while (i < num)
	{
		aux[i] = (char *)ft_calloc(ft_strlen(args[i]) + 1, sizeof(char *));
		ft_memcpy(aux[i], args[i], ft_strlen(args[i]));
		i++;
	}
	aux[num] = NULL;
	if (num == 1)
	{
		args[0] = ft_memfree(args[0]);
		args = NULL;
	}
	return (aux);
}

/*
 * Función optimizada que busca y ejecuta comandos usando PATH
 * Soporta rutas absolutas, relativas y búsqueda en PATH
 */
int	check_exec(char *command, char **envp, int status)
{
	char	*command_path;
	char	**args;
	char	**final_envp;

	(void)status; // Parámetro no usado en la nueva implementación
	
	if (!command)
		return (EXIT_FAILURE);

	// Dividir comando en argumentos
	args = ft_split_bash(command);
	if (!args || !args[0])
	{
		if (args)
		{
			int i = 0;
			while (args[i])
			{
				free(args[i]);
				i++;
			}
			free(args);
		}
		return (EXIT_FAILURE);
	}

	// Buscar el comando en PATH (envp puede ser NULL, se usará env por defecto)
	command_path = find_command_in_path(args[0], envp, NULL);
	if (!command_path)
	{
		ft_printf("minishell: %s: command not found\n", args[0]);
		
		// Liberar args
		int i = 0;
		while (args[i])
		{
			free(args[i]);
			i++;
		}
		free(args);
		
		return (127); // Código de error estándar para "command not found"
	}

	// Verificar que el comando sea ejecutable
	if (!is_command_executable(command_path))
	{
		ft_printf("minishell: %s: Permission denied\n", args[0]);
		
		free(command_path);
		int i = 0;
		while (args[i])
		{
			free(args[i]);
			i++;
		}
		free(args);
		
		return (126); // Código de error estándar para "permission denied"
	}

	// Preparar entorno
	final_envp = ft_add_null(envp);
	if (!final_envp)
	{
		free(command_path);
		int i = 0;
		while (args[i])
		{
			free(args[i]);
			i++;
		}
		free(args);
		return (EXIT_FAILURE);
	}

	// Ejecutar comando
	if (execve(command_path, args, final_envp) == -1)
	{
		perror("execve");
		
		// Limpiar memoria (aunque execve no debería fallar si llegamos aquí)
		free(command_path);
		int i = 0;
		while (args[i])
		{
			free(args[i]);
			i++;
		}
		free(args);
		
		i = 0;
		while (final_envp[i])
		{
			free(final_envp[i]);
			i++;
		}
		free(final_envp);
		
		return (EXIT_FAILURE);
	}

	// Este punto nunca debería alcanzarse si execve tiene éxito
	return (EXIT_SUCCESS);
}
