/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fd_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:34:59 by mergarci          #+#    #+#             */
/*   Updated: 2025/05/16 19:07:50 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

/*It duplicates fd1 to fd2 and closes it. Besides, it closes fd_close*/
void	ft_dup_close(int fd1, int fd2, int fd_close)
{
	dup2(fd1, fd2);
	ft_closefd(fd1);
	ft_closefd(fd_close);
}

/*Closes fd checking if it exits */
void	ft_closefd(int fd)
{
	if (fd != -1)
		close(fd);
}

/*Only to be used at parent process. It closes fd[WRITE], copies
 fd[READ] to the previous fd*/
void	ft_parent_fd(int *fd, int *fd_saved)
{
	ft_closefd(fd[WRITE]);
	fd_saved[READ] = fd[READ];
}

/*Closes all file descriptors*/
void	ft_close_fds(int *fd1, int *fd2)
{
	ft_closefd(fd1[READ]);
	ft_closefd(fd1[WRITE]);
	ft_closefd(fd2[READ]);
	ft_closefd(fd2[WRITE]);
}

/*Functions to open files depending of the mode. Besides,
it checks if the file has been opened properly*/
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
