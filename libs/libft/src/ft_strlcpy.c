/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strlcpy.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mergarci <mergarci@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/02/20 15:56:45 by mergarci		  #+#	#+#			 */
/*   Updated: 2024/03/20 16:00:42 by mergarci		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

/* Function copy strings. It is designed to be safer, more consistent*/
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	else
	{
		while (src[i] != '\0' && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
		if (i < ft_strlen(src))
			return (ft_strlen(src));
	}
	return (i);
}

/*int	main (void)
{
	char	str[40] = "123456";
	char	dst0[40] = "";
	char	dst1[40] = "";
	int n;
	size_t fun;
	size_t my;
	
	n = 0;
	fun = strlcpy(dst0, str, n);
	my = ft_strlcpy(dst1, str,n);
	printf("La cadena es: %s\n", str);
	printf("Resultado de strlcpy: %lu, %s\n", fun, dst0);
	printf("Resultado de ft_strlcpy: %lu, %s\n", my, dst1);
	printf("diferencia de resultados: %d\n", strcmp(dst0, dst1));
	printf("comparacion resultados: %lu\n", fun - my);
	
	return (0);
}*/
