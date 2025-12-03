/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integration.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <cinaquiz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:37:22 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/12/03 08:38:07 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

/*
** Execute pipeline
*/
int	execute_pipeline(t_token *tokens, t_env *env)
{
	int	pipe_count;

	if (!tokens)
		return (0);
	pipe_count = count_pipes(tokens);
	if (pipe_count == 0)
		return (execute_simple_command(tokens, env));
	else
		return (execute_multiple_pipes(tokens, env, pipe_count));
}
