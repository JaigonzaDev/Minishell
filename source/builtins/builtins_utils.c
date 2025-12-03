/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <cinaquiz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:34:21 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/12/03 08:34:55 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

/*
** Check if command is a builtin
*/
bool	ft_is_builtin(char *command)
{
	if (!command)
		return (false);
	return (ft_strncmp(command, "cd", 3) == 0 || ft_strncmp(command, "echo",
			5) == 0 || ft_strncmp(command, "env", 4) == 0 || ft_strncmp(command,
			"exit", 5) == 0 || ft_strncmp(command, "export", 7) == 0
		|| ft_strncmp(command, "pwd", 4) == 0 || ft_strncmp(command, "unset",
			6) == 0 || ft_strncmp(command, "true", 5) == 0
		|| ft_strncmp(command, "false", 6) == 0);
}

/*
** Execute simple builtins
*/
static int	exec_simple_builtins(char **args, t_env **environment)
{
	if (ft_strncmp(args[0], "pwd", 4) == 0)
	{
		ft_pwd();
		return (0);
	}
	else if (ft_strncmp(args[0], "unset", 6) == 0)
	{
		ft_unset(args[1], environment);
		return (0);
	}
	else if (ft_strncmp(args[0], "true", 5) == 0)
		return (ft_true());
	else if (ft_strncmp(args[0], "false", 6) == 0)
		return (ft_false());
	return (-1);
}

/*
** Execute builtin command
*/
int	ft_execute_builtin(char **args, t_env **environment)
{
	int	status;

	status = 0;
	if (ft_strncmp(args[0], "cd", 3) == 0)
		status = ft_cd(args[1], environment);
	else if (ft_strncmp(args[0], "echo", 5) == 0)
	{
		ft_echo(args);
		status = 0;
	}
	else if (ft_strncmp(args[0], "env", 4) == 0)
	{
		ft_env(*environment);
		status = 0;
	}
	else if (ft_strncmp(args[0], "exit", 5) == 0)
	{
		ft_exit(args, environment);
		status = 0;
	}
	else if (ft_strncmp(args[0], "export", 7) == 0)
		status = ft_export(args, environment);
	else
		status = exec_simple_builtins(args, environment);
	return (status);
}
