/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_setup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <cinaquiz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:37:50 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/12/04 18:44:00 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

/*
** Process single redirection
*/
int	process_single_redirection(t_token *prev, t_token *current,
		int *input_fd, int *output_fd)
{
	int	status;

	if (prev->type == E_REDIRECT_IN)
		return (handle_redirect_in(current, input_fd));
	else if (prev->type == E_REDIRECT_OUT)
		return (handle_redirect_out(current, output_fd));
	else if (prev->type == E_REDIRECT_APPEND)
		return (handle_redirect_append(current, output_fd));
	else if (prev->type == E_REDIRECT_HEREDOC)
	{
		status = handle_redirect_heredoc(current, input_fd);
		if (status == 130)
			return (130);
		return (status);
	}
	return (0);
}

/*
** Setup redirections
*/
int	setup_redirections(t_token *tokens, int *input_fd, int *output_fd)
{
	t_token	*current;
	t_token	*prev;
	int		status;

	current = tokens;
	prev = NULL;
	while (current)
	{
		if ((current->type == E_FILE || current->type == E_DELIMITER) && prev)
		{
			status = process_single_redirection(prev, current, input_fd,
					output_fd);
			if (status != 0)
				return (status);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}
