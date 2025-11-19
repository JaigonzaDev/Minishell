/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_memset.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mergarci <mergarci@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/12 18:11:46 by mergarci		  #+#	#+#			 */
/*   Updated: 2024/03/20 15:30:46 by mergarci		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

/* Fill a byte string with a byte value */
void	*ft_memset(void *b, int c, size_t len)
{
	size_t			cont;
	unsigned char	*ptr;

	ptr = b;
	cont = 0;
	while (cont < len)
		ptr[cont++] = (unsigned char)c;
	return (b);
}

/*int	main(void)
{
	int	c;
	char str1[50] = "GeeksForGeeks is for programming geeks.";
	int int1[4] = {1, 2, 3, 4}; 
	char str2[50] = "GeeksForGeeks is for programming geeks.";
	printf("Before memset(): %s\n", str1);
	printf("Before memset(): %s\n", str2);
	memset(str1 + 1, 'x', 6*sizeof(char));
	ft_memset(str2 + 1, 'x', 6*sizeof(char));
	printf("After memset():  %s\n", str1);
	printf("After ft_memset():  %s\n", str2);

	return (0);
}*/