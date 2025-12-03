/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fd_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <cinaquiz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:37:58 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/12/03 08:38:00 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

/*
** Duplicate and close fd
*/
void	ft_dup_close(int fd1, int fd2, int fd_close)
{
	dup2(fd1, fd2);
	ft_closefd(fd1);
	ft_closefd(fd_close);
}

/*
** Close fd if valid
*/
void	ft_closefd(int fd)
{
	if (fd != -1)
		close(fd);
}

/*
** Handle parent fd
*/
void	ft_parent_fd(int *fd, int *fd_saved)
{
	ft_closefd(fd[WRITE]);
	fd_saved[READ] = fd[READ];
}

/*
** Close all fds
*/
void	ft_close_fds(int *fd1, int *fd2)
{
	ft_closefd(fd1[READ]);
	ft_closefd(fd1[WRITE]);
	ft_closefd(fd2[READ]);
	ft_closefd(fd2[WRITE]);
}

/*
** Open file with mode
*/
int	ft_openfil(char *name_file, int open_mode)
{
	int	fd;

	if (open_mode == O_RDONLY)
		fd = open(name_file, open_mode);
	else
		fd = open(name_file, open_mode, 0644);
	if (fd == -1)
		perror(name_file);
	return (fd);
}
