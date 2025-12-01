/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42madrid.com> +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 18:00:00 by antigravity       #+#    #+#             */
/*   Updated: 2025/12/01 18:00:00 by antigravity      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

/*
** Create pipes array
*/
int	**create_pipes(int pipe_count)
{
	int	**pipes;
	int	i;

	pipes = (int **)ft_calloc(pipe_count, sizeof(int *));
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < pipe_count)
	{
		pipes[i] = (int *)ft_calloc(2, sizeof(int));
		if (!pipes[i] || pipe(pipes[i]) == -1)
			return (NULL);
		i++;
	}
	return (pipes);
}

/*
** Close pipes
*/
void	close_pipes(int **pipes, int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

/*
** Configure child pipes
*/
void	config_child_pipes(int i, int pipe_count, int **pipes, int *fds)
{
	if (i == 0)
	{
		fds[1] = pipes[i][1];
	}
	else if (i == pipe_count)
	{
		fds[0] = pipes[i - 1][0];
	}
	else
	{
		fds[0] = pipes[i - 1][0];
		fds[1] = pipes[i][1];
	}
}
