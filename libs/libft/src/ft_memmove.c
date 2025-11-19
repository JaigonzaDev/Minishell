/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_memmove.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mergarci <mergarci@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/14 15:42:56 by mergarci		  #+#	#+#			 */
/*   Updated: 2024/03/15 15:35:44 by mergarci		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

/* Function copies len bytes from string src to string dst. The two strings 
may overlap; the copy is always done in a non-destructive manner.*/
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*d;
	const char	*s;

	d = (char *)dst;
	s = (const char *)src;
	if (src != NULL || dst != NULL)
	{
		if (src < dst)
		{
			while (len--)
				d[len] = s[len];
		}
		else
		{
			while (len--)
				*d++ = *s++;
		}
	}
	return (dst);
}

/*int main(void)
{
char str[] = "abcdefghijk";
	char str2[] = "abcdefghijk";
	size_t size = 3;
	int i = 2;
	printf("origen: %s\n", str);
	printf("memmove: %s\n", memmove((void *)(str + i), (const void*)str, size));
	printf("ft :%s\n", ft_memmove((void *)(str2 + i), (const void*)str2, size));
	return (0);
}*/