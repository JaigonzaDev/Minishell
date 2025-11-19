/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_putnbr_fd.c									 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mergarci <mergarci@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/26 21:43:02 by mergarci		  #+#	#+#			 */
/*   Updated: 2024/03/26 21:43:02 by mergarci		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

/*Get the power of 10*/
int	power10(int power)
{
	int	result;

	result = 1;
	while (power > 0)
	{
		result = result * 10;
		power--;
	}
	return (result);
}

/*Get the number of digits*/
int	ft_digit(int nb)
{
	int	iter;

	iter = 1;
	while (nb >= 10)
	{
		nb = nb / 10;
		iter++;
	}
	return (iter);
}

/* Write the given number to the file descriptor.*/
void	ft_write_num(int fd, int num_aux, int is_negative, int is_overflow)
{
	int		coef;
	char	num;
	int		iter;

	iter = ft_digit(num_aux);
	if (!is_overflow)
	{
		if (is_negative)
			write(fd, "-", 1);
		while (iter > 0)
		{
			coef = num_aux / power10(iter - 1);
			num = coef + '0';
			ft_putchar_fd(num, fd);
			num_aux = num_aux - coef * power10(iter - 1);
			iter--;
		}
	}
	else
		write(fd, "-2147483648", 11);
}

/* Sends the number 'n' to the given file descriptor.*/
void	ft_putnbr_fd(int n, int fd)

{
	int		is_overflow;
	int		is_negative;
	int		num_aux;

	is_negative = 0;
	is_overflow = 0;
	num_aux = n;
	if (n < 0)
	{
		is_negative = 1;
		num_aux = -n;
	}
	if ((n == INT_MIN) && is_negative)
	{
		is_overflow = 1;
		ft_write_num(fd, num_aux, is_negative, is_overflow);
	}
	else
		ft_write_num(fd, num_aux, is_negative, is_overflow);
}

/*int main(void)
{
	int fd;
	int n = 164189; 

	fd = open("test.txt", O_TRUNC | O_RDWR | O_CREAT, 0600);
	if (fd >= 0)
		ft_putnbr_fd(n, fd);

	return (0);
}*/