/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_toupper.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mergarci <mergarci@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/15 14:22:13 by mergarci		  #+#	#+#			 */
/*   Updated: 2024/03/15 15:40:23 by mergarci		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

/* Function converts a lower-case letter to the corresponding 
upper-case letter.*/
int	ft_toupper(int c)
{
	if (ft_isalpha(c) && (c >= 'a' && c <= 'z'))
		c = c - 32;
	return (c);
}

/*int	main(void)
{
	int c = 'a';
	printf("toupper: %c pasa a %c \n", c, toupper(c));
	printf("ft_toupper: %c pasa a %c \n", c, ft_toupper(c));
}	*/
