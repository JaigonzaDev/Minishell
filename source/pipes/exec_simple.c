/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <cinaquiz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 18:55:00 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/12/05 06:30:29 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "pipes.h"

/*
** Execute command logic
*/
static int	execute_command_logic(char **args, t_env *env, int input_fd,
		int output_fd)
{
	int		status;
	pid_t	pid;

	status = 0;
	if (ft_is_builtin(args[0]))
		status = exec_builtin_with_redir(args, env, input_fd, output_fd);
	else
	{
		ignore_exec_signals();
		pid = fork();
		if (pid == 0)
		{
			child_signal_config();
			exec_external_child(args, env, input_fd, output_fd);
		}
		else
		{
			status = wait_external_command(pid);
			main_signal_config();
		}
	}
	return (status);
}

/*
** Handle simple redirection
*/
static void	handle_simple_redirection(int input_fd, int output_fd)
{
	char	buffer[1024];
	int		bytes_read;

	if (input_fd == 0)
		return ;
	while (1)
	{
		bytes_read = read(input_fd, buffer, sizeof(buffer));
		if (bytes_read <= 0)
			break ;
		write(output_fd, buffer, bytes_read);
	}
	close(input_fd);
	if (output_fd != 1)
		close(output_fd);
}

/*
** Execute simple command
*/
int	execute_simple_command(t_token *tokens, t_env *env)
{
	char	**args;
	int		input_fd;
	int		output_fd;
	int		status;

	input_fd = 0;
	output_fd = 1;
	if (setup_redirections(tokens, &input_fd, &output_fd))
		return (1);
	args = tokens_to_args(tokens);
	if (!args || !args[0])
	{
		handle_simple_redirection(input_fd, output_fd);
		free_args(args);
		return (0);
	}
	status = execute_command_logic(args, env, input_fd, output_fd);
	free_args(args);
	return (status);
}
