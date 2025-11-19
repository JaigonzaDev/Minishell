/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_isprint.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mergarci <mergarci@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/12 15:05:45 by mergarci		  #+#	#+#			 */
/*   Updated: 2024/03/12 15:26:11 by mergarci		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

/* Function tests for a decimal digit character*/
int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
/*
int	main(void)
{
	int	c;

	c = 32;
	printf("valor de isprint: %d\n", isprint(c));
	printf("valor de ft_isprint: %d\n", ft_isprint(c));
	
	return 1;
}*/