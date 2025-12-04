/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handlers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <cinaquiz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:37:47 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/12/04 17:42:18 by cinaquiz         ###   ########.fr       */
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
	int		fd[2];
	char	*line;
	char	*delimiter;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	delimiter = current->token;
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", 2);
			ft_putstr_fd(delimiter, 2);
			ft_putstr_fd("')\n", 2);
			break ;
		}
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	if (*input_fd != 0)
		close(*input_fd);
	*input_fd = fd[0];
	return (0);
}
