/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_itoa.c										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mergarci <mergarci@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/25 18:01:44 by mergarci		  #+#	#+#			 */
/*   Updated: 2024/03/25 18:01:44 by mergarci		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

/* Function that count the number of digits that input has */
static int	ft_digit(int nb)
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

/* Function that allocate memory to the string. It takes if number is negative
or if the number is the negative number */
static char	*ft_strnbr(int digits, int num_aux, int is_neg, int is_overflow)
{
	char	*ptr;

	if (is_overflow)
		return (ft_strdup("-2147483648"));
	if (num_aux == 0)
		return (ft_strdup("0"));
	ptr = ft_calloc(digits + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	while (digits >= 0)
	{
		if (digits == 0 && is_neg)
			ptr[0] = '-';
		digits--;
		if (digits >= 0)
		{
			ptr[digits] = num_aux % 10 + '0';
			num_aux = num_aux / 10;
		}
	}
	return (ptr);
}

/* Using malloc(3), generate a string that represents the integer value 
received as an argument. Negative numbers have to be managed.*/
char	*ft_itoa(int n)
{
	int	digits;
	int	n_aux;
	int	is_negative;
	int	is_overflow;

	n_aux = n;
	is_negative = 0;
	is_overflow = 0;
	digits = 0;
	if (n != -2147483648)
	{
		if (n < 0)
		{
			n_aux = -n;
			is_negative = 1;
		}
		digits = ft_digit(n_aux);
		if (is_negative)
			digits++;
		return (ft_strnbr(digits, n_aux, is_negative, is_overflow));
	}
	else
		return (ft_strnbr(11, 2147483647, 1, 1));
}

/*int main()
{
	char *str;
	int n = 1000034;
	str = ft_itoa(n);
	printf("%d\n%s\n", n, str);
	return 0;
}*/