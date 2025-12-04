/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <cinaquiz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:37:44 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/12/04 14:54:21 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

/*
** Create pipe and fork
*/
static pid_t	ft_createfd_fork(int *fd)
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		clean_exit(errno);
	}
	return (fork());
}

/*
** Redirect file descriptors
*/
static int	ft_redirect_fd(int *prev_pipe, char **commands, int *fd, int i)
{
	int	num_commands;

	num_commands = ft_count_string(commands);
	if (prev_pipe[READ] != -1)
		ft_dup_close(prev_pipe[READ], STDIN_FILENO, fd[READ]);
	else
	{
		ft_closefd(fd[READ]);
		ft_closefd(fd[WRITE]);
		return (EXIT_FAILURE);
	}
	if ((i < num_commands - 2) && (prev_pipe[READ] != -1))
		ft_dup_close(fd[WRITE], STDOUT_FILENO, prev_pipe[WRITE]);
	else if ((i == num_commands - 2) && (prev_pipe[WRITE] != -1))
		ft_dup_close(prev_pipe[WRITE], STDOUT_FILENO, fd[WRITE]);
	else if (prev_pipe[WRITE] == -1)
	{
		ft_closefd(fd[READ]);
		ft_closefd(fd[WRITE]);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/*
** Wait for children and close fds
*/
static int	ft_wait_closefd(pid_t *pid, int num_com, int *fd, int *prev_pipe)
{
	int	i;
	int	status;

	status = 0;
	i = -1;
	while (++i < num_com)
		waitpid(pid[i], &status, 0);
	ft_close_fds(fd, prev_pipe);
	return (WEXITSTATUS(status));
}

/*
** Handle child process
*/
static int	handle_child(int *files, char **commands, char **envp, int i)
{
	int	status;
	int	fd[2];
	int	prev_pipe[2];

	prev_pipe[READ] = files[I];
	prev_pipe[WRITE] = files[O];
	status = ft_redirect_fd(prev_pipe, commands, fd, i + 2);
	if (status != 0 || check_exec(commands[i + 2], envp, status) != 0)
		return (EXIT_FAILURE);
	ft_closefd(files[O]);
	ft_closefd(files[I]);
	return (EXIT_SUCCESS);
}

/*
** Pipeline execution
*/
int	ft_pipeline(int *files, char **commands, char **envp)
{
	int	i;
	int	fd[2];
	int	pid[MAX_PIPES];
	int	prev_pipe[2];

	prev_pipe[READ] = files[I];
	prev_pipe[WRITE] = files[O];
	i = -1;
	while (++i < ft_count_string(commands) - 3)
	{
		pid[i] = ft_createfd_fork(fd);
		if (pid[i] == 0)
		{
			if (handle_child(files, commands, envp, i))
				clean_exit(EXIT_FAILURE);
		}
		else
			ft_parent_fd(fd, prev_pipe);
	}
	return (ft_wait_closefd(pid, ft_count_string(commands) - 3, fd, prev_pipe));
}
