/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <cinaquiz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:34:36 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/12/03 08:34:51 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*
** Validate identifier
*/
int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/*
** Extract variable name
*/
char	*extract_var_name(const char *arg)
{
	char	*equal_sign;
	int		len;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
		len = equal_sign - arg;
	else
		len = ft_strlen(arg);
	return (ft_substr(arg, 0, len));
}

/*
** Extract variable value
*/
char	*extract_var_value(const char *arg)
{
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
		return (ft_strdup(equal_sign + 1));
	return (NULL);
}

/*
** Create environment node
*/
t_env	*create_env_node(char *key, char *value)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->var = ft_strdup(key);
	if (value)
		new_node->content = ft_strdup(value);
	else
		new_node->content = ft_strdup("");
	new_node->next = NULL;
	return (new_node);
}

/*
** Update existing environment variable
*/
int	update_existing_env(t_env *env, char *key, char *value)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strncmp(current->var, key, ft_strlen(key) + 1) == 0)
		{
			if (value)
			{
				free(current->content);
				current->content = ft_strdup(value);
			}
			return (1);
		}
		current = current->next;
	}
	return (0);
}
