/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <cinaquiz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:34:25 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/12/03 08:34:53 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*
** Update PWD environment variable
*/
static void	update_pwd_env(t_env **environment)
{
	t_env	*current;
	char	*cwd;

	if (environment == NULL || *environment == NULL)
		return ;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return ;
	current = *environment;
	while (current)
	{
		if (ft_strncmp(current->var, "PWD", 4) == 0)
		{
			free(current->content);
			current->content = ft_strdup(cwd);
			break ;
		}
		current = current->next;
	}
	free(cwd);
}

/*
** Get HOME directory from environment
*/
static char	*get_home_dir(t_env *environment)
{
	t_env	*current;

	current = environment;
	while (current)
	{
		if (ft_strncmp(current->var, "HOME", 5) == 0)
			return (current->content);
		current = current->next;
	}
	return (NULL);
}

/*
** Change directory builtin
*/
int	ft_cd(char *path, t_env **environment)
{
	char	*target_path;

	if (environment == NULL || *environment == NULL)
		return (1);
	if (path == NULL)
	{
		target_path = get_home_dir(*environment);
		if (target_path == NULL)
		{
			ft_printf("cd: HOME not set\n");
			return (1);
		}
		path = target_path;
	}
	if (chdir(path) == -1)
	{
		ft_printf("cd: %s: No such file or directory\n", path);
		return (1);
	}
	update_pwd_env(environment);
	return (0);
}
