/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 12:43:20 by mergarci          #+#    #+#             */
/*   Updated: 2025/09/13 12:43:21 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void update_pwd_env(t_env **environment)
{
	t_env *current;
	char *cwd;
	
	if (environment == NULL || *environment == NULL)
		return;
		
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return;
	
	// Buscar y actualizar PWD
	current = *environment;
	while (current)
	{
		if (ft_strncmp(current->var, "PWD", 4) == 0)
		{
			free(current->content);
			current->content = ft_strdup(cwd);
			break;
		}
		current = current->next;
	}
	
	free(cwd);
}

int ft_cd(char *path, t_env **environment)
{
	if (path == NULL || environment == NULL || *environment == NULL)
	{
		ft_printf("cd: missing argument\n");
		return (1);
	}
	
	if (chdir(path) == -1)
	{
		ft_printf("cd: %s: No such file or directory\n", path);
		return (1);
	}
	
	// Actualizar la variable PWD en el environment
	update_pwd_env(environment);
	return (0);
}