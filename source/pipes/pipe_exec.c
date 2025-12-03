/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <cinaquiz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:37:39 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/12/03 08:38:03 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "pipes.h"

/*
** Execute pipe command logic
*/
int	execute_pipe_logic(char **args, t_env *env, int in_fd, int out_fd)
{
	if (in_fd != 0)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != 1)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
	if (ft_is_builtin(args[0]))
		exit(ft_execute_builtin(args, &env));
	else
		exec_external_child(args, env, 0, 1);
	return (0);
}

/*
** Execute pipe command
*/
int	execute_pipe_command(t_token *tokens, t_env *env, int input_fd,
		int output_fd)
{
	char	**args;
	int		status;

	if (setup_redirections(tokens, &input_fd, &output_fd))
		exit(1);
	args = tokens_to_args(tokens);
	if (!args || !args[0])
	{
		free_args(args);
		exit(0);
	}
	status = execute_pipe_logic(args, env, input_fd, output_fd);
	free_args(args);
	return (status);
}
