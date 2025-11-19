/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_putendl_fd.c									:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mergarci <mergarci@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/26 21:40:29 by mergarci		  #+#	#+#			 */
/*   Updated: 2024/03/26 21:40:29 by mergarci		 ###   ########.fr	   */
/*																			*/
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