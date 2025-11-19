/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_putstr_fd.c									 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mergarci <mergarci@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/26 21:31:15 by mergarci		  #+#	#+#			 */
/*   Updated: 2024/03/26 21:31:15 by mergarci		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

/* Sends the string 's' to the specified file descriptor.*/
void	ft_putstr_fd(char *c, int fd)
{
	write(fd, c, ft_strlen(c));
}

/*
int main(void)
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