/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <cinaquiz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:37:56 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/12/03 08:38:00 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

/*
** Print help message
*/
void	ft_print_help(void)
{
	ft_printf("ERROR: Invalid inputs. Please introduce:\n");
	ft_printf("\t./pipex_bonus infile com1 com2 ... comn outfile\n");
	ft_printf("If you want to use HERE_DOC:\n");
	ft_printf("\t./pipex_bonus here_doc <LIMIT> command1 command2 outfile\n");
	exit(EXIT_FAILURE);
}

/*
** Count strings in array
*/
int	ft_count_string(char **string)
{
	int	len;

	len = 0;
	while (string[len])
		len++;
	return (len);
}

/*
** Create pipe
*/
void	ft_create_fd(int *fd)
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
}

/*
** Read heredoc input
*/
void	ft_read_heredoc(int fd, char *limit)
{
	char	*line;
	int		limit_len;

	limit_len = ft_strlen(limit);
	while (1)
	{
		ft_printf("> ");
		line = ft_gnl(STDIN_FILENO, NULL);
		if (!line)
			break ;
		if (ft_strncmp(line, limit, limit_len) == 0 && (line[limit_len] == '\0'
				|| line[limit_len] == '\n'))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

/*
** Handle heredoc process
*/
void	ft_heredoc(int *files, char *limit)
{
	int	fd[2];
	int	pid;

	ft_create_fd(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[READ]);
		ft_read_heredoc(fd[WRITE], limit);
		close(fd[WRITE]);
		exit(errno);
	}
	else
	{
		waitpid(pid, NULL, 0);
		ft_parent_fd(fd, files);
	}
}
