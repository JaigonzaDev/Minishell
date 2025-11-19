/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_isdigit.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mergarci <mergarci@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/11 15:13:59 by mergarci		  #+#	#+#			 */
/*   Updated: 2024/03/12 14:49:36 by mergarci		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

/* Function tests for a decimal digit character */
int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/*int	main(void)
{
	int	c;

	c = 47;
	printf("valor de isdigit: %d\n", isdigit(c));
	printf("valor de ft_isdigit: %d\n", ft_isdigit(c));
	
	return 1;
}*/