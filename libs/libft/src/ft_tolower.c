/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_tolower.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mergarci <mergarci@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/15 15:41:23 by mergarci		  #+#	#+#			 */
/*   Updated: 2024/03/15 15:45:38 by mergarci		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

/* Function converts an upper-case letter to the corresponding
lower-case letter.*/
int	ft_tolower(int c)
{
	if (ft_isalpha(c) && (c >= 'A' && c <= 'Z'))
		c = c + 32;
	return (c);
}

/*int	main(void)
{
	int c = 'A';
	printf("tolower: %c pasa a %c \n", c, tolower(c));
	printf("ft_tolower: %c pasa a %c \n", c, ft_tolower(c));
}	*/
