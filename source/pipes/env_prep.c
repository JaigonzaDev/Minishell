/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_prep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <cinaquiz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:37:10 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/12/03 08:38:10 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

/*
** Count environment variables
*/
static int	count_env_vars(t_env *env)
{
	int		count;
	t_env	*current;

	count = 0;
	current = env;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

/*
** Create environment entry string
*/
static char	*create_env_entry(t_env *node)
{
	char	*temp;
	char	*entry;

	if (node->content && node->var)
	{
		temp = ft_strjoin(node->var, "=");
		if (temp)
		{
			entry = ft_strjoin(temp, node->content);
			free(temp);
			if (!entry)
				return (ft_strdup(""));
			return (entry);
		}
		return (ft_strdup(""));
	}
	if (node->var)
	{
		entry = ft_strdup(node->var);
		if (!entry)
			return (ft_strdup(""));
		return (entry);
	}
	return (ft_strdup(""));
}

/*
** Prepare environment for execve
*/
char	**prepare_envp(char **envp, t_env *env)
{
	char	**new_envp;
	t_env	*current;
	int		count;
	int		i;

	if (envp)
		return (envp);
	count = count_env_vars(env);
	new_envp = (char **)ft_calloc(count + 1, sizeof(char *));
	if (!new_envp)
		return (NULL);
	i = 0;
	current = env;
	while (current && i < count)
	{
		new_envp[i] = create_env_entry(current);
		current = current->next;
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}
