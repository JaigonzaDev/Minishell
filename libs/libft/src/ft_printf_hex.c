/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 19:37:53 by mergarci          #+#    #+#             */
/*   Updated: 2025/02/05 00:04:51 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_printf_hex(char c, char type)
{
	if ((type == 'x') || (type == 'p'))
		ft_putchar_fd(c, 1);
	else
		ft_putchar_fd(ft_toupper(c), 1);
}

int	ft_convert(long int nb, char type, int n_written)
{
	long int	num;
	long int	mod;

	num = nb / 16;
	mod = nb % 16;
	if ((type == 'p') && (n_written == 0))
	{
		ft_putstr_fd("0x", 1);
		n_written = 2;
	}
	if (num > 16)
		n_written = ft_convert(num, type, n_written++);
	else if (num > 0)
	{
		ft_printf_hex(HEX[num], type);
		n_written++;
	}
	ft_printf_hex(HEX[mod], type);
	n_written++;
	return (n_written);
}

int	ft_placeholder_hex(va_list vargs, char type)
{
	long long int	num;
	int				n_written;
	unsigned int	complement;

	n_written = 0;
	num = va_arg(vargs, long long int);
	if ((type == 'x') || (type == 'X'))
		num = (int)num;
	complement = 0;
	if (num == LONG_MIN)
		num = 0;
	if (num < 0)
	{
		complement = (unsigned int)(-num);
		complement = ~complement + 1;
		n_written = ft_convert(complement, type, n_written);
	}
	else
		n_written = ft_convert(num, type, n_written);
	return (n_written);
}
