/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handlers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <cinaquiz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:37:47 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/12/04 18:58:12 by cinaquiz         ###   ########.fr       */
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
/*
** Handle heredoc redirection
*/
int	handle_redirect_heredoc(t_token *current, int *input_fd)
{
	int		fd[2];
	char	*delimiter;
	int		cancelled;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	delimiter = current->token;
	if (!delimiter)
		return (1);
	cancelled = process_heredoc_loop(fd[1], delimiter);
	close(fd[1]);
	if (cancelled)
	{
		close(fd[0]);
		return (130);
	}
	if (*input_fd != 0)
		close(*input_fd);
	*input_fd = fd[0];
	return (0);
}
