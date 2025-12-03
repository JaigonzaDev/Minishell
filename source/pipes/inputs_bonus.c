/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <cinaquiz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:37:18 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/12/03 08:38:08 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

/*
** Execute execve
*/
static int	execute_execve(char *path, char **args, char **envp)
{
	char	**final_envp;

	final_envp = ft_add_null(envp);
	if (!final_envp)
	{
		free(path);
		free_str_array(args);
		return (EXIT_FAILURE);
	}
	if (execve(path, args, final_envp) == -1)
	{
		perror("execve");
		free(path);
		free_str_array(args);
		free_str_array(final_envp);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/*
** Check and execute command
*/
int	check_exec(char *command, char **envp, int status)
{
	char	*command_path;
	char	**args;

	(void)status;
	if (!command)
		return (EXIT_FAILURE);
	args = ft_split_bash(command);
	if (!args || !args[0])
	{
		free_str_array(args);
		return (EXIT_FAILURE);
	}
	command_path = find_command_in_path(args[0], envp, NULL);
	if (!command_path)
		return (handle_cmd_not_found(args));
	if (!is_command_executable(command_path))
		return (handle_permission_denied(args, command_path));
	return (execute_execve(command_path, args, envp));
}
