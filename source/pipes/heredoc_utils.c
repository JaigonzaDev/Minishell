/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <cinaquiz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 00:00:00 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/12/07 00:00:00 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

/*
** Check if heredoc was cancelled by ctrl-C
*/
static int	check_heredoc_cancel(int stdin_backup)
{
	if (g_status.last_signal == SIGINT)
	{
		dup2(stdin_backup, STDIN_FILENO);
		g_status.last_exit_status = 130;
		return (1);
	}
	return (0);
}

/*
** Cleanup heredoc resources
*/
static void	cleanup_heredoc(int stdin_backup)
{
	close(stdin_backup);
	g_status.last_signal = 0;
	main_signal_config();
}

/*
** Read and process heredoc line
** Returns: 1 to continue, 0 to break
*/
static int	process_heredoc_line(int fd, char *delimiter, char *line)
{
	if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
	{
		free(line);
		return (0);
	}
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	free(line);
	return (1);
}

/*
** Process heredoc loop
** Returns: 0 if completed normally, 1 if cancelled by ctrl-C
*/
int	process_heredoc_loop(int fd, char *delimiter)
{
	char	*line;
	int		stdin_backup;
	int		cancelled;

	stdin_backup = dup(STDIN_FILENO);
	g_status.last_signal = 0;
	cancelled = 0;
	heredoc_signal_config();
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			cancelled = check_heredoc_cancel(stdin_backup);
			break ;
		}
		if (!process_heredoc_line(fd, delimiter, line))
			break ;
	}
	cleanup_heredoc(stdin_backup);
	return (cancelled);
}
