/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_substitution_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 20:15:00 by mergarci          #+#    #+#             */
/*   Updated: 2025/10/14 20:15:00 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipes.h"
#include <sys/wait.h>
#include <unistd.h>

/*
** Setup fork and pipes
*/
pid_t	setup_command_fork(char *command, t_env *env, int pipefd[2])
{
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (-1);
	}
	if (pid == 0)
		exec_child_process(command, env, pipefd);
	return (pid);
}

/*
** Trim trailing newline from output
*/
void	trim_trailing_newline(char *output)
{
	size_t	len;

	if (!output)
		return ;
	len = ft_strlen(output);
	if (len > 0 && output[len - 1] == '\n')
		output[len - 1] = '\0';
}

/*
** Execute command in child process
*/
void	exec_child_process(char *command, t_env *env, int pipefd[2])
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
char	*read_pipe_output(int fd, pid_t pid)
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
