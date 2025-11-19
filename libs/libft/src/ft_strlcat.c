/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strlcat.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mergarci <mergarci@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/02/22 17:20:42 by mergarci		  #+#	#+#			 */
/*   Updated: 2024/03/20 15:29:32 by mergarci		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

/* Function concatenate strings. It is designed to be safer, more consistent*/
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_dest;
	size_t	len_src;
	size_t	i;

	len_src = ft_strlen(src);
	len_dest = ft_strlen(dst);
	i = 0;
	if (dstsize <= len_dest)
		return (dstsize + len_src);
	i = len_dest;
	while (i < (dstsize - 1) && *src != '\0')
	{
		*(dst + i++) = *src++;
	}
	dst[i++] = '\0';
	return (len_dest + len_src);
}

/*int	main(void)
{
	char 			str2[100];
	char			str1[100] = "lorem ipsum dolor sit amet";
	char			str3[100] = "lorem ipsum dolor sit amet";
	size_t fun;
	size_t my;
	unsigned int	m;
	str2[1] = 'a';
	//printf("strlen de input: %zu\n",ft_strlen(str2));
	m = 15;
	printf("La cadena src es: %s\n", str2);
	printf("La cadena dst es: %s\n", str1);
	fun = strlcat(str1, str2, m);
	my = ft_strlcat(str3, str2, m);
	printf("Resultado de la funcion es: %lu, %s\n", fun, str1);
	printf("Resultado de mi funcion es: %lu, %s\n", my, str3);
	printf("comparacion funciones: %d\n", strcmp(str1, str3));
	printf("comparacion resultados: %lu\n", fun - my);
	return (0);
}*/
