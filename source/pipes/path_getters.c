/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_getters.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <cinaquiz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:37:29 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/12/03 08:38:05 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

/*
** Get PATH variable from environment array
*/
char	*get_path_env(char **envp)
{
	int	i;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

/*
** Get PATH variable from environment list
*/
char	*get_path_from_env_list(t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (current->var && ft_strncmp(current->var, "PATH", 4) == 0)
			return (current->content);
		current = current->next;
	}
	return (NULL);
}

/*
** Get PATH variable from simple environment
*/
char	*get_path_from_env_simple(void)
{
	char	*path;

	path = env_get_simple("PATH");
	if (path)
		return (path);
	return (NULL);
}
