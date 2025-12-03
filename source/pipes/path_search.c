/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <cinaquiz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:37:32 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/12/03 08:38:05 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

/*
** Build full command path
*/
static char	*build_command_path(char *dir, char *command)
{
	char	*temp;
	char	*full_path;

	if (!dir || !command)
		return (NULL);
	if (dir[ft_strlen(dir) - 1] != '/')
	{
		temp = ft_strjoin(dir, "/");
		if (!temp)
			return (NULL);
		full_path = ft_strjoin(temp, command);
		free(temp);
	}
	else
	{
		full_path = ft_strjoin(dir, command);
	}
	return (full_path);
}

/*
** Check if command is an absolute or relative path
*/
static char	*check_absolute_path(char *command)
{
	if (ft_strchr(command, '/'))
	{
		if (access(command, X_OK) == 0)
			return (ft_strdup(command));
		return (NULL);
	}
	return (NULL);
}

/*
** Search for command in path directories
*/
static char	*search_in_paths(char **path_dirs, char *command)
{
	int		i;
	char	*full_path;

	i = 0;
	while (path_dirs[i])
	{
		full_path = build_command_path(path_dirs[i], command);
		if (full_path)
		{
			if (access(full_path, X_OK) == 0)
				return (full_path);
			free(full_path);
		}
		i++;
	}
	return (NULL);
}

/*
** Get PATH variable
*/
static char	*get_path_var(char **envp, t_env *env)
{
	char	*path_env;

	path_env = get_path_from_env_simple();
	if (!path_env)
	{
		if (env)
			path_env = get_path_from_env_list(env);
		else
			path_env = get_path_env(envp);
	}
	return (path_env);
}

/*
** Find command in PATH
*/
char	*find_command_in_path(char *command, char **envp, t_env *env)
{
	char	*path_env;
	char	**path_dirs;
	char	*full_path;

	if (!command)
		return (NULL);
	full_path = check_absolute_path(command);
	if (full_path)
		return (full_path);
	if (ft_strchr(command, '/'))
		return (ft_strdup(command));
	path_env = get_path_var(envp, env);
	if (!path_env)
		return (NULL);
	path_dirs = ft_split(path_env, ':');
	if (!path_dirs)
		return (NULL);
	full_path = search_in_paths(path_dirs, command);
	free_str_array(path_dirs);
	return (full_path);
}
