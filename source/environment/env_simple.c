/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_simple.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <cinaquiz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:36:44 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/12/03 09:34:42 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environment.h"

/*
** Free environment copy on error
*/
static void	free_env_on_error(int count)
{
	int	i;

	i = count;
	while (--i >= 0)
		free(g_status.g_env_copy[i]);
	free(g_status.g_env_copy);
	g_status.g_env_copy = NULL;
	g_status.env_count = 0;
}

/*
** Save environment copy
*/
void	env_save_simple(char **envp)
{
	int	i;

	if (!envp)
		return ;
	g_status.env_count = 0;
	while (envp[g_status.env_count])
		g_status.env_count++;
	g_status.g_env_copy = malloc((g_status.env_count + 1) * sizeof(char *));
	if (!g_status.g_env_copy)
		return ;
	i = 0;
	while (i < g_status.env_count)
	{
		g_status.g_env_copy[i] = ft_strdup(envp[i]);
		if (!g_status.g_env_copy[i])
		{
			free_env_on_error(i);
			return ;
		}
		i++;
	}
	g_status.g_env_copy[g_status.env_count] = NULL;
}

/*
** Print environment copy
*/
void	env_print_simple(void)
{
	int	i;

	if (!g_status.g_env_copy)
	{
		ft_printf("Environment not initialized\n");
		return ;
	}
	i = 0;
	while (i < g_status.env_count && i < 10)
	{
		if (g_status.g_env_copy[i])
			ft_printf("%s\n", g_status.g_env_copy[i]);
		i++;
	}
}

/*
** Free environment copy
*/
void	env_free_simple(void)
{
	int	i;

	if (!g_status.g_env_copy)
		return ;
	i = 0;
	while (i < g_status.env_count)
	{
		if (g_status.g_env_copy[i])
			free(g_status.g_env_copy[i]);
		i++;
	}
	free(g_status.g_env_copy);
	g_status.g_env_copy = NULL;
	g_status.env_count = 0;
}

/*
** Get environment variable
*/
char	*env_get_simple(const char *name)
{
	int	i;
	int	name_len;

	if (!g_status.g_env_copy || !name)
		return (NULL);
	name_len = ft_strlen(name);
	i = 0;
	while (i < g_status.env_count)
	{
		if (g_status.g_env_copy[i]
			&& ft_strncmp(g_status.g_env_copy[i], name, name_len) == 0
			&& g_status.g_env_copy[i][name_len] == '=')
		{
			return (g_status.g_env_copy[i] + name_len + 1);
		}
		i++;
	}
	return (NULL);
}
