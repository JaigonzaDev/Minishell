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
