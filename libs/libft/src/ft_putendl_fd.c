/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <cinaquiz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:32:30 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/12/03 08:33:41 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Send the string 's' to the given file descriptor, followed by a new line*/
void	ft_putendl_fd(char *c, int fd)
{
	write(fd, c, ft_strlen(c));
	write(fd, "\n", 1);
}

/*int main(void)
{
	int fd;
	char *c = "hola hola";

	//fd = 0;
	fd = open("test.txt", O_TRUNC | O_RDWR | O_CREAT, 0600);
	//printf("%d", fd);
	if (fd >= 0)
		ft_putendl_fd(c, fd);

	return (0);
}*/