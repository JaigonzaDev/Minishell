/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42madrid.com> +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 18:00:00 by antigravity       #+#    #+#             */
/*   Updated: 2025/12/01 18:00:00 by antigravity      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "pipes.h"

/*
** Execute builtin with redirections
*/
int	exec_builtin_with_redir(char **args, t_env *env, int input_fd,
		int output_fd)
{
	int	saved_stdin;
	int	saved_stdout;
	int	status;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (input_fd != 0)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	if (output_fd != 1)
	{
		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);
	}
	status = ft_execute_builtin(args, &env);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	return (status);
}

/*
** Execute external command child process
*/
void	exec_external_child(char **args, t_env *env, int input_fd,
		int output_fd)
{
	char	*path;
	char	**envp;

	if (input_fd != 0)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	if (output_fd != 1)
	{
		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);
	}
	path = find_command_in_path(args[0], NULL, env);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	envp = prepare_envp(NULL, env);
	execve(path, args, envp);
	perror("minishell");
	exit(1);
}

/*
** Wait for external command
*/
int	wait_external_command(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

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
		pid = fork();
		if (pid == 0)
			exec_external_child(args, env, input_fd, output_fd);
		else
			status = wait_external_command(pid);
	}
	return (status);
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
		free_args(args);
		return (0);
	}
	status = execute_command_logic(args, env, input_fd, output_fd);
	free_args(args);
	return (status);
}
