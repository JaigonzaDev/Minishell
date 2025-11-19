/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_isascii.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mergarci <mergarci@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/12 15:00:16 by mergarci		  #+#	#+#			 */
/*   Updated: 2024/03/12 15:03:04 by mergarci		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

/* Test for any ASCII character */
int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

/*int	main(void)
{
	int	c;

	c = 222;
	printf("valor de isascii: %d\n", isascii(c));
	printf("valor de ft_isascii: %d\n", ft_isascii(c));
	
	return 1;
}*/