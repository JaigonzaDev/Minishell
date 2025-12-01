/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_substitution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 19:00:00 by mergarci          #+#    #+#             */
/*   Updated: 2025/10/30 10:40:22 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipes.h"
#include <sys/wait.h>
#include <unistd.h>

int			g_last_exit_status = 0;

/*
** Execute command in child process
*/
static void	exec_child_process(char *command, t_env *env, int pipefd[2])
{
	t_token	*tokens;
	int		status;

	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	tokens = bash_split(&command, env);
	if (tokens)
	{
		status = parse_commands_new(&tokens);
		if (status == 0)
			status = bash_execute(tokens, env);
		update_exit_status(status);
		free_token_list(tokens);
	}
	exit(0);
}

/*
** Read output from pipe
*/
static char	*read_pipe_output(int fd, pid_t pid)
{
	char	*output;
	char	buffer[4096];
	ssize_t	bytes_read;
	char	*temp;

	output = ft_strdup("");
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(output, buffer);
		free(output);
		output = temp;
		if (!output)
		{
			close(fd);
			waitpid(pid, NULL, 0);
			return (ft_strdup(""));
		}
		bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	}
	return (output);
}

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
	if (pipe(pipefd) == -1)
		return (ft_strdup(""));
	pid = fork();
	if (pid == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (ft_strdup(""));
	}
	if (pid == 0)
		exec_child_process(command, env, pipefd);
	close(pipefd[1]);
	output = read_pipe_output(pipefd[0], pid);
	close(pipefd[0]);
	waitpid(pid, &status, 0);
	if (output && ft_strlen(output) > 0 && output[ft_strlen(output)
		- 1] == '\n')
		output[ft_strlen(output) - 1] = '\0';
	return (output ? output : ft_strdup(""));
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
