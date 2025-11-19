/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_memcmp.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mergarci <mergarci@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/22 11:43:41 by mergarci		  #+#	#+#			 */
/*   Updated: 2024/03/22 11:53:34 by mergarci		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

/* Function compares byte string s1 against byte string s2. Both strings are
assumed to be n bytes long.*/
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int				diff;
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	diff = 0;
	i = 0;
	while ((s1++ != NULL || s2++ != NULL) && diff == 0 && i < n)
	{
		diff = ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return (diff);
}

/*int	main(void)
{
	char	str1[100] = "holi hola\200";
	char 	str2[100] = "holi hola\0";
	int n;

	n = 15;
	printf("La cadena 1 es: %s\n", str1);
	printf("La cadena 2 es: %s\n", str2);
	printf("Resultado de la funcion es: %d\n", memcmp(str1,str2,n));
	printf("El resultado de mi funcion es: %d\n", ft_memcmp(str1, str2, n));
	return (0);
}*/