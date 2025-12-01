/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_setup.c                                :+:      :+:    :+:   */
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
** Process single redirection
*/
int	process_single_redirection(t_token *prev, t_token *current, int *input_fd,
		int *output_fd)
{
	if (prev->type == E_REDIRECT_IN)
		return (handle_redirect_in(current, input_fd));
	else if (prev->type == E_REDIRECT_OUT)
		return (handle_redirect_out(current, output_fd));
	else if (prev->type == E_REDIRECT_APPEND)
		return (handle_redirect_append(current, output_fd));
	else if (prev->type == E_REDIRECT_HEREDOC)
		return (handle_redirect_heredoc(current, input_fd));
	return (0);
}

/*
** Setup redirections
*/
int	setup_redirections(t_token *tokens, int *input_fd, int *output_fd)
{
	t_token	*current;
	t_token	*prev;

	current = tokens;
	prev = NULL;
	while (current)
	{
		if (current->type == E_FILE && prev)
		{
			if (process_single_redirection(prev, current, input_fd, output_fd))
				return (1);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}
