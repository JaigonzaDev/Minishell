/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <cinaquiz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:32:03 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/12/03 08:33:47 by cinaquiz         ###   ########.fr       */
/*                                                                            */
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