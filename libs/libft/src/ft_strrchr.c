/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strrchr.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mergarci <mergarci@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/21 10:59:16 by mergarci		  #+#	#+#			 */
/*   Updated: 2024/03/21 11:40:08 by mergarci		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

/* Function locates the last occurrence of c in the string pointed to by s*/
char	*ft_strrchr(const char *s, int c)
{
	int				found_char;
	unsigned char	c_aux;
	char			*ptr;

	ptr = (char *)s;
	c_aux = c;
	found_char = 0;
	while (*s != '\0')
	{
		if (*s == c_aux)
		{
			found_char = 1;
			ptr = (char *)s;
		}
		s++;
	}
	if (c_aux == 0 && *s == '\0')
		return ((char *)s);
	if (!found_char)
		return (NULL);
	return (ptr);
}

/*int	main(void)
{
	char	str1[100] = "the cake is a lie";
	char	str2[100] = "the cake is a lie";
	int c = 1024;
	char *fun = strrchr(str1, c);
	char *my = ft_strrchr(str2, c);
	
	printf("Cadena: %s\n", str1);
	printf("Resultado de la funcion es: %s\n", fun);
	printf("Resultado de mi funcion es: %s\n", my);
	printf("comparacion funciones: %d\n", strcmp(fun, my));
	
	return (0);
}*/
