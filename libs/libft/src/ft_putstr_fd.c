/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <cinaquiz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:32:34 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/12/03 08:33:40 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Sends the string 's' to the specified file descriptor.*/
void	ft_putstr_fd(char *c, int fd)
{
	write(fd, c, ft_strlen(c));
}

/*
int	main(void)
{
	int fd;
	char *c = "hola hola";

	//fd = 0;
	fd = open("test.txt", O_TRUNC | O_RDWR | O_CREAT, 0600);
	//printf("%d", fd);
	if (fd >= 0)
		ft_putstr_fd(c, fd);

	return (0);
}*/