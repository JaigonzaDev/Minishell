/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:58:21 by mergarci          #+#    #+#             */
/*   Updated: 2025/08/30 18:54:18 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

static void env_getInfo(t_env *var, char *str)
{
	char *equal_pos;
	int var_len;
	
	if (!var || !str)
		return;
	
	// Inicializar la estructura
	var->var = NULL;
	var->content = NULL;
	var->next = NULL;
	
	// Buscar el '='
	equal_pos = ft_strchr(str, '=');
	if (!equal_pos)
	{
		// Variable sin valor
		var->var = ft_strdup(str);
		var->content = ft_strdup("");
		return;
	}
	
	// Calcular longitud del nombre de variable
	var_len = equal_pos - str;
	
	// Asignar memoria para el nombre de variable
	var->var = malloc(var_len + 1);
	if (!var->var)
	{
		var->var = ft_strdup("");
		var->content = ft_strdup("");
		return;
	}
	
	// Copiar el nombre de variable
	ft_strlcpy(var->var, str, var_len + 1);
	
	// Copiar el contenido (después del '=')
	var->content = ft_strdup(equal_pos + 1);
	if (!var->content)
		var->content = ft_strdup("");
}

void env_save(char **envp, t_env **myEnvironment)
{
	t_env	*var;
	t_env	*last;
	int		i;

	if (!envp || !myEnvironment)
		return;
	
	*myEnvironment = NULL; // Inicializar
	last = NULL;
	i = -1;
	
	while (envp[++i] != NULL)
	{
		var = (t_env *)ft_calloc(1, sizeof(t_env));
		if (!var)
			return; // Error de memoria
		
		env_getInfo(var, envp[i]);
		
		if (*myEnvironment == NULL)
		{
			*myEnvironment = var;
			last = var;
		}
		else
		{
			if (last) // Verificación adicional de seguridad
				last->next = var;
			last = var;
		}
	}
	return;
}

t_env *env_free(t_env *env)
{
	if (!env)
		return (NULL);
	
	if (env->var)
	{
		free(env->var);
		env->var = NULL;
	}
	
	if (env->content)
	{
		free(env->content);
		env->content = NULL;
	}
	
	// No liberamos env aquí, eso lo hace el caller
	return (NULL);
}

void env_freeall(t_env **env)
{
	t_env *aux;
	t_env *deleted;
	
	if (!env || !*env)
		return;
	
	aux = *env;
	while (aux != NULL)
	{
		deleted = aux;
		aux = aux->next;
		env_free(deleted);
		free(deleted);
		deleted = NULL;
	}
	*env = NULL; // Marcar el puntero original como NULL
}