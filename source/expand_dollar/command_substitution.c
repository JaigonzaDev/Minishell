/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_substitution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:27:39 by jaigonza          #+#    #+#             */
/*   Updated: 2025/12/03 08:30:03 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipes.h"
#include <sys/wait.h>
#include <unistd.h>

int		g_last_exit_status = 0;

/*
** Execute command and capture output
*/
char	*execute_command_capture_output(char *command, t_env *env)
{
	int		pipefd[2];
	pid_t	pid;
	char	*output;
	int		status;

	if (!command || ft_strlen(command) == 0)
		return (ft_strdup(""));
	pid = setup_command_fork(command, env, pipefd);
	if (pid == -1)
		return (ft_strdup(""));
	close(pipefd[1]);
	output = read_pipe_output(pipefd[0], pid);
	close(pipefd[0]);
	waitpid(pid, &status, 0);
	trim_trailing_newline(output);
	if (!output)
		return (ft_strdup(""));
	return (output);
}

/*
** Get exit status string
*/
char	*get_exit_status_string(void)
{
	return (ft_itoa(g_last_exit_status));
}

/*
** Update exit status
*/
void	update_exit_status(int status)
{
	g_last_exit_status = status;
}

/*
** Process command substitution
*/
char	*process_command_substitution(char *command, t_env *env)
{
	char	*result;
	char	*trimmed_command;

	if (!command)
		return (ft_strdup(""));
	trimmed_command = ft_strtrim(command, " \t\n");
	if (!trimmed_command)
		return (ft_strdup(""));
	result = execute_command_capture_output(trimmed_command, env);
	free(trimmed_command);
	return (result);
}

/*
** Process backtick substitution
*/
char	*process_backtick_substitution(char *command, t_env *env)
{
	return (process_command_substitution(command, env));
}
