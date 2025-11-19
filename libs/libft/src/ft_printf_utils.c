/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 11:21:59 by mergarci          #+#    #+#             */
/*   Updated: 2025/05/03 19:45:20 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*Print a decimal number*/
int	ft_placeholder_d(va_list vargs)
{
	int		n_written;
	char	*str_num;

	str_num = ft_itoa(va_arg(vargs, int));
	n_written = ft_strlen(str_num);
	ft_putstr_fd(str_num, 1);
	str_num = ft_memfree(str_num);
	return (n_written);
}

int	ft_placeholder_u(va_list vargs)
{
	int				n_written;
	unsigned int	num;
	unsigned int	divisor;

	n_written = 0;
	divisor = 1;
	num = va_arg(vargs, unsigned int);
	while (num / divisor >= 10)
		divisor *= 10;
	while (divisor > 0)
	{
		ft_putnbr_fd(num / divisor, 1);
		num %= divisor;
		divisor /= 10;
		n_written++;
	}
	return (n_written);
}

/*Print a string and it returns number of character 
printed*/
int	ft_print_str(char *str)
{
	int		n;

	n = 0;
	while (str[n])
	{
		ft_putchar_fd(str[n], 1);
		n++;
	}
	return (n);
}
