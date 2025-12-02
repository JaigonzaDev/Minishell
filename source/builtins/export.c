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

/*
** Print exported variables
*/
static void	print_exported_vars(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->content && tmp->content[0] != '\0')
			printf("declare -x %s=\"%s\"\n", tmp->var, tmp->content);
		else
			printf("declare -x %s\n", tmp->var);
		tmp = tmp->next;
	}
}

/*
** Validate identifier
*/
static int	is_valid_identifier(const char *str)
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
static char	*extract_var_name(const char *arg)
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
static char	*extract_var_value(const char *arg)
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
static t_env	*create_env_node(char *key, char *value)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->var = ft_strdup(key);
	new_node->content = ft_strdup(value ? value : "");
	new_node->next = NULL;
	return (new_node);
}

/*
** Update existing environment variable
*/
static int	update_existing_env(t_env *env, char *key, char *value)
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

/*
** Add or update environment variable
*/
static void	add_or_update_env(t_env **env, char *key, char *value)
{
	t_env	*new_node;
	t_env	*current;

	if (update_existing_env(*env, key, value))
		return ;
	new_node = create_env_node(key, value);
	if (!new_node)
		return ;
	if (!*env)
	{
		*env = new_node;
		return ;
	}
	current = *env;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

/*
** Process export argument
*/
static int	process_export_arg(char *arg, t_env **env)
{
	char	*var_name;
	char	*var_value;

	var_name = extract_var_name(arg);
	if (!is_valid_identifier(var_name))
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		free(var_name);
		return (1);
	}
	if (ft_strchr(arg, '='))
	{
		var_value = extract_var_value(arg);
		add_or_update_env(env, var_name, var_value);
		free(var_value);
	}
	else
		add_or_update_env(env, var_name, NULL);
	free(var_name);
	return (0);
}

/*
** Export builtin
*/
int	ft_export(char **args, t_env **env)
{
	int	i;
	int	exit_status;

	exit_status = 0;
	if (!args[1])
	{
		print_exported_vars(*env);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		if (process_export_arg(args[i], env))
			exit_status = 1;
		i++;
	}
	return (exit_status);
}
