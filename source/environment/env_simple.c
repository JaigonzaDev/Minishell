/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_simple.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <cinaquiz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:36:44 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/12/03 08:36:57 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

/*
** Simple environment storage using string array
*/

static char	**g_env_copy = NULL;
static int	g_env_count = 0;

/*
** Free environment copy on error
*/
static void	free_env_on_error(int count)
{
	int	i;

	i = count;
	while (--i >= 0)
		free(g_env_copy[i]);
	free(g_env_copy);
	g_env_copy = NULL;
	g_env_count = 0;
}

/*
** Save environment copy
*/
void	env_save_simple(char **envp)
{
	int	i;

	if (!envp)
		return ;
	g_env_count = 0;
	while (envp[g_env_count])
		g_env_count++;
	g_env_copy = malloc((g_env_count + 1) * sizeof(char *));
	if (!g_env_copy)
		return ;
	i = 0;
	while (i < g_env_count)
	{
		g_env_copy[i] = ft_strdup(envp[i]);
		if (!g_env_copy[i])
		{
			free_env_on_error(i);
			return ;
		}
		i++;
	}
	g_env_copy[g_env_count] = NULL;
}

/*
** Print environment copy
*/
void	env_print_simple(void)
{
	int	i;

	if (!g_env_copy)
	{
		ft_printf("Environment not initialized\n");
		return ;
	}
	i = 0;
	while (i < g_env_count && i < 10)
	{
		if (g_env_copy[i])
			ft_printf("%s\n", g_env_copy[i]);
		i++;
	}
}

/*
** Free environment copy
*/
void	env_free_simple(void)
{
	int	i;

	if (!g_env_copy)
		return ;
	i = 0;
	while (i < g_env_count)
	{
		if (g_env_copy[i])
			free(g_env_copy[i]);
		i++;
	}
	free(g_env_copy);
	g_env_copy = NULL;
	g_env_count = 0;
}

/*
** Get environment variable
*/
char	*env_get_simple(const char *name)
{
	int	i;
	int	name_len;

	if (!g_env_copy || !name)
		return (NULL);
	name_len = ft_strlen(name);
	i = 0;
	while (i < g_env_count)
	{
		if (g_env_copy[i] && ft_strncmp(g_env_copy[i], name, name_len) == 0
			&& g_env_copy[i][name_len] == '=')
		{
			return (g_env_copy[i] + name_len + 1);
		}
		i++;
	}
	return (NULL);
}
