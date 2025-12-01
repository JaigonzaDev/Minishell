/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handlers.c                             :+:      :+:    :+:   */
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
** Handle input redirection
*/
int	handle_redirect_in(t_token *current, int *input_fd)
{
	if (*input_fd != 0)
		close(*input_fd);
	*input_fd = open(current->token, O_RDONLY);
	if (*input_fd == -1)
	{
		perror(current->token);
		return (1);
	}
	return (0);
}

/*
** Handle output redirection
*/
int	handle_redirect_out(t_token *current, int *output_fd)
{
	if (*output_fd != 1)
		close(*output_fd);
	*output_fd = open(current->token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*output_fd == -1)
	{
		perror(current->token);
		return (1);
	}
	return (0);
}

/*
** Handle append redirection
*/
int	handle_redirect_append(t_token *current, int *output_fd)
{
	if (*output_fd != 1)
		close(*output_fd);
	*output_fd = open(current->token, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*output_fd == -1)
	{
		perror(current->token);
		return (1);
	}
	return (0);
}

/*
** Handle heredoc redirection
*/
int	handle_redirect_heredoc(t_token *current, int *input_fd)
{
	(void)current;
	(void)input_fd;
	return (0);
}
