/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:33:32 by mergarci          #+#    #+#             */
/*   Updated: 2025/05/16 19:06:55 by mergarci         ###   ########.fr       */
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
	char	buffer[1024];
	char	*newlimit;
	ssize_t	bytes_read;

	newlimit = ft_strjoin(limit, "\n");
	while (1)
	{
		ft_printf("> ");
		bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		if (ft_strncmp(buffer, newlimit, ft_strlen(newlimit)) == 0)
			break ;
		write(fd, buffer, bytes_read);
	}
	newlimit = ft_memfree(newlimit);
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
