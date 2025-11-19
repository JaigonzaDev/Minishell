/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_memcpy.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mergarci <mergarci@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/14 11:07:17 by mergarci		  #+#	#+#			 */
/*   Updated: 2024/03/15 14:18:36 by mergarci		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

/* function copies n bytes from memory area src to memory area dst. If dst
and src overlap, behavior is undefined.*/
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	if (src != NULL || dst != NULL)
	{
		while (n--)
			*d++ = *s++;
	}
	return (dst);
}

/*int main(void)
{
	char str1[7] = "abcdef";
	char dst1[7] = "";

	printf("The string: %s\n", str1);
	memcpy(dst1, str1, 10);
	printf("New string: %s\n", dst1 );
	
	*str1 = "abcdef";
	printf("\nstr1: %s\n", str1);
	printf("The string: %s\n", str1);
	memmove((str1+6), str1, 10);
	printf("New string: %s\n", str1);


}*/