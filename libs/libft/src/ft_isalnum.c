/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_isalnum.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mergarci <mergarci@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/12 14:51:59 by mergarci		  #+#	#+#			 */
/*   Updated: 2024/03/12 14:53:59 by mergarci		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

/* Alphanumeric character test. Check if ft_isalpha or isdigit is true. */
int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}

/*int	main(void)
{
	int	c;

	c = 47;
	printf("valor de isalnum: %d\n", isalnum(c));
	printf("valor de ft_isalnum: %d\n", ft_isalnum(c));
	
	return 1;
}*/