/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <cinaquiz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:36:50 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/12/03 08:36:56 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

/*
** Get environment info from string
*/
static void	env_get_info(t_env *var, char *str)
{
	char	*equal_pos;

	if (!var || !str)
		return ;
	var->var = NULL;
	var->content = NULL;
	var->next = NULL;
	equal_pos = ft_strchr(str, '=');
	if (!equal_pos)
	{
		var->var = ft_strdup(str);
		var->content = ft_strdup("");
		return ;
	}
	allocate_var_content(var, str, equal_pos);
}

/*
** Create new environment node
*/
static t_env	*create_new_node(char *str)
{
	t_env	*var;

	var = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!var)
		return (NULL);
	env_get_info(var, str);
	return (var);
}

/*
** Save environment to list
*/
void	env_save(char **envp, t_env **my_environment)
{
	t_env	*var;
	t_env	*last;
	int		i;

	if (!envp || !my_environment)
		return ;
	*my_environment = NULL;
	last = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		var = create_new_node(envp[i]);
		if (!var)
			return ;
		if (*my_environment == NULL)
			*my_environment = var;
		else
		{
			if (last)
				last->next = var;
		}
		last = var;
		i++;
	}
}

/*
** Free environment node content
*/
t_env	*env_free(t_env *env)
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
	return (NULL);
}

/*
** Free all environment nodes
*/
void	env_freeall(t_env **env)
{
	t_env	*aux;
	t_env	*deleted;

	if (!env || !*env)
		return ;
	aux = *env;
	while (aux != NULL)
	{
		deleted = aux;
		aux = aux->next;
		env_free(deleted);
		free(deleted);
		deleted = NULL;
	}
	*env = NULL;
}
