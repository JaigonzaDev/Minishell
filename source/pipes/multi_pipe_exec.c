/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <cinaquiz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:37:24 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/12/05 06:32:29 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

/*
** Execute child in multiple pipes
*/
void	exec_child_multi(t_pipe_context *ctx, t_token *tokens, t_env *env)
{
	int		fds[2];
	t_token	group_tokens;
	int		j;

	fds[0] = 0;
	fds[1] = 1;
	config_child_pipes(ctx->i, ctx->pipe_count, ctx->pipes, fds);
	j = 0;
	while (j < ctx->pipe_count)
	{
		if (j != ctx->i - 1)
			close(ctx->pipes[j][0]);
		if (j != ctx->i)
			close(ctx->pipes[j][1]);
		j++;
	}
	group_tokens = get_group_tokens(tokens, ctx->i);
	execute_pipe_command(&group_tokens, env, fds[0], fds[1]);
}

/*
** Wait for children
*/
int	wait_children(pid_t *pids, int pipe_count)
{
	int	i;
	int	status;

	i = 0;
	while (i <= pipe_count)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

/*
** Execute multiple pipes
*/
int	execute_multiple_pipes(t_token *tokens, t_env *env, int pipe_count)
{
	t_pipe_context	ctx;
	pid_t			*pids;
	int				status;

	ctx.pipe_count = pipe_count;
	ctx.pipes = create_pipes(pipe_count);
	if (!ctx.pipes)
		return (1);
	pids = (pid_t *)malloc(sizeof(pid_t) * (pipe_count + 1));
	ctx.i = 0;
	while (ctx.i <= pipe_count)
	{
		pids[ctx.i] = fork();
		if (pids[ctx.i] == 0)
			exec_child_multi(&ctx, tokens, env);
		ctx.i++;
	}
	close_pipes(ctx.pipes, pipe_count);
	ignore_exec_signals();
	status = wait_children(pids, pipe_count);
	main_signal_config();
	free(pids);
	return (status);
}
