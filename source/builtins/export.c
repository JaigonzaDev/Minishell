/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 12:44:24 by mergarci          #+#    #+#             */
/*   Updated: 2025/09/13 12:44:25 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static t_env *create_env_node(char *var, char *content)
{
	t_env *new_node;
	
	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	
	new_node->var = ft_strdup(var);
	new_node->content = ft_strdup(content);
	new_node->next = NULL;
	
	return (new_node);
}

static void add_to_environment(t_env **environment, char *var, char *content)
{
	t_env *new_node;
	t_env *current;
	
	new_node = create_env_node(var, content);
	if (!new_node)
		return;
	
	if (!*environment)
	{
		*environment = new_node;
		return;
	}
	
	current = *environment;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

void ft_export(char *str, t_env **environment)
{
	char *equal_pos;
	char *var_name;
	char *var_content;
	
	if (str == NULL || environment == NULL)
		return;
	
	equal_pos = ft_strchr(str, '=');
	if (equal_pos == NULL)
	{
		ft_printf("export: %s: not a valid identifier\n", str);
		return;
	}
	
	var_name = ft_substr(str, 0, equal_pos - str);
	var_content = ft_strdup(equal_pos + 1);
	
	if (var_name == NULL || var_content == NULL)
	{
		free(var_name);
		free(var_content);
		return;
	}
	
	t_env *current = *environment;
	while (current)
	{
		if (ft_strncmp(current->var, var_name, ft_strlen(var_name) + 1) == 0)
		{
			free(current->content);
			current->content = var_content;
			free(var_name);
			return;
		}
		current = current->next;
	}
	
	add_to_environment(environment, var_name, var_content);
	free(var_name);
	free(var_content);
}